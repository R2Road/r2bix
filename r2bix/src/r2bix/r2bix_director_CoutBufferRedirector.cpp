#include "r2bix_director_CoutBufferRedirector.h"

#include <Windows.h>

namespace r2bix_director
{
	CoutBufferRedirector::CoutBufferRedirector() : mHandle( INVALID_HANDLE_VALUE )
	{}

	CoutBufferRedirector::CoutBufferRedirector( HandleT handle ) : mHandle( handle )
	{}

	std::streambuf::int_type CoutBufferRedirector::overflow( std::streambuf::int_type c )
	{
		//
		// INVALID_HANDLE_VALUE 를 Handle 로 사용해도 Debug/Release 아무 문제 없다.
		//

		if( c != EOF )
		{
			DWORD written;
			WriteConsole( mHandle, &c, 1, &written, nullptr );
		}

		return c;
	}

	std::streamsize CoutBufferRedirector::xsputn( std::streambuf::char_type const *s, std::streamsize count )
	{
		//
		// INVALID_HANDLE_VALUE 를 Handle 로 사용해도 Debug/Release 아무 문제 없다.
		//

		DWORD written;
		WriteConsoleA( mHandle, s, static_cast<DWORD>( count ), &written, nullptr );
		return written;
	}
}