#pragma once

#include <memory>

namespace r2base
{
	using ActionUp = std::unique_ptr<class Action>;
	class Action
	{
	public:
		Action() {}

		virtual void Update() = 0;
	};
}