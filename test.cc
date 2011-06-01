/******************************************************************************
 *
 *  Test file (test.cc)
 *  ---
 *  ... just some testing
 *
 *  Created: 02.02.2011 03:25:14
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#include <iostream>

#include "src/cppnbt.h"
#include "src/nbtfile.h"

using namespace std;
using namespace nbt;

void dumpTag(Tag *t)
{
    nbt::ByteArray b = t->toByteArray();

    for (size_t i = 0; i < b.size(); ++i)
    {
        cout << "0x";
        cout.width(2);
        cout.fill('0');
        cout << hex << (int)b[i] << " ";
    }

    cout << endl;
}

int main(int argc, char **argv)
{
    NbtFile f;

    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <nbtfile>" << std::endl;
        return 1;
    }

    try
    {
        f.open(argv[1]);
        f.read();

        Tag *root = f.getRoot();
        std::cout << root->toString() << std::endl;

    }
    catch (GzipIOException &gzioe)
    {
        std::cerr << "Unable to load NBT file " << argv[1] << ": "
        		  << gzioe.getCode() << std::endl;
    }

    return 0;
}
