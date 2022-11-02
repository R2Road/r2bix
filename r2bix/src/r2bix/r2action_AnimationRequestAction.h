#pragma once

#include "r2bix_action_iAction.h"
#include "r2bix_animation_constant.h"

namespace r2bix_action
{
	class AnimationRequestAction : public r2bix_action::iAction
	{
	public:
		enum class eOrder
		{
			PlayOnce,
			PlayRepeat,
			Stop,
		};
	private:
		AnimationRequestAction();

	public:
		static std::unique_ptr<AnimationRequestAction> Create();

		//
		//
		//
		void Enter() override;
		bool Update( const float delta_time ) override;

		void SetOrder( const eOrder order )
		{
			mOrder = order;
		}
		void SetAnimationIndex( const r2bix_animation::eIndex animation_index )
		{
			mAnimationIndex = animation_index;
		}

	private:
		eOrder mOrder;
		r2bix_animation::eIndex mAnimationIndex;
	};
}