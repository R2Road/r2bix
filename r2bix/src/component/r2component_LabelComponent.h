#pragma once

#include <string>
#include <string_view>

#include "base/r2base_Component.h"

namespace r2component
{
	class TextureRenderComponent;

	class LabelComponent : public r2base::Component
	{
	private:
		LabelComponent( r2base::Node& owner_node );

	public:
		static std::unique_ptr<LabelComponent> Create( r2base::Node& owner_node );

		//
		// Setter
		//
		void SetString( const std::string_view str );

	private:
		std::string mText;
	public:
		TextureRenderComponent* mTextureRenderComponent;
	};
}