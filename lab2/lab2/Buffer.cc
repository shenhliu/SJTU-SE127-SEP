#include <fstream>
#include <iostream>
#include "Buffer.h"

Buffer::Buffer()
{
    currentLine = maxLine = 0;
}
Buffer::~Buffer()
{
}
void Buffer::moveToPrevLine()
{
    if (currentLine <= 1)
        throw out_of_range("Line number out of range");
    currentLine--;
}
string Buffer::moveToLine(int lineNum)
{
    if (lineNum <= 0 || lineNum > maxLine)
        throw out_of_range("Line number out of range");
    currentLine = lineNum;
    return lines[lineNum];
}

void Buffer::writeToFile(const string &filename) const
{
    ofstream out("Makefile");
    int len = 0;
    for (int i = 1; i <= maxLine; ++i)
    {
        out << lines[i] << endl;
        len += lines[i].length();
    }
    out.close();
    // TODO: write lines to the file and output the number of bytes written.
}

void Buffer::showLines(int start, int end) const
{
    if (end > maxLine)
        throw range_error("Number range error");
    for (int i = start; i <= end; ++i)
    {
        cout << i << '\t' << lines[i] << endl;
    }
    // TODO: print lines according to the requirement.
}
void Buffer::deleteLines(int start, int end)
{
    if (start <= 0 || end > maxLine || start > end)
        throw range_error("Delete range error");
    for (int i = end + 1; i <= maxLine; ++i)
    {
        lines[i - end - 1 + start] = lines[i];
    }
    currentLine = start;
    maxLine -= end - start + 1;
    if (maxLine == 0)
    {
        currentLine = 0;
    }
}

void Buffer::insertLine(const string &text)
{

    for (int i = maxLine; i >= currentLine; i--)
    {
        lines[i + 1] = lines[i];
    }

    lines[currentLine] = text;
    maxLine++;

    // TODO: insert a line to current line.
}

void Buffer::appendLine(const string &text)
{
    if (maxLine >= MAX_LINE)
        throw out_of_range("move beyond the file line limit");
    for (int i = maxLine; i > currentLine; i--)
    {
        lines[i + 1] = lines[i];
    }
    lines[currentLine + 1] = text;
    maxLine++;
    currentLine++;
}