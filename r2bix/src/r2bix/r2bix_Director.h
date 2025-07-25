#pragma once

#include <memory>

#include "r2_SizeInt.h"
#include "r2_Point.h"

#include "r2bix_director_Config.h"
#include "r2bix_director_DefarredTaskQueue.h"
#include "r2bix_director_Scheduler.h"
#include "r2bix_director_ScreenBufferManager.h"
#include "r2bix_input_InputManager.h"
#include "r2bix_node_Node.h"
#include "r2bix_Camera.h"
#include "r2bix_render_Texture.h"


namespace r2bix
{
	class Director
	{
	public:
		explicit Director( const r2bix_director::Config& director_config );



		//
		//
		//
		void Setup( r2bix_node::NodeUp node );



		//
		//
		//
		void Run();
	private:
		void onUpdate( const float delta_time );
		void onRender();



		//
		//
		//
	public:
		void Terminate();



		//
		//
		//
		r2::SizeInt GetScreenSize() const
		{
			return mScreenSIze;
		}
		r2::Point<short> GetScreenOffset() const
		{
			return mScreenOffset;
		}

		r2bix_node::Node& GetRootNode() const
		{
			return ( *mRootNode );
		}



		//
		//
		//
		void RequestAbort()
		{
			mbAbort = true;
		}
		void ClearScreen();
		void Write2BackBuffer( const r2bix_render::Texture* const texture );
		std::string StartTextInputMode( const short cursor_x, const short cursor_y, const int text_length );



		//
		// Input
		//
		r2bix_input::InputManager& GetInputManager()
		{
			return mInputManager;
		}



		//
		//
		//
		void AddDefarredTask( const r2bix_director::DefarredTaskQueue::TaskT& task );



	private:
		r2bix_director::ScreenBufferManager mScreenBufferManager;
		r2bix_director::Scheduler mScheduler;
		bool mbAbort;
		r2::SizeInt mScreenSIze;
		r2::Point<short> mScreenOffset;

		r2bix::Camera mCamera;
		r2bix_render::Texture mRenderTarget;

		r2bix_input::InputManager mInputManager;

		r2bix_node::NodeUp mRootNode;
		r2bix_node::Node* mCurrentSceneNode;
		r2bix_node::NodeUp mNextSceneNode;

		r2bix_director::DefarredTaskQueue mDefarredTaskQueue;
	};
}