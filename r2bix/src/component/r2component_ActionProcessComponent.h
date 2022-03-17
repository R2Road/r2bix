#pragma once

#include "base/r2base_Component.h"
#include "base/r2base_ComponentStaticID.h"

namespace r2component
{
	class ActionProcessComponent : public r2base::Component
	{
	private:
		ActionProcessComponent( r2base::Node& owner_node );

	public:
		int GetStaticID() const override { return r2base::ComponentStaticID<ActionProcessComponent>::Get(); }
		static std::unique_ptr<ActionProcessComponent> Create( r2base::Node& owner_node );
	};
}