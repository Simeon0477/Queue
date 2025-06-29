#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "header/queue.h"

Queue queue;
int choix;
char nomFichier[] = "queue.txt";
int nbre;

// Fonction principale
int main() {
    srand(time(NULL));
    initQueue(&queue);

    printf("\033[35m******** Simulateur de file d'attente ******** \n\033[0m");

    while (1) {
        printf("\nMenu:\n");
        printf(" 1 - Ajouter des clients aléatoires\n");
        printf(" 2 - Traiter les clients\n");
        printf(" 3 - Calculer le temps d'attente total\n");
        printf(" 4 - Quitter\n");
        printf("Votre choix -> ");
        scanf("%d", &choix);

        loadQueue(&queue, nomFichier);

        switch (choix) {
            case 1:
                printf("\n\033[32m1 - Ajout de clients \n\n\033[0m");
                printf("Entrez le nombre de clients que vous voulez générer : ");
                scanf("%d", &nbre);

                for (int i = 0; i < nbre; i++) {
                    Client *client = generateClient(i + 1);
                    printf("Client %d est arrivé avec un temps de traitement de %d minutes.\n", client->id, client->temps_traitement);
                    enqueue(&queue, client);
                }
                saveQueue(&queue, nomFichier);
                break;
            case 2:
                printf("\n\033[32m2 -Traitement des clients \n\n\033[0m");
                printf("Entrez le nombre de clients que vous voulez traiter : ");
                scanf("%d", &nbre);
                for (int i = 0; i < nbre; i++) {
                    Client *client = dequeue(&queue);
                    printf("Client %d est servi.\n", client->id);
                    sleep(client->temps_traitement);
                    free(client);
                }
                saveQueue(&queue, nomFichier);
                break;
            case 3:
                printf("\n\033[32m3 - Calculer le temps d'attente total \n\n\033[0m");
                printf("Le temps d'attente total est : %d minutesS\n", totalTime(&queue));
                break;
            case 4:
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