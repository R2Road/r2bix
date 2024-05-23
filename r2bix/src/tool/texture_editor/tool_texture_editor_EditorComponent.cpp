#include "tool_texture_editor_EditorComponent.h"

#include "r2bix_node_Node.h"

#include "r2bix_component_LabelSComponent.h"

namespace tool_texture_editor
{
	EditorComponent::EditorComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<EditorComponent>( owner_node )
	{}



	void EditorComponent::SetFileName( const std::string_view str )
	{
		mFileName = str;

		auto file_name_view_node = GetOwnerNode().GetChildByName( "file_name_view" );
		if( file_name_view_node )
		{
			file_name_view_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( str );
		}
	}
}