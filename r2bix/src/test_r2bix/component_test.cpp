#include "pch.h"
#include "component_test.h"

#include <Windows.h>

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "base/r2base_Director.h"
#include "base/r2base_Node.h"
#include "component/r2component_LabelComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "component/r2component_TransformComponent.h"
#include "render/r2render_Camera.h"
#include "render/r2render_Texture.h"

namespace component_test
{
	r2cm::iItem::TitleFuncT ComponentID::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Component ID";
		};
	}
	r2cm::iItem::DoFuncT ComponentID::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			r2base::Director dummy_director;
			auto node = r2base::Node::Create( dummy_director );
			auto transform_1 = r2component::TransformComponent::Create( *node );
			auto transform_2 = r2component::TransformComponent::Create( *node );
			auto texture_render_1 = r2component::TextureRenderComponent::Create( *node );

			std::cout << r2::split;

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "auto transform_1 = r2component::TransformComponent::Create( *node );" << r2::linefeed;
				std::cout << r2::tab << "auto transform_2 = r2component::TransformComponent::Create( *node );" << r2::linefeed;
				std::cout << r2::tab << "auto texture_render_1 = r2component::TextureRenderComponent::Create( *node );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << "transform_1->GetStaticID();" << " > " << transform_1->GetStaticID() << r2::linefeed;
				EXPECT_EQ( transform_1->GetStaticID(), r2base::ComponentStaticID<r2component::TransformComponent>::Get() );
				EXPECT_EQ( transform_1->GetStaticID(), transform_2->GetStaticID() );

				std::cout << r2::linefeed2;

				std::cout << "texture_render_1->GetStaticID();" << " > " << texture_render_1->GetStaticID() << r2::linefeed;
				EXPECT_EQ( texture_render_1->GetStaticID(), r2base::ComponentStaticID<r2component::TextureRenderComponent>::Get() );
				EXPECT_NE( texture_render_1->GetStaticID(), transform_1->GetStaticID() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT GetComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "GetComponent";
		};
	}
	r2cm::iItem::DoFuncT GetComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			r2base::Director dummy_director;
			auto node = r2base::Node::Create( dummy_director );

			std::cout << r2::split;

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "r2base::Director dummy_director;" << r2::linefeed;
				std::cout << r2::tab << "auto node = r2base::Node::Create( dummy_director );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				EXPECT_NE( nullptr, node->GetComponent<r2component::TransformComponent>() );
				EXPECT_EQ( node->mTransformComponent, node->GetComponent<r2component::TransformComponent>() );

				EXPECT_EQ( nullptr, node->GetComponent<r2component::TextureRenderComponent>() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT AddComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "AddComponent";
		};
	}
	r2cm::iItem::DoFuncT AddComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			r2base::Director dummy_director;
			auto node = r2base::Node::Create( dummy_director );

			std::cout << r2::split;

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "r2base::Director dummy_director;" << r2::linefeed;
				std::cout << r2::tab << "auto node = r2base::Node::Create( dummy_director );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				EXPECT_EQ( nullptr, node->GetComponent<r2component::TextureRenderComponent>() );

				EXPECT_TRUE( node->AddComponent<r2component::TextureRenderComponent>() );
				EXPECT_FALSE( node->AddComponent<r2component::TextureRenderComponent>() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TextureRenderComponentTest_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Render Component 1";
		};
	}
	r2cm::iItem::DoFuncT TextureRenderComponentTest_1::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			r2render::Camera camera( { 20, 25 }, { 20, 10 } );
			r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' );

			r2base::Director dummy_director;
			auto node = r2base::Node::Create( dummy_director );
			{
				auto component = node->AddComponent<r2component::TextureRenderComponent>();
				component->SetRect( -1, -1, 4, 4 );
			}

			std::cout << r2::split;

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "r2render::Camera camera( { 20, 25 }, { 20, 10 } );" << r2::linefeed;
				std::cout << r2::tab << "r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' );" << r2::linefeed2;

				std::cout << r2::tab << "r2base::Director dummy_director;" << r2::linefeed2;

				std::cout << r2::tab << "auto node = r2base::Node::Create( dummy_director );" << r2::linefeed2;

				std::cout << r2::tab << "auto component = r2component::TextureRenderComponent::Create( *node );" << r2::linefeed;
				std::cout << r2::tab << "component->SetRect( -1, -1, 4, 4 );" << r2::linefeed;
				std::cout << r2::tab << "node->AddComponent( std::move( component ) );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				EXPECT_EQ( nullptr, node->GetComponent<r2component::TextureRenderComponent>()->GetTexture() );
			}

			std::cout << r2::split;

			{
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << "+ Process" << r2::linefeed2;
				std::cout << r2::tab << "node->Render( &camera, &render_target, r2::PointInt::GetZERO() );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 32 } );

				std::cout << "+ Show Render Target" << r2::linefeed2;

				int current_x = 0;
				for( const auto& p : render_target )
				{
					std::cout << p;

					++current_x;

					if( render_target.GetWidth() <= current_x )
					{
						current_x = 0;
						std::cout << r2::linefeed;
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 45 } );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TextureRenderComponentTest_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Render Component 2";
		};
	}
	r2cm::iItem::DoFuncT TextureRenderComponentTest_2::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			r2render::Camera camera( { 20, 25 }, { 20, 10 } );
			r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' );

			r2base::Director dummy_director;
			r2render::Texture texture( 5, 5, 'A' );
			auto node = r2base::Node::Create( dummy_director );
			{
				node->mTransformComponent->SetPosition( 20, 25 );

				auto component = node->AddComponent<r2component::TextureRenderComponent>();
				component->SetTexture( &texture );
				component->SetRect( -1, -1, 4, 4 );
			}

			std::cout << r2::split;

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "r2render::Camera camera( { 20, 25 }, { 20, 10 } );" << r2::linefeed;
				std::cout << r2::tab << "r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' );" << r2::linefeed2;

				std::cout << r2::tab << "r2base::Director dummy_director;" << r2::linefeed2;

				std::cout << r2::tab << "r2render::Texture texture( 5, 5, '+' );" << r2::linefeed2;

				std::cout << r2::tab << "auto node = r2base::Node::Create( dummy_director );" << r2::linefeed;
				std::cout << r2::tab << "node->mTransformComponent->SetPosition( 20, 25 );" << r2::linefeed2;

				std::cout << r2::tab << "auto component = r2component::TextureRenderComponent::Create( *node );" << r2::linefeed;
				std::cout << r2::tab << "component->SetTexture( &texture );" << r2::linefeed;
				std::cout << r2::tab << "component->SetRect( -1, -1, 4, 4 );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				EXPECT_NE( nullptr, node->GetComponent<r2component::TextureRenderComponent>()->GetTexture() );
				EXPECT_EQ( &texture, node->GetComponent<r2component::TextureRenderComponent>()->GetTexture() );
			}

			std::cout << r2::split;

			{
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << "+ Process" << r2::linefeed2;
				std::cout << r2::tab << "node->Render( &camera, &render_target, r2::PointInt::GetZERO() );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 32 } );

				std::cout << "+ Show Render Target" << r2::linefeed2;

				

				int current_x = 0;
				for( const auto& p : render_target )
				{
					std::cout << p;

					++current_x;

					if( render_target.GetWidth() <= current_x )
					{
						current_x = 0;
						std::cout << r2::linefeed;
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 45 } );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT LabelComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label Component";
		};
	}
	r2cm::iItem::DoFuncT LabelComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			r2render::Camera camera( { 20, 25 }, { 20, 10 } );
			r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' );

			r2base::Director dummy_director;

			auto node = r2base::Node::Create( dummy_director );
			{
				node->mTransformComponent->SetPosition( 20, 25 );

				node->AddComponent<r2component::LabelComponent>();

				auto component = node->AddComponent<r2component::TextureRenderComponent>();
				component->SetTexture( node->GetComponent<r2component::LabelComponent>()->GetTexture() );
				component->SetRect( -1, -1, 5, 0 );
			
			}

			const char* const dummy_text = "Bla Bla Bla";
			node->GetComponent<r2component::LabelComponent>()->SetString( dummy_text );

			std::cout << r2::split;

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "r2render::Camera camera( { 20, 25 }, { 20, 10 } );" << r2::linefeed;
				std::cout << r2::tab << "r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' );" << r2::linefeed2;

				std::cout << r2::tab << "r2base::Director dummy_director;" << r2::linefeed2;

				std::cout << r2::tab << "auto node = r2base::Node::Create( dummy_director );" << r2::linefeed;
				std::cout << r2::tab << "node->mTransformComponent->SetPosition( 20, 25 );" << r2::linefeed2;

				std::cout << r2::tab << "node->AddComponent( r2component::LabelComponent::Create( *node ) );" << r2::linefeed2;

				std::cout << r2::tab << "auto component = r2component::TextureRenderComponent::Create( *node );" << r2::linefeed;
				std::cout << r2::tab << "component->SetTexture( node->GetComponent<r2component::LabelComponent>()->GetTexture() );" << r2::linefeed;
				std::cout << r2::tab << "component->SetRect( -1, -1, 5, 0 );" << r2::linefeed2;

				std::cout << r2::tab << "const char* const dummy_text = \"Bla Bla Bla\";" << r2::linefeed;
				std::cout << r2::tab << "node->GetComponent<r2component::LabelComponent>()->SetString( dummy_text );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				EXPECT_EQ( dummy_text, node->GetComponent<r2component::LabelComponent>()->GetString() );
			}

			std::cout << r2::split;

			{
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << "+ Process" << r2::linefeed2;
				std::cout << r2::tab << "node->Render( &camera, &render_target, r2::PointInt::GetZERO() );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 35 } );

				std::cout << "+ Show Render Target" << r2::linefeed2;

				int current_x = 0;
				for( const auto& p : render_target )
				{
					std::cout << p;

					++current_x;

					if( render_target.GetWidth() <= current_x )
					{
						current_x = 0;
						std::cout << r2::linefeed;
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 50 } );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}