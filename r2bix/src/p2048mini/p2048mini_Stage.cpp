#include "pch.h"
#include "p2048mini_Stage.h"

#include "r2/r2_Point_Int.h"

namespace p2048
{
	Stage::Stage( const uint32_t width, const uint32_t height ) :
		mGridIndexConverter( width, height )
		, mContainer( width * height, -1 )
	{}

	bool Stage::IsIn( const int32_t x, const int32_t y ) const
	{
		return ( 0 <= x && 0 <= y && static_cast<int>( GetWidth() ) > x && static_cast<int>( GetHeight() ) > y );
	}

	uint32_t Stage::Get( const uint32_t x, const uint32_t y ) const
	{
		const int linear_index = mGridIndexConverter.To_Linear( x, y );
		return mContainer[linear_index];
	}

	void Stage::ClearAll()
	{
		for( auto& v : mContainer )
		{
			v = -1;
		}
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

	//
	// # 이동 규칙
	// 1. 도착점에 가장 가까운 녀석부터 이동
	// 2. 아무도 움직이지 못했다면 이동 한 것이 아니다.
	//
	void Stage::Move( const r2::Direction4::eState direction_state )
	{
		//
		// 중점을 만든다.
		// Dierction 을 사용해서 중점을 이동 한계점 까지 이동시킨다.
		// 이동 완료된 지점을 기준점으로 삼는다.
		//
		// 기준점에서 가까운 녀석부터 이동을 시켜야 한다.
		// ( 먼 녀석을 먼저 움직이면 이후 처리로 움직여질 가까운 녀석들 때문에 움직이지 못할 수 있다. )
		// 편한 작업을 위해 기준점을 가지고 전체 목록을 정렬한다.
		//
		// 이동, 합성 처리를 한다.
		//

		r2::Direction4 dir( direction_state );
		r2::PointInt center_point( mGridIndexConverter.GetWidth() / 2, mGridIndexConverter.GetHeight() );
	}
}