#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "MakeIP/makeip.h"
#include <comparator/comparator.h>

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

int main(int , char const **)
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;
        std::vector<std::string> BigVec;
        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
            BigVec.push_back(v.at(0));
            //std::cout<<"line="<<v.at(0)<<std::endl;
        }


        vector<string> ips = sortIPAddress(BigVec);
        for(std::string ip : ips)
            std::cout<<ip<<std::endl;
        //*
        for(auto ip : ips){
            const size_t index_dot=ip.find(".");
            //std::cout<<"idot="<<index_dot<<std::endl;
            if(index_dot == 1 && ip[0] == '1') std::cout<<ip<<std::endl;
        }
        for(auto ip : ips){
            bool flag=true;
            int count=0;
            size_t start=0;
            while(count<2){
                const size_t end=ip.find(".");
                auto s=ip.substr(start,end);
                start=end+1;
                if(count == 0 && std::stoi(s) != 46) flag=false;
                if(count == 1 && std::stoi(s) != 70) flag=false;
                count++;
            }
            if(flag) std::cout<<ip<<std::endl;
        }
        for(auto ip : ips){
            bool flag=false;
            int count=0;
            size_t start=0;
            size_t end=0;
            while(count<3){
                end=ip.find( ".", start);
                auto s=ip.substr(start,end-start);
                //std::cout<<"#"<<count<<" s="<<s<<" start="
                //        <<start<<" e="<<end<<std::endl;
                start=end+1;
                if(std::stoi(s) == 46) flag=true;
                count++;
            }
            auto s=ip.substr(start,ip.size());
            //std::cout<<"ip="<<ip<<" s4="<<s<<std::endl;
            if(std::stoi(s) == 46) flag=true;
            if(flag) std::cout<<ip<<std::endl;
        }
        //*/


/*
        std::vector<unsigned int> ips;
        for(std::vector<std::vector<std::string> >::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
            ips.push_back(MakeIP((*ip)[0], (*ip)[1], (*ip)[2], (*ip)[3]));

        std::sort(ips.begin(),ips.end(), std::greater<unsigned int>());
        for(auto ip : ips) std::cout << MakeIP(ip) << std::endl;
        for(auto ip : ips)
            if( ((ip>>24)&0xFF) == 1) std::cout << MakeIP(ip) << std::endl;
        for(auto ip : ips)
            if( ((ip>>24)&0xFF) == 46 && ((ip>>16)&0xFF) == 70)
                std::cout << MakeIP(ip) << std::endl;
        for(auto ip : ips)
            if( ((ip>>24)&0xFF) == 46 || ((ip>>16)&0xFF) == 46 || ((ip>>8)&0xFF) == 46 || (ip&0xFF) == 46)
                std::cout << MakeIP(ip) << std::endl;
*/



        exit(0);


        // TODO reverse lexicographically sort

        for(std::vector<std::vector<std::string> >::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            for(std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

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
