#pragma once

namespace r2game
{
	class ScreenBufferManager
	{
	private:
		using HandleT = void*;

	public:
		ScreenBufferManager();

		void Init();
		void Close();

		void Swap();

	private:
		HandleT mBufferHandle4First;
		HandleT mBufferHandle4Second;
		bool mbFirst;
	};
}