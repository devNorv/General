#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
enum TrafficSignalState
{
    RED,
    YELLOW,
    GREEN
};

class TrafficLight
{

public:
    TrafficLight() : state(TrafficSignalState::RED)
    {
    }

    void run()
    {
        while (true)
        {
            switch (state)
            {
            case TrafficSignalState::RED:
                std::cout << "RED - STOP!" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(RedDuration));
                state = TrafficSignalState::GREEN;
                break;
            case TrafficSignalState::GREEN:
                std::cout << "GREEN - GO!" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(GreenDuration));
                state = TrafficSignalState::YELLOW;
                break;
            case TrafficSignalState::YELLOW:
                std::cout << "YELLOW - SLOW DOWN!" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(YellowDuration));
                state = TrafficSignalState::RED;
                break;
            default:
                break;
            }

        }
    }

private:
    TrafficSignalState state;
    const int RedDuration = 5;
    const int YellowDuration = 3;
    const int GreenDuration = 5;
};

int main()
{
    TrafficLight t;
    t.run();
    return 0;
}