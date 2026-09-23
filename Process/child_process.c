#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Child started\n");

    sleep(3);

    printf("Child returning 10\n");

    return 10;
}
