// g++ -std=c++11 `pkg-config freetype2 --cflags` textmanagertest.cc ../src/textmanager.cc ../src/debug.cc -o textmanagertest -lGL -lGLEW -lGLU -lfreetype `pkg-config freetype2 --libs

#include "../src/textmanager.h"
#include "../src/text.h"

#include <string>
#include <iostream>

using namespace std;

int main()
{
    TextManager tm{"../fonts/DroidSans.ttf"};

    string s{"Simple text"};

    auto it = s.begin();
    for (; it != s.end(); ++it) {
	cout << *it << endl;
	TextManager::Character ch = tm.character(*it);
	cout << ch.texture_id << endl;
	cout << ch.advance << endl;
    }
    cout << endl;
    
    return 0;
}
