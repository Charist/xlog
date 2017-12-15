#pragma once

#include <string>
#include <Poco/DateTime.h>

namespace mstp {



class LogFile 
{

public:
    LogFile(const std::string dir, const std::string prefix);        
    ~LogFile();

    bool write2file(const void* data, int len);

    void close();
private:
    bool __openlogfile();

private:
    FILE* m_logFile;
    std::string m_dir;
    std::string m_prefix;

    Poco::DateTime m_openFileTime;
};
  

} /* namespace mstp */

