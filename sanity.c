#include "types.h"
#include "user.h"

// just the definitions
void RRSanity();
void QQQSanity();

int main(int argc, char const *argv[])
{
    
    //todo : add the argument processing for different sanity runs

    QQQSanity();

    exit(); // father of all in all cases will exit here 
    return 0;
}

// implementation of normal round robin sanity test

void RRSanity()
{
    int numberOfChildern = 10;
    int numberOfLoops = 50;
    int pid;

    // arrays to hold the reports
    int child_ids[numberOfChildern];
    int wait_times[numberOfChildern];
    int run_times[numberOfChildern];

    // integers to pass in and get reports
    int wtime, rtime;

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
                // int child_id = getpid();
                // printf(1, "child id: %d is is on: %d\n", child_id, i2);
                sleep(5);
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
        // printf(1, "father waiting for ith time: %d", i);
        pid = wait_and_performance(&wtime, &rtime); // pass in the address of ints to get them filled : /
        child_ids[i] = pid;
        wait_times[i] = wtime;
        run_times[i] = rtime;
        printf(1, "FATHER REPORTING: child with id: %d, is done\n", pid);
    }

    // report:
    for (int i = 0; i < numberOfChildern; i++)
    {
        printf(1, "child report\t id: %d, run time: %d, wait time: %d\n", child_ids[i], run_times[i], wait_times[i]);
    }
};

void QQQSanity()
{
    int numberOfChildern = 30;
    int numberOfLoops = 10;
    int pid;

    int wtime, rtime;

    for(int i = 0; i < numberOfChildern; i ++)
    {
        pid = fork();
        if(pid > 0) // father process
        {
            continue; // just jump back to the loop and make more children
        }
        else if (pid == 0) // child process
        {
            int cid = i;
            int nice_time = i % 3;
            int child_id = getpid();
            while(nice_time > 0)
            {
                nice(child_id);
                nice_time = nice_time -1;
            }
            for(int i2 = 0; i2 < numberOfLoops; i2++)
            {
                printf(1, "child id: %d is is on: %d\n", cid, i2);
                // sleep(5);
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
        // printf(1, "father waiting for ith time: %d", i);
        pid = wait_and_performance(&wtime, &rtime); // pass in the address of ints to get them filled : /
        // child_ids[i] = pid;
        // wait_times[i] = wtime;
        // run_times[i] = rtime;
        printf(1, "FATHER REPORTING: child with id: %d, is done\n", pid);
    }
}