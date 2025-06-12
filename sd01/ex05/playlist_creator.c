#include "playlist_creator.h"

static struct Playlist *safe_error_return(
	struct MoodSettings *ms,
	struct FilterSettings *filters,
	struct SongData *song_data)
{
	if (ms)
		free_mood_settings(ms);
	if (filters)
		free_filter_settings(filters);
	if (song_data)
		free_song_data(song_data);
	return NULL;
}

struct Playlist *create_playlist(void)
{
	struct MoodSettings *user_mood = analyze_user_mood();
	if (!user_mood)
		return NULL;

	struct FilterSettings *base_filters = default_filters();
	if (!base_filters)
		return safe_error_return(user_mood, NULL, NULL);

	int mood_variations = get_mood_variations(user_mood);

	struct FilterSettings *final_filters = NULL;
	struct FilterSettings *prev_filters = base_filters;
	for (int i = 0; i < mood_variations; i++){
		final_filters = refine_filters(prev_filters);
		if (!final_filters)
			return safe_error_return(user_mood, prev_filters, NULL);
		if (final_filters != prev_filters)
			free_filter_settings(prev_filters);
		prev_filters = final_filters;
	}

	const bool is_popular_required = filters_require_popular_song(final_filters) != 0;

	struct SongData *song_data = NULL;
	if (is_popular_required)
		song_data = fetch_popular_song();
	else
		song_data = fetch_niche_song();
	if (!song_data)
		return safe_error_return(user_mood, final_filters, NULL);

	struct Playlist *result = combine_with_mood_playlist(song_data, user_mood);
	if (!result)
		return safe_error_return(user_mood, final_filters, song_data);

	return result;
}
