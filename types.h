#ifndef __TYPES__
#define __TYPES__

#define MAXLINE 8192
#define NAMELEN 256
#define SHORTLEN 100

#define DT_UNKNOWN  0
#define DT_CHAR     1
#define DT_INT      2
#define DT_LONG     4
#define DT_FLOAT    8
#define DT_DOUBLE   16
#define DT_TEXT     32
#define DT_BOOL     64


#define NEED_FREE_MASK  256

union DataUnion{
    bool b;
    char c;
    int i;
    long l;
    float f;
    double d;
    char *s;
};

const char *GET_TYPE_NAME(int);
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
     length is in bytes 
    unsigned len;
     max_len is set by column recommendation or storage constraints 
    unsigned max_len;
    char *str;
};*/
#endif
