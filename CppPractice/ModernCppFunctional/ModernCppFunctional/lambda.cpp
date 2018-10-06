#include "pch.h"

#include "lambda.h"
#include "util.h"

void LambdaPractice()
{
	PrintTitle("lambda_multiline_func");

	std::array<int,10> arr;
	std::generate(arr.begin(), arr.end(), [n = 0]() mutable	{ return n++; });
	std::for_each(arr.begin(), arr.end(), [](const int n)
	{
		std::cout << n << " is";

		if(n < 2)
		{
			if( n == 0 )
			{
				std::cout << " not";
			}
		}
		else
		{
			for( auto i = 2; i < n; ++i )
			{
				if( n % i == 0)
				{
					std::cout << " not";
				}
			}
		}

		std::cout << " prime number" << std::endl;
	});
}
