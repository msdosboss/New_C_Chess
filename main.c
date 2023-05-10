#include <stdio.h>
#include "chess_func.h"




int whitekingpst = 4;
int blackkingpst = 60;

struct square (*lastpiecemoved)[8] = NULL;


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


