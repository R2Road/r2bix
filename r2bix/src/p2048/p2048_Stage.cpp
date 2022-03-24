#include "pch.h"
#include "p2048_Stage.h"

namespace p2048
{
	Stage::Stage( const uint32_t width, const uint32_t height ) :
		mGridIndexConverter( width, height )
		, mContainer( width * height, -1 )
	{}

	uint32_t Stage::Get( const uint32_t x, const uint32_t y ) const
	{
		const int linear_index = mGridIndexConverter.To_Linear( x, y );
		return mContainer[linear_index];
	}

	void Stage::Add( const uint32_t x, const uint32_t y, const uint32_t val )
	{
		const int linear_index = mGridIndexConverter.To_Linear( x, y );
		mContainer[linear_index] = val;
	}

	void Stage::Remove( const uint32_t x, const uint32_t y )
	{
		const int linear_index = mGridIndexConverter.To_Linear( x, y );
		mContainer[linear_index] = -1;
	}

	void Stage::Move( int move_x, int move_y )
	{

	}
}