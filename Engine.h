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

//key pressed flag
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

    int width;
    int height;
    int realHeight;

    void clearScreen() {
        cerr << string(100, '\n') << flush;
    }

    void render() {
        clearScreen();
        if (mainObject == NULL)
            stopLoop("You must set the mainObject a value, because the camera is fixed on the main object");
        else {
            cerr << "Delta Time: " << deltaTime << "\t\t | FPS : " << (float) 1 / deltaTime << "\t\t | " << monitor <<
            endl << endl;
            gameBoard = new char *[realHeight];
            for (int row = 0; row < realHeight; ++row) {
                gameBoard[row] = new char[width];
                for (int col = 0; col < width; ++col) {
                    if (row == 0)
                        gameBoard[row][col] = '-';
                    if (row == realHeight-1)
                        gameBoard[row][col] = '-';
                    else
                        gameBoard[row][col] = ' ';
                }
            }

            int minX = (int) (mainObject->xPos - 21),
                    maxX = (int) (mainObject->xPos + (width - 20));

            for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {
                GameObject *gameObject = (GameObject *) *it;
                if (gameObject->xPos > minX && gameObject->xPos < maxX) {
                    int x = (int) (gameObject->xPos - minX);
                    gameBoard[int(realHeight - (gameObject->yPos+2))][x] = gameObject->character;
                }
            }

            for (int row = 0; row < realHeight; row++) {
                for (int col = 0; col < width; col++)
                    cerr << gameBoard[row][col] << flush;
                cerr << endl << flush;
            }
        }
    }

    void physEngine(){
        for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {
            GameObject *gameObject = (GameObject *) *it;
            if(gameObject->physics){
                gameObject->ySpeed -= (9)*getDeltaTime();
            }
            gameObject->yPos += gameObject->ySpeed*getDeltaTime();
            gameObject->xPos += gameObject->xSpeed*getDeltaTime();

            if(gameObject->yPos > getHeight())
                gameObject->yPos = getHeight();
            if(gameObject->yPos < 0) {
                gameObject->yPos = 0;
                gameObject->ySpeed = 0;
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
        cerr << "\n\n\nprocess finished with message :" << _message << endl;
    }

    int getWidth(){
        return width;
    }

    int getHeight(){
        return height;
    }


public:

    void run(int _width=200, int _height=16) {

        //we tell the system to not to stop the main loop
        notStopCommand = true;

        //in this line we initial the window width and height
        width = _width;
        height = _height;
        realHeight = _height+2;


        //calls the overrided of init method
        init();

        //creating thread object
        pthread_t thread;
        int i = 0;
        pthread_create(&thread, NULL,
                       charGetter, (void *) i);

        //main loop
        while (notStopCommand) {
            //getting the start time of every loop in nanoseconds
            auto start = std::chrono::high_resolution_clock::now();

            //calls the physics engine of the game engine
            physEngine();

            //calls the overrided logic function of the game
            doLogic();

            //checks if the stop flag is set of not in logic function
            if (notStopCommand)
                render();

            //getting the end time of logic function in nanoseconds
            auto endOfAction = std::chrono::high_resolution_clock::now();

            //calculating delta time of doing logic function in nanoseconds
            float deltaToSleep = std::chrono::duration_cast<std::chrono::nanoseconds>(endOfAction - start).count();

            //sleeps the thread for a time btween 0 to 50000
            usleep((useconds_t) (50000 - deltaToSleep / 1000));

            //calculating the delta time of loop
            auto finish = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
            deltaTime /= 1000000000;
        }
    }
};


#endif //CONTEST_ENGINE_H
