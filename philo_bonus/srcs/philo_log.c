#include "philo_bonus.h"

void	philo_log(t_philo *philo, char *log)
{
	sem_wait(philo->data->stop);
	pthread_mutex_lock(&philo->infos);
	if (philo->stop == false)
		print_log(log, philo);
	pthread_mutex_unlock(&philo->infos);
	sem_post(philo->data->stop);
}
