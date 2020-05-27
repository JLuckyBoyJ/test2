#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "snake.h"

using namespace std;

const int WIDTH = 50;
const int HEIGHT = 40;
const int SIZE = 15;
const int SCREEN_WIDTH = WIDTH*SIZE;
const int SCREEN_HEIGHT = HEIGHT*SIZE;
const string WINDOW_TITLE = "SNAKE";
enum TrangThai {UP,DOWN,LEFT,RIGHT};


string s;
int score;
TTF_Font *font;
SDL_Color color = {255,0,0,200};
SDL_Texture *text;
SDL_Surface *temp;
SDL_Rect rr,qwer;
int Ran(int l,int r)
{
    int temp = rand() % (r - l + 1);
    return temp + l;
}
string ConvertToString(int x)
{
    string res = "";
    if (!x) res = "0";
    else
    {
        while (x)
        {
            res = res + (char) ('0' + x % 10);
            x /= 10;
        }
    }
    reverse(res.begin(),res.end());
    return res;
}
struct Toado
{
    int x,y;
};
struct Snake
{
    Toado dot[1000];
    int n;
    TrangThai tt;
    void MOVE()
    {
        if(tt == UP)
        {
            dot[0].y -= 1;
        }
        else if(tt == DOWN)
        {
            dot[0].y += 1;
        }
        else if(tt == LEFT)
        {
            dot[0].x -= 1;
        }
        else if(tt == RIGHT)
        {
            dot[0].x += 1;
        }
    }
};
struct Fruit
{
    Toado td;
};

void KhoiTao(Snake &snake, Fruit &hq);
void HienThi(Snake snake, Fruit hq, SDL_Renderer *renderer);
bool DieuKhien(Snake &snake, Fruit &hq);
int Xuly(Snake &snake, Fruit &hq);

int main(int argc, char *argv[])
{
    srand(time(NULL));

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Init();
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    font = TTF_OpenFont("TIMES.TTF",200);

    Snake snake;
    Fruit hq;

Playagain:
    {
        KhoiTao(snake,hq);
        bool quit = 0;
        while(!quit)
        {

            SDL_SetRenderDrawColor(renderer,0,0,0,0);
            SDL_RenderClear(renderer);
            HienThi(snake,hq,renderer);
            quit = DieuKhien(snake,hq);
            snake.MOVE();
            int check = Xuly(snake,hq);
            if(check == 0)
            {
                qwer = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
                temp = IMG_Load("lose.jpg");
                text = SDL_CreateTextureFromSurface(renderer, temp);
                SDL_RenderCopy(renderer, text, NULL, &qwer);
                /// cout << "You lost" << '\n';
                s = "YOU LOST!!! Play again? Y=YES  N=NO"; /// xau can in ra
                temp = TTF_RenderText_Solid(font,s.c_str(),color); /// update len 1 cai surface
                text = SDL_CreateTextureFromSurface(renderer,temp); /// tao texture tu surface
                rr = {SCREEN_WIDTH/2-180,SCREEN_HEIGHT/2-100,s.size() * 10,100}; /// chon vi tri va kich thuoc dat xau
                SDL_RenderCopy(renderer,text,NULL,&rr); /// copy ra renderer
                SDL_FreeSurface(temp);
                SDL_DestroyTexture(text);
                SDL_RenderPresent(renderer);
                /// cout << Play again? << Y N;

                while (true)
                {
                    SDL_Event e;
                    if (SDL_PollEvent(&e))
                    {
                        if(e.type == SDL_KEYDOWN)
                        {
                            if (e.key.keysym.sym == SDLK_y)
                            {
                                score = 0;
                                goto Playagain;
                            }
                            else if (e.key.keysym.sym == SDLK_n)
                            {
                                quit = 1;
                                break;
                            }
                        }
                    }
                }
                break;
            }
            SDL_Delay(50);
        }
    }
    quitSDL(window, renderer);

    return 0;

}

