#include "AES.h"

namespace cryption {

void AES::ShiftRows(unsigned char *state) {
    unsigned char tmp;

    // just substitute row 0
    state[0] = sbox[state[0]], state[4] = sbox[state[4]];
    state[8] = sbox[state[8]], state[12] = sbox[state[12]];

    // rotate row 1
    tmp = sbox[state[1]], state[1] = sbox[state[5]];
    state[5] = sbox[state[9]], state[9] = sbox[state[13]], state[13] = tmp;

    // rotate row 2
    tmp = sbox[state[2]], state[2] = sbox[state[10]], state[10] = tmp;
    tmp = sbox[state[6]], state[6] = sbox[state[14]], state[14] = tmp;

    // rotate row 3
    tmp = sbox[state[15]], state[15] = sbox[state[11]];
    state[11] = sbox[state[7]], state[7] = sbox[state[3]], state[3] = tmp;
}

void AES::InvShiftRows(unsigned char *state) {
    unsigned char tmp;

    // restore row 0
    state[0] = invSbox[state[0]], state[4] = invSbox[state[4]];
    state[8] = invSbox[state[8]], state[12] = invSbox[state[12]];

    // restore row 1
    tmp = invSbox[state[13]], state[13] = invSbox[state[9]];
    state[9] = invSbox[state[5]], state[5] = invSbox[state[1]], state[1] = tmp;

    // restore row 2
    tmp = invSbox[state[2]], state[2] = invSbox[state[10]], state[10] = tmp;
    tmp = invSbox[state[6]], state[6] = invSbox[state[14]], state[14] = tmp;

    // restore row 3
    tmp = invSbox[state[3]], state[3] = invSbox[state[7]];
    state[7] = invSbox[state[11]], state[11] = invSbox[state[15]], state[15] = tmp;
}

/*
 * recombine and mix each row in a column
 */
void AES::MixSubColumns(unsigned char *state) {
    unsigned char nextState[4 * NB];

    // mixing column 0
    nextState[0] = xtime2Sbox[state[0]] ^ xtime3Sbox[state[5]] ^ sbox[state[10]] ^ sbox[state[15]];
    nextState[1] = sbox[state[0]] ^ xtime2Sbox[state[5]] ^ xtime3Sbox[state[10]] ^ sbox[state[15]];
    nextState[2] = sbox[state[0]] ^ sbox[state[5]] ^ xtime2Sbox[state[10]] ^ xtime3Sbox[state[15]];
    nextState[3] = xtime3Sbox[state[0]] ^ sbox[state[5]] ^ sbox[state[10]] ^ xtime2Sbox[state[15]];

    // mixing column 1
    nextState[4] = xtime2Sbox[state[4]] ^ xtime3Sbox[state[9]] ^ sbox[state[14]] ^ sbox[state[3]];
    nextState[5] = sbox[state[4]] ^ xtime2Sbox[state[9]] ^ xtime3Sbox[state[14]] ^ sbox[state[3]];
    nextState[6] = sbox[state[4]] ^ sbox[state[9]] ^ xtime2Sbox[state[14]] ^ xtime3Sbox[state[3]];
    nextState[7] = xtime3Sbox[state[4]] ^ sbox[state[9]] ^ sbox[state[14]] ^ xtime2Sbox[state[3]];

    // mixing column 2
    nextState[8] = xtime2Sbox[state[8]] ^ xtime3Sbox[state[13]] ^ sbox[state[2]] ^ sbox[state[7]];
    nextState[9] = sbox[state[8]] ^ xtime2Sbox[state[13]] ^ xtime3Sbox[state[2]] ^ sbox[state[7]];
    nextState[10] = sbox[state[8]] ^ sbox[state[13]] ^ xtime2Sbox[state[2]] ^ xtime3Sbox[state[7]];
    nextState[11] = xtime3Sbox[state[8]] ^ sbox[state[13]] ^ sbox[state[2]] ^ xtime2Sbox[state[7]];

    // mixing column 3
    nextState[12] = xtime2Sbox[state[12]] ^ xtime3Sbox[state[1]] ^ sbox[state[6]] ^ sbox[state[11]];
    nextState[13] = sbox[state[12]] ^ xtime2Sbox[state[1]] ^ xtime3Sbox[state[6]] ^ sbox[state[11]];
    nextState[14] = sbox[state[12]] ^ sbox[state[1]] ^ xtime2Sbox[state[6]] ^ xtime3Sbox[state[11]];
    nextState[15] = xtime3Sbox[state[12]] ^ sbox[state[1]] ^ sbox[state[6]] ^ xtime2Sbox[state[11]];

    for(unsigned char j = 0; j < sizeof(nextState); j++)
        *(state + j) = *(nextState + j);
}

/*
 * restore and un-mix each row in a column
 */
void AES::InvMixSubColumns(unsigned char *state) {
    unsigned char nextState[4 * NB];

    // restore column 0
    nextState[0] = xtimeE[state[0]] ^ xtimeB[state[1]] ^ xtimeD[state[2]] ^ xtime9[state[3]];
    nextState[5] = xtime9[state[0]] ^ xtimeE[state[1]] ^ xtimeB[state[2]] ^ xtimeD[state[3]];
    nextState[10] = xtimeD[state[0]] ^ xtime9[state[1]] ^ xtimeE[state[2]] ^ xtimeB[state[3]];
    nextState[15] = xtimeB[state[0]] ^ xtimeD[state[1]] ^ xtime9[state[2]] ^ xtimeE[state[3]];

    // restore column 1
    nextState[4] = xtimeE[state[4]] ^ xtimeB[state[5]] ^ xtimeD[state[6]] ^ xtime9[state[7]];
    nextState[9] = xtime9[state[4]] ^ xtimeE[state[5]] ^ xtimeB[state[6]] ^ xtimeD[state[7]];
    nextState[14] = xtimeD[state[4]] ^ xtime9[state[5]] ^ xtimeE[state[6]] ^ xtimeB[state[7]];
    nextState[3] = xtimeB[state[4]] ^ xtimeD[state[5]] ^ xtime9[state[6]] ^ xtimeE[state[7]];

    // restore column 2
    nextState[8] = xtimeE[state[8]] ^ xtimeB[state[9]] ^ xtimeD[state[10]] ^ xtime9[state[11]];
    nextState[13] = xtime9[state[8]] ^ xtimeE[state[9]] ^ xtimeB[state[10]] ^ xtimeD[state[11]];
    nextState[2] = xtimeD[state[8]] ^ xtime9[state[9]] ^ xtimeE[state[10]] ^ xtimeB[state[11]];
    nextState[7] = xtimeB[state[8]] ^ xtimeD[state[9]] ^ xtime9[state[10]] ^ xtimeE[state[11]];

    // restore column 3
    nextState[12] = xtimeE[state[12]] ^ xtimeB[state[13]] ^ xtimeD[state[14]] ^ xtime9[state[15]];
    nextState[1] = xtime9[state[12]] ^ xtimeE[state[13]] ^ xtimeB[state[14]] ^ xtimeD[state[15]];
    nextState[6] = xtimeD[state[12]] ^ xtime9[state[13]] ^ xtimeE[state[14]] ^ xtimeB[state[15]];
    nextState[11] = xtimeB[state[12]] ^ xtimeD[state[13]] ^ xtime9[state[14]] ^ xtimeE[state[15]];

    for(int i = 0; i < 4 * NB; i++)
        state[i] = invSbox[nextState[i]];
}

void AES::AddRoundKey(unsigned *state, unsigned *key) {
    for(int i = 0; i < 4; i++)
        state[i] ^= key[i];
}

/*
 * produce NK bytes for each round
 */
void AES::ExpandKey(unsigned char *key, unsigned char *expKey) {
    unsigned char tmp0, tmp1, tmp2, tmp3, tmp4;
    unsigned idx;

    for(idx = 0; idx < NK; idx++) {
        expKey[4 * idx + 0] = key[4 * idx + 0];
        expKey[4 * idx + 1] = key[4 * idx + 1];
        expKey[4 * idx + 2] = key[4 * idx + 2];
        expKey[4 * idx + 3] = key[4 * idx + 3];
    }

    for(idx = NK; idx < NB * (NR + 1); idx++) {
        tmp0 = expKey[4 * idx - 4];
        tmp1 = expKey[4 * idx - 3];
        tmp2 = expKey[4 * idx - 2];
        tmp3 = expKey[4 * idx - 1];
        if(!(idx % NK)) {
            tmp4 = tmp3;
            tmp3 = sbox[tmp0];
            tmp0 = sbox[tmp1] ^ rcon[idx / NK];
            tmp1 = sbox[tmp2];
            tmp2 = sbox[tmp4];
        }

        //  convert from longs to bytes
        expKey[4 * idx + 0] = expKey[4 * idx - 4 * NK + 0] ^ tmp0;
        expKey[4 * idx + 1] = expKey[4 * idx - 4 * NK + 1] ^ tmp1;
        expKey[4 * idx + 2] = expKey[4 * idx - 4 * NK + 2] ^ tmp2;
        expKey[4 * idx + 3] = expKey[4 * idx - 4 * NK + 3] ^ tmp3;
    }
}

/*
 * 加密数据
 */
void AES::Encrypt(unsigned char *inText, unsigned int length, unsigned char *key, unsigned char *outText) {
    if(length <= 16) {
        EncryptInt(inText, key, outText);
    }
    else {
        int round = length / 16 + (length % 16 == 0 ? 0 : 1);
        unsigned char tmpInput[16];
        unsigned char tmpOutput[16];
        for(int i = 0; i < round; i++) {
            memcpy(tmpInput, inText + i * 16, 16);
            EncryptInt(tmpInput, key, tmpOutput);
            memcpy(outText + i * 16, tmpOutput, 16);
        }
    }
}

/*
 * 解密数据
 */
void AES::Decrypt(unsigned char *inText, unsigned int length, unsigned char *key, unsigned char *outText) {
    if(length <= 16) {
        DecryptInt(inText, key, outText);
    }
    else {
        int round = length / 16 + (length % 16 == 0 ? 0 : 1);
        unsigned char tmpInput[16];
        unsigned char tmpOutput[16];
        for(int i = 0; i < round; i++) {
            memcpy(tmpInput, inText + i * 16, 16);
            DecryptInt(tmpInput, key, tmpOutput);
            memcpy(outText + i * 16, tmpOutput, 16);
        }
    }
}

/*
 * encrypt one 128 bit block
 */
void AES::EncryptInt (unsigned char *inText, unsigned char *key, unsigned char *outText) {
    unsigned round, idx;
    unsigned char state[NB * 4];
    unsigned char expKey[4 * NB * ( NR + 1)];
    ExpandKey(key, expKey);

    for(idx = 0; idx < NB; idx++) {
        state[4 * idx + 0] = *inText++;
        state[4 * idx + 1] = *inText++;
        state[4 * idx + 2] = *inText++;
        state[4 * idx + 3] = *inText++;
    }

    AddRoundKey((unsigned *)state, (unsigned *)expKey);

    for(round = 1; round < NR + 1; round++) {
        if(round < NR)
            MixSubColumns(state);
        else
            ShiftRows(state);
        AddRoundKey((unsigned *)state, (unsigned *)expKey + round * NB);
    }

    for(idx = 0; idx < NB; idx++) {
        *outText++ = state[4 * idx + 0];
        *outText++ = state[4 * idx + 1];
        *outText++ = state[4 * idx + 2];
        *outText++ = state[4 * idx + 3];
    }
}

void AES::DecryptInt(unsigned char *inText, unsigned char *key, unsigned char *outText) {
    unsigned idx, round;
    unsigned char state[NB * 4];
    unsigned char expKey[4 * NB * (NR + 1)];
    ExpandKey(key, expKey);
    for(idx = 0; idx < NB; idx++) {
        state[4 * idx + 0] = *inText++;
        state[4 * idx + 1] = *inText++;
        state[4 * idx + 2] = *inText++;
        state[4 * idx + 3] = *inText++;
    }

    AddRoundKey((unsigned *)state, (unsigned *)expKey + NR * NB);
    round = NR;

    InvShiftRows(state);

    while(round--) {
        AddRoundKey((unsigned *)state, (unsigned *)expKey + round * NB);
        if(round) InvMixSubColumns(state);
    }

    for(idx = 0; idx < NB; idx++) {
        *outText++ = state[4 * idx + 0];
        *outText++ = state[4 * idx + 1];
        *outText++ = state[4 * idx + 2];
        *outText++ = state[4 * idx + 3];
    }
}

}
