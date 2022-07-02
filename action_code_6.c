/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_code_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guyar <guyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 00:01:13 by guyar             #+#    #+#             */
/*   Updated: 2022/07/02 00:36:06 by guyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// void ft_action_code_6(t_philo *p_struc)
// {
// 	while ((p_struc->eaten != p_struc->number_of_eat) && (*p_struc->dead) == 0)
// 	{
// 		pthread_mutex_unlock(p_struc->mx_p_dead);
// 		pthread_mutex_lock(p_struc->mx_p_dead);
// 		if ((*p_struc->dead) == 0)
// 		{
// 			pthread_mutex_unlock(p_struc->mx_p_dead);
// 			ft_eat(p_struc);
// 		}
// 		pthread_mutex_unlock(p_struc->mx_p_dead);
// 		pthread_mutex_lock(p_struc->mx_p_dead);
// 		if ((*p_struc->dead) == 0)
// 		{
// 			pthread_mutex_unlock(p_struc->mx_p_dead);
// 			ft_sleep(p_struc);
// 		}
// 		pthread_mutex_unlock(p_struc->mx_p_dead);
// 		pthread_mutex_lock(p_struc->mx_p_dead);
// 		if ((*p_struc->dead) == 0)
// 		{
// 			pthread_mutex_unlock(p_struc->mx_p_dead);
// 			ft_think(p_struc);
// 		}
// 		pthread_mutex_unlock(p_struc->mx_p_dead);	
// 		if (p_struc->eaten == p_struc->number_of_eat)
// 		{
// 			pthread_mutex_lock(p_struc->p_mx_finished);
// 			*p_struc->p_finished -= 1; 
// 			pthread_mutex_unlock(p_struc->p_mx_finished);
// 		}
// 		pthread_mutex_lock(p_struc->mx_p_dead);
// 		}
// 	pthread_mutex_unlock(p_struc->mx_p_dead);
// }