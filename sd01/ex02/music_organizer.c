#include "music_organizer.h"

struct MusicLibrary *organize_music_library(const char *directory_path)
{
	struct MusicLibrary *library = create_music_library();
	if (!library)
		return NULL;

	const char **filenames = scan_directory(directory_path);

	for (int i = 0; filenames[i]; i++)
	{
		struct MusicFile *song = process_music_file(directory_path, filenames[i]);
		update_music_library(library, song);
	}

	return library;
}
