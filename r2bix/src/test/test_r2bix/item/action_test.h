#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace action_test
{
	class TickActionTest : public r2cm::iItem, public r2cm::SingleTon<TickActionTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class DelayActionTest : public r2cm::iItem, public r2cm::SingleTon<DelayActionTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class SequenceActionTest : public r2cm::iItem, public r2cm::SingleTon<SequenceActionTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class MoveByActionTest : public r2cm::iItem, public r2cm::SingleTon<MoveByActionTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class MoveToActionTest : public r2cm::iItem, public r2cm::SingleTon<MoveToActionTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class RepeatActionTest : public r2cm::iItem, public r2cm::SingleTon<RepeatActionTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class BlinkActionTest : public r2cm::iItem, public r2cm::SingleTon<BlinkActionTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class CallbackActionTest : public r2cm::iItem, public r2cm::SingleTon<CallbackActionTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class AnimationRequestActionTest : public r2cm::iItem, public r2cm::SingleTon<AnimationRequestActionTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}