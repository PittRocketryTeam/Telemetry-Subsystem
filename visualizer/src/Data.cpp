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


void Data::getHealthpacket()
{
    
}

void Data::getOrientationPacket()
{

}

void Data::readData(std::string path)
{
    std::string packet; 
     std::cout << "DID324" << std::endl; 
    // Read from the text file
    std::ifstream MyReadFile(path);

    // Use a while loop together with the getline() function to read the file line by line
    while (std::getline(MyReadFile, packet)) {
        // Output the text from the file
        data.push(packet);
    }

    // Close the file
    MyReadFile.close();

    std::cout << isEmpty() << std::endl; 
}

bool Data::isEmpty()
{
    return data.empty(); 
}

void Data::pollData()
{
    if(!isEmpty())
    {
        std::cout << data.front() << std::endl; 
        data.pop(); //Remove front item 
    }
    else
    {
        std::cout << "Queue is empty." << std::endl; 
    }
}


}
