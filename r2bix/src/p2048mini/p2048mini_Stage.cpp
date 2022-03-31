#include "pch.h"
#include "p2048mini_Stage.h"

#include <algorithm>

#include "r2/r2_Point_Int.h"

namespace p2048mini
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
	// # �̵� ��Ģ
	// 1. �������� ���� ����� �༮���� �̵�
	// 2. �ƹ��� �������� ���ߴٸ� �̵� �� ���� �ƴϴ�.
	//
	void Stage::Move( const r2::Direction4::eState direction_state )
	{
		const r2::PointInt center_point( GetWidth() / 2, GetHeight() );

		const r2::Direction4 move_dir( direction_state );
		r2::Direction4 reverse_dir = move_dir;
		reverse_dir.Rotate( true );
		reverse_dir.Rotate( true );

		//
		// # Step 1
		// > ������ �����.
		//
		// =====
		// ==P==
		// =====
		//
		r2::PointInt pivot_point_1 = center_point;

		//
		// # Step 2
		//
		// Dierction �� ����ؼ� ������ �̵� �Ѱ��� ���� �̵���Ų��.
		//
		// > condition : dir == left
		//
		// =====
		// P====
		// =====
		//
		pivot_point_1 += r2::PointInt( center_point.GetX() * move_dir.GetPoint().GetX(), center_point.GetY() * move_dir.GetPoint().GetY() );
		pivot_point_1.SetX( std::clamp( pivot_point_1.GetX(), 0, static_cast<int32_t>( GetMaxX() ) ) );
		pivot_point_1.SetY( std::clamp( pivot_point_1.GetY(), 0, static_cast<int32_t>( GetMaxY() ) ) );

		//
		// # Step 3
		//
		// �̵� �Ϸ�� ���� move_dir �� ���ؼ� ���� �������� �������� �ϼ��Ѵ�.
		//
		// > condition : dir == left
		//
		// P====
		// =====
		// =====
		//
		r2::PointInt pivot_point_2( pivot_point_1.GetX() * std::abs( move_dir.GetPoint().GetX() ), pivot_point_1.GetY() * std::abs( move_dir.GetPoint().GetY() ) );

		//
		// # Step 4
		//
		// move_dir == -1, 0
		// reverse_dir == 1, 0
		// pivot_point_2 == 0, 0
		//
		// �� �������� �������� "reverse_dir" ���ؼ� ���� ó���� ���� �����Ѵ�.
		// pivot_point_2 += reverse_dir : ( 0, 0 ) > ( 1, 0 ) > ( 2, 0 ) > ( 3, 0 ) > ( 4,  0 )
		//
		// 01234
		// =====
		// =====		
		//
		// temp_point = x * std::abs( move_dir.GetPoint().GetX() ), y * std::abs( move_dir.GetPoint().GetY() )
		// �� �ڵ带 ���� ���� ó���� ������ �´��� Ȯ���Ѵ�.
		//
		// 01234
		// 01234
		// 01234
		//
		for( int loop_count = 0; IsIn( pivot_point_2.GetX(), pivot_point_2.GetY() ); ++loop_count )
		{
			for( uint32_t y = 0; GetHeight() > y; ++y )
			{
				for( uint32_t x = 0; GetWidth() > x; ++x )
				{
					r2::PointInt temp_point( x * std::abs( move_dir.GetPoint().GetX() ), y * std::abs( move_dir.GetPoint().GetY() ) );

					if( pivot_point_2.GetX() == temp_point.GetX() && pivot_point_2.GetY() == temp_point.GetY() )
					{
						//
						// # Step 5
						//
						// �� ������ �̵�, �ռ� ó���� �Ѵ�.
						//

						Add( x, y, loop_count );
					}
				}
			}

			pivot_point_2 += reverse_dir.GetPoint();
		}
	}
}