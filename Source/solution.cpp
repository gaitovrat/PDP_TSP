#include "solution.h"

#include <algorithm>

TSP::TSP(const TSP::matrix<int>& graph, int start) : m_permutations(), m_graph(graph), m_minDistance(INT_MAX), m_minDistanceMutex(), m_start(start)
{
	for (int i = 0; i < m_graph.size(); ++i)
	{
		m_permutations.push_back(i);
	}
}

int TSP::Solve()
{
	std::vector<std::thread> threads;

	for (int i = 0; i < m_graph.size(); ++i)
	{
		std::swap(m_permutations[0], m_permutations[i]);
		threads.emplace_back([this]() { GeneratePermutation(1); });
		std::swap(m_permutations[0], m_permutations[i]);
	}

	for (auto& thread : threads)
	{
		thread.join();
	}

	return m_minDistance;
}

void TSP::ComputeDistance()
{
	int distance = 0;
	for (int i = 0; i < m_permutations.size(); ++i)
	{
		int from = m_permutations[i];
		int to = m_permutations[(i + 1) % m_permutations.size()];
		distance += m_graph[from][to];
	}

	m_minDistanceMutex.lock();
	m_minDistance = std::min(m_minDistance, distance);
	m_minDistanceMutex.unlock();
}

void TSP::GeneratePermutation(int i)
{
	if (i == m_graph.size()) {
		ComputeDistance();
	}
	else {
		for (int j = i; j < m_graph.size(); j++) {
			std::swap(m_permutations[i], m_permutations[j]);
			GeneratePermutation(i + 1);
			std::swap(m_permutations[j], m_permutations[i]);
		}
	}
}
