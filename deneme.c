#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t tid[2];
int counter;
pthread_mutex_t lock;
void* Operation(void *arg)
{	
	pthread_mutex_lock(&lock);//Kritik bölgeyi kilitliyoruz
	unsigned long i=0;
	counter  +=1;
	printf("\n Job %d started\n",counter);
	for (int i = 0; i < 100000000; i++);
	printf("\n %d finished\n",counter);
	pthread_mutex_unlock(&lock);//Kilit açılıyor diğer thread erişim sağlıyor
	return NULL;
	
}
int main(int argc, char const *argv[])
{	
	if(pthread_mutex_init(&lock,NULL)!=0)
	{
		printf("Mutex Failed\n");
		return 1;
	}
	pthread_create(&(tid[0]),NULL,&Operation,NULL);
	pthread_create(&(tid[1]),NULL,&Operation,NULL);
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);

	pthread_mutex_destroy(&lock);//mutex kaldırılıyor
	return 0;
}