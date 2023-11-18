#include <MakeIP/makeip.h>

unsigned int MakeIP(std::string oct1, std::string oct2,
                    std::string oct3, std::string oct4)
{
    unsigned int _3 = std::stoi(oct1);
    unsigned int _2 = std::stoi(oct2);
    unsigned int _1 = std::stoi(oct3);
    unsigned int _0 = std::stoi(oct4);
    unsigned int ip=_3 << 24 | _2 << 16 | _1 << 8 | _0;
    return ip;
}

std::string MakeIP(unsigned int ip)
{
    std::string ip_address=std::to_string(  ((ip>>24)&0xFF) ) + "." +
                           std::to_string(  ((ip>>16)&0xFF) ) + "." +
                           std::to_string(  ((ip>>8)&0xFF ) ) + "." +
                           std::to_string(    ip&0xFF );
    return ip_address;
}
