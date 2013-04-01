#include "scan.h"

///////////////////////////////////////////////////////////////////////////////

void ReadFile(char *filename, Token table[])
{
     int boolVal = 1;
     int lineNum = 1;
     
     //char filename[80]
     
     char *line = malloc(sizeof(char) * 256);
     //const char filename[] = "prog.txt";
          
     FILE *input = fopen(filename, "r");
     while((fgets(line, 256, input)) != NULL)
     {
           printf("%s %i\n", "Line Number:", lineNum);             
           brkLine(line, &boolVal, table, lineNum);
           
           lineNum++;
           //system("pause");
     }
     
     free(line);     
     fclose(input);   
}

///////////////////////////////////////////////////////////////////////////////

void brkLine(char *line, int *boolVal, Token table[], int lineNum)
{
  char *word;
  int lineIndex = 0;
  
  word = strtok (line," \t\n");
  while (word != NULL)
  {
      
       if(((word[0] == '(') && (word[1] == '*')) || word[0] == '{')
       {
               word = strtok (NULL, " \t\n");
               *boolVal = 0;                  
       }
       
       else if(((word[0] == '*') && (word[1] == ')')) || word[0] == '}')
       {
               word = strtok (NULL, " \t\n");
               *boolVal = 1;
       }
               
               
       else if(word[0] == '/' && word[1] == '/')
       {
            while(word != NULL)
               word = strtok (NULL, " \t\n");
       }
       
       else
       {
           if(*boolVal == 1)
                      brkToken(word, table, lineNum, &lineIndex);
                      
           //printf("%i\n", lineIndex);
    
           word = strtok (NULL, " \t\n");
           
       }
       
  }
}

///////////////////////////////////////////////////////////////////////////////

