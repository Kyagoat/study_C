/* ---------------------------------------------------------------------------
 * Programme affichant une voiture qui parcours une route
 * Auteur(s)  :
 * Groupe TP  :
 * Avancement : <Où en êtes vous ? Qu'est-ce qui fonctionne ?>
 */

#define _GNU_SOURCE
#include <unistd.h> // For usleep
#include <pthread.h>
#include <errno.h>
#include <stdlib.h> // For rand
#include <semaphore.h> 

#include "road.h"

// Forward declarations
void* car_thread(void* rid);
void* create_cars(void* unused);

int main(int argc, const char *argv[])
{
   // Create road
   road_init(1);

   pthread_t create_cars_thread;
   pthread_create(&create_cars_thread, NULL, create_cars, NULL);

   while (!road_isEscPressed() && pthread_tryjoin_np(create_cars_thread, NULL) == EBUSY)
   {
      usleep(1000);
      road_refresh();
   }

   road_shutdown();

   return 0;
}

// Function that create cars
void* create_cars(void* unused)
{
   const int nb_cars = 300;
   pthread_t car_threads[nb_cars];

   int road_ids[nb_cars];

   const int minDelay = 300000;
   int delay;

   // Create cars
   for (int i = 0; i < nb_cars; i++) {
      delay = minDelay + rand()%(minDelay);
      usleep(delay);
      road_ids[i] = 0;
      if (rand() < RAND_MAX/3) {
         road_ids[i] = 1;
      }
      // Start car thread
      pthread_create(&car_threads[i], NULL, car_thread, &road_ids[i]);
   }

   // Wait for all cars to finish
   for (size_t i = 0; i < nb_cars; i++)
   {
      pthread_join(car_threads[i], NULL);
   }

   return NULL;
}

// Function that create a car and make it move until it reaches the end of the road
void* car_thread(void* rid)
{
   int road_id = *((int*) rid);
   int car_id = road_addCar(road_id);

   while (road_stepCar(car_id))
   {
      usleep(3000);
   }

   road_removeCar(car_id);

   return NULL;
}
