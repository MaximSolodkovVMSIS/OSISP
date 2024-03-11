#include "dirwalk.h"

int main(int argc, char* argv[]){
    
    int opt;
    char *path = ".";
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
            listSort(argv[optind]);
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