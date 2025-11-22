#pragma once
#include<string>
#include<map>

using String=std::string;
namespace csv {
class ReadCsv
{
public:
    void OpenCsv();
    bool IsTime();
private:
    std::map<int,String> ClassTime;
};
}