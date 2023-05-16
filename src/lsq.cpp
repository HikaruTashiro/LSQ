#include "lsq.h"
#include <ios>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <cmath>
#include <iomanip>


lsq::lsq()
{
    /* f(x) = ax + b, na qual a: line[1] e b: line[0]*/
    line[0] = 1.0f;
    line[1] = 0.0f;
    pearson = pearson_sqr =  sum_x = sum_y
    = sum_xx =  sum_xy = n_pairs = 0.0f;
}

lsq::lsq(std::vector<std::pair<float, float>> &point_data)
{
    associate_data(point_data);
}

void lsq::associate_data(std::vector<std::pair<float, float>> &point_data)
{
    #define x first
    #define y second 

    float mean_x{}, mean_y{}, desv_x, desv_y, sum_yy{};
    sum_x = sum_y = sum_xx = sum_xy = 0.0f;

    for (auto elem : point_data)
    {
        sum_x += elem.x;
        sum_y += elem.y;
        sum_xy += elem.x * elem.y;
        sum_xx += elem.x * elem.x;
        sum_yy += elem.y * elem.y;
    }

    n_pairs = point_data.size();
    mean_x = sum_x / static_cast<float>(n_pairs);
    mean_y = sum_y / static_cast<float>(n_pairs);
    pearson = sum_xy / static_cast<float>(n_pairs);
    pearson = pearson - mean_x * mean_y; // Cov(mean_x, mean_y)
    desv_x = sum_xx / static_cast<float>(n_pairs) - mean_x * mean_x;
    desv_y = sum_yy / static_cast<float>(n_pairs) - mean_y * mean_y;
    pearson /= std::sqrt(desv_x * desv_y);
    pearson_sqr = pearson * pearson;
    float denum = static_cast<float>(n_pairs) * sum_xx - sum_x * sum_x;
    
    line[0] = (static_cast<float>(n_pairs) * sum_xy - sum_x * sum_y) / denum;
    line[1] = (sum_y * sum_xx - sum_x * sum_xy) / denum; 
}

void lsq::get_fuction_expr(std::string& expression, int precision)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << line[0];
    expression.clear();
    expression = stream.str();
    expression += " * x + ";
    stream.str("");
    stream << line[1];
    expression += stream.str();
}

void lsq::get_info(std::string &lsq_info, int precision)
{
    std::stringstream stream;
    lsq_info.clear();
    stream << std::fixed << std::setprecision(precision) << pearson;
    lsq_info = "pearson = ";
    lsq_info += stream.str();
    stream.str("");
    stream << pearson_sqr;
    lsq_info += "\npearson_sqr = ";
    lsq_info += stream.str();
    stream.str("");
    stream << sum_x;
    lsq_info += "\nsum_x = ";
    lsq_info += stream.str();
    stream.str("");
    stream << sum_y;
    lsq_info += "\nsum_y = ";
    lsq_info += stream.str();
    stream.str("");
    stream << sum_xy;
    lsq_info += "\nsum_xy = ";
    lsq_info += stream.str();
    stream.str("");
    stream << sum_xx;
    lsq_info += "\nsum_xx = ";
    lsq_info += stream.str();
    lsq_info += "\nNumero de Pares = ";
    lsq_info += std::to_string(n_pairs);
}

void lsq::generate_graph(std::array<float,2> &x_axis, std::array<float,2> &y_axis,
                        std::vector<float> &x_axis_points, std::vector<float> &y_axis_points,
                        std::vector<std::pair<float, float>> &point_data)
{
    float max_x = (*find_max_x(point_data.begin(), point_data.end())).first;
    float min_x = (*find_min_x(point_data.begin(), point_data.end())).first;

    x_axis[0] = min_x - 10.0f;
    y_axis[0] = line[0] * x_axis[0] + line[1];
    x_axis[1] = max_x + 10.0f;
    y_axis[1] = line[0] * x_axis[1] + line[1];

    x_axis_points.clear();
    y_axis_points.clear();
    for (auto elem : point_data)
    {
        x_axis_points.push_back(elem.first);
        y_axis_points.push_back(elem.second);
    }
}

pair_iter lsq::find_max_x(const pair_iter& begin, const pair_iter&end)
{
    pair_iter found = begin;
    pair_iter b_iter = begin;
    pair_iter e_iter = end;
    while (b_iter != e_iter)
    {
        if((*found).first < (*b_iter).first)
            found = b_iter;
        b_iter++;    
    }
    return found;
}

pair_iter lsq::find_min_x(const pair_iter& begin, const pair_iter&end)
{
    pair_iter found = begin;
    pair_iter b_iter = begin;
    pair_iter e_iter = end;
    while (b_iter != e_iter)
    {
        if((*found).first > (*b_iter).first)
            found = b_iter;
        b_iter++;    
    }
    return found;
}

pair_iter lsq::find_max_y(const pair_iter& begin, const pair_iter&end)
{
    pair_iter found = begin;
    pair_iter b_iter = begin;
    pair_iter e_iter = end;
    while (b_iter != e_iter)
    {
        if((*found).second < (*b_iter).second)
            found = b_iter;
        b_iter++;    
    }
    return found;
}

pair_iter lsq::find_min_y(const pair_iter& begin, const pair_iter&end)
{
    pair_iter found = begin;
    pair_iter b_iter = begin;
    pair_iter e_iter = end;
    while (b_iter != e_iter)
    {
        if((*found).second > (*b_iter).second)
            found = b_iter;
        b_iter++;    
    }
    return found;
}
