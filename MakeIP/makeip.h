#pragma once

#include <string>

unsigned int MakeIP(std::string oct1, std::string oct2,
                    std::string oct3, std::string oct4);

std::string MakeIP(unsigned int ip);
