#include "scan.h"

int main ()
{
    char filename[80];
    
    Token hashTable[HASH_SIZE];
    
    int i, j, k;
    
    for(i = 0; i < HASH_SIZE; i++)
    {
          hashTable[i].token = malloc(HASH_SIZE);
          for(j = 0; j < HASH_SIZE; j++)
                hashTable[i].token[j] = '\0';
          
          hashTable[i].code = 0; 
          
          hashTable[i].lineNum = malloc(HASH_SIZE);
          memset(hashTable[i].lineNum, '\0', HASH_SIZE);
          
          hashTable[i].lexOrder = malloc(HASH_SIZE); 
          memset(hashTable[i].lexOrder, '\0', HASH_SIZE);  
    }
    
    printf("Enter a file name (name.ext): ");
    scanf("%s",filename);
    
    ReadFile(filename, hashTable);  

//==============================================================================
//Free Memory    
      for(i = 0; i < HASH_SIZE; i++)
    {
          free(hashTable[i].token);
          hashTable[i].code = '\0';  
          free(hashTable[i].lineNum);       
          free(hashTable[i].lexOrder); 
 
    }
    
    free(hashTable);
//==============================================================================
  
    system("pause");
    return 0;    
}
