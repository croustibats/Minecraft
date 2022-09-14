#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include <memory>
#include <chrono>
#include <iostream>


int main()
{

    //computing delta time
    std::chrono::system_clock::time_point m_previousTime;
    float m_scale = 0;


    auto currentTime = std::chrono::system_clock::now();
    auto elapsedSeconds = std::chrono::duration<double>();

    if (m_previousTime.time_since_epoch().count())
        elapsedSeconds = currentTime - m_previousTime;
    m_previousTime = currentTime;


    currentTime = std::chrono::system_clock::now();

    if (m_previousTime.time_since_epoch().count())
        elapsedSeconds = currentTime - m_previousTime;

    auto deltaTime = (float)elapsedSeconds.count();

    m_scale += 3.14f * deltaTime;
    auto currentScale = abs(sin(m_scale));

    std::cout << deltaTime<< std::endl;

    return 0;
}