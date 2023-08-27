/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialousse <ialousse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:56:07 by ialousse          #+#    #+#             */
/*   Updated: 2023/08/27 22:06:20 by ialousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_init(t_info *data)
{
	int	i;

	data->time_start = timestamp();
	i = -1;
	while (++i < data->nbr_philo)
	{
		data->philo[i].n = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].fork_right = NULL;
		data->philo[i].info = data;
		data->philo[i].m_count = 0;
		pthread_mutex_init(&(data->philo[i].fork_left), NULL);
		if (i == data->nbr_philo -1)
			data->philo[i].fork_right = &data->philo[0].fork_left;
		else
			data->philo[i].fork_right = &data->philo[i + 1].fork_left;
		if (pthread_create(&data->philo[i].thread, NULL, \
				&philo_life, &(data->philo[i])) != 0)
			return (-1);
	}
	i = -1;
	while (++i < data->nbr_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
		retun (0);
	}
}

int	var_init(t_info *data, char **av)
{
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->m_stop, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	pthread_mutex_init(&data->dead, NULL);
	data->stop = 0;
	data->philo = malloc(sizeof(t_philo) * data->nbr_philo);
	if (data->philo == NULL)
		return (2);
	if (ft_check_nbr(av))
	{
		printf("Arguments invalides\n");
		return (1);
	}
	data->philo_eat = 0;
	data->nbr_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nbr_eat = ft_atoi(av[5]);
	if (av[5] && data->nbr_eat == 0)
		return (1);
	return (0);
}
