//
// # 2024.03.15 by R2Road
// 
// 모든 컴포넌트는 우선 Create 되고 이후 설정된다.
// 생성즉시 초기화는 컴포넌트에 해당하지 않는다.
//

#pragma once

#include <memory>

#include "r2_PointInt.h"

namespace r2bix
{
	class Camera;
	class Director;
}

namespace r2bix_render
{
	class iRenderTarget;
}

namespace r2bix_node
{
	class Node;
}

namespace r2bix_component
{
	using ComponentUp = std::unique_ptr<class iComponent>;
	class iComponent
	{
	protected:
		iComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) :
			  mDirector( director )
			, mOwnerNode( owner_node )
			, mbActivate( false )
		{}
	public:
		virtual ~iComponent()
		{}



		//
		//
		//
	public:
		virtual int GetStaticID() const = 0;

		r2bix_node::Node& GetOwnerNode() const
		{
			return mOwnerNode;
		}

		r2bix::Director& GetDirector() const
		{
			return mDirector;
		}

		bool IsActivate() const
		{
			return mbActivate;
		}



		//
		// 생성시 1회 불리는 자기 초기화 함수
		//
		bool Init()
		{
			return initProcess();
		}
	protected:
		virtual bool initProcess()
		{
			return true;
		}



		//
		// 소유한 Node 가 AddChild, RemoveChild 되면 호출
		//
	public:
		void Enter()
		{
			enterProcess();
		}
	protected:
		virtual void enterProcess()
		{}

	public:
		void Exit()
		{
			exitProcess();
		}
	protected:
		virtual void exitProcess()
		{}



		//
		// Node, Component 가 생성 완료된 이후에
		// 데이터 설정 단계에서 Activate Flag에 따라 호출
		//
	public:
		void Activate()
		{
			if( false == mbActivate )
			{
				mbActivate = true;
				activateProcess();
			}
		}
	protected:
		virtual void activateProcess()
		{}

	public:
		void Deactivate()
		{
			if( true == mbActivate )
			{
				mbActivate = false;
				deactivateProcess();
			}
		}
	protected:
		virtual void deactivateProcess()
		{}



		//
		//
		//
	public:
		void Terminate()
		{
			Deactivate();
			terminateProcess();
		}
	protected:
		virtual void terminateProcess()
		{}



		//
		//
		//
	public:
		void Update( const float delta_time )
		{
			updateProcess( delta_time );
		}
	protected:
		virtual void updateProcess( const float /*delta_time*/ )
		{}

	public:
		virtual void Render( const r2bix::Camera* const /*camera*/, r2bix_render::iRenderTarget* const /*render_target*/, r2::PointInt /*offset*/ )
		{}



	protected:
		r2bix::Director& mDirector;
		r2bix_node::Node& mOwnerNode;
		bool mbActivate;
	};
}