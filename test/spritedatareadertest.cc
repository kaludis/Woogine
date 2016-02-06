#include "../src/spritedatareader.h"
#include "../src/spriterawdata.h"
#include "../src/debug.h"

#include <iostream>

using namespace std;

int main()
{
    SpriteDataReader sdr;
    SpriteRawDataPtr dptr = sdr.read_sprite_data("../textures/bob.dat");
    if (dptr) {
	cout << dptr->sprite_width << endl
	     << dptr->sprite_height << endl
	     << dptr->sprites_count << endl
	     << dptr->sprites_stride << endl
	     << dptr->sprites_rows << endl;
    } else {
	cout << "pointe is NULL\n";
    }
    return 0;
}
