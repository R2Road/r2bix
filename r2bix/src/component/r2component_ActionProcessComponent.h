#pragma once

#include <vector>

#include "base/r2base_Action.h"
#include "base/r2base_Component.h"
#include "base/r2base_ComponentStaticID.h"

namespace r2component
{
	class ActionProcessComponent : public r2base::Component
	{
	private:
		using ActionContainerT = std::vector<r2base::ActionUp>;

		ActionProcessComponent( r2base::Node& owner_node );

	public:
		int GetStaticID() const override { return r2base::ComponentStaticID<ActionProcessComponent>::Get(); }
		static std::unique_ptr<ActionProcessComponent> Create( r2base::Node& owner_node );

		template<typename ActionT>
		ActionT* AddAction()
		{
			static_assert( std::is_base_of<r2base::Action, ActionT>() );

			std::unique_ptr<ActionT> action( new ( std::nothrow ) ActionT() );
			auto ret = action.get();
			mActionContainer.push_back( std::move( action ) );

			return ret;
		}

		//
		//
		//
		void StartAction();

	private:
		ActionContainerT mActionContainer;
		bool mbStart;
	};
}