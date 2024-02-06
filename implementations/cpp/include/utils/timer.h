#pragma once
#include <chrono>
#include <string>

class Timer {

    Timer(std::string &measurement) 
    : m_Measurement{measurement}
    {
        auto start = std::chrono::high_resolution_clock::now();
        
    }


    ~Timer() {
        auto endTimepoint = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        auto stop = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
        
        auto duration = stop - start;
        double ms = duration * 0.001;

    }

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
        std::string m_Measurement;
};