void brkToken(char *word, Token table[], int lineVar, int *lineIndex)
{
     char *ident = malloc(sizeof(char) * 16);
     memset(ident, '\0', 16);
     char *readVal = malloc(sizeof(char) * 16);
     memset(readVal, '\0', 16);
     char *writeVal = malloc(sizeof(char) * 16);
     memset(writeVal, '\0', 16);
     char *commaVal = malloc(sizeof(char) * 16);
     memset(commaVal, '\0', 16);
     char *semicVal = malloc(sizeof(char) * 16);
     memset(semicVal, '\0', 16);
     char *intVal = malloc(sizeof(int) * 20);
     memset(intVal, '\0', 16);
     
     int indexOfToken = 0; //token.lineNum & token.lexOrder
     
     int valid = 0;
     int alphaBool = 1;
     
     int i = 0;
     while(word[i] != '\0')
     {
         if(isalpha(word[i]))
               word[i] = toupper(word[i]);
         else
             alphaBool = 0;              
               
         i++;          
     }
     
     if(alphaBool == 1)
     {
             if(validIden(word) == 1)
             {
                      table[hashIndex(word)].token = word;            
                      table[hashIndex(word)].code =  codeFinder(word);
                      table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
                      table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
                      indexOfToken = indexOfToken + 1;
                      *lineIndex = *lineIndex + 1;
             }
             else
             {
                   printf("%s\n", "Invalid Identifier");
                   getchar();
                   //exit(0);  
             }
             
             
     }
     
     //printf("%u\n", strncmp("read", word, 4));
     
     if((word[0] == ':') && (word[1] == '='))
     {
          table[hashIndex(word)].token = word;    
          table[hashIndex(word)].code =  codeFinder(word);         
          table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
          table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
          indexOfToken = indexOfToken + 1;  
          *lineIndex = *lineIndex + 1;          
     }
     else if((word[0] == ':') && (word[1] == '\0'))
     {
          table[hashIndex(word)].token = word;
          table[hashIndex(word)].code =  codeFinder(word);             
          table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
          table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
          indexOfToken = indexOfToken + 1;
          *lineIndex = *lineIndex + 1;     
     }
     
     
     if( strncmp("READ", word, 4) == 0)
     {
          table[hashIndex(word)].token = "READ";
          table[hashIndex(word)].code =  codeFinder("READ");             
          table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
          table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
          indexOfToken = indexOfToken + 1;
          *lineIndex = *lineIndex + 1;
         
         if(word[4] == '(')
         {
              table[hashIndex(word)].token = "("; 
              table[hashIndex(word)].code =  codeFinder("(");            
              table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
              table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
              indexOfToken = indexOfToken + 1;
              *lineIndex = *lineIndex + 1;           
         }
                  //printf("%s\n", "oBrac"); 
         
         int m;
         int n = 0;;
         for (m = 5; word[m] != ')'; m++)
         {
             readVal[n] = word[m];
             n++;    
         }
         //printf("%s\n", readVal);
         valid = validIden(readVal);
         if (valid != 1)
         {
            printf("%s\n", "Invalid Identifier");
            getchar();
            //exit(0);
         }
         else
         {
              table[hashIndex(word)].token = readVal;
              table[hashIndex(word)].code =  codeFinder(readVal);             
              table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
              table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
              indexOfToken = indexOfToken + 1;
              *lineIndex = *lineIndex + 1;
         }
         if(word[strlen(word) - 2] == ')')
         {
              table[hashIndex(word)].token = ")";
              table[hashIndex(word)].code =  codeFinder(")");             
              table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
              table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
              indexOfToken = indexOfToken + 1;
              *lineIndex = *lineIndex + 1;                                       
         }
             
     } //end read(value)
     
     if(strncmp("WRITE", word, 5) == 0)
     {
          table[hashIndex(word)].token = "WRITE";
          table[hashIndex(word)].code =  codeFinder("WRITE");             
          table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
          table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
          indexOfToken = indexOfToken + 1;
          *lineIndex = *lineIndex + 1;
          
          if(word[5] == '(')
          {
              table[hashIndex(word)].token = "(";
              table[hashIndex(word)].code =  codeFinder(")");             
              table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
              table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
              indexOfToken = indexOfToken + 1;
              *lineIndex = *lineIndex + 1;           
          }
                       
          int p;
          int q = 0;;
          for (p = 6; word[p] != ')'; p++)
          {
             writeVal[q] = word[p];
             q++;    
          }
          valid = validIden(writeVal);
          if (valid != 1)
          {
            printf("%s\n", "Invalid Identifier");
            getchar();
            //exit(0);
          }
          else
          {
              table[hashIndex(word)].token = writeVal;
              table[hashIndex(word)].code =  codeFinder(writeVal);             
              table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
              table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
              indexOfToken = indexOfToken + 1;
              *lineIndex = *lineIndex + 1;
          } 
          
          
              
          if(word[strlen(word) - 2] == ')' || word[strlen(word) - 1] == ')')
          {
              table[hashIndex(word)].token = ")";
              table[hashIndex(word)].code =  codeFinder(")");             
              table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
              table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
              indexOfToken = indexOfToken + 1;
              *lineIndex = *lineIndex + 1;
          }
          
     } //end write(value)
     
     if((word[strlen(word)-1] == ';') && (isalpha(word[strlen(word) - 2])))
     {    
          int boolInt = 1;
          int a, b = 0;
          for(a = 0; a < (strlen(word) - 1); a++)
          {
                semicVal[b] = word[a];
                b = b + 1;
          }
          valid = validIden(semicVal);
          if (valid != 1)
          {
            printf("%s\n", "Invalid Identifier");
            getchar();
            //exit(0);
          }
          else
          {
              table[hashIndex(word)].token = semicVal;
              table[hashIndex(word)].code =  codeFinder(semicVal);             
              table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
              table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
              indexOfToken = indexOfToken + 1;
              *lineIndex = *lineIndex + 1;
          }
                                 
     }
     else if((word[strlen(word)-1] == ';') && (word[strlen(word)-2] == ')'))
     {
          table[hashIndex(word)].token = ";";
          table[hashIndex(word)].code =  codeFinder(";");             
          table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
          table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
          indexOfToken = indexOfToken + 1;
          *lineIndex = *lineIndex + 1;       
     }
     else if((word[strlen(word)-1] == ';') && (isdigit(word[strlen(word)-2] - 48)))
     {
          int a, b = 0;
          for(a = 0; a < (strlen(word) - 1); a++)
          {
                intVal[b] = word[a];
                b = b + 1;
          } 
          table[hashIndex(word)].token = "intVal";
          table[hashIndex(word)].code =  23;             
          table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
          table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
          indexOfToken = indexOfToken + 1;
          *lineIndex = *lineIndex + 1;        
     }
     if(word[strlen(word)-1] == '.')
     {
         table[hashIndex(word)].token = (word);
         table[hashIndex(word)].code =  codeFinder(word);             
         table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
         table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
         indexOfToken = indexOfToken + 1;
         *lineIndex = *lineIndex + 1;
     }
     if(word[0] == '+')
     {
         table[hashIndex(word)].token = "+";
         table[hashIndex(word)].code =  codeFinder(word);             
         table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
         table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
         indexOfToken = indexOfToken + 1;
         *lineIndex = *lineIndex + 1;
     }
     if(word[0] == '*')
     {
         table[hashIndex(word)].token = "*";
         table[hashIndex(word)].code =  codeFinder(word);             
         table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
         table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
         indexOfToken = indexOfToken + 1;
         *lineIndex = *lineIndex + 1;
     }
     if(word[0] == '-')
     {
         table[hashIndex(word)].token = "-";
         table[hashIndex(word)].code =  codeFinder(word);             
         table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
         table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
         indexOfToken = indexOfToken + 1;
         *lineIndex = *lineIndex + 1;
     }
     if(word[strlen(word) - 1] == ',')
     {
          int boolInt = 1;
          int a, b = 0;
          for(a = 0; a < (strlen(word) - 1); a++)
          {
                commaVal[b] = word[a];
                b = b + 1;
          }
          valid = validIden(commaVal);
          if (valid != 1)
          {
            printf("%s\n", "Invalid Identifier");
            getchar();
            //exit(0);
          }
          else
          {
              table[hashIndex(word)].token = commaVal;
              table[hashIndex(word)].code =  codeFinder(commaVal);             
              table[hashIndex(word)].lineNum[indexOfToken] = lineVar;
              table[hashIndex(word)].lexOrder[indexOfToken] = *lineIndex;
              indexOfToken = indexOfToken + 1;
              *lineIndex = *lineIndex + 1;
          }
     }
        
     //printf("%s\n", word);    
     

     free(ident);
     free(semicVal);
     free(readVal);
     free(writeVal);
     free(commaVal);
     free(intVal);   
}

