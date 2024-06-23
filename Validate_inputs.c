#include "common.h"

//Define validate function
int Validate_inputs(char **argv)
{
	//Declare the variables
	size_t no_of_args = 0,i;
	int len = 0;
	FILE *fp;
	char code[4];
	char mp3[4] = "ID3";


	//Check for count of arguements
	for(i = 0 ;argv[i] ;i++)
	{
		no_of_args++;
	}

	//Check for 1 arguement
	if(no_of_args == 1)
	{
		printf("Error : ./mp3_tag_reader: Invalid Arguements\nUsage: ./mp3_tag_reader -h for help");
	return ERROR;
	}

	//Check the error case 1:
	if((strcmp(argv[1], "-h") != 0) && (strcmp(argv[1], "-v") != 0) && (strcmp(argv[1], "-e") != 0))
	{
		printf("INVALID OPTIONS");
		return ERROR;
	}

	//For proper usage go for help menu
	if(strcmp(argv[1], "-h") == 0)
	{
		printf("Help menu for Mp3 Tag Reader and Editor:\n\nFor viewing the tags- ./mp3_tag_reader -v <.mp3 file>\n\nFor editing the tags- ./mp3_tag_reader -e <.mp3 file> <modifier> <tag>\n\nModifier  Function\n  -t   Modifies Title tag\n  -T   Modifies Track tag\n  -a   Modifies Artist tag\n  -A   Modifies Album tag\n  -y   Modifies Year tag\n  -c   Modifies Comment tag\n  -g   Modifies Genre tag\n");
		return SUCCESS;
	}

	//Check the error case for no of arguements for viewing tags
	if(strcmp(argv[1],"-v") == 0)
	{
		if(no_of_args < 3 || no_of_args > 4)
		{
			printf("INSUFFICIENT ARGUEMENTS\nUSAGE : ./mp3_tag_reader -v <.mp3 file>\n");
		return ERROR;
		}
	}

	//Check the error case for no of arguements for editing tags
	if(strcmp(argv[1],"-e") == 0)
	{
		if(no_of_args < 4 || no_of_args > 5)
		{
          printf("INSUFFICIENT ARGUEMENTS\nUSAGE : ./mp3_tag_reader -e <.mp3 file> <modifier> <tag>");
		return ERROR;
		}
	}

    //Check for second error case to check whether mp3 file or not
	len = strlen(argv[2]);
	if(strcmp((argv[2] + (len - 3)), "mp3") != 0)
	{
		printf("INVALID FILE FORMAT\n");
		return ERROR;
	}

	//Open the mp3 file
	if((strcmp(argv[1], "-v") == 0) || (strcmp(argv[1], "-e") == 0))
	{
		if((fp = fopen(argv[2], "rb")) == NULL)
		{
			perror("fopen");
			printf("UNABLE TO OPEN SOURCE FILE");
			return ERROR;
		}
          
        //Read 3 bytes + store it in int variable
         fread(code, 3, 1, fp);
         for(i = 0 ;i < 3 ;i++ )
		 {
         if(code[i] != mp3[i])
         {
              printf("THE OPENED FILE CODE DOESN'T MATCH\n");
              return ERROR; 
          }
		 }
           fclose(fp);
     }

     if(strcmp(argv[1], "-e") == 0)
	 {
	 	 if((strcmp(argv[3], "-t") != 0) && (strcmp(argv[3], "-T") != 0) && 
(strcmp(argv[3], "-a") != 0) && (strcmp(argv[3], "-A") != 0) && (strcmp(argv[3], "-y") != 0) && (strcmp(argv[3], "-c") != 0) && (strcmp(argv[3], "-g") != 0))
		 {
		 	 printf("INVALID MODIFIER\nUSAGE : -t/-T/-a/-A/-y/-c/-g");
		 	 return ERROR;
		 }
	 }

	 if(strcmp(argv[1],"-e") == 0)
	 {
		 if(argv[4] == NULL)
		 {
		 	 printf("Enter tag");
		 	 return ERROR;
		 }
	 }
	 return SUCCESS;
}
