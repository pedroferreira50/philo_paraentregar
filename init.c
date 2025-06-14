/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:39:10 by pviegas-          #+#    #+#             */
/*   Updated: 2025/06/13 11:52:59 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_simulation *sim)
{
	int	i;

	i = -1;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philo_count);
	if (!sim->forks)
		return (0);
	while (++i < sim->philo_count)
		pthread_mutex_init(&sim->forks[i], NULL);
	pthread_mutex_init(&sim->state_mutex, NULL);
	return (1);
}

int	init_philosophers(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->philos = malloc(sizeof(t_philo) * sim->philo_count);
	if (!sim->philos)
		return (0);
	while (i < sim->philo_count)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1) % sim->philo_count];
		sim->philos[i].sim = sim;
		sim->philos[i].death_deadline = sim->time_to_die;
		sim->philos[i].last_meal = sim->start_time;
		sim->philos[i].meals_eaten = 0;
		i++;
	}
	return (1);
}

static void	destroy_mutexes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->philo_count)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->state_mutex);
}

void	cleanup_simulation(t_simulation *sim)
{
	destroy_mutexes(sim);
	free(sim->philos);
	free(sim->forks);
}

int	setup_simulation(t_simulation *sim, char **argv)
{
	sim->philo_count = (int)parse_number(argv[1]);
	sim->time_to_die = (int)parse_number(argv[2]);
	sim->time_to_eat = (int)parse_number(argv[3]);
	sim->time_to_sleep = (int)parse_number(argv[4]);
	if (argv[5])
		sim->required_meals = (int)parse_number(argv[5]);
	else
		sim->required_meals = -1;
	sim->simulation_ended = 0;
	sim->start_time = get_current_time();
	if (init_mutexes(sim) == 0)
		return (0);
	if (init_philosophers(sim) == 0)
		return (0);
	return (1);
}
