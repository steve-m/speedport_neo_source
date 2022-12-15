/* crypto/crypto.h */

#ifndef HEADER_SC_CRYPTO_H
#define HEADER_SC_CRYPTO_H

#ifdef _SC_BUILD_
#include <openssl/e_os2.h>

#include <stdlib.h>
#include <string.h>

#include <openssl/ssl.h>
#include <openssl/pem.h>
#include <openssl/ossl_typ.h>

extern int tr64_pem_flag;
extern int tr69_pem_flag;

static char tr64_passphase1[]={"DTW724VR I"};
static char tr69_passphase1[]={"Zertifikatsm"};

static char tr69_rsa_header[]=
{"Proc-Type: 4,ENCRYPTED\n\
DEK-Info: DES-EDE3-CBC,6B3B74BE030FFC8B\n\
"};
static char tr69_rsa_key_phase[]=
{"lvcDaRic5h/SJASF8TipsR2TkYOyfv8sCXpglji9PH2iWqIaaZc3fNts+8lKEHQD\n\
ZwIre/Rpo9iMQKHSetL3z1bWyZ9VC0gjT/58m/O9qZZ8vB72tLMYwFpEtCzMNvDl\n\
4025rWLyEuib52GxQjoY/RlSacPf0X+qWfq3lXWV8E12EmXY2ET9nHxSF2n3gQz6\n\
uOQxvcBCywd0OBCyzXsbu2DkQ1lBotENNOQcB7zGSgToJemSquYQvklD4uB8qdY4\n\
bsYQM/kMJzBAlwbXkfWuHZtRyRmZnB+kco50B3fWKp1JkdGV6idLwPac3L6nlyTk\n\
c04J2lcccCYoh7SI9eQstzEsTCM53d9M2M/+r3o7VQfTnIOYGPHtCDLiNK2udrzO\n\
3ugPfEc6m0ejHxA5XLhS+yA4udb7TyBCy9L02HoyNn08lBbF0mcQduVhL6kZQVgp\n\
klpmqL4gxyqLmWkdPTCclroftfKZN4clO/tvlkDu08n5kIvkS2TYSToRMZfQIWkS\n\
gy6TghbSPVLpsIvosVlY2D6p90gjDO9TpM/oD1icuxBbLM7XrwaE52ZCFvQHfr6S\n\
cYo0Pqa5uv6ZFMKT9Comd0AmeR7QaRMTV38cZZGv3TwgkEwvvjfGrGVlq6u+I6Ly\n\
aIA9xoZKYazJsZGw4em1rQFLil/7eUQTSbZiIzg7XrbzZPm9bUQ036k/ISYynOf4\n\
TABQLrfiHBJm+SVeUqk2B6ai205QzSHzEr+iEWFac5ui3kKEAlrXx8vOZ0T98He9\n\
Pb0yuB/of2/sCaES2gr460TeWUmOaEq2vmfUBy5Cxqhyjim2bET1KpstQ2gbuubI\n\
"};

static char tr64_rsa_header[]=
{"Proc-Type: 4,ENCRYPTED\n\
DEK-Info: DES-EDE3-CBC,5E9648CE6C773E57\n\
"};
static char tr64_rsa_key_phase[]=
{"0Tt/ntozxlXDNZl3tBxy609215ltUdFNaJ12tMz0eKmkjR1hkTRkJ6J9ZuN8uCEh\n\
gTcSK3Rs9LMr9VuUqGfMpfAYKje6Xq/J2s93FoNqJXCQiVE7/7OLwGZ4ln2EzwYi\n\
91DxxqDO0H2QI77XmY4IXKIHyumX4ngK0kGPhGxs9bf+EytFjgB9Xgk9dcxB3agC\n\
9n92TETNwfFpe1pM3EuHccaLi1DVXKWTDsQv+6YbMjrVpnpaHeiTeZmGlXubPpi3\n\
xqKMz9zc0d4BRk9mapAksBXp2kTjo9q6gS2JbtLY86O+ESdMMRYCXuFBV9pFmqXl\n\
T5vGIPdqtMY2VlZBsx8++h/ZIsNF+qKkkzblfKJ2N/1SfRMpc+dsJDJDijBbN21s\n\
jY05uIZ7AiIo4rOBAg8hy3/3hbQcwWxU6bPZ8JXwZAz9n7ChYExwHyLPNoS9rxEh\n\
76Mb/hGB0CwcKLfn4tvEpO560ZeupyelYiyrzgHIR9xMPVntonp3sjR/X2UIVu+0\n\
a8ke6JJMRt51CVtr71nGxUOCc8Nc/vBUhpMJ+TWoZNWQ+WgNUpsO2MQQ5q5BPugs\n\
Px5WuZAs8XkZFMouiwHDd/6ksn9dQom2nTwROOG5JP09hqGUs/17EPxTVHqzA5Fs\n\
oXyXiZYZh7z7FKKOM7wBC7vFOZKZ8ueaMzTv7ZUp+XfIPZjvOJyUCb8imZOPxMnU\n\
NU8v2FoWiR7jWEws7ROxbCGcr9LdrquIlcUaRiM4gBybRZnuyaTOKw0x3MYAYkqH\n\
xWAwXADq9eydQrdV2nLC7cB8pWKUiiKggXypPfwCbGAVI+3NHG++9L1x8tBCQYm/\n\
Un482Cjf7SziNkWj2fHEgcCdYYgUzEMLFEyEbtSXCfJGUxRPFEZgBOOp2if78V7a\n\
"};

