#ifndef MOVE_H
#define MOVE_H
#include"stack.h"
#include<stdlib.h>
#include<math.h>
#define ROW 9
#define COLUMN 9
#define player1 "\033[1;34mPlayer1\033[m"
#define player2 "\033[1;31mPlayer2\033[m"

short IsStandard = 1;//是否符合規則，初始值1，符合
short restart = 0;//是否重新輸入，1:是
short WrongPlayer = 0;//1: 下對方的棋
int regret = 0;//1:悔棋
char xi;//輸入的x座標
int xj, yi, yj;//輸入的座標
int x0, x1, Y0, Y1;
short turn;//1:player1, -1:player2
int Write = 0;
int amount;

Item *tmp;

FILE *fp;

void BlueMove();
void RedMove();
void RulesOfAllKindsOfPiece();

enum name {
    osho = 1, hisha, kakugyou, kinshou, ginshou, keima, kyousha, fuhyo
};
enum player {
    blue = 1, red
};

Piece board[ROW][COLUMN];//棋盤

void BlueMove(){
    printf("top = %d\n", top);
    if(restart){
        if(WrongPlayer == 1){
            printf("\033[1;33m不可以下別人的棋\033[m\n");
            WrongPlayer = 0;
            restart = 0;    
        }else{
            printf("\033[1;33m違反規則，請從新輸入\033[m\n");
            restart = 0;
        }
        
    }
    printf("%s請輸入你要移動的棋子:(若%s想悔棋請輸入0，存檔則輸入s或S)\n", player1, player2);
    scanf(" %c", &xi);
    if(xi - '0' == 0){
        printf("是否悔棋?(1:是，其他:否)\n");//是否悔棋
        scanf("%d", &regret);
        if(regret == 1){
            if(IsEmpty()){
                printf("\033[1;33m已為初始狀態，無法悔棋!\033[m\n");
                turn *= -1;
            }else{
                tmp = (Item*)pop();
                board[tmp->position0[0]][tmp->position0[1]] = tmp->p0;
                board[tmp->position1[0]][tmp->position1[1]] = tmp->p1;
            }
        }else{
            printf("%s請輸入你要移動的棋子:\n", player1);
            scanf(" %c %d", &xi, &yi);
            if(((xi - '0') > COLUMN) || (yi > ROW) || ((xi - '0') < 1) || (yi < 1)){
                restart = 1;
            }
            Y0 = yi - 1;
            x0 = 9 - (xi - '0');
            if(board[Y0][x0].color != blue){
                WrongPlayer = 1;
            }
            printf("%s請輸入你要放的位置\n", player1);
            scanf("%d %d", &xj, &yj);
            if((xj > COLUMN) || (yj > ROW) || (xj < 1) || (yj < 1)){
                restart = 1;
            }
            Y1 = yj - 1;
            x1 = 9 - xj;
            RulesOfAllKindsOfPiece();
        }
    }else{
        printf("hey\n");
        if(xi == 's' || xi == 'S'){
            for(Write = 0; Write < top + 1; Write++){
                amount += 1;
                fprintf(fp, "%d %d %d %d %d %d %d %d %d\n", amount, stack[Write].p0.id, stack[Write].p0.color, stack[Write].p1.id, stack[Write].p1.color, stack[Write].position0[0], stack[Write].position0[1], stack[Write].position1[0], stack[Write].position1[1]);
                printf("Write = %d\n", Write);
            }
            Write = top;
            printf("\033[1;33m儲存成功!\033[m!\n");
            printf("%s請輸入你要移動的棋子:\n", player1);
            scanf(" %c %d",&xi, &yi);
            if(((xi - '0') > COLUMN) || (yi > ROW) || ((xi - '0') < 1) || (yi < 1)){
                restart = 1;
            }
            Y0 = yi - 1;
            x0 = 9 - (xi - '0');
            if(board[Y0][x0].color != blue){
                WrongPlayer = 1;
            }
            printf("%s請輸入你要放的位置\n", player1);
            scanf("%d %d", &xj, &yj);
            if((xj > COLUMN) || (yj > ROW) || (xj < 1) || (yj < 1)){
                restart = 1;
            }
            Y1 = yj - 1;
            x1 = 9 - xj;
            RulesOfAllKindsOfPiece();
        }else{
            scanf("%d", &yi);
            if(((xi - '0') > COLUMN) || (yi > ROW) || ((xi - '0') < 1) || (yi < 1)){
                restart = 1;
            }
            Y0 = yi - 1;
            x0 = 9 - (xi - '0');
            if(board[Y0][x0].color != blue){
                WrongPlayer = 1;
            }
            printf("%s請輸入你要放的位置\n", player1);
            scanf("%d %d", &xj, &yj);
            if((xj > COLUMN) || (yj > ROW) || (xj < 1) || (yj < 1)){
                restart = 1;
            }
            Y1 = yj - 1;
            x1 = 9 - xj;
            RulesOfAllKindsOfPiece();
        }        
    }
}

