#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "../header/queue.h"

// Initialisation de la file d'attente
void initQueue(Queue *q) {
    q->first = NULL;
    q->last = NULL;
}

// Vérifie si la queue est vide
int isEmpty(Queue *q) {
    return (q->first == NULL);
}

// Ajout d'un client à la queue
void enqueue(Queue *q, Client *client) {
    if (isEmpty(q)) {
        q->first = client;
        q->last = client;
    } else {
        q->last->next = client;
        q->last = client;
    }
    client->next = NULL;
}

// Retrait d'un client de la queue
Client* dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("La file d'attente est vide.\n");
        return NULL;
    }
    Client *client = q->first;
    q->first = q->first->next;
    return client;
}

// Génération d'un client aléatoire
Client* generateClient(int id) {
    Client *client = (Client *)malloc(sizeof(Client));
    client->id = id;
    client->temps_traitement = rand() % 10 + 1; 
    client->next = NULL;
    return client;
}

//Calcul du temps d'attente total
int totalTime(Queue *q) {
    int total = 0;
    Client *current = q->first;

    while (current != NULL) {
        total += current->temps_traitement; 
        current = current->next;
    }

    return total;
}

// Sauvegarde de la file d'attente
void saveQueue(Queue *q, const char *nomFichier) {
    FILE *file = fopen(nomFichier, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    Client *current = q->first;
    while (current != NULL) {
        fprintf(file, "%d %d\n", current->id, current->temps_traitement);
        current = current->next;
    }

    fclose(file);
    printf("File d'attente sauvegardée.\n");
}

// Chargement la file d'attente
void loadQueue(Queue *q, const char *nomFichier) {
    FILE *file = fopen(nomFichier, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    Client *client;
    while (!feof(file)) {
        client = (Client *)malloc(sizeof(Client));
        if (fscanf(file, "%d %d", &client->id, &client->temps_traitement) == 3) {
            enqueue(q, client);
        } else {
            free(client);
        }
    }

    fclose(file);
}