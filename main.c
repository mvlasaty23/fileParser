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
    while(fp != EOF){
        line = get_line(fp);
        
        if(*line == NULL)
            break;
        
        printf("%s", line);
        free(line);
    }
    fclose(fp);
    
    int lines_count = line_count(name);
    printf("\nFile beinhaltet %i Zeilen.\n", lines_count);
    
    return (EXIT_SUCCESS);
}

