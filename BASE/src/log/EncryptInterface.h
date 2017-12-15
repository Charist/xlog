#pragma once
#include <stdlib.h>

namespace mstp {


class EncryptInterface {
public:
    virtual ~EncryptInterface() { }

    //外面释放内存
    virtual void encryptContent(const char* const pInData, size_t inputLen, char* pOutData, size_t& _output_len) = 0;

    //外面释放内存
    virtual void dencryptContent(const char* const pInData, size_t inputLen, char* pOutData, size_t& _output_len) = 0;

};

}  // namespace mstp

