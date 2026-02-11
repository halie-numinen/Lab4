#include <pthread.h> 
#include <stdio.h> 
#include <errno.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h>
#include <signal.h>

void* doGreeting(void* arg); 
void handleSigint(int sig);
// global (shared and specific) data 
volatile sig_atomic_t shutdown_requested = 0;

//char sampleArray[2] = {'a','b'}; 

void handleSigint(int sig) {
    // printf("%d", numberOfFiles);
    shutdown_requested = 1;
}

int main() { 
    pthread_t thread1[500]; 
    // void *result1; 
    int threadStatus1; 
    int joinStatus1;

    int numberOfFiles = 0; 
    char userFile[500];  // buffer
    srand(time(NULL));

    signal(SIGINT, handleSigint);

    while(shutdown_requested != 1) {
        //getting user input of filename
        printf("Please input a file name: "); 
        if (fgets(userFile, 500, stdin) == NULL) {
            break;
            
        }
        numberOfFiles ++;
        userFile[strcspn(userFile, "\n")] = '\0'; 
        char *fileName = malloc(strlen(userFile) + 1);
        if (!fileName) {
            perror("malloc failed.");
            continue;
        } 
        // char userFile = ("Please input a file name: ");
        // scanf("%s", &userInput);

        //spawning child Just use the pthread_create()

        //repeating input and spawn process NEED loop aka multiple and rapid
        // char userInput;
        // char userFile = ("Please input a file name: ");
        // scanf("%s", &userInput);
    
        threadStatus1 = pthread_create (&thread1[numberOfFiles], NULL,  doGreeting, &userFile[0]); 
        if (threadStatus1 != 0){ 
            fprintf (stderr, "Thread create error %d: %s\n", threadStatus1, strerror(threadStatus1)); 
            exit (1); 
        } 
    }
    // printf ("Parent sees %d\n", sharedData); 
    // sharedData++; 
    
    // printf ("Parent sees %d\n", sharedData);
    for(int i = 0; i < numberOfFiles; i++) {
        joinStatus1 = pthread_join(thread1[i], NULL); 
        if (joinStatus1 != 0) { 
            fprintf (stderr, "Join error %d: %s\n", joinStatus1, strerror(joinStatus1)); 
            exit (1); 
        } 
    } 
    return 0; 
} 
void* doGreeting(void* myArgument) { 
    char *myPtr[500] = {(char *)myArgument}; 
    // printf ("Child receiving %c initially sees %d\n", *myPtr, sharedData); 
    int probability = rand() % 100;
    if (probability < 80) {
        sleep(1);
    }
    else {
        int randomNumber = (rand() % 4) + 7;
        sleep(randomNumber);
    }
    printf ("Child receiving %s now sees\n", *myPtr); 
    return NULL; 
}

