#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "MakeIP/makeip.h"
#include <comparator/comparator.h>

#include <tuple>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


std::vector<std::vector<std::string> > ip_pool;

template <typename T>
void filter(T atuple)
{
    const size_t tupsize=std::tuple_size<decltype(atuple)>::value;
    if(tupsize == 0 || tupsize > 4) throw("Wrong size of input tuple!");

    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        bool flag=false;
        if(std::stoi(*(ip->cbegin()+=0)) == std::get<0>(atuple) &&
           std::get<0>(atuple) != 0)
            flag=true;
        else if(std::get<0>(atuple) != 0) continue;
        if(std::stoi(*(ip->cbegin()+=1)) == std::get<1>(atuple) &&
           std::get<1>(atuple) != 0)
            flag=true;
        else if(std::get<1>(atuple) != 0) continue;
        if(std::stoi(*(ip->cbegin()+=2)) == std::get<2>(atuple) &&
           std::get<2>(atuple) != 0)
            flag=true;
        else if(std::get<2>(atuple) != 0) continue;
        if(std::stoi(*(ip->cbegin()+=3)) == std::get<3>(atuple) &&
           std::get<3>(atuple) != 0)
            flag=true;
        else if(std::get<3>(atuple) != 0) continue;


        if(flag)
        {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
    }
}

void filter_any(int x)
{
    if(x < 0 || x > 255) throw("Wrong value of IP octet!");

    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        bool flag=false;
        for(int j=0; j<4; ++j) if( std::stoi(*(ip->cbegin()+=j)) == x ) flag=true;

        if(flag)
        {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
    }
}

int main(int, char const **)
{
    try
    {
        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(),[](std::vector<std::string> a, std::vector<std::string> b) -> bool{
            if(a == b) return false;
            for(int i=0; i<4; ++i){
                if(std::stoi(a[i]) < std::stoi(b[i])) return false;
                else if(std::stoi(a[i]) > std::stoi(b[i])) return true;
            }
            return false;
        });

        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

        // TODO filter by first byte and output
        // ip = filter(1)
        filter(std::make_tuple(1, 0, 0, 0));
        /*
        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            if(std::stoi(*ip->cbegin()) == 1)
            {
                for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
                {
                    if (ip_part != ip->cbegin())
                    {
                        std::cout << ".";
                    }
                    std::cout << *ip_part;
                }
                std::cout << std::endl;
            }
        }
        */
        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        filter(std::make_tuple(46, 70, 0, 0));
        /*
        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            if(std::stoi(*ip->cbegin()) == 46 && std::stoi(*(ip->cbegin()+=1)) == 70)
            {
                for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
                {
                    if (ip_part != ip->cbegin())
                    {
                        std::cout << ".";
                    }
                    std::cout << *ip_part;
                }
                std::cout << std::endl;
            }
        }*/
        // TODO filter by any byte and output
        // ip = filter_any(46)
        filter_any(46);
        /*
        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            if(std::stoi(*ip->cbegin()) == 46 || std::stoi(*(ip->cbegin()+=1)) == 46 || std::stoi(*(ip->cbegin()+=2)) == 46 || std::stoi(*(ip->cbegin()+=3)) == 46
            )
            {
                for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
                {
                    if (ip_part != ip->cbegin())
                    {
                        std::cout << ".";
                    }
                    std::cout << *ip_part;
                }
                std::cout << std::endl;
            }
        }
        */


        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
