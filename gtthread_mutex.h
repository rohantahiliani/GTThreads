#include "gtthread_sched.h"

#define MAX_M 100000

typedef unsigned long gtthread_mutex_t;
unsigned long used_muts[MAX_M];
struct list *lm;

extern gtthread_mutex_t get_mutex_id();
extern int  gtthread_mutex_init(gtthread_mutex_t *mutex);
extern int  gtthread_mutex_lock(gtthread_mutex_t *mutex);
extern int  gtthread_mutex_unlock(gtthread_mutex_t *mutex);

