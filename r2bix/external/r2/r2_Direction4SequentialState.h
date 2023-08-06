//
// # Version Rule
// - 1.0.0 : ��� ����
// - 0.1.0 : ����ڰ� �ڵ带 �ٲ� ������ ��ȭ
// - 0.0.1 : ������ ��ȭ
//
// # Last Update		: 2023.06.02 AM.05.21
// # Version			: 1.0.0
//

#pragma once

namespace r2
{
	class Direction4SequentialState
	{
	public:
		enum class eState : char
		{
			NONE = -1,

			Up,
			Right,
			Down,
			Left,

			FIRST = Up,
			END = Left,

			SIZE = END + 1,
			HALF_SIZE = SIZE / 2,
		};

		using CoordinateT = char;


		static eState GetRandomState();

		static void ConvertState2Point( const eState state, CoordinateT* out_x, CoordinateT* out_y );
		static eState ConvertPoint2State( const CoordinateT x, const CoordinateT y );

		static eState ConvertInteger2State( const int value );

		static eState Rotate( const eState state, const bool bRight );
		static eState Reverse( const eState state );
	};
}
