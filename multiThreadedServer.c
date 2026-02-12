#include <pthread.h> 
#include <stdio.h> 
#include <errno.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h>
#include <signal.h>

void* doGreeting(void* arg); 
// void handleSigint(int sig);
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
        
        userFile[strcspn(userFile, "\n")] = '\0'; 
        
        char *fileName = malloc(strlen(userFile) + 1);
        if (!fileName) {
            perror("malloc failed.");
            continue;
        } 
        strcpy(fileName, userFile);
        // char userFile = ("Please input a file name: ");
        // scanf("%s", &userInput);

        //spawning child Just use the pthread_create()

        //repeating input and spawn process NEED loop aka multiple and rapid
        // char userInput;
        // char userFile = ("Please input a file name: ");
        // scanf("%s", &userInput);
    
        threadStatus1 = pthread_create (&thread1[numberOfFiles], NULL,  doGreeting, fileName); 
        if (threadStatus1 != 0){ 
            fprintf (stderr, "Thread create error %d: %s\n", threadStatus1, strerror(threadStatus1)); 
            free(fileName);
            continue;
        } 
        numberOfFiles ++;
    }

    printf("\nProgram terminating\n");
    printf("The total number of file request received: %d\n", numberOfFiles);
    fflush(stdout);
    for(int i = 0; i < numberOfFiles; i++) {
        pthread_join(thread1[i], NULL); 
    } 
    return 0; 
} 
void* doGreeting(void* myArgument) { 
    char *myPtr = (char *)myArgument; 
    // printf ("Child receiving %c initially sees %d\n", *myPtr, sharedData); 
    int probability = rand() % 100;
    if (probability < 80) {
        sleep(1);
    }
    else {
        int randomNumber = (rand() % 4) + 7;
        sleep(randomNumber);
    }
    printf ("The file accessed is: %s\n", myPtr); 
    free(myPtr);
    return NULL; 
}

