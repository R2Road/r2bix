#include "pch.h"
#include "r2base_ScreenBufferManager.h"

#include <cassert>
#include <Windows.h>

namespace r2base
{
	ScreenBufferManager::ScreenBufferManager() :
		mCoutOriginalStreamBuffer( nullptr )

		, mBufferHandle4First( INVALID_HANDLE_VALUE )
		, mCoutBufferRedirector4First( nullptr )

		, mBufferHandle4Second( INVALID_HANDLE_VALUE )
		, mCoutBufferRedirector4Second( nullptr )

		, mbFirst( true )
	{
		init();
	}
	ScreenBufferManager::~ScreenBufferManager()
	{
		release();
	}

	void ScreenBufferManager::init()
	{
		//
		// # 20220215 - R
		// Debug, Release ��� CreateConsoleScreenBuffer�� �����ص� ������ �ʴ´�.
		// SetConsoleActiveScreenBuffer�� INVALID_HANDLE_VALUE �� ���� �ƹ� �۵��� ���� �ʴ´�.
		//

		mCoutOriginalStreamBuffer = std::cout.rdbuf();


		mBufferHandle4First = GetStdHandle( STD_OUTPUT_HANDLE );
		assert( INVALID_HANDLE_VALUE != mBufferHandle4First );
		mCoutBufferRedirector4First = CoutBufferRedirector( mBufferHandle4First );

		CONSOLE_SCREEN_BUFFER_INFO csbi{};
		if( !GetConsoleScreenBufferInfo( mBufferHandle4First, &csbi ) )
		{
			assert( false && "Failed : GetConsoleScreenBufferInfo" );
		}


		mBufferHandle4Second = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE
			, 0//FILE_SHARE_WRITE | FILE_SHARE_READ
			, nullptr
			, CONSOLE_TEXTMODE_BUFFER
			, nullptr
		);
		assert( INVALID_HANDLE_VALUE != mBufferHandle4First );
		mCoutBufferRedirector4Second = CoutBufferRedirector( mBufferHandle4Second );

		if( !SetConsoleScreenBufferSize( mBufferHandle4Second, csbi.dwSize ) )
		{
			assert( false && "Failed : SetConsoleScreenBufferSize" );
		}
	}

	void ScreenBufferManager::release()
	{
		if( INVALID_HANDLE_VALUE != mBufferHandle4First )
		{
			SetConsoleActiveScreenBuffer( mBufferHandle4First );
			std::cout.rdbuf( mCoutOriginalStreamBuffer );
		}

		if( INVALID_HANDLE_VALUE != mBufferHandle4Second )
		{
			CloseHandle( mBufferHandle4Second );
		}
	}

	void ScreenBufferManager::ClearCurrentBuffer()
	{
		void* CurrentBufferHandle = nullptr;
		if( mbFirst )
		{
			CurrentBufferHandle = mBufferHandle4First;
		}
		else
		{
			CurrentBufferHandle = mBufferHandle4Second;
		}

		COORD top_left = { 0, 0 };
		CONSOLE_SCREEN_BUFFER_INFO cs_buffer_info{};
		DWORD out_result;
		GetConsoleScreenBufferInfo( CurrentBufferHandle, &cs_buffer_info );
		const DWORD length = cs_buffer_info.dwSize.X * cs_buffer_info.dwSize.Y;

		FillConsoleOutputCharacter( CurrentBufferHandle, TEXT( ' ' ), length, top_left, &out_result );

		SetConsoleCursorPosition( CurrentBufferHandle, top_left );
	}
	void ScreenBufferManager::Swap()
	{
		mbFirst = !mbFirst;

		if( mbFirst )
		{
			SetConsoleActiveScreenBuffer( mBufferHandle4First );
			std::cout.rdbuf( &mCoutBufferRedirector4First );
		}
		else
		{
			SetConsoleActiveScreenBuffer( mBufferHandle4Second );
			std::cout.rdbuf( &mCoutBufferRedirector4Second );
		}
	}
}