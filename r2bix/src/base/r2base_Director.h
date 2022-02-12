#pragma once

#include <memory>

namespace r2base
{
	using NodeUp = std::unique_ptr<class iNode>;

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