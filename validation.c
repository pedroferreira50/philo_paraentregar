/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:38:45 by pviegas-          #+#    #+#             */
/*   Updated: 2025/06/14 11:42:41 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	parse_number(const char *str)
{
	long	result;

	result = 0;
	if (str == NULL)
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str++ - '0');
		if (result > 2147483647)
			return (0);
	}
	if (*str != '\0')
		return (0);
	return (result);
}

static int	check_argument_validity(long value)
{
	if (value <= 0 || value > 2147483647)
		return (0);
	return (1);
}

int	validate_arguments(int argc, char **argv)
{
	long	value;
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid arguments\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		value = parse_number(argv[i]);
		if (!check_argument_validity(value))
		{
			printf("Error: Invalid input\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	handle_single_philo(char *time_to_die)
{
	printf("0 1 has taken a fork\n");
	usleep((int)parse_number(time_to_die) * 1000);
	printf("%s 1 \033[31mdied\n\033[0m", time_to_die);
}
