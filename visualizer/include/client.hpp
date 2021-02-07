#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector>

class Client
{
public:
    static void connect();
    static void disconnect();
    static std::vector<float> getPacket();
};

#endif /* CLIENT_HPP */