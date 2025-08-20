#pragma once

namespace r2util
{
	class StringConverter
	{
	private:
		StringConverter() = delete;

	public:
		static int ToInt( const char* str );
		static float ToFloat( const char* str );
	};
}