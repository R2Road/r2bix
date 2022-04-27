#include "pch.h"
#include "p2048mini_Stage.h"

#include <algorithm>

#include "r2/r2_Point_Int.h"
#include "r2/r2_Direction4.h"

namespace p2048mini
{
	Stage::Stage( const uint32_t width, const uint32_t height ) :
		mGridIndexConverter( width, height )
		, mContainer( width * height )
		, mCurrentNumberCount( 0 )
	{}

	bool Stage::IsIn( const int32_t x, const int32_t y ) const
	{
		return ( 0 <= x && 0 <= y && static_cast<int>( GetWidth() ) > x && static_cast<int>( GetHeight() ) > y );
	}

	const Stage::Cell Stage::Get( const uint32_t linear_index ) const
	{
		return mContainer[linear_index];
	}
	Stage::Cell& Stage::Get( const uint32_t linear_index )
	{
		return mContainer[linear_index];
	}

	uint32_t Stage::GetNumber( const uint32_t linear_index ) const
	{
		return Get( linear_index ).number;
	}
	uint32_t Stage::GetNumber( const uint32_t x, const uint32_t y ) const
	{
		const int linear_index = mGridIndexConverter.To_Linear( x, y );
		return GetNumber( linear_index );
	}

	bool Stage::IsMovable() const
	{
		r2::Direction4 dir4;
		r2::PointInt currept_point;
		r2::PointInt next_point;
		for( uint32_t y = 0; GetHeight() > y; ++y )
		{
			for( uint32_t x = 0; GetWidth() > x; ++x )
			{
				currept_point.Set( x, y );

				// Has Empty Space
				const auto my_number = GetNumber( currept_point.GetX(), currept_point.GetY() );
				if( 0 == my_number )
				{
					return true;
				}

				dir4.SetState( r2::Direction4::eState::Up );
				for( int d = 0, e = static_cast<int>( r2::Direction4::eState::SIZE ); e > d; ++d, dir4.Rotate( true ) )
				{
					next_point = currept_point + dir4.GetPoint();
					if( !IsIn( next_point.GetX(), next_point.GetY() ) )
					{
						continue;
					}

					const auto next_number = GetNumber( next_point.GetX(), next_point.GetY() );
					if( 0 == next_number )
					{
						return true;
					}
					if( my_number == next_number )
					{
						return true;
					}
				}
			}
		}

		return false;
	}
	bool Stage::IsLock( const uint32_t x, const uint32_t y ) const
	{
		const int linear_index = mGridIndexConverter.To_Linear( x, y );
		return Get( linear_index ).merge_lock;
	}

	void Stage::ClearAll()
	{
		mCurrentNumberCount = 0;
		for( auto& cell : mContainer )
		{
			cell.number = 0;
			cell.merge_lock = false;
		}
	}

	void Stage::Add( const uint32_t linear_index, const uint32_t val )
	{
		if( 0 == Get( linear_index ).number )
		{
			++mCurrentNumberCount;
		}

		Get( linear_index ).number = val;
	}
	void Stage::Add( const uint32_t x, const uint32_t y, const uint32_t val )
	{
		const int linear_index = mGridIndexConverter.To_Linear( x, y );
		Add( linear_index, val );
	}

	void Stage::Remove( const uint32_t x, const uint32_t y )
	{
		const int linear_index = mGridIndexConverter.To_Linear( x, y );
		if( 0 == Get( linear_index ).number )
		{
			return;
		}

		--mCurrentNumberCount;
		Get( linear_index ).number = 0;
	}

	void Stage::ClearAllLocks()
	{
		for( auto& cell : mContainer )
		{
			cell.merge_lock = false;
		}
	}
	void Stage::Lock( const uint32_t x, const uint32_t y )
	{
		const int linear_index = mGridIndexConverter.To_Linear( x, y );
		Get( linear_index ).merge_lock = true;
	}

