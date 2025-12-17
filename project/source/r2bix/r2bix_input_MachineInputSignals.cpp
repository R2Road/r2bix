#include "r2bix_input_MachineInputSignals.hpp"

namespace r2bix_input
{
	MachineInputSignals::MachineInputSignals() :
		  mOffset()
		, mObservationKeySignals()
		, mCursorPoint_Last()
		, mCursorPoint()
		, mbMouseMoved( false )
	{}

	MachineInputSignals::MachineInputSignals( const int offset_x, const int offset_y ) :
		  mOffset( offset_x, offset_y )
		, mObservationKeySignals()
		, mCursorPoint_Last()
		, mCursorPoint()
		, mbMouseMoved( false )
	{}

	MachineInputSignals::MachineInputSignals( const CursorPoint& offset ) :
		  mOffset( offset.GetX(), offset.GetY() )
		, mObservationKeySignals()
		, mCursorPoint_Last()
		, mCursorPoint()
		, mbMouseMoved( false )
	{}

	void MachineInputSignals::Collect()
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
					mObservationKeySignals.set( i, key_states[i] & 0b10000000 );
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
}