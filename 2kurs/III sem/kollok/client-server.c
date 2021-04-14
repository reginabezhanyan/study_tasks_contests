#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    mkfifo("fifo", S_IFIFO | 0666);
    if (!fork()) {
        int fd = open("fifo", O_RDONLY);
        while (read(fd, &pid, sizeof(pid)) == sizeof(pid)) {
            printf("Server %d got message from %d!\n", getpid(), pid);
        }   
        close(fd);
        _exit(0);
    }
    if (!fork()) {
        pid = getpid();
        int fd = open("fifo", O_RDWR);
        sleep(2);
        write(fd, &pid, sizeof(pid));
        close(fd);
        _exit(0);
    }
    while (wait(NULL) != -1);
    unlink("fifo");
    return 0;
}
