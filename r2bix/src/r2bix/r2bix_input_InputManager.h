#pragma once

#include "r2bix_input_MachineInputCollector.h"

namespace r2bix_input
{
	class InputManager
	{
	public:
		InputManager();

		void Update();

	public:
		MachineInputCollector mMachineInputCollector;
	};
}