static char tr69_rsa_key_phase2[]=
{"5e/fLIpznJ7anY0Zs8PLj3GE7e4vsxAWrIov4K7kMVQiYtD9pLdim92Jy1nlbsyI\n\
97BofjGy80Lj14tOawMomj5gQuQjsB3gfkptS2LxyNvPOULrSjnhZd9RhYugIEAH\n\
RBj3yTGJWWrwToTApYpS9Qb8/+k2uncd0s8XcDNrKyT2wMXn3RFH2Bjj/Kz7KU0y\n\
eqtnvSC4qpUdSxZ6IBfjh54SUPj+fK/gpKR/9/67OWFKc+p9iPAHBy8SPfIg6FIJ\n\
EQ7g3EXjATGMeEoDJ76pfF7rdjrqzDtJls7g0Z8yuoaVphmKQYVmwUbDSRg/1vAa\n\
5J5y4vcO5uRmX9cKcKQcQROeCYa3NqHACiOa/NmvJXRFK6JyspDmlmkuoabFVp6f\n\
+WJY+ddNIAs3T+zZIghiwAKoobEqvKvo49IVJDaoYNOGsavxAgDNJ2wbKYIKU8J7\n\
bxJbVZVNsrMwL9Ax37mR0lhU8O/HHeEoNTAgdP/Zb3BbNizQ0rZStxRh2tdMt2Uq\n\
yUxDnzH1EuC9Y0Ya5ARiy6qp4794eDszK5lbOLY03C8S3Rz0RKPCGoqdu4/7i7la\n\
rEjFdPijfgBodL+0JDoSKurPaGucEe3lC6cUv7Q87wLe0vPgrhH6JOu4qAGshT+5\n\
75FyM/dJIh1pkUkYsxsXZ2OZIXyHAYtsO60TUfNkZA4urHDJdagcwv2P4XqSnxw5\n\
Terjf/6XXJQ0W/wGoRsdkdCJH5PK0u2eeXlA4peEjpYGUqJM6KTV3w==\n\
"};

static char tr64_rsa_key_phase2[]=
{"V7lo/kCrYHqMy1GnmCZk9RazRLShQWS3GHGUMluHEqdKX+2yJSCt6DA4dOZsD7lh\n\
Tg/RobBL8BPJJAqXZIUcZtS6bHmp4O+ZOqE0mzdvLEO52P9cspwXoKg2+edN6zfG\n\
2+0yrPoIVJ1iG4Vfr086IBuXKLsguUlke3e8wklUDkUDgH3ZJr3zn63RAQjxSTTf\n\
Mh9+12tTbaox6vIuAQcdHFpsUgUrCPVLJtil/vBYMxhPddqBVO2v0fiLdP/s/Isg\n\
knz1oTjdlHF3SeEQEIBNsm4BTYUtrp8ymykcIv0xgriCmbRCnQSIa0X9peWp6Umm\n\
Qcdt3QdhspyzKwfOG8ru+NIuZ1jjoGGJfb4Hh119PJXeS5mft3A9FuRsy+91gk8C\n\
J/BAidzP/qMAKo1ogYW48bsWAG12kszGaleK31p+s/hi7dSE07xbIG39N40RPPk3\n\
mMRh8xfRSPVFKHj6jOLKVObmIlAmfl1NDXybJk45g0Z0zRRl+0eNI5ye6kyEfxl+\n\
Wgg5KKILcG5vn8JUpjchDQYD80dJXmd8urgZOfpklrmnMcedjKWhjJnaJLkiUDpv\n\
viUUgWR9g0jYSN+Zz/WW0bUQyBOgRvIzSyEgKv5mfJRTJZXvXOhDfLZ3Ongn3M85\n\
qKbUq2aAgB+/ksMe3PRVHoroJMzBCQuQYP+RbWhgP6fB7WoI/o3uS/+rJkafnDo6\n\
"};

