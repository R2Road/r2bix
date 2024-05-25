#include "p2048_NumberComponent.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_LabelSComponent.h"

namespace p2048
{
	NumberComponent::NumberComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<NumberComponent>( director, owner_node )
		, mLabelComponent( nullptr )
		, mCustomTextureComponent( nullptr )
	{}

	void NumberComponent::SetNumber( const int new_number, const bool merged, const bool newcomer )
	{
		mLabelComponent->SetString( std::to_string( new_number ) );

		if( merged )
		{
			mCustomTextureComponent->GetTexture()->FillColorAll( r2bix::BG_Aqua);
			mLabelComponent->GetCustomTextureComponent()->GetTexture()->FillColorAll( r2bix::BG_Aqua | r2bix::FG_Black );
		}
		else
		{
			mCustomTextureComponent->GetTexture()->FillColorAll( r2bix::BG_Black );
			mLabelComponent->GetCustomTextureComponent()->GetTexture()->FillColorAll(
				newcomer
				? r2bix::BG_Black | r2bix::FG_LightYellow
				: r2bix::BG_Black | r2bix::FG_Aqua
			);
		}
	}
}