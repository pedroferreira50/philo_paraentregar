/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:38:50 by pviegas-          #+#    #+#             */
/*   Updated: 2025/06/13 17:23:41 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	print_action(char *action, t_philo *philo)
{
	char	*color;

	pthread_mutex_lock(&philo->sim->state_mutex);
	if (philo->sim->simulation_ended == 0)
	{
		color = "";
		if (ft_strcmp(action, "is thinking") == 0)
			color = "\033[35m";
		else if (ft_strcmp(action, "is eating") == 0)
			color = "\033[32m";
		else if (ft_strcmp(action, "is sleeping") == 0)
			color = "\033[34m";
		else if (ft_strcmp(action, "has taken a fork") == 0)
			color = "\033[33m";
		printf("%d %d %s%s\033[0m\n", get_current_time()
			- philo->sim->start_time, philo->id, color, action);
	}
	pthread_mutex_unlock(&philo->sim->state_mutex);
}

int	get_current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	precise_sleep(int duration, t_philo *philo)
{
	int	start;

	start = get_current_time();
	while ((get_current_time() - start) < duration
		&& is_simulation_ended(philo) == 0)
		usleep(200);
}

int	is_simulation_ended(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->state_mutex);
	if (philo->sim->simulation_ended == 1)
	{
		pthread_mutex_unlock(&philo->sim->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->state_mutex);
	return (0);
}
