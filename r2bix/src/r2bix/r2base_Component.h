#pragma once

#include "r2base_iComponent.h"
#include "r2base_ComponentStaticID.h"

namespace r2base
{
	template<typename T>
	class Component : public iComponent
	{
	public:
		using MyT = T;
		using MyUp = std::unique_ptr<MyT>;

	protected:
		Component( r2bix_node::Node& owner_node ) : r2base::iComponent( owner_node )
		{}

	public:
		static MyUp Create( r2bix_node::Node& owner_node )
		{
			MyUp ret( new ( std::nothrow ) MyT( owner_node ) );
			if( !ret || !ret->Init() )
			{
				ret.reset();
			}

			return ret;
		}

		int GetStaticID() const override
		{
			return r2base::ComponentStaticID<MyT>::Get();
		}
	};
}