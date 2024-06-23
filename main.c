/*
Name: Lokeshkumar P
Date: 23.06.2024
Description: MP3 Tag Reader
Sample input: ./mp3_tag_reader -v music.mp3
Sample output: Version_id :
               buffer content is content_type : Cinematic
               buffer content is Album : YouTube Audio Library
               buffer content is Title : CINEMATIC
               buffer content is Artist : Kevin MacLeod
               Mp3 tags successfully viewedl
*/

#include "common.h"

int main(int argc, char *argv[])
{
	//collect status
	int status = Validate_inputs(argv);
	if(status == ERROR)
	{
		return 0;
	}
    
    //Check for viewing tags without error
	if(strcmp(argv[1],"-v") == 0)
	{
		if(status != ERROR)
		{
			View_mp3(argv);
			printf("Mp3 tags successfully viewed");
			return 0;
		}
	}

    //Check for editing tags without error
	if(strcmp(argv[1],"-e") == 0)
	{
		if(status != ERROR)
		{
			Edit_mp3(argv);
			printf("Mp3 tags were successfully edited");
			return 0;
		}
	}
}
