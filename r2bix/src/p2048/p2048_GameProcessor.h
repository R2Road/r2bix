#pragma once

#include <stdint.h>

#include "r2_Direction4Sequential.h"

namespace p2048
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
		uint32_t GetScore() const { return mScore; }
		uint32_t GetSum4Merged() const { return mSum4Merged; }
		uint32_t GetMaxNumber() const { return mMaxNumber; }

		//
		//
		//
	public:
		void Reset();

		void AddNumber( const uint32_t min, const uint32_t max );

		MoveResult Move( const r2::Direction4Sequential::eState direction_state );
		bool IsMovable() const;
		bool IsGameClear() const;
		bool IsGameEnd() const;

	private:
		Stage* const mStage;
		uint32_t mScore;
		uint32_t mSum4Merged;
		uint32_t mMaxNumber;
	};
}