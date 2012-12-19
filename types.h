#ifndef __TYPES__
#define __TYPES__
enum DataType{
    CHAR,
    INT,
    LONG,
    FLOAT,
    DOUBLE,
    TEXT
};
/*
struct Bytes
{
    unsigned size;
    unsigned max_size;
    unsigned char *bytes;
};
*/
struct Text
{
    /* length is in bytes */
    unsigned len;
    /* max_len is set by column recommendation or storage constraints */
    unsigned max_len;
    char *str;
};
#endif
