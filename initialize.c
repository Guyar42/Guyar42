/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guyar <guyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 23:04:26 by guyar             #+#    #+#             */
/*   Updated: 2022/07/02 02:01:30 by guyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_initialize(t_struc *m_struc, char **argv, int code)
{
	int i;
	
	if (code == 6)
		m_struc->finished = m_struc->nb_p;
	m_struc->dead = 0;
	if (ft_malloc_struc(m_struc, code) == 1)
		return (1);
	if (ft_init_mutex(m_struc, code) == 1)
		return (1);
	i = -1;
	ft_init_struc(m_struc, argv, i, code);
	return (0);
}

int	ft_malloc_struc(t_struc *m_struc, int code)
{
	m_struc->p_struc = malloc(sizeof(t_philo) * (m_struc->nb_p));
	m_struc->fork = malloc(sizeof(pthread_mutex_t) * (m_struc->nb_p));
	m_struc->mdead = malloc(sizeof(pthread_mutex_t) * 1 ); 
	if (code == 6)
	{
		m_struc->mx_finished = malloc(sizeof(pthread_mutex_t) * 1);
		if (m_struc->mx_finished == NULL)												// free avant si null;
			return (1); 
	}
	if (m_struc->p_struc == NULL || m_struc->fork == NULL || m_struc->mdead == NULL)	// free l'un et l'autre
		return (1);
	return (0);
}

int	ft_init_mutex(t_struc *m_struc, int code)
{
	int i;

	i = -1;
	(void) code;
	while (++i < m_struc->nb_p)
	{
		if (pthread_mutex_init(&m_struc->fork[i], NULL) != 0)
				//	&& pthread_mutex_init()) // to destroy;
			return (1);
	}
	if (pthread_mutex_init(m_struc->mdead, NULL) != 0)
		return (1);
	if (pthread_mutex_init(m_struc->mx_finished, NULL) != 0)
		return (1);
	if (pthread_mutex_init(m_struc->mdead, NULL) != 0)
		return (1);
	if (pthread_mutex_init(m_struc->mx_finished, NULL) != 0)
		return (1);
	return (0);
}

void ft_init_struc(t_struc *m_struc, char **argv, int i, int code)
{
	(void) code;
	while (++i < m_struc->nb_p)
	{
		m_struc->p_struc[i].mx_p_dead = m_struc->mdead;
		m_struc->p_struc[i].eaten = 0;
		m_struc->p_struc[i].time_to_die = ft_atoi(argv[2]);
		m_struc->p_struc[i].time_to_eat = ft_atoi(argv[3]);
		m_struc->p_struc[i].time_to_sleep = ft_atoi(argv[4]);
		if (code == 6)
		{
			m_struc->p_struc[i].number_of_eat = ft_atoi(argv[5]);
			m_struc->p_struc[i].p_mx_finished = m_struc->mx_finished;
			m_struc->p_struc[i].p_finished = &m_struc->finished;
		}
		m_struc->p_struc[i].number_p = i + 1;
		m_struc->p_struc[i].dead = &m_struc->dead;
		m_struc->p_struc[i].mx_p_dead = m_struc->mdead;
		m_struc->p_struc[i].fork_r = &m_struc->fork[i];
		m_struc->p_struc[i].start_time = &m_struc->start_time;
		m_struc->start_time = ft_gettime();
		m_struc->p_struc[i].last_meal = m_struc->start_time;
		if (i == (m_struc->nb_p) - 1)
			m_struc->p_struc[i].fork_l = &m_struc->fork[0];
		else if (i != (m_struc->nb_p) - 1)
			m_struc->p_struc[i].fork_l = &m_struc->fork[i + 1];
 	}
}