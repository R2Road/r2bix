#pragma once

namespace r2
{
	class Direction8SequentialState
	{
	public:
		enum class eState : char
		{
			NONE = -1,

			Up,
			Up_Right,
			Right,
			Down_Right,
			Down,
			Down_Left,
			Left,
			Up_Left,

			FIRST = Up,
			END = Up_Left,

			SIZE = END + 1,
			HALF_SIZE = SIZE / 2,
		};

		using CoordinateT = char;


		static eState GetRandomState_F2E();
		static eState GetRandomState_N2E();

		static void ConvertState2Point( const eState state, CoordinateT* out_x, CoordinateT* out_y );
		static void ConvertPoint2State( const CoordinateT x, const CoordinateT y, eState* out_state );

		static eState ConvertInteger2State( const int value );

		static bool IsDiagonalState( const eState state );

		static eState Rotate( const eState state, const bool bRight );
		static eState Reverse( const eState state );
	};
}
