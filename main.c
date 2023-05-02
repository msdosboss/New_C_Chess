#include <stdio.h>

int whitekingpst = 4;
int blackkingpst = 60;




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


struct square *lastpiecemoved = NULL;



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

int main(){
    
    int condition = 0;
    int color = 1;
    int flag;
    
    struct square board[8][8] = {
        {{1,1,{5,1,0}},{2,1,{2,1,0}},{3,1,{3,1,0}},{4,1,{9,1,0}},{5,1,{10,1,0}},{6,1,{3,1,0}},{7,1,{2,1,0}},{8,1,{5,1,0}}},
        {{1,2,{1,1,0}},{2,2,1,1,0},{3,2,1,1,0},{4,2,1,1,0},{5,2,1,1,0},{6,2,1,1,0},{7,2,1,1,0},{8,2,1,1,0}},
        {{1,3,0,0,0},{2,3,0,0,0},{3,3,0,0,0},{4,3,0,0,0},{5,3,0,0,0},{6,3,0,0,0},{7,3,0,0,0},{8,3,0,0,0}},
        {{1,4,0,0,0},{2,4,0,0,0},{3,4,0,0,0},{4,4,0,0,0},{5,4,0,0,0},{6,4,{0,0,0}},{7,4,0,0,0},{8,4,0,0,0}},
        {{1,5,0,0,0},{2,5,0,0,0},{3,5,0,0,0},{4,5,0,0,0},{5,5,0,0,0},{5,6,0,0,0},{5,7,0,0,0},{5,8,0,0,0}},
        {{1,6,0,0,0},{2,6,0,0,0},{3,6,0,0,0},{4,6,0,0,0},{5,6,0,0,0},{6,6,0,0,0},{7,6,0,0,0},{8,6,0,0,0}},
        {{1,7,1,-1,0},{2,7,1,-1,0},{3,7,1,-1,0},{4,7,1,-1,0},{5,7,1,-1,0},{6,7,1,-1,0},{7,7,1,-1,0},{8,7,1,-1,0}},
        {{1,8,5,-1,0},{2,8,2,-1,0},{3,8,3,-1,0},{4,8,9,-1,0},{5,8,10,-1,0},{6,8,3,-1,0},{7,8,2,-1,0},{8,8,5,-1,0}}
    };
    struct square *boardpst = NULL;
    boardpst = board;
    lastpiecemoved = board;



    while(condition == 0){
        if(color == 1){
            if(ischeckmate(boardpst, whitekingpst) || isdraw(boardpst, whitekingpst)){
                printf("whitecheckmateflag");
                break;
            }
        }
        else{
            if(ischeckmate(boardpst, blackkingpst) || isdraw(boardpst, blackkingpst)){
                printf("blackcheckmateflag");
                break;

            }

        }
        printboard(boardpst);
        printf("\nColor = %d\n",color);
            while(1){
                flag = (move(boardpst, color));
                if(flag != -1){
                    break;
                }
            }

        color = (color == 1) ? (-1) : (1);

    }
    return 0;

}


void printboard(struct square *boardpst){
    int colorholder;
    for (int i = 0; i < 64; i++){
        if(boardpst[i].piece.color == 1){
            colorholder = 0;
        }
        else if(boardpst[i].piece.color == -1){
            colorholder = 1;
        }
        else{
            colorholder = 0; 
        }
        printf("-%d",(boardpst[i].piece.piece * 10 + colorholder) );
            
        if(boardpst[i].piece.piece == 0){
            putchar('-');
        }

        if((i + 1) % 8 == 0){
            putchar('\n');
        }
    }

}


