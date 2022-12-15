#ifndef SC_SJCL
#define SC_SJCL
#include <openssl/x509.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>

int sc_sjcl_md5(char*in,unsigned char*out,unsigned int* outlen);
int sc_sjcl_decrypt(unsigned char* password,unsigned char* ct,unsigned char* pt);
int sc_sjcl_encrypt(unsigned char* password,unsigned char* pt,unsigned char* ct);
int sc_rand_get(unsigned char* para ,int len);
int sc_PKCS5_PBKDF2_HMAC_SHA1(unsigned char *pass, int passlen,
                           const unsigned char *salt, int saltlen, int iter,
                           int keylen, unsigned char *out);
#endif
