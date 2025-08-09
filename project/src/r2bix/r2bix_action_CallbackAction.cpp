#include "r2bix_action_CallbackAction.h"

#include <cassert>

namespace r2bix_action
{
	CallbackAction::CallbackAction() : mCallback()
	{}

	std::unique_ptr<CallbackAction> CallbackAction::Create()
	{
		std::unique_ptr<CallbackAction> ret( new ( std::nothrow ) CallbackAction() );
		return ret;
	}

	void CallbackAction::Enter()
	{
		assert( nullptr != mCallback );
	}
	bool CallbackAction::Update( const float /*delta_time*/ )
	{
		mCallback();
		return false;
	}
}