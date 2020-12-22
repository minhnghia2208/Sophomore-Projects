#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int next_id = 1;
static sem_t lock;	// lock for id
static sem_t connected_lock;	// lock for connected line
static sem_t operators;		// lock for operators line
static int NUM_OPERATORS = 2;
static int NUM_LINES = 5;
static int connected = 0;    // Callers that are connected

void* phonecall(void* vargp) {
        // get id
        sem_wait(&lock);
        int id = next_id++;
        sem_post(&lock);

        printf("Thread [%i] is attemping to connect ...\n", id);
        sem_wait(&connected_lock);
        while (connected >= NUM_LINES) {        // if no free line then exit
                sem_post(&connected_lock);      // close lock so others can't access during sleep
                sleep(1);       // try again in one second
                sem_wait(&connected_lock); // open lock to check again
        }

        if (connected < NUM_LINES) { // connect if there is free line
                connected++;    // take the slot
                printf("Thread [%i] connects to and availale line, call ringing ...\n", id);
                sem_post(&connected_lock);
        }


        sem_wait(&operators);
        while (NUM_OPERATORS <= 0) {    // if no free operator then exit
                sem_post(&operators);
                sleep(1);       // try again in one second
                sem_wait(&operators);
        }

        if (NUM_OPERATORS > 0) {
                printf("Thread [%i] is speaking to an operator.\n", id);
                NUM_OPERATORS--;
                sem_post(&operators);

        }

        sleep(1);

        printf("Thread [%i] has proposed question! The operator has left ...\n", id);
        sem_wait(&operators);
        NUM_OPERATORS++;        // increase free operator after call
        sem_post(&operators);


        sem_wait(&connected_lock);
        connected--;    // create more slot after call
        sem_post(&connected_lock);
        printf("Thread [%i] has hung up!\n", id);
	pthread_detach(pthread_self());
        return NULL;
}
void* timer(void* vargp) {
        int length = *((int *)(vargp)); // take input
        sleep(length);
	pthread_detach(pthread_self());
        exit(0);        // stop thread after length time
}

void* main_thread(void*vargp) {
	
        int length = *((int *)(vargp)); // take input
        pthread_t tid[200]; // initialize array of 200 threads
        pthread_t timing;       // initilize timing thread

        if (pthread_create(&timing, NULL, timer, &length) != 0) printf("Fail to create thread.\n");
        for (int i = 0; i < 200; i++){  // Iterate and create 200 threads
                if (pthread_create(&tid[i], NULL, phonecall, NULL) != 0) printf("Fail to create thread.\n");
        }
        if (pthread_join(timing, NULL) != 0) printf("Fail to join thread.\n");
	pthread_detach(pthread_self());

}

int main(int argc, char **argv) {

        int length = atoi(argv[1]);     // take in the time length of debate

	if (sem_init(&lock, 0, 1) != 0) printf("Fail to init semaphores.\n");
        if (sem_init(&connected_lock, 0, 1) != 0) printf("Fail to init semaphore.\n");
        if (sem_init(&operators, 0, 1) != 0) printf("Fail to init semaphore.\n");

        pthread_t main_t;       // create main thread
        if (pthread_create(&main_t, NULL, main_thread, &length) != 0) printf("Fail to create thread.\n");
        if (pthread_join(main_t, NULL) != 0) printf("Fail to join thread.\n");

        // Destroy all locks and thread
        if (sem_destroy(&lock) != 0) printf("Fail to destroy semaphores.\n");
        if (sem_destroy(&connected_lock) != 0) printf("Fail to destroy semaphores.\n");
        if (sem_destroy(&operators) != 0) printf("Fail to destroy semaphores.\n");

        pthread_exit(NULL);
}


