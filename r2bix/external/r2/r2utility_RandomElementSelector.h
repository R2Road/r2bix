#pragma once

#include <stdint.h>

#include "r2_Random.h"

namespace r2utility
{
	template<typename iterator_T>
	iterator_T RandomElementSelector( iterator_T first, const iterator_T last, const std::size_t size )
	{
		if( last == first )
		{
			return last;
		}

		if( 1 == size )
		{
			return first;
		}

		const int32_t targetIndex = r2::Random::GetInt( 0, static_cast<int32_t>( size - 1 ) );
		for( int32_t i = 0; i < targetIndex; ++i, ++first );

		return first;
	}
}
