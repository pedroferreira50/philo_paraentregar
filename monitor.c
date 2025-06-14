/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:39:01 by pviegas-          #+#    #+#             */
/*   Updated: 2025/06/13 19:21:15 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philosopher_death(t_philo *philo)
{
	int	current_time;
	int	time_since_last_meal;
	int	is_dead;

	current_time = get_current_time();
	time_since_last_meal = current_time - philo->last_meal;
	is_dead = (time_since_last_meal >= philo->sim->time_to_die);
	if (is_dead)
	{
		philo->sim->simulation_ended = 1;
		printf("%d %d died",
			current_time - philo->sim->start_time, philo->id);
	}
	return (is_dead);
}

int	check_all_philosophers(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->philo_count)
	{
		if (check_philosopher_death(&sim->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

int	all_meals_completed(t_simulation *sim)
{
	int	i;

	if (sim->required_meals == -1)
		return (0);
	i = 0;
	while (i < sim->philo_count)
	{
		if (sim->philos[i].meals_eaten < sim->required_meals)
			return (0);
		i++;
	}
	sim->simulation_ended = 1;
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;
	int				should_end;

	sim = (t_simulation *)arg;
	while (1)
	{
		pthread_mutex_lock(&sim->state_mutex);
		should_end = check_all_philosophers(sim) || all_meals_completed(sim);
		pthread_mutex_unlock(&sim->state_mutex);
		if (should_end)
			return (NULL);
		usleep(10);
	}
	return (NULL);
}
