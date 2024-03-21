#pragma once

#include "r2bix_component_Component.h"

namespace r2bix_component
{
	class CustomTextureComponent;
	class TextureRenderComponent;
	class UIPannelComponent;

	class UIButtonComponent : public r2bix_component::Component<UIButtonComponent>
	{
	public:
		UIButtonComponent( r2bix_node::Node& owner_node );


		//
		// Override
		//
	private:
		void EnterProcess() override;
		void ExitProcess() override;



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

		UIPannelComponent* const GetUIPannelComponent() const
		{
			return mUIPannelComponent;
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

		void SetSize( const uint32_t width, const uint32_t height, const char fill );



	private:
		CustomTextureComponent* mCustomTextureComponent;
		TextureRenderComponent* mTextureRenderComponent;

		UIPannelComponent* mUIPannelComponent;
	};
}