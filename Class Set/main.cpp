#include<iostream>
#include"Enum.h"
#include"Set.h"



int main()
{
	try
	{
	}
	catch (Mistakes mistake)
	{
		switch (mistake)
		{
		case Invalid_size:
			std::cout << "Invalid_size";
			exit(0);
		case Invalid_index:
			std::cout << "Invalid_index";
			exit(1);
		case Invalid_column:
			std::cout << "Invalid_column";
			exit(2);
		case Invalid_line:
			std::cout << "Invalid_line";
			exit(3);
		case Invalid_value:
			std::cout << "Invalid_value";
			exit(4);
		default:
			std::cout << "Something went wrong";
			exit(-1);
		}
	}
	return 0;
}