#include "node_test.h"

#include "r2bix/r2bix_Director.h"
#include "r2bix/r2bix_node_Node.h"
#include "r2bix/r2bix_component_CustomTextureComponent.h"
#include "r2bix/r2bix_component_LabelSComponent.h"
#include "r2bix/r2bix_component_LabelMComponent.h"
#include "r2bix/r2bix_component_TextureFrameAnimationComponent.h"
#include "r2bix/r2bix_component_TextureFrameRenderComponent.h"
#include "r2bix/r2bix_component_TextureRenderComponent.h"
#include "r2bix/r2bix_component_TransformComponent.h"
#include "r2bix/r2bix_node_CustomTextureNode.h"
#include "r2bix/r2bix_node_LabelSNode.h"
#include "r2bix/r2bix_node_LabelMNode.h"
#include "r2bix/r2bix_node_SceneNode.h"
#include "r2bix/r2bix_node_SpriteAnimationNode.h"
#include "r2bix/r2bix_node_SpriteNode.h"
#include "r2bix_helper/r2bix_helper_Printer4Texture.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

namespace node_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2bix_node::Node::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TransformComponent>() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Child_Count::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Child : Count";
		};
	}
	r2cm::iItem::DoFunctionT Child_Count::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2bix_node::Node::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_EQ( 0, dummy_node->GetChildCount() );

				std::cout << r2cm::linefeed;

				EXPECT_NE( nullptr, dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( 1, dummy_node->GetChildCount() );

				std::cout << r2cm::linefeed;

				EXPECT_NE( nullptr, dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( 2, dummy_node->GetChildCount() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Child_Sequence::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Child : Sequence";
		};
	}
	r2cm::iItem::DoFunctionT Child_Sequence::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Z값이 큰 노드가 목록의 뒤쪽으로 자리한다." << r2cm::linefeed2;

				DECLARATION_MAIN( const auto dummy_node = r2bix_node::Node::Create( dummy_director ) );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( auto child_1 = dummy_node->AddChild<r2bix_node::Node>( 1 ) );
				EXPECT_EQ( child_1, ( *dummy_node->GetChildContainer().begin() ).get() );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( auto child_2 = dummy_node->AddChild<r2bix_node::Node>( 0 ) );
				EXPECT_EQ( child_2, ( *dummy_node->GetChildContainer().begin() ).get() );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ 동일한 Z의 노드가 이미 있다면 새로 추가된 노드는 같은 Z를 가진 노드 군의 가장 마지막에 자리한다." << r2cm::linefeed2;

				DECLARATION_MAIN( const auto dummy_node = r2bix_node::Node::Create( dummy_director ) );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( auto child_1 = dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( child_1, ( *dummy_node->GetChildContainer().begin() ).get() );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( auto child_2 = dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( child_1, ( *dummy_node->GetChildContainer().begin() ).get() );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( child_2, ( *( ++dummy_node->GetChildContainer().begin() ) ).get() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Scene::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Scene";
		};
	}
	r2cm::iItem::DoFunctionT Scene::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2bix_node::SceneNode::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TransformComponent>() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT LabelS::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label S";
		};
	}
	r2cm::iItem::DoFunctionT LabelS::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2bix_node::LabelSNode::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::CustomTextureComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TextureRenderComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::LabelSComponent>() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT LabelM::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label M";
		};
	}
	r2cm::iItem::DoFunctionT LabelM::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2bix_node::LabelMNode::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::CustomTextureComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TextureRenderComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::LabelMComponent>() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Sprite::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sprite";
		};
	}
	r2cm::iItem::DoFunctionT Sprite::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2bix_node::SpriteNode::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT SpriteAnimation::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sprite Animation";
		};
	}
	r2cm::iItem::DoFunctionT SpriteAnimation::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2bix_node::SpriteAnimationNode::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TextureFrameAnimationComponent>() );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( auto frame = dummy_node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );
				DECLARATION_MAIN( auto animation = dummy_node->GetComponent<r2bix_component::TextureFrameAnimationComponent>() );
				EXPECT_EQ( frame, animation->GetTextureFrameRenderComponent() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT CustomeTexture::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Custome Texture Node";
		};
	}
	r2cm::iItem::DoFunctionT CustomeTexture::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 13, 5 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto node = r2bix_node::CustomTextureNode::Create( dummy_director ) );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::TransformComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::TextureRenderComponent>() );

			std::cout << r2cm::split;

			{
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->Reset( 3, 3, 'T' ) );
				PROCESS_MAIN( node->GetComponent<r2bix_component::TextureRenderComponent>()->ResetVisibleRect() );

				std::cout << r2cm::linefeed;

				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->Reset( 5, 5, 'S' ) );
				PROCESS_MAIN( node->GetComponent<r2bix_component::TextureRenderComponent>()->ResetVisibleRect() );

				std::cout << r2cm::linefeed;

				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}