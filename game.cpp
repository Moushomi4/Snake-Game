#include<bits/stdc++.h>
#include<conio.h> //has key press event library(kbhit)(keyboard hit)
#include<windows.h>//to draw on colsole

using namespace std;
#define MAX_LENGTH 1000

const char DIR_UP='U';
const char DIR_DOWN='D';
const char DIR_RIGHT='R';
const char DIR_LEFT='L';

int consoleWidth,consoleHeight;

void initScreen(){// tto initialize the screen
// HANDLE is a predefined class in windows.h
HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);//syntax
//GIVE THE HANDLE(CONTROL) OF THE WINDOW
CONSOLE_SCREEN_BUFFER_INFO csbi;//gives the information of the buffer
GetConsoleScreenBufferInfo(hConsole,&csbi);
consoleHeight=csbi.srWindow.Bottom-csbi.srWindow.Top+1;
consoleWidth=csbi.srWindow.Right-csbi.srWindow.Left+1;
}
struct Point{ //by default public members
    int xCoord;
    int yCoord;
    Point(){

    }
    Point(int x,int y){
        xCoord=x;
        yCoord=y;
    }
};
class Snake{ //by default private members
    int length;
    char direction;
public: // because we are making array and we need to specify the max length of the body, can also make private but we need to return a method.so to kkep it single we keeping it public
    Point body[MAX_LENGTH];//stack memory
    Snake(int x,int y){
        length=1;
        body[0]=Point(x,y);
        direction=DIR_RIGHT;
    }
    
    int getLength(){
        return length;
    }
    void changeDirection(char newDirection){
        if(newDirection==DIR_UP && direction!=DIR_DOWN){
            direction=newDirection;
        }
        else if(newDirection==DIR_UP && direction!=DIR_DOWN){
            direction=newDirection;
        }
        else if(newDirection==DIR_DOWN && direction!=DIR_UP){
            direction=newDirection;
        }
        else if(newDirection==DIR_LEFT && direction!=DIR_RIGHT){
            direction=newDirection;
        }
        else if(newDirection==DIR_RIGHT && direction!=DIR_LEFT){
            direction=newDirection;
        }
    }
    bool move(Point food){
        for(int i=length-1;i>0;i--){
            body[i]=body[i-1];
        }
        switch(direction){
            int val;
            case DIR_UP:
                val=body[0].yCoord;
                body[0].yCoord=val-1;
                break;
            case DIR_DOWN:
                val=body[0].yCoord;
                body[0].yCoord=val+1;
                break;
            case DIR_LEFT:
                val=body[0].xCoord;
                body[0].xCoord=val-1;
                break;
            case DIR_RIGHT:
                val=body[0].xCoord;
                body[0].xCoord=val+1;
                break;

        }
        for(int i=1;i<length;i++){
            if(body[0].xCoord==body[i].xCoord && body[0].yCoord==body[i].yCoord){
                return false;
            }
        }
        if(food.xCoord==body[0].xCoord && food.yCoord==body[0].yCoord){
            body[length]=Point(body[length-1].xCoord,body[length-1].yCoord);
            length++;
        }
        return true;
    }
};
class Board{
Snake *snake; //greated in heap(dynamic memory allocation)
const char SNAKE_BODY='O';
Point food;
const char FOOD='o';
int score;
public:
    Board(){
        spawnFood();
        snake=new Snake(10,10);
        score=0;
    }

    ~Board(){
        delete snake;
    }

    int getScore(){
        return score;
    }

    void spawnFood(){
        int x=rand()%consoleWidth;
        int y=rand()%consoleHeight;
        food=Point(x,y);
    }

    void displayCurrentScore(){
        gotoxy(consoleWidth/2,0);
        cout<<"Current Score:"<<score;
    }

    void gotoxy(int x,int y){//set the cursor position 
    COORD coord; //class
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    }

    void draw(){
        system("cls");
        for(int i=0;i<snake->getLength();i++){
            gotoxy(snake->body[i].xCoord,snake->body[i].yCoord);//(->)DYNAMIC MEMORY ALLOCATION OF SNAKE
            cout<<SNAKE_BODY;
        }
        gotoxy(food.xCoord,food.yCoord);//(.)STACK MEMMORY ALLLOCATION
        cout<<FOOD;

        displayCurrentScore();
    }

    bool update(){
        bool isAlive=snake->move(food);
        if(isAlive==false){
            return false;
        }
        if(food.xCoord==snake->body[0].xCoord && food.yCoord==snake->body[0].yCoord){
            score++;
            spawnFood();
        }
        return true;
    }

    void getInput(){
        if(kbhit()){
            int key=getch();
            if(key=='w'|| key=='W'){
                snake->changeDirection(DIR_UP);
            }
            else if(key=='a'|| key=='A'){
                snake->changeDirection(DIR_LEFT);
            }
            else if(key=='s'|| key=='S'){
                snake->changeDirection(DIR_DOWN);
            }
            else if(key=='d'|| key=='D'){
                snake->changeDirection(DIR_RIGHT);
            }
        }
    }

};
int main(){
    initScreen();
    Board *board=new Board();
    while (board->update())
    {
        board->getInput();
        board->draw();
        Sleep(100);
    }
    cout<<"Game Over"<<endl;
    cout<<"Final Score is"<<board->getScore();
    return 0;
}