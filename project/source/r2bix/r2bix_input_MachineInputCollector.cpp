#include "r2bix_input_MachineInputCollector.h"

namespace r2bix_input
{
	MachineInputCollector::MachineInputCollector() :
		  mOffset()
		, mObservationKeyFlags()
		, mObservationKeySignals()
		, mCursorPoint_Last()
		, mCursorPoint()
		, mbMouseMoved( false )
	{
		mObservationKeySignals.fill( 0 );
	}

	MachineInputCollector::MachineInputCollector( const int offset_x, const int offset_y ) :
		  mOffset( offset_x, offset_y )
		, mObservationKeyFlags()
		, mObservationKeySignals()
		, mCursorPoint_Last()
		, mCursorPoint()
		, mbMouseMoved( false )
	{
		mObservationKeySignals.fill( 0 );
	}

	MachineInputCollector::MachineInputCollector( const CursorPoint& offset ) :
		  mOffset( offset.GetX(), offset.GetY() )
		, mObservationKeyFlags()
		, mObservationKeySignals()
		, mCursorPoint_Last()
		, mCursorPoint()
		, mbMouseMoved( false )
	{
		mObservationKeySignals.fill( 0 );
	}

	void MachineInputCollector::Collect()
	{
		if( !HasWindowFocus() )
		{
			//
			// # Window Focus 가 없다면 입력 상태 모두 초기화
			//

			//
			// Key : Keyboard, Mouse
			//
			{
				mObservationKeyFlags.reset(); // 모두 false
			}

			//
			// Mouse Position
			//
			{
				mCursorPoint_Last = mCursorPoint;
				mbMouseMoved = false;
			}
		}
		else
		{
			//
			// Key : Keyboard, Mouse
			//
			{
				int key_value = 0;
				for( unsigned char i = 0x01, end = static_cast< unsigned char >( mObservationKeySignals.size() ); end > i; ++i )
				{
					if( 0 == mObservationKeySignals[i] )
					{
						continue;
					}

					key_value = GetKeyState( i );

					mObservationKeyFlags[i] = key_value & 0x8000;
				}
			}

			//
			// Mouse Key Swap
			//
			{
				if( IsMouseKeyReversed() )
				{
					const bool lbutton_state = mObservationKeyFlags[VK_LBUTTON];
					const bool rbutton_state = mObservationKeyFlags[VK_RBUTTON];

					mObservationKeyFlags[VK_LBUTTON] = rbutton_state;
					mObservationKeyFlags[VK_RBUTTON] = lbutton_state;
				}
			}

			//
			// Mouse Position
			//
			{
				mCursorPoint_Last = mCursorPoint;
				mCursorPoint = ( r2bix_input::GetCursorPoint() - mOffset );
				mbMouseMoved = ( mCursorPoint_Last != mCursorPoint );
			}
		}
	}



	void MachineInputCollector::AddObservationKeys( const ObservationKeyContainer& observation_key_container )
	{
		for( const auto k : observation_key_container )
		{
			++mObservationKeySignals[k.key_code];
		}
	}
	void MachineInputCollector::RemoveObservationKeys( const ObservationKeyContainer& observation_key_container )
	{
		for( const auto k : observation_key_container )
		{
			--mObservationKeySignals[k.key_code];
		}
	}
}