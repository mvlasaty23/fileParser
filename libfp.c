/* 
 * File:   main.c
 * Author: mvlasaty
 *
 * Created on 03. April 2013, 15:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 110
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(*(x)))

char *getLine(FILE *csv){
    
    //define our initial size to alloc for the lines we read
    const size_t bufIncrSize = 128;
    size_t bufSize = bufIncrSize;
    char *pLine = (char *)malloc(bufIncrSize);
    
    //handle malloc error
    if(pLine == NULL){
        fprintf("stderr", "Failed to allocate %d bytes\n", bufIncrSize);
        exit(EXIT_FAILURE);
    }
    
    pLine[0] = '\0'; //make empty string
    
    /*get string chunk from file as long fgets doesn't return NULL
    * if we find a newline in our string we can stop
    * else we have to realloc double size of memory
    * and handle realloc error
    */
    while(fgets(&pLine[strlen(pLine)], bufIncrSize, csv) != NULL){
        if (pLine[strlen(pLine) - 1] == '\n'){
            break;
        }
        
        bufSize += bufIncrSize;
        pLine = (char *)realloc(pLine, bufSize);
        
        if(pLine == NULL){
            fprintf("stderr", "ERROR: can't realloc!\n");
            exit(EXIT_FAILURE);
        }
            
    }
    return pLine; //return line don't forget to free allocated heap mem!
}

int line_cnt(char *file){
    
    FILE *pt = fopen(file, "r");
    char buff[LINE_LENGTH];
    int cnt = 0;
    
    while(fgets(buff, LINE_LENGTH, pt) != NULL) cnt++;
    
    return cnt;
}

