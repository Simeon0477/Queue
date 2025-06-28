#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

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
        q->last->suivant = client;
        q->last = client;
    }
    client->suivant = NULL;
}

// Retrait d'un client de la queue
Client* dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("La file d'attente est vide.\n");
        return NULL;
    }
    Client *client = q->first;
    q->first = q->first->suivant;
    return client;
}

// Génération d'un client aléatoire
Client* generateClient(int id) {
    srand(time(NULL));
    Client *client = (Client *)malloc(sizeof(Client));
    client->id = id;
    client->temps_arrivee = rand() % 10;
    client->temps_traitement = rand() % 5 + 1; 
    client->suivant = NULL;
    return client;
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
        fprintf(file, "%d %d %d\n", current->id, current->temps_arrivee, current->temps_traitement);
        current = current->suivant;
    }

    fclose(file);
    printf("File d'attente sauvegardée dans %s.\n", nomFichier);
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
        if (fscanf(file, "%d %d %d", &client->id, &client->temps_arrivee, &client->temps_traitement) == 3) {
            enqueue(q, client);
        } else {
            free(client);
        }
    }

    fclose(file);
    printf("File d'attente chargée depuis %s.\n", nomFichier);
}