#include "r2_Direction4SequentialState.h"

#include "r2_Random.h"

namespace r2
{
	Direction4SequentialState::eState Direction4SequentialState::GetRandomState()
	{
		return static_cast<eState>( r2::Random::GetInt(
			static_cast<int>( eState::FIRST )
			, static_cast<int>( eState::END )
		) );
	}



	void Direction4SequentialState::ConvertState2Point( const eState state, CoordinateT* out_x, CoordinateT* out_y )
	{
		switch( state )
		{
		case eState::Up:
			( *out_x ) = 0; ( *out_y ) = 1;
			break;
		case eState::Right:
			( *out_x ) = 1; ( *out_y ) = 0;
			break;
		case eState::Down:
			( *out_x ) = 0; ( *out_y ) = -1;
			break;
		case eState::Left:
			( *out_x ) = -1; ( *out_y ) = 0;
			break;

		//case eState::NONE:
		default:
			( *out_x ) = 0; ( *out_y ) = 0;
			break;
		}
	}
	Direction4SequentialState::eState Direction4SequentialState::ConvertPoint2State( const CoordinateT x, const CoordinateT y )
	{
		if( 1 <= x )
		{
			return eState::Right;
		}
		else if( -1 >= x )
		{
			return eState::Left;
		}
		else if( 1 <= y )
		{
			return eState::Up;
		}
		else if( -1 >= y )
		{
			return eState::Down;
		}

		return eState::NONE;
	}


		
	Direction4SequentialState::eState Direction4SequentialState::ConvertInteger2State( const int value )
	{
		if( static_cast<int>( eState::NONE ) <= value && static_cast<int>( eState::END ) >= value )
		{
			return static_cast<eState>( value );
		}

		return eState::NONE;
	}



	Direction4SequentialState::eState Direction4SequentialState::Rotate( const eState state, const bool bRight )
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
	Direction4SequentialState::eState Direction4SequentialState::Reverse( const eState state )
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
