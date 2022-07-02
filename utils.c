/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guyar <guyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:30:06 by guyar             #+#    #+#             */
/*   Updated: 2022/04/18 16:41:24 by guyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int     ft_atoi(const char *str)
{
        long int        i;
        long int        j;
        long int        signe;

        signe = 1;
        i = 0;
        j = 0;
        while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
                i++;
        if (str[i] == '-' || str[i] == '+')
        {
                if (str[i] == '-')
                        signe = -1;
                i++;
        }
        while (str[i] >= '0' && str[i] <= '9')
        {
                j = j * 10 + str[i] - '0';
                if (j > 2147483648 && signe == -1)
                        return (0);
                if (j > 2147483647 && signe == 1)
                        return (-1);
                i++;
        }
        return ((j * signe));
}

long long       ft_gettime()
{
        long long time;
        struct timeval t_val;

        gettimeofday(&t_val, NULL);
        time = (t_val.tv_sec * 1000) + (t_val.tv_usec / 1000);
        return (time);
}

void ft_time_to_die(t_philo *p_struc)
{
        if (p_struc->last_meal - ft_gettime() > p_struc->time_to_die)
        {
                pthread_mutex_lock(p_struc->mx_p_dead);
                *p_struc->dead = 1;
                pthread_mutex_unlock(p_struc->mx_p_dead);
        }
        return ;
}

int ft_check_dead(t_struc *main_struc)
{
        int i;
        
        i = 0;
        while (main_struc->dead != 0 && i < main_struc->nb_p)
        {
                if ((ft_gettime() - main_struc->p_struc[i].last_meal)
                        > main_struc->p_struc[i].time_to_die)
                        main_struc->dead = main_struc->p_struc->number_p;
                i++;
                if (i == main_struc->nb_p)
                        i = 0;
        }
        return (0);
}