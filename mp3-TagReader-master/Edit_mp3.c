#include "common.h"

mp3tag_info tag;

void Edit_mp3(char **argv)
{
	int i;
	FILE *fp;
	char buffer[300];

	fp = fopen(argv[2],"rb+wb");
	if(fp == NULL)
	{
		perror("fopen");
		exit(1);
	}
if(strcmp(argv[3],"-t") == 0)
	edit_title(fp,argv);

else if(strcmp(argv[3],"-a") == 0)
	edit_artist(fp,argv);

else if(strcmp(argv[3],"-A") == 0)
	edit_album(fp,argv);

else
	edit_content_type(fp,argv);
	


printf("%ld",ftell(fp));
}

void edit_content_type(FILE *fp,char **argv)
{
	char buffer[30];
    if(strlen(argv[4]) > 9)
	{
		exit(2);
	}else
	{
    fseek(fp, +10, SEEK_SET);

	//printf("%ld",ftell(fp));
    fread(buffer,4,1,fp);
    if(strcmp(buffer,"TCON") == 0)
	{
		memset(buffer,'\0',30);
	strcpy(buffer,argv[4]);
    fseek(fp, +21, SEEK_SET);
    //printf("buffer content is %s", buffer);
    fwrite(buffer,9,1,fp);
    strcpy(tag.content_type,buffer);
    printf("content_type : %s\n", tag.content_type);
	}
	}

}

void edit_album(FILE *fp,char **argv)
{
	char buffer[30] = {'\0'};
    
    if(strlen(argv[4]) > 21)
	{
		exit(3);
	}else
	{
	fseek(fp, +30, SEEK_SET);

	fread(buffer,4,1,fp);
	if(strcmp(buffer, "TALB") == 0)
	{
    fseek(fp, +41, SEEK_SET);
    memset(buffer,'\0',30);
    strcpy(buffer,argv[4]);
    //printf("buffer content is %s", buffer);
    fwrite(buffer,21,1,fp);
    strcpy(tag.album,buffer);
    printf("Album : %s\n", tag.album);
	}
	}
}


void edit_title(FILE *fp,char **argv)
{
	char buffer[30] = {'\0'};

    if(strlen(argv[4]) > 15)
	{
		exit(4);
	}else
	{
	fseek(fp, +62, SEEK_SET);

	fread(buffer,4,1,fp);
	if(strcmp(buffer, "TIT2") == 0)
	{
    fseek(fp, +73, SEEK_SET);
    memset(buffer,'\0',30);
    strcpy(buffer,argv[4]);
    //printf("buffer content is %s", buffer);
    fwrite(buffer,15,1,fp);
    strcpy(tag.title,buffer);
    printf("Title : %s\n", tag.title);
	}
	}
}

void edit_artist(FILE *fp,char **argv)
{
	char buffer[30] = {'\0'};

    if(strlen(argv[4]) > 13)
	{
		exit(5);
	}else
	{
	fseek(fp, +88, SEEK_SET);

	fread(buffer,4,1,fp);
	if(strcmp(buffer, "TPE1") == 0)
	{
    fseek(fp, +99, SEEK_SET);
    memset(buffer,'\0',30);
    strcpy(buffer,argv[4]);
    //printf("buffer content is %s", buffer);
    fwrite(buffer,13,1,fp);
    strcpy(tag.artist,buffer);
    printf("Artist : %s\n", tag.artist);
	}
	}
}
