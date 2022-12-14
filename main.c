#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"move.h"
#define B(Piece) "\033[1;34m"#Piece"\033[m"
#define R(Piece) "\033[1;31m"#Piece"\033[m"

/*棋盤長這樣:
先段(行)再筋(列)
 ９ ８ ７ ６ ５ ４ ３ ２ １
|香 桂 銀 金 玉 金 銀 桂 香|1
|　 飛 　 　 　 　 　 角 　|2
|步 步 步 步 步 步 步 步 步|3
|　 　 　 　 　 　 　 　 　|4
|　 　 　 　 　 　 　 　 　|5
|　 　 　 　 　 　 　 　 　|6
|步 步 步 步 步 步 步 步 步|7
|　 角 　 　 　 　 　 飛 　|8
|香 桂 銀 金 玉 金 銀 桂 香|9
*/

void initialize();
void printboard();
void IsGameOver();

short WhoWin = 0;//0: 遊戲繼續 1:player1 win, -1:player2 win 
int Read = -1;
const int zero = 0;
int counter = -1;

char FOrB;

int NewOrOld = -1;//1:開新檔，0:開舊檔
char *filename;

struct piece board[ROW][COLUMN];


int main(int argc, char **argv) {
    
    int ch;
    while((ch = getopt(argc, argv, "ns:l:")) != 1){
        switch(ch){
            case 'n':
                printf("n\n");
                NewOrOld = 1;
                break;
            case 's':
                printf("s\n");
                filename = optarg;
                printf("filename = %s\n", filename);
                if(NewOrOld == 1){
                    fp = NULL;
                    printf("NewOrOld = %d\n", NewOrOld);
                    if((fp = fopen(filename, "w")) == NULL){
                        printf("\033[1;31m無法創建檔案!\033[m");
                        return 0;
                    }else{
                        initialize();
                        while(WhoWin == 0 && tie == 0){
                            IsStandard = 1;
                            printboard();
                            switch (turn) {
                                case 1:
                                    BlueMove();
                                    turn = (restart) ? turn : (turn * (-1));
                                    break;
                                case -1:
                                    RedMove();
                                    turn = (restart) ? turn : (turn * (-1));
                                    break;
                            }

                            IsGameOver();
                        }
                        printf("遊戲結束，");
                        if(WhoWin == 1){
                            printf("\033[1;34mPlayer1\033[m 獲勝!\n");
                        }else if(WhoWin == -1){
                            printf("\033[1;31mPlayer2\033[m 獲勝!\n");
                        }else if(tie == 1){
                            printf("和局\n");
                        }
                        return 0;
                    }
                }else{
                    printf("\033[1;31m無法創建檔案!\033[m");
                }
                break;
            case 'l':
                printf("l\n");
                NewOrOld = 0;
                filename = optarg;
                counter = 0;
                printf("filename = %s\n", filename);
                if(NewOrOld == 0){
                    // printf("NewOrOld = %d\n", NewOrOld);
                    // printf("why?/n");
                    if((fp = fopen(filename, "r")) == NULL){
                        printf("\033[1;31m找不到檔案!\033[m");
                        return 0;
                    }else{
                        printf("hi\n");
                        //將檔案寫到stack
                        fscanf(fp, "%d", &amount);
                        while(amount != 0){
                            counter++;
                            fscanf(fp, "%d%d%d%d%d%d%d%d", &stack[counter].p0.id, &stack[counter].p0.color, &stack[counter].p1.id, &stack[counter].p1.color, &stack[counter].position0[0], &stack[counter].position0[1], &stack[counter].position1[0], &stack[counter].position1[1]);
                            fscanf(fp, "%d", &amount);
                        }
                        initialize();
                        while((Read <= counter) && (Read < -1)){
                            printboard();
                            printf("輸入f移動下一手，輸入b退回上一手\n");
                            scanf(" %c", &FOrB);
                            if(FOrB == 'f'){
                                Read++;
                                if(Read == counter){
                                    printf("已為最後一手!\n");
                                }else{
                                    board[stack[Read].position0[0]][stack[Read].position0[1]] = stack[Read].p0;
                                    board[stack[Read].position1[0]][stack[Read].position1[1]] = stack[Read].p1;
                                }
                            }else if(FOrB == 'b'){
                                Read--;
                                if(Read <= -1){
                                    printf("已為初始狀態!\n");
                                }else{
                                    board[stack[Read].position0[0]][stack[Read].position0[1]] = stack[Read].p0;
                                    board[stack[Read].position1[0]][stack[Read].position1[1]] = stack[Read].p1;
                                }
                            }else{
                                printf("請重新輸入!\n");
                            }
                        }
                        return 0;
                    }
                }else{
                    printf("\033[1;31m找不到檔案!\033[m");
                }
                break;
        }
    }
    fprintf(fp, "%d", zero);
    fclose(fp);
}

