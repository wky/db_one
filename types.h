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

static char types[][10] = {"Unknown", "Char", "Int", "Long", "Float", "Double", "Text", "Bool"};

static char *GET_TYPE_NAME(int t) {
    switch (t & ~NEED_FREE_MASK){
        case DT_UNKNOWN:    return types[0];
        case DT_CHAR:       return types[1];
        case DT_INT:        return types[2];
        case DT_LONG:       return types[3];
        case DT_FLOAT:      return types[4];
        case DT_DOUBLE:     return types[5];
        case DT_TEXT:       return types[6];
        case DT_BOOL:       return types[7];
        default:            return 0;
    }
}

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
