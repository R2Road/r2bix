#include "p2048mini_NumberComponent.h"

#include "r2bix/r2component_CustomTextureComponent.h"
#include "r2bix/r2component_LabelComponent.h"

namespace p2048mini
{
	NumberComponent::NumberComponent( r2base::Node& owner_node ) : r2base::Component( owner_node )
		, mLabelComponent( nullptr )
		, mCustomTextureComponent( nullptr )
	{}

	std::unique_ptr<NumberComponent> NumberComponent::Create( r2base::Node& owner_node )
	{
		std::unique_ptr<NumberComponent> ret( new ( std::nothrow ) NumberComponent( owner_node ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	void NumberComponent::SetNumber( const int new_number, const bool merged )
	{
		mCustomTextureComponent->GetTexture()->FillColorAll(
			merged
			? r2base::BG_Aqua
			: r2base::BG_Black
		);

		mLabelComponent->SetString( std::to_string( new_number ) );
		mLabelComponent->GetCustomTextureComponent()->GetTexture()->FillColorAll(
			merged
			? r2base::BG_Aqua | r2base::FG_Black
			: r2base::BG_Black | r2base::FG_Aqua
		);
	}
}