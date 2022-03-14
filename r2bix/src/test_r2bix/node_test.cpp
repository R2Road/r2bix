#include "pch.h"
#include "node_test.h"

#include "r2cm/r2cm_eTestEndAction.h"

#include "base/r2base_Director.h"
#include "base/r2base_Node.h"
#include "component/r2component_LabelComponent.h"
#include "component/r2component_TextureFrameAnimationComponent.h"
#include "component/r2component_TextureFrameRenderComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "component/r2component_TransformComponent.h"
#include "node/r2node_LabelNode.h"
#include "node/r2node_SceneNode.h"
#include "node/r2node_SpriteAnimationNode.h"
#include "node/r2node_SpriteNode.h"
#include "r2/r2_Inspector.h"

namespace node_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2::split;

			DECLARATION_MAIN( const auto dummy_node = r2base::Node::Create( dummy_director ) );

			std::cout << r2::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TransformComponent>() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Scene::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Scene";
		};
	}
	r2cm::iItem::DoFuncT Scene::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2::split;

			DECLARATION_MAIN( const auto dummy_node = r2node::SceneNode::Create( dummy_director ) );

			std::cout << r2::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TransformComponent>() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Label::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label";
		};
	}
	r2cm::iItem::DoFuncT Label::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2::split;

			DECLARATION_MAIN( const auto dummy_node = r2node::LabelNode::Create( dummy_director ) );

			std::cout << r2::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TextureRenderComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::LabelComponent>() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Sprite::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sprite";
		};
	}
	r2cm::iItem::DoFuncT Sprite::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2::split;

			DECLARATION_MAIN( const auto dummy_node = r2node::SpriteNode::Create( dummy_director ) );

			std::cout << r2::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TextureFrameRenderComponent>() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT SpriteAnimation::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sprite Animation";
		};
	}
	r2cm::iItem::DoFuncT SpriteAnimation::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2::split;

			DECLARATION_MAIN( const auto dummy_node = r2node::SpriteAnimationNode::Create( dummy_director ) );

			std::cout << r2::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TextureFrameRenderComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TextureFrameAnimationComponent>() );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( auto frame = dummy_node->GetComponent<r2component::TextureFrameRenderComponent>() );
				DECLARATION_MAIN( auto animation = dummy_node->GetComponent<r2component::TextureFrameAnimationComponent>() );
				EXPECT_EQ( frame, animation->GetTextureFrameRenderComponent() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}