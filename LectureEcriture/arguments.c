#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>

int main(int argc, char* argv[])
{
   char* inputFilename;
   char* outputFilename;
   if (argc < 3){
      fprintf(stderr, "You should provide an input and an output filenames. Aborting");
      exit(-1);
   }
   inputFilename = argv[1];
   outputFilename = argv[2];

   FILE* f = fopen(inputFilename, "r");
   FILE* darker = fopen(outputFilename, "w");

   int entier;


   char line[200];
   for(int i =0; i<=3; i++){
      fgets(line, 200, f);
      fprintf(darker, "%s", line);    
   }

   
   while(fscanf(f, "%d", &entier) == 1){
      fprintf(darker, "%d\n", entier/6);
   }
}
