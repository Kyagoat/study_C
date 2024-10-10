#include <stdio.h>     /* Pour utiliser printf, perror, NULL... */
#include <stdlib.h>    /* Pour exit */
#include <unistd.h>    /* Pour fork, getpid, getppid */
#include <errno.h>
#include <sys/types.h> /* Pour pid_t */
#include <sys/wait.h>  /* Pour wait */

extern int errno;

void parent(void);
void enfant(void);



int main(void){
   
  pid_t id;
  FILE* sharedFile = fopen("./sharedFile.txt","w");
  id = fork();
  

  switch (id) {
     case -1:
        perror("fork");
        return errno;

     case 0:
        for (int i = 0; i < 1000; i++) {
            fprintf(sharedFile, "Je suis l'enfaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaant !![%d:%d]\n", getpid(), i);
            fflush(sharedFile);
            }
        return EXIT_SUCCESS;  
        break;

     default:
        usleep(100);
        for (int i = 0; i < 1000; i++) {
            fprintf(sharedFile, "Je suis le peeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeere !![%d:%d]\n", getpid(), i);
            fflush(sharedFile);
        }
    }
  return EXIT_SUCCESS;
}



