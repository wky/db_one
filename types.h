#ifndef __TYPES__
#define __TYPES__

#define MAXLINE 8192
#define NAMELEN 256

enum DataType{
    CHAR,
    INT,
    LONG,
    FLOAT,
    DOUBLE,
    TEXT,
    UNKNOWN
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
