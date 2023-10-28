#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define N 5

#define QUEUE 0
#define INSIDE 1
#define NOWANT 2



int max_count = 0;

sem_t sem_men[N];
sem_t sem_women[N];

int state_men[N];
int state_women[N];

sem_t mutex;

void m_queue(int k);
void w_queue(int k);
void another();
void woman_wants_to_enter(int i);
void woman_leaves(int i);
void man_wants_to_enter(int i);
void man_leaves(int i);
void *man(void *id);
void *woman(void *id);





int main(int argc, char* argv[])
{
    srand(time(NULL));
    if (argc != 2) {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    max_count = atoi(argv[1]);
    pthread_t potok[N*2];

    if (sem_init(&mutex, 0, 1) == -1) {
        printf("trouble semafore init\n");
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        if (sem_init(&sem_men[i], 0, 0) == -1) {
            printf("trouble semafore init\n");
            return 1;
        }

        if (sem_init(&sem_women[i], 0, 0) == -1) {
            printf("trouble semafore init\n");
            return 1;
        }

        state_men[i] = NOWANT;
        state_women[i] = NOWANT;
    }




    int menoid[N];
    int womenoid[N];

    for (int i = 0; i < N; i++)//init
    {
        menoid[i] = i;
        womenoid[i] = i;

        pthread_create(&potok[i], NULL, woman, &womenoid[i]);
        pthread_create(&potok[N+i], NULL, man, &menoid[i]);

    }

    for (int i = 0; i < N; i++)//finish
     {

        pthread_join(potok[i], NULL);
        pthread_join(potok[N+i], NULL);
    }

    return 0;
}


void m_queue(int k)
{
    int n = 0;
    for (int i = 0; i < N; i++)
    {
        if (state_women[i] == INSIDE)
        {
            return;
        }
        if (state_men[i] == INSIDE)
        {
            n++;
        }
    }


    if (state_men[k] == QUEUE && n < max_count)
    {
        state_men[k] = INSIDE;
        sem_post(&sem_men[k]);
    }
}



void w_queue(int k)
{
    int n = 0;
    for (int i = 0; i < N; i++)
    {
        if (state_men[i] == INSIDE)
        {
            return;
        }
        if (state_women[i] == INSIDE)
        {
            n++;
        }
    }

    if (state_women[k] == QUEUE && n < max_count)
    {
        state_women[k] = INSIDE;
        sem_post(&sem_women[k]);
    }
}

void another()
{
    for (int i = 0; i < N; i++)
    {
        w_queue(i);
        m_queue(i);
    }
}


void woman_wants_to_enter(int i)
{
    sem_wait(&mutex);

    state_women[i] = QUEUE;
    another();

    sem_post(&mutex);

    sem_wait(&sem_women[i]);
}

void man_wants_to_enter(int i)
{
    sem_wait(&mutex);

    state_men[i] = QUEUE;
    another();

    sem_post(&mutex);

    sem_wait(&sem_men[i]);
}


void woman_leaves(int i)
{
    sem_wait(&mutex);

    state_women[i] = NOWANT;
    another();

    sem_post(&mutex);
}


void man_leaves(int i)
{
    sem_wait(&mutex);

    state_men[i] = NOWANT;
    another();

    sem_post(&mutex);
}


void *woman(void *id)
{
    int i = *((int*)id);
    while (1)
    {

        sleep(rand()%5);

        printf("W %d queue\n", i+1);
        woman_wants_to_enter(i);

        printf("W %d inside\n", i+1);
        sleep(rand()%5);

        printf("W %d out\n", i+1);
        woman_leaves(i);
        sleep(rand()%5);
    }
}

void *man(void *id)
{
    int i = *((int*)id);
    while (1)
    {

        sleep(rand()%5);

        printf("M %d queue\n", i+1);
        man_wants_to_enter(i);

        printf("M %d in\n", i+1);
        sleep(rand()%5);

        printf("M %d out\n", i+1);
        man_leaves(i);
        sleep(rand()%5);
    }
}