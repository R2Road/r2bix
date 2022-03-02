#pragma once

#include <memory>

#include "base/r2base_FPSTimer.h"

namespace r2node
{
	using SceneNodeUp = std::unique_ptr<class SceneNode>;
}

namespace r2base
{
	class Director
	{
	public:
		Director();

		void Setup( r2node::SceneNodeUp node );

		void Update();

		void RequestAbort() { mbAbort = true; }

	private:
		FPSTimer mFPSTimer;
		bool mbAbort;
		r2node::SceneNodeUp mSceneNode;
	};
}