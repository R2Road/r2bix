#pragma once

#include "r2bix_component_iComponent.h"
#include "r2bix_component_ComponentStaticID.h"

namespace r2bix_component
{
	template<typename T>
	class Component : public iComponent
	{
	public:
		friend class r2bix_node::Node;

		using MyT = T;
		using MyUp = std::unique_ptr<MyT>;


	protected:
		Component( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::iComponent( director, owner_node )
		{}
	private:
		static MyUp Create( r2bix::Director& director, r2bix_node::Node& owner_node )
		{
			MyUp ret( new ( std::nothrow ) MyT( director, owner_node ) );
			if( !ret || !ret->Init() )
			{
				ret.reset();
			}

			return ret;
		}


	public:
		int GetStaticID() const override
		{
			return r2bix_component::ComponentStaticID<MyT>::Get();
		}
	};
}