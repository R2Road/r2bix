#pragma once

#include "r2bix/r2bix_component_Component.h"
#include "r2bix/r2bix_component_ComponentStaticID.h"

namespace r2bix_component
{
	class CustomTextureComponent;
	class LabelSComponent;
}

namespace p2048
{
	class NumberComponent : public r2bix_component::Component<NumberComponent>
	{
	public:
		NumberComponent( r2bix_node::Node& owner_node );

		void SetLabelComponent( r2bix_component::LabelSComponent* const label_component )
		{
			mLabelComponent = label_component;
		}
		void SetCustomTextureComponent( r2bix_component::CustomTextureComponent* const custom_texture_component )
		{
			mCustomTextureComponent = custom_texture_component;
		}
		void SetNumber( const int new_number, const bool merged, const bool newcomer );

	private:
		r2bix_component::LabelSComponent* mLabelComponent;
		r2bix_component::CustomTextureComponent* mCustomTextureComponent;
	};
}