int getmove(){                          //needs lowercase input maybe fix that later 
    char c;
    int count = 0;
    int offset = 0;
    while((c = getchar()) != EOF && count != 2){
        if(c == 81){                // 81 == 'Q'
            printf("Qflag");
            return -1;
        }
        if(count == 0){
            if(!(c >= 97 && c <= 104)){
                printf("not a valid input1\n");
                return -1;
            }
            offset = offset + (c - 97);
        }
        if(count == 1){
            if(!(c >= 49 && c <= 56)){
                printf("not a valid input2\n");
                return -1;
            }
            offset = offset + ((c - 49) * 8);
        }
        count++;
    }
    return offset;
}

int move(struct square *boardpst, int color){
    printf("select a square to move a piece from: ");
    int currentsquare;
    int orca;
    if(color == 1){
        if(issquareincheck(boardpst,whitekingpst,color)){
            while(1){
                printf("you are in check you must move your king");
                currentsquare = getmove();
                if(boardpst[currentsquare].piece.piece != 10){
                    continue;
                }
                else{
                    return moveking(boardpst, currentsquare);
                }

            }
        }
        
    }
    else{
        if(issquareincheck(boardpst,blackkingpst,color)){
            while(1){
                printf("you are in check you must move your king");
                currentsquare = getmove();
                if(boardpst[currentsquare].piece.piece != 10){
                    continue;
                }
                else{
                    return moveking(boardpst, currentsquare);
                }

            }
        }
    }
    currentsquare = getmove();

    if(boardpst[currentsquare].piece.piece == 1 && boardpst[currentsquare].piece.color == color){
        return movepawn(boardpst, currentsquare);
    }
    if(boardpst[currentsquare].piece.piece == 5 && boardpst[currentsquare].piece.color == color){
        return moverook(boardpst, currentsquare);
    }
    if(boardpst[currentsquare].piece.piece == 3 && boardpst[currentsquare].piece.color == color){
        return movebishop(boardpst, currentsquare);
    }
    if(boardpst[currentsquare].piece.piece == 9 && boardpst[currentsquare].piece.color == color){
        return movequeen(boardpst, currentsquare);
    }
    if(boardpst[currentsquare].piece.piece == 2 && boardpst[currentsquare].piece.color == color){
        return moveknight(boardpst, currentsquare);
    }
    if(boardpst[currentsquare].piece.piece == 10 && boardpst[currentsquare].piece.color == color){
        return moveking(boardpst, currentsquare);
    }
    return -1;
}


int limit(int vert, int hor, struct square *boardpst, int currentsquare){
    int limitx = boardpst[currentsquare].x -1;
    int limity = boardpst[currentsquare].y - 1;
    for(int i = 1; boardpst[currentsquare].x + (i * hor) <= 8 && boardpst[currentsquare].x + (i * hor) >= 1 && boardpst[currentsquare].y + (i * vert) <= 8 && boardpst[currentsquare].y + (i * vert) >= 1   ; i++){

        limitx = boardpst[currentsquare].x + ((i * hor) - 1);
        limity = ((boardpst[currentsquare].y + (i * vert)) - 1);
        if(boardpst[(limity * 8) + limitx].piece.piece > 0 && boardpst[currentsquare].piece.color != boardpst[(limity * 8) + limitx].piece.color){
            break;
        }
        if(boardpst[(limity * 8) + limitx].piece.piece > 0 && boardpst[currentsquare].piece.color == boardpst[(limity * 8) + limitx].piece.color){
            limitx = limitx - (1 * hor);
            limity = limity - (1 * vert);
            break;
        }
    }

    return ((limity * 8) + (limitx));
}

int limitdefend(int vert, int hor, struct square *boardpst, int currentsquare){
    int limitx = boardpst[currentsquare].x -1;
    int limity = boardpst[currentsquare].y - 1;
    for(int i = 1; boardpst[currentsquare].x + (i * hor) <= 8 && boardpst[currentsquare].x + (i * hor) >= 1 && boardpst[currentsquare].y + (i * vert) <= 8 && boardpst[currentsquare].y + (i * vert) >= 1   ; i++){

        limitx = boardpst[currentsquare].x + ((i * hor) - 1);
        limity = ((boardpst[currentsquare].y + (i * vert)) - 1);
        if(boardpst[(limity * 8) + limitx].piece.piece > 0 && boardpst[currentsquare].piece.color != boardpst[(limity * 8) + limitx].piece.color){
            break;
        }
        if(boardpst[(limity * 8) + limitx].piece.piece > 0 && boardpst[currentsquare].piece.color == boardpst[(limity * 8) + limitx].piece.color){
            break;
        }
    }

    return ((limity * 8) + (limitx));
}

