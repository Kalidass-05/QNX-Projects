#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>

typedef struct
{
    char msg[100];
} message_t;

int main()
{
    name_attach_t *attach;
    message_t msg;
    int rcvid;

    attach = name_attach(NULL, "myserver", 0);

    if (attach == NULL)
    {
        perror("name_attach");
        return 1;
    }

    printf("Server started\n");

    while (1)
    {
        rcvid = MsgReceive(
            attach->chid,
            &msg,
            sizeof(msg),
            NULL
        );

        if (rcvid == -1)
        {
            perror("MsgReceive");
            continue;
        }

        printf("Server received: %s\n", msg.msg);

        MsgReply(
            rcvid,
            EOK,
            "Hello Client",
            strlen("Hello Client") + 1
        );
    }

    name_detach(attach);

    return 0;
}
