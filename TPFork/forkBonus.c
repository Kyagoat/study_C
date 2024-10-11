#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(void){
   
  pid_t id;
  id = fork();
  

  switch (id) {
     case -1:
        perror("fork");
        return errno;

     case 0:
        execlp("ps", "ps", "-fU", "root", NULL);
        printf("Fin du programme\n");
        return EXIT_FAILURE;  
        break;

     default:
        printf("\nFin du programme\n");
    }
  return EXIT_SUCCESS;
}
