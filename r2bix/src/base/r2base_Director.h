#pragma once

#include <memory>

#include "base/r2base_ScreenBufferManager.h"
#include "node/r2node_SceneNode.h"
#include "r2/r2_FPSTimer.h"
#include "r2/r2_Size_Int.h"

namespace r2base
{
	class Director
	{
	public:
		Director();

		void Setup( r2node::SceneNodeUp node );

		void Run();

		//
		//
		//
		r2::SizeInt GetScreenBufferSize() const { return mScreenBufferSIze; }

		//
		//
		//
		void RequestAbort() { mbAbort = true; }
		void ClearScreen();
		void Write2BackBuffer( const r2render::Texture* const texture );

	private:
		ScreenBufferManager mScreenBufferManager;
		r2::FPSTimer mFPSTimer;
		bool mbAbort;
		r2::SizeInt mScreenBufferSIze;

		r2node::SceneNodeUp mCurrentSceneNode;
		r2node::SceneNodeUp mNextSceneNode;
	};
}