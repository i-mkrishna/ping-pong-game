#include<bits/stdc++.h>
#include<iostream>
#include<time.h>
#include<conio.h>

using namespace std;

enum eDir{ STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class cBall
{
private:
    int x,y;
    int originalX, orignalY;
    eDir direction;
public:
    cBall(int posX, int posY){
        // COnstructor for clss cBall
        originalX = posX;
        orignalY = posY;
        x = posX;
        y = posY;
        direction = STOP;
    }

    void Reset(){
        x = originalX;
        y = orignalY;
        direction = STOP;
    }

    void changeDirection(eDir d){
        direction = d;
    }

    void randomDirection(){
        direction = (eDir)(( rand() %6 ) + 1);
    }


    inline int getX(){
        return x;
    }
    inline int getY(){
        return y;
    }
    inline eDir getDirection(){
        return direction;
    }

    void Move(){
        switch (direction){
            
            case STOP:
                break;
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UPLEFT:
                x--; y--;
                break;
            case DOWNLEFT:
                x--; y++;
                break;
            case UPRIGHT:
                x++; y--;
                break;
            case DOWNRIGHT:
                x++; y++;
                break;
            default:
                break;
        }
    }

    friend ostream & operator << (ostream & o, cBall c){
        o << "Ball [" << c.x << "," << c.y << "][" << c.direction  << "]";
        return o;
    }
};

class cPaddle
{
private:
    int x, y;
    int orignalX, orignalY;
public:
    cPaddle(){
        x = y = 0;
    }
    cPaddle(int posX, int posY) : cPaddle(){
        orignalX = posX;
        orignalY = posY;
        x = posX; y = posY;
    }

    inline void Reset(){
        x = orignalX; y = orignalY;
    }

    inline int getX(){
        return x;
    }

    inline int getY(){
        return y;
    }

    inline void moveUp(){
        y--;
    }

    inline void moveDown(){
        y++;
    }

    friend ostream & operator << (ostream & o, cPaddle c){
        o << "Paddle [" << c.x << "," << c.y << "]";
        return o;
    }

};

class cGameManeger
{
private:
    int width, height;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    cBall *ball;
    cPaddle *player1;
    cPaddle *player2;
public:
    cGameManeger(int w, int h){
        srand(time(NULL));
        quit = false;
        up1 = '7'; up2 = '9';
        down1 = '1'; down2 = '3';
        score1 = score2 = 0;
        width = w; height = h;
        ball = new cBall(w/2, h/2);
        player1 = new cPaddle(1, h/2 - 3);
        player2 = new cPaddle(w - 2, h/2 - 3);
    }

    ~cGameManeger(){
        delete ball, player1, player2;
    }

    void ScoreUp(cPaddle *player){
        if(player == player1){
            score1++;
        }
        else if (player == player2){
            score2++;
        }
        ball->Reset();
        player1->Reset();
        player2->Reset();
    }

    void Draw(){

        system("cls");

        for (int i = 0; i < width + 2; i++){
            std::cout << "\xB0";
        }
        std::cout << endl;

        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                int ballx = ball->getX();
                int bally = ball->getY(); 
                int player1x = player1->getX();
                int player2x = player2->getX();
                int player1y = player1->getY();
                int player2y = player2->getY();

                if(j == 0){
                    std::cout << "\xB0";
                }
                
                if(ballx == j && bally == i){
                    std::cout << "O"; // ball
                }
                else if (player1x == j && player1y == i){
                    std::cout << "\xBA"; // player1
                }
                else if (player2x == j && player2y == i){
                    std::cout << "\xBA"; // player2
                }

                else if (player1x == j && player1y + 1 == i){
                    std::cout << "\xBA"; // player1
                }
                else if (player1x == j && player1y + 2 == i){
                    std::cout << "\xBA"; // player1
                }
                else if (player1x == j && player1y + 3 == i){
                    std::cout << "\xBA"; // player1
                }

                else if (player2x == j && player2y + 1 == i){
                    std::cout << "\xBA"; // player2
                }
                else if (player2x == j && player2y + 2 == i){
                    std::cout << "\xBA"; // player2
                }
                else if (player2x == j && player2y + 3 == i){
                    std::cout << "\xBA"; // player2
                }
                

                else{
                    std::cout << " ";
                }

                if(j == width - 1){
                    std::cout << "\xB0";
                }
            }
            std::cout << endl;
        }

        for (int i = 0; i < width + 2; i++){
            std::cout << "\xB0";
        }
        std::cout << endl;

        std::cout << "Score1 : " << score1 << endl;
        std::cout << "Score2 : " << score2 << endl;

    }

    void Input(){
        ball->Move();

        int ballx = ball->getX();
        int bally = ball->getY(); 
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        // Ball movement logic
        if (ball->getDirection() == STOP) {
            ball->randomDirection();
        }

        if (_kbhit()){
            char current = _getch();
            if (current == up1){
                if (player1y > 0){
                    player1->moveUp();
                }  
            }
            if (current == up2){
                if (player2y > 0){
                    player2->moveUp();
                }  
            }
            if (current == down1){
                if (player1y + 4 < height){
                    player1->moveDown();
                }  
            }
            if (current == down2){
                if (player2y + 4 < height){
                    player2->moveDown();
                }  
            }

            if(ball->getDirection() == STOP){
                ball->randomDirection();
            }
            
            if(current == 'q'){
                quit = true;
            }
        }
    }

    void Logic(){

        int ballx = ball->getX();
        int bally = ball->getY(); 
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        // Left paddle
        for (int i = 0; i < 4; i++){
            if(ballx == player1x + 1){
                if (bally == player1y + i){
                    ball->changeDirection((eDir)((rand() % 3) + 4));
                }
            }
        }

        //right paddle
        for (int i = 0; i < 4; i++){
            if(ballx == player2x - 1){
                if (bally == player2y + i){
                    ball->changeDirection((eDir)((rand() % 3) + 1));
                }
            }
        }

        // bottom wall
        if(bally == height - 1){
            ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
        }

        //top wall
        if(bally == 0){
            ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        }

        // right wall
        if(ballx == width - 1){
            ScoreUp(player1);
        }

        //left wall
        if(ballx == 0){
            ScoreUp(player2);
        }
    }

    void Run(){

        while (!quit){
            Draw();
            Input();
            Logic();
            std::this_thread::sleep_for(std::chrono::milliseconds(11));
        }
    }
};


int main(){


    cGameManeger c(40, 20);
    c.Run();


    
    // std::cout << c << endl;

    // cPaddle p1(0, 0);
    // cPaddle p2(10, 0);

    // std::cout << p1 << endl;
    // std::cout << p2 << endl;
    // p1.moveUp();
    // p2.moveDown();
    // std::cout << p1 << endl;
    // std::cout << p2 << endl;



    // cBall c(0, 0);
    // std::cout << c<< endl;
    // c.randomDirection();
    // std::
    // cout << c<< endl;
    // c.Move();
    // std::cout << c<< endl;
    // c.randomDirection();
    // std::cout << c << endl;
    // c.randomDirection();
    // std::cout << c << endl;

    return 0;
}