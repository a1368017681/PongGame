#ifndef _BOUNCE_H_
#define _BOUNCE_H_

#define BLANK  ' '
#define WALL 'x'
#define DFL_SYMBOL  'o'
#define RULE "f:speedup in x_dir,F:speedup in y_dir,s:slow in x_dir,S:slow in y_dir"
#define TOP_ROW  5
#define BOT_ROW  20
#define LEFT_EDGE  10
#define RIGHT_EDGE  70
#define X_INIT  10
#define Y_INIT  10
#define TICKS_PER_SEC  150
#define X_TTM  5
#define Y_TTM  8
struct ppball{
    int y_pos,x_pos;
    int y_ttm,x_ttm;
    int y_ttg,x_ttg;
    int y_dir,x_dir;
    char symbol;
};

struct barrier{
    int top_x,top_y;
    int bot_x,bot_y;
    int dir;
    char symbol;
};

#endif