	//
	// # 이동 규칙
	// 1. 도착점에 가장 가까운 녀석부터 이동
	// 2. 아무도 움직이지 못했다면 이동 한 것이 아니다.
	//
	bool Stage::Move( const r2::Direction4::eState direction_state )
	{
		ClearAllLocks();


		bool has_moved = false;


		const r2::PointInt center_point( GetWidth() / 2, GetHeight() );

		const r2::Direction4 move_dir( direction_state );
		r2::Direction4 reverse_dir = move_dir;
		reverse_dir.Rotate( true );
		reverse_dir.Rotate( true );

		//
		// # Step 1
		// > 중점을 만든다.
		//
		// =====
		// ==P==
		// =====
		//
		r2::PointInt pivot_point_1 = center_point;

		//
		// # Step 2
		//
		// Dierction 을 사용해서 중점을 이동 한계점 까지 이동시킨다.
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
		// 이동 완료된 점과 move_dir 을 곱해서 열을 지정해줄 기준점을 완성한다.
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
		// 각 루프마다 기준점에 "reverse_dir" 더해서 현재 처리할 열을 지정한다.
		// pivot_point_2 += reverse_dir : ( 0, 0 ) > ( 1, 0 ) > ( 2, 0 ) > ( 3, 0 ) > ( 4,  0 )
		//
		// 01234
		// =====
		// =====		
		//
		// temp_point = x * std::abs( move_dir.GetPoint().GetX() ), y * std::abs( move_dir.GetPoint().GetY() )
		// 이 코드를 통해 현재 처리할 라인이 맞는지 확인한다.
		//
		// 01234
		// 01234
		// 01234
		//
		for( ; IsIn( pivot_point_2.GetX(), pivot_point_2.GetY() ); pivot_point_2 += reverse_dir.GetPoint() )
		{
			for( uint32_t y = 0; GetHeight() > y; ++y )
			{
				for( uint32_t x = 0; GetWidth() > x; ++x )
				{
					r2::PointInt check_point( x * std::abs( move_dir.GetPoint().GetX() ), y * std::abs( move_dir.GetPoint().GetY() ) );

					if( pivot_point_2.GetX() != check_point.GetX() || pivot_point_2.GetY() != check_point.GetY() )
					{
						continue;
					}

					//
					// # Step 5
					//
					// 이 곳에서 이동, 합성 처리를 한다.
					//

					r2::PointInt currept_point( x, y );
					do
					{
						// Has Value?
						const auto my_number = GetNumber( currept_point.GetX(), currept_point.GetY() );
						if( 0 >= my_number )
						{
							break;
						}

						// Is In?
						r2::PointInt next_point( currept_point.GetX(), currept_point.GetY() );
						next_point += move_dir.GetPoint();
						if( !IsIn( next_point.GetX(), next_point.GetY() ) )
						{
							break;
						}

						// Is Empty?
						const auto other_number = GetNumber( next_point.GetX(), next_point.GetY() );
						if( 0 < other_number ) // Not Empty
						{
							// Is Same Number?
							if( other_number != my_number ) // Different Number
							{
								//
								// Can't Move
								//
								break;
							}
							else // Same Number
							{
								//
								// Merge and Stop
								//
								if( !IsLock( next_point.GetX(), next_point.GetY() ) )
								{
									const auto new_number = my_number + other_number;

									Remove( currept_point.GetX(), currept_point.GetY() );
									Add( next_point.GetX(), next_point.GetY(), new_number );
									Lock( next_point.GetX(), next_point.GetY() );

									has_moved = true;
								}

								break;
							}
						}
						else // Empty
						{
							//
							// Move
							//
							Remove( currept_point.GetX(), currept_point.GetY() );
							Add( next_point.GetX(), next_point.GetY(), my_number );

							has_moved = true;
						}

						currept_point = next_point;

					} while( true );
				}
			}
		}


		return has_moved;
	}
}