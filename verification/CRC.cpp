#include "CRC.h"

namespace verification {

/*
 * 用于得到相应的CRC校验码
 */
unsigned int CRC::GetCRC(unsigned char *_buf, unsigned int _len) {
    unsigned char index;
    unsigned char crcHigh, crcLow;

    //_buf为数组首地址，len为数据长度
    crcHigh = 0xFF;
    crcLow = 0xFF;

    for(unsigned int i = 0; i < _len; i++) {
        index = crcHigh ^ (_buf[i]);
        crcHigh = crcLow ^ TABLE_CRCHi[index];
        crcLow = TABLE_CRCLo[index];
    }

    return (crcHigh <<8 ) | crcLow;
}

}