int ispawncheck(struct square *boardpst, int currentsquare, int kingsquare){
    if(currentsquare + (7 * boardpst[currentsquare].piece.color) == kingsquare || currentsquare + (9 * boardpst[currentsquare].piece.color) == kingsquare){
        return 1;
    }
    return 0;
}

int isrookcheck(struct square *boardpst, int currentsquare, int kingsquare){
    
    int uplim = limitdefend(1, 0, boardpst, currentsquare);
    int downlim = limitdefend(-1, 0, boardpst, currentsquare);
    int rightlim = limitdefend(0, 1, boardpst, currentsquare);
    int leftlim = limitdefend(0, -1, boardpst, currentsquare);

    if(currentsquare == kingsquare){
        return 0;
    }
    if(boardpst[currentsquare].x == boardpst[kingsquare].x){
            if(kingsquare <= uplim && kingsquare >= downlim){
                return 1;
            }
        }
        else if(boardpst[currentsquare].y == boardpst[kingsquare].y){
            if(kingsquare <= rightlim && kingsquare >= leftlim){
                return 1;
            }
        }
        return 0;
}

int isbishopcheck(struct square *boardpst, int currentsquare, int kingsquare){
    int uprightlim = limitdefend(1, 1, boardpst, currentsquare);
    int downrightlim = limitdefend(-1, 1, boardpst, currentsquare);
    int upleftlim = limitdefend(1, -1, boardpst, currentsquare);
    int downleftlim = limitdefend(-1, -1, boardpst, currentsquare);

    for(int i = 1; currentsquare + (i * 8) + i <= uprightlim || currentsquare - (i * 8) + i >= downrightlim || currentsquare + (i * 8) - i <= upleftlim || currentsquare - (i * 8) - i >= downleftlim; i++){
        if(kingsquare == currentsquare + (i * 8) + i &&  kingsquare <= uprightlim){
            return 1;
        }
        if(kingsquare == currentsquare - (i * 8) + i &&  kingsquare >= downrightlim){
            return 1;
        }
        if(kingsquare == currentsquare + (i * 8) - i &&  kingsquare <= upleftlim){
            return 1;
        }
        if(kingsquare == currentsquare - (i * 8) - i &&  kingsquare >= downleftlim){
            return 1;
        }
    }
    return 0;

}

int isqueencheck(struct square *boardpst, int currentsquare, int kingsquare){
    int uplim = limitdefend(1, 0, boardpst, currentsquare);
    int downlim = limitdefend(-1, 0, boardpst, currentsquare);
    int rightlim = limitdefend(0, 1, boardpst, currentsquare);
    int leftlim = limitdefend(0, -1, boardpst, currentsquare);
    int uprightlim = limitdefend(1, 1, boardpst, currentsquare);
    int downrightlim = limitdefend(-1, 1, boardpst, currentsquare);
    int upleftlim = limitdefend(1, -1, boardpst, currentsquare);
    int downleftlim = limitdefend(-1, -1, boardpst, currentsquare);

    if(boardpst[currentsquare].x == boardpst[kingsquare].x){
            if(kingsquare <= uplim && kingsquare >= downlim){
                return 1;
            }
        }
        else if(boardpst[currentsquare].y == boardpst[kingsquare].y){
            if(kingsquare <= rightlim && kingsquare >= leftlim){
                return 1;
            }
        }
    

    for(int i = 1; currentsquare + (i * 8) + i <= uprightlim || currentsquare - (i * 8) + i >= downrightlim || currentsquare + (i * 8) - i <= upleftlim || currentsquare - (i * 8) - i >= downleftlim; i++){
        if(kingsquare == currentsquare + (i * 8) + i &&  kingsquare <= uprightlim){
            return 1;
        }
        if(kingsquare == currentsquare - (i * 8) + i &&  kingsquare >= downrightlim){
            return 1;
        }
        if(kingsquare == currentsquare + (i * 8) - i &&  kingsquare <= upleftlim){
            return 1;
        }
        if(kingsquare == currentsquare - (i * 8) - i &&  kingsquare >= downleftlim){
            return 1;
        }
    }
    return 0;

}

