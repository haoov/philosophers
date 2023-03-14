#include "philo.h"

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->infos);
	if (philo->dead == true)
	{
		pthread_mutex_lock(&philo->data->mutex[END]);
		if (philo->data->sig != STOP)
			philo->sig = PRINT_DEATH;
		else
			philo->sig = STOP;
		philo->data->sig = STOP;
		pthread_mutex_unlock(&philo->data->mutex[END]);
	}
	pthread_mutex_unlock(&philo->infos);
}

void	check_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[COUNT]);
	if (philo->data->full_count == philo->data->philo_nb)
	{
		pthread_mutex_lock(&philo->data->mutex[END]);
		philo->data->sig = STOP;
		philo->sig = STOP;
		pthread_mutex_unlock(&philo->data->mutex[END]);
	}
	pthread_mutex_unlock(&philo->data->mutex[COUNT]);
}

void	check(t_philo *philo, t_check check)
{
	if (check == SIGSTOP || check == (SIGSTOP | DEATH))
	{
		pthread_mutex_lock(&philo->data->mutex[END]);
		if (philo->data->sig == STOP)
			philo->sig = STOP;
		pthread_mutex_unlock(&philo->data->mutex[END]);
	}
	if (check == DEATH || check == (DEATH | SIGSTOP))
		check_death(philo);
	if (check == FULL)
		check_full(philo);
}
