#ifndef __TYPES__
#define __TYPES__

#define MAXLINE 8192
#define NAMELEN 256
#define SHORTLEN 100

#define DT_UNKNOWN  0
#define DT_CHAR     1
#define DT_INT      2
#define DT_LONG     3
#define DT_FLOAT    4
#define DT_DOUBLE   5
#define DT_TEXT     6
#define DT_BOOL     7

#define NEED_FREE_MASK  0x100
/*
struct Bytes
{
    unsigned size;
    unsigned max_size;
    unsigned char *bytes;
};
*/
/*
struct Text
{
    /* length is in bytes 
    unsigned len;
    /* max_len is set by column recommendation or storage constraints 
    unsigned max_len;
    char *str;
};*/
#endif
