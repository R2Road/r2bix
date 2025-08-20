#include "r2util_c_file.hpp"

#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <direct.h>

#include "r2_assert.hpp"

namespace r2util
{
	bool C_File::IsEnable()
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
	bool C_File::Exist( const char* utf8_path )
	{
		struct stat s = { 0 };
		return 0 == stat( utf8_path, &s );
	}



	//
	// Directory
	//
	bool C_File::CurrentDirectory( char* out_string, const int out_string_size )
	{
		return( nullptr != _getcwd( out_string, out_string_size ) );
	}
	bool C_File::DirectoryOpen( const char* utf8_path )
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
	int C_File::FileSize( const char* utf8_path )
	{
		struct stat s = { 0 };
		if( 0 != stat( utf8_path, &s ) )
		{
			return 0;
		}

		return s.st_size;
	}
	void C_File::MakeFile( const char* utf8_path, const char* file_string )
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
	bool C_File::Remove( const char* utf8_path )
	{
		return( 0 == remove( utf8_path ) );
	}

	bool C_File::GetFileString( const char* utf8_path, char* out_string, const int out_string_size )
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