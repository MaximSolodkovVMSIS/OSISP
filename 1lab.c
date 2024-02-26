#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/stat.h"
#include "dirent.h"
#include "getopt.h"
#include "unistd.h"

#define PATH_MAX 4096

int compare(const struct dirent **a, const struct dirent **b){
    return strcoll((*a) -> d_name, (*b) -> d_name);
}

void listAll(const char* path){
    DIR *dir;
    struct dirent *entry;
    
    if((dir = opendir(path)) == NULL){
        perror("Can't open directory");
        exit(EXIT_FAILURE);
    }
    while((entry = readdir(dir)) != NULL){
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}
void listFiles(const char *path){
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    if((dir = opendir(path)) == NULL){
        perror("Can't open directory");
        exit(EXIT_FAILURE);
    }
    while((entry = readdir(dir)) != NULL){
        char full_path[PATH_MAX];
        sprintf(full_path, "%s/%s", path, entry -> d_name);

        if(stat(full_path, &file_stat) == -1){
            perror("Can't get file status");
            continue;
        }
        if(S_ISREG(file_stat.st_mode)){
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
}

void listDirectory(const char* path){
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    if((dir = opendir(path)) == NULL){
        perror("Can't open directory");
        exit(EXIT_FAILURE);
    }

    while((entry = readdir(dir)) != NULL){
        char full_path[PATH_MAX];
        sprintf(full_path, "%s/%s", path, entry -> d_name);

        if(stat(full_path, &file_stat) == -1){
            perror("Can't get file status");
            continue;
        } 
        if(S_ISDIR(file_stat.st_mode)){
            printf("%s\n", entry -> d_name);
        }
    }
    closedir(dir);
}

void listSortDirectory(const char* path){
    struct dirent **namelist;
    int num;

    num = scandir(path, &namelist, NULL, compare);
    if(num == -1){
        perror("Scandir failed");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < num; i++){
        printf("%s\n", namelist[i]->d_name);
        free(namelist[i]);
    }
    free(namelist);
    
}

void listLink(const char *path){
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    if((dir = opendir(path)) == NULL){
        perror("Can't open directory");
        exit(EXIT_FAILURE);
    }
    while((entry = readdir(dir)) != NULL){
        char full_path[PATH_MAX];
        sprintf(full_path, "%s%s", path, entry->d_name);

        if(lstat(full_path, &file_stat) == -1){
            perror("Can't get file status");
            continue;
        }

        if(S_ISLNK(file_stat.st_mode)){
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
}

int main(int argc, char* argv[]){
    
    int opt;
    char *path = ".";
    int listAllFlags = 0;
    while((opt = getopt(argc, argv, "fdls")) != -1){
        switch (opt)
        {
        case 'f':
            listFiles(argv[optind]);
            break;
        case 'd':
            listDirectory(argv[optind]);
            break;
        case 'l':
            listLink(argv[optind]);
            break;
        case 's':
            listSortDirectory(argv[optind]);
            break;
        default:
            fprintf(stderr, "Usage: %s [-fdls directory]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    if(argc == 1){
        listAll(path);
    }
    else if(argc == 2){
        path = argv[1];
        listAll(path);
    }
    return 0;
}