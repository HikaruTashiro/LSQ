#include "lsq.h"
#include <type_traits>
#include <utility>

lsq::lsq()
{
    line[0] = 1.0f;
    line[1] = 0.0f;
}

lsq::lsq(std::vector<std::pair<float, float>> &point_data)
{
    associate_data(point_data);
}

void lsq::associate_data(std::vector<std::pair<float, float>> &point_data)
{
    #define x first
    #define y second 

    float mean_x{}, mean_y{}, dif_x;

    for (auto elem : point_data)
    {
        mean_x += elem.x;
        mean_y += elem.y;
    }

    mean_x /= static_cast<float>(point_data.size());
    mean_y /= static_cast<float>(point_data.size());

    float sum_num{}, sum_denum{};

    for (auto elem : point_data)
    {
        dif_x = elem.x - mean_x;
        sum_num += (elem.y - mean_y) * dif_x;
        sum_denum += dif_x * dif_x;
    }

    line[0] = sum_num / sum_denum;
    line[1] = - line[0] * mean_x + mean_y;

}

void lsq::generate_graph(std::vector<float> &y_axis, int qtd, float start, float end)
{

}
