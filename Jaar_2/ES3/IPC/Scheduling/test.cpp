#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>


int main(void)
{
    static long long    counter = 0;
    static long long    prev_time = 0;
    long long           curr_time;
    
    counter++;
    curr_time = get_time();
    if (curr_time >= prev_time + 1000000LL)
    {
        // each second...
        printf ("%lld%%  %lld\n", get_consumed_cputime(), counter);
        prev_time = curr_time;
        counter = 0;
	}
	return 0;
}
