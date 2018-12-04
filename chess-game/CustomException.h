#pragma once

#include <iostream>

namespace Mistake
{
    class CustomException : public std::exception
	{
	public:
        CustomException(std::string msg);
        std::string message;
	};
}
