///////////////////////////////////////////////////////////////////////////////

#ifndef SCAN_H_INCLUDED
#define SCAN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///////////////////////////////////////////////////////////////////////////////

#define HASH_SIZE 41

///////////////////////////////////////////////////////////////////////////////

typedef struct
{
   char *token;
   int code;  
   int *lineNum; //stores the line number
   int *lexOrder; //stores the order of identifier   
} Token;

typedef struct
{
    char *ident;
    int outCode;
    int outIndex;        
} outHelper;

///////////////////////////////////////////////////////////////////////////////

void ReadFile(char *filename, Token table[]);
void brkLine(char *line, int *boolVar, Token table[], int lineNum);
void brkToken(char *chr, Token table[], int lineNum, int *lineIndex);
int hashIndex(char *str);
int checkHash(Token table[], char *word);

//int arraySize(int *intVar);

void insertToken(char *str, Token table[], int line, int lineIndex, int order, int orderIndex);

int validHash(int hash, Token table[]);
int codeFinder(char *token);
int validIden(char *iden);
void outHash(Token table[]);
///////////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////
