#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

int numPhilo;		//  creating the number of philosopher as global variable
int spaceleft=1;

struct my_semaphore
{
	pthread_mutex_t mutex;		//mutex lock
	pthread_cond_t cond;		//condition variable
	int val;
};

int wait(struct my_semaphore *sem)
{
	pthread_mutex_lock(&sem->mutex);
	sem->val--;
	pthread_mutex_unlock(&sem->mutex);
	// if(sem->val < 0)
	// 	pthread_cond_wait(&sem->cond, &sem->mutex);	//this will make the process to wait
	if(sem->val < 0)
	{
		// spaceleft=0;	
		// sleep(2);
		return -1;
	}
	return 0;

}

int signal(struct my_semaphore *sem)
{
	pthread_mutex_lock(&sem->mutex);
	//sem->val++;
	sem->val=1;
	pthread_mutex_unlock(&sem->mutex);
	// if(sem->val <=0)
	// pthread_cond_signal(&sem->cond);
	return 0;

}

void PrintValue(struct my_semaphore *s)		//function for debugging
{
	printf("%d\n", s->val);
}


struct helperStruct
{
	struct my_semaphore* helper_fork;
	struct my_semaphore* helper_forknext;
	int helper_philoNumber;
};

// struct my_semaphore room;
struct my_semaphore bowl;		// Pair of bowl is taken as one object because both the bowls is needed at a time

void* work(void* helper_var){
	//int c=0;
	
	int num = (*(struct helperStruct*)helper_var).helper_philoNumber;
	struct my_semaphore *fork = ((struct helperStruct*)helper_var)->helper_fork;
	struct my_semaphore *forknext = ((struct helperStruct*)helper_var)->helper_forknext;
	
	while(1)
	{
		int c=0;
		while(c==-1)
		{
			c= wait(&bowl);
		}

		// printf("Philosopher %d eats using forks %d and %d\n",num, num,(num+1)%numPhilo);
		// sleep(2);

		// if(c!=-1)
		// {
		printf("Philosopher %d eats using forks %d and %d\n",num, num,(num+1)%numPhilo);
		sleep(1);
		signal(&bowl);
			// (&bowl)->val=1;
		// }

		// c=signal(&bowl);
	}
	
	// PrintValue(fork);

}

int main(int argc, char const *argv[])
{	

	printf("Enter the number of Philosophers\n");
	scanf("%d",&numPhilo);

	struct my_semaphore forks[numPhilo];

	//  This struct is used to pass multiple arguments using pthread_create
	struct helperStruct helper[numPhilo];

	pthread_t tid[numPhilo];
	
	// A pair of bowl is needed for eating and when eating is done both the bowls are left therefore we are creating a single bowl.under the assumption that they pick both bowl very fast.
	pthread_mutex_init(&(&bowl)->mutex, NULL);			
	pthread_cond_init(&(&bowl)->cond, NULL);
	(&bowl)->val = 1;


	for(int i=0; i<numPhilo; i++)
	{

		pthread_mutex_init(&(&forks[i])->mutex, NULL);
		pthread_cond_init(&(&forks[i])->cond, NULL);
		(&forks[i])->val = 1;

		helper[i].helper_fork = &forks[i];
		// helper[i].helper_forknext = &forks[(i+1)%numPhilo];
	}


	for(int i=0; i<numPhilo;i++)
	{
		helper[i].helper_forknext = &forks[(i+1)%numPhilo];
	}


	for(int i=0; i<numPhilo; i++)
	{
		helper[i].helper_philoNumber = i;			
		pthread_create(&tid[i],NULL, &work, (void*)&helper[i]);
	}

	for(int i=0; i<numPhilo; i++)
		pthread_join(tid[i], NULL);


	return 0;
}