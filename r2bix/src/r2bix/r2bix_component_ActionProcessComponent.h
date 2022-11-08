#pragma once

#include <vector>

#include "r2bix_action_iAction.h"
#include "r2bix_component_Component.h"

namespace r2bix_component
{
	class ActionProcessComponent : public r2bix_component::Component<ActionProcessComponent>
	{
	public:
		ActionProcessComponent( r2bix_node::Node& owner_node );

		//
		//
		//
		void SetAction( r2bix_action::ActionUp action )
		{
			mAction = std::move( action );
		}
		bool HasAction() const { return ( nullptr != mAction ); }
		void StartAction();
		bool IsRunning() const { return mbStart; }

		//
		// Override
		//
		void Update( const float delta_time ) override;

	private:
		r2bix_action::ActionUp mAction;
		bool mbStart;
	};
}