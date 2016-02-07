// g++ -std=c++11 `pkg-config freetype2 --cflags` textmanagertest.cc ../src/textmanager.cc ../src/debug.cc -o textmanagertest -lGL -lGLEW -lGLU -lfreetype `pkg-config freetype2 --libs

#include "../src/textmanager.h"

int main()
{
    TextManager tm{"../fonts/DroidSans.ttf"};

    return 0;
}
