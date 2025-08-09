//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.07.02 PM.10.02
// # Version			: 1.1.0
//

#pragma once

namespace r2utility
{
	class CFileUtility
	{
	private:
		CFileUtility() = delete;

	public:
		static bool IsEnable();

		//
		//
		//
		static bool Exist( const char* utf8_path );

		//
		// Directory
		//
		static bool CurrentDirectory( char* out_string, const int out_string_size );
		static bool DirectoryOpen( const char* utf8_path );

		//
		// File
		//
		static int FileSize( const char* utf8_path );
		static void MakeFile( const char* utf8_path, const char* file_string );
		static bool Remove( const char* utf8_path );

		static bool GetFileString( const char* utf8_path, char* out_string, const int out_string_size );
	};
}
