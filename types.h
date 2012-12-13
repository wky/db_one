#ifndef __TYPES__
#define __TYPES__
enum DataType{
    UI8,
    I8,
    UI32,
    I32,
    UI64,
    I64,
    F32,
    F64,
    BYTES,
    STRING
};
struct Bytes
{
    int size;
    unsigned char *bytes;
};
struct String
{
    int len;
    char *str;
};
#endif
