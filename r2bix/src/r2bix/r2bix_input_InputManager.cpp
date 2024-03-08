#include "r2bix_input_InputManager.h"

namespace r2bix_input
{
	InputManager::InputManager() : mMachineInputCollector()
	{}

	void InputManager::Update()
	{
		mMachineInputCollector.Collect();
	}
}