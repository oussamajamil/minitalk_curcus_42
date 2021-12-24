/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamil <ojamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:59:30 by ojamil            #+#    #+#             */
/*   Updated: 2021/12/24 17:59:25 by ojamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minitalk.h"

int	ft_power(int a, int p)
{
	if (p == 0)
		return (1);
	if (p == 1)
		return (a);
	return (a * ft_power(a, p - 1));
}

void	ft_initialiser_cp(int *cp, int *cp_signal1, char *caractere)
{
	*cp = 0;
	*cp_signal1 = 0;
	*caractere = 0;
}

void	ft_increment_cp(int *cp, int *c, int a)
{
	if (a == 0)
		*c = 0;
	else
		(*c)++;
	(*cp)++;
}

void	ft_accepte_signale(int signal, siginfo_t *info, void *uc)
{
	static int	cp;
	static int	cp_signal1;
	static char	caractere;
	static int	client_pid;

	(void)*uc;
	if (client_pid != info->si_pid && cp != 0)
		ft_initialiser_cp(&cp, &cp_signal1, &caractere);
	if (signal == SIGUSR2)
	{
		caractere += ft_power(2, cp);
		ft_increment_cp(&cp, &cp_signal1, 0);
	}
	if (signal == SIGUSR1)
		ft_increment_cp(&cp, &cp_signal1, 1);
	if (cp == 8 && cp_signal1 < 8)
	{
		ft_putchar_fd(caractere, 1);
		ft_initialiser_cp(&cp, &cp_signal1, &caractere);
	}
	if (cp_signal1 == 8)
		kill(info->si_pid, SIGUSR1);
	client_pid = info->si_pid;
}

int	main(void)
{
	struct sigaction	action;

	ft_putstr_fd("Server PID:", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	action.sa_sigaction = ft_accepte_signale;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		usleep(5000);
	return (0);
}
