#include <stdio.h>


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
        {{1,6,0,0,0},{2,6,0,0,0},{3,6,0,0,0},{4,6,1,1,0},{5,6,0,0,0},{6,6,0,0,0},{7,6,0,0,0},{8,6,0,0,0}},
        {{1,7,1,-1,0},{2,7,1,-1,0},{3,7,1,-1,0},{4,7,1,-1,0},{5,7,1,-1,0},{6,7,1,-1,0},{7,7,1,-1,0},{8,7,1,-1,0}},
        {{1,8,5,-1,0},{2,8,2,-1,0},{3,8,3,-1,0},{4,8,9,-1,0},{5,8,10,-1,0},{6,8,3,-1,0},{7,8,2,-1,0},{8,8,5,-1,0}}
    };
    struct square *boardpst = NULL;
    boardpst = board;

    while(condition == 0){
        printf("\nColor = %d\n",color);
            while(1){
                flag = (move(boardpst, color));
                if(flag != -1){
                    break;
                }
            }
        printboard(boardpst);

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
    int currentsquare = getmove();
    int orca;
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

void makemove(struct square *boardpst, int currentsquare, int square){
    boardpst[currentsquare].piece.totalmoves++;
    boardpst[square].piece = boardpst[currentsquare].piece;
    boardpst[currentsquare].piece.piece = 0;
    boardpst[currentsquare].piece.color = 0;
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
        else if((square == currentsquare + (7 * boardpst[currentsquare].piece.color) || square == currentsquare + (9 * boardpst[currentsquare].piece.color)) && boardpst[currentsquare].piece.color != boardpst[square].piece.color && boardpst[square].piece.piece > 0){
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

    int flag = 0;

    while(1){
        printf("where would you like to move your bishop that is on offset %d: ?", currentsquare);
        square = getmove();
        if(square == -1){
            return -1;
        }
        for(int i = 1; currentsquare + (i * 8) + i <= uprightlim || currentsquare - (i * 8) + i >= downrightlim || currentsquare + (i * 8) - i <= upleftlim || currentsquare - (i * 8) - i <= downleftlim; i++){
            
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

            for(int i = 1; currentsquare + (i * 8) + i <= uprightlim || currentsquare - (i * 8) + i >= downrightlim || currentsquare + (i * 8) - i <= upleftlim || currentsquare - (i * 8) - i <= downleftlim; i++){
            
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

        if((boardpst[currentsquare].x + 1 == boardpst[square].x || boardpst[currentsquare].x - 1 == boardpst[square].x || boardpst[currentsquare].x == boardpst[square].x) && (boardpst[currentsquare].y + 1 == boardpst[square].y || boardpst[currentsquare].y - 1 == boardpst[square].y || boardpst[currentsquare].y == boardpst[square].y) && (boardpst[square].piece.piece == 0 || boardpst[square].piece.color != boardpst[currentsquare].piece.color)){
            makemove(boardpst, currentsquare, square);
            return 0;
        }
        printf("not a valid move\n");
    }
}