void RedMove(){
    printf("top = %d\n", top);
    if(restart){
        if(WrongPlayer == 1){
            printf("\033[1;33m不可以下別人的棋\033[m\n");
            WrongPlayer = 0;
            restart = 0;    
        }else{
            printf("\033[1;33m違反規則，請從新輸入\033[m\n");
            restart = 0;
        }
    }
    printf("%s請輸入你要移動的棋子:(若%s想悔棋請輸入0，存檔則輸入s或S)\n", player2, player1);
    scanf(" %c", &xi);
    if((xi - '0') == 0){
        printf("是否悔棋?(1:是，其他:否)\n");//是否悔棋
        scanf("%d", &regret);
        if(regret == 1){
            if(IsEmpty()){
                printf("\033[1;33m已為初始狀態，無法悔棋!\033[m\n");
                turn *= -1;
            }else{
                tmp = (Item*)pop();
                board[tmp->position0[0]][tmp->position0[1]] = tmp->p0;
                board[tmp->position1[0]][tmp->position1[1]] = tmp->p1;
            }
        }else{
            printf("%s請輸入你要移動的棋子:\n", player2);
            scanf(" %c %d",&xi, &yi);
            if(((xi - '0') > COLUMN) || (yi > ROW) || ((xi - '0') < 1) || (yi < 1)){
                restart = 1;
            }
            Y0 = yi - 1;
            x0 = 9 - (xi - '0');
            if(board[Y0][x0].color != red){
                WrongPlayer = 1;
            }
            printf("%s請輸入你要放的位置\n", player2);
            scanf("%d %d", &xj, &yj);
            if((xj > COLUMN) || (yj > ROW) || (xj < 1) || (yj < 1)){
                restart = 1;
            }
            Y1 = yj - 1;
            x1 = 9 - xj;
            RulesOfAllKindsOfPiece();
        }
    }else{
        printf("hi\n");
        if(xi == 's' || xi == 'S'){
            for(Write = 0; Write < top + 1; Write++){
                amount += 1;
                fprintf(fp, "%d %d %d %d %d %d %d %d %d\n", amount, stack[Write].p0.id, stack[Write].p0.color, stack[Write].p1.id, stack[Write].p1.color, stack[Write].position0[0], stack[Write].position0[1], stack[Write].position1[0], stack[Write].position1[1]);
                printf("Write = %d\n", Write);
            }
            Write = top;
            printf("\033[1;33m儲存成功!\033[m!\n");
            printf("%s請輸入你要移動的棋子:\n", player2);
            scanf(" %c %d",&xi, &yi);
            if(((xi - '0') > COLUMN) || (yi > ROW) || ((xi - '0') < 1) || (yi < 1)){
                restart = 1;
            }
            Y0 = yi - 1;
            x0 = 9 - (xi - '0');
            if(board[Y0][x0].color != red){
                WrongPlayer = 1;
            }
            printf("%s請輸入你要放的位置\n", player2);
            scanf("%d %d", &xj, &yj);
            if((xj > COLUMN) || (yj > ROW) || (xj < 1) || (yj < 1)){
                restart = 1;
            }
            Y1 = yj - 1;
            x1 = 9 - xj;
            RulesOfAllKindsOfPiece();
        }else{
            scanf("%d", &yi);
            if(((xi - '0') > COLUMN) || (yi > ROW) || ((xi - '0') < 1) || (yi < 1)){
                restart = 1;
            }
            Y0 = yi - 1;
            x0 = 9 - (xi - '0');
            if(board[Y0][x0].color != red){
                WrongPlayer = 1;
            }
            printf("%s請輸入你要放的位置\n", player2);
            scanf("%d %d", &xj, &yj);
            if((xj > COLUMN) || (yj > ROW) || (xj < 1) || (yj < 1)){
                restart = 1;
            }
            Y1 = yj - 1;
            x1 = 9 - xj;
            RulesOfAllKindsOfPiece();
        }
    }
}