int isknightcheck(struct square *boardpst, int currentsquare, int kingsquare){
    if(currentsquare == kingsquare + 10 || currentsquare == kingsquare + 6 || currentsquare == kingsquare + 17 || currentsquare == kingsquare + 15 || currentsquare == kingsquare - 6 || currentsquare == kingsquare - 10 || currentsquare == kingsquare - 15 || currentsquare == kingsquare - 17){
        return 1;
    }
    return 0;
}

int iskingcheck(struct square *boardpst, int currentsquare, int kingsquare){
    if((boardpst[currentsquare].x + 1 == boardpst[kingsquare].x || boardpst[currentsquare].x - 1 == boardpst[kingsquare].x || boardpst[currentsquare].x == boardpst[kingsquare].x) && (boardpst[currentsquare].y + 1 == boardpst[kingsquare].y || boardpst[currentsquare].y - 1 == boardpst[kingsquare].y || boardpst[currentsquare].y == boardpst[kingsquare].y)){
        return 1;
    }
    return 0;
}

int issquareincheck(struct square *boardpst, int kingsquare, int color){
    for(int i = 0; i <= 63; i++){
        switch(boardpst[i].piece.piece){
            case(0):
                break;
            case(1):
                if(ispawncheck(boardpst, i, kingsquare) && color != boardpst[i].piece.color){
                    return 1;
                }
                break;
            case(2):
                if(isknightcheck(boardpst, i, kingsquare) && color != boardpst[i].piece.color){
                    return 1;
                }
                break;
            case (3):
                if(isbishopcheck(boardpst, i, kingsquare) && color != boardpst[i].piece.color){
                    return 1;
                }
                break;
            case (5):
                if(isrookcheck(boardpst, i, kingsquare) && color != boardpst[i].piece.color){
                    return 1;
                }
                break;
            case(9):
                if(isqueencheck(boardpst, i, kingsquare) && color != boardpst[i].piece.color){
                    return 1;
                }
                break;
            case(10):
                if(isqueencheck(boardpst, i, kingsquare) && color != boardpst[i].piece.color){
                    return 1;
                }
                break;

        }
    }
    return 0;
}

int ischeckmate(struct square *boardpst, int kingsquare){
    int flag = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(kingsquare + (i * 8) + j > 0 && kingsquare + (i * 8) + j < 63){
                if(boardpst[kingsquare + (i * 8) + j].piece.color == boardpst[kingsquare].piece.color){
                    if(kingsquare + (i * 8) + j == kingsquare){

                    }
                    else{
                        flag = flag + 1;
                        continue;
                    }
                }
                if(issquareincheck(boardpst, kingsquare + (i * 8) + j, boardpst[kingsquare].piece.color)){
                    flag = flag + 1;
                }
            }
            else{
                flag = flag + 1;
            }
        }
    }
    if(flag > 8){
        return 1;
    }
    return 0;
    
}

int isdraw(struct square *boardpst, int kingsquare){
    int flag = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(kingsquare == kingsquare + (i * 8) + j){
                continue;
            }
            if(kingsquare + (i * 8) + j > 0 && kingsquare + (i * 8) + j < 63){
                if(issquareincheck(boardpst, kingsquare + (i * 8) + j, boardpst[kingsquare].piece.color)){
                    flag = flag + 1;
                }
            }
            else{
                flag = flag + 1;
            }
        }
    }
    if(flag > 7){
        return 1;
    }
    return 0;
    
}

