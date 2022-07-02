#include <pthread.h>
#include <stdio.h>

int ft_bonjour(int i)
{
	return (0);
}

int main()
{
	pthread_t t1;
	pthread_t t2;
	int i;

	pthread_create(&t1, NULL, &ft_bonjour, 11);
	// pthread_create(&t2, NULL, NULL, NULL);

	pthread_join(t1, NULL);
	// pthread_join(t2, NULL);

	return (0);
}
 // comment exit un phtread;
 // phtread_join attend les fonctions
 // ne pas oublier de destroy les mutex; 