// TEST THREAD PROJECT BY GAZIZ RAZHAPOV  - VISUAL STUDIO 2013 ULTIMATE (C++11)
// INCLUDES 
#include <iostream>
#include <thread>
#include <Windows.h>
#include <array>
#include <time.h>

const size_t sSize = 10000;

typedef std::array<int, sSize> tdArrInt;

// Insert sort
void InsertSort(tdArrInt &_arrInput) 
{
	for (size_t i = 1; i < _arrInput.size(); i++)
		for (size_t j = i; j > 0 && _arrInput[j] < _arrInput[j - 1]; j--)
			std::swap(_arrInput[j], _arrInput[j -1]);

	std::cout << "InsertSort: thread id = " << std::this_thread::get_id() << std::endl;
}

// Select sort
void SelectSort(tdArrInt &_arrInput)
{
	for (size_t i = 0; i < _arrInput.size(); i++)
	{
		int iMin = i;
		for (size_t j = i + 1; j < _arrInput.size(); j++)
		{
			if (_arrInput[j] < _arrInput[iMin]) iMin = j;
			std::swap(_arrInput[i], _arrInput[iMin]);
		}
	}

	std::cout << "SelectSort: thread id = " << std::this_thread::get_id() << std::endl;
}

// Print array
void PrintArray(tdArrInt &_arrInput) 
{
	for (auto iValue : _arrInput)  std::cout << iValue << " ";
	std::cout << std::endl;
}

// Main process 
int main() 
{
	tdArrInt arrNumbersOne,
	         arrNumbersTwo;

	for (size_t i = 0; i < sSize; i++)
	{
		arrNumbersOne[i] = rand() % 10000;
		arrNumbersTwo[i] = rand() % 10000;
	}
	
	std::thread thrTwo(SelectSort, std::ref(arrNumbersTwo)),
	            thrOne(InsertSort, std::ref(arrNumbersOne));
	
	thrOne.join();
	thrTwo.join();

	system("pause");
	return 0;
}