#pragma once
namespace tggd::common
{
	class Thingie
	{
	protected:
		virtual void Start() = 0;
		virtual void Finish() = 0;
	};
}