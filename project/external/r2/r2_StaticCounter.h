#pragma once

#include "r2_Log.h"

namespace r2
{
	template<typename Owner_T>
	class StaticCounter
	{
	private:
		using OwnerT = Owner_T;
		using ValueT = unsigned long long;



	public:
		StaticCounter() : mCount( 0ull )
		{}
	private:
		static StaticCounter& getInstance()
		{
			static StaticCounter instance;
			return instance;
		}



	public:
		static void Increase()
		{
			++getInstance().mCount;
		}
		static void Clear()
		{
			getInstance().mCount = 0;
		}
		static void Capture()
		{
			getInstance().mCapture = getInstance().mCount;
		}



		static void PrintCount( const char* str = "" )
		{
			R2LOG( "[%s] SC : count : %llud", str, getInstance().mCount );
		}
		static void PrintCapture( const char* str = "" )
		{
			R2LOG( "[%s] SC : capture : %llud", str, getInstance().mCapture );
		}



	private:
		ValueT mCount;
		ValueT mCapture;
	};
}