#pragma once
/* some code from Libconio 1.0 (C) 2004 FSL A.C. */

#ifdef _WIN32
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
static void clrscr()
{
    system("cls");
}
#else
#include <termios.h>
#include <stdio.h>
#define ESC 033 /* Escape char */

static int getch()
{
    struct termios t;
    int c;

    tcgetattr(0, &t);
    t.c_lflag &= ~ECHO + ~ICANON;
    tcsetattr(0, TCSANOW, &t);
    fflush(stdout);
    c = getchar();
    t.c_lflag |= ICANON + ECHO;
    tcsetattr(0, TCSANOW, &t);
    return c;
}

static void clrscr()
{
    printf("%c[2J", ESC);
    printf("%c[%d;%dH", ESC, 0, 0);
}
#endif

#include <iostream>
#include "linkStack.h"
using namespace std;

linkStack stack;
class Termio
{
  public:
    static const int CANVAS_WIDTH = 64;
    static const int CANVAS_HEIGHT = 13;
    static int MAX_WIDTH, MAX_HEIGHT;
    static char buffer[CANVAS_HEIGHT][CANVAS_WIDTH + 1];
    static int num;
    static int start;
    static int end;

    static char GetChar()
    {
        return getch();
    }

    static void Clear()
    {
        clrscr();
    }

    static void Draw()
    {
        for (int i = 0; i < CANVAS_HEIGHT; i++)
        {
            buffer[i][CANVAS_WIDTH] = '\0';
            cout << buffer[i] << endl;
        }
    }

    static void ResetBuffer()
    {
        for (int i = 0; i < CANVAS_HEIGHT; i++)
            memset(buffer[i], ' ', CANVAS_WIDTH);
    }

    static void normal(int a)
    {
        for (int i = 0; i <= 5; ++i)
        {
            buffer[i][5] = '|';
            buffer[i][17] = '|';
            buffer[i][29] = '|';
        }
        for (int i = 1; i <= a; ++i)
        {
            for (int j = 5 - i; j <= (5 + i); ++j)
            {
                buffer[i][j] = '*';
            }
        }
    }

    static int trans(int a)
    {
        if (a == 1)
            return 5;
        if (a == 2)
            return 17;
        if (a == 3)
            return 29;
        else
            return 0;
    }

    static bool canmove(int a, int b)
    {
        int atop = 6;
        int btop = 6;
        for (int i = 1; i <= 5; ++i)
        {
            if (buffer[i][a] == '*')
            {
                atop = i;
                break;
            }
        }
        for (int i = 1; i <= 5; ++i)
        {
            if (buffer[i][b] == '*')
            {
                btop = i;
                break;
            }
        }

        if (atop < btop)
            return true;
        else
        {
            return false;
        }
    }

    static void move(int a, int b)
    {
        int starttop = 0;
        for (int i = 1; i <= 5; ++i)
        {
            if (buffer[i][a] == '*')
            {
                starttop = i;
                break;
            }
        }
        for (int i = 1; i <= starttop; ++i)
        {
            for (int j = a - i; j <= a + i; ++j)
            {
                buffer[i][j] = ' ';
            }
            buffer[i][a] = '|';
        }

        for (int j = b - starttop; j <= b + starttop; ++j)
        {
            buffer[starttop][j] = '*';
        }
    }
    static bool iswinning(int num)
    {
        int i = 0;
        while (i <= num)
        {
            ++i;
            if (buffer[i][29] != '*')
                break;
        }
        if ((i - 1) == num)
            return true;
        else
            return false;
    }

    static void hanoi(int n, int a, int b, int c)
    {
        if (n == 1)
        {
            move(a, c);
            Draw();
        }
        else
        {
            hanoi(n - 1, a, c, b);
            move(a, c);
            Draw();
            hanoi(n - 1, b, a, c);
        }
    }

    static void automation()
    {
        cout << "automation" << endl;
        while (!stack.isEmpty())
        {
            node *tmp = stack.pop();
            cout << tmp->s << ' ' << tmp->e << endl;
            move(tmp->e, tmp->s);
            Draw();
        }
        hanoi(num, 5, 17, 29);
    }
};
int Termio::num = 0;
int Termio::start = 0;
int Termio::end = 0;
