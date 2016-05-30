#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define SHHHH

int main(){
    void wakeup(int);

    printf("about to sleep for 4 seconds\n");
    signal(SIGALRM,wakeup);
    alarm(4);
    pause();
    printf("Morning so soon? \n");
    return 0;
}
void wakeup(int signum){
#ifdef SHHHH
    printf("Alarm received from kernel\n");
#endif
}
