#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace test_p2048mini_stage
{
	class Basic : public r2cm::iItem, public r2::SingleTon<Basic>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class MoveReadyTest : public r2cm::iItem, public r2::SingleTon<MoveReadyTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class MoveTest : public r2cm::iItem, public r2::SingleTon<MoveTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class StageViewNode_Generate : public r2cm::iItem, public r2::SingleTon<StageViewNode_Generate>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class StageViewNode_Setup_Render : public r2cm::iItem, public r2::SingleTon<StageViewNode_Setup_Render>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}