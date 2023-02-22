/*
WORKED WITH:
- JOHN
- JEFF
- JOSE
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

void *thread_function(int n);

pthread_t philosopher[5];
pthread_mutex_t chopstick[5];

int main()
{
    int res, i;
    void *msg;

    for (i = 1; i <= 5; i++)
    {
        res = pthread_mutex_init(&chopstick[i], NULL);
        if (res == -1)
        {
            printf("\n Mutex initialization failed");
            exit(1);
        }
    }
    for (i = 1; i <= 5; i++)
    {
        res = pthread_create(&philosopher[i], NULL, (void *)thread_function, (int *)i);
        if (res != 0)
        {
            printf("\n Thread creation error \n");
            exit(1);
        }
    }
    for (i = 1; i <= 5; i++)
    {
        res = pthread_join(philosopher[i], &msg);
        if (res != 0)
        {
            printf("\n Thread join failed \n");
            exit(1);
        }
    }
    for (i = 1; i <= 5; i++)
    {
        res = pthread_mutex_destroy(&chopstick[i]);
        if (res != 0)
        {
            printf("\n Mutex Destroyed \n");
            exit(1);
        }
    }
    return 0;
}

void *thread_function(int n)
{
    printf("Philosopher % d is thinking \n", n);
    pthread_mutex_lock(&chopstick[n]); // 1, 2, 3, 4, 5
    pthread_mutex_lock(&chopstick[(n + 1) % 5]); // 1, 2, 3, 4, 0
    printf("Philosopher % d is eating \n", n);
    sleep(3);
    pthread_mutex_unlock(&chopstick[n]);
    pthread_mutex_unlock(&chopstick[(n + 1) % 5]);
    printf("Philosopher % d Finished eating \n", n);
}