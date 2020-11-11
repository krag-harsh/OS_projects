//https://mechpen.github.io/posts/2020-04-27-cfs-group/index.html  

/* inside function entity_before*/
u64			rtnice;  //inside iclude/linux/sched.h
p->se.rtnice= 0;  	//inside kernel/sched/core.c




//inside kernel/sched/fair.c

//---editing this might not work
// static inline int entity_before(struct sched_entity *a, struct  sched_entity *b)
// {

// 	if(a->rtnice>0 && b->rtnice>0)
// 	{
// 		return (s64)(a->rtnice - b->rtnice) < 0;
// 	}
// 	else if(a->rtnice>0 || b->rtnice>0)
// 	{
// 		if(a->rtnice > b->rtnice)
// 			return 1;
// 		else
// 			return 0;
// 	}
// 	else
// 		return (s64)(a->vruntime - b->vruntime) < 0;

//  }



//insdie pick_next_entity()
pick_next_entity(struct cfs_rq *cfs_rq, struct sched_entity *curr)
{
	//edit for assignment 3
	
	struct task_struct *task;
	u64 minval = 0;
	for_each_process(task)
	{
		if(task->se.on_rq == 1 && task->se.rtnice > minval)
		{
			se= &(task->se);
			minval=task->se.rtnice;
			printk("Value found and changed");
		}
	}	


	//editing done
 	return se;
}

/*inside function update_curr*/

static void update_curr(struct cfs_rq *cfs_rq)
{
	if(curr->rtnice==0)
		curr->vruntime += calc_delta_fair(delta_exec, curr);
	else
	{
		if(curr->rtnice > delta_exec)
			curr->rtnice-=delta_exec;
		else
			curr->rtnice = 0;
	}
}
