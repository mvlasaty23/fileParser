/* 
 * File:   libfp.h
 * Author: michael.vlasaty
 *
 * Created on 29. März 2013, 19:11
 */

#ifndef LIBFP_H
#define	LIBFP_H
#define ARRAY_SIZE(x) sizeof(x)/sizeof((*x))

/*
 *hier werden laengen von strings und andere
 * speichergroessen abgelegt
 */ 
//typedef unsigned long size_t;

//get line of a file free pointer after use
char *get_line(FILE *fp);

//count lines of file
int line_count(FILE *fp);

//count rows of csv file
int row_count(char *file, char *delimiter);

//chop trailing newline char from a string
void chomp(char *string);

#endif	/* LIBFP_H */

