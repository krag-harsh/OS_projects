#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>


//  Global vars
int numPhilo;


struct my_semaphore{
	pthread_mutex_t mutex;	//mutex lock
	pthread_cond_t cond;		//condition variable k basis pe
	int val;
};

void wait(struct my_semaphore *sem)
{
	// pthread_mutex_lock(&sem->mutex);
	// while(sem->val == 0)
	// 	pthread_cond_wait(&sem->cond, &sem->mutex);	//wait karwayega process ko
	// sem->val--;
	// pthread_mutex_unlock(&sem->mutex);

	pthread_mutex_lock(&sem->mutex);
	sem->val--;
	if(sem->val < 0)
		pthread_cond_wait(&sem->cond, &sem->mutex);	//wait karwayega process ko
	pthread_mutex_unlock(&sem->mutex);
}

void signal(struct my_semaphore *sem)
{
	// pthread_mutex_lock(&sem->mutex);
	// sem->val++;
	// pthread_cond_signal(&sem->cond);
	// pthread_mutex_unlock(&sem->mutex);
	pthread_mutex_lock(&sem->mutex);
	sem->val++;
	if(sem->val <=0)
	pthread_cond_signal(&sem->cond);	//wait karwayega process ko
	pthread_mutex_unlock(&sem->mutex);
}

void PrintValue(struct my_semaphore *s)
{
	printf("%d\n", s->val);
}


struct helperStruct{

	// struct my_semaphore* helper_room;
	// struct my_semaphore* helper_bowl;
	struct my_semaphore* helper_fork;
	struct my_semaphore* helper_forknext;
	int helper_philoNumber;

};

// struct my_semaphore room;
struct my_semaphore bowl;		// Pair of bowl is taken as one object because both the bowls is needed at a time

void* work(void* helper_var){
	
	int num = (*(struct helperStruct*)helper_var).helper_philoNumber;
	struct my_semaphore *fork = ((struct helperStruct*)helper_var)->helper_fork;
	struct my_semaphore *forknext = ((struct helperStruct*)helper_var)->helper_forknext;
	
	while(1)
	{
		//wait(&room);
		wait(&bowl);
		wait(fork);
		wait(forknext);
		
		printf("Philosopher %d eats using forks %d and %d\n",num, num,(num+1)%numPhilo);
		sleep(1);

		signal(forknext);
		signal(fork);
		signal(&bowl);
		//signal(&room);
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
	
	//  In order to avoid deadlocks, n-1 philosophers should be allowed in a room at once
	// sem_INIT(&room, numPhilo-1);

	// pthread_mutex_init(&(&room)->mutex, NULL);			
	// pthread_cond_init(&(&room)->cond, NULL);
	// (&room)->val = numPhilo-1;

	// A pair of bowl is needed for eating and when eating is done both the bowls are left therefore we are creating a single bowl.under the assumption that they pick both bowl very fast.
	// sem_INIT(&bowl, 1);
	pthread_mutex_init(&(&bowl)->mutex, NULL);			
	pthread_cond_init(&(&bowl)->cond, NULL);
	(&bowl)->val = 1;

	// helper[i].helper_bowl = &bowl;
	// helper[i].helper_room = &room;


	for(int i=0; i<numPhilo; i++){

		pthread_mutex_init(&(&forks[i])->mutex, NULL);
		pthread_cond_init(&(&forks[i])->cond, NULL);
		(&forks[i])->val = 1;

		helper[i].helper_fork = &forks[i];
		helper[i].helper_forknext = &forks[(i+1)%numPhilo];
	}

	for(int i=0; i<numPhilo; i++){
		helper[i].helper_philoNumber = i;				// For checking the baju vala banda //
		pthread_create(&tid[i],NULL, &work, (void*)&helper[i]);
	}

	for(int i=0; i<numPhilo; i++)
		pthread_join(tid[i], NULL);

	return 0;
}