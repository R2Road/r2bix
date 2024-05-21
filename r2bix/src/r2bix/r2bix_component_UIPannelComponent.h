#pragma once

#include "r2_SignalSlot.h"

#include "r2bix_component_Component.h"
#include "r2bix_input_Listener4Mouse.h"

namespace r2bix_component
{
	class UIControlComponent;

	class UIPannelComponent : public r2bix_component::Component<UIPannelComponent>
	{
	public:
		using Slot4VisibleFlagChanged = r2::Slot<void, bool>;

		using UIControlComponentContainer = std::list<r2bix_component::UIControlComponent*>;



		UIPannelComponent( r2bix_node::Node& owner_node );



		//
		//
		//
	private:
		bool initProcess() override;
		void activateProcess() override;
		void deactivateProcess() override;



		//
		//
		//
	public:
		r2bix_input::Listener4Mouse* const GetListener4Mouse()
		{
			return &mListener4Mouse;
		}
		const r2bix_input::Listener4Mouse* const GetListener4Mouse() const
		{
			return &mListener4Mouse;
		}



		//
		//
		//
		UIControlComponent* const GetMyUIControlComponent() const
		{
			return mMyUIControlComponent;
		}
		void SetMyUIControlComponent( UIControlComponent* const ui_control_component );



		//
		//
		//
		int GetWidth() const;
		int GetHeight() const;

		void SetSize( const uint32_t width, const uint32_t height );



		//
		// UI Input Listener
		//
		void AddUIControl( r2bix_component::UIControlComponent* const control );
		void RemoveUIControl( r2bix_component::UIControlComponent* const control );
	private:
		void OnCursorResponse( const r2bix_input::CursorPoint cursor_point );
		void OnKeyResponse( const int key_index, const r2bix_input::eKeyStatus key_status );



	private:
		r2bix_input::Listener4Mouse mListener4Mouse;
		UIControlComponent* mMyUIControlComponent;

		UIControlComponentContainer mUIControlComponentContainer;

		Slot4VisibleFlagChanged mSlot4VisibleFlagChanged;
	};
}