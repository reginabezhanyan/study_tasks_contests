#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
const char *tempfile = "abc";

void handler(int s) 
{
    unlink(tempfile);
    signal(SIGINT, SIG_DFL);
    kill(getpid(), SIGINT);
}

int main(void)
{
    signal(SIGINT, handler);
    creat(tempfile, 0666);
    sleep(3);
    unlink(tempfile);
    return 0;
}
