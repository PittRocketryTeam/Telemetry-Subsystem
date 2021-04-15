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

    //Ignore file header (first line in .csv file)
    std::getline(MyReadFile, packet);

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
        std::vector<float> packet; 
        
        std::stringstream s(data.front()); 
        std::string val; 
        while(std::getline(s, val, ','))
        {
            try{
                packet.push_back(stof(val)); 
            }
            catch (std::exception& e)
            { 
                    //If stof fails due to bad input, look at csv file encoding.(i.e. UTF-8 works)
                    std::cout << "Yikes if this prints" << std::endl; 
            }
        }
        data.pop(); 
        return packet; 
    }
    std::cout << "Queue is empty." << std::endl;
}


}
