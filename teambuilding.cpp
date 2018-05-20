#include <vector>
#include <iostream>
#include <queue>

int bipartition()
{
    unsigned V, E;
    std::cin >> V >> E;
    std::vector<std::vector<int>> matrix(V, std::vector<int>(V, 1));
    for (unsigned i = 0; i < E; ++i) {
        unsigned a, b;
        std::cin >> a >> b;
        matrix[a-1][b-1] = matrix[b-1][a-1] = 0;
    }

    std::vector<int> partition(V, -1);
    unsigned counter = 0;
    bool divisible = true;
    for (unsigned current = 0; current < V; ++current) {
        if (partition[current] != -1)
            continue;
        partition[current] = 1;
        ++counter;

        std::queue<unsigned> nexts;
        nexts.push(current);
        while (!nexts.empty() && divisible) {
            current = nexts.front();
            nexts.pop();
            for (unsigned next = 0; next < V; ++next) {
                if (matrix[current][next] == 1 && next != current)
                    if (partition[next] == partition[current]) {
                        divisible = false;
                        break;
                    }
                    else if (partition[next] == -1) {
                        partition[next] = !partition[current];
                        if (partition[next] == 1)
                            ++counter;
                        nexts.push(next);
                    }
            }
        }
        if (!divisible)
            break;
    }
    if (divisible) {
        if (counter == V) {
            std::cout << 1 << std::endl;
            std::cout << 1 << std::endl;
            for (unsigned i = 1; i < V; ++i) {
                    std::cout << i + 1 << " ";
            }
        }
        else {
            std::cout << counter;
            std::cout << std::endl;
            for (unsigned i = 0; i < V; ++i) {
                if (partition[i])
                    std::cout << i + 1 << " ";
            }
            std::cout << std::endl;
            for (unsigned i = 0; i < V; ++i) {
                if (!partition[i])
                    std::cout << i + 1 << " ";
            }
        }
    }
    else
        std::cout << -1;

    return 0;
}

int main() 
{
    bipartition();
    return 0;
}
