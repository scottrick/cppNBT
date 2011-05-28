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
#include "nbtfile.h"

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
    TagCompound t("Balls");
    TagList l(TAG_SHORT, "Fibonacci");

    l.append(TagShort("", 1));
    l.append(TagShort("", 1));
    l.append(TagShort("", 2));
    l.append(TagShort("", 3));
    l.append(TagShort("", 5));

    t.insert(TagString("of", "steel"));
    t.insert(l);

    t.remove("Fbonacci");
    cout << "Created Tag with name '" << t.getName() << endl;

    cout << t.toString() << endl << endl;
    cout << "Dumping to NBT..." << endl;

    dumpTag(&t);

    NbtFile f;

    Tag *tc = t.clone();
    f.setRoot(*tc);
    f.write("out.nbt");

    dumpTag(tc);
    delete tc;

    return 0;
}
