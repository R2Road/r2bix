#include "pch.h"
#include "input/r2_input_KeyboardInputListener.h"

#include <numeric>

namespace r2_input
{
	KeyboardInputListener::KeyboardInputListener() :
		mObservationKeyList( { 27 } )
		, mKeyStatusList( std::numeric_limits<KeyCodeTypeT>::max(), 0 )
	{}
}