#include "r2bix_input_Listener4Keyboard.h"

namespace r2bix_input
{
	Listener4Keyboard::Listener4Keyboard() :
		  mOrder( 0 )
		, mObservationKeyContainer()
	{}
	Listener4Keyboard::Listener4Keyboard( const int order, std::initializer_list<uint8_t> list ) :
		  mOrder( order )
		, mObservationKeyContainer( list )
	{}

	void Listener4Keyboard::Update( const int key_index, const bool key_flag )
	{
		if( key_flag )
		{
			switch( mObservationKeyContainer[key_index].key_status )
			{
			case eKeyStatus::None:
				mObservationKeyContainer[key_index].key_status = eKeyStatus::Push;
				break;

			case eKeyStatus::Push:
				mObservationKeyContainer[key_index].key_status = eKeyStatus::Pressed;
				break;

				//case eKeyStatus::Pressed:
				//	break;

			}
		}
		else
		{
			switch( mObservationKeyContainer[key_index].key_status )
			{
				//case eKeyStatus::None:
				//	break;

			case eKeyStatus::Push:
			case eKeyStatus::Pressed:
				mObservationKeyContainer[key_index].key_status = eKeyStatus::Release;
				break;

			case eKeyStatus::Release:
				mObservationKeyContainer[key_index].key_status = eKeyStatus::None;
				break;
			}
		}
	}
}