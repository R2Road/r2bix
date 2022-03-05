#include "pch.h"
#include "r2base_ScreenBufferManager.h"

#include <cassert>
#include <Windows.h>

#include "render/r2render_Texture.h"

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
		// Debug, Release 모두 CreateConsoleScreenBuffer에 실패해도 터지지 않는다.
		// SetConsoleActiveScreenBuffer에 INVALID_HANDLE_VALUE 가 들어가면 아무 작동도 하지 않는다.
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
		void* current_buffer_handle = nullptr;
		if( mbFirst )
		{
			current_buffer_handle = mBufferHandle4First;
		}
		else
		{
			current_buffer_handle = mBufferHandle4Second;
		}

		COORD top_left = { 0, 0 };
		CONSOLE_SCREEN_BUFFER_INFO cs_buffer_info{};
		DWORD out_result;
		GetConsoleScreenBufferInfo( current_buffer_handle, &cs_buffer_info );
		const DWORD length = cs_buffer_info.dwSize.X * cs_buffer_info.dwSize.Y;

		FillConsoleOutputCharacter( current_buffer_handle, TEXT( ' ' ), length, top_left, &out_result );

		SetConsoleCursorPosition( current_buffer_handle, top_left );
	}

	void ScreenBufferManager::Write2BackBuffer( const r2render::Texture* const texture )
	{
		void* back_buffer_handle = nullptr;
		if( !mbFirst )
		{
			back_buffer_handle = mBufferHandle4First;
		}
		else
		{
			back_buffer_handle = mBufferHandle4Second;
		}

		COORD write_pivot = { 0, 0 };
		DWORD out_result;

		std::string_view output_line;
		for( SHORT y = 0, end_y = static_cast<SHORT>( texture->GetHeight() ); end_y > y; ++y )
		{
			write_pivot.Y = y;
			output_line = texture->GetLine( static_cast<uint32_t>( y ) );
			WriteConsoleOutputCharacterA( back_buffer_handle, output_line.data(), static_cast<DWORD>( output_line.length() ), write_pivot, &out_result );
		}
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