void makemove(struct square *boardpst, int currentsquare, int square){
    boardpst[currentsquare].piece.totalmoves++;
    boardpst[square].piece = boardpst[currentsquare].piece;
    boardpst[currentsquare].piece.piece = 0;
    boardpst[currentsquare].piece.color = 0;
    lastpiecemoved = &boardpst[square].piece;

}


int movepawn(struct square *boardpst, int currentsquare){
    printf("where would you like to move your pawn that is on offset %d: ?", currentsquare);
    int i = 0;
    int flag = 0;
    int square;
    while(1){
        square = getmove();
        if(square == -1){
            return -1;
        }
        
        if(square == currentsquare + (8 * boardpst[currentsquare].piece.color) || square == currentsquare + (16 * boardpst[currentsquare].piece.color)){
            if(square == currentsquare + (16 * boardpst[currentsquare].piece.color) && boardpst[currentsquare].piece.totalmoves > 0){
                printf("move not valid try again1");
                continue;
            }
            while(currentsquare + (i * boardpst[currentsquare].piece.color) != square + (8 * boardpst[currentsquare].piece.color)){
                if(boardpst[currentsquare + (i * boardpst[currentsquare].piece.color)].piece.piece != 0 && i != 0){
                    flag = 1;
                }
                i = i + 8;
            }
            if(flag == 0){
                makemove(boardpst, currentsquare, square);
                break;
            }
            else{
                continue;
            }
        }
        else if((square == currentsquare + (7 * boardpst[currentsquare].piece.color) || square == currentsquare + (9 * boardpst[currentsquare].piece.color)) && ((boardpst[currentsquare].piece.color != boardpst[square].piece.color && boardpst[square].piece.piece > 0) || (boardpst[currentsquare + (1)].piece.piece == 1 && boardpst[currentsquare + (1)].piece.totalmoves == 1 && boardpst[currentsquare + (1)].piece.color != boardpst[currentsquare].piece.color && lastpiecemoved == &boardpst[currentsquare + 1].piece) || (boardpst[currentsquare - (1)].piece.piece == 1 && boardpst[currentsquare - (1)].piece.totalmoves == 1 && boardpst[currentsquare - (1)].piece.color != boardpst[currentsquare].piece.color && lastpiecemoved == &boardpst[currentsquare - 1].piece))){
            if((boardpst[currentsquare + (1)].piece.piece == 1 && boardpst[currentsquare + (1)].piece.totalmoves == 1 && boardpst[currentsquare + (1)].piece.color != boardpst[currentsquare].piece.color && lastpiecemoved == &boardpst[currentsquare + 1].piece) || (boardpst[currentsquare - 1].piece.piece == 1 && boardpst[currentsquare - 1].piece.totalmoves == 1 && boardpst[currentsquare - 1].piece.color != boardpst[currentsquare].piece.color && lastpiecemoved == &boardpst[currentsquare - 1].piece)){
                printf("orca\n");
                boardpst[currentsquare].piece.totalmoves++;
                boardpst[square].piece = boardpst[currentsquare].piece;
                boardpst[square - (8 * boardpst[currentsquare].piece.color)].piece.piece = 0;
                boardpst[square - (8 * boardpst[currentsquare].piece.color)].piece.color = 0;
                boardpst[currentsquare].piece.piece = 0;
                boardpst[currentsquare].piece.color = 0;
                break;
            }
            makemove(boardpst, currentsquare, square);
            break;
        }
        else{
            printf("move not valid try again2");
            continue; 
        }
    }
    return 0;
}