void RulesOfAllKindsOfPiece(){
    if(WrongPlayer){
        restart = 1;
    }
    //王將
    else if(board[Y0][x0].id == osho){
        if (((abs(x0 - x1) == 1) && (abs(Y0 - Y1) == 1)) || ((abs(x0 - x1) == 1) && (Y0 == Y1)) || ((x0 == x1) && (abs(Y0 - Y1) == 1))) {
            if((board[Y0][x0].color == blue) && (board[Y1][x1].color != blue)){
                push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);
                
                board[Y1][x1] = board[Y0][x0];
                board[Y0][x0].id = 0;
                board[Y0][x0].color = 0;
            }else if((board[Y0][x0].color == red) && (board[Y1][x1].color != red)){
                push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);

                board[Y1][x1] = board[Y0][x0];
                board[Y0][x0].id = 0;
                board[Y0][x0].color = 0;
            }else{
                restart = 1;
            }
        }
        else {
            restart = 1;
        }
    }
    //飛車
    else if(board[Y0][x0].id == hisha){
        if(x0 == x1){//直著走
            printf("2\n");
            for(i = Y0 + 1; i < Y1; i++){
                if(board[i][x0].id != 0){
                    IsStandard = 0;
                }
            }
            for(i = Y0 - 1; i > Y1; i--){
                if(board[i][x0].id != 0){
                    IsStandard = 0;
                }
            }
        }else if(Y0 == Y1){//橫著走
            for(i = x0 + 1; i < x1; i++){
                if(board[Y0][i].id != 0){
                    IsStandard = 0;
                }
            }
            for(i = x0 - 1; i > x1; i--){
                if(board[Y0][i].id != 0){
                    IsStandard = 0;
                }
            }
        }else{
            IsStandard = 0;
        }

        if((board[Y0][x0].color == blue) && IsStandard && (board[Y1][x1].color != blue)){
            push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);

            board[Y1][x1] = board[Y0][x0];
            board[Y0][x0].id = 0;
            board[Y0][x0].color = 0;
        }else if((board[Y0][x0].color == red) && IsStandard && (board[Y1][x1].color != red)){
            push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);
            
            board[Y1][x1] = board[Y0][x0];
            board[Y0][x0].id = 0;
            board[Y0][x0].color = 0;
        }else{
            restart = 1;
        }
    }
    //角形
    else if(board[Y0][x0].id == kakugyou){
        if(x1 == x0){
            restart = 1;
        }else{
            if(((float)Y1 - (float)Y0) / ((float)x1 - (float)x0) == 1){
                for(i = x0 + 1, j = Y0 + 1; i < x1; i++, j++){
                    if(board[j][i].id != 0){
                        IsStandard = 0;
                    }
                }

                for(i = x0 - 1, j = Y0 - 1; i > x1; i--, j--){
                    if(board[j][i].id != 0){
                        IsStandard = 0;
                    }
                }
            }else if(((float)Y1 - (float)Y0) / ((float)x1 - (float)x0) == -1){
                for(i = x0 + 1, j = Y0 - 1; i < x1; i++, j--){
                    if(board[j][i].id != 0){
                        IsStandard = 0;
                    }
                }

                for(i = x0 - 1, j = Y0 + 1; i > x1; i--, j++){
                    if(board[j][i].id != 0){
                        IsStandard = 0;
                    }
                }
            }else{
                IsStandard = 0;
            }

            if((board[Y0][x0].color == blue) && IsStandard && (board[Y1][x1].color != blue)){
                push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);
                
                board[Y1][x1] = board[Y0][x0];
                board[Y0][x0].id = 0;
                board[Y0][x0].color = 0;
            }else if((board[Y0][x0].color == red) && IsStandard && (board[Y1][x1].color != red)){
                push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);
                
                board[Y1][x1] = board[Y0][x0];
                board[Y0][x0].id = 0;
                board[Y0][x0].color = 0;
            }else{
                restart = 1;
            }
        }
    }
    //金將
    else if(board[Y0][x0].id == kinshou){
        if(board[Y0][x0].color == blue){
            if((((abs(x1 - x0) == 1) && (Y1 == Y0)) || ((abs(x1 - x0) == 1) && (Y0 - Y1 == 1)) || ((abs(Y1 - Y0) == 1) && (x1 == x0))) && (board[Y1][x1].color != blue)){
                push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);
                
                board[Y1][x1] = board[Y0][x0];
                board[Y0][x0].id = 0;
                board[Y0][x0].color = 0;
            }else{
                restart = 1;
            }
        }else if(board[Y0][x0].color == red){
            if((((abs(x1 - x0) == 1) && (Y1 == Y0)) || ((abs(x1 - x0) == 1) && (Y0 - Y1 == -1)) || ((abs(Y1 - Y0) == 1) && (x1 == x0))) && (board[Y1][x1].color != red)){
                push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);
                
                board[Y1][x1] = board[Y0][x0];
                board[Y0][x0].id = 0;
                board[Y0][x0].color = 0;
            }else{
                restart = 1;
            }
        }
    }
    //銀將
    else if(board[Y0][x0].id == ginshou){
        if (((abs(x0 - x1) == 1 && (abs(Y0 - Y1) == 1)) || ((x0 = x1) && (Y0 - Y1 == -1))) && (board[Y0][x0].color == red)){
            if(board[Y1][x1].color != red){
                push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);
                
                board[Y1][x1] = board[Y0][x0];
                board[Y0][x0].id = 0;
                board[Y0][x0].color = 0;
            }else{
                restart = 1;
            }
        }else if(((abs(x0 - x1) == 1 && (abs(Y0 - Y1) == 1)) || ((x0 = x1) && (Y0 - Y1 == 1))) && (board[Y0][x0].color == blue)){
            if(board[Y1][x1].color != blue){
                push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);
                
                board[Y1][x1] = board[Y0][x0];
                board[Y0][x0].id = 0;
                board[Y0][x0].color = 0;
            }else{
                restart = 1;
            }
        }else{
            restart = 1;
        }
    }
    //桂馬
    else if(board[Y0][x0].id == keima){
        if ((abs(x0 - x1) == 1) && (Y1 - Y0 == 2) && (board[Y0][x0].color == red)){
            if(board[Y1][x1].color != red){
                push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);
                
                board[Y1][x1] = board[Y0][x0];
                board[Y0][x0].id = 0;
                board[Y0][x0].color = 0;
            }else{
                restart = 1;
            }
        }else if((abs(x0 - x1) == 1) && (Y1 - Y0 == -2) && (board[Y0][x0].color == blue)){
            if(board[Y1][x1].color != blue){
                push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);
                
                board[Y1][x1] = board[Y0][x0];
                board[Y0][x0].id = 0;
                board[Y0][x0].color = 0;
            }else{
                restart = 1;
            }
        }else{
            restart = 1;
        }
    }
    //香車
    else if(board[Y0][x0].id == kyousha){
        if((x0 == x1)){
            if((board[Y0][x0].color == blue) && (Y0 > Y1)){
                for(i = Y0 - 1; i > Y1; i--){
                    if(board[i][x0].id != 0){
                        IsStandard = 0;
                    }
                }
                
                if((board[Y1][x1].color != blue) && IsStandard){
                    push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);
                    
                    board[Y1][x1] = board[Y0][x0];
                    board[Y0][x0].id = 0;
                    board[Y0][x0].color = 0;
                }else{
                    restart = 1;
                }
            }else if((board[Y0][x0].color == red) && (Y0 < Y1)){
                for(i = Y0 + 1; i < Y1; i++){
                    if(board[i][x0].id != 0){
                        IsStandard = 0;
                    }
                }

                if((board[Y1][x1].color != red) && IsStandard){
                    push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);
                    
                    board[Y1][x1] = board[Y0][x0];
                    board[Y0][x0].id = 0;
                    board[Y0][x0].color = 0;
                }else{
                    restart = 1;
                }
            }else{
                restart = 1;
            }
        }else{
            restart = 1;
        }
    }
    //步兵
    else if(board[Y0][x0].id == fuhyo){
        if(x1 == x0){
            if((board[Y0][x0].color == blue) && (Y0 - Y1 == 1)){
                if(board[Y1][x1].color != blue){
                    push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);
                    
                    board[Y1][x1] = board[Y0][x0];
                    board[Y0][x0].id = 0;
                    board[Y0][x0].color = 0;
                }else{
                    restart = 1;
                }
            }else if((board[Y0][x0].color == red) && (Y1 - Y0 == 1)){
                if(board[Y1][x1].color != red){
                    push(&(board[Y0][x0]), &(board[Y1][x1]), x0, Y0, x1, Y1);
                    
                    board[Y1][x1] = board[Y0][x0];
                    board[Y0][x0].id = 0;
                    board[Y0][x0].color = 0;
                }else{
                    restart = 1;
                }
            }else{
                restart = 1;
            }
        }else{
            restart = 1;
        }
    }
    //空白
    else{
        restart = 1;
    }
}

#endif