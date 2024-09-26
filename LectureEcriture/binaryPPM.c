#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>

int main(int argc, char const *argv[]){
    
    FILE* f = fopen("Chaton.ppm", "r");
    FILE* out = fopen("BinaryChaton.ppm", "w");

    char* en_tete = "P6\n";
    char line[200];

    fprintf(out, "%s", en_tete);

    fgets(line,200,f);
    fgets(line,200,f);

    for (int i = 0; i < 2; i++){
        fgets(line,200,f);
        fprintf(out,"%s",line);
    }
    
    int entier;

    while (fscanf(f, "%d", &entier) == 1){
        sscanf(f, "%d", &entier);
        fputc(entier,out);
    }

}