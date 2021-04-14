#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

void tree(int fd, int ind){
    struct Node beg; 
    if(lseek(fd, ind*sizeof(beg), SEEK_SET) < 0){
        exit(1);
    }
    if(read(fd, &beg, sizeof(beg)) != sizeof(beg)) {
        exit(1);
    }
    if(beg.right_idx){ 
        tree(fd, beg.right_idx);
    }
    printf("%d ", beg.key);
    if(beg.left_idx){
        tree(fd, beg.left_idx);
    }
}

int
main(int argc, char *argv[])
{
    int fd; 
    if((fd = open(argv[1], O_RDONLY)) < 0) {
        exit(1);
    }
    tree(fd, 0);
    printf("\n");
    close(fd);
    return 0;
}