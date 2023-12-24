#include "Item.h"

void Item::Init()
{
	symbol = '\x05';
	overrideColor = 4;
	/*'\x0E' (U+2605)
'\x0F' (U+2606)
'\x06' (U+2660)
'\x05' (U+2663)
'\x03' (U+2665)
'\x04' (U+2666)*/
}

void Item::Update(float deltaTime)
{
}
