#include "r2_Direction8InGrid.h"

namespace r2
{
	void ConvertDirection8State2LinearIndex( const Direction8InGrid::eState state, const int width, int& out_linear_index )
	{
		switch( state )
		{
		case Direction8InGrid::eState::Up:
			out_linear_index = -width;
			break;
		case Direction8InGrid::eState::Up_Right:
			out_linear_index = -width + 1;
			break;
		case Direction8InGrid::eState::Right:
			out_linear_index = 1;
			break;
		case Direction8InGrid::eState::Down_Right:
			out_linear_index = width + 1;
			break;
		case Direction8InGrid::eState::Down:
			out_linear_index = width;
			break;
		case Direction8InGrid::eState::Down_Left:
			out_linear_index = width - 1;
			break;
		case Direction8InGrid::eState::Left:
			out_linear_index = -1;
			break;
		case Direction8InGrid::eState::Up_Left:
			out_linear_index = -width - 1;
			break;
		default:
			out_linear_index = 0;
			break;
		}
	}



	Direction8InGrid::Direction8InGrid() :
		mGridWidth( 1 )
		, mState( eState::Up )
		, mLinearIndex( 0 )
	{
		ConvertDirection8State2LinearIndex( mState, mGridWidth, mLinearIndex );
	}
	Direction8InGrid::Direction8InGrid( const eState state ) :
		mGridWidth( 1 )
		, mState( state )
		, mLinearIndex( 0 )
	{
		ConvertDirection8State2LinearIndex( mState, mGridWidth, mLinearIndex );
	}
	Direction8InGrid::Direction8InGrid( const eState state, const int grid_width ) :
		mGridWidth( grid_width )
		, mState( state )
		, mLinearIndex( 0 )
	{
		ConvertDirection8State2LinearIndex( mState, mGridWidth, mLinearIndex );
	}



	void Direction8InGrid::SetState( const eState new_state )
	{
		mState = new_state;
		ConvertDirection8State2LinearIndex( mState, mGridWidth, mLinearIndex );
	}



	bool Direction8InGrid::IsDiagonal() const
	{
		return StateT::IsDiagonalState( mState );
	}



	void Direction8InGrid::Rotate( const bool is_right )
	{
		SetState( StateT::Rotate( mState, is_right ) );
	}
}
