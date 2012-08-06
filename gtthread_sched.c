#include "gtthread_sched.h"

long gt_reset_time=-1;

void block_sig(){
	sigprocmask(SIG_BLOCK, &block, NULL);
}

void unblock_sig(){
	sigprocmask(SIG_UNBLOCK, &block, NULL);	
}

void init_timer(long period){
	gt_reset_time=period;
	sigemptyset(&block);
	sigaddset(&block,SIGPROF);
	timer_set.it_value.tv_sec=-0;
	timer_set.it_value.tv_usec=period;
	timer_set.it_interval.tv_sec=0;
	timer_set.it_interval.tv_usec=period;
	signal(SIGPROF,swap_thread);
	setitimer(ITIMER_PROF,&timer_set,NULL);
}

void swap_thread(int sig){
	block_sig();
	if(ll->kill==0 && (ll->count>1 || (ll->count==1 && ll->curr->gt_id==ll->curr->next->gt_id))){
		ll->curr=ll->curr->next;
		init_timer(gt_reset_time);
		unblock_sig();
		swapcontext(&ll->curr->prev->gt_context,&ll->curr->gt_context);
	}
	else{
		ll->curr=ll->curr->next;
		ll->kill=0;
		init_timer(gt_reset_time);
		unblock_sig();
		swapcontext(&dead_context,&ll->curr->gt_context);
	}
}

void add_thread(struct gtthread *thread){
	block_sig();
	list_add(thread);
	unblock_sig();
}

void rem_thread(gtthread_t thread){
	block_sig();
	list_rem(thread);
	unblock_sig();
}
