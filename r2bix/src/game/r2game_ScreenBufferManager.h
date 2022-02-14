#pragma once

namespace r2game
{
	class ScreenBufferManager
	{
	private:
		using HandleT = void*;

	public:
		ScreenBufferManager();
		~ScreenBufferManager();

	private:
		void Init();
		void Close();

	public:
		void Swap();

	private:
		HandleT mBufferHandle4First;
		HandleT mBufferHandle4Second;
		bool mbFirst;
	};
}