///////////////////////////////////////////////////////////////////////////////

int validIden(char *iden)
{
     
     printf("%s\n", iden);
     int boolVal = 1;
     int i;
     
     if(strlen(iden) > 16)
           boolVal = 0;
     if (iden[0] ==  '_')
          boolVal = 0;
     else if (isalpha(iden[0]) == 0)
          boolVal = 0;
     else
     {
         for(i = 0; i < strlen(iden); i++)
         {
               if((iden[i] != '_') && (isalpha(iden[i]) == 0))
                           boolVal = 0;      
         }
     }
     
     return boolVal;     
}

///////////////////////////////////////////////////////////////////////////////
unsigned int hashIndex(char *str)
{
         int i;
         unsigned int index;
         
         for(i = 0; i < strlen(str); i++)
               index = index + str[i];

         return index % HASH_SIZE;
}

///////////////////////////////////////////////////////////////////////////////
/*
int arraySize(int *intVar)
{
    int i, size = 0;
    for(i = 0; intVar[i] != '\0'; i++)
          size = size + 1;
    if(size == 0)
        return 1;
    else
        return size;
              
}*/


///////////////////////////////////////////////////////////////////////////////

void outHash(Token table[])
{
     outHelper outTable[25];
     int k;
     for(k = 0; k < 25; k++)
     {
          outTable[k].ident = malloc(sizeof(char) * 16);
          int q;
          for(q = 0; q < 16; q++)
                outTable[k].ident[q] = '\0';
          outTable[k].outCode = 0;
          outTable[k].outIndex = 0;       
     }
     
     int i, j = 0, line = 1, a = 0, z, b = 0;
     for(z = 0; z < HASH_SIZE; z++)
     {
         for( i = 0; i < HASH_SIZE; i++)
         {
              if(table[i].token != '\0')
              {  
                 int x;
                 for(x = 0; x < (sizeof(table[i].lineNum)/ sizeof(int)); x++)
                 {     
                       if(table[i].lineNum[x] == line)
                       {           
                           outTable[j].ident = table[i].token;
                           outTable[j].outCode = table[i].code;
                           outTable[j].outIndex = table[i].lexOrder[x];
                           j = j + 1;       
                       }
                 }
              }
         }
                       
         int order = 1;
         while(outTable[b].ident)
         {
             a = 0;
             while(outTable[a].ident)
             {
                  if(outTable[a].outIndex == order)
                  {
                      printf("Token :  %s\n", outTable[a].ident);
                      printf("Line  #  %i\n", line);
                      printf("Order #  %i\n\n", order);
                  }
                  
                  a = a + 1;
             }
             order = order + 1;
             b = b + 1;
         }
              
         line = line + 1;
     }
     
     for(i = 0; i < 25; i++)
    {
          int q; 
          for(q = 0; q < 16; q++)
                outTable[i].ident[q] = '\0';
          outTable[i].outCode = '\0';
          outTable[i].outIndex = '\0'; 
 
    }
    
    free(outTable);
       
       //exit outHash     
}

///////////////////////////////////////////////////////////////////////////////

int checkHash(Token table[], char *word)
{
    int boolVal = 1;
    
    return boolVal;
        
}

///////////////////////////////////////////////////////////////////////////////

int codeFinder(char *token)
{
    if(token == "PROGRAM")
         return 1;
    else if(token == "VAR")
         return 2;
    else if(token == "BEGIN")
         return 3;
    else if(token == "END")
         return 4;
    else if(token == "END."){
         printf("error");
         return 5;}
    else if(token == "INTEGER")
         return 6;
    else if(token == "FOR")
         return 7;
    else if(token == "READ")
         return 8;
    else if(token == "WRITE")
         return 9;
    else if(token == "TO")
         return 10;
    else if(token == "DO")
         return 11;
    else if(token == ";")
         return 12;
    else if(token == ":")
         return 13;
    else if(token == ",")
         return 14;
    else if(token == ":=")
         return 15;
    else if(token == "+")
         return 16;
    else if(token == "-")
         return 17;
    else if(token == "*")
         return 18;
    else if(token == "DIV")
         return 19;
    else if(token == "(")
         return 20;
    else if(token == ")")
         return 21;
    else if(token == "int")
         return 23;
    else 
         return 22;
}
