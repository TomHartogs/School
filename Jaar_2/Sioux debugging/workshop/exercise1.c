#include <stdio.h>
#include <unistd.h>

void do_it()
{
    usleep(100000);
}

int main(void)
{
    int i = 0;

    while (i < 10)
    {
        do_it();
    }

    printf("slept for 1 second (or perhaps a bit longer)\n");

    return 0;
}
