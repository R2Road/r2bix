//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.05.20 PM.02.25
// # Version			: 1.3.0.0
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



		//
		//
		//
		bool IsChanged() const
		{
			return ( mLast != mCurrent );
		}



	private:
		ValueT mCurrent;
		ValueT mLast;
	};
}
