#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define INPUTLEN 100

int main(int ac,char *av[]){
    void inthandler(int);
    void quithandler(int);
    char input[INPUTLEN];
    int nchars;

    signal(SIGINT,inthandler);
    signal(SIGQUIT,quithandler);

    do{
        printf("\nTypea message\n");
        nchars = read(0,input,(INPUTLEN - 1));
        if(nchars == -1) perror("read returned an error");
        else{
            input[nchars] = '\0';
            printf("You typed: %s",input);
        }
    }while(strncmp(input,"quit",4) != 0);
    return 0;
}

void inthandler(int s){
    printf("Recieved signal %d..waiting\n",s);
    sleep(2);
    printf("Leaving inthandler \n");
}

void quithandler(int s){
    printf("Recieved signal %d..waiting\n",s);
    sleep(3);
    printf("Leaving quithandler \n");
}
