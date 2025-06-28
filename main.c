#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "header/queue.h"

// Fonction principale
int main() {
    Queue queue;
    initQueue(&queue);

    int choix;
    char nomFichier[] = "file_attente.txt";

    while (1) {
        printf("\033[35m******** Simulateur de file d'attente ******** \n\n\033[0m");
        printf("\nMenu:\n");
        printf("1. Charger la file d'attente depuis un fichier\n");
        printf("2. Ajouter des clients aléatoires\n");
        printf("3. Traiter les clients\n");
        printf("4. Sauvegarder la file d'attente dans un fichier\n");
        printf("5. Quitter\n");
        printf("Choisissez une option: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                loadQueue(&queue, nomFichier);
                break;
            case 2:
                for (int i = 0; i < 5; i++) {
                    Client *client = generateClient(i + 1);
                    printf("Client %d est arrivé avec un temps d'attente de %d minutes.\n", client->id, client->temps_arrivee);
                    enqueue(&queue, client);
                }
                break;
            case 3:
                while (!isEmpty(&queue)) {
                    Client *client = dequeue(&queue);
                    printf("Client %d est servi. Temps de traitement: %d minutes.\n", client->id, client->temps_traitement);
                    sleep(client->temps_traitement);
                    free(client);
                }
                break;
            case 4:
                saveQueue(&queue, nomFichier);
                break;
            case 5:
                // Libérer la mémoire restante
                while (!isEmpty(&queue)) {
                    Client *client = dequeue(&queue);
                    free(client);
                }
                printf("Au revoir!\n");
                exit(0);
            default:
                printf("Option invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}