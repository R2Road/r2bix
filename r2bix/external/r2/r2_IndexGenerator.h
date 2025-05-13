//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.05.09 PM.11.35
// # Version			: 1.0.0
//

#pragma once

#include "r2_TypeTraits.h"

namespace r2
{
	template<typename Index_T, Index_T Start_Value = 0, Index_T Invalid_Value = -1>
	class IndexGenerator
	{
	public:
		static_assert(
			   r2::is_same_v<Index_T, int>
			|| r2::is_same_v<Index_T, unsigned int>
			|| r2::is_same_v<Index_T, long long>
			|| r2::is_same_v<Index_T, unsigned long long>
			, "r2::IndexGenerator - Not Allowed Type"
		);

		using IndexT = Index_T;



		explicit IndexGenerator() : mCurrentIndex( Start_Value )
		{}
		explicit IndexGenerator( const IndexT continuity_start_value ) : mCurrentIndex( continuity_start_value )
		{}



		void Clear()
		{
			mCurrentIndex = Start_Value;
		}



		IndexT GetInvalidIndex() const
		{
			return Invalid_Value;
		}
		IndexT GetNewIndex()
		{
			return mCurrentIndex++;
		}
		bool IsValid( const IndexT index ) const
		{
			return GetInvalidIndex() != index;
		}
		bool IsInvalid( const IndexT index ) const
		{
			return GetInvalidIndex() == index;
		}



	private:
		IndexT mCurrentIndex;
	};
}