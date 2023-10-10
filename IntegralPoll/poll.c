#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <poll.h>
#include <math.h>
#define NUM 50
#define errExit(msg)    do { perror(msg); _exit(EXIT_FAILURE); } while (0)

float f(float x){
    return exp(x);
}
float integral(float a, float b){
    float s=0;
    float delta=(b-a)/NUM;
    for(int i=0; i<NUM; i++){
        s=s+f(a+(i+0.5)*delta)*delta;
    }
    return s;
}

int main(int argc, char *argv[]) {
    int pipefd[NUM][2];
    pid_t cpid[NUM];
    int nfds, num_open_fds;
    struct pollfd *pfds;
    int i, rr;
    float a, b, buf;
    if(argc<3) {
        fprintf(stderr, "Usage: %s <float: a> <float: b>\tn", argv[0]);
        exit(EXIT_FAILURE);
    }
    a=atof(argv[1]);
    b=atof(argv[2]);
    float delta=(b-a)/NUM;
    num_open_fds = nfds = NUM;
    pfds = calloc(nfds, sizeof(struct pollfd));
    if (pfds == NULL) errExit("malloc");
    for (i=0;i<NUM;i++){

        if (pipe(pipefd[i]) == -1) errExit("pipe");
        pfds[i].fd = pipefd[i][0];
        pfds[i].events = POLLIN;
        if ((cpid[i] = fork()) == -1) errExit("fork");

        if (cpid[i] == 0) {
             printf("Child processes [%d] equals integral [%f;%f]\n", getpid(), a+i*delta, a+(i+1)*delta);
             sleep(6);
             close(pipefd[i][0]);
             buf=integral(a+i*delta,a+(i+1)*delta);
             write(pipefd[i][1], &buf, 4);             close(pipefd[i][1]);
             _exit(EXIT_SUCCESS);
        }
        else {
             close(pipefd[i][1]);
        }
      }

    printf("waiting... %d\n",num_open_fds);
    sleep(5);
    float s=0;
    while (num_open_fds > 0) {
        printf("\ntry poll:\n");
        for (i = 0; i < NUM; i++) pfds[i].revents=0;
        if (poll(pfds, nfds, -1) == -1) errExit("poll");
        for (i = 0; i < NUM; i++) {
             if (pfds[i].revents != 0) {
                  printf("  fd=%d; events: %7s%8s%8s  ", pfds[i].fd,
                          (pfds[i].revents & POLLIN)  ? "POLLIN "  : "",
                          (pfds[i].revents & POLLHUP) ? "POLLHUP " : "",
                          (pfds[i].revents & POLLERR) ? "POLLERR " : "");
                  if (pfds[i].revents & POLLIN) {
                       if(rr=read(pfds[i].fd, &buf, 4) > 0) s+= buf;
                       printf("s=%f\n",s);
                       if(rr < 0 ) errExit("read");
                       if(rr == 0 ) write(STDOUT_FILENO, "\n", 1);
                  } else
                  if ((pfds[i].revents & POLLHUP)&&~(pfds[i].revents & POLLIN)) {
                       printf("closing [%d] %d %d\n",i,pipefd[i][0],pfds[i].fd);
                       if (close(pfds[i].fd) < 0 ) errExit("close pfds");
                       pfds[i].fd = -1;
                       pfds[i].events=0;
                       num_open_fds--;
                  }
             }
        }
    }
    printf("result: %f\n",s);
    exit(EXIT_SUCCESS);
}
