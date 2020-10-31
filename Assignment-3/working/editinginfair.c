//https://mechpen.github.io/posts/2020-04-27-cfs-group/index.html  

/* inside function entity_before*/
u64			rtnice;  //inside iclude/linux/sched.h
p->se.rtnice= 0;  	//inside kernel/sched/core.c

//inside kernel/sched/fair.c
static inline int entity_before(struct sched_entity *a, struct  sched_entity *b)
{

	if(a->rtnice>0 && b->rtnice>0)
	{
		return (s64)(a->rtnice - b->rtnice) < 0;
	}
	else if(a->rtnice>0 || b->rtnice>0)
	{
		if(a->rtnice > b->rtnice)
			return 1;
		else
			return 0;
	}
	else
		return (s64)(a->vruntime - b->vruntime) < 0;

 }


/*inside function update_curr*/

static void update_curr(struct cfs_rq *cfs_rq)
{
	if(curr->rtnice==0)
		curr->vruntime += calc_delta_fair(delta_exec, curr);
	else
	{
		if(curr->sr_prio > delta_exec)
			curr->sr_prio-=delta_exec;
		else
			curr->sr_prio = 0;
	}
}