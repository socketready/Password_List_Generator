/**
 *  Password list generator
 *
 *  This program will create a dictionary list of all possible
 *  password combinations of characters.  All character sets can
 *  be selected to create a main list for input of the generator.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//sizes for each array
#define NUM_SIZE 10
#define ALPH_SIZE 26
#define SPE_SIZE 22

void generator(int *list, int list_size, char *temp, int index, int n, FILE *out);

//declare decimal values of chars
int num[NUM_SIZE]   = {48,49,50,51,52,53,54,55,56,57};
int cap[ALPH_SIZE]  = {65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90};
int low[ALPH_SIZE]  = {97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122};
int spe[SPE_SIZE]   = {33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,58,59,60,61,62,63,64};

int main (int argc, char *argv[]){
    char *temp;
    int min, max, i, type, j;
    FILE *out;
    int *list;
    int list_size;
    
    // if invalid input or argument count display options
    if(argc != 5){
        printf("Usage: %s <min length> <max length> <type> <output>\n", argv[0]);
        printf("Types:\n");
        printf(" 1 - numeric (0-9)\n");
        printf(" 2 - alpha (uppercase only)\n");
        printf(" 3 - alpha (lowercase only)\n");
        printf(" 4 - alpha numeric (lowercase only)\n");
        printf(" 5 - alpha numeric (uppercase only)\n");
        printf(" 6 - alpha numeric (upper/lower)\n");
        printf(" 7 - alpha numeric (upper/lower) + special chars\n");
        exit(0);
    }
    
    //parse input
    min = atoi(argv[1]);
    max = atoi(argv[2]);
    type = atoi(argv[3]);
    j = 0;
    
    // create list of chosen chars for passwords
    switch(type){
        case 1:
            list_size = NUM_SIZE;
            list = (int *)malloc(NUM_SIZE * sizeof(int));
            for(i=0; i<NUM_SIZE; i++)
                list[i] = num[i];
            break;
        case 2:
            list_size = ALPH_SIZE;
            list = (int *)malloc(ALPH_SIZE * sizeof(int));
            for(i=0; i<ALPH_SIZE; i++)
                list[i] = cap[i];
            break;
        case 3:
            list_size = ALPH_SIZE;
            list = (int *)malloc(ALPH_SIZE * sizeof(int));
            for(i=0; i<ALPH_SIZE; i++)
                list[i] = low[i];
            break;
        case 4:
            list_size = ALPH_SIZE + NUM_SIZE;
            list = (int *)malloc((ALPH_SIZE + NUM_SIZE) * sizeof(int));
            for(i=0; i<NUM_SIZE; i++)
                list[j++] = num[i];
            for(i=0; i<ALPH_SIZE; i++)
                list[j++] = low[i];
            break;
        case 5:
            list_size = ALPH_SIZE + NUM_SIZE;
            list = (int *)malloc((ALPH_SIZE + NUM_SIZE) * sizeof(int));
            for(i=0; i<NUM_SIZE; i++)
                list[j++] = num[i];
            for(i=0; i<ALPH_SIZE; i++)
                list[j++] = cap[i];
            break;
            break;
        case 6:
            list_size = ALPH_SIZE + NUM_SIZE + ALPH_SIZE;
            list = (int *)malloc((ALPH_SIZE + NUM_SIZE + ALPH_SIZE) * sizeof(int));
            for(i=0; i<NUM_SIZE; i++)
                list[j++] = num[i];
            for(i=0; i<ALPH_SIZE; i++)
                list[j++] = low[i];
            for(i=0; i<ALPH_SIZE; i++)
                list[j++] = cap[i];
            break;
        case 7:
            list_size = ALPH_SIZE + NUM_SIZE + ALPH_SIZE + SPE_SIZE;
            list = (int *)malloc((ALPH_SIZE + NUM_SIZE + ALPH_SIZE + SPE_SIZE) * sizeof(int));
            for(i=0; i<NUM_SIZE; i++)
                list[j++] = num[i];
            for(i=0; i<ALPH_SIZE; i++)
                list[j++] = low[i];
            for(i=0; i<ALPH_SIZE; i++)
                list[j++] = cap[i];
            for(i=0; i<SPE_SIZE; i++)
                list[j++] = spe[i];
            break;
        default:
            printf("Incorrect type set\n");
            exit(1);
    }
    
    //open file for writing exit if error
    out = fopen(argv[4], "wt");
    if(out == NULL){
        printf("Error opening file for writing\n");
        exit(1);
    }
    
    //alloc temp string
    temp = malloc(sizeof(char) * max);
    //start main loop for generator
    for(i=min; i<max+1; i++)
        generator(list, list_size, temp, 0, i, out);

    //close program
    free(temp);
    free(list);
    fclose(out);
    return 0;
}

/**
 *  generator
 *  generates every combination of passwords given a list of chars and range 
 *  of password lengths.
 *  
 *  output:  writes each password to a file 'out'
 */
void generator(int *list, int list_size, char *temp, int index, int n, FILE *out){
    if(index == n){
        fprintf(out, "%s\n", temp);
    }else{
        int i;
        for(i=0; i<list_size; i++){
            temp[index] = (char)list[i];
            generator(list, list_size, temp, index+1, n, out);
        }
    }
}





