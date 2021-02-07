#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector>

class Client
{
public:
    static void con();
    static void disconnect(int);
    static std::vector<float> getPacket();
};

#endif /* CLIENT_HPP */