#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void    handler(int sig, siginfo_t *info, void *context)
{
    static unsigned char c;
    static int bits;
    static int   pid;

    bits = 7;
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
        sleep(1);
    return (0);
}