//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.05.10 AM.08.38
// # Version			: 1.0.0
//

#pragma once

#include "r2_Direction8SequentialState.h"

namespace r2
{
	class Direction8Sequential
	{
	public:
		using StateT = r2::Direction8SequentialState;
		using eState = StateT::eState;
		using CoordinateT = typename StateT::CoordinateT;



		Direction8Sequential() :
			mState( eState::Up )
			, mX( 0 )
			, mY( 0 )
		{
			StateT::ConvertState2Point( mState, &mX, &mY );
		}
		explicit Direction8Sequential( const eState state ) :
			mState( state )
			, mX( 0 )
			, mY( 0 )
		{
			StateT::ConvertState2Point( mState, &mX, &mY );
		}
		explicit Direction8Sequential( const CoordinateT x, const CoordinateT y ) :
			mState( eState::NONE )
			, mX( 0 )
			, mY( 0 )
		{
			StateT::ConvertPoint2State( x, y, &mState );
			StateT::ConvertState2Point( mState, &mX, &mY );
		}



		//
		//
		//
		bool operator==( const Direction8Sequential& other ) const
		{
			return ( other.mState == mState );
		}
		bool operator!=( const Direction8Sequential& other ) const
		{
			return !( operator==( other ) );
		}



		//
		// Get
		//
		eState GetState() const
		{
			return mState;
		}
		eState GetReverseState() const
		{
			return StateT::Reverse( mState );
		}
		CoordinateT GetX() const
		{
			return mX;
		}
		CoordinateT GetY() const
		{
			return mY;
		}
		bool IsDiagonal() const
		{
			return StateT::IsDiagonalState( mState );
		}



		//
		// Set
		//
		void SetState( const eState new_state )
		{
			mState = new_state;
			StateT::ConvertState2Point( mState, &mX, &mY );
		}
		void SetRandomState()
		{
			SetState( StateT::GetRandomState_F2E() );
		}



		//
		//
		//
		void Rotate( const bool bRight = true )
		{
			SetState( StateT::Rotate( mState, bRight ) );
		}
		void Rotate( const bool bRight, const int count )
		{
			for( int i = 0; count > i; ++i )
			{
				Rotate( bRight );
			}
		}
		//
		//
		//
		void Reverse()
		{
			SetState( GetReverseState() );
		}



	private:
		eState mState;
		CoordinateT mX;
		CoordinateT mY;
	};
}