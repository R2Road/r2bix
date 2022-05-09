#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace action_test
{
	class TickActionTest : public r2cm::iItem, public r2cm::SingleTon<TickActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class DelayActionTest : public r2cm::iItem, public r2cm::SingleTon<DelayActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class SequenceActionTest : public r2cm::iItem, public r2cm::SingleTon<SequenceActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class MoveByActionTest : public r2cm::iItem, public r2cm::SingleTon<MoveByActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class MoveToActionTest : public r2cm::iItem, public r2cm::SingleTon<MoveToActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class RepeatActionTest : public r2cm::iItem, public r2cm::SingleTon<RepeatActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class BlinkActionTest : public r2cm::iItem, public r2cm::SingleTon<BlinkActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class CallbackActionTest : public r2cm::iItem, public r2cm::SingleTon<CallbackActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class AnimationRequestActionTest : public r2cm::iItem, public r2cm::SingleTon<AnimationRequestActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}