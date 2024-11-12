/* ---------------------------------------------------------------------------
 * Programme affichant une voiture qui parcourt une route
 * Auteur(s)  : Kylian MEHDI & Nadia LAHYA
 * Groupe TP  : TD1H
 * Entrées    : Aucune
 * Sorties    : Affichage d'une fenêtre graphique
 * Avancement : <Où en êtes vous ? Qu'est-ce qui fonctionne ?>
 */

#include "road.h"
#include <allegro5/allegro.h>
#include <unistd.h>  // For usleep
#include <pthread.h> // For threading in general
#include <stdlib.h>  // For EXIT_FAILURE
#include <stdio.h>   // For fprintf
#include <time.h>    // For time and srand

#define NUM_CARS 6

int isPaused = 0;  // Variable pour savoir si le jeu est en pause
pthread_mutex_t pause_mutex;  // Mutex pour gérer l'état de pause

void* car_thread(void* param) {
    int direction = *((int*)param);
    int carId = road_addCar(direction);

    while (road_stepCar(carId)) {
        pthread_mutex_lock(&pause_mutex);
        int paused = isPaused;
        pthread_mutex_unlock(&pause_mutex);

        if (!paused) {
            usleep(10000);
        } else {
            while (paused) {
                usleep(1000);
                pthread_mutex_lock(&pause_mutex);
                paused = isPaused;
                pthread_mutex_unlock(&pause_mutex);
            }
        }
    }

    road_removeCar(carId);
    free(param);
    return NULL;
}

void* create_cars(void* param) {
    pthread_t th;

    for (int i = 0; i < NUM_CARS; i++) {
        int *direction = malloc(sizeof(int));
        if (direction == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            continue;
        }
        *direction = rand() % 2;

        if (pthread_create(&th, NULL, car_thread, direction) != 0) {
            fprintf(stderr, "Erreur de création de thread\n");
            free(direction);
        }

        sleep(rand() % 3 + 1);
    }

    pthread_join(th, NULL);
    return NULL;
}

void handle_keyboard(ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (event.keyboard.keycode == ALLEGRO_KEY_V) {
            pthread_t th;
            int *direction = malloc(sizeof(int));
            if (direction == NULL) {
                fprintf(stderr, "Erreur d'allocation de mémoire\n");
                return;
            }
            *direction = rand() % 2;

            if (pthread_create(&th, NULL, car_thread, direction) != 0) {
                fprintf(stderr, "Erreur de création de voiture\n");
                free(direction);
            }
        } else if (event.keyboard.keycode == ALLEGRO_KEY_P) {
            pthread_mutex_lock(&pause_mutex);
            isPaused = !isPaused;
            pthread_mutex_unlock(&pause_mutex);
        }
    }
}

int main(int argc, const char *argv[]) {
    if (!al_init()) {
        fprintf(stderr, "Échec de l'initialisation d'Allegro.\n");
        return EXIT_FAILURE;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "Échec de l'installation du clavier.\n");
        return EXIT_FAILURE;
    }

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "Échec de la création de la file d'événements.\n");
        return EXIT_FAILURE;
    }

    al_register_event_source(event_queue, al_get_keyboard_event_source());

    road_init(0);
    srand(time(NULL));

    pthread_mutex_init(&pause_mutex, NULL);

    pthread_t th;
    if (pthread_create(&th, NULL, create_cars, NULL) != 0) {
        fprintf(stderr, "Erreur de création du thread principal des voitures.\n");
    }

    while (!road_isEscPressed()) {
        ALLEGRO_EVENT event;
        if (al_get_next_event(event_queue, &event)) {
            handle_keyboard(event);
        }

        pthread_mutex_lock(&pause_mutex);
        int paused = isPaused;
        pthread_mutex_unlock(&pause_mutex);

        if (!paused) {
            road_refresh();
        }

        usleep(1000);
    }

    road_shutdown();
    al_destroy_event_queue(event_queue);
    pthread_mutex_destroy(&pause_mutex);
    return 0;
}

