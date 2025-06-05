//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.05.22 PM.05.30
// # Version			: 1.5.0.0
//

#pragma once

namespace r2
{
	template<typename Property_T>
	class Value
	{
	public:
		using PropertyT = Property_T;



		Value() noexcept :
			  mLast( 0 )
			, mCurrent( 0 )
			, mChanges( 0 )
		{}



		//
		// Operator
		//
		bool operator=( const PropertyT new_value ) noexcept
		{
			return Assign( new_value );
		}
		bool operator+=( const PropertyT new_value ) noexcept
		{
			return Plus( new_value );
		}
		bool operator-=( const PropertyT new_value ) noexcept
		{
			return Minus( new_value );
		}

		//
		// Getter
		//
		PropertyT GetLast() const noexcept
		{
			return mLast;
		}
		PropertyT GetCurrent() const noexcept
		{
			return mCurrent;
		}
		PropertyT GetChanges() const noexcept
		{
			return mChanges;
		}
		bool IsChanged() const noexcept
		{
			return ( mLast != mCurrent );
		}

		//
		//
		//
		void Init() noexcept
		{
			mLast = 0;
			mCurrent = 0;
			mChanges = 0;
		}
		void Clean() noexcept
		{
			mLast = mCurrent;
			mChanges = 0;
		}
		bool Assign( const PropertyT changes ) noexcept
		{
			const bool last_changed = IsChanged();

			mLast = ( last_changed ? mLast : mCurrent );
			mCurrent = changes;
			mChanges = ( last_changed ? mCurrent - mLast : changes );

			return IsChanged();
		}
		bool Plus( const PropertyT changes ) noexcept
		{
			const bool last_changed = IsChanged();

			mLast = ( last_changed ? mLast : mCurrent );
			mCurrent += changes;
			mChanges = ( last_changed ? mChanges + changes : changes );

			return IsChanged();
		}
		bool Minus( const PropertyT changes ) noexcept
		{
			const bool last_changed = IsChanged();

			mLast = ( last_changed ? mLast : mCurrent );
			mCurrent -= changes;
			mChanges = ( last_changed ? mChanges - changes : -changes );

			return IsChanged();
		}

	private:
		PropertyT mLast;
		PropertyT mCurrent;
		PropertyT mChanges;
	};
}
