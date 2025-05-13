//
// # Version Rule
// - 1.0.0 : ��� ����
// - 0.1.0 : ����ڰ� �ڵ带 �ٲ� ������ ��ȭ
// - 0.0.1 : ������ ��ȭ
//
// # Last Update		: 2023.04.12 PM.04.50
// # Version			: 1.2.0
//

#pragma once

#include "r2_DummyInitialValue.h"

namespace r2
{
	template<typename T, typename U = DummyInitialValue<T>>
	class ValueWithDirty
	{
	public:
		using MyT = ValueWithDirty<T, U>;

		using ValueT = T;
		using InitialValueGeneratorT = U;



		ValueWithDirty() : mValue( InitialValueGeneratorT{}() ), mbDirty( false )
		{}
		explicit ValueWithDirty( const ValueT& new_value ) : mValue( new_value ), mbDirty( false )
		{}



		//
		// Operator
		//
		void operator=( const ValueT& new_value )
		{
			if( new_value == mValue )
			{
				return;
			}

			mValue = new_value;
			mbDirty = true;
		}
		void operator=( const MyT& other )
		{
			mValue = other.Get();
			mbDirty = other.IsDirty();
		}



		//
		//
		//
		ValueT& Get()
		{
			return mValue;
		}
		const ValueT& Get() const
		{
			return mValue;
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
		ValueT mValue;
		bool mbDirty;
	};
}
