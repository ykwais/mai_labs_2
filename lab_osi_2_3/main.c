#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i+1)%N

#define THINKING 0
#define HUNGRY 1
#define EATING 2



sem_t s[N];//семафор на каждого
int state[N];//cостояние каждого
sem_t mutex;//0 - доступ разрешен, иначе запрещен


void test(int i)
{
    if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
        state[i] = EATING;
        sem_post(&s[i]);//открываем доступ значение семафора +1
    }
}

void take_forks(int i)
{
    sem_wait(&mutex);//семафор -1//вход в критическую область
    state[i] = HUNGRY;//стремится поесть
    test(i);
    sem_post(&mutex);//выход из критической области
    sem_wait(&s[i]);


}

void put_forks(int i)
{
    sem_wait(&mutex);
    state[i] = THINKING;
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void* philosoph(void* pos)
{
    int i = *((int*)pos);
    while(1)
    {
        printf("философ #%d размышляет...\n", i+1);
        sleep(2);

        printf("философ №%d проголодался\n", i+1);
        take_forks(i);

        printf("философ №%d взял левую вилку %d и правую вилку %d и употребляет пищу\n", i+1, i+1, RIGHT+1);
        sleep(2);

        printf("философ #%d закончил кушац и кладет обе вилки\n", i+1);
        put_forks(i);


    }
}

int main() {


    pthread_t potok[N];//создание 5 потоков

    if(sem_init(&mutex, 0, 1) ==  -1){//объявляем мьютекс = 1, так как в начале мы должны бьть способн войти в критическую область
        printf("ошибка объявления семафора\n");
        return 0;
    }
    for(int i = 0; i<N; ++i){
        sem_init(&s[i], 0, 0);//семафор для каждого философа = 0, чтобы контролировать работу
    }
    for(int i = 0; i < N; ++i){
        state[i] = i;
        pthread_create(&potok[i], NULL, philosoph, &state[i]);//создание нового потока для philosoph
    }
    for(int i = 0; i < N; ++i){
        pthread_join(potok[i], NULL);//ожидаем завершение потока
    }


}
