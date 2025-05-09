#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Video 
{
    char *name;
    int unique_views;
} Video;

typedef struct Viewer 
{
    char *username;
    Video *watched_videos;
    int watched_videos_size;
} Viewer;

int count_views(Viewer **viewers, int viewers_size, char *video_name)
{
    	int count = 0;
	for(int i = 0; i < viewers_size; ++i)
	{
		const Viewer* viewer = viewers[i];
		for(int k = 0; k < viewer->watched_videos_size; ++k)
		{
			const Video watched_video = viewer->watched_videos[k];
			if(strcmp(video_name, watched_video.name) == 0)
				++count;
		}
	}

    	return count;
}

#ifndef RunTests
int main()
{
    Video videos[] = { {.name = "Soccer", .unique_views = 500},
                       {.name = "Basketball", .unique_views = 1000} };
    Viewer viewer = {.username = "Dave", .watched_videos = videos,
                     .watched_videos_size = 2};
    
    Viewer *viewers[] = { &viewer };
    printf("%d", count_views(viewers, 1, "Soccer")); /* should print 1 */
}
#endif
