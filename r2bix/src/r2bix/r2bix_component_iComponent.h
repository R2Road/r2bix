//
// # 2024.03.15 by R2Road
// 
// ��� ������Ʈ�� �켱 Create �ǰ� ���� �����ȴ�.
// ������� �ʱ�ȭ�� ������Ʈ�� �ش����� �ʴ´�.
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
		// ������ 1ȸ �Ҹ��� �ڱ� �ʱ�ȭ �Լ�
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
		// ������ Node �� AddChild, RemoveChild �Ǹ� ȣ��
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
		// Node, Component �� ���� �Ϸ�� ���Ŀ�
		// ������ ���� �ܰ迡�� Activate Flag�� ���� ȣ��
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