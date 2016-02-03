#include "imageloader.h"

#include <iostream>

using namespace std;

int main()
{
    ImageLoader iloader{};
    ImageLoader::ImageData image_data = iloader.read_data("saved.png");
    if (!iloader.write_data("saved2.png", image_data)) {
	cout << "Save file: Error" << endl;
    }
    
    return 0;
}
