//
// UIButtonComponent는 Mouse 입력에만 반응한다.
//

#pragma once

#include "r2bix_component_Component.h"
#include "r2bix_ui_UIInputListener.h"

namespace r2bix_component
{
	class UIPannelComponent;

	class UIButtonComponent : public r2bix_component::Component<UIButtonComponent>
	{
	public:
		using Callback4CursorStatusChangedT = std::function<bool( r2bix_ui::eCursorStatus )>;
		using Callback4KeyStatusChangedT = std::function<bool( r2bix_input::eKeyStatus )>;



		UIButtonComponent( r2bix_node::Node& owner_node );


		//
		// Override
		//
	private:
		bool InitProcess() override;
		void EnterProcess() override;
		void ExitProcess() override;



		//
		//
		//
	public:
		int GetWidth() const
		{
			return mUIInputListener.GetWidth();
		}
		int GetHeight() const
		{
			return mUIInputListener.GetHeight();
		}

		void SetSize( const uint32_t width, const uint32_t height )
		{
			mUIInputListener.SetSize( width, height );
		}



		//
		//
		//
		void SetCallback4CursorResponse( const Callback4CursorStatusChangedT& callback );
		void SetCallback4KeyResponse( const Callback4KeyStatusChangedT& callback );

		void AddObservationKey( const r2bix_input::eKeyCode key_code );



	private:
		UIPannelComponent* mUIPannelComponent;
		r2bix_ui::UIInputListener mUIInputListener;

		r2bix_ui::eCursorStatus mCursorState;

		Callback4CursorStatusChangedT mCallback4CursorStatusChanged;
		Callback4KeyStatusChangedT mCallback4KeyStatusChanged;
	};
}