#pragma once

#include <vector>

#include "r2bix_action_iAction.h"
#include "r2base_Component.h"

namespace r2component
{
	class ActionProcessComponent : public r2base::Component<ActionProcessComponent>
	{
	public:
		ActionProcessComponent( r2base::Node& owner_node );

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