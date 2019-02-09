#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define FIELD_HEIGHT 8
#define FIELD_WIDTH 10
#define BOMB 20

int min(int, int);
int max(int, int);
int getkey(int*, int*, int*, int*, int*, int*);
void init(int, int);
void open_check(int, int, int);
int count1();

int field[FIELD_HEIGHT][FIELD_WIDTH];
//0:地雷なし 1:地雷あり
int f_num[FIELD_HEIGHT][FIELD_WIDTH];
//周り8マスの地雷の数
int opened[FIELD_HEIGHT][FIELD_WIDTH];
//0:開いていない 1:開いている
int field_flag[FIELD_HEIGHT][FIELD_WIDTH];
//0:フラッグなし 1:フラッグあり

int main(void){
    int x, y, flag = 0, mode = 0, win=-1;
    //mode 0:決定 1:カーソル非表示
    int cursored_x = 0, cursored_y = 0;
    int selected_x = -1, selected_y = -1;
    system("cls");
    printf("===操作方法===\n");
    printf("↑→↓←キーでｶｰｿﾙ(◎)移動\n");
    printf("Eキーで決定\n");
    printf("Fキーで旗を立てる\n");
    printf("Hキーでｶｰｿﾙ非ﾋｮｳｼﾞ\n");
    for(y = 0;y < FIELD_HEIGHT;y++){
        for(x = 0;x < FIELD_WIDTH;x++){
            if(x == 0 && y == 0) printf("◎");
            else printf("●");
        }
        printf("\n");
    }
    while (1){
        if (getkey(&cursored_x, &cursored_y, &selected_x, &selected_y, &flag, &mode) == -1) break;
        //printf("%d %d %d %d\n", cursored_x, cursored_y, selected_x, selected_y);
        if(flag == 1){
            init(selected_x, selected_y);
            flag = 2;
        }
        if(f_num[selected_y][selected_x] == -1){
            win = 0;
            break;
        }
        if(flag > 0) open_check(selected_x, selected_y, -1);
        kbhit();
        system("cls");
        printf("===操作方法===\n");
        printf("↑→↓←キーでｶｰｿﾙ(◎)移動\n");
        printf("Eキーで決定\n");
        printf("Fキーで旗を立てる\n");
        printf("Hキーでｶｰｿﾙ非ﾋｮｳｼﾞ\n");
        for(y = 0;y < FIELD_HEIGHT;y++){
            for(x = 0;x < FIELD_WIDTH;x++){
                if(x == cursored_x && y == cursored_y){
                    if(mode != 1) printf("◎");
                    else{
                        if(field_flag[y][x] == 1) printf(" F");
                        else if(opened[y][x] == 1) printf("%2d", f_num[y][x]);
                        else printf("●");
                    }
                }               

                else{
                    if(field_flag[y][x] == 1) printf(" F");
                    else if(opened[y][x] == 1) printf("%2d", f_num[y][x]);
                    else printf("●");
                }
            }
            printf("\n");
        }
        if(count1() == 1){
            win = 1;
            break;
        }
    }
    system("cls");
    for(y = 0;y < FIELD_HEIGHT;y++){
        for(x = 0;x < FIELD_WIDTH;x++){
            if(f_num[y][x] == -1) printf(" B");
            else printf("%2d", f_num[y][x]);
        }
        printf("\n");
    }
    if(win == 0){
        printf("あなたの負けです\n");
    }
    else{
        printf("あなたの勝ちです\n");
    }
    return 0;
}

int min(int a, int b){
    if(a >= b) return b;
    else return a;
}
int max(int a, int b){
    if(b >= a) return b;
    else return a;
}
int getkey(int *x, int *y, int *sx, int *sy, int *fl, int *mo){
    int key;
    key = getch();
    if(key == 0xe0){
        key = getch();
        if(key == 0x48){
            //↑
            if(*y != 0){
                *y -= 1;
            }
        }
        else if(key == 0x4d){
            //→
            if(*x != FIELD_WIDTH-1){
                *x += 1;
            }
        }    
        else if(key == 0x4b){
            //←
            if(*x != 0){
                *x -= 1;
            }
        }      
        else if(key == 0x50){
            //↓
            if(*y != FIELD_HEIGHT-1){
                *y += 1;
            }
        }
    }
    else if(key == 'e'){
        *mo = 0;
        *sx = *x;
        *sy = *y;
        if(*fl == 0){
            *fl = 1;
        }
        
    }
    else if(key == 'h'){
        *mo += 1;
        *mo %= 2;
    }
    else if(key == 'f'){
        field_flag[*y][*x] ++; 
        field_flag[*y][*x] %= 2;
    }
    else if(key == 'p') return -1;
}
void init(int fx, int fy){
    int height[FIELD_HEIGHT], width[FIELD_WIDTH];
    int x, y, i, j, sum;
    srand((unsigned)time(NULL));
    for(i = 0;i < FIELD_HEIGHT;i++){
        height[i] = i;
    }
    for(i = 0;i < FIELD_WIDTH;i++){
        width[i] = i;
    }
    for(i = 0;i < BOMB;i++){
        while(1){
            y = rand() % FIELD_HEIGHT;
            x = rand() % FIELD_WIDTH;
            if(field[y][x] != 0 || x != fx && y != fy){
                field[y][x] = 1;
                break;
            }           
        }
    }
    for(y = 0;y < FIELD_HEIGHT;y++){
        for(x = 0;x < FIELD_WIDTH;x++){
            sum = 0;
            if(field[y][x] == 0){
                for(j = max(0, y-1);j <= min(FIELD_HEIGHT, y+1);j++){
                    for(i = max(0, x-1);i <= min(FIELD_WIDTH,x+1);i++){
                        if(field[j][i] == 1) sum += 1;
                    }
                }
            }
            else sum = -1;
            f_num[y][x] = sum;
        }
    }
}
void open_check(int fx, int fy, int once_before){
    if(opened[fy][fx] == 1) return;
    else if(fx < 0 || fy < 0 || fx > FIELD_WIDTH || fy > FIELD_HEIGHT) return;
    else if(once_before > 0) return;
    else if(f_num[fy][fx] >= 0){
        once_before = f_num[fy][fx];
        opened[fy][fx] = 1;
        open_check(fx-1, fy, once_before);
        open_check(fx+1, fy, once_before);
        open_check(fx, fy-1, once_before);
        open_check(fx, fy+1, once_before);
        return;
    }

}
int count1(){
    int i, j, sum=0;
    for(i = 0;i < FIELD_HEIGHT;i++){
        for(j = 0;j < FIELD_WIDTH;j++){
            if(f_num[i][j] == 1) sum++;
        }
    }
    if(sum == FIELD_HEIGHT*FIELD_WIDTH-BOMB) return 1;
}