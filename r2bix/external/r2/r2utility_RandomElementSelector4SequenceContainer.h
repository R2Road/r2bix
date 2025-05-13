#pragma once

#include <stdint.h>

#include "r2_Random.h"

namespace r2utility
{
	template<typename ContainerT>
	const typename ContainerT::value_type& RandomElementSelector4SequenceContainer( const ContainerT& container )
	{
		if( container.empty() )
		{
			static typename ContainerT::value_type dummy{};
			return dummy;
		}

		if( 1 == container.size() )
		{
			return container[0];
		}

		const int32_t target_index = r2::Random::GetInt( 0, static_cast<int32_t>( container.size() - 1 ) );

		return container[target_index];
	}
}
