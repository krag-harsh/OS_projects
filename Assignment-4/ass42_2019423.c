/*	HARSH KUMAR AGARWAL
	2019423		*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

int NumPhil;		//  creating the number of philosopher as global variable
int spaceleft=1;

struct my_semaphore
{
	pthread_mutex_t mutex;		//mutex lock
	pthread_cond_t cond;		//condition variable
	int val;
};

int wait(struct my_semaphore *sem)		//our own wait function(without blocking)
{
	pthread_mutex_lock(&sem->mutex);		//locks so that the part of the code cannot be accessed by multiple threads at once
	sem->val--;
	pthread_mutex_unlock(&sem->mutex);

	if(sem->val < 0)		//condition if the resources are available
	{
		// spaceleft=0;	
		return -1;		//if the resources are not available it will return with -1
	}
	return 0;		//if the resources are available, it will return with 0

}

int signal(struct my_semaphore *sem)
{
	pthread_mutex_lock(&sem->mutex);
	//sem->val++;
	sem->val=1;		//we are using constant value,explained in the writeup
	pthread_mutex_unlock(&sem->mutex);
	// if(sem->val <=0)
	// pthread_cond_signal(&sem->cond);
	return 0;

}

void PrintValue(struct my_semaphore *s)		//function for debugging(which was asked)
{
	printf("%d\n", s->val);
}


struct helperStruct			//creating this stuct so that we can pass many values at once.
{
	struct my_semaphore* h_f;
	struct my_semaphore* h_fnext;
	int h_p_number;
};

struct my_semaphore bowl;		// Pair of bowl is taken as one object because both the bowls is needed at a time

void* working(void* hvariable){
	
	//storing passed values to variables.
	int num = (*(struct helperStruct*)hvariable).h_p_number;
	struct my_semaphore *fork = ((struct helperStruct*)hvariable)->h_f;
	struct my_semaphore *forknext = ((struct helperStruct*)hvariable)->h_fnext;
	
	while(1)
	{
		int c=0;
		while(c==-1)		//this loop will continue until there is free resource available
		{
			c= wait(&bowl);
		}

		// if(c!=-1)
		// {
		printf("Philosopher %d eats using forks %d and %d\n",num, num,(num+1)%NumPhil);		//printing as asked in the question
		sleep(1);
		signal(&bowl);		//once the resources are available we signal it
			// (&bowl)->val=1;
		// }

		// c=signal(&bowl);
	}
	
	// PrintValue(fork);

}

int main(int argc, char const *argv[])
{	

	printf("Enter the Number of Philosophers\n");
	scanf("%d",&NumPhil);

	//  This struct is used to pass multiple arguments using pthread_create
	struct helperStruct helper[NumPhil];
	struct my_semaphore forks[NumPhil];

	pthread_t tid[NumPhil];		//creating threads
	
	// A pair of bowl is needed for eating and when eating is done both the bowls are left therefore we are creating a single bowl.under the assumption that they pick both bowl very fast.
	pthread_mutex_init(&(&bowl)->mutex, NULL);			
	pthread_cond_init(&(&bowl)->cond, NULL);
	(&bowl)->val = 1;


	for(int i=0; i<NumPhil; i++)
	{
		//initialising mutex and conditions and value of the struct
		pthread_mutex_init(&(&forks[i])->mutex, NULL);		//initialising mutex and conditions
		pthread_cond_init(&(&forks[i])->cond, NULL);
		(&forks[i])->val = 1;

		// helper[i].h_f = &forks[i];
	}

	for(int i=0; i<NumPhil;i++)		//loop so that we can copy our data to helper function(so that can be passed easily)
	{
		helper[i].h_f = &forks[i];
	}

	for(int i=0; i<NumPhil;i++)		//loop so that we can copy our data to helper function(so that can be passed easily)
	{
		helper[i].h_fnext = &forks[(i+1)%NumPhil];
	}

	for(int i=0; i<NumPhil; i++)
	{
		helper[i].h_p_number = i;			
		pthread_create(&tid[i],NULL, &working, (void*)&helper[i]);		//calling thread with working function
	}

	for(int i=0; i<NumPhil; i++)
		pthread_join(tid[i], NULL);		//joining all the function created

	return 0;
}