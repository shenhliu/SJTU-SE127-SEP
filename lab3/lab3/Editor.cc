#include <iostream>
#include <sstream>
#include <cmath>
#include "Editor.h"

using namespace std;

void Editor::run()
{
    string cmd;
    while (true)
    {
        cout << "cmd> ";
        cout.flush();
        getline(cin, cmd);
        if (cmd == "Q")
            break;
        try
        {
            dispatchCmd(cmd);
        }
        catch (const char *e)
        {
            cout << "? " << e << endl;
        }
        catch (const out_of_range &oor)
        {
            cout << "? " << oor.what() << endl;
        }
        catch (const range_error &re)
        {
            cout << "? " << re.what() << endl;
        }
    }
}

void Editor::dispatchCmd(const string &cmd)
{
    if (cmd[0] == '-')
    {
        throw "out of scale";
    }
    //这一个模块用来处理 cmd-1;
    if (cmd[0] >= '0' && cmd[0] <= '9')
    {
        int space = 0;
        int num = 0; //num为操作的行
        string truetext;
        while (cmd[space] != ' ')
            ++space;
        int weishu = space - 1;
        for (int i = 0; i < space; ++i)
        {
            num += (cmd[i] - '0') * (pow(10, weishu));
            weishu--;
        }
        truetext = cmd.substr(space + 1);
        buffer->insertLine(num, truetext);
    }

    //这个模块用来处理cmd-2;
    if (cmd[0] == 'd')
    {
        string truenum;
        int num;
        truenum = cmd.substr(2);
        for (int i = 0; i < truenum.length(); ++i)
        {
            num += (truenum[i] - '0') * pow(10, truenum.length() - i - 1);
        }
        buffer->deleteLine(num);
    }

    //这个模块用来处理cmd-3;
    if (cmd[0] == 'l' || cmd[0] == 'L')
    {
        buffer->showLines();
    }

    //这个模块用来处理cmd-4;
    if (cmd[0] == 's' && cmd[1] == 'a')
    {
        string truefile;
        truefile = cmd.substr(5);
        buffer->writeToFile(truefile);
    }
    /*
    TODO: your code here.
          cmd-1: non-negative integer + statement (e.g., 100 let a = b + c)
          cmd-2: delete (e.g., d 100)
          cmd-3: list   (e.g., lisT) 
          cmd-4: save as a file (e.g., save code.sh)
    */
}

//TODO: add other code you want