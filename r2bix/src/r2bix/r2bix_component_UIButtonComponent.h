#pragma once

#include "r2_SizeInt.h"

#include "r2bix_component_Component.h"
#include "r2bix_input_UIInputListener.h"

namespace r2bix_component
{
	class UIPannelComponent;

	class UIButtonComponent : public r2bix_component::Component<UIButtonComponent>
	{
	public:
		UIButtonComponent( r2bix_node::Node& owner_node );


		//
		// Override
		//
	private:
		void EnterProcess() override;
		void ExitProcess() override;



		//
		//
		//
	public:
		int GetWidth() const
		{
			return mSize.GetWidth();
		}
		int GetHeight() const
		{
			return mSize.GetHeight();
		}

		void SetSize( const uint32_t width, const uint32_t height );



	private:
		r2::SizeInt mSize;

		UIPannelComponent* mUIPannelComponent;
		r2bix_input::UIInputListener mUIInputListener;
	};
}