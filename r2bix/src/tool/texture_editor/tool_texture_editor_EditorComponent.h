#pragma once

#include <string>

#include "r2_SignalSlot.h"

#include "r2bix_component_Component.h"

#include "r2bix_ui_Constant.h"

namespace tool_texture_editor
{
	class EditorComponent : public r2bix_component::Component<EditorComponent>
	{
	public:
		using Slot4CursorResponseT = r2::Slot<void, r2bix_ui::eCursorStatus>;
		using Slot4KeyResponseT = r2::Slot<bool, int, r2bix_ui::eKeyStatus>;



		EditorComponent( r2bix::Director& director, r2bix_node::Node& owner_node );



		//
		//
		//
		void SetFileName( const std::string_view str );



		//
		//
		//
		void SetCanvas( r2bix_node::Node* canvas_node );
	private:
		void fillTextureOnCurrentCursor();



	private:
		std::string mFileName;
		Slot4CursorResponseT mSlot4CursorResponse;
		Slot4KeyResponseT mSlot4KeyResponse;

		r2bix_node::Node* mCanvasNode;
		bool mbFill;
	};
}