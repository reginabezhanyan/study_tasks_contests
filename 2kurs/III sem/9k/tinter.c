#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

enum { MAX_COM = PATH_MAX * 2 + 9 };

int main(int argc, char *argv[])
{ 
    char buf[PATH_MAX + 1];
    if (getenv("XDG_RUNTIME_DIR")) {
        snprintf(buf, PATH_MAX + 1, "%s/%d", getenv("XDG_RUNTIME_DIR"), getpid()); 
    } else if (getenv("TMPDIR")) {
        snprintf(buf, PATH_MAX + 1, "%s/%d", getenv("TMPDIR"), getpid());
    } else {
        snprintf(buf, PATH_MAX + 1, "%s/%d", "/tmp", getpid());
    }
    int tf = open(buf, O_CREAT | O_WRONLY | O_TRUNC, 0700); 
    if (tf < 0) {
        _exit(1);
    }
    FILE *f = fdopen(tf, "w");
    fprintf(f, "#! /usr/bin/python3\nprint(");
    for(int i = 1; i < argc - 1; i++) {
        fprintf(f, "%s*", argv[i]);
    }
    fprintf(f, "%s)", argv[argc - 1]); 
    fclose(f);
    close(tf);
    char command[MAX_COM];
    snprintf(command, MAX_COM, "%s && rm %s", buf, buf);
    execlp("/bin/sh", "sh", "-c", command, NULL); 
    _exit(1);
}