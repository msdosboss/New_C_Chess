#if !defined CHESS_FUNC


struct piecestruc {
        int piece;
        int color;
        int totalmoves
    };

    struct square {
    int x;
    int y;
    struct piecestruc piece;      
    };






void printboard(struct square*);
int getmove();
int move(struct square*, int);
void makemove(struct square*, int, int);
int limit(int, int, struct square*, int);
int movepawn(struct square*, int);
int moverook(struct square*, int);
int movebishop(struct square*, int);
int movequeen(struct square*, int);
int moveknight(struct square*, int);
int moveking(struct square*, int);
int ispawncheck(struct square*, int, int);
int isrookcheck(struct square*, int, int);
int isbishopcheck(struct square*, int, int);
int isqueencheck(struct square*, int, int);
int isknightcheck(struct square*, int, int);
int iskingcheck(struct square*, int, int);
int issquareincheck(struct square*, int, int);
int ischeckmate(struct square*, int);
int limitdefend(int, int, struct square*, int);




#endif
#define CHESS_FUNC 1