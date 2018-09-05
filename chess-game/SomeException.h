#pragma once
#include <string>
using namespace std;

namespace Mistake
{
	class SomeException : public exception
	{
	public:
		SomeException(string msg);
		string message;
	};
}
