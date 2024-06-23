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
