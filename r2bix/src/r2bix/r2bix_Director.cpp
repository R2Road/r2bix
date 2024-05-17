#include "r2bix_Director.h"

#include <utility> // std::move

#include "r2_Assert.h"

#include "r2bix_utility_InputUtil.h"

namespace r2bix
{
	Director::Director( const r2bix_director::Config& director_config ) :
		  mScreenBufferManager()
		, mScheduler( director_config, std::bind( &Director::onUpdate, this, std::placeholders::_1 ), std::bind( &Director::onRender, this ) )
		, mbAbort( false )
		, mScreenSIze( director_config.ScreenSize_Width, director_config.ScreenSize_Height )
		, mScreenOffset( director_config.ScreenOffset_X, director_config.ScreenOffset_Y )

		, mCamera(
			  director_config.ScreenSize_Width / 2
			, director_config.ScreenSize_Height / 2
			, director_config.ScreenSize_Width
			, director_config.ScreenSize_Height
		)
		, mRenderTarget( director_config.ScreenSize_Width, director_config.ScreenSize_Height, '@' )

		, mInputManager( director_config.ScreenOffset_X, director_config.ScreenOffset_Y )

		, mCurrentSceneNode()
		, mNextSceneNode()

		, mDefarredTaskQueue()
	{
		R2ASSERT( ( director_config.ScreenSize_Width & 1 ), "Director 스크린 버퍼 크기 홀수로 넣어라." );
		R2ASSERT( ( director_config.ScreenSize_Height & 1 ), "Director 스크린 버퍼 크기 홀수로 넣어라." );
	}



	void Director::Setup( r2bix_node::NodeUp node )
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

			mDefarredTaskQueue.Process();
		}

		r2bix_utility::ClearCInputBuffer();
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
		mScreenBufferManager.SetCursorPosition( 0, 0 );
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
		mScreenBufferManager.Write2BackBuffer( mScreenOffset.GetX(), mScreenOffset.GetY(), texture );
	}

	std::string Director::StartTextInputMode( const short cursor_x, const short cursor_y, const int text_length )
	{
		return mScreenBufferManager.OpenTextInputBuffer( mScreenOffset.GetX(), mScreenOffset.GetY(), cursor_x, cursor_y, text_length, &mRenderTarget );
	}



	void Director::AddDefarredTask( const r2bix_director::DefarredTaskQueue::TaskT& task )
	{
		mDefarredTaskQueue.Add( task );
	}
}