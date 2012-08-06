#include "gtthread_list.h"

gtthread_t get_gt_id(){
	unsigned long i=1;
	for(;i<MAX_T;i++){
		if(!used_ids[i]){ used_ids[i]=1; return i;}
	}
	return 0;
}

void list_add(struct gtthread *n){
	if(ll->count==0){
		n->next=n;
		n->prev=n;
		ll->head=n;
		ll->tail=n;
	}
	else{
		n->next=ll->head;
		n->prev=ll->tail;
		ll->tail->next=n;
		ll->head->prev=n;
		ll->tail=n;
	}
	ll->count++;
}

void list_rem(gtthread_t _id){
	struct gtthread *p,*q;
	p=ll->head;
	do{
		if(p->gt_id==_id){
			if(ll->count==1){
				ll->head=NULL;
				ll->tail=NULL;
				exit(0);
			}
			else{
				ll->count=ll->count-1;
				q=&gtt[p->parent_id];
				q->child_cnt=q->child_cnt-1;
				if(p==ll->head) ll->head=p->next;
				else if(p==ll->tail) ll->tail=p->prev;
				if(p->prev!=NULL) p->prev->next=p->next;
				if(p->next!=NULL) p->next->prev=p->prev;
			}
			return;
		}
		else{
			p=p->prev;
		}
	} while(p->gt_id!=ll->head->gt_id);

}
