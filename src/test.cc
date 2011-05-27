/******************************************************************************
 *
 *  Balls (test.cc)
 *  ---
 *  Have you seen 'em?
 *
 *  Created: 02.02.2011 03:25:14
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#include <iostream>

#include "tags.h"

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
    TagCompound t("Root");

    t.insert(TagShort("Age", 21));
    cout << "Created Tag with name '" << t.getName() << endl;

    cout << t.toString() << endl << endl;
    cout << "Dumping to NBT..." << endl;

    dumpTag(&t);

    Tag *tc = t.clone();
    dumpTag(tc);
    delete tc;

    return 0;
}
