#pragma once

#include "r2bix_component_Component.h"
#include "r2bix_input_Listener4Mouse.h"

namespace r2bix_ui
{
	class UIInputListener;
}

namespace r2bix_component
{
	class UIControlComponent;

	class UIPannelComponent : public r2bix_component::Component<UIPannelComponent>
	{
	public:
		using UIInputListenerContainer = std::list<r2bix_ui::UIInputListener*>;



		UIPannelComponent( r2bix_node::Node& owner_node );



		//
		//
		//
	private:
		bool InitProcess() override;
		void ActivateProcess() override;
		void DeactivateProcess() override;



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
		void SetUIControlComponent( UIControlComponent* const ui_control_component )
		{
			mUIControlComponent = ui_control_component;
		}
		UIControlComponent* const GetUIControlComponent() const
		{
			return mUIControlComponent;
		}




		//
		// UI Input Listener
		//
		void AddListener( r2bix_ui::UIInputListener* const listener );
		void RemoveListener( r2bix_ui::UIInputListener* const listener );
		void OnCursorResponse( const r2bix_input::CursorPoint cursor_point );



	private:
		r2bix_input::Listener4Mouse mListener4Mouse;
		UIInputListenerContainer mUIInputListenerContainer;

		UIControlComponent* mUIControlComponent;
	};
}