//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.06.09 PM.00.39
// # Version			: 1.2.0
//

#pragma once

namespace r2
{
	class Direction8BitwiseLimitedState
	{
	public:
		enum class eState : unsigned char
		{
			NONE = 0,

			Up = 1,
			Up_Right = 1 << 1,
			Right = 1 << 2,
			Down_Right = 1 << 3,
			Down = 1 << 4,
			Down_Left = 1 << 5,
			Left = 1 << 6,
			Up_Left = 1 << 7,

			ALL = Up | Up_Right | Right | Down_Right | Down | Down_Left | Left | Up_Left,

			FIRST = Up,
			END = Up_Left,
		};

		using CoordinateT = char;

		using FlagType = unsigned char;


		static void ConvertFlags2EnableDirectionCount( const FlagType enable_state_flags, char* out_size );

		static void ConvertState2Point( const eState state, CoordinateT* out_x, CoordinateT* out_y );
		static void ConvertPoint2State( const int x, const int y, eState* out_state );

		static eState ConvertInteger2State( const int value );

		static void SelectEnableState( const FlagType enable_state_flags, eState* out_state );
		static void SelectRandomState( const FlagType enable_state_flags, eState* out_state );

		static bool IsDiagonalState( const eState state );

		static void Rotate( const FlagType enable_state_flags, const bool bRight, eState* out_state );
		static void Reverse( eState* out_state );
		static eState Reverse( const eState state );
	};
}
