#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void    sendchar(char c, int pid)
{
    int n;
    int k = 1;

    n = 7;
    while(n >= 0)
    {
        if(((c >> n) & 1) == 0)
            k = kill(pid, SIGUSR1);
        else if(((c >> n) & 1) == 1)
            k = kill(pid, SIGUSR2);
        if (k < 0)
            exit(EXIT_FAILURE);
        n--;
        usleep(100);
    }
}

void    sendstring(char *s, int pid)
{
    while(*s)
        sendchar(*s++, pid);
}

void    handler(int seg)
{
    if(seg == SIGUSR1)
    printf("Message Sent successfully\n");
}
int main(int argc, char *argv[])
{
    int pid;
    if(argc == 3)
    {
        pid = atoi(argv[1]);
        sendstring(argv[2], pid);
        sendchar('\n', pid);
        signal(SIGUSR1, handler);
        while(1)
            sleep(1);
    }
    else
        printf("WORNG ARGUMENT");
    return (0);
}
