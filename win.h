#ifndef WIN_H_INCLUDED
#define WIN_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include "button.h"
#pragma once
#endif // WIN_H_INCLUDED
#define TITLE_SIZE      30
#define BORDER_SIZE     7

class Win
{
    int winWeight, winHeight, titlePosX, titlePosY, leftBorderPosX, leftBorderPosY, vertBorderHeight, rightBorderPosX, rightBorderPosY, botBorderPosX, botBorderPosY, botBorderWeight;
    int r, g, b, t;
    public:
    sf::RectangleShape title;
    sf::RectangleShape leftBorder;
    sf::RectangleShape rightBorder;
    sf::RectangleShape botBorder;
    sf::RectangleShape body;
    Button exit;

    void initWin (int posx, int posy, int wht, int hht)
    {

    titlePosX=posx;
    titlePosY=posy;
    winWeight=wht;
    winHeight=hht;
    leftBorderPosX=titlePosX;
    leftBorderPosY=titlePosY+TITLE_SIZE;
    vertBorderHeight=winHeight-TITLE_SIZE;
    rightBorderPosX=titlePosX+winWeight-BORDER_SIZE;
    rightBorderPosY=titlePosY+TITLE_SIZE;
    botBorderPosX=titlePosX;
    botBorderPosY=titlePosY+winHeight;
    botBorderWeight=winWeight;

    title.setSize(sf::Vector2f(winWeight, TITLE_SIZE));
    title.setPosition(titlePosX, titlePosY);
    leftBorder.setSize(sf::Vector2f(BORDER_SIZE, vertBorderHeight));
    leftBorder.setPosition(leftBorderPosX, leftBorderPosY);
    rightBorder.setSize(sf::Vector2f(BORDER_SIZE, vertBorderHeight));
    rightBorder.setPosition(rightBorderPosX, rightBorderPosY);
    botBorder.setSize(sf::Vector2f(botBorderWeight, BORDER_SIZE));
    botBorder.setPosition(botBorderPosX, botBorderPosY);
    body.setSize(sf::Vector2f(winWeight-2*BORDER_SIZE, winHeight-(TITLE_SIZE+2/BORDER_SIZE)));
    body.setPosition(titlePosX+BORDER_SIZE,titlePosY+TITLE_SIZE);

    exit.newButton(80,30,(titlePosX+winWeight)-50,(titlePosY+winHeight)-50);
    //exit.setLabel("exit","times.ttf");

    }



    bool isMove(float corx, float cory)
    {

        if ((corx>titlePosX) && (corx<winWeight+titlePosX) && (cory>titlePosY) && (cory<TITLE_SIZE+titlePosY))
        return true;
        else
        return false;
    }


    bool isResize(float corxr, float coryr)
    {

        if ((corxr>rightBorderPosX) && (corxr<rightBorderPosX+BORDER_SIZE) && (coryr>rightBorderPosY) && (coryr<rightBorderPosY+vertBorderHeight))
        return true;
        //std::cout<<"true";
        else
        //std::cout<<"false";
        return false;
    }


    void setColor(int rc, int gc, int bc, int tc)
    {

    r = rc; g = gc; b = bc;

    title.setFillColor(sf::Color(r, g, b, tc));
    leftBorder.setFillColor(sf::Color(r, g, b, tc));
    rightBorder.setFillColor(sf::Color(r, g, b, tc));
    botBorder.setFillColor(sf::Color(r, g, b, tc));
    }


    int getPosx(int relx)
    {
    return titlePosX+relx;
    }
    int getPosy(int rely)
    {
    return titlePosY+rely;
    }
    int getWinw()
    {
    return winWeight;
    }




};
