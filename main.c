/* 
 * File:   main.c
 * Author: mvlasaty
 *
 * Created on 28. März 2013, 14:53
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libfp.h>

#define LINE_LENGTH 110
#define ROW_LENGTH 42
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(*(x)))



/*Testing programm for reading csv file line per line
 * and sort it into two differnet csv files on some criteria
 * 
 */

int main(int argc, char** argv) {

    typedef unsigned long size_t;
    
    //our file
    const char *file = "/home/mvlasaty/Dokumente/test.csv";
    FILE *csv = fopen(file, "r");
    
    //delmiter & file should become cmd args or something TO DO!
    const char *delimiter = ";";
    
    //handle access error
    if(csv == NULL){
        printf("Can't access file %s!\n", file);
        return(EXIT_FAILURE);
    }
 
    /*Read line by line
     * handle if line is NULL, we're probably at EOF
     * split lines by delimiter into elements
     * than decide on contact name in which file to write
     * undef: companys.csv
     * def: contacts.csv
     * finally free read line 
     */
    char *Line;
    char *row;
    
    while(Line != NULL){

        Line = getLine(csv);
        
        if(*Line == NULL)
            break;

        printf("%s", Line);
        row = strtok(Line, delimiter);

        while(row){
            printf("%s\n", row);
            row = strtok(NULL, delimiter);
        }
        
        free(Line);
    }

    free(Line);
    fclose(csv);
    
    return (EXIT_SUCCESS);
}

