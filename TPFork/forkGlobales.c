#include <stdio.h>     /* Pour utiliser printf, perror, NULL... */
#include <stdlib.h>    /* Pour exit */
#include <unistd.h>    /* Pour fork, getpid, getppid */
#include <errno.h>
#include <sys/types.h> /* Pour pid_t */
#include <sys/wait.h>  /* Pour wait */

extern int errno;      /* Modifiée en cas d'erreur */

/* Fonctions exécutant le code du parent et de l'enfant */
void parent(void);
void enfant(void);
int count = 434;

/* ---------------------------------------------------------------------------
 * Création d'un processus enfant et exécution d'une fonction particulière
 * par chaque processus (parent et enfant).
 */
int main(void)
{
  pid_t id;

  id = fork();

  switch (id) {
     case -1:
        perror("fork");
        return errno;
     case 0:
        /* Code exécuté uniquement par l'enfant */
        enfant();
        return EXIT_SUCCESS;  /* Garantit que l'enfant ne fait que la *
                               * fonction enfant() */
        break;
     default:
        /* Code exécuté uniquement par le parent, ici ident == identification du 
         * enfant créé */
        parent();
        
  }
  return EXIT_SUCCESS;
}


/* Actions du processus parent, regroupées dans une procédure. */
void parent(void){
  for (int i = 0; i<=200; i++){
    //count ++;
    
  }
  printf("Parent %d\n",count);
}

/* Actions du processus enfant */
void enfant(void){
  for (int i = 0; i<=200; i++){
    //count ++;
    
  }
  printf("Enfant %d\n",count);
}