void initialize() {
    turn = 1;
    IsStandard = 1;
    WrongPlayer = 0;
    restart = 0;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COLUMN; j++) {
            board[i][j].id = 0;
            board[i][j].color = 0;
        }
    }

    //香車
    for (i = 0, j = 0; j < COLUMN; j += 8) {
        board[i][j].id = kyousha;
        board[i][j].color = red;

        board[i + 8][j].id = kyousha;
        board[i + 8][j].color = blue;
    }

    //桂馬
    for (i = 0, j = 1; j < COLUMN; j += 6) {
        board[i][j].id = keima;
        board[i][j].color = red;

        board[i + 8][j].id = keima;
        board[i + 8][j].color = blue;
    }

    //銀將
    for (i = 0, j = 2; j < COLUMN; j += 4) {
        board[i][j].id = ginshou;
        board[i][j].color = red;

        board[i + 8][j].id = ginshou;
        board[i + 8][j].color = blue;
    }

    //金將
    board[0][3].id = kinshou;
    board[0][3].color = red;
    board[8][3].id = kinshou;
    board[8][3].color = blue;
    board[0][5].id = kinshou;
    board[0][5].color = red;
    board[8][5].id = kinshou;
    board[8][5].color = blue;

    //玉將
    board[0][4].id = osho;
    board[0][4].color = red;
    board[8][4].id = osho;
    board[8][4].color = blue;

    //飛車
    board[1][1].id = hisha;
    board[1][1].color = red;
    board[7][7].id = hisha;
    board[7][7].color = blue;

    //角形
    board[1][7].id = kakugyou;
    board[1][7].color = red;
    board[7][1].id = kakugyou;
    board[7][1].color = blue;

    //步兵
    for (j = 0, i = 2; j < COLUMN; j++) {
        board[i][j].id = fuhyo;
        board[i][j].color = red;

        board[i + 4][j].id = fuhyo;
        board[i + 4][j].color = blue;
    }
}

void printboard() {
    //system("clear");
    printf(" ９ ８ ７ ６ ５ ４ ３ ２ １ \n");
    for(i = 0; i < COLUMN; i++){
        printf("|");
        for(j = 0; j < ROW; j++){
            if(board[i][j].id == osho){
                if(board[i][j].color == red){
                    printf("%s", R(玉));
                }else if(board[i][j].color == blue){
                    printf("%s", B(玉));
                }                
            }else if(board[i][j].id == hisha){
                if(board[i][j].color == red){
                    printf("%s", R(飛));
                }else if(board[i][j].color == blue){
                    printf("%s", B(飛));
                }
            }else if(board[i][j].id == kakugyou){
                if(board[i][j].color == red){
                    printf("%s", R(角));
                }else if(board[i][j].color == blue){
                    printf("%s", B(角));
                }
            }else if(board[i][j].id == kinshou){
                if(board[i][j].color == red){
                    printf("%s", R(金));
                }else if(board[i][j].color == blue){
                    printf("%s", B(金));
                }
            }else if(board[i][j].id == ginshou){
                if(board[i][j].color == red){
                    printf("%s", R(銀));
                }else if(board[i][j].color == blue){
                    printf("%s", B(銀));
                }
            }else if(board[i][j].id == keima){
                if(board[i][j].color == red){
                    printf("%s", R(桂));
                }else if(board[i][j].color == blue){
                    printf("%s", B(桂));
                }
            }else if(board[i][j].id == kyousha){
                if(board[i][j].color == red){
                    printf("%s", R(香));
                }else if(board[i][j].color == blue){
                    printf("%s", B(香));
                }
            }else if(board[i][j].id == fuhyo){
                if(board[i][j].color == red){
                    printf("%s", R(步));
                }else if(board[i][j].color == blue){
                    printf("%s", B(步));
                }
            }else{
                printf("　");
            }

            printf("%s",(j == COLUMN - 1)? "" : " ");
        }
        printf("|%d\n", i + 1);
    }
}

void IsGameOver(){
    short sign_r = 0;
    short sign_b = 0;
    for(i = 0; i < ROW; i++){
        for(j = 0; j < COLUMN; j++){
            if(board[i][j].id == osho){
                if(board[i][j].color == blue){
                    sign_b = 1;
                }else if(board[i][j].color == red){
                    sign_r = 1;
                }
            }
        }
    }
    if((sign_b == 0) && (sign_r == 1)){
        WhoWin = -1;
    }else if((sign_r == 0) && (sign_b == 1)){
        WhoWin = 1;
    }
}