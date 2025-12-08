#include "r2bix_input_MachineInputCollector.h"

namespace r2bix_input
{
	MachineInputCollector::MachineInputCollector() :
		  mOffset()
		, mObservationKeySignals()
		, mObservationKeyFlags()
		, mCursorPoint_Last()
		, mCursorPoint()
		, mbMouseMoved( false )
	{
		mObservationKeyFlags.fill( 0 );
	}

	MachineInputCollector::MachineInputCollector( const int offset_x, const int offset_y ) :
		  mOffset( offset_x, offset_y )
		, mObservationKeySignals()
		, mObservationKeyFlags()
		, mCursorPoint_Last()
		, mCursorPoint()
		, mbMouseMoved( false )
	{
		mObservationKeyFlags.fill( 0 );
	}

	MachineInputCollector::MachineInputCollector( const CursorPoint& offset ) :
		  mOffset( offset.GetX(), offset.GetY() )
		, mObservationKeySignals()
		, mObservationKeyFlags()
		, mCursorPoint_Last()
		, mCursorPoint()
		, mbMouseMoved( false )
	{
		mObservationKeyFlags.fill( 0 );
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
				mObservationKeySignals.reset(); // 모두 false
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
				static unsigned char key_states[256] = { 0 };
				GetKeyStates( key_states );

				for(
					unsigned char i = r2bix_input::eKeyCode::START, end = r2bix_input::eKeyCode::END;
					end >= i;
					++i
				)
				{
					if( 0 == mObservationKeyFlags[i] )
					{
						continue;
					}

					mObservationKeySignals[i] = ( key_states[i] & 0b10000000 );
				}
			}

			//
			// Mouse Key Swap
			//
			{
				if( IsMouseKeyReversed() )
				{
					const bool lbutton_state = mObservationKeySignals[VK_LBUTTON];
					const bool rbutton_state = mObservationKeySignals[VK_RBUTTON];

					mObservationKeySignals[VK_LBUTTON] = rbutton_state;
					mObservationKeySignals[VK_RBUTTON] = lbutton_state;
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
			++mObservationKeyFlags[k.key_code];
		}
	}
	void MachineInputCollector::RemoveObservationKeys( const ObservationKeyContainer& observation_key_container )
	{
		for( const auto k : observation_key_container )
		{
			--mObservationKeyFlags[k.key_code];
		}
	}
}