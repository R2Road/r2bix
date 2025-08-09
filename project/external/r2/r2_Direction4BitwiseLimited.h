//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.06.14 AM.06.00
// # Version			: 1.0.0
//

#pragma once

#include "r2_Direction4BitwiseLimitedState.h"

namespace r2
{
	class Direction4BitwiseLimited
	{
	public:
		using StateT = r2::Direction4BitwiseLimitedState;
		using eState = StateT::eState;
		using CoordinateT = StateT::CoordinateT;

		using FlagType = StateT::FlagType;



		explicit Direction4BitwiseLimited( const int enable_state_flags );
		explicit Direction4BitwiseLimited( const CoordinateT x, const CoordinateT y );

		

		//
		//
		//
		FlagType GetEnableStateFlags() const
		{
			return mEnableStateFlags;
		}
		eState GetState() const
		{
			return static_cast< eState>( mState );
		}
		CoordinateT GetX() const
		{
			return mX;
		}
		CoordinateT GetY() const
		{
			return mY;
		}



		bool Equal( const CoordinateT x, const CoordinateT y ) const
		{
			return ( x == mX ) && ( y == mY );
		}



		//
		//
		//
		void SetState( const eState state );
		void SetState( const CoordinateT x, const CoordinateT y );



		//
		//
		//
		void Rotate( const bool bRight = true );



		//
		//
		//
		void SelectRandomState();



	private:
		const FlagType mEnableStateFlags;
		eState mState;
		CoordinateT mX;
		CoordinateT mY;
	};
}
