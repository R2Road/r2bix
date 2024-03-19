#pragma once

#include "r2bix_component_Component.h"
#include "r2bix_input_Listener4Mouse.h"

namespace r2bix_component
{
	class CustomTextureComponent;
	class TextureRenderComponent;

	class UIPannelComponent : public r2bix_component::Component<UIPannelComponent>
	{
	public:
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
		CustomTextureComponent* const GetCustomTextureComponent() const
		{
			return mCustomTextureComponent;
		}
		TextureRenderComponent* const GetTextureRenderComponent() const
		{
			return mTextureRenderComponent;
		}

		int GetWidth() const;
		int GetHeight() const;

		

		//
		// Setter
		//
		void SetCustomTextureComponent( CustomTextureComponent* const custom_texture_component )
		{
			mCustomTextureComponent = custom_texture_component;
		}
		void SetTextureRenderComponent(	TextureRenderComponent* const texture_render_component )
		{
			mTextureRenderComponent = texture_render_component;
		}

		void SetSize( const uint32_t width, const uint32_t height, const char fill_char );
		void SetSize( const uint32_t width, const uint32_t height );



	private:
		CustomTextureComponent* mCustomTextureComponent;
		TextureRenderComponent* mTextureRenderComponent;

		r2bix_input::Listener4Mouse mListener4Mouse;
	};
}