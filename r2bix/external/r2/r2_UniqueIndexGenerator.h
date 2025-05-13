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

namespace r2
{
	template<typename Owner_T, typename Index_T = unsigned long long, Index_T Start_Value = 1, Index_T Invalid_Value = 0>
	class UniqueIndexGenerator
	{
	public:
		using OwnerT = Owner_T;
		using IndexT = Index_T;



		UniqueIndexGenerator() = delete;
		


		//
		//
		//
		static const IndexT GetNewIndex()
		{
			static IndexT start_index = Start_Value;
			return start_index++;
		}
		static const IndexT GetInvalidIndex()
		{
			static const IndexT invalid_index = Invalid_Value;
			return invalid_index;
		}
	};
}
