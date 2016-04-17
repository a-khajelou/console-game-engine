//
// Created by Arash Khajelou on 4/17/16.
//

#ifndef CONTEST_ENGINE_H
#define CONTEST_ENGINE_H

#include <iostream>
#include <list>
#include <string>
#include <chrono>

#include "getch.h"
#include "GameObject.h"

using namespace std;


bool isKeyPressed = false;
char theKey = ' ';

void *charGetter(void *_threadid) {
    while (true) {
        theKey = getch();
        isKeyPressed = true;
    }
}

class Engine {
private:
    bool notStopCommand;
    float deltaTime;
    char **gameBoard;

    void clearScreen() {
        cout << string(100, '\n') << flush;
    }

    void render() {
        clearScreen();
        if (mainObject == NULL)
            stopLoop("You must set the mainObject a value, because the camera is fixed on the main object");
        else {
            cout << "Delta Time: " << deltaTime << "\t\t | FPS : " << (float) 1 / deltaTime << "\t\t | " << monitor <<
            endl << endl;
            gameBoard = new char *[16];
            for (int row = 0; row < 16; ++row) {
                gameBoard[row] = new char[200];
                for (int col = 0; col < 200; ++col) {
                    if (row == 0)
                        gameBoard[row][col] = '-';
                    if (row == 15)
                        gameBoard[row][col] = '-';
                    else
                        gameBoard[row][col] = ' ';
                }
            }

            int minX = mainObject->xPos - 21,
                    maxX = mainObject->xPos + 180;
            for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {
                GameObject *gameObject = (GameObject *) *it;
                if (gameObject->xPos > minX && gameObject->xPos < maxX) {
                    int x = gameObject->xPos - minX;
                    gameBoard[int(14 - gameObject->yPos)][x] = gameObject->character;
                }
            }

            for (int row = 0; row < 16; ++row) {
                for (int col = 0; col < 200; ++col)
                    cout << gameBoard[row][col] << flush;
                cout << endl << flush;
            }
        }
    }

protected:
    list<GameObject *> gameObjects;
    GameObject *mainObject;
    string monitor;

    virtual void doLogic() = 0;

    virtual void init() = 0;

    float getDeltaTime() {
        return this->deltaTime;
    }

    void stopLoop(string _message) {
        notStopCommand = false;
        cout << "\n\n\nprocess finished with message :" << _message << endl;
    }


public:

    void run() {
        init();
        notStopCommand = true;

        pthread_t thread;
        int i = 0;
        pthread_create(&thread, NULL,
                       charGetter, (void *) i);

        while (notStopCommand) {
            auto start = std::chrono::high_resolution_clock::now();

            doLogic();
            if (notStopCommand)
                render();

            auto endOfAction = std::chrono::high_resolution_clock::now();

            float deltaToSleep = std::chrono::duration_cast<std::chrono::nanoseconds>(endOfAction - start).count();
            usleep((useconds_t) (50000 - (float) deltaToSleep / 1000));

            auto finish = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
            deltaTime /= 1000000000;
        }
    }
};


#endif //CONTEST_ENGINE_H
