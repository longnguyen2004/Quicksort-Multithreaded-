// Quicksort (Multithreaded).cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <type_traits>

std::ifstream input;
std::ofstream output;

void OutputVector(std::vector<int> A)
{
	for (std::vector<int>::iterator i = A.begin(); i < A.end(); i++)
		output << *i << ' ';
	output << std::endl;
}

template <typename Iterator>
void Quicksort_multi(Iterator begin, Iterator end)
{
	static_assert(std::is_convertible<std::random_access_iterator_tag,
                  typename std::iterator_traits<Iterator>::iterator_category>::value,
    			  "The sorting function only accepts random access iterators or raw pointers to an array.\n");
	if (begin >= end) return;
	Iterator i = begin, j = end;
	auto pivot = *(begin + std::distance(begin, end) / 2);
	while (i < j)
	{
		while (*i < pivot) i++;
		while (*j > pivot) j--;
		if (i <= j)
		{
			std::iter_swap(i, j);
			i++; j--;
		}
	}
	std::thread sortleft(Quicksort_multi<Iterator>, begin, j);
	std::thread sortright(Quicksort_multi<Iterator>, i, end);
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

