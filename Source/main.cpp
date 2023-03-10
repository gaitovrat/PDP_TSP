// main.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <ranges>
#include <chrono>

#include "solution.h"

int main(int argc, const char **argv)
{
	TSP::matrix<int> graph;
	int size;

	if (argc < 2)
	{
		std::cout << "Input filename missing.\n";

		return EXIT_FAILURE;
	}

	std::ifstream input(argv[1]);

	std::cout << "Filename: " << argv[1] << std::endl;
	
	input >> size;

	std::cout << "Reading graph...";
	for (const auto& i : std::views::iota(0, size))
	{
		graph.emplace_back();
		for (const auto& j : std::views::iota(0, size))
		{
			int number;
			input >> number;

			graph[i].push_back(number);
		}
	}
	std::cout << "Complete\n";

	TSP tsp(graph, 0);
	std::cout << "Call TSP::solve()\n";
	auto start = std::chrono::high_resolution_clock::now();
	std::cout << tsp.Solve() << std::endl;
	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time: " << duration << std::endl;

	return EXIT_SUCCESS;
}
