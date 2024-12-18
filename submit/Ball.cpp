//
//  Ball.cpp
//  Lab 2 Pong Game
//
//  Created by Author Name, Date

#include "Ball.h"

#include <cmath>

#include "Globals.h"
#include "Player.h"
#include "Screen.h"

Ball::Ball() {
  // Default constructor used to initialize the data memebers

  velocity_x = 0;
  velocity_y = 0;
  x = 0;
  y = 0;
  width = 1;
  height = 1;
  id = 0;
}

Ball::Ball(double xcoord, double ycoord, double velocity_xpos,
           double velocity_ypos, int idVal) {
  x = xcoord;
  y = ycoord;
  velocity_x = velocity_xpos;
  velocity_y = velocity_ypos;
  id = idVal;
}

void Ball::update() {
  velocity_y = velocity_y - 0.02 * timeStep;

  double dx = velocity_x * timeStep;
  double dy = velocity_y * timeStep;

  // Update new ball position given the vel

  x = x + dx;
  y = y + dy;
}

void Ball::draw(Screen& screen_to_draw_to) {
  // Draw the positon of the ball
  screen_to_draw_to.addPixel(x, y, 'o');
}

void Ball::bounce(Ball arr[], int ballCount, Player player) {
  // call the ovelp of ball and player

  for (int i = 0; i < ballCount; i++) {
    if (id != arr[i].id) {  // not colliding with it self
      int overlapDir = overlap(arr[i]);

      if (overlapDir == VERTICAL_OVERLAP) {
        velocity_y = velocity_y * (-1);
      }
      if (overlapDir == HORIZONTAL_OVERLAP) {
        velocity_x = velocity_x * (-1);
      }
    }
  }

  // check if ball collides with a player
  int overlapPlayer = overlap(player);

  if (overlapPlayer == VERTICAL_OVERLAP) {
    velocity_y = velocity_y * (-1);
  }

  if (overlapPlayer == HORIZONTAL_OVERLAP) {
    velocity_x = velocity_x * (-1);
  }

  // check if ball touches the sides
  if (x >= WIDTH - 1) {
    velocity_x = velocity_x * (-1);
  }

  if (y <= 0 || y >= HEIGHT - 1) {
    velocity_y = velocity_y * (-1);
  }
}

int Ball::getID() { return id; }

double Ball::getX() { return x; }

int Ball::overlap(Ball& b) {
  double bx, by, bheight, bwidth;

  // position of another ball
  bx = b.x;
  by = b.y;
  // bheight = b.height;
  // bwidth=b.width;

  double horizontal_overlap = (x + width) - bx; 
  double vertical_overlap = (y + height) - by;

  //double horizontal_overlap = (by+width) - y;
 // double vertical_overlap = bx - (x + width);

  // check for overlap
  if ((x <= bx && bx <= x + width) || (y <= by && by <= y + height)) {

    // check if vertical overlap is greater than horizontal

    if (vertical_overlap > horizontal_overlap) {
      return VERTICAL_OVERLAP;
    } else {
      return HORIZONTAL_OVERLAP;
    }
  }

  // no overlap
  else {

    return NO_OVERLAP;

  }
}

int Ball::overlap(Player& p) {

  // values for the paddle

  double px = p.getX();
  double py = p.getY();
  int pHeight = p.getHeight();
  int pwidth = p.getWidth();

 //double horizontal_overlap = (px + 1) - x; 
 //double vertical_overlap = (py + pHeight) - y;

  double horizontal_overlap = x - (px + 1); 
  double vertical_overlap = y - (py + pHeight);

  // check overlap of the ball and paddle
 // if ((px <= x && x <= px + 1) || (py <= y && y <= py + pHeight)) {
 if((x<=px+1) && (py <= y && y <= py + pHeight)){
   if (vertical_overlap > horizontal_overlap) {
    return VERTICAL_OVERLAP;
    
    } 
   else {
      return HORIZONTAL_OVERLAP;
   }
  }

  // no overlap
  return NO_OVERLAP;


}
