#pragma once

#include "r2_iNode.h"

namespace r2
{
	class Director
	{
	public:
		Director();

		void Setup( NodeUp node );

		void Update();

	private:
		NodeUp mNode;
	};
}