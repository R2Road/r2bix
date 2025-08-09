#include "r2bix_utility_InputUtil.h"

#include <conio.h>

namespace r2bix_utility
{
	void ClearCInputBuffer()
	{
		while( _kbhit() )
		{
			_getch();
		}
	}
}
