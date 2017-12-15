
#include "log/LogBuffer.h"

#include <cstdio>
#include <time.h>
#include <algorithm>
//#include <sys/time.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#ifdef WIN32
#define snprintf _snprintf
#endif


namespace mstp {

static const int kOneLogBuffSize = 2048;

std::shared_ptr<EncryptInterface> LogBuffer::s_log_crypt = nullptr;

LogBuffer::LogBuffer(void* _pbuffer, size_t _len, bool _isCompress) : is_compress_(_isCompress) {
    buff_.Attach(_pbuffer, 0, _len);
    s_log_crypt = std::shared_ptr<EncryptLog>(new EncryptLog());
    //memset(&cstream_, 0, sizeof(cstream_));
}

LogBuffer::~LogBuffer() {
   /* if (Z_NULL != cstream_.state) {
        deflateEnd(&cstream_);
    }*/
}

bool LogBuffer::OutputBuffer(const void* _data, size_t _inputlen, void* _output, size_t& _len) {
    if (NULL == _data || NULL == _output || 0 == _inputlen) {
        return false;
    }
    s_log_crypt->encryptContent((char*)_data, _inputlen, (char*)_output, _len);

    return true;
}

PtrBuffer& LogBuffer::GetData() {
    return buff_;
}

void LogBuffer::Flush(AutoBuffer& _buff) {
    /*if (Z_NULL != cstream_.state) {
        deflateEnd(&cstream_);
    }

    if (s_log_crypt->GetLogLen((char*)buff_.Ptr(), buff_.Length()) == 0){
        __Clear();
        return;
    }
*/
    if (buff_.Length() <= 0)
    {
        return;
    }

    _buff.Write(buff_.Ptr(), buff_.Length());
    __Clear();
}


bool LogBuffer::Write(const void* _data, size_t _length) {
    if (NULL == _data || 0 == _length) {
        return false;
    }

    if (buff_.Length() == 0) {
        if (!__Reset()) return false;
    }


    /*if (is_compress_) {
    cstream_.avail_in = (uInt)_length;
    cstream_.next_in = (Bytef*)_data;

    uInt avail_out = (uInt)(buff_.MaxLength() - buff_.Length());
    cstream_.next_out = (Bytef*)buff_.PosPtr();
    cstream_.avail_out = avail_out;

    if (Z_OK != deflate(&cstream_, Z_SYNC_FLUSH)) {
    return false;
    }

    write_len = avail_out - cstream_.avail_out;
    } else {
    buff_.Write(_data, _length);
    }*/

  

    // compress

    // encrypt  

    size_t before_len = buff_.Length();
    size_t crypt_buffer_len = buff_.MaxLength() - before_len; //buf 剩余的最大长度

    s_log_crypt->encryptContent((char*)_data , _length, (char*)buff_.Ptr() + before_len, crypt_buffer_len);
    buff_.Length(crypt_buffer_len + before_len, crypt_buffer_len + before_len);

    return true;
}

bool LogBuffer::__Reset() {

    __Clear();

   /* if (is_compress_) {
        cstream_.zalloc = Z_NULL;
        cstream_.zfree = Z_NULL;
        cstream_.opaque = Z_NULL;

        if (Z_OK != deflateInit2(&cstream_, Z_BEST_COMPRESSION, Z_DEFLATED, -MAX_WBITS, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY)) {
            return false;
        }

    }*/

    return true;
}


void LogBuffer::__Clear() {
    memset(buff_.Ptr(), 0, buff_.MaxLength());
    buff_.Length(0, 0);
}




} /* namespace mstp */

