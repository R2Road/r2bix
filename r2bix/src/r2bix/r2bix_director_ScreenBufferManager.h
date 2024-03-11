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

	public:
		ScreenBufferManager();
		~ScreenBufferManager();

		//
		//
		//
		void SetScreenBufferOffset( const short x, const short y )
		{
			mScreenBufferOffset.Set( x, y );
		}

	private:
		void init();
		void release();
		void setCursorVisibility( const bool visible );

	public:
		void InitCursor();
		void ClearCurrentBuffer();
		void Write2BackBuffer( const r2bix_render::Texture* const texture );
		void Swap();

	private:
		std::streambuf* mCoutOriginalStreamBuffer;

		HandleT mBufferHandle4First;
		CoutBufferRedirector mCoutBufferRedirector4First;

		HandleT mBufferHandle4Second;
		CoutBufferRedirector mCoutBufferRedirector4Second;

		bool mbFirst;

		r2::Point<short> mScreenBufferOffset;
	};
}