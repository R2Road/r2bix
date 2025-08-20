#include "r2util_string_converter.hpp"

#include <cstring>
#include <sstream>

namespace r2util
{
	int StringConverter::ToInt( const char* str )
	{
		int temp_value = 0;

		if( 0 != std::strlen( str ) )
		{
			static std::stringstream ss;
			ss.str( "" );
			ss.clear();
			ss << str;
			ss >> temp_value;

			if( ss.fail() )
			{
				temp_value = 0;
			}
		}

		return temp_value;
	}
	float StringConverter::ToFloat( const char* str )
	{
		float temp_value = 0.f;

		if( 0 != std::strlen( str ) )
		{
			static std::stringstream ss;
			ss.str( "" );
			ss.clear();
			ss << str;
			ss >> temp_value;

			if( ss.fail() )
			{
				temp_value = 0.f;
			}
		}

		return temp_value;
	}
}