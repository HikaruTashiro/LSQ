#include <array>
#include <utility>
#include <vector>

class lsq
{
    public:
        std::array<float, 2> line;
        lsq();
        lsq(std::vector<std::pair<float, float>> &point_data);
        void generate_graph(std::vector<float> &y_axis, int qtd, float start, float end);
        void associate_data(std::vector<std::pair<float, float>> &point_data);
};
