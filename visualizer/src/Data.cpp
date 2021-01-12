#include "Data.hpp"

namespace mode7
{
    std::queue<std::string> data; 

Data::Data()
{

}

Data::~Data()
{

}

void Data::getHealthPacket()
{

}

void Data::getOrientationPacket()
{

}

void Data::readData(std::string path)
{
    std::string packet;  
    // Read from the .csv file
    std::ifstream MyReadFile(path);

    // Use a while loop together with the getline() function to read the file line by line
    while (std::getline(MyReadFile, packet)) {
        // Push data info into queue. 
        data.push(packet);
    }

    // Close the .csv file
    MyReadFile.close();
}

bool Data::isEmpty()
{
    return data.empty(); 
}

std::vector<float> Data::pollData()
{
    if(!isEmpty())
    {
        //Version One 
        std::vector<float> packet; 
        std::stringstream s(data.front()); 
        std::string val; 
        while(std::getline(s, val, ','))
        {
            packet.push_back(stof(val)); 
        }
        data.pop(); 
        return packet; 
    }
    std::cout << "Queue is empty." << std::endl;
}


}
