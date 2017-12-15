#pragma once

#include "EncryptInterface.h"

namespace mstp {

class EncryptLog : public EncryptInterface {
public:
    EncryptLog();
    ~EncryptLog();

    //外面释放内存
    virtual void encryptContent(const char* const pInData, size_t inputLen, char* pOutData, size_t& _output_len);

    //外面释放内存
    virtual void dencryptContent(const char* const pInData, size_t inputLen, char* pOutData, size_t& _output_len);
};

}  // namespace mstp