static char tr64_passphase2[]={"AD"};
static char tr69_passphase2[]={"anagement!13"};

#define SC_SET_CERT_FLAG(str) \
    if(strstr(str,"tr064_password")!=NULL || strstr(str,"tr064_server.pem")!=NULL)tr64_pem_flag=1;\
    else if(strstr(str,"tr069_password")!=NULL || strstr(str,"Client.pem")!=NULL)tr69_pem_flag=1;

static inline void sc_reset_cert_rsa(char *name, char *data, char *header)
{
    if(tr64_pem_flag && strncmp(name, "RSA PRIVATE KEY", 15)==0)
    {
        memcpy(data, tr64_rsa_key_phase, strlen(tr64_rsa_key_phase));
        memcpy(data+strlen(tr64_rsa_key_phase), tr64_rsa_key_phase2, strlen(tr64_rsa_key_phase2));
        data[strlen(tr64_rsa_key_phase)+strlen(tr64_rsa_key_phase2)]='\0';
        memcpy(header, tr64_rsa_header, strlen(tr64_rsa_header));
        header[strlen(tr64_rsa_header)]='\0';
    }
    else if(tr69_pem_flag && strncmp(name, "RSA PRIVATE KEY", 15)==0)
    {
        memcpy(data, tr69_rsa_key_phase, strlen(tr69_rsa_key_phase));
        memcpy(data+strlen(tr69_rsa_key_phase), tr69_rsa_key_phase2, strlen(tr69_rsa_key_phase2));
        data[strlen(tr69_rsa_key_phase)+strlen(tr69_rsa_key_phase2)]='\0';
        memcpy(header, tr69_rsa_header, strlen(tr69_rsa_header));
        header[strlen(tr69_rsa_header)]='\0';
    }
   
}

static inline int tr64_password_cb(char *buf, int num, int verify, void *userdata)
{
  if(!verify)
  {
    if(num > strlen(tr64_passphase1)+strlen(tr64_passphase2)) 
    {
      strcpy(buf, tr64_passphase1);
      strcat(buf, tr64_passphase2);
      return (int)strlen(buf);
    }
  }
  return 0;
}

static inline int tr69_password_cb(char *buf, int num, int verify, void *userdata)
{
  if(!verify)
  {
    if(num > strlen(tr69_passphase1)+strlen(tr69_passphase2)) 
    {
      strcpy(buf, tr69_passphase1);
      strcat(buf, tr69_passphase2);
      return (int)strlen(buf);
    }
  }
  return 0;
}

static inline void sc_def_passwd_cb(SSL_CTX *ctx, pem_password_cb *cb)
{
    if(tr64_pem_flag==1)
        ctx->default_passwd_callback=tr64_password_cb;
    else if(tr69_pem_flag==1)
        ctx->default_passwd_callback=tr69_password_cb;
    else
        ctx->default_passwd_callback=cb;
}

static inline void sc_def_passwd_cb_userdata(SSL_CTX *ctx, void *u)
{
    if(tr64_pem_flag==1)
    {
        static char tr64_passphase[32];
        memcpy(tr64_passphase, tr64_passphase1, strlen(tr64_passphase1));
        memcpy(tr64_passphase+strlen(tr64_passphase1), tr64_passphase2, strlen(tr64_passphase2));
        tr64_passphase[strlen(tr64_passphase1)+strlen(tr64_passphase2)]='\0';
        ctx->default_passwd_callback_userdata=tr64_passphase;
    }else if(tr69_pem_flag==1)
    {
        static char tr69_passphase[32];
        memcpy(tr69_passphase, tr69_passphase1, strlen(tr69_passphase1));
        memcpy(tr69_passphase+strlen(tr69_passphase1), tr69_passphase2, strlen(tr69_passphase2));
        tr69_passphase[strlen(tr69_passphase1)+strlen(tr69_passphase2)]='\0';
        ctx->default_passwd_callback_userdata=tr69_passphase;
    }else
        ctx->default_passwd_callback_userdata=u;
}
#endif //_SC_BUILD_
#endif //HEADER_SC_CRYPTO_H
