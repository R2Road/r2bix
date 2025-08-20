//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.08.18 PM.07.50
// # Version			: 1.0.0
//

//
// # 개요
// 1. 추가된 case_iteraion_data 를 순회하며 모든 조합의 경우를 만든다.
// 
// # 예
// 1. cid : { 1, 2, 3 }
// 2. cid : { 4, 5 }
// 3. cid : { 6, 7 }
// 
// # 출력
// { 1, 4, 6 }
// { 1, 4, 7 }
// { 1, 5, 6 }
// { 1, 5, 7 }
// { 2, 4, 6 }
// { 2, 4, 7 }
// { 2, 5, 6 }
// ...
//

#pragma once

#include <vector>

#include "r2_case_iteration_data.hpp"

namespace r2
{
	template<typename element_container_T>
	class CaseIterationManager
	{
	public:
		using ElementContainerT = element_container_T;

		using value_type = CaseIterationData<ElementContainerT>;
		using ContainerT = std::vector<value_type>;
		using const_iterator = typename ContainerT::const_iterator;

		//
		//
		//
		CaseIterationManager() : mContainer()
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
		void Add( const ElementContainerT& _target_element )
		{
			mContainer.push_back( value_type(
				  _target_element.begin()
				, _target_element.end()
				, _target_element.begin()
			) );
		}
		bool MoveNext()
		{
			auto current = mContainer.rbegin();
			auto end = mContainer.rend();
			for( ; current != end; ++current )
			{
				if( current->MoveNext() )
				{
					return true;
				}

				current->Restart();
			}

			return false;
		}

	private:
		ContainerT mContainer;
	};
}
