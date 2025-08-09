//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.05.09 PM.02.34
// # Version			: 1.0.0
//

#pragma once

namespace r2
{
	template<typename Owner_T, typename Index_T = unsigned long long, Index_T Start_Value = 1, Index_T Invalid_Value = 0>
	class UniqueIndex
	{
	public:
		using OwnerT = Owner_T;
		using MyT = UniqueIndex<OwnerT>;
		using IndexT = Index_T;



		explicit UniqueIndex() : mIndex( getNewIndex() )
		{}
	private:
		static IndexT getNewIndex()
		{
			static IndexT temp_index = Start_Value;
			return temp_index++;
		}



	public:
		bool operator==( const MyT& rhs ) const
		{
			return ( rhs.mIndex == mIndex );
		}
		bool operator!=( const MyT& rhs ) const
		{
			return !operator==( rhs );
		}



		IndexT Get() const
		{
			return mIndex;
		}



		static IndexT GetInvalidIndex()
		{
			static const IndexT invalid_index = Invalid_Value;
			return invalid_index;
		}



	private:
		const IndexT mIndex;
	};
}
