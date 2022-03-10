#include "pch.h"
#include "node_test.h"

#include "r2cm/r2cm_eTestEndAction.h"

#include "base/r2base_Director.h"
#include "base/r2base_Node.h"
#include "component/r2component_LabelComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "component/r2component_TransformComponent.h"
#include "node/r2node_LabelNode.h"
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


			r2base::Director dummy_director;
			const auto dummy_node = r2base::Node::Create( dummy_director );

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "r2base::Director dummy_director;" << r2::linefeed2;
				std::cout << r2::tab << "const auto dummy_node = r2base::Node::Create( dummy_director );" << r2::linefeed;
			}

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


			r2base::Director dummy_director;
			const auto dummy_node = r2node::LabelNode::Create( dummy_director );

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "r2base::Director dummy_director;" << r2::linefeed2;
				std::cout << r2::tab << "const auto dummy_node = r2node::LabelNode::Create( dummy_director );" << r2::linefeed;
			}

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
}