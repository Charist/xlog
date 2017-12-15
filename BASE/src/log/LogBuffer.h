
#pragma once

#include "log/EncryptLog.h"
#include "utility/autobuffer.h"
#include "utility/ptrbuffer.h"
#include <memory>

using namespace mstp;

namespace mstp {

class LogBuffer
{
public:
    LogBuffer(void* _pbuffer, size_t _len, bool _is_compress);
    ~LogBuffer();

public:
    static bool OutputBuffer(const void* _data, size_t _inputlen, void* _output, size_t& _len);

public:
    PtrBuffer& GetData();

    void Flush(AutoBuffer& _buff);
    bool Write(const void* _data, size_t _length);

private:

    bool __Reset();
    void __Flush();
    void __Clear();

    void __Fix();

private:
    PtrBuffer buff_;
    bool is_compress_;
    //z_stream cstream_;

    static std::shared_ptr<EncryptInterface> s_log_crypt;
};


} /* namespace mstp */

