#include "road.h"

#define _GNU_SOURCE  // For pthread_tryjoin_np
#include <unistd.h>  // For usleep
#include <pthread.h> // For threading in general
#include <errno.h>   // For EBUSY
#include <stdlib.h>  // For EXIT_FAILURE
#include <stdio.h>   // Just in case

#include <sys/types.h>
#include <sys/socket.h>
#include "Reseau.h"

#define PORT 4321 //macro

void* car_thread(void* param) {
   int carId = road_addCar(0);
   while (road_stepCar(carId)){
      usleep(10000);
   }
   road_removeCar(carId);
}


void* create_cars(void* param) {

   int client_socket, serveur_socket;

   road_init(1);
   pthread_t th;

   serveur_socket = socketServer(PORT, TCP);
   while (!road_isEscPressed()){
      road_refresh();
      client_socket = accept(serveur_socket, NULL, NULL);
      if (client_socket == -1){
         printf("client non connecté");
      }
      printf("client connecté");
      if (pthread_create(&th, NULL, car_thread, NULL) != 0){
      	 fprintf(stderr,"erreur de création");
      }
      else {
         while (!road_isEscPressed() && pthread_tryjoin_np(th, NULL) != 0) {
      		usleep(1000);
            road_refresh();
   		 }
		 road_shutdown();
      }

   }
   /**/
}

// ----------   MAIN   ----------- 

int main(int argc, const char* argv[]){

   char port_ecoute = atoi(argv[1]);
   char port_connexion = atoi(argv[2]);
   pthread_t th;

   if (pthread_create(&th, NULL, create_cars, NULL) != 0){
      fprintf(stderr,"erreur de création");
   }

   pthread_join(th, NULL);

   road_shutdown();
   return 0;
}


