#include "pch.h"
#include "r2base_Director.h"

#include <utility> // std::move

#include "node/r2node_SceneNode.h"

namespace r2base
{
	Director::Director() :
		mScreenBufferManager()
		, mFPSTimer()
		, mbAbort( false )
		, mScreenBufferSIze( 107, 53 )

		, mSceneNode()
	{}

	void Director::Setup( r2node::SceneNodeUp node )
	{
		mSceneNode = std::move( node );
	}

	void Director::Run()
	{
		ClearScreen();

		while( !mbAbort )
		{
			if( mFPSTimer.Update() )
			{
				mSceneNode->Update( mFPSTimer.GetElapsedTime() );
				mSceneNode->Render();

				mScreenBufferManager.InitCursor();
				mScreenBufferManager.Swap();
			}
		}
	}

	void Director::ClearScreen()
	{
		mScreenBufferManager.ClearCurrentBuffer();
	}

	void Director::Write2BackBuffer( const r2render::Texture* const texture )
	{
		mScreenBufferManager.Write2BackBuffer( texture );
	}
}