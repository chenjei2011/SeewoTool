#include<fstream>
#include"csv.h"
#include<iostream>
#include<windows.h>


namespace csv
{
    void ReadCsv::OpenCsv()
    {
        std::fstream CsvPath;
        //抛出异常
        CsvPath.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            CsvPath.open("ClassTime.csv",std::ios::in);
        }
        catch(const std::ios_base::failure& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        for(int i=0;i<9;++i)
        {
            std::getline(CsvPath,ClassTime[i]);
            
        }
    }

    bool ReadCsv::IsTime()
    {
        SYSTEMTIME sysTime;
        GetLocalTime(&sysTime);
        String TimeHour=std::to_string(sysTime.wHour);
        String TimeMin=std::to_string(sysTime.wMinute);
        
        return false;
    }
}