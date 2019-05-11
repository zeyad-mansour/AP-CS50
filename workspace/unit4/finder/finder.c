// Recursively searches for a query in a directory.

#define _BSD_SOURCE
#define _GNU_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAXLENGTH 50

// Struct to hold the file name and type
typedef struct
{
    string name;
    string type;
}
path;

// Struct to hold the directory info
typedef struct
{
    string name;
    int npaths;
    path *paths;
}
directory;

// String to hold the word to seek
string key;

// The function to search for files in a directory and populate the struct
directory populate(directory dir);

// The function to recursively iterate through directories and handle files
int seek(directory dir);

int main(int argc, char* argv[])
{

    // TODO: ensure proper number of command line arguments
    if(argc != 3 && argc != 2)
    {
        return 1;
    }
    directory dir;
    key = argv[1];

    // TODO: set "dir"s name based on command line arguments entered
    if(argc == 3){
        dir.name = argv[2];
    }
    else
    {
        dir.name  = "./";
    }
    seek(dir);
}

directory populate(directory dir)
{
    // Initialize all pointers and values in the given struct
    dir.npaths = 0;
    dir.paths = NULL;
    DIR *dirp;
    struct dirent* entry;

    dirp = opendir(dir.name);
    if (dirp == NULL)
    {
        printf("Opening directory failed. Check your key filepath!\n");
        return dir;
    }

    while ((entry = readdir(dirp)) != NULL)
    {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            // Allocate zeroed-out memory for the construction of the file name
            string name = calloc(1, strlen(dir.name) + strlen(entry->d_name) + 2);
            strcat(name, dir.name);
            strcat(name, entry->d_name);
            strcat(name, "/");

            // Reallocate memory to expand the array
            dir.paths = realloc(dir.paths, (dir.npaths + 1) * sizeof(path));

            // Add a new element to the array containing names and types
            path newPath = {.name = name, .type = "directory"};
            dir.paths[dir.npaths] = newPath;

            // Increase file count for the directory
            dir.npaths++;
        }

        // Else if entry is a file, increase file count and populate the struct
        else if (entry->d_type == DT_REG)
        {
            // Allocate zeroed-out memory for the construction of the file name
            string name = calloc(1, strlen(dir.name) + strlen(entry->d_name) + 1);
            strcat(name, dir.name);
            strcat(name, entry->d_name);

            // Reallocate memory to expand the array
            dir.paths = realloc(dir.paths, (dir.npaths + 1) * sizeof(path));

            // Add a new element to the array containing names and types
            path newPath = {.name = name, .type = "file"};
            dir.paths[dir.npaths] = newPath;

            // Increase file count for the directory
            dir.npaths++;
        }
    }

    // Close directory stream using system call closedir and return struct
    closedir(dirp);
    return dir;
}

// Recursive function to iterate through directories and search files
int seek(directory dir)
{
    dir = populate(dir);
    for(int i = 0; i < dir.npaths; i++)
    {
        if(strcmp(dir.paths[i].type,"file") == 0 && strcmp(dir.paths[i].name,"./found.txt") != 0 && strcmp(dir.paths[i].name,"./finder") != 0)
        {
            FILE *fr = fopen(dir.paths[i].name,"r");
            if(fr == NULL)
            {
                return 1;
            }
            bool search = false;
			char search_string[50];
            while(fgets (search_string, sizeof(search_string),fr) != NULL)
            {
                char *sub_dir;
                sub_dir = strstr(search_string,key);
                if(sub_dir == NULL)
                {
                    sub_dir = search_string;
                }

                if(strlen(sub_dir) > strlen(key))
                {
                    sub_dir[strlen(key)] = '\0';
                }

                if(strcmp(sub_dir,key) == 0)
                {
                    FILE *fw = fopen("found.txt","a"); //start adding onto found.txt
                    if (fw == NULL)
                    {
                        return 1;
                    }
                    if(!search)
                    {
                        fputs("for keysearch_string ",fw);
                        fputs(key,fw);
                        fputs(" in ",fw);
                        fputs(dir.paths[i].name,fw);
                        fputs(":\n",fw);
                        search = true;
                    }
                    fputs(key,fw);
                    fputs("\n",fw);
                    fclose(fw);
                }
            }
            fclose(fr);
        }
        else if(strcmp(dir.paths[i].type,"directory") == 0)
        {
            directory new_dir;
            new_dir.name = dir.paths[i].name;
            seek(new_dir);
        }
    }
}