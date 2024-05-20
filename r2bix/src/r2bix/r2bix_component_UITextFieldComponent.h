//
//
//

#pragma once

#include "r2_SignalSlot.h"

#include "r2bix_component_Component.h"
#include "r2bix_ui_Constant.h"

namespace r2bix_component
{
	class CustomTextureComponent;
	class TextureRenderComponent;
	class UIControlComponent;

	class UITextFieldComponent : public r2bix_component::Component<UITextFieldComponent>
	{
	public:
		UITextFieldComponent( r2bix_node::Node& owner_node );



		//
		//
		//
		void SetUIControlComponent( r2bix_component::UIControlComponent* const ui_control_component );
		void SetCustomTextureComponent( r2bix_component::CustomTextureComponent* const custom_texture_component );
		void SetTextureRenderComponent( r2bix_component::TextureRenderComponent* const texture_render_component );



		//
		//
		//
		void SetPivotPoint( const float x, const float y );

		int GetLength() const;
		void SetLength( const int length );

		void SetText( const char* str );

		void Set( const int length, const char* str );



	private:
		r2bix_component::UIControlComponent* mUIControlComponent;
		r2bix_component::CustomTextureComponent* mCustomTextureComponent;
		r2bix_component::TextureRenderComponent* mTextureRenderComponent;

		r2::Slot<bool, int, r2bix_ui::eKeyStatus> mSlot4KeyResponse;
	};
}