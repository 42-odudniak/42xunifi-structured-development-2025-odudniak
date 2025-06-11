#include "workout_scheduler.h"

struct WorkoutPlan *safe_error_return(struct UserData *user_data, struct WorkoutPlan *workout_plan)
{
	if (user_data)
		free_user_data(user_data);
	if (workout_plan)
		free_workout_plan(workout_plan);
	return NULL;
}


struct WorkoutPlan *create_workout_schedule(char *username)
{
	struct UserData *user_data = get_user_data(username);
	if (!user_data)
		return safe_error_return(user_data, NULL);

	struct WorkoutPlan *base_plan = build_base_plan(user_data);
	if (!base_plan)
		return safe_error_return(user_data, base_plan);

	struct WorkoutPlan *final_plan = refine_plan(base_plan, user_data);
	if (!final_plan)
		return safe_error_return(user_data, base_plan);
	if (base_plan != final_plan)
		free_workout_plan(base_plan);

	int days_scheduled = determine_duration(final_plan);
	if (days_scheduled <= 0)
		return safe_error_return(user_data, final_plan);

	//Assuming the plan can keep all the days' exercises and tips
	for (int day = 1; day <= days_scheduled; day++){
		assign_daily_exercises(final_plan, day);
		assign_daily_tips(final_plan, day);
	}

	//Might do it earlier
	free_user_data(user_data);
	return final_plan;
}
