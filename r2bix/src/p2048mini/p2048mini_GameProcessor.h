#pragma once

namespace p2048mini
{
	class Stage;

	class GameProcessor
	{
	public:
		GameProcessor( Stage* const stage );

	private:
		Stage* const mStage;
	};
}