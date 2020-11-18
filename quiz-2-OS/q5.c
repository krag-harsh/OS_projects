#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;
pthread_mutex_t mutex;
int counting = 1;
int numberofread = 0;

void *writer(void *writernumber)
{   
    sem_wait(&sem);
	counting++;
	sleep(1);
    printf("Writer %d changed the counting to %d\n",(*((int *)writernumber)),counting);
    sem_post(&sem);

}

void *reader(void *readernumber)
{   
    pthread_mutex_lock(&mutex);
    numberofread++;
    if(numberofread == 1) 
        sem_wait(&sem);
    pthread_mutex_unlock(&mutex);
	sleep(2);
    printf("Reader %d: read the counting as %d\n",*((int *)readernumber),counting);

    pthread_mutex_lock(&mutex);
    numberofread--;
    if(numberofread == 0) 
        sem_post(&sem);
    pthread_mutex_unlock(&mutex);
}

int main()
{   
    pthread_t readerarray[5];
    pthread_t writerarray[3];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&sem,0,1);

    int a[5] = {1,2,3,4,5};

    for(int i=0;i<3;i++) 
        pthread_create(&writerarray[i], NULL, (void *)writer, (void *)&a[i]);

    for(int i=0;i<5;i++) 
        pthread_create(&readerarray[i], NULL, (void *)reader, (void *)&a[i]);

    for(int i=0;i<5;i++) 
        pthread_join(readerarray[i], NULL);

    for(int i=0;i<3;i++) 
        pthread_join(writerarray[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);

    return 0;   
}