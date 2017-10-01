//
// Created by zakrent on 10/1/17.
//

//serialization

#include "serialize.h"
#include "../misc/types.h"
namespace network {
    void serializeUInt64(char *buffer, uint64 value) {
        for (int i = 0; i < 8; ++i) {
            buffer[i] = (value >> i * 8) & 0xFF;
        }
    }

    void serializeInt(char *buffer, int value) {
        for (int i = 0; i < 4; ++i) {
            buffer[i] = (value >> i * 8) & 0xFF;
        }
    }

//modified version of https://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#serialization
    void serializeDouble(char *buffer, double value) {

        unsigned bits = 64;
        unsigned expbits = 11;
        double f = value;

        //
        long double fnorm;
        int shift;
        long long sign, exp, significand;
        unsigned significandbits = bits - expbits - 1; // -1 for sign bit

        if (f == 0.0) {
            serializeUInt64(buffer, (uint64) 0);
            return;
        } // get this special case out of the way

        // check sign and begin normalization
        if (f < 0) {
            sign = 1;
            fnorm = -f;
        }
        else {
            sign = 0;
            fnorm = f;
        }

        // get the normalized form of f and track the exponent
        shift = 0;
        while (fnorm >= 2.0) {
            fnorm /= 2.0;
            shift++;
        }
        while (fnorm < 1.0) {
            fnorm *= 2.0;
            shift--;
        }
        fnorm = fnorm - 1.0;

        // calculate the binary form (non-float) of the significand data
        significand = fnorm * ((1LL << significandbits) + 0.5f);

        // get the biased exponent
        exp = shift + ((1 << (expbits - 1)) - 1); // shift + bias
        //

        uint64 result = (sign << (bits - 1)) | (exp << (bits - expbits - 1)) | significand;
        serializeUInt64(buffer, result);
    }

    uint64 unserializeUInt64(char *data) {
        uint64 result = 0;
        for (int i = 0; i < 8; ++i) {
            result = result ^ ((data[i] << i * 8) & 0xFF);
        }
    }

    int unserializeInt(char *data) {
        uint64 result = 0;
        for (int i = 0; i < 4; ++i) {
            result = result ^ ((data[i] << i * 8) & 0xFF);
        }
    }

//modified version of https://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#serialization
    double unserializeDouble(char *data) {
        uint64 i = unserializeUInt64(data);

        unsigned bits = 64;
        unsigned expbits = 11;

        long double result;
        long long shift;
        unsigned bias;
        unsigned significandbits = bits - expbits - 1; // -1 for sign bit

        if (i == 0) return 0.0;

        // pull the significand
        result = (i & ((1LL << significandbits) - 1)); // mask
        result /= (1LL << significandbits); // convert back to float
        result += 1.0f; // add the one back on

        // deal with the exponent
        bias = (1 << (expbits - 1)) - 1;
        shift = ((i >> significandbits) & ((1LL << expbits) - 1)) - bias;
        while (shift > 0) {
            result *= 2.0;
            shift--;
        }
        while (shift < 0) {
            result /= 2.0;
            shift++;
        }

        // sign it
        result *= (i >> (bits - 1)) & 1 ? -1.0 : 1.0;

        return result;
    }
}
