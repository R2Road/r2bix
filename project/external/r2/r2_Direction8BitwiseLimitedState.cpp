#include "r2_Direction8BitwiseLimitedState.h"

#include "r2_Random.h"

namespace r2
{
	void Direction8BitwiseLimitedState::ConvertFlags2EnableDirectionCount( const FlagType enable_state_flags, char* out_size )
	{
		*out_size = 0;
		for(
			short cur = 1, end = static_cast<short>( eState::END );
			end >= cur;
			cur = cur << 1
		)
		{
			if( enable_state_flags & cur )
			{
				++( *out_size );
			}
		}
	}



	void Direction8BitwiseLimitedState::ConvertState2Point( const eState state, CoordinateT* out_x, CoordinateT* out_y )
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

	void Direction8BitwiseLimitedState::ConvertPoint2State( const int x, const int y, eState* out_state )
	{
		if( x == 0 && y == 0 )
		{
			*out_state = eState::NONE;
			return;
		}

		eState horizontal_dir( eState::NONE );
		eState vertical_dir( eState::NONE );

		//
		// Direction Analysis
		//
		{
			if( 0 > x )
			{
				horizontal_dir = eState::Left;
			}
			else if( 0 < x )
			{
				horizontal_dir = eState::Right;
			}

			if( 0 > y )
			{
				vertical_dir = eState::Down;
			}
			else if( 0 < y )
			{
				vertical_dir = eState::Up;
			}
		}

		//
		//
		//
		if( eState::NONE == horizontal_dir ) // vertical only
		{
			*out_state = vertical_dir;
			return;
		}
		if( eState::NONE == vertical_dir ) // horizontal only
		{
			*out_state = horizontal_dir;
			return;
		}


		//
		// Diagonal
		//
		{
			//
			// 수평이 eState::Left	> 64
			// 수직이 eState::Up		> 1
			// ...일때 아래의 [ horizontal_dir > vertical_dir ] 조건에서 역방향으로 회전하는 문제가 생기므로 예외처리 한다.
			//
			if( eState::Left == horizontal_dir && eState::Up == vertical_dir )
			{
				*out_state = static_cast<eState>( static_cast<FlagType>( horizontal_dir ) << 1 );
			}
			else if( horizontal_dir > vertical_dir )
			{
				*out_state = static_cast<eState>( static_cast<FlagType>( horizontal_dir ) >> 1 );
			}
			else
			{
				*out_state = static_cast<eState>( static_cast<FlagType>( horizontal_dir ) << 1 );
			}
		}
	}



	Direction8BitwiseLimitedState::eState Direction8BitwiseLimitedState::ConvertInteger2State( const int value )
	{
		eState ret = static_cast<eState>( value );

		switch( ret )
		{
		case eState::Up:
		case eState::Up_Right:
		case eState::Right:
		case eState::Down_Right:
		case eState::Down:
		case eState::Down_Left:
		case eState::Left:
		case eState::Up_Left:
			break;

			//case eState::NONE:
		default:
			ret = eState::NONE;
			break;
		}

		return ret;
	}



	void Direction8BitwiseLimitedState::SelectEnableState( const FlagType enable_state_flags, eState* out_state )
	{
		for(
			int cur = 1, end = static_cast<int>( eState::END );
			end >= cur;
			cur = cur << 1
		)
		{
			if( enable_state_flags & cur )
			{
				*out_state = static_cast<eState>( cur );
				return;
			}
		}

		*out_state = eState::NONE;
	}
	void Direction8BitwiseLimitedState::SelectRandomState( const FlagType enable_state_flags, eState* out_state )
	{
		char enable_state_count = 0;
		ConvertFlags2EnableDirectionCount( enable_state_flags, &enable_state_count );
		if( 0 == enable_state_count )
		{
			*out_state = eState::NONE;
		}
		else
		{
			char current_match_count = 0;
			const char required_match_count = static_cast<char>( r2::Random::GetInt( 1, enable_state_count ) );

			short flags = 1;
			while( required_match_count > current_match_count )
			{
				if( enable_state_flags & flags )
				{
					++current_match_count;

					if( required_match_count == current_match_count )
					{
						break;
					}
				}

				flags = flags << 1;
			}

			*out_state = static_cast<eState>( flags );
		}
	}



	bool Direction8BitwiseLimitedState::IsDiagonalState( const eState state )
	{
		return (
			eState::Up_Right == state
			|| eState::Down_Right == state
			|| eState::Down_Left == state
			|| eState::Up_Left == state
		);
	}



	void Direction8BitwiseLimitedState::Rotate( const FlagType enable_state_flags, const bool bRight, eState* out_state )
	{
		if( 0 == enable_state_flags )
		{
			return;
		}

		if( eState::NONE == *out_state )
		{
			return;
		}

		do
		{

			if( bRight )
			{
				*out_state = ( eState::END <= *out_state ? eState::FIRST : static_cast<eState>( static_cast<FlagType>( *out_state ) << 1 ) );
			}
			else
			{
				*out_state = ( eState::FIRST >= *out_state ? eState::END : static_cast<eState>( static_cast<FlagType>( *out_state ) >> 1 ) );
			}

		} while( !( enable_state_flags & static_cast<FlagType>( *out_state ) ) );

	}
	void Direction8BitwiseLimitedState::Reverse( eState* out_state )
	{
		*out_state = ConvertInteger2State( static_cast<int>( *out_state ) );

		//
		// Up_Left 에서 Up 으로 넘어가는 것을 피하기 위해
		// 전체 상태의 절반 이전에는 <<
		// 전체 상태의 절반 이후에는 >>
		//
		if( eState::Down > *out_state )
		{
			*out_state = static_cast<eState>( static_cast<int>( *out_state ) << 4 );
		}
		else
		{
			*out_state = static_cast<eState>( static_cast<int>( *out_state ) >> 4 );
		}
	}
	Direction8BitwiseLimitedState::eState Direction8BitwiseLimitedState::Reverse( const eState state )
	{
		auto ret = state;
		Reverse( &ret );

		return ret;
	}
}
