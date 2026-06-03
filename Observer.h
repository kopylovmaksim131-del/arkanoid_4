#pragma once

namespace ArkanoidGame
{
	class IObserver
	{
	public:
		virtual void onNotify() = 0;
		~IObserver() = default;
	};
}
