#pragma once

namespace r2bix_ui
{
	enum class eCursorStatus
	{
		None,

		CursorLeave,
		CursorOver,
		CursorMove, // required cursor over
	};

	enum class eKeyStatus
	{
		None,

		Push,
		Pressed,
		Release, // required cursor over
		Cancel,
	};
}