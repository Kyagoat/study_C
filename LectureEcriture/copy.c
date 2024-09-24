#include <fcntl.h>  // For 'open'
#include <unistd.h> // For 'write'
#include <string.h> // For 'strlen'
#include <stdio.h> 


int main(int argc, char const *argv[]){

    FILE* f = fopen("Chaton.ppm", "r");
    FILE* copy = fopen("ChatonCopy.ppm", "w");

    int entier;


    char line[200];
    for(int i =0; i<=3; i++){
        fgets(line, 200, f);
        fprintf(copy, "%s", line);    
    }
      
   
    while(fscanf(f, "%d", &entier) == 1){
        fprintf(copy, "%d\n", entier);
    }

}