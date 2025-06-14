/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:43:42 by pviegas-          #+#    #+#             */
/*   Updated: 2025/06/13 11:49:33 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// System includes
# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_simulation	t_simulation;

/// @brief Individual philosopher structure representing one dining philosopher
/// @param id Unique philosopher identifier (1-based numbering)
/// @param meals_eaten Current count of completed meals
/// @param death_deadline Absolute simulation time when philosopher will die
/// @param thread_id POSIX thread identifier for this philosopher's thread
/// @param left_fork Pointer to mutex protecting the left fork resource
/// @param right_fork Pointer to mutex protecting the right fork resource
/// @param sim Pointer to parent simulation structure for shared state access
typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	int					death_deadline;
	int					last_meal;
	pthread_t			thread_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_simulation		*sim;
}	t_philo;

/// @brief Complete simulation state containing all philosophers and resources
/// @param philo_count Total number of philosophers in the simulation
/// @param time_to_die Maximum milliseconds between meals before death
/// @param time_to_eat Duration in milliseconds required for eating action
/// @param time_to_sleep Duration in milliseconds required for sleeping action
/// @param required_meals Target meals per philosopher (-1 for unlimited)
/// @param start_time Simulation start timestamp in milliseconds
/// @param simulation_ended Flag indicating if simulation has terminated
/// @param forks Array of fork mutexes (one per philosopher)
/// @param state_mutex Master mutex protecting shared simulation state
/// @param philos Array of all philosopher structures in the simulation
typedef struct s_simulation
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					required_meals;
	int					start_time;
	int					simulation_ended;
	pthread_mutex_t		*forks;
	pthread_mutex_t		state_mutex;
	t_philo				*philos;
}	t_simulation;

// Initialization functions
int		setup_simulation(t_simulation *sim, char **argv);
int		init_philosophers(t_simulation *sim);
int		init_mutexes(t_simulation *sim);
void	cleanup_simulation(t_simulation *sim);

// Philosopher actions
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
int		philo_take_forks(t_philo *philo);
void	philo_drop_forks(t_philo *philo);

// Thread management
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);
void	start_simulation(t_simulation *sim);
void	wait_for_threads(t_simulation *sim);

// Status checking
int		is_simulation_ended(t_philo *philo);
int		should_continue_eating(t_philo *philo);
int		all_meals_completed(t_simulation *sim);
int		check_all_philosophers(t_simulation *sim);

// Utility functions
void	print_action(char *action, t_philo *philo);
void	precise_sleep(int duration, t_philo *philo);
void	handle_single_philo(char *time_to_die);
int		get_current_time(void);
int		validate_arguments(int argc, char **argv);
long	parse_number(const char *str);

#endif