int moverook(struct square *boardpst, int currentsquare){    
    int square;
    
    int uplim = limit(1, 0, boardpst, currentsquare);
    int downlim = limit(-1, 0, boardpst, currentsquare);
    int rightlim = limit(0, 1, boardpst, currentsquare);
    int leftlim = limit(0, -1, boardpst, currentsquare);

    while(1){
        printf("where would you like to move your rook that is on offset %d: ?", currentsquare);
        square = getmove();
        if(square == -1){
            return -1;
        }
        if(boardpst[currentsquare].x == boardpst[square].x){
            if(square <= uplim && square >= downlim){
                makemove(boardpst, currentsquare, square);
                break;
            }
        }
        else if(boardpst[currentsquare].y == boardpst[square].y){
            if(square <= rightlim && square >= leftlim){
                makemove(boardpst, currentsquare, square);
                break;
            }
        }
        else{
            printf("not a possible move");
            continue;
        }
    }
    
    
    return 0;
}

int movebishop(struct square *boardpst, int currentsquare){
    int square;
    
    int uprightlim = limit(1, 1, boardpst, currentsquare);
    int downrightlim = limit(-1, 1, boardpst, currentsquare);
    int upleftlim = limit(1, -1, boardpst, currentsquare);
    int downleftlim = limit(-1, -1, boardpst, currentsquare);

    while(1){
        printf("where would you like to move your bishop that is on offset %d: ?", currentsquare);
        square = getmove();
        if(square == -1){
            return -1;
        }
        for(int i = 1; currentsquare + (i * 8) + i <= uprightlim || currentsquare - (i * 8) + i >= downrightlim || currentsquare + (i * 8) - i <= upleftlim || currentsquare - (i * 8) - i >= downleftlim; i++){
            
            if(square == currentsquare + (i * 8) + i &&  square <= uprightlim){
                makemove(boardpst, currentsquare, square);
                return 0;
            }
            if(square == currentsquare - (i * 8) + i &&  square >= downrightlim){
                makemove(boardpst, currentsquare, square);
                return 0;
            }
            if(square == currentsquare + (i * 8) - i &&  square <= upleftlim){
                makemove(boardpst, currentsquare, square);
                return 0;
            }
            if(square == currentsquare - (i * 8) - i &&  square >= downleftlim){
                makemove(boardpst, currentsquare, square);
                return 0;
            }
        }
        printf("not a valid move");
    }
    return 0;
}

int movequeen(struct square *boardpst, int currentsquare){
    int square;
    
    int uprightlim = limit(1, 1, boardpst, currentsquare);
    int downrightlim = limit(-1, 1, boardpst, currentsquare);
    int upleftlim = limit(1, -1, boardpst, currentsquare);
    int downleftlim = limit(-1, -1, boardpst, currentsquare);
    int uplim = limit(1, 0, boardpst, currentsquare);
    int downlim = limit(-1, 0, boardpst, currentsquare);
    int rightlim = limit(0, 1, boardpst, currentsquare);
    int leftlim = limit(0, -1, boardpst, currentsquare);

    int flag = 0;
    while(1){
        printf("where would you like to move your queen that is on offset %d: ?", currentsquare);
        square = getmove();

        if(square == -1){
            return -1;
        }

        while(1){

            if(boardpst[currentsquare].x == boardpst[square].x){
                if(square <= uplim && square >= downlim){
                    makemove(boardpst, currentsquare, square);
                    return 0;
                }
            }
            else if(boardpst[currentsquare].y == boardpst[square].y){
                if(square <= rightlim && square >= leftlim){
                    makemove(boardpst, currentsquare, square);
                    return 0;
                }
            }
            else{
                break;
            }
        }
        while(1){

            for(int i = 1; currentsquare + (i * 8) + i <= uprightlim || currentsquare - (i * 8) + i >= downrightlim || currentsquare + (i * 8) - i <= upleftlim || currentsquare - (i * 8) - i >= downleftlim; i++){
            
                if(square == currentsquare + (i * 8) + i &&  square <= uprightlim){
                    makemove(boardpst, currentsquare, square);
                    return 0;
                }
                if(square == currentsquare - (i * 8) + i &&  square >= downrightlim){
                    makemove(boardpst, currentsquare, square);
                    return 0;
                }
                if(square == currentsquare + (i * 8) - i &&  square <= upleftlim){
                    makemove(boardpst, currentsquare, square);
                    return 0;
                }
                if(square == currentsquare - (i * 8) - i &&  square >= downleftlim){
                    makemove(boardpst, currentsquare, square);
                    return 0;
                }
            }
            break;
        }
        printf("Not a valid move try again\n");
    }
}

