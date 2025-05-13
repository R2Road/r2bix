#pragma once

#include <vector>

#include "r2_CaseIterationData.h"

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
