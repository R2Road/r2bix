#pragma once

#include "r2bix_component_Component.h"

#include "r2_PointInt.h"
#include "r2_SignalSlot.h"
#include "r2_Vector2.h"

namespace r2bix_component
{
	class TransformComponent : public r2bix_component::Component<TransformComponent>
	{
	public:
		using Signal4PivotChanged = r2::Signal<void, float, float>;
		using Slot4PivotPointChanged = typename Signal4PivotChanged::SlotT;



		TransformComponent( r2bix_node::Node& owner_node );



		//
		// Getter
		//
		r2::PointInt GetPosition() const
		{
			return mPosition;
		}
		int32_t GetPositionX() const
		{
			return mPosition.GetX();
		}
		int32_t GetPositionY() const
		{
			return mPosition.GetY();
		}
		int32_t GetZ() const
		{
			return mZOrder;
		}

		r2::PointInt GetWorldPosition() const;
		r2::PointInt GetScreenPosition() const;



		//
		// Setter
		//
		void SetPosition( const int32_t new_x, const int32_t new_y )
		{
			mPosition.Set( new_x, new_y );
		}
		void SetPosition( const float new_x, const float new_y )
		{
			mPosition.Set( static_cast<int>( new_x ), static_cast<int>( new_y ) );
		}
		void SetPosition( const r2::PointInt new_position )
		{
			mPosition = new_position;
		}
		void SetPositionX( const r2::PointInt::ValueT new_x )
		{
			mPosition.SetX( new_x );
		}
		void SetPositionY( const r2::PointInt::ValueT new_y )
		{
			mPosition.SetY( new_y );
		}
		void SetZ( const int32_t new_z_order )
		{
			mZOrder = new_z_order;
		}

		void SetPivot( const float x, const float y )
		{
			mPivotPoint.x = x;
			mPivotPoint.y = y;

			mSignal4PivotChanged.Emit( x, y );
		}

		void ConnectSlot4PivotPointChanged( Slot4PivotPointChanged* slot )
		{
			mSignal4PivotChanged.Connect( slot );
		}



	private:
		r2::PointInt mPosition;
		int32_t mZOrder;

		r2::Vector2 mPivotPoint;
		Signal4PivotChanged mSignal4PivotChanged;
	};
}