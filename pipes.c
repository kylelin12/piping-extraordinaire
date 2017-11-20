#include "pipes.h"

int main() {
    int READ = 0; // READ IS INDEX 0
    int WRITE = 1; // WRITE IS INDEX 1
    int value = 2; // VALUE TO SEND IS 2

    int fdsparchild[2]; // First pipe. Parent writes. Child reads.
    pipe(fdsparchild); // Initialized

    int fdschildpar[2]; // Second pipe. Parent reads. Child writes.
    pipe(fdschildpar); // Initialized

    if (fork() == 0) {
        // Child
        close(fdsparchild[WRITE]); // Close the unused pipe
        close(fdschildpar[READ]); // Closed the unused pipe

        read(fdsparchild[READ], &value, sizeof(value)); // Block until a value is received from the parent
        close(fdsparchild[READ]); // Close the read pipe now that you read the value
        
        printf("[child] doing quick maffs on: %d\n", value); // Print what value is received
        value = value + value - 1; // Quick maffs

        write(fdschildpar[WRITE], &value, sizeof(value)); // Write the result to the parent
        close(fdschildpar[WRITE]); // Close the write pipe now that the value has been written
    } else {
        // Parent
        close(fdsparchild[READ]); // Close the unused pipes
        close(fdschildpar[WRITE]); // Close the unused pipes

        printf("[parent] sending: %d\n", value); // Print what value is being sent
        write(fdsparchild[WRITE], &value, sizeof(value)); // Write the input value to the parent
        close(fdsparchild[WRITE]); // Close the write pipe now that the value has been written

        read(fdschildpar[READ], &value, sizeof(value)); // Block until a value is received from the child
        close(fdschildpar[READ]); // Close the read pipe now that a value has been read
        printf("[parent] received: %d\n", value); // Print the received value
    }

    return 0;
}