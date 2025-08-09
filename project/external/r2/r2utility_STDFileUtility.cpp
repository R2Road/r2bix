#include "r2utility_STDFileUtility.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>

#include "r2_Assert.h"

namespace r2utility
{
	bool STDFileUtility::IsEnable()
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
	bool STDFileUtility::Exist( const char* utf8_path )
	{
		return std::filesystem::exists( std::filesystem::path( utf8_path ) );
	}



	//
	// Directory
	//
	bool STDFileUtility::DirectoryOpen( const char* utf8_path )
	{
		if( !Exist( utf8_path ) )
		{
			return false;
		}

		std::string s( "explorer " );
		s += utf8_path;
		std::system( s.c_str() );

		return true;
	}



	//
	// File
	//
	void STDFileUtility::MakeFile( const char* utf8_path, const char* file_string )
	{
		std::ofstream fs( utf8_path, std::ios::out );
		if( fs.is_open() )
		{
			fs << file_string << std::endl;
		}

		fs.close();
	}
	bool STDFileUtility::Remove( const char* utf8_path )
	{
		return std::filesystem::remove( std::filesystem::path( utf8_path ) );
	}

	std::string STDFileUtility::GetFileString( const char* utf8_path )
	{
		std::string ret;

		//
		//
		//
		if( !Exist( utf8_path ) )
		{
			return ret;
		}

		//
		// Memory Allocate
		//
		const auto file_size = std::filesystem::file_size( utf8_path );
		ret.resize( file_size );

		//
		// Read 2 File
		//
		{
			std::FILE* file = nullptr;
			fopen_s( &file, utf8_path, "rb" ); // "r" 옵션으로 열면 \r\n /s 등의 문자들이 사라지고 파일 크기와 읽은 크기에 차이가 발생한다.
			if( !file )
			{
				return ret;
			}

			const size_t read_size = std::fread( &ret[0], 1, file_size, file );
			R2ASSERT( read_size == file_size, "" );
			( read_size != file_size ? ret.clear() : void() );

			fclose( file );
		}

		return ret;
	}
}