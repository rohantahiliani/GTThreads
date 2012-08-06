#include "gtthread_mutex.h"

#define GT_SS 1024*8
#define GTTHREAD_CANCELED "GTTHREAD_CANCELED"
struct list lp;

extern void gtthread_init(long period);
extern int  gtthread_create(gtthread_t *thread, void *(*start_routine)(void *), void *arg);
extern int  gtthread_join(gtthread_t thread, void **status);
extern void gtthread_exit(void *retval);
extern void gtthread_yield(void);
extern int  gtthread_equal(gtthread_t t1, gtthread_t t2);
extern int  gtthread_cancel(gtthread_t thread);
extern gtthread_t gtthread_self(void);
extern void gtthread_execute(void *(*start_routine)(void *),void *arg);
