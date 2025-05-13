//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.04.12 PM.09.00
// # Version			: 1.3.0
//

#pragma once

#include <functional>

#include "r2_DummyInitialValue.h"

namespace r2
{
	template<typename T, typename U = DummyInitialValue<T>>
	class ValueWithHistory1AndCallback
	{
	public:
		using MyT = ValueWithHistory1AndCallback<T, U>;

		using ValueT = T;
		using InitialValueGeneratorT = U;

		using ChangedCallbackT = std::function<void( ValueT last_value, ValueT current_value )>;



		ValueWithHistory1AndCallback() : mCurrent( InitialValueGeneratorT{}() ), mLast( InitialValueGeneratorT{}() ), mChangedCallback()
		{
			ClearChangedCallback();
		}
		explicit ValueWithHistory1AndCallback( const ValueT& new_value ) : mCurrent( new_value ), mLast( new_value ), mChangedCallback()
		{
			ClearChangedCallback();
		}



		//
		// Operator
		//
		void operator=( const ValueT& new_value )
		{
			//
			// Update
			//
			mLast = mCurrent;
			mCurrent = new_value;

			//
			// Callback
			//
			( new_value == mLast ? void() : mChangedCallback( mLast, mCurrent ) );
		}
		void operator=( const MyT& other )
		{ 
			mLast = other.GetLast();
			mCurrent = other.GetCurrent();
			mChangedCallback = other.mChangedCallback;
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
		void SetChangedCallback( const ChangedCallbackT& callback )
		{
			mChangedCallback = callback;
		}
		void ClearChangedCallback()
		{
			static const ChangedCallbackT dummy = []( ValueT, ValueT ) {};
			mChangedCallback = dummy;
		}



	private:
		ValueT mCurrent;
		ValueT mLast;
		ChangedCallbackT mChangedCallback;
	};
}
