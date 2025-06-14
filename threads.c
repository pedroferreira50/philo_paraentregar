/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:38:55 by pviegas-          #+#    #+#             */
/*   Updated: 2025/06/14 11:42:09 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_continue_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->state_mutex);
	if (philo->sim->simulation_ended == 0
		&& (philo->sim->required_meals == -1
			|| philo->meals_eaten < philo->sim->required_meals))
	{
		pthread_mutex_unlock(&philo->sim->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->state_mutex);
	return (0);
}

void	pre_routine(t_philo *philo)
{
	if (philo->sim->philo_count % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_sleep(20, philo);
	}
	else
	{
		if (philo->id % 2 == 1)
			philo_think(philo);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pre_routine(philo);
	while (should_continue_eating(philo))
	{
		if (is_simulation_ended(philo))
			return (NULL);
		if (!philo_take_forks(philo))
			return (NULL);
		if (is_simulation_ended(philo))
		{
			philo_drop_forks(philo);
			return (NULL);
		}
		philo_eat(philo);
		if (is_simulation_ended(philo))
			return (NULL);
		philo_sleep(philo);
		if (is_simulation_ended(philo))
			return (NULL);
		philo_think(philo);
	}
	return (NULL);
}

void	start_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->philo_count)
	{
		pthread_create(&sim->philos[i].thread_id, NULL,
			&philo_routine, (void *)&sim->philos[i]);
		i++;
	}
}

void	wait_for_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->philo_count)
	{
		pthread_join(sim->philos[i].thread_id, NULL);
		i++;
	}
}
