//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.08.18 PM.08.30
// # Version			: 1.0.0
//

//
// # 개요
// 1. 추가된 case_iteraion_data 를 순회하며 제한적인 조합의 경우를 만든다.
// 
// # 예
// 1. cid : { 1, 2, 3 }
// 2. cid : { 4, 5 }
// 3. cid : { 6, 7 }
// 
// # 출력
// { 1, 4, 6 }
// { 2, 5, 7 }
// { 3 }
// ...
//

#pragma once

#include <vector>

#include "r2_case_iteration_data.hpp"

namespace r2
{
	template<typename element_container_T>
	class CaseIterationManager_SingleCycle
	{
	public:
		using ElementContainerT = element_container_T;

		using value_type = CaseIterationData<ElementContainerT>;
		using ContainerT = std::vector<value_type>;
		using const_iterator = typename ContainerT::const_iterator;

		//
		//
		//
		CaseIterationManager_SingleCycle() : mContainer()
		{}

		//
		//
		//
		const_iterator begin() const
		{
			return mContainer.begin();
		}
		const_iterator end() const
		{
			return mContainer.end();
		}

		//
		//
		//
		bool Empty() const
		{
			return mContainer.empty();
		}

		//
		//
		//
		void Add( const ElementContainerT& _element )
		{
			if( _element.empty() )
			{
				return;
			}

			mContainer.push_back( value_type{
				_element.begin()
				, _element.end()
				, _element.begin()
			} );
		}
		bool MoveNext()
		{
			//
			// 모든 iteration_data에 동시에 MoveNext
			//
			std::size_t failed_count = 0;
			for( auto& i : mContainer )
			{
				if( !i.MoveNext() )
				{
					++failed_count;
				}
			}

			//
			// 모든 CaseIterationData가 MoveNext에 실패하면 종료의 의미로 return fasle
			//
			return ( mContainer.size() > failed_count );
		}

	private:
		ContainerT mContainer;
	};
}
