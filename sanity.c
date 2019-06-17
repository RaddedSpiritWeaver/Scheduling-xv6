#include "types.h"
#include "user.h"

// just the definitions
void RRSanity();
void FRRSanity();
void GRTSanity();
void QQQSanity();

int main(int argc, char const *argv[])
{
    
    //todo : add the argument processing for different sanity runs

    if(argc > 1)
    {
        for(int i = 0; i < argc; i++) // process arguments
        {
            if(0 == strcmp(argv[i], "-3Q"))
                QQQSanity();
            if(0 == strcmp(argv[i], "-RR"))
                RRSanity();
            if(0 == strcmp(argv[i], "-FRR"))
                FRRSanity();
            if(0 == strcmp(argv[i], "-GRT"))
                GRTSanity();
            if(0 == strcmp(argv[i], "-ALL"))
            {
                RRSanity();
                FRRSanity();
                GRTSanity();
                QQQSanity();
            }
            if(0 == strcmp(argv[i], "--help"))
            {
                printf(1, "this is command is used for all sanity tests\n");
                printf(1, "-RR for Round Rubin and XV6 defualt policy\n");
                printf(1, "-FRR for FIFO Round Rubin test\n");
                printf(1, "-GRT for Fair Share test \n");
                printf(1, "-3Q for the Multi-level Queue test\n");
                printf(1, "-ALL to run all tests in the same order as stated above\n");
            }
                
            
        }
    }
    else // set defult to QQQ sanity test
    {
        QQQSanity();
    }
    
    exit(); // father of all in all cases will exit here 
    return 0;
}

// implementation of normal round robin sanity test

void RRSanity()
{
    int numberOfChildern = 10;
    int numberOfLoops = 1000;
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
        // printf(1, "father waiting for ith time: %d", i);
        pid = wait_and_performance(&wtime, &rtime); // pass in the address of ints to get them filled : /
        child_ids[i] = pid;
        wait_times[i] = wtime;
        run_times[i] = rtime;
        // printf(1, "FATHER REPORTING: child with id: %d, is done\n", pid);
    }

    // report:
    for (int i = 0; i < numberOfChildern; i++)
    {
        printf(1, "child report\t id: %d, run time: %d, wait time: %d\n", child_ids[i], run_times[i], wait_times[i]);
    }
};

void FRRSanity()
{
    int numberOfChildern = 10;
    int numberOfLoops = 1000;
    int pid;

    int dummy = 100; // usd to consume some cpu time

    // arrays to hold the reports
    int child_ids[numberOfChildern];
    int wait_times[numberOfChildern];
    int run_times[numberOfChildern];

    // integers to pass in and get reports
    int wtime, rtime;

    printf(1, "FRR sanity test is running\n");

    for(int i = 0; i < numberOfChildern; i ++)
    {
        pid = fork(); // create a child

        if(pid > 0)
        {
            // father process should continue and make more children
            continue;
        }
        else if(pid == 0) // children
        {
            for(int count = 0; count < numberOfLoops; count++) // some computation time
            {
                sleep(5);
                dummy ++;
            }
            exit();
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
        pid = wait_and_performance(&wtime, &rtime); // pass in the address of ints to get them filled : /
        child_ids[i] = pid;
        wait_times[i] = wtime;
        run_times[i] = rtime;
    }

    // report:
    for (int i = 0; i < numberOfChildern; i++)
    {
        printf(1, "child report\t id: %d, run time: %d, wait time: %d\n", child_ids[i], run_times[i], wait_times[i]);
    }

}

void GRTSanity()
{
    int numberOfLoops = 5;
    int sleepTime = 1000; // mesured in CPU ticks
    int pid;

    printf(1, "GRT sanity test is running\n");

    printf(1, "father pid is: <%d>\n", getpid()); // get pid of this process ( the father )

    pid = fork(); // create a child
    if(pid > 0) // parent should sleep first then start its loop
        sleep(sleepTime);
    for(int i = 0; i < numberOfLoops; i++ ) // parent and child should execute the same code 
    {
        printf(1, "Process <%d> is printing i: %d\n", getpid(), (i + 1));
        sleep(sleepTime);
    }
    if(pid > 0)
    {
        // father needs to eventually wait for its child
        printf(1, "father is done now waiting for child\n");
        pid = wait();
        printf(1, "child <%d> is done\n", pid);
    }
    else
        exit(); // child should exit 
}

//todo: comp it, needs reportings i think
void QQQSanity()
{
    int numberOfChildern = 30;
    int numberOfLoops = 10;
    int pid;

    int wtime, rtime;

    //array to gather info for report
    int all_wait_time[numberOfChildern];
    int all_run_time[numberOfChildern];
    int all_child_ids[numberOfChildern];

    int father_pid = getpid();

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
        pid = wait_and_performance(&wtime, &rtime); // pass in the address of ints to get them filled : /
        all_child_ids[i] = pid;
        all_run_time[i] = rtime;
        all_wait_time[i] = wtime;
    }
    // generate the report
    
    // average run and wait time for all children
    int sum_run = 0;
    int sum_wait = 0;
    for(int i =0; i < numberOfChildern; i++)
    {
        sum_run = sum_run + all_run_time[i];
        sum_wait = sum_wait + all_wait_time[i];
    }
    printf(1,"average run time for all children: %d", sum_run / numberOfChildern);
    printf(1,"average wait time for all children: %d", sum_wait / numberOfChildern);
    // average wait and run time for each queue
    
    char* strings[3] = {"RR", "FRR", "GRT"};

    for(int j = 0; j < 3; j++)
    {
        sum_run = 0;
        sum_wait = 0;
        for(int i = 0; i < numberOfChildern; i ++)
        {
            int child_id = all_child_ids[i];
            if(j = (child_id - father_pid - 1) % 3)
            {
                sum_run = sum_run + all_run_time[i];
                sum_wait = sum_wait + all_wait_time[i];
            }
        }
        printf(1, "average run time for %s : %d", *strings[2 - j], sum_run / 10);
        printf(1, "average wait time for %s : %d", *strings[2 - j], sum_wait / 10);
    }
    // run and wait time for all children
    for(int i = 0; i < numberOfChildern; i++)
    {
        printf(1, "child report \t id: %d, run: %d, wait: %d", all_child_ids[i], all_run_time[i], all_wait_time[i]);
    }
}