void KhoiTao(Snake &snake, Fruit &hq)
{
    snake.n = 1;
    snake.dot[0].x = 10;
    snake.dot[0].y = 10;
    snake.tt = RIGHT;
    hq.td.x = 25;
    hq.td.y = 20;

}
void HienThi(Snake snake, Fruit hq, SDL_Renderer *renderer)
{
    SDL_Rect filled_rect;
    filled_rect.w = SIZE;
    filled_rect.h = SIZE;
    SDL_SetRenderDrawColor(renderer, 128, 128, 255, 255);
    filled_rect.x = snake.dot[0].x*SIZE;
    filled_rect.y = snake.dot[0].y*SIZE;
    SDL_RenderFillRect(renderer,&filled_rect);

    SDL_SetRenderDrawColor(renderer,153, 153, 255, 255);
    for(int i = 1 ; i < snake.n ; ++i)
    {
        filled_rect.x = snake.dot[i].x*SIZE;
        filled_rect.y = snake.dot[i].y*SIZE;
        SDL_RenderFillRect(renderer,&filled_rect);

    }

    SDL_SetRenderDrawColor(renderer,  250, 128, 114, 255);
    filled_rect.x = hq.td.x*SIZE;
    filled_rect.y = hq.td.y*SIZE;
    SDL_RenderFillRect(renderer,&filled_rect);


    ///in diem
    s = "Score : " + ConvertToString(score); /// xau can in ra
    temp = TTF_RenderText_Solid(font,s.c_str(),color); /// update len 1 cai surface
    text = SDL_CreateTextureFromSurface(renderer,temp); /// tao texture tu surface
    rr = {0,0,s.size() * 10,100}; /// chon vi tri va kich thuoc dat xau
    SDL_RenderCopy(renderer,text,NULL,&rr); /// copy ra renderer
    SDL_FreeSurface(temp);
    SDL_DestroyTexture(text);

    SDL_Rect rect;
    rect.w = SCREEN_WIDTH;
    rect.h = SIZE;
    SDL_SetRenderDrawColor(renderer, 227, 187, 28, 255);
    rect.x = 0;
    rect.y = 6*SIZE;
    SDL_RenderFillRect(renderer,&rect);


    SDL_RenderPresent(renderer);
}
bool DieuKhien(Snake &snake, Fruit &hq)
{
    for(int i = snake.n -1 ; i > 0 ; --i)
    {
        snake.dot[i] = snake.dot[i-1];
    }
    SDL_Event e;
    if(SDL_PollEvent(&e) == 0)
        return 0;
    if(e.type == SDL_QUIT)
        return 1;
    if(e.type == SDL_KEYDOWN)
    {
        if(e.key.keysym.sym == SDLK_UP && snake.tt != DOWN)
        {
            snake.tt = UP;
        }
        if(e.key.keysym.sym == SDLK_DOWN && snake.tt != UP)
        {
            snake.tt = DOWN;
        }
        if(e.key.keysym.sym == SDLK_LEFT && snake.tt != RIGHT)
        {
            snake.tt = LEFT;
        }
        if(e.key.keysym.sym == SDLK_RIGHT && snake.tt != LEFT)
        {
            snake.tt = RIGHT;
        }
    }

    return 0;
}

int Xuly(Snake &snake, Fruit &hq)
{
    // xulu an hoa qua
    if(snake.dot[0].x == hq.td.x && snake.dot[0].y == hq.td.y)
    {
        for(int i = snake.n ; i > 0 ; i--)
        {
            snake.dot[i] = snake.dot[i-1];
        }
        snake.n++;
        ++score;
        if(snake.tt == UP)
            snake.dot[0].y-=1;
        else if(snake.tt == RIGHT)
            snake.dot[0].x+=1;
        else if(snake.tt == DOWN)
            snake.dot[0].y+=1;
        else if(snake.tt == LEFT)
            snake.dot[0].x-=1;
        hq.td.x = Ran(1,WIDTH);
        hq.td.y = Ran(6,HEIGHT);
    }
    if(snake.dot[0].x >= WIDTH || snake.dot[0].x < 0 || snake.dot[0].y < 7 || snake.dot[0].y >= HEIGHT)
    {
        return 0;
    }
    for(int i = 1 ; i < snake.n; ++i)
    {
        if(snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y)
        {
            return 0;
        }
    }
    return 1;
}
