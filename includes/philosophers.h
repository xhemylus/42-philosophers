/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollen <abollen@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:34:29 by abollen           #+#    #+#             */
/*   Updated: 2022/03/01 20:54:18 by abollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_pdata	t_pdata;

typedef struct s_time
{
	struct timeval	lau;
	struct timeval	cur;
}	t_time;

typedef struct s_philosophers
{
	int				id;
	int				meal_count;
	u_int64_t		timeofmeal;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t datalock;
	t_pdata			*sys;
}				t_philosophers;

typedef struct s_pdata
{
	pthread_t		*philo;
	pthread_t		bigbrother;
	pthread_mutex_t	*forks;
	u_int64_t		cur;
	u_int64_t		tom;
	int				isfull;
	int				solofull;
	int				run;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				philo_count;
	int				total_meal;
	pthread_mutex_t	mic;
	pthread_mutex_t simlock;
	t_time			time;
	t_philosophers	*ph;
}				t_pdata;

/* --- prototypes --- */

/* -- action.c -- */
void		philosleep(int id, t_philosophers *ph);
void		philofork(int id, t_philosophers *ph);
void		philoeat(int id, t_philosophers *ph);
void		philothink(int id, t_philosophers *ph);
void		philodie(int id, t_pdata *pdata);

/* -- destroy.c -- */
void		mallocdestroy(t_pdata *pdata);
int			threaddestroy(t_pdata *pdata);

/* -- init.c -- */
int			mallocinit(t_pdata *pdata);
int			threadinit(t_pdata *pdata);

/* -- parsing.c -- */
int			posatoi(char *str);
int			ft_isdigit(char *str);
int			check_int(int argc, char **argv);
int			parsing(int argc, char **argv, t_pdata *pdata);

/* -- protect.c -- */
int			protmalloc(int code, t_pdata *pdata);
int			protthread(int index, t_pdata *pdata);

/* -- threads.c -- */
void		*philo(void *pdata);
void		*bigbrother(void *data);

/* -- utils.c --*/
u_int64_t	ms_time(t_pdata *pdata);
void		eat(int id, t_philosophers *ph);
int			fterr(char *str);
void		milisleep(u_int64_t time, t_pdata *pdata);

#endif