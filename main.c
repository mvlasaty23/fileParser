/* 
 * File:   main.c
 * Author: michael.vlasaty
 *
 * Created on 29. März 2013, 19:10
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libfp.h>

/*
 *Programm liest Textfile von stdin
 * und gibt dieses dann zeile fuer zeile aus. 
 */
int main(int argc, char** argv) {

    char ch;
    char *name = "";
    
    
    while((ch = getopt(argc, argv,"hi:")) != EOF){
        switch(ch){
            case 'h':
                puts("Usage: fileparser.exe -i [INPUT FILENAME]");
                return(EXIT_FAILURE);
            case 'i':
                name = optarg;
                if(name == 0){
                    fprintf(stderr, "Es wurde kein Dateiname angegeben!\n");
                    return(EXIT_FAILURE);
                }
                break;
            default:
                puts("Usage: fileparser.exe -i [INPUT FILENAME]");
                return(EXIT_FAILURE);
        }
    }
    argc -= optind;
    argv += optind;
    
    FILE *fp = fopen(name, "r");
    if(fp == NULL){
        printf("Datei: %s konnte nicht geöffnet werden!\n", name);
        return(EXIT_FAILURE);
    }
    
    char *line;
    int lines_count = line_count(name);
    char elements[lines_count][6][40];
    char *row;
    int i = 0;
    int j = 0;
    char *delimiter = ",";
    while(fp != EOF){
        line = get_line(fp);
        
        if(*line == NULL)
            break;
        
        //printf("%s", line);
        
        for(row = strtok(line, delimiter); row != NULL; row = strtok(NULL, delimiter)){
            
            chomp(row);
            strcpy(elements[i][j], row);
            //printf("[%i][%i]%s ", i, j, row);
            j++;
            
            if(j >= 6){
                j = 0;  
                i++;
            }
        }
        
        free(line);
    }
    fclose(fp);
    char *undefE = "\"\"";
    
    for(i = 0; i < lines_count; i++){
        for(j = 0; j < 6; j++){
            printf("%s ", elements[i][j]);
        }
        printf("\n");
        if(strcmp(elements[i][4], undefE) == 0)
            printf("Umeleiten!!\n");
    }
    
    int row_count = row_count(name, delimiter);
    printf("File has %i rows\n", row_count);
    
    return (EXIT_SUCCESS);
}

