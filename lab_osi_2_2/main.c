
#include <unistd.h>
#include <stdio.h>

int main()
{
    int pid;
    printf("PID родительского %d\n", getpid());
    pid = fork(); // создание нового процесса, который является точной копией текущего процесса, но имеет свой PID
    printf("если процесс родительский то fork() вернет PID дочки: PID = %d\n", pid);

    if (pid == -1) {// Ошибка при создании процесса
        printf("troubles");
    } else if (pid == 0) {//если PID == 0 -> мы находимся в дочернем процессе
        printf("\nДочка! PID: %d\n", getpid());
    } else {//fork() В род.процессе возвращает идентификатор дочки
        printf("\nМама! (PID: %d), дочка PID: %d\n", getpid(), pid);
    }
}

//абсолютная параллельность