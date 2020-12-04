/*	HARSH KUMAR AGARWAL
	2019423		*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

int NumPhil;		//  creating the number of philosopher as global variable


struct my_semaphore		//Here is the struct we need to create
{
	pthread_mutex_t mutex;		//mutex lock
	pthread_cond_t cond;		//condition variable
	int val;
};

void wait(struct my_semaphore *sem)		//our wait function with blocking
{
	pthread_mutex_lock(&sem->mutex);		//using lock so that not more than one thread can access this part of the code at same time
	sem->val--;
	if(sem->val < 0)		//will check if the value of the semaphore is less than 0 or not, if not will make the thread wait for the signal
		pthread_cond_wait(&sem->cond, &sem->mutex);	//this will make the process to wait
	pthread_mutex_unlock(&sem->mutex);

}

void signal(struct my_semaphore *sem)		//our signal fucntion 
{
	pthread_mutex_lock(&sem->mutex);		//using lock so that not more than one thread can access this part of the code at same time
	sem->val++;
	if(sem->val <=0)		//check the condition for sending back the signal
	pthread_cond_signal(&sem->cond);	//signal back that now other thread can enter
	// sem->val++;
	pthread_mutex_unlock(&sem->mutex);

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

// struct my_semaphore room;
struct my_semaphore bowl;		// Pair of bowl is taken as one object because both the bowls is needed at a time

void* working(void* hvariable){
	
	//storing passed values to variables.
	int num = (*(struct helperStruct*)hvariable).h_p_number;
	struct my_semaphore *fork = ((struct helperStruct*)hvariable)->h_f;
	struct my_semaphore *forknext = ((struct helperStruct*)hvariable)->h_fnext;
	
	while(1)		//so that our loop goes on for infinit, we can stop using ctrl+c on terminal
	{
		//wait(&room);
		wait(&bowl);		//first we are selecting bowl this will avoid any kind of deadlock
		wait(fork);		//selecting first fork
		wait(forknext);		//selecting second fork
		
		printf("Philosopher %d eats using forks %d and %d\n",num, num,(num+1)%NumPhil);
		sleep(1);

		signal(forknext);		//keeping back second fork
		signal(fork);		//keeping back first fork
		signal(&bowl);
		//signal(&room);
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
	
	//  In order to avoid deadlocks, n-1 philosophers should be allowed in a room at once
	// pthread_mutex_init(&(&room)->mutex, NULL);			
	// pthread_cond_init(&(&room)->cond, NULL);
	// (&room)->val = NumPhil-1;

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