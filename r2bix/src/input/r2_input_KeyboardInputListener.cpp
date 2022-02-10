#include "pch.h"
#include "input/r2_input_KeyboardInputListener.h"

namespace r2_input
{
	KeyboardInputListener::KeyboardInputListener() :
		mObservationKeyList( {
			0x1B		// esc
			, 0x41		// a
			, 0x44		// d
			, 0x53		// s
			, 0x57		// w
		} )
		, mKeyStatusList( mObservationKeyList.size(), 0 )
	{}
}