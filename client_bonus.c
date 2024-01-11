/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:10:49 by soel-bou          #+#    #+#             */
/*   Updated: 2024/01/12 00:32:14 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "./printf/ft_printf.h"

void    sendchar(char c, int pid)
{
    int n;
    int k;

    n = 7;
    while(n >= 0)
    {
        if (((c >> n) & 1) == 0)
            k = kill(pid, SIGUSR1);
        else if (((c >> n) & 1) == 1)
            k = kill(pid, SIGUSR2);
        if (k < 0)
            exit(EXIT_FAILURE);
        n--;
        usleep(1337);
    }
}

void    sendstring(char *s, int pid)
{
    while (*s)
        sendchar(*s++, pid);
}

void    handler(int seg, siginfo_t *info, void *context)
{
    (void)context;
    if (seg == SIGUSR1)
        ft_printf("Message Sent successfully to Server(%d)\n", info->si_pid);
}
int main(int argc, char *argv[])
{
    int pid;
    if (argc == 3)
    {
        struct sigaction	sa;
	    sa.sa_sigaction = handler;
        sa.sa_flags = SA_SIGINFO;
        sigaction(SIGUSR1, &sa, NULL);
        pid = ft_atoi(argv[1]);
        sendstring(argv[2], pid);
        sendchar('\n', pid);
        while (1)
            sleep(1);
    }
    else
        ft_printf("WORNG ARGUMENT");
    return (0);
}
