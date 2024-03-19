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

	void Listener4Keyboard::Update( const ObservationKeyStatesT& observation_key_states )
	{
		int i = 0;
		for( const r2bix_input::ObservationKey o : mObservationKeyContainer )
		{
			if( observation_key_states.test( mObservationKeyContainer[i].key_code ) )
			{
				switch( mObservationKeyContainer[i].key_status )
				{
				case eKeyStatus::None:
					mObservationKeyContainer[i].key_status = eKeyStatus::Push;
					break;

				case eKeyStatus::Push:
					mObservationKeyContainer[i].key_status = eKeyStatus::Pressed;
					break;

					//case eKeyStatus::Pressed:
					//	break;

				}
			}
			else
			{
				switch( mObservationKeyContainer[i].key_status )
				{
					//case eKeyStatus::None:
					//	break;

				case eKeyStatus::Push:
				case eKeyStatus::Pressed:
					mObservationKeyContainer[i].key_status = eKeyStatus::Release;
					break;

				case eKeyStatus::Release:
					mObservationKeyContainer[i].key_status = eKeyStatus::None;
					break;
				}
			}

			++i;
		}
	}
}