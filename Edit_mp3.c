#include "common.h"

mp3tag_info tag;

void Edit_mp3(char **argv)
{
    FILE *fp;

    fp = fopen(argv[2], "rb+");
    if (fp == NULL)
    {
        perror("fopen");
        exit(1);
    }

    if (strcmp(argv[3], "-t") == 0)
        edit_title(fp, argv);
    else if (strcmp(argv[3], "-a") == 0)
        edit_artist(fp, argv);
    else if (strcmp(argv[3], "-A") == 0)
        edit_album(fp, argv);
    else
        edit_content_type(fp, argv);

    fclose(fp);
}

void edit_content_type(FILE *fp, char **argv)
{
    char buffer[30];
    if (strlen(argv[4]) > 9)
    {
        fprintf(stderr, "Error: Content type too long\n");
        exit(2);
    }
    else
    {
        if (fseek(fp, 10, SEEK_SET) != 0)
        {
            perror("fseek");
            exit(1);
        }

        if (fread(buffer, 4, 1, fp) != 1)
        {
            perror("fread");
            exit(2);
        }

        if (strcmp(buffer, "TCON") == 0)
        {
            memset(buffer, '\0', 30);
            strcpy(buffer, argv[4]);
            if (fseek(fp, 21, SEEK_SET) != 0)
            {
                perror("fseek");
                exit(1);
            }

            if (fwrite(buffer, 9, 1, fp) != 1)
            {
                fprintf(stderr, "Error writing to file\n");
                exit(6);
            }

            if (fflush(fp) != 0)
            {
                perror("fflush");
                exit(3);
            }

            fseek(fp, 21, SEEK_SET);
            memset(buffer, '\0', 30);
            fread(buffer, 9, 1, fp);

            if (strcmp(buffer, argv[4]) == 0)
            {
                strcpy(tag.content_type, buffer);
                printf("Content Type : %s\n", tag.content_type);
            }
            else
            {
                fprintf(stderr, "Verification failed. Data not written correctly.\n");
                exit(7);
            }
        }
        else
        {
            fprintf(stderr, "Error: Content type tag not found\n");
            exit(4);
        }
    }
}

void edit_album(FILE *fp, char **argv)
{
    char buffer[30] = {'\0'};

    if (strlen(argv[4]) > 21)
    {
        fprintf(stderr, "Error: Album name too long\n");
        exit(3);
    }
    else
    {
        if (fseek(fp, 30, SEEK_SET) != 0)
        {
            perror("fseek");
            exit(1);
        }

        if (fread(buffer, 4, 1, fp) != 1)
        {
            perror("fread");
            exit(2);
        }

        if (strcmp(buffer, "TALB") == 0)
        {
            if (fseek(fp, 41, SEEK_SET) != 0)
            {
                perror("fseek");
                exit(1);
            }

            memset(buffer, '\0', 30);
            strcpy(buffer, argv[4]);

            if (fwrite(buffer, 21, 1, fp) != 1)
            {
                fprintf(stderr, "Error writing to file\n");
                exit(6);
            }

            if (fflush(fp) != 0)
            {
                perror("fflush");
                exit(3);
            }

            fseek(fp, 41, SEEK_SET);
            memset(buffer, '\0', 30);
            fread(buffer, 21, 1, fp);

            if (strcmp(buffer, argv[4]) == 0)
            {
                strcpy(tag.album, buffer);
                printf("Album : %s\n", tag.album);
            }
            else
            {
                fprintf(stderr, "Verification failed. Data not written correctly.\n");
                exit(7);
            }
        }
        else
        {
            fprintf(stderr, "Error: Album tag not found\n");
            exit(4);
        }
    }
}

void edit_title(FILE *fp, char **argv)
{
    char buffer[30] = {'\0'};

    if (strlen(argv[4]) > 15)
    {
        fprintf(stderr, "Error: Title too long\n");
        exit(4);
    }
    else
    {
        if (fseek(fp, 62, SEEK_SET) != 0)
        {
            perror("fseek");
            exit(1);
        }

        if (fread(buffer, 4, 1, fp) != 1)
        {
            perror("fread");
            exit(2);
        }

        if (strcmp(buffer, "TIT2") == 0)
        {
            if (fseek(fp, 73, SEEK_SET) != 0)
            {
                perror("fseek");
                exit(1);
            }

            memset(buffer, '\0', 30);
            strcpy(buffer, argv[4]);

            if (fwrite(buffer, 15, 1, fp) != 1)
            {
                fprintf(stderr, "Error writing to file\n");
                exit(6);
            }

            if (fflush(fp) != 0)
            {
                perror("fflush");
                exit(3);
            }

            fseek(fp, 73, SEEK_SET);
            memset(buffer, '\0', 30);
            fread(buffer, 15, 1, fp);

            if (strcmp(buffer, argv[4]) == 0)
            {
                strcpy(tag.title, buffer);
                printf("Title : %s\n", tag.title);
            }
            else
            {
                fprintf(stderr, "Verification failed. Data not written correctly.\n");
                exit(7);
            }
        }
        else
        {
            fprintf(stderr, "Error: Title tag not found\n");
            exit(4);
        }
    }
}

void edit_artist(FILE *fp, char **argv)
{
    char buffer[30] = {'\0'};

    if (strlen(argv[4]) > 13)
    {
        fprintf(stderr, "Error: Artist name too long\n");
        exit(5);
    }
    else
    {
        if (fseek(fp, 88, SEEK_SET) != 0)
        {
            perror("fseek");
            exit(1);
        }

        if (fread(buffer, 4, 1, fp) != 1)
        {
            perror("fread");
            exit(2);
        }

        if (strcmp(buffer, "TPE1") == 0)
        {
            if (fseek(fp, 99, SEEK_SET) != 0)
            {
                perror("fseek");
                exit(1);
            }

            memset(buffer, '\0', 30);
            strcpy(buffer, argv[4]);

            size_t elements_written = fwrite(buffer, 13, 1, fp);

            if (fflush(fp) != 0)
            {
                perror("fflush");
                exit(3);
            }

            if (elements_written != 1)
            {
                fprintf(stderr, "Error writing to file\n");
                exit(6);
            }

            if (fseek(fp, 99, SEEK_SET) != 0)
            {
                perror("fseek");
                exit(1);
            }

            memset(buffer, '\0', 30);
            if (fread(buffer, 13, 1, fp) != 1)
            {
                perror("fread");
                exit(2);
            }

            if (strcmp(buffer, argv[4]) == 0)
            {
                strcpy(tag.artist, buffer);
                printf("Artist : %s\n", tag.artist);
            }
            else
            {
                fprintf(stderr, "Verification failed. Data not written correctly.\n");
                exit(7);
            }
        }
        else
        {
            fprintf(stderr, "Error: Artist tag not found\n");
            exit(4);
        }
    }
}

