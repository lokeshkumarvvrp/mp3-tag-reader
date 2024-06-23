#include "common.h"

/*void version_id(FILE *fp);
void content_type(FILE *fp);
void album(FILE *fp);
void title(FILE *fp);
void artist(FILE *fp);

typedef struct tag
{
	char  version_id[3];
	char title[30];
	char album[30];
	char content_type[30];
	char artist[30];
}mp3tag_info;*/

mp3tag_info tag;

void View_mp3(char **argv)
{
	FILE *fp;

	fp = fopen(argv[2], "rb");
	if(fp == NULL)
	{
		perror("fopen");
		exit(1);
	}

//	printf("\n%ld",ftell(fp));

	version_id(fp);
	content_type(fp);
	album(fp);
	title(fp);
	artist(fp);

	fclose(fp);
}

void version_id(FILE *fp)
{

	char buffer[3]={'\0'};
    fseek(fp, +3, SEEK_SET);
    fread(buffer,2,1,fp);
    printf("%s", buffer);
    strcpy(tag.version_id,buffer);
    printf("Version_id : %s\n", tag.version_id);

//	printf("%ld",ftell(fp));
//	rewind(fp);
}

void content_type(FILE *fp)
{

	char buffer[30]={'\0'};
    fseek(fp, +10, SEEK_SET);

	//printf("%ld",ftell(fp));
    fread(buffer,4,1,fp);
    if(strcmp(buffer,"TCON") == 0)
	{
    fseek(fp, +21, SEEK_SET);
    memset(buffer,'\0',30);
    //printf("buffer content is %s", buffer);
    fread(buffer,9,1,fp);
    strcpy(tag.content_type,buffer);
    printf("content_type : %s\n", tag.content_type);
	}
//	printf("%ld",ftell(fp));
//	rewind(fp);
}

void album(FILE *fp)
{
	char buffer[30] = {'\0'};
	fseek(fp, +30, SEEK_SET);

	fread(buffer,4,1,fp);
	if(strcmp(buffer, "TALB") == 0)
	{
    fseek(fp, +41, SEEK_SET);
    memset(buffer,'\0',30);
    //printf("buffer content is %s", buffer);
    fread(buffer,21,1,fp);
    strcpy(tag.album,buffer);
    printf("Album : %s\n", tag.album);
	}
}


void title(FILE *fp)
{
	char buffer[30] = {'\0'};
	fseek(fp, +62, SEEK_SET);

	fread(buffer,4,1,fp);
	if(strcmp(buffer, "TIT2") == 0)
	{
    fseek(fp, +73, SEEK_SET);
    memset(buffer,'\0',30);
    //printf("buffer content is %s", buffer);
    fread(buffer,15,1,fp);
    strcpy(tag.title,buffer);
    printf("Title : %s\n", tag.title);
	}
}

void artist(FILE *fp)
{
	char buffer[30] = {'\0'};
	fseek(fp, +88, SEEK_SET);

	fread(buffer,4,1,fp);
	if(strcmp(buffer, "TPE1") == 0)
	{
    fseek(fp, +99, SEEK_SET);
    memset(buffer,'\0',30);
    //printf("buffer content is %s", buffer);
    fread(buffer,13,1,fp);
    strcpy(tag.artist,buffer);
    printf("Artist : %s\n", tag.artist);
	}
}
