#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_stdlib.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/implot.h"
#include "imgui/implot_internal.h"
#include <array>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include "lsq.h"
#define glsl_version "#version 420" // <--- based version number 

void Initialize_GLFW();
void Initialize_GLEW();
void Initialize_ImGui();
void Cleanup_OpenGL();
void Cleanup_ImGui();
void display();

int main()
{
    Initialize_GLFW();
    Initialize_ImGui();

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Least Squares Method", NULL, NULL);
    if(window == NULL)
    {
        std::cout<<"Failed to Initialize Window\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    Initialize_GLEW();

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame(); 
        display();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwPollEvents();                     
        glfwSwapBuffers(window); 
    }

    Cleanup_ImGui();
    Cleanup_OpenGL();

    //std::vector<std::pair<float, float>> pog = {{2.0f,5.0f},{4.0f,4.0f},{6.0f,8.0f},{8.0f,6.0f},{10.0f,12.0f}};
    //std::vector<std::pair<float, float>> pog = {{6.0f,8.0f},{5.0f,7.0f},{8.0f,7.0f},{8.0f,10.0f},
    //                                            {7.0f,5.0f},{6.0f,8.0f},{10.0f,10.0f},{4.0f,6.0f},
    //                                            {9.0f,8.0f},{7.0f,6.0f}};
    //lsq based(pog);
    //std::cout << based.line[0] << " * " << 'x' << " + " << based.line[1] << '\n';
    //std::cout << "pearson = " << based.pearson << '\n';
    //std::cout << "pearson_sqr = " << based.pearson_sqr << '\n';
    //std::cout << "sum_x = " << based.sum_x << '\n';
    //std::cout << "sum_y = " << based.sum_y << '\n';
    //std::cout << "sum_xy = " << based.sum_xy << '\n';
    //std::cout << "sum_xx = " << based.sum_xx << '\n';
    //std::cout << "N = " << based.n_pairs << '\n';

    return 0;
}

void Initialize_GLFW()
{
    if (!glfwInit())
    {
        std::cout << "Failed to Initialize GLFW\n";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
}

void Initialize_GLEW()
{
    /*Initialize GLEW Library*/
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void Initialize_ImGui()
{
    /*ImGUI Initialization*/
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
}

void Cleanup_OpenGL()
{
    glfwTerminate();
}

void Cleanup_ImGui()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
}

void display()
{
    static int precision = 3;
    static int number = 5;
    static std::string ids[20];
    static std::string expression;
    static std::string info;
    static std::array<float, 2> x_axis;
    static std::array<float, 2> y_axis;
    static std::vector<float> points_x_axis;
    static std::vector<float> points_y_axis;
    static std::vector<std::pair<float, float>> coord_pairs = 
        {{2.0f,5.0f},{4.0f,4.0f},{6.0f,8.0f},{8.0f,6.0f},{10.0f,12.0f}};
    static lsq solver(coord_pairs);
    static bool setup = true;   // used only once

    if(setup)
    {
        for (int i = 0; i < 20; i++)
        {
            ids[i] = 'P';
            ids[i] += std::to_string(i + 1);
            ids[i] += "(x,y)";
        }
        solver.get_fuction_expr(expression, precision);
        solver.generate_graph(x_axis, y_axis, points_x_axis, points_y_axis, coord_pairs);
        solver.get_info(info, precision);
        setup = false;
    }

    ImGui::Begin("Opcoes", NULL, ImGuiWindowFlags_NoCollapse);
    ImGui::SliderInt("Precisao", &precision, 2, 10);
    ImGui::SliderInt("Numero de Pares", &number, 3, 20);

    while (coord_pairs.size() <  (std::size_t) number)
        coord_pairs.push_back(std::make_pair(1.0f, 1.0f));
    if ((std::size_t) number < coord_pairs.size())
        coord_pairs.resize(number);

    ImGui::Spacing();
    if(ImGui::TreeNode("Coordenadas"))
    {
        for (int i = 0; i < number; i++)
            ImGui::InputFloat2(ids[i].data(), (float*) &coord_pairs[i]); 
        ImGui::TreePop();
    }

    if(ImGui::Button("Atualizar Dados"))
    {
        solver.associate_data(coord_pairs);
        solver.generate_graph(x_axis, y_axis, points_x_axis, points_y_axis, coord_pairs);
        solver.get_fuction_expr(expression, precision);
        solver.get_info(info, precision);
    }

    if(ImPlot::BeginPlot("Grafico"))
    {
        ImPlot::PlotLine(expression.data(), x_axis.data(), y_axis.data(),x_axis.size());
        ImPlot::PlotScatter("Pares de Pontos", points_x_axis.data(),points_y_axis.data(),points_x_axis.size());
        ImPlot::EndPlot();
    }

    ImGui::InputTextMultiline("Info", &info, ImVec2(0,0), ImGuiInputTextFlags_ReadOnly);

    ImGui::End();
}
