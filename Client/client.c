/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamil <ojamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:25:10 by ojamil            #+#    #+#             */
/*   Updated: 2021/12/22 15:35:57 by ojamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include <signal.h>
#include <stdio.h>
#include "./../minitalk.h"

int ft_Controller_pid(int argc,char *argv[])
{
	if(argc == 3)
	{
		int i ;
		
		i = -1;
		while (argv[1][++i])
		{
			if (ft_isdigit(argv[1][i]) == 0)
				return (-1);
		}
		return (0);
	}
	return(-1);
}

void ft_send_caractere(int pid,unsigned char c)
{
	int i;

	i = -1;
	while (++i < 8)
	{
		if(c & 1)
			kill(pid,SIGUSR2);
		else
			kill(pid,SIGUSR1);
		c = c >> 1;
		usleep(50);
	}
	
}

int main (int argc,char *argv[])
{
	int pid;
	char *text;
	int i;
	
	if (ft_Controller_pid(argc,argv) == 0)
	{
		i = -1;
		pid = ft_atoi(argv[1]);
		text = argv[2];
		while (text[++i])
		{
			ft_send_caractere(pid,text[i]);
			usleep(50);
		}
	}
	return (0);
}