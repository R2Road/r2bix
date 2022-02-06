#include "pch.h"
#include "input/r2_input_KeyboardInputListener.h"

namespace r2_input
{
	KeyboardInputListener::KeyboardInputListener() :
		mObservationKeyList( { 27 } )
		, mKeyStatusList( mObservationKeyList.size(), 0 )
	{}
}