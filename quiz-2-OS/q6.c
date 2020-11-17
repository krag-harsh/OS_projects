#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t room;
sem_t chopstick[5];

// void * philosopher(void *);

void * philosopher(void * num)
{
	int phil=*(int *)num;

	if(phil==4)
	{
		sem_wait(&room);
		//printf("Philosopher %d has entered room",phil);
		sem_wait(&chopstick[(phil+1)%5]);
		printf("P%d received F%d\n",phil,phil);
		sem_wait(&chopstick[phil]);
		printf("P%d received F%d and F%d\n",phil,phil,(phil+1)%5);

		// eat(phil);
		printf("Philosopher %d is eating\n",phil);
		sleep(2);
		printf("Philosopher %d has finished eating\n",phil);

		sem_post(&chopstick[phil]);
		sem_post(&chopstick[(phil+1)%5]);
		sem_post(&room);
	}
	else
	{
		sem_wait(&room);
		// printf("Philosopher %d has entered room",phil);
		sem_wait(&chopstick[phil]);
		printf("P%d received F%d\n",phil,phil);
		sem_wait(&chopstick[(phil+1)%5]);
		printf("P%d received F%d and F%d\n",phil,phil,(phil+1)%5);

		// eat(phil);
		printf("Philosopher %d is eating\n",phil);
		sleep(2);
		printf("Philosopher %d has finished eating\n",phil);

		sem_post(&chopstick[(phil+1)%5]);
		sem_post(&chopstick[phil]);
		sem_post(&room);
	}

}


int main()
{
	int i,a[5];
	pthread_t tid[5];
	
	sem_init(&room,0,4);
	
	for(i=0;i<5;i++)
		sem_init(&chopstick[i],0,1);
		
	for(i=0;i<5;i++){
		a[i]=i;
		pthread_create(&tid[i],NULL,philosopher,(void *)&a[i]);
	}
	for(i=0;i<5;i++)
		pthread_join(tid[i],NULL);

	printf("All the professor have eaten successfully\n");
}
