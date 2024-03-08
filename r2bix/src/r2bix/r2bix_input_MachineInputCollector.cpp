#include "r2bix_input_MachineInputCollector.h"

#include "r2bix_input_KeyboardInputListener.h"

namespace r2bix_input
{
	MachineInputCollector::MachineInputCollector() :
			mObservationKeyList()
		,	mObservationKeyStates()
	{
		mObservationKeyList.fill( 0 );
	}

	void MachineInputCollector::Collect()
	{
		if( !HasWindowFocus() )
		{
			return;
		}

		int key_value = 0;

		for( unsigned char i = 0x01, end = static_cast< unsigned char >( mObservationKeyList.size() ); end > i; ++i )
		{
			if( 0 == mObservationKeyList[i] )
			{
				continue;
			}

			key_value = GetKeyState( i );

			mObservationKeyStates[i] = key_value & 0x8000;
		}
	}



	void MachineInputCollector::AddListener( KeyboardInputListener* listener )
	{
		if( nullptr == listener )
		{
			return;
		}

		for( const auto k : listener->mObservationKeys )
		{
			++mObservationKeyList[k];
		}
	}
	void MachineInputCollector::RemoveListener( KeyboardInputListener* listener )
	{
		if( nullptr == listener )
		{
			return;
		}

		for( const auto k : listener->mObservationKeys )
		{
			--mObservationKeyList[k];
		}
	}
}