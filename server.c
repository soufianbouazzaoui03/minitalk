#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void    reset(int pid, unsigned char *c, int *bits)
{
    if(*c == '\n')
    {
        usleep(100);
        kill(pid, SIGUSR1);
    }
    write(1, c, 1);
    *bits = 7;
    *c = 0;
}

void    handler(int sig, siginfo_t *info, void *context)
{
    static unsigned char c;
    static int bits = 7;
    static int   pid;

    if(pid != info->si_pid)
    {
        bits = 7;
        c = 0;
        pid = info->si_pid;
    }
    if (sig == SIGUSR1)
        c = c << 1;
    else if (sig == SIGUSR2)
        c = (c << 1) | 1;
    bits--;
    if (bits < 0)
    {
        if(c == '\n')
        {
            usleep(100);
            kill(info->si_pid, SIGUSR1);
        }
        write(1, &c, 1);
        bits = 7;
        c = 0;
    }
}

int main()
{
    printf("Server PID: %d\n", getpid());
    struct sigaction	sa;
	sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (1)
    {
        pause();
    }
    return (0);
}