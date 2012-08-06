#include "gtthread.h"

long gt_period=-1;
long temp_id=0;
int i;

void gtthread_init(long period){
	if(period>0 && gt_period<=0) {
		gt_period=period;
		temp_id=get_gt_id();
		gt_main=&gtt[temp_id];
		gt_main->gt_id=temp_id;
		gt_main->complete=0;
		gt_main->child_cnt=0;
		gt_main->parent_id=gt_main->gt_id;
		ll=&lp;
		lm=&lp;
		ll->head=NULL;
		ll->tail=NULL;
		ll->curr=gt_main;
		ll->count=0;
		ll->kill=0;
		add_thread(gt_main);
		init_timer(period);
	}
	else{
		perror("Invalid value for period.");
		exit(1);
	}
}

void gtthread_check_init(){
	if(gt_period<=0) {
		perror("GTThread library not initialized. Please use gtthread_init(period). Program terminating.");
		exit(1);
	}
}

void gtthread_execute(void *(*start_routine)(void *),void *arg){
	void *retval=start_routine(arg);
	gtthread_exit(retval);
}

int gtthread_create(gtthread_t *thread, void *(*start_routine)(void *), void *arg){
	struct gtthread *gt_new;

	gtthread_check_init();
	
	temp_id=get_gt_id();
	gt_new=&gtt[temp_id];
	gt_new->gt_id=temp_id;
	gt_new->complete=0;
	gt_new->parent_id=ll->curr->gt_id;
	ll->curr->child_cnt=ll->curr->child_cnt+1;
	gt_new->child_cnt=0;
	if(thread!=NULL) *thread=gt_new->gt_id;

	getcontext(&gt_new->gt_context);
	gt_new->gt_context.uc_link=0;
	gt_new->gt_context.uc_stack.ss_sp=malloc(GT_SS);
	gt_new->gt_context.uc_stack.ss_size=GT_SS;
	gt_new->gt_context.uc_stack.ss_flags=0;
	makecontext(&gt_new->gt_context,gtthread_execute,2,start_routine,arg);

	if(gt_new->gt_context.uc_stack.ss_sp==0){
		perror("Allocation error.");
		exit(1);
	}
	add_thread(gt_new);
	fflush(stdout);
	return 0;
}

int gtthread_equal(gtthread_t t1,gtthread_t t2){
	gtthread_check_init();	
	if(t1==t2) return 1;
	else return 0;
}

gtthread_t gtthread_self(){
	gtthread_check_init();
	return ll->curr->gt_id;
}

void gtthread_yield(void){
	gtthread_check_init();
	raise(SIGPROF);
}

int  gtthread_join(gtthread_t thread, void **status){
	struct gtthread *gt_join;
	gtthread_check_init();
	gt_join=&gtt[thread];
	while(gt_join->complete!=1)gtthread_yield();
	if(status!=NULL) *status=gt_join->ret;
	return 0;
}

void gtthread_exit(void *retval){
	gtthread_check_init();
	ll->curr->ret=retval;
	ll->curr->complete=1;
	while(ll->curr->child_cnt>0) gtthread_yield();
	if(ll->curr->gt_id==gt_main->gt_id) exit(0);
	rem_thread(ll->curr->gt_id);
	ll->kill=1;
	raise(SIGPROF);
}

int  gtthread_cancel(gtthread_t thread){
	struct gtthread *gt_cancel;
	gtthread_check_init();
	if(ll->curr->gt_id==thread) gtthread_exit((void*)GTTHREAD_CANCELED);
	else{
		gt_cancel=&gtt[thread];
		gt_cancel->ret=(void*)GTTHREAD_CANCELED;
		gt_cancel->complete=1;
		while(gt_cancel->child_cnt>0) gtthread_yield();
		rem_thread(thread);
	}
	return 0;
}
