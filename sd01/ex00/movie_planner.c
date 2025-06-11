#include "movie_planner.h"

struct Plan *create_movie_night_plan(void)
{
	struct Preferences *user_preferences = get_user_preferences();

	struct MovieList *movies = find_movies(user_preferences);

	struct Plan *final_plan = build_plan(movies);

	return final_plan;
}
