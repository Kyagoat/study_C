#include <stdio.h>     /* Pour utiliser printf, perror, NULL... */
#include <stdlib.h>    /* Pour exit */
#include <unistd.h>    /* Pour fork, getpid, getppid */
#include <errno.h>
#include <sys/types.h> /* Pour pid_t */
#include <sys/wait.h>  /* Pour wait */

extern int errno;

void parent(void);
void enfant(void);


int main(void)
{
  pid_t id;
  id = fork();
  FILE* sharedFile = fopen("./sharedFile.txt","a");

  switch (id) {
     case -1:
        perror("fork");
        return errno;

     case 0:
        for (int i = 0; i < 50; i++) {
            fprintf(sharedFile, "%d - Je suis l'enfaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaant !!\n",i);
            fflush(sharedFile);
            }
        return EXIT_SUCCESS;  
        break;

     default:
        wait(NULL);
        usleep(100);
        for (int i = 0; i < 50; i++) {
            fprintf(sharedFile, "%d - Je suis le peeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeere !!\n",i);
            fflush(sharedFile);
        }
    }
  return EXIT_SUCCESS;
}



