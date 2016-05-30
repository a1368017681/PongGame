#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

int main(){
    int i;
    initscr();

    clear();
    for(i = 0; i < LINES; ++i){
        move(i,i + 1);
        if(i&1) standout();
        addstr("Hello world");
        if(i&1) standend();
     //   refresh();
     //   getch();
     //   endwin();
    }
//    refresh(); 
    getch();
    endwin();
    /*  move(10,20);
    addstr("hello world");
    move(LINES - 1,0);
    refresh();
    getch();
    endwin();*/
    return 0;
}
