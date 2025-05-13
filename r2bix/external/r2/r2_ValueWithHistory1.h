//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.04.12 PM.04.50
// # Version			: 1.2.0
//

#pragma once

#include "r2_DummyInitialValue.h"

namespace r2
{
	template<typename T, typename U = DummyInitialValue<T>>
	class ValueWithHistory1
	{
	public:
		using MyT = ValueWithHistory1<T, U>;

		using ValueT = T;
		using InitialValueGeneratorT = U;



		ValueWithHistory1() : mCurrent( InitialValueGeneratorT{}( ) ), mLast( InitialValueGeneratorT{}() )
		{}
		explicit ValueWithHistory1( const ValueT& new_value ) : mCurrent( new_value ), mLast( new_value )
		{}



		//
		// Operator
		//
		void operator=( const ValueT& new_value )
		{
			mLast = mCurrent;
			mCurrent = new_value;
		}
		void operator=( const MyT& other )
		{
			mLast = other.GetLast();
			mCurrent = other.GetCurrent();
		}



		//
		//
		//
		ValueT& GetCurrent()
		{
			return mCurrent;
		}
		const ValueT& GetCurrent() const
		{
			return mCurrent;
		}
		ValueT& GetLast()
		{
			return mLast;
		}
		const ValueT& GetLast() const
		{
			return mLast;
		}



	private:
		ValueT mCurrent;
		ValueT mLast;
	};
}
