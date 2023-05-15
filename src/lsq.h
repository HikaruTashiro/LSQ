#include <array>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

using pair_iter = std::vector<std::pair<float, float>>::iterator;

struct lsq
{
    /* data */
        std::array<float, 2> line;
        float pearson;
        float pearson_sqr;
        float sum_x;
        float sum_y;
        float sum_xx;
        float sum_xy;
        std::size_t n_pairs;
    /* methods */
        lsq();
        lsq(std::vector<std::pair<float, float>> &point_data);
        void generate_graph(std::array<float,2> &x_axis, std::array<float,2> &y_axis,
                        std::vector<float> &x_axis_points, std::vector<float> &y_axis_points,
                        std::vector<std::pair<float, float>> &point_data);
        void associate_data(std::vector<std::pair<float, float>> &point_data);
        void get_fuction_expr(std::string& expression);
        void get_info(std::string& lsq_info);

        private:
        pair_iter find_max_x(const pair_iter& begin, const pair_iter&end);
        pair_iter find_min_x(const pair_iter& begin, const pair_iter&end);
        pair_iter find_max_y(const pair_iter& begin, const pair_iter&end);
        pair_iter find_min_y(const pair_iter& begin, const pair_iter&end);
};
