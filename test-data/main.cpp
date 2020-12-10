#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cmath>

class Packet
{
public:
    Packet();
    virtual ~Packet();

    virtual void gendata(unsigned int) = 0;
    virtual std::string csv() = 0;

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
    virtual ~HealthPacket();

    virtual void gendata(unsigned int);
    virtual std::string csv();

    int vbat;
    int vr5;
    int vr3;
    int tbat;
    int amps;
};

HealthPacket::HealthPacket() :
    Packet()
{
    id = 1;
}

HealthPacket::~HealthPacket()
{

}

void HealthPacket::gendata(unsigned int t)
{
    float s = (float)t / 1000.f;
    vbat = (int)roundf(1024.f * sinf(s));
    vr5 = (int)roundf(1024.f * sinf(s));
    vr3 = (int)roundf(1024.f * sinf(s));
    tbat = (int)roundf(1024.f * sinf(s));
    amps = (int)roundf(1024.f * sinf(s));
}

std::string HealthPacket::csv()
{
    std::stringstream ss;

    ss << id << "," << vbat << "," << vr5 << "," << vr3 << "," << tbat << "," << amps;

    return ss.str();
}

class OrientationPacket: public Packet
{
public:
    OrientationPacket();
    virtual ~OrientationPacket();

    virtual void gendata(unsigned int);
    virtual std::string csv();

    glm::vec3 accel;
    float vy;
    float alt;
    glm::vec3 omega;
    glm::quat quat;
};

OrientationPacket::OrientationPacket() :
    Packet()
{
    id = 2;
}

OrientationPacket::~OrientationPacket()
{

}

void OrientationPacket::gendata(unsigned int t)
{
    float s = (float)t / 1000.f;

    accel.y = -9.8f;
    vy = 10000 + accel.y * s;
    alt = vy * s;
    omega.y = sinf(s);

    quat = glm::angleAxis(glm::degrees(10.f * s), glm::vec3(0, 1, 0));
}

std::string OrientationPacket::csv()
{
    std::stringstream ss;

    ss << id << "," << accel.x << "," << accel.y << "," << accel.z << "," <<
            vy << "," << alt << "," <<
            omega.x << "," << omega.y << "," << omega.z << "," <<
            quat.w << "," << quat.x << "," << quat.y << "," << quat.z;

    return ss.str();
}

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

    int seconds = atoi(argv[1]);
    OrientationPacket op;
    HealthPacket hp;

    std::ofstream out("./data.csv");

    for (int i = 0; i < seconds * 1000; ++i)
    {
        hp.gendata(i);
        op.gendata(i);
        out << hp.csv() << "\n";
        out << op.csv() << "\n";
    }

    return 0;
}
