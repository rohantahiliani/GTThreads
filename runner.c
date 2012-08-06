#include <stdio.h>
#include <stdlib.h>
#include "gtthread.h"

gtthread_t t1,t2,t3,t4,t5;
gtthread_mutex_t m1,m2,m3,m4,m5;

void *philosopher(void *arg){
	short i;
	gtthread_mutex_t f1,f2;
	switch((int)arg){
		case 1: f1=m5; f2=m1;break;
		case 2: f1=m2; f2=m1;break;
		case 3: f1=m3; f2=m2;break;
		case 4: f1=m4; f2=m3;break;
		case 5: f1=m5; f2=m4;break;
	}
	while(1){
		printf("Philosopher #%d tries to acquire fork %lu\n",(int)arg,f1);
		gtthread_mutex_lock(&f1);
		printf("Philosopher #%d tries to acquire fork %lu\n",(int)arg,f2);
		gtthread_mutex_lock(&f2);
		printf("Philosopher #%d eating with fork %lu and %lu\n",(int)arg,f1,f2);
		gtthread_yield();
		i=rand()%9999;
		while(--i>0);
		printf("Philosopher #%d releasing fork %lu\n",(int)arg,f2);
		gtthread_mutex_unlock(&f2);
		printf("Philosopher #%d releasing fork %lu\n",(int)arg,f1);
		gtthread_mutex_unlock(&f1);
		printf("Philosopher #%d thinking\n",(int)arg);
		gtthread_yield();
		i=rand()%9999;
		while(--i>0);
	}
}

int main(){

	gtthread_init(10000);

	gtthread_mutex_init(&m1);
	gtthread_mutex_init(&m2);
	gtthread_mutex_init(&m3);
	gtthread_mutex_init(&m4);
	gtthread_mutex_init(&m5);
	gtthread_create(&t1, philosopher, (void*)1);
	gtthread_create(&t2, philosopher, (void*)2);
	gtthread_create(&t3, philosopher, (void*)3);
	gtthread_create(&t4, philosopher, (void*)4);
	gtthread_create(&t5, philosopher, (void*)5);

	while(1);

}
