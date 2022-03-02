#include "pch.h"
#include "r2base_ScreenBufferManager.h"

#include <cassert>
#include <Windows.h>

namespace r2game
{
	ScreenBufferManager::ScreenBufferManager() : mBufferHandle4First( INVALID_HANDLE_VALUE ), mBufferHandle4Second( INVALID_HANDLE_VALUE ), mbFirst( true )
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
		// Debug, Release 모두 CreateConsoleScreenBuffer에 실패해도 터지지 않는다.
		// SetConsoleActiveScreenBuffer에 INVALID_HANDLE_VALUE 가 들어가면 아무 작동도 하지 않는다.
		//

		mBufferHandle4First = GetStdHandle( STD_OUTPUT_HANDLE );
		assert( INVALID_HANDLE_VALUE != mBufferHandle4First );

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
		}

		if( INVALID_HANDLE_VALUE != mBufferHandle4Second )
		{
			CloseHandle( mBufferHandle4Second );
		}
	}

	void ScreenBufferManager::Swap()
	{
		mbFirst = !mbFirst;

		if( mbFirst )
		{
			SetConsoleActiveScreenBuffer( mBufferHandle4First );
		}
		else
		{
			SetConsoleActiveScreenBuffer( mBufferHandle4Second );
		}
	}
}