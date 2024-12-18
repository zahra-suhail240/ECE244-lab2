//
//  main.cpp
//  Lab 2 Pong Game
//
//  Created by Nathan Hung on 2024-09-11.
//  Modified by Salma Emara on 2024-09-11
//  Copyright © 2024 Nathan Hung. No rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <string>

#include "Ball.h"
#include "Globals.h"
#include "Player.h"
#include "Screen.h"
#include "io.h"

int main() {
  int score = 0;
  bool gameEnded = false;
  std::string messageToPutOnScreen;

  std::chrono::steady_clock::time_point begin_time =
      std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point now_time;
  Screen screen = Screen();

  int ballCount = 0;
  const int max_ballCount = 5;

  Ball balls_array[max_ballCount];

  balls_array[0] = Ball(30.0, 30.0, 1.7, 0, ballCount);
  ballCount++;  // updates the number of balls in the game

  Player player = Player(0, 5, 10);

  while (!gameEnded) {
    // TODO: ECE 244 Student: Complete the game loop here only!
    // ECE 244 Student: DO NOT edit any other segments of this file!

    // player.draw(screen);
    //  balls_array[0].draw(screen);

    for (int length = 0; length < simulation_fps; length++) {
      char userInput = get_input();

      if (userInput == 'q' || userInput == 'Q') {
        gameEnded = true;
      }

      if (userInput != '\0') {
        player.update(userInput);
      
      }

      

      for (int i = 0; i < ballCount; i++) {
        balls_array[i].update();  // update the position of ball
        //balls_array[i].bounce(balls_array, ballCount, player); //check if
        

        // check if the ball touches paddels
        int result = balls_array[i].overlap(player);

        if (result == VERTICAL_OVERLAP || result == HORIZONTAL_OVERLAP) {
          score++;

        //  cout<< "score tracker: "<< score<<endl;
          // keep track of nmber of hits of the paddel
          //paddel_hits_counter++;

          // every 2 hits, we decrease the size of paddels
          //cout<<"enters the loop"<<endl;
          if (score % 2 == 0) {
            if (player.getHeight() > 3) {
               player.decreaseHeight(1);
             
            }
          }
          // every 5 hits add new ball
          if (score % 5 == 0) {
            if (ballCount < 5) {
              balls_array[ballCount] = Ball(30.0, 30.0, 1.9, 0, ballCount);
              ballCount++;
            }
          }

        }

      balls_array[i].bounce(balls_array, ballCount, player);  // check if bounce with other ball,paddle
      }


      // check for game end, when player misses hitting the ball

      for (int j = 0; j < ballCount; j++) {
        if (balls_array[j].getX() < 0) {
         // cout << balls_array[j].getX() << endl;
          gameEnded = true;
        }
      }
    }

    for (int k = 0; k < ballCount; k++) {
      balls_array[k].draw(screen);
    }

    player.draw(screen);


    messageToPutOnScreen = "Your score is: " + std::to_string(score);
    screen.update(messageToPutOnScreen);

    // wait until 1/fps seconds
    while (std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - begin_time)
               .count() < (long int)milliseconds_per_frame) {
    }

    begin_time = std::chrono::steady_clock::now();
  }
  messageToPutOnScreen = "Game over. Your score is: " + std::to_string(score);
  screen.update(messageToPutOnScreen);

  return 0;
}