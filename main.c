#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int randomFile;

int randint()
{
    int random;
    int readCheck = read(randomFile, &random, sizeof(random));
    if (readCheck == -1)
    {
        printf("Error while reading from random file.\n");
        return -1;
    }
    else
    {
        return random;
    }
}

void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("\trandom #%d: %d\n", i, *(arr + i));
    }
}

int main()
{
    randomFile = open("/dev/random", O_RDONLY);
    if (randomFile == -1)
    {
        printf("Error opening /dev/random - errno: %d error msg:%s\n", errno, strerror(errno));
        return 1;
    }
    printf("Generating random numbers:\n");
    int randArr[10];
    for (int i = 0; i < 10; i++)
    {
        randArr[i] = randint();
    }
    printArray(randArr, 10);
    printf("\nWriting numbers to file...\n");
    int outFile = open("tmp", O_CREAT | O_WRONLY, 0664);
    if (outFile == -1)
    {
        printf("Error opening tmp file - errno: %d error msg:%s\n", errno, strerror(errno));
        return 1;
    }
    int writeCheck = write(outFile,randArr,sizeof(randArr));
    if (writeCheck==-1)
    {
        printf("Error writing to tmp file - errno: %d error msg:%s\n", errno, strerror(errno));
        return 1;
    }
    printf("done.\n");

    printf("\nReading numbers to file...\n");
    int inFile = open("tmp", O_RDONLY);
    if (inFile == -1)
    {
        printf("Error opening tmp file - errno: %d error msg:%s\n", errno, strerror(errno));
        return 1;
    }
    int newArr[10];
    int readCheck = read(inFile,newArr,sizeof(newArr));
    if (readCheck==-1)
    {
        printf("Error reading from tmp file - errno: %d error msg:%s\n", errno, strerror(errno));
        return 1;
    }
    printf("done.\n\nVerification that written values were the same:\n");
    printArray(newArr, 10);
    printf("done.\n");
    return 0;
}