#include "pch.h"
#include "r2action_BlinkAction.h"

#include "base/r2base_Node.h"

namespace r2action
{
	BlinkAction::BlinkAction() :
		mStartStep( eStep::Show )
		, mCurrentStep( eStep::Sleep )
		, mTimer4Show( 1.f )
		, mTimer4Hide( 1.f )
	{}

	std::unique_ptr<BlinkAction> BlinkAction::Create()
	{
		std::unique_ptr<BlinkAction> ret( new ( std::nothrow ) BlinkAction() );
		return ret;
	}

	void BlinkAction::Enter()
	{
		mCurrentStep = mStartStep;

		mOwnerNode->SetVisible( eStep::Show == mCurrentStep );

		mTimer4Show.reset();
		mTimer4Hide.reset();
	}
	bool BlinkAction::Update( const float delta_time )
	{
		switch( mCurrentStep )
		{
		case eStep::Show:
			if( !mTimer4Show.update( delta_time ) )
			{
				mCurrentStep = eStep::Hide;
				mOwnerNode->SetVisible( false );
			}
			break;
		case eStep::Hide:
			if( !mTimer4Hide.update( delta_time ) )
			{
				mCurrentStep = eStep::Sleep;
				mOwnerNode->SetVisible( true );
			}
			break;
		}

		return eStep::Sleep != mCurrentStep;
	}
}