#pragma once

#include <vector>

#include "r2_CaseIterationData.h"

namespace r2
{
	template<typename element_container_T>
	class CaseIterationManager4SingleCycle
	{
	public:
		using ElementContainerT = element_container_T;

		using value_type = CaseIterationData<ElementContainerT>;
		using ContainerT = std::vector<value_type>;
		using const_iterator = typename ContainerT::const_iterator;

		//
		//
		//
		const_iterator begin() const
		{
			return iterationInfos.begin();
		}
		const_iterator end() const
		{
			return iterationInfos.end();
		}

		//
		//
		//
		bool Empty() const
		{
			return iterationInfos.empty();
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

			iterationInfos.push_back( value_type{
				_element.begin()
				, _element.end()
				, _element.begin()
			} );
		}
		bool MoveNext()
		{
			std::size_t failed_count = 0;
			for( auto& i : iterationInfos )
			{
				if( !i.MoveNext() )
				{
					++failed_count;
				}
			}

			return iterationInfos.size() > failed_count;
		}

	private:
		ContainerT iterationInfos;
	};
}
