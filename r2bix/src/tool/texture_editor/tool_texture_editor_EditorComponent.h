#pragma once

#include <string>

#include "r2bix_component_Component.h"

namespace tool_texture_editor
{
	class EditorComponent : public r2bix_component::Component<EditorComponent>
	{
	public:
		EditorComponent( r2bix_node::Node& owner_node );



		//
		//
		//
		void SetFileName( const std::string_view str )
		{
			mFileName = str;
		}

	private:
		std::string mFileName;
	};
}