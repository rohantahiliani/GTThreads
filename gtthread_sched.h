#include "gtthread_list.h"

struct gtthread *gt_main;
struct itimerval timer_set;
ucontext_t dead_context;
sigset_t block;

extern void gt_reset();
extern void block_sig();
extern void unblock_sig();
extern void swap_thread(int sig);
extern void init_timer(long period);
extern void add_process(struct gtthread *thread);
