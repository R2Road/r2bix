#include "pch.h"
#include "Utility4Test.h"

#include <Windows.h>

void Utility4Test::DrawRect( const int offset_y, const r2::RectInt& rect, const char c )
{
	HANDLE stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );

	for( int y = rect.GetMinY(); rect.GetMaxY() >= y; ++y )
	{
		for( int x = rect.GetMinX(); rect.GetMaxX() >= x; ++x )
		{
			SetConsoleCursorPosition( stdHandle, { static_cast<short>( x ), static_cast<short>( offset_y + y ) } );

			std::cout << c;
		}
	}
}

void Utility4Test::DrawRectInfo_Min_Max( const r2::RectInt& rect )
{
	std::cout << r2::tab << "rect min, max :" << " " << rect.GetMinX() << " " << rect.GetMinY() << " " << rect.GetMaxX() << " " << rect.GetMaxY() << r2::linefeed;
}