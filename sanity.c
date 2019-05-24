#include "types.h"
#include "user.h"

// just the definitions
void RRSanity();

int main(int argc, char const *argv[])
{
    
    //todo : add the argument processing for different sanity runs

    RRSanity();

    exit(); // father of all in all cases will exit here 
    return 0;
}

// implementation of normal round robin sanity test

void RRSanity()
{
    int numberOfChildern = 10;
    int numberOfLoops = 100;
    int pid;

    printf(1, "this is the RR sanity test\n");

    // create children
    for(int i = 0; i < numberOfChildern; i ++)
    {
        pid = fork();
        if(pid > 0) // father process
        {
            continue; // just jump back to the loop and make more children
        }
        else if (pid == 0) // child process
        {
            for(int i2 = 0; i2 < numberOfLoops; i2++)
            {
                int child_id = getpid();
                printf(1, "child id: %d is is on: %d\n", child_id, i2);
            }
            exit(); // child exits here
        }
        else // error in forking 
        {
            printf(1, "!!!!! for some reason there was a fork ERROR !!!!!\n");
            exit(); // exit father in case of fork error
        }
        
    }
    // father now should wait for his childern to exit
    for(int i = 0; i < numberOfChildern; i ++)
    {
        pid = wait();
        printf(1, "FATHER REPORTING: child with id: %d, is done\n", pid);
    }
};
