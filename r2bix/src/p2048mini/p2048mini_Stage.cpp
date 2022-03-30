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
	// # �̵� ��Ģ
	// 1. �������� ���� ����� �༮���� �̵�
	// 2. �ƹ��� �������� ���ߴٸ� �̵� �� ���� �ƴϴ�.
	//
	void Stage::Move( const r2::Direction4::eState direction_state )
	{
		//
		// ������ �����.
		// Dierction �� ����ؼ� ������ �̵� �Ѱ��� ���� �̵���Ų��.
		// �̵� �Ϸ�� ������ ���������� ��´�.
		//
		// ���������� ����� �༮���� �̵��� ���Ѿ� �Ѵ�.
		// ( �� �༮�� ���� �����̸� ���� ó���� �������� ����� �༮�� ������ �������� ���� �� �ִ�. )
		// ���� �۾��� ���� �������� ������ ��ü ����� �����Ѵ�.
		//
		// �̵�, �ռ� ó���� �Ѵ�.
		//

		r2::Direction4 dir( direction_state );
		r2::PointInt center_point( mGridIndexConverter.GetWidth() / 2, mGridIndexConverter.GetHeight() );
	}
}