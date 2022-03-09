#pragma once

#include <list>
#include <memory>

#include "r2/r2_PointInt.h"
#include "r2base_Component.h"

//
// # 2022.02.28 by R2Road
//
// 컴포넌트 기반 시스템을 써본 경험은 있으나 만들어 본 경험이 없으니 여기서 해본다.
//
// 노드와 컴포넌트를 조합하여 특정 기능을 가진 표준 노드를 제작한다.
// 사용자 정의 노드의 제작은 가급적 없도록 노력하자.
//

namespace r2component
{
	class TransformComponent;
}

namespace r2render
{
	class Camera;
	class iRenderTarget;
}

namespace r2base
{
	class Director;

	using NodeUp = std::unique_ptr<class Node>;
	class Node
	{
	protected:
		using ComponentContainerT = std::list<ComponentUp>;
		using ChildContainerT = std::list<r2base::NodeUp>;

	public:
		Node( Director& director );
		virtual ~Node() {}

	static std::unique_ptr<Node> Create( r2base::Director& director );

	public:
		virtual bool Init();
		virtual void Update();
		virtual void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target, r2::PointInt offset );

		//
		//
		//
		template<typename ComponentT>
		ComponentT* const GetComponent() const
		{
			for( auto& c : mComponentContainer )
			{
				if( r2base::ComponentStaticID<ComponentT>::Get() == c->GetStaticID() )
				{
					return static_cast<ComponentT*>( c.get() );
				}
			}

			return nullptr;
		}
		void AddComponent( r2base::ComponentUp component );

		//
		//
		//
		void AddChild( r2base::NodeUp child_node );

	protected:
		Director& mDirector;
		ComponentContainerT mComponentContainer;
		ChildContainerT mChildContainer;
	public:
		r2component::TransformComponent* mTransformComponent;
	};
}