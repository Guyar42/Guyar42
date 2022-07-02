/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guyar <guyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:42:25 by guyar             #+#    #+#             */
/*   Updated: 2022/07/02 03:00:10 by guyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void ft_eat(t_philo *p_struc)
{
	pthread_mutex_lock(p_struc->fork_r);
	pthread_mutex_lock(p_struc->fork_l);
	pthread_mutex_lock(p_struc->mx_p_dead);
	if (*p_struc->dead == 0)
	{
		printf("%lld %d has taken a fork \n", (ft_gettime() - *p_struc->start_time), p_struc->number_p);
		printf("%lld %d is eating\n", (ft_gettime() - *p_struc->start_time), p_struc->number_p);
		p_struc->last_meal = ft_gettime();
		ft_usleep(p_struc->time_to_eat);
		pthread_mutex_unlock(p_struc->fork_r);
		pthread_mutex_unlock(p_struc->fork_l);
	}
	pthread_mutex_unlock(p_struc->fork_r);
	pthread_mutex_unlock(p_struc->fork_l);
	pthread_mutex_unlock(p_struc->mx_p_dead);
	p_struc->eaten += 1;
}

void ft_sleep(t_philo *p_struc)
{
	pthread_mutex_lock(p_struc->mx_p_dead);
	if (*p_struc->dead == 0)
	{
		printf("%lld %d is sleeping\n", (ft_gettime() - *p_struc->start_time), p_struc->number_p);
		pthread_mutex_unlock(p_struc->mx_p_dead);
		ft_usleep(p_struc->time_to_sleep);
	}
	pthread_mutex_unlock(p_struc->mx_p_dead);
}

void ft_think(t_philo *p_struc)
{
	pthread_mutex_lock(p_struc->mx_p_dead);
	if (*p_struc->dead == 0)
	{
		pthread_mutex_unlock(p_struc->mx_p_dead);
		printf("%lld %d is thinking\n", (ft_gettime() - *p_struc->start_time), p_struc->number_p);
	}
	pthread_mutex_unlock(p_struc->mx_p_dead);
}

void *ft_action(void *p)
{
	t_philo *p_struc;
	p_struc = p;
	if	(p_struc->number_p % 2 == 0)
		usleep(100);
	pthread_mutex_lock(p_struc->mx_p_dead);
	while ((p_struc->eaten != p_struc->number_of_eat) && (*p_struc->dead) == 0)
	{
		pthread_mutex_unlock(p_struc->mx_p_dead);
		pthread_mutex_lock(p_struc->mx_p_dead);
		if ((*p_struc->dead) == 0)
		{
			pthread_mutex_unlock(p_struc->mx_p_dead);
			ft_eat(p_struc);
		}
		pthread_mutex_unlock(p_struc->mx_p_dead);
 		if (p_struc->eaten == p_struc->number_of_eat)
		{
			pthread_mutex_lock(p_struc->p_mx_finished);
			*p_struc->p_finished -= 1;
			pthread_mutex_unlock(p_struc->p_mx_finished);
		}
		pthread_mutex_unlock(p_struc->mx_p_dead);
		pthread_mutex_lock(p_struc->mx_p_dead);
		if ((*p_struc->dead) == 0)
		{
			pthread_mutex_unlock(p_struc->mx_p_dead);
			ft_sleep(p_struc);
		}
		pthread_mutex_unlock(p_struc->mx_p_dead);
		pthread_mutex_lock(p_struc->mx_p_dead);
		if ((*p_struc->dead) == 0)
		{
			pthread_mutex_unlock(p_struc->mx_p_dead);
			ft_think(p_struc);
		}
		pthread_mutex_unlock(p_struc->mx_p_dead);	
		pthread_mutex_lock(p_struc->mx_p_dead);
	}
	pthread_mutex_unlock(p_struc->mx_p_dead);
	return (NULL);
}

void ft_usleep(int time_to_wait)
{
	long long now;
	long long expected;
	
	now = ft_gettime();
	expected = now + time_to_wait;
	
	while (ft_gettime() < expected)
	{
		usleep(100);
	}
	return;
}