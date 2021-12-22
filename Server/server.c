/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamil <ojamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:59:30 by ojamil            #+#    #+#             */
/*   Updated: 2021/12/22 19:03:11 by ojamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minitalk.h"
#include <stdio.h>
#include <signal.h>

int ft_power(int a,int p)
{
    if (p == 0)
        return (1);
    if (p == 1)
        return (a);
    return(a * ft_power(a,p-1));
}

void ft_accepte_signale(int signal,siginfo_t *info,void *uc)
{
	(void) *uc;
	(void) *info;
	static int cp = 0 ;
	static int cp_signal1 = 0;
	static char caractere;

	if (signal == SIGUSR2)
	{
		caractere += ft_power(2,cp);
		cp++;
		cp_signal1 = 0;
	}
	if (signal == SIGUSR1)
	{
		cp++;
		cp_signal1++;
	}
	if(cp == 8 && cp_signal1 < 8)
	{
		ft_putchar_fd(caractere, 1);
		cp = 0;
		caractere = 0;
		cp_signal1 = 0;
	}
	else if (cp_signal1 == 8)
	{
		kill(info->si_pid,SIGUSR1);
		ft_putstr_fd("hello\n",6);
	}
}
int main ()
{ 
	struct sigaction action;
	
	int i;

	i = 0;
	ft_putstr_fd("Server PID:",1);
	ft_putnbr_fd(getpid(),1);
	ft_putchar_fd('\n',1);
	action.sa_sigaction = ft_accepte_signale;
	action.sa_flags = 0;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1,&action,NULL);
	sigaction(SIGUSR2,&action,NULL);
	while (1)
		usleep(5000);
	return (0);
}