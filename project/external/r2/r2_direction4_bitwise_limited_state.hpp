#pragma once

//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.06.22 AM.10.52
// # Version			: 1.0.2
//

namespace r2
{
	class Direction4BitwiseLimitedState
	{
	public:
		enum class eState : unsigned char
		{
			NONE = 0,

			Up          = 1,
			Right       = 1 << 1,
			Down        = 1 << 2,
			Left        = 1 << 3,

			FIRST = Up,
			END = Left,

			SIZE = 4,
			HALF_SIZE = SIZE / 2,

			ALL = Up | Right | Down | Left,
		};

		using CoordinateT = char;

		using FlagType = unsigned char;


		static void ConvertFlags2EnableDirectionCount( const FlagType enable_state_flags, char* out_size );

		static FlagType ConvertPoint2EnableStateFlags( const CoordinateT x, const CoordinateT y );

		static void ConvertState2Point( const eState state, CoordinateT* out_x, CoordinateT* out_y );
		static void ConvertPoint2State( const CoordinateT x, const CoordinateT y, eState* out_state );

		static eState ConvertInteger2State( const int value );

		static void SelectEnableState( const FlagType enable_state_flags, eState* out_state );
		static void SelectRandomState( const FlagType enable_state_flags, eState* out_state );

		static void Rotate( const FlagType enable_state_flags, const bool bRight, eState* out_state );
		static void Reverse( eState* out_state );
		static eState Reverse( const eState state );
	};
}
