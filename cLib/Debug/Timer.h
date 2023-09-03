//
// Created by ibrahim on 9/3/23.
//

#ifndef CLIB_TIMER_H
#define CLIB_TIMER_H

#include <chrono>
#include <iostream>

class Timer {
public:
    Timer() {
        m_StartTimepoint =  std::chrono::high_resolution_clock::now();
    }
    ~Timer(){
        stop();
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    void stop(){
        auto endTimepoint = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
        auto duration = end -start;
        double ms = duration *.001;
        std::cout<< ms << "ms" << std::endl;
    }
};

#endif //CLIB_TIMER_H
