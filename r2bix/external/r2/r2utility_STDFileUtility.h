//
// # Version Rule
// - 1.0.0 : ��� ����
// - 0.1.0 : ����ڰ� �ڵ带 �ٲ� ������ ��ȭ
// - 0.0.1 : ������ ��ȭ
//
// # Last Update		: 2023.07.02 PM.09.48
// # Version			: 1.0.0
//

#pragma once

#include <string>

namespace r2utility
{
	class STDFileUtility
	{
	private:
		STDFileUtility() = delete;

	public:
		static bool IsEnable();

		//
		//
		//
		static bool Exist( const char* utf8_path );

		//
		// Directory
		//
		static bool DirectoryOpen( const char* utf8_path );

		//
		// File
		//
		static void MakeFile( const char* utf8_path, const char* file_string );
		static bool Remove( const char* utf8_path );

		static std::string GetFileString( const char* utf8_path );
	};
}
