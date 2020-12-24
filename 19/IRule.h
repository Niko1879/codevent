#pragma once
#include <string>

namespace Codevent19
{
	class IRule
	{
	public:
		IRule(size_t size) : size(size) {}

		virtual bool check(const std::string& expression) = 0;

		inline size_t getSize() const { return size; }

	protected:
		size_t size;
	};
}
