//
//
//

#pragma once

#include "r2bix_component_Component.h"

namespace r2bix_component
{
	class UIControlComponent;

	class UITextFieldComponent : public r2bix_component::Component<UITextFieldComponent>
	{
	public:
		UITextFieldComponent( r2bix_node::Node& owner_node );



		void SetUIControlComponent( r2bix_component::UIControlComponent* const ui_control_component );

		int GetLength() const;
		void SetLength( const int length );



	private:
		r2bix_component::UIControlComponent* mUIControlComponent;
	};
}