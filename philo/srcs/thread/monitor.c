#include "philo.h"

void	*monitor(void *arg)
{
	t_philo	*philo;
	t_state	state;

	philo = (t_philo *)arg;
	state = ALIVE;
	philo->last_meal = philo->data->t0;
	while (state == ALIVE)
	{
		pthread_mutex_lock(&philo->infos);
		if (timestamp() - philo->last_meal >= philo->time.die)
		{
			philo->dead = true;
			state = DEAD;
		}
		pthread_mutex_unlock(&philo->infos);
		if (state == DEAD)
			print_log(DEATH_LOG, philo);
		usleep(1000);
	}
	return (NULL);
}
