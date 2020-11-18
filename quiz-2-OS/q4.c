#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main (int argc, char **argv){
    int i;                        /*      loop variables          */
    key_t shmkey1, shmkey2;                 /*      shared memory key       */
    int shmid1, shmid2;                    /*      shared memory id        */
    sem_t *sem1, *sem2;                   /*      synch semaphore         *//*shared */
    pid_t pid;                    /*      fork pid                */
    int *p;                       /*      shared variable         *//*shared */
    unsigned int n;               /*      fork count              */
    unsigned int value1, value2;           /*      semaphore value1         */

    /* initialize a shared variable in shared memory */
    shmkey1 = ftok ("/dev/null", 5);       /* valid directory name and a number */
    shmkey2 = ftok ("shmfile", 65);
    //printf ("shmkey1 for p = %d\n", shmkey1);
    shmid1 = shmget (shmkey1, sizeof (int), 0644 | IPC_CREAT);
    shmid2 = shmget (shmkey2, sizeof (int), 0644 | IPC_CREAT);
    if (shmid1 < 0){                           /* shared memory error check */
        perror ("shmget\n");
        exit (1);
    }

    p = (int *) shmat (shmid1, NULL, 0);   /* attach p to shared memory */
    *p = 0;
    char *sharedch = (char *) shmat (shmid2, NULL, 0);   /* attach sharedch to shared memory */
    strcpy(sharedch,"initiated");
    // printf ("p=%d is allocated in shared memory.\n\n", *p);
    // printf ("p=%s is allocated in shared memory.\n\n", sharedch);


    /********************************************************/
    n=1;
    value1=1;
    value2=1;

    /* initialize semaphores for shared processes */
    sem1 = sem_open ("Psem1", O_CREAT | O_EXCL, 0644, value1); 
    sem2 = sem_open ("Psem2", O_CREAT | O_EXCL, 0644, value2); 
    /* name of semaphore is "Psem1", semaphore is reached using this name */

    printf ("semaphores initialized.\n\n");

    pid = fork ();
    if (pid < 0) {
        sem_unlink ("Psem1");   
        sem_close(sem1);  
        printf ("Fork error.\n");
    }



    /******************************************************/
    /******************   PARENT PROCESS   ****************/
    /******************************************************/
    if (pid != 0){

        sem_wait (sem1);           /* P operation */
        // printf ("  Child(%d) is in critical section.\n", i);
        sleep (1);
        *p = *p +1;             
        printf ("Writing in parent(int) new value of *p=%d.\n", *p);
        sem_post (sem1);           /* V operation */

        sem_wait (sem1);           /* P operation */
        // sleep (1);
        printf ("reading in parent(int) value of *p=%d.\n", *p);
        sem_post (sem1);           /* V operation */


        sem_wait (sem2);           /* P operation */
        // printf ("  Child(%d) is in critical section.\n", i);
        sleep (1);
        strcpy(sharedch,"XYZ");    
        printf ("Writing in parent(char) new value: XYZ\n");
        sem_post (sem2);           /* V operation */

        sem_wait (sem2);           /* P operation */
        // sleep (1);
        printf ("reading in parent(char) value is=%s.\n",sharedch);
        sem_post (sem2);           /* V operation */



        waitpid (-1, NULL, 0);

        printf ("\nParent: All children have exited.\n");

        /* shared memory detach */
        shmdt (p);
        shmdt (sharedch);
        shmctl (shmid1, IPC_RMID, 0);
        shmctl (shmid2, IPC_RMID, 0);

        /* cleanup semaphores */
        sem_unlink ("Psem1");   
        sem_close(sem1);  
        sem_unlink ("Psem2");   
        sem_close(sem2);
        /* unlink prevents the semaphore existing forever */
        /* if a crash occurs during the execution         */
        exit (0);
    }

    /******************************************************/
    /******************   CHILD PROCESS   *****************/
    /******************************************************/
    else{

        sem_wait (sem1);           /* P operation */
        // printf ("  Child(%d) is in critical section.\n", i);
        sleep (1);
        *p = *p +1;             
        printf ("Writing in Child(int) new value of *p=%d.\n", *p);
        sem_post (sem1);           /* V operation */

        sem_wait (sem1);           /* P operation */
        // sleep (1);
        printf ("reading in Child(int) value of *p=%d.\n", *p);
        sem_post (sem1);           /* V operation */


        sem_wait (sem2);           /* P operation */
        // printf ("  Child(%d) is in critical section.\n", i);
        sleep (1);
        strcpy(sharedch,"ABCD");    
        printf ("Writing in Child(char) new value: ABCD\n");
        sem_post (sem2);           /* V operation */

        sem_wait (sem2);           /* P operation */
        // sleep (1);
        printf ("reading in Child(char) value is=%s.\n",sharedch);
        sem_post (sem2);           /* V operation */


        exit (0);
    }
}