#ifndef DATA_HPP
#define DATA_HPP
#include <fstream>
#include <iostream>
#include <queue> 
#include <string>
#include <sstream>

namespace mode7
{

class Data
{
public:
    Data(); 
    ~Data(); 
 
    void getHealthPacket();
    void getOrientationPacket();
    void readData(std::string); 
    bool isEmpty(); 
    std::vector<float> pollData(); 
    
private:
    std::queue<std::string> data; 
};

}

#endif /* DATA_HPP */