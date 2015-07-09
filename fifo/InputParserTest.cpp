#include "InputParser.h"
#include <iostream>
#include <stdlib.h>

int main()
{
		InputParser Parser;
		InputParser::Coord crd;
		Parser.PutChar('c');
		crd.X = 1000;
		for (int i = 0; i < 4; i++)
			Parser.PutChar(crd.byX[i]);
		crd.Y = 2000;
		for (int i = 0; i < 4; i++)
			Parser.PutChar(crd.byY[i]);
		crd.Z = 3000;
		for (int i = 0; i < 4; i++)
			Parser.PutChar(crd.byZ[i]);
		bool passed = true;
		InputParser::Coord result = Parser.GetLastCoord();
		if (result.X != crd.X) passed = false;
		if (result.Y != crd.Y) passed = false;
		if (result.Z != crd.Z) passed = false;
		if (passed)
		{
			std::cout<<"1. Test Passed"<<std::endl;
		}
		else
		{
			std::cout<<"1. Test Failed"<<std::endl;
		}
		Parser.PutChar('t');
		crd.X = 5000; // abuse Coord functionality
		for (int i = 0; i < 4; i++)
			Parser.PutChar(crd.byX[i]);
		passed = true;
		unsigned int uiresult = Parser.GetLastThrottle();
		if (uiresult != 5000) passed = false;
		if (passed)
		{
			std::cout<<"2. Test Passed"<<std::endl;
		}
		else
		{
			std::cout<<"2. Test Failed"<<std::endl;
		}
		Parser.PutChar('c');
		crd.X = 4000;
		for (int i = 0; i < 4; i++)
			Parser.PutChar(crd.byX[i]);
		crd.Y = 5000;
		for (int i = 0; i < 4; i++)
			Parser.PutChar(crd.byY[i]);
		crd.Z = 6000;
		for (int i = 0; i < 4; i++)
			Parser.PutChar(crd.byZ[i]);
		passed = true;
		result = Parser.GetLastCoord();
		if (result.X != crd.X) passed = false;
		if (result.Y != crd.Y) passed = false;
		if (result.Z != crd.Z) passed = false;
		if (passed)
		{
			std::cout<<"3. Test Passed"<<std::endl;
		}
		else
		{
			std::cout<<"3. Test Failed"<<std::endl;
		}
		for (int j = 0; j < 100; j++)
		{
			Parser.PutChar('c');
			crd.X = rand();
			for (int i = 0; i < 4; i++)
				Parser.PutChar(crd.byX[i]);
			crd.Y = rand();
			for (int i = 0; i < 4; i++)
				Parser.PutChar(crd.byY[i]);
			crd.Z = rand();
			for (int i = 0; i < 4; i++)
				Parser.PutChar(crd.byZ[i]);
			passed = true;
			result = Parser.GetLastCoord();
			if (result.X != crd.X) passed = false;
			if (result.Y != crd.Y) passed = false;
			if (result.Z != crd.Z) passed = false;
			if (passed)
			{
				std::cout<<(j+4)<<". Test Passed"<<std::endl;
			}
			else
			{
				std::cout<<(j+4)<<". Test Failed"<<std::endl;
			}
		}
	return 0;
};
