#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

extern int yylineno;

#define FALSE 			0
#define TRUE 			1

/* void ERROR(char *message, unsigned int lineNum, char systemError) -- prints
 * error message then exits program with status -1
 */
void ERROR(char *message, unsigned int lineNum, char systemError);

#endif
