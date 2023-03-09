// main.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <ranges>

int main(int argc, const char **argv)
{
	std::vector<std::vector<int>> matrix;
	int size;

	if (argc < 2)
	{
		std::cout << "Input filename missing.\n";

		return EXIT_FAILURE;
	}

	std::ifstream input(argv[1]);
	
	input >> size;

	for (const auto& i : std::views::iota(0, size))
	{
		matrix.emplace_back();
		for (const auto& j : std::views::iota(0, size))
		{
			int number;
			input >> number;

			matrix[i].push_back(number);

			std::cout << matrix[i][j] << ' ';
		}
		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}
