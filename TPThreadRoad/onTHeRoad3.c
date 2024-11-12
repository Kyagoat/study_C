/* ---------------------------------------------------------------------------
 * Programme affichant une voiture qui parcours une route
 * Auteur(s)  : 
 * Groupe TP  : 
 * Entrées    : Aucune
 * Sorties    : Affichage d'une fenêtre graphique
 * Avancement : <Où en êtes vous ? Qu'est-ce qui fonctionne ?>
 */

#include "road.h"

#define _GNU_SOURCE  // For pthread_tryjoin_np
#include <unistd.h>  // For usleep
#include <pthread.h> // For threading in general
#include <errno.h>   // For EBUSY
#include <stdlib.h>  // For EXIT_FAILURE
#include <stdio.h>   // Just in case


void* car_thread(void* param){

    int carId = road_addCar(0);

    if (carId == -1) {
      fprintf(stderr, "Something went wrong while trying to add a car on the road. Exiting.\n");
      return EXIT_FAILURE;
    }
    if (road_stepCar(carId) == 0){
        usleep(1000);
        break;
    }

    while()


    road_removeCar(carId);
    pthread_exit(NULL);
}

void* create_cars(void* param){

    road_init(0);
    int nb_voitures = 10;
    pthread_t threads[nb_voitures];

    while (!road_isEscPressed()) {
        for (int i; i<=nb_voitures; i++){
            if (pthread_create(&threads[i], NULL, car_thread, NULL) != 0){
                fprintf(stderr,"Erreur lors de la création du thread %d\n", i);
                return 1;
            }
        }
        usleep(1);
      
        road_refresh();
    }


    //pour vérifier que ça se termine une fois que tt les thread sont terminés
    for (int i; i<=nb_voitures; i++){
        pthread_join(threads[i], NULL);
        usleep(1000);
    }
    pthread_exit(NULL);
}


int main(int argc, const char *argv[]) {
    pthread_t cars_thread;
    
    if (pthread_create(&cars_thread, NULL, create_cars, NULL) != 0){
        fprintf(stderr,"Erreur");
        return 1;
    }

    pthread_join(&cars_thread,NULL);
    printf("Fin du processus\n");

    road_shutdown();
    return 0;
}


