//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.05.21 AM.08.37
// # Version			: 1.0.0
//

#pragma once

#include "r2_Direction8SequentialState.h"

namespace r2
{
	class Direction8InGrid
	{
	public:
		using StateT = r2::Direction8SequentialState;
		using eState = StateT::eState;



		Direction8InGrid();
		explicit Direction8InGrid( const eState state );
		explicit Direction8InGrid( const eState state, const int grid_width );



		//
		//
		//
		bool operator==( const Direction8InGrid& other ) const
		{
			return other.mState == mState;
		}
		bool operator!=( const Direction8InGrid& other ) const
		{
			return !( operator==( other ) );
		}



		//
		//
		//
		eState GetState() const
		{
			return mState;
		}
		int GetWidth() const
		{
			return mGridWidth;
		}
		int GetLinearIndex() const
		{
			return mLinearIndex;
		}



		//
		//
		//
		void SetState( const eState new_state );



		//
		//
		//
		bool IsDiagonal() const;



		//
		//
		//
		void Rotate( const bool is_right = true );



	private:
		const int mGridWidth;

		eState mState;
		int mLinearIndex;
	};
}