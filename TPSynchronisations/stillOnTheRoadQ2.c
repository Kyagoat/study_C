#define _GNU_SOURCE

#include <unistd.h> // For usleep
#include <pthread.h>
#include <errno.h>
#include <stdlib.h> // For rand
#include <semaphore.h>
#include <stdio.h>
#include "road.h"
#include <stdbool.h>
#include <time.h>

void *car_thread(void *rid);
void *switchLanes();
void *create_cars(void *unused);
bool safeStepCar(int id);

pthread_mutex_t haut = PTHREAD_MUTEX_INITIALIZER;
sem_t semaphoreTopLane;
sem_t semaphoreBottomLane;
int MAX_PASSAGE = 3;

int main(int argc, const char *argv[]) {
    srand(time(NULL));

    road_init(1);

    pthread_t create_cars_thread;
    pthread_create(&create_cars_thread, NULL, create_cars, NULL);

    pthread_t th_switchLanes;
    pthread_create(&th_switchLanes, NULL, switchLanes, NULL);

    sem_init(&semaphoreTopLane, 0, MAX_PASSAGE);
    sem_init(&semaphoreBottomLane, 0, 0);

    while (!road_isEscPressed() && pthread_tryjoin_np(create_cars_thread, NULL) == EBUSY) {
        usleep(1000);
        road_refresh();
    }

    road_shutdown();

    return 0;
}

void *create_cars(void *unused) {
    const int nb_cars = 300;
    pthread_t car_threads[nb_cars];
    int road_ids[nb_cars];
    const int minDelay = 300000;
    int delay;

    for (int i = 0; i < nb_cars; i++) {
        delay = minDelay + rand() % minDelay;
        usleep(delay);
        road_ids[i] = 0;
        if (rand() < RAND_MAX / 2) {
            road_ids[i] = 1;
        }
        pthread_create(&car_threads[i], NULL, car_thread, &road_ids[i]);
    }

    for (size_t i = 0; i < nb_cars; i++) {
        pthread_join(car_threads[i], NULL);
    }

    return NULL;
}

void *car_thread(void *rid) {
    int speed = 1 * 1000;
    int road_id = *((int *)rid);
    int car_id = road_addCar(road_id);

    while (road_distToCross(car_id) > road_minDist) {
        safeStepCar(car_id);
        usleep(speed);
    }

    if (road_id == 0) {
        sem_wait(&semaphoreTopLane);
    } else {
        sem_wait(&semaphoreBottomLane);
    }

    while (road_distToCross(car_id) < INT_MAX) {
        safeStepCar(car_id);
        usleep(speed);
    }

    if (road_id == 0) {
        sem_post(&semaphoreTopLane);
    } else {
        sem_post(&semaphoreBottomLane);
    }

    while (safeStepCar(car_id)) {
        usleep(speed);
    }

    road_removeCar(car_id);

    return NULL;
}

bool safeStepCar(int id) {
    if (road_distNextCar(id) > road_minDist) {
        return road_stepCar(id);
    }
    return true;
}

void *switchLanes() {
    bool up = false;
    int bottomValue;
    int topValue;
    while (true) {
        if (up) {
            for (int i = 0; i < MAX_PASSAGE; i++) {
                sem_wait(&semaphoreBottomLane);
            }
            for (int i = 0; i < MAX_PASSAGE; i++) {
                sem_post(&semaphoreTopLane);
            }
        } else {
            for (int i = 0; i < MAX_PASSAGE; i++) {
                sem_wait(&semaphoreTopLane);
            }
            for (int i = 0; i < MAX_PASSAGE; i++) {
                sem_post(&semaphoreBottomLane);
            }
        }

        sem_getvalue(&semaphoreTopLane, &topValue);
        sem_getvalue(&semaphoreBottomLane, &bottomValue);
        up = !up;
        sleep(2);
    }
}
