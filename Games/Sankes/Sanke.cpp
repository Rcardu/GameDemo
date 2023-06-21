#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;
bool gameOver;//游戏结束标志
//地图尺寸
const int width=20;
const int height=20;
//蛇的坐标，食物坐标，分数
int x,y,fruitX,fruitY,score;
//尾部的坐标数组
int tailX[100],tailY[100];
int nTail;
//使用枚举来追踪蛇的方向
enum eDirection {STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;//方向变量

//游戏初始化
void Setup(){
    gameOver=false;//开始时，结束游戏标志为假
    dir=STOP;
    //使蛇头初始化在地图的中心
    x=width / 2;
    y=height / 2;
    //将食物随机分布在地图上，即取一个随机数，使之在地图范围内(此实现已转移到逻辑部分)
    fruitX=rand()%width;
    fruitY=rand()%height;
    score=0;//初始分数置为0;
}
/*
#####
#   #
#####
*/
//地图初始化
void Draw(){
    system("cls");//清除屏幕
    //设置地图边界
    for(int i=0;i<width+1;i++)cout<<"#";
    cout<<endl;

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(j==0||j==width-1)cout<<"#";
            if(i==y&&j==x)cout<<"O";
            else if(i==fruitY&&j==fruitX)cout<<"F";
            else {
                bool print=false;
                for(int k=0;k<nTail;k++){
                    if(tailX[k]==j&&tailY[k]==i){
                        cout<<"o";
                        print=true;
                    }
                } 
                if(!print)cout<<" ";
            }
        }
        cout<<endl;
    }
    for(int i=0;i<width+1;i++)cout<<"#";
    cout<<endl;
    cout<<"Score:"<<score<<endl;
}
/*
    w
   a d
    s 
按键响应
*/
void Input(){
    if(_kbhit){
        switch(_getch()){
            case 'a':
                dir=LEFT;
                break;
            case 'd':
                dir=RIGHT;
                break;
            case 'w':
                dir=UP;
                break;
            case 's':
                dir=DOWN;
                break;
            case 'x':
                gameOver=true;
                break;
        }
    }
}
/*实现逻辑*/
void Logic(){
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for(int i=1;i<nTail;i++){
         prev2X=tailX[i];
         prev2Y=tailY[i];

         tailX[i]=prevX;
         tailY[i]=prevY;

         prevX=prev2X;
         prevY=prev2Y;
    }
    switch(dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
        break;
    }
    if(x>=width-1||x<0||y>=height||y<0)gameOver=true;
    for(int i=0;i<nTail;i++)
        if(tailX[i]==x&&tailY[i]==y)
            gameOver=true;
    if(x==fruitX && y==fruitY){
        //将食物随机分布在地图上，即取一个随机数，使之在地图范围内
        score+=10;
        fruitX=rand()%width;
        fruitY=rand()%height;
        nTail++;
    }
}

int main(){
    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
        Sleep(10);//slep(10);
    }
    return 0;
}