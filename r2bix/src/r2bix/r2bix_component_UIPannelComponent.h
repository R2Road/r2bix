#pragma once

#include "r2_SizeInt.h"

#include "r2bix_component_Component.h"
#include "r2bix_input_Listener4Mouse.h"

namespace r2bix_input
{
	class UIInputListener;
}

namespace r2bix_component
{
	class UIPannelComponent : public r2bix_component::Component<UIPannelComponent>
	{
	public:
		enum eState
		{
			None,

			MouseOver,
			MouseMove, // required mouse over
			MouseLeave,
		};

		using MouseResponseCallbackT = std::function<void()>;
		using ListenerContainer = std::list<r2bix_input::UIInputListener*>;



		UIPannelComponent( r2bix_node::Node& owner_node );



		//
		//
		//
	private:
		void ActivateProcess() override;
		void DeactivateProcess() override;

		void Update( const float delta_time ) override final;



		//
		//
		//
	public:
		int GetWidth() const
		{
			return mSize.GetWidth();
		}
		int GetHeight() const
		{
			return mSize.GetHeight();
		}

		void SetSize( const uint32_t width, const uint32_t height )
		{
			mSize.Set( width, height );
		}



		//
		//
		//
		r2bix_input::Listener4Mouse* const GetListener4Mouse()
		{
			return &mListener4Mouse;
		}
		const r2bix_input::Listener4Mouse* const GetListener4Mouse() const
		{
			return &mListener4Mouse;
		}
		
		

		//
		//
		//
		void SetMouseOverCallback( const MouseResponseCallbackT& callback )
		{
			mMouseOverCallback = callback;
		}
		void SetMouseMoveCallback( const MouseResponseCallbackT& callback )
		{
			mMouseMoveCallback = callback;
		}
		void SetMouseLeaveCallback( const MouseResponseCallbackT& callback )
		{
			mMouseLeaveCallback = callback;
		}



		//
		//
		//
		eState GetState() const
		{
			return mState;
		}



		//
		// UI Input Listener
		//
		void AddListener( r2bix_input::UIInputListener* const listener );
		void RemoveListener( r2bix_input::UIInputListener* const listener );



	private:
		r2::SizeInt mSize;

		r2bix_input::Listener4Mouse mListener4Mouse;
		MouseResponseCallbackT mMouseOverCallback;
		MouseResponseCallbackT mMouseMoveCallback;
		MouseResponseCallbackT mMouseLeaveCallback;

		eState mState;

		ListenerContainer mListenerContainer;
	};
}