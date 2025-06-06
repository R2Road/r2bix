#pragma once

#include <functional>

#include "r2_RectInt.h"
#include "r2_SignalSlot.h"
#include "r2_Vector2.h"

#include "r2bix_component_Component.h"
#include "r2bix_input_Constant.h"
#include "r2bix_ui_Constant.h"

namespace r2bix_component
{
	class UIPannelComponent;

	class UIControlComponent : public r2bix_component::Component<UIControlComponent>
	{
	public:
		using Slot4PivotChanged = r2::Slot<void( float, float )>;

		using Signal4CursorResponseT = r2::Signal<void( r2bix_ui::eCursorStatus )>;
		using Signal4KeyResponseT = r2::Signal<bool( int, r2bix_ui::eKeyStatus )>;

		using Slot4CursorResponseT = typename Signal4CursorResponseT::SlotT;
		using Slot4KeyResponseT = typename Signal4KeyResponseT::SlotT;

		using SlotCount4CursorResponseT = typename Signal4CursorResponseT::SizeT;
		using SlotCount4KeyResponseT = typename Signal4KeyResponseT::SizeT;



		UIControlComponent( r2bix::Director& director, r2bix_node::Node& owner_node );



		//
		// Override
		//
	private:
		bool initProcess() override;
		void enterProcess() override;
		void exitProcess() override;



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
			return mResponseRect.GetWidth();
		}
		int GetHeight() const
		{
			return mResponseRect.GetHeight();
		}
		r2::Vector2 GetPivotPoint() const
		{
			return mPivotVector;
		}

		void SetSize( const uint32_t width, const uint32_t height );
	private:
		void resetResponseRect();
		
		

	public:
		//
		//
		//
		r2bix_ui::eCursorStatus GetState() const
		{
			return mCursorState;
		}



		//
		// Signal/Slot
		//
		void ConnectSlot4CursorResponse( Slot4CursorResponseT* slot )
		{
			mSignal4CursorResponse.Connect( slot );
		}
		void ConnectSlot4KeyResponse( Slot4KeyResponseT* slot )
		{
			mSignal4KeyResponse.Connect( slot );
		}

		SlotCount4CursorResponseT GetSlotCount4CursorResponse() const
		{
			return mSignal4CursorResponse.Count();
		}
		SlotCount4KeyResponseT GetSlotCount4KeyResponse() const
		{
			return mSignal4KeyResponse.Count();
		}





		//
		//
		//
		bool OnCursorResponse( const r2bix_input::CursorPoint cursor_point );
		bool OnKeyResponse( const int key_index, const r2bix_input::eKeyStatus key_status );



	private:
		int mOrder;

		r2::Vector2 mPivotVector;
		Slot4PivotChanged mSlot4PivotChanged;
		r2::RectInt mResponseRect;

		r2bix_ui::eCursorStatus mCursorState;
		r2bix_ui::eKeyStatus mKeyStatus;

		Signal4CursorResponseT mSignal4CursorResponse;
		Signal4KeyResponseT mSignal4KeyResponse;

		UIPannelComponent* mUIPannelComponent;
	};
}