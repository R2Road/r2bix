#pragma once

namespace r2utility
{
	class StringUtility
	{
	private:
		StringUtility() = delete;

	public:
		static int ToInt( const char* str );
		static float ToFloat( const char* str );
	};
}