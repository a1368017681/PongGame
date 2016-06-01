#include <curses.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "bounce.h"
#include "set_ticker.c"

struct ppball the_ball;
struct barrier the_barrier;

void set_up();
void wrap_up();
int bounce_or_lose(struct ppball*);
void barrier_mv_up();
void barrier_mv_down();

int main(){
    int c;

    set_up();

    while((c = getchar()) != 'Q'){
        if(c == 'f') {
            if(the_ball.x_ttm > 1)
            the_ball.x_ttm--;
        }
        else if(c == 's') the_ball.x_ttm++;
        else if(c == 'F'){
            if(the_ball.y_ttm > 1)
            the_ball.y_ttm--;
        }
        else if(c == 'S') the_ball.y_ttm++;
        else if(c == '8') barrier_mv_up();
        else if(c == '2') barrier_mv_down();
    }

    wrap_up();
    return 0;
}

void set_up(){
    void ball_move(int);

    the_ball.y_pos = Y_INIT;
    the_ball.x_pos = X_INIT;
    the_ball.y_ttg = the_ball.y_ttm = Y_TTM;
    the_ball.x_ttg = the_ball.x_ttm = X_TTM;
    the_ball.y_dir = 1;
    the_ball.x_dir = 1;
    the_ball.symbol = DFL_SYMBOL;
    
    the_barrier.top_x = RIGHT_EDGE + 1;
    the_barrier.top_y = TOP_ROW + 3;
    the_barrier.bot_x = RIGHT_EDGE + 1;
    the_barrier.bot_y = BOT_ROW - 3;
    the_barrier.symbol = WALL;

    initscr();
    noecho();
    crmode();

    for(int i = LEFT_EDGE;i < RIGHT_EDGE; ++i){
        mvaddch(TOP_ROW-1,i,WALL);
        mvaddch(BOT_ROW+1,i,WALL);
    }
    for(int j = TOP_ROW-1; j <= BOT_ROW+1; ++j){
        mvaddch(j,LEFT_EDGE-1,WALL);
        if(j >= the_barrier.top_y && j <= the_barrier.bot_y) mvaddch(j,RIGHT_EDGE+1,WALL);
    }
    mvaddstr(1,9,"Q:quit,8:move up,2:move down");    
    mvaddstr(2,9,RULE);
    signal(SIGINT,SIG_IGN);
    mvaddch(the_ball.y_pos,the_ball.x_pos,the_ball.symbol);
    refresh();

    signal(SIGALRM,ball_move);
    
    set_ticker(1000/TICKS_PER_SEC);
}

void wrap_up(){
    set_ticker(0);
    endwin();
}

void barrier_mv_up(){
    if(the_barrier.top_y >= TOP_ROW){
        the_barrier.dir = 1;
        mvaddch(the_barrier.bot_y,the_barrier.bot_x,BLANK);
        the_barrier.bot_y--;
        mvaddch(the_barrier.top_y,the_barrier.top_x,WALL);
        the_barrier.top_y--;
    }
    refresh();
}

void barrier_mv_down(){
    if(the_barrier.bot_y <= BOT_ROW){
         the_barrier.dir = -1;      
         mvaddch(the_barrier.top_y,the_barrier.top_x,BLANK);
         the_barrier.top_y++;
         mvaddch(the_barrier.bot_y,the_barrier.bot_x,WALL);
         the_barrier.bot_y++;
  //       refresh();
    }    
    refresh();
}

void ball_move(int signum){
    int y_cur,x_cur,moved;
    signal(SIGALRM,SIG_IGN);
    y_cur = the_ball.y_pos;
    x_cur = the_ball.x_pos;
    moved = 0;
    
    if(the_ball.y_ttm > 0 && the_ball.y_ttg-- == 1){
        the_ball.y_pos += the_ball.y_dir;
        the_ball.y_ttg = the_ball.y_ttm;
        moved = 1;
    }

    if(the_ball.x_ttm > 0 && the_ball.x_ttg-- == 1){
        the_ball.x_pos += the_ball.x_dir;
        the_ball.x_ttg = the_ball.x_ttm;
        moved = 1;
    }

    if(moved){
        mvaddch(y_cur,x_cur,BLANK);
        mvaddch(y_cur,x_cur,BLANK);
        mvaddch(the_ball.y_pos,the_ball.x_pos,the_ball.symbol);
        int flag =  bounce_or_lose(&the_ball);
        move(LINES - 1,COLS - 1);
        refresh();
        if(!flag){
            standout();
            mvaddstr((TOP_ROW+BOT_ROW)/2,(LEFT_EDGE+RIGHT_EDGE)/2 - 5,"GAME OVER!");
            standend();
            move(BOT_ROW+2,COLS-1);
            refresh();
            exit(0);
        }
    }
    signal(SIGALRM,ball_move);
}

int bounce_or_lose(struct ppball *bp){
    int return_val = 1;

    if(bp->y_pos == TOP_ROW){
        bp->y_dir = 1;
        return_val = 1;
    }else if(bp->y_pos == BOT_ROW){
        bp->y_dir = -1;
        return_val = 1;
    }

    if(bp->x_pos == LEFT_EDGE){
        bp->x_dir = 1;
        return_val = 1;
    }else if(bp->x_pos == RIGHT_EDGE){
        if(the_barrier.top_y <= bp->y_pos && the_barrier.bot_y >= bp->y_pos)
        {
            bp->x_dir = -1;
            return_val = 1;
        }else{
            return_val = 0;
        }
    }

    return return_val;
}

