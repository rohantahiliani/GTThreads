#include "gtthread_mutex.h"

gtthread_mutex_t get_mutex_id(){
	unsigned long i=1;
	for(;i<MAX_M;i++){
		if(!used_muts[i]){ used_muts[i]=1; return i;}
	}
	return 0;
}
int  gtthread_mutex_init(gtthread_mutex_t *mutex){
	*mutex=get_mutex_id();
	return 0;
}

int  gtthread_mutex_lock(gtthread_mutex_t *mutex){
	while(used_muts[*mutex]!=1) raise(SIGPROF);
	used_muts[*mutex]=lm->curr->gt_id+1;
	return 0;
}

int  gtthread_mutex_unlock(gtthread_mutex_t *mutex){
	if(used_muts[*mutex]==lm->curr->gt_id+1){used_muts[*mutex]=1; return 0;}
	else {perror("This thread cannot unlock the mutex presently."); exit(1);}
}

