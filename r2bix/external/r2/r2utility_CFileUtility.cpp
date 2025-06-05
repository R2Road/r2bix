#include "r2utility_CFileUtility.h"

#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <direct.h>

#include "r2_Assert.h"

namespace r2utility
{
	bool CFileUtility::IsEnable()
	{
#if _WIN64 == 1 || _WIN32 == 1
		return true;
#elif
		return false;
#endif
	}



	//
	//
	//
	bool CFileUtility::Exist( const char* utf8_path )
	{
		struct stat s = { 0 };
		return 0 == stat( utf8_path, &s );
	}



	//
	// Directory
	//
	bool CFileUtility::CurrentDirectory( char* out_string, const int out_string_size )
	{
		return( nullptr != _getcwd( out_string, out_string_size ) );
	}
	bool CFileUtility::DirectoryOpen( const char* utf8_path )
	{
		if( !Exist( utf8_path ) )
		{
			return false;
		}

		char terminal_command[256] = {};
		sprintf_s( terminal_command, "explorer %s", utf8_path );
		system( terminal_command );

		return true;
	}



	//
	// File
	//
	int CFileUtility::FileSize( const char* utf8_path )
	{
		struct stat s = { 0 };
		if( 0 != stat( utf8_path, &s ) )
		{
			return 0;
		}

		return s.st_size;
	}
	void CFileUtility::MakeFile( const char* utf8_path, const char* file_string )
	{
		FILE* fp = nullptr;
		if( 0 == fopen_s( &fp, utf8_path, "w" ) )
		{
			fprintf( fp, file_string );
		}

		if( nullptr != fp )
		{
			fclose( fp );
		}
	}
	bool CFileUtility::Remove( const char* utf8_path )
	{
		return( 0 == remove( utf8_path ) );
	}

	bool CFileUtility::GetFileString( const char* utf8_path, char* out_string, const int out_string_size )
	{
		//
		//
		//
		struct stat s = { 0 };
		if( 0 != stat( utf8_path, &s ) )
		{
			return false;
		}

		//
		//
		//
		memset( out_string, 0, out_string_size );

		//
		// Read 2 File
		//
		{
			FILE* file = nullptr;
			fopen_s( &file, utf8_path, "rb" ); // "r" 옵션으로 열면 \r\n /s 등의 문자들이 사라지고 파일 크기와 읽은 크기에 차이가 발생한다.
			if( !file )
			{
				return false;
			}

			const size_t read_size = fread( out_string, 1, out_string_size, file );
			R2ASSERT( s.st_size == read_size, "" );
			( s.st_size != read_size ? memset( out_string, 0, out_string_size ) : nullptr );

			fclose( file );
		}

		return true;
	}
}