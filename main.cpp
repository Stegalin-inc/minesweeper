#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include "button.h"
#include "win.h"
#define MINES_COUNT 40
#define FIELD_X 19
#define FIELD_Y 19

void draw();
void openTile(int x, int y);
void openTileNew(int x, int y);
void textDraw();
void putMines();
void setNumbers();
void setZero();
void setZeroWave();

int field[FIELD_X][FIELD_Y];
bool opened[FIELD_X][FIELD_Y];
bool wave[FIELD_X][FIELD_Y];
int corx, cory;
int tileNum=0;
int mouseCorX, mouseCorY;
bool leftMouse;
bool waves;
bool settingsWindow;
bool lose;

int wincorx=20, wincory=20, winwt=400, winht=255, bposx, bposy, bcorx, bcory, bwt, bht; //������������� ��������� � ���������� ���� � �������� �� ��������
bool moved=false, resized=false;  //��������� ����

int main()
{
    setZero();
    srand(time(0));
    putMines();
    setNumbers();
    draw();
    return EXIT_SUCCESS;
}


void draw()  //������ � ������� SFML
{

    sf::RenderWindow app(sf::VideoMode((FIELD_X*30)-60, (FIELD_Y*30)), "Glebs Minesweeper");  //�������� ���� � ��������� ��� ���������� �����

    sf::Texture texture;  // ������ ��������
    texture.loadFromFile("texture.png");
    sf::Sprite sprite(texture);

    Button exit, newGame, settings;
    exit.newButton(70,25,((FIELD_X*30)-130),((FIELD_Y*30)-40) );
    exit.setLabel("exit","times.ttf");
    newGame.newButton(70,25,60,((FIELD_Y*30)-40) );
    newGame.setLabel("new","times.ttf");
    settings.newButton(90,25,((FIELD_X*30)-80)/2,((FIELD_Y*30)-40) );
    settings.setLabel("settings","times.ttf");

    Win setWin;
    setWin.initWin(90,90,270,270);
    setWin.setColor(200, 255, 100, 200);
    Win loseWin;
    loseWin.initWin(90,90,270,270);
    loseWin.setColor(200, 2, 1, 200);

    while (app.isOpen())
    {

        sf::Vector2i pixelPos = sf::Mouse::getPosition(app);  //�������� ������� ���� � �������� � ������� ��� �������� ��������� ���������� ��������
        sf::Vector2f pos = app.mapPixelToCoords(pixelPos);

        sf::Event event;
        while (app.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::MouseButtonReleased)  //���� ������ ���� ������ ����� ������ ���� �������� �������, ����� �����
            {
                leftMouse=true;
            }
            else
            {
                leftMouse=false;
            }

            if(leftMouse && !settingsWindow && !lose)
            {
                openTileNew((pos.x/30)+1,(pos.y/30)+1);
            }


            if ((newGame.isCursor(pos.x+30,pos.y)) && (event.type == sf::Event::MouseButtonReleased))  //�������� ����� ����
            {
                setZero();
                putMines();
                setNumbers();
                lose=false;
            }

            if ((settings.isCursor(pos.x+30,pos.y)) && (event.type == sf::Event::MouseButtonReleased) && (!settingsWindow))
            {
                settingsWindow=true;
            } else if ((settings.isCursor(pos.x+30,pos.y)) && (event.type == sf::Event::MouseButtonReleased) && (settingsWindow))
                settingsWindow=false;


            }

        if ((exit.isCursor(pos.x+30,pos.y)) && (event.type == sf::Event::MouseButtonReleased))
                break; //���� ��� �� ������ ���� (��������) ���������





        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))  //��������� ���������� ���� ����� ��������������� ����
        {

            bposy=pos.y;
            bposx=pos.x;
            wincorx = bcorx; wincory = bcory;
            //winwt = bwt; winht = bht;

        }

        if ((setWin.isMove(pos.x,pos.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
        {
            moved=true;  //��� � ���������, ���� �������� ��������� ��� ������ ������ ������ � ����� ������������� ����

        }

        if(moved)   //���������� ������� ���������� ���� ������� ������� ���������� ���� � ��������� �� ������ ����� ������������������
        {

            setWin.initWin(wincorx+(pos.x-bposx),wincory+(pos.y-bposy),winwt,winht);
            bcorx = wincorx+(pos.x-bposx); bcory = wincory+(pos.y-bposy);
        }

        if (event.type == sf::Event::MouseButtonReleased)   //��������� �������, ������� �� ������ �����������������, �������� � ���������� ���� ��� ������� ���������
        {

            moved=false;
            resized=false;
            wincorx = bcorx; wincory = bcory;
           // winwt = bwt; winht = bht;
        }





        app.clear(sf::Color(255,255,255));

        for(int yqwe = 1; yqwe <= (FIELD_Y-2); yqwe+=1)  //� ����� �������� ��� ������ � ������ �� � ��������������� ��������
        {
            for(int zqwe = 1; zqwe <= (FIELD_X-2); zqwe+=1)
            {
                if (opened[zqwe][yqwe])  //���� ������ ������� ������ ��������
                {
                switch (field[zqwe][yqwe])  //� ����������� �� �������� ������ �������� ������ ������� ��������
                {
                    case 1: {sprite.setTextureRect(sf::IntRect(0,0,30,30)); break;}
                    case 2: {sprite.setTextureRect(sf::IntRect(31,0,61,30)); break;}
                    case 3: {sprite.setTextureRect(sf::IntRect(62,0,92,30)); break;}
                    case 4: {sprite.setTextureRect(sf::IntRect(93,0,123,30)); break;}
                    case 5: {sprite.setTextureRect(sf::IntRect(124,0,154,30)); break;}
                    case 6: {sprite.setTextureRect(sf::IntRect(155,0,185,30)); break;}
                    case 9: {sprite.setTextureRect(sf::IntRect(217,0,247,30)); break;}
                    case 0: {sprite.setTextureRect(sf::IntRect(248,0,278,30)); break;}
                    case 10: {sprite.setTextureRect(sf::IntRect(186,0,216,30)); break;}

                }
                } else {sprite.setTextureRect(sf::IntRect(186,0,216,30));}  //����� ������ ������
                sprite.setPosition((zqwe-1)*30,(yqwe-1)*30);
                app.draw(sprite);

            }
        }
        app.draw(exit.button);
        app.draw(exit.text);
        app.draw(newGame.button);
        app.draw(newGame.text);
        app.draw(settings.button);
        app.draw(settings.text);
        if (settingsWindow)
        {
        app.draw(setWin.title);
        app.draw(setWin.leftBorder);
        app.draw(setWin.rightBorder);
        app.draw(setWin.botBorder);
        app.draw(setWin.body);
        }
        if (lose)
        {
        app.draw(loseWin.title);
        app.draw(loseWin.leftBorder);
        app.draw(loseWin.rightBorder);
        app.draw(loseWin.botBorder);
        app.draw(loseWin.body);
        }
        app.display();
    }
}


void putMines()  //�������� ������������ ����
{

    for(int z=0;z<MINES_COUNT;z++)
    {
        field[1+rand()%(FIELD_X-2)][1+rand()%(FIELD_Y-2)]=9;
    }
}


void setNumbers()  //����������� �������
{

    for(int yf = 1; yf < (FIELD_Y-1); yf++)
    {
        for(int zf = 1; zf < (FIELD_X-1); zf++)
        {
            if (field[zf][yf]==0)
            {
                tileNum=0;
                if (field[zf-1][yf-1]==9) tileNum+=1;
                if (field[zf+1][yf-1]==9) tileNum+=1;
                if (field[zf+1][yf+1]==9) tileNum+=1;
                if (field[zf-1][yf+1]==9) tileNum+=1;
                if (field[zf][yf-1]==9) tileNum+=1;
                if (field[zf+1][yf]==9) tileNum+=1;
                if (field[zf][yf+1]==9) tileNum+=1;
                if (field[zf-1][yf]==9) tileNum+=1;
                field[zf][yf]=tileNum;
            }
        }
    }
}


void setZero()  //�������� ����
{

    for(int y = 0; y < FIELD_Y; y+=1)
    {
        for(int z = 0; z < FIELD_X; z+=1)
        {
            field[z][y]=0;
            opened[z][y]=false;

        }
    }
}


void setZeroWave()  //�������� �����
{

    for(int y = 0; y < FIELD_Y; y+=1)
    {
        for(int z = 0; z < FIELD_X; z+=1)
        {
            wave[z][y]=false;

        }
    }
}


void openTileNew(int xc, int yc)  //��������� ���������
{
    if (field[xc][yc]==0)  //���� �� ����� ����...
    {
        wave[xc][yc]=true;  //�� � ��� ������ �����
        for(int r=0;r<900;r++)  //������� ����, ��� �����
        {
            for(int y=1; y<=(FIELD_Y-2); y++)  //���� �� ���� �������
            {
                for(int x=1; x<=(FIELD_X-2); x++)
                {
                    if(wave[x][y])  //���� � ������ ���� �����, ������� �� ��������, ���� ���� ��� ���������, � ���� ��� ����� �� ������ ���� �����
                    {
                        if ( (field[x-1][y-1]!=9)  ) {opened[x-1][y-1]=true; if (field[x-1][y-1]==0) wave[x-1][y-1]=true; else wave[x-1][y-1]=false;}
                        if ( (field[x+1][y-1]!=9)  ) {opened[x+1][y-1]=true; if (field[x+1][y-1]==0) wave[x+1][y-1]=true;else wave[x+1][y-1]=false;}
                        if ( (field[x+1][y+1]!=9) ) {opened[x+1][y+1]=true; if (field[x+1][y+1]==0) wave[x+1][y+1]=true;else wave[x+1][y+1]=false;}
                        if ( (field[x-1][y+1]!=9)  ) {opened[x-1][y+1]=true; if (field[x-1][y+1]==0) wave[x-1][y+1]=true;else wave[x-1][y+1]=false;}
                        if ( (field[x][y-1]!=9)  ) {opened[x][y-1]=true; if (field[x][y-1]==0) wave[x][y-1]=true;else wave[x][y-1]=false;}
                        if ( (field[x+1][y]!=9)  ) {opened[x+1][y]=true; if (field[x+1][y]==0) wave[x+1][y]=true;else wave[x+1][y]=false;}
                        if ( (field[x][y+1]!=9)  ) {opened[x][y+1]=true; if (field[x][y+1]==0) wave[x][y+1]=true;else wave[x][y+1]=false;}
                        if ( (field[x-1][y]!=9)  ) {opened[x-1][y]=true; if (field[x-1][y]==0) wave[x-1][y]=true;else wave[x-1][y]=false;}
                    }
                }
            }
        }
    } else  if (field[xc][yc]!=9) {opened[xc][yc]=true;} else {lose=true; opened[xc][yc]=true; }//� ���� ����� �� ���� �� ���������
}











