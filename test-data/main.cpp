#include <iostream>
#include <fstream>
#include <string>
#include <glm/glm.hpp>
#include <cmath>

class Packet
{
public:
    Packet();
    ~Packet();

    int id;
};

Packet::Packet()
{
    id = 0;
}

Packet::~Packet()
{

}

class HealthPacket : public Packet
{
public:
    HealthPacket();
    ~HealthPacket();

    int vbat;
    int vr5;
    int vr3;
    int tbat;
    int amps;
};

class OrientationPacket: public Packet
{
public:
    OrientationPacket();
    ~OrientationPacket();
};

void print_usage()
{
    std::cout << "usage: ./td <amt of data>" << std::endl;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        print_usage();
        return 0;
    }
    return 0;
}
