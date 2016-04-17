//
// Created by Arash Khajelou on 4/17/16.
//

#ifndef CONTEST_MYGAME_H
#define CONTEST_MYGAME_H


#include "Engine.h"

class MyGame : public Engine {
    GameObject *runner = new GameObject('@', 0, 0);

    bool isJumping;
    bool isLanding;
    float jumpingDeltaY;

    int speed;

    int score() {
        return (int) runner->xPos * 10;
    }

    void init() {
        mainObject = runner;
        speed = 12;

        gameObjects.push_back(runner);

        //creating the game map !
        int range[4] = {3, 4, 5, 6};
        for (int i = 2; i < 400; i++) {
            if (i <= 20) {
                GameObject *tree = new GameObject(char(35), i * (range[(i % 4)] * 5), 0);
                gameObjects.push_back(tree);
            }
            if (i > 20 && i <= 30) {
                GameObject *tree = new GameObject(char(35), i * (range[(i % 4)] * 5), 0);
                gameObjects.push_back(tree);
                tree = new GameObject(char(35), i * (range[(i % 4)] * 5), 1);
                gameObjects.push_back(tree);
            }
            if (i > 30) {
                GameObject *tree = new GameObject(char(35), i * (range[(i % 4)] * 5), 0);
                gameObjects.push_back(tree);
                tree = new GameObject(char(35), i * (range[(i % 4)] * 5), 1);
                gameObjects.push_back(tree);
                tree = new GameObject(char(35), (i * (range[(i % 4)] * 5)) + 1, 0);
                gameObjects.push_back(tree);
                tree = new GameObject(char(35), (i * (range[(i % 4)] * 5)) + 1, 1);
                gameObjects.push_back(tree);
            }


        }
    }

    void doLogic() {
        runner->xPos += speed * getDeltaTime();
        monitor = "your score : " + to_string(score());

        if (isKeyPressed) {
            isJumping = true;
            isKeyPressed = false;
            jumpingDeltaY = 0;
        }

        if (isJumping || isLanding)
            doJump();

        for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {
            GameObject *gameObject = (GameObject *) *it;
            if (gameObject->character != '@' &&
                (int) gameObject->xPos == (int) runner->xPos &&
                (int) gameObject->yPos == (int) runner->yPos)
                stopLoop("The game is Over ! your high score is : " + to_string(score()) + "\n\n\n");
        }
    }


    void doJump() {
        if (jumpingDeltaY < 4 && isJumping && (int)runner->yPos <= 13) {
            jumpingDeltaY += speed * getDeltaTime();
            runner->yPos += speed * getDeltaTime();
        }
        else {
            isJumping = false;
            isLanding = true;
            runner->yPos -= speed * getDeltaTime();
            if ((int) runner->yPos == 0) {
                runner->yPos = 0;
                isLanding = false;
            }
        }
    }

};


#endif //CONTEST_MYGAME_H
