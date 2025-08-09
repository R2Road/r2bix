#pragma once

#include <vector>

#include "r2_Direction4BitwiseLimited.h"
#include "r2_Point.h"
#include "r2_NoneCopyable.h"

namespace r2utility
{
	class Point2PointStraightLinePath : private r2::NoneCopyable
	{
	private:
		Point2PointStraightLinePath() = delete;



	public:
		template<typename T>
		static void BuildAsDirection4( const r2::Point<T>& start_point, const r2::Point<T>& end_point, std::vector<r2::Point<T>>* out_path )
		{
			using ElementT = T;
			using PointT = r2::Point<ElementT>;

			PointT current_point = start_point;
			PointT temp_point;

			PointT current_distance = end_point - current_point;
			PointT temp_distance;

			//
			//
			//
			r2::Direction4BitwiseLimited dir( ( end_point - current_point ).GetX(), ( end_point - current_point ).GetY() );

			//
			// collect road
			//
			while( end_point != current_point )
			{
				temp_point.Set( current_point.GetX() + dir.GetX(), current_point.GetY() + dir.GetY() );

				//
				// Distance Check
				//
				temp_distance = end_point - temp_point;
				if( current_distance.Length() <= temp_distance.Length() )
				{
					dir.Rotate();
					continue;
				}

				current_point = temp_point;
				current_distance = temp_distance;
				out_path->push_back( current_point );

				dir.Rotate();
			}
		}
	};
}

