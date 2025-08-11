#include "test_camera_3d.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_WindowsUtility.h"

#include "r2bix_Camera3D.h"

#include "r2_FPSTimer.h"
#include "r2_math.hpp"
#include "r2_matrix44_render_transform.hpp"
#include "r2_matrix44_transform_vector3.hpp"
#include "r2helper_std_printer_quaternion.hpp"
#include "r2helper_std_printer_radian.hpp"
#include "r2helper_std_printer_vector3.hpp"

namespace test_camera_3d
{
	r2tm::TitleFunctionT Declaration::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera3D : Declaration";
		};
	}
	r2tm::DoFunctionT Declaration::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			{
				OUTPUT_SUBJECT( "기본 생성자" );

				SS();

				DECLARATION_MAIN( r2bix::Camera3D cam );

				SS();

				{
					OUTPUT_SIZE( cam );

					LF();

					OUTPUT_BINARY( cam );
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Constant::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera3D : Constant";
		};
	}
	r2tm::DoFunctionT Constant::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			{
				{
					EXPECT_EQ( r2::Vector3( 0, 0, -1 ), r2bix::WORLD_FRONT );

					LF();

					OUTPUT_VALUE( r2bix::WORLD_FRONT );
				}

				SS();

				{
					EXPECT_EQ( r2::Vector3( 0, 1, 0 ), r2bix::WORLD_UP );

					LF();

					OUTPUT_VALUE( r2bix::WORLD_UP );
				}

				SS();

				{
					EXPECT_EQ( r2::Vector3( 1, 0, 0 ), r2bix::WORLD_RIGHT );

					LF();

					OUTPUT_VALUE( r2bix::WORLD_RIGHT );
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
			{
				return "Camera3D : Basic";
			};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( using V = r2bix::Camera3D::Vec3 );
			DECLARATION_MAIN( r2bix::Camera3D cam );

			LS();

			{
				OUTPUT_SUBJECT( "Position" );

				LF();

				EXPECT_EQ( V( 0, 0, 0 ), cam.GetPosition() );

				SS();

				DECLARATION_MAIN( const V v( 10, 20, 30 ) );
				PROCESS_MAIN( cam.SetPosition( v ) );

				LF();

				EXPECT_EQ( v, cam.GetPosition() );
			}

			LS();

			{
				OUTPUT_SUBJECT( "Front" );

				LF();

				EXPECT_EQ( r2bix::WORLD_FRONT, cam.GetFront() );
			}

			LS();

			{
				OUTPUT_SUBJECT( "Up" );

				LF();

				EXPECT_EQ( r2bix::WORLD_UP, cam.GetUp() );
			}

			LS();

			{
				OUTPUT_SUBJECT( "Right" );

				LF();

				EXPECT_EQ( r2bix::WORLD_RIGHT, cam.GetRight() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Move::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera3D : Move";
		};
	}
	r2tm::DoFunctionT Move::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( using V = r2bix::Camera3D::Vec3 );
			DECLARATION_MAIN( r2bix::Camera3D cam );

			LF();

			DECLARATION_MAIN( const V v( 10, 20, 30 ) );

			LS();

			{
				OUTPUT_SUBJECT( "Move" );

				LF();

				EXPECT_EQ( V( 0, 0, 0 ), cam.GetPosition() );

				SS();

				{
					PROCESS_MAIN( cam.Move( v ) );

					LF();

					EXPECT_EQ( v, cam.GetPosition() );
				}

				SS();
				
				{
					PROCESS_MAIN( cam.Move( v ) );

					LF();

					EXPECT_EQ( v + v, cam.GetPosition() );
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Rotation::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera3D : Rotation";
		};
	}
	r2tm::DoFunctionT Rotation::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix::Camera3D cam );
			DECLARATION_MAIN( const r2::Radian radian( r2::deg2rad( r2::Degree( 30.f ) ) ) );

			LS();

			{
				OUTPUT_SUBJECT( "X" );

				LF();

				EXPECT_EQ( r2::Radian(), cam.GetRotationX() );

				SS();

				{
					PROCESS_MAIN( cam.RotationX( radian ) );

					LF();

					EXPECT_EQ( radian, cam.GetRotationX() );
				}
			}

			LS();

			{
				OUTPUT_SUBJECT( "Y" );

				LF();

				EXPECT_EQ( r2::Radian(), cam.GetRotationY() );

				SS();

				{
					PROCESS_MAIN( cam.RotationY( radian ) );

					LF();

					EXPECT_EQ( radian, cam.GetRotationY() );
				}
			}

			LS();

			{
				OUTPUT_SUBJECT( "Z" );

				LF();

				EXPECT_EQ( r2::Radian(), cam.GetRotationZ() );

				SS();

				{
					PROCESS_MAIN( cam.RotationZ( radian ) );

					LF();

					EXPECT_EQ( radian, cam.GetRotationZ() );
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Vectors::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera3D : Vectors";
		};
	}
	r2tm::DoFunctionT Vectors::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix::Camera3D cam );
			DECLARATION_MAIN( const r2::Radian radian( r2::deg2rad( r2::Degree( 90.f ) ) ) );

			LS();

			EXPECT_EQ( r2bix::WORLD_FRONT, cam.GetFront() );
			EXPECT_EQ( r2bix::WORLD_RIGHT, cam.GetRight() );
			EXPECT_EQ( r2bix::WORLD_UP, cam.GetUp() );

			LS();

			{
				OUTPUT_SUBJECT( "Y" );

				LF();

				{
					PROCESS_MAIN( cam.RotationY( radian ) );
					PROCESS_MAIN( cam.UpdateVectors() );

					LF();

					EXPECT_EQ( -r2::VEC3_X, cam.GetFront() );
					EXPECT_EQ( -r2::VEC3_Z, cam.GetRight() );
					EXPECT_EQ( r2bix::WORLD_UP, cam.GetUp() );
				}
			}

			LS();

			{
				OUTPUT_SUBJECT( "Y + X" );

				LF();

				{
					PROCESS_MAIN( cam.RotationX( radian ) );
					PROCESS_MAIN( cam.UpdateVectors() );

					LF();

					EXPECT_EQ( r2::VEC3_Y, cam.GetFront() );
					EXPECT_EQ( -r2::VEC3_Z, cam.GetRight() );
					EXPECT_EQ( r2::VEC3_X, cam.GetUp() );
				}
			}

			LS();

			{
				OUTPUT_SUBJECT( "Y + X + Z" );

				LF();

				{
					PROCESS_MAIN( cam.RotationZ( radian ) );
					PROCESS_MAIN( cam.UpdateVectors() );

					LF();

					EXPECT_EQ( r2::VEC3_Y, cam.GetFront() );
					EXPECT_EQ( -r2::VEC3_X, cam.GetRight() );
					EXPECT_EQ( -r2::VEC3_Z, cam.GetUp() );
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT ViewTransform::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera3D : ViewTransform";
		};
	}
	r2tm::DoFunctionT ViewTransform::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix::Camera3D cam );

			LS();

			{
				OUTPUT_SUBJECT( "설정" );

				LF();

				PROCESS_MAIN( cam.SetPosition( r2bix::Camera3D::Vec3( 0, 0, 10 ) ) );
				PROCESS_MAIN( cam.SetRotationY( r2::deg2rad( r2::Degree( -45.f ) ) ) );
				PROCESS_MAIN( cam.UpdateVectors() );
			}

			LS();

			{
				OUTPUT_SUBJECT( "적용" );

				LF();

				DECLARATION_MAIN( r2bix::Camera3D::Vec3 vs( 1, 0, 9 ) );
				DECLARATION_MAIN( r2bix::Camera3D::Mat44 view_mat = cam.GetViewMatrix() );

				LF();

				PROCESS_MAIN( vs = view_mat * vs );

				LF();

				EXPECT_EP_EQ( 0, vs.x );
				EXPECT_EP_EQ( 0, vs.y );
				EXPECT_EP_EQ( -r2::length( r2::Vector3( 1, 0, 1 ) ), vs.z );

				LF();

				OUTPUT_VALUE( vs );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT LookAt::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera3D : LookAt";
		};
	}
	r2tm::DoFunctionT LookAt::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			OUTPUT_SUBJECT( "카메라가 특정 위치를 바라보게 한다." );

			LS();

			DECLARATION_MAIN( r2bix::Camera3D cam );

			LF();

			DECLARATION_MAIN( constexpr r2bix::Camera3D::Vec3 v_position( 0, 0, 0 ) );
			DECLARATION_MAIN( constexpr r2bix::Camera3D::Vec3 v_target( 10, 10, -10 ) );

			LS();

			{
				OUTPUT_SUBJECT( "LookAt" );

				LF();

				PROCESS_MAIN( cam.SetPosition( r2bix::Camera3D::Vec3( 0, 0, 0 ) ) );
				PROCESS_MAIN( cam.LookAt( v_target ) );

				LF();

				EXPECT_EQ( v_position, cam.GetPosition() );
				EXPECT_EQ( r2::normalize( v_target ), cam.GetFront() );
			}

			LS();

			{
				OUTPUT_SUBJECT( "ViewMatrix 검사" );

				LF();

				DECLARATION_MAIN( const r2::Vector3 v3 = cam.GetViewMatrix() * v_target );

				LF();

				EXPECT_EQ( r2::Vector3( 0, 0, -r2::length( v_target ) ), v3);

				LF();

				OUTPUT_VALUE( cam.GetFront() );
				OUTPUT_VALUE( cam.GetRight() );
				OUTPUT_VALUE( cam.GetUp() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Demo::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera3D : Demo";
		};
	}
	r2tm::DoFunctionT Demo::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			const r2bix::Camera3D::Vec3 position( 0, 4, -10 );

			DECLARATION_MAIN( r2bix::Camera3D cam );
			PROCESS_MAIN( cam.SetPosition( position ) );
			PROCESS_MAIN( cam.LookAt( r2bix::Camera3D::Vec3() ) );

			LF();

			const int v_size = 3;
			const r2::Vector4 vs[v_size] = {
				  r2::Vector4{  0, -4, 0, 1 }
				, r2::Vector4{  6,  3, 0, 1 }
				, r2::Vector4{ -6,  3, 0, 1 }
			};
			r2::Vector4 fixed_vs[v_size];


			const int viewport_w = 50;
			const int viewport_h = 30;

			const float left = -viewport_w / 2;
			const float right = viewport_w / 2;
			const float bottom = -viewport_h / 2;
			const float top = viewport_h / 2;
			const float near = 0.1f;
			const float far = 100.f;

			const auto projection_mat44 = r2::build_mat44_render_transform_projection_orthographic_z01(
				left
				, right
				, bottom
				, top
				, near
				, far
			);
			const auto viewport_mat44 = r2::build_mat44_render_transform_viewport_zm1p1(
				viewport_w
				, viewport_h
				, near
				, far
			);

			LS();

			OUTPUT_SUBJECT( "삼각형을 가운데 두고 카메라를 회전" );

			LS();

			{
				const auto pivot = r2tm::WindowsUtility::GetCursorPoint();

				r2::FPSTimer timer( 30 );
				float accumulate_time = 0.f;
				do
				{
					if( timer.Update() )
					{
						accumulate_time += ( timer.GetElapsedTime() * 0.5f );
						accumulate_time -= ( int )accumulate_time;

						r2tm::WindowsUtility::MoveCursorPointWithClearBuffer( pivot );

						const auto cam_rotation_y_mat44 = r2::build_mat44_rotation_y_vec4( r2::Degree( 360 * accumulate_time ) );
						const auto new_p = cam_rotation_y_mat44 * position;

						cam.SetPosition( new_p );
						cam.LookAt( r2bix::Camera3D::Vec3() );

						const auto view_mat44 = cam.GetViewMatrix();

						// Draw : vs
						{
							for( int i = 0; v_size > i; ++i )
							{
								// setup
								auto& v = fixed_vs[i] = vs[i];

								v = view_mat44 * v;

								v = projection_mat44 * v;
								v /= v.w;

								v = viewport_mat44 * v;
							}

							r2::Vector4 v_start;
							r2::Vector4 v_end;
							r2::Vector4 v_dir;
							for( int i = 0; v_size > i; ++i )
							{
								v_start = fixed_vs[i];
								v_end = ( i + 1 == v_size ? fixed_vs[0] : fixed_vs[i + 1] );

								v_dir = v_end - v_start;

								int divider = int( std::abs( v_dir.x ) > std::abs( v_dir.y ) ? std::abs( v_dir.x ) : std::abs( v_dir.y ) );
								v_dir.x /= divider;
								v_dir.y /= divider;

								for( int j = 0; divider > j; ++j )
								{
									auto v = v_start + ( v_dir * static_cast<float>( j ) );

									r2tm::WindowsUtility::FillCharacter( pivot + r2tm::WindowsUtility::CursorPoint( ( short )v.x, ( short )v.y ), 'c' );
								}
							}
						}

						// Draw : Bottom
						{
							auto v = view_mat44 * r2::Vector4( 7, 0, 0, 1 );

							v = projection_mat44 * v;
							v /= v.w;

							v = viewport_mat44 * v;

							r2tm::WindowsUtility::FillCharacter( pivot + r2tm::WindowsUtility::CursorPoint( ( short )v.x, ( short )v.y ), 'b' );
						}

						// Draw : 0, 0
						{
							auto v = view_mat44 * r2::Vector4( 0, 0, 0, 1 );

							v = projection_mat44 * v;
							v /= v.w;

							v = viewport_mat44 * v;

							r2tm::WindowsUtility::FillString( pivot + r2tm::WindowsUtility::CursorPoint( ( short )v.x, ( short )v.y ), "0,0 ", 3, r2tm::WindowsUtility::eColor::FG_Green);
						}

						r2tm::WindowsUtility::MoveCursorPoint( r2tm::WindowsUtility::CursorPoint( 0, pivot.y + ( short )viewport_h ) );

						LS();
					}

				} while( !KB_HIT );

				//
				// _getch() 를 부리지 않아. r2tm::eDoLeaveAction::None 사용시 메뉴에서 키가 작동한다.
				//
				WAIT_ANY_KEY;
			}

			LS();

			return r2tm::eDoLeaveAction::None;
		};
	}
}