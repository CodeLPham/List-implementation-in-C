//
//  Lex.c
//
//
//  Created by Leon Pham on 10/13/17.
//  Copyright © 2017 Leon Pham. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"


#define MAX_LEN 160

int main(int argc, const char * argv[]) {
    
    if(argc != 3){
        printf("USAGE FORMAT: %s <input file> <output file>\n",argv[0]);
        exit(1);
    }
    
    List L = newList();
    int line_count = 0, count=0;
    FILE *in, *out;
    int k = 0;
    char lines[MAX_LEN];
    char *line_ptr[MAX_LEN];
    
    in = fopen(argv[1],"r");
    
    out = fopen(argv[2], "w");
    
    if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    
    //Get number of lines
    
    while(fgets(lines, MAX_LEN,in) != NULL){
        line_count++;
    }
    char line[line_count-1][MAX_LEN];
    
    fclose(in); //close to start at the top
    in = fopen(argv[1], "r"); //reopen file
    
    
    for(int i = 0; i < line_count;i++){
        line_ptr[i] = calloc(1, sizeof(char*[MAX_LEN]));
    }
    
    while(fgets(lines, MAX_LEN,in) != NULL){
        strcpy(line_ptr[count],lines);
        count++;
    }
    
    append(L,0); //append 0
    for(int i = 1; i < line_count; i++){
        k = i -1;
        char *temp_ptr = line[i];
        moveBack(L);
        
        while(strcmp(temp_ptr, line[get(L)]) <= 0 && k>= 0){
            movePrev(L);
            k--;
        }
        if(index(L) == -1){
            prepend(L,i);
        }
        else
            insertAfter(L, i);
    }
    
    for(moveFront(L); index(L) >= 0; moveNext(L)){
        fprintf(out, "%s", line_ptr[get(L)]);
    }
    
    freeList(&L);
    fclose(in);
    fclose(out);
    for(int i = 0; i <= line_count;i++) free(line_ptr[i]);
    
    return 0;
}


