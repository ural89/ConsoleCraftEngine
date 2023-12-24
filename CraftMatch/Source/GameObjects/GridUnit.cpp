#include "GridUnit.h"
#include <vector>
void GridUnit::Init()
{
	sprite = {  {1,1,1,1,1},
				{1,0,0,0,1},
				{1,0,0,0,1},
				{1,1,1,1,1}
	};
	symbol = '\xDB';
	
}

void GridUnit::OnSelected()
{
	overrideColor = 3;
}
