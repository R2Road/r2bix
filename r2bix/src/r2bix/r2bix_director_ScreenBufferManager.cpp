#include "r2bix_director_ScreenBufferManager.h"

#include <cassert>
#include <iostream>
#include <Windows.h>

//
// for Windows.h
// - wtf... o_o;;;
//
#undef min
#undef max

#include "r2bix_render_Texture.h"

namespace r2bix_director
{
	ScreenBufferManager::ScreenBufferManager() :
		  mBufferHandleOriginal( INVALID_HANDLE_VALUE )
		, mCoutOriginalStreamBuffer( nullptr )

		, mBufferHandleList()
		, mCoutBufferRedirectorList()

		, mCurrentBufferIndex( 0 )

		, mScreenBufferOffset()
	{
		init();
	}

	ScreenBufferManager::ScreenBufferManager( const short x, const short y ) :
		  mBufferHandleOriginal( INVALID_HANDLE_VALUE )
		, mCoutOriginalStreamBuffer( nullptr )

		, mBufferHandleList()
		, mCoutBufferRedirectorList()

		, mCurrentBufferIndex( 0 )

		, mScreenBufferOffset( x, y )
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

		mBufferHandleOriginal = GetStdHandle( STD_OUTPUT_HANDLE );
		mCoutOriginalStreamBuffer = std::cout.rdbuf();


		mBufferHandleList[0] = GetStdHandle( STD_OUTPUT_HANDLE );
		assert( INVALID_HANDLE_VALUE != mBufferHandleList[0] );
		mCoutBufferRedirectorList[0] = CoutBufferRedirector(mBufferHandleList[0]);

		CONSOLE_SCREEN_BUFFER_INFO csbi{};
		if( !GetConsoleScreenBufferInfo( mBufferHandleList[0], &csbi ) )
		{
			assert( false && "Failed : GetConsoleScreenBufferInfo" );
		}


		mBufferHandleList[1] = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE
			, 0//FILE_SHARE_WRITE | FILE_SHARE_READ
			, nullptr
			, CONSOLE_TEXTMODE_BUFFER
			, nullptr
		);
		assert( INVALID_HANDLE_VALUE != mBufferHandleList[1] );
		mCoutBufferRedirectorList[1] = CoutBufferRedirector(mBufferHandleList[1]);

		if( !SetConsoleScreenBufferSize( mBufferHandleList[1], csbi.dwSize ) )
		{
			assert( false && "Failed : SetConsoleScreenBufferSize" );
		}

		//
		// Cursor
		//
		{
			setCursorVisibility( false );
		}
	}

	void ScreenBufferManager::release()
	{
		setCursorVisibility( true );

		//
		// Rollback
		//
		if( INVALID_HANDLE_VALUE != mBufferHandleOriginal )
		{
			SetConsoleActiveScreenBuffer( mBufferHandleOriginal );
			std::cout.rdbuf( mCoutOriginalStreamBuffer );
		}

		//
		// Close Handle List
		//
		for( int i = 1; BUFFER_COUNT > i; ++i )
		{
			CloseHandle( mBufferHandleList[i] );
		}
	}
	void ScreenBufferManager::setCursorVisibility( const bool visible )
	{
		CONSOLE_CURSOR_INFO cursorInfo;

		for( int i = 0; BUFFER_COUNT > i; ++i )
		{
			if( INVALID_HANDLE_VALUE != mBufferHandleList[i] )
			{
				GetConsoleCursorInfo( mBufferHandleList[i], &cursorInfo );
				cursorInfo.bVisible = visible;
				SetConsoleCursorInfo( mBufferHandleList[i], &cursorInfo );
			}
		}
	}

	void ScreenBufferManager::InitCursor()
	{
		void* current_buffer_handle = mBufferHandleList[mCurrentBufferIndex];

		const COORD top_left = { 0, 0 };
		SetConsoleCursorPosition( current_buffer_handle, top_left );
	}

	void ScreenBufferManager::ClearCurrentBuffer()
	{
		void* current_buffer_handle = mBufferHandleList[mCurrentBufferIndex];

		const COORD top_left = { mScreenBufferOffset.GetX(), mScreenBufferOffset.GetY() };
		CONSOLE_SCREEN_BUFFER_INFO cs_buffer_info{};
		DWORD out_result;
		GetConsoleScreenBufferInfo( current_buffer_handle, &cs_buffer_info );
		const DWORD length = cs_buffer_info.dwSize.X * cs_buffer_info.dwSize.Y;

		FillConsoleOutputCharacter( current_buffer_handle, TEXT( ' ' ), length, top_left, &out_result );

		SetConsoleCursorPosition( current_buffer_handle, top_left );
	}

	void ScreenBufferManager::Write2BackBuffer( const r2bix_render::Texture* const texture )
	{
		int next_buffer_index = mCurrentBufferIndex + 1;
		if( BUFFER_COUNT <= next_buffer_index )
		{
			next_buffer_index = 0;
		}

		void* const next_buffer_handle = mBufferHandleList[next_buffer_index];

		const COORD write_offset_coord = { mScreenBufferOffset.GetX(), mScreenBufferOffset.GetY() };
		COORD current_write_coord;
		DWORD out_result;

		std::string_view output_line;
		const r2bix::ColorValue* color_line;
		for( SHORT y = 0, end_y = static_cast< SHORT >( texture->GetHeight() ); end_y > y; ++y )
		{
			current_write_coord = write_offset_coord;
			current_write_coord.Y += y;

			//
			// Character
			//
			output_line = texture->GetCharacterLine( static_cast< uint32_t >( y ) );
			WriteConsoleOutputCharacterA( next_buffer_handle, output_line.data(), static_cast< DWORD >( output_line.length() ), current_write_coord, &out_result );

			//
			// Color
			//
			color_line = texture->GetColorLine( static_cast< uint32_t >( y ) );
			WriteConsoleOutputAttribute( next_buffer_handle, ( WORD* )( color_line ), static_cast< DWORD >( output_line.length() ), current_write_coord, &out_result );
		}
	}

	void ScreenBufferManager::Swap()
	{
		//
		// Update Index
		//
		++mCurrentBufferIndex;
		if( BUFFER_COUNT <= mCurrentBufferIndex )
		{
			mCurrentBufferIndex = 0;
		}

		//
		// Swap
		//
		SetConsoleActiveScreenBuffer( mBufferHandleList[mCurrentBufferIndex] );
		std::cout.rdbuf( &mCoutBufferRedirectorList[mCurrentBufferIndex] );
	}
}