int moveknight(struct square *boardpst, int currentsquare){
    int square;

    while(1){
        printf("where would you like to move your knight that is on offset %d: ?", currentsquare);
        square = getmove();

        if(currentsquare == square + 10 || currentsquare == square + 6 || currentsquare == square + 17 || currentsquare == square + 15 || currentsquare == square - 6 || currentsquare == square - 10 || currentsquare == square - 15 || currentsquare == square - 17){
            makemove(boardpst, currentsquare, square);
            return 0;
        }
        printf("Not a valid move try again\n");
    }
}

int moveking(struct square *boardpst, int currentsquare){
    int square;
    
    while(1){
        printf("where would you like to move your king that is on offset %d: ?", currentsquare);
        square = getmove();
        if(issquareincheck(boardpst, square, boardpst[currentsquare].piece.color)){
            printf("that move would put you in check not a legal move");
        }
        else{
            if(boardpst[currentsquare].piece.totalmoves == 0 && boardpst[currentsquare + 3].piece.totalmoves == 0 && currentsquare + 2 == square && boardpst[currentsquare + 1].piece.piece == 0 && boardpst[currentsquare + 2].piece.piece == 0 && !issquareincheck(boardpst,currentsquare + 1,boardpst[currentsquare].piece.color) && !issquareincheck(boardpst,currentsquare + 2,boardpst[currentsquare].piece.color)){
                if(boardpst[currentsquare].piece.color == 1){
                    whitekingpst = square;
                }
                else{
                    blackkingpst = square;
                }
                makemove(boardpst, currentsquare, square);
                makemove(boardpst, currentsquare + 3, square - 1);
                return 0;
            }
            if(boardpst[currentsquare].piece.totalmoves == 0 && boardpst[currentsquare - 4].piece.totalmoves == 0 && currentsquare - 2 == square && boardpst[currentsquare - 1].piece.piece == 0 && boardpst[currentsquare - 2].piece.piece == 0 && boardpst[currentsquare - 3].piece.piece == 0 && !issquareincheck(boardpst,currentsquare - 1,boardpst[currentsquare].piece.color) && !issquareincheck(boardpst,currentsquare - 2,boardpst[currentsquare].piece.color) && !issquareincheck(boardpst,currentsquare - 3,boardpst[currentsquare].piece.color)){
                if(boardpst[currentsquare].piece.color == 1){
                    whitekingpst = square;
                }
                else{
                    blackkingpst = square;
                }
                makemove(boardpst, currentsquare, square);
                makemove(boardpst, currentsquare + 3, square - 1);
                return 0;
            }
            if((boardpst[currentsquare].x + 1 == boardpst[square].x || boardpst[currentsquare].x - 1 == boardpst[square].x || boardpst[currentsquare].x == boardpst[square].x) && (boardpst[currentsquare].y + 1 == boardpst[square].y || boardpst[currentsquare].y - 1 == boardpst[square].y || boardpst[currentsquare].y == boardpst[square].y) && (boardpst[square].piece.piece == 0 || boardpst[square].piece.color != boardpst[currentsquare].piece.color)){
                if(boardpst[currentsquare].piece.color == 1){
                    whitekingpst = square;
                }
                else{
                    blackkingpst = square;
                }
                makemove(boardpst, currentsquare, square);
                return 0;
            }
            printf("not a valid move\n");
        }
    }
}






