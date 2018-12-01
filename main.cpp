// main.cpp
// by Benjamin Rausch

#include "CompleteMaze.h"
#include <iostream>
#include <string.h>
#include <cassert>
#include <stack>

using namespace std;

const char HELP_FLAG[3] = "-h";
const char LENGTH_FLAG[3] = "-l";
const char WIDTH_FLAG[3] = "-w";

int main(int argc, char **argv)
{
    stack<char*> args;
    bool helpFlagSet = false;
    bool widthSet = false;
    unsigned long width;
    bool lengthSet = false;
    unsigned long length;
    bool thereIsInputError = false;
    // add to stack all arguments besides the name of the program
    for (int i = argc - 1; i > 0; --i) {
        args.push(argv[i]);
    }
    char *item;
    // Process arguments
    while (!args.empty())
    {
        item = args.top();
        args.pop();
        if (strcmp(item, HELP_FLAG) == 0)
        {
            helpFlagSet = true;
        }
        else if (strcmp(item, WIDTH_FLAG) == 0)
        {
            if (args.empty())
            {
                cout << "ERROR: missing operand to '-w' flag" << '\n';
                thereIsInputError = true;
                break;
            }
            string widthString = args.top();
            args.pop();
            width = stoul(widthString);
            if (!(width > 0))
            {
                cout << "ERROR: width must be greater than zero." << '\n';
                thereIsInputError = true;
                break;
            }
            widthSet = true;
        }
        else if (strcmp(item, LENGTH_FLAG) == 0)
        {
            if (args.empty())
            {
                cout << "ERROR: missing operand to '-l' flag" << '\n';
                thereIsInputError = true;
                break;
            }
            string lengthString = args.top();
            args.pop();
            length = stoul(lengthString);
            if (!(length > 0))
            {
                cout << "ERROR: length must be greater than zero." << '\n';
                thereIsInputError = true;
                break;
            }
            lengthSet = true;
        }
        else
        {
            cout << "ERROR: unrecognized argument '" << item << "'." << '\n';
            thereIsInputError = true;
            break;
        }
    }
    if (!widthSet && !thereIsInputError && !helpFlagSet) {
        cout << "ERROR: width was not set." << '\n'; 
        thereIsInputError = true;
    }
    if (!lengthSet && !thereIsInputError && !helpFlagSet) {
        cout << "ERROR: length was not set." << '\n';
        thereIsInputError = true;
    }

    if (thereIsInputError)
    {
        cout << "Try '-h' for help." << '\n';
        return 0;
    }

    if (helpFlagSet) {
        if (widthSet || lengthSet) {
            cout << "ERROR: The help flag '-h' must be called by itself." << '\n';
        }
        else
        {
            cout << "MAZE MAKER 4000, v1.1" << '\n' << '\n';
            cout << "Normal Usage: " << argv[0] << " -l [NUMBER] -w [NUMBER]" << '\n';
            cout << '\n';
            cout << "-h             // help" << '\n';
            cout << "-l [NUMBER]    // maze length" << '\n';
            cout << "-w [NUMBER]    // maze width" << '\n';
        }
        return 0;
    }

    stuff::CompleteMaze myMaze(width, length);
    cout << myMaze;
    return 0;
}
