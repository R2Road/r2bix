//
// # 2024.03.15 by R2Road
// 
// 모든 컴포넌트는 우선 Create 되고 이후 설정된다.
// 생성즉시 초기화는 컴포넌트에 해당하지 않는다.
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
		// 생성시 1회 불리는 자기 초기화 함수
		//
		virtual bool Init()
		{
			return true;
		}



		//
		// 
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
		virtual void Update( const float /*delta_time*/ )
		{}

		virtual void Render( const r2bix_render::Camera* const /*camera*/, r2bix_render::iRenderTarget* const /*render_target*/, r2::PointInt /*offset*/ )
		{}



	protected:
		r2bix_node::Node& mOwnerNode;
		bool mbActivate;
	};
}