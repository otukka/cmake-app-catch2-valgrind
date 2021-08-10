

#include <fstream>
#include <sstream>
#include <vector>
#include <cstddef> /* nullptr_t */

namespace CSV
{
    std::vector<std::vector<int64_t>> readIntegerCSV(const std::string &filename)
    {

        std::vector<std::vector<int64_t>> result;

        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line))
        {

            std::vector<int64_t> inner;

            std::stringstream ss(line);
            std::string cell;

            while (std::getline(ss, cell, ','))
            {
                std::cout << cell << std::endl;
                if (!ss || cell.empty())
                {
                    inner.push_back(0);
                }
                else
                {
                    inner.push_back(std::stoi(cell));
                }
            }
            result.push_back(inner);
        }
        return result;
    }
}