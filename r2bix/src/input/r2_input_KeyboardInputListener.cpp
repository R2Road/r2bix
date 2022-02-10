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
		, mKeyFlags( mObservationKeyList.size(), 0 )
		, mKeyStatusContainer( mObservationKeyList.size(), eKeyStatus::Release )
	{}

	void KeyboardInputListener::Update()
	{
		for( std::size_t i = 0u; mKeyFlags.size() > i; ++i )
		{
			if( mKeyFlags[i] )
			{
				switch( mKeyStatusContainer[i] )
				{
				case eKeyStatus::Push:
					mKeyStatusContainer[i] = eKeyStatus::Pressed;
					break;

				//case eKeyStatus::Pressed:
				//	break;

				case eKeyStatus::Release:
					mKeyStatusContainer[i] = eKeyStatus::Push;
					break;
				}
			}
			else
			{
				mKeyStatusContainer[i] = eKeyStatus::Release;
			}
		}
	}
}