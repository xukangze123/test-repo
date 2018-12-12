#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SNAKE_MAX_LENGTH 100
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'
#define INF 0x3f3f3f3f

//snake stepping: dy = -1(up),1(down); dx = -1(left),1(right),0(no move)
void snakeMove(int,int);
//put a food randomized on a blank cell
void put_money(void);
//out cells of the grid
void output(void);
//outs when gameover
void gameover(void);
//find next
char whereGoNext(int ,int ,int ,int );

char map[13][13]=
     {"************",
      "*XXXXH     *",
      "*          *",
      "*          *",
      "*          *",
      "*          *",
      "*          *",
      "*          *",
      "*          *",
      "*          *",
      "*          *",
      "************"};

// define vars for snake , notice name of vars in C
int snakeX[SNAKE_MAX_LENGTH]={1,2,3,4,5};
int snakeY[SNAKE_MAX_LENGTH]={1,1,1,1,1};
int snakelength=5;
//记录分数
int score=0;
//判断游戏是否结束
int ok=1;
int money_x,money_y;
int step;

int main(){
    srand(time(NULL));
    put_money();
    output();
    step=-1;
    while(ok){
        step++;
        char ch=whereGoNext(snakeX[snakelength-1],snakeY[snakelength-1],money_x,money_y);
        if (ch!='A'&ch!='D'&ch!='W'&ch!='S') continue;
        switch (ch){
            case 'A':
                snakeMove(-1,0);
                break;
            case 'D':
                snakeMove(1,0);
                break;
            case 'W':
                snakeMove(0,-1);
                break;
            case 'S':
                snakeMove(0,1);
                break;
        }
        output();
    }
    gameover();
    return 0;
}

void snakeMove(int dx,int dy){
    int x=snakeX[snakelength-1]+dx;
    int y=snakeY[snakelength-1]+dy;
    snakeX[snakelength]=x;
    snakeY[snakelength]=y;

    //如果碰到边界
    if (map[y][x]=='*') {
        ok=0;
        return ;
    }   
    //如果碰到蛇身
    else if (map[y][x]=='X'){
        ok=0;
        return ;
    }
    //如果吃到钱，不用处理蛇尾,处理蛇头，长度+1，放钱，分数+1
    else if (map[y][x]=='$') {
        snakelength++;
        //蛇头处理
        map[snakeY[snakelength-2]][snakeX[snakelength-2]]='X';
        map[y][x]='H';//蛇头处理


        score++;
        put_money();

    }
    //如果吃不到钱，处理蛇头，蛇尾位置变空格，身体移一位
    else if (map[y][x]==' ') {
        map[snakeY[0]][snakeX[0]]=' ';
        for(int i=0;i<snakelength;i++){
            snakeX[i]=snakeX[i+1];
            snakeY[i]=snakeY[i+1];
        }
        //蛇头处理
        map[snakeY[snakelength-2]][snakeX[snakelength-2]]='X';
        map[y][x]='H';      
    }


}

void put_money(void){
    //找到合法位置
    do{
        money_x=rand()%10+1;
        money_y=rand()%10+1;
    } while (map[money_y][money_x]!=' ');
    map[money_y][money_x]='$';
}

void output(void){
    system("cls");
    printf("score:%d\n",score);
    for(int i=0;i<12;i++){
        for(int j=0;j<12;j++){
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
}

void gameover(void){
    printf("Game Over!!!");
}

char whereGoNext(int Hx,int Hy,int Fx,int Fy){
    char moveable[4]={'A','D','W','S'};
    int distance[4]={INF,INF,INF,INF};
    int dx[4]={-1,1,0,0},
        dy[4]={0,0,-1,1};
    for(int i=0;i<4;i++){
        int X=Hx+dx[i];
        int Y=Hy+dy[i];
        if (map[Y][X]==' '||map[Y][X]=='$'){
            distance[i]=abs(Fx-(Hx+dx[i]))+abs(Fy-(Hy+dy[i]));
        }
    }
    int k=-1,tmp=INF;
    for(int i=0;i<4;i++){
        if (distance[i]<tmp){
            k=i;
            tmp=distance[i];
        }
    }
    if (k!=-1) return moveable[k];
    else {
        ok=0;
        return moveable[0];
    }
}
