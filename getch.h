//
// Created by Arash Khajelou on 4/17/16.
//

#ifndef CONTEST_GETCH_H
#define CONTEST_GETCH_H

#include <unistd.h>
#include <termios.h>
#include <stdio.h>

static struct termios oldTerm, newTerm;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
    tcgetattr(0, &oldTerm); /* grab old terminal i/o settings */
    newTerm = oldTerm; /* make new settings same as old settings */
    newTerm.c_lflag &= ~ICANON; /* disable buffered i/o */
    newTerm.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
    tcsetattr(0, TCSANOW, &newTerm); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &oldTerm);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void)
{
    return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
    return getch_(1);
}

#endif //CONTEST_GETCH_H
