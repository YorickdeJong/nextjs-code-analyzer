#pragma once

#include <iostream>
#include <chrono>
#include <string>

class Timer {
public:
    Timer(const std::string &measurement) 
    : m_Measurement(measurement), m_StartTimepoint(std::chrono::high_resolution_clock::now()) 
    {
        // Constructor initializes m_StartTimepoint with the current time
    }

    ~Timer() {
        auto endTimepoint = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        auto stop = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
        
        auto duration = stop - start;
        double ms = duration * 0.001;

        std::cout << "Duration of " << m_Measurement << " is: " << ms << " ms\n";
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    const std::string m_Measurement;
};