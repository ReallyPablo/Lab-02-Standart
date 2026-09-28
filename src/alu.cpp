#include "alu.hpp"

static void update_zn(Byte res, Flags& f) {
    f.z = (res == 0);
    f.n = (res & 0x80) != 0; 
}

Byte alu_add(Byte a, Byte b, Flags& f) {
    uint16_t sum = (uint16_t)a + (uint16_t)b;
    Byte res = (Byte)sum;
    f.c = (sum > 255);
    update_zn(res, f);
    return res;
}

Byte alu_sub(Byte a, Byte b, Flags& f) {
    f.c = (a < b); 
    Byte res = a - b;
    update_zn(res, f);
    return res;
}

Byte alu_and(Byte a, Byte b, Flags& f) {
    Byte res = a & b;
    f.c = false;
    update_zn(res, f);
    return res;
}

Byte alu_or(Byte a, Byte b, Flags& f) {
    Byte res = a | b;
    f.c = false;
    update_zn(res, f);
    return res;
}

Byte alu_xor(Byte a, Byte b, Flags& f) {
    Byte res = a ^ b;
    f.c = false;
    update_zn(res, f);
    return res;
}

Byte alu_not(Byte a, Flags& f) {
    Byte res = ~a;
    f.c = false;
    update_zn(res, f);
    return res;
}

Byte alu_shl(Byte a, Flags& f) {
    f.c = (a & 0x80) != 0; 
    Byte res = a << 1;
    update_zn(res, f);
    return res;
}

Byte alu_shr(Byte a, Flags& f) {
    f.c = (a & 0x01) != 0; 
    Byte res = a >> 1;
    update_zn(res, f);
    return res;
}

Byte alu_inc(Byte a, Flags& f) {
    Byte res = a + 1;
    update_zn(res, f);
    return res;
}

Byte alu_dec(Byte a, Flags& f) {
    Byte res = a - 1;
    update_zn(res, f);
    return res;
}