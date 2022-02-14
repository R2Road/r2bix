#include "pch.h"
#include "r2game_ScreenBufferManager.h"

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
		mBufferHandle4First = GetStdHandle( STD_OUTPUT_HANDLE );
		assert( INVALID_HANDLE_VALUE != mBufferHandle4First );

		CONSOLE_SCREEN_BUFFER_INFO csbi{};
		assert( GetConsoleScreenBufferInfo( mBufferHandle4First, &csbi ) && "Failed : GetConsoleScreenBufferInfo" );

		mBufferHandle4Second = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE
			, FILE_SHARE_WRITE | FILE_SHARE_READ
			, nullptr
			, CONSOLE_TEXTMODE_BUFFER
			, nullptr
		);
		assert( INVALID_HANDLE_VALUE != mBufferHandle4First );

		SetConsoleScreenBufferSize( mBufferHandle4Second, csbi.dwSize );
		{
			DWORD out_result;
			FillConsoleOutputCharacter( mBufferHandle4Second, TEXT( '2' ), csbi.dwSize.X * csbi.dwSize.Y, { 0, 0 }, &out_result );
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