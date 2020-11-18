#include <stdio.h>          
#include <stdlib.h>         
#include <sys/types.h>      
#include <sys/shm.h>        
#include <errno.h>          
#include <semaphore.h>      
#include <fcntl.h>          
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main (int argc, char **argv){
    int i, shmid1, shmid2;                    
    key_t shmkey1, shmkey2;                
    sem_t *sem1, *sem2;                  
    pid_t pid;                    
    int *p;                                     
    unsigned int value1, value2;           
 
    shmkey1 = ftok ("/dev/null", 5);       
    shmkey2 = ftok ("shmfile", 65);
    shmid1 = shmget (shmkey1, sizeof (int), 0644 | IPC_CREAT);
    shmid2 = shmget (shmkey2, sizeof (int), 0644 | IPC_CREAT);

    p = (int *) shmat (shmid1, NULL, 0);   
    *p = 0;
    char *sharedch = (char *) shmat (shmid2, NULL, 0);   // attach sharedch to shared memory
    strcpy(sharedch,"initiated");
    // printf ("p=%d is allocated in shared memory.\n\n", *p);
    // printf ("p=%s is allocated in shared memory.\n\n", sharedch);

    value1=1;
    value2=1;

    //initialize semaphores
    sem1 = sem_open ("Psem1", O_CREAT | O_EXCL, 0644, value1); 
    sem2 = sem_open ("Psem2", O_CREAT | O_EXCL, 0644, value2); 

    printf ("semaphores initialized.\n\n");

    pid = fork ();
    if (pid < 0) 
    {
        sem_unlink ("Psem1");   
        sem_close(sem1);  
        printf ("Fork error.\n");
    }


    //PARENT PROCESS
    if (pid != 0){

        sem_wait (sem1);           /* P operation */
        sleep (1);
        *p = *p +1;             
        printf ("Writing in parent(int) new value of *p=%d.\n", *p);
        sem_post (sem1);           /* V operation */

        sem_wait (sem1);         
        // sleep (1);
        printf ("reading in parent(int) value of *p=%d.\n", *p);
        sem_post (sem1);           


        sem_wait (sem2);          
        sleep (1);
        strcpy(sharedch,"XYZ");    
        printf ("Writing in parent(char) new value: XYZ\n");
        sem_post (sem2);          

        sem_wait (sem2);          
        // sleep (1);
        printf ("reading in parent(char) value is=%s.\n",sharedch);
        sem_post (sem2);          



        waitpid (-1, NULL, 0);

        // printf ("\nParent: All children have exited.\n");
        shmdt (p);
        shmdt (sharedch);
        shmctl (shmid1, IPC_RMID, 0);
        shmctl (shmid2, IPC_RMID, 0);
        sem_unlink ("Psem1");   
        sem_close(sem1);  
        sem_unlink ("Psem2");   
        sem_close(sem2);
        exit (0);
    }

    //CHILD PROCESS
    else
    {

        sem_wait (sem1);           
        sleep (1);
        *p = *p +1;             
        printf ("Writing in Child(int) new value of *p=%d.\n", *p);
        sem_post (sem1);           

        sem_wait (sem1);          
        // sleep (1);
        printf ("reading in Child(int) value of *p=%d.\n", *p);
        sem_post (sem1);           


        sem_wait (sem2);          
        sleep (1);
        strcpy(sharedch,"ABCD");    
        printf ("Writing in Child(char) new value: ABCD\n");
        sem_post (sem2);          

        sem_wait (sem2);
        // sleep (1);
        printf ("reading in Child(char) value is=%s.\n",sharedch);
        sem_post (sem2); 

        exit (0);
    }
}