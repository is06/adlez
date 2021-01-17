#include <iostream>
#include <SDL2/SDL.h>

#include "game.h"
#include "asefileloader.h"

using namespace std;

int main()
{
    try {
        //Game::run();
        AseFileLoader loader = AseFileLoader();
        AseFile* file = loader.load("test");
        delete file;
    }  catch (const exception& e) {
        cerr << "An exception occurred: " + string(e.what()) << endl;
        return 1;
    }

    return 0;
}
