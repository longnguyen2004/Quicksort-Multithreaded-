// Quicksort (Multithreaded).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

std::ifstream input;
std::ofstream output;

void OutputVector(std::vector<int> A)
{
	for (std::vector<int>::iterator i = A.begin(); i < A.end(); i++)
		output << *i << ' ';
	output << std::endl;
}

void Quicksort_multi(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	if (begin >= end) return;
	std::vector<int>::iterator i = begin, j = end;
	int pivot = *(begin + std::distance(begin, end) / 2);
	while (i < j)
	{
		while (*i < pivot) i++;
		while (*j > pivot) j--;
		if (i < j)
		{
			std::iter_swap(i, j);
			i++; j--;
		}
	}
	std::thread sortleft(Quicksort_multi, begin, j);
	std::thread sortright(Quicksort_multi, i, end);
	sortleft.join();
	sortright.join();
}

int main()
{
	std::string s;
	while (!input.is_open()) input.open("input.txt");
	std::getline(input, s);
	std::istringstream is(s);
	std::vector<int> A;
	
	int temp;
	while (is >> temp) A.push_back(temp);
	Quicksort_multi(A.begin(), A.end() - 1);
	
	output.open("output.txt", std::ios::out | std::ios::trunc);
	OutputVector(A);
    return 0;
}

