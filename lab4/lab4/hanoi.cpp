#include "termio.h"

// Do not delete the following 3 lines
char Termio::buffer[Termio::CANVAS_HEIGHT][Termio::CANVAS_WIDTH + 1];
int Termio::MAX_WIDTH;
int Termio::MAX_HEIGHT;

void write_hi()
{
    for (int i = 0; i < 5; i++)
    {
        Termio::buffer[i][0] = '|';
        Termio::buffer[i][5] = '|';
        Termio::buffer[i][9] = '|';
        Termio::buffer[i][13] = '*';
    }
    Termio::buffer[3][13] = ' ';
    Termio::buffer[1][9] = ' ';
    for (int i = 1; i < 5; i++)
    {
        Termio::buffer[2][i] = '-';
    }
}

int main()
{
    //linkStack stack;
    // ---- Example: how to use termio.h ----
    // clear screen
    Termio::Clear();
    // reset buffer
    Termio::ResetBuffer();
    //write_hi();
    Termio::Draw();
    // ----------- End of example -----------
    // Your code here

    Termio::Clear();
    cout << "How many disks do you want?    (1~5)" << endl;
    cin >> Termio::num;
    Termio::normal(Termio::num);
    Termio::Draw();
    while (!Termio::iswinning(Termio::num))
    {
        cout << "Move a disk. Format: x y" << endl;
        cin >> Termio::start >> Termio::end;
        if (Termio::start < 0 || Termio::start > 3 || Termio::end < 0 || Termio::end > 3)
        {
            continue;
        }
        if (Termio::start == 0 && Termio::end == 0)
        {

            //node *tmp = stack.pop();
            //cout << tmp->s << ' ' << tmp->e << endl;

            Termio::automation();
        }

        else
        {
            Termio::start = Termio::trans(Termio::start);
            Termio::end = Termio::trans(Termio::end);
            if (Termio::canmove(Termio::start, Termio::end))
            {
                stack.push(Termio::start, Termio::end);
                Termio::move(Termio::start, Termio::end);
                Termio::Draw();
            }
            else
                continue;
        }
    }
    if (Termio::iswinning(Termio::num))
    {
        cout << "Yes,you win!";
    }
    return 0;
}
