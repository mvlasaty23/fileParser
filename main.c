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
    char *delimiter = NULL;
    int isSet = 4;
    
    //split output should be args TODO!
    char *out1 = "companys.csv";
    char *out2 = "contacts.csv";
    FILE *op1 = fopen(out1, "w");
    FILE *op2 = fopen(out2, "w");
    
    while((ch = getopt(argc, argv,"hi:d:r:")) != EOF){
        switch(ch){
            case 'h'://print usage
                puts("Usage: fileparser.exe -i [INPUT FILENAME] -d \"DELIMITER\" -r ROW NUMBER ");
                return(EXIT_FAILURE);
            case 'i'://get input file
                name = optarg;
                if(name == 0){
                    fprintf(stderr, "Es wurde kein Dateiname angegeben!\n");
                    return(EXIT_FAILURE);
                }
                break;
            case 'd'://set delimiter default ","
                delimiter = optarg;
                break;
            case 'r'://set row number at which we are looking
                isSet = optarg;
                break;
            default:
                puts("Usage: fileparser.exe -i [INPUT FILENAME]");
                return(EXIT_FAILURE);
        }
    }
    argc -= optind;
    argv += optind;
    
    //open file exit if undef
    FILE *fp = fopen(name, "r");
    if(fp == NULL){
        printf("Datei: %s konnte nicht geöffnet werden!\n", name);
        return(EXIT_FAILURE);
    }
    
    //set default delimiter
    if(delimiter == NULL){
        delimiter = ",";
    }
    
    char *line;
    int lines_count = line_count(name);
    int rows_count = row_count(name, delimiter);
    char elements[lines_count][rows_count][40];
    int i = 0;
    int j = 0;
    
    /*
     * Get line by line and
     * chomp off newline char
     * split each row into array elemnts for later use
     */
    while(fp != EOF){
        line = get_line(fp);
        
        if(*line == NULL)
            break;
    
        char *row;
        
        for(row = strtok(line, delimiter); row != NULL; row = strtok(NULL, delimiter)){
            
            chomp(row);
            strcpy(elements[i][j], row);
            j++;
            
            if(j >= rows_count){
                j = 0;  
                i++;
            }
        }
        free(line);
    }
    fclose(fp);
    
    char *undefE = "\"\"";
    FILE *fpout;
    
    /*
     * check if the row that we are looking for
     * is empty or not
     * so we can decide in which file we put it
     */
    for(i = 0; i < lines_count; i++){

        if(strcmp(elements[i][isSet], undefE) == 0){
            fpout = op1;
        }else{
            fpout = op2;
        }
        for(j = 0; j < rows_count; j++){
            if(j == rows_count - 1){
                fprintf(fpout, "%s\n", elements[i][j]);
            }else{
                fprintf(fpout, "%s,", elements[i][j]);
            }
        }
    }
    
    fclose(op1);
    fclose(op2);
    
    return (EXIT_SUCCESS);
}

