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

void* car_thread(void* param) {
   int carId = road_addCar(0);

   while (road_stepCar(carId)){
      usleep(10000);
   }
   
   road_removeCar(carId);
}


void* create_cars(void* param) {

   pthread_t th;

   for (int i = 0; i < 6; i++){

      if (pthread_create(&th, NULL, car_thread, NULL) != 0){
         fprintf(stderr,"erreur de création");
      }

      sleep(1);
   }

   pthread_join(th, NULL);
}


// ----------   MAIN   ----------- 

int main(int argc, const char *argv[]){
   pthread_t th;

   road_init(0);

   if (pthread_create(&th, NULL, create_cars, NULL) != 0){
      fprintf(stderr,"erreur de création");
   }
   
   while (!road_isEscPressed() && pthread_tryjoin_np(th, NULL) != 0) {
      usleep(1000);
      road_refresh();
   }

   road_shutdown();
   return 0;
}


