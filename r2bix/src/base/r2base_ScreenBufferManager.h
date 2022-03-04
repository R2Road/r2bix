#pragma once

#include "r2base_CoutBufferRedirector.h"

namespace r2base
{
	class ScreenBufferManager
	{
	private:
		using HandleT = void*;

	public:
		ScreenBufferManager();
		~ScreenBufferManager();

	private:
		void init();
		void release();

	public:
		void ClearCurrentBuffer();
		void Swap();

	private:
		std::streambuf* mCoutOriginalStreamBuffer;

		HandleT mBufferHandle4First;
		CoutBufferRedirector mCoutBufferRedirector4First;

		HandleT mBufferHandle4Second;
		CoutBufferRedirector mCoutBufferRedirector4Second;

		bool mbFirst;
	};
}