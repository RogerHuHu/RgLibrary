#ifndef _AES_H_
#define _AES_H_

#include <string.h>
#include "AESResource.h"

namespace cryption {

#define NB 4  //number of columns in the State & expanded key, AES only supports NB=4
#define NK 6  //number of columns in a key
#define NR 12  //number of rounds in encryption

/************************************************
 * \brief AES加密
 *************************************************/
class AES {
public:
    AES() {}
    ~AES() {}

    /************************************************
     * \brief 加密数据
     *
     * \param inText 待加密的数据
     * \param length 数据长度
     * \param key 密钥
     * \param outText 加密后的数据
     *************************************************/
    void Encrypt(unsigned char *inText, unsigned int length, unsigned char *key, unsigned char *outText);

    /************************************************
     * \brief 解密数据
     *
     * \param inText 待解密的数据
     * \param length 数据长度
     * \param key 密钥
     * \param outText 解密后的数据
     *************************************************/
    void Decrypt(unsigned char *inText, unsigned int length, unsigned char *key, unsigned char *outText);

private:
    void EncryptInt(unsigned char *inText, unsigned char *key, unsigned char *outText);
    void DecryptInt(unsigned char *inText, unsigned char *key, unsigned char *outText);
    void ShiftRows(unsigned char *state);
    void InvShiftRows(unsigned char *state);
    void MixSubColumns(unsigned char *state);
    void InvMixSubColumns(unsigned char *state);
    void AddRoundKey(unsigned *state, unsigned *key);
    void ExpandKey(unsigned char *key, unsigned char *expKey);
};

}
#endif // _AES_H_
