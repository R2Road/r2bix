#pragma once

#include <functional>

#include "r2bix_action_iAction.h"

namespace r2bix_action
{
	class CallbackAction : public r2bix_action::iAction
	{
	public:
		using CallbackT = std::function<void()>;

	private:
		CallbackAction();

	public:
		static std::unique_ptr<CallbackAction> Create();

		//
		//
		//
		void Enter() override;
		bool Update( const float delta_time ) override;

		void SetCallback( const CallbackT& callback )
		{
			mCallback = callback;
		}

	private:
		CallbackT mCallback;
	};
}