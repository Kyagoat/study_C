#include "road.h"

#define _GNU_SOURCE  // For pthread_tryjoin_np
#include <unistd.h>  // For usleep
#include <pthread.h> // For threading in general
#include <errno.h>   // For EBUSY
#include <stdlib.h>  // For EXIT_FAILURE
#include <stdio.h>   // Just in case
#include <string.h>   // Just in case

#include <sys/types.h>
#include <sys/socket.h>
#include "Reseau.h"



void* car_thread(void* param) {
   int carId = road_addCar(0);
   while (road_stepCar(carId)){
      usleep(10000);
   }
   road_removeCar(carId);
}


void* create_cars(void* param) {

   int client_socket, serveur_socket;


   int* ports = (int*)param;
   int port = ports[0];       // Port principal
   int port_ecoute = ports[1];

   road_init(1);
   pthread_t th;

   serveur_socket = socketServer(port, TCP);
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
   }
   // création nouveau client
   char buffer[1024];
   int sockfd = socketClient("localhost", port_ecoute,TCP);
   if (sockfd < 0) {
      fprintf(stderr, "Erreur de connexion au serveur sur le port %d\n", port_ecoute);
   }
   else {
      printf("Connecté au serveur sur le port %d\n", port_ecoute);

      snprintf(buffer, 1024, "La voiture est arrivée au bout de la route\n");
      send(sockfd, buffer, strlen(buffer), 0);
      printf("Message envoyé : %s\n", buffer);

      // Fermer le socket
      close(sockfd);
   }
   road_shutdown();
   }
}
// ----------   MAIN   ----------- 

int main(int argc, const char* argv[]){

   int port = atoi(argv[1]);
   int port_ecoute = atoi(argv[2]);

   pthread_t th;

   // Passage des ports comme paramètres au thread
   int ports[2] = {port, port_ecoute};

   if (pthread_create(&th, NULL, create_cars, (void*)ports) != 0){
      fprintf(stderr,"erreur de création");
   }

   pthread_join(th, NULL);

   road_shutdown();
   return 0;
}


