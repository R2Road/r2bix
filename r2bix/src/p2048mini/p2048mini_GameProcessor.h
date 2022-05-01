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
		};

		GameProcessor( Stage* const stage );

		//
		//
		//
	public:
		int GetScore() const { return mScore; }
		int GetSum4Merged() const { return mSum4Merged; }

		//
		//
		//
	public:
		void Reset();

		void AddNumber( const uint32_t min, const uint32_t max );

		MoveResult Move( const r2::Direction4::eState direction_state );
		bool IsMovable() const;
		bool IsGameEnd() const;

	private:
		Stage* const mStage;
		int mScore;
		int mSum4Merged;
		uint32_t mMaxNumber;
	};
}