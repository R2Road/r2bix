#include "r2bix_Director.h"

#include <utility> // std::move

#include "r2_Assert.h"
#include "r2bix_node_SceneNode.h"

namespace r2bix
{
	Director::Director( const r2bix_director::Config& director_config ) :
		mScreenBufferManager( director_config.ScreenBufferOffset_X, director_config.ScreenBufferOffset_Y )
		, mScheduler( director_config, std::bind( &Director::onUpdate, this, std::placeholders::_1 ), std::bind( &Director::onRender, this ) )
		, mbAbort( false )
		, mScreenBufferSIze( director_config.ScreenBufferSize_Width, director_config.ScreenBufferSize_Height )

		, mCamera(
			  director_config.ScreenBufferSize_Width / 2
			, director_config.ScreenBufferSize_Height / 2
			, director_config.ScreenBufferSize_Width
			, director_config.ScreenBufferSize_Height
		)
		, mRenderTarget( director_config.ScreenBufferSize_Width, director_config.ScreenBufferSize_Height, '@' )

		, mInputManager( director_config.ScreenBufferOffset_X, director_config.ScreenBufferOffset_Y )

		, mCurrentSceneNode()
		, mNextSceneNode()
	{
		R2ASSERT( ( director_config.ScreenBufferSize_Width & 1 ), "Director 스크린 버퍼 크기 홀수로 넣어라." );
		R2ASSERT( ( director_config.ScreenBufferSize_Height & 1 ), "Director 스크린 버퍼 크기 홀수로 넣어라." );
	}



	void Director::Setup( r2bix_node::SceneNodeUp node )
	{
		if( mCurrentSceneNode )
		{
			mNextSceneNode = std::move( node );
		}
		else
		{
			mCurrentSceneNode = std::move( node );
		}
	}



	void Director::Run()
	{
		ClearScreen();

		while( !mbAbort )
		{
			if( mNextSceneNode )
			{
				mCurrentSceneNode->Terminate();
				mCurrentSceneNode = std::move( mNextSceneNode );
			}

			mScheduler.Do();
		}
	}
	void Director::onUpdate( const float delta_time )
	{
		mInputManager.Update();

		mCurrentSceneNode->Update( delta_time );
	}
	void Director::onRender()
	{
		//
		// Render 2 Render-Target
		//
		mRenderTarget.FillCharacterAll( ' ' );
		mRenderTarget.FillColorAll( r2bix::DefaultColorValue );

		mCurrentSceneNode->Render( &mCamera, &mRenderTarget, r2::PointInt::GetZERO() );

		//
		// Write 2 Back-Buffer
		//
		Write2BackBuffer( &mRenderTarget );

		//
		// Swap
		//
		mScreenBufferManager.InitCursor();
		mScreenBufferManager.Swap();
	}



	void Director::Terminate()
	{
		if( mCurrentSceneNode )
		{
			mCurrentSceneNode->Terminate();
		}
	}



	void Director::ClearScreen()
	{
		mScreenBufferManager.ClearCurrentBuffer();
	}

	void Director::Write2BackBuffer( const r2bix_render::Texture* const texture )
	{
		mScreenBufferManager.Write2BackBuffer( texture );
	}
}