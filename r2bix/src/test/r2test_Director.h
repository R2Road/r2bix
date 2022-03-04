#pragma once

#include "r2test_Menu.h"

namespace r2test
{
	class Director
	{
	public:
		Director();

		void Setup( MenuUp menu );

		void Update();

	private:
		MenuUp mMenu;
	};
}