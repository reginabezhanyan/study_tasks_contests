#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

enum { OFFSET = 3 };

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

static int
checkuid (int mode, int access)
{
    return ((((mode >> OFFSET) >> OFFSET) & access) == access);
}

static int
checkgid (int mode, int access)
{
    return (((mode >> OFFSET) & access) == access);
}

static int
checkoid (int mode, int access)
{
    return ((mode & access) == access);
}

int
myaccess(const struct stat *stb, const struct Task *task, int access)
{
    if (!stb || !task) {
        return 0;
    }
    if (!access) {
        return 1;
    }
    if (!task->uid) {
        return 1;
    }
    if (task->uid == stb->st_uid) {
        return checkuid(stb->st_mode, access);
    }
    for (int i = 0; i < task->gid_count; i++) {
        if (task->gids[i] == stb->st_gid) {
            return checkgid(stb->st_mode, access);
        }
    }
    return checkoid(stb->st_mode, access);
}