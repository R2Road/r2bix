#pragma once

#include "r2/r2_Point.h"

#include "r2bix_director_CoutBufferRedirector.h"

namespace r2bix_render
{
	class Texture;
}

namespace r2bix_director
{
	class ScreenBufferManager
	{
	private:
		using HandleT = void*;
		enum { BUFFER_COUNT = 2 };

	public:
		ScreenBufferManager();
		ScreenBufferManager( const short x, const short y );
		~ScreenBufferManager();

	private:
		void init();
		void release();

	public:
		void SetCursorVisibility( const bool visible );
		void SetCursorPosition( const short x, const short y );
		void SetCursorPosition_0_0();
		void ClearCurrentBuffer();
		void Write2BackBuffer( const r2bix_render::Texture* const texture );
		void Swap();

		void ShowOriginalBuffer();
		void CloseOriginalBuffer();

	private:
		HandleT mBufferHandleOriginal;
		std::streambuf* mCoutOriginalStreamBuffer;

		HandleT mBufferHandleList[BUFFER_COUNT];
		CoutBufferRedirector mCoutBufferRedirectorList[BUFFER_COUNT];

		int mCurrentBufferIndex;

		r2::Point<short> mScreenBufferOffset;
	};
}