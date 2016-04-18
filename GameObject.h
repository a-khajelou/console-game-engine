//
// Created by Arash Khajelou on 4/17/16.
//

#ifndef CONTEST_GAMEOBJECT_H
#define CONTEST_GAMEOBJECT_H


class GameObject {

public:
    float xPos;
    float yPos;
    char character;
    bool isRigid;
    bool physics;
    float xSpeed = 0;
    float ySpeed = 0;

    GameObject() {

    }

    GameObject(char _character) {
        this->character = _character;
    }

    GameObject(int _xPos, int _yPos) {
        this->xPos = _xPos;
        this->yPos = _yPos;
    }

    GameObject(char _character, int _xPos, int _yPos) {
        this->character = _character;
        this->xPos = _xPos;
        this->yPos = _yPos;
    }
};


#endif //CONTEST_GAMEOBJECT_H
