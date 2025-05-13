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
	class ValueWithHistory1AndDirty
	{
	public:
		using MyT = ValueWithHistory1AndDirty<T, U>;

		using ValueT = T;
		using InitialValueGeneratorT = U;



		ValueWithHistory1AndDirty() : mCurrent( InitialValueGeneratorT{}( ) ), mLast( InitialValueGeneratorT{}() ), mbDirty( false )
		{}
		explicit ValueWithHistory1AndDirty( const ValueT& new_value ) : mCurrent( new_value ), mLast( new_value ), mbDirty( false )
		{}



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
			// Dirty
			//
			mbDirty = ( mLast == new_value ? mbDirty : true );
		}
		void operator=( const MyT& other )
		{
			mLast = other.GetLast();
			mCurrent = other.GetCurrent();
			mbDirty = other.IsDirty();
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

		bool IsDirty() const
		{
			return mbDirty;
		}



		//
		//
		//
		void Cleanup()
		{
			mbDirty = false;
		}



	private:
		ValueT mCurrent;
		ValueT mLast;
		bool mbDirty;
	};
}
