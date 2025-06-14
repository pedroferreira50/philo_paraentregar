/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:39:16 by pviegas-          #+#    #+#             */
/*   Updated: 2025/06/13 16:20:36 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	print_action("is eating", philo);
	pthread_mutex_lock(&philo->sim->state_mutex);
	philo->last_meal = get_current_time();
	philo->death_deadline = (get_current_time() - philo->sim->start_time)
		+ philo->sim->time_to_die;
	if (philo->sim->required_meals != -1)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->sim->state_mutex);
	precise_sleep(philo->sim->time_to_eat, philo);
	philo_drop_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->state_mutex);
	if (all_meals_completed(philo->sim))
	{
		pthread_mutex_unlock(&philo->sim->state_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->sim->state_mutex);
	print_action("is sleeping", philo);
	precise_sleep(philo->sim->time_to_sleep, philo);
}

/* void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->state_mutex);
	if (all_meals_completed(philo->sim))
	{
		pthread_mutex_unlock(&philo->sim->state_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->sim->state_mutex);
	print_action("is thinking", philo);
} */

void	philo_think(t_philo *philo)
{
	int	think_time;
	int	eat_time;
	int	sleep_time;

	pthread_mutex_lock(&philo->sim->state_mutex);
	if (all_meals_completed(philo->sim))
	{
		pthread_mutex_unlock(&philo->sim->state_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->sim->state_mutex);
	print_action("is thinking", philo);
	eat_time = philo->sim->time_to_eat;
	sleep_time = philo->sim->time_to_sleep;
	think_time = eat_time * 2 - sleep_time;
	if (think_time < 0)
		think_time = 0;
	if (philo->sim->philo_count % 2 == 1)
		precise_sleep(think_time * 0.42, philo);
}
