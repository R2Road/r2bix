#pragma once

#include "r2bix_action_iAction.h"

namespace r2bix_action
{
	class RepeatAction : public r2bix_action::iAction
	{
	private:
		RepeatAction();

	public:
		static std::unique_ptr<RepeatAction> Create();

		//
		//
		//
		void Enter() override;
		bool Update( const float delta_time ) override;

		//
		//
		//
		void SetAction( r2bix_action::ActionUp action )
		{
			mAction = std::move( action );
		}

	private:
		r2bix_action::ActionUp mAction;
	};
}