#include "r2_Direction8SequentialState.h"

#include "r2_Random.h"

namespace r2
{
	Direction8SequentialState::eState Direction8SequentialState::GetRandomState_F2E()
	{
		return static_cast<eState>( r2::Random::GetInt(
			static_cast<int>( eState::FIRST )
			, static_cast<int>( eState::END )
		) );
	}
	Direction8SequentialState::eState Direction8SequentialState::GetRandomState_N2E()
	{
		return static_cast<eState>( r2::Random::GetInt(
			static_cast<int>( eState::NONE )
			, static_cast<int>( eState::END )
		) );
	}



	void Direction8SequentialState::ConvertState2Point( const eState state, CoordinateT* out_x, CoordinateT* out_y )
	{
		switch( state )
		{
		case eState::Up:
			( *out_x ) = 0; ( *out_y ) = 1;
			break;
		case eState::Up_Right:
			( *out_x ) = 1; ( *out_y ) = 1;
			break;
		case eState::Right:
			( *out_x ) = 1; ( *out_y ) = 0;
			break;
		case eState::Down_Right:
			( *out_x ) = 1; ( *out_y ) = -1;
			break;
		case eState::Down:
			( *out_x ) = 0; ( *out_y ) = -1;
			break;
		case eState::Down_Left:
			( *out_x ) = -1; ( *out_y ) = -1;
			break;
		case eState::Left:
			( *out_x ) = -1; ( *out_y ) = 0;
			break;
		case eState::Up_Left:
			( *out_x ) = -1; ( *out_y ) = 1;
			break;

		//case eState::NONE:
		default:
			( *out_x ) = 0; ( *out_y ) = 0;
			break;
		}
	}
	void Direction8SequentialState::ConvertPoint2State( const CoordinateT x, const CoordinateT y, eState* out_state )
	{
		if( x == 0 && y >= 1 )
		{
			( *out_state ) = eState::Up;
		}
		else if( x >= 1 && y >= 1 )
		{
			( *out_state ) = eState::Up_Right;
		}
		else if( x >= 1 && y == 0 )
		{
			( *out_state ) = eState::Right;
		}
		else if( x >= 1 && y <= -1 )
		{
			( *out_state ) = eState::Down_Right;
		}
		else if( x == 0 && y <= -1 )
		{
			( *out_state ) = eState::Down;
		}
		else if( x <= -1 && y <= -1 )
		{
			( *out_state ) = eState::Down_Left;
		}
		else if( x <= -1 && y == 0 )
		{
			( *out_state ) = eState::Left;
		}
		else if( x <= -1 && y >= 1 )
		{
			( *out_state ) = eState::Up_Left;
		}
		else
		{
			( *out_state ) = eState::NONE;
		}
	}



	Direction8SequentialState::eState Direction8SequentialState::ConvertInteger2State( const int value )
	{
		if( static_cast<int>( eState::NONE ) <= value && static_cast<int>( eState::END ) >= value )
		{
			return static_cast<eState>( value );
		}

		return eState::NONE;
	}



	bool Direction8SequentialState::IsDiagonalState( const eState state )
	{
		return (
			eState::Up_Right == state
			|| eState::Down_Right == state
			|| eState::Down_Left == state
			|| eState::Up_Left == state
		);
	}



	Direction8SequentialState::eState Direction8SequentialState::Rotate( const eState state, const bool bRight )
	{
		eState ret = eState::NONE;

		if( eState::NONE != state && eState::SIZE > state )
		{
			ret = (
				bRight
				? ( eState::END <= state ? eState::FIRST : static_cast<eState>( static_cast<int>( state ) + 1 ) )
				: ( eState::FIRST >= state ? eState::END : static_cast<eState>( static_cast<int>( state ) - 1 ) )
			);
		}

		return ret;
	}
	Direction8SequentialState::eState Direction8SequentialState::Reverse( const eState state )
	{
		int ret = static_cast<int>( eState::NONE );

		if( eState::NONE != state && eState::SIZE > state )
		{
			ret = static_cast<int>( state ) + static_cast<int>( eState::HALF_SIZE );

			(
				static_cast<int>( eState::END ) < ret
				? ret -= static_cast<int>( eState::SIZE )
				: ret
			);
		}

		return static_cast<eState>( ret );
	}
}
