/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamil <ojamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:59:30 by ojamil            #+#    #+#             */
/*   Updated: 2021/12/22 15:18:28 by ojamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minitalk.h"
#include <stdio.h>

int ft_power(int a,int p)
{
    if (p == 0)
        return (1);
    if (p == 1)
        return (a);
    return(a * ft_power(a,p-1));
}

void ft_accepte_signale(int signal)
{
	static int cp = 0 ;
	static char caractere;

	if (signal == SIGUSR2)
	{
		caractere += ft_power(2,cp);
		cp++;
	}
	if (signal == SIGUSR1)
		cp++;
	if(cp == 8)
	{
		ft_putchar_fd(caractere, 1);
		cp = 0;
		caractere = 0;
	}
}
int main ()
{ 
	ft_putstr_fd("Server PID:",1);
	ft_putnbr_fd(getpid(),1);
	ft_putchar_fd('\n',1);
	signal(SIGUSR1,ft_accepte_signale);
	signal(SIGUSR2,ft_accepte_signale);
	while (1)
		usleep(5000);
	return (0);
}