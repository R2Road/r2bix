//
// UIButtonComponent는 Mouse 입력에만 반응한다.
//

#pragma once

#include <functional>

#include "r2bix_component_Component.h"
#include "r2bix_input_Constant.h"
#include "r2bix_ui_Constant.h"

namespace r2bix_component
{
	class UIControlComponent;

	class UIButtonComponent : public r2bix_component::Component<UIButtonComponent>
	{
	public:
		using Callback4CursorStatusChangedT = std::function<bool( r2bix_ui::eCursorStatus )>;
		using Callback4KeyStatusChangedT = std::function<bool( int, r2bix_ui::eKeyStatus )>;



		UIButtonComponent( r2bix_node::Node& owner_node );



		//
		// Override
		//
	private:
		void EnterProcess() override;



		//
		//
		//
	public:
		int GetWidth() const;
		int GetHeight() const;

		void SetSize( const uint32_t width, const uint32_t height );



		//
		//
		//
		void SetMyUIControlComponent( UIControlComponent* const ui_control_component )
		{
			mMyUIControlComponent = ui_control_component;
		}
		UIControlComponent* const GetMyUIControlComponent() const
		{
			return mMyUIControlComponent;
		}



		//
		//
		//
		void SetCallback4CursorResponse( const Callback4CursorStatusChangedT& callback );
		void SetCallback4KeyResponse( const Callback4KeyStatusChangedT& callback );



	private:
		UIControlComponent* mMyUIControlComponent;

		Callback4CursorStatusChangedT mCallback4CursorStatusChanged;
		Callback4KeyStatusChangedT mCallback4KeyStatusChanged;
	};
}