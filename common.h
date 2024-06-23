#ifndef COMMON_H
#define COMMON_H
#define ERROR -1
#define SUCCESS 1

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int Validate_inputs(char **argv);

void View_mp3(char **argv);

void version_id(FILE *fp);
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
}mp3tag_info;

void Edit_mp3(char **argv);

void edit_content_type(FILE *fp,char **argv);
void edit_album(FILE *fp,char **argv);
void edit_title(FILE *fp,char **argv);
void edit_artist(FILE *fp,char **argv);
#endif
  

