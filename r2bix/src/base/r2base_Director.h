#pragma once

#include <memory>

#include "base/r2base_FPSTimer.h"
#include "node/r2node_SceneNode.h"
#include "base/r2base_ScreenBufferManager.h"

namespace r2base
{
	class Director
	{
	public:
		Director();

		void Setup( r2node::SceneNodeUp node );

		void Update();

		void RequestAbort() { mbAbort = true; }
		void ClearScreen();

	private:
		ScreenBufferManager mScreenBufferManager;
		FPSTimer mFPSTimer;
		bool mbAbort;
		r2node::SceneNodeUp mSceneNode;
	};
}