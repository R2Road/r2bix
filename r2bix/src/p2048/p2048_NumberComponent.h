#pragma once

#include "r2bix/r2base_Component.h"
#include "r2bix/r2base_ComponentStaticID.h"

namespace r2component
{
	class CustomTextureComponent;
	class LabelSComponent;
}

namespace p2048
{
	class NumberComponent : public r2base::Component<NumberComponent>
	{
	public:
		NumberComponent( r2bix_node::Node& owner_node );

		void SetLabelComponent( r2component::LabelSComponent* const label_component )
		{
			mLabelComponent = label_component;
		}
		void SetCustomTextureComponent( r2component::CustomTextureComponent* const custom_texture_component )
		{
			mCustomTextureComponent = custom_texture_component;
		}
		void SetNumber( const int new_number, const bool merged, const bool newcomer );

	private:
		r2component::LabelSComponent* mLabelComponent;
		r2component::CustomTextureComponent* mCustomTextureComponent;
	};
}