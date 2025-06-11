#include "movie_planner.h"

struct Plan *create_movie_night_plan(void)
{
	struct Preferences *user_preferences = get_user_preferences();
	if (!user_preferences)
		return (NULL);

	struct MovieList *movies = find_movies(user_preferences);
	if (!movies)
		return (NULL);

	struct Plan *final_plan = build_plan(movies);

	return final_plan;
}
