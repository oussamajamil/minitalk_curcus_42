/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamil <ojamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:25:10 by ojamil            #+#    #+#             */
/*   Updated: 2021/12/22 19:00:25 by ojamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "./../minitalk.h"

int ft_Controller_pid(int argc, char *argv[])
{
	if (argc == 3)
	{
		int i;

		i = -1;
		while (argv[1][++i])
		{
			if (ft_isdigit(argv[1][i]) == 0)
				return (-1);
		}
		return (0);
	}
	return (-1);
}

void ft_send_caractere(int pid, unsigned char c)
{
	int i;

	i = -1;
	while (++i < 8)
	{
		if (c & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(50);
	}
}
void ft_send_message(int pid)
{
	int i;

	i = -1;
	while (++i < 8)
	{
		kill(pid, SIGUSR1);
		usleep(50);
	}
}
// void get_message(int signal)
// {
// 	if (signal == SIGUSR1)
// 	{
// 		write(1,"hello",5);
// 	}
// 	else
// 		eit(0);
// }
void ft_accepte_message(int signal, siginfo_t *info, void *uc)
{
	(void)*uc;
	(void)*info;
	if (signal == SIGUSR1)
	{
		ft_putstr_fd("hello\n", 1);
	}
}

int main(int argc, char *argv[])
{
	int pid;
	char *text;
	int i;
	struct sigaction action;

	if (ft_Controller_pid(argc, argv) == 0)
	{
		i = -1;
		pid = ft_atoi(argv[1]);
		text = argv[2];
		action.sa_sigaction = ft_accepte_message;
		action.sa_flags = 0;
		sigemptyset(&action.sa_mask);
		while (text[++i])
		{
			ft_send_caractere(pid, text[i]);
			usleep(50);
		}
		sigemptyset(&action.sa_mask);
		sigaction(SIGUSR1, &action, NULL);
		sigaction(SIGUSR2, &action, NULL);
		while (1)
			usleep(5000);
	}
	return (0);
}