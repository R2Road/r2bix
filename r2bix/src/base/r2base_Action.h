#pragma once

namespace r2base
{
	class Action
	{
	public:
		Action() = default;

		virtual void Update() = 0;
	};
}