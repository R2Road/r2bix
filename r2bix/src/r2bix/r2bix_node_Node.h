//
// # 2022.02.28 by R2Road
//
// 컴포넌트 기반 시스템을 써본 경험은 있으나 만들어 본 경험이 없으니 여기서 해본다.
//
// 노드와 컴포넌트를 조합하여 특정 기능을 가진 표준 노드를 제작한다.
// 사용자 정의 노드의 제작은 가급적 없도록 노력하자.
//

//
// # 2024.03.15 by R2Road
// 
// 모든 노드는 우선 Create 되고 이후 설정된다.
// 생성즉시 초기화는 노드에 해당하지 않는다.
// 
// 노드 생성이 완료되면 컴포넌트의 생성도 완료되어 있다.
//

#pragma once

#include <list>
#include <memory>
#include <string>
#include <type_traits>

#include "r2_PointInt.h"
#include "r2bix_component_TransformComponent.h"

namespace r2bix
{
	class Director;
}

namespace r2component
{
	class TransformComponent;
}

namespace r2bix_render
{
	class Camera;
	class iRenderTarget;
}

namespace r2bix_node
{
	using NodeUp = std::unique_ptr<class Node>;
	class Node
	{
	private:
		using ComponentContainerT = std::list<r2bix_component::ComponentUp>;
	public:
		using ChildContainerT = std::list<NodeUp>;



	private:
		Node( r2bix::Director& director );
	public:
		~Node() {}



	static std::unique_ptr<Node> Create( r2bix::Director& director );



	public:
		//
		// 생성시 1회 불리는 자기 초기화 함수
		//
		bool Init();

		//
		// Add Child, Remove Child 되면 호출
		//
		void Enter();
		void Exit();

		//
		// 보유 컴포넌트, 자식 노드의 Update, Render 호출.
		//
		void Update( const float delta_time );
		void Render( const r2bix_render::Camera* const camera, r2bix_render::iRenderTarget* const render_target, r2::PointInt offset );
		//
		//
		//
		void Terminate();



		//
		//
		//
		const std::string& GetName() const
		{
			return mName;
		}
		r2bix::Director& GetDirector() const { return mDirector; }
		bool IsVisible() const { return mbVisible; }
		void SetVisible( const bool visible )
		{
			mbVisible = visible;
		}



		//
		//
		//
		template<typename ComponentT>
		ComponentT* const GetComponent() const
		{
			for( auto& c : mComponentContainer )
			{
				if( r2bix_component::ComponentStaticID<ComponentT>::Get() == c->GetStaticID() )
				{
					return static_cast<ComponentT*>( c.get() );
				}
			}

			return nullptr;
		}
		template<typename ComponentT>
		ComponentT* AddComponent()
		{
			static_assert( std::is_base_of<r2bix_component::iComponent, ComponentT>() );

			if( GetComponent<ComponentT>() )
			{
				return nullptr;
			}

			auto component = ComponentT::Create( *this );
			auto ret = component.get();
			mComponentContainer.push_back( std::move( component ) );

			return ret;
		}



		//
		//
		//
		int GetChildCount() const
		{
			return static_cast<int>( mChildContainer.size() );
		}
		const ChildContainerT& GetChildContainer() const
		{
			return mChildContainer;
		}

		void SetParentNode( Node* parent_node )
		{
			mParentNode = parent_node;
		}
		Node* GetParentNode() const
		{
			return mParentNode;
		}

		template<typename NodeT>
		Node* AddChild()
		{
			return AddChild<NodeT>( 0 );
		}
		template<typename NodeT>
		Node* AddChild( const int32_t z_order )
		{
			//
			// 생성
			//
			NodeUp child_node = NodeT::Create( mDirector );

			//
			// 기본 설정
			//
			child_node->SetParentNode( this );
			child_node->mTransformComponent->SetZ( z_order );

			Node* ret = child_node.get();

			//
			// Find Insert Pivot
			//
			auto cur = mChildContainer.begin();
			for( auto end = mChildContainer.end(); end != cur; ++cur )
			{
				if( z_order > ( *cur )->mTransformComponent->GetZ() )
				{
					continue;
				}

				if( z_order < ( *cur )->mTransformComponent->GetZ() )
				{
					break;
				}

				//if( z_order == ( *cur )->mTransformComponent->GetZ() )
				{
					auto temp = cur;
					++temp;
					for( ; end != temp; ++temp )
					{
						if( z_order != ( *cur )->mTransformComponent->GetZ() )
						{
							break;
						}
					}
					cur = temp;
				}

				break;
			}

			//
			// Insert
			//
			if( cur == mChildContainer.end() )
			{
				mChildContainer.push_back( std::move( child_node ) );
			}
			else
			{
				mChildContainer.insert( cur, std::move( child_node ) );
			}

			//
			// Enter The Hierarchy
			//
			ret->Enter();

			return ret;
		}



	protected:
		std::string mName;

		r2bix::Director& mDirector;
		bool mbVisible;
		ComponentContainerT mComponentContainer;

		Node* mParentNode;
		ChildContainerT mChildContainer;
	public:
		r2bix_component::TransformComponent* mTransformComponent;
	};
}