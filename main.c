/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:39:05 by pviegas-          #+#    #+#             */
/*   Updated: 2025/06/13 11:52:57 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	run_simulation(t_simulation *sim)
{
	start_simulation(sim);
	monitor_routine(sim);
	wait_for_threads(sim);
	cleanup_simulation(sim);
	return (0);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (!validate_arguments(argc, argv))
		return (1);
	if (parse_number(argv[1]) == 1)
	{
		handle_single_philo(argv[2]);
		return (0);
	}
	if (setup_simulation(&sim, argv))
		return (run_simulation(&sim));
	return (1);
}
