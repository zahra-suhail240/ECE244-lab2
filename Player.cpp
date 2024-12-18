//
//  Player.cpp
//  Lab 2 Pong Game
//
//  Created by Author Name, Date


#include <string>
#include "Globals.h"
#include "Screen.h"
#include "Player.h"


Player::Player(){ //constructor
    x=0;
    y=0;
    width=1;
    height=0;

}

Player::Player(double xcoord, double ycoord, int heightval){ //constructor

    x=xcoord;
    y=ycoord;
    height=heightval;
}

double Player::getX(){
    return x;

}
double Player::getY(){
    return y;
}

int Player::getHeight(){
    return height;
}

int Player::getWidth(){
    return width;
}

void Player::update(char c){
    
    if(c == 'A'|| c == 'a'){
        if(y >= 0 && y+height < HEIGHT-1){
            y=y+2;
        }
        
    }

    else if(c == 'B' || c == 'b'){
       //if(y+height < HEIGHT-1){

      if(y >= 0){
            y=y-2;
        } 

        if(y==-1 || y==-2) { // y=1-2
            y=0;
        }


        
         
    }

}

void Player::draw(Screen& screen_to_draw_to){
    /*Notes: screen_to_draw_to is an object of class Screen
    and since we're passing by refernce, you're directly accessing the 
    screen_to_draw_to object, no need to make a copy of it.

    if the function was void Player::draw(Screen screen_to_draw_to), that 
    means ur passing a copy of the entire object. Tkes up memory
    if your the object was too big
    */
   

    for(int i=0; i<height; i++){
        screen_to_draw_to.addPixel(x, y+i, '#');
    }
   
   
}

void Player::decreaseHeight(int delta_to_decrease_by){

   // if(delta_to_decrease_by > 3){
        height = height - delta_to_decrease_by;
   // }

}

