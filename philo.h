/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guyar <guyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:22:30 by guyar             #+#    #+#             */
/*   Updated: 2022/07/02 00:05:40 by guyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>


typedef struct s_struc	t_struc;
typedef struct s_philo	t_philo;


struct s_struc {

	int	nb_p;
	pthread_t	*id_thread;
	t_philo		*p_struc;
	pthread_mutex_t	*fork;
	pthread_mutex_t *mdead;
	pthread_mutex_t *mx_finished;
	int dead;
	int finished;
	long long start_time;
};

struct  s_philo {
	pthread_t	thread;
	long long time;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_eat;
	long long *start_time;
	long long last_meal;
	int	number_p;
	int fork;
	pthread_mutex_t *fork_l;
	pthread_mutex_t *fork_r;
	pthread_mutex_t *mx_p_dead; // renvoi mdead
	pthread_mutex_t *p_mx_finished;
	int *p_finished;
	int eaten;
	int *dead;
	int code;
};

int			ft_atoi(const char *str);
void		*ft_action(void *p_struc);
void		ft_start_thread(t_struc *m_struc);
long long	ft_gettime();
void 		ft_usleep(int time_to_wait);
int			ft_initialize(t_struc *m_struc, char **argv, int code);
int			ft_malloc_struc(t_struc *m_struc, int code);
int 		ft_init_mutex(t_struc *m_struc, int code);
void 		ft_init_struc(t_struc *m_struc, char **argv, int i, int code);
void 		ft_action_code_6(t_philo *p_struc);
void 		ft_eat(t_philo *p_struc);
void ft_sleep(t_philo *p_struc);
void ft_think(t_philo *p_struc);