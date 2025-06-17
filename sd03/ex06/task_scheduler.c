#include "task_scheduler.h"

static struct ScheduleResult *safe_error_return(
	struct TaskProfile *profile,
	struct PriorityMap *priority_map,
	struct ScheduleResult *schedule)
{
	if (profile)
		free_task_profile(profile);
	if (priority_map)
		free_priority_map(priority_map);
	// free for `schedule` is missing
	(void)schedule;
	return NULL;
}

struct ScheduleResult *schedule_tasks(struct TaskList *tasks)
{
	struct TaskProfile *profile = profile_tasks(tasks);
	if (!profile)
		return NULL;

	struct PriorityMap *priority_map = compute_priorities_mock(profile);
	if (!priority_map)
		return safe_error_return(profile, NULL, NULL);

	int available_cores = get_available_core_count();

	struct ScheduleResult *result = create_schedule_result(available_cores);
	if (!result)
		return safe_error_return(profile, priority_map, NULL);

	for (int core_id = 0; core_id < available_cores; core_id++)
	{
		int task_id = select_best_task_for_current_priorities(profile, priority_map);
		if (task_id == -1)
			return safe_error_return(profile, priority_map, result);
		update_schedule_entry(result, core_id, task_id);
	}

	free_task_profile(profile);
	free_priority_map(priority_map);

	return result;
}
