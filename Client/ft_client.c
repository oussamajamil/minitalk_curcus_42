/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamil <ojamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:59:14 by ojamil            #+#    #+#             */
/*   Updated: 2021/12/24 17:59:18 by ojamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minitalk.h"

int	ft_controller_pid(int argc, char *argv[])
{
	int	i;

	if (argc == 3)
	{
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

void	ft_send_caractere(int pid, unsigned char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(120);
	}
}

void	ft_accepte_message(int signal, siginfo_t *info, void *uc)
{
	(void)*uc;
	(void)*info;
	if (signal == SIGUSR1)
	{
		ft_putstr_fd("\033[0;32m\e[1mMessage bien recu\n", 1);
		exit (0);
	}
	else
		return ;
}

int	main(int argc, char *argv[])
{
	int					pid;
	char				*text;
	size_t				i;
	struct sigaction	sigact;

	if (ft_controller_pid(argc, argv) == 0)
	{
		sigact.sa_sigaction = ft_accepte_message;
		sigact.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &sigact, NULL);
		sigaction(SIGUSR2, &sigact, NULL);
		i = -1;
		pid = ft_atoi(argv[1]);
		text = argv[2];
		while (++i <= ft_strlen(text))
		{
			ft_send_caractere(pid, text[i]);
			usleep(200);
		}
		while (1)
			usleep(5000);
	}
	return (0);
}
