#pragma once

#include <functional>

#include "r2_SizeInt.h"

#include "r2bix_component_Component.h"
#include "r2bix_input_Constant.h"
#include "r2bix_ui_Constant.h"

namespace r2bix_component
{
	class UIPannelComponent;

	class UIControlComponent : public r2bix_component::Component<UIControlComponent>
	{
	public:
		using Callback4CursorResponseT = std::function<void( r2bix_ui::eCursorStatus )>;
		using Callback4KeyResponseT = std::function<bool( int, r2bix_ui::eKeyStatus )>;



		UIControlComponent( r2bix_node::Node& owner_node );



		//
		//
		//
	private:
		void EnterProcess() override;
		void ExitProcess() override;



		//
		//
		//
	public:
		int GetOrder() const
		{
			return mOrder;
		}
		void SetOrder( const int order )
		{
			mOrder = order;
		}



		int GetWidth() const
		{
			return mSize.GetWidth();
		}
		int GetHeight() const
		{
			return mSize.GetHeight();
		}

		void SetSize( const uint32_t width, const uint32_t height )
		{
			mSize.Set( width, height );
		}
		
		

		//
		//
		//
		r2bix_ui::eCursorStatus GetState() const
		{
			return mCursorState;
		}



		//
		// Callback
		//
		void SetCallback4CursorResponse( const Callback4CursorResponseT& callback )
		{
			mCallback4CursorResponse = callback;
		}
		const Callback4CursorResponseT& GetCallback4CursorResponse() const
		{
			return mCallback4CursorResponse;
		}

		void SetCallback4KeyResponse( const Callback4KeyResponseT& callback )
		{
			mCallback4KeyResponse = callback;
		}
		const Callback4KeyResponseT& GetCallback4KeyResponse() const
		{
			return mCallback4KeyResponse;
		}



		//
		//
		//
		bool OnCursorResponse( const r2bix_input::CursorPoint cursor_point );
		bool OnKeyResponse( const int key_index, const r2bix_input::eKeyStatus key_status );



	private:
		int mOrder;

		r2::SizeInt mSize;

		r2bix_ui::eCursorStatus mCursorState;
		r2bix_ui::eKeyStatus mKeyStatus;

		Callback4CursorResponseT mCallback4CursorResponse;
		Callback4KeyResponseT mCallback4KeyResponse;

		UIPannelComponent* mUIPannelComponent;
	};
}