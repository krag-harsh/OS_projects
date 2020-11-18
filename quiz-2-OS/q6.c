#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t room;
sem_t spoon[5];

void *philosopher(void * num)
{
	int phphernum=*(int *)num;

	if(phphernum==4)		//the last philosopher first takes spoon on right, this will avoid anytype of deadlock
	{
		sem_wait(&room);
		sem_wait(&spoon[(phphernum+1)%5]);
		printf("P%d receives F%d\n",phphernum,phphernum);
		sem_wait(&spoon[phphernum]);
		printf("P%d receives F%d,F%d\n",phphernum,phphernum,(phphernum+1)%5);

		printf("P%d is eating\n",phphernum);
		sleep(2);
		// printf("phphernumosopher %d has finished eating\n",phphernum);

		sem_post(&spoon[phphernum]);
		sem_post(&spoon[(phphernum+1)%5]);
		printf("P%d has finished eating and kept back F%d,F%d\n",phphernum,phphernum,(phphernum+1)%5);
		sem_post(&room);
	}
	else
	{
		sem_wait(&room);
		sem_wait(&spoon[phphernum]);
		printf("P%d receives F%d\n",phphernum,phphernum);
		sem_wait(&spoon[(phphernum+1)%5]);
		printf("P%d receives F%d,F%d\n",phphernum,phphernum,(phphernum+1)%5);

		printf("P%d is eating\n",phphernum);
		sleep(2);
		// printf("phphernumosopher %d has finished eating\n",phphernum);

		sem_post(&spoon[(phphernum+1)%5]);
		sem_post(&spoon[phphernum]);
		printf("P%d has finished eating and kept back F%d,F%d\n",phphernum,phphernum,(phphernum+1)%5);
		sem_post(&room);
	}

}


int main()
{
	int i,a[5];
	pthread_t tid[5];
	
	sem_init(&room,0,4);
	
	for(i=0;i<5;i++)
		sem_init(&spoon[i],0,1);
		
	for(i=0;i<5;i++)
	{
		a[i]=i;
		pthread_create(&tid[i],NULL,philosopher,(void *)&a[i]);
	}

	for(i=0;i<5;i++)
		pthread_join(tid[i],NULL);

	printf("All the professor have eaten once successfully\n");

	return 0;
}
