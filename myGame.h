//
// Created by Arash Khajelou on 4/17/16.
//

#ifndef CONTEST_MYGAME_H
#define CONTEST_MYGAME_H


#include "Engine.h"

//this is a simple flappy bird game

class MyGame : public Engine {
    GameObject *runner = new GameObject('@', 0, 0);

    int speed;
    float runnerAcceleration;

    int score() {
        return (int) runner->xPos * 10;
    }

    void init() {
        mainObject = runner;
        speed = 6;
        runner->physics = true;

        gameObjects.push_back(runner);

        //creating the game map !
        int range[4] = {3, 5, 7, 11};
        for (int i = 2; i < 402; ++i) {
            for(int j=0; j <= getHeight(); j++){
                int tmp = (j == 0) ? j+1 : ((j == getHeight()) ? j-1 : j);
                if(i%getHeight() != j && i%getHeight() != j+1 && i%getHeight() != j-1){
                    GameObject *tree = new GameObject('#', i * (range[(i % 4)] * 5), j);
                    gameObjects.push_back(tree);
                }
            }
        }
    }

    void doLogic() {
        runner->xPos += speed * getDeltaTime();
        monitor = "your score : " + to_string(score());

        if (isKeyPressed) {
            isKeyPressed = false;
            runner->ySpeed += 4;
        }else{
            if(runner->ySpeed > 1.5)
                runner->ySpeed = 1.5;
        }

        for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {
            GameObject *gameObject = (GameObject *) *it;
            if (gameObject->character != '@' &&
                (int) gameObject->xPos == (int) runner->xPos &&
                (int) gameObject->yPos == (int) runner->yPos)
                stopLoop("The game is Over ! your high score is : " + to_string(score()) + "\n\n\n");
        }
    }

};


#endif //CONTEST_MYGAME_H
