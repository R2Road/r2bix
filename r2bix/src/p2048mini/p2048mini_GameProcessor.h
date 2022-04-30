#pragma once

#include "r2/r2_Direction4.h"

namespace p2048mini
{
	class Stage;

	class GameProcessor
	{
	public:
		struct MoveResult
		{
			bool has_moved = false;
			uint32_t sum4merged = 0;
		};

		GameProcessor( Stage* const stage );

		//
		//
		//
	public:
		void AddNumber( const uint32_t min, const uint32_t max );

		MoveResult Move( const r2::Direction4::eState direction_state );
		bool IsMovable() const;
		bool IsGameEnd() const;

	private:
		Stage* const mStage;
	};
}