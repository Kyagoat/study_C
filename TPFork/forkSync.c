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
void enfant2(void);
    
int main(){
    pid_t child_a, child_b;

    child_a = fork();

    
    if (child_a == 0) {
        /* Child A code */
        enfant();
    } else {
        child_b = fork();
        
        if (child_b == 0) {
            /* Child B code */
            enfant2();
        } else {
            /* Parent Code */
            parent();
        }
    }
}

void parent(void){
    printf("Parent :  PID = %d - PPID = %d\n", getpid(), getppid());
    int fils1 = wait(NULL);
    int fils2 = wait(NULL);
    printf("Enfant1 : %d ; Enfant2 : %d \n", fils1, fils2);
}

/* Actions du processus enfant */
void enfant(void){
   printf("Enfant1 : PID = %d \n", getpid());
}

void enfant2(void){
   printf("Enfant2 : PID = %d \n", getpid());
}