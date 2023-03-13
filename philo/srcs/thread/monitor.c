#include "philo.h"

void	*monitor(void *arg)
{
	t_philo		*philo;
	t_signal	sig;

	sig = CONTINUE;
	philo = (t_philo *)arg;
	while (sig == CONTINUE)
	{
		pthread_mutex_lock(&philo->infos);
		if (timestamp() - philo->last_meal >= philo->time.die)
		{
			philo->dead = true;
			sig = STOP;
			pthread_mutex_lock(&philo->data->mutex[END]);
			print_log(DEATH_LOG, philo);
			philo->data->sig = STOP;
			pthread_mutex_unlock(&philo->data->mutex[END]);
		}
		pthread_mutex_unlock(&philo->infos);
		usleep(1000);
	}
	return (NULL);
}
