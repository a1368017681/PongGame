#include <stdio.h>
#include <curses.h>
#include <unistd.h>

int main(){
    int i;
    initscr();
    clear();
    for(int i = 0; i < LINES; ++i){
        move(i,i+i);
        if(i&1) standout();
        addstr("hello world");
        if(i&1) standend();
        refresh();
        sleep(1);
        move(i,i+i);
        addstr("                       ");
    }
    endwin();
    return 0;
}
