#include <stdio.h>
#include <unistd.h>

void increase(int *number)
{
    (*number)++;
}

int main(void)
{
    int number = 0;

    increase(number);

    printf("number is now: %d\n", number);

    return 0;
}
