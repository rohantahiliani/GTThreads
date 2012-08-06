#include <malloc.h>
#include <sched.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <ucontext.h>

#define MAX_T 100000

typedef unsigned long gtthread_t;
short used_ids[MAX_T];

struct gtthread{
	gtthread_t gt_id;
	ucontext_t gt_context;
	void *ret;
	int complete;
	int child_cnt;
	gtthread_t parent_id;
  	struct gtthread *next;
	struct gtthread *prev;
}gtt[MAX_T];

struct list{
	struct gtthread *head;
	struct gtthread *tail;
	struct gtthread *curr;
	unsigned long count;
	int kill;
};

struct list *ll;

extern gtthread_t get_gt_id();
extern void list_add(struct gtthread *n);
extern void list_rem(gtthread_t _id);
