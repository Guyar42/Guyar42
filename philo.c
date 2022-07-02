/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guyar <guyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:21:52 by guyar             #+#    #+#             */
/*   Updated: 2022/07/02 02:28:52 by guyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void ft_start_thread(t_struc *m_struc)
{
	int i;
	
	i = -1;
	while (++i < m_struc->nb_p)
		pthread_create(&m_struc->p_struc[i].thread, NULL, ft_action, &m_struc->p_struc[i]); // essayer avec id_thread
}

int ft_parsing(int argc, char **argv, t_struc *main_struc)
{
	dprintf(2, "argc = %d\n", argc);
	if ((argc < 5)
		|| (argc > 6)
		|| ft_atoi(argv[1]) == 0
		|| (ft_atoi(argv[2]) == 0)
		|| (ft_atoi(argv[3]) == 0)
		|| (ft_atoi(argv[4]) == 0))
	{
		return (1);
	}
	else
	{
		 if (argv[5])
		 {
		 	if (ft_atoi(argv[5]) == 0)
		 		return (1);
		 }
		main_struc->nb_p = ft_atoi(argv[1]);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_struc main_struc;
	int i;

	i = 0;
	if (ft_parsing(argc, argv, &main_struc) == 1)
	{
		write(1, "Arg error\n", 10);
		return (1);
	}
	if (ft_initialize(&main_struc, argv, argc) != 0)
	{
		write(1, "Initialisation error\n", 21);
		return (1);
	}
	ft_start_thread(&main_struc);	
	pthread_mutex_lock(main_struc.mdead);
	pthread_mutex_lock(main_struc.mx_finished);
	while (main_struc.dead == 0 && main_struc.finished != 0)  
	{
		pthread_mutex_unlock(main_struc.mx_finished);
		pthread_mutex_unlock(main_struc.mdead);
		i = 0;
		pthread_mutex_lock(main_struc.mdead);
		while ((i < main_struc.nb_p) && (main_struc.dead == 0) && (main_struc.finished != 0))
		{	
			pthread_mutex_unlock(main_struc.mx_finished);
			pthread_mutex_unlock(main_struc.mdead);
			if ((ft_gettime() - main_struc.p_struc[i].last_meal) > main_struc.p_struc[i].time_to_die)
			{	
				pthread_mutex_lock(main_struc.mdead);
				main_struc.dead = 1;
				pthread_mutex_lock(main_struc.mx_finished);
				if (main_struc.finished != 0)
				{	 
					pthread_mutex_unlock(main_struc.mx_finished);
					printf("%lld %d is dead\n", (ft_gettime() - *main_struc.p_struc[i].start_time), main_struc.p_struc[i].number_p);
				}
				pthread_mutex_unlock(main_struc.mdead);
				pthread_mutex_unlock(main_struc.mx_finished);
			}
			i++;
			pthread_mutex_lock(main_struc.mx_finished);
			pthread_mutex_lock(main_struc.mdead);
		}
		pthread_mutex_unlock(main_struc.mdead);
		pthread_mutex_unlock(main_struc.mx_finished);
		pthread_mutex_lock(main_struc.mx_finished);
		pthread_mutex_lock(main_struc.mdead);
	}
	pthread_mutex_unlock(main_struc.mdead);
	pthread_mutex_unlock(main_struc.mx_finished);
	i = -1;
	while (++i <= main_struc.nb_p)
	{
		pthread_join(main_struc.p_struc[i].thread, NULL); 
	}
	return(0);
}

// last meal a mutex;
// verifier si un philo est mort;
