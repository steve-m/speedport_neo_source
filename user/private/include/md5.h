#ifndef	__INCmd5h
#define	__INCmd5h

#ifndef A_UINT32
#define A_UINT32 	unsigned long
#endif

struct MD5Context {
        A_UINT32 buf[4];
        A_UINT32 bits[2];
        unsigned char in[64];
};

void MD5Init();
void MD5Update();
void MD5Final();
void MD5Transform();
void md5_calc(unsigned char *output, unsigned char *input, unsigned int inlen);
void md5_hex_str(char *output, unsigned char *input, int inlen);

void generate_wepkey(unsigned char type, char *s, unsigned char *key);

typedef struct MD5Context MD5_CTX;

#endif /* __INCmd5h */
