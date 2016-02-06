#include "objloader.h"
#include "objdata.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    ObjLoader loader{};
    ObjDataPtr odptr = loader.read_data("../data/suzanne.obj");

    switch (loader.error()) {
    case ObjLoader::ObjLoaderError::FileNotExists:
	cout << "File not exists" << endl;
    case ObjLoader::ObjLoaderError::FileReadError:
	cout << "File read error" << endl;
    case ObjLoader::ObjLoaderError::BadFileFormat:
	cout << "Bad file format" << endl;
	return EXIT_FAILURE;
    }
    
    if (loader.error() != ObjLoader::ObjLoaderError::None) {
	cout << "error" << endl;
	return EXIT_FAILURE;
    }
    
    for (int i = 0; i < odptr->vertices.size(); i += 3) {
	cout << "{" << odptr->vertices[i]
	     << ", " << odptr->vertices[i + 1]
	     << ", " << odptr->vertices[i + 2]
	     << "}" << endl;
    }

    for (int i = 0; i < odptr->normals.size(); i += 3) {
	cout << "{" << odptr->normals[i]
	     << ", " << odptr->normals[i + 1]
	     << ", " << odptr->normals[i + 2]
	     << "}" << endl;
    }    

    return 0;
}
