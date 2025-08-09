#pragma once

#include <vector>

#include "r2bix_action_iAction.h"

namespace r2bix_action
{
	class SequenceAction : public r2bix_action::iAction
	{
	private:
		using ActionContainerT = std::vector<r2bix_action::ActionUp>;

		SequenceAction();

	public:
		static std::unique_ptr<SequenceAction> Create();

		void Enter() override;
		bool Update( const float delta_time ) override;

		template<typename ActionT>
		ActionT* AddAction()
		{
			static_assert( std::is_base_of<r2bix_action::iAction, ActionT>() );

			auto action = ActionT::Create();
			auto ret = action.get();
			mActionContainer.push_back( std::move( action ) );

			return ret;
		}

	private:
		ActionContainerT mActionContainer;
		ActionContainerT::iterator mCurrentActionIndicator;
	};
}