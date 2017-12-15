#include "log/EncryptLog.h"
#include <string.h>

namespace mstp {


EncryptLog::EncryptLog()
{
    
}

EncryptLog::~EncryptLog()
{

}

void EncryptLog::encryptContent(const char* const pInData, size_t inputLen, char* pOutData, size_t& _output_len)
{
    size_t copyLen = inputLen;
    if (_output_len < inputLen)
    {
        //error
        copyLen = _output_len;
    }
    memcpy(pOutData, pInData, copyLen);
    _output_len = copyLen;
}

void EncryptLog::dencryptContent(const char* const pInData, size_t inputLen, char* pOutData, size_t& _output_len)
{

}


}  // namespace mstp
