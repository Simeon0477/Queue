#ifndef __TASK_MGT_H__
#define __TASK_MGT_H__

typedef struct Client {
    int id;
    int temps_traitement;
    struct Client *next;
} Client;

typedef struct Queue {
    Client *first;
    Client *last;
} Queue;

void initQueue(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q, Client *client);
Client* dequeue(Queue *q);
Client* generateClient(int id);
int totalTime(Queue *q);
void saveQueue(Queue *q, const char *nomFichier);
void loadQueue(Queue *q, const char *nomFichier);

#endif