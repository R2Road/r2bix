//
// # 2024.03.15 by R2Road
// 
// ��� ������Ʈ�� �켱 Create �ǰ� ���� �����ȴ�.
// ������� �ʱ�ȭ�� ������Ʈ�� �ش����� �ʴ´�.
//

#pragma once

#include <memory>

#include "r2_PointInt.h"

namespace r2bix_render
{
	class Camera;
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
		iComponent( r2bix_node::Node& owner_node ) :
			  mOwnerNode( owner_node )
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

		bool IsActivate() const
		{
			return mbActivate;
		}



		//
		// ������ 1ȸ �Ҹ��� �ڱ� �ʱ�ȭ �Լ�
		//
		bool Init()
		{
			return InitProcess();
		}
	protected:
		virtual bool InitProcess()
		{
			return true;
		}



		//
		// ������ Node �� AddChild, RemoveChild �Ǹ� ȣ��
		//
	public:
		void Enter()
		{
			EnterProcess();
		}
	protected:
		virtual void EnterProcess()
		{}

	public:
		void Exit()
		{
			ExitProcess();
		}
	protected:
		virtual void ExitProcess()
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
				ActivateProcess();
			}
		}
	protected:
		virtual void ActivateProcess()
		{}

	public:
		void Deactivate()
		{
			if( true == mbActivate )
			{
				mbActivate = false;
				DeactivateProcess();
			}
		}
	protected:
		virtual void DeactivateProcess()
		{}



		//
		//
		//
	public:
		void Terminate()
		{
			Deactivate();
			TerminateProcess();
		}
	protected:
		virtual void TerminateProcess()
		{}



		//
		//
		//
	public:
		void Update( const float delta_time )
		{
			UpdateProcess( delta_time );
		}
	protected:
		virtual void UpdateProcess( const float /*delta_time*/ )
		{}

	public:
		virtual void Render( const r2bix_render::Camera* const /*camera*/, r2bix_render::iRenderTarget* const /*render_target*/, r2::PointInt /*offset*/ )
		{}



	protected:
		r2bix_node::Node& mOwnerNode;
		bool mbActivate;
	};
}