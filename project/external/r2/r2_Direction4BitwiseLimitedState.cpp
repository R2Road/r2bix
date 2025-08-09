#include "r2_Direction4BitwiseLimitedState.h"

#include <algorithm>

#include "r2_Random.h"

namespace r2
{
	void Direction4BitwiseLimitedState::ConvertFlags2EnableDirectionCount( const FlagType enable_state_flags, char* out_size )
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



	Direction4BitwiseLimitedState::FlagType Direction4BitwiseLimitedState::ConvertPoint2EnableStateFlags( const CoordinateT x, const CoordinateT y )
	{
		FlagType ret = static_cast<FlagType>( eState::NONE );

		// dir analysis
		if( 0 > x )
		{
			ret |= static_cast<FlagType>( eState::Left );
		}
		else if( 0 < x )
		{
			ret |= static_cast<FlagType>( eState::Right );
		}

		if( 0 > y )
		{
			ret |= static_cast<FlagType>( eState::Down );
		}
		else if( 0 < y )
		{
			ret |= static_cast<FlagType>( eState::Up );
		}

		return ret;
	}



	void Direction4BitwiseLimitedState::ConvertState2Point( const eState state, CoordinateT* out_x, CoordinateT* out_y )
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

	void Direction4BitwiseLimitedState::ConvertPoint2State( const CoordinateT x, const CoordinateT y, eState* out_state )
	{
		if( 0 == x && 0 == y )
		{
			( *out_state ) = eState::NONE;
			return;
		}

		if( std::abs( x ) > std::abs( y ) )
		{
			if( 0 > x )
			{
				( *out_state ) = eState::Left;
			}
			else
			{
				( *out_state ) = eState::Right;
			}
		}
		else
		{
			if( 0 > y )
			{
				( *out_state ) = eState::Down;
			}
			else
			{
				( *out_state ) = eState::Up;
			}
		}
	}



	Direction4BitwiseLimitedState::eState Direction4BitwiseLimitedState::ConvertInteger2State( const int value )
	{
		eState ret = static_cast<eState>( value );

		switch( ret )
		{
		case eState::Up:
		case eState::Right:
		case eState::Down:
		case eState::Left:
			break;

			//case eState::NONE:
		default:
			ret = eState::NONE;
			break;
		}

		return ret;
	}



	void Direction4BitwiseLimitedState::SelectEnableState( const FlagType enable_state_flags, eState* out_state )
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
	void Direction4BitwiseLimitedState::SelectRandomState( const FlagType enable_state_flags, eState* out_state )
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



	void Direction4BitwiseLimitedState::Rotate( const FlagType enable_state_flags, const bool bRight, eState* out_state )
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
	void Direction4BitwiseLimitedState::Reverse( eState* out_state )
	{
		*out_state = ConvertInteger2State( static_cast<int>( *out_state ) );

		//
		// Left 에서 Up 으로 넘어가는 것을 피하기 위해
		// 전체 상태의 절반 이전에는 <<
		// 전체 상태의 절반 이후에는 >>
		//
		if( eState::Down > *out_state )
		{
			*out_state = static_cast<eState>( static_cast<int>( *out_state ) << static_cast<int>( eState::HALF_SIZE ) );
		}
		else
		{
			*out_state = static_cast<eState>( static_cast<int>( *out_state ) >> static_cast<int>( eState::HALF_SIZE ) );
		}
	}
	Direction4BitwiseLimitedState::eState Direction4BitwiseLimitedState::Reverse( const eState state )
	{
		auto ret = state;
		Reverse( &ret );

		return ret;
	}
}
