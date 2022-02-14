#include "pch.h"
#include "r2game_ScreenBufferManager.h"

#include <cassert>
#include <Windows.h>

namespace r2game
{
	ScreenBufferManager::ScreenBufferManager() : mBufferHandle4First( nullptr ), mBufferHandle4Second( nullptr ), mbFirst( true )
	{}

	void ScreenBufferManager::Init()
	{
		mBufferHandle4First = GetStdHandle( STD_OUTPUT_HANDLE );
		CONSOLE_SCREEN_BUFFER_INFO first_csbi{};
		{
			assert( GetConsoleScreenBufferInfo( mBufferHandle4First, &first_csbi ) && "Failed : GetConsoleScreenBufferInfo" );
		}

		mBufferHandle4Second = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE
			, FILE_SHARE_WRITE | FILE_SHARE_READ
			, nullptr
			, CONSOLE_TEXTMODE_BUFFER
			, nullptr
		);
		SetConsoleScreenBufferSize( mBufferHandle4Second, first_csbi.dwSize );
		{
			DWORD out_result;
			FillConsoleOutputCharacter( mBufferHandle4Second, TEXT( '2' ), first_csbi.dwSize.X * first_csbi.dwSize.Y, { 0, 0 }, &out_result );
		}
	}

	void ScreenBufferManager::Close()
	{
		if( nullptr != mBufferHandle4First )
		{
			SetConsoleActiveScreenBuffer( mBufferHandle4First );
		}

		if( nullptr != mBufferHandle4Second )
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