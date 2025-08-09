#include "r2_Direction8BitwiseLimited.h"

namespace r2
{
	Direction8BitwiseLimited::Direction8BitwiseLimited( const int enable_state_flags ) :
		mEnableStateFlags( ( enable_state_flags & static_cast<FlagType>( eState::ALL ) ) )
		, mState( eState::NONE )
		, mX( 0 ), mY( 0 )
	{
		StateT::SelectEnableState( mEnableStateFlags, &mState );
		StateT::ConvertState2Point( mState, &mX, &mY );
	}



	void Direction8BitwiseLimited::SetState( const eState state )
	{
		if( mEnableStateFlags & static_cast<FlagType>( state ) )
		{
			mState = state;
			StateT::ConvertState2Point( mState, &mX, &mY );
		}
	}
	void Direction8BitwiseLimited::SetState( const int x, const int y )
	{
		eState temp_state = eState::NONE;
		StateT::ConvertPoint2State( x, y, &temp_state );

		if( mEnableStateFlags & static_cast<FlagType>( temp_state ) )
		{
			mState = temp_state;
			StateT::ConvertState2Point( mState, &mX, &mY );
		}
	}



	void Direction8BitwiseLimited::Rotate( const bool bRight )
	{
		StateT::Rotate( mEnableStateFlags, bRight, &mState );
		StateT::ConvertState2Point( mState, &mX, &mY );
	}



	void Direction8BitwiseLimited::SelectRandomState()
	{
		StateT::SelectRandomState( mEnableStateFlags, &mState );
		StateT::ConvertState2Point( mState, &mX, &mY );
	}
}
