#define _GNU_SOURCE
#include <unistd.h> // For usleep
#include <pthread.h>
#include <errno.h>
#include <stdlib.h> // For rand
#include <semaphore.h>
#include <stdio.h>

#include "road.h"

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void* car_thread(void* rid);
void* create_cars(void* unused);
int road_validate(int car);
void *switchLanes(void *sem);

sem_t sem_lane_1;
sem_t sem_lane_2;

int main(int argc, const char *argv[]) {
   sem_init(&sem_lane_1, 0, 1);
   sem_init(&sem_lane_2, 0, 0);

   pthread_t switch_thread;
   if(pthread_create(&switch_thread, NULL, switchLanes, NULL) != 0){
      fprintf(stderr, "Erreur lors de la création du thread de gestion des voies. \n");
      return EXIT_FAILURE;
   }

   pthread_t cars_thread;
   if (pthread_create(&cars_thread, NULL, car_thread, NULL) != 0){
      fprintf(stderr,"Erreur lors de la création du thread des voitures");
      return EXIT_FAILURE;
   }

   pthread_join(cars_thread, NULL);
   pthread_join(switch_thread, NULL);

   road_shutdown();
   sem_destroy(&sem_lane_1);
   sem_destroy(&sem_lane_2);
   return 0;
}

void *create_cars(void *unused) {
   road_init(1);
   pthread_t car_thread_id = NULL;
   int delay = 0;

   while (!road_isEscPressed()){
      road_refresh();
      usleep(1);

      if (delay++ >= 1000%rand() || car_thread_id == NULL){
         for (int i = 0; i < 10; i++) {
            if (pthread_create(&car_thread_id, NULL, car_thread, NULL) != 0){
               fprintf(stderr,"Erreur lors de la création du thread des voitures");
               return EXIT_FAILURE;
            }
         usleep(100);
      }
      delay = 0;
   }

   while(1){
      road_refresh();
      usleep(1);
      if (pthread_tryjoin_np(car_thread_id, NULL) == 0){
         break;
      }
   }
   }
   pthread_exit(NULL);
}

void *car_thread(void *rid) {
    int road_id = *((int*) rid);
    int car_id = road_addCar(road_id);
    int lane = rand()%2;

    sem_t *current_lane = (lane ==0) ? &sem_lane_1 : &sem_lane_2;

    while(1){
        usleep(3000);
        if (road_distToCross(car_id) <= road_minDist){
            sem_wait(current_lane);
            while(road_distToCross(car_id) <= road_minDist){
                road_stepCar(car_id);
                usleep(3000);
            }
            sem_post(current_lane);
        }
        else{
           if (road_stepCar(car_id) ==0){break;}
           usleep(3000);
           road_stepCar(car_id);
        }
    }
   road_removeCar(car_id);
   pthread_exit(NULL);
   return NULL;
}

int road_validate(int car) {
   if(road_distNextCar(car) != -1 && 0 < road_distNextCar(car) && road_distNextCar(car) < 50){
      return 1;
   }
   if (road_stepCar(car) == 0){
      return 0;
   }
   return 1;
}

void* switchLanes(void *sem){
   while (!road_isEscPressed()){
      sem_wait(&sem_lane_1);
      sem_post(&sem_lane_2);
      usleep(3000);

      sem_wait(&sem_lane_2);
      sem_post(&sem_lane_1);
      usleep(3000);
   }
   pthread_exit(NULL);
}
