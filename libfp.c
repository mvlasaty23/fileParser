/* 
 * File:   main.c
 * Author: michael.vlasaty
 *
 * Created on 29. März 2013, 19:12
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

#define LINE_LENGTH 128

char *get_line(FILE *fp){
    
    size_t IncrBuff = LINE_LENGTH;
    char *buffer = (char*)malloc(IncrBuff);
    
    if(buffer == NULL){
        fprintf(stderr, "Failed to allocate %d bytes\n", IncrBuff);
        exit(EXIT_FAILURE);
    }
    
    buffer[0] = '\0'; //leerer string
    
    
        while(fgets(&buffer[strlen(buffer)], IncrBuff, fp) != NULL){
            size_t len = strlen(buffer);
            if(buffer[len - 1] == '\n'){
                break;
                
            }else{
            
                IncrBuff += LINE_LENGTH;
                buffer = (char*)realloc(buffer, IncrBuff);
            
                if(buffer == NULL){
                    fprintf(stderr, "ERROR: can't realloc!\n");
                    exit(EXIT_FAILURE);
                }
            
            }

        }
    
    return buffer;
}

int line_count(char *file){
    
    FILE *fp = fopen(file, "r");
    char buff[LINE_LENGTH];
    int cnt = 0;
    
    while(fgets(buff, LINE_LENGTH, fp) != NULL) cnt++;
    
    fclose(fp);
    
    return cnt;
}

int row_count(char *file, char *delimiter){
    
    FILE *fp = fopen(file, "r");
    char buff[LINE_LENGTH];
    int cnt = 0;
    char *line;
    char *row;
    char ch[2] = "\n";
    
    while(fp != EOF){
        
        line = get_line(fp);
        
        if(*line == NULL)
            break;
        
        for(row = strtok(line, delimiter); row != NULL; row = strtok(NULL, delimiter)){

            cnt++;
            
            if(strstr(row, ch) != NULL){
                return cnt;
            }
        }
    }
    
    fclose(fp);
    
    return cnt;
}

void chomp(char *string){
    string[strcspn(string, "\n")] = '\0';
}