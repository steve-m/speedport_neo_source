#ifndef _BASE64_H_
#define _BASE64_H_
#ifdef __cplusplus
extern "C" {
#endif
int B64_encode(char *source, char *destination, int size_source, int size_destination);
int B64_decode(char *source, char *destination, int size_source, int size_destination);
#ifdef __cplusplus
}
#endif
#endif
