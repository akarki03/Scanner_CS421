#include "scan.h"

int main ()
{
    char filename[80];
    
    Token hashTable[HASH_SIZE];
    
    int i, j, k;
    
    for(i = 0; i < HASH_SIZE; i++)
    {
          hashTable[i].token = malloc(sizeof(char) * 16);
          memset(hashTable[i].token, '\0', 16);
          
          hashTable[i].code = 0; 
          
          hashTable[i].lineNum = malloc(HASH_SIZE);
          memset(hashTable[i].lineNum, '\0', HASH_SIZE);
          
          hashTable[i].lexOrder = malloc(HASH_SIZE); 
          memset(hashTable[i].lexOrder, '\0', HASH_SIZE);  
    }
    
    printf("Enter a file name (name.ext): ");
    scanf("%s",filename);
    
    ReadFile(filename, hashTable);
    
    /*for(i = 0; i < 41; i++){
          printf("%s Token\n", hashTable[i].token);  
          printf("%s Code\n", hashTable[i].code); 
          printf("%s lineNum\n", hashTable[i].lineNum);
          printf("%s lexOrder\n", hashTable[i].lexOrder);     
          }
*/
    //outHash(hashTable);
    
    system("pause");
    return 0;    
}
