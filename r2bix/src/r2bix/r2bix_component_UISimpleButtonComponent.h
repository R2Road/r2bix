//
// UISimpleButtonComponent는 Mouse 입력에만 반응한다.
//

#pragma once

#include "r2_SignalSlot.h"

#include "r2bix_component_Component.h"
#include "r2bix_input_Constant.h"
#include "r2bix_ui_Constant.h"

namespace r2bix_component
{
	class CustomTextureComponent;
	class UIControlComponent;
	class TextureRenderComponent;

	class UISimpleButtonComponent : public r2bix_component::Component<UISimpleButtonComponent>
	{
	public:
		using Slot4CursorStatusChangedT = r2::Slot<void( r2bix_ui::eCursorStatus )>;
		using Slot4KeyStatusChangedT = r2::Slot<bool( int, r2bix_ui::eKeyStatus )>;

		using Callback4CursorStatusChangedT = typename Slot4CursorStatusChangedT::CallbackT;
		using Callback4KeyStatusChangedT = typename Slot4KeyStatusChangedT::CallbackT;



		UISimpleButtonComponent( r2bix::Director& director, r2bix_node::Node& owner_node );



		//
		// Override
		//
	private:
		void enterProcess() override;



		//
		//
		//
	public:
		void SetMyUIControlComponent( UIControlComponent* const ui_control_component )
		{
			mMyUIControlComponent = ui_control_component;
		}
		UIControlComponent* const GetMyUIControlComponent() const
		{
			return mMyUIControlComponent;
		}

		void SetMyCustomTextureComponent( CustomTextureComponent* const component )
		{
			mMyCustomTextureComponent = component;
		}
		CustomTextureComponent* const GetMyCustomTextureComponent() const
		{
			return mMyCustomTextureComponent;
		}

		void SetMyTextureRenderComponent( TextureRenderComponent* const component )
		{
			mMyTextureRenderComponent = component;
		}
		TextureRenderComponent* const GetMyTextureRenderComponent() const
		{
			return mMyTextureRenderComponent;
		}



		//
		//
		//
		void SetCallback4CursorResponse( const Callback4CursorStatusChangedT& callback );
		void SetCallback4KeyResponse( const Callback4KeyStatusChangedT& callback );



		//
		//
		//
		void Set( const int width, const int height, const char c );
		void Set( const int width, const int height );



	private:
		UIControlComponent* mMyUIControlComponent;
		CustomTextureComponent* mMyCustomTextureComponent;
		TextureRenderComponent* mMyTextureRenderComponent;

		Slot4CursorStatusChangedT mSlot4CursorStatusChanged_ViewProcess;
		Slot4KeyStatusChangedT mSlot4KeyStatusChanged_ViewProcess;

		Slot4CursorStatusChangedT mSlot4CursorStatusChanged;
		Slot4KeyStatusChangedT mSlot4KeyStatusChanged;
	};
}