/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:36:55 by pviegas-          #+#    #+#             */
/*   Updated: 2025/06/13 11:53:02 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_first_fork(t_philo *philo)
{
	if (philo->id == philo->sim->philo_count)
		pthread_mutex_lock(philo->right_fork);
	else if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (is_simulation_ended(philo))
	{
		if (philo->id == philo->sim->philo_count || philo->id % 2 == 0)
			pthread_mutex_unlock(philo->right_fork);
		else
			pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	print_action("has taken a fork", philo);
	return (1);
}

static int	take_second_fork(t_philo *philo)
{
	if (philo->id == philo->sim->philo_count)
	{
		pthread_mutex_lock(philo->left_fork);
		if (is_simulation_ended(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		print_action("has taken a fork", philo);
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (is_simulation_ended(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		print_action("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (is_simulation_ended(philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		print_action("has taken a fork", philo);
	}
	return (1);
}

int	philo_take_forks(t_philo *philo)
{
	if (!take_first_fork(philo))
		return (0);
	if (!take_second_fork(philo))
		return (0);
	return (1);
}

void	philo_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
