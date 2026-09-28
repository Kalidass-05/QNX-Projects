#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/neutrino.h>
#include <sys/dispatch.h>

int main()
{
    int coid;

    char send_msg[] = "Hello Server";
    char receive_msg[100];

    coid = name_open("myserver", 0);

    if (coid == -1)
    {
        perror("name_open");
        return 1;
    }

    printf("Sending message...\n");

    if (MsgSend(
            coid,
            send_msg,
            sizeof(send_msg),
            receive_msg,
            sizeof(receive_msg)) == -1)
    {
        perror("MsgSend");
        return 1;
    }

    printf("Server replied: %s\n", receive_msg);

    name_close(coid);

    return 0;
}
