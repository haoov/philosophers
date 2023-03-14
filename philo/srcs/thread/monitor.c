#include "philo.h"

//[ ]: 42 header

static void	philo_death(t_philo *philo)
{
	t_signal sig;

	pthread_mutex_lock(&philo->data->mutex[END]);
	if (philo->data->sig == STOP)
		sig = NOFPRINT;
	else
		sig = FPRINT;
	philo->data->sig = STOP;
	pthread_mutex_unlock(&philo->data->mutex[END]);
	print_log(DEATH_LOG, philo, sig);
}

/**
 * @brief monitoring the philo to check if he is dead or not

 * @param arg The philosophers data

 * ! thread is never ending
 
 //TODO find a way to stop thread when philos are full
*/
void	*monitor(void *arg)
{
	t_philo	*philo;
	bool	stop;

	philo = (t_philo *)arg;
	philo->last_meal = philo->data->t0;
	stop = false;
	while (stop == false)
	{
		pthread_mutex_lock(&philo->infos);
		if (timestamp() - philo->last_meal >= philo->time.die)
			philo_death(philo);
		pthread_mutex_unlock(&philo->infos);
		usleep(5000);
	}
	return (NULL);
}
