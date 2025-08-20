#include "r2util_string_builder.hpp"

#include <stdarg.h> // va
#include <stdio.h> // vsnprintf

namespace r2util
{
	namespace StringBuilder
	{
		const char* Build( const char* format_string, ... )
		{
			static char buffer[256] = { 0, };

			va_list argList;
			va_start( argList, format_string );

			vsnprintf( buffer, 256, format_string, argList );

			va_end( argList );

			return buffer;
		}

		const char* Build( const int value )
		{
			return Build( "%d", value );
		}
	}
}