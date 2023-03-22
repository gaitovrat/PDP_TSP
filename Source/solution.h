#include <vector>
#include <thread>
#include <mutex>

class TSP
{
public:
	template <class T>
	using matrix = std::vector<std::vector<T> >;
	
	TSP(const TSP::matrix<int>& graph, int start);

	int Solve();	

private:
	void ComputeDistance();

	void GeneratePermutation(int i);

	std::vector<int> m_permutations;
	TSP::matrix<int> m_graph;
	int m_minDistance;
	std::mutex m_minDistanceMutex;
	int m_start;
};