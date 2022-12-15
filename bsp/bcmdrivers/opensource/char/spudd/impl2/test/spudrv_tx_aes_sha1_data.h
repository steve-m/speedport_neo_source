/*
<:copyright-BRCM:2007:DUAL/GPL:standard

   Copyright (c) 2007 Broadcom Corporation
   All Rights Reserved

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation (the "GPL").

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.


A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.

:>
*/
/***************************************************************************
 * File Name  : 
 *
 * Description: 
 *              
 ***************************************************************************/
#ifndef __SPUDRV_TX_AES_SHA1_DATA_H__
#define __SPUDRV_TX_AES_SHA1_DATA_H__

#if defined(CONFIG_BCM_SPU_TEST)

//

// Automatically generated vector file.

//

// Vector format is: {EOP, SOP, PKT_DATA}.

//

// Example vectors:

//     101234567 // EOP = 0, SOP = 1, PKT_DATA = 01234567

//     089abcdef // EOP = 0, SOP = 0, PKT_DATA = 89abcdef

//     213572468 // EOP = 1, SOP = 0, PKT_DATA = 13572468

//

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 72 (0x48) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt0_tmpl[] = {
    0xb8010048,// 1 CCH   1 

/// ECH cache_idx      : 0x02 

/// ECH pdu_tag        : 0x00 

    0x00020000,// 2 ECH   1 

/// SCX is 17 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x00000011,// 3 SCX   1 

    0x80804830,// 4 SCX   2 

    0x00006400,// 5 SCX   3 

    0xf0ce73c9,// 6 SCX   4 

    0xcbe306fc,// 7 SCX   5 

    0x4522f72b,// 8 SCX   6 

    0xf44c7cb9,// 9 SCX   7 

    0xa2e96778,// 10 SCX   8 

    0x7abd27f8,// 11 SCX   9 

    0xed2b6aaf,// 12 SCX  10 

    0xb42d8298,// 13 SCX  11 

    0x0351a08f,// 14 SCX  12 

    0xd2d33276,// 15 SCX  13 

    0x6cb32c5c,// 16 SCX  14 

    0x7d7d056d,// 17 SCX  15 

    0xeb51374d,// 18 SCX  16 

    0x54579a06,// 19 SCX  17 

/// BFD is 3 words. 

/// BFD tot_len        : 1630 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 522 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 522 

/// BFD lencrypto      : 64 

/// BFD ofstcrypto     : 308 

/// BFD (ofst+len)cry  : 372 

/// BFD ofstiv         : 12 

/// BFD ofsticv        : 1160 

    0x0000020a,// 20 BFD   1 

    0x01340040,// 21 BFD   2 

    0x0488000c,// 22 BFD   3 

/// MFM is 3 words. 

/// MFM vldnibs        : 14 

    0x1400f6e4,// 23 MFM   1 

    0x4eee3a1d,// 24 MFM   2 

    0xa315776a,// 25 MFM   3 

/// BDA is 409 words. 

/// BDA size     is 1630 (0x65e) 

/// BDA id       is 0xd8ea 

    0x065ed8ea,// 26 BDA   1 

/// PAY Generic Data size   : 1630 byte(s) 

/// PAD Buffer Data Pad size   : 2 byte(s) 

    0x01da9c78,// 27 PAY   1 

    0x665a7a40,// 28 PAY   2 

    0x12a1f8e8,// 29 PAY   3 

    0x79490ec8,// 30 PAY   4 

    0x0f232a81,// 31 PAY   5 

    0x2ffcca31,// 32 PAY   6 

    0xea207e56,// 33 PAY   7 

    0x4ec321aa,// 34 PAY   8 

    0x13899779,// 35 PAY   9 

    0x14df1148,// 36 PAY  10 

    0x2c7dfdc8,// 37 PAY  11 

    0x6e4a8584,// 38 PAY  12 

    0x7e2857e8,// 39 PAY  13 

    0xfebf8aba,// 40 PAY  14 

    0x2b27b444,// 41 PAY  15 

    0xb1329713,// 42 PAY  16 

    0x15f597a1,// 43 PAY  17 

    0x94e3fd33,// 44 PAY  18 

    0x23ea7405,// 45 PAY  19 

    0xa53cd1d1,// 46 PAY  20 

    0x77e43e1d,// 47 PAY  21 

    0xec665679,// 48 PAY  22 

    0x231f3914,// 49 PAY  23 

    0x59af3aca,// 50 PAY  24 

    0x9ed55b0c,// 51 PAY  25 

    0x01f5d354,// 52 PAY  26 

    0xf879ea07,// 53 PAY  27 

    0x1807cc77,// 54 PAY  28 

    0x156d5bb4,// 55 PAY  29 

    0x9e7ef91c,// 56 PAY  30 

    0x865391bc,// 57 PAY  31 

    0xee3839e3,// 58 PAY  32 

    0x47e15aa8,// 59 PAY  33 

    0xe32dfd03,// 60 PAY  34 

    0xc6eced8a,// 61 PAY  35 

    0x6e91cd22,// 62 PAY  36 

    0x9eeb56e2,// 63 PAY  37 

    0xcebc4b06,// 64 PAY  38 

    0x5777376f,// 65 PAY  39 

    0x0e0ad5ea,// 66 PAY  40 

    0x60e5975d,// 67 PAY  41 

    0xb0cef425,// 68 PAY  42 

    0x669c80ed,// 69 PAY  43 

    0x9fc22248,// 70 PAY  44 

    0x89146de6,// 71 PAY  45 

    0xeb5ceaf8,// 72 PAY  46 

    0x873af488,// 73 PAY  47 

    0xa0627799,// 74 PAY  48 

    0x179638d3,// 75 PAY  49 

    0xc53b0aac,// 76 PAY  50 

    0x70495ef8,// 77 PAY  51 

    0x4a330f3d,// 78 PAY  52 

    0x92c0f68c,// 79 PAY  53 

    0x1725c769,// 80 PAY  54 

    0x8de8a1bc,// 81 PAY  55 

    0x7611210f,// 82 PAY  56 

    0x6f396734,// 83 PAY  57 

    0x77e130f1,// 84 PAY  58 

    0xbc44f4c9,// 85 PAY  59 

    0x148a59f2,// 86 PAY  60 

    0x617826df,// 87 PAY  61 

    0xa38cb68a,// 88 PAY  62 

    0x3c8b1e58,// 89 PAY  63 

    0x0540f8a2,// 90 PAY  64 

    0x96659e26,// 91 PAY  65 

    0x4b1ff483,// 92 PAY  66 

    0x0720cb29,// 93 PAY  67 

    0x88b1a5cd,// 94 PAY  68 

    0x6391fcec,// 95 PAY  69 

    0x900fa899,// 96 PAY  70 

    0x678e0e82,// 97 PAY  71 

    0x3b91e20a,// 98 PAY  72 

    0x2528e1b8,// 99 PAY  73 

    0x6516577c,// 100 PAY  74 

    0x997a3045,// 101 PAY  75 

    0x9c4d41a3,// 102 PAY  76 

    0x9e583145,// 103 PAY  77 

    0x66ebc8e5,// 104 PAY  78 

    0x9f15b42f,// 105 PAY  79 

    0xf406e36f,// 106 PAY  80 

    0xe957e914,// 107 PAY  81 

    0x3914264b,// 108 PAY  82 

    0x319e357e,// 109 PAY  83 

    0xde480e57,// 110 PAY  84 

    0x613bd724,// 111 PAY  85 

    0x2ca8a073,// 112 PAY  86 

    0x65d05acd,// 113 PAY  87 

    0x0824b15e,// 114 PAY  88 

    0x0d3bc730,// 115 PAY  89 

    0xb482f5c8,// 116 PAY  90 

    0xfb1a8a42,// 117 PAY  91 

    0x3ce921d4,// 118 PAY  92 

    0x26b811e9,// 119 PAY  93 

    0xcb677eb8,// 120 PAY  94 

    0x37d30225,// 121 PAY  95 

    0x1276808b,// 122 PAY  96 

    0xac75a71e,// 123 PAY  97 

    0xa216ec67,// 124 PAY  98 

    0xe49cbaeb,// 125 PAY  99 

    0x6e2c29cd,// 126 PAY 100 

    0xe50a6a2d,// 127 PAY 101 

    0x8617457a,// 128 PAY 102 

    0x58ae35c1,// 129 PAY 103 

    0x79e27cfd,// 130 PAY 104 

    0xb204a802,// 131 PAY 105 

    0xe2eeb7f3,// 132 PAY 106 

    0x1597aa9d,// 133 PAY 107 

    0xa858f271,// 134 PAY 108 

    0xed27529d,// 135 PAY 109 

    0xebb5af5f,// 136 PAY 110 

    0xea2acec0,// 137 PAY 111 

    0x09df95f0,// 138 PAY 112 

    0xeefec536,// 139 PAY 113 

    0x4d5218ef,// 140 PAY 114 

    0x5760b9f7,// 141 PAY 115 

    0x44f4ff02,// 142 PAY 116 

    0x29764d44,// 143 PAY 117 

    0x497ef3bc,// 144 PAY 118 

    0xe84b434b,// 145 PAY 119 

    0x0e6c80e7,// 146 PAY 120 

    0x25f99c06,// 147 PAY 121 

    0x277ee95e,// 148 PAY 122 

    0xf0c8d1f6,// 149 PAY 123 

    0xa2891492,// 150 PAY 124 

    0xdf3cc9d2,// 151 PAY 125 

    0xdd86aad9,// 152 PAY 126 

    0x8f3c9b62,// 153 PAY 127 

    0x3d8115d7,// 154 PAY 128 

    0x71105e31,// 155 PAY 129 

    0x6b7c0d5a,// 156 PAY 130 

    0x723c9af8,// 157 PAY 131 

    0x09aaeeee,// 158 PAY 132 

    0x37de7cd7,// 159 PAY 133 

    0x860e4df5,// 160 PAY 134 

    0x99c19bfd,// 161 PAY 135 

    0xdd819363,// 162 PAY 136 

    0x213a7519,// 163 PAY 137 

    0xa8574091,// 164 PAY 138 

    0x2303da37,// 165 PAY 139 

    0xd10e60be,// 166 PAY 140 

    0x95e8ba99,// 167 PAY 141 

    0xfac630f0,// 168 PAY 142 

    0x62b1d096,// 169 PAY 143 

    0x2c99c7e0,// 170 PAY 144 

    0x046e495e,// 171 PAY 145 

    0x6c3d17b6,// 172 PAY 146 

    0x7cd48aaf,// 173 PAY 147 

    0x484202a3,// 174 PAY 148 

    0x38cc4098,// 175 PAY 149 

    0x390062d6,// 176 PAY 150 

    0x62f21221,// 177 PAY 151 

    0x2957055f,// 178 PAY 152 

    0x808ed1b0,// 179 PAY 153 

    0xb4866c33,// 180 PAY 154 

    0x502c7858,// 181 PAY 155 

    0x90b73543,// 182 PAY 156 

    0xc15269cf,// 183 PAY 157 

    0xe91f83b2,// 184 PAY 158 

    0xa7298558,// 185 PAY 159 

    0x7695bac1,// 186 PAY 160 

    0x613ab8e0,// 187 PAY 161 

    0x12ffc7c4,// 188 PAY 162 

    0x8ae52e92,// 189 PAY 163 

    0xc9dfd79d,// 190 PAY 164 

    0x1c2b5f30,// 191 PAY 165 

    0x34ba0d38,// 192 PAY 166 

    0xff5dc6ec,// 193 PAY 167 

    0x918a5d3d,// 194 PAY 168 

    0x7e5e790f,// 195 PAY 169 

    0x66aaadb2,// 196 PAY 170 

    0x39cf4d65,// 197 PAY 171 

    0x222c33f9,// 198 PAY 172 

    0x179ffa07,// 199 PAY 173 

    0x9727b0d3,// 200 PAY 174 

    0x93b27ac7,// 201 PAY 175 

    0xa6da5b86,// 202 PAY 176 

    0x99b138cf,// 203 PAY 177 

    0xed8ed7fe,// 204 PAY 178 

    0x8ca17355,// 205 PAY 179 

    0x2d304164,// 206 PAY 180 

    0x4706543a,// 207 PAY 181 

    0x0304e6db,// 208 PAY 182 

    0x3f9cb331,// 209 PAY 183 

    0xc3f22f79,// 210 PAY 184 

    0x82e92eda,// 211 PAY 185 

    0xe2da842f,// 212 PAY 186 

    0xdd2eb074,// 213 PAY 187 

    0x9ba6fbdc,// 214 PAY 188 

    0x7214e6a9,// 215 PAY 189 

    0x43233777,// 216 PAY 190 

    0x91f60016,// 217 PAY 191 

    0x46db5d4c,// 218 PAY 192 

    0xa7e08506,// 219 PAY 193 

    0x74aa7d29,// 220 PAY 194 

    0x924ee0b5,// 221 PAY 195 

    0x0a76f712,// 222 PAY 196 

    0xf32c0429,// 223 PAY 197 

    0x01780e21,// 224 PAY 198 

    0xf0a9d78b,// 225 PAY 199 

    0x36b44dab,// 226 PAY 200 

    0x84147fc8,// 227 PAY 201 

    0xdb7f30e5,// 228 PAY 202 

    0xea70dbb1,// 229 PAY 203 

    0xeb8d037b,// 230 PAY 204 

    0x5ac30362,// 231 PAY 205 

    0x855011ac,// 232 PAY 206 

    0x7097b49f,// 233 PAY 207 

    0x8aacbd1b,// 234 PAY 208 

    0x250a5e39,// 235 PAY 209 

    0xdee7d4e7,// 236 PAY 210 

    0x14325cdf,// 237 PAY 211 

    0xfe2dfe54,// 238 PAY 212 

    0x9c8da7f0,// 239 PAY 213 

    0x49e54bb1,// 240 PAY 214 

    0x9e112443,// 241 PAY 215 

    0x40836990,// 242 PAY 216 

    0x478f2080,// 243 PAY 217 

    0xc9d880ea,// 244 PAY 218 

    0xea2d44c2,// 245 PAY 219 

    0xd0950d28,// 246 PAY 220 

    0x52e5db73,// 247 PAY 221 

    0x1d6b7aba,// 248 PAY 222 

    0x32b5d070,// 249 PAY 223 

    0x4802b83d,// 250 PAY 224 

    0xec0e3832,// 251 PAY 225 

    0x50893d8a,// 252 PAY 226 

    0xef595ff3,// 253 PAY 227 

    0x4c4a8635,// 254 PAY 228 

    0x2a350fff,// 255 PAY 229 

    0x2dc061cf,// 256 PAY 230 

    0x161cc825,// 257 PAY 231 

    0x202fd253,// 258 PAY 232 

    0x13a06bf3,// 259 PAY 233 

    0xe08a9e7c,// 260 PAY 234 

    0xee61bf5d,// 261 PAY 235 

    0x48b5d489,// 262 PAY 236 

    0xafb39e1e,// 263 PAY 237 

    0x3ee1e750,// 264 PAY 238 

    0xefcdd2f3,// 265 PAY 239 

    0x4c2b2559,// 266 PAY 240 

    0xbd12689c,// 267 PAY 241 

    0xb133907a,// 268 PAY 242 

    0x2ed8fa4a,// 269 PAY 243 

    0x4c32d31a,// 270 PAY 244 

    0x5eacf37c,// 271 PAY 245 

    0x3ac8c7fe,// 272 PAY 246 

    0xd5e5fe1f,// 273 PAY 247 

    0x02de59f3,// 274 PAY 248 

    0xc2be1446,// 275 PAY 249 

    0x62a03e3e,// 276 PAY 250 

    0x5752b5d7,// 277 PAY 251 

    0xe776d48e,// 278 PAY 252 

    0x66101e00,// 279 PAY 253 

    0x6bf03436,// 280 PAY 254 

    0xe6153322,// 281 PAY 255 

    0xbc3fec5c,// 282 PAY 256 

    0x27acd3ca,// 283 PAY 257 

    0xdc5c10fd,// 284 PAY 258 

    0xd6f2f64b,// 285 PAY 259 

    0xaf7b945c,// 286 PAY 260 

    0xcb75a728,// 287 PAY 261 

    0x498b09cf,// 288 PAY 262 

    0xeb6091d3,// 289 PAY 263 

    0x01590053,// 290 PAY 264 

    0x2f243054,// 291 PAY 265 

    0x5e58f7a7,// 292 PAY 266 

    0x80d56156,// 293 PAY 267 

    0x0cda6e64,// 294 PAY 268 

    0xa08e6b08,// 295 PAY 269 

    0xeeb9b3d4,// 296 PAY 270 

    0x12aee6b9,// 297 PAY 271 

    0x8d6995c5,// 298 PAY 272 

    0x427b4a0b,// 299 PAY 273 

    0x8e7c6181,// 300 PAY 274 

    0xa19e15cd,// 301 PAY 275 

    0x8737ca7d,// 302 PAY 276 

    0xd3b29dd0,// 303 PAY 277 

    0x1a8d764d,// 304 PAY 278 

    0xe7d99b5d,// 305 PAY 279 

    0x25bcd779,// 306 PAY 280 

    0x2ef0987e,// 307 PAY 281 

    0xa2f522c0,// 308 PAY 282 

    0x58ed06c6,// 309 PAY 283 

    0x7f5b7823,// 310 PAY 284 

    0xc7d5e20f,// 311 PAY 285 

    0x73bc6a1f,// 312 PAY 286 

    0xc1624ca1,// 313 PAY 287 

    0xbd14b566,// 314 PAY 288 

    0xdd08f45b,// 315 PAY 289 

    0x09563f3a,// 316 PAY 290 

    0x7ddded00,// 317 PAY 291 

    0xf6de7768,// 318 PAY 292 

    0x2b741984,// 319 PAY 293 

    0x83bc76a0,// 320 PAY 294 

    0x9020481c,// 321 PAY 295 

    0xb7be6853,// 322 PAY 296 

    0x3b8f9051,// 323 PAY 297 

    0x7f89957f,// 324 PAY 298 

    0xb36c5cc6,// 325 PAY 299 

    0x17abdf59,// 326 PAY 300 

    0x9380073a,// 327 PAY 301 

    0xf43e7c7c,// 328 PAY 302 

    0xebc9bca2,// 329 PAY 303 

    0xaec58776,// 330 PAY 304 

    0xe41f7da5,// 331 PAY 305 

    0xa9d092df,// 332 PAY 306 

    0x91dd007a,// 333 PAY 307 

    0x13b63592,// 334 PAY 308 

    0xddb00260,// 335 PAY 309 

    0x5f21fb04,// 336 PAY 310 

    0xb77c9bd6,// 337 PAY 311 

    0x89cd264e,// 338 PAY 312 

    0xe41a2708,// 339 PAY 313 

    0x3e58c5f9,// 340 PAY 314 

    0x6b0632d8,// 341 PAY 315 

    0x9ac72d54,// 342 PAY 316 

    0x5d3eedbe,// 343 PAY 317 

    0x1e23ef90,// 344 PAY 318 

    0x38685cee,// 345 PAY 319 

    0xb6e7a3f1,// 346 PAY 320 

    0x420dc260,// 347 PAY 321 

    0x146676f0,// 348 PAY 322 

    0x4677f295,// 349 PAY 323 

    0x635a0cbf,// 350 PAY 324 

    0x1df5cd00,// 351 PAY 325 

    0x7cc72a5e,// 352 PAY 326 

    0x6afc9c85,// 353 PAY 327 

    0xd5269420,// 354 PAY 328 

    0x87fb3b52,// 355 PAY 329 

    0x8656fa3d,// 356 PAY 330 

    0xf1b4f0fe,// 357 PAY 331 

    0xf845c876,// 358 PAY 332 

    0xbbe6bb88,// 359 PAY 333 

    0x079455c8,// 360 PAY 334 

    0xa94e2379,// 361 PAY 335 

    0x778e84ed,// 362 PAY 336 

    0x67d5e6e7,// 363 PAY 337 

    0xa1b6c4dc,// 364 PAY 338 

    0x8b4f790b,// 365 PAY 339 

    0xd60318e9,// 366 PAY 340 

    0x1ed4988d,// 367 PAY 341 

    0x2658be98,// 368 PAY 342 

    0x90fb3424,// 369 PAY 343 

    0x80f6139b,// 370 PAY 344 

    0xd570c21c,// 371 PAY 345 

    0x11075456,// 372 PAY 346 

    0x1ccf85b9,// 373 PAY 347 

    0xd6b2dbd0,// 374 PAY 348 

    0x636e3f2e,// 375 PAY 349 

    0x109999e5,// 376 PAY 350 

    0xa7c5cd77,// 377 PAY 351 

    0x367fa4c5,// 378 PAY 352 

    0x18610de9,// 379 PAY 353 

    0xa5156386,// 380 PAY 354 

    0x9bc9cb03,// 381 PAY 355 

    0xa74c0eb7,// 382 PAY 356 

    0x5dbf7b61,// 383 PAY 357 

    0x14eeb6e5,// 384 PAY 358 

    0x5220e71b,// 385 PAY 359 

    0xc046928f,// 386 PAY 360 

    0x0b8eec14,// 387 PAY 361 

    0x4d43656b,// 388 PAY 362 

    0x822bf32e,// 389 PAY 363 

    0xab9ffee4,// 390 PAY 364 

    0x22884cd9,// 391 PAY 365 

    0xf1175dc2,// 392 PAY 366 

    0xaa033508,// 393 PAY 367 

    0xa2e3adc0,// 394 PAY 368 

    0xf4eae98e,// 395 PAY 369 

    0xcedf0b6d,// 396 PAY 370 

    0x84f4ab70,// 397 PAY 371 

    0x759e319e,// 398 PAY 372 

    0x048a85d6,// 399 PAY 373 

    0x9d740559,// 400 PAY 374 

    0xb8bb10a2,// 401 PAY 375 

    0x345d2c8b,// 402 PAY 376 

    0xf45dbcf3,// 403 PAY 377 

    0xfe1b39ea,// 404 PAY 378 

    0x0aa150f1,// 405 PAY 379 

    0xef3a8237,// 406 PAY 380 

    0x139e94dd,// 407 PAY 381 

    0xf4adb0c4,// 408 PAY 382 

    0x43e5bf3d,// 409 PAY 383 

    0x16ad342d,// 410 PAY 384 

    0xc4020262,// 411 PAY 385 

    0x0a38dfc5,// 412 PAY 386 

    0x3331fdc1,// 413 PAY 387 

    0xc53fbeea,// 414 PAY 388 

    0x00449d3b,// 415 PAY 389 

    0x5cad81ee,// 416 PAY 390 

    0xa95967e2,// 417 PAY 391 

    0xca7af5cc,// 418 PAY 392 

    0xafe4425c,// 419 PAY 393 

    0x789be653,// 420 PAY 394 

    0xb7f967c4,// 421 PAY 395 

    0x87f5a618,// 422 PAY 396 

    0xccd19fa0,// 423 PAY 397 

    0xde4faa12,// 424 PAY 398 

    0xf69e0fbe,// 425 PAY 399 

    0x3ad6acaf,// 426 PAY 400 

    0x72d0895e,// 427 PAY 401 

    0x0680000d,// 428 PAY 402 

    0x3885f71e,// 429 PAY 403 

    0x8de0a0cb,// 430 PAY 404 

    0x7252ae8c,// 431 PAY 405 

    0x41cc4b24,// 432 PAY 406 

    0x7c014ce2,// 433 PAY 407 

    0x8e7e0000,// 434 PAY 408 

/// STA is 1 words. 

/// STA num_pkts       : 99 

/// STA pkt_idx        : 152 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x93 

    0x02609363 // 435 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt1_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x0b 

/// ECH pdu_tag        : 0x00 

    0x000b0000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv !insert_icv check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x2 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x80844853,// 4 SCX   2 

    0x00001284,// 5 SCX   3 

    0x6eb407cd,// 6 SCX   4 

    0xd45102f5,// 7 SCX   5 

    0xacf6c415,// 8 SCX   6 

    0x9ee15e1e,// 9 SCX   7 

    0xff1433f1,// 10 SCX   8 

    0x20d82a7e,// 11 SCX   9 

    0x6d5a7f70,// 12 SCX  10 

    0x430751cf,// 13 SCX  11 

    0xbf1bac8e,// 14 SCX  12 

    0x05caa7d4,// 15 SCX  13 

    0x0f0a740c,// 16 SCX  14 

    0xf2ed4b38,// 17 SCX  15 

    0x2ed7675d,// 18 SCX  16 

    0x650d3851,// 19 SCX  17 

    0xeea36ccb,// 20 SCX  18 

    0x75f600bc,// 21 SCX  19 

    0xb9d12f80,// 22 SCX  20 

    0xba290c94,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1833 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 1132 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1132 

/// BFD lencrypto      : 144 

/// BFD ofstcrypto     : 952 

/// BFD (ofst+len)cry  : 1096 

/// BFD ofstiv         : 640 

/// BFD ofsticv        : 1788 

    0x0000046c,// 24 BFD   1 

    0x03b80090,// 25 BFD   2 

    0x06fc0280,// 26 BFD   3 

/// MFM is 3 words. 

/// MFM vldnibs        : 13 

    0x130091ce,// 27 MFM   1 

    0x458bf0d7,// 28 MFM   2 

    0x862d8650,// 29 MFM   3 

/// BDA is 460 words. 

/// BDA size     is 1833 (0x729) 

/// BDA id       is 0x3d82 

    0x07293d82,// 30 BDA   1 

/// PAY Generic Data size   : 1833 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0xb0c9a8c4,// 31 PAY   1 

    0x51089638,// 32 PAY   2 

    0x46eb14dd,// 33 PAY   3 

    0x13913e05,// 34 PAY   4 

    0x8496e494,// 35 PAY   5 

    0x9e46e71c,// 36 PAY   6 

    0x46109785,// 37 PAY   7 

    0x64b071c4,// 38 PAY   8 

    0xd072598d,// 39 PAY   9 

    0x74512c4d,// 40 PAY  10 

    0x7beba878,// 41 PAY  11 

    0x8caf29a0,// 42 PAY  12 

    0x3f108a9b,// 43 PAY  13 

    0xe6c79b8e,// 44 PAY  14 

    0x1585d4bb,// 45 PAY  15 

    0x5a96ee3b,// 46 PAY  16 

    0xc58e77f3,// 47 PAY  17 

    0xc5a55673,// 48 PAY  18 

    0x8ab0979a,// 49 PAY  19 

    0xee5ab97c,// 50 PAY  20 

    0x60891b85,// 51 PAY  21 

    0x3d14bd84,// 52 PAY  22 

    0x4109264a,// 53 PAY  23 

    0x05f61300,// 54 PAY  24 

    0x93857c55,// 55 PAY  25 

    0xdd44bd73,// 56 PAY  26 

    0x1af6f43e,// 57 PAY  27 

    0x93f95033,// 58 PAY  28 

    0x03df1874,// 59 PAY  29 

    0xce3f383f,// 60 PAY  30 

    0x4ac8cc76,// 61 PAY  31 

    0xc48822e9,// 62 PAY  32 

    0x368c75f2,// 63 PAY  33 

    0x20755d9b,// 64 PAY  34 

    0xa284e31e,// 65 PAY  35 

    0x8febb025,// 66 PAY  36 

    0x9a6c1d8e,// 67 PAY  37 

    0xcda5b537,// 68 PAY  38 

    0x3dea5332,// 69 PAY  39 

    0xe9ae1c56,// 70 PAY  40 

    0xac52a8cf,// 71 PAY  41 

    0x311966b0,// 72 PAY  42 

    0xaad3bae5,// 73 PAY  43 

    0x452a0bb5,// 74 PAY  44 

    0x8c2d56cc,// 75 PAY  45 

    0x303e2ce6,// 76 PAY  46 

    0xa6c2b162,// 77 PAY  47 

    0xa135efa0,// 78 PAY  48 

    0xed66c352,// 79 PAY  49 

    0x2e3e05e2,// 80 PAY  50 

    0x5ce3cb2f,// 81 PAY  51 

    0x748bd237,// 82 PAY  52 

    0xae06909d,// 83 PAY  53 

    0x1255ef8b,// 84 PAY  54 

    0xeff62e6a,// 85 PAY  55 

    0xd892cd1e,// 86 PAY  56 

    0x459cdf74,// 87 PAY  57 

    0xe90545d6,// 88 PAY  58 

    0xc4ebd94e,// 89 PAY  59 

    0xe7cf9c67,// 90 PAY  60 

    0xcc94a7ad,// 91 PAY  61 

    0x4014b31e,// 92 PAY  62 

    0x419fea8d,// 93 PAY  63 

    0x01eebf46,// 94 PAY  64 

    0x615a4d4d,// 95 PAY  65 

    0x43d71755,// 96 PAY  66 

    0xe1a86bbd,// 97 PAY  67 

    0x727c0528,// 98 PAY  68 

    0x997dd366,// 99 PAY  69 

    0x3865eb02,// 100 PAY  70 

    0x9feb9845,// 101 PAY  71 

    0x51aa6e19,// 102 PAY  72 

    0x4c2063d5,// 103 PAY  73 

    0xec8ba105,// 104 PAY  74 

    0x0faccdfa,// 105 PAY  75 

    0xd5fde89d,// 106 PAY  76 

    0x195c0933,// 107 PAY  77 

    0x3d1bd543,// 108 PAY  78 

    0x4c678377,// 109 PAY  79 

    0x359b7b3a,// 110 PAY  80 

    0x7743c8ea,// 111 PAY  81 

    0xb1a016fa,// 112 PAY  82 

    0xee1e839e,// 113 PAY  83 

    0xd7f0de6c,// 114 PAY  84 

    0xecb0790e,// 115 PAY  85 

    0xda7bab68,// 116 PAY  86 

    0x64bf6a1b,// 117 PAY  87 

    0x969e3846,// 118 PAY  88 

    0x2341ba9e,// 119 PAY  89 

    0x345193da,// 120 PAY  90 

    0xeb34b7a9,// 121 PAY  91 

    0x14fbf6fc,// 122 PAY  92 

    0x457b2ddc,// 123 PAY  93 

    0xaec82a70,// 124 PAY  94 

    0x4908992e,// 125 PAY  95 

    0x0b255b6e,// 126 PAY  96 

    0xc5bf8dd0,// 127 PAY  97 

    0x3697f4c2,// 128 PAY  98 

    0xe9398960,// 129 PAY  99 

    0x92ae2699,// 130 PAY 100 

    0x84f0fc2f,// 131 PAY 101 

    0xa00e71d1,// 132 PAY 102 

    0xe9c83d1d,// 133 PAY 103 

    0x7a8d9f56,// 134 PAY 104 

    0x1d63d322,// 135 PAY 105 

    0xc8b6046d,// 136 PAY 106 

    0xf476772e,// 137 PAY 107 

    0x50dd9bdd,// 138 PAY 108 

    0xa5ff8b64,// 139 PAY 109 

    0x9a68a5c9,// 140 PAY 110 

    0x7dca0b5a,// 141 PAY 111 

    0xff7f839f,// 142 PAY 112 

    0x26976a30,// 143 PAY 113 

    0x76dec78f,// 144 PAY 114 

    0xef599a96,// 145 PAY 115 

    0x8dfdb1da,// 146 PAY 116 

    0x9aaf9339,// 147 PAY 117 

    0x996dfc7b,// 148 PAY 118 

    0x0c5cc13f,// 149 PAY 119 

    0x32532b66,// 150 PAY 120 

    0x87c8e2d1,// 151 PAY 121 

    0x40f34cb5,// 152 PAY 122 

    0x75ed9cd5,// 153 PAY 123 

    0xa8c884c9,// 154 PAY 124 

    0x09a88a68,// 155 PAY 125 

    0xa3d654a9,// 156 PAY 126 

    0x894a52d7,// 157 PAY 127 

    0x66a30bb6,// 158 PAY 128 

    0xf28bf251,// 159 PAY 129 

    0xb9676090,// 160 PAY 130 

    0xe7c55cad,// 161 PAY 131 

    0x4231192c,// 162 PAY 132 

    0xd9e26bb6,// 163 PAY 133 

    0x850d7661,// 164 PAY 134 

    0xd620c16e,// 165 PAY 135 

    0x7b4edc57,// 166 PAY 136 

    0x3441724d,// 167 PAY 137 

    0x0478286b,// 168 PAY 138 

    0xc098e7ec,// 169 PAY 139 

    0xd52ab664,// 170 PAY 140 

    0x442b51eb,// 171 PAY 141 

    0x5545c076,// 172 PAY 142 

    0x99a726dc,// 173 PAY 143 

    0x81ede5aa,// 174 PAY 144 

    0xa7cb0bfe,// 175 PAY 145 

    0xe2cf9b26,// 176 PAY 146 

    0xbc283747,// 177 PAY 147 

    0x1dfa1d36,// 178 PAY 148 

    0xd22c0bde,// 179 PAY 149 

    0xa50b30b0,// 180 PAY 150 

    0x166f2df8,// 181 PAY 151 

    0xfb0a8cbb,// 182 PAY 152 

    0x41fc45db,// 183 PAY 153 

    0x02f96663,// 184 PAY 154 

    0x96b7a7f7,// 185 PAY 155 

    0x7a0c6538,// 186 PAY 156 

    0xb77e0cac,// 187 PAY 157 

    0x7d2929e9,// 188 PAY 158 

    0x6f7f0949,// 189 PAY 159 

    0xebf04ead,// 190 PAY 160 

    0xe2022086,// 191 PAY 161 

    0xe890d85f,// 192 PAY 162 

    0x1c24374a,// 193 PAY 163 

    0x50356f59,// 194 PAY 164 

    0x81f554b8,// 195 PAY 165 

    0xa746c96c,// 196 PAY 166 

    0xfe935007,// 197 PAY 167 

    0xaad8ec7c,// 198 PAY 168 

    0xc02c5fe9,// 199 PAY 169 

    0x3c08674e,// 200 PAY 170 

    0x122d56c1,// 201 PAY 171 

    0x3b2c70e8,// 202 PAY 172 

    0x19a59109,// 203 PAY 173 

    0xd64f3881,// 204 PAY 174 

    0xe2585560,// 205 PAY 175 

    0x038e256a,// 206 PAY 176 

    0x1c7ef2d5,// 207 PAY 177 

    0x37189a21,// 208 PAY 178 

    0x15dda8eb,// 209 PAY 179 

    0x552fcf3c,// 210 PAY 180 

    0x6bec36d0,// 211 PAY 181 

    0x27b782f9,// 212 PAY 182 

    0x542110be,// 213 PAY 183 

    0xf9407a31,// 214 PAY 184 

    0x9c892bd1,// 215 PAY 185 

    0x1b148111,// 216 PAY 186 

    0xb76615fe,// 217 PAY 187 

    0xd8240a4d,// 218 PAY 188 

    0x5c6bd6f0,// 219 PAY 189 

    0x70c82c96,// 220 PAY 190 

    0x81f0c02d,// 221 PAY 191 

    0x24cf2b04,// 222 PAY 192 

    0x3c7c291b,// 223 PAY 193 

    0xca70902a,// 224 PAY 194 

    0xa34bdfba,// 225 PAY 195 

    0x8bba4f34,// 226 PAY 196 

    0x6625e141,// 227 PAY 197 

    0x9808ac83,// 228 PAY 198 

    0xb4501919,// 229 PAY 199 

    0xeb43d316,// 230 PAY 200 

    0xc146bc56,// 231 PAY 201 

    0x1b342b00,// 232 PAY 202 

    0x832e96fb,// 233 PAY 203 

    0x8a517571,// 234 PAY 204 

    0x7ef3dc18,// 235 PAY 205 

    0xd11be509,// 236 PAY 206 

    0x511229da,// 237 PAY 207 

    0xde1e7ca4,// 238 PAY 208 

    0x5d3d545c,// 239 PAY 209 

    0x1a59b1a1,// 240 PAY 210 

    0x689cb423,// 241 PAY 211 

    0x3bf2d663,// 242 PAY 212 

    0xedbf5bfb,// 243 PAY 213 

    0xa86602fe,// 244 PAY 214 

    0xa53956d4,// 245 PAY 215 

    0x623b8c8b,// 246 PAY 216 

    0x08b5a977,// 247 PAY 217 

    0x406f93e5,// 248 PAY 218 

    0x1d7edf10,// 249 PAY 219 

    0x50db2272,// 250 PAY 220 

    0x304c8be2,// 251 PAY 221 

    0xf110bbcb,// 252 PAY 222 

    0x0be01493,// 253 PAY 223 

    0xdaf9eab8,// 254 PAY 224 

    0x7bfc5f72,// 255 PAY 225 

    0x3e859b6b,// 256 PAY 226 

    0x728bbc28,// 257 PAY 227 

    0x0ade517c,// 258 PAY 228 

    0x9a52ec49,// 259 PAY 229 

    0xa25a9e85,// 260 PAY 230 

    0x0f33f12d,// 261 PAY 231 

    0xed73b5f9,// 262 PAY 232 

    0xabedd58b,// 263 PAY 233 

    0xf446cea4,// 264 PAY 234 

    0x2c1fc125,// 265 PAY 235 

    0xa849815b,// 266 PAY 236 

    0xbb94b743,// 267 PAY 237 

    0xf28df386,// 268 PAY 238 

    0x066c78ed,// 269 PAY 239 

    0xe85405c1,// 270 PAY 240 

    0x9710e55d,// 271 PAY 241 

    0x64e00fb0,// 272 PAY 242 

    0xb8056563,// 273 PAY 243 

    0x6adddb66,// 274 PAY 244 

    0x972190e8,// 275 PAY 245 

    0x8b9400fe,// 276 PAY 246 

    0xee31ccdf,// 277 PAY 247 

    0x9abb4ea3,// 278 PAY 248 

    0x473d8e2a,// 279 PAY 249 

    0xf8f6e8c2,// 280 PAY 250 

    0x50c086e1,// 281 PAY 251 

    0x5c6c0bed,// 282 PAY 252 

    0x7759a41e,// 283 PAY 253 

    0xb54b0680,// 284 PAY 254 

    0xb01b2b24,// 285 PAY 255 

    0x35ce2eff,// 286 PAY 256 

    0x7a56325f,// 287 PAY 257 

    0x6b6a4dce,// 288 PAY 258 

    0xd903f1b4,// 289 PAY 259 

    0x9bf40b1e,// 290 PAY 260 

    0x349d1362,// 291 PAY 261 

    0x137e5f53,// 292 PAY 262 

    0x42709b68,// 293 PAY 263 

    0xc274a207,// 294 PAY 264 

    0xb8d69e61,// 295 PAY 265 

    0xe054108b,// 296 PAY 266 

    0x6c3250b8,// 297 PAY 267 

    0x93b3f463,// 298 PAY 268 

    0xec9d13bf,// 299 PAY 269 

    0x3605adb8,// 300 PAY 270 

    0xefa6fc27,// 301 PAY 271 

    0x7f147291,// 302 PAY 272 

    0x7aa1be4b,// 303 PAY 273 

    0x81db37f3,// 304 PAY 274 

    0x88b38bdb,// 305 PAY 275 

    0x1d51936a,// 306 PAY 276 

    0x141d8ec9,// 307 PAY 277 

    0xf07adaf3,// 308 PAY 278 

    0x60ff9b42,// 309 PAY 279 

    0xb7a8733d,// 310 PAY 280 

    0xbe911580,// 311 PAY 281 

    0x388e3141,// 312 PAY 282 

    0xba948ccd,// 313 PAY 283 

    0xeeebcdf1,// 314 PAY 284 

    0x33eab765,// 315 PAY 285 

    0xd3afec08,// 316 PAY 286 

    0x904ca2e2,// 317 PAY 287 

    0x651d1f3c,// 318 PAY 288 

    0x0b330d7a,// 319 PAY 289 

    0x5bcc02ef,// 320 PAY 290 

    0xa7a2eb13,// 321 PAY 291 

    0xa5184a42,// 322 PAY 292 

    0x4677f3d7,// 323 PAY 293 

    0xff66be2e,// 324 PAY 294 

    0x1214d128,// 325 PAY 295 

    0x424067c4,// 326 PAY 296 

    0x0ad6864e,// 327 PAY 297 

    0xdbc7feea,// 328 PAY 298 

    0x40444c3a,// 329 PAY 299 

    0x306a5022,// 330 PAY 300 

    0x3c5b650f,// 331 PAY 301 

    0x53ca48b3,// 332 PAY 302 

    0x1c3a0cf9,// 333 PAY 303 

    0x56e4f7fc,// 334 PAY 304 

    0x915dbe26,// 335 PAY 305 

    0xb1806d38,// 336 PAY 306 

    0x7ce920be,// 337 PAY 307 

    0x2cbc0895,// 338 PAY 308 

    0xd4df4151,// 339 PAY 309 

    0xe3e93f04,// 340 PAY 310 

    0x7e7a32f3,// 341 PAY 311 

    0xa702db76,// 342 PAY 312 

    0x39290794,// 343 PAY 313 

    0x207bf706,// 344 PAY 314 

    0x8e5ab89b,// 345 PAY 315 

    0xb3aadde0,// 346 PAY 316 

    0xecfd99d9,// 347 PAY 317 

    0x83b8f2ee,// 348 PAY 318 

    0xfa870769,// 349 PAY 319 

    0xc467f130,// 350 PAY 320 

    0x9e9c3747,// 351 PAY 321 

    0xe201e479,// 352 PAY 322 

    0xb381517b,// 353 PAY 323 

    0x2515bb4a,// 354 PAY 324 

    0xb30d33f1,// 355 PAY 325 

    0x4b567897,// 356 PAY 326 

    0x30c04726,// 357 PAY 327 

    0xea37fd10,// 358 PAY 328 

    0xe482483a,// 359 PAY 329 

    0xec8ea946,// 360 PAY 330 

    0xf3cbc0bb,// 361 PAY 331 

    0x9d486944,// 362 PAY 332 

    0xf13eca97,// 363 PAY 333 

    0x9344f39d,// 364 PAY 334 

    0x08a26953,// 365 PAY 335 

    0xace54dca,// 366 PAY 336 

    0xe1f0b54a,// 367 PAY 337 

    0x73ead946,// 368 PAY 338 

    0xcbef54df,// 369 PAY 339 

    0x7262e206,// 370 PAY 340 

    0xe12fb20c,// 371 PAY 341 

    0x91d8acf8,// 372 PAY 342 

    0x677bb0bc,// 373 PAY 343 

    0x6f7b9382,// 374 PAY 344 

    0x900f33c7,// 375 PAY 345 

    0x99b62362,// 376 PAY 346 

    0x87d23ce3,// 377 PAY 347 

    0xbd8db423,// 378 PAY 348 

    0xd69f1267,// 379 PAY 349 

    0x336d46e2,// 380 PAY 350 

    0xf1dcabd0,// 381 PAY 351 

    0xa91b2590,// 382 PAY 352 

    0x939a71ca,// 383 PAY 353 

    0xd0ebad38,// 384 PAY 354 

    0x3cd9090a,// 385 PAY 355 

    0xb014ec76,// 386 PAY 356 

    0x7be2eeeb,// 387 PAY 357 

    0x0a9d5ac7,// 388 PAY 358 

    0x6ac521cd,// 389 PAY 359 

    0x55d32283,// 390 PAY 360 

    0x3a4b4b40,// 391 PAY 361 

    0xdebbf578,// 392 PAY 362 

    0xefe1fdd2,// 393 PAY 363 

    0x33947259,// 394 PAY 364 

    0x399f2f6d,// 395 PAY 365 

    0xa4bb034c,// 396 PAY 366 

    0x409e582d,// 397 PAY 367 

    0x54286633,// 398 PAY 368 

    0xf8c9c9dd,// 399 PAY 369 

    0x8e556ac1,// 400 PAY 370 

    0x68729908,// 401 PAY 371 

    0x4b0f7546,// 402 PAY 372 

    0xf737a93c,// 403 PAY 373 

    0x2f9bea43,// 404 PAY 374 

    0x49069435,// 405 PAY 375 

    0x8f0ddf6e,// 406 PAY 376 

    0x963802e9,// 407 PAY 377 

    0x7b7f20b1,// 408 PAY 378 

    0xdf262228,// 409 PAY 379 

    0x88f91c92,// 410 PAY 380 

    0xa4c08af0,// 411 PAY 381 

    0x98a7a726,// 412 PAY 382 

    0xf4264d81,// 413 PAY 383 

    0xcaa27897,// 414 PAY 384 

    0xb32c08aa,// 415 PAY 385 

    0x347fa621,// 416 PAY 386 

    0xc4a1087f,// 417 PAY 387 

    0xde893e93,// 418 PAY 388 

    0xe17e34dd,// 419 PAY 389 

    0x6a74d5a1,// 420 PAY 390 

    0xa9998724,// 421 PAY 391 

    0x3bf5399c,// 422 PAY 392 

    0xd7cb4061,// 423 PAY 393 

    0x0c1b42ab,// 424 PAY 394 

    0x9ffad3c6,// 425 PAY 395 

    0x39bca658,// 426 PAY 396 

    0x42d976fb,// 427 PAY 397 

    0x97a9d518,// 428 PAY 398 

    0x446439c6,// 429 PAY 399 

    0xbe8e2618,// 430 PAY 400 

    0x6106ae69,// 431 PAY 401 

    0x3102f08e,// 432 PAY 402 

    0x0d791de7,// 433 PAY 403 

    0x702d9617,// 434 PAY 404 

    0x0c04bc2f,// 435 PAY 405 

    0x9644e078,// 436 PAY 406 

    0x19f7d404,// 437 PAY 407 

    0x28b7286a,// 438 PAY 408 

    0xb3b4231f,// 439 PAY 409 

    0x5937da47,// 440 PAY 410 

    0xbf406468,// 441 PAY 411 

    0x61142897,// 442 PAY 412 

    0xd62795d7,// 443 PAY 413 

    0x8651a7ad,// 444 PAY 414 

    0x8244397e,// 445 PAY 415 

    0x0e443f2f,// 446 PAY 416 

    0x1bcc8731,// 447 PAY 417 

    0xfcad9c7d,// 448 PAY 418 

    0xcbb59a90,// 449 PAY 419 

    0xc55c7d40,// 450 PAY 420 

    0xe7238450,// 451 PAY 421 

    0x14661514,// 452 PAY 422 

    0x5f99d960,// 453 PAY 423 

    0x05b0ff6f,// 454 PAY 424 

    0xe2ac95d9,// 455 PAY 425 

    0x04567830,// 456 PAY 426 

    0x05c6c753,// 457 PAY 427 

    0x3985191d,// 458 PAY 428 

    0x543a1b40,// 459 PAY 429 

    0x98605601,// 460 PAY 430 

    0xa72e4ebd,// 461 PAY 431 

    0x7b2e82f0,// 462 PAY 432 

    0x044a8417,// 463 PAY 433 

    0x63212aa7,// 464 PAY 434 

    0x298fcc69,// 465 PAY 435 

    0x13d8efc7,// 466 PAY 436 

    0x2c5479af,// 467 PAY 437 

    0x1a9818bb,// 468 PAY 438 

    0x4b1f612b,// 469 PAY 439 

    0xb8bbfc31,// 470 PAY 440 

    0xb5dc3931,// 471 PAY 441 

    0x2b0ffc06,// 472 PAY 442 

    0xf89363f9,// 473 PAY 443 

    0x3f696293,// 474 PAY 444 

    0x1922eb05,// 475 PAY 445 

    0x7a7f9bf4,// 476 PAY 446 

    0x0680c4d9,// 477 PAY 447 

    0x126c8953,// 478 PAY 448 

    0x06897856,// 479 PAY 449 

    0x6cf67166,// 480 PAY 450 

    0x525ed106,// 481 PAY 451 

    0x7da3a3ca,// 482 PAY 452 

    0x216d4212,// 483 PAY 453 

    0xdfd1539f,// 484 PAY 454 

    0xfe625d3c,// 485 PAY 455 

    0x4213bf1b,// 486 PAY 456 

    0xd7f8834a,// 487 PAY 457 

    0xc4b065b9,// 488 PAY 458 

    0xd5000000,// 489 PAY 459 

/// STA is 1 words. 

/// STA num_pkts       : 178 

/// STA pkt_idx        : 98 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x80 

    0x018880b2 // 490 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt2_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x02 

/// ECH pdu_tag        : 0x00 

    0x00020000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv !insert_icv check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000015,// 3 SCX   1 

    0x80844860,// 4 SCX   2 

    0x000053c4,// 5 SCX   3 

    0xd4b3b33c,// 6 SCX   4 

    0xf9e241f1,// 7 SCX   5 

    0x8decd16d,// 8 SCX   6 

    0x96f87d47,// 9 SCX   7 

    0x7644a376,// 10 SCX   8 

    0xb743db68,// 11 SCX   9 

    0xe86ccc55,// 12 SCX  10 

    0xff18914a,// 13 SCX  11 

    0x333d4184,// 14 SCX  12 

    0xce82bfc8,// 15 SCX  13 

    0x37922e5a,// 16 SCX  14 

    0x85a9f912,// 17 SCX  15 

    0xb72fbaa0,// 18 SCX  16 

    0x8d3bfa85,// 19 SCX  17 

    0x921ef119,// 20 SCX  18 

    0x32929f12,// 21 SCX  19 

    0x95b62db6,// 22 SCX  20 

    0x04449932,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1665 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 1029 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1029 

/// BFD lencrypto      : 832 

/// BFD ofstcrypto     : 188 

/// BFD (ofst+len)cry  : 1020 

/// BFD ofstiv         : 100 

/// BFD ofsticv        : 1440 

    0x00000405,// 24 BFD   1 

    0x00bc0340,// 25 BFD   2 

    0x05a00064,// 26 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c00e19e,// 27 MFM   1 

    0x24878576,// 28 MFM   2 

    0xa3e15c21,// 29 MFM   3 

    0x45f63ac8,// 30 MFM   4 

    0xeb146452,// 31 MFM   5 

    0xcff79a9d,// 32 MFM   6 

    0xfc4a3a28,// 33 MFM   7 

    0x1fafeec1,// 34 MFM   8 

    0x1e8c528a,// 35 MFM   9 

    0x8b53b76f,// 36 MFM  10 

    0x2d4795b2,// 37 MFM  11 

    0x413ce3b4,// 38 MFM  12 

    0x33464422,// 39 MFM  13 

    0x84ca1c7b,// 40 MFM  14 

    0x29b7f3f4,// 41 MFM  15 

    0x8ac19512,// 42 MFM  16 

/// BDA is 418 words. 

/// BDA size     is 1665 (0x681) 

/// BDA id       is 0xb49d 

    0x0681b49d,// 43 BDA   1 

/// PAY Generic Data size   : 1665 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0xf8c4c718,// 44 PAY   1 

    0xd044d0fe,// 45 PAY   2 

    0x62e48565,// 46 PAY   3 

    0x80e5d09e,// 47 PAY   4 

    0x4ba985c9,// 48 PAY   5 

    0x96ad0613,// 49 PAY   6 

    0x291c6b26,// 50 PAY   7 

    0x7866055b,// 51 PAY   8 

    0x7fb216ca,// 52 PAY   9 

    0xe9d07e3b,// 53 PAY  10 

    0x6fdc40b1,// 54 PAY  11 

    0xa55d67f3,// 55 PAY  12 

    0x0b9cc94e,// 56 PAY  13 

    0x424deecf,// 57 PAY  14 

    0xafd36b37,// 58 PAY  15 

    0xf2a582be,// 59 PAY  16 

    0xa0604b7c,// 60 PAY  17 

    0x567a4db5,// 61 PAY  18 

    0x3dcf6fa7,// 62 PAY  19 

    0x62ab18fe,// 63 PAY  20 

    0x80220751,// 64 PAY  21 

    0x5e07eee5,// 65 PAY  22 

    0x500508e9,// 66 PAY  23 

    0x91241e0c,// 67 PAY  24 

    0xb1dd6761,// 68 PAY  25 

    0xa71ba8ed,// 69 PAY  26 

    0xd2853a87,// 70 PAY  27 

    0xf225b47f,// 71 PAY  28 

    0x2911bbde,// 72 PAY  29 

    0xc53a2e43,// 73 PAY  30 

    0x5e329820,// 74 PAY  31 

    0x388b4f7c,// 75 PAY  32 

    0x3eb16c0f,// 76 PAY  33 

    0x0a2dd7ce,// 77 PAY  34 

    0xd58bc84e,// 78 PAY  35 

    0x94abdb09,// 79 PAY  36 

    0x240d9aca,// 80 PAY  37 

    0x9ef06fc3,// 81 PAY  38 

    0xdba1cbeb,// 82 PAY  39 

    0xdba3d296,// 83 PAY  40 

    0x78d375c1,// 84 PAY  41 

    0x188c7d0d,// 85 PAY  42 

    0xd42bad77,// 86 PAY  43 

    0x24474aac,// 87 PAY  44 

    0x1436c8e1,// 88 PAY  45 

    0x2980a233,// 89 PAY  46 

    0x05c683ce,// 90 PAY  47 

    0xbb6ca6f2,// 91 PAY  48 

    0xf4f61256,// 92 PAY  49 

    0x2a4b4b5d,// 93 PAY  50 

    0x76617587,// 94 PAY  51 

    0x7e4caf8d,// 95 PAY  52 

    0xffa71d83,// 96 PAY  53 

    0x67933d7f,// 97 PAY  54 

    0x6d51d5dd,// 98 PAY  55 

    0x71987a0a,// 99 PAY  56 

    0xf43e66ea,// 100 PAY  57 

    0xd2eec87f,// 101 PAY  58 

    0x32da1550,// 102 PAY  59 

    0x9440be64,// 103 PAY  60 

    0xcf519d6e,// 104 PAY  61 

    0x0e8ceae1,// 105 PAY  62 

    0x06de8271,// 106 PAY  63 

    0x891d5fc4,// 107 PAY  64 

    0xa79a3424,// 108 PAY  65 

    0xc2f4ed36,// 109 PAY  66 

    0x368442fe,// 110 PAY  67 

    0x89186ef6,// 111 PAY  68 

    0xa4991709,// 112 PAY  69 

    0xce8c3ad3,// 113 PAY  70 

    0x5edd7bb8,// 114 PAY  71 

    0x3ee578bb,// 115 PAY  72 

    0xcb12ddfd,// 116 PAY  73 

    0xc775659d,// 117 PAY  74 

    0x25564464,// 118 PAY  75 

    0x24af4f8e,// 119 PAY  76 

    0xcc73a349,// 120 PAY  77 

    0x62dc6224,// 121 PAY  78 

    0xc15f1adf,// 122 PAY  79 

    0x6d637ee7,// 123 PAY  80 

    0x8c55ac11,// 124 PAY  81 

    0xac9ac335,// 125 PAY  82 

    0x8a837e02,// 126 PAY  83 

    0xeca7f9aa,// 127 PAY  84 

    0xa8c64cf7,// 128 PAY  85 

    0x149b6770,// 129 PAY  86 

    0xd2cd8080,// 130 PAY  87 

    0xb00b0ac9,// 131 PAY  88 

    0x6037ddac,// 132 PAY  89 

    0x47152267,// 133 PAY  90 

    0x3f2720c6,// 134 PAY  91 

    0x9f1bedf3,// 135 PAY  92 

    0xc8cbdf4e,// 136 PAY  93 

    0x4a5067ce,// 137 PAY  94 

    0x16bd6c45,// 138 PAY  95 

    0x9199b7c8,// 139 PAY  96 

    0x4e9c8d32,// 140 PAY  97 

    0xdfd536ae,// 141 PAY  98 

    0x20afda67,// 142 PAY  99 

    0x5bd742cd,// 143 PAY 100 

    0xdfe5542a,// 144 PAY 101 

    0x34187a72,// 145 PAY 102 

    0x265f5389,// 146 PAY 103 

    0x894b3391,// 147 PAY 104 

    0x8549f53c,// 148 PAY 105 

    0xbe7d7a5b,// 149 PAY 106 

    0xbe6db653,// 150 PAY 107 

    0x52f50b80,// 151 PAY 108 

    0xf2e8b27d,// 152 PAY 109 

    0xec003ec5,// 153 PAY 110 

    0x535d8af5,// 154 PAY 111 

    0x45f738b5,// 155 PAY 112 

    0xf9fdc64c,// 156 PAY 113 

    0x854f27b7,// 157 PAY 114 

    0xac464d81,// 158 PAY 115 

    0xd8cdf20d,// 159 PAY 116 

    0x12b3188c,// 160 PAY 117 

    0x782df160,// 161 PAY 118 

    0xf437478a,// 162 PAY 119 

    0xabc4c19c,// 163 PAY 120 

    0xcf968ca8,// 164 PAY 121 

    0xc3105dbd,// 165 PAY 122 

    0x5c99050d,// 166 PAY 123 

    0xf2252466,// 167 PAY 124 

    0x09450a20,// 168 PAY 125 

    0x7223ae54,// 169 PAY 126 

    0x89c5b538,// 170 PAY 127 

    0x6261778d,// 171 PAY 128 

    0x4efe2dbc,// 172 PAY 129 

    0x71a6b8f5,// 173 PAY 130 

    0xc428d4eb,// 174 PAY 131 

    0xd705cc92,// 175 PAY 132 

    0x19ef5975,// 176 PAY 133 

    0xf29107a0,// 177 PAY 134 

    0x02ffac5a,// 178 PAY 135 

    0x71ffabdd,// 179 PAY 136 

    0x7de8ce7a,// 180 PAY 137 

    0xb5f317cf,// 181 PAY 138 

    0x59bb539f,// 182 PAY 139 

    0xc44fdd81,// 183 PAY 140 

    0xc117a999,// 184 PAY 141 

    0x88bb329c,// 185 PAY 142 

    0x5c4a02b9,// 186 PAY 143 

    0x1a4cb57c,// 187 PAY 144 

    0x66f74103,// 188 PAY 145 

    0x5f9a9ac5,// 189 PAY 146 

    0xf630f851,// 190 PAY 147 

    0xa356191b,// 191 PAY 148 

    0x870cf880,// 192 PAY 149 

    0x02b8505a,// 193 PAY 150 

    0x9f9267cb,// 194 PAY 151 

    0x334b66c2,// 195 PAY 152 

    0xc005da76,// 196 PAY 153 

    0xf634f728,// 197 PAY 154 

    0xea46528c,// 198 PAY 155 

    0x1c7e43b4,// 199 PAY 156 

    0x5dfff8d6,// 200 PAY 157 

    0x83f95e38,// 201 PAY 158 

    0xea6d617c,// 202 PAY 159 

    0x4a44f115,// 203 PAY 160 

    0x7ea459ad,// 204 PAY 161 

    0x88d5bdd5,// 205 PAY 162 

    0x7b4cf846,// 206 PAY 163 

    0xe8ffe9b7,// 207 PAY 164 

    0x5e71aacc,// 208 PAY 165 

    0x2158a5ca,// 209 PAY 166 

    0x8816308f,// 210 PAY 167 

    0xb1adc6b9,// 211 PAY 168 

    0x6d25550e,// 212 PAY 169 

    0xe45ee5ed,// 213 PAY 170 

    0x785a154e,// 214 PAY 171 

    0x42f2d0a5,// 215 PAY 172 

    0xd23d6a9e,// 216 PAY 173 

    0x9b115d78,// 217 PAY 174 

    0xd6a32437,// 218 PAY 175 

    0x940a4a6f,// 219 PAY 176 

    0x67fd4773,// 220 PAY 177 

    0x8e956b7b,// 221 PAY 178 

    0xa745dd88,// 222 PAY 179 

    0x905a3ad3,// 223 PAY 180 

    0x3e4293e0,// 224 PAY 181 

    0x0d5b8393,// 225 PAY 182 

    0x4e242689,// 226 PAY 183 

    0x0c84d580,// 227 PAY 184 

    0x7a009b20,// 228 PAY 185 

    0xf120eda8,// 229 PAY 186 

    0x1498291f,// 230 PAY 187 

    0xa59167d1,// 231 PAY 188 

    0x90d8af80,// 232 PAY 189 

    0xe918d5da,// 233 PAY 190 

    0xc7e14145,// 234 PAY 191 

    0xd80e3513,// 235 PAY 192 

    0xac6939ae,// 236 PAY 193 

    0xf31a42f7,// 237 PAY 194 

    0x9dafb4b3,// 238 PAY 195 

    0xa2ad631e,// 239 PAY 196 

    0xcc3ae9a7,// 240 PAY 197 

    0x5701a56a,// 241 PAY 198 

    0xa7f3e379,// 242 PAY 199 

    0x4ad5d2ee,// 243 PAY 200 

    0xf2ba29a5,// 244 PAY 201 

    0x880809b5,// 245 PAY 202 

    0x2a6a94b6,// 246 PAY 203 

    0xbb150075,// 247 PAY 204 

    0x53a6707b,// 248 PAY 205 

    0xcfc92bbd,// 249 PAY 206 

    0xdd57f918,// 250 PAY 207 

    0x4d0c6a70,// 251 PAY 208 

    0xe065f473,// 252 PAY 209 

    0x3db690d2,// 253 PAY 210 

    0xc80369a9,// 254 PAY 211 

    0x7bebc799,// 255 PAY 212 

    0x19bbe3e3,// 256 PAY 213 

    0xf5d5a28d,// 257 PAY 214 

    0x70f69c16,// 258 PAY 215 

    0xba6043df,// 259 PAY 216 

    0x427871fc,// 260 PAY 217 

    0x6293eaaf,// 261 PAY 218 

    0x955ae1f2,// 262 PAY 219 

    0x9b8cbd1c,// 263 PAY 220 

    0x72013ae4,// 264 PAY 221 

    0xa18b2dce,// 265 PAY 222 

    0xe8643781,// 266 PAY 223 

    0x2890a07f,// 267 PAY 224 

    0xa75851c6,// 268 PAY 225 

    0x7e7208e0,// 269 PAY 226 

    0xa3a5a0bb,// 270 PAY 227 

    0x9943ff0a,// 271 PAY 228 

    0xf16ad6bb,// 272 PAY 229 

    0xdd59d1de,// 273 PAY 230 

    0x75ebf82f,// 274 PAY 231 

    0x7ce74250,// 275 PAY 232 

    0xfb9323cd,// 276 PAY 233 

    0xde089518,// 277 PAY 234 

    0xf6588cf6,// 278 PAY 235 

    0x818ec03a,// 279 PAY 236 

    0x013c530a,// 280 PAY 237 

    0x8b68f62d,// 281 PAY 238 

    0xd8990558,// 282 PAY 239 

    0x89f5cb97,// 283 PAY 240 

    0x4e7d278e,// 284 PAY 241 

    0x1cc58e89,// 285 PAY 242 

    0x06d66688,// 286 PAY 243 

    0xa7764a24,// 287 PAY 244 

    0x82cb8795,// 288 PAY 245 

    0x2f6ecbad,// 289 PAY 246 

    0xc56f3537,// 290 PAY 247 

    0xd67e87de,// 291 PAY 248 

    0x063a88f0,// 292 PAY 249 

    0x0c7942bc,// 293 PAY 250 

    0x5c76ef87,// 294 PAY 251 

    0x30a3e71c,// 295 PAY 252 

    0xc5bd54a7,// 296 PAY 253 

    0x9286957e,// 297 PAY 254 

    0xed9f250f,// 298 PAY 255 

    0x8a1e658a,// 299 PAY 256 

    0x2609394c,// 300 PAY 257 

    0xa2c663d5,// 301 PAY 258 

    0x71cddf17,// 302 PAY 259 

    0xbe8fb0e7,// 303 PAY 260 

    0xc59c35f5,// 304 PAY 261 

    0xacc4fb12,// 305 PAY 262 

    0xf96b41fc,// 306 PAY 263 

    0x65da2988,// 307 PAY 264 

    0xa9dfe988,// 308 PAY 265 

    0x711fb787,// 309 PAY 266 

    0xcee88a88,// 310 PAY 267 

    0xf42ab9f1,// 311 PAY 268 

    0xb12370e7,// 312 PAY 269 

    0x2b59f368,// 313 PAY 270 

    0x95717141,// 314 PAY 271 

    0x43f4e93c,// 315 PAY 272 

    0xd9fe3631,// 316 PAY 273 

    0x417479f6,// 317 PAY 274 

    0xa0f884e0,// 318 PAY 275 

    0x1b1257b3,// 319 PAY 276 

    0x4b856b06,// 320 PAY 277 

    0xb43c3fa1,// 321 PAY 278 

    0xde3286db,// 322 PAY 279 

    0xbf09bc60,// 323 PAY 280 

    0x4d0ea9d9,// 324 PAY 281 

    0x595b6ba4,// 325 PAY 282 

    0xc9523860,// 326 PAY 283 

    0xfa19cda8,// 327 PAY 284 

    0x50065e84,// 328 PAY 285 

    0xfd25ac4a,// 329 PAY 286 

    0x676e0256,// 330 PAY 287 

    0xcc6287be,// 331 PAY 288 

    0x5963b0ae,// 332 PAY 289 

    0xee4bf4f5,// 333 PAY 290 

    0x57946741,// 334 PAY 291 

    0xda59ec12,// 335 PAY 292 

    0x2e52beb8,// 336 PAY 293 

    0xda859d3c,// 337 PAY 294 

    0xc1c61900,// 338 PAY 295 

    0xf5ddc70b,// 339 PAY 296 

    0x54faca7f,// 340 PAY 297 

    0xb1a00dca,// 341 PAY 298 

    0x36c0fe98,// 342 PAY 299 

    0x7f9e50c7,// 343 PAY 300 

    0x60e710e1,// 344 PAY 301 

    0x6f02385b,// 345 PAY 302 

    0x328b8937,// 346 PAY 303 

    0x42cc3475,// 347 PAY 304 

    0xfc7a220b,// 348 PAY 305 

    0x39545885,// 349 PAY 306 

    0x44dc382f,// 350 PAY 307 

    0x7bf17122,// 351 PAY 308 

    0xbb2b6eb0,// 352 PAY 309 

    0xebcbf550,// 353 PAY 310 

    0xb68810aa,// 354 PAY 311 

    0xa7333513,// 355 PAY 312 

    0x43b49ea7,// 356 PAY 313 

    0x47990243,// 357 PAY 314 

    0x4cedf958,// 358 PAY 315 

    0xf953d373,// 359 PAY 316 

    0xf4180637,// 360 PAY 317 

    0x9f2fccae,// 361 PAY 318 

    0xbdc9aac4,// 362 PAY 319 

    0xf5d18ff0,// 363 PAY 320 

    0x4fc99ebe,// 364 PAY 321 

    0xbe6017be,// 365 PAY 322 

    0x17a86db6,// 366 PAY 323 

    0x861baa0e,// 367 PAY 324 

    0x4d5f68c8,// 368 PAY 325 

    0xd1449091,// 369 PAY 326 

    0x769e8b0b,// 370 PAY 327 

    0xe3ad286d,// 371 PAY 328 

    0x7fc0bd05,// 372 PAY 329 

    0xb755a713,// 373 PAY 330 

    0x5671e0ee,// 374 PAY 331 

    0xaa2d6f95,// 375 PAY 332 

    0x2c1735fc,// 376 PAY 333 

    0x54cbf907,// 377 PAY 334 

    0x2391f994,// 378 PAY 335 

    0xe6081dc4,// 379 PAY 336 

    0x20c988b1,// 380 PAY 337 

    0x66544887,// 381 PAY 338 

    0x7b61de34,// 382 PAY 339 

    0x31561d13,// 383 PAY 340 

    0x930043ef,// 384 PAY 341 

    0x0ad1ebe9,// 385 PAY 342 

    0xf8cac3a6,// 386 PAY 343 

    0xecfabfb2,// 387 PAY 344 

    0x72f0e74d,// 388 PAY 345 

    0xfbeb434a,// 389 PAY 346 

    0x430343e5,// 390 PAY 347 

    0x46afeb4a,// 391 PAY 348 

    0xca0e97de,// 392 PAY 349 

    0x3d73eb96,// 393 PAY 350 

    0x5ea15a03,// 394 PAY 351 

    0xed58a651,// 395 PAY 352 

    0xddffb565,// 396 PAY 353 

    0xd5664c4f,// 397 PAY 354 

    0x3c3448ca,// 398 PAY 355 

    0x1ac0ff70,// 399 PAY 356 

    0x09fe17b4,// 400 PAY 357 

    0x507d31c7,// 401 PAY 358 

    0x49334560,// 402 PAY 359 

    0x7303b13a,// 403 PAY 360 

    0x8d19d014,// 404 PAY 361 

    0x19a1cdc6,// 405 PAY 362 

    0xd9f97847,// 406 PAY 363 

    0x365cd26f,// 407 PAY 364 

    0x2f1d68ee,// 408 PAY 365 

    0xfd7a4061,// 409 PAY 366 

    0xad4a7438,// 410 PAY 367 

    0x504f8d54,// 411 PAY 368 

    0x81dadc6f,// 412 PAY 369 

    0x5b049b7e,// 413 PAY 370 

    0xa1d21a76,// 414 PAY 371 

    0x476bfe7e,// 415 PAY 372 

    0xa799e80d,// 416 PAY 373 

    0x2371051b,// 417 PAY 374 

    0x3c13b123,// 418 PAY 375 

    0xb89a46a0,// 419 PAY 376 

    0xe4f5bf21,// 420 PAY 377 

    0xe3f1ed2b,// 421 PAY 378 

    0x01599d7a,// 422 PAY 379 

    0x05f786d9,// 423 PAY 380 

    0xfc0b495b,// 424 PAY 381 

    0x9b7a6db0,// 425 PAY 382 

    0x473b73e1,// 426 PAY 383 

    0xd352d10a,// 427 PAY 384 

    0x06ccec57,// 428 PAY 385 

    0xcc420b0e,// 429 PAY 386 

    0x4f0bcdea,// 430 PAY 387 

    0x33e3953d,// 431 PAY 388 

    0x5d550d43,// 432 PAY 389 

    0x395db758,// 433 PAY 390 

    0x428cbcaa,// 434 PAY 391 

    0x4e6068a0,// 435 PAY 392 

    0x2f4c05e0,// 436 PAY 393 

    0x3f5fa874,// 437 PAY 394 

    0xaec0807d,// 438 PAY 395 

    0x4f4966c2,// 439 PAY 396 

    0x63ab750b,// 440 PAY 397 

    0x4f5ad259,// 441 PAY 398 

    0x1025ea48,// 442 PAY 399 

    0x2b578b01,// 443 PAY 400 

    0xd684ed22,// 444 PAY 401 

    0x0ab8df84,// 445 PAY 402 

    0x30ba45a8,// 446 PAY 403 

    0xf56e83e7,// 447 PAY 404 

    0xfc1c20ab,// 448 PAY 405 

    0xc50c0a9c,// 449 PAY 406 

    0xd7db82ae,// 450 PAY 407 

    0x2f8cfc5f,// 451 PAY 408 

    0xc230c120,// 452 PAY 409 

    0x81d30183,// 453 PAY 410 

    0xc386d8f9,// 454 PAY 411 

    0xb79e7a02,// 455 PAY 412 

    0x13824bfb,// 456 PAY 413 

    0x8e34d0a2,// 457 PAY 414 

    0x70b7a004,// 458 PAY 415 

    0xb40780b6,// 459 PAY 416 

    0x54000000,// 460 PAY 417 

/// STA is 1 words. 

/// STA num_pkts       : 74 

/// STA pkt_idx        : 189 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xe9 

    0x02f5e94a // 461 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt3_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x09 

/// ECH pdu_tag        : 0x00 

    0x00090000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x2 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000019,// 3 SCX   1 

    0x808648c1,// 4 SCX   2 

    0x000042c4,// 5 SCX   3 

    0xe6aa0b24,// 6 SCX   4 

    0x83be153d,// 7 SCX   5 

    0xab049046,// 8 SCX   6 

    0xdd485063,// 9 SCX   7 

    0x2c65f334,// 10 SCX   8 

    0x1f1062a2,// 11 SCX   9 

    0xfb27e466,// 12 SCX  10 

    0x2f534b8f,// 13 SCX  11 

    0x6f66ce36,// 14 SCX  12 

    0x9a32ffc5,// 15 SCX  13 

    0x76c4b48b,// 16 SCX  14 

    0xbd55b020,// 17 SCX  15 

    0x02537519,// 18 SCX  16 

    0x209140c7,// 19 SCX  17 

    0x85e1f745,// 20 SCX  18 

    0xb7a3d9e9,// 21 SCX  19 

    0x615a0175,// 22 SCX  20 

    0xbc00af74,// 23 SCX  21 

    0x304c2868,// 24 SCX  22 

    0x1cda680f,// 25 SCX  23 

    0x4dcef08c,// 26 SCX  24 

    0x63e7647f,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 1055 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 432 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 432 

/// BFD lencrypto      : 176 

/// BFD ofstcrypto     : 208 

/// BFD (ofst+len)cry  : 384 

/// BFD ofstiv         : 120 

/// BFD ofsticv        : 860 

    0x000001b0,// 28 BFD   1 

    0x00d000b0,// 29 BFD   2 

    0x035c0078,// 30 BFD   3 

/// MFM is 1 words. 

/// MFM vldnibs        : 2 

    0x0200e400,// 31 MFM   1 

/// BDA is 265 words. 

/// BDA size     is 1055 (0x41f) 

/// BDA id       is 0x61e 

    0x041f061e,// 32 BDA   1 

/// PAY Generic Data size   : 1055 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0xd04c17e5,// 33 PAY   1 

    0x7af956f3,// 34 PAY   2 

    0xce50f284,// 35 PAY   3 

    0xe7bed5f3,// 36 PAY   4 

    0x323ef08e,// 37 PAY   5 

    0x62d0e779,// 38 PAY   6 

    0x81f8f0ba,// 39 PAY   7 

    0x1cd9f79e,// 40 PAY   8 

    0xd43057e8,// 41 PAY   9 

    0x7ce9d632,// 42 PAY  10 

    0x594b464d,// 43 PAY  11 

    0x65141b2b,// 44 PAY  12 

    0xbeae74f3,// 45 PAY  13 

    0xf034c156,// 46 PAY  14 

    0x05af7156,// 47 PAY  15 

    0x2f6e49e2,// 48 PAY  16 

    0xeeb59942,// 49 PAY  17 

    0xa11b51f8,// 50 PAY  18 

    0x264a7311,// 51 PAY  19 

    0x3f640eba,// 52 PAY  20 

    0x582b163e,// 53 PAY  21 

    0xf0a4d3c0,// 54 PAY  22 

    0x1883ef56,// 55 PAY  23 

    0x3ae39f11,// 56 PAY  24 

    0xef23ef70,// 57 PAY  25 

    0x554a3cc2,// 58 PAY  26 

    0xc3874185,// 59 PAY  27 

    0x8ff4a023,// 60 PAY  28 

    0xe9144cf4,// 61 PAY  29 

    0xbec2531a,// 62 PAY  30 

    0xfef7ae99,// 63 PAY  31 

    0xcecd9f33,// 64 PAY  32 

    0x8e8467d3,// 65 PAY  33 

    0x691d51d0,// 66 PAY  34 

    0x053d5f45,// 67 PAY  35 

    0x69e48bf5,// 68 PAY  36 

    0xe428776b,// 69 PAY  37 

    0x323f382c,// 70 PAY  38 

    0x3ca1cec9,// 71 PAY  39 

    0x1e77bd66,// 72 PAY  40 

    0x6388ee59,// 73 PAY  41 

    0xc915c172,// 74 PAY  42 

    0x8c789ebc,// 75 PAY  43 

    0xc8ad18db,// 76 PAY  44 

    0xc2883ebc,// 77 PAY  45 

    0x4adc7a7d,// 78 PAY  46 

    0x8954472e,// 79 PAY  47 

    0xb82a20f0,// 80 PAY  48 

    0xe400a2c8,// 81 PAY  49 

    0xa150c4f1,// 82 PAY  50 

    0x1073df46,// 83 PAY  51 

    0x72549864,// 84 PAY  52 

    0x4fda3341,// 85 PAY  53 

    0x3d1e6e52,// 86 PAY  54 

    0x6328bd08,// 87 PAY  55 

    0xa40d6b95,// 88 PAY  56 

    0x773b39de,// 89 PAY  57 

    0x9e9916c4,// 90 PAY  58 

    0xf3c8a7ac,// 91 PAY  59 

    0x04537c26,// 92 PAY  60 

    0xc31ed5bf,// 93 PAY  61 

    0x01f039df,// 94 PAY  62 

    0x50aa1d7a,// 95 PAY  63 

    0x0489186f,// 96 PAY  64 

    0x5a2a2c23,// 97 PAY  65 

    0xfe720b2b,// 98 PAY  66 

    0x00a9bc19,// 99 PAY  67 

    0xcb1c4f60,// 100 PAY  68 

    0xf1755257,// 101 PAY  69 

    0x203411f9,// 102 PAY  70 

    0x3b9abb7f,// 103 PAY  71 

    0x1a970df4,// 104 PAY  72 

    0x3e77666c,// 105 PAY  73 

    0x81e156a8,// 106 PAY  74 

    0xb9adbbcc,// 107 PAY  75 

    0x72a603d8,// 108 PAY  76 

    0x0774a334,// 109 PAY  77 

    0x2a554af5,// 110 PAY  78 

    0x2ced2a58,// 111 PAY  79 

    0xf2b24031,// 112 PAY  80 

    0x09ca4da2,// 113 PAY  81 

    0xe9db09d3,// 114 PAY  82 

    0x792b57e1,// 115 PAY  83 

    0x6d67d658,// 116 PAY  84 

    0x4359ddbd,// 117 PAY  85 

    0xd59366bc,// 118 PAY  86 

    0x3c9531bc,// 119 PAY  87 

    0x2bdc3b34,// 120 PAY  88 

    0x43ee0d57,// 121 PAY  89 

    0x26b14a62,// 122 PAY  90 

    0xc86aaa76,// 123 PAY  91 

    0x20299e06,// 124 PAY  92 

    0x7aa21947,// 125 PAY  93 

    0xc16d15d1,// 126 PAY  94 

    0x95b51d89,// 127 PAY  95 

    0x8473143a,// 128 PAY  96 

    0x564e9d14,// 129 PAY  97 

    0x2aae6dfe,// 130 PAY  98 

    0x94860e0b,// 131 PAY  99 

    0xcb54ff3c,// 132 PAY 100 

    0x70e6514e,// 133 PAY 101 

    0xbae5598a,// 134 PAY 102 

    0x5d4dc8d6,// 135 PAY 103 

    0xfedf7321,// 136 PAY 104 

    0x49293cff,// 137 PAY 105 

    0xf3040369,// 138 PAY 106 

    0xc8bafd8f,// 139 PAY 107 

    0xc0bbd333,// 140 PAY 108 

    0xac1e3992,// 141 PAY 109 

    0xe9413114,// 142 PAY 110 

    0x39cd5886,// 143 PAY 111 

    0xa9f9aaa5,// 144 PAY 112 

    0xec2ff718,// 145 PAY 113 

    0x06d86028,// 146 PAY 114 

    0x1b3b93b7,// 147 PAY 115 

    0xc3ed43c3,// 148 PAY 116 

    0x921ce0d2,// 149 PAY 117 

    0x6ee2da95,// 150 PAY 118 

    0x95db2eeb,// 151 PAY 119 

    0xb757293a,// 152 PAY 120 

    0xd3dd244f,// 153 PAY 121 

    0x28eaf696,// 154 PAY 122 

    0x3a398fdf,// 155 PAY 123 

    0xccad862a,// 156 PAY 124 

    0x84cc2aca,// 157 PAY 125 

    0x9172410a,// 158 PAY 126 

    0x4cad7e69,// 159 PAY 127 

    0xafc44977,// 160 PAY 128 

    0x9508aa75,// 161 PAY 129 

    0x3d809c0a,// 162 PAY 130 

    0x2ee894d7,// 163 PAY 131 

    0x8ddfccb1,// 164 PAY 132 

    0xccbf6805,// 165 PAY 133 

    0x8d40b13f,// 166 PAY 134 

    0xaa40fd23,// 167 PAY 135 

    0x5483b58e,// 168 PAY 136 

    0x7c986ebd,// 169 PAY 137 

    0xe46dc773,// 170 PAY 138 

    0xe68c5697,// 171 PAY 139 

    0xd2df36e2,// 172 PAY 140 

    0xe9c186d3,// 173 PAY 141 

    0xbd3af3a6,// 174 PAY 142 

    0x1b8996dc,// 175 PAY 143 

    0x04907115,// 176 PAY 144 

    0x148b6a12,// 177 PAY 145 

    0xb14666c5,// 178 PAY 146 

    0x3c6e92db,// 179 PAY 147 

    0x6a64e33b,// 180 PAY 148 

    0x08861609,// 181 PAY 149 

    0x9a3b9c36,// 182 PAY 150 

    0xdd73023e,// 183 PAY 151 

    0x5bf1cdf6,// 184 PAY 152 

    0xd58c18c3,// 185 PAY 153 

    0x1709557b,// 186 PAY 154 

    0x5cfc8303,// 187 PAY 155 

    0xc857ccbe,// 188 PAY 156 

    0xbb854fe9,// 189 PAY 157 

    0x61704a96,// 190 PAY 158 

    0x2de19050,// 191 PAY 159 

    0x6cef3f79,// 192 PAY 160 

    0x8d217784,// 193 PAY 161 

    0xbbde8cf6,// 194 PAY 162 

    0xbb8df29e,// 195 PAY 163 

    0x45458a13,// 196 PAY 164 

    0xe251ffda,// 197 PAY 165 

    0x1fc5b97c,// 198 PAY 166 

    0x4f842917,// 199 PAY 167 

    0x9a3f944e,// 200 PAY 168 

    0x6bc05cbb,// 201 PAY 169 

    0xe72e1447,// 202 PAY 170 

    0x3f462a38,// 203 PAY 171 

    0x092889a5,// 204 PAY 172 

    0x07598579,// 205 PAY 173 

    0xab0f0791,// 206 PAY 174 

    0x19531121,// 207 PAY 175 

    0xd11e23d7,// 208 PAY 176 

    0x062bc80c,// 209 PAY 177 

    0xce02506f,// 210 PAY 178 

    0x616f463e,// 211 PAY 179 

    0x3ac3f73b,// 212 PAY 180 

    0x31896526,// 213 PAY 181 

    0x3aa9ea22,// 214 PAY 182 

    0xd3ec24ba,// 215 PAY 183 

    0x946cb132,// 216 PAY 184 

    0xdf8244f1,// 217 PAY 185 

    0xf1fcc299,// 218 PAY 186 

    0x7c014a04,// 219 PAY 187 

    0x564610b2,// 220 PAY 188 

    0x1ac19a52,// 221 PAY 189 

    0x550953da,// 222 PAY 190 

    0xd7ca0016,// 223 PAY 191 

    0x0dd23a12,// 224 PAY 192 

    0xc010d7c6,// 225 PAY 193 

    0xacf93d95,// 226 PAY 194 

    0xc33b71c6,// 227 PAY 195 

    0x87bdc006,// 228 PAY 196 

    0x12a2546c,// 229 PAY 197 

    0x3b5ec29d,// 230 PAY 198 

    0x14481049,// 231 PAY 199 

    0x063f989a,// 232 PAY 200 

    0xc79b8dcf,// 233 PAY 201 

    0x7d38acae,// 234 PAY 202 

    0xcc3d19af,// 235 PAY 203 

    0x538b5843,// 236 PAY 204 

    0x55602636,// 237 PAY 205 

    0xed2d46bf,// 238 PAY 206 

    0x5c071b69,// 239 PAY 207 

    0x91715ce7,// 240 PAY 208 

    0x7a634502,// 241 PAY 209 

    0xa6cf9901,// 242 PAY 210 

    0x5c986634,// 243 PAY 211 

    0x7fdf6220,// 244 PAY 212 

    0x71769269,// 245 PAY 213 

    0x42a860b4,// 246 PAY 214 

    0xff39845b,// 247 PAY 215 

    0x82b915c8,// 248 PAY 216 

    0xf40a34b3,// 249 PAY 217 

    0x5e938aac,// 250 PAY 218 

    0x17d5cc18,// 251 PAY 219 

    0xc2e52025,// 252 PAY 220 

    0x4fac1fb6,// 253 PAY 221 

    0x9c763460,// 254 PAY 222 

    0xea614b56,// 255 PAY 223 

    0xdda8d7d3,// 256 PAY 224 

    0x52ab3fc4,// 257 PAY 225 

    0xb935bfaf,// 258 PAY 226 

    0x24195a12,// 259 PAY 227 

    0xede5f7d0,// 260 PAY 228 

    0x496d2430,// 261 PAY 229 

    0x1a6b4bd6,// 262 PAY 230 

    0x3197afe2,// 263 PAY 231 

    0x9e9e3b8d,// 264 PAY 232 

    0x161896f3,// 265 PAY 233 

    0xa574d79a,// 266 PAY 234 

    0x89574d46,// 267 PAY 235 

    0x63908fa4,// 268 PAY 236 

    0xb6187b02,// 269 PAY 237 

    0x8dd603d1,// 270 PAY 238 

    0x9e17b3cf,// 271 PAY 239 

    0x22c21190,// 272 PAY 240 

    0xdf1b0444,// 273 PAY 241 

    0xc1483cbd,// 274 PAY 242 

    0x0066d0bc,// 275 PAY 243 

    0x365987cf,// 276 PAY 244 

    0xd9cae268,// 277 PAY 245 

    0x1a706a8b,// 278 PAY 246 

    0x9dfd8079,// 279 PAY 247 

    0xca0e74cb,// 280 PAY 248 

    0x2f3ac9ec,// 281 PAY 249 

    0x53198637,// 282 PAY 250 

    0x74215705,// 283 PAY 251 

    0x8b19721f,// 284 PAY 252 

    0x75136567,// 285 PAY 253 

    0x0a79f9bb,// 286 PAY 254 

    0x96aab64c,// 287 PAY 255 

    0xe6d1535d,// 288 PAY 256 

    0x414d9c39,// 289 PAY 257 

    0x49da01da,// 290 PAY 258 

    0xc8729d9c,// 291 PAY 259 

    0x8d1ab53f,// 292 PAY 260 

    0x35c32306,// 293 PAY 261 

    0x8041832a,// 294 PAY 262 

    0xff31377c,// 295 PAY 263 

    0xec9fff00,// 296 PAY 264 

/// STA is 1 words. 

/// STA num_pkts       : 112 

/// STA pkt_idx        : 18 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xb1 

    0x0049b170 // 297 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt4_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x04 

/// ECH pdu_tag        : 0x00 

    0x00040000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv !check_icv !sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x8086480d,// 4 SCX   2 

    0x00002444,// 5 SCX   3 

    0xc0645da5,// 6 SCX   4 

    0x8fffafda,// 7 SCX   5 

    0xfc0309a2,// 8 SCX   6 

    0xb82a091b,// 9 SCX   7 

    0x0c2db65d,// 10 SCX   8 

    0x5a5ea9a4,// 11 SCX   9 

    0xce8cea98,// 12 SCX  10 

    0xe03d5480,// 13 SCX  11 

    0xc503262a,// 14 SCX  12 

    0xfaa6d17a,// 15 SCX  13 

    0x0e004ff2,// 16 SCX  14 

    0xa0c6d91c,// 17 SCX  15 

    0x5893dd9f,// 18 SCX  16 

    0x193d62e5,// 19 SCX  17 

    0x7316f137,// 20 SCX  18 

    0xdabd5c4b,// 21 SCX  19 

    0x1a1a0212,// 22 SCX  20 

    0x2ee9aac3,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1368 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 413 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 413 

/// BFD lencrypto      : 48 

/// BFD ofstcrypto     : 160 

/// BFD (ofst+len)cry  : 208 

/// BFD ofstiv         : 144 

/// BFD ofsticv        : 624 

    0x0000019d,// 24 BFD   1 

    0x00a00030,// 25 BFD   2 

    0x02700090,// 26 BFD   3 

/// MFM is 3 words. 

/// MFM vldnibs        : 14 

    0x1400b571,// 27 MFM   1 

    0x82fa2f9a,// 28 MFM   2 

    0xc29a4470,// 29 MFM   3 

/// BDA is 343 words. 

/// BDA size     is 1368 (0x558) 

/// BDA id       is 0xff9 

    0x05580ff9,// 30 BDA   1 

/// PAY Generic Data size   : 1368 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0xea989e54,// 31 PAY   1 

    0x8eea52ee,// 32 PAY   2 

    0x8a4131eb,// 33 PAY   3 

    0xa8a1f5bc,// 34 PAY   4 

    0xebd1656c,// 35 PAY   5 

    0x1c62b056,// 36 PAY   6 

    0x251138c1,// 37 PAY   7 

    0xec940eb4,// 38 PAY   8 

    0x7a0b0f93,// 39 PAY   9 

    0x8c95142c,// 40 PAY  10 

    0x8c913966,// 41 PAY  11 

    0x7f161322,// 42 PAY  12 

    0x63d87181,// 43 PAY  13 

    0x12dce921,// 44 PAY  14 

    0x60fc63be,// 45 PAY  15 

    0xca2c0ce9,// 46 PAY  16 

    0x0189f2f5,// 47 PAY  17 

    0x23be0521,// 48 PAY  18 

    0xf5af28c5,// 49 PAY  19 

    0xb33541a4,// 50 PAY  20 

    0x54b3f0a4,// 51 PAY  21 

    0xa0a892c3,// 52 PAY  22 

    0x2f7add54,// 53 PAY  23 

    0xffd48f48,// 54 PAY  24 

    0x332e5e30,// 55 PAY  25 

    0x9e3bab1d,// 56 PAY  26 

    0xdd2c213f,// 57 PAY  27 

    0x80199b26,// 58 PAY  28 

    0x5515f5a9,// 59 PAY  29 

    0x12c0c768,// 60 PAY  30 

    0x9eba46df,// 61 PAY  31 

    0xa4a2e735,// 62 PAY  32 

    0xb70b2cdb,// 63 PAY  33 

    0xb2969f02,// 64 PAY  34 

    0x0ff14b60,// 65 PAY  35 

    0xae5949dc,// 66 PAY  36 

    0xc81ff3ae,// 67 PAY  37 

    0x6dbd3f29,// 68 PAY  38 

    0x58012212,// 69 PAY  39 

    0x38952af9,// 70 PAY  40 

    0x2274aa0d,// 71 PAY  41 

    0xed370384,// 72 PAY  42 

    0xb044e6c6,// 73 PAY  43 

    0xfffab55e,// 74 PAY  44 

    0xa8b8ca70,// 75 PAY  45 

    0xf72d5625,// 76 PAY  46 

    0x2d762eb7,// 77 PAY  47 

    0x0df65d3f,// 78 PAY  48 

    0x629969a3,// 79 PAY  49 

    0x37327ddb,// 80 PAY  50 

    0xc2de564e,// 81 PAY  51 

    0x5e5e0227,// 82 PAY  52 

    0x78a66043,// 83 PAY  53 

    0x01a66b40,// 84 PAY  54 

    0x149b28d5,// 85 PAY  55 

    0x5eb509c6,// 86 PAY  56 

    0x5999fec8,// 87 PAY  57 

    0x05f3d303,// 88 PAY  58 

    0x3dd0a538,// 89 PAY  59 

    0xf918eb79,// 90 PAY  60 

    0x66f53a89,// 91 PAY  61 

    0x1b6b702e,// 92 PAY  62 

    0xfb098168,// 93 PAY  63 

    0xc7244f94,// 94 PAY  64 

    0x15957908,// 95 PAY  65 

    0xf5f0f351,// 96 PAY  66 

    0x3a28b326,// 97 PAY  67 

    0xc0b06a6c,// 98 PAY  68 

    0x4d1170b7,// 99 PAY  69 

    0xb3d6bc2e,// 100 PAY  70 

    0x9f1d2506,// 101 PAY  71 

    0x2c6d887c,// 102 PAY  72 

    0xfa084936,// 103 PAY  73 

    0xae61a1a9,// 104 PAY  74 

    0xc71d5ecc,// 105 PAY  75 

    0x4fbc93db,// 106 PAY  76 

    0x76d2646b,// 107 PAY  77 

    0x08726d42,// 108 PAY  78 

    0xe156bd29,// 109 PAY  79 

    0xaed28808,// 110 PAY  80 

    0xb23e39ab,// 111 PAY  81 

    0xd1394bd2,// 112 PAY  82 

    0x6a78b792,// 113 PAY  83 

    0xf5e12253,// 114 PAY  84 

    0xd1a26b74,// 115 PAY  85 

    0xd9834e71,// 116 PAY  86 

    0x411ce544,// 117 PAY  87 

    0x03403e62,// 118 PAY  88 

    0x2e1309bf,// 119 PAY  89 

    0x1658b21a,// 120 PAY  90 

    0x08158030,// 121 PAY  91 

    0x0d6188b9,// 122 PAY  92 

    0xe24d2852,// 123 PAY  93 

    0x1ce1cd18,// 124 PAY  94 

    0x319f9c76,// 125 PAY  95 

    0xa0ce4a30,// 126 PAY  96 

    0x06cca2f2,// 127 PAY  97 

    0x6ebde4f8,// 128 PAY  98 

    0xe9d5650e,// 129 PAY  99 

    0x3fd5ddfe,// 130 PAY 100 

    0x95d7c6f5,// 131 PAY 101 

    0x57ac95ee,// 132 PAY 102 

    0xabef10aa,// 133 PAY 103 

    0x9f1a6a4d,// 134 PAY 104 

    0x0ebf9a21,// 135 PAY 105 

    0x2275be2b,// 136 PAY 106 

    0xc602a1e3,// 137 PAY 107 

    0xc1edb958,// 138 PAY 108 

    0x32e3d11c,// 139 PAY 109 

    0x419dc441,// 140 PAY 110 

    0x7b36e09e,// 141 PAY 111 

    0x91188066,// 142 PAY 112 

    0x08479f0b,// 143 PAY 113 

    0xb8dd2a57,// 144 PAY 114 

    0xc097c2ff,// 145 PAY 115 

    0x1367f776,// 146 PAY 116 

    0x81f907ce,// 147 PAY 117 

    0x34282708,// 148 PAY 118 

    0x7e23c4c6,// 149 PAY 119 

    0x3a969b7f,// 150 PAY 120 

    0x6fbaad6b,// 151 PAY 121 

    0xab7bc195,// 152 PAY 122 

    0xfdcc0d88,// 153 PAY 123 

    0x39d8a792,// 154 PAY 124 

    0x6fe04cd5,// 155 PAY 125 

    0x6601ab0e,// 156 PAY 126 

    0x114077e9,// 157 PAY 127 

    0x61d67aea,// 158 PAY 128 

    0xffce4e53,// 159 PAY 129 

    0x4b1d80d9,// 160 PAY 130 

    0xc1826c27,// 161 PAY 131 

    0xc05e976a,// 162 PAY 132 

    0x6f33d59c,// 163 PAY 133 

    0x33d5f7a0,// 164 PAY 134 

    0xe752a62d,// 165 PAY 135 

    0xa4dd64e0,// 166 PAY 136 

    0x197f7050,// 167 PAY 137 

    0x9560544f,// 168 PAY 138 

    0x0ce1bda5,// 169 PAY 139 

    0x49fcc4a0,// 170 PAY 140 

    0x50aad7c5,// 171 PAY 141 

    0x7a275c10,// 172 PAY 142 

    0x0d58c4d9,// 173 PAY 143 

    0xf17d53d8,// 174 PAY 144 

    0xebaf035c,// 175 PAY 145 

    0xc7b719b9,// 176 PAY 146 

    0x4e92774d,// 177 PAY 147 

    0xb318fdc0,// 178 PAY 148 

    0xa61f20e4,// 179 PAY 149 

    0x9b958d8c,// 180 PAY 150 

    0x38b78576,// 181 PAY 151 

    0x719f4034,// 182 PAY 152 

    0x02f104b5,// 183 PAY 153 

    0xe7cf4f94,// 184 PAY 154 

    0x4bfeb1e4,// 185 PAY 155 

    0x261750aa,// 186 PAY 156 

    0xa3b43eaf,// 187 PAY 157 

    0xfa12511d,// 188 PAY 158 

    0x3550aa5f,// 189 PAY 159 

    0xc087d6a9,// 190 PAY 160 

    0x5674e8f2,// 191 PAY 161 

    0x97cd8465,// 192 PAY 162 

    0x26cbc071,// 193 PAY 163 

    0xe2f18a5b,// 194 PAY 164 

    0x0c581b81,// 195 PAY 165 

    0x169a511f,// 196 PAY 166 

    0xf0822e00,// 197 PAY 167 

    0xa3d4f244,// 198 PAY 168 

    0xabb8c7dc,// 199 PAY 169 

    0xebc9af26,// 200 PAY 170 

    0xab6b3a09,// 201 PAY 171 

    0x10fff074,// 202 PAY 172 

    0x286b888b,// 203 PAY 173 

    0xea096397,// 204 PAY 174 

    0x0b7625c5,// 205 PAY 175 

    0x1e22a1fa,// 206 PAY 176 

    0xba6d9f93,// 207 PAY 177 

    0xd5103fd0,// 208 PAY 178 

    0x5b43f707,// 209 PAY 179 

    0x3999a3e1,// 210 PAY 180 

    0xb965b572,// 211 PAY 181 

    0xa0be3ddb,// 212 PAY 182 

    0x86886fcb,// 213 PAY 183 

    0x767f6714,// 214 PAY 184 

    0x5efabefd,// 215 PAY 185 

    0x806240d3,// 216 PAY 186 

    0x82aec060,// 217 PAY 187 

    0xe9242b16,// 218 PAY 188 

    0xa2ca9945,// 219 PAY 189 

    0xe9d042b5,// 220 PAY 190 

    0xf3dfd3b3,// 221 PAY 191 

    0xe58e8894,// 222 PAY 192 

    0xb7d2eb29,// 223 PAY 193 

    0x37f30db6,// 224 PAY 194 

    0xae60fef4,// 225 PAY 195 

    0xf9ca6f34,// 226 PAY 196 

    0xec46874f,// 227 PAY 197 

    0xa1411e50,// 228 PAY 198 

    0xa1122187,// 229 PAY 199 

    0xf56cffb3,// 230 PAY 200 

    0x519d9535,// 231 PAY 201 

    0x0b20f663,// 232 PAY 202 

    0x4c9e71f3,// 233 PAY 203 

    0xe920706c,// 234 PAY 204 

    0x5a8ae925,// 235 PAY 205 

    0xf8469d1d,// 236 PAY 206 

    0x49803992,// 237 PAY 207 

    0x1b1dd737,// 238 PAY 208 

    0x259e6564,// 239 PAY 209 

    0xc0c588cc,// 240 PAY 210 

    0x3aca694a,// 241 PAY 211 

    0x44a8ae8d,// 242 PAY 212 

    0xf30cfd39,// 243 PAY 213 

    0x0fb84b9d,// 244 PAY 214 

    0x3b38a440,// 245 PAY 215 

    0xe0f1c8e1,// 246 PAY 216 

    0xd5cd688a,// 247 PAY 217 

    0x79975295,// 248 PAY 218 

    0x6f974ac1,// 249 PAY 219 

    0x15bd5ac2,// 250 PAY 220 

    0xf51a7066,// 251 PAY 221 

    0x884643e5,// 252 PAY 222 

    0xd4c883b4,// 253 PAY 223 

    0xd2074cc2,// 254 PAY 224 

    0x1236f982,// 255 PAY 225 

    0xe2d6647f,// 256 PAY 226 

    0x5e1f9c6c,// 257 PAY 227 

    0xca6e7799,// 258 PAY 228 

    0xfb1dcef8,// 259 PAY 229 

    0x9f5dd788,// 260 PAY 230 

    0x9140dcef,// 261 PAY 231 

    0xa07f388d,// 262 PAY 232 

    0x76228c11,// 263 PAY 233 

    0xb723558f,// 264 PAY 234 

    0x5839d60e,// 265 PAY 235 

    0x96e6f013,// 266 PAY 236 

    0xc9ad4130,// 267 PAY 237 

    0x2c10edc5,// 268 PAY 238 

    0xc1125f0a,// 269 PAY 239 

    0x810bdd94,// 270 PAY 240 

    0x74547d5b,// 271 PAY 241 

    0x771adbc8,// 272 PAY 242 

    0x8449a0f9,// 273 PAY 243 

    0xee1d001d,// 274 PAY 244 

    0x26ea03b9,// 275 PAY 245 

    0x31d1f29e,// 276 PAY 246 

    0x94eeff8e,// 277 PAY 247 

    0x4cce2ba9,// 278 PAY 248 

    0xcca7b8d1,// 279 PAY 249 

    0x39ac02b2,// 280 PAY 250 

    0x54164aa5,// 281 PAY 251 

    0xca2171a8,// 282 PAY 252 

    0x6fc94125,// 283 PAY 253 

    0xea8c836e,// 284 PAY 254 

    0xca2ec021,// 285 PAY 255 

    0xdf7d8e2f,// 286 PAY 256 

    0x39cb04f2,// 287 PAY 257 

    0x176c2eee,// 288 PAY 258 

    0x91288d2a,// 289 PAY 259 

    0x805af8d3,// 290 PAY 260 

    0xe0ab3045,// 291 PAY 261 

    0x9abab7ab,// 292 PAY 262 

    0x15411725,// 293 PAY 263 

    0x19d51e81,// 294 PAY 264 

    0xc3eea0a4,// 295 PAY 265 

    0xa5eeb0fa,// 296 PAY 266 

    0xd9175722,// 297 PAY 267 

    0xef5d7979,// 298 PAY 268 

    0xc0a49e3b,// 299 PAY 269 

    0xc31dd90a,// 300 PAY 270 

    0x8f75b43a,// 301 PAY 271 

    0x911387c6,// 302 PAY 272 

    0xdd196165,// 303 PAY 273 

    0x80891f91,// 304 PAY 274 

    0xc27be148,// 305 PAY 275 

    0x4be6cd7f,// 306 PAY 276 

    0x1afb867d,// 307 PAY 277 

    0x2f5f1906,// 308 PAY 278 

    0xf6a85682,// 309 PAY 279 

    0xae7fecd0,// 310 PAY 280 

    0xb98dfd0d,// 311 PAY 281 

    0xb859a1d1,// 312 PAY 282 

    0x5e61dc5a,// 313 PAY 283 

    0xd313b45b,// 314 PAY 284 

    0x44e27be6,// 315 PAY 285 

    0x698e99e2,// 316 PAY 286 

    0xeb9c28a6,// 317 PAY 287 

    0xc6796000,// 318 PAY 288 

    0xceb51b2a,// 319 PAY 289 

    0x4369590d,// 320 PAY 290 

    0xf09180c7,// 321 PAY 291 

    0x6e2c74aa,// 322 PAY 292 

    0x2f4c8f2f,// 323 PAY 293 

    0xe166630f,// 324 PAY 294 

    0x591eea35,// 325 PAY 295 

    0x289d4a01,// 326 PAY 296 

    0x6e6d27f6,// 327 PAY 297 

    0x8a584178,// 328 PAY 298 

    0x19690323,// 329 PAY 299 

    0xf2c6759f,// 330 PAY 300 

    0xe6143753,// 331 PAY 301 

    0x3c0c0a2f,// 332 PAY 302 

    0x38dd2a46,// 333 PAY 303 

    0xc13b4b76,// 334 PAY 304 

    0x081e6094,// 335 PAY 305 

    0x712d9918,// 336 PAY 306 

    0x9e3c4e33,// 337 PAY 307 

    0x2a397e8a,// 338 PAY 308 

    0xbe05741c,// 339 PAY 309 

    0xe4ca2a3c,// 340 PAY 310 

    0x7452a6a0,// 341 PAY 311 

    0x783dd5d5,// 342 PAY 312 

    0x7584517d,// 343 PAY 313 

    0x2c7f7a9f,// 344 PAY 314 

    0xf8798061,// 345 PAY 315 

    0x42d783db,// 346 PAY 316 

    0x8171576e,// 347 PAY 317 

    0x2423ca39,// 348 PAY 318 

    0x910e9f79,// 349 PAY 319 

    0x960acfd4,// 350 PAY 320 

    0x99ba4681,// 351 PAY 321 

    0xeef62ea6,// 352 PAY 322 

    0xccc6f040,// 353 PAY 323 

    0xe078e32d,// 354 PAY 324 

    0xcb285c3a,// 355 PAY 325 

    0x4f360876,// 356 PAY 326 

    0x5e658a7c,// 357 PAY 327 

    0x48a3dbef,// 358 PAY 328 

    0xacfb1914,// 359 PAY 329 

    0xd2b9861d,// 360 PAY 330 

    0x40c4e0bd,// 361 PAY 331 

    0x66d086f0,// 362 PAY 332 

    0x94d2db5d,// 363 PAY 333 

    0x05711aa5,// 364 PAY 334 

    0x8cc85540,// 365 PAY 335 

    0xe6500b6a,// 366 PAY 336 

    0x056bafdf,// 367 PAY 337 

    0x5f9cc538,// 368 PAY 338 

    0x064a442e,// 369 PAY 339 

    0x3232eae9,// 370 PAY 340 

    0xca61caa7,// 371 PAY 341 

    0x67233c7b,// 372 PAY 342 

/// STA is 1 words. 

/// STA num_pkts       : 162 

/// STA pkt_idx        : 20 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xce 

    0x0051cea2 // 373 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt5_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x0d 

/// ECH pdu_tag        : 0x00 

    0x000d0000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv !insert_icv check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000019,// 3 SCX   1 

    0x809248aa,// 4 SCX   2 

    0x000013c2,// 5 SCX   3 

    0x407bf5fe,// 6 SCX   4 

    0x52c1f895,// 7 SCX   5 

    0x06b6fe8a,// 8 SCX   6 

    0xfac4dccd,// 9 SCX   7 

    0x60d0a013,// 10 SCX   8 

    0xa76b19de,// 11 SCX   9 

    0x45af4e26,// 12 SCX  10 

    0xa28faf97,// 13 SCX  11 

    0xc581d6c7,// 14 SCX  12 

    0xb8a4eb6e,// 15 SCX  13 

    0x8642474a,// 16 SCX  14 

    0x42f220f1,// 17 SCX  15 

    0x67f213b9,// 18 SCX  16 

    0xc6969c97,// 19 SCX  17 

    0x22852d37,// 20 SCX  18 

    0x7281c970,// 21 SCX  19 

    0x498fe167,// 22 SCX  20 

    0x949935cc,// 23 SCX  21 

    0xa95b62d3,// 24 SCX  22 

    0xa27b4bf0,// 25 SCX  23 

    0x2f913d52,// 26 SCX  24 

    0xb03d584d,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 1023 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 118 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 118 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 92 

/// BFD (ofst+len)cry  : 108 

/// BFD ofstiv         : 60 

/// BFD ofsticv        : 460 

    0x00000076,// 28 BFD   1 

    0x005c0010,// 29 BFD   2 

    0x01cc003c,// 30 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : b 

    0x0b000d6d,// 31 MFM   1 

    0x3d0758d0,// 32 MFM   2 

/// BDA is 257 words. 

/// BDA size     is 1023 (0x3ff) 

/// BDA id       is 0x93b0 

    0x03ff93b0,// 33 BDA   1 

/// PAY Generic Data size   : 1023 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0x59d1b362,// 34 PAY   1 

    0x57c98d37,// 35 PAY   2 

    0x7a3efdd9,// 36 PAY   3 

    0x5d903373,// 37 PAY   4 

    0x24977305,// 38 PAY   5 

    0xe5f33d44,// 39 PAY   6 

    0xe229de08,// 40 PAY   7 

    0x21aac376,// 41 PAY   8 

    0xb2fac023,// 42 PAY   9 

    0xdd47f109,// 43 PAY  10 

    0x2d09540c,// 44 PAY  11 

    0x6fef7a76,// 45 PAY  12 

    0xc0f1dbca,// 46 PAY  13 

    0x7e3a891d,// 47 PAY  14 

    0x83541e8b,// 48 PAY  15 

    0x70e3e409,// 49 PAY  16 

    0x9b5ff111,// 50 PAY  17 

    0xff68919b,// 51 PAY  18 

    0xfc9214db,// 52 PAY  19 

    0x5fe1b731,// 53 PAY  20 

    0x034e5b41,// 54 PAY  21 

    0xde562dc4,// 55 PAY  22 

    0x8a73e7db,// 56 PAY  23 

    0x4f072c8a,// 57 PAY  24 

    0x9f435408,// 58 PAY  25 

    0xe44abea9,// 59 PAY  26 

    0x227cd3f0,// 60 PAY  27 

    0x44bff8eb,// 61 PAY  28 

    0xaa921814,// 62 PAY  29 

    0xab847e90,// 63 PAY  30 

    0x971ced09,// 64 PAY  31 

    0xd208e989,// 65 PAY  32 

    0xf44d39db,// 66 PAY  33 

    0xf19e8d82,// 67 PAY  34 

    0xa3bcce12,// 68 PAY  35 

    0x0aed7bd1,// 69 PAY  36 

    0xda77313a,// 70 PAY  37 

    0xe2376b44,// 71 PAY  38 

    0x27f42c92,// 72 PAY  39 

    0x89cde1ca,// 73 PAY  40 

    0xd5976ae1,// 74 PAY  41 

    0xbc01e94a,// 75 PAY  42 

    0x16994d5c,// 76 PAY  43 

    0x50e4f419,// 77 PAY  44 

    0x62efe5e1,// 78 PAY  45 

    0x629f2b70,// 79 PAY  46 

    0x0d2f706c,// 80 PAY  47 

    0xd74a9f0a,// 81 PAY  48 

    0xbfc1545e,// 82 PAY  49 

    0x4f8e809c,// 83 PAY  50 

    0x2787a00a,// 84 PAY  51 

    0x3a1efd31,// 85 PAY  52 

    0x8b33d09b,// 86 PAY  53 

    0x44f1a928,// 87 PAY  54 

    0xb4c6d43c,// 88 PAY  55 

    0x4b2c7086,// 89 PAY  56 

    0x3114cb4f,// 90 PAY  57 

    0xb3b6ed98,// 91 PAY  58 

    0x65c16a6a,// 92 PAY  59 

    0xbfd23329,// 93 PAY  60 

    0xfaba8290,// 94 PAY  61 

    0x15a91658,// 95 PAY  62 

    0x19545ebc,// 96 PAY  63 

    0x682de205,// 97 PAY  64 

    0xd2ba7d85,// 98 PAY  65 

    0x00731536,// 99 PAY  66 

    0x5694961c,// 100 PAY  67 

    0x07ba647a,// 101 PAY  68 

    0xacc17492,// 102 PAY  69 

    0x4e195ec9,// 103 PAY  70 

    0xb543a5a3,// 104 PAY  71 

    0xdb263012,// 105 PAY  72 

    0x0dfcba16,// 106 PAY  73 

    0x81206f23,// 107 PAY  74 

    0x7746552c,// 108 PAY  75 

    0xa354d7aa,// 109 PAY  76 

    0xa735a3f5,// 110 PAY  77 

    0x66c6d0f4,// 111 PAY  78 

    0x04c4fe3d,// 112 PAY  79 

    0xbc3f84d5,// 113 PAY  80 

    0x7ac81727,// 114 PAY  81 

    0x618d7df0,// 115 PAY  82 

    0x6c4c6496,// 116 PAY  83 

    0xb65831b3,// 117 PAY  84 

    0xc80b2d97,// 118 PAY  85 

    0xe3226c77,// 119 PAY  86 

    0x0c686975,// 120 PAY  87 

    0x66238639,// 121 PAY  88 

    0xebaed710,// 122 PAY  89 

    0x5f929bdb,// 123 PAY  90 

    0x4b18110d,// 124 PAY  91 

    0x2d8667ad,// 125 PAY  92 

    0x4d3acf27,// 126 PAY  93 

    0x0391732b,// 127 PAY  94 

    0x424eeed2,// 128 PAY  95 

    0x405cb24d,// 129 PAY  96 

    0xf9204515,// 130 PAY  97 

    0xa6b77428,// 131 PAY  98 

    0x25361eef,// 132 PAY  99 

    0x21837dea,// 133 PAY 100 

    0x220ba498,// 134 PAY 101 

    0xa56757ca,// 135 PAY 102 

    0x2d8f45ac,// 136 PAY 103 

    0xa0d8b69f,// 137 PAY 104 

    0xe4dd469f,// 138 PAY 105 

    0xd455dbfe,// 139 PAY 106 

    0x1a08ce26,// 140 PAY 107 

    0x83769481,// 141 PAY 108 

    0xd97e1991,// 142 PAY 109 

    0x8f548ad5,// 143 PAY 110 

    0x481e0dbc,// 144 PAY 111 

    0x6726df13,// 145 PAY 112 

    0xa6341b60,// 146 PAY 113 

    0xfec6b5a0,// 147 PAY 114 

    0x64fc355e,// 148 PAY 115 

    0x54c2b099,// 149 PAY 116 

    0x99aa2a45,// 150 PAY 117 

    0xd6ba65c7,// 151 PAY 118 

    0x1a5dde5b,// 152 PAY 119 

    0xac487086,// 153 PAY 120 

    0x7048ba43,// 154 PAY 121 

    0x7dfdd403,// 155 PAY 122 

    0xc90d273e,// 156 PAY 123 

    0x89f59d36,// 157 PAY 124 

    0xb1f21401,// 158 PAY 125 

    0xea329323,// 159 PAY 126 

    0x25f93c23,// 160 PAY 127 

    0xaba90f16,// 161 PAY 128 

    0x8df48c9b,// 162 PAY 129 

    0x3a279d15,// 163 PAY 130 

    0xd8bc76f0,// 164 PAY 131 

    0xd5eace1e,// 165 PAY 132 

    0x56040dde,// 166 PAY 133 

    0xc7e267f6,// 167 PAY 134 

    0x281c0737,// 168 PAY 135 

    0x39a8205c,// 169 PAY 136 

    0x56e4ef63,// 170 PAY 137 

    0xec946fd3,// 171 PAY 138 

    0x92dc9189,// 172 PAY 139 

    0x00907085,// 173 PAY 140 

    0xed17b073,// 174 PAY 141 

    0xceab558e,// 175 PAY 142 

    0xe07cffeb,// 176 PAY 143 

    0x1a971b55,// 177 PAY 144 

    0xac654b74,// 178 PAY 145 

    0xa90072fd,// 179 PAY 146 

    0x231e42f4,// 180 PAY 147 

    0xc8d280b3,// 181 PAY 148 

    0x2f987dea,// 182 PAY 149 

    0x680c5e26,// 183 PAY 150 

    0x46058317,// 184 PAY 151 

    0x6bb53c81,// 185 PAY 152 

    0x8bb77b36,// 186 PAY 153 

    0x0e313818,// 187 PAY 154 

    0x095884fd,// 188 PAY 155 

    0x235b3e2c,// 189 PAY 156 

    0x9cde9b2a,// 190 PAY 157 

    0x2e2eb3c7,// 191 PAY 158 

    0x29442113,// 192 PAY 159 

    0x0f79478f,// 193 PAY 160 

    0x6fc6912c,// 194 PAY 161 

    0x0ddd8e01,// 195 PAY 162 

    0x7960a675,// 196 PAY 163 

    0xb23f8763,// 197 PAY 164 

    0xefbeada4,// 198 PAY 165 

    0x111f6a63,// 199 PAY 166 

    0x048c5824,// 200 PAY 167 

    0x6a806133,// 201 PAY 168 

    0x29669e83,// 202 PAY 169 

    0x3939a336,// 203 PAY 170 

    0x4738f1d3,// 204 PAY 171 

    0x05bfb21b,// 205 PAY 172 

    0xe52755ea,// 206 PAY 173 

    0xb155d2d4,// 207 PAY 174 

    0x090b2692,// 208 PAY 175 

    0x240d7587,// 209 PAY 176 

    0xaa63f8e2,// 210 PAY 177 

    0xbf9fb463,// 211 PAY 178 

    0xc29f5465,// 212 PAY 179 

    0x4c96f744,// 213 PAY 180 

    0x9ac83963,// 214 PAY 181 

    0x4c21950f,// 215 PAY 182 

    0x1bb79612,// 216 PAY 183 

    0xa48facd4,// 217 PAY 184 

    0x46f50d14,// 218 PAY 185 

    0x5cc428a6,// 219 PAY 186 

    0x5a66fbe0,// 220 PAY 187 

    0x842f3294,// 221 PAY 188 

    0xab320fee,// 222 PAY 189 

    0xaeac5cf4,// 223 PAY 190 

    0xb51f6938,// 224 PAY 191 

    0x47bb99d8,// 225 PAY 192 

    0x84d33b3f,// 226 PAY 193 

    0x38dbe5f9,// 227 PAY 194 

    0xf758cad5,// 228 PAY 195 

    0xe693179b,// 229 PAY 196 

    0x408939a1,// 230 PAY 197 

    0x37088aad,// 231 PAY 198 

    0x6886f4fc,// 232 PAY 199 

    0xb7dbf3aa,// 233 PAY 200 

    0x539ce4b4,// 234 PAY 201 

    0xe5c3197f,// 235 PAY 202 

    0x8b4b1587,// 236 PAY 203 

    0x30ea8b14,// 237 PAY 204 

    0x3e0c3e94,// 238 PAY 205 

    0x4077cd1c,// 239 PAY 206 

    0x9ca3dce7,// 240 PAY 207 

    0xc50a2ef6,// 241 PAY 208 

    0xd6922192,// 242 PAY 209 

    0x82a06c66,// 243 PAY 210 

    0x25216ef5,// 244 PAY 211 

    0x3daf8bfc,// 245 PAY 212 

    0x39668c99,// 246 PAY 213 

    0xe796b2d5,// 247 PAY 214 

    0xd83ed91f,// 248 PAY 215 

    0xd2d42f83,// 249 PAY 216 

    0x799589fb,// 250 PAY 217 

    0xd64c09bb,// 251 PAY 218 

    0xbfa2ebd3,// 252 PAY 219 

    0xab08170d,// 253 PAY 220 

    0xc590fb79,// 254 PAY 221 

    0xd16e6897,// 255 PAY 222 

    0xe365d1d7,// 256 PAY 223 

    0x1a67f705,// 257 PAY 224 

    0x739977cc,// 258 PAY 225 

    0x301d899c,// 259 PAY 226 

    0xd900ed29,// 260 PAY 227 

    0x288a5f64,// 261 PAY 228 

    0xbda180e9,// 262 PAY 229 

    0x96ed50dd,// 263 PAY 230 

    0x9ed543f0,// 264 PAY 231 

    0x8c778dd8,// 265 PAY 232 

    0xdd67ea7e,// 266 PAY 233 

    0xa887f619,// 267 PAY 234 

    0x1f55f9a9,// 268 PAY 235 

    0x518ef4c3,// 269 PAY 236 

    0xcb978c95,// 270 PAY 237 

    0xc47680a3,// 271 PAY 238 

    0x09130ec7,// 272 PAY 239 

    0x972f83d5,// 273 PAY 240 

    0xabfad66b,// 274 PAY 241 

    0x1c837fe9,// 275 PAY 242 

    0xe79b17a9,// 276 PAY 243 

    0x975c9814,// 277 PAY 244 

    0x22218f2a,// 278 PAY 245 

    0xc304e40b,// 279 PAY 246 

    0xeee17a05,// 280 PAY 247 

    0xe4ff9d49,// 281 PAY 248 

    0xc0d20ca8,// 282 PAY 249 

    0xe2cac35f,// 283 PAY 250 

    0xa1cca8a2,// 284 PAY 251 

    0xcc7d6769,// 285 PAY 252 

    0x299eb807,// 286 PAY 253 

    0x78a5597c,// 287 PAY 254 

    0xa6ef2b5a,// 288 PAY 255 

    0xc06dce00,// 289 PAY 256 

/// STA is 1 words. 

/// STA num_pkts       : 83 

/// STA pkt_idx        : 146 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x20 

    0x02492053 // 290 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt6_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x0a 

/// ECH pdu_tag        : 0x00 

    0x000a0000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000015,// 3 SCX   1 

    0x809048e9,// 4 SCX   2 

    0x000023c2,// 5 SCX   3 

    0xd1c8ac66,// 6 SCX   4 

    0xa979ed35,// 7 SCX   5 

    0xf50fb0ac,// 8 SCX   6 

    0x20c5a458,// 9 SCX   7 

    0x37301214,// 10 SCX   8 

    0x99bf3fc8,// 11 SCX   9 

    0x05615006,// 12 SCX  10 

    0x16f66a60,// 13 SCX  11 

    0x1b4a4a2d,// 14 SCX  12 

    0x5cd40f54,// 15 SCX  13 

    0xe677f69c,// 16 SCX  14 

    0x7e633525,// 17 SCX  15 

    0xf115518f,// 18 SCX  16 

    0x1ea8eed3,// 19 SCX  17 

    0x7cbea924,// 20 SCX  18 

    0x4b36fae8,// 21 SCX  19 

    0x23a4f8ff,// 22 SCX  20 

    0xf3ea8453,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1748 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 243 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 243 

/// BFD lencrypto      : 68 

/// BFD ofstcrypto     : 108 

/// BFD (ofst+len)cry  : 176 

/// BFD ofstiv         : 28 

/// BFD ofsticv        : 324 

    0x000000f3,// 24 BFD   1 

    0x006c0044,// 25 BFD   2 

    0x0144001c,// 26 BFD   3 

/// MFM is 5 words. 

/// MFM vldnibs        : 20 

    0x20000421,// 27 MFM   1 

    0x5a1b28ef,// 28 MFM   2 

    0x5c067128,// 29 MFM   3 

    0x0f72edde,// 30 MFM   4 

    0x0a9b0000,// 31 MFM   5 

/// BDA is 438 words. 

/// BDA size     is 1748 (0x6d4) 

/// BDA id       is 0x4456 

    0x06d44456,// 32 BDA   1 

/// PAY Generic Data size   : 1748 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0x89b21f43,// 33 PAY   1 

    0xd4bf5993,// 34 PAY   2 

    0xadb47145,// 35 PAY   3 

    0xd9092b51,// 36 PAY   4 

    0xc14524a9,// 37 PAY   5 

    0x87f025f0,// 38 PAY   6 

    0x9a295bd5,// 39 PAY   7 

    0x904c8ccd,// 40 PAY   8 

    0x8d6854ee,// 41 PAY   9 

    0xd8789317,// 42 PAY  10 

    0x7dd54cef,// 43 PAY  11 

    0x02b7ba9f,// 44 PAY  12 

    0x8e3f6e31,// 45 PAY  13 

    0xd6364921,// 46 PAY  14 

    0x6b7ef026,// 47 PAY  15 

    0x3d24e4ec,// 48 PAY  16 

    0x05dc83de,// 49 PAY  17 

    0x932c642b,// 50 PAY  18 

    0xcdef9ea3,// 51 PAY  19 

    0x99ca566d,// 52 PAY  20 

    0x2d173e2e,// 53 PAY  21 

    0xe23013f7,// 54 PAY  22 

    0xc2912c64,// 55 PAY  23 

    0x5c171651,// 56 PAY  24 

    0x0abbed7b,// 57 PAY  25 

    0x740fc007,// 58 PAY  26 

    0xcd872d37,// 59 PAY  27 

    0xd5fbcd20,// 60 PAY  28 

    0x7f63f010,// 61 PAY  29 

    0x47ed8830,// 62 PAY  30 

    0x42e1aec7,// 63 PAY  31 

    0x44fa2d67,// 64 PAY  32 

    0xd0e77fa7,// 65 PAY  33 

    0xd5a501cc,// 66 PAY  34 

    0xd4e09b33,// 67 PAY  35 

    0xfb568742,// 68 PAY  36 

    0x57f3c612,// 69 PAY  37 

    0xe1086526,// 70 PAY  38 

    0xc5a1e39a,// 71 PAY  39 

    0x68121f78,// 72 PAY  40 

    0xf9fc1723,// 73 PAY  41 

    0xe04764c2,// 74 PAY  42 

    0x1c25c3e6,// 75 PAY  43 

    0xfa6ff584,// 76 PAY  44 

    0x4ad433d1,// 77 PAY  45 

    0xa0adae45,// 78 PAY  46 

    0xceb9c9b8,// 79 PAY  47 

    0x21beb450,// 80 PAY  48 

    0xf1054681,// 81 PAY  49 

    0xfeec6ee0,// 82 PAY  50 

    0xf2b3f9e3,// 83 PAY  51 

    0xebf110e6,// 84 PAY  52 

    0xa604a2a6,// 85 PAY  53 

    0x0d81bb6e,// 86 PAY  54 

    0xa3d22408,// 87 PAY  55 

    0x98735146,// 88 PAY  56 

    0x9cac3a6b,// 89 PAY  57 

    0x80a72f43,// 90 PAY  58 

    0xb8d7f1ed,// 91 PAY  59 

    0x8e611b31,// 92 PAY  60 

    0x9d892b7f,// 93 PAY  61 

    0xe13f7273,// 94 PAY  62 

    0xa9a4a75d,// 95 PAY  63 

    0x686f0b9c,// 96 PAY  64 

    0x9b427b8a,// 97 PAY  65 

    0x43b761d7,// 98 PAY  66 

    0xc6ade130,// 99 PAY  67 

    0x24cd7bfb,// 100 PAY  68 

    0x789cb381,// 101 PAY  69 

    0x6e9241d9,// 102 PAY  70 

    0x6de90ad5,// 103 PAY  71 

    0xeda8470b,// 104 PAY  72 

    0x67223435,// 105 PAY  73 

    0xe5357e40,// 106 PAY  74 

    0x9c05ef5f,// 107 PAY  75 

    0x9fb07655,// 108 PAY  76 

    0x1dfdb57a,// 109 PAY  77 

    0x5f058879,// 110 PAY  78 

    0x5f37921d,// 111 PAY  79 

    0xa7dcc3f4,// 112 PAY  80 

    0xef661c74,// 113 PAY  81 

    0x46ebf169,// 114 PAY  82 

    0xd8099092,// 115 PAY  83 

    0x08d0bf55,// 116 PAY  84 

    0x1c2a6329,// 117 PAY  85 

    0x8b4e8044,// 118 PAY  86 

    0x642c96a0,// 119 PAY  87 

    0x87395eb5,// 120 PAY  88 

    0xf60fb5c3,// 121 PAY  89 

    0x76925841,// 122 PAY  90 

    0x2873ede5,// 123 PAY  91 

    0x1493eb0f,// 124 PAY  92 

    0xa58aed0c,// 125 PAY  93 

    0xe06bb36d,// 126 PAY  94 

    0xd59e695d,// 127 PAY  95 

    0x74d1f9b7,// 128 PAY  96 

    0xdc17b52a,// 129 PAY  97 

    0x3103242c,// 130 PAY  98 

    0x95da9776,// 131 PAY  99 

    0x33ad7110,// 132 PAY 100 

    0x88b62a17,// 133 PAY 101 

    0x01987dc8,// 134 PAY 102 

    0xd675e4c1,// 135 PAY 103 

    0x07d5e376,// 136 PAY 104 

    0xaaec28f5,// 137 PAY 105 

    0x3752f0b3,// 138 PAY 106 

    0x69bc8db6,// 139 PAY 107 

    0x7ebdd597,// 140 PAY 108 

    0x8c814f7e,// 141 PAY 109 

    0xf7d659b9,// 142 PAY 110 

    0xbeed46ed,// 143 PAY 111 

    0x0b704ec9,// 144 PAY 112 

    0xa5c8f69d,// 145 PAY 113 

    0x24c91bd8,// 146 PAY 114 

    0x08fb3091,// 147 PAY 115 

    0x91ed390c,// 148 PAY 116 

    0x59c732cc,// 149 PAY 117 

    0x27042b42,// 150 PAY 118 

    0x88e6166e,// 151 PAY 119 

    0x13d5af35,// 152 PAY 120 

    0xba4b4963,// 153 PAY 121 

    0x526a5518,// 154 PAY 122 

    0x8e9dab28,// 155 PAY 123 

    0x7082dde0,// 156 PAY 124 

    0x83c07b70,// 157 PAY 125 

    0xffee1d25,// 158 PAY 126 

    0x86d6d12f,// 159 PAY 127 

    0xd39fcb20,// 160 PAY 128 

    0x1b05a45a,// 161 PAY 129 

    0xe5855ba4,// 162 PAY 130 

    0x0c3fd84d,// 163 PAY 131 

    0xac5e9a9f,// 164 PAY 132 

    0x37cbe98f,// 165 PAY 133 

    0xa86edb60,// 166 PAY 134 

    0xc44509b4,// 167 PAY 135 

    0x4a92ae32,// 168 PAY 136 

    0xe1270a08,// 169 PAY 137 

    0xe80f58fd,// 170 PAY 138 

    0x30bf9db3,// 171 PAY 139 

    0xf1cef3d4,// 172 PAY 140 

    0x22f4d1ae,// 173 PAY 141 

    0xa78ed5e0,// 174 PAY 142 

    0xfcb0143e,// 175 PAY 143 

    0xfc9819d8,// 176 PAY 144 

    0x543b2d8d,// 177 PAY 145 

    0x18166120,// 178 PAY 146 

    0xd974cb27,// 179 PAY 147 

    0xb71c5a56,// 180 PAY 148 

    0x5cc1d42a,// 181 PAY 149 

    0xd53fba8d,// 182 PAY 150 

    0xadb7eae7,// 183 PAY 151 

    0x068d1d97,// 184 PAY 152 

    0x1f3a5114,// 185 PAY 153 

    0xe43006ba,// 186 PAY 154 

    0x7b3bec11,// 187 PAY 155 

    0xf639d4f8,// 188 PAY 156 

    0x30b1cdac,// 189 PAY 157 

    0xe3614b00,// 190 PAY 158 

    0xa6d06b99,// 191 PAY 159 

    0x40d01937,// 192 PAY 160 

    0x2964d657,// 193 PAY 161 

    0x77e5caed,// 194 PAY 162 

    0xe0717519,// 195 PAY 163 

    0x2392827c,// 196 PAY 164 

    0xd816075e,// 197 PAY 165 

    0x53d6f83d,// 198 PAY 166 

    0xfd2a8ae5,// 199 PAY 167 

    0x27ed129f,// 200 PAY 168 

    0x95339c85,// 201 PAY 169 

    0x2ea5a47e,// 202 PAY 170 

    0xf01a3c00,// 203 PAY 171 

    0x557f9118,// 204 PAY 172 

    0x4295a6d5,// 205 PAY 173 

    0x895e79fc,// 206 PAY 174 

    0xea90ce7b,// 207 PAY 175 

    0x171a393a,// 208 PAY 176 

    0xce4f1998,// 209 PAY 177 

    0xefe5203c,// 210 PAY 178 

    0x9d1e0e61,// 211 PAY 179 

    0x00b71487,// 212 PAY 180 

    0x55331314,// 213 PAY 181 

    0xe79af46a,// 214 PAY 182 

    0x1f3d9024,// 215 PAY 183 

    0x1a003c4c,// 216 PAY 184 

    0xcee3d0ba,// 217 PAY 185 

    0xd9e97424,// 218 PAY 186 

    0xad06e774,// 219 PAY 187 

    0xdc1cb956,// 220 PAY 188 

    0xf38c9868,// 221 PAY 189 

    0xb8d1bfcb,// 222 PAY 190 

    0x2d444f57,// 223 PAY 191 

    0x0b13d700,// 224 PAY 192 

    0x1db93204,// 225 PAY 193 

    0xdc1dcfa9,// 226 PAY 194 

    0x22e3f602,// 227 PAY 195 

    0x85dd48f4,// 228 PAY 196 

    0x86452ea7,// 229 PAY 197 

    0x1b77eeeb,// 230 PAY 198 

    0xb7bb5b86,// 231 PAY 199 

    0x7ce6055b,// 232 PAY 200 

    0x0fe70c4b,// 233 PAY 201 

    0x108a770b,// 234 PAY 202 

    0x68def0bc,// 235 PAY 203 

    0x1278d898,// 236 PAY 204 

    0xe158b050,// 237 PAY 205 

    0x9883d88c,// 238 PAY 206 

    0xadad07dd,// 239 PAY 207 

    0x635db64b,// 240 PAY 208 

    0x4333b690,// 241 PAY 209 

    0xff372dd3,// 242 PAY 210 

    0xf3ce2e42,// 243 PAY 211 

    0x8f9e36d1,// 244 PAY 212 

    0x2a0b4ff1,// 245 PAY 213 

    0x2fd24b58,// 246 PAY 214 

    0x4b9236e1,// 247 PAY 215 

    0x171f0376,// 248 PAY 216 

    0x8bba280e,// 249 PAY 217 

    0x948bc3c8,// 250 PAY 218 

    0xebd92812,// 251 PAY 219 

    0x26fe8434,// 252 PAY 220 

    0x955c8cc6,// 253 PAY 221 

    0x8d59d506,// 254 PAY 222 

    0x1d85baef,// 255 PAY 223 

    0x0d44d39a,// 256 PAY 224 

    0xf038a808,// 257 PAY 225 

    0x5a45ea17,// 258 PAY 226 

    0x1dc8c391,// 259 PAY 227 

    0x6999e266,// 260 PAY 228 

    0x4cd32da7,// 261 PAY 229 

    0x289383c2,// 262 PAY 230 

    0x7250ca89,// 263 PAY 231 

    0x706aea8f,// 264 PAY 232 

    0x1bac50e1,// 265 PAY 233 

    0x56304ff0,// 266 PAY 234 

    0x6956f12e,// 267 PAY 235 

    0x15d70d1d,// 268 PAY 236 

    0xbb8aea55,// 269 PAY 237 

    0x66037fae,// 270 PAY 238 

    0xabc38722,// 271 PAY 239 

    0x414bd574,// 272 PAY 240 

    0xd59170c0,// 273 PAY 241 

    0x7f333b9d,// 274 PAY 242 

    0xa70497b5,// 275 PAY 243 

    0x248bca3d,// 276 PAY 244 

    0xf17f2aa0,// 277 PAY 245 

    0x56291fb6,// 278 PAY 246 

    0xcea91870,// 279 PAY 247 

    0x93d4956d,// 280 PAY 248 

    0x4d8409e3,// 281 PAY 249 

    0x67ca620d,// 282 PAY 250 

    0x654b1bde,// 283 PAY 251 

    0xc4cef84d,// 284 PAY 252 

    0x13b2d1b7,// 285 PAY 253 

    0x03fd1f04,// 286 PAY 254 

    0x9cf71d85,// 287 PAY 255 

    0x3102b2ba,// 288 PAY 256 

    0xa2eab23a,// 289 PAY 257 

    0x5cc5071f,// 290 PAY 258 

    0xae13f401,// 291 PAY 259 

    0x672a6420,// 292 PAY 260 

    0x2ca93146,// 293 PAY 261 

    0xeb59fcf5,// 294 PAY 262 

    0x99c14911,// 295 PAY 263 

    0x2a472931,// 296 PAY 264 

    0x07cce5a5,// 297 PAY 265 

    0xc80f05e3,// 298 PAY 266 

    0x85c4a973,// 299 PAY 267 

    0xa23cdc22,// 300 PAY 268 

    0xc140fbc2,// 301 PAY 269 

    0xbf62f425,// 302 PAY 270 

    0x5bd96823,// 303 PAY 271 

    0xf2e5ab45,// 304 PAY 272 

    0xf09c2ac7,// 305 PAY 273 

    0x083fd084,// 306 PAY 274 

    0x27774f88,// 307 PAY 275 

    0xa491c271,// 308 PAY 276 

    0xe7711103,// 309 PAY 277 

    0x7456aaa9,// 310 PAY 278 

    0xac4d04ed,// 311 PAY 279 

    0x4198a83f,// 312 PAY 280 

    0x204f2cc5,// 313 PAY 281 

    0x0ff26bef,// 314 PAY 282 

    0xd75e4eee,// 315 PAY 283 

    0x18e63571,// 316 PAY 284 

    0xb5eba53e,// 317 PAY 285 

    0x318567de,// 318 PAY 286 

    0x45d5eb28,// 319 PAY 287 

    0x2117e443,// 320 PAY 288 

    0xeb3474db,// 321 PAY 289 

    0xb2cdb58b,// 322 PAY 290 

    0x8f96612f,// 323 PAY 291 

    0x20fbe3aa,// 324 PAY 292 

    0xbb332ac9,// 325 PAY 293 

    0x0aa49b37,// 326 PAY 294 

    0xf9dafab1,// 327 PAY 295 

    0xe55db4cc,// 328 PAY 296 

    0x9e600a70,// 329 PAY 297 

    0xdd2a6bd1,// 330 PAY 298 

    0xd2d7f14e,// 331 PAY 299 

    0xc67c34f5,// 332 PAY 300 

    0xaa166dbc,// 333 PAY 301 

    0x640524dd,// 334 PAY 302 

    0xa47b144c,// 335 PAY 303 

    0xab4b809b,// 336 PAY 304 

    0xa2da8e78,// 337 PAY 305 

    0xf560e23e,// 338 PAY 306 

    0xd0afa329,// 339 PAY 307 

    0x71ea0bcb,// 340 PAY 308 

    0x6fa17160,// 341 PAY 309 

    0x39f7fe3f,// 342 PAY 310 

    0xec32211a,// 343 PAY 311 

    0xc922d321,// 344 PAY 312 

    0x353bba67,// 345 PAY 313 

    0x8a26c74a,// 346 PAY 314 

    0x340afb63,// 347 PAY 315 

    0x1b670d8e,// 348 PAY 316 

    0x796b0f3f,// 349 PAY 317 

    0x1c358c30,// 350 PAY 318 

    0xba187d41,// 351 PAY 319 

    0x02163283,// 352 PAY 320 

    0xd0873f0b,// 353 PAY 321 

    0xd3325c42,// 354 PAY 322 

    0x87e3d1f4,// 355 PAY 323 

    0x905c78e9,// 356 PAY 324 

    0x92f13eda,// 357 PAY 325 

    0xbc2ed5f1,// 358 PAY 326 

    0x4f81a5e3,// 359 PAY 327 

    0x099380c9,// 360 PAY 328 

    0x80373502,// 361 PAY 329 

    0xffec6106,// 362 PAY 330 

    0x8449f286,// 363 PAY 331 

    0xb041ac21,// 364 PAY 332 

    0x181dc405,// 365 PAY 333 

    0xafc2050e,// 366 PAY 334 

    0x719a6f19,// 367 PAY 335 

    0xc8c500a0,// 368 PAY 336 

    0x5f832704,// 369 PAY 337 

    0xba1d399e,// 370 PAY 338 

    0xd1285f74,// 371 PAY 339 

    0xa05d227f,// 372 PAY 340 

    0xb08d84a3,// 373 PAY 341 

    0xfeef377d,// 374 PAY 342 

    0xf743651d,// 375 PAY 343 

    0xa6853224,// 376 PAY 344 

    0x9b2150c5,// 377 PAY 345 

    0x98672e55,// 378 PAY 346 

    0xc3bc58a2,// 379 PAY 347 

    0x18511dfe,// 380 PAY 348 

    0x2c3126ab,// 381 PAY 349 

    0x6eb4b08f,// 382 PAY 350 

    0x8209c915,// 383 PAY 351 

    0xe0e0a007,// 384 PAY 352 

    0x2546e69a,// 385 PAY 353 

    0xcccfe759,// 386 PAY 354 

    0x2f96e53b,// 387 PAY 355 

    0xca2a7307,// 388 PAY 356 

    0x368cccb8,// 389 PAY 357 

    0xbee69860,// 390 PAY 358 

    0xd730f563,// 391 PAY 359 

    0xffde4831,// 392 PAY 360 

    0xee20aefa,// 393 PAY 361 

    0x450a7e2c,// 394 PAY 362 

    0x4ae5357b,// 395 PAY 363 

    0x2f170e47,// 396 PAY 364 

    0x6945a266,// 397 PAY 365 

    0x861e731e,// 398 PAY 366 

    0x4cb1cff1,// 399 PAY 367 

    0x14c84cd9,// 400 PAY 368 

    0x5c9c129d,// 401 PAY 369 

    0x1446b137,// 402 PAY 370 

    0x0e3c3237,// 403 PAY 371 

    0x04f5f8de,// 404 PAY 372 

    0x3d31eae9,// 405 PAY 373 

    0xb3713c08,// 406 PAY 374 

    0x6e738978,// 407 PAY 375 

    0x1bbecb19,// 408 PAY 376 

    0xa7619a11,// 409 PAY 377 

    0x6659d4b0,// 410 PAY 378 

    0x8352a59c,// 411 PAY 379 

    0x21a1e8e6,// 412 PAY 380 

    0x4ea3de5c,// 413 PAY 381 

    0xf81f08e3,// 414 PAY 382 

    0xecd99a2b,// 415 PAY 383 

    0x892bf19a,// 416 PAY 384 

    0x21a7b859,// 417 PAY 385 

    0x55115a5d,// 418 PAY 386 

    0xc19dbdc4,// 419 PAY 387 

    0x4abe641b,// 420 PAY 388 

    0x4898112f,// 421 PAY 389 

    0x10b01015,// 422 PAY 390 

    0x77aba804,// 423 PAY 391 

    0x4c01b3a9,// 424 PAY 392 

    0xcca7197c,// 425 PAY 393 

    0x4ecc672b,// 426 PAY 394 

    0x16dd72f6,// 427 PAY 395 

    0xc366dba2,// 428 PAY 396 

    0xcea08746,// 429 PAY 397 

    0xc0d5097d,// 430 PAY 398 

    0x594ae5cc,// 431 PAY 399 

    0xf164baa5,// 432 PAY 400 

    0x85fc693f,// 433 PAY 401 

    0xfa98741b,// 434 PAY 402 

    0x8edadb4e,// 435 PAY 403 

    0xbe56a92c,// 436 PAY 404 

    0x2db9622a,// 437 PAY 405 

    0xb1617272,// 438 PAY 406 

    0x6479856e,// 439 PAY 407 

    0x6d23c252,// 440 PAY 408 

    0x9e650953,// 441 PAY 409 

    0x23e0dad8,// 442 PAY 410 

    0x7f61f3d5,// 443 PAY 411 

    0x5721e9b0,// 444 PAY 412 

    0xffc9b905,// 445 PAY 413 

    0x677a8ccc,// 446 PAY 414 

    0xa92c6a75,// 447 PAY 415 

    0xe83a465b,// 448 PAY 416 

    0x44915dc9,// 449 PAY 417 

    0xce0041ef,// 450 PAY 418 

    0xb524071c,// 451 PAY 419 

    0xa93bd230,// 452 PAY 420 

    0x28a96c36,// 453 PAY 421 

    0x476fd5d0,// 454 PAY 422 

    0xec20ee49,// 455 PAY 423 

    0xbfa47606,// 456 PAY 424 

    0xd303ad9d,// 457 PAY 425 

    0x1d823058,// 458 PAY 426 

    0x15d9812a,// 459 PAY 427 

    0xe21209e8,// 460 PAY 428 

    0x1b157f40,// 461 PAY 429 

    0x0eeec2b5,// 462 PAY 430 

    0x9303f661,// 463 PAY 431 

    0x414ac280,// 464 PAY 432 

    0x9e3090c9,// 465 PAY 433 

    0xd778e467,// 466 PAY 434 

    0x13297f1e,// 467 PAY 435 

    0x915d796c,// 468 PAY 436 

    0xb8811bd5,// 469 PAY 437 

/// STA is 1 words. 

/// STA num_pkts       : 34 

/// STA pkt_idx        : 231 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xdf 

    0x039cdf22 // 470 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 96 (0x60) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt7_tmpl[] = {
    0xb8010060,// 1 CCH   1 

/// ECH cache_idx      : 0x0a 

/// ECH pdu_tag        : 0x00 

    0x000a0000,// 2 ECH   1 

/// SCX is 23 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv insert_icv check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000017,// 3 SCX   1 

    0x808548c1,// 4 SCX   2 

    0x00007484,// 5 SCX   3 

    0x273c2e70,// 6 SCX   4 

    0x6369ee70,// 7 SCX   5 

    0x99cdf4f6,// 8 SCX   6 

    0x2df7a84d,// 9 SCX   7 

    0xcf82eaa3,// 10 SCX   8 

    0x7947d0b1,// 11 SCX   9 

    0x31b47416,// 12 SCX  10 

    0x811a677b,// 13 SCX  11 

    0x44f29955,// 14 SCX  12 

    0x7af4d8b2,// 15 SCX  13 

    0xc2974028,// 16 SCX  14 

    0x19230a38,// 17 SCX  15 

    0xb8b0186c,// 18 SCX  16 

    0x8d36c595,// 19 SCX  17 

    0x38b3920a,// 20 SCX  18 

    0x4fd31fcc,// 21 SCX  19 

    0x4825ca59,// 22 SCX  20 

    0x5483eef2,// 23 SCX  21 

    0x625542b1,// 24 SCX  22 

    0x51c56f0d,// 25 SCX  23 

/// BFD is 3 words. 

/// BFD tot_len        : 1128 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 767 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 767 

/// BFD lencrypto      : 176 

/// BFD ofstcrypto     : 324 

/// BFD (ofst+len)cry  : 500 

/// BFD ofstiv         : 60 

/// BFD ofsticv        : 1048 

    0x000002ff,// 26 BFD   1 

    0x014400b0,// 27 BFD   2 

    0x0418003c,// 28 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c00bd98,// 29 MFM   1 

    0xdff0cf63,// 30 MFM   2 

    0x8a99c4b8,// 31 MFM   3 

    0x960abcef,// 32 MFM   4 

    0xab1fd861,// 33 MFM   5 

    0xf1df1338,// 34 MFM   6 

    0x57c098ef,// 35 MFM   7 

    0x50a44595,// 36 MFM   8 

    0x8f50fbde,// 37 MFM   9 

    0xbd3fb6af,// 38 MFM  10 

    0xe31e6de6,// 39 MFM  11 

    0x5822314c,// 40 MFM  12 

    0xc1efb260,// 41 MFM  13 

    0x74025eaa,// 42 MFM  14 

    0x80cf1f31,// 43 MFM  15 

    0xf26e9325,// 44 MFM  16 

/// BDA is 283 words. 

/// BDA size     is 1128 (0x468) 

/// BDA id       is 0xd61 

    0x04680d61,// 45 BDA   1 

/// PAY Generic Data size   : 1128 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0x91b9113c,// 46 PAY   1 

    0x12661c2b,// 47 PAY   2 

    0xabafb8df,// 48 PAY   3 

    0xf1332895,// 49 PAY   4 

    0xdc972641,// 50 PAY   5 

    0x6fc34caf,// 51 PAY   6 

    0x9830fc24,// 52 PAY   7 

    0x5773f5b9,// 53 PAY   8 

    0xf680f880,// 54 PAY   9 

    0xf925e046,// 55 PAY  10 

    0xa2f5ccfa,// 56 PAY  11 

    0xa0424b7d,// 57 PAY  12 

    0xd13c722e,// 58 PAY  13 

    0xb3707986,// 59 PAY  14 

    0x2ea01628,// 60 PAY  15 

    0xeb4a8c76,// 61 PAY  16 

    0x23e6bc29,// 62 PAY  17 

    0x5e27ecd9,// 63 PAY  18 

    0x494b38f5,// 64 PAY  19 

    0x367d7354,// 65 PAY  20 

    0x1c2edfb4,// 66 PAY  21 

    0x272e70c9,// 67 PAY  22 

    0x87595251,// 68 PAY  23 

    0xf8b17a80,// 69 PAY  24 

    0xf4e993f1,// 70 PAY  25 

    0x75f7aff6,// 71 PAY  26 

    0x72c7789d,// 72 PAY  27 

    0xb4517a8b,// 73 PAY  28 

    0x032fc4aa,// 74 PAY  29 

    0xcd443208,// 75 PAY  30 

    0xc90f87e4,// 76 PAY  31 

    0x96f44990,// 77 PAY  32 

    0x8ace8844,// 78 PAY  33 

    0x95366fac,// 79 PAY  34 

    0xe16d5793,// 80 PAY  35 

    0x596542bf,// 81 PAY  36 

    0x5d1a0419,// 82 PAY  37 

    0xa0207a3c,// 83 PAY  38 

    0x75b6c56c,// 84 PAY  39 

    0x4f3570dd,// 85 PAY  40 

    0xec9f2c53,// 86 PAY  41 

    0x7a689aa9,// 87 PAY  42 

    0x35a8904c,// 88 PAY  43 

    0xd976a5a6,// 89 PAY  44 

    0x652ee98b,// 90 PAY  45 

    0x7c5bd74f,// 91 PAY  46 

    0x0f712a39,// 92 PAY  47 

    0x05b79cc5,// 93 PAY  48 

    0xf7bbe2c5,// 94 PAY  49 

    0xd3b0b65a,// 95 PAY  50 

    0x854b18c7,// 96 PAY  51 

    0x1515cfe6,// 97 PAY  52 

    0xd54fab58,// 98 PAY  53 

    0x636978f1,// 99 PAY  54 

    0x6b9c9077,// 100 PAY  55 

    0xd65ff414,// 101 PAY  56 

    0xeea08bf3,// 102 PAY  57 

    0xf94f0beb,// 103 PAY  58 

    0x38978763,// 104 PAY  59 

    0xdd3c3524,// 105 PAY  60 

    0xc4f6b2fc,// 106 PAY  61 

    0xadaf29e3,// 107 PAY  62 

    0x87dec873,// 108 PAY  63 

    0x24dabc26,// 109 PAY  64 

    0x8d15bb60,// 110 PAY  65 

    0x5f1b8817,// 111 PAY  66 

    0x7817f0d0,// 112 PAY  67 

    0xcbbdc1ae,// 113 PAY  68 

    0x8bb19c7c,// 114 PAY  69 

    0x327b71f1,// 115 PAY  70 

    0xd429842e,// 116 PAY  71 

    0xed65811a,// 117 PAY  72 

    0x474ee4fa,// 118 PAY  73 

    0xbcadde18,// 119 PAY  74 

    0x32208299,// 120 PAY  75 

    0x80999c63,// 121 PAY  76 

    0xfcdc99bc,// 122 PAY  77 

    0x02fc5757,// 123 PAY  78 

    0xaa0b8bdf,// 124 PAY  79 

    0x6e15d8d2,// 125 PAY  80 

    0xf9e15a14,// 126 PAY  81 

    0x9037c69f,// 127 PAY  82 

    0x9f4440c7,// 128 PAY  83 

    0x1dcd2710,// 129 PAY  84 

    0x8b8967a3,// 130 PAY  85 

    0xd8d111db,// 131 PAY  86 

    0x1aef41bb,// 132 PAY  87 

    0x89f2f4bc,// 133 PAY  88 

    0xcf7daf4f,// 134 PAY  89 

    0xe25563c2,// 135 PAY  90 

    0x703a1e8a,// 136 PAY  91 

    0x552ef9f1,// 137 PAY  92 

    0x7efa0096,// 138 PAY  93 

    0x30a6984b,// 139 PAY  94 

    0x3a9fb312,// 140 PAY  95 

    0x3519abe0,// 141 PAY  96 

    0x8e309d59,// 142 PAY  97 

    0x0966d355,// 143 PAY  98 

    0xa8080d65,// 144 PAY  99 

    0x67cdbf17,// 145 PAY 100 

    0xd5b3a7ea,// 146 PAY 101 

    0x33f45bdd,// 147 PAY 102 

    0x7cc6e3c3,// 148 PAY 103 

    0x705f6e07,// 149 PAY 104 

    0xdc163365,// 150 PAY 105 

    0x2e0a8036,// 151 PAY 106 

    0x83aa877c,// 152 PAY 107 

    0xff25a7ab,// 153 PAY 108 

    0x9074fc54,// 154 PAY 109 

    0xc8b48491,// 155 PAY 110 

    0x0fe22076,// 156 PAY 111 

    0xdd51f6ae,// 157 PAY 112 

    0xa68944be,// 158 PAY 113 

    0x2060797c,// 159 PAY 114 

    0x31401f95,// 160 PAY 115 

    0x0a3df340,// 161 PAY 116 

    0xbf2736fa,// 162 PAY 117 

    0xce7126c5,// 163 PAY 118 

    0x55280a28,// 164 PAY 119 

    0xa3690082,// 165 PAY 120 

    0xc66dcdf0,// 166 PAY 121 

    0xb8dc547e,// 167 PAY 122 

    0x57fc9b9b,// 168 PAY 123 

    0x6d186b5a,// 169 PAY 124 

    0x927fe5e6,// 170 PAY 125 

    0x11f5d9e0,// 171 PAY 126 

    0x29637845,// 172 PAY 127 

    0x9f5c9a91,// 173 PAY 128 

    0x3f61736d,// 174 PAY 129 

    0x812b5809,// 175 PAY 130 

    0x062425ee,// 176 PAY 131 

    0xd789872a,// 177 PAY 132 

    0xb658137f,// 178 PAY 133 

    0xfdb1d003,// 179 PAY 134 

    0xa7b380a9,// 180 PAY 135 

    0x1cb20220,// 181 PAY 136 

    0xbf39b03a,// 182 PAY 137 

    0x64aa589a,// 183 PAY 138 

    0x88c6a7e2,// 184 PAY 139 

    0xf4472967,// 185 PAY 140 

    0x9db8bf43,// 186 PAY 141 

    0x286cc97e,// 187 PAY 142 

    0x95927111,// 188 PAY 143 

    0x9c95eaa2,// 189 PAY 144 

    0x035c2e29,// 190 PAY 145 

    0xa60a51c1,// 191 PAY 146 

    0x9574eb3c,// 192 PAY 147 

    0x4e208add,// 193 PAY 148 

    0xe1ba63b0,// 194 PAY 149 

    0xdb2859b9,// 195 PAY 150 

    0x24ba3292,// 196 PAY 151 

    0x3135d348,// 197 PAY 152 

    0xde564db0,// 198 PAY 153 

    0x57a25908,// 199 PAY 154 

    0x88c9e4d2,// 200 PAY 155 

    0x01a88a21,// 201 PAY 156 

    0x9cb50945,// 202 PAY 157 

    0x16573211,// 203 PAY 158 

    0xfac70d66,// 204 PAY 159 

    0x40c10842,// 205 PAY 160 

    0x4c666761,// 206 PAY 161 

    0x95b2037b,// 207 PAY 162 

    0xbbc86f96,// 208 PAY 163 

    0xdbbfca5b,// 209 PAY 164 

    0x71e02d8c,// 210 PAY 165 

    0xddfd588c,// 211 PAY 166 

    0x8a9cb76b,// 212 PAY 167 

    0x6be30c32,// 213 PAY 168 

    0xd72bb40f,// 214 PAY 169 

    0x057e75e3,// 215 PAY 170 

    0x300a7218,// 216 PAY 171 

    0x9351ba6e,// 217 PAY 172 

    0xaa3cd1af,// 218 PAY 173 

    0x8dfa2fa0,// 219 PAY 174 

    0xd04a9abc,// 220 PAY 175 

    0x7e37dce4,// 221 PAY 176 

    0x669d596c,// 222 PAY 177 

    0x67b314d9,// 223 PAY 178 

    0x03699976,// 224 PAY 179 

    0x5fb775fe,// 225 PAY 180 

    0x36cd5360,// 226 PAY 181 

    0x2067ff5b,// 227 PAY 182 

    0x9ca6bbda,// 228 PAY 183 

    0x34c1e148,// 229 PAY 184 

    0x8519f293,// 230 PAY 185 

    0x24ce9d55,// 231 PAY 186 

    0xd7046315,// 232 PAY 187 

    0x60ac8c6a,// 233 PAY 188 

    0x246241bc,// 234 PAY 189 

    0x2a0be061,// 235 PAY 190 

    0xd516c4ca,// 236 PAY 191 

    0x721d5638,// 237 PAY 192 

    0xcc4ec946,// 238 PAY 193 

    0x2dbc41e2,// 239 PAY 194 

    0x523f45b5,// 240 PAY 195 

    0x15377f12,// 241 PAY 196 

    0x22576a6a,// 242 PAY 197 

    0x2cfdfb40,// 243 PAY 198 

    0xde156779,// 244 PAY 199 

    0x0c75920b,// 245 PAY 200 

    0x28dbde33,// 246 PAY 201 

    0x1fdde78f,// 247 PAY 202 

    0x6c9f39aa,// 248 PAY 203 

    0x699adc73,// 249 PAY 204 

    0x770c7670,// 250 PAY 205 

    0x3357f220,// 251 PAY 206 

    0x6910deb8,// 252 PAY 207 

    0x6151f8fa,// 253 PAY 208 

    0x8c377da9,// 254 PAY 209 

    0xe08b1594,// 255 PAY 210 

    0x8fc4a755,// 256 PAY 211 

    0x84ce301c,// 257 PAY 212 

    0x559e4e43,// 258 PAY 213 

    0x4305e1ef,// 259 PAY 214 

    0xdc0bb3af,// 260 PAY 215 

    0xded7cb01,// 261 PAY 216 

    0xf1116e96,// 262 PAY 217 

    0x3cda0ef7,// 263 PAY 218 

    0x58e163e7,// 264 PAY 219 

    0xe78135dd,// 265 PAY 220 

    0x80ab2190,// 266 PAY 221 

    0x28b46226,// 267 PAY 222 

    0xd6061dce,// 268 PAY 223 

    0x89a675eb,// 269 PAY 224 

    0xb72fd4e8,// 270 PAY 225 

    0x82eaecf6,// 271 PAY 226 

    0x6d936dc6,// 272 PAY 227 

    0xdc7c83b4,// 273 PAY 228 

    0x8292dca6,// 274 PAY 229 

    0x9f9d1990,// 275 PAY 230 

    0x2df3740a,// 276 PAY 231 

    0xf53e2d3c,// 277 PAY 232 

    0x4bd0c0ed,// 278 PAY 233 

    0xd707a290,// 279 PAY 234 

    0xd5bebaae,// 280 PAY 235 

    0x21b40250,// 281 PAY 236 

    0xc8f1c635,// 282 PAY 237 

    0x7440faf6,// 283 PAY 238 

    0xe7e66d6e,// 284 PAY 239 

    0x9851818a,// 285 PAY 240 

    0xb5e98ee1,// 286 PAY 241 

    0xea2e2505,// 287 PAY 242 

    0xbe7cf242,// 288 PAY 243 

    0xb306503a,// 289 PAY 244 

    0xe064cfd2,// 290 PAY 245 

    0x3248517b,// 291 PAY 246 

    0xbb71f92e,// 292 PAY 247 

    0xa21afa33,// 293 PAY 248 

    0x3bae1b04,// 294 PAY 249 

    0x8fbb2e05,// 295 PAY 250 

    0xc42db805,// 296 PAY 251 

    0x74fae3f9,// 297 PAY 252 

    0x9a892364,// 298 PAY 253 

    0xdf8473bf,// 299 PAY 254 

    0x09069a54,// 300 PAY 255 

    0xaa474f20,// 301 PAY 256 

    0xef967f29,// 302 PAY 257 

    0xc2e38ab4,// 303 PAY 258 

    0x47292160,// 304 PAY 259 

    0x606780b1,// 305 PAY 260 

    0x4c2d2d36,// 306 PAY 261 

    0x6db53570,// 307 PAY 262 

    0xce09532d,// 308 PAY 263 

    0x8a88644b,// 309 PAY 264 

    0xac929318,// 310 PAY 265 

    0x5e276cfc,// 311 PAY 266 

    0x8854bfa2,// 312 PAY 267 

    0x0c15285b,// 313 PAY 268 

    0xbdd7e976,// 314 PAY 269 

    0x7f7e2d40,// 315 PAY 270 

    0x3161ce1d,// 316 PAY 271 

    0x652c2773,// 317 PAY 272 

    0xa9738506,// 318 PAY 273 

    0x5efc323a,// 319 PAY 274 

    0x68a19b5e,// 320 PAY 275 

    0xf196c9de,// 321 PAY 276 

    0xa1a4791d,// 322 PAY 277 

    0x8cadd153,// 323 PAY 278 

    0x5bef0cf2,// 324 PAY 279 

    0xf81722b9,// 325 PAY 280 

    0x8eafbb5e,// 326 PAY 281 

    0x3384a9b5,// 327 PAY 282 

/// STA is 1 words. 

/// STA num_pkts       : 140 

/// STA pkt_idx        : 203 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xee 

    0x032dee8c // 328 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 72 (0x48) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt8_tmpl[] = {
    0xb8010048,// 1 CCH   1 

/// ECH cache_idx      : 0x02 

/// ECH pdu_tag        : 0x00 

    0x00020000,// 2 ECH   1 

/// SCX is 17 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x00000011,// 3 SCX   1 

    0x8080483a,// 4 SCX   2 

    0x00002100,// 5 SCX   3 

    0xa8d0d58d,// 6 SCX   4 

    0x4a01745b,// 7 SCX   5 

    0x345c8fec,// 8 SCX   6 

    0x857e1f7a,// 9 SCX   7 

    0x318e1fa8,// 10 SCX   8 

    0x53915b9d,// 11 SCX   9 

    0xfa6d0990,// 12 SCX  10 

    0xb32ee7eb,// 13 SCX  11 

    0x86faca93,// 14 SCX  12 

    0x0daf0f12,// 15 SCX  13 

    0x387953d0,// 16 SCX  14 

    0x29783ddd,// 17 SCX  15 

    0x51414020,// 18 SCX  16 

    0xbab1b284,// 19 SCX  17 

/// BFD is 3 words. 

/// BFD tot_len        : 1247 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 485 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 485 

/// BFD lencrypto      : 32 

/// BFD ofstcrypto     : 228 

/// BFD (ofst+len)cry  : 260 

/// BFD ofstiv         : 92 

/// BFD ofsticv        : 548 

    0x000001e5,// 20 BFD   1 

    0x00e40020,// 21 BFD   2 

    0x0224005c,// 22 BFD   3 

/// MFM is 6 words. 

/// MFM vldnibs        : 2b 

    0x2b00590f,// 23 MFM   1 

    0x0e910130,// 24 MFM   2 

    0xade8dca8,// 25 MFM   3 

    0x8e48fa5a,// 26 MFM   4 

    0xa16431fa,// 27 MFM   5 

    0xf31da1d0,// 28 MFM   6 

/// BDA is 313 words. 

/// BDA size     is 1247 (0x4df) 

/// BDA id       is 0x5dfa 

    0x04df5dfa,// 29 BDA   1 

/// PAY Generic Data size   : 1247 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0x9e613fc6,// 30 PAY   1 

    0xc9106f1a,// 31 PAY   2 

    0x4b2a21de,// 32 PAY   3 

    0xe880e04f,// 33 PAY   4 

    0x3182082b,// 34 PAY   5 

    0xb1d56124,// 35 PAY   6 

    0xfbd1d3dd,// 36 PAY   7 

    0x71eff672,// 37 PAY   8 

    0x830bca62,// 38 PAY   9 

    0x6fc626c3,// 39 PAY  10 

    0xffb8a0e8,// 40 PAY  11 

    0x18712a15,// 41 PAY  12 

    0x493ef91c,// 42 PAY  13 

    0x89df42ed,// 43 PAY  14 

    0x27b14441,// 44 PAY  15 

    0x021b028b,// 45 PAY  16 

    0x679b15fe,// 46 PAY  17 

    0x7e609a5a,// 47 PAY  18 

    0x4f1a680f,// 48 PAY  19 

    0x15e8faa2,// 49 PAY  20 

    0xb0d97702,// 50 PAY  21 

    0xe1dc9d08,// 51 PAY  22 

    0x3c9ed106,// 52 PAY  23 

    0x29960426,// 53 PAY  24 

    0x01733e5e,// 54 PAY  25 

    0x23e5249b,// 55 PAY  26 

    0x391eade7,// 56 PAY  27 

    0xa289ec20,// 57 PAY  28 

    0x3d52e060,// 58 PAY  29 

    0xe60e6545,// 59 PAY  30 

    0x834db967,// 60 PAY  31 

    0xdc811068,// 61 PAY  32 

    0x75a14112,// 62 PAY  33 

    0x11303d84,// 63 PAY  34 

    0x87610325,// 64 PAY  35 

    0x030a8d32,// 65 PAY  36 

    0x8852c39f,// 66 PAY  37 

    0x8698e6ba,// 67 PAY  38 

    0x262b4f8a,// 68 PAY  39 

    0xcd9c22e5,// 69 PAY  40 

    0x25e0be13,// 70 PAY  41 

    0x9c13ded9,// 71 PAY  42 

    0xa2bc8f30,// 72 PAY  43 

    0xd70d8625,// 73 PAY  44 

    0x1fa3e70b,// 74 PAY  45 

    0x1a67f926,// 75 PAY  46 

    0x310c979c,// 76 PAY  47 

    0x09f9b299,// 77 PAY  48 

    0xe4ce7f6d,// 78 PAY  49 

    0xd4e57816,// 79 PAY  50 

    0xa78c34e4,// 80 PAY  51 

    0x48d91e78,// 81 PAY  52 

    0xec0992cd,// 82 PAY  53 

    0xc170cb31,// 83 PAY  54 

    0xd710abca,// 84 PAY  55 

    0xae9450e5,// 85 PAY  56 

    0x79c995ac,// 86 PAY  57 

    0x93db69f4,// 87 PAY  58 

    0xc4e316e6,// 88 PAY  59 

    0xd179c413,// 89 PAY  60 

    0x3f523cc9,// 90 PAY  61 

    0x6b6afa09,// 91 PAY  62 

    0xb1496c9a,// 92 PAY  63 

    0x07fa7e2c,// 93 PAY  64 

    0xdea5a3f1,// 94 PAY  65 

    0xa6937576,// 95 PAY  66 

    0x1a742ce2,// 96 PAY  67 

    0x1b63584d,// 97 PAY  68 

    0x07d6ecc3,// 98 PAY  69 

    0x1ad0e828,// 99 PAY  70 

    0xc046a839,// 100 PAY  71 

    0xad5c63ad,// 101 PAY  72 

    0x6e0498f4,// 102 PAY  73 

    0xdc68db06,// 103 PAY  74 

    0x4e6f81f7,// 104 PAY  75 

    0x2289d39a,// 105 PAY  76 

    0x62e59c03,// 106 PAY  77 

    0x21efdf46,// 107 PAY  78 

    0x666daa99,// 108 PAY  79 

    0x36c74db0,// 109 PAY  80 

    0xd8be80a8,// 110 PAY  81 

    0xcb4c1c9e,// 111 PAY  82 

    0xb5d141eb,// 112 PAY  83 

    0x56dea846,// 113 PAY  84 

    0x1152c64e,// 114 PAY  85 

    0xf84ce48c,// 115 PAY  86 

    0x5a7abf22,// 116 PAY  87 

    0xbd883130,// 117 PAY  88 

    0x8a6d4cac,// 118 PAY  89 

    0x5c75bce0,// 119 PAY  90 

    0xb39da914,// 120 PAY  91 

    0x53f9502a,// 121 PAY  92 

    0x72fc0cec,// 122 PAY  93 

    0xf0b7f4e0,// 123 PAY  94 

    0x57bda404,// 124 PAY  95 

    0x49caf248,// 125 PAY  96 

    0x080c76f6,// 126 PAY  97 

    0xd704771d,// 127 PAY  98 

    0x18e97603,// 128 PAY  99 

    0xbdbc14e9,// 129 PAY 100 

    0x2e1d33bd,// 130 PAY 101 

    0xd99d5f3a,// 131 PAY 102 

    0x84466ec7,// 132 PAY 103 

    0x739a4cf1,// 133 PAY 104 

    0x9acc5fad,// 134 PAY 105 

    0x76071ddf,// 135 PAY 106 

    0x0ed2c5a7,// 136 PAY 107 

    0xb582882f,// 137 PAY 108 

    0xc93d8bfd,// 138 PAY 109 

    0x35e4048b,// 139 PAY 110 

    0x99f156fe,// 140 PAY 111 

    0x59ed701f,// 141 PAY 112 

    0xacd5d308,// 142 PAY 113 

    0xc352d5d0,// 143 PAY 114 

    0xec7b28cb,// 144 PAY 115 

    0xeb699384,// 145 PAY 116 

    0x87f08884,// 146 PAY 117 

    0xb1453dc1,// 147 PAY 118 

    0x25b49613,// 148 PAY 119 

    0x381b74b6,// 149 PAY 120 

    0xd836b821,// 150 PAY 121 

    0x0636ebe5,// 151 PAY 122 

    0x18fd95b7,// 152 PAY 123 

    0xc3688ac4,// 153 PAY 124 

    0x73077f55,// 154 PAY 125 

    0xc8224672,// 155 PAY 126 

    0xace3adb7,// 156 PAY 127 

    0x67176420,// 157 PAY 128 

    0x12780302,// 158 PAY 129 

    0xa96c2719,// 159 PAY 130 

    0x7dcb06cc,// 160 PAY 131 

    0x71039b8d,// 161 PAY 132 

    0x0c2edbb1,// 162 PAY 133 

    0x3955df1b,// 163 PAY 134 

    0x16f4e577,// 164 PAY 135 

    0xafe6bd41,// 165 PAY 136 

    0x60f12995,// 166 PAY 137 

    0xe7e4f8ff,// 167 PAY 138 

    0x89e5e43b,// 168 PAY 139 

    0x4d9dc067,// 169 PAY 140 

    0x2cb70083,// 170 PAY 141 

    0xd814fd3e,// 171 PAY 142 

    0x0ec62343,// 172 PAY 143 

    0xc0c8eb01,// 173 PAY 144 

    0x9f367c14,// 174 PAY 145 

    0x06b4fa27,// 175 PAY 146 

    0xfb70d926,// 176 PAY 147 

    0x6c6d1e4b,// 177 PAY 148 

    0x20c7dc03,// 178 PAY 149 

    0xb76282d2,// 179 PAY 150 

    0xa6e386de,// 180 PAY 151 

    0x51fe008a,// 181 PAY 152 

    0xb658313b,// 182 PAY 153 

    0xf032c6c4,// 183 PAY 154 

    0x51f98c7b,// 184 PAY 155 

    0x5b38b541,// 185 PAY 156 

    0xb0e0e6a4,// 186 PAY 157 

    0x16747b4b,// 187 PAY 158 

    0x581098c3,// 188 PAY 159 

    0x091a7dbb,// 189 PAY 160 

    0x21206286,// 190 PAY 161 

    0x2bfcb130,// 191 PAY 162 

    0x90f6b16b,// 192 PAY 163 

    0x7d2532ad,// 193 PAY 164 

    0x952fb801,// 194 PAY 165 

    0xf05f27a3,// 195 PAY 166 

    0xe203a3cc,// 196 PAY 167 

    0x3af05450,// 197 PAY 168 

    0x3d3497d3,// 198 PAY 169 

    0x88cf9143,// 199 PAY 170 

    0x7f59aa97,// 200 PAY 171 

    0xe3caf8a7,// 201 PAY 172 

    0x393f66b2,// 202 PAY 173 

    0xddefea42,// 203 PAY 174 

    0x8aae8f92,// 204 PAY 175 

    0x6fca552f,// 205 PAY 176 

    0x323f6395,// 206 PAY 177 

    0x50ad7c67,// 207 PAY 178 

    0xc046dabd,// 208 PAY 179 

    0xdd42371c,// 209 PAY 180 

    0x0a5fcced,// 210 PAY 181 

    0xc26e9cc2,// 211 PAY 182 

    0xcfd80174,// 212 PAY 183 

    0xfafe318a,// 213 PAY 184 

    0x211edc03,// 214 PAY 185 

    0x38175470,// 215 PAY 186 

    0x8f3ae7c9,// 216 PAY 187 

    0xdc5b1787,// 217 PAY 188 

    0x6f16548a,// 218 PAY 189 

    0xe89f9cd3,// 219 PAY 190 

    0x49908891,// 220 PAY 191 

    0x03fb2584,// 221 PAY 192 

    0x20d5b349,// 222 PAY 193 

    0xfbde5fab,// 223 PAY 194 

    0x55ddfd20,// 224 PAY 195 

    0x8945cff6,// 225 PAY 196 

    0x242b1d85,// 226 PAY 197 

    0x669971a4,// 227 PAY 198 

    0x2a1eeb1b,// 228 PAY 199 

    0x1843cf3d,// 229 PAY 200 

    0x05e0adbb,// 230 PAY 201 

    0x6e441854,// 231 PAY 202 

    0x8285792d,// 232 PAY 203 

    0xfe922c31,// 233 PAY 204 

    0x86ebc963,// 234 PAY 205 

    0x04cf465f,// 235 PAY 206 

    0xce9f5a02,// 236 PAY 207 

    0xe7fd9226,// 237 PAY 208 

    0x0ad9ee69,// 238 PAY 209 

    0x9f598e83,// 239 PAY 210 

    0x9c4e66cb,// 240 PAY 211 

    0xef26feed,// 241 PAY 212 

    0xaf32caad,// 242 PAY 213 

    0x0241030f,// 243 PAY 214 

    0x9e1d59e8,// 244 PAY 215 

    0xf20c7c3b,// 245 PAY 216 

    0xa806c465,// 246 PAY 217 

    0x1a388640,// 247 PAY 218 

    0x495a3f0b,// 248 PAY 219 

    0xa1b2946e,// 249 PAY 220 

    0x6e84db7b,// 250 PAY 221 

    0xaed7c922,// 251 PAY 222 

    0x47cf11e9,// 252 PAY 223 

    0x23493f5f,// 253 PAY 224 

    0x69f419c8,// 254 PAY 225 

    0x2749a187,// 255 PAY 226 

    0x5a4347b7,// 256 PAY 227 

    0xddd65d6a,// 257 PAY 228 

    0x9210d460,// 258 PAY 229 

    0xdb11088f,// 259 PAY 230 

    0x831386f0,// 260 PAY 231 

    0x183f69e6,// 261 PAY 232 

    0x881ed6e4,// 262 PAY 233 

    0x6b653f56,// 263 PAY 234 

    0x1a6f8111,// 264 PAY 235 

    0x125dd0df,// 265 PAY 236 

    0xe674ea8a,// 266 PAY 237 

    0x9d5ed9d1,// 267 PAY 238 

    0xf270bf60,// 268 PAY 239 

    0xf86c1f88,// 269 PAY 240 

    0x432d994d,// 270 PAY 241 

    0xcd245632,// 271 PAY 242 

    0xae973ffb,// 272 PAY 243 

    0xae3976ab,// 273 PAY 244 

    0xd98802ba,// 274 PAY 245 

    0xbb966db4,// 275 PAY 246 

    0xf92e7a1a,// 276 PAY 247 

    0x9f35701c,// 277 PAY 248 

    0xc3b81626,// 278 PAY 249 

    0x6de4c956,// 279 PAY 250 

    0xbd73a86a,// 280 PAY 251 

    0x76eeda10,// 281 PAY 252 

    0x409a76e6,// 282 PAY 253 

    0x2370c406,// 283 PAY 254 

    0x2cf06569,// 284 PAY 255 

    0xd676e733,// 285 PAY 256 

    0x2d09d7db,// 286 PAY 257 

    0x58c6219e,// 287 PAY 258 

    0xce48921e,// 288 PAY 259 

    0x388c8ed7,// 289 PAY 260 

    0x6937189f,// 290 PAY 261 

    0xba92e108,// 291 PAY 262 

    0xb70ebf58,// 292 PAY 263 

    0xe262d00a,// 293 PAY 264 

    0x16ae0651,// 294 PAY 265 

    0x2bb4ab74,// 295 PAY 266 

    0xa45d3698,// 296 PAY 267 

    0x0afd1aa7,// 297 PAY 268 

    0x36c9b4a9,// 298 PAY 269 

    0xc15fc2a1,// 299 PAY 270 

    0xea161c2e,// 300 PAY 271 

    0x96d2ab0b,// 301 PAY 272 

    0x42d3e3e0,// 302 PAY 273 

    0xdf1c891a,// 303 PAY 274 

    0x50666fca,// 304 PAY 275 

    0xb69eb97e,// 305 PAY 276 

    0xc427b202,// 306 PAY 277 

    0xd55436a5,// 307 PAY 278 

    0xc044a2e6,// 308 PAY 279 

    0x6bc0e24f,// 309 PAY 280 

    0x05ae00a3,// 310 PAY 281 

    0xd069cd2a,// 311 PAY 282 

    0x9c65f476,// 312 PAY 283 

    0xfd03cb96,// 313 PAY 284 

    0x898c8fd6,// 314 PAY 285 

    0xe5094fe9,// 315 PAY 286 

    0x0c25ba47,// 316 PAY 287 

    0xcb2c94b5,// 317 PAY 288 

    0x7de7927c,// 318 PAY 289 

    0xa9aa21a2,// 319 PAY 290 

    0x6014dbac,// 320 PAY 291 

    0x31351246,// 321 PAY 292 

    0x304b649a,// 322 PAY 293 

    0x472e34b5,// 323 PAY 294 

    0x2ba30fc3,// 324 PAY 295 

    0x28452a15,// 325 PAY 296 

    0x9e10b59c,// 326 PAY 297 

    0x182e6a0a,// 327 PAY 298 

    0x2e2b4db8,// 328 PAY 299 

    0x0c2ff5d8,// 329 PAY 300 

    0x3eb23f8e,// 330 PAY 301 

    0x334f5537,// 331 PAY 302 

    0x6c9f9471,// 332 PAY 303 

    0xe6046115,// 333 PAY 304 

    0xf0c0aba8,// 334 PAY 305 

    0xfbfc4bbd,// 335 PAY 306 

    0xbf031c15,// 336 PAY 307 

    0x7fa1f758,// 337 PAY 308 

    0x3e8bf106,// 338 PAY 309 

    0x706fc565,// 339 PAY 310 

    0xb245b6b0,// 340 PAY 311 

    0xbaced500,// 341 PAY 312 

/// STA is 1 words. 

/// STA num_pkts       : 239 

/// STA pkt_idx        : 63 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x1c 

    0x00fc1cef // 342 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 80 (0x50) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt9_tmpl[] = {
    0xb8010050,// 1 CCH   1 

/// ECH cache_idx      : 0x00 

/// ECH pdu_tag        : 0x00 

    0x00000000,// 2 ECH   1 

/// SCX is 19 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv !insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x2 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x00000013,// 3 SCX   1 

    0x808148c1,// 4 SCX   2 

    0x00005200,// 5 SCX   3 

    0xf68d753c,// 6 SCX   4 

    0xd196ea7b,// 7 SCX   5 

    0x56d4bdf3,// 8 SCX   6 

    0x6283e544,// 9 SCX   7 

    0x9e04d1f7,// 10 SCX   8 

    0x1e710a88,// 11 SCX   9 

    0xac42c045,// 12 SCX  10 

    0x540f99da,// 13 SCX  11 

    0xf9c2f7a5,// 14 SCX  12 

    0x57bda1da,// 15 SCX  13 

    0x4732f694,// 16 SCX  14 

    0xa8ed2776,// 17 SCX  15 

    0xffb041c2,// 18 SCX  16 

    0xadaf1720,// 19 SCX  17 

    0xf7eafa70,// 20 SCX  18 

    0xa176d648,// 21 SCX  19 

/// BFD is 3 words. 

/// BFD tot_len        : 1035 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 575 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 575 

/// BFD lencrypto      : 96 

/// BFD ofstcrypto     : 472 

/// BFD (ofst+len)cry  : 568 

/// BFD ofstiv         : 400 

/// BFD ofsticv        : 1012 

    0x0000023f,// 22 BFD   1 

    0x01d80060,// 23 BFD   2 

    0x03f40190,// 24 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : b 

    0x0b00b235,// 25 MFM   1 

    0x0eeea1f0,// 26 MFM   2 

/// BDA is 260 words. 

/// BDA size     is 1035 (0x40b) 

/// BDA id       is 0xc580 

    0x040bc580,// 27 BDA   1 

/// PAY Generic Data size   : 1035 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0xb03e5da3,// 28 PAY   1 

    0xf27233f1,// 29 PAY   2 

    0xd1688303,// 30 PAY   3 

    0xd5a4e6e5,// 31 PAY   4 

    0x917fb94a,// 32 PAY   5 

    0xdf4e978b,// 33 PAY   6 

    0x6b32b2c5,// 34 PAY   7 

    0xb0970987,// 35 PAY   8 

    0xeaa832c5,// 36 PAY   9 

    0x7f0c69e3,// 37 PAY  10 

    0x9c320b42,// 38 PAY  11 

    0x60d5f5b2,// 39 PAY  12 

    0x0b67f975,// 40 PAY  13 

    0xe267efaf,// 41 PAY  14 

    0x19c44204,// 42 PAY  15 

    0xfebaa6ef,// 43 PAY  16 

    0x9defc1cb,// 44 PAY  17 

    0x52550f1a,// 45 PAY  18 

    0x92ca8566,// 46 PAY  19 

    0xaef3b83a,// 47 PAY  20 

    0xa7ae5e07,// 48 PAY  21 

    0x0f8428d6,// 49 PAY  22 

    0x8c4d2304,// 50 PAY  23 

    0x125529a0,// 51 PAY  24 

    0x2c228b74,// 52 PAY  25 

    0xa640a0f1,// 53 PAY  26 

    0x29ad4d16,// 54 PAY  27 

    0xdec9ad19,// 55 PAY  28 

    0xe6a43e37,// 56 PAY  29 

    0xb4a14e11,// 57 PAY  30 

    0x95ad3741,// 58 PAY  31 

    0x15189841,// 59 PAY  32 

    0x4a043e15,// 60 PAY  33 

    0x40b47261,// 61 PAY  34 

    0x9a241410,// 62 PAY  35 

    0x91598154,// 63 PAY  36 

    0xc2f0fb97,// 64 PAY  37 

    0xdbc6b6ee,// 65 PAY  38 

    0xf314e5c6,// 66 PAY  39 

    0x7fdea901,// 67 PAY  40 

    0x849bcc52,// 68 PAY  41 

    0x277cc372,// 69 PAY  42 

    0x88639561,// 70 PAY  43 

    0x138f9796,// 71 PAY  44 

    0x650ba079,// 72 PAY  45 

    0xefe11bd4,// 73 PAY  46 

    0xdc614875,// 74 PAY  47 

    0xd6b56d32,// 75 PAY  48 

    0x1d000eb3,// 76 PAY  49 

    0xaf92b4d6,// 77 PAY  50 

    0x6bc5497a,// 78 PAY  51 

    0xb719666d,// 79 PAY  52 

    0x19ef9618,// 80 PAY  53 

    0xec8aea68,// 81 PAY  54 

    0x70f3c731,// 82 PAY  55 

    0x33984ab4,// 83 PAY  56 

    0x14154dc8,// 84 PAY  57 

    0xa0b9f4ff,// 85 PAY  58 

    0xca68d849,// 86 PAY  59 

    0xaa31dd0c,// 87 PAY  60 

    0x4dfa42d7,// 88 PAY  61 

    0x09761b22,// 89 PAY  62 

    0x236c828f,// 90 PAY  63 

    0x1526a848,// 91 PAY  64 

    0xa22d9e15,// 92 PAY  65 

    0x36ece59f,// 93 PAY  66 

    0x19d8b86e,// 94 PAY  67 

    0xc656bbcc,// 95 PAY  68 

    0x1e9aba43,// 96 PAY  69 

    0x20ea8645,// 97 PAY  70 

    0x6402dbd0,// 98 PAY  71 

    0x741ea35e,// 99 PAY  72 

    0x79be86da,// 100 PAY  73 

    0x6aec87a7,// 101 PAY  74 

    0x94c56ad0,// 102 PAY  75 

    0x75e4b2ac,// 103 PAY  76 

    0x27cc49f8,// 104 PAY  77 

    0x7ab86750,// 105 PAY  78 

    0xc37d063d,// 106 PAY  79 

    0x54f3355a,// 107 PAY  80 

    0x81f5c57d,// 108 PAY  81 

    0xf737a763,// 109 PAY  82 

    0x6f429854,// 110 PAY  83 

    0x9480c4ee,// 111 PAY  84 

    0x2539bd4c,// 112 PAY  85 

    0x6b49d37c,// 113 PAY  86 

    0x01b34ad6,// 114 PAY  87 

    0x50e0495d,// 115 PAY  88 

    0x61bc1bb1,// 116 PAY  89 

    0xb14c0e1c,// 117 PAY  90 

    0x669b1dbc,// 118 PAY  91 

    0xc804c4cb,// 119 PAY  92 

    0xc3d10b07,// 120 PAY  93 

    0x9f2f6a0f,// 121 PAY  94 

    0x65d2457e,// 122 PAY  95 

    0x5141d781,// 123 PAY  96 

    0xf8b31267,// 124 PAY  97 

    0x1f0cc512,// 125 PAY  98 

    0x6366b112,// 126 PAY  99 

    0xacd4bf6f,// 127 PAY 100 

    0x63945765,// 128 PAY 101 

    0x7d769c64,// 129 PAY 102 

    0x5b6d9f47,// 130 PAY 103 

    0x50bdf654,// 131 PAY 104 

    0xecc2da01,// 132 PAY 105 

    0x1410db3b,// 133 PAY 106 

    0x94845df4,// 134 PAY 107 

    0xc7c82e44,// 135 PAY 108 

    0xc82d6312,// 136 PAY 109 

    0xbc367860,// 137 PAY 110 

    0xf97e9676,// 138 PAY 111 

    0xbf0ba480,// 139 PAY 112 

    0x9959aec6,// 140 PAY 113 

    0x81d4dbc7,// 141 PAY 114 

    0x35e61e31,// 142 PAY 115 

    0xccd584a5,// 143 PAY 116 

    0xc7b88e5a,// 144 PAY 117 

    0xa468eabc,// 145 PAY 118 

    0x6e34e071,// 146 PAY 119 

    0xad242901,// 147 PAY 120 

    0x196d5678,// 148 PAY 121 

    0x12b1d6c4,// 149 PAY 122 

    0xab59cb91,// 150 PAY 123 

    0x5241681e,// 151 PAY 124 

    0xa018f313,// 152 PAY 125 

    0x6a2d0875,// 153 PAY 126 

    0xcc2f33f0,// 154 PAY 127 

    0x5f577940,// 155 PAY 128 

    0xa42b9a95,// 156 PAY 129 

    0x724d1c4e,// 157 PAY 130 

    0xa73b8d93,// 158 PAY 131 

    0xcb16c4d6,// 159 PAY 132 

    0x5b16cff8,// 160 PAY 133 

    0xbe468a29,// 161 PAY 134 

    0x5df6a68c,// 162 PAY 135 

    0x7cdca352,// 163 PAY 136 

    0x5176bf04,// 164 PAY 137 

    0xcf807435,// 165 PAY 138 

    0x25f3917b,// 166 PAY 139 

    0xc2909aa7,// 167 PAY 140 

    0xd1aab749,// 168 PAY 141 

    0xc80c9c20,// 169 PAY 142 

    0xbe1988f5,// 170 PAY 143 

    0xf109946a,// 171 PAY 144 

    0x8684ee85,// 172 PAY 145 

    0x255bd29e,// 173 PAY 146 

    0x5596b77f,// 174 PAY 147 

    0x0c8aa184,// 175 PAY 148 

    0x7acec6a3,// 176 PAY 149 

    0x2d6ece8b,// 177 PAY 150 

    0x8e35abd8,// 178 PAY 151 

    0x4e47a77f,// 179 PAY 152 

    0x4f1f5635,// 180 PAY 153 

    0x02eba323,// 181 PAY 154 

    0xf219ee99,// 182 PAY 155 

    0xc1166bb3,// 183 PAY 156 

    0x7c7efcec,// 184 PAY 157 

    0xc5d9acd0,// 185 PAY 158 

    0x721a1587,// 186 PAY 159 

    0x95235f1c,// 187 PAY 160 

    0x0e754f6a,// 188 PAY 161 

    0x7ac7f15c,// 189 PAY 162 

    0x1b6edf46,// 190 PAY 163 

    0x76b35c17,// 191 PAY 164 

    0xe685573c,// 192 PAY 165 

    0xaadf90fe,// 193 PAY 166 

    0xca4f4e61,// 194 PAY 167 

    0xe2f92cd9,// 195 PAY 168 

    0x968cc4d6,// 196 PAY 169 

    0x165c03e8,// 197 PAY 170 

    0x5e1c241b,// 198 PAY 171 

    0x128abe65,// 199 PAY 172 

    0xe7ba07ac,// 200 PAY 173 

    0x54791b4c,// 201 PAY 174 

    0xc718b896,// 202 PAY 175 

    0x8d2837e5,// 203 PAY 176 

    0xb2efcfcf,// 204 PAY 177 

    0xc92cbdac,// 205 PAY 178 

    0x60116439,// 206 PAY 179 

    0xeada5876,// 207 PAY 180 

    0xe383db4a,// 208 PAY 181 

    0x7134d267,// 209 PAY 182 

    0x8bf39504,// 210 PAY 183 

    0x04590152,// 211 PAY 184 

    0x2111af35,// 212 PAY 185 

    0x846fc7a5,// 213 PAY 186 

    0xbb7eb771,// 214 PAY 187 

    0xa7442f9b,// 215 PAY 188 

    0x8ba1abf4,// 216 PAY 189 

    0xd4730f32,// 217 PAY 190 

    0xec359a8e,// 218 PAY 191 

    0x741558c1,// 219 PAY 192 

    0x7d482140,// 220 PAY 193 

    0x75fc9c54,// 221 PAY 194 

    0x5209067c,// 222 PAY 195 

    0xd61f891d,// 223 PAY 196 

    0xf4061f4e,// 224 PAY 197 

    0xb023b4a4,// 225 PAY 198 

    0xd9cdd109,// 226 PAY 199 

    0x849e41e7,// 227 PAY 200 

    0x9290b5b3,// 228 PAY 201 

    0x8d1a1ac9,// 229 PAY 202 

    0x5cddc926,// 230 PAY 203 

    0x076e988d,// 231 PAY 204 

    0x26dbf318,// 232 PAY 205 

    0x1887eb25,// 233 PAY 206 

    0xd514177f,// 234 PAY 207 

    0x2c9d78d7,// 235 PAY 208 

    0x2a167582,// 236 PAY 209 

    0x0920fb7f,// 237 PAY 210 

    0x38fa8d59,// 238 PAY 211 

    0xbb5c8493,// 239 PAY 212 

    0xb5d46d5c,// 240 PAY 213 

    0x88af5e55,// 241 PAY 214 

    0x5aca8666,// 242 PAY 215 

    0x1ce86d33,// 243 PAY 216 

    0xd3271ba2,// 244 PAY 217 

    0x21e79df9,// 245 PAY 218 

    0xb8f25f64,// 246 PAY 219 

    0x40b4df1d,// 247 PAY 220 

    0xbab2fad5,// 248 PAY 221 

    0x67ec02f6,// 249 PAY 222 

    0xfb6dda31,// 250 PAY 223 

    0x291b6061,// 251 PAY 224 

    0xcf660fdb,// 252 PAY 225 

    0x70418c30,// 253 PAY 226 

    0x3b3b4cfa,// 254 PAY 227 

    0xc817ae50,// 255 PAY 228 

    0xc73ff68b,// 256 PAY 229 

    0xc1824ec9,// 257 PAY 230 

    0xd78aec57,// 258 PAY 231 

    0x5912fbdc,// 259 PAY 232 

    0xee1bf2e6,// 260 PAY 233 

    0xf452d10c,// 261 PAY 234 

    0x85914ff2,// 262 PAY 235 

    0xf46bb6ff,// 263 PAY 236 

    0xca3b02c8,// 264 PAY 237 

    0x179d3321,// 265 PAY 238 

    0x40bc7475,// 266 PAY 239 

    0x6939b2d6,// 267 PAY 240 

    0xfb346fc5,// 268 PAY 241 

    0x1d9dc3b7,// 269 PAY 242 

    0x5a276947,// 270 PAY 243 

    0xe12f0469,// 271 PAY 244 

    0xcdb142b0,// 272 PAY 245 

    0x582450bd,// 273 PAY 246 

    0x082dc4f0,// 274 PAY 247 

    0xdb61169d,// 275 PAY 248 

    0xd70d8214,// 276 PAY 249 

    0x71093e50,// 277 PAY 250 

    0xe6d46826,// 278 PAY 251 

    0x544547ce,// 279 PAY 252 

    0x4aebcdce,// 280 PAY 253 

    0xd00e4329,// 281 PAY 254 

    0x92155074,// 282 PAY 255 

    0x3c098fab,// 283 PAY 256 

    0x99a04fbf,// 284 PAY 257 

    0x215bf313,// 285 PAY 258 

    0x648f4300,// 286 PAY 259 

/// STA is 1 words. 

/// STA num_pkts       : 73 

/// STA pkt_idx        : 76 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x71 

    0x01317149 // 287 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt10_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x0b 

/// ECH pdu_tag        : 0x00 

    0x000b0000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv insert_icv check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x808448f6,// 4 SCX   2 

    0x000071c4,// 5 SCX   3 

    0x1b55cca9,// 6 SCX   4 

    0xd2d89c70,// 7 SCX   5 

    0x9938a993,// 8 SCX   6 

    0xfa1aa68d,// 9 SCX   7 

    0x32dddf2b,// 10 SCX   8 

    0xd4e7b295,// 11 SCX   9 

    0x31642154,// 12 SCX  10 

    0x9243a835,// 13 SCX  11 

    0xc4e3f7f3,// 14 SCX  12 

    0xe004c7fb,// 15 SCX  13 

    0x195a5957,// 16 SCX  14 

    0xf67a65b7,// 17 SCX  15 

    0x25db0802,// 18 SCX  16 

    0xa5ec2f6f,// 19 SCX  17 

    0xf8fa9103,// 20 SCX  18 

    0xc6f5faee,// 21 SCX  19 

    0x0c3c99d6,// 22 SCX  20 

    0xb67d1b9d,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 745 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 662 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 662 

/// BFD lencrypto      : 320 

/// BFD ofstcrypto     : 148 

/// BFD (ofst+len)cry  : 468 

/// BFD ofstiv         : 16 

/// BFD ofsticv        : 672 

    0x00000296,// 24 BFD   1 

    0x00940140,// 25 BFD   2 

    0x02a00010,// 26 BFD   3 

/// MFM is 12 words. 

/// MFM vldnibs        : 5b 

    0x5b008849,// 27 MFM   1 

    0x8c84ece2,// 28 MFM   2 

    0x21d8a026,// 29 MFM   3 

    0x8b1ae113,// 30 MFM   4 

    0xc16f553b,// 31 MFM   5 

    0xe5bd2612,// 32 MFM   6 

    0x861fa655,// 33 MFM   7 

    0x7f2a30c2,// 34 MFM   8 

    0xbf6e0294,// 35 MFM   9 

    0x19ded98b,// 36 MFM  10 

    0x843f0537,// 37 MFM  11 

    0x423849e0,// 38 MFM  12 

/// BDA is 188 words. 

/// BDA size     is 745 (0x2e9) 

/// BDA id       is 0xdf39 

    0x02e9df39,// 39 BDA   1 

/// PAY Generic Data size   : 745 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x21dfa479,// 40 PAY   1 

    0x3ff61a7f,// 41 PAY   2 

    0x091c03e4,// 42 PAY   3 

    0xf6b59947,// 43 PAY   4 

    0x7ecf2943,// 44 PAY   5 

    0x5b75308f,// 45 PAY   6 

    0xbd93d5d9,// 46 PAY   7 

    0xc693ce4c,// 47 PAY   8 

    0x2250d1a3,// 48 PAY   9 

    0x215cd62e,// 49 PAY  10 

    0x203fb0e0,// 50 PAY  11 

    0x10d44d56,// 51 PAY  12 

    0x600b65a5,// 52 PAY  13 

    0x0ef18eee,// 53 PAY  14 

    0x897bf6a8,// 54 PAY  15 

    0xd1b72c47,// 55 PAY  16 

    0x5cbd95bc,// 56 PAY  17 

    0xbac4a43e,// 57 PAY  18 

    0xa5b39e40,// 58 PAY  19 

    0x20b7501f,// 59 PAY  20 

    0xb55fd748,// 60 PAY  21 

    0x7a17b832,// 61 PAY  22 

    0xb0f0bff3,// 62 PAY  23 

    0x37ae3c0a,// 63 PAY  24 

    0xfc5acb2e,// 64 PAY  25 

    0x623b85bf,// 65 PAY  26 

    0x79ca7d62,// 66 PAY  27 

    0x4797b17e,// 67 PAY  28 

    0xa1013847,// 68 PAY  29 

    0x90b68566,// 69 PAY  30 

    0x251dbe84,// 70 PAY  31 

    0xbb521501,// 71 PAY  32 

    0x254209d7,// 72 PAY  33 

    0xb481ee7d,// 73 PAY  34 

    0xcca6c4f2,// 74 PAY  35 

    0x73c77860,// 75 PAY  36 

    0xccccf6ab,// 76 PAY  37 

    0xefe73a79,// 77 PAY  38 

    0x66720265,// 78 PAY  39 

    0x95d93e92,// 79 PAY  40 

    0xb148e514,// 80 PAY  41 

    0x8a6d45ce,// 81 PAY  42 

    0xa1e24d53,// 82 PAY  43 

    0x80243758,// 83 PAY  44 

    0x346f4c71,// 84 PAY  45 

    0x4630fc8b,// 85 PAY  46 

    0x521026c2,// 86 PAY  47 

    0xe1cccdf3,// 87 PAY  48 

    0x6eb08195,// 88 PAY  49 

    0x0a233c91,// 89 PAY  50 

    0xc3403e85,// 90 PAY  51 

    0xa40837d7,// 91 PAY  52 

    0xd71d5986,// 92 PAY  53 

    0x7d8ca3c3,// 93 PAY  54 

    0x4b30a052,// 94 PAY  55 

    0x3aba6888,// 95 PAY  56 

    0x53ebd89e,// 96 PAY  57 

    0xa23f928b,// 97 PAY  58 

    0xd662f7fa,// 98 PAY  59 

    0xb3f7bf04,// 99 PAY  60 

    0x8710daf6,// 100 PAY  61 

    0x16a57b1f,// 101 PAY  62 

    0x3f171890,// 102 PAY  63 

    0xa74e3e16,// 103 PAY  64 

    0x692ddbeb,// 104 PAY  65 

    0x0ea0d6ac,// 105 PAY  66 

    0x292b1cc1,// 106 PAY  67 

    0x682c501f,// 107 PAY  68 

    0x63106e01,// 108 PAY  69 

    0x6bb49727,// 109 PAY  70 

    0xc1d1df32,// 110 PAY  71 

    0xc9f05e2d,// 111 PAY  72 

    0x5591c27b,// 112 PAY  73 

    0x201255a8,// 113 PAY  74 

    0xa9179216,// 114 PAY  75 

    0x4f2a7c8b,// 115 PAY  76 

    0x36cd7960,// 116 PAY  77 

    0xf2042006,// 117 PAY  78 

    0x823711b9,// 118 PAY  79 

    0x53f068fd,// 119 PAY  80 

    0x791ab25b,// 120 PAY  81 

    0xaf510a07,// 121 PAY  82 

    0xf3afe286,// 122 PAY  83 

    0x93ec1c5f,// 123 PAY  84 

    0xa88a12ea,// 124 PAY  85 

    0x2c4de881,// 125 PAY  86 

    0x54153a2c,// 126 PAY  87 

    0x04129b11,// 127 PAY  88 

    0x6caa7594,// 128 PAY  89 

    0x51476b08,// 129 PAY  90 

    0x588a32df,// 130 PAY  91 

    0x85b96929,// 131 PAY  92 

    0x6a3a0e5a,// 132 PAY  93 

    0xefe63e7a,// 133 PAY  94 

    0x856259f4,// 134 PAY  95 

    0x30149643,// 135 PAY  96 

    0xa155f337,// 136 PAY  97 

    0xa353df6e,// 137 PAY  98 

    0xa8dc0756,// 138 PAY  99 

    0x899833e1,// 139 PAY 100 

    0xf2bacb09,// 140 PAY 101 

    0xf4707201,// 141 PAY 102 

    0x3d59664e,// 142 PAY 103 

    0x9fc947e3,// 143 PAY 104 

    0xe2664944,// 144 PAY 105 

    0x2bae9822,// 145 PAY 106 

    0xd5f0455b,// 146 PAY 107 

    0x11c4815d,// 147 PAY 108 

    0x07a215fa,// 148 PAY 109 

    0x91bb4c02,// 149 PAY 110 

    0xf225133d,// 150 PAY 111 

    0x96a1d625,// 151 PAY 112 

    0xc960dd12,// 152 PAY 113 

    0xa99a9b48,// 153 PAY 114 

    0xddc3b498,// 154 PAY 115 

    0xd9b4b1e1,// 155 PAY 116 

    0x1e47a156,// 156 PAY 117 

    0x6e856d8c,// 157 PAY 118 

    0xb09fadd4,// 158 PAY 119 

    0xdd7dadb2,// 159 PAY 120 

    0x729433ec,// 160 PAY 121 

    0xb59e2f80,// 161 PAY 122 

    0x97187eeb,// 162 PAY 123 

    0x259d7782,// 163 PAY 124 

    0x5f4b2f78,// 164 PAY 125 

    0x7c9f9459,// 165 PAY 126 

    0xe2b32441,// 166 PAY 127 

    0xebc6bdc0,// 167 PAY 128 

    0x806333b1,// 168 PAY 129 

    0x7c482afe,// 169 PAY 130 

    0xfe960f66,// 170 PAY 131 

    0x04fb96a0,// 171 PAY 132 

    0xddbb9ffb,// 172 PAY 133 

    0x8b982a3b,// 173 PAY 134 

    0xc2f5cca7,// 174 PAY 135 

    0x408144bf,// 175 PAY 136 

    0xe325347e,// 176 PAY 137 

    0xdb2b17a5,// 177 PAY 138 

    0xdbae6bcb,// 178 PAY 139 

    0x4821ec4e,// 179 PAY 140 

    0x9051edbc,// 180 PAY 141 

    0x61643ead,// 181 PAY 142 

    0x67d23f62,// 182 PAY 143 

    0xb4ff714e,// 183 PAY 144 

    0x6d406be7,// 184 PAY 145 

    0x18ec2796,// 185 PAY 146 

    0x110211af,// 186 PAY 147 

    0x75776ad5,// 187 PAY 148 

    0x879adc70,// 188 PAY 149 

    0x29ec0cbd,// 189 PAY 150 

    0xe5d9b18a,// 190 PAY 151 

    0x6ff39f74,// 191 PAY 152 

    0x8a21d946,// 192 PAY 153 

    0x9a804654,// 193 PAY 154 

    0x868bfdd9,// 194 PAY 155 

    0x7d42706e,// 195 PAY 156 

    0x30aa3a11,// 196 PAY 157 

    0x702b87ee,// 197 PAY 158 

    0x191397e1,// 198 PAY 159 

    0xe125f8c2,// 199 PAY 160 

    0xc339efbc,// 200 PAY 161 

    0xe44a287a,// 201 PAY 162 

    0x35d22e61,// 202 PAY 163 

    0xecb449ad,// 203 PAY 164 

    0x9db764c5,// 204 PAY 165 

    0x423dc51f,// 205 PAY 166 

    0x12b31864,// 206 PAY 167 

    0xa9090c9d,// 207 PAY 168 

    0xeba6857d,// 208 PAY 169 

    0x1090116b,// 209 PAY 170 

    0x8c54df86,// 210 PAY 171 

    0x3aa14744,// 211 PAY 172 

    0x1e564b9e,// 212 PAY 173 

    0x144012f6,// 213 PAY 174 

    0xad3ff031,// 214 PAY 175 

    0x10b6df8a,// 215 PAY 176 

    0xfab6988c,// 216 PAY 177 

    0xb0f48a97,// 217 PAY 178 

    0xaa908c81,// 218 PAY 179 

    0x6b318090,// 219 PAY 180 

    0x1027b3ae,// 220 PAY 181 

    0xf6f82248,// 221 PAY 182 

    0x408bfdd5,// 222 PAY 183 

    0x05c1d5fe,// 223 PAY 184 

    0xb82dd639,// 224 PAY 185 

    0x7dd9b21b,// 225 PAY 186 

    0x87000000,// 226 PAY 187 

/// STA is 1 words. 

/// STA num_pkts       : 44 

/// STA pkt_idx        : 214 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xe8 

    0x0359e82c // 227 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt11_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x01 

/// ECH pdu_tag        : 0x00 

    0x00010000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x2 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x8082483e,// 4 SCX   2 

    0x00007200,// 5 SCX   3 

    0xe69a9842,// 6 SCX   4 

    0x5e03a171,// 7 SCX   5 

    0x0df3fa30,// 8 SCX   6 

    0x0b787088,// 9 SCX   7 

    0xf5abc2ff,// 10 SCX   8 

    0x54134657,// 11 SCX   9 

    0x4d4b1114,// 12 SCX  10 

    0x862562e5,// 13 SCX  11 

    0x15ae2cc8,// 14 SCX  12 

    0x0e4b2bf0,// 15 SCX  13 

    0x99a3fee8,// 16 SCX  14 

    0x9d153eec,// 17 SCX  15 

    0x2f492576,// 18 SCX  16 

    0x43de03f6,// 19 SCX  17 

    0xdc0409dd,// 20 SCX  18 

    0xd7e84ab5,// 21 SCX  19 

    0xbec2581a,// 22 SCX  20 

    0xa9b299e4,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1472 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 66 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 66 

/// BFD lencrypto      : 32 

/// BFD ofstcrypto     : 20 

/// BFD (ofst+len)cry  : 52 

/// BFD ofstiv         : 4 

/// BFD ofsticv        : 980 

    0x00000042,// 24 BFD   1 

    0x00140020,// 25 BFD   2 

    0x03d40004,// 26 BFD   3 

/// MFM is 1 words. 

/// MFM vldnibs        : 4 

    0x040013b6,// 27 MFM   1 

/// BDA is 369 words. 

/// BDA size     is 1472 (0x5c0) 

/// BDA id       is 0x906 

    0x05c00906,// 28 BDA   1 

/// PAY Generic Data size   : 1472 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0x054050f8,// 29 PAY   1 

    0x752de8f0,// 30 PAY   2 

    0xcbad4284,// 31 PAY   3 

    0x027f3b8f,// 32 PAY   4 

    0x6e08d1b3,// 33 PAY   5 

    0xb32b8ccb,// 34 PAY   6 

    0x516bed93,// 35 PAY   7 

    0xc0af06ea,// 36 PAY   8 

    0xeb5442be,// 37 PAY   9 

    0x37322649,// 38 PAY  10 

    0x668af793,// 39 PAY  11 

    0x1d1f0d37,// 40 PAY  12 

    0xac60c7ea,// 41 PAY  13 

    0x9b2e7081,// 42 PAY  14 

    0xf36a3d08,// 43 PAY  15 

    0x13c465ff,// 44 PAY  16 

    0x7bf94f14,// 45 PAY  17 

    0x436db5cb,// 46 PAY  18 

    0x3cea67e6,// 47 PAY  19 

    0x0c4e3d93,// 48 PAY  20 

    0x96510e8e,// 49 PAY  21 

    0x46ff83a1,// 50 PAY  22 

    0xc9a5df06,// 51 PAY  23 

    0x2ae9f275,// 52 PAY  24 

    0x883de9f3,// 53 PAY  25 

    0xcfc11ba8,// 54 PAY  26 

    0xf031c5f8,// 55 PAY  27 

    0xf6ce2774,// 56 PAY  28 

    0x8d78b1cb,// 57 PAY  29 

    0x3b3befd1,// 58 PAY  30 

    0x6e93b9dd,// 59 PAY  31 

    0x327a5b4c,// 60 PAY  32 

    0xa43f3a97,// 61 PAY  33 

    0x1a1caa8f,// 62 PAY  34 

    0xa8682e9c,// 63 PAY  35 

    0x890552f8,// 64 PAY  36 

    0x73260d03,// 65 PAY  37 

    0x54f979a0,// 66 PAY  38 

    0x90b0dbaf,// 67 PAY  39 

    0xda810f0c,// 68 PAY  40 

    0x23511260,// 69 PAY  41 

    0x55a7424f,// 70 PAY  42 

    0x5e6c73b3,// 71 PAY  43 

    0x384cef42,// 72 PAY  44 

    0x2d63d83e,// 73 PAY  45 

    0x5f5212a3,// 74 PAY  46 

    0x7b306669,// 75 PAY  47 

    0x6ab0af8d,// 76 PAY  48 

    0xd456c3c0,// 77 PAY  49 

    0x2fad6279,// 78 PAY  50 

    0x7a374d22,// 79 PAY  51 

    0x06978533,// 80 PAY  52 

    0xcb3255bb,// 81 PAY  53 

    0xdca531f4,// 82 PAY  54 

    0xb3ff11d0,// 83 PAY  55 

    0xafa281e6,// 84 PAY  56 

    0x95b68e4e,// 85 PAY  57 

    0xa7322a7d,// 86 PAY  58 

    0x2fb90315,// 87 PAY  59 

    0x32492be3,// 88 PAY  60 

    0x0d5193c5,// 89 PAY  61 

    0x42e37ff2,// 90 PAY  62 

    0xa896ef3c,// 91 PAY  63 

    0x2eda34e0,// 92 PAY  64 

    0x80c57db2,// 93 PAY  65 

    0x73a62440,// 94 PAY  66 

    0x97a59904,// 95 PAY  67 

    0xda4b990a,// 96 PAY  68 

    0xc20c764b,// 97 PAY  69 

    0x0d03f0bd,// 98 PAY  70 

    0xe167a0d6,// 99 PAY  71 

    0xec2b0e57,// 100 PAY  72 

    0xc379a17a,// 101 PAY  73 

    0x3bacbe89,// 102 PAY  74 

    0x7eaa7ade,// 103 PAY  75 

    0xaa102562,// 104 PAY  76 

    0xf95478dc,// 105 PAY  77 

    0x6bcd9ccd,// 106 PAY  78 

    0x21adb193,// 107 PAY  79 

    0x6c93a565,// 108 PAY  80 

    0x166f7124,// 109 PAY  81 

    0xecd272c4,// 110 PAY  82 

    0xe0933108,// 111 PAY  83 

    0xd6880d1d,// 112 PAY  84 

    0xc4105c9b,// 113 PAY  85 

    0x277432c2,// 114 PAY  86 

    0xc30a8b78,// 115 PAY  87 

    0x9ced9b95,// 116 PAY  88 

    0x1446d2a9,// 117 PAY  89 

    0x9560c5c1,// 118 PAY  90 

    0xb1656469,// 119 PAY  91 

    0x6585fc3a,// 120 PAY  92 

    0x5a3dfe46,// 121 PAY  93 

    0xbd60cd8c,// 122 PAY  94 

    0x1a8a0cfb,// 123 PAY  95 

    0xe1a72da2,// 124 PAY  96 

    0x416c8514,// 125 PAY  97 

    0x2e932ee9,// 126 PAY  98 

    0xcb5ed8a0,// 127 PAY  99 

    0xb38cce61,// 128 PAY 100 

    0xbeb0a704,// 129 PAY 101 

    0x41b0f536,// 130 PAY 102 

    0x54ff7bee,// 131 PAY 103 

    0x950e5313,// 132 PAY 104 

    0xf503b557,// 133 PAY 105 

    0xdacba06c,// 134 PAY 106 

    0x4a4c4e0b,// 135 PAY 107 

    0x35a841bd,// 136 PAY 108 

    0xde508424,// 137 PAY 109 

    0x2fab6984,// 138 PAY 110 

    0x7d6db8ee,// 139 PAY 111 

    0x0e7d04a4,// 140 PAY 112 

    0x54d3042a,// 141 PAY 113 

    0xa08c504f,// 142 PAY 114 

    0x7737506a,// 143 PAY 115 

    0x32fcc2d9,// 144 PAY 116 

    0xbdcdcd1f,// 145 PAY 117 

    0x3a29edda,// 146 PAY 118 

    0xc9c85418,// 147 PAY 119 

    0x585741b1,// 148 PAY 120 

    0x94b9c742,// 149 PAY 121 

    0xbb6c2553,// 150 PAY 122 

    0xaff12e29,// 151 PAY 123 

    0x2ae46f42,// 152 PAY 124 

    0xa0ff06df,// 153 PAY 125 

    0x4343994b,// 154 PAY 126 

    0xdd131482,// 155 PAY 127 

    0x7ba9e498,// 156 PAY 128 

    0x73a51dbb,// 157 PAY 129 

    0xa3e8a7b8,// 158 PAY 130 

    0xa062be02,// 159 PAY 131 

    0x5381da81,// 160 PAY 132 

    0x9ec04b8b,// 161 PAY 133 

    0xca2b3e22,// 162 PAY 134 

    0x24b14d45,// 163 PAY 135 

    0xf1e9aa44,// 164 PAY 136 

    0x72c8069f,// 165 PAY 137 

    0x10aa87af,// 166 PAY 138 

    0xfa00f9b6,// 167 PAY 139 

    0x126c6630,// 168 PAY 140 

    0x187af8d8,// 169 PAY 141 

    0xcb6e5ad3,// 170 PAY 142 

    0x9403e84b,// 171 PAY 143 

    0x4b69121e,// 172 PAY 144 

    0x84c385f6,// 173 PAY 145 

    0xad0277ee,// 174 PAY 146 

    0xb4ddd5ef,// 175 PAY 147 

    0x8bba353c,// 176 PAY 148 

    0x3e7dec84,// 177 PAY 149 

    0x010b0da9,// 178 PAY 150 

    0xc8088058,// 179 PAY 151 

    0x25a81c0b,// 180 PAY 152 

    0xbda826c4,// 181 PAY 153 

    0x4e7c21cc,// 182 PAY 154 

    0x73f3d61d,// 183 PAY 155 

    0xe739ae09,// 184 PAY 156 

    0x7791aabb,// 185 PAY 157 

    0xd9fc40dd,// 186 PAY 158 

    0x69a4dbc9,// 187 PAY 159 

    0x88fffb9e,// 188 PAY 160 

    0x6d8d5609,// 189 PAY 161 

    0xfd308f38,// 190 PAY 162 

    0x10b1911e,// 191 PAY 163 

    0xc8c294d6,// 192 PAY 164 

    0xc4bbb7e5,// 193 PAY 165 

    0xd967c849,// 194 PAY 166 

    0x88e750e4,// 195 PAY 167 

    0xadbd7f91,// 196 PAY 168 

    0x7efd05dd,// 197 PAY 169 

    0x866efb02,// 198 PAY 170 

    0x12391a15,// 199 PAY 171 

    0xf55eb464,// 200 PAY 172 

    0x317e0f29,// 201 PAY 173 

    0xf25d5037,// 202 PAY 174 

    0x71a833b6,// 203 PAY 175 

    0x1648e696,// 204 PAY 176 

    0xcb9949a1,// 205 PAY 177 

    0xe8f83439,// 206 PAY 178 

    0xa06cc068,// 207 PAY 179 

    0x3b0c095c,// 208 PAY 180 

    0x6cc70313,// 209 PAY 181 

    0xacab14c6,// 210 PAY 182 

    0xfd51b6bf,// 211 PAY 183 

    0x08754a4b,// 212 PAY 184 

    0xd4615f45,// 213 PAY 185 

    0x998ecf25,// 214 PAY 186 

    0xc8d8fd59,// 215 PAY 187 

    0xab0fb83b,// 216 PAY 188 

    0x4e8ac1c6,// 217 PAY 189 

    0x96fee4d9,// 218 PAY 190 

    0x7d8fc21e,// 219 PAY 191 

    0x22627f0e,// 220 PAY 192 

    0xcd90384b,// 221 PAY 193 

    0xb5b66c99,// 222 PAY 194 

    0x4c1061f8,// 223 PAY 195 

    0xb068a0ee,// 224 PAY 196 

    0x08fef841,// 225 PAY 197 

    0xfaf8a575,// 226 PAY 198 

    0xb813de9c,// 227 PAY 199 

    0xb3618e06,// 228 PAY 200 

    0xcb05bda7,// 229 PAY 201 

    0xf48e760e,// 230 PAY 202 

    0xe389c79a,// 231 PAY 203 

    0x8d53bbf1,// 232 PAY 204 

    0x94f471eb,// 233 PAY 205 

    0x9653551d,// 234 PAY 206 

    0x33dec2b6,// 235 PAY 207 

    0xd6c2dfef,// 236 PAY 208 

    0xd826ef6a,// 237 PAY 209 

    0x2249f93c,// 238 PAY 210 

    0x8cfdef87,// 239 PAY 211 

    0x896a9652,// 240 PAY 212 

    0x1116aa46,// 241 PAY 213 

    0x4020cbc9,// 242 PAY 214 

    0x9687cbb1,// 243 PAY 215 

    0x9958aabe,// 244 PAY 216 

    0xadad8167,// 245 PAY 217 

    0xd71e9aa8,// 246 PAY 218 

    0x93518a69,// 247 PAY 219 

    0xf494939c,// 248 PAY 220 

    0x0237e022,// 249 PAY 221 

    0xedd14f98,// 250 PAY 222 

    0x85c08de7,// 251 PAY 223 

    0xe4e59b7d,// 252 PAY 224 

    0xe3925297,// 253 PAY 225 

    0xaa0a91cd,// 254 PAY 226 

    0x9128a168,// 255 PAY 227 

    0xe6abc90f,// 256 PAY 228 

    0x86a6052c,// 257 PAY 229 

    0xb47342aa,// 258 PAY 230 

    0xe3b106b0,// 259 PAY 231 

    0x7671395b,// 260 PAY 232 

    0xe0d0d9c7,// 261 PAY 233 

    0x67edc5af,// 262 PAY 234 

    0x405d83cf,// 263 PAY 235 

    0x9d3942a0,// 264 PAY 236 

    0x5258282a,// 265 PAY 237 

    0x51732f05,// 266 PAY 238 

    0xe363d5d8,// 267 PAY 239 

    0xb826efa5,// 268 PAY 240 

    0xb3a95439,// 269 PAY 241 

    0x881fa2a4,// 270 PAY 242 

    0xa04d2df1,// 271 PAY 243 

    0x5a8dc412,// 272 PAY 244 

    0xaded396b,// 273 PAY 245 

    0xc22ce556,// 274 PAY 246 

    0xd6644481,// 275 PAY 247 

    0x0c6531de,// 276 PAY 248 

    0xef7dd1d8,// 277 PAY 249 

    0x387276fa,// 278 PAY 250 

    0x618f2c95,// 279 PAY 251 

    0xbb84c89a,// 280 PAY 252 

    0xa69f8a61,// 281 PAY 253 

    0x714e2fef,// 282 PAY 254 

    0xcd719bf0,// 283 PAY 255 

    0xf538704d,// 284 PAY 256 

    0x9448a395,// 285 PAY 257 

    0x88e06ce4,// 286 PAY 258 

    0x1ade376a,// 287 PAY 259 

    0x5df95e5d,// 288 PAY 260 

    0x94bd1ce2,// 289 PAY 261 

    0x7201d5a3,// 290 PAY 262 

    0x97f496fc,// 291 PAY 263 

    0x5b3d9525,// 292 PAY 264 

    0xddf2f8ac,// 293 PAY 265 

    0x8976c38e,// 294 PAY 266 

    0xee16a877,// 295 PAY 267 

    0xd95d774f,// 296 PAY 268 

    0x793ebd99,// 297 PAY 269 

    0x0600857e,// 298 PAY 270 

    0xe90c9640,// 299 PAY 271 

    0x0d723895,// 300 PAY 272 

    0x160f5cee,// 301 PAY 273 

    0xd0a3599d,// 302 PAY 274 

    0x7351462a,// 303 PAY 275 

    0x76b7e299,// 304 PAY 276 

    0x13c5dd27,// 305 PAY 277 

    0x8eb11bf7,// 306 PAY 278 

    0xc9ce8933,// 307 PAY 279 

    0x2337fb2b,// 308 PAY 280 

    0x62896df6,// 309 PAY 281 

    0x7d91e9ad,// 310 PAY 282 

    0x4dadf760,// 311 PAY 283 

    0xc0724ac2,// 312 PAY 284 

    0x2d102bb6,// 313 PAY 285 

    0xdb46a07f,// 314 PAY 286 

    0x1eaa06f1,// 315 PAY 287 

    0x91692df1,// 316 PAY 288 

    0xf7eab869,// 317 PAY 289 

    0xc3b20574,// 318 PAY 290 

    0xe19bf4c4,// 319 PAY 291 

    0xc15da5c3,// 320 PAY 292 

    0x24b7f79d,// 321 PAY 293 

    0xf1d5ab72,// 322 PAY 294 

    0x016d8988,// 323 PAY 295 

    0x6373c78b,// 324 PAY 296 

    0xe41ad8a2,// 325 PAY 297 

    0x50c570a1,// 326 PAY 298 

    0x9c557c3e,// 327 PAY 299 

    0x9082c806,// 328 PAY 300 

    0xbf25879f,// 329 PAY 301 

    0x5bd1cbb8,// 330 PAY 302 

    0xcbf8bee0,// 331 PAY 303 

    0xb3e2b971,// 332 PAY 304 

    0x10d38568,// 333 PAY 305 

    0x3dc947ba,// 334 PAY 306 

    0x536fc5d0,// 335 PAY 307 

    0x1ce7201e,// 336 PAY 308 

    0xe1cf9e0d,// 337 PAY 309 

    0x4a30d65c,// 338 PAY 310 

    0x4d199c2f,// 339 PAY 311 

    0x4c623984,// 340 PAY 312 

    0xaba96ccc,// 341 PAY 313 

    0xd8c6ac42,// 342 PAY 314 

    0x6f825c19,// 343 PAY 315 

    0xa0ef5588,// 344 PAY 316 

    0x1f324b30,// 345 PAY 317 

    0x3e48bae0,// 346 PAY 318 

    0x524fbfb5,// 347 PAY 319 

    0x4870fe17,// 348 PAY 320 

    0x039ebc44,// 349 PAY 321 

    0x7d9908db,// 350 PAY 322 

    0x73d0b925,// 351 PAY 323 

    0x80236510,// 352 PAY 324 

    0xf808c71a,// 353 PAY 325 

    0x4c02e872,// 354 PAY 326 

    0x3eb71bb0,// 355 PAY 327 

    0x8d970c7a,// 356 PAY 328 

    0x60411262,// 357 PAY 329 

    0x009d0204,// 358 PAY 330 

    0xb019451f,// 359 PAY 331 

    0x6d51377e,// 360 PAY 332 

    0xda649e2f,// 361 PAY 333 

    0x88d2e594,// 362 PAY 334 

    0x53eefeb0,// 363 PAY 335 

    0xe7ef110f,// 364 PAY 336 

    0x8b09a8b7,// 365 PAY 337 

    0xbb1611f6,// 366 PAY 338 

    0x3352a938,// 367 PAY 339 

    0x3954c5ef,// 368 PAY 340 

    0x4ffeb2ae,// 369 PAY 341 

    0x982779ed,// 370 PAY 342 

    0x176b023a,// 371 PAY 343 

    0x5f24552b,// 372 PAY 344 

    0x9543135b,// 373 PAY 345 

    0x47a29bf5,// 374 PAY 346 

    0x629ab7b5,// 375 PAY 347 

    0x05960861,// 376 PAY 348 

    0xce5fd20f,// 377 PAY 349 

    0x2d67bc6c,// 378 PAY 350 

    0x998308e9,// 379 PAY 351 

    0x4ae3ec89,// 380 PAY 352 

    0x7e2e0e42,// 381 PAY 353 

    0x74189848,// 382 PAY 354 

    0xcb6e2041,// 383 PAY 355 

    0xb816ae5e,// 384 PAY 356 

    0x9fad92d0,// 385 PAY 357 

    0x5c92bd67,// 386 PAY 358 

    0x1b192721,// 387 PAY 359 

    0xeb93652f,// 388 PAY 360 

    0xc104bcb7,// 389 PAY 361 

    0xe9c9975e,// 390 PAY 362 

    0x2481f8a0,// 391 PAY 363 

    0xb110d244,// 392 PAY 364 

    0x9843be5e,// 393 PAY 365 

    0x405eb80d,// 394 PAY 366 

    0x5385c5b9,// 395 PAY 367 

    0xbd466b20,// 396 PAY 368 

/// STA is 1 words. 

/// STA num_pkts       : 10 

/// STA pkt_idx        : 216 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x7c 

    0x03607c0a // 397 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt12_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x0a 

/// ECH pdu_tag        : 0x00 

    0x000a0000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv insert_icv check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000015,// 3 SCX   1 

    0x808448b2,// 4 SCX   2 

    0x00003184,// 5 SCX   3 

    0x81fb5b3b,// 6 SCX   4 

    0xc20a0b5b,// 7 SCX   5 

    0xb02459b2,// 8 SCX   6 

    0xf9de0733,// 9 SCX   7 

    0x024147cf,// 10 SCX   8 

    0x40c18299,// 11 SCX   9 

    0xacaba97e,// 12 SCX  10 

    0x7437eda9,// 13 SCX  11 

    0x43b9df14,// 14 SCX  12 

    0x491a0a9e,// 15 SCX  13 

    0x7d872c05,// 16 SCX  14 

    0x8618da5c,// 17 SCX  15 

    0x897cdbc3,// 18 SCX  16 

    0xc46711f9,// 19 SCX  17 

    0x9ae20df5,// 20 SCX  18 

    0x3ecc5cc4,// 21 SCX  19 

    0x06ede13e,// 22 SCX  20 

    0xaadc61ff,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 688 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 35 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 35 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 16 

/// BFD (ofst+len)cry  : 32 

/// BFD ofstiv         : 0 

/// BFD ofsticv        : 204 

    0x00000023,// 24 BFD   1 

    0x00100010,// 25 BFD   2 

    0x00cc0000,// 26 BFD   3 

/// MFM is 1 words. 

/// MFM vldnibs        : 3 

    0x03003820,// 27 MFM   1 

/// BDA is 173 words. 

/// BDA size     is 688 (0x2b0) 

/// BDA id       is 0x79ee 

    0x02b079ee,// 28 BDA   1 

/// PAY Generic Data size   : 688 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0x0af21026,// 29 PAY   1 

    0x46781300,// 30 PAY   2 

    0x735a9290,// 31 PAY   3 

    0x5b7edd51,// 32 PAY   4 

    0xba012eb3,// 33 PAY   5 

    0x0f157e71,// 34 PAY   6 

    0x6e00c677,// 35 PAY   7 

    0x5b7c2d82,// 36 PAY   8 

    0x6d7ab3ce,// 37 PAY   9 

    0x58e1cef5,// 38 PAY  10 

    0x68761e67,// 39 PAY  11 

    0x2b4eec92,// 40 PAY  12 

    0x426fcc4c,// 41 PAY  13 

    0xbee6b78a,// 42 PAY  14 

    0x91aa1488,// 43 PAY  15 

    0x05bd1c21,// 44 PAY  16 

    0x5279530c,// 45 PAY  17 

    0x2edbd840,// 46 PAY  18 

    0xd4112095,// 47 PAY  19 

    0xb186ba7a,// 48 PAY  20 

    0x8de434d2,// 49 PAY  21 

    0xac05de5e,// 50 PAY  22 

    0xfebf5d29,// 51 PAY  23 

    0xe49c37f8,// 52 PAY  24 

    0x0db2beb0,// 53 PAY  25 

    0xf02b150e,// 54 PAY  26 

    0x483d022b,// 55 PAY  27 

    0xe58b6da0,// 56 PAY  28 

    0x5165adda,// 57 PAY  29 

    0xc5bd2f3f,// 58 PAY  30 

    0xc9582342,// 59 PAY  31 

    0x40fbf075,// 60 PAY  32 

    0x428b2ad5,// 61 PAY  33 

    0x35f1e372,// 62 PAY  34 

    0x16c36ff7,// 63 PAY  35 

    0xf8b7b17d,// 64 PAY  36 

    0xf709b320,// 65 PAY  37 

    0x115765cf,// 66 PAY  38 

    0xcb6f495c,// 67 PAY  39 

    0xf1216ed2,// 68 PAY  40 

    0x758d44e5,// 69 PAY  41 

    0x1ed5d16c,// 70 PAY  42 

    0xd98e4d50,// 71 PAY  43 

    0x1dd55082,// 72 PAY  44 

    0x7ae6b9ef,// 73 PAY  45 

    0xaa96685e,// 74 PAY  46 

    0xcafdf3a3,// 75 PAY  47 

    0xf4440105,// 76 PAY  48 

    0x6e5e4540,// 77 PAY  49 

    0x22a876e5,// 78 PAY  50 

    0x40b7ed19,// 79 PAY  51 

    0xa93125e3,// 80 PAY  52 

    0x5825caeb,// 81 PAY  53 

    0x9906934e,// 82 PAY  54 

    0xf4b8fade,// 83 PAY  55 

    0xbb277792,// 84 PAY  56 

    0x92866d98,// 85 PAY  57 

    0x9681c03a,// 86 PAY  58 

    0xa509da4a,// 87 PAY  59 

    0x78b3427d,// 88 PAY  60 

    0x9cc6e5a3,// 89 PAY  61 

    0xc2743061,// 90 PAY  62 

    0xac4ea492,// 91 PAY  63 

    0xcb76515b,// 92 PAY  64 

    0xf12b8022,// 93 PAY  65 

    0xd2257034,// 94 PAY  66 

    0xb2422ac6,// 95 PAY  67 

    0x7973c319,// 96 PAY  68 

    0xab06b056,// 97 PAY  69 

    0xc5bfd1f2,// 98 PAY  70 

    0x174b83ca,// 99 PAY  71 

    0x9b3f8d53,// 100 PAY  72 

    0xae881a5d,// 101 PAY  73 

    0x53d10c08,// 102 PAY  74 

    0xce71ef1a,// 103 PAY  75 

    0xf107f9db,// 104 PAY  76 

    0xe8af6224,// 105 PAY  77 

    0xdedc23a7,// 106 PAY  78 

    0x1fb7707b,// 107 PAY  79 

    0xc2331d27,// 108 PAY  80 

    0xec719594,// 109 PAY  81 

    0x09b735aa,// 110 PAY  82 

    0xbc677e2e,// 111 PAY  83 

    0x935f5d0d,// 112 PAY  84 

    0x6bbe7d15,// 113 PAY  85 

    0x7c796385,// 114 PAY  86 

    0x998556df,// 115 PAY  87 

    0xcbd99982,// 116 PAY  88 

    0x6210d0a3,// 117 PAY  89 

    0xd4157a63,// 118 PAY  90 

    0x42c8b81c,// 119 PAY  91 

    0x36bb31a9,// 120 PAY  92 

    0xc25808d8,// 121 PAY  93 

    0x0a529739,// 122 PAY  94 

    0xa07a2447,// 123 PAY  95 

    0x5204d480,// 124 PAY  96 

    0xa555113d,// 125 PAY  97 

    0xa530ed94,// 126 PAY  98 

    0x7e23b79a,// 127 PAY  99 

    0x99620c5a,// 128 PAY 100 

    0x032b5baa,// 129 PAY 101 

    0xb447c365,// 130 PAY 102 

    0x90db7311,// 131 PAY 103 

    0x3177b104,// 132 PAY 104 

    0x16fbbf9f,// 133 PAY 105 

    0xc6d0808c,// 134 PAY 106 

    0xf3aa5550,// 135 PAY 107 

    0x015a026e,// 136 PAY 108 

    0x279afd78,// 137 PAY 109 

    0x2964600b,// 138 PAY 110 

    0x20626202,// 139 PAY 111 

    0x9f3c0606,// 140 PAY 112 

    0xe129eb2d,// 141 PAY 113 

    0x207292e0,// 142 PAY 114 

    0x6a89ce8e,// 143 PAY 115 

    0x3b857df8,// 144 PAY 116 

    0x5e0d5866,// 145 PAY 117 

    0x9a7df2bf,// 146 PAY 118 

    0xcef3faa9,// 147 PAY 119 

    0x0d8b9537,// 148 PAY 120 

    0x30e1da9a,// 149 PAY 121 

    0x0bf461a9,// 150 PAY 122 

    0x0499e119,// 151 PAY 123 

    0x259fb9cb,// 152 PAY 124 

    0xb4bef5be,// 153 PAY 125 

    0x755f5495,// 154 PAY 126 

    0xd3c9e7b6,// 155 PAY 127 

    0xe5f17410,// 156 PAY 128 

    0xff2a6658,// 157 PAY 129 

    0x50868a22,// 158 PAY 130 

    0x01fda41e,// 159 PAY 131 

    0x4e08de0e,// 160 PAY 132 

    0x036c1baf,// 161 PAY 133 

    0x41dd44d2,// 162 PAY 134 

    0x3c67a8c9,// 163 PAY 135 

    0x502521c7,// 164 PAY 136 

    0x9168bf1c,// 165 PAY 137 

    0x3cf26144,// 166 PAY 138 

    0x1361b492,// 167 PAY 139 

    0x7c80dc35,// 168 PAY 140 

    0x80110f86,// 169 PAY 141 

    0x8331da77,// 170 PAY 142 

    0xee9ab219,// 171 PAY 143 

    0xe3d98ea7,// 172 PAY 144 

    0x9b13e366,// 173 PAY 145 

    0xd5c5963a,// 174 PAY 146 

    0xaffcb31b,// 175 PAY 147 

    0x4f7274b7,// 176 PAY 148 

    0xa0dbfe69,// 177 PAY 149 

    0xf30d0793,// 178 PAY 150 

    0xce4a92f5,// 179 PAY 151 

    0xdef4ba48,// 180 PAY 152 

    0x27109ead,// 181 PAY 153 

    0x961191e4,// 182 PAY 154 

    0xc71d0b70,// 183 PAY 155 

    0xa1ef4206,// 184 PAY 156 

    0xdc5fba0e,// 185 PAY 157 

    0xe1ecb8a7,// 186 PAY 158 

    0xae1663b5,// 187 PAY 159 

    0x33959d47,// 188 PAY 160 

    0xa0020fce,// 189 PAY 161 

    0x43ccfad2,// 190 PAY 162 

    0x433472f9,// 191 PAY 163 

    0xae1193bc,// 192 PAY 164 

    0xf45d6525,// 193 PAY 165 

    0xf0254d3a,// 194 PAY 166 

    0x1b1bdb8f,// 195 PAY 167 

    0xbb7dcde2,// 196 PAY 168 

    0xcb8b1c72,// 197 PAY 169 

    0xcada00e2,// 198 PAY 170 

    0x07ef5cf6,// 199 PAY 171 

    0x90f819b5,// 200 PAY 172 

/// STA is 1 words. 

/// STA num_pkts       : 116 

/// STA pkt_idx        : 70 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xcf 

    0x0119cf74 // 201 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt13_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x05 

/// ECH pdu_tag        : 0x00 

    0x00050000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x808248b7,// 4 SCX   2 

    0x00006500,// 5 SCX   3 

    0x87881312,// 6 SCX   4 

    0x234475c6,// 7 SCX   5 

    0x91e6de42,// 8 SCX   6 

    0x645d57b7,// 9 SCX   7 

    0xb4b092d3,// 10 SCX   8 

    0xa5757684,// 11 SCX   9 

    0xbe89e9fb,// 12 SCX  10 

    0xae9ecf92,// 13 SCX  11 

    0x719c5dc9,// 14 SCX  12 

    0xaec511ee,// 15 SCX  13 

    0x20b24ad1,// 16 SCX  14 

    0x93e976d3,// 17 SCX  15 

    0x8c7b82ea,// 18 SCX  16 

    0x713db1e2,// 19 SCX  17 

    0x7426a498,// 20 SCX  18 

    0x3056c034,// 21 SCX  19 

    0x7b9d4e33,// 22 SCX  20 

    0xb65972cf,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1709 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 884 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 884 

/// BFD lencrypto      : 64 

/// BFD ofstcrypto     : 636 

/// BFD (ofst+len)cry  : 700 

/// BFD ofstiv         : 276 

/// BFD ofsticv        : 1144 

    0x00000374,// 24 BFD   1 

    0x027c0040,// 25 BFD   2 

    0x04780114,// 26 BFD   3 

/// MFM is 11 words. 

/// MFM vldnibs        : 52 

    0x52008df9,// 27 MFM   1 

    0x31e85b55,// 28 MFM   2 

    0x8f42cc47,// 29 MFM   3 

    0x69411235,// 30 MFM   4 

    0xddbadc84,// 31 MFM   5 

    0xe0e7bbbd,// 32 MFM   6 

    0x2c929859,// 33 MFM   7 

    0x58f0de88,// 34 MFM   8 

    0x426532ce,// 35 MFM   9 

    0x86cea436,// 36 MFM  10 

    0xab468c00,// 37 MFM  11 

/// BDA is 429 words. 

/// BDA size     is 1709 (0x6ad) 

/// BDA id       is 0x91a 

    0x06ad091a,// 38 BDA   1 

/// PAY Generic Data size   : 1709 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x217f8f27,// 39 PAY   1 

    0x49d2a6ff,// 40 PAY   2 

    0xc83b2f92,// 41 PAY   3 

    0x35bcb58f,// 42 PAY   4 

    0x5e117217,// 43 PAY   5 

    0xf52bb811,// 44 PAY   6 

    0xed76b3f4,// 45 PAY   7 

    0xf7138d47,// 46 PAY   8 

    0xec368332,// 47 PAY   9 

    0xcfb6cd39,// 48 PAY  10 

    0x1cf2d476,// 49 PAY  11 

    0x971a681e,// 50 PAY  12 

    0x209e7e7c,// 51 PAY  13 

    0xe54816fb,// 52 PAY  14 

    0x2b7c8ca3,// 53 PAY  15 

    0x75515b15,// 54 PAY  16 

    0xd6788929,// 55 PAY  17 

    0xc7c3c436,// 56 PAY  18 

    0xf3241fb1,// 57 PAY  19 

    0x95a69561,// 58 PAY  20 

    0xe13b129a,// 59 PAY  21 

    0x5d3d4189,// 60 PAY  22 

    0x7ec298d3,// 61 PAY  23 

    0x2395f052,// 62 PAY  24 

    0x1c9f1ba5,// 63 PAY  25 

    0x4330091c,// 64 PAY  26 

    0xb417f212,// 65 PAY  27 

    0x94cfa75e,// 66 PAY  28 

    0xfe931f1d,// 67 PAY  29 

    0xb6a9844e,// 68 PAY  30 

    0x346c6f11,// 69 PAY  31 

    0xc2d50b8f,// 70 PAY  32 

    0x97b1acaa,// 71 PAY  33 

    0x12a837d2,// 72 PAY  34 

    0x2d5148fa,// 73 PAY  35 

    0x9b7c69d3,// 74 PAY  36 

    0x04c38b92,// 75 PAY  37 

    0x7e2674ac,// 76 PAY  38 

    0x7decebd0,// 77 PAY  39 

    0x12b813ff,// 78 PAY  40 

    0xe71aacfd,// 79 PAY  41 

    0xdace2528,// 80 PAY  42 

    0xfe4ec648,// 81 PAY  43 

    0x28efbd93,// 82 PAY  44 

    0x894d4715,// 83 PAY  45 

    0x80670c8a,// 84 PAY  46 

    0x3d359da1,// 85 PAY  47 

    0x505c2303,// 86 PAY  48 

    0xe8f15ec1,// 87 PAY  49 

    0xf63616db,// 88 PAY  50 

    0x887ca7c6,// 89 PAY  51 

    0xea0b99e8,// 90 PAY  52 

    0x4dfc9e10,// 91 PAY  53 

    0xdaa06570,// 92 PAY  54 

    0xf990b1f9,// 93 PAY  55 

    0x7f28a01f,// 94 PAY  56 

    0x9d1642a5,// 95 PAY  57 

    0x742bdd03,// 96 PAY  58 

    0x139d793d,// 97 PAY  59 

    0x89f747c9,// 98 PAY  60 

    0x0fcf5dc7,// 99 PAY  61 

    0x367d465f,// 100 PAY  62 

    0x17f0044b,// 101 PAY  63 

    0xc444f68c,// 102 PAY  64 

    0xb8c8c32c,// 103 PAY  65 

    0xce52a481,// 104 PAY  66 

    0x50273edc,// 105 PAY  67 

    0x1fcbad8f,// 106 PAY  68 

    0x5e8ff0a6,// 107 PAY  69 

    0x3567ba28,// 108 PAY  70 

    0x8c6888e4,// 109 PAY  71 

    0x4a6ad06e,// 110 PAY  72 

    0xed2c566d,// 111 PAY  73 

    0x76834dec,// 112 PAY  74 

    0x8985f9c9,// 113 PAY  75 

    0xafe5ba33,// 114 PAY  76 

    0x4357b0a0,// 115 PAY  77 

    0xf709da7b,// 116 PAY  78 

    0x6898e65c,// 117 PAY  79 

    0xcdb4af06,// 118 PAY  80 

    0x57fcda92,// 119 PAY  81 

    0xebf21972,// 120 PAY  82 

    0x5407cb06,// 121 PAY  83 

    0x12df2c8b,// 122 PAY  84 

    0xa4fec5b5,// 123 PAY  85 

    0x10d2c3a7,// 124 PAY  86 

    0x9d5644ef,// 125 PAY  87 

    0x94db09bb,// 126 PAY  88 

    0x792b7f0b,// 127 PAY  89 

    0x58ec9e9b,// 128 PAY  90 

    0x07e58ae5,// 129 PAY  91 

    0xdeadfd22,// 130 PAY  92 

    0xdce73b86,// 131 PAY  93 

    0xf38b405f,// 132 PAY  94 

    0x696a32ee,// 133 PAY  95 

    0x9da76370,// 134 PAY  96 

    0x4d65bcbb,// 135 PAY  97 

    0xe77cde02,// 136 PAY  98 

    0xa7555f8f,// 137 PAY  99 

    0xf9fae6c4,// 138 PAY 100 

    0x3abad1ad,// 139 PAY 101 

    0xa1a30665,// 140 PAY 102 

    0x5e3c1767,// 141 PAY 103 

    0xc3cbe564,// 142 PAY 104 

    0x3cb44328,// 143 PAY 105 

    0x36bf0fde,// 144 PAY 106 

    0x2dd6b67e,// 145 PAY 107 

    0x81a38aef,// 146 PAY 108 

    0x231bc893,// 147 PAY 109 

    0x27cdba01,// 148 PAY 110 

    0x588a6e22,// 149 PAY 111 

    0x4f91c11c,// 150 PAY 112 

    0xa30d2fc4,// 151 PAY 113 

    0x65d55aba,// 152 PAY 114 

    0xe0f23984,// 153 PAY 115 

    0x9d138bf6,// 154 PAY 116 

    0xc9f872b3,// 155 PAY 117 

    0xebfaf92b,// 156 PAY 118 

    0x6c61e483,// 157 PAY 119 

    0xfb21b7aa,// 158 PAY 120 

    0xd2f5f7ce,// 159 PAY 121 

    0x0cdab480,// 160 PAY 122 

    0x14880a40,// 161 PAY 123 

    0x162e5f89,// 162 PAY 124 

    0x798ecfb2,// 163 PAY 125 

    0xcb18754f,// 164 PAY 126 

    0xf7985220,// 165 PAY 127 

    0x89f769e9,// 166 PAY 128 

    0xc0623efb,// 167 PAY 129 

    0xbde03d41,// 168 PAY 130 

    0xcf3a3dc7,// 169 PAY 131 

    0x14f9569f,// 170 PAY 132 

    0xa27b4db3,// 171 PAY 133 

    0x1ead972a,// 172 PAY 134 

    0xf9d1afc5,// 173 PAY 135 

    0xd8f8aed7,// 174 PAY 136 

    0x1828cacd,// 175 PAY 137 

    0x53329e7d,// 176 PAY 138 

    0xfe2f5354,// 177 PAY 139 

    0x420cf69e,// 178 PAY 140 

    0xc552004c,// 179 PAY 141 

    0xf47ced60,// 180 PAY 142 

    0xfc9e4d6f,// 181 PAY 143 

    0x1c90d564,// 182 PAY 144 

    0xa01c1297,// 183 PAY 145 

    0xc7ff3af8,// 184 PAY 146 

    0xbac3ecf2,// 185 PAY 147 

    0xbb37d29b,// 186 PAY 148 

    0xd3ae7bf8,// 187 PAY 149 

    0x2bb1c68a,// 188 PAY 150 

    0xcb2ab7f9,// 189 PAY 151 

    0xfb2a02c1,// 190 PAY 152 

    0xdbc3c1a1,// 191 PAY 153 

    0x7aaa02cf,// 192 PAY 154 

    0x69c0d0cb,// 193 PAY 155 

    0xf65108a3,// 194 PAY 156 

    0x95164fa5,// 195 PAY 157 

    0xef399a05,// 196 PAY 158 

    0x48fcd8cc,// 197 PAY 159 

    0x53426c3e,// 198 PAY 160 

    0x35a58ebd,// 199 PAY 161 

    0x5fc2aa44,// 200 PAY 162 

    0xc2309372,// 201 PAY 163 

    0x34eb1866,// 202 PAY 164 

    0x64baa998,// 203 PAY 165 

    0x30590fa7,// 204 PAY 166 

    0xa3c750d4,// 205 PAY 167 

    0x5eec600a,// 206 PAY 168 

    0xa593916b,// 207 PAY 169 

    0x33f59297,// 208 PAY 170 

    0x25f2a72c,// 209 PAY 171 

    0x842aabfa,// 210 PAY 172 

    0xc0c417ee,// 211 PAY 173 

    0x8f4e6d8e,// 212 PAY 174 

    0x2aa873a3,// 213 PAY 175 

    0x2ce534e5,// 214 PAY 176 

    0x46ad479c,// 215 PAY 177 

    0x54755434,// 216 PAY 178 

    0x14255b50,// 217 PAY 179 

    0xeb6eef52,// 218 PAY 180 

    0x350008ab,// 219 PAY 181 

    0x4d18142c,// 220 PAY 182 

    0xd6728619,// 221 PAY 183 

    0x8e619ee4,// 222 PAY 184 

    0x47a0b7d7,// 223 PAY 185 

    0x0b8573b2,// 224 PAY 186 

    0xe6ae1253,// 225 PAY 187 

    0x11d38b28,// 226 PAY 188 

    0x870e03f6,// 227 PAY 189 

    0x0529f0e3,// 228 PAY 190 

    0xb7b13ece,// 229 PAY 191 

    0x3c66e4be,// 230 PAY 192 

    0xe10b142e,// 231 PAY 193 

    0x46d83752,// 232 PAY 194 

    0x9c4f050d,// 233 PAY 195 

    0xd6e31735,// 234 PAY 196 

    0xe3e210eb,// 235 PAY 197 

    0x5f63eb5e,// 236 PAY 198 

    0x4832241a,// 237 PAY 199 

    0x9391fb26,// 238 PAY 200 

    0x9ab6f13b,// 239 PAY 201 

    0x3ca4fc48,// 240 PAY 202 

    0x3e17bc71,// 241 PAY 203 

    0xb6aae146,// 242 PAY 204 

    0x0a7eaa1d,// 243 PAY 205 

    0x979273ec,// 244 PAY 206 

    0x58ac19a8,// 245 PAY 207 

    0x9c0e6b4e,// 246 PAY 208 

    0x1e5039d3,// 247 PAY 209 

    0x9973e208,// 248 PAY 210 

    0xf3129683,// 249 PAY 211 

    0x188c6f88,// 250 PAY 212 

    0xded0d901,// 251 PAY 213 

    0x8ee9e5bb,// 252 PAY 214 

    0xd3d0840a,// 253 PAY 215 

    0xaf9c4b00,// 254 PAY 216 

    0xe62ea681,// 255 PAY 217 

    0xa5424d69,// 256 PAY 218 

    0xbd88e3e3,// 257 PAY 219 

    0x034e7a9b,// 258 PAY 220 

    0x06f517bb,// 259 PAY 221 

    0x2a0920a8,// 260 PAY 222 

    0xb5eb6b03,// 261 PAY 223 

    0x53b2b36b,// 262 PAY 224 

    0xe11c35cd,// 263 PAY 225 

    0x81ab9427,// 264 PAY 226 

    0x4cfbe5f1,// 265 PAY 227 

    0x4ef5bbbc,// 266 PAY 228 

    0xba6dbd64,// 267 PAY 229 

    0xbccb1e2e,// 268 PAY 230 

    0x3138a034,// 269 PAY 231 

    0x6644d2d0,// 270 PAY 232 

    0x89654473,// 271 PAY 233 

    0x79cbd30d,// 272 PAY 234 

    0x15e32c8c,// 273 PAY 235 

    0xff8f48bf,// 274 PAY 236 

    0x6d73538c,// 275 PAY 237 

    0x41671a2e,// 276 PAY 238 

    0xa4d7262c,// 277 PAY 239 

    0x299c361c,// 278 PAY 240 

    0xcf8ee44a,// 279 PAY 241 

    0xe1f0718b,// 280 PAY 242 

    0x4c0fbb15,// 281 PAY 243 

    0xb0ec5e28,// 282 PAY 244 

    0x91ee192f,// 283 PAY 245 

    0x4317fe4e,// 284 PAY 246 

    0x3af24aea,// 285 PAY 247 

    0xc0218034,// 286 PAY 248 

    0xb89e3498,// 287 PAY 249 

    0x0b59cb20,// 288 PAY 250 

    0xa47306c2,// 289 PAY 251 

    0xa34d8471,// 290 PAY 252 

    0x8985c317,// 291 PAY 253 

    0x9ade2522,// 292 PAY 254 

    0x73d90b7d,// 293 PAY 255 

    0x8562b706,// 294 PAY 256 

    0x891d935d,// 295 PAY 257 

    0xd90169ed,// 296 PAY 258 

    0xf3dc8f77,// 297 PAY 259 

    0xc00eb1df,// 298 PAY 260 

    0xd6167769,// 299 PAY 261 

    0x4a80f055,// 300 PAY 262 

    0x69f4a0aa,// 301 PAY 263 

    0x21dafb33,// 302 PAY 264 

    0xc0e86492,// 303 PAY 265 

    0x9e172f9a,// 304 PAY 266 

    0x7a860d77,// 305 PAY 267 

    0xba15523e,// 306 PAY 268 

    0x5ab63413,// 307 PAY 269 

    0x1e4ad7a0,// 308 PAY 270 

    0x676884d8,// 309 PAY 271 

    0x42a661a6,// 310 PAY 272 

    0xd424197f,// 311 PAY 273 

    0xe65e67a5,// 312 PAY 274 

    0xd2935102,// 313 PAY 275 

    0xfb872641,// 314 PAY 276 

    0xc8c23594,// 315 PAY 277 

    0x851daa1f,// 316 PAY 278 

    0x75808b8d,// 317 PAY 279 

    0x6a203307,// 318 PAY 280 

    0x09e27ec6,// 319 PAY 281 

    0x6444aec5,// 320 PAY 282 

    0xc08ceb94,// 321 PAY 283 

    0xe2120c3d,// 322 PAY 284 

    0x4c5c1b62,// 323 PAY 285 

    0xa0976123,// 324 PAY 286 

    0xef719b91,// 325 PAY 287 

    0x7a6499c0,// 326 PAY 288 

    0xc712d621,// 327 PAY 289 

    0x96ce3ecd,// 328 PAY 290 

    0x8274ecbc,// 329 PAY 291 

    0x6a60e9ed,// 330 PAY 292 

    0x4c491282,// 331 PAY 293 

    0xdb3f9e99,// 332 PAY 294 

    0x54edc82c,// 333 PAY 295 

    0x4ebaac16,// 334 PAY 296 

    0xcc85d225,// 335 PAY 297 

    0xd49ba18d,// 336 PAY 298 

    0xd500a44a,// 337 PAY 299 

    0x1fc7b762,// 338 PAY 300 

    0x2fe46644,// 339 PAY 301 

    0x188b817d,// 340 PAY 302 

    0xc966db06,// 341 PAY 303 

    0xc600e5d2,// 342 PAY 304 

    0xa32dc3e9,// 343 PAY 305 

    0xae638ef5,// 344 PAY 306 

    0x4ac4e7f9,// 345 PAY 307 

    0x74a67a46,// 346 PAY 308 

    0x44664bd4,// 347 PAY 309 

    0x160a328d,// 348 PAY 310 

    0xe852d851,// 349 PAY 311 

    0x21ca2df5,// 350 PAY 312 

    0x073992ad,// 351 PAY 313 

    0xabf45422,// 352 PAY 314 

    0x60272d7a,// 353 PAY 315 

    0x38c680dc,// 354 PAY 316 

    0xf50bbb87,// 355 PAY 317 

    0x14de4e2d,// 356 PAY 318 

    0xa7545acf,// 357 PAY 319 

    0x03b5678a,// 358 PAY 320 

    0x06490826,// 359 PAY 321 

    0x82727016,// 360 PAY 322 

    0x4c02981a,// 361 PAY 323 

    0x5e5b594f,// 362 PAY 324 

    0x66f5d7ea,// 363 PAY 325 

    0x5165a38f,// 364 PAY 326 

    0x4f974266,// 365 PAY 327 

    0x1336428f,// 366 PAY 328 

    0x2cd64f23,// 367 PAY 329 

    0xb7dd3008,// 368 PAY 330 

    0x4e7add85,// 369 PAY 331 

    0xc86afb6e,// 370 PAY 332 

    0x7ec8bb52,// 371 PAY 333 

    0xc2e43ef0,// 372 PAY 334 

    0xc338d83f,// 373 PAY 335 

    0x03522299,// 374 PAY 336 

    0x96c470b5,// 375 PAY 337 

    0x71a4dcd2,// 376 PAY 338 

    0xcf0ed51a,// 377 PAY 339 

    0x5901bbf8,// 378 PAY 340 

    0xbc507f0c,// 379 PAY 341 

    0xd6bb5e85,// 380 PAY 342 

    0xa35b032d,// 381 PAY 343 

    0xd1fd2599,// 382 PAY 344 

    0x0961a0b4,// 383 PAY 345 

    0x8781a3e8,// 384 PAY 346 

    0x885ef828,// 385 PAY 347 

    0x9dec9650,// 386 PAY 348 

    0xb538e7a7,// 387 PAY 349 

    0x2fd0fadb,// 388 PAY 350 

    0x152ebe69,// 389 PAY 351 

    0x4d871d18,// 390 PAY 352 

    0x8dd99a99,// 391 PAY 353 

    0x14e1117e,// 392 PAY 354 

    0xf496233b,// 393 PAY 355 

    0x9c3cae31,// 394 PAY 356 

    0x7eef3dc9,// 395 PAY 357 

    0xc92ba0d8,// 396 PAY 358 

    0x3c48e908,// 397 PAY 359 

    0xc7c34d88,// 398 PAY 360 

    0x425eeba3,// 399 PAY 361 

    0xa0772a4e,// 400 PAY 362 

    0x54925fbf,// 401 PAY 363 

    0x28ba5444,// 402 PAY 364 

    0x822409e1,// 403 PAY 365 

    0x74554429,// 404 PAY 366 

    0x91891957,// 405 PAY 367 

    0x5ca7a8bc,// 406 PAY 368 

    0x1dd443f8,// 407 PAY 369 

    0x96c51073,// 408 PAY 370 

    0xee4c78bb,// 409 PAY 371 

    0x2f3cbebc,// 410 PAY 372 

    0x2e5acc04,// 411 PAY 373 

    0x6ae178e6,// 412 PAY 374 

    0x3a3df664,// 413 PAY 375 

    0xe13d0c59,// 414 PAY 376 

    0xd8b2018e,// 415 PAY 377 

    0x0cfde799,// 416 PAY 378 

    0xdbbe7d21,// 417 PAY 379 

    0x7a203619,// 418 PAY 380 

    0xda86d627,// 419 PAY 381 

    0xeb9efd81,// 420 PAY 382 

    0x013a66a1,// 421 PAY 383 

    0xe46499ef,// 422 PAY 384 

    0xac222d56,// 423 PAY 385 

    0x9df40cbc,// 424 PAY 386 

    0xe186b2b8,// 425 PAY 387 

    0x63c0e84a,// 426 PAY 388 

    0x5912af9d,// 427 PAY 389 

    0x41ffc26e,// 428 PAY 390 

    0x1a0d4266,// 429 PAY 391 

    0x58a17a2b,// 430 PAY 392 

    0xe684d98c,// 431 PAY 393 

    0x9aa7b72b,// 432 PAY 394 

    0x5025fa47,// 433 PAY 395 

    0x81b09dc6,// 434 PAY 396 

    0x1ad82d7f,// 435 PAY 397 

    0xc9fce28f,// 436 PAY 398 

    0xe15ef6f9,// 437 PAY 399 

    0xa70e5f1d,// 438 PAY 400 

    0xc8e56611,// 439 PAY 401 

    0x6c35ba86,// 440 PAY 402 

    0x4d426555,// 441 PAY 403 

    0x3dee1173,// 442 PAY 404 

    0xd07e44b9,// 443 PAY 405 

    0xdae3672f,// 444 PAY 406 

    0x72a02c39,// 445 PAY 407 

    0x9fd95b4e,// 446 PAY 408 

    0xbd203c75,// 447 PAY 409 

    0x4b79e5f3,// 448 PAY 410 

    0xd27e93a9,// 449 PAY 411 

    0x81832c4b,// 450 PAY 412 

    0xe2ba0e4f,// 451 PAY 413 

    0x380f6eaa,// 452 PAY 414 

    0xcadfdec5,// 453 PAY 415 

    0x7d6aecfd,// 454 PAY 416 

    0x2f7e4a47,// 455 PAY 417 

    0x12d823f9,// 456 PAY 418 

    0x880b6f3c,// 457 PAY 419 

    0x0313aaab,// 458 PAY 420 

    0xe1b49c9a,// 459 PAY 421 

    0x67659b6e,// 460 PAY 422 

    0xa08e082c,// 461 PAY 423 

    0x713cb6ca,// 462 PAY 424 

    0x2859adc4,// 463 PAY 425 

    0x1232832c,// 464 PAY 426 

    0x888464d3,// 465 PAY 427 

    0xda000000,// 466 PAY 428 

/// STA is 1 words. 

/// STA num_pkts       : 168 

/// STA pkt_idx        : 182 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x3e 

    0x02d93ea8 // 467 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt14_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x05 

/// ECH pdu_tag        : 0x00 

    0x00050000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x80904874,// 4 SCX   2 

    0x000024c2,// 5 SCX   3 

    0x5eb4a0d2,// 6 SCX   4 

    0x5aa6df11,// 7 SCX   5 

    0xae8f0351,// 8 SCX   6 

    0xc925b30c,// 9 SCX   7 

    0x5d5cbec3,// 10 SCX   8 

    0x30b2a671,// 11 SCX   9 

    0xed2a7fe1,// 12 SCX  10 

    0xcdb31492,// 13 SCX  11 

    0x66d84def,// 14 SCX  12 

    0xee77e426,// 15 SCX  13 

    0xeec12d9f,// 16 SCX  14 

    0x95f65d53,// 17 SCX  15 

    0x9664a2e8,// 18 SCX  16 

    0x8f9926f2,// 19 SCX  17 

    0xba6f4283,// 20 SCX  18 

    0x31d12fe2,// 21 SCX  19 

    0x124ebcd2,// 22 SCX  20 

    0x9e72b65e,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1772 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 734 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 734 

/// BFD lencrypto      : 152 

/// BFD ofstcrypto     : 116 

/// BFD (ofst+len)cry  : 268 

/// BFD ofstiv         : 48 

/// BFD ofsticv        : 1040 

    0x000002de,// 24 BFD   1 

    0x00740098,// 25 BFD   2 

    0x04100030,// 26 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c00acd3,// 27 MFM   1 

    0x71673ddf,// 28 MFM   2 

    0x8375f853,// 29 MFM   3 

    0x3987f2a5,// 30 MFM   4 

    0xbe95dfc6,// 31 MFM   5 

    0xa3a5f7d7,// 32 MFM   6 

    0x8c20662c,// 33 MFM   7 

    0x5e870d96,// 34 MFM   8 

    0xa275a2e5,// 35 MFM   9 

    0x20f845bb,// 36 MFM  10 

    0x1274c101,// 37 MFM  11 

    0x651677c7,// 38 MFM  12 

    0x38ef3496,// 39 MFM  13 

    0x68334ba2,// 40 MFM  14 

    0xbe690d8e,// 41 MFM  15 

    0x22a52be9,// 42 MFM  16 

/// BDA is 444 words. 

/// BDA size     is 1772 (0x6ec) 

/// BDA id       is 0x241b 

    0x06ec241b,// 43 BDA   1 

/// PAY Generic Data size   : 1772 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0xb1f6c0e4,// 44 PAY   1 

    0xfc130bb3,// 45 PAY   2 

    0x85dd1cf7,// 46 PAY   3 

    0x72811996,// 47 PAY   4 

    0xb53c8f85,// 48 PAY   5 

    0xf32c3028,// 49 PAY   6 

    0x02b5bb41,// 50 PAY   7 

    0x9e9f249e,// 51 PAY   8 

    0xeb0764ba,// 52 PAY   9 

    0x7f22b5ef,// 53 PAY  10 

    0xb0801143,// 54 PAY  11 

    0x04a7f6dc,// 55 PAY  12 

    0xafeb6f98,// 56 PAY  13 

    0x3696e3b1,// 57 PAY  14 

    0xcb50e85f,// 58 PAY  15 

    0x56f06b2a,// 59 PAY  16 

    0x226b8691,// 60 PAY  17 

    0xa5c7b731,// 61 PAY  18 

    0x4df5b220,// 62 PAY  19 

    0x45ac1408,// 63 PAY  20 

    0x2c1a5458,// 64 PAY  21 

    0xe446cda7,// 65 PAY  22 

    0x52c762b0,// 66 PAY  23 

    0x3c642779,// 67 PAY  24 

    0xcba79440,// 68 PAY  25 

    0x3a704336,// 69 PAY  26 

    0xc8b6c901,// 70 PAY  27 

    0xd9c21c3c,// 71 PAY  28 

    0x0857ec42,// 72 PAY  29 

    0x9a18641a,// 73 PAY  30 

    0xa7d8d2ee,// 74 PAY  31 

    0x7cf23cd2,// 75 PAY  32 

    0xd90d152c,// 76 PAY  33 

    0x48bc61b2,// 77 PAY  34 

    0xcb163b8e,// 78 PAY  35 

    0xeb5f43cb,// 79 PAY  36 

    0x630fa43d,// 80 PAY  37 

    0x72431b2a,// 81 PAY  38 

    0x2af70ab2,// 82 PAY  39 

    0x840c1166,// 83 PAY  40 

    0xe16a7cdf,// 84 PAY  41 

    0x2739e258,// 85 PAY  42 

    0xb024147c,// 86 PAY  43 

    0x1c0c2638,// 87 PAY  44 

    0x8c5c72cf,// 88 PAY  45 

    0x32c8e358,// 89 PAY  46 

    0x8d159e2a,// 90 PAY  47 

    0xec1e7df1,// 91 PAY  48 

    0xd97898c0,// 92 PAY  49 

    0x28f62381,// 93 PAY  50 

    0x263db424,// 94 PAY  51 

    0x97173231,// 95 PAY  52 

    0xfb8ed35c,// 96 PAY  53 

    0x48e79868,// 97 PAY  54 

    0xf2898f34,// 98 PAY  55 

    0xd5a01d25,// 99 PAY  56 

    0x0006edba,// 100 PAY  57 

    0xb41fe8b1,// 101 PAY  58 

    0x7f6a9148,// 102 PAY  59 

    0xad935b66,// 103 PAY  60 

    0xf9839e01,// 104 PAY  61 

    0x37ba4fc2,// 105 PAY  62 

    0xb63e9698,// 106 PAY  63 

    0x59b9b76c,// 107 PAY  64 

    0xa82d5b1f,// 108 PAY  65 

    0xb21c23a3,// 109 PAY  66 

    0x384116b6,// 110 PAY  67 

    0x40836755,// 111 PAY  68 

    0xca0810b2,// 112 PAY  69 

    0x312f2e6f,// 113 PAY  70 

    0xa8aed427,// 114 PAY  71 

    0x529af83e,// 115 PAY  72 

    0x0f0e69d2,// 116 PAY  73 

    0x9a24655c,// 117 PAY  74 

    0xbdd73095,// 118 PAY  75 

    0xee6948a3,// 119 PAY  76 

    0x92a7caba,// 120 PAY  77 

    0xac6564c3,// 121 PAY  78 

    0x43b8facf,// 122 PAY  79 

    0x29760d4e,// 123 PAY  80 

    0xe041e59f,// 124 PAY  81 

    0xfbe18d75,// 125 PAY  82 

    0x0442e7c6,// 126 PAY  83 

    0x5a76ec71,// 127 PAY  84 

    0xbcc36ebe,// 128 PAY  85 

    0xf965caf6,// 129 PAY  86 

    0xd8f5c362,// 130 PAY  87 

    0x5f2515c8,// 131 PAY  88 

    0xc488e90b,// 132 PAY  89 

    0x662b8ab4,// 133 PAY  90 

    0xdfca3cec,// 134 PAY  91 

    0x96183f6f,// 135 PAY  92 

    0x0af78fec,// 136 PAY  93 

    0x12beccc8,// 137 PAY  94 

    0xbb0b404c,// 138 PAY  95 

    0xe64d2b03,// 139 PAY  96 

    0x7e12254a,// 140 PAY  97 

    0xb6f646ea,// 141 PAY  98 

    0x25e6ad64,// 142 PAY  99 

    0xeb554a74,// 143 PAY 100 

    0xe9fb1921,// 144 PAY 101 

    0x6ce32a59,// 145 PAY 102 

    0x280c87a4,// 146 PAY 103 

    0xd5b50c86,// 147 PAY 104 

    0x02db43f7,// 148 PAY 105 

    0xa5b9b172,// 149 PAY 106 

    0x68164b8a,// 150 PAY 107 

    0x50203ff7,// 151 PAY 108 

    0x5de2d8c8,// 152 PAY 109 

    0x372649dd,// 153 PAY 110 

    0xa4c283e2,// 154 PAY 111 

    0x7fcf2800,// 155 PAY 112 

    0xdd1a92dd,// 156 PAY 113 

    0xf78b0a94,// 157 PAY 114 

    0x4ca4583d,// 158 PAY 115 

    0xb4cef613,// 159 PAY 116 

    0x31b786fe,// 160 PAY 117 

    0x966e9cfc,// 161 PAY 118 

    0x09a0b05c,// 162 PAY 119 

    0x4aa83d6e,// 163 PAY 120 

    0xf679f0ff,// 164 PAY 121 

    0x747ed886,// 165 PAY 122 

    0xd34b0999,// 166 PAY 123 

    0x06ac979a,// 167 PAY 124 

    0x25040184,// 168 PAY 125 

    0x19ca5f03,// 169 PAY 126 

    0x13be60fa,// 170 PAY 127 

    0x39ed4686,// 171 PAY 128 

    0x54f0d41c,// 172 PAY 129 

    0xcf1a275f,// 173 PAY 130 

    0xc545daac,// 174 PAY 131 

    0x70166543,// 175 PAY 132 

    0x429d527a,// 176 PAY 133 

    0xb93a841f,// 177 PAY 134 

    0x867a6ace,// 178 PAY 135 

    0x82e971c9,// 179 PAY 136 

    0x7049c230,// 180 PAY 137 

    0x8aa1def2,// 181 PAY 138 

    0xa769f768,// 182 PAY 139 

    0xe05089b0,// 183 PAY 140 

    0x8e130789,// 184 PAY 141 

    0x7d61f0d9,// 185 PAY 142 

    0x058209a8,// 186 PAY 143 

    0x959c48e6,// 187 PAY 144 

    0xdcbef4bd,// 188 PAY 145 

    0x2a4bec88,// 189 PAY 146 

    0x2cbf3307,// 190 PAY 147 

    0x11d793a2,// 191 PAY 148 

    0x93863494,// 192 PAY 149 

    0x4943d3eb,// 193 PAY 150 

    0x792dec64,// 194 PAY 151 

    0xe6118fd8,// 195 PAY 152 

    0x56e76c0f,// 196 PAY 153 

    0x280e62e0,// 197 PAY 154 

    0x4de8938b,// 198 PAY 155 

    0x89711d97,// 199 PAY 156 

    0x38743e67,// 200 PAY 157 

    0x8ff8d102,// 201 PAY 158 

    0xc596c34a,// 202 PAY 159 

    0x82edf518,// 203 PAY 160 

    0xcbb3d7d0,// 204 PAY 161 

    0x105883f9,// 205 PAY 162 

    0x58c83785,// 206 PAY 163 

    0x99b64b3d,// 207 PAY 164 

    0xd9f037a5,// 208 PAY 165 

    0x719c68f2,// 209 PAY 166 

    0x9a39bbf1,// 210 PAY 167 

    0xa8ce61cf,// 211 PAY 168 

    0xe5a9b40c,// 212 PAY 169 

    0xfffac5e5,// 213 PAY 170 

    0xf26910ed,// 214 PAY 171 

    0x55c2c19b,// 215 PAY 172 

    0xe8249b45,// 216 PAY 173 

    0xcf8ace98,// 217 PAY 174 

    0xd0b335a3,// 218 PAY 175 

    0x9f858b11,// 219 PAY 176 

    0xe32e680f,// 220 PAY 177 

    0x7a61d952,// 221 PAY 178 

    0x0a00ba51,// 222 PAY 179 

    0xbdf617e7,// 223 PAY 180 

    0x3c1ba740,// 224 PAY 181 

    0x235b22a1,// 225 PAY 182 

    0xeb5183e9,// 226 PAY 183 

    0x8b8f5686,// 227 PAY 184 

    0xdb59bcc4,// 228 PAY 185 

    0x2a688d52,// 229 PAY 186 

    0xe0301259,// 230 PAY 187 

    0x9bad6488,// 231 PAY 188 

    0x4aca85f6,// 232 PAY 189 

    0xa2837340,// 233 PAY 190 

    0x12529313,// 234 PAY 191 

    0x099cb8e0,// 235 PAY 192 

    0x0dc8330a,// 236 PAY 193 

    0x9d41381a,// 237 PAY 194 

    0x135831e3,// 238 PAY 195 

    0xa22e8677,// 239 PAY 196 

    0x9920b7a9,// 240 PAY 197 

    0x157d0466,// 241 PAY 198 

    0xf50141c4,// 242 PAY 199 

    0x6b52b3c9,// 243 PAY 200 

    0x09c74048,// 244 PAY 201 

    0xac4a2b06,// 245 PAY 202 

    0xf7fc5966,// 246 PAY 203 

    0x3460bfd9,// 247 PAY 204 

    0x6d973825,// 248 PAY 205 

    0xc1b2197a,// 249 PAY 206 

    0x6b4c07ed,// 250 PAY 207 

    0x6160ac72,// 251 PAY 208 

    0x048e414a,// 252 PAY 209 

    0xd589a29e,// 253 PAY 210 

    0xea4cfc09,// 254 PAY 211 

    0x8f459e34,// 255 PAY 212 

    0x45af5d99,// 256 PAY 213 

    0x44043de0,// 257 PAY 214 

    0x7f07e13e,// 258 PAY 215 

    0xa340de6c,// 259 PAY 216 

    0xce3816a8,// 260 PAY 217 

    0xc05fdd56,// 261 PAY 218 

    0x5888814f,// 262 PAY 219 

    0x31603f5b,// 263 PAY 220 

    0x0ded6a97,// 264 PAY 221 

    0xb8793d2c,// 265 PAY 222 

    0x4d75672a,// 266 PAY 223 

    0x82ba1c2c,// 267 PAY 224 

    0x50b503b1,// 268 PAY 225 

    0x3766bb74,// 269 PAY 226 

    0x86521a88,// 270 PAY 227 

    0x84a0611a,// 271 PAY 228 

    0x7d5c7060,// 272 PAY 229 

    0xf5f9e050,// 273 PAY 230 

    0x76fa5c19,// 274 PAY 231 

    0xee123fe2,// 275 PAY 232 

    0xff59f34f,// 276 PAY 233 

    0xf17e408c,// 277 PAY 234 

    0x9e2ea7d0,// 278 PAY 235 

    0x3290e095,// 279 PAY 236 

    0x9904dc99,// 280 PAY 237 

    0xd8304f68,// 281 PAY 238 

    0x1c9fcbe9,// 282 PAY 239 

    0x2e8f4f0d,// 283 PAY 240 

    0xd5636ddf,// 284 PAY 241 

    0x99e13e59,// 285 PAY 242 

    0xff730c66,// 286 PAY 243 

    0x6ca776b7,// 287 PAY 244 

    0x0094970b,// 288 PAY 245 

    0x5b0b1237,// 289 PAY 246 

    0x6b0fd7ec,// 290 PAY 247 

    0x1056e8b7,// 291 PAY 248 

    0x93b3cb9a,// 292 PAY 249 

    0x2a5827c0,// 293 PAY 250 

    0x4dc603be,// 294 PAY 251 

    0x4bec5565,// 295 PAY 252 

    0x3bf2a65b,// 296 PAY 253 

    0xd0218444,// 297 PAY 254 

    0xfb5f4b28,// 298 PAY 255 

    0xb6591da0,// 299 PAY 256 

    0x922ef262,// 300 PAY 257 

    0x75e9f0ac,// 301 PAY 258 

    0xca6f0a1c,// 302 PAY 259 

    0x4f6ea0d3,// 303 PAY 260 

    0x81129b31,// 304 PAY 261 

    0x823eaaaf,// 305 PAY 262 

    0x2300d6d0,// 306 PAY 263 

    0xa8515d00,// 307 PAY 264 

    0x439d9722,// 308 PAY 265 

    0x37e58514,// 309 PAY 266 

    0x5c73e96d,// 310 PAY 267 

    0x8b98e4c8,// 311 PAY 268 

    0x5e9502eb,// 312 PAY 269 

    0x8511c5e5,// 313 PAY 270 

    0xb2cda944,// 314 PAY 271 

    0x19eb87cc,// 315 PAY 272 

    0xb4735207,// 316 PAY 273 

    0xa40142a3,// 317 PAY 274 

    0xf112ae01,// 318 PAY 275 

    0xbb762c9a,// 319 PAY 276 

    0x20d6ed75,// 320 PAY 277 

    0x6fe95012,// 321 PAY 278 

    0xd7c788ab,// 322 PAY 279 

    0x2f4cd4ca,// 323 PAY 280 

    0x070796f5,// 324 PAY 281 

    0x2fe85961,// 325 PAY 282 

    0x03d7b2ee,// 326 PAY 283 

    0x6cd567e5,// 327 PAY 284 

    0xa0b98540,// 328 PAY 285 

    0x6ab4b727,// 329 PAY 286 

    0x5d883d76,// 330 PAY 287 

    0xfe2143e0,// 331 PAY 288 

    0xb4e71717,// 332 PAY 289 

    0xe371992a,// 333 PAY 290 

    0x7758c8bf,// 334 PAY 291 

    0xf93437c4,// 335 PAY 292 

    0xa5772681,// 336 PAY 293 

    0x2f9ac84c,// 337 PAY 294 

    0xe29a9c70,// 338 PAY 295 

    0xbc0e4488,// 339 PAY 296 

    0xbaa7df93,// 340 PAY 297 

    0x04a520a2,// 341 PAY 298 

    0x112a5580,// 342 PAY 299 

    0x8236b1f8,// 343 PAY 300 

    0xa5861cbd,// 344 PAY 301 

    0x7ff7071a,// 345 PAY 302 

    0xe678da23,// 346 PAY 303 

    0x4ace2022,// 347 PAY 304 

    0x789b736f,// 348 PAY 305 

    0xa92f8e36,// 349 PAY 306 

    0x475fe2a3,// 350 PAY 307 

    0xa79e9adb,// 351 PAY 308 

    0xbfc31626,// 352 PAY 309 

    0xde70a480,// 353 PAY 310 

    0x805e2dca,// 354 PAY 311 

    0x6680934d,// 355 PAY 312 

    0xc46d92ea,// 356 PAY 313 

    0xec8e351b,// 357 PAY 314 

    0xcfb34d68,// 358 PAY 315 

    0xf9aa95fc,// 359 PAY 316 

    0xa2df2e2e,// 360 PAY 317 

    0x9d192e92,// 361 PAY 318 

    0xcae0d908,// 362 PAY 319 

    0xddca430a,// 363 PAY 320 

    0xc730d333,// 364 PAY 321 

    0x24448528,// 365 PAY 322 

    0x2262f405,// 366 PAY 323 

    0x1d723e08,// 367 PAY 324 

    0x72c4faf0,// 368 PAY 325 

    0xd49f6772,// 369 PAY 326 

    0x6062eca4,// 370 PAY 327 

    0x82a847ae,// 371 PAY 328 

    0xf03ad882,// 372 PAY 329 

    0xa59e5f5f,// 373 PAY 330 

    0x9c8b95f3,// 374 PAY 331 

    0xd1a1fce8,// 375 PAY 332 

    0x08a8934f,// 376 PAY 333 

    0x6e0ddea2,// 377 PAY 334 

    0x230065f5,// 378 PAY 335 

    0xf8d8411f,// 379 PAY 336 

    0xbe28d514,// 380 PAY 337 

    0x933d6100,// 381 PAY 338 

    0x7c9efa43,// 382 PAY 339 

    0x73dc6712,// 383 PAY 340 

    0x531b2e1a,// 384 PAY 341 

    0xb091e342,// 385 PAY 342 

    0xe03aba8c,// 386 PAY 343 

    0x3713418c,// 387 PAY 344 

    0x52d4d608,// 388 PAY 345 

    0x98d18182,// 389 PAY 346 

    0xa67c6c78,// 390 PAY 347 

    0xa49465bf,// 391 PAY 348 

    0x36ff48ae,// 392 PAY 349 

    0xfdfd2146,// 393 PAY 350 

    0xeddbc4e6,// 394 PAY 351 

    0x5fb0bcff,// 395 PAY 352 

    0x692e2687,// 396 PAY 353 

    0x88abeed8,// 397 PAY 354 

    0x2f2f1a55,// 398 PAY 355 

    0x1e4dabb8,// 399 PAY 356 

    0x4eb7d0d1,// 400 PAY 357 

    0x1b3dc5c5,// 401 PAY 358 

    0x7d96080e,// 402 PAY 359 

    0x3c74cbc4,// 403 PAY 360 

    0x6fbb4853,// 404 PAY 361 

    0x85e81a8f,// 405 PAY 362 

    0x3bd22fe9,// 406 PAY 363 

    0xf5ceaa7c,// 407 PAY 364 

    0xbf1632ef,// 408 PAY 365 

    0xcc51864b,// 409 PAY 366 

    0x274bbb4b,// 410 PAY 367 

    0x808cee77,// 411 PAY 368 

    0xe78cc016,// 412 PAY 369 

    0xf331ccac,// 413 PAY 370 

    0xaeac3884,// 414 PAY 371 

    0x5d1e50e6,// 415 PAY 372 

    0x08a75dae,// 416 PAY 373 

    0xf07bc79b,// 417 PAY 374 

    0x78808360,// 418 PAY 375 

    0x1c74b839,// 419 PAY 376 

    0x4a90e440,// 420 PAY 377 

    0xed5a8772,// 421 PAY 378 

    0xbc536dbf,// 422 PAY 379 

    0x306aa08a,// 423 PAY 380 

    0x31600f5b,// 424 PAY 381 

    0xc0bd6988,// 425 PAY 382 

    0x2ecf8bc8,// 426 PAY 383 

    0x930a62e7,// 427 PAY 384 

    0x3e7c5146,// 428 PAY 385 

    0x2a73ab0c,// 429 PAY 386 

    0xf5522a6e,// 430 PAY 387 

    0xcfb912f5,// 431 PAY 388 

    0x56beac22,// 432 PAY 389 

    0x2cb369ff,// 433 PAY 390 

    0x1604f1a7,// 434 PAY 391 

    0xe87b2132,// 435 PAY 392 

    0x20ea17c6,// 436 PAY 393 

    0x2717e44f,// 437 PAY 394 

    0xf878ef12,// 438 PAY 395 

    0x75b11e50,// 439 PAY 396 

    0x25efaaa3,// 440 PAY 397 

    0x7cf9ea90,// 441 PAY 398 

    0xec4c6b96,// 442 PAY 399 

    0x32c57246,// 443 PAY 400 

    0x88546db1,// 444 PAY 401 

    0x11a0afb0,// 445 PAY 402 

    0x9e15adcc,// 446 PAY 403 

    0x38780da3,// 447 PAY 404 

    0x055a3ca7,// 448 PAY 405 

    0x1a0ee810,// 449 PAY 406 

    0xb713386a,// 450 PAY 407 

    0x26bb3c0e,// 451 PAY 408 

    0xce6c9091,// 452 PAY 409 

    0xa6f26361,// 453 PAY 410 

    0x38212fe9,// 454 PAY 411 

    0x1aa4fdf6,// 455 PAY 412 

    0x63fc5e5f,// 456 PAY 413 

    0x1d545d2c,// 457 PAY 414 

    0x06d337a2,// 458 PAY 415 

    0x2f2e384b,// 459 PAY 416 

    0x1e101aa2,// 460 PAY 417 

    0x29aaf629,// 461 PAY 418 

    0x06505567,// 462 PAY 419 

    0xfe1cab1e,// 463 PAY 420 

    0x73b8a883,// 464 PAY 421 

    0xc3b379cc,// 465 PAY 422 

    0xc88bbc56,// 466 PAY 423 

    0x8c14a592,// 467 PAY 424 

    0xb11151c4,// 468 PAY 425 

    0xf5ec86d0,// 469 PAY 426 

    0xa4e31a2e,// 470 PAY 427 

    0xaae47694,// 471 PAY 428 

    0x55f01d08,// 472 PAY 429 

    0x3aa7f3e0,// 473 PAY 430 

    0x69e1284f,// 474 PAY 431 

    0x5ea0061f,// 475 PAY 432 

    0x864fcf60,// 476 PAY 433 

    0xdd40696b,// 477 PAY 434 

    0xc771ce18,// 478 PAY 435 

    0x2c8a14d1,// 479 PAY 436 

    0xdacb79b2,// 480 PAY 437 

    0xc6f9695b,// 481 PAY 438 

    0xbcda0922,// 482 PAY 439 

    0x72382f6d,// 483 PAY 440 

    0xb758a83c,// 484 PAY 441 

    0x6d6141f5,// 485 PAY 442 

    0xeb9c1307,// 486 PAY 443 

/// STA is 1 words. 

/// STA num_pkts       : 132 

/// STA pkt_idx        : 124 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x26 

    0x01f12684 // 487 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc !incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt15_tmpl[] = {
    0xa8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x06 

/// ECH pdu_tag        : 0x00 

    0x00060000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x00000015,// 3 SCX   1 

    0x808248cc,// 4 SCX   2 

    0x00003100,// 5 SCX   3 

    0xadd4a2a9,// 6 SCX   4 

    0xf384d6b2,// 7 SCX   5 

    0x4c3120ea,// 8 SCX   6 

    0x6ae61ec3,// 9 SCX   7 

    0x7248417e,// 10 SCX   8 

    0x79a78b39,// 11 SCX   9 

    0xfcc04107,// 12 SCX  10 

    0x72b9fdd9,// 13 SCX  11 

    0x836e0a31,// 14 SCX  12 

    0x5934f1df,// 15 SCX  13 

    0x274cf14c,// 16 SCX  14 

    0x58680721,// 17 SCX  15 

    0xc0267ff2,// 18 SCX  16 

    0xde37de17,// 19 SCX  17 

    0x526d7767,// 20 SCX  18 

    0x9785df81,// 21 SCX  19 

    0x6625f84a,// 22 SCX  20 

    0xf2456d58,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 240 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 51 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 51 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 32 

/// BFD (ofst+len)cry  : 48 

/// BFD ofstiv         : 12 

/// BFD ofsticv        : 220 

    0x00000033,// 24 BFD   1 

    0x00200010,// 25 BFD   2 

    0x00dc000c,// 26 BFD   3 

/// BDA is 61 words. 

/// BDA size     is 240 (0xf0) 

/// BDA id       is 0xa24 

    0x00f00a24,// 27 BDA   1 

/// PAY Generic Data size   : 240 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0x24cdbae5,// 28 PAY   1 

    0x4ebf7281,// 29 PAY   2 

    0xb5e22747,// 30 PAY   3 

    0x92edc4b5,// 31 PAY   4 

    0xc19a4bbd,// 32 PAY   5 

    0x2361b47f,// 33 PAY   6 

    0xc7169c07,// 34 PAY   7 

    0x69361fbe,// 35 PAY   8 

    0x95fc62aa,// 36 PAY   9 

    0xd9e36334,// 37 PAY  10 

    0x7e5b61d9,// 38 PAY  11 

    0x6609d589,// 39 PAY  12 

    0x435f719c,// 40 PAY  13 

    0x2938f58f,// 41 PAY  14 

    0x4d6603c2,// 42 PAY  15 

    0x29493f2b,// 43 PAY  16 

    0x6ec3258a,// 44 PAY  17 

    0xb9ab7588,// 45 PAY  18 

    0xe9bf9713,// 46 PAY  19 

    0x49cbd518,// 47 PAY  20 

    0xb50a1709,// 48 PAY  21 

    0x90b1cb0a,// 49 PAY  22 

    0x9b73bbd1,// 50 PAY  23 

    0x57ceee80,// 51 PAY  24 

    0xc62df69b,// 52 PAY  25 

    0x4fbfb668,// 53 PAY  26 

    0x8db814f7,// 54 PAY  27 

    0x3122cce9,// 55 PAY  28 

    0x5ba7d9a3,// 56 PAY  29 

    0x21b99f87,// 57 PAY  30 

    0x7cf3f8ed,// 58 PAY  31 

    0xbee8228b,// 59 PAY  32 

    0x5303aa81,// 60 PAY  33 

    0xc0feb368,// 61 PAY  34 

    0x922dd8a4,// 62 PAY  35 

    0xbd86e794,// 63 PAY  36 

    0xd5b7b8a8,// 64 PAY  37 

    0x13bcef17,// 65 PAY  38 

    0x80b5e900,// 66 PAY  39 

    0x886a212d,// 67 PAY  40 

    0x31b51011,// 68 PAY  41 

    0xeb6546a1,// 69 PAY  42 

    0xdebd9cc2,// 70 PAY  43 

    0x0f91759c,// 71 PAY  44 

    0x5ea9e83c,// 72 PAY  45 

    0xcdddc529,// 73 PAY  46 

    0x15cc9308,// 74 PAY  47 

    0xec13847d,// 75 PAY  48 

    0xc0ced4a5,// 76 PAY  49 

    0x276b7eff,// 77 PAY  50 

    0x7d22bf96,// 78 PAY  51 

    0x5bf7c067,// 79 PAY  52 

    0x0e5d5280,// 80 PAY  53 

    0xb671ade5,// 81 PAY  54 

    0x67d7a130,// 82 PAY  55 

    0xc3c2f8c2,// 83 PAY  56 

    0xfd28773b,// 84 PAY  57 

    0x5f28c63d,// 85 PAY  58 

    0xe75a1aa7,// 86 PAY  59 

    0xc382f564,// 87 PAY  60 

/// STA is 1 words. 

/// STA num_pkts       : 92 

/// STA pkt_idx        : 100 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xde 

    0x0191de5c // 88 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 72 (0x48) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt16_tmpl[] = {
    0xb8010048,// 1 CCH   1 

/// ECH cache_idx      : 0x09 

/// ECH pdu_tag        : 0x00 

    0x00090000,// 2 ECH   1 

/// SCX is 17 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000011,// 3 SCX   1 

    0x80804838,// 4 SCX   2 

    0x00003500,// 5 SCX   3 

    0x3301f00c,// 6 SCX   4 

    0x8cb7fcb0,// 7 SCX   5 

    0xe46fd4fa,// 8 SCX   6 

    0x27cd181b,// 9 SCX   7 

    0xcb8f32aa,// 10 SCX   8 

    0xcabb1b0f,// 11 SCX   9 

    0x32811373,// 12 SCX  10 

    0x2230f135,// 13 SCX  11 

    0x12316fba,// 14 SCX  12 

    0xc1bb2219,// 15 SCX  13 

    0xa5a04fb5,// 16 SCX  14 

    0xef10eaee,// 17 SCX  15 

    0x24042f1b,// 18 SCX  16 

    0x0956ef0b,// 19 SCX  17 

/// BFD is 3 words. 

/// BFD tot_len        : 235 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 189 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 189 

/// BFD lencrypto      : 32 

/// BFD ofstcrypto     : 124 

/// BFD (ofst+len)cry  : 156 

/// BFD ofstiv         : 104 

/// BFD ofsticv        : 192 

    0x000000bd,// 20 BFD   1 

    0x007c0020,// 21 BFD   2 

    0x00c00068,// 22 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : 9 

    0x090055e0,// 23 MFM   1 

    0x42244000,// 24 MFM   2 

/// BDA is 60 words. 

/// BDA size     is 235 (0xeb) 

/// BDA id       is 0x8a3d 

    0x00eb8a3d,// 25 BDA   1 

/// PAY Generic Data size   : 235 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0x776950d0,// 26 PAY   1 

    0x0b9849d9,// 27 PAY   2 

    0x4c3b7f96,// 28 PAY   3 

    0x3a3224a3,// 29 PAY   4 

    0x63c0f483,// 30 PAY   5 

    0x5980b4bf,// 31 PAY   6 

    0xdb0a6e22,// 32 PAY   7 

    0x71fbab37,// 33 PAY   8 

    0xab8c802f,// 34 PAY   9 

    0x4a11b792,// 35 PAY  10 

    0x9757f112,// 36 PAY  11 

    0x83927c9e,// 37 PAY  12 

    0xc79676c5,// 38 PAY  13 

    0x642db763,// 39 PAY  14 

    0x91855181,// 40 PAY  15 

    0x25df92d8,// 41 PAY  16 

    0x15eed87a,// 42 PAY  17 

    0xdd9ee247,// 43 PAY  18 

    0xaa6194ac,// 44 PAY  19 

    0x5d0be4d4,// 45 PAY  20 

    0x0d3f53e2,// 46 PAY  21 

    0x4a569e41,// 47 PAY  22 

    0x8e493c0a,// 48 PAY  23 

    0xb6f72cdf,// 49 PAY  24 

    0x5a11c8e4,// 50 PAY  25 

    0xe0ab5338,// 51 PAY  26 

    0x8a42782c,// 52 PAY  27 

    0xcf769938,// 53 PAY  28 

    0xad4102fc,// 54 PAY  29 

    0xdd290a87,// 55 PAY  30 

    0x4f6d467a,// 56 PAY  31 

    0x51d642bd,// 57 PAY  32 

    0x63b2668f,// 58 PAY  33 

    0x48012f06,// 59 PAY  34 

    0x909067be,// 60 PAY  35 

    0x51ffbcc2,// 61 PAY  36 

    0x5d00e5fb,// 62 PAY  37 

    0xa67a1d28,// 63 PAY  38 

    0xf78aa62d,// 64 PAY  39 

    0xd29bc7cd,// 65 PAY  40 

    0x026b8c3e,// 66 PAY  41 

    0xeb79110b,// 67 PAY  42 

    0xe1222029,// 68 PAY  43 

    0xfa3f47cc,// 69 PAY  44 

    0xe266c4e2,// 70 PAY  45 

    0x30017205,// 71 PAY  46 

    0xbec1142b,// 72 PAY  47 

    0xcc387594,// 73 PAY  48 

    0x71d9fb2f,// 74 PAY  49 

    0x4bc34b70,// 75 PAY  50 

    0xa0c48a65,// 76 PAY  51 

    0xee19ed5c,// 77 PAY  52 

    0xe110140f,// 78 PAY  53 

    0xd3ba4342,// 79 PAY  54 

    0xfc8b33c3,// 80 PAY  55 

    0x0366a0fb,// 81 PAY  56 

    0x09f0ed43,// 82 PAY  57 

    0x1d8963a3,// 83 PAY  58 

    0xddb62300,// 84 PAY  59 

/// STA is 1 words. 

/// STA num_pkts       : 124 

/// STA pkt_idx        : 247 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xc5 

    0x03dcc57c // 85 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 72 (0x48) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt17_tmpl[] = {
    0xb8010048,// 1 CCH   1 

/// ECH cache_idx      : 0x0f 

/// ECH pdu_tag        : 0x00 

    0x000f0000,// 2 ECH   1 

/// SCX is 17 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000011,// 3 SCX   1 

    0x8080487b,// 4 SCX   2 

    0x00002500,// 5 SCX   3 

    0x57dedb2b,// 6 SCX   4 

    0x8f54cafa,// 7 SCX   5 

    0xab1c2ea3,// 8 SCX   6 

    0x7f603a58,// 9 SCX   7 

    0xc9761f97,// 10 SCX   8 

    0x80a3ce17,// 11 SCX   9 

    0xab8ac270,// 12 SCX  10 

    0xcdadfd9c,// 13 SCX  11 

    0x0cf6c986,// 14 SCX  12 

    0x7d7f7bb2,// 15 SCX  13 

    0x3a781ee5,// 16 SCX  14 

    0x740619b5,// 17 SCX  15 

    0x429f85fc,// 18 SCX  16 

    0x557ec84d,// 19 SCX  17 

/// BFD is 3 words. 

/// BFD tot_len        : 177 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 89 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 89 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 44 

/// BFD (ofst+len)cry  : 60 

/// BFD ofstiv         : 4 

/// BFD ofsticv        : 120 

    0x00000059,// 20 BFD   1 

    0x002c0010,// 21 BFD   2 

    0x00780004,// 22 BFD   3 

/// MFM is 3 words. 

/// MFM vldnibs        : 14 

    0x14007cbc,// 23 MFM   1 

    0x63e26f29,// 24 MFM   2 

    0xd3c71798,// 25 MFM   3 

/// BDA is 46 words. 

/// BDA size     is 177 (0xb1) 

/// BDA id       is 0xc3ba 

    0x00b1c3ba,// 26 BDA   1 

/// PAY Generic Data size   : 177 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0xe8b99d53,// 27 PAY   1 

    0xeb6e9040,// 28 PAY   2 

    0x60314c6b,// 29 PAY   3 

    0x48765a27,// 30 PAY   4 

    0x63cb98b1,// 31 PAY   5 

    0x0511c772,// 32 PAY   6 

    0x63c97192,// 33 PAY   7 

    0x6184f4e8,// 34 PAY   8 

    0x842a5498,// 35 PAY   9 

    0xe7d032c7,// 36 PAY  10 

    0x8d6ea372,// 37 PAY  11 

    0x12be442e,// 38 PAY  12 

    0xac3f979f,// 39 PAY  13 

    0x488950f0,// 40 PAY  14 

    0x35933c88,// 41 PAY  15 

    0xb94327fa,// 42 PAY  16 

    0x1310e997,// 43 PAY  17 

    0xe098272f,// 44 PAY  18 

    0x74e1dc69,// 45 PAY  19 

    0xa2dda24d,// 46 PAY  20 

    0xef17f30e,// 47 PAY  21 

    0x7e279507,// 48 PAY  22 

    0x09c70922,// 49 PAY  23 

    0xfe80c5a8,// 50 PAY  24 

    0xac577ab5,// 51 PAY  25 

    0x77026357,// 52 PAY  26 

    0x8183e9c3,// 53 PAY  27 

    0x64478862,// 54 PAY  28 

    0x737710ea,// 55 PAY  29 

    0x8b1c7079,// 56 PAY  30 

    0x535a78a5,// 57 PAY  31 

    0xd111c5db,// 58 PAY  32 

    0x7046b97e,// 59 PAY  33 

    0x772d5100,// 60 PAY  34 

    0x10005503,// 61 PAY  35 

    0x9627c343,// 62 PAY  36 

    0xae10fc30,// 63 PAY  37 

    0x7a682d98,// 64 PAY  38 

    0x13630e57,// 65 PAY  39 

    0x97bea1f3,// 66 PAY  40 

    0x548f3724,// 67 PAY  41 

    0xbbc42263,// 68 PAY  42 

    0x7bdace7f,// 69 PAY  43 

    0x171781f5,// 70 PAY  44 

    0xd0000000,// 71 PAY  45 

/// STA is 1 words. 

/// STA num_pkts       : 137 

/// STA pkt_idx        : 109 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xc0 

    0x01b5c089 // 72 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt18_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x05 

/// ECH pdu_tag        : 0x00 

    0x00050000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv !insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000015,// 3 SCX   1 

    0x809048a9,// 4 SCX   2 

    0x000041c2,// 5 SCX   3 

    0x8f55a53f,// 6 SCX   4 

    0xc4055260,// 7 SCX   5 

    0x58b9576b,// 8 SCX   6 

    0xea162c95,// 9 SCX   7 

    0x91444c1e,// 10 SCX   8 

    0x9714ac4b,// 11 SCX   9 

    0xaaad240f,// 12 SCX  10 

    0xe748f3dc,// 13 SCX  11 

    0x2f42ecac,// 14 SCX  12 

    0x4066986b,// 15 SCX  13 

    0x90fd7e05,// 16 SCX  14 

    0x92e9e2e2,// 17 SCX  15 

    0x7c005beb,// 18 SCX  16 

    0x443ad036,// 19 SCX  17 

    0x78dde563,// 20 SCX  18 

    0x03c66a62,// 21 SCX  19 

    0x844ebf1f,// 22 SCX  20 

    0xb0024782,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1124 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 786 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 786 

/// BFD lencrypto      : 216 

/// BFD ofstcrypto     : 560 

/// BFD (ofst+len)cry  : 776 

/// BFD ofstiv         : 296 

/// BFD ofsticv        : 812 

    0x00000312,// 24 BFD   1 

    0x023000d8,// 25 BFD   2 

    0x032c0128,// 26 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : 6 

    0x0600dbd6,// 27 MFM   1 

    0x02000000,// 28 MFM   2 

/// BDA is 282 words. 

/// BDA size     is 1124 (0x464) 

/// BDA id       is 0xdbea 

    0x0464dbea,// 29 BDA   1 

/// PAY Generic Data size   : 1124 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0xb4fa0432,// 30 PAY   1 

    0x3938787c,// 31 PAY   2 

    0x0382a186,// 32 PAY   3 

    0x67fa62eb,// 33 PAY   4 

    0xb5a1561f,// 34 PAY   5 

    0x7923eed3,// 35 PAY   6 

    0xa4f11e3a,// 36 PAY   7 

    0x61c0a935,// 37 PAY   8 

    0xaddb2e19,// 38 PAY   9 

    0xeeebc88b,// 39 PAY  10 

    0xb39bbb4c,// 40 PAY  11 

    0x2476fe69,// 41 PAY  12 

    0xe527e872,// 42 PAY  13 

    0x3118762a,// 43 PAY  14 

    0x89cdef1e,// 44 PAY  15 

    0x26ec42ab,// 45 PAY  16 

    0x5be55de2,// 46 PAY  17 

    0x40615408,// 47 PAY  18 

    0x3d20064b,// 48 PAY  19 

    0x627f7f4c,// 49 PAY  20 

    0x63a693ee,// 50 PAY  21 

    0xac102d8e,// 51 PAY  22 

    0x0978b69c,// 52 PAY  23 

    0x4bafe1aa,// 53 PAY  24 

    0x20c66fff,// 54 PAY  25 

    0x4c8ce3f5,// 55 PAY  26 

    0xdf04c087,// 56 PAY  27 

    0x673677a8,// 57 PAY  28 

    0xc7f57f39,// 58 PAY  29 

    0xb4fc4900,// 59 PAY  30 

    0x16142807,// 60 PAY  31 

    0x039c71c7,// 61 PAY  32 

    0x44839c2d,// 62 PAY  33 

    0xd594214b,// 63 PAY  34 

    0xc00bfdc1,// 64 PAY  35 

    0x4134f64a,// 65 PAY  36 

    0x1f7048e8,// 66 PAY  37 

    0x5a3c99f2,// 67 PAY  38 

    0xfc8d6dea,// 68 PAY  39 

    0x05f23771,// 69 PAY  40 

    0x9e9572b3,// 70 PAY  41 

    0xc7db662f,// 71 PAY  42 

    0xbfe98042,// 72 PAY  43 

    0xa44acd94,// 73 PAY  44 

    0xa89e98f2,// 74 PAY  45 

    0xb97b762b,// 75 PAY  46 

    0xcdad43e7,// 76 PAY  47 

    0x426bc377,// 77 PAY  48 

    0x2e2bf20e,// 78 PAY  49 

    0x12d841a4,// 79 PAY  50 

    0x690f12c1,// 80 PAY  51 

    0x3d83b1b0,// 81 PAY  52 

    0x96ef02fb,// 82 PAY  53 

    0x0484a4e8,// 83 PAY  54 

    0x782b1411,// 84 PAY  55 

    0x8614a3dd,// 85 PAY  56 

    0x2f89ad8e,// 86 PAY  57 

    0xba930e96,// 87 PAY  58 

    0x1a92c54f,// 88 PAY  59 

    0x42578ee0,// 89 PAY  60 

    0x17005f36,// 90 PAY  61 

    0x28699ad3,// 91 PAY  62 

    0x68c6983a,// 92 PAY  63 

    0x788571dc,// 93 PAY  64 

    0xa892d982,// 94 PAY  65 

    0x8c97eaad,// 95 PAY  66 

    0x75441f45,// 96 PAY  67 

    0x4afe68e8,// 97 PAY  68 

    0x062bc37e,// 98 PAY  69 

    0xb9044d27,// 99 PAY  70 

    0x4ef03f43,// 100 PAY  71 

    0x7ecaa805,// 101 PAY  72 

    0x300ec008,// 102 PAY  73 

    0xd5e2de1f,// 103 PAY  74 

    0x1af15388,// 104 PAY  75 

    0xdf44da4c,// 105 PAY  76 

    0xeb72ff0f,// 106 PAY  77 

    0x844d6fbb,// 107 PAY  78 

    0x66b6e2d5,// 108 PAY  79 

    0x503bb1f6,// 109 PAY  80 

    0xc5319a49,// 110 PAY  81 

    0x7ea22b1e,// 111 PAY  82 

    0x3b796e6a,// 112 PAY  83 

    0x2178f5e7,// 113 PAY  84 

    0xd8f2590d,// 114 PAY  85 

    0xde3f605c,// 115 PAY  86 

    0x3012ba37,// 116 PAY  87 

    0xe8541d8d,// 117 PAY  88 

    0xea467812,// 118 PAY  89 

    0xebbb46d0,// 119 PAY  90 

    0x39803c48,// 120 PAY  91 

    0xa51c4675,// 121 PAY  92 

    0x2e469752,// 122 PAY  93 

    0xecde2167,// 123 PAY  94 

    0x3ee5d3d8,// 124 PAY  95 

    0x208bca93,// 125 PAY  96 

    0x5752a3d9,// 126 PAY  97 

    0xfbc3d965,// 127 PAY  98 

    0x03f91209,// 128 PAY  99 

    0x2a9d4b67,// 129 PAY 100 

    0x6331c913,// 130 PAY 101 

    0x8e1c0abf,// 131 PAY 102 

    0x680b03cf,// 132 PAY 103 

    0xb58f5caa,// 133 PAY 104 

    0x48903301,// 134 PAY 105 

    0xd560125d,// 135 PAY 106 

    0xd16939a2,// 136 PAY 107 

    0x8495b648,// 137 PAY 108 

    0x62083b13,// 138 PAY 109 

    0xfe2db590,// 139 PAY 110 

    0x7cb399fd,// 140 PAY 111 

    0xdd277b25,// 141 PAY 112 

    0xd4fedf62,// 142 PAY 113 

    0x4dac0c91,// 143 PAY 114 

    0x5eb1bec0,// 144 PAY 115 

    0x76c38205,// 145 PAY 116 

    0x50b03b5a,// 146 PAY 117 

    0x879d3a22,// 147 PAY 118 

    0xf55619d2,// 148 PAY 119 

    0x2312b2f4,// 149 PAY 120 

    0x8b773bd2,// 150 PAY 121 

    0xabc23b37,// 151 PAY 122 

    0x7597fd38,// 152 PAY 123 

    0x303fcaaf,// 153 PAY 124 

    0xd3e39c74,// 154 PAY 125 

    0x5a973d9b,// 155 PAY 126 

    0xb8333ebe,// 156 PAY 127 

    0x0e5045dd,// 157 PAY 128 

    0x9ce92bce,// 158 PAY 129 

    0x43b78583,// 159 PAY 130 

    0x2073b36c,// 160 PAY 131 

    0x1a903987,// 161 PAY 132 

    0x178f52ba,// 162 PAY 133 

    0x194ba172,// 163 PAY 134 

    0xe49d419a,// 164 PAY 135 

    0x5ec6dae5,// 165 PAY 136 

    0xac24fcf1,// 166 PAY 137 

    0xd4084c25,// 167 PAY 138 

    0xe426b64d,// 168 PAY 139 

    0xe8bd03c6,// 169 PAY 140 

    0x31bd3498,// 170 PAY 141 

    0xa92c9d02,// 171 PAY 142 

    0x61c84e5e,// 172 PAY 143 

    0xcfe2b6d9,// 173 PAY 144 

    0xedafc8a1,// 174 PAY 145 

    0x5546b57b,// 175 PAY 146 

    0x90522644,// 176 PAY 147 

    0xe49a4f03,// 177 PAY 148 

    0xf862d342,// 178 PAY 149 

    0x4699a8c3,// 179 PAY 150 

    0x9936055c,// 180 PAY 151 

    0xe7951abb,// 181 PAY 152 

    0xe16fa6f8,// 182 PAY 153 

    0x14a52eb2,// 183 PAY 154 

    0x92067bd4,// 184 PAY 155 

    0x3ccb9ca5,// 185 PAY 156 

    0xf5646d5e,// 186 PAY 157 

    0xbb2bc183,// 187 PAY 158 

    0x1aa89099,// 188 PAY 159 

    0x60b03e9e,// 189 PAY 160 

    0xb95676aa,// 190 PAY 161 

    0xa3170f6f,// 191 PAY 162 

    0xd1949e84,// 192 PAY 163 

    0xf4d280f9,// 193 PAY 164 

    0x3ccbf16f,// 194 PAY 165 

    0x530ce0ba,// 195 PAY 166 

    0xf025b7dc,// 196 PAY 167 

    0x185d35aa,// 197 PAY 168 

    0x022bb96f,// 198 PAY 169 

    0x7ae77ead,// 199 PAY 170 

    0x42a4d4e4,// 200 PAY 171 

    0x8edc2c5f,// 201 PAY 172 

    0x33e99f7c,// 202 PAY 173 

    0x0ae9cff1,// 203 PAY 174 

    0x4dc7b216,// 204 PAY 175 

    0xa3189749,// 205 PAY 176 

    0x9ad001c3,// 206 PAY 177 

    0x8c74e7ac,// 207 PAY 178 

    0x80afdf88,// 208 PAY 179 

    0x655961a3,// 209 PAY 180 

    0x2996bd9c,// 210 PAY 181 

    0x26f86c27,// 211 PAY 182 

    0xa2274fa0,// 212 PAY 183 

    0xb1dec40e,// 213 PAY 184 

    0x94f0e2e5,// 214 PAY 185 

    0x9d903ef2,// 215 PAY 186 

    0x1b7f3d5a,// 216 PAY 187 

    0x404ba125,// 217 PAY 188 

    0x8d8213e6,// 218 PAY 189 

    0xfda842cb,// 219 PAY 190 

    0x27cf0096,// 220 PAY 191 

    0x8acc9c6e,// 221 PAY 192 

    0x4fd99d91,// 222 PAY 193 

    0x92d1d7c7,// 223 PAY 194 

    0xac7634e0,// 224 PAY 195 

    0x2fde3a7d,// 225 PAY 196 

    0xa24c4338,// 226 PAY 197 

    0xc1d29bfa,// 227 PAY 198 

    0x92c803c1,// 228 PAY 199 

    0xa5dac28e,// 229 PAY 200 

    0xfcc84ce2,// 230 PAY 201 

    0x8298b189,// 231 PAY 202 

    0x5530d0ba,// 232 PAY 203 

    0xfb33fa25,// 233 PAY 204 

    0x3012f6b8,// 234 PAY 205 

    0x71d61f74,// 235 PAY 206 

    0x87cd10bd,// 236 PAY 207 

    0x8a43669a,// 237 PAY 208 

    0xb548279f,// 238 PAY 209 

    0x0a8bee17,// 239 PAY 210 

    0xfe389be7,// 240 PAY 211 

    0x7501a92e,// 241 PAY 212 

    0xbc46b148,// 242 PAY 213 

    0x892657bc,// 243 PAY 214 

    0x8f3183c0,// 244 PAY 215 

    0x1c4c7f2d,// 245 PAY 216 

    0xa2abfd45,// 246 PAY 217 

    0xbe950715,// 247 PAY 218 

    0x062cbbf5,// 248 PAY 219 

    0x87f0fa8d,// 249 PAY 220 

    0x167ab394,// 250 PAY 221 

    0xc14b481a,// 251 PAY 222 

    0x6ef857cf,// 252 PAY 223 

    0x3ac294ec,// 253 PAY 224 

    0x96d44e59,// 254 PAY 225 

    0xd9a7499c,// 255 PAY 226 

    0x7d3d4825,// 256 PAY 227 

    0x92ca0eb6,// 257 PAY 228 

    0x00234111,// 258 PAY 229 

    0xc2b7f24d,// 259 PAY 230 

    0xe7b67a63,// 260 PAY 231 

    0xf01663c4,// 261 PAY 232 

    0xb991564f,// 262 PAY 233 

    0x3d1ba290,// 263 PAY 234 

    0xe430d0a7,// 264 PAY 235 

    0xea9e6441,// 265 PAY 236 

    0x3b272914,// 266 PAY 237 

    0x89cbd0ac,// 267 PAY 238 

    0x6881a57a,// 268 PAY 239 

    0xc4472840,// 269 PAY 240 

    0x2dea35ca,// 270 PAY 241 

    0x7cf80498,// 271 PAY 242 

    0xa020d081,// 272 PAY 243 

    0x8cdb55db,// 273 PAY 244 

    0x7f27398c,// 274 PAY 245 

    0x2c91a3ca,// 275 PAY 246 

    0x28639a9e,// 276 PAY 247 

    0x9f804aca,// 277 PAY 248 

    0x14bd2a01,// 278 PAY 249 

    0x823f41a0,// 279 PAY 250 

    0xbfae014d,// 280 PAY 251 

    0xff26fb48,// 281 PAY 252 

    0x63b2e221,// 282 PAY 253 

    0xc924a421,// 283 PAY 254 

    0x3302888b,// 284 PAY 255 

    0xb4a971ba,// 285 PAY 256 

    0x6e1ff127,// 286 PAY 257 

    0x290be738,// 287 PAY 258 

    0xe98c1512,// 288 PAY 259 

    0xca68609f,// 289 PAY 260 

    0x2a1ffc28,// 290 PAY 261 

    0xaf3462da,// 291 PAY 262 

    0x8c0ac601,// 292 PAY 263 

    0x64cece64,// 293 PAY 264 

    0x611691f1,// 294 PAY 265 

    0x78be3a7d,// 295 PAY 266 

    0x3c3244b6,// 296 PAY 267 

    0xb4cbb768,// 297 PAY 268 

    0xc34838ac,// 298 PAY 269 

    0x63e28c9d,// 299 PAY 270 

    0xcff1a796,// 300 PAY 271 

    0x2d163e39,// 301 PAY 272 

    0x3059b99d,// 302 PAY 273 

    0x6f3375cf,// 303 PAY 274 

    0xba57a608,// 304 PAY 275 

    0xf27c1bee,// 305 PAY 276 

    0x829178b0,// 306 PAY 277 

    0x7281af6b,// 307 PAY 278 

    0x6b5b3bee,// 308 PAY 279 

    0x230c65a8,// 309 PAY 280 

    0x71224a56,// 310 PAY 281 

/// STA is 1 words. 

/// STA num_pkts       : 212 

/// STA pkt_idx        : 86 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xe6 

    0x0158e6d4 // 311 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 80 (0x50) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt19_tmpl[] = {
    0xb8010050,// 1 CCH   1 

/// ECH cache_idx      : 0x02 

/// ECH pdu_tag        : 0x00 

    0x00020000,// 2 ECH   1 

/// SCX is 19 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000013,// 3 SCX   1 

    0x808148c6,// 4 SCX   2 

    0x00006500,// 5 SCX   3 

    0x9cb6831d,// 6 SCX   4 

    0x6e0fd957,// 7 SCX   5 

    0x63f87a7a,// 8 SCX   6 

    0xde25b1f1,// 9 SCX   7 

    0xc3c11b00,// 10 SCX   8 

    0x405a2968,// 11 SCX   9 

    0xa0d348d9,// 12 SCX  10 

    0xb51ad2e3,// 13 SCX  11 

    0xb44b5f3c,// 14 SCX  12 

    0xb2ee353a,// 15 SCX  13 

    0x648b28f8,// 16 SCX  14 

    0x37fd3ae8,// 17 SCX  15 

    0x33eeef8a,// 18 SCX  16 

    0xf50f2230,// 19 SCX  17 

    0xf4b28dec,// 20 SCX  18 

    0x7f6f293b,// 21 SCX  19 

/// BFD is 3 words. 

/// BFD tot_len        : 1837 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 963 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 963 

/// BFD lencrypto      : 336 

/// BFD ofstcrypto     : 600 

/// BFD (ofst+len)cry  : 936 

/// BFD ofstiv         : 212 

/// BFD ofsticv        : 1116 

    0x000003c3,// 22 BFD   1 

    0x02580150,// 23 BFD   2 

    0x045c00d4,// 24 BFD   3 

/// MFM is 10 words. 

/// MFM vldnibs        : 4c 

    0x4c004e04,// 25 MFM   1 

    0x714964d0,// 26 MFM   2 

    0x68f545fd,// 27 MFM   3 

    0x5d83f78a,// 28 MFM   4 

    0xe763b30e,// 29 MFM   5 

    0x9285ff8b,// 30 MFM   6 

    0x1c58534b,// 31 MFM   7 

    0x2435b2d1,// 32 MFM   8 

    0x832937a0,// 33 MFM   9 

    0x62381f44,// 34 MFM  10 

/// BDA is 461 words. 

/// BDA size     is 1837 (0x72d) 

/// BDA id       is 0x426c 

    0x072d426c,// 35 BDA   1 

/// PAY Generic Data size   : 1837 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x3facbe09,// 36 PAY   1 

    0xcdbb6d2b,// 37 PAY   2 

    0x39b0e49c,// 38 PAY   3 

    0x815b64bf,// 39 PAY   4 

    0x85789291,// 40 PAY   5 

    0x9ce6f0a1,// 41 PAY   6 

    0x83ed0a7f,// 42 PAY   7 

    0x4ef415b8,// 43 PAY   8 

    0x69f6b9da,// 44 PAY   9 

    0x82bff0a3,// 45 PAY  10 

    0xae439fdd,// 46 PAY  11 

    0xc9021c7b,// 47 PAY  12 

    0xdb7f81b2,// 48 PAY  13 

    0x069e7a3f,// 49 PAY  14 

    0x1663ad22,// 50 PAY  15 

    0xb17a79bd,// 51 PAY  16 

    0x595ae63d,// 52 PAY  17 

    0x5c91d396,// 53 PAY  18 

    0x9cdaa1b9,// 54 PAY  19 

    0xdb2eaee9,// 55 PAY  20 

    0x45890267,// 56 PAY  21 

    0xadfda7b6,// 57 PAY  22 

    0x996274c7,// 58 PAY  23 

    0x8801b5be,// 59 PAY  24 

    0xa988ae46,// 60 PAY  25 

    0xf60c0368,// 61 PAY  26 

    0xfe2e7655,// 62 PAY  27 

    0x13f88942,// 63 PAY  28 

    0xa9e3f69f,// 64 PAY  29 

    0x61285de8,// 65 PAY  30 

    0xfddb9292,// 66 PAY  31 

    0xbfb55955,// 67 PAY  32 

    0x5316f052,// 68 PAY  33 

    0xe6de9487,// 69 PAY  34 

    0x3c801984,// 70 PAY  35 

    0x12dd19bc,// 71 PAY  36 

    0x1bf365b2,// 72 PAY  37 

    0x4377a2d0,// 73 PAY  38 

    0x1bdac452,// 74 PAY  39 

    0x422f788b,// 75 PAY  40 

    0x870aa717,// 76 PAY  41 

    0xacfd8df0,// 77 PAY  42 

    0x847a37f2,// 78 PAY  43 

    0x45be2d78,// 79 PAY  44 

    0x1cac1f31,// 80 PAY  45 

    0x9507b999,// 81 PAY  46 

    0xa4adc4e8,// 82 PAY  47 

    0x49a30807,// 83 PAY  48 

    0x3cc81bed,// 84 PAY  49 

    0xf7bd8708,// 85 PAY  50 

    0x3e9c84f8,// 86 PAY  51 

    0xd9e0a02a,// 87 PAY  52 

    0x097f9c16,// 88 PAY  53 

    0x2f2fa799,// 89 PAY  54 

    0xbb6d8ae3,// 90 PAY  55 

    0x74ab75ec,// 91 PAY  56 

    0xb96f3882,// 92 PAY  57 

    0xd39eda1d,// 93 PAY  58 

    0x7052106f,// 94 PAY  59 

    0xca323d60,// 95 PAY  60 

    0xfd275ffe,// 96 PAY  61 

    0xd5dc3c0f,// 97 PAY  62 

    0xe7a0624f,// 98 PAY  63 

    0x9cdc4a6b,// 99 PAY  64 

    0xe3f9880c,// 100 PAY  65 

    0x51297ee0,// 101 PAY  66 

    0x928706db,// 102 PAY  67 

    0x1bc1aa79,// 103 PAY  68 

    0x4952c2db,// 104 PAY  69 

    0x41005cb0,// 105 PAY  70 

    0x5a1ebfe0,// 106 PAY  71 

    0x7c498b73,// 107 PAY  72 

    0x127dbd3a,// 108 PAY  73 

    0x8b0ed761,// 109 PAY  74 

    0xa9ab0902,// 110 PAY  75 

    0x835ab227,// 111 PAY  76 

    0xd11b13a8,// 112 PAY  77 

    0x603a6984,// 113 PAY  78 

    0xe7291a75,// 114 PAY  79 

    0x6e7275d6,// 115 PAY  80 

    0x912bd26a,// 116 PAY  81 

    0x3c9a71ea,// 117 PAY  82 

    0xc7beaa36,// 118 PAY  83 

    0x782f0d23,// 119 PAY  84 

    0xd5586957,// 120 PAY  85 

    0xf122c740,// 121 PAY  86 

    0x0d6973d2,// 122 PAY  87 

    0x3671fbbd,// 123 PAY  88 

    0xbd106fe0,// 124 PAY  89 

    0xcb787cc0,// 125 PAY  90 

    0x7b2283ae,// 126 PAY  91 

    0xb5e6451f,// 127 PAY  92 

    0xe76012cf,// 128 PAY  93 

    0x177c19a1,// 129 PAY  94 

    0x3fb7666c,// 130 PAY  95 

    0x6cc4f0d0,// 131 PAY  96 

    0xa554428b,// 132 PAY  97 

    0xafa729c1,// 133 PAY  98 

    0x6f1c5d93,// 134 PAY  99 

    0x7706bc87,// 135 PAY 100 

    0x9775266e,// 136 PAY 101 

    0x14aff09b,// 137 PAY 102 

    0x4c40f945,// 138 PAY 103 

    0x853ce225,// 139 PAY 104 

    0x8519bfca,// 140 PAY 105 

    0x556c9544,// 141 PAY 106 

    0x49649a94,// 142 PAY 107 

    0x4986aac1,// 143 PAY 108 

    0x72cedfb2,// 144 PAY 109 

    0x71f66b99,// 145 PAY 110 

    0x5f51181f,// 146 PAY 111 

    0x441d44eb,// 147 PAY 112 

    0x9e9112b2,// 148 PAY 113 

    0x33a7f217,// 149 PAY 114 

    0xb53ea8aa,// 150 PAY 115 

    0x86611028,// 151 PAY 116 

    0xf734ea5d,// 152 PAY 117 

    0xb38a8cb5,// 153 PAY 118 

    0x26fe7c68,// 154 PAY 119 

    0x3eeac03d,// 155 PAY 120 

    0x295065e8,// 156 PAY 121 

    0x77d41ca5,// 157 PAY 122 

    0xa22ee64c,// 158 PAY 123 

    0xaf6171c3,// 159 PAY 124 

    0xcada88af,// 160 PAY 125 

    0xd8b4bc38,// 161 PAY 126 

    0xffa3376b,// 162 PAY 127 

    0x6c87a5e5,// 163 PAY 128 

    0xc1f9fc2e,// 164 PAY 129 

    0x25df8659,// 165 PAY 130 

    0x646d30da,// 166 PAY 131 

    0x1ace77fd,// 167 PAY 132 

    0xe0f0d6e6,// 168 PAY 133 

    0xb01292c0,// 169 PAY 134 

    0x50b04287,// 170 PAY 135 

    0x79d0ccfe,// 171 PAY 136 

    0x1d4807eb,// 172 PAY 137 

    0x6190e082,// 173 PAY 138 

    0x1607f844,// 174 PAY 139 

    0xd3d106e5,// 175 PAY 140 

    0x4c6debe5,// 176 PAY 141 

    0x0335c296,// 177 PAY 142 

    0xc0a8e5b5,// 178 PAY 143 

    0xdef83bed,// 179 PAY 144 

    0x1c69fe30,// 180 PAY 145 

    0x934be7c8,// 181 PAY 146 

    0xf679651c,// 182 PAY 147 

    0xda105320,// 183 PAY 148 

    0x75724f28,// 184 PAY 149 

    0x02ba313f,// 185 PAY 150 

    0xb1a50a76,// 186 PAY 151 

    0xbd7fe943,// 187 PAY 152 

    0xaf91e0b1,// 188 PAY 153 

    0xdc0421a8,// 189 PAY 154 

    0x01b560c7,// 190 PAY 155 

    0xfa40a619,// 191 PAY 156 

    0x0a7bff79,// 192 PAY 157 

    0x677aac9f,// 193 PAY 158 

    0x3a4b8339,// 194 PAY 159 

    0xce981503,// 195 PAY 160 

    0xa5e2c99e,// 196 PAY 161 

    0x2696f8f1,// 197 PAY 162 

    0x112aed66,// 198 PAY 163 

    0xf0820919,// 199 PAY 164 

    0x7e620b89,// 200 PAY 165 

    0x5278776d,// 201 PAY 166 

    0x20119d64,// 202 PAY 167 

    0xabc134db,// 203 PAY 168 

    0x51279b9c,// 204 PAY 169 

    0x46d2c99b,// 205 PAY 170 

    0xf3b56645,// 206 PAY 171 

    0x0b2fb89b,// 207 PAY 172 

    0x05e9f649,// 208 PAY 173 

    0x1f03c218,// 209 PAY 174 

    0x4e782a40,// 210 PAY 175 

    0xdee8425d,// 211 PAY 176 

    0x3e826ab5,// 212 PAY 177 

    0x5a322eaa,// 213 PAY 178 

    0x705e71f5,// 214 PAY 179 

    0xadf9bb08,// 215 PAY 180 

    0xe749d010,// 216 PAY 181 

    0xa344f6e7,// 217 PAY 182 

    0xb6833c42,// 218 PAY 183 

    0x2d9c2628,// 219 PAY 184 

    0x4eba60a8,// 220 PAY 185 

    0xb598c63c,// 221 PAY 186 

    0x11b3bf4f,// 222 PAY 187 

    0x7089d092,// 223 PAY 188 

    0xe5150fb3,// 224 PAY 189 

    0x8aed0bc8,// 225 PAY 190 

    0xa0e85f56,// 226 PAY 191 

    0xef80b6a8,// 227 PAY 192 

    0xfa46519a,// 228 PAY 193 

    0x0f2c72ff,// 229 PAY 194 

    0x68f54463,// 230 PAY 195 

    0x6f5588e3,// 231 PAY 196 

    0x6cafa321,// 232 PAY 197 

    0x5c8df187,// 233 PAY 198 

    0x2ab44a31,// 234 PAY 199 

    0x10878350,// 235 PAY 200 

    0x06e5b8b3,// 236 PAY 201 

    0x1bcd5cad,// 237 PAY 202 

    0xef73aa0e,// 238 PAY 203 

    0x6087939b,// 239 PAY 204 

    0x833ef9a2,// 240 PAY 205 

    0x55fdc969,// 241 PAY 206 

    0xd1580fd5,// 242 PAY 207 

    0x8344fc06,// 243 PAY 208 

    0xbf482afb,// 244 PAY 209 

    0x4b2877e9,// 245 PAY 210 

    0x9f2774c1,// 246 PAY 211 

    0xb5b0e6d8,// 247 PAY 212 

    0x9b17162c,// 248 PAY 213 

    0x50c6c88e,// 249 PAY 214 

    0xcf7bf1c9,// 250 PAY 215 

    0xcb4934cd,// 251 PAY 216 

    0xff55036f,// 252 PAY 217 

    0xe1c62d4a,// 253 PAY 218 

    0x0ba58ead,// 254 PAY 219 

    0xc5101178,// 255 PAY 220 

    0x4fed21fa,// 256 PAY 221 

    0xfa5e2042,// 257 PAY 222 

    0x6990e435,// 258 PAY 223 

    0x654d3976,// 259 PAY 224 

    0x6ab678ec,// 260 PAY 225 

    0x455fc5ab,// 261 PAY 226 

    0x4e595ac6,// 262 PAY 227 

    0xe4cb4972,// 263 PAY 228 

    0xc5c58189,// 264 PAY 229 

    0xc917ed86,// 265 PAY 230 

    0xd1c27f81,// 266 PAY 231 

    0xc0b63534,// 267 PAY 232 

    0x26c4e54d,// 268 PAY 233 

    0x26615746,// 269 PAY 234 

    0x2d5692ba,// 270 PAY 235 

    0x7fb3a1e4,// 271 PAY 236 

    0x738503a6,// 272 PAY 237 

    0xd4a5512c,// 273 PAY 238 

    0x8bccb08a,// 274 PAY 239 

    0x6b704178,// 275 PAY 240 

    0x04d68e1a,// 276 PAY 241 

    0x17824d41,// 277 PAY 242 

    0xf650ad21,// 278 PAY 243 

    0x1852b9c0,// 279 PAY 244 

    0xe050826d,// 280 PAY 245 

    0xb89269d2,// 281 PAY 246 

    0xf13e0279,// 282 PAY 247 

    0x11c32130,// 283 PAY 248 

    0x61cdfd4d,// 284 PAY 249 

    0x096a1583,// 285 PAY 250 

    0x258d45e1,// 286 PAY 251 

    0x41bf2b58,// 287 PAY 252 

    0xf540273b,// 288 PAY 253 

    0xa6a05037,// 289 PAY 254 

    0x24d0be8a,// 290 PAY 255 

    0x6d9380a6,// 291 PAY 256 

    0x9d79e06f,// 292 PAY 257 

    0xf9fdecf3,// 293 PAY 258 

    0x1502e2d2,// 294 PAY 259 

    0x2cda8116,// 295 PAY 260 

    0x8baf740c,// 296 PAY 261 

    0xd847cdf4,// 297 PAY 262 

    0xe8748926,// 298 PAY 263 

    0x3463db56,// 299 PAY 264 

    0x4a4e66a4,// 300 PAY 265 

    0x5457a7b3,// 301 PAY 266 

    0x88b6c232,// 302 PAY 267 

    0xa7741fe9,// 303 PAY 268 

    0x6dda63ec,// 304 PAY 269 

    0x0bc9f215,// 305 PAY 270 

    0x849bafe0,// 306 PAY 271 

    0x17f4899e,// 307 PAY 272 

    0x2cd1bf4e,// 308 PAY 273 

    0x54e292b4,// 309 PAY 274 

    0x54f76479,// 310 PAY 275 

    0xd3467e69,// 311 PAY 276 

    0xdb21c505,// 312 PAY 277 

    0x30b0227a,// 313 PAY 278 

    0xb299efea,// 314 PAY 279 

    0x4fb3a965,// 315 PAY 280 

    0x97934319,// 316 PAY 281 

    0x2b5832f7,// 317 PAY 282 

    0xb82167d4,// 318 PAY 283 

    0x612fe265,// 319 PAY 284 

    0x7f2cd47b,// 320 PAY 285 

    0xc2ceb9e1,// 321 PAY 286 

    0xccb177f4,// 322 PAY 287 

    0xe999b969,// 323 PAY 288 

    0xc1592666,// 324 PAY 289 

    0xecaf254e,// 325 PAY 290 

    0x666fea3b,// 326 PAY 291 

    0x19348eaa,// 327 PAY 292 

    0x15e9f39a,// 328 PAY 293 

    0x6c45eba9,// 329 PAY 294 

    0xeaa0086b,// 330 PAY 295 

    0x8f848f52,// 331 PAY 296 

    0x5ee4f389,// 332 PAY 297 

    0x76e934c3,// 333 PAY 298 

    0xb1c1f0a6,// 334 PAY 299 

    0x23d261df,// 335 PAY 300 

    0xaffdbe5c,// 336 PAY 301 

    0x566f38fb,// 337 PAY 302 

    0x2531814e,// 338 PAY 303 

    0xcc12d4cd,// 339 PAY 304 

    0xd4abc50d,// 340 PAY 305 

    0xc0dbd608,// 341 PAY 306 

    0x96647e86,// 342 PAY 307 

    0xf9caaf09,// 343 PAY 308 

    0xd3d721f6,// 344 PAY 309 

    0x0047f0db,// 345 PAY 310 

    0x8d5bf342,// 346 PAY 311 

    0x61605d3c,// 347 PAY 312 

    0x83d69abc,// 348 PAY 313 

    0xa4fe8fd0,// 349 PAY 314 

    0x06ce1c53,// 350 PAY 315 

    0xf02c0d65,// 351 PAY 316 

    0xd864f4f6,// 352 PAY 317 

    0xff76e4ab,// 353 PAY 318 

    0xd769aa85,// 354 PAY 319 

    0x92bba86b,// 355 PAY 320 

    0xca728b81,// 356 PAY 321 

    0x53856ffb,// 357 PAY 322 

    0xc075fdc0,// 358 PAY 323 

    0xd2eac4d9,// 359 PAY 324 

    0x8178e117,// 360 PAY 325 

    0xf71a62d1,// 361 PAY 326 

    0x34f851cc,// 362 PAY 327 

    0x6ea311d9,// 363 PAY 328 

    0xc1ca12b9,// 364 PAY 329 

    0xe9f8b1a1,// 365 PAY 330 

    0x822f3c6f,// 366 PAY 331 

    0x6165d521,// 367 PAY 332 

    0xc763df63,// 368 PAY 333 

    0x0573203d,// 369 PAY 334 

    0x8c66cfa3,// 370 PAY 335 

    0xcba1ffaf,// 371 PAY 336 

    0x0158d090,// 372 PAY 337 

    0x4a29d551,// 373 PAY 338 

    0x2c9d4a1d,// 374 PAY 339 

    0xa12df3e0,// 375 PAY 340 

    0x2fa5b4d2,// 376 PAY 341 

    0x78ae221d,// 377 PAY 342 

    0xeaa853b9,// 378 PAY 343 

    0x923bb4ef,// 379 PAY 344 

    0x1b1313aa,// 380 PAY 345 

    0x85c93893,// 381 PAY 346 

    0xc5dc275f,// 382 PAY 347 

    0xb3289328,// 383 PAY 348 

    0x101560e0,// 384 PAY 349 

    0x97063835,// 385 PAY 350 

    0xe553a50a,// 386 PAY 351 

    0xe66f2cbf,// 387 PAY 352 

    0x432d1b8b,// 388 PAY 353 

    0x6822bf05,// 389 PAY 354 

    0x21286d47,// 390 PAY 355 

    0x77e933d0,// 391 PAY 356 

    0x858db6e8,// 392 PAY 357 

    0xf37f63c8,// 393 PAY 358 

    0xe5661333,// 394 PAY 359 

    0xe4976bfc,// 395 PAY 360 

    0xcaf747db,// 396 PAY 361 

    0xa64db82f,// 397 PAY 362 

    0x1166b3e4,// 398 PAY 363 

    0x9ccdc58f,// 399 PAY 364 

    0xba5a12f1,// 400 PAY 365 

    0xc618bf1b,// 401 PAY 366 

    0xcc36cc3d,// 402 PAY 367 

    0xbf72bc77,// 403 PAY 368 

    0x52ed55c0,// 404 PAY 369 

    0x8e1ab105,// 405 PAY 370 

    0x3688dd13,// 406 PAY 371 

    0xb6179283,// 407 PAY 372 

    0x2607c980,// 408 PAY 373 

    0x55db37f6,// 409 PAY 374 

    0xc5995747,// 410 PAY 375 

    0x3c698a25,// 411 PAY 376 

    0xd20a0a5a,// 412 PAY 377 

    0x6fd67a34,// 413 PAY 378 

    0x824930a4,// 414 PAY 379 

    0x5557f5aa,// 415 PAY 380 

    0x190428ad,// 416 PAY 381 

    0x735a3ba3,// 417 PAY 382 

    0x671d47a2,// 418 PAY 383 

    0x25254f7b,// 419 PAY 384 

    0xe260a675,// 420 PAY 385 

    0xa7093243,// 421 PAY 386 

    0x14e9490b,// 422 PAY 387 

    0xddcd86f4,// 423 PAY 388 

    0xad681ec2,// 424 PAY 389 

    0xd0adfa14,// 425 PAY 390 

    0x2f2d20b9,// 426 PAY 391 

    0x28cfae69,// 427 PAY 392 

    0xb35a4a74,// 428 PAY 393 

    0x795b0c26,// 429 PAY 394 

    0x1115658f,// 430 PAY 395 

    0xb49b1aac,// 431 PAY 396 

    0x978841c0,// 432 PAY 397 

    0x391fb94c,// 433 PAY 398 

    0x72967f67,// 434 PAY 399 

    0x6f15c1e3,// 435 PAY 400 

    0xf04e556d,// 436 PAY 401 

    0xd3dd8314,// 437 PAY 402 

    0x8f3fe05f,// 438 PAY 403 

    0xb63df964,// 439 PAY 404 

    0x0ad9cf57,// 440 PAY 405 

    0x071785be,// 441 PAY 406 

    0x689f0803,// 442 PAY 407 

    0xe7a23c43,// 443 PAY 408 

    0xfbcde3af,// 444 PAY 409 

    0x2ffd489c,// 445 PAY 410 

    0x6e5ba174,// 446 PAY 411 

    0x8dbc916e,// 447 PAY 412 

    0x4acd687b,// 448 PAY 413 

    0xea989e2d,// 449 PAY 414 

    0x02650c62,// 450 PAY 415 

    0x02a46c61,// 451 PAY 416 

    0x5cd7b506,// 452 PAY 417 

    0xd6b3d156,// 453 PAY 418 

    0xc133b6b5,// 454 PAY 419 

    0x88a58306,// 455 PAY 420 

    0x0d7e8d5a,// 456 PAY 421 

    0x4df92ef1,// 457 PAY 422 

    0x695c3305,// 458 PAY 423 

    0xa263ae94,// 459 PAY 424 

    0x65cbdbfe,// 460 PAY 425 

    0x1cfcbaf5,// 461 PAY 426 

    0xac324cd3,// 462 PAY 427 

    0x02ab6017,// 463 PAY 428 

    0x123458c3,// 464 PAY 429 

    0xd240a84a,// 465 PAY 430 

    0x1a706150,// 466 PAY 431 

    0xffcb737c,// 467 PAY 432 

    0xe8aa824d,// 468 PAY 433 

    0x8c3bc5df,// 469 PAY 434 

    0x7ee74647,// 470 PAY 435 

    0xa120db3d,// 471 PAY 436 

    0x93c132c8,// 472 PAY 437 

    0x1bdad2db,// 473 PAY 438 

    0xdbb0530f,// 474 PAY 439 

    0xdc7f8239,// 475 PAY 440 

    0xd704ef46,// 476 PAY 441 

    0x383d0f21,// 477 PAY 442 

    0xf1530a66,// 478 PAY 443 

    0x459bc656,// 479 PAY 444 

    0x12ab6882,// 480 PAY 445 

    0x83e68c34,// 481 PAY 446 

    0xf36ead2c,// 482 PAY 447 

    0x1789e979,// 483 PAY 448 

    0xaad83033,// 484 PAY 449 

    0x591d8383,// 485 PAY 450 

    0x51b019b2,// 486 PAY 451 

    0x3530a378,// 487 PAY 452 

    0xd9bca042,// 488 PAY 453 

    0x43546c89,// 489 PAY 454 

    0x72883e5b,// 490 PAY 455 

    0x3df9bc6d,// 491 PAY 456 

    0x3e62106b,// 492 PAY 457 

    0x3bab668b,// 493 PAY 458 

    0x9f316da3,// 494 PAY 459 

    0xfd000000,// 495 PAY 460 

/// STA is 1 words. 

/// STA num_pkts       : 27 

/// STA pkt_idx        : 179 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x3c 

    0x02cc3c1b // 496 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 72 (0x48) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt20_tmpl[] = {
    0xb8010048,// 1 CCH   1 

/// ECH cache_idx      : 0x07 

/// ECH pdu_tag        : 0x00 

    0x00070000,// 2 ECH   1 

/// SCX is 17 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000011,// 3 SCX   1 

    0x808048a8,// 4 SCX   2 

    0x00004400,// 5 SCX   3 

    0x01724b61,// 6 SCX   4 

    0xe56ec4ed,// 7 SCX   5 

    0x591f1d2f,// 8 SCX   6 

    0x16ea72c9,// 9 SCX   7 

    0x41a3360e,// 10 SCX   8 

    0x5e50088e,// 11 SCX   9 

    0x0f43e3fd,// 12 SCX  10 

    0x26f421c8,// 13 SCX  11 

    0x958191e8,// 14 SCX  12 

    0xee3f2dde,// 15 SCX  13 

    0x2e4ac5d9,// 16 SCX  14 

    0x2b77b774,// 17 SCX  15 

    0x402620a7,// 18 SCX  16 

    0x6846aadc,// 19 SCX  17 

/// BFD is 3 words. 

/// BFD tot_len        : 1500 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 1221 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1221 

/// BFD lencrypto      : 80 

/// BFD ofstcrypto     : 1128 

/// BFD (ofst+len)cry  : 1208 

/// BFD ofstiv         : 280 

/// BFD ofsticv        : 1444 

    0x000004c5,// 20 BFD   1 

    0x04680050,// 21 BFD   2 

    0x05a40118,// 22 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c00a782,// 23 MFM   1 

    0x35803223,// 24 MFM   2 

    0x630716ab,// 25 MFM   3 

    0xfbfc6b53,// 26 MFM   4 

    0xf60ad70a,// 27 MFM   5 

    0x1c5ded23,// 28 MFM   6 

    0x3f89bef4,// 29 MFM   7 

    0x1004213e,// 30 MFM   8 

    0x4cc7fe11,// 31 MFM   9 

    0xfc735efe,// 32 MFM  10 

    0xab109e46,// 33 MFM  11 

    0x7343edc5,// 34 MFM  12 

    0x138870c3,// 35 MFM  13 

    0x5f00c538,// 36 MFM  14 

    0xd95a879e,// 37 MFM  15 

    0xd2de3a96,// 38 MFM  16 

/// BDA is 376 words. 

/// BDA size     is 1500 (0x5dc) 

/// BDA id       is 0x1692 

    0x05dc1692,// 39 BDA   1 

/// PAY Generic Data size   : 1500 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0xf9c1d470,// 40 PAY   1 

    0x29aa7bc2,// 41 PAY   2 

    0x24b63403,// 42 PAY   3 

    0xf2049d91,// 43 PAY   4 

    0x3e19d1f3,// 44 PAY   5 

    0xcd33bba5,// 45 PAY   6 

    0x04154796,// 46 PAY   7 

    0x61f2a978,// 47 PAY   8 

    0x8e121b63,// 48 PAY   9 

    0xeaf42c49,// 49 PAY  10 

    0x6e0c5d65,// 50 PAY  11 

    0x2ac16ae5,// 51 PAY  12 

    0xb1cb6316,// 52 PAY  13 

    0x6c1f5479,// 53 PAY  14 

    0xd3bdd75f,// 54 PAY  15 

    0x6a09d672,// 55 PAY  16 

    0xa6fbf972,// 56 PAY  17 

    0x5a362ac7,// 57 PAY  18 

    0x3d3c8a13,// 58 PAY  19 

    0x2e095bce,// 59 PAY  20 

    0xa84101aa,// 60 PAY  21 

    0x70546116,// 61 PAY  22 

    0xd65613ee,// 62 PAY  23 

    0x6e97b9cb,// 63 PAY  24 

    0x38ee7556,// 64 PAY  25 

    0x0fa4533d,// 65 PAY  26 

    0x43aff3b7,// 66 PAY  27 

    0xd6d8a8fe,// 67 PAY  28 

    0xd6c84c56,// 68 PAY  29 

    0x435b8673,// 69 PAY  30 

    0xa81b21d4,// 70 PAY  31 

    0x78ddb9d8,// 71 PAY  32 

    0xf177e7f6,// 72 PAY  33 

    0x624f6623,// 73 PAY  34 

    0x7fd20f00,// 74 PAY  35 

    0x78683270,// 75 PAY  36 

    0x05f7b962,// 76 PAY  37 

    0x9fed3d89,// 77 PAY  38 

    0x58bbc8a9,// 78 PAY  39 

    0x29bf9241,// 79 PAY  40 

    0xcb21b67b,// 80 PAY  41 

    0x02e64205,// 81 PAY  42 

    0x147dc6b3,// 82 PAY  43 

    0x2bc0d7bf,// 83 PAY  44 

    0xfb657218,// 84 PAY  45 

    0xf993871f,// 85 PAY  46 

    0x405168e5,// 86 PAY  47 

    0x97e41617,// 87 PAY  48 

    0xe05e06d6,// 88 PAY  49 

    0x503b19ad,// 89 PAY  50 

    0x1f0ec989,// 90 PAY  51 

    0x45058cd2,// 91 PAY  52 

    0xf4e1185f,// 92 PAY  53 

    0xc4ae5eff,// 93 PAY  54 

    0x080d5c11,// 94 PAY  55 

    0x6161f607,// 95 PAY  56 

    0x4817e38c,// 96 PAY  57 

    0x719d5669,// 97 PAY  58 

    0x60eb33b7,// 98 PAY  59 

    0x59230c9c,// 99 PAY  60 

    0x2617860f,// 100 PAY  61 

    0xdff05d10,// 101 PAY  62 

    0xafb54a32,// 102 PAY  63 

    0xde29b200,// 103 PAY  64 

    0x64baf386,// 104 PAY  65 

    0xbb4ddecd,// 105 PAY  66 

    0x822c3a2a,// 106 PAY  67 

    0x47c8b2c2,// 107 PAY  68 

    0xfde6ba05,// 108 PAY  69 

    0x65ac8446,// 109 PAY  70 

    0xcf89eb07,// 110 PAY  71 

    0x6d6b3946,// 111 PAY  72 

    0xd9192196,// 112 PAY  73 

    0x09f4c9d2,// 113 PAY  74 

    0x0cc08864,// 114 PAY  75 

    0x9a40435f,// 115 PAY  76 

    0xa74ed7b4,// 116 PAY  77 

    0x0245ac17,// 117 PAY  78 

    0x43ec83ac,// 118 PAY  79 

    0x49b8d962,// 119 PAY  80 

    0xb52e938d,// 120 PAY  81 

    0xe42e45d9,// 121 PAY  82 

    0x5a9e5e4c,// 122 PAY  83 

    0xb8142ffc,// 123 PAY  84 

    0x585fb562,// 124 PAY  85 

    0xfbca8810,// 125 PAY  86 

    0x1bc2d526,// 126 PAY  87 

    0x9696dbfd,// 127 PAY  88 

    0x0caa88a8,// 128 PAY  89 

    0xacdfd7b0,// 129 PAY  90 

    0x6c61857c,// 130 PAY  91 

    0xa23b6f30,// 131 PAY  92 

    0x750e55d8,// 132 PAY  93 

    0x0795c718,// 133 PAY  94 

    0xa6460fa4,// 134 PAY  95 

    0xb919857c,// 135 PAY  96 

    0x42e3c066,// 136 PAY  97 

    0xfe1a69db,// 137 PAY  98 

    0xd1394d0c,// 138 PAY  99 

    0xb22efe1e,// 139 PAY 100 

    0x0fb59192,// 140 PAY 101 

    0x411a39f5,// 141 PAY 102 

    0x600b3bac,// 142 PAY 103 

    0xbda712dc,// 143 PAY 104 

    0x033bbf79,// 144 PAY 105 

    0x8d720e73,// 145 PAY 106 

    0x90c52c11,// 146 PAY 107 

    0x7b074b5b,// 147 PAY 108 

    0x11635b4b,// 148 PAY 109 

    0xf61b2e56,// 149 PAY 110 

    0x1cd6f4c0,// 150 PAY 111 

    0x4eded6c8,// 151 PAY 112 

    0x81a54c4d,// 152 PAY 113 

    0x3a5329b0,// 153 PAY 114 

    0x9e408791,// 154 PAY 115 

    0x46f81498,// 155 PAY 116 

    0xce15539e,// 156 PAY 117 

    0xe5d0a4ce,// 157 PAY 118 

    0x7012cdb1,// 158 PAY 119 

    0x7147741f,// 159 PAY 120 

    0x9aa39799,// 160 PAY 121 

    0xf3dee3fe,// 161 PAY 122 

    0x30eebdf9,// 162 PAY 123 

    0x268b7c93,// 163 PAY 124 

    0x66aa2cff,// 164 PAY 125 

    0x9627cbb2,// 165 PAY 126 

    0x72435d4e,// 166 PAY 127 

    0xb75d6187,// 167 PAY 128 

    0xd7cef32f,// 168 PAY 129 

    0x2421b92d,// 169 PAY 130 

    0x691689c3,// 170 PAY 131 

    0xaba18801,// 171 PAY 132 

    0x2814a9cd,// 172 PAY 133 

    0x40b3c0dc,// 173 PAY 134 

    0xf22df363,// 174 PAY 135 

    0xf10488ad,// 175 PAY 136 

    0xb20bc1aa,// 176 PAY 137 

    0xb0d05aee,// 177 PAY 138 

    0x5a834f2f,// 178 PAY 139 

    0x2ca4165c,// 179 PAY 140 

    0xff6b4354,// 180 PAY 141 

    0xb363dbbf,// 181 PAY 142 

    0xb0dce2ce,// 182 PAY 143 

    0xeb891d86,// 183 PAY 144 

    0x8847964b,// 184 PAY 145 

    0x55e699f6,// 185 PAY 146 

    0x863aa4e8,// 186 PAY 147 

    0xd054d6ac,// 187 PAY 148 

    0x9b46a27b,// 188 PAY 149 

    0x8e8d22bd,// 189 PAY 150 

    0xdb1e684b,// 190 PAY 151 

    0xfaea1aa1,// 191 PAY 152 

    0x6efb5b18,// 192 PAY 153 

    0xc62f8187,// 193 PAY 154 

    0xb169283e,// 194 PAY 155 

    0xdea18f38,// 195 PAY 156 

    0x7c54ee1d,// 196 PAY 157 

    0x3deb6f49,// 197 PAY 158 

    0x913bf9c7,// 198 PAY 159 

    0xd71943a0,// 199 PAY 160 

    0x5236997c,// 200 PAY 161 

    0xefb4cbb7,// 201 PAY 162 

    0x8675a6fe,// 202 PAY 163 

    0x100e721f,// 203 PAY 164 

    0xe482b4fc,// 204 PAY 165 

    0x8a7aefb8,// 205 PAY 166 

    0x7fcea9b9,// 206 PAY 167 

    0x2d0a576b,// 207 PAY 168 

    0xbddd229c,// 208 PAY 169 

    0x631aef47,// 209 PAY 170 

    0xc6164e52,// 210 PAY 171 

    0x4b9ace60,// 211 PAY 172 

    0xd34e5ae3,// 212 PAY 173 

    0x7df6b48b,// 213 PAY 174 

    0xabfe1ec2,// 214 PAY 175 

    0x901b8241,// 215 PAY 176 

    0x8720ccdf,// 216 PAY 177 

    0x3a4dd39d,// 217 PAY 178 

    0x58e4ec93,// 218 PAY 179 

    0xb206fe74,// 219 PAY 180 

    0x367e0c49,// 220 PAY 181 

    0xe38403f5,// 221 PAY 182 

    0xdc31e3c5,// 222 PAY 183 

    0x5f58f2be,// 223 PAY 184 

    0x7827337a,// 224 PAY 185 

    0x8bfe249a,// 225 PAY 186 

    0x082994da,// 226 PAY 187 

    0xab8f694b,// 227 PAY 188 

    0xec0455d7,// 228 PAY 189 

    0x730a0ccf,// 229 PAY 190 

    0xa987cfbe,// 230 PAY 191 

    0x67409e6a,// 231 PAY 192 

    0xacbbb3a0,// 232 PAY 193 

    0x5e849e86,// 233 PAY 194 

    0x4f8c997a,// 234 PAY 195 

    0x1c288e4d,// 235 PAY 196 

    0xc43fb796,// 236 PAY 197 

    0xf67542fc,// 237 PAY 198 

    0xfac9db84,// 238 PAY 199 

    0x12403215,// 239 PAY 200 

    0x8ceb1388,// 240 PAY 201 

    0xa7b01db4,// 241 PAY 202 

    0xe89ffae8,// 242 PAY 203 

    0xb05372d6,// 243 PAY 204 

    0xa4947a88,// 244 PAY 205 

    0x8211d4f0,// 245 PAY 206 

    0x01ffb03b,// 246 PAY 207 

    0xb15bfcdc,// 247 PAY 208 

    0xa00dec10,// 248 PAY 209 

    0x0f07a8d1,// 249 PAY 210 

    0xab2ada92,// 250 PAY 211 

    0xd6a3dc94,// 251 PAY 212 

    0xfa65c286,// 252 PAY 213 

    0x23086f05,// 253 PAY 214 

    0xfe6f3069,// 254 PAY 215 

    0x3c3c693a,// 255 PAY 216 

    0x054784a0,// 256 PAY 217 

    0x31074d06,// 257 PAY 218 

    0xb5684b75,// 258 PAY 219 

    0x3da12273,// 259 PAY 220 

    0x9ed9e0ec,// 260 PAY 221 

    0x030bfa87,// 261 PAY 222 

    0xd8032d8d,// 262 PAY 223 

    0x57fa1918,// 263 PAY 224 

    0x1aad5a56,// 264 PAY 225 

    0x945b1333,// 265 PAY 226 

    0x8dd48205,// 266 PAY 227 

    0x27e7fc1f,// 267 PAY 228 

    0x28d83440,// 268 PAY 229 

    0x565f1ca1,// 269 PAY 230 

    0xecc970b7,// 270 PAY 231 

    0x4051b677,// 271 PAY 232 

    0x8314ccd8,// 272 PAY 233 

    0xc5eb6f6a,// 273 PAY 234 

    0x0ff07c96,// 274 PAY 235 

    0xadfc5516,// 275 PAY 236 

    0xcc4e41da,// 276 PAY 237 

    0x196b48cb,// 277 PAY 238 

    0xd08775aa,// 278 PAY 239 

    0x0f402a63,// 279 PAY 240 

    0x44916331,// 280 PAY 241 

    0x041f0520,// 281 PAY 242 

    0x6bffce90,// 282 PAY 243 

    0x0f7011a5,// 283 PAY 244 

    0xecfa8423,// 284 PAY 245 

    0x9f258aa5,// 285 PAY 246 

    0x281cbf17,// 286 PAY 247 

    0x9ba3f553,// 287 PAY 248 

    0xbc069319,// 288 PAY 249 

    0x61955b5a,// 289 PAY 250 

    0x6a92dddf,// 290 PAY 251 

    0xfa1589cb,// 291 PAY 252 

    0xae124ae5,// 292 PAY 253 

    0xe0b8618b,// 293 PAY 254 

    0x53117441,// 294 PAY 255 

    0x56b0ddc8,// 295 PAY 256 

    0x5f3865ad,// 296 PAY 257 

    0x7da0d06c,// 297 PAY 258 

    0xead315f0,// 298 PAY 259 

    0xbcdc841d,// 299 PAY 260 

    0x26acda4f,// 300 PAY 261 

    0x394bd7a0,// 301 PAY 262 

    0x8c8dbe70,// 302 PAY 263 

    0x5e018770,// 303 PAY 264 

    0xe9182a4a,// 304 PAY 265 

    0xca7250b3,// 305 PAY 266 

    0x4441250c,// 306 PAY 267 

    0xd3c15dfd,// 307 PAY 268 

    0x5fa097f0,// 308 PAY 269 

    0x93ed43cc,// 309 PAY 270 

    0x1ccc5d94,// 310 PAY 271 

    0x2ec5f415,// 311 PAY 272 

    0x723d2198,// 312 PAY 273 

    0xde1c9150,// 313 PAY 274 

    0x83cbf64d,// 314 PAY 275 

    0x7072ff52,// 315 PAY 276 

    0xaef836a0,// 316 PAY 277 

    0x79ba1ae1,// 317 PAY 278 

    0x69becff5,// 318 PAY 279 

    0x3a1c0ac0,// 319 PAY 280 

    0xa9998935,// 320 PAY 281 

    0x608f00db,// 321 PAY 282 

    0x7a5a7a11,// 322 PAY 283 

    0x3a00dd47,// 323 PAY 284 

    0x7932a505,// 324 PAY 285 

    0x704a2c67,// 325 PAY 286 

    0xd78c4fde,// 326 PAY 287 

    0x3ec8aac3,// 327 PAY 288 

    0x940f9183,// 328 PAY 289 

    0x963161a7,// 329 PAY 290 

    0x9f99b58f,// 330 PAY 291 

    0x790f1b50,// 331 PAY 292 

    0xfe3ff946,// 332 PAY 293 

    0x07addb79,// 333 PAY 294 

    0x9bad9b98,// 334 PAY 295 

    0xb483809f,// 335 PAY 296 

    0xa45c5b9f,// 336 PAY 297 

    0xfa928fb5,// 337 PAY 298 

    0x658e090b,// 338 PAY 299 

    0xb7e59695,// 339 PAY 300 

    0xf9bd9c43,// 340 PAY 301 

    0x00179f63,// 341 PAY 302 

    0xede1a76d,// 342 PAY 303 

    0xb7ff6532,// 343 PAY 304 

    0x2624b5e8,// 344 PAY 305 

    0x76efd4fb,// 345 PAY 306 

    0x1f359db2,// 346 PAY 307 

    0x8f1b50e1,// 347 PAY 308 

    0x1dd446c5,// 348 PAY 309 

    0xef59c556,// 349 PAY 310 

    0x3eebbe29,// 350 PAY 311 

    0xf1b783fd,// 351 PAY 312 

    0x523575ae,// 352 PAY 313 

    0x0dd0ea5c,// 353 PAY 314 

    0xfdc99a37,// 354 PAY 315 

    0x00963b62,// 355 PAY 316 

    0x99713762,// 356 PAY 317 

    0xa0063407,// 357 PAY 318 

    0x89113364,// 358 PAY 319 

    0x086386b9,// 359 PAY 320 

    0xfbedf101,// 360 PAY 321 

    0xad423951,// 361 PAY 322 

    0xb858f229,// 362 PAY 323 

    0x4e1f4400,// 363 PAY 324 

    0x2da8a955,// 364 PAY 325 

    0x81f877a1,// 365 PAY 326 

    0x3cbccedc,// 366 PAY 327 

    0x51f9a3ff,// 367 PAY 328 

    0x783d7f74,// 368 PAY 329 

    0x6c4d2011,// 369 PAY 330 

    0x46696f0a,// 370 PAY 331 

    0xc42713dc,// 371 PAY 332 

    0x447f65d2,// 372 PAY 333 

    0x9eb80b7b,// 373 PAY 334 

    0xfa9f5fc7,// 374 PAY 335 

    0x195e9885,// 375 PAY 336 

    0xc22de9b3,// 376 PAY 337 

    0xb39c6805,// 377 PAY 338 

    0xf38fffbe,// 378 PAY 339 

    0xee53baa2,// 379 PAY 340 

    0x16c3e49e,// 380 PAY 341 

    0x4c31b1e4,// 381 PAY 342 

    0x1647e421,// 382 PAY 343 

    0x5ced6fe4,// 383 PAY 344 

    0xffc8ebe3,// 384 PAY 345 

    0x8200bbc0,// 385 PAY 346 

    0x577aa2bb,// 386 PAY 347 

    0x4a2808cd,// 387 PAY 348 

    0x06afcb35,// 388 PAY 349 

    0x14a0bb5b,// 389 PAY 350 

    0xb3ba0fc9,// 390 PAY 351 

    0xc5e90469,// 391 PAY 352 

    0x77a756e8,// 392 PAY 353 

    0xd48b61b4,// 393 PAY 354 

    0x0829650b,// 394 PAY 355 

    0x011084c1,// 395 PAY 356 

    0x8d73b55d,// 396 PAY 357 

    0xe86c1d0a,// 397 PAY 358 

    0x508f99d2,// 398 PAY 359 

    0xd81c644d,// 399 PAY 360 

    0xa964ab09,// 400 PAY 361 

    0xa6707e79,// 401 PAY 362 

    0x86d139ae,// 402 PAY 363 

    0x98259168,// 403 PAY 364 

    0x34ada48d,// 404 PAY 365 

    0x32d9b605,// 405 PAY 366 

    0x2a686709,// 406 PAY 367 

    0xa7d3608b,// 407 PAY 368 

    0x6ffffbb6,// 408 PAY 369 

    0xf06571bc,// 409 PAY 370 

    0x8d5e357d,// 410 PAY 371 

    0xf0759a57,// 411 PAY 372 

    0xf41d18a2,// 412 PAY 373 

    0x97f3aea4,// 413 PAY 374 

    0x7fabaf00,// 414 PAY 375 

/// STA is 1 words. 

/// STA num_pkts       : 230 

/// STA pkt_idx        : 23 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x5b 

    0x005c5be6 // 415 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 80 (0x50) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt21_tmpl[] = {
    0xb8010050,// 1 CCH   1 

/// ECH cache_idx      : 0x02 

/// ECH pdu_tag        : 0x00 

    0x00020000,// 2 ECH   1 

/// SCX is 19 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x2 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000013,// 3 SCX   1 

    0x80814811,// 4 SCX   2 

    0x00003200,// 5 SCX   3 

    0xc42ead8d,// 6 SCX   4 

    0x110325c5,// 7 SCX   5 

    0xe8486e02,// 8 SCX   6 

    0x43386d37,// 9 SCX   7 

    0x041a0fa7,// 10 SCX   8 

    0x2df25cf6,// 11 SCX   9 

    0x99eb2d26,// 12 SCX  10 

    0x870706bd,// 13 SCX  11 

    0x6d64b319,// 14 SCX  12 

    0xe891e593,// 15 SCX  13 

    0xaf7328eb,// 16 SCX  14 

    0x42702c55,// 17 SCX  15 

    0x4405df01,// 18 SCX  16 

    0x5cbfc1a4,// 19 SCX  17 

    0xc75ca77c,// 20 SCX  18 

    0xa338485e,// 21 SCX  19 

/// BFD is 3 words. 

/// BFD tot_len        : 905 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 863 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 863 

/// BFD lencrypto      : 384 

/// BFD ofstcrypto     : 276 

/// BFD (ofst+len)cry  : 660 

/// BFD ofstiv         : 236 

/// BFD ofsticv        : 864 

    0x0000035f,// 22 BFD   1 

    0x01140180,// 23 BFD   2 

    0x036000ec,// 24 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : c 

    0x0c00d72b,// 25 MFM   1 

    0x80d64bdb,// 26 MFM   2 

/// BDA is 228 words. 

/// BDA size     is 905 (0x389) 

/// BDA id       is 0xb7c2 

    0x0389b7c2,// 27 BDA   1 

/// PAY Generic Data size   : 905 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x0d4f1c68,// 28 PAY   1 

    0x6e60d984,// 29 PAY   2 

    0xdf4139b4,// 30 PAY   3 

    0x215f0c2a,// 31 PAY   4 

    0x3f128837,// 32 PAY   5 

    0xd7bf3830,// 33 PAY   6 

    0x918ac106,// 34 PAY   7 

    0x23e41595,// 35 PAY   8 

    0xd65601fb,// 36 PAY   9 

    0x21c2743c,// 37 PAY  10 

    0x91372caf,// 38 PAY  11 

    0x3d58574f,// 39 PAY  12 

    0xeb6f9d15,// 40 PAY  13 

    0xae5c513f,// 41 PAY  14 

    0x069edebe,// 42 PAY  15 

    0x20601538,// 43 PAY  16 

    0xea7a2f70,// 44 PAY  17 

    0xdd96bf5e,// 45 PAY  18 

    0xf67eb667,// 46 PAY  19 

    0x3c3a1daa,// 47 PAY  20 

    0xaf859d40,// 48 PAY  21 

    0x4f00dd1f,// 49 PAY  22 

    0xd1d0e712,// 50 PAY  23 

    0x4535aea6,// 51 PAY  24 

    0xd49111ce,// 52 PAY  25 

    0x00cfdb89,// 53 PAY  26 

    0x93a27741,// 54 PAY  27 

    0xd82d2464,// 55 PAY  28 

    0xba3b5c1c,// 56 PAY  29 

    0x1b35fcf0,// 57 PAY  30 

    0x3554f991,// 58 PAY  31 

    0x1c337275,// 59 PAY  32 

    0x609b12c4,// 60 PAY  33 

    0x5394dabe,// 61 PAY  34 

    0x5a77bb68,// 62 PAY  35 

    0xe1b125e8,// 63 PAY  36 

    0xca2ff296,// 64 PAY  37 

    0x9c984c61,// 65 PAY  38 

    0x7e896a54,// 66 PAY  39 

    0x53dd02d0,// 67 PAY  40 

    0x7eadb562,// 68 PAY  41 

    0x8fbd92e2,// 69 PAY  42 

    0x334ce669,// 70 PAY  43 

    0xb0f45eb0,// 71 PAY  44 

    0x23ec22ba,// 72 PAY  45 

    0xaac8a4b2,// 73 PAY  46 

    0x4bf1fa9b,// 74 PAY  47 

    0x07bbecb4,// 75 PAY  48 

    0xe71d5e67,// 76 PAY  49 

    0x7f9ae1a8,// 77 PAY  50 

    0xaaf1663d,// 78 PAY  51 

    0x7334742e,// 79 PAY  52 

    0x896a27c5,// 80 PAY  53 

    0x961ff471,// 81 PAY  54 

    0xeb172cb5,// 82 PAY  55 

    0x464e7ab1,// 83 PAY  56 

    0x46254c0b,// 84 PAY  57 

    0xe7167be1,// 85 PAY  58 

    0xca492531,// 86 PAY  59 

    0x09985603,// 87 PAY  60 

    0x7fc0507b,// 88 PAY  61 

    0x0c3de502,// 89 PAY  62 

    0x84fc822c,// 90 PAY  63 

    0xec87d0c0,// 91 PAY  64 

    0xa81cff77,// 92 PAY  65 

    0xbff8fa17,// 93 PAY  66 

    0xc5a9c3f0,// 94 PAY  67 

    0x8efc5f5d,// 95 PAY  68 

    0x630f2c00,// 96 PAY  69 

    0x528fae14,// 97 PAY  70 

    0x4b2717f2,// 98 PAY  71 

    0x4e99364e,// 99 PAY  72 

    0x3bea4b6e,// 100 PAY  73 

    0x0c9e840f,// 101 PAY  74 

    0x0822cae3,// 102 PAY  75 

    0xfc785749,// 103 PAY  76 

    0x1667e318,// 104 PAY  77 

    0xe436a0bd,// 105 PAY  78 

    0x022201cb,// 106 PAY  79 

    0xdc6ccbcb,// 107 PAY  80 

    0x997cecdf,// 108 PAY  81 

    0xec6903d8,// 109 PAY  82 

    0x43fb36e4,// 110 PAY  83 

    0x96a91e85,// 111 PAY  84 

    0x35b8f25e,// 112 PAY  85 

    0x30dd2e89,// 113 PAY  86 

    0x265203f2,// 114 PAY  87 

    0xa2014fa3,// 115 PAY  88 

    0x18dd837d,// 116 PAY  89 

    0xae1bd075,// 117 PAY  90 

    0x20f342ec,// 118 PAY  91 

    0x6e7bc44d,// 119 PAY  92 

    0x65a16c75,// 120 PAY  93 

    0xd023df67,// 121 PAY  94 

    0xc5ed0fa4,// 122 PAY  95 

    0x6ff6e9e5,// 123 PAY  96 

    0xfcb7dcdb,// 124 PAY  97 

    0x6bd67649,// 125 PAY  98 

    0x100ea9e1,// 126 PAY  99 

    0x2c47793d,// 127 PAY 100 

    0x5d1b525f,// 128 PAY 101 

    0x651c001e,// 129 PAY 102 

    0x0dd0d9b6,// 130 PAY 103 

    0x98b4de79,// 131 PAY 104 

    0x4eda3962,// 132 PAY 105 

    0x8fafe3df,// 133 PAY 106 

    0xca998211,// 134 PAY 107 

    0x982aeb46,// 135 PAY 108 

    0x72275590,// 136 PAY 109 

    0xd0a03de0,// 137 PAY 110 

    0x2052d132,// 138 PAY 111 

    0x740ea70b,// 139 PAY 112 

    0xd960b7bc,// 140 PAY 113 

    0x9840a331,// 141 PAY 114 

    0x9f23f940,// 142 PAY 115 

    0xfe52c5e7,// 143 PAY 116 

    0x8a17a30c,// 144 PAY 117 

    0x2c7ee2d4,// 145 PAY 118 

    0x2d938263,// 146 PAY 119 

    0xcdca0076,// 147 PAY 120 

    0x312cba6a,// 148 PAY 121 

    0x83c3b974,// 149 PAY 122 

    0xe715ec9c,// 150 PAY 123 

    0x60214374,// 151 PAY 124 

    0x0366c153,// 152 PAY 125 

    0x6619a083,// 153 PAY 126 

    0xc89db9d2,// 154 PAY 127 

    0x4c25a301,// 155 PAY 128 

    0xd00a13b5,// 156 PAY 129 

    0x718f6d0e,// 157 PAY 130 

    0x74896ad2,// 158 PAY 131 

    0x11c60281,// 159 PAY 132 

    0xc9f8e6b7,// 160 PAY 133 

    0x5d14f484,// 161 PAY 134 

    0x51311475,// 162 PAY 135 

    0xf169b913,// 163 PAY 136 

    0xc3d231d1,// 164 PAY 137 

    0x618fb85f,// 165 PAY 138 

    0x79591c5f,// 166 PAY 139 

    0xdc8a8ecd,// 167 PAY 140 

    0xb24e4a0a,// 168 PAY 141 

    0xf20f0fb7,// 169 PAY 142 

    0x3187f228,// 170 PAY 143 

    0x3c340c1e,// 171 PAY 144 

    0x72ff77ae,// 172 PAY 145 

    0x87518e8a,// 173 PAY 146 

    0xa850db1b,// 174 PAY 147 

    0xc91b5934,// 175 PAY 148 

    0xa7249ac0,// 176 PAY 149 

    0xb30301db,// 177 PAY 150 

    0x3ee39494,// 178 PAY 151 

    0xa33a3609,// 179 PAY 152 

    0xfc671c39,// 180 PAY 153 

    0x7e15e7a5,// 181 PAY 154 

    0x85268f2c,// 182 PAY 155 

    0x1c9b2f1f,// 183 PAY 156 

    0x3c54c0a7,// 184 PAY 157 

    0x6094db7e,// 185 PAY 158 

    0x544aa871,// 186 PAY 159 

    0x63afaa65,// 187 PAY 160 

    0x0cf6fe4f,// 188 PAY 161 

    0xa726433a,// 189 PAY 162 

    0x979c5e62,// 190 PAY 163 

    0xab53d7d2,// 191 PAY 164 

    0x21d8e1f7,// 192 PAY 165 

    0xd0a9f877,// 193 PAY 166 

    0x432a992a,// 194 PAY 167 

    0x9cd6a7dd,// 195 PAY 168 

    0xd5395ff3,// 196 PAY 169 

    0x49141133,// 197 PAY 170 

    0x0bf069a8,// 198 PAY 171 

    0x82fe5860,// 199 PAY 172 

    0x50c3415b,// 200 PAY 173 

    0x31081b9d,// 201 PAY 174 

    0xc60229d0,// 202 PAY 175 

    0xf74657f6,// 203 PAY 176 

    0x897922ef,// 204 PAY 177 

    0x38af1e60,// 205 PAY 178 

    0x6a2593da,// 206 PAY 179 

    0xc17db52a,// 207 PAY 180 

    0x6d1b3364,// 208 PAY 181 

    0x246ac585,// 209 PAY 182 

    0x09b21465,// 210 PAY 183 

    0x4a4e177f,// 211 PAY 184 

    0x8dae3465,// 212 PAY 185 

    0x958ff289,// 213 PAY 186 

    0x547358fe,// 214 PAY 187 

    0x09d8aad5,// 215 PAY 188 

    0x28a25697,// 216 PAY 189 

    0x18ff95e0,// 217 PAY 190 

    0xf9c12193,// 218 PAY 191 

    0xa6513a8c,// 219 PAY 192 

    0x8c215bfb,// 220 PAY 193 

    0xdee9106d,// 221 PAY 194 

    0x5122db8f,// 222 PAY 195 

    0x41a38880,// 223 PAY 196 

    0x96c2c08c,// 224 PAY 197 

    0x9a130361,// 225 PAY 198 

    0x70da903f,// 226 PAY 199 

    0x9f78cf48,// 227 PAY 200 

    0x6865e75a,// 228 PAY 201 

    0xdb27ddc7,// 229 PAY 202 

    0x9cf18611,// 230 PAY 203 

    0xcdfb8bad,// 231 PAY 204 

    0x661dd859,// 232 PAY 205 

    0x36fc3421,// 233 PAY 206 

    0xcaba4698,// 234 PAY 207 

    0x4d4d32f4,// 235 PAY 208 

    0xe58cee2c,// 236 PAY 209 

    0xa1245d21,// 237 PAY 210 

    0x12a6db22,// 238 PAY 211 

    0xd3515355,// 239 PAY 212 

    0xc565a8a6,// 240 PAY 213 

    0x83790d20,// 241 PAY 214 

    0xaa784fbe,// 242 PAY 215 

    0x4e042d6e,// 243 PAY 216 

    0x4c296bfb,// 244 PAY 217 

    0x57d6d66e,// 245 PAY 218 

    0x1e4f9265,// 246 PAY 219 

    0x987f8158,// 247 PAY 220 

    0x1ed46684,// 248 PAY 221 

    0x22aff49e,// 249 PAY 222 

    0xf77b90d7,// 250 PAY 223 

    0x031968d9,// 251 PAY 224 

    0x311edd04,// 252 PAY 225 

    0x2e7a4a40,// 253 PAY 226 

    0x46000000,// 254 PAY 227 

/// STA is 1 words. 

/// STA num_pkts       : 133 

/// STA pkt_idx        : 59 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x14 

    0x00ec1485 // 255 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 72 (0x48) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt22_tmpl[] = {
    0xb8010048,// 1 CCH   1 

/// ECH cache_idx      : 0x05 

/// ECH pdu_tag        : 0x00 

    0x00050000,// 2 ECH   1 

/// SCX is 17 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x00000011,// 3 SCX   1 

    0x808048e0,// 4 SCX   2 

    0x00002100,// 5 SCX   3 

    0x6d5a45ec,// 6 SCX   4 

    0x5fa2a5af,// 7 SCX   5 

    0x314d2249,// 8 SCX   6 

    0xd7876329,// 9 SCX   7 

    0x8fd8d8dc,// 10 SCX   8 

    0x7a5b27f1,// 11 SCX   9 

    0x780c70bf,// 12 SCX  10 

    0xbfd845de,// 13 SCX  11 

    0x8e14724f,// 14 SCX  12 

    0xc48fa869,// 15 SCX  13 

    0x7f777c9d,// 16 SCX  14 

    0x7b953b19,// 17 SCX  15 

    0x90cef32c,// 18 SCX  16 

    0x686bed40,// 19 SCX  17 

/// BFD is 3 words. 

/// BFD tot_len        : 539 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 102 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 102 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 72 

/// BFD (ofst+len)cry  : 88 

/// BFD ofstiv         : 40 

/// BFD ofsticv        : 128 

    0x00000066,// 20 BFD   1 

    0x00480010,// 21 BFD   2 

    0x00800028,// 22 BFD   3 

/// MFM is 3 words. 

/// MFM vldnibs        : 14 

    0x140029c7,// 23 MFM   1 

    0x039ec31f,// 24 MFM   2 

    0x2140663b,// 25 MFM   3 

/// BDA is 136 words. 

/// BDA size     is 539 (0x21b) 

/// BDA id       is 0x393e 

    0x021b393e,// 26 BDA   1 

/// PAY Generic Data size   : 539 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0xcecef410,// 27 PAY   1 

    0x32da1635,// 28 PAY   2 

    0xecf24b88,// 29 PAY   3 

    0x92969d23,// 30 PAY   4 

    0x944f4280,// 31 PAY   5 

    0x5ddd02cb,// 32 PAY   6 

    0xce323b4d,// 33 PAY   7 

    0xe8c5bfe1,// 34 PAY   8 

    0x5359677f,// 35 PAY   9 

    0x53197127,// 36 PAY  10 

    0x2ff888b2,// 37 PAY  11 

    0xd1549f01,// 38 PAY  12 

    0x30bc7bcc,// 39 PAY  13 

    0x7d06ee14,// 40 PAY  14 

    0x34b512cd,// 41 PAY  15 

    0x0abd4975,// 42 PAY  16 

    0xfcc2b9ab,// 43 PAY  17 

    0x15821e90,// 44 PAY  18 

    0xcfe5dd4a,// 45 PAY  19 

    0xa6df7583,// 46 PAY  20 

    0xdcb12dda,// 47 PAY  21 

    0x14a6c5d7,// 48 PAY  22 

    0x45fcd566,// 49 PAY  23 

    0x74c9a789,// 50 PAY  24 

    0xb3a37f4f,// 51 PAY  25 

    0x3d1c9e10,// 52 PAY  26 

    0xbb0d70ac,// 53 PAY  27 

    0x7c148efe,// 54 PAY  28 

    0xf1342ab1,// 55 PAY  29 

    0x9480954e,// 56 PAY  30 

    0xed78ed8a,// 57 PAY  31 

    0x0244a30a,// 58 PAY  32 

    0xcb690389,// 59 PAY  33 

    0xb771f6f0,// 60 PAY  34 

    0xcec2d3ef,// 61 PAY  35 

    0x512ba69f,// 62 PAY  36 

    0x547d0ffd,// 63 PAY  37 

    0x8b4e6d78,// 64 PAY  38 

    0x232610d3,// 65 PAY  39 

    0x4c02601f,// 66 PAY  40 

    0x684ca8fd,// 67 PAY  41 

    0xeba77d82,// 68 PAY  42 

    0xfc7a20d0,// 69 PAY  43 

    0x8fb42925,// 70 PAY  44 

    0x892c6e9e,// 71 PAY  45 

    0x13a4549a,// 72 PAY  46 

    0xb82063c6,// 73 PAY  47 

    0xfec94370,// 74 PAY  48 

    0x7279bf7a,// 75 PAY  49 

    0x3c553069,// 76 PAY  50 

    0x6545dc21,// 77 PAY  51 

    0x5c8161ed,// 78 PAY  52 

    0x64944e06,// 79 PAY  53 

    0x2b470b6d,// 80 PAY  54 

    0x1f5f6577,// 81 PAY  55 

    0x15d3a237,// 82 PAY  56 

    0x3b06b183,// 83 PAY  57 

    0xef533c4e,// 84 PAY  58 

    0x5545be2f,// 85 PAY  59 

    0x2fd7cd0f,// 86 PAY  60 

    0x28ba0ede,// 87 PAY  61 

    0x6b6a10fb,// 88 PAY  62 

    0xddb8c939,// 89 PAY  63 

    0x1b8697d6,// 90 PAY  64 

    0xd358e254,// 91 PAY  65 

    0x49d81dff,// 92 PAY  66 

    0x35dbcef2,// 93 PAY  67 

    0x1b91cb50,// 94 PAY  68 

    0x2799eb09,// 95 PAY  69 

    0xa772d28b,// 96 PAY  70 

    0xdac01b35,// 97 PAY  71 

    0xa9466b5f,// 98 PAY  72 

    0xb8134023,// 99 PAY  73 

    0x3fd369f7,// 100 PAY  74 

    0x188654d8,// 101 PAY  75 

    0xa8bd8fab,// 102 PAY  76 

    0x434e0bb3,// 103 PAY  77 

    0x55bea09d,// 104 PAY  78 

    0xd0bb3045,// 105 PAY  79 

    0x8666489f,// 106 PAY  80 

    0x19c424f6,// 107 PAY  81 

    0x56f0cf3b,// 108 PAY  82 

    0xc4436067,// 109 PAY  83 

    0xa8239ba9,// 110 PAY  84 

    0xa0184fb7,// 111 PAY  85 

    0xc7cafa28,// 112 PAY  86 

    0x06f65146,// 113 PAY  87 

    0x3dbd266a,// 114 PAY  88 

    0x290adad4,// 115 PAY  89 

    0xe60a7086,// 116 PAY  90 

    0x04a388d8,// 117 PAY  91 

    0x4a7f3e5a,// 118 PAY  92 

    0xc9a9235e,// 119 PAY  93 

    0x3d9f6447,// 120 PAY  94 

    0x663fc2f8,// 121 PAY  95 

    0x7018b28e,// 122 PAY  96 

    0x39b24085,// 123 PAY  97 

    0xfe54ab9e,// 124 PAY  98 

    0xc9c1e42f,// 125 PAY  99 

    0xcfa7f5f7,// 126 PAY 100 

    0x8ff4f68a,// 127 PAY 101 

    0x204ff525,// 128 PAY 102 

    0x8b62f307,// 129 PAY 103 

    0x85fcbc59,// 130 PAY 104 

    0xfd919473,// 131 PAY 105 

    0x2e918d23,// 132 PAY 106 

    0x12d4071d,// 133 PAY 107 

    0x254da1f5,// 134 PAY 108 

    0x165fda0f,// 135 PAY 109 

    0xff3d148c,// 136 PAY 110 

    0xa7b7af62,// 137 PAY 111 

    0x43ea359f,// 138 PAY 112 

    0x05e6a710,// 139 PAY 113 

    0x704423a6,// 140 PAY 114 

    0x54b74fe1,// 141 PAY 115 

    0xfa5710f9,// 142 PAY 116 

    0x72285060,// 143 PAY 117 

    0xb8c1f9cd,// 144 PAY 118 

    0x9e16fc11,// 145 PAY 119 

    0x4b164f94,// 146 PAY 120 

    0x247985c7,// 147 PAY 121 

    0x6346be21,// 148 PAY 122 

    0xd25050db,// 149 PAY 123 

    0x7306cf61,// 150 PAY 124 

    0x47098499,// 151 PAY 125 

    0x8627b9e0,// 152 PAY 126 

    0x834bc765,// 153 PAY 127 

    0x09be5a9b,// 154 PAY 128 

    0x0d1c369e,// 155 PAY 129 

    0xaaa4daf6,// 156 PAY 130 

    0x790eac44,// 157 PAY 131 

    0x5c77b6ba,// 158 PAY 132 

    0x6810d392,// 159 PAY 133 

    0x6b07302b,// 160 PAY 134 

    0x3d812900,// 161 PAY 135 

/// STA is 1 words. 

/// STA num_pkts       : 76 

/// STA pkt_idx        : 88 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x80 

    0x0160804c // 162 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt23_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x06 

/// ECH pdu_tag        : 0x00 

    0x00060000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv insert_icv check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000019,// 3 SCX   1 

    0x80924813,// 4 SCX   2 

    0x000074c2,// 5 SCX   3 

    0xfa41ade5,// 6 SCX   4 

    0x3cb26810,// 7 SCX   5 

    0x57040bf5,// 8 SCX   6 

    0xd9d40c3c,// 9 SCX   7 

    0x73f33a3f,// 10 SCX   8 

    0x7a185994,// 11 SCX   9 

    0x5a01e625,// 12 SCX  10 

    0xd74fa3f1,// 13 SCX  11 

    0x164af3ea,// 14 SCX  12 

    0xc5db3cbe,// 15 SCX  13 

    0x3dca1d66,// 16 SCX  14 

    0x79601bd3,// 17 SCX  15 

    0x85cb5a1a,// 18 SCX  16 

    0xe74129d9,// 19 SCX  17 

    0xa8992dff,// 20 SCX  18 

    0x0de7a039,// 21 SCX  19 

    0xd5cc2c6e,// 22 SCX  20 

    0x303ef685,// 23 SCX  21 

    0x4ac1f545,// 24 SCX  22 

    0x5951f79d,// 25 SCX  23 

    0x8ba2475b,// 26 SCX  24 

    0x52189528,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 1057 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 893 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 893 

/// BFD lencrypto      : 24 

/// BFD ofstcrypto     : 852 

/// BFD (ofst+len)cry  : 876 

/// BFD ofstiv         : 464 

/// BFD ofsticv        : 1024 

    0x0000037d,// 28 BFD   1 

    0x03540018,// 29 BFD   2 

    0x040001d0,// 30 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c00d948,// 31 MFM   1 

    0xfe12c277,// 32 MFM   2 

    0x1f6a4164,// 33 MFM   3 

    0x97530d81,// 34 MFM   4 

    0xb34c3f7c,// 35 MFM   5 

    0x9f7036d2,// 36 MFM   6 

    0xc058332e,// 37 MFM   7 

    0xd8e1cc05,// 38 MFM   8 

    0x377e38a9,// 39 MFM   9 

    0xb90dfceb,// 40 MFM  10 

    0x57b3fcdd,// 41 MFM  11 

    0xb7c521be,// 42 MFM  12 

    0x724cc6cb,// 43 MFM  13 

    0x873ee439,// 44 MFM  14 

    0x4d6e3351,// 45 MFM  15 

    0x5c43ff8f,// 46 MFM  16 

/// BDA is 266 words. 

/// BDA size     is 1057 (0x421) 

/// BDA id       is 0x6a15 

    0x04216a15,// 47 BDA   1 

/// PAY Generic Data size   : 1057 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x84ed67f9,// 48 PAY   1 

    0x3e4701f1,// 49 PAY   2 

    0x22b27b78,// 50 PAY   3 

    0xc0986950,// 51 PAY   4 

    0xf19a1fdd,// 52 PAY   5 

    0x3c9ecc6b,// 53 PAY   6 

    0x88c0861c,// 54 PAY   7 

    0xcab41d00,// 55 PAY   8 

    0xb8ce4d53,// 56 PAY   9 

    0x7828474d,// 57 PAY  10 

    0x3dba2055,// 58 PAY  11 

    0xede8d875,// 59 PAY  12 

    0x7278c9b2,// 60 PAY  13 

    0x37658e87,// 61 PAY  14 

    0x0fff4c38,// 62 PAY  15 

    0xec139d72,// 63 PAY  16 

    0xaf98788b,// 64 PAY  17 

    0xfe87e10d,// 65 PAY  18 

    0xf9a8d1cb,// 66 PAY  19 

    0xc666a220,// 67 PAY  20 

    0xa25677a2,// 68 PAY  21 

    0x40ff3646,// 69 PAY  22 

    0xd7cf0d91,// 70 PAY  23 

    0x66707cae,// 71 PAY  24 

    0xa41e8c02,// 72 PAY  25 

    0x53c1bde8,// 73 PAY  26 

    0xeba96ea5,// 74 PAY  27 

    0x42823171,// 75 PAY  28 

    0x9bcd030d,// 76 PAY  29 

    0x0fe795b0,// 77 PAY  30 

    0xc7a60757,// 78 PAY  31 

    0x8966beb8,// 79 PAY  32 

    0xae47bcb5,// 80 PAY  33 

    0xefcaf348,// 81 PAY  34 

    0xc5186eab,// 82 PAY  35 

    0x1f9c912e,// 83 PAY  36 

    0x80662465,// 84 PAY  37 

    0x97cfef24,// 85 PAY  38 

    0x46054baf,// 86 PAY  39 

    0x4282ffce,// 87 PAY  40 

    0xbe5f89a2,// 88 PAY  41 

    0x662a70f0,// 89 PAY  42 

    0x66d9bcd4,// 90 PAY  43 

    0x265695f7,// 91 PAY  44 

    0x6f9d6b51,// 92 PAY  45 

    0xa52f8436,// 93 PAY  46 

    0xf1f7c5c1,// 94 PAY  47 

    0x183a88f3,// 95 PAY  48 

    0x34c06997,// 96 PAY  49 

    0xb0b84473,// 97 PAY  50 

    0x7bba54da,// 98 PAY  51 

    0x407209cd,// 99 PAY  52 

    0xf7522a1d,// 100 PAY  53 

    0xa16dcefe,// 101 PAY  54 

    0x4e103d0e,// 102 PAY  55 

    0xf6ee836d,// 103 PAY  56 

    0x983df713,// 104 PAY  57 

    0x94d6bb97,// 105 PAY  58 

    0x319b3401,// 106 PAY  59 

    0xec652c83,// 107 PAY  60 

    0xf2a3ae86,// 108 PAY  61 

    0xafc0494f,// 109 PAY  62 

    0x58cb4e46,// 110 PAY  63 

    0xae3d2bcb,// 111 PAY  64 

    0x5b61ddfb,// 112 PAY  65 

    0x7e914a87,// 113 PAY  66 

    0x50fc1b09,// 114 PAY  67 

    0x27ab413d,// 115 PAY  68 

    0x05a5692d,// 116 PAY  69 

    0x7c132842,// 117 PAY  70 

    0x1a6103f6,// 118 PAY  71 

    0x081755a0,// 119 PAY  72 

    0x94fac159,// 120 PAY  73 

    0xa35d1f46,// 121 PAY  74 

    0x8196ec7a,// 122 PAY  75 

    0x55d59b42,// 123 PAY  76 

    0x36b34cb9,// 124 PAY  77 

    0x4f0222ae,// 125 PAY  78 

    0xbf68dddb,// 126 PAY  79 

    0xec70957e,// 127 PAY  80 

    0xeb0bcd98,// 128 PAY  81 

    0x0a456b90,// 129 PAY  82 

    0xd376cb42,// 130 PAY  83 

    0x5232ab52,// 131 PAY  84 

    0x3b0438ef,// 132 PAY  85 

    0x2afba6c8,// 133 PAY  86 

    0x97185f8d,// 134 PAY  87 

    0x49c64091,// 135 PAY  88 

    0xaeaf969a,// 136 PAY  89 

    0x6c93094a,// 137 PAY  90 

    0xe59c01fa,// 138 PAY  91 

    0x44b06e06,// 139 PAY  92 

    0x5ef240b4,// 140 PAY  93 

    0xdd190339,// 141 PAY  94 

    0x8b7495ee,// 142 PAY  95 

    0xe99fd93f,// 143 PAY  96 

    0x915444b2,// 144 PAY  97 

    0x81ac3bf5,// 145 PAY  98 

    0x52a68e82,// 146 PAY  99 

    0xe2b91799,// 147 PAY 100 

    0xef5984d9,// 148 PAY 101 

    0xb2b7b33d,// 149 PAY 102 

    0xca790110,// 150 PAY 103 

    0x6e4d6b1c,// 151 PAY 104 

    0x91d8b6d2,// 152 PAY 105 

    0xcb0d05f6,// 153 PAY 106 

    0xa94c3630,// 154 PAY 107 

    0x10113fa2,// 155 PAY 108 

    0x5cd4d1d9,// 156 PAY 109 

    0x995a3832,// 157 PAY 110 

    0x65cfb745,// 158 PAY 111 

    0xcb6abc47,// 159 PAY 112 

    0x81e9c4da,// 160 PAY 113 

    0x061f769c,// 161 PAY 114 

    0x71420422,// 162 PAY 115 

    0xd7627ba5,// 163 PAY 116 

    0xfa5cb902,// 164 PAY 117 

    0x4a7f0b78,// 165 PAY 118 

    0xf4c81fe4,// 166 PAY 119 

    0xaf633b81,// 167 PAY 120 

    0xdbf0f604,// 168 PAY 121 

    0x3690c0b9,// 169 PAY 122 

    0x698d91d3,// 170 PAY 123 

    0xfe479dbc,// 171 PAY 124 

    0xcc99345b,// 172 PAY 125 

    0xc19aefe2,// 173 PAY 126 

    0x55565aac,// 174 PAY 127 

    0x0377a4df,// 175 PAY 128 

    0x94f199a5,// 176 PAY 129 

    0x0150b93b,// 177 PAY 130 

    0x7c4af8d4,// 178 PAY 131 

    0x30c7bed7,// 179 PAY 132 

    0xb2ab5130,// 180 PAY 133 

    0x89caa542,// 181 PAY 134 

    0xa31fda2e,// 182 PAY 135 

    0x6a878502,// 183 PAY 136 

    0x4d406644,// 184 PAY 137 

    0xc0e371a3,// 185 PAY 138 

    0x48b09b32,// 186 PAY 139 

    0x9b00979b,// 187 PAY 140 

    0x37d6b4ec,// 188 PAY 141 

    0x20e9d46a,// 189 PAY 142 

    0x738d1dac,// 190 PAY 143 

    0x504161e7,// 191 PAY 144 

    0xed335f53,// 192 PAY 145 

    0x265b64ae,// 193 PAY 146 

    0x5326d155,// 194 PAY 147 

    0x611060e7,// 195 PAY 148 

    0x4c100fac,// 196 PAY 149 

    0xacdfa7b6,// 197 PAY 150 

    0x1a02140d,// 198 PAY 151 

    0xf53f55ba,// 199 PAY 152 

    0x32ed1b91,// 200 PAY 153 

    0x1dd9d2c7,// 201 PAY 154 

    0xbb7b1279,// 202 PAY 155 

    0x3d360493,// 203 PAY 156 

    0x7993ee94,// 204 PAY 157 

    0x0935d487,// 205 PAY 158 

    0xb034f804,// 206 PAY 159 

    0xc2a2a5fb,// 207 PAY 160 

    0xddc1a177,// 208 PAY 161 

    0xe7eaaeee,// 209 PAY 162 

    0xc320b804,// 210 PAY 163 

    0xc3e27fef,// 211 PAY 164 

    0x10717a2d,// 212 PAY 165 

    0x41e4fc0d,// 213 PAY 166 

    0x21d30afe,// 214 PAY 167 

    0xd52f98d8,// 215 PAY 168 

    0xe13b9fcb,// 216 PAY 169 

    0xb0827ae4,// 217 PAY 170 

    0x168ace24,// 218 PAY 171 

    0x9e5ff0d8,// 219 PAY 172 

    0xf5807435,// 220 PAY 173 

    0x18e9771f,// 221 PAY 174 

    0xff12b1a3,// 222 PAY 175 

    0x6e708cf3,// 223 PAY 176 

    0x9d8a9a84,// 224 PAY 177 

    0x78ede197,// 225 PAY 178 

    0x9b72fd0a,// 226 PAY 179 

    0x721dd733,// 227 PAY 180 

    0x021c823c,// 228 PAY 181 

    0xfbb329cf,// 229 PAY 182 

    0xf339e4b6,// 230 PAY 183 

    0x817c258e,// 231 PAY 184 

    0xc3b40c34,// 232 PAY 185 

    0x18de15a4,// 233 PAY 186 

    0xeb2d85ed,// 234 PAY 187 

    0x4d87da28,// 235 PAY 188 

    0x24a7edb1,// 236 PAY 189 

    0x6750d4c6,// 237 PAY 190 

    0xbf977be8,// 238 PAY 191 

    0xfc17e9af,// 239 PAY 192 

    0x424a7422,// 240 PAY 193 

    0x7c7dc794,// 241 PAY 194 

    0x277dfa3b,// 242 PAY 195 

    0xb3f5c66b,// 243 PAY 196 

    0x78b90cb2,// 244 PAY 197 

    0x15cb5cb5,// 245 PAY 198 

    0x9d70d730,// 246 PAY 199 

    0x31a928d4,// 247 PAY 200 

    0x0085ea5c,// 248 PAY 201 

    0x4fb50de9,// 249 PAY 202 

    0x34483cfa,// 250 PAY 203 

    0x71420851,// 251 PAY 204 

    0x234e6bb0,// 252 PAY 205 

    0x962144fb,// 253 PAY 206 

    0x28edc014,// 254 PAY 207 

    0x056abad7,// 255 PAY 208 

    0xe5007731,// 256 PAY 209 

    0x078a9963,// 257 PAY 210 

    0xe54ab136,// 258 PAY 211 

    0x65dbf0aa,// 259 PAY 212 

    0x34a9ad96,// 260 PAY 213 

    0xa4b91dc0,// 261 PAY 214 

    0xfc9faf60,// 262 PAY 215 

    0x63d66127,// 263 PAY 216 

    0x338544f9,// 264 PAY 217 

    0xbf5f71f6,// 265 PAY 218 

    0x4fabeedd,// 266 PAY 219 

    0x6bf46f6f,// 267 PAY 220 

    0xa126bfef,// 268 PAY 221 

    0xf0a7fe98,// 269 PAY 222 

    0x11a7b63f,// 270 PAY 223 

    0xcb22389f,// 271 PAY 224 

    0xbdaaf5d6,// 272 PAY 225 

    0xe886c30b,// 273 PAY 226 

    0x05a34e5a,// 274 PAY 227 

    0xb0e99f54,// 275 PAY 228 

    0xd24d38fa,// 276 PAY 229 

    0xe6c167cb,// 277 PAY 230 

    0x9d76c78e,// 278 PAY 231 

    0x516988f7,// 279 PAY 232 

    0x4f7ecbcd,// 280 PAY 233 

    0x211be02c,// 281 PAY 234 

    0x5729d757,// 282 PAY 235 

    0x2720d785,// 283 PAY 236 

    0x241e3617,// 284 PAY 237 

    0xf1207f93,// 285 PAY 238 

    0x19910fac,// 286 PAY 239 

    0xf5eb08ec,// 287 PAY 240 

    0x273d39f0,// 288 PAY 241 

    0x574aaed0,// 289 PAY 242 

    0x3c4a3862,// 290 PAY 243 

    0x18fd7da0,// 291 PAY 244 

    0x4401db25,// 292 PAY 245 

    0xb1f1efb6,// 293 PAY 246 

    0x89a9db5e,// 294 PAY 247 

    0x3fb7c15d,// 295 PAY 248 

    0x08c78dd2,// 296 PAY 249 

    0x0ce41ba2,// 297 PAY 250 

    0x1329613b,// 298 PAY 251 

    0x247a3f45,// 299 PAY 252 

    0xb009d7f2,// 300 PAY 253 

    0x056654e4,// 301 PAY 254 

    0xb6ff038e,// 302 PAY 255 

    0xf826f073,// 303 PAY 256 

    0x2fd593be,// 304 PAY 257 

    0x9ad91161,// 305 PAY 258 

    0xb2a8687f,// 306 PAY 259 

    0x032fccd0,// 307 PAY 260 

    0x47089ed6,// 308 PAY 261 

    0x0315f9dd,// 309 PAY 262 

    0xaa4ee854,// 310 PAY 263 

    0x8d3a1d33,// 311 PAY 264 

    0xac000000,// 312 PAY 265 

/// STA is 1 words. 

/// STA num_pkts       : 23 

/// STA pkt_idx        : 246 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xd8 

    0x03d9d817 // 313 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 72 (0x48) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt24_tmpl[] = {
    0xb8010048,// 1 CCH   1 

/// ECH cache_idx      : 0x0f 

/// ECH pdu_tag        : 0x00 

    0x000f0000,// 2 ECH   1 

/// SCX is 17 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv insert_icv check_icv !sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x2 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x00000011,// 3 SCX   1 

    0x8084487f,// 4 SCX   2 

    0x00003244,// 5 SCX   3 

    0xf96ee650,// 6 SCX   4 

    0x17a5bc0c,// 7 SCX   5 

    0x8951a09b,// 8 SCX   6 

    0x5ba07c7d,// 9 SCX   7 

    0x20dfab72,// 10 SCX   8 

    0x9544d9a2,// 11 SCX   9 

    0xc93d4646,// 12 SCX  10 

    0x1a0a9196,// 13 SCX  11 

    0x5bc7b0f9,// 14 SCX  12 

    0x36a76641,// 15 SCX  13 

    0x86e72a84,// 16 SCX  14 

    0xb111dbfa,// 17 SCX  15 

    0x370f8f90,// 18 SCX  16 

    0xa224f9fc,// 19 SCX  17 

/// BFD is 3 words. 

/// BFD tot_len        : 2038 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 651 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 651 

/// BFD lencrypto      : 160 

/// BFD ofstcrypto     : 488 

/// BFD (ofst+len)cry  : 648 

/// BFD ofstiv         : 216 

/// BFD ofsticv        : 692 

    0x0000028b,// 20 BFD   1 

    0x01e800a0,// 21 BFD   2 

    0x02b400d8,// 22 BFD   3 

/// MFM is 11 words. 

/// MFM vldnibs        : 54 

    0x54004d59,// 23 MFM   1 

    0xf5947e22,// 24 MFM   2 

    0x8e4c30e0,// 25 MFM   3 

    0xc3d5b368,// 26 MFM   4 

    0x70e20f03,// 27 MFM   5 

    0xed5c235a,// 28 MFM   6 

    0x1147c8a4,// 29 MFM   7 

    0x779b0e96,// 30 MFM   8 

    0x57cfed4f,// 31 MFM   9 

    0xd1fe0b19,// 32 MFM  10 

    0xb2dfbaf0,// 33 MFM  11 

/// BDA is 511 words. 

/// BDA size     is 2038 (0x7f6) 

/// BDA id       is 0x2a9b 

    0x07f62a9b,// 34 BDA   1 

/// PAY Generic Data size   : 2038 byte(s) 

/// PAD Buffer Data Pad size   : 2 byte(s) 

    0xe9ce01b5,// 35 PAY   1 

    0xb84189e5,// 36 PAY   2 

    0x85391d98,// 37 PAY   3 

    0x6cece17d,// 38 PAY   4 

    0x761939b0,// 39 PAY   5 

    0x40ad74dc,// 40 PAY   6 

    0x2933a88e,// 41 PAY   7 

    0x774deb6d,// 42 PAY   8 

    0x469e8370,// 43 PAY   9 

    0x34ef951d,// 44 PAY  10 

    0xb558b748,// 45 PAY  11 

    0x3f5f046a,// 46 PAY  12 

    0xbba2bb1a,// 47 PAY  13 

    0x4c2001d1,// 48 PAY  14 

    0xdb328285,// 49 PAY  15 

    0xc5d73b1f,// 50 PAY  16 

    0x4cf240fe,// 51 PAY  17 

    0x26b90fa9,// 52 PAY  18 

    0x52113337,// 53 PAY  19 

    0x8c03c598,// 54 PAY  20 

    0x531101c1,// 55 PAY  21 

    0xf2031bc5,// 56 PAY  22 

    0x869a3902,// 57 PAY  23 

    0xe8e1de58,// 58 PAY  24 

    0xe18f674b,// 59 PAY  25 

    0xc1ad7739,// 60 PAY  26 

    0x279812a1,// 61 PAY  27 

    0xba281bd6,// 62 PAY  28 

    0xbfa371c2,// 63 PAY  29 

    0x0d5c1b53,// 64 PAY  30 

    0xa5f5c98f,// 65 PAY  31 

    0x5e47e5a3,// 66 PAY  32 

    0x5761f8be,// 67 PAY  33 

    0x6a5e50bc,// 68 PAY  34 

    0xe4ef8b50,// 69 PAY  35 

    0x9a01d152,// 70 PAY  36 

    0x88a615f1,// 71 PAY  37 

    0xe268227f,// 72 PAY  38 

    0x64394bf4,// 73 PAY  39 

    0x99d194d8,// 74 PAY  40 

    0x058533bc,// 75 PAY  41 

    0x1c4228b3,// 76 PAY  42 

    0xcf098f46,// 77 PAY  43 

    0x5ea49c24,// 78 PAY  44 

    0x33b2283c,// 79 PAY  45 

    0xffbae27a,// 80 PAY  46 

    0xd7884843,// 81 PAY  47 

    0x469a0c97,// 82 PAY  48 

    0xe396a31e,// 83 PAY  49 

    0x494df5a0,// 84 PAY  50 

    0xf7659839,// 85 PAY  51 

    0x1833c568,// 86 PAY  52 

    0x82f93d36,// 87 PAY  53 

    0x1e500d7d,// 88 PAY  54 

    0xa1774794,// 89 PAY  55 

    0x8f1d65df,// 90 PAY  56 

    0x07c590f6,// 91 PAY  57 

    0x9fbc1004,// 92 PAY  58 

    0xc121c18e,// 93 PAY  59 

    0xf45e503c,// 94 PAY  60 

    0x0cd326cf,// 95 PAY  61 

    0x12a3f678,// 96 PAY  62 

    0x906e7296,// 97 PAY  63 

    0x568588b1,// 98 PAY  64 

    0x506016bc,// 99 PAY  65 

    0xab794ef5,// 100 PAY  66 

    0xcc97b91a,// 101 PAY  67 

    0xea3a10b4,// 102 PAY  68 

    0xf4e2dae3,// 103 PAY  69 

    0x16d39aab,// 104 PAY  70 

    0x33497a03,// 105 PAY  71 

    0xf84cdfb4,// 106 PAY  72 

    0xf759353f,// 107 PAY  73 

    0x968d5c3e,// 108 PAY  74 

    0xcf3fae3a,// 109 PAY  75 

    0x35edc071,// 110 PAY  76 

    0x0765cf38,// 111 PAY  77 

    0xc31e3ab5,// 112 PAY  78 

    0xdbc23bf4,// 113 PAY  79 

    0x10423526,// 114 PAY  80 

    0x53b461cd,// 115 PAY  81 

    0xdfe41662,// 116 PAY  82 

    0xa8e2b450,// 117 PAY  83 

    0xef102264,// 118 PAY  84 

    0x1b2247b8,// 119 PAY  85 

    0x94706fe5,// 120 PAY  86 

    0x264f406c,// 121 PAY  87 

    0xb73f9318,// 122 PAY  88 

    0xf16acd04,// 123 PAY  89 

    0x8bff9605,// 124 PAY  90 

    0x93cdf187,// 125 PAY  91 

    0x6408039b,// 126 PAY  92 

    0xfba46069,// 127 PAY  93 

    0x6ffb8c23,// 128 PAY  94 

    0xe2cf1ff5,// 129 PAY  95 

    0xd0e8f5fa,// 130 PAY  96 

    0xef3f52a5,// 131 PAY  97 

    0x010de071,// 132 PAY  98 

    0xb426ac9d,// 133 PAY  99 

    0x773f44ab,// 134 PAY 100 

    0x53eb5b6f,// 135 PAY 101 

    0x10039187,// 136 PAY 102 

    0x99afe9d7,// 137 PAY 103 

    0x83cf8cd1,// 138 PAY 104 

    0x2ff4c20b,// 139 PAY 105 

    0x1b46ce4b,// 140 PAY 106 

    0x55b193ba,// 141 PAY 107 

    0xc5b62717,// 142 PAY 108 

    0xf74749e5,// 143 PAY 109 

    0x63d25e51,// 144 PAY 110 

    0x5cb7916a,// 145 PAY 111 

    0x014b36a6,// 146 PAY 112 

    0xde041fd8,// 147 PAY 113 

    0x6445d734,// 148 PAY 114 

    0x905de24b,// 149 PAY 115 

    0xe87f9af9,// 150 PAY 116 

    0x54bdab44,// 151 PAY 117 

    0xe5ee39e7,// 152 PAY 118 

    0xcf709848,// 153 PAY 119 

    0x4b01555b,// 154 PAY 120 

    0xfac353e3,// 155 PAY 121 

    0xf2d089fa,// 156 PAY 122 

    0x707edd78,// 157 PAY 123 

    0xa8ebbbbe,// 158 PAY 124 

    0x04f582c4,// 159 PAY 125 

    0x4542518a,// 160 PAY 126 

    0x012ac530,// 161 PAY 127 

    0x30381d16,// 162 PAY 128 

    0x65d1bb36,// 163 PAY 129 

    0x91812d47,// 164 PAY 130 

    0x812ef945,// 165 PAY 131 

    0x81599204,// 166 PAY 132 

    0x7bc0d56e,// 167 PAY 133 

    0x5d761354,// 168 PAY 134 

    0x7ecfd23c,// 169 PAY 135 

    0xa1bf6a8a,// 170 PAY 136 

    0x05dd7226,// 171 PAY 137 

    0xf0cea485,// 172 PAY 138 

    0x307bcaa5,// 173 PAY 139 

    0xbd31fcbe,// 174 PAY 140 

    0x4378776c,// 175 PAY 141 

    0xb7429b6a,// 176 PAY 142 

    0x1f3243c1,// 177 PAY 143 

    0x7430bf81,// 178 PAY 144 

    0x1c980c72,// 179 PAY 145 

    0x8e3d21d2,// 180 PAY 146 

    0x567b9108,// 181 PAY 147 

    0xc12165bb,// 182 PAY 148 

    0x598156a8,// 183 PAY 149 

    0x0822d0a1,// 184 PAY 150 

    0x050a24f3,// 185 PAY 151 

    0x6619ea00,// 186 PAY 152 

    0x21ad91b7,// 187 PAY 153 

    0x2d559bfd,// 188 PAY 154 

    0x31d6b3d0,// 189 PAY 155 

    0xfc842b2b,// 190 PAY 156 

    0x8c7b5bb3,// 191 PAY 157 

    0xd161f19c,// 192 PAY 158 

    0xe2ff9f7b,// 193 PAY 159 

    0xa694b4ae,// 194 PAY 160 

    0xca24a574,// 195 PAY 161 

    0x824b2e3d,// 196 PAY 162 

    0x78b4e3f9,// 197 PAY 163 

    0x048d4678,// 198 PAY 164 

    0x9858ae62,// 199 PAY 165 

    0xf628e0c4,// 200 PAY 166 

    0xda653e77,// 201 PAY 167 

    0x7ad419c0,// 202 PAY 168 

    0xf9450080,// 203 PAY 169 

    0xa70f76de,// 204 PAY 170 

    0x0814d024,// 205 PAY 171 

    0x77ce2440,// 206 PAY 172 

    0x4dd80348,// 207 PAY 173 

    0xc1160801,// 208 PAY 174 

    0x1d04d9c2,// 209 PAY 175 

    0x708cd149,// 210 PAY 176 

    0xcd205567,// 211 PAY 177 

    0x9bcf9443,// 212 PAY 178 

    0xb042395b,// 213 PAY 179 

    0xe7b72cff,// 214 PAY 180 

    0x4347b12f,// 215 PAY 181 

    0x44131d62,// 216 PAY 182 

    0x391b023c,// 217 PAY 183 

    0x884b452d,// 218 PAY 184 

    0x0a640e09,// 219 PAY 185 

    0x985f0fbd,// 220 PAY 186 

    0x6c0343dc,// 221 PAY 187 

    0x6a9d170e,// 222 PAY 188 

    0xa0bb88d3,// 223 PAY 189 

    0x566a0bfb,// 224 PAY 190 

    0x1eb398eb,// 225 PAY 191 

    0x758be03f,// 226 PAY 192 

    0xaa3ecec4,// 227 PAY 193 

    0x3488bc9e,// 228 PAY 194 

    0x8de0e85b,// 229 PAY 195 

    0xbfb71c72,// 230 PAY 196 

    0xb4121330,// 231 PAY 197 

    0x40c47c66,// 232 PAY 198 

    0xf6427592,// 233 PAY 199 

    0x8b35b8fa,// 234 PAY 200 

    0x3d426d15,// 235 PAY 201 

    0xc4e46513,// 236 PAY 202 

    0x6da3342e,// 237 PAY 203 

    0x0380c97c,// 238 PAY 204 

    0x56ec9841,// 239 PAY 205 

    0x24357a77,// 240 PAY 206 

    0xc47722ca,// 241 PAY 207 

    0x98f8731d,// 242 PAY 208 

    0x080eb503,// 243 PAY 209 

    0xfd55f456,// 244 PAY 210 

    0x3b6c5a76,// 245 PAY 211 

    0x59c1a2fc,// 246 PAY 212 

    0xa8f90ffd,// 247 PAY 213 

    0xe924390c,// 248 PAY 214 

    0x755edd8d,// 249 PAY 215 

    0x0946f8fd,// 250 PAY 216 

    0xf42586e1,// 251 PAY 217 

    0x276e9621,// 252 PAY 218 

    0xc6e37a62,// 253 PAY 219 

    0xdc66a414,// 254 PAY 220 

    0x0d0e1348,// 255 PAY 221 

    0xe101b6fc,// 256 PAY 222 

    0xe2d0b0fc,// 257 PAY 223 

    0xfc29ef1a,// 258 PAY 224 

    0xa3218286,// 259 PAY 225 

    0xc34c76af,// 260 PAY 226 

    0x81674056,// 261 PAY 227 

    0xf1f83950,// 262 PAY 228 

    0xe8490a03,// 263 PAY 229 

    0xec7f089c,// 264 PAY 230 

    0xaba41b29,// 265 PAY 231 

    0x4921e315,// 266 PAY 232 

    0xa4851790,// 267 PAY 233 

    0x527337cc,// 268 PAY 234 

    0x4da83836,// 269 PAY 235 

    0xf389b714,// 270 PAY 236 

    0x670044e7,// 271 PAY 237 

    0xafc85df1,// 272 PAY 238 

    0x6b6f1566,// 273 PAY 239 

    0xe1560309,// 274 PAY 240 

    0xf79ef567,// 275 PAY 241 

    0xcefddcee,// 276 PAY 242 

    0x7c8c3189,// 277 PAY 243 

    0xfef402fa,// 278 PAY 244 

    0xf92b91a6,// 279 PAY 245 

    0xd60010df,// 280 PAY 246 

    0xed4e230c,// 281 PAY 247 

    0xdee30f98,// 282 PAY 248 

    0x86d49486,// 283 PAY 249 

    0xbdcae232,// 284 PAY 250 

    0xbc77608f,// 285 PAY 251 

    0x58d52ab9,// 286 PAY 252 

    0xd7370ec7,// 287 PAY 253 

    0xcbc5053e,// 288 PAY 254 

    0xe1802f07,// 289 PAY 255 

    0x496bc812,// 290 PAY 256 

    0x148de4dd,// 291 PAY 257 

    0xbf7e795b,// 292 PAY 258 

    0xa4d2753a,// 293 PAY 259 

    0x2ca5c862,// 294 PAY 260 

    0xb71c8fb0,// 295 PAY 261 

    0xf614558a,// 296 PAY 262 

    0xaf9a73c4,// 297 PAY 263 

    0x1ff36370,// 298 PAY 264 

    0xfe7de949,// 299 PAY 265 

    0xef967870,// 300 PAY 266 

    0x5d8293e5,// 301 PAY 267 

    0xdaa4d0ed,// 302 PAY 268 

    0xa3ede4ed,// 303 PAY 269 

    0x34d6ce94,// 304 PAY 270 

    0xc0445f55,// 305 PAY 271 

    0x67db0668,// 306 PAY 272 

    0xf1624832,// 307 PAY 273 

    0x501c5058,// 308 PAY 274 

    0x39c5f79c,// 309 PAY 275 

    0x1109e017,// 310 PAY 276 

    0x5a1ec6ee,// 311 PAY 277 

    0x369d95ad,// 312 PAY 278 

    0x2d49be40,// 313 PAY 279 

    0x5f9c74ed,// 314 PAY 280 

    0xb043c7f2,// 315 PAY 281 

    0x44d85e8f,// 316 PAY 282 

    0x04ff5791,// 317 PAY 283 

    0xdb54db4a,// 318 PAY 284 

    0x84683829,// 319 PAY 285 

    0xc2bf8539,// 320 PAY 286 

    0x76a056e7,// 321 PAY 287 

    0xa46686dc,// 322 PAY 288 

    0x4fdf6530,// 323 PAY 289 

    0x669d73ff,// 324 PAY 290 

    0x6d8611c2,// 325 PAY 291 

    0xe0202df8,// 326 PAY 292 

    0xedb83a2a,// 327 PAY 293 

    0xab2ed3ab,// 328 PAY 294 

    0x356bfc49,// 329 PAY 295 

    0xe3e71992,// 330 PAY 296 

    0xfa4b0aee,// 331 PAY 297 

    0x296b43a0,// 332 PAY 298 

    0x3ed82008,// 333 PAY 299 

    0xad64e42f,// 334 PAY 300 

    0xde826f67,// 335 PAY 301 

    0x89feeb58,// 336 PAY 302 

    0x82ec627a,// 337 PAY 303 

    0x03af211c,// 338 PAY 304 

    0x0d992ce1,// 339 PAY 305 

    0xe3a903f2,// 340 PAY 306 

    0xcd9ce720,// 341 PAY 307 

    0x5e642533,// 342 PAY 308 

    0x6ac930dc,// 343 PAY 309 

    0x372c5833,// 344 PAY 310 

    0xe5f7e2c4,// 345 PAY 311 

    0x78e662f3,// 346 PAY 312 

    0xb20ac4bb,// 347 PAY 313 

    0x28b671d0,// 348 PAY 314 

    0x9764febd,// 349 PAY 315 

    0xab4e3a7e,// 350 PAY 316 

    0xbe2309a4,// 351 PAY 317 

    0x9319950d,// 352 PAY 318 

    0x9067a976,// 353 PAY 319 

    0xe332ed3f,// 354 PAY 320 

    0x00925daa,// 355 PAY 321 

    0x3500e2d8,// 356 PAY 322 

    0x4d4b4bb4,// 357 PAY 323 

    0x7bca1e2e,// 358 PAY 324 

    0xf81317f1,// 359 PAY 325 

    0x228a9dc0,// 360 PAY 326 

    0x2f2e290f,// 361 PAY 327 

    0x0c3f0465,// 362 PAY 328 

    0x9c816185,// 363 PAY 329 

    0x76ef3291,// 364 PAY 330 

    0xcb524dcc,// 365 PAY 331 

    0x58a94e24,// 366 PAY 332 

    0xcbf6cf59,// 367 PAY 333 

    0x2e44ebf8,// 368 PAY 334 

    0x2ed209ea,// 369 PAY 335 

    0x49eb1917,// 370 PAY 336 

    0x7841a5a4,// 371 PAY 337 

    0x5bedfcb2,// 372 PAY 338 

    0x2db7683e,// 373 PAY 339 

    0xf59a2dd8,// 374 PAY 340 

    0xaf37d5a5,// 375 PAY 341 

    0x2d0ce308,// 376 PAY 342 

    0x527a9320,// 377 PAY 343 

    0x73b8c864,// 378 PAY 344 

    0x4f9464e0,// 379 PAY 345 

    0xf27c60ff,// 380 PAY 346 

    0xf7b85b63,// 381 PAY 347 

    0x352dd401,// 382 PAY 348 

    0x614a17b3,// 383 PAY 349 

    0xd4bfdfe5,// 384 PAY 350 

    0x6fc92e8e,// 385 PAY 351 

    0xda538c7d,// 386 PAY 352 

    0x1425cd9e,// 387 PAY 353 

    0x69e8f6cb,// 388 PAY 354 

    0x7bbc0d8e,// 389 PAY 355 

    0x8c378b8b,// 390 PAY 356 

    0x671aa0cb,// 391 PAY 357 

    0x33880aff,// 392 PAY 358 

    0x4327f49d,// 393 PAY 359 

    0x3df71093,// 394 PAY 360 

    0x54f1c138,// 395 PAY 361 

    0x2bf61121,// 396 PAY 362 

    0xdc8b2b6a,// 397 PAY 363 

    0x73bc093e,// 398 PAY 364 

    0xae9d0693,// 399 PAY 365 

    0x16af64c4,// 400 PAY 366 

    0xe18e1af4,// 401 PAY 367 

    0x9aea380b,// 402 PAY 368 

    0x9868d705,// 403 PAY 369 

    0xa9a0d7e3,// 404 PAY 370 

    0xe1fb86d8,// 405 PAY 371 

    0x343454a0,// 406 PAY 372 

    0x00e4363b,// 407 PAY 373 

    0x3bdf14ed,// 408 PAY 374 

    0x05ead44b,// 409 PAY 375 

    0x027c2938,// 410 PAY 376 

    0xee210b2e,// 411 PAY 377 

    0x91cd5ff4,// 412 PAY 378 

    0x3b74e469,// 413 PAY 379 

    0x6d8afd4f,// 414 PAY 380 

    0x4f6e5f43,// 415 PAY 381 

    0x96cbc1ef,// 416 PAY 382 

    0x24f16789,// 417 PAY 383 

    0x91652e65,// 418 PAY 384 

    0xceb360a4,// 419 PAY 385 

    0xa0770ee5,// 420 PAY 386 

    0x0403f0d4,// 421 PAY 387 

    0x558315c4,// 422 PAY 388 

    0x583d3d6e,// 423 PAY 389 

    0xf38285ab,// 424 PAY 390 

    0x2722b3b2,// 425 PAY 391 

    0x9022eaac,// 426 PAY 392 

    0xebedbd1a,// 427 PAY 393 

    0xa7c2c18b,// 428 PAY 394 

    0x4b55ee4c,// 429 PAY 395 

    0xfb872784,// 430 PAY 396 

    0xda03cbe5,// 431 PAY 397 

    0x82856583,// 432 PAY 398 

    0x1a78503b,// 433 PAY 399 

    0x47a2a654,// 434 PAY 400 

    0x766f965f,// 435 PAY 401 

    0xd7898c7e,// 436 PAY 402 

    0xf58e245a,// 437 PAY 403 

    0x2f1ed373,// 438 PAY 404 

    0x86f35c3d,// 439 PAY 405 

    0xfcb22a49,// 440 PAY 406 

    0x86d72692,// 441 PAY 407 

    0xeafc60db,// 442 PAY 408 

    0xafe7f4d6,// 443 PAY 409 

    0x9c806667,// 444 PAY 410 

    0x215cd579,// 445 PAY 411 

    0x8d6f58bc,// 446 PAY 412 

    0x4724512c,// 447 PAY 413 

    0x4a8bd6c8,// 448 PAY 414 

    0xd07247e1,// 449 PAY 415 

    0xd4acf821,// 450 PAY 416 

    0xc3bf11ba,// 451 PAY 417 

    0x6ad629d3,// 452 PAY 418 

    0xbc3d305c,// 453 PAY 419 

    0x98829e69,// 454 PAY 420 

    0xd4762a42,// 455 PAY 421 

    0x2184da8f,// 456 PAY 422 

    0x1a3eb327,// 457 PAY 423 

    0x22c68361,// 458 PAY 424 

    0xf0170121,// 459 PAY 425 

    0x00ba7401,// 460 PAY 426 

    0xf7ebfd3e,// 461 PAY 427 

    0x2f12af7e,// 462 PAY 428 

    0x04882835,// 463 PAY 429 

    0xb7935d08,// 464 PAY 430 

    0xb82bacb4,// 465 PAY 431 

    0x9bb4d163,// 466 PAY 432 

    0x79dfb8fd,// 467 PAY 433 

    0x55d600c9,// 468 PAY 434 

    0xd995cf71,// 469 PAY 435 

    0xd317307c,// 470 PAY 436 

    0x848e1d3b,// 471 PAY 437 

    0x598bc1a5,// 472 PAY 438 

    0x7d737d01,// 473 PAY 439 

    0x302fe7cc,// 474 PAY 440 

    0x121e3b87,// 475 PAY 441 

    0x09184172,// 476 PAY 442 

    0x42d89f5a,// 477 PAY 443 

    0x288f0ca4,// 478 PAY 444 

    0x7fdff556,// 479 PAY 445 

    0x639dbe1b,// 480 PAY 446 

    0x3571583c,// 481 PAY 447 

    0xe07c3a96,// 482 PAY 448 

    0xe297f4b9,// 483 PAY 449 

    0x820cfd3e,// 484 PAY 450 

    0x01059d53,// 485 PAY 451 

    0x361fdc67,// 486 PAY 452 

    0xcb1a5fb0,// 487 PAY 453 

    0x5a5d6709,// 488 PAY 454 

    0x405e9c78,// 489 PAY 455 

    0x1929046b,// 490 PAY 456 

    0x24762d47,// 491 PAY 457 

    0x7ce8c9e9,// 492 PAY 458 

    0xdc6b6ffb,// 493 PAY 459 

    0xe18a6fba,// 494 PAY 460 

    0xad6b8018,// 495 PAY 461 

    0x5b715b71,// 496 PAY 462 

    0x807f3089,// 497 PAY 463 

    0xc42d3ee3,// 498 PAY 464 

    0xfb553a7a,// 499 PAY 465 

    0xca9c59bc,// 500 PAY 466 

    0x13885e0d,// 501 PAY 467 

    0xc7c51533,// 502 PAY 468 

    0x0f15015a,// 503 PAY 469 

    0x8f8dfc0b,// 504 PAY 470 

    0xfa3aed2f,// 505 PAY 471 

    0x3112277d,// 506 PAY 472 

    0x596f70c1,// 507 PAY 473 

    0x10326c58,// 508 PAY 474 

    0x9c933db4,// 509 PAY 475 

    0x1eb0a115,// 510 PAY 476 

    0xa508477a,// 511 PAY 477 

    0x6d776fb9,// 512 PAY 478 

    0x712836c4,// 513 PAY 479 

    0x03ab5d77,// 514 PAY 480 

    0x310bbe49,// 515 PAY 481 

    0x257e3bf8,// 516 PAY 482 

    0x0a5bc5f5,// 517 PAY 483 

    0xa8c9678a,// 518 PAY 484 

    0xfcfd89a4,// 519 PAY 485 

    0x728d0738,// 520 PAY 486 

    0x3d57f376,// 521 PAY 487 

    0x5946c3be,// 522 PAY 488 

    0xb51b4fc9,// 523 PAY 489 

    0x98ac4917,// 524 PAY 490 

    0x2903b967,// 525 PAY 491 

    0xdd3da8a7,// 526 PAY 492 

    0x54296891,// 527 PAY 493 

    0xaff94688,// 528 PAY 494 

    0xb0ae5696,// 529 PAY 495 

    0xddaef993,// 530 PAY 496 

    0x78d248b9,// 531 PAY 497 

    0x1992a810,// 532 PAY 498 

    0xb366b5b4,// 533 PAY 499 

    0x325802e5,// 534 PAY 500 

    0x348fa571,// 535 PAY 501 

    0x0ed7d0b0,// 536 PAY 502 

    0x7ee6244e,// 537 PAY 503 

    0x46caf135,// 538 PAY 504 

    0x452fdbae,// 539 PAY 505 

    0x2bc2dcff,// 540 PAY 506 

    0x4a493acb,// 541 PAY 507 

    0x4678bbf7,// 542 PAY 508 

    0x4e25fd57,// 543 PAY 509 

    0x7b660000,// 544 PAY 510 

/// STA is 1 words. 

/// STA num_pkts       : 151 

/// STA pkt_idx        : 156 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x3c 

    0x02703c97 // 545 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt25_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x07 

/// ECH pdu_tag        : 0x00 

    0x00070000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x80844846,// 4 SCX   2 

    0x000044c4,// 5 SCX   3 

    0xb14f48ac,// 6 SCX   4 

    0x16453001,// 7 SCX   5 

    0x04e83d2d,// 8 SCX   6 

    0x60a4c345,// 9 SCX   7 

    0x755211c8,// 10 SCX   8 

    0xd42ec6cb,// 11 SCX   9 

    0xbed1b9d1,// 12 SCX  10 

    0x668e2582,// 13 SCX  11 

    0x4765a242,// 14 SCX  12 

    0xca4286f0,// 15 SCX  13 

    0x228d46a0,// 16 SCX  14 

    0x004c4f7b,// 17 SCX  15 

    0x97ced582,// 18 SCX  16 

    0xf030b8a7,// 19 SCX  17 

    0x1d36eedd,// 20 SCX  18 

    0xbf715ef8,// 21 SCX  19 

    0xc397a0c3,// 22 SCX  20 

    0x18281ce8,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 453 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 280 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 280 

/// BFD lencrypto      : 176 

/// BFD ofstcrypto     : 40 

/// BFD (ofst+len)cry  : 216 

/// BFD ofstiv         : 20 

/// BFD ofsticv        : 332 

    0x00000118,// 24 BFD   1 

    0x002800b0,// 25 BFD   2 

    0x014c0014,// 26 BFD   3 

/// MFM is 8 words. 

/// MFM vldnibs        : 35 

    0x3500343e,// 27 MFM   1 

    0x15f96a9b,// 28 MFM   2 

    0x1b728884,// 29 MFM   3 

    0x4bdff446,// 30 MFM   4 

    0x71082249,// 31 MFM   5 

    0xae728ca4,// 32 MFM   6 

    0xd89c1af0,// 33 MFM   7 

    0x30000000,// 34 MFM   8 

/// BDA is 115 words. 

/// BDA size     is 453 (0x1c5) 

/// BDA id       is 0xdca0 

    0x01c5dca0,// 35 BDA   1 

/// PAY Generic Data size   : 453 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x5d405d3f,// 36 PAY   1 

    0xf47d5bb9,// 37 PAY   2 

    0x3152ef9a,// 38 PAY   3 

    0x768181b4,// 39 PAY   4 

    0x0bff2877,// 40 PAY   5 

    0x03478903,// 41 PAY   6 

    0xc75d15cf,// 42 PAY   7 

    0x24bad10c,// 43 PAY   8 

    0xd5d0ab45,// 44 PAY   9 

    0xb8ab37ff,// 45 PAY  10 

    0xc862bfdc,// 46 PAY  11 

    0xec06937c,// 47 PAY  12 

    0xb1f5a430,// 48 PAY  13 

    0xcd58a3c6,// 49 PAY  14 

    0x9ff08281,// 50 PAY  15 

    0x7c242eb9,// 51 PAY  16 

    0xa70c6232,// 52 PAY  17 

    0x86bb0c52,// 53 PAY  18 

    0xa3b3af33,// 54 PAY  19 

    0x8d14093c,// 55 PAY  20 

    0x198d5faf,// 56 PAY  21 

    0xe6472e2f,// 57 PAY  22 

    0xa297a410,// 58 PAY  23 

    0xc8be8c34,// 59 PAY  24 

    0x64125a3e,// 60 PAY  25 

    0x498e67ce,// 61 PAY  26 

    0xac152c89,// 62 PAY  27 

    0x2b1a9cbb,// 63 PAY  28 

    0xc626cc28,// 64 PAY  29 

    0xcca8e031,// 65 PAY  30 

    0xabe82cb9,// 66 PAY  31 

    0xdc4cb8ab,// 67 PAY  32 

    0x35809d72,// 68 PAY  33 

    0x8fdcae88,// 69 PAY  34 

    0x0b4d2ecd,// 70 PAY  35 

    0x9ccb2cd6,// 71 PAY  36 

    0x4e59f13f,// 72 PAY  37 

    0x4351cb03,// 73 PAY  38 

    0xaf1fc223,// 74 PAY  39 

    0x7ed3c1c7,// 75 PAY  40 

    0xa94345cb,// 76 PAY  41 

    0xb1db52d5,// 77 PAY  42 

    0x6050b997,// 78 PAY  43 

    0x3b5f3bb4,// 79 PAY  44 

    0xe6f8f3cb,// 80 PAY  45 

    0xf0875474,// 81 PAY  46 

    0xdeb3d832,// 82 PAY  47 

    0xc2b78962,// 83 PAY  48 

    0xd6dd5e13,// 84 PAY  49 

    0x37e951cf,// 85 PAY  50 

    0x4f64ea33,// 86 PAY  51 

    0xdef4954b,// 87 PAY  52 

    0x6891cd48,// 88 PAY  53 

    0x8e434b21,// 89 PAY  54 

    0x2081fe67,// 90 PAY  55 

    0xeac125a5,// 91 PAY  56 

    0xd102170a,// 92 PAY  57 

    0x79563095,// 93 PAY  58 

    0x7cd41db1,// 94 PAY  59 

    0x1f62e5e3,// 95 PAY  60 

    0xd272644d,// 96 PAY  61 

    0x3232000d,// 97 PAY  62 

    0xbd30db2b,// 98 PAY  63 

    0x89dbb70e,// 99 PAY  64 

    0x8950aa89,// 100 PAY  65 

    0xd564a8c9,// 101 PAY  66 

    0x3c01cc3b,// 102 PAY  67 

    0x5f271e3a,// 103 PAY  68 

    0x6a11cca9,// 104 PAY  69 

    0x2cd1fddc,// 105 PAY  70 

    0x2326774f,// 106 PAY  71 

    0x940b6a2a,// 107 PAY  72 

    0xbd848ee6,// 108 PAY  73 

    0x53f38aca,// 109 PAY  74 

    0x30e849ef,// 110 PAY  75 

    0x2541a435,// 111 PAY  76 

    0xd3b16b02,// 112 PAY  77 

    0xe66a512d,// 113 PAY  78 

    0x1150280a,// 114 PAY  79 

    0xb24a8bd0,// 115 PAY  80 

    0x552c9cea,// 116 PAY  81 

    0x0c15b879,// 117 PAY  82 

    0x744112bb,// 118 PAY  83 

    0xdc2a9f03,// 119 PAY  84 

    0x5703ed5e,// 120 PAY  85 

    0xbd7c9e6b,// 121 PAY  86 

    0x16bdc59a,// 122 PAY  87 

    0x89f7e2b8,// 123 PAY  88 

    0x14edc88d,// 124 PAY  89 

    0x4786ec3f,// 125 PAY  90 

    0xd2d8bb14,// 126 PAY  91 

    0xda1c82bc,// 127 PAY  92 

    0x3d16deb6,// 128 PAY  93 

    0xd177ae74,// 129 PAY  94 

    0x47db56c5,// 130 PAY  95 

    0x0ee470bc,// 131 PAY  96 

    0x4cf9a364,// 132 PAY  97 

    0xa8e39c34,// 133 PAY  98 

    0xea33485f,// 134 PAY  99 

    0x7ecd35b6,// 135 PAY 100 

    0xa6aaf191,// 136 PAY 101 

    0x05c6fba1,// 137 PAY 102 

    0x57bb6ce0,// 138 PAY 103 

    0x9a33be40,// 139 PAY 104 

    0xdd219c97,// 140 PAY 105 

    0x236308d8,// 141 PAY 106 

    0x09e5854b,// 142 PAY 107 

    0x81f895c4,// 143 PAY 108 

    0x46cf58c2,// 144 PAY 109 

    0x31a8440e,// 145 PAY 110 

    0x467be644,// 146 PAY 111 

    0xe0c4e5f9,// 147 PAY 112 

    0x725de6cd,// 148 PAY 113 

    0x57000000,// 149 PAY 114 

/// STA is 1 words. 

/// STA num_pkts       : 145 

/// STA pkt_idx        : 230 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x4d 

    0x03994d91 // 150 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 80 (0x50) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt26_tmpl[] = {
    0xb8010050,// 1 CCH   1 

/// ECH cache_idx      : 0x00 

/// ECH pdu_tag        : 0x00 

    0x00000000,// 2 ECH   1 

/// SCX is 19 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv !insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000013,// 3 SCX   1 

    0x8081480c,// 4 SCX   2 

    0x00001500,// 5 SCX   3 

    0x07c4248e,// 6 SCX   4 

    0xabacf235,// 7 SCX   5 

    0xf37f50c0,// 8 SCX   6 

    0xb3d5e538,// 9 SCX   7 

    0xbd79e6a2,// 10 SCX   8 

    0x5f8216ec,// 11 SCX   9 

    0x9804c1dc,// 12 SCX  10 

    0xeeb8b8fc,// 13 SCX  11 

    0x389fa894,// 14 SCX  12 

    0xcac2e3a6,// 15 SCX  13 

    0x31eeaafa,// 16 SCX  14 

    0x97f7fc5d,// 17 SCX  15 

    0x1fa381f8,// 18 SCX  16 

    0xef3ae0c4,// 19 SCX  17 

    0x6eb3f88a,// 20 SCX  18 

    0xbd0e2b6c,// 21 SCX  19 

/// BFD is 3 words. 

/// BFD tot_len        : 134 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 82 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 82 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 24 

/// BFD (ofst+len)cry  : 40 

/// BFD ofstiv         : 8 

/// BFD ofsticv        : 100 

    0x00000052,// 22 BFD   1 

    0x00180010,// 23 BFD   2 

    0x00640008,// 24 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : b 

    0x0b00a124,// 25 MFM   1 

    0x5f480330,// 26 MFM   2 

/// BDA is 35 words. 

/// BDA size     is 134 (0x86) 

/// BDA id       is 0x9ed4 

    0x00869ed4,// 27 BDA   1 

/// PAY Generic Data size   : 134 byte(s) 

/// PAD Buffer Data Pad size   : 2 byte(s) 

    0x680450c7,// 28 PAY   1 

    0x27eddf55,// 29 PAY   2 

    0xedc35bc2,// 30 PAY   3 

    0x2aa246a7,// 31 PAY   4 

    0xc7b89fc7,// 32 PAY   5 

    0x50e0afac,// 33 PAY   6 

    0xec50f585,// 34 PAY   7 

    0xb1e0b75c,// 35 PAY   8 

    0x4b6e5217,// 36 PAY   9 

    0x2d3f7bbd,// 37 PAY  10 

    0x8892f878,// 38 PAY  11 

    0xd851777b,// 39 PAY  12 

    0x08084719,// 40 PAY  13 

    0x896e5bda,// 41 PAY  14 

    0x652b30fd,// 42 PAY  15 

    0x72cbfc03,// 43 PAY  16 

    0x431cde6e,// 44 PAY  17 

    0xafe33b91,// 45 PAY  18 

    0x4c6ca3ff,// 46 PAY  19 

    0xe7c3fa74,// 47 PAY  20 

    0xbf169a28,// 48 PAY  21 

    0xd113d8f7,// 49 PAY  22 

    0x24094e70,// 50 PAY  23 

    0x1c1b895a,// 51 PAY  24 

    0x330fca13,// 52 PAY  25 

    0xb7aeead7,// 53 PAY  26 

    0x7a554816,// 54 PAY  27 

    0x9a909003,// 55 PAY  28 

    0x0107de09,// 56 PAY  29 

    0xa6997ca0,// 57 PAY  30 

    0x7a1342b5,// 58 PAY  31 

    0x50c81312,// 59 PAY  32 

    0x76f6915c,// 60 PAY  33 

    0x70000000,// 61 PAY  34 

/// STA is 1 words. 

/// STA num_pkts       : 14 

/// STA pkt_idx        : 249 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xc8 

    0x03e4c80e // 62 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 96 (0x60) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt27_tmpl[] = {
    0xb8010060,// 1 CCH   1 

/// ECH cache_idx      : 0x06 

/// ECH pdu_tag        : 0x00 

    0x00060000,// 2 ECH   1 

/// SCX is 23 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000017,// 3 SCX   1 

    0x809148b1,// 4 SCX   2 

    0x00003482,// 5 SCX   3 

    0x864581f7,// 6 SCX   4 

    0x4f04043e,// 7 SCX   5 

    0xc0667ed4,// 8 SCX   6 

    0x68d66dea,// 9 SCX   7 

    0x048b29d5,// 10 SCX   8 

    0xa588b8a2,// 11 SCX   9 

    0xd318be3b,// 12 SCX  10 

    0xa8139da5,// 13 SCX  11 

    0x39f4431d,// 14 SCX  12 

    0x3663c1bd,// 15 SCX  13 

    0x3bc823b4,// 16 SCX  14 

    0xb0298441,// 17 SCX  15 

    0xdc61a33f,// 18 SCX  16 

    0xc97cb18f,// 19 SCX  17 

    0xaf970922,// 20 SCX  18 

    0x1bc6e180,// 21 SCX  19 

    0xb4d70f48,// 22 SCX  20 

    0xfa3a572b,// 23 SCX  21 

    0x70791114,// 24 SCX  22 

    0xbfa91e77,// 25 SCX  23 

/// BFD is 3 words. 

/// BFD tot_len        : 1787 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 1480 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1480 

/// BFD lencrypto      : 124 

/// BFD ofstcrypto     : 1336 

/// BFD (ofst+len)cry  : 1460 

/// BFD ofstiv         : 408 

/// BFD ofsticv        : 1712 

    0x000005c8,// 26 BFD   1 

    0x0538007c,// 27 BFD   2 

    0x06b00198,// 28 BFD   3 

/// MFM is 4 words. 

/// MFM vldnibs        : 18 

    0x1800ee1b,// 29 MFM   1 

    0xd5c4c8fc,// 30 MFM   2 

    0x6ad9aa03,// 31 MFM   3 

    0xe31f0000,// 32 MFM   4 

/// BDA is 448 words. 

/// BDA size     is 1787 (0x6fb) 

/// BDA id       is 0x601b 

    0x06fb601b,// 33 BDA   1 

/// PAY Generic Data size   : 1787 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0x71609395,// 34 PAY   1 

    0x6c64867b,// 35 PAY   2 

    0x5bb6228d,// 36 PAY   3 

    0xc8c86762,// 37 PAY   4 

    0x2ca14855,// 38 PAY   5 

    0x7a722ff4,// 39 PAY   6 

    0xad73e42f,// 40 PAY   7 

    0xbcc47455,// 41 PAY   8 

    0xcdf18a40,// 42 PAY   9 

    0xd3f62183,// 43 PAY  10 

    0x92775984,// 44 PAY  11 

    0xe34236bb,// 45 PAY  12 

    0xb44a5934,// 46 PAY  13 

    0x71173019,// 47 PAY  14 

    0x84e46f87,// 48 PAY  15 

    0x5000fe1f,// 49 PAY  16 

    0x794ba69d,// 50 PAY  17 

    0x9d8b4f8f,// 51 PAY  18 

    0x5b108b2e,// 52 PAY  19 

    0x186ae61f,// 53 PAY  20 

    0x12a9c891,// 54 PAY  21 

    0xa3304bf1,// 55 PAY  22 

    0xb890593b,// 56 PAY  23 

    0x4576f216,// 57 PAY  24 

    0xc60bb5d7,// 58 PAY  25 

    0xd9db3d56,// 59 PAY  26 

    0xcf73be06,// 60 PAY  27 

    0x0561875d,// 61 PAY  28 

    0x37b2baaa,// 62 PAY  29 

    0x2093dac6,// 63 PAY  30 

    0x1be8651f,// 64 PAY  31 

    0xfc1ffd3c,// 65 PAY  32 

    0x5b34902d,// 66 PAY  33 

    0xd27c4575,// 67 PAY  34 

    0xa5a69a35,// 68 PAY  35 

    0x48a09f4d,// 69 PAY  36 

    0x6e6f1b1b,// 70 PAY  37 

    0xb5bfacbe,// 71 PAY  38 

    0xafa63d08,// 72 PAY  39 

    0xbeddd132,// 73 PAY  40 

    0x9c5a6580,// 74 PAY  41 

    0x2473f568,// 75 PAY  42 

    0x490a6dcf,// 76 PAY  43 

    0xd04eac19,// 77 PAY  44 

    0xb859904f,// 78 PAY  45 

    0x6d808980,// 79 PAY  46 

    0xe288deda,// 80 PAY  47 

    0x0b3f9da0,// 81 PAY  48 

    0x8166e540,// 82 PAY  49 

    0xce50acb0,// 83 PAY  50 

    0xc98a92fc,// 84 PAY  51 

    0x86fe576c,// 85 PAY  52 

    0x5ae172ca,// 86 PAY  53 

    0x639282a2,// 87 PAY  54 

    0xbdd61997,// 88 PAY  55 

    0x87d9493d,// 89 PAY  56 

    0xedde6002,// 90 PAY  57 

    0xda19474c,// 91 PAY  58 

    0xf468656b,// 92 PAY  59 

    0xc8c807bb,// 93 PAY  60 

    0xf4dedd31,// 94 PAY  61 

    0x0463914b,// 95 PAY  62 

    0x48e8d065,// 96 PAY  63 

    0x88828adc,// 97 PAY  64 

    0x565a1592,// 98 PAY  65 

    0x990dc53c,// 99 PAY  66 

    0xb3f40b41,// 100 PAY  67 

    0xf66e05e7,// 101 PAY  68 

    0x171cc561,// 102 PAY  69 

    0x9a9d5778,// 103 PAY  70 

    0xfbe60dec,// 104 PAY  71 

    0xc5d524d4,// 105 PAY  72 

    0xf15497df,// 106 PAY  73 

    0x5f980a1c,// 107 PAY  74 

    0x3096b2ab,// 108 PAY  75 

    0x531fbcdf,// 109 PAY  76 

    0x44cf542f,// 110 PAY  77 

    0x388f4d04,// 111 PAY  78 

    0x1037a2a3,// 112 PAY  79 

    0x466ba3c2,// 113 PAY  80 

    0xef23b37e,// 114 PAY  81 

    0xf63f4fca,// 115 PAY  82 

    0x7635a31c,// 116 PAY  83 

    0x2a59b677,// 117 PAY  84 

    0x4f573ebe,// 118 PAY  85 

    0x6dd4a533,// 119 PAY  86 

    0x68d5ecd2,// 120 PAY  87 

    0x830ea1d3,// 121 PAY  88 

    0x8c7df4b1,// 122 PAY  89 

    0x63e1c45d,// 123 PAY  90 

    0xcfe70ac6,// 124 PAY  91 

    0xe791839d,// 125 PAY  92 

    0x075f81d2,// 126 PAY  93 

    0xa1783e7f,// 127 PAY  94 

    0x316c658c,// 128 PAY  95 

    0x0ec406c6,// 129 PAY  96 

    0xcd1a91b4,// 130 PAY  97 

    0x7f6b78b8,// 131 PAY  98 

    0xebf3d7aa,// 132 PAY  99 

    0x7686f91c,// 133 PAY 100 

    0xb518e789,// 134 PAY 101 

    0x455af88a,// 135 PAY 102 

    0xa746d672,// 136 PAY 103 

    0x5d680e97,// 137 PAY 104 

    0x8116d227,// 138 PAY 105 

    0x7f33ce8a,// 139 PAY 106 

    0xb423682f,// 140 PAY 107 

    0x7b3014de,// 141 PAY 108 

    0x08fc9f24,// 142 PAY 109 

    0x4cd3b535,// 143 PAY 110 

    0x4c4f127a,// 144 PAY 111 

    0x5aff0f2e,// 145 PAY 112 

    0xb3b45eac,// 146 PAY 113 

    0x89c311ee,// 147 PAY 114 

    0x2607ec4d,// 148 PAY 115 

    0x17101c40,// 149 PAY 116 

    0xcab3b6b9,// 150 PAY 117 

    0x1cdb5a98,// 151 PAY 118 

    0xe7d4e5c6,// 152 PAY 119 

    0x2fe91b55,// 153 PAY 120 

    0x91d25bdf,// 154 PAY 121 

    0xf0564ce9,// 155 PAY 122 

    0x660d0e82,// 156 PAY 123 

    0x381b3ac0,// 157 PAY 124 

    0xcf023707,// 158 PAY 125 

    0xec3a7444,// 159 PAY 126 

    0x5feb55e2,// 160 PAY 127 

    0xa0eb1ddb,// 161 PAY 128 

    0xd3ccf203,// 162 PAY 129 

    0x7385ed93,// 163 PAY 130 

    0x4ee0dc69,// 164 PAY 131 

    0x91a2ca00,// 165 PAY 132 

    0x6cc4e883,// 166 PAY 133 

    0x2d4fa6f4,// 167 PAY 134 

    0x748cea69,// 168 PAY 135 

    0xd6dc2b65,// 169 PAY 136 

    0x3b48624b,// 170 PAY 137 

    0xf70f13c9,// 171 PAY 138 

    0x24dbdbdc,// 172 PAY 139 

    0x0c25e62a,// 173 PAY 140 

    0x55cbcc03,// 174 PAY 141 

    0xa7b78e50,// 175 PAY 142 

    0xe9d0be1a,// 176 PAY 143 

    0x0279911d,// 177 PAY 144 

    0x917b5fcf,// 178 PAY 145 

    0x3f741cc1,// 179 PAY 146 

    0xfc9fc50e,// 180 PAY 147 

    0xafe0b03a,// 181 PAY 148 

    0x9c11f81e,// 182 PAY 149 

    0x4170b3da,// 183 PAY 150 

    0x49db9a28,// 184 PAY 151 

    0xce0f61c6,// 185 PAY 152 

    0x8353d0b8,// 186 PAY 153 

    0x5f6b87fb,// 187 PAY 154 

    0x554511fc,// 188 PAY 155 

    0xf932d764,// 189 PAY 156 

    0x9fe8f614,// 190 PAY 157 

    0x0aa172cb,// 191 PAY 158 

    0xb926dad9,// 192 PAY 159 

    0x7a1927ca,// 193 PAY 160 

    0x305cd413,// 194 PAY 161 

    0xece9213b,// 195 PAY 162 

    0xa55c2af6,// 196 PAY 163 

    0xb27d73dc,// 197 PAY 164 

    0x82a765d1,// 198 PAY 165 

    0x300ed7bc,// 199 PAY 166 

    0xc133e1c1,// 200 PAY 167 

    0xc7a7e415,// 201 PAY 168 

    0x480f0080,// 202 PAY 169 

    0xba7dc32e,// 203 PAY 170 

    0xe4358d2a,// 204 PAY 171 

    0xcb395692,// 205 PAY 172 

    0xb5d98273,// 206 PAY 173 

    0x505a0aa4,// 207 PAY 174 

    0xbf838732,// 208 PAY 175 

    0x64f7eb1e,// 209 PAY 176 

    0xecf2cdb2,// 210 PAY 177 

    0x3c37c299,// 211 PAY 178 

    0x2c035203,// 212 PAY 179 

    0x7d2825a0,// 213 PAY 180 

    0x7776a028,// 214 PAY 181 

    0xd1551f82,// 215 PAY 182 

    0x399d982f,// 216 PAY 183 

    0x342aba99,// 217 PAY 184 

    0x2a9e051c,// 218 PAY 185 

    0xfec0c878,// 219 PAY 186 

    0x113b4972,// 220 PAY 187 

    0x7d3be178,// 221 PAY 188 

    0x5fa472e9,// 222 PAY 189 

    0x3368bb7f,// 223 PAY 190 

    0xa5f03f21,// 224 PAY 191 

    0xce41a9a3,// 225 PAY 192 

    0xdcab506e,// 226 PAY 193 

    0xb64aa7aa,// 227 PAY 194 

    0x0dd8eab5,// 228 PAY 195 

    0x94bc9160,// 229 PAY 196 

    0xf567fa8f,// 230 PAY 197 

    0xace61eea,// 231 PAY 198 

    0x097b7bbc,// 232 PAY 199 

    0x1573d64f,// 233 PAY 200 

    0x9a75191b,// 234 PAY 201 

    0xb291fd0b,// 235 PAY 202 

    0xfb7b17f5,// 236 PAY 203 

    0x56c9c770,// 237 PAY 204 

    0x13bdb6ff,// 238 PAY 205 

    0xa46ccc58,// 239 PAY 206 

    0x89d232d7,// 240 PAY 207 

    0xec71dc7b,// 241 PAY 208 

    0x166f979e,// 242 PAY 209 

    0xb0ea6910,// 243 PAY 210 

    0xdb74d2f3,// 244 PAY 211 

    0xe2ed53b1,// 245 PAY 212 

    0x464ea985,// 246 PAY 213 

    0x6a6ff746,// 247 PAY 214 

    0xf7433900,// 248 PAY 215 

    0x880c1141,// 249 PAY 216 

    0x5935c0f7,// 250 PAY 217 

    0x46df027b,// 251 PAY 218 

    0xc149cc82,// 252 PAY 219 

    0xef7878b7,// 253 PAY 220 

    0x1084c283,// 254 PAY 221 

    0xfb8d15b7,// 255 PAY 222 

    0x77aaa02d,// 256 PAY 223 

    0x9b64d34f,// 257 PAY 224 

    0xb155a21d,// 258 PAY 225 

    0x4b159ac9,// 259 PAY 226 

    0x983fa0b3,// 260 PAY 227 

    0x08e5e5d1,// 261 PAY 228 

    0xe804c210,// 262 PAY 229 

    0xeb770aea,// 263 PAY 230 

    0xb3516f8d,// 264 PAY 231 

    0x9a6c4ad3,// 265 PAY 232 

    0x0fcf2805,// 266 PAY 233 

    0xd07c0319,// 267 PAY 234 

    0xe8cb1e5a,// 268 PAY 235 

    0x98226876,// 269 PAY 236 

    0x8391858b,// 270 PAY 237 

    0xc038037e,// 271 PAY 238 

    0x8cfe5e44,// 272 PAY 239 

    0x2c288d08,// 273 PAY 240 

    0x883389a7,// 274 PAY 241 

    0x1993ca98,// 275 PAY 242 

    0xaa00f6d5,// 276 PAY 243 

    0xab84e5b4,// 277 PAY 244 

    0x7e12a846,// 278 PAY 245 

    0x74a7a5f5,// 279 PAY 246 

    0xafe8b346,// 280 PAY 247 

    0x46cbb766,// 281 PAY 248 

    0x2c7eaa3c,// 282 PAY 249 

    0x5e347f6b,// 283 PAY 250 

    0x4b40daec,// 284 PAY 251 

    0x2fd36456,// 285 PAY 252 

    0xa1988198,// 286 PAY 253 

    0x852b443b,// 287 PAY 254 

    0x5b3f38b3,// 288 PAY 255 

    0x7d67a0f6,// 289 PAY 256 

    0xb846a376,// 290 PAY 257 

    0xcf1ac5dd,// 291 PAY 258 

    0x71fa9dae,// 292 PAY 259 

    0xe8d28bb3,// 293 PAY 260 

    0x709bf0da,// 294 PAY 261 

    0x03d5ef13,// 295 PAY 262 

    0x8c404311,// 296 PAY 263 

    0xb42ecf81,// 297 PAY 264 

    0x3c618323,// 298 PAY 265 

    0x13e963af,// 299 PAY 266 

    0xab6df4c7,// 300 PAY 267 

    0xf629c486,// 301 PAY 268 

    0x2d82a7b3,// 302 PAY 269 

    0xa0b40480,// 303 PAY 270 

    0x17e09914,// 304 PAY 271 

    0xfc4c1999,// 305 PAY 272 

    0xd7267b3e,// 306 PAY 273 

    0x943278cc,// 307 PAY 274 

    0xf98f5281,// 308 PAY 275 

    0xb683e5e0,// 309 PAY 276 

    0x18f096ea,// 310 PAY 277 

    0x5ef9c65e,// 311 PAY 278 

    0xdbf04b17,// 312 PAY 279 

    0x321e456a,// 313 PAY 280 

    0x680feb82,// 314 PAY 281 

    0xe43ea188,// 315 PAY 282 

    0x67250d63,// 316 PAY 283 

    0xdaf6876b,// 317 PAY 284 

    0xcee624bc,// 318 PAY 285 

    0x23d3f7b0,// 319 PAY 286 

    0x59b434c2,// 320 PAY 287 

    0x41c73cbd,// 321 PAY 288 

    0xf39f1b46,// 322 PAY 289 

    0x098b7647,// 323 PAY 290 

    0x26bfbd12,// 324 PAY 291 

    0x9e654f45,// 325 PAY 292 

    0x5fb64833,// 326 PAY 293 

    0xcf59a242,// 327 PAY 294 

    0xe543d401,// 328 PAY 295 

    0x2e9ae414,// 329 PAY 296 

    0xbe0a1b32,// 330 PAY 297 

    0xb674555b,// 331 PAY 298 

    0xdb7126c4,// 332 PAY 299 

    0x88564358,// 333 PAY 300 

    0x21daa2ff,// 334 PAY 301 

    0x2e67e4ba,// 335 PAY 302 

    0x417c50eb,// 336 PAY 303 

    0x72c55fde,// 337 PAY 304 

    0x15c73d4b,// 338 PAY 305 

    0x127993ce,// 339 PAY 306 

    0xdc793621,// 340 PAY 307 

    0x0f83b236,// 341 PAY 308 

    0xc79a444e,// 342 PAY 309 

    0x46067b36,// 343 PAY 310 

    0x1b7866f1,// 344 PAY 311 

    0x6b0b3fa0,// 345 PAY 312 

    0xe109f06a,// 346 PAY 313 

    0x4c7523d6,// 347 PAY 314 

    0x52b18cad,// 348 PAY 315 

    0x38c9aaa5,// 349 PAY 316 

    0xac2a693c,// 350 PAY 317 

    0x049f6bb0,// 351 PAY 318 

    0x998f2416,// 352 PAY 319 

    0xa403cc45,// 353 PAY 320 

    0xd5948800,// 354 PAY 321 

    0xda2c5d29,// 355 PAY 322 

    0x2a4eb4bb,// 356 PAY 323 

    0xb3e47bfb,// 357 PAY 324 

    0xd9d3491e,// 358 PAY 325 

    0x13f5f000,// 359 PAY 326 

    0xfaa6748d,// 360 PAY 327 

    0xb314b78a,// 361 PAY 328 

    0xa8745d54,// 362 PAY 329 

    0x588b9680,// 363 PAY 330 

    0x279f477b,// 364 PAY 331 

    0xe0ebb850,// 365 PAY 332 

    0xc16e9c7c,// 366 PAY 333 

    0x9af5bda1,// 367 PAY 334 

    0xf57b738f,// 368 PAY 335 

    0xd148aa75,// 369 PAY 336 

    0x55fb31a5,// 370 PAY 337 

    0x0fb6d0f9,// 371 PAY 338 

    0xa2c4e6f7,// 372 PAY 339 

    0xd46998c7,// 373 PAY 340 

    0x50421d8e,// 374 PAY 341 

    0xfeed3fb7,// 375 PAY 342 

    0x1716c53f,// 376 PAY 343 

    0x76e42e13,// 377 PAY 344 

    0xdd5423dc,// 378 PAY 345 

    0x59f13b73,// 379 PAY 346 

    0xf145d6ef,// 380 PAY 347 

    0x410dc6ca,// 381 PAY 348 

    0xb705de7e,// 382 PAY 349 

    0x3727906a,// 383 PAY 350 

    0x07d1257a,// 384 PAY 351 

    0x7d2acf55,// 385 PAY 352 

    0xdf1ef3e7,// 386 PAY 353 

    0x174e55a9,// 387 PAY 354 

    0xdf9e426b,// 388 PAY 355 

    0x2257f68f,// 389 PAY 356 

    0x3f078667,// 390 PAY 357 

    0xad031f0a,// 391 PAY 358 

    0x2e53efd0,// 392 PAY 359 

    0x6bfe4f69,// 393 PAY 360 

    0xc8aaa7d3,// 394 PAY 361 

    0x7a0fa657,// 395 PAY 362 

    0x203c9364,// 396 PAY 363 

    0x7e1e2d9e,// 397 PAY 364 

    0xc48976fd,// 398 PAY 365 

    0x3013af9c,// 399 PAY 366 

    0xb8324d23,// 400 PAY 367 

    0xdfed1952,// 401 PAY 368 

    0x72a43a28,// 402 PAY 369 

    0x12906d5d,// 403 PAY 370 

    0x2b957967,// 404 PAY 371 

    0xbe103c45,// 405 PAY 372 

    0x4e769252,// 406 PAY 373 

    0x7ccaec99,// 407 PAY 374 

    0x2af84307,// 408 PAY 375 

    0x5d327cc5,// 409 PAY 376 

    0x95481873,// 410 PAY 377 

    0x5ead798b,// 411 PAY 378 

    0xab013bff,// 412 PAY 379 

    0x890b2a76,// 413 PAY 380 

    0x6b177126,// 414 PAY 381 

    0xa85ca3f0,// 415 PAY 382 

    0xcc0524e8,// 416 PAY 383 

    0x2a2ff3bf,// 417 PAY 384 

    0xfe0e95af,// 418 PAY 385 

    0x3de12dcf,// 419 PAY 386 

    0x0c58d0df,// 420 PAY 387 

    0xf559697f,// 421 PAY 388 

    0x297f0a52,// 422 PAY 389 

    0x32ee6bc4,// 423 PAY 390 

    0xaa664786,// 424 PAY 391 

    0x67c34955,// 425 PAY 392 

    0xebe4f062,// 426 PAY 393 

    0x31d94c5c,// 427 PAY 394 

    0x85898a57,// 428 PAY 395 

    0x61e28fee,// 429 PAY 396 

    0x4efb0b50,// 430 PAY 397 

    0x62838b01,// 431 PAY 398 

    0xff65819d,// 432 PAY 399 

    0x838f73ab,// 433 PAY 400 

    0xe9d9da52,// 434 PAY 401 

    0xb2a717ca,// 435 PAY 402 

    0x0ae74865,// 436 PAY 403 

    0xd07b24b5,// 437 PAY 404 

    0x3aff003e,// 438 PAY 405 

    0x76ab2b89,// 439 PAY 406 

    0xa2df3618,// 440 PAY 407 

    0xb4707d17,// 441 PAY 408 

    0x41af5508,// 442 PAY 409 

    0xf3244d93,// 443 PAY 410 

    0xb2170312,// 444 PAY 411 

    0x656363d5,// 445 PAY 412 

    0x3c5cd69f,// 446 PAY 413 

    0xaa27535f,// 447 PAY 414 

    0xf50a1d0f,// 448 PAY 415 

    0x5b3f0249,// 449 PAY 416 

    0x43f775c2,// 450 PAY 417 

    0xaa812ec1,// 451 PAY 418 

    0x5bef8257,// 452 PAY 419 

    0x4ce5c865,// 453 PAY 420 

    0x5fce7be5,// 454 PAY 421 

    0x553dcbf1,// 455 PAY 422 

    0xd357c400,// 456 PAY 423 

    0x021b86f8,// 457 PAY 424 

    0xa3f659b5,// 458 PAY 425 

    0x4f8b40e1,// 459 PAY 426 

    0x1d65da9e,// 460 PAY 427 

    0x5306fa45,// 461 PAY 428 

    0xdaa200ef,// 462 PAY 429 

    0x3cb7f535,// 463 PAY 430 

    0x477b0e20,// 464 PAY 431 

    0x447420c8,// 465 PAY 432 

    0x7ed7f06a,// 466 PAY 433 

    0x104b4a9b,// 467 PAY 434 

    0xd02545ae,// 468 PAY 435 

    0xb3714988,// 469 PAY 436 

    0x39f0e5c9,// 470 PAY 437 

    0xdfe92a59,// 471 PAY 438 

    0x654af32a,// 472 PAY 439 

    0x9674f2f2,// 473 PAY 440 

    0x0393647c,// 474 PAY 441 

    0xb4523744,// 475 PAY 442 

    0x083183d5,// 476 PAY 443 

    0x34e423a4,// 477 PAY 444 

    0x933a3f1f,// 478 PAY 445 

    0xcc402871,// 479 PAY 446 

    0xb7b9c800,// 480 PAY 447 

/// STA is 1 words. 

/// STA num_pkts       : 214 

/// STA pkt_idx        : 254 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xc1 

    0x03f8c1d6 // 481 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 72 (0x48) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt28_tmpl[] = {
    0xb8010048,// 1 CCH   1 

/// ECH cache_idx      : 0x0a 

/// ECH pdu_tag        : 0x00 

    0x000a0000,// 2 ECH   1 

/// SCX is 17 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000011,// 3 SCX   1 

    0x8080487b,// 4 SCX   2 

    0x00003500,// 5 SCX   3 

    0x1d902c6f,// 6 SCX   4 

    0x9cdec43f,// 7 SCX   5 

    0xca4df573,// 8 SCX   6 

    0xd12d8c0d,// 9 SCX   7 

    0xa1626e82,// 10 SCX   8 

    0x28806b29,// 11 SCX   9 

    0xe6009d69,// 12 SCX  10 

    0x2efd22ce,// 13 SCX  11 

    0x46ed1c19,// 14 SCX  12 

    0x38150954,// 15 SCX  13 

    0x217a9d42,// 16 SCX  14 

    0x38f2a709,// 17 SCX  15 

    0xca9e9622,// 18 SCX  16 

    0xfde26edb,// 19 SCX  17 

/// BFD is 3 words. 

/// BFD tot_len        : 1133 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 646 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 646 

/// BFD lencrypto      : 128 

/// BFD ofstcrypto     : 216 

/// BFD (ofst+len)cry  : 344 

/// BFD ofstiv         : 184 

/// BFD ofsticv        : 944 

    0x00000286,// 20 BFD   1 

    0x00d80080,// 21 BFD   2 

    0x03b000b8,// 22 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7b 

    0x7b00e95a,// 23 MFM   1 

    0x6236ad09,// 24 MFM   2 

    0x4d59ff40,// 25 MFM   3 

    0x722eb7b2,// 26 MFM   4 

    0xaf56e3c0,// 27 MFM   5 

    0x2dc35697,// 28 MFM   6 

    0x580e3928,// 29 MFM   7 

    0xefc91c20,// 30 MFM   8 

    0xbf83cae7,// 31 MFM   9 

    0xdd4633fd,// 32 MFM  10 

    0x88ca890d,// 33 MFM  11 

    0x2f489118,// 34 MFM  12 

    0xb1dc959b,// 35 MFM  13 

    0xbfcb598e,// 36 MFM  14 

    0x95732070,// 37 MFM  15 

    0x536e6af0,// 38 MFM  16 

/// BDA is 285 words. 

/// BDA size     is 1133 (0x46d) 

/// BDA id       is 0x24a3 

    0x046d24a3,// 39 BDA   1 

/// PAY Generic Data size   : 1133 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x3f614c14,// 40 PAY   1 

    0x8408fcb9,// 41 PAY   2 

    0xdb600bb3,// 42 PAY   3 

    0xd3c8bd16,// 43 PAY   4 

    0xe46be464,// 44 PAY   5 

    0xd6ea03d2,// 45 PAY   6 

    0x76b0ef48,// 46 PAY   7 

    0x6ddcc8e2,// 47 PAY   8 

    0x1d2461fe,// 48 PAY   9 

    0x30a97d17,// 49 PAY  10 

    0xfac16eff,// 50 PAY  11 

    0xa90527ff,// 51 PAY  12 

    0x33b7f059,// 52 PAY  13 

    0x11ca82ad,// 53 PAY  14 

    0x1eecf4b3,// 54 PAY  15 

    0x0f86f155,// 55 PAY  16 

    0x7f72a861,// 56 PAY  17 

    0x9a27e3f5,// 57 PAY  18 

    0xdae6e14e,// 58 PAY  19 

    0x4d8508da,// 59 PAY  20 

    0xe4ed2a7a,// 60 PAY  21 

    0x1cf55ec8,// 61 PAY  22 

    0x7fb2b258,// 62 PAY  23 

    0x11ae51e9,// 63 PAY  24 

    0xd0007996,// 64 PAY  25 

    0x02a7a5b9,// 65 PAY  26 

    0xc88e4207,// 66 PAY  27 

    0x3908bbc7,// 67 PAY  28 

    0xc4ca33d6,// 68 PAY  29 

    0x415d6933,// 69 PAY  30 

    0x47f9f655,// 70 PAY  31 

    0xb07bf970,// 71 PAY  32 

    0x4b1cc118,// 72 PAY  33 

    0x8f9d7488,// 73 PAY  34 

    0xc6885a50,// 74 PAY  35 

    0x71a0fc0d,// 75 PAY  36 

    0x4f155524,// 76 PAY  37 

    0x456ceff5,// 77 PAY  38 

    0x939cf0c3,// 78 PAY  39 

    0xaf30c985,// 79 PAY  40 

    0xc95eb642,// 80 PAY  41 

    0xde251884,// 81 PAY  42 

    0x92845f61,// 82 PAY  43 

    0xc35ca720,// 83 PAY  44 

    0x7c9ca7e8,// 84 PAY  45 

    0x1e34917a,// 85 PAY  46 

    0x4e77a3b7,// 86 PAY  47 

    0x62ee2278,// 87 PAY  48 

    0x096b8a69,// 88 PAY  49 

    0xcaa4e8f9,// 89 PAY  50 

    0xb2418186,// 90 PAY  51 

    0xd579b2f1,// 91 PAY  52 

    0x2c31851f,// 92 PAY  53 

    0x12d00c66,// 93 PAY  54 

    0x8b9b9548,// 94 PAY  55 

    0x98eac40c,// 95 PAY  56 

    0x3b3c033c,// 96 PAY  57 

    0xae98d39f,// 97 PAY  58 

    0x3f2de989,// 98 PAY  59 

    0xae99451d,// 99 PAY  60 

    0x067d6dc3,// 100 PAY  61 

    0x9140e242,// 101 PAY  62 

    0x147dcfae,// 102 PAY  63 

    0xdf617f3f,// 103 PAY  64 

    0xb1797b23,// 104 PAY  65 

    0xd3ecf6f1,// 105 PAY  66 

    0x5cead6df,// 106 PAY  67 

    0xdab10fbb,// 107 PAY  68 

    0xbf4d8285,// 108 PAY  69 

    0x7d74d559,// 109 PAY  70 

    0x5e54365e,// 110 PAY  71 

    0x9606ad40,// 111 PAY  72 

    0xbf84de48,// 112 PAY  73 

    0xf18353a6,// 113 PAY  74 

    0x67541320,// 114 PAY  75 

    0x88c15207,// 115 PAY  76 

    0x94bb43b1,// 116 PAY  77 

    0x7fbc0758,// 117 PAY  78 

    0x3b898855,// 118 PAY  79 

    0x14d92a7c,// 119 PAY  80 

    0x82c1d7cf,// 120 PAY  81 

    0x27b5438a,// 121 PAY  82 

    0xd0665ae0,// 122 PAY  83 

    0xff105b2a,// 123 PAY  84 

    0xaf9405ca,// 124 PAY  85 

    0x04b0f9f5,// 125 PAY  86 

    0xc63c4a90,// 126 PAY  87 

    0x9c5a89d7,// 127 PAY  88 

    0x994b7622,// 128 PAY  89 

    0xa63bac38,// 129 PAY  90 

    0xd9de9334,// 130 PAY  91 

    0xa904c0c3,// 131 PAY  92 

    0x2003ba24,// 132 PAY  93 

    0x72e452b2,// 133 PAY  94 

    0xc7ed71cd,// 134 PAY  95 

    0x3738017a,// 135 PAY  96 

    0x488c39eb,// 136 PAY  97 

    0x37c75334,// 137 PAY  98 

    0xab2f28d2,// 138 PAY  99 

    0x48fb48fb,// 139 PAY 100 

    0xe5e55632,// 140 PAY 101 

    0x82d23804,// 141 PAY 102 

    0xf6d9f558,// 142 PAY 103 

    0x4d02e0c8,// 143 PAY 104 

    0x1d469fd1,// 144 PAY 105 

    0xc472208c,// 145 PAY 106 

    0x132278ca,// 146 PAY 107 

    0xb05166ac,// 147 PAY 108 

    0x2ae0ecc1,// 148 PAY 109 

    0x7bf7ae33,// 149 PAY 110 

    0xa2cf8326,// 150 PAY 111 

    0xdcd7e261,// 151 PAY 112 

    0x242c2df0,// 152 PAY 113 

    0xa3c66e46,// 153 PAY 114 

    0x577e2f0c,// 154 PAY 115 

    0x2fc9c54e,// 155 PAY 116 

    0xf2f4925a,// 156 PAY 117 

    0x3dc8a830,// 157 PAY 118 

    0x16f8c985,// 158 PAY 119 

    0x12fb4d90,// 159 PAY 120 

    0x2adea9fd,// 160 PAY 121 

    0xe5c171d4,// 161 PAY 122 

    0x4ca933e6,// 162 PAY 123 

    0xbb8a729d,// 163 PAY 124 

    0x13346c49,// 164 PAY 125 

    0x16733b6a,// 165 PAY 126 

    0xfd9439c4,// 166 PAY 127 

    0x778cb88a,// 167 PAY 128 

    0x14623871,// 168 PAY 129 

    0x14c0daba,// 169 PAY 130 

    0xb72ef37a,// 170 PAY 131 

    0x24ae7de6,// 171 PAY 132 

    0x00382e34,// 172 PAY 133 

    0x6c475dbe,// 173 PAY 134 

    0xad267448,// 174 PAY 135 

    0x864f6e64,// 175 PAY 136 

    0x4938f51d,// 176 PAY 137 

    0x8951f9d9,// 177 PAY 138 

    0x08c36268,// 178 PAY 139 

    0x4d96ec72,// 179 PAY 140 

    0xa7fd8e54,// 180 PAY 141 

    0x38e0c1c7,// 181 PAY 142 

    0xa00af3a7,// 182 PAY 143 

    0x2254febf,// 183 PAY 144 

    0x72267066,// 184 PAY 145 

    0x53d29d78,// 185 PAY 146 

    0x3b228e73,// 186 PAY 147 

    0xdcccc8c5,// 187 PAY 148 

    0x9c3b3cd3,// 188 PAY 149 

    0xd0214db1,// 189 PAY 150 

    0x11994723,// 190 PAY 151 

    0x5bd3b5d6,// 191 PAY 152 

    0x3ec8b269,// 192 PAY 153 

    0xcbe16cda,// 193 PAY 154 

    0x4aa07623,// 194 PAY 155 

    0xcd4682fc,// 195 PAY 156 

    0x14721f55,// 196 PAY 157 

    0x61bbfb88,// 197 PAY 158 

    0x298c97e7,// 198 PAY 159 

    0xc2bb8a0b,// 199 PAY 160 

    0xb0986a58,// 200 PAY 161 

    0x422145f2,// 201 PAY 162 

    0x4433c358,// 202 PAY 163 

    0x1bcce3d5,// 203 PAY 164 

    0xefa74849,// 204 PAY 165 

    0xb323ed99,// 205 PAY 166 

    0x8d4ed436,// 206 PAY 167 

    0xfab34cd7,// 207 PAY 168 

    0x4e9e2bbe,// 208 PAY 169 

    0xbbe2c00e,// 209 PAY 170 

    0xc59874aa,// 210 PAY 171 

    0xb40aeccb,// 211 PAY 172 

    0x06601553,// 212 PAY 173 

    0x40b008aa,// 213 PAY 174 

    0x840ff390,// 214 PAY 175 

    0x05647ea4,// 215 PAY 176 

    0x8e2ab29e,// 216 PAY 177 

    0x6d795f62,// 217 PAY 178 

    0x4b5e26df,// 218 PAY 179 

    0x82b516fe,// 219 PAY 180 

    0xd52b87d3,// 220 PAY 181 

    0xa8f92792,// 221 PAY 182 

    0x4ac43252,// 222 PAY 183 

    0xcac7604f,// 223 PAY 184 

    0x82a6dbdb,// 224 PAY 185 

    0x9f370de8,// 225 PAY 186 

    0xbf071cd0,// 226 PAY 187 

    0x33f76e2b,// 227 PAY 188 

    0x7f74421f,// 228 PAY 189 

    0x0e30aa13,// 229 PAY 190 

    0x542bb53f,// 230 PAY 191 

    0x1f874acc,// 231 PAY 192 

    0x98089caf,// 232 PAY 193 

    0x8ae6f424,// 233 PAY 194 

    0x2b3ad38f,// 234 PAY 195 

    0x8fd07439,// 235 PAY 196 

    0x91a4b6b5,// 236 PAY 197 

    0x46490b9b,// 237 PAY 198 

    0x6710e2d1,// 238 PAY 199 

    0x2b1203a7,// 239 PAY 200 

    0xeecf633a,// 240 PAY 201 

    0xfac1311a,// 241 PAY 202 

    0x03e452a4,// 242 PAY 203 

    0x6311561b,// 243 PAY 204 

    0x3f3aa77e,// 244 PAY 205 

    0xc09be41d,// 245 PAY 206 

    0x4e77992a,// 246 PAY 207 

    0x8ecde911,// 247 PAY 208 

    0x60be04b1,// 248 PAY 209 

    0xe2bd31a0,// 249 PAY 210 

    0x1c87e278,// 250 PAY 211 

    0xcfa6e3b9,// 251 PAY 212 

    0x7bc8bc72,// 252 PAY 213 

    0x0e038cc9,// 253 PAY 214 

    0x9294ca67,// 254 PAY 215 

    0x25419164,// 255 PAY 216 

    0x89babc96,// 256 PAY 217 

    0x20e662bf,// 257 PAY 218 

    0xfd79d9ab,// 258 PAY 219 

    0x8628c252,// 259 PAY 220 

    0x20916bf9,// 260 PAY 221 

    0xfe274369,// 261 PAY 222 

    0x2ad1dd1f,// 262 PAY 223 

    0x6178d11f,// 263 PAY 224 

    0x0b6d479f,// 264 PAY 225 

    0x312e92f3,// 265 PAY 226 

    0x90124922,// 266 PAY 227 

    0xbaf82b70,// 267 PAY 228 

    0xbfb14f64,// 268 PAY 229 

    0xc3eaf093,// 269 PAY 230 

    0x2e399875,// 270 PAY 231 

    0xd876feab,// 271 PAY 232 

    0xce4c79bd,// 272 PAY 233 

    0x6f503e4d,// 273 PAY 234 

    0x564b7b24,// 274 PAY 235 

    0x0baa53ce,// 275 PAY 236 

    0xdeddf6c3,// 276 PAY 237 

    0x97bb49c5,// 277 PAY 238 

    0xb650f7d9,// 278 PAY 239 

    0x0d025088,// 279 PAY 240 

    0x49758c5e,// 280 PAY 241 

    0x65b62b43,// 281 PAY 242 

    0xdebf5738,// 282 PAY 243 

    0x9e5285c5,// 283 PAY 244 

    0x73eb350d,// 284 PAY 245 

    0x33d5ae71,// 285 PAY 246 

    0x62d489eb,// 286 PAY 247 

    0xe873bb5b,// 287 PAY 248 

    0x8d84ba27,// 288 PAY 249 

    0xe72beab2,// 289 PAY 250 

    0xfd3fe1a6,// 290 PAY 251 

    0x63ffab63,// 291 PAY 252 

    0xc9fbca15,// 292 PAY 253 

    0x4d248eec,// 293 PAY 254 

    0xa9319df3,// 294 PAY 255 

    0x26b6b359,// 295 PAY 256 

    0xdefe6e9f,// 296 PAY 257 

    0x0fc344c4,// 297 PAY 258 

    0xefcb1f17,// 298 PAY 259 

    0x37d976ae,// 299 PAY 260 

    0xbf1bd335,// 300 PAY 261 

    0x24fb2e1c,// 301 PAY 262 

    0xc420993c,// 302 PAY 263 

    0x73421364,// 303 PAY 264 

    0xe5c4cbe2,// 304 PAY 265 

    0x5d448a3f,// 305 PAY 266 

    0xea48a347,// 306 PAY 267 

    0xee5f7557,// 307 PAY 268 

    0x859dc015,// 308 PAY 269 

    0x3c3701e0,// 309 PAY 270 

    0xa75ee144,// 310 PAY 271 

    0xfec1666f,// 311 PAY 272 

    0x8c97e0cb,// 312 PAY 273 

    0x41f179f3,// 313 PAY 274 

    0x31a3f847,// 314 PAY 275 

    0x81ac6f55,// 315 PAY 276 

    0xf66936b5,// 316 PAY 277 

    0xc9f11a37,// 317 PAY 278 

    0xe476ff76,// 318 PAY 279 

    0x5de2fd1d,// 319 PAY 280 

    0x9200cfd4,// 320 PAY 281 

    0x470cdc1a,// 321 PAY 282 

    0x96cd4e84,// 322 PAY 283 

    0x8b000000,// 323 PAY 284 

/// STA is 1 words. 

/// STA num_pkts       : 128 

/// STA pkt_idx        : 122 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xe5 

    0x01e8e580 // 324 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt29_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x02 

/// ECH pdu_tag        : 0x00 

    0x00020000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x2 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000019,// 3 SCX   1 

    0x80924802,// 4 SCX   2 

    0x000062c2,// 5 SCX   3 

    0xe2ae96fe,// 6 SCX   4 

    0x07e24212,// 7 SCX   5 

    0x5f9b8e2e,// 8 SCX   6 

    0x33569262,// 9 SCX   7 

    0xe66fc8c8,// 10 SCX   8 

    0xcaf8e88b,// 11 SCX   9 

    0x7fa6cc30,// 12 SCX  10 

    0xa951ec99,// 13 SCX  11 

    0x55f2d818,// 14 SCX  12 

    0xd4826d8d,// 15 SCX  13 

    0xa1d01263,// 16 SCX  14 

    0x4d5c304e,// 17 SCX  15 

    0x64af5667,// 18 SCX  16 

    0x5ecefdfa,// 19 SCX  17 

    0x57ae1efa,// 20 SCX  18 

    0x2a4675c9,// 21 SCX  19 

    0x06a33d02,// 22 SCX  20 

    0xd709eb2e,// 23 SCX  21 

    0x64c24c51,// 24 SCX  22 

    0xd21619dc,// 25 SCX  23 

    0x512ab359,// 26 SCX  24 

    0xfb5fde70,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 143 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 87 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 87 

/// BFD lencrypto      : 8 

/// BFD ofstcrypto     : 68 

/// BFD (ofst+len)cry  : 76 

/// BFD ofstiv         : 52 

/// BFD ofsticv        : 120 

    0x00000057,// 28 BFD   1 

    0x00440008,// 29 BFD   2 

    0x00780034,// 30 BFD   3 

/// MFM is 3 words. 

/// MFM vldnibs        : 11 

    0x1100d012,// 31 MFM   1 

    0x4f962e05,// 32 MFM   2 

    0x8fe6f000,// 33 MFM   3 

/// BDA is 37 words. 

/// BDA size     is 143 (0x8f) 

/// BDA id       is 0x31c5 

    0x008f31c5,// 34 BDA   1 

/// PAY Generic Data size   : 143 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0xba159dab,// 35 PAY   1 

    0x3a5810fd,// 36 PAY   2 

    0x2c0db1af,// 37 PAY   3 

    0x086eb5ac,// 38 PAY   4 

    0x9d08338e,// 39 PAY   5 

    0x5229c8a9,// 40 PAY   6 

    0x5715c70b,// 41 PAY   7 

    0xb72e6137,// 42 PAY   8 

    0xa0e5f1d7,// 43 PAY   9 

    0x6e3f3ff3,// 44 PAY  10 

    0x84d1c428,// 45 PAY  11 

    0x2a86fa97,// 46 PAY  12 

    0xa66ec9e4,// 47 PAY  13 

    0xd52fcde2,// 48 PAY  14 

    0xc7d63825,// 49 PAY  15 

    0xaee144d8,// 50 PAY  16 

    0x653ccaaf,// 51 PAY  17 

    0x3cabc6c0,// 52 PAY  18 

    0xf87f8ed3,// 53 PAY  19 

    0xa6538f25,// 54 PAY  20 

    0x9508e4fb,// 55 PAY  21 

    0x6351bf9e,// 56 PAY  22 

    0x05da0f56,// 57 PAY  23 

    0xa1ea519e,// 58 PAY  24 

    0xcc087906,// 59 PAY  25 

    0xadea3d12,// 60 PAY  26 

    0xbc70ca58,// 61 PAY  27 

    0x886d36bd,// 62 PAY  28 

    0x466cea68,// 63 PAY  29 

    0x42c823ab,// 64 PAY  30 

    0x89901401,// 65 PAY  31 

    0x6f68c5df,// 66 PAY  32 

    0x91b8ae1f,// 67 PAY  33 

    0x23918cb0,// 68 PAY  34 

    0x28b8cbcf,// 69 PAY  35 

    0xaca35900,// 70 PAY  36 

/// STA is 1 words. 

/// STA num_pkts       : 28 

/// STA pkt_idx        : 43 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x6e 

    0x00ac6e1c // 71 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt30_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x03 

/// ECH pdu_tag        : 0x00 

    0x00030000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x8082483e,// 4 SCX   2 

    0x00005100,// 5 SCX   3 

    0xe554c192,// 6 SCX   4 

    0x2e36029a,// 7 SCX   5 

    0xbbc07892,// 8 SCX   6 

    0x9dbd9995,// 9 SCX   7 

    0x2ed286ca,// 10 SCX   8 

    0xa68a93ea,// 11 SCX   9 

    0x350037b3,// 12 SCX  10 

    0xc000b8ed,// 13 SCX  11 

    0x434c09d6,// 14 SCX  12 

    0x1b3818ec,// 15 SCX  13 

    0x7d44917a,// 16 SCX  14 

    0x0036e07b,// 17 SCX  15 

    0x1d2471bb,// 18 SCX  16 

    0x30e99c54,// 19 SCX  17 

    0x4203d84e,// 20 SCX  18 

    0xd9f5115c,// 21 SCX  19 

    0xcf33bc24,// 22 SCX  20 

    0x72157152,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 73 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 39 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 39 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 16 

/// BFD (ofst+len)cry  : 32 

/// BFD ofstiv         : 0 

/// BFD ofsticv        : 52 

    0x00000027,// 24 BFD   1 

    0x00100010,// 25 BFD   2 

    0x00340000,// 26 BFD   3 

/// MFM is 1 words. 

/// MFM vldnibs        : 2 

    0x02000000,// 27 MFM   1 

/// BDA is 20 words. 

/// BDA size     is 73 (0x49) 

/// BDA id       is 0x15c 

    0x0049015c,// 28 BDA   1 

/// PAY Generic Data size   : 73 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x577d1c20,// 29 PAY   1 

    0x04325a35,// 30 PAY   2 

    0xd67c2de0,// 31 PAY   3 

    0x67fe963e,// 32 PAY   4 

    0x1c1ad6bd,// 33 PAY   5 

    0x223a7441,// 34 PAY   6 

    0x94029589,// 35 PAY   7 

    0x5fe61a49,// 36 PAY   8 

    0xd50e1a83,// 37 PAY   9 

    0x697a7177,// 38 PAY  10 

    0x2c43222d,// 39 PAY  11 

    0xac4e2924,// 40 PAY  12 

    0x5153db27,// 41 PAY  13 

    0x6aefc1c1,// 42 PAY  14 

    0xd163bc79,// 43 PAY  15 

    0xc8974470,// 44 PAY  16 

    0x650e0314,// 45 PAY  17 

    0x81f01952,// 46 PAY  18 

    0xc6000000,// 47 PAY  19 

/// STA is 1 words. 

/// STA num_pkts       : 6 

/// STA pkt_idx        : 105 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x53 

    0x01a55306 // 48 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 96 (0x60) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt31_tmpl[] = {
    0xb8010060,// 1 CCH   1 

/// ECH cache_idx      : 0x0e 

/// ECH pdu_tag        : 0x00 

    0x000e0000,// 2 ECH   1 

/// SCX is 23 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv insert_icv !check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : AUTH_ENC 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000017,// 3 SCX   1 

    0xc0854870,// 4 SCX   2 

    0x00006184,// 5 SCX   3 

    0x22980b94,// 6 SCX   4 

    0x1e72eadb,// 7 SCX   5 

    0xec6c6536,// 8 SCX   6 

    0x749ab9b9,// 9 SCX   7 

    0xfbeeefff,// 10 SCX   8 

    0x71b8f0c6,// 11 SCX   9 

    0x5d61c124,// 12 SCX  10 

    0xfbf23f22,// 13 SCX  11 

    0xb3e87b63,// 14 SCX  12 

    0x7d3ce26d,// 15 SCX  13 

    0xf87293f4,// 16 SCX  14 

    0x0e18b0b0,// 17 SCX  15 

    0x2a04c639,// 18 SCX  16 

    0x0fd4653d,// 19 SCX  17 

    0xcfebf34c,// 20 SCX  18 

    0x808f1dab,// 21 SCX  19 

    0x2539eb70,// 22 SCX  20 

    0x0dfa8d43,// 23 SCX  21 

    0x82634fe1,// 24 SCX  22 

    0x7b55d5e2,// 25 SCX  23 

/// BFD is 3 words. 

/// BFD tot_len        : 52 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 32 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 32 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 16 

/// BFD (ofst+len)cry  : 32 

/// BFD ofstiv         : 0 

/// BFD ofsticv        : 32 

    0x00000020,// 26 BFD   1 

    0x00100010,// 27 BFD   2 

    0x00200000,// 28 BFD   3 

/// MFM is 1 words. 

/// MFM vldnibs        : 3 

    0x0300c470,// 29 MFM   1 

/// BDA is 14 words. 

/// BDA size     is 52 (0x34) 

/// BDA id       is 0x2b67 

    0x00342b67,// 30 BDA   1 

/// PAY Generic Data size   : 52 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0xa59181ba,// 31 PAY   1 

    0x7d280840,// 32 PAY   2 

    0x7396fef7,// 33 PAY   3 

    0xfaca1bc6,// 34 PAY   4 

    0x474cadac,// 35 PAY   5 

    0xca5f864b,// 36 PAY   6 

    0x57ef8105,// 37 PAY   7 

    0x8a5063c8,// 38 PAY   8 

    0x5f82c4c7,// 39 PAY   9 

    0x00b79393,// 40 PAY  10 

    0x2978ea9a,// 41 PAY  11 

    0xdb5d39e2,// 42 PAY  12 

    0x602e43bc,// 43 PAY  13 

/// STA is 1 words. 

/// STA num_pkts       : 179 

/// STA pkt_idx        : 154 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xb8 

    0x0269b8b3 // 44 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 96 (0x60) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt32_tmpl[] = {
    0xb8010060,// 1 CCH   1 

/// ECH cache_idx      : 0x0a 

/// ECH pdu_tag        : 0x00 

    0x000a0000,// 2 ECH   1 

/// SCX is 23 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv !check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000017,// 3 SCX   1 

    0x809148f5,// 4 SCX   2 

    0x00004382,// 5 SCX   3 

    0x07bd12f1,// 6 SCX   4 

    0x641af403,// 7 SCX   5 

    0xe9c10c4e,// 8 SCX   6 

    0x786fc2e2,// 9 SCX   7 

    0xccf6c305,// 10 SCX   8 

    0x4c510960,// 11 SCX   9 

    0xe02b8e01,// 12 SCX  10 

    0xeb57f924,// 13 SCX  11 

    0xdf531721,// 14 SCX  12 

    0xf31f4f65,// 15 SCX  13 

    0xb1dbf5b9,// 16 SCX  14 

    0x999dcd00,// 17 SCX  15 

    0xafccb82c,// 18 SCX  16 

    0x89ce3293,// 19 SCX  17 

    0xe2223104,// 20 SCX  18 

    0x365fdb80,// 21 SCX  19 

    0xb74a9dca,// 22 SCX  20 

    0xee4fe91a,// 23 SCX  21 

    0xe4536ade,// 24 SCX  22 

    0x25d16d84,// 25 SCX  23 

/// BFD is 3 words. 

/// BFD tot_len        : 468 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 121 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 121 

/// BFD lencrypto      : 4 

/// BFD ofstcrypto     : 116 

/// BFD (ofst+len)cry  : 120 

/// BFD ofstiv         : 48 

/// BFD ofsticv        : 148 

    0x00000079,// 26 BFD   1 

    0x00740004,// 27 BFD   2 

    0x00940030,// 28 BFD   3 

/// MFM is 1 words. 

/// MFM vldnibs        : 4 

    0x04006ac6,// 29 MFM   1 

/// BDA is 118 words. 

/// BDA size     is 468 (0x1d4) 

/// BDA id       is 0x1659 

    0x01d41659,// 30 BDA   1 

/// PAY Generic Data size   : 468 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0xe14a0e3a,// 31 PAY   1 

    0xf1804402,// 32 PAY   2 

    0x8efb7816,// 33 PAY   3 

    0x03eb350c,// 34 PAY   4 

    0xeb921450,// 35 PAY   5 

    0x705badd3,// 36 PAY   6 

    0x8244a412,// 37 PAY   7 

    0xa1e0ef84,// 38 PAY   8 

    0xfa8a69bd,// 39 PAY   9 

    0x5af0a664,// 40 PAY  10 

    0x535df48c,// 41 PAY  11 

    0xae14108a,// 42 PAY  12 

    0x8d5a7c77,// 43 PAY  13 

    0x6df535a6,// 44 PAY  14 

    0x10127b92,// 45 PAY  15 

    0xc9fd2ccd,// 46 PAY  16 

    0x1283b40e,// 47 PAY  17 

    0x5c6c8b31,// 48 PAY  18 

    0x4a14922c,// 49 PAY  19 

    0x00f38a16,// 50 PAY  20 

    0xa96fbfed,// 51 PAY  21 

    0x41839512,// 52 PAY  22 

    0x11d0795b,// 53 PAY  23 

    0xb441dbbd,// 54 PAY  24 

    0x3cd1838c,// 55 PAY  25 

    0x4be5055d,// 56 PAY  26 

    0xa33c7f22,// 57 PAY  27 

    0x0c7b9fea,// 58 PAY  28 

    0xb0587a44,// 59 PAY  29 

    0x52018aad,// 60 PAY  30 

    0xb1f7cc95,// 61 PAY  31 

    0x3e51e5b8,// 62 PAY  32 

    0x813fe830,// 63 PAY  33 

    0x69ad6c32,// 64 PAY  34 

    0xac74fe65,// 65 PAY  35 

    0x9c8d071f,// 66 PAY  36 

    0xb86ff75b,// 67 PAY  37 

    0xecbad958,// 68 PAY  38 

    0xdd6e40ad,// 69 PAY  39 

    0xa61b1f4b,// 70 PAY  40 

    0xbf262c72,// 71 PAY  41 

    0xd3626f38,// 72 PAY  42 

    0xacc4cce0,// 73 PAY  43 

    0x2ceb22b4,// 74 PAY  44 

    0xc356cae1,// 75 PAY  45 

    0xbfa31031,// 76 PAY  46 

    0x2665accf,// 77 PAY  47 

    0xd1cf4086,// 78 PAY  48 

    0x85231a2d,// 79 PAY  49 

    0xae3dd39d,// 80 PAY  50 

    0xcda84fbd,// 81 PAY  51 

    0xc83a9074,// 82 PAY  52 

    0xa77dc269,// 83 PAY  53 

    0xc51ae4cb,// 84 PAY  54 

    0xed97432e,// 85 PAY  55 

    0xf1ad4dbe,// 86 PAY  56 

    0xcd01c95b,// 87 PAY  57 

    0x15d28c43,// 88 PAY  58 

    0x7606aaad,// 89 PAY  59 

    0x52e28a68,// 90 PAY  60 

    0xfecd51be,// 91 PAY  61 

    0xbe1aee75,// 92 PAY  62 

    0xc0cef3e2,// 93 PAY  63 

    0x64427c46,// 94 PAY  64 

    0xeed09566,// 95 PAY  65 

    0xdb09f656,// 96 PAY  66 

    0x385851d2,// 97 PAY  67 

    0x2f9f618a,// 98 PAY  68 

    0x4ac32376,// 99 PAY  69 

    0x65aded9f,// 100 PAY  70 

    0xbfd3aa84,// 101 PAY  71 

    0xa84f3648,// 102 PAY  72 

    0xfc195c90,// 103 PAY  73 

    0x411d1406,// 104 PAY  74 

    0x526bc264,// 105 PAY  75 

    0x62a4881b,// 106 PAY  76 

    0x50488361,// 107 PAY  77 

    0x3b26800d,// 108 PAY  78 

    0x5718763d,// 109 PAY  79 

    0xce694ed1,// 110 PAY  80 

    0x85b54e61,// 111 PAY  81 

    0xecfcf2a0,// 112 PAY  82 

    0xb9ef5acb,// 113 PAY  83 

    0xaee0b763,// 114 PAY  84 

    0x45bf0bc7,// 115 PAY  85 

    0xd42e9bfe,// 116 PAY  86 

    0x687fbac7,// 117 PAY  87 

    0x8eeae278,// 118 PAY  88 

    0xa498537e,// 119 PAY  89 

    0x1523870e,// 120 PAY  90 

    0x4947ed26,// 121 PAY  91 

    0xe2da4973,// 122 PAY  92 

    0x0cfe45c0,// 123 PAY  93 

    0xff756fda,// 124 PAY  94 

    0x5188b8ce,// 125 PAY  95 

    0x1d16cfbd,// 126 PAY  96 

    0x4c58579e,// 127 PAY  97 

    0x23710478,// 128 PAY  98 

    0x113c41c0,// 129 PAY  99 

    0x8da435ca,// 130 PAY 100 

    0x4c81d469,// 131 PAY 101 

    0x69d43474,// 132 PAY 102 

    0xb4a26982,// 133 PAY 103 

    0xc76e4da8,// 134 PAY 104 

    0x5e776fef,// 135 PAY 105 

    0x04a4958a,// 136 PAY 106 

    0x77163f2e,// 137 PAY 107 

    0x0614efc3,// 138 PAY 108 

    0x1558be96,// 139 PAY 109 

    0xbabb575b,// 140 PAY 110 

    0x007cdd82,// 141 PAY 111 

    0xe548d3b6,// 142 PAY 112 

    0xa2d438e0,// 143 PAY 113 

    0x4b5cc796,// 144 PAY 114 

    0x87cea418,// 145 PAY 115 

    0x4eff9eb5,// 146 PAY 116 

    0xe58791ac,// 147 PAY 117 

/// STA is 1 words. 

/// STA num_pkts       : 75 

/// STA pkt_idx        : 68 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x28 

    0x0111284b // 148 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 80 (0x50) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt33_tmpl[] = {
    0xb8010050,// 1 CCH   1 

/// ECH cache_idx      : 0x06 

/// ECH pdu_tag        : 0x00 

    0x00060000,// 2 ECH   1 

/// SCX is 19 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv !insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000013,// 3 SCX   1 

    0x8081485f,// 4 SCX   2 

    0x00001500,// 5 SCX   3 

    0x4db8129a,// 6 SCX   4 

    0x61c4bca0,// 7 SCX   5 

    0x956c95b8,// 8 SCX   6 

    0xc27a4c66,// 9 SCX   7 

    0x510b4293,// 10 SCX   8 

    0x961eb6f1,// 11 SCX   9 

    0xc6f89957,// 12 SCX  10 

    0x03105da5,// 13 SCX  11 

    0x3fdbc817,// 14 SCX  12 

    0xa67abd27,// 15 SCX  13 

    0x90b416a5,// 16 SCX  14 

    0x57c80d87,// 17 SCX  15 

    0xf37b4b30,// 18 SCX  16 

    0xecd0cdad,// 19 SCX  17 

    0x9666f250,// 20 SCX  18 

    0x113dc5c8,// 21 SCX  19 

/// BFD is 3 words. 

/// BFD tot_len        : 799 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 754 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 754 

/// BFD lencrypto      : 48 

/// BFD ofstcrypto     : 440 

/// BFD (ofst+len)cry  : 488 

/// BFD ofstiv         : 316 

/// BFD ofsticv        : 756 

    0x000002f2,// 22 BFD   1 

    0x01b80030,// 23 BFD   2 

    0x02f4013c,// 24 BFD   3 

/// MFM is 14 words. 

/// MFM vldnibs        : 67 

    0x6700577e,// 25 MFM   1 

    0x112c832c,// 26 MFM   2 

    0xd83efcbe,// 27 MFM   3 

    0x2bc243a1,// 28 MFM   4 

    0x79da57e7,// 29 MFM   5 

    0x0efd23eb,// 30 MFM   6 

    0x48e61557,// 31 MFM   7 

    0xdc52b9c7,// 32 MFM   8 

    0x871625f7,// 33 MFM   9 

    0xa56154f2,// 34 MFM  10 

    0x94386470,// 35 MFM  11 

    0x8a438c8d,// 36 MFM  12 

    0xb42469e7,// 37 MFM  13 

    0x4fa00000,// 38 MFM  14 

/// BDA is 201 words. 

/// BDA size     is 799 (0x31f) 

/// BDA id       is 0x8db2 

    0x031f8db2,// 39 BDA   1 

/// PAY Generic Data size   : 799 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0x05b81d17,// 40 PAY   1 

    0x3a6c8254,// 41 PAY   2 

    0xf64565c2,// 42 PAY   3 

    0x93c25d7c,// 43 PAY   4 

    0x314b3f43,// 44 PAY   5 

    0x7bea6b0b,// 45 PAY   6 

    0xbcc46941,// 46 PAY   7 

    0x55a75b8d,// 47 PAY   8 

    0xc6537966,// 48 PAY   9 

    0xa7c0863f,// 49 PAY  10 

    0x1b43b86f,// 50 PAY  11 

    0x177c6e9e,// 51 PAY  12 

    0xcc0975d1,// 52 PAY  13 

    0x0e05f001,// 53 PAY  14 

    0x243dce1c,// 54 PAY  15 

    0xc1fc80c4,// 55 PAY  16 

    0x7f173b72,// 56 PAY  17 

    0xf46b1bfe,// 57 PAY  18 

    0x98a33d18,// 58 PAY  19 

    0xc757d2d0,// 59 PAY  20 

    0xa46c03b5,// 60 PAY  21 

    0xd74ab563,// 61 PAY  22 

    0xa52499ab,// 62 PAY  23 

    0xfabac680,// 63 PAY  24 

    0x07cd5628,// 64 PAY  25 

    0x8eb3d4ee,// 65 PAY  26 

    0x175dd802,// 66 PAY  27 

    0x58e374e4,// 67 PAY  28 

    0x62cf8c14,// 68 PAY  29 

    0xb747aa4c,// 69 PAY  30 

    0x822dad3a,// 70 PAY  31 

    0x642f8073,// 71 PAY  32 

    0xd6b8b21c,// 72 PAY  33 

    0x78800bd0,// 73 PAY  34 

    0x8c51e4f9,// 74 PAY  35 

    0x087765c2,// 75 PAY  36 

    0xda99b2b1,// 76 PAY  37 

    0x1ad5cbb4,// 77 PAY  38 

    0xb16c7e95,// 78 PAY  39 

    0xcc4e2c2c,// 79 PAY  40 

    0x60cf8022,// 80 PAY  41 

    0x445a817d,// 81 PAY  42 

    0xbfb0ee22,// 82 PAY  43 

    0x3fcf5385,// 83 PAY  44 

    0x1b00aaa4,// 84 PAY  45 

    0xe66d332e,// 85 PAY  46 

    0xb69f53cb,// 86 PAY  47 

    0x6f881758,// 87 PAY  48 

    0x1c133094,// 88 PAY  49 

    0x74c778e0,// 89 PAY  50 

    0x6b47d71c,// 90 PAY  51 

    0x26b797ce,// 91 PAY  52 

    0x4f32c755,// 92 PAY  53 

    0x69c16eac,// 93 PAY  54 

    0x66ccd825,// 94 PAY  55 

    0xe6cb435f,// 95 PAY  56 

    0x09f622e2,// 96 PAY  57 

    0x3356a0f6,// 97 PAY  58 

    0xcb9db251,// 98 PAY  59 

    0x23f9925e,// 99 PAY  60 

    0xfd03ceb4,// 100 PAY  61 

    0x6072225b,// 101 PAY  62 

    0x915b6568,// 102 PAY  63 

    0xebaca34a,// 103 PAY  64 

    0xe7efae46,// 104 PAY  65 

    0x6ac89109,// 105 PAY  66 

    0x81550a97,// 106 PAY  67 

    0xd28bfb54,// 107 PAY  68 

    0x21b0ba9a,// 108 PAY  69 

    0x985b0092,// 109 PAY  70 

    0xb6f6767d,// 110 PAY  71 

    0x201e8768,// 111 PAY  72 

    0xd94a9c6a,// 112 PAY  73 

    0x482fafe7,// 113 PAY  74 

    0xa04a317f,// 114 PAY  75 

    0x60d6ac7e,// 115 PAY  76 

    0x58a854f4,// 116 PAY  77 

    0x7e692755,// 117 PAY  78 

    0x850a40f9,// 118 PAY  79 

    0x11e6b27c,// 119 PAY  80 

    0xeda1f283,// 120 PAY  81 

    0xdf8bade0,// 121 PAY  82 

    0x9eaeac14,// 122 PAY  83 

    0xfcc4b9db,// 123 PAY  84 

    0x5d68ed45,// 124 PAY  85 

    0x7270a528,// 125 PAY  86 

    0x9543ccf0,// 126 PAY  87 

    0xd68512f8,// 127 PAY  88 

    0xd70f96cc,// 128 PAY  89 

    0x0f7d534c,// 129 PAY  90 

    0x42c4e068,// 130 PAY  91 

    0x709158a7,// 131 PAY  92 

    0xfaaa6fe3,// 132 PAY  93 

    0xe116826c,// 133 PAY  94 

    0xe6f1225f,// 134 PAY  95 

    0xe448df2e,// 135 PAY  96 

    0xd558f01c,// 136 PAY  97 

    0x582ac99b,// 137 PAY  98 

    0x26337d7c,// 138 PAY  99 

    0xa6877ceb,// 139 PAY 100 

    0x519d8aa9,// 140 PAY 101 

    0x8a6dcd44,// 141 PAY 102 

    0x5468792b,// 142 PAY 103 

    0x85359562,// 143 PAY 104 

    0x363c2d66,// 144 PAY 105 

    0x2997dc5d,// 145 PAY 106 

    0x04c0bbd1,// 146 PAY 107 

    0x5e1838ac,// 147 PAY 108 

    0x2c6067c8,// 148 PAY 109 

    0x60719a94,// 149 PAY 110 

    0xaa3efb16,// 150 PAY 111 

    0x2b1b75fb,// 151 PAY 112 

    0xc5ca1bb5,// 152 PAY 113 

    0xf3033eee,// 153 PAY 114 

    0xbb23556f,// 154 PAY 115 

    0xb95cafa3,// 155 PAY 116 

    0x66186960,// 156 PAY 117 

    0xf5ccabaf,// 157 PAY 118 

    0x013e1fde,// 158 PAY 119 

    0x6ef13e3c,// 159 PAY 120 

    0x5119e7f0,// 160 PAY 121 

    0x7b9e7cd1,// 161 PAY 122 

    0x48a16eb8,// 162 PAY 123 

    0xa1f73963,// 163 PAY 124 

    0xcfd4802a,// 164 PAY 125 

    0xfdb21b52,// 165 PAY 126 

    0x770be155,// 166 PAY 127 

    0xfe5403f7,// 167 PAY 128 

    0x90fda9c7,// 168 PAY 129 

    0x4d3b2d5c,// 169 PAY 130 

    0x6f829a64,// 170 PAY 131 

    0xeb4c611d,// 171 PAY 132 

    0x0f38b57a,// 172 PAY 133 

    0xb0523cd4,// 173 PAY 134 

    0x14353042,// 174 PAY 135 

    0xf8899a78,// 175 PAY 136 

    0xb56e89b1,// 176 PAY 137 

    0x39b0c170,// 177 PAY 138 

    0xf1eb9099,// 178 PAY 139 

    0x56d31b20,// 179 PAY 140 

    0xe48e35bb,// 180 PAY 141 

    0x65d4962f,// 181 PAY 142 

    0x855c4430,// 182 PAY 143 

    0xf9e95764,// 183 PAY 144 

    0xc703199d,// 184 PAY 145 

    0x30989479,// 185 PAY 146 

    0x3fcd1747,// 186 PAY 147 

    0x9b78579e,// 187 PAY 148 

    0x6454e44b,// 188 PAY 149 

    0xd08c98ee,// 189 PAY 150 

    0x3d5558c5,// 190 PAY 151 

    0xe7058a59,// 191 PAY 152 

    0xd8425e31,// 192 PAY 153 

    0x4ef0f5d8,// 193 PAY 154 

    0x655f737a,// 194 PAY 155 

    0x91b4e611,// 195 PAY 156 

    0x58b5f69f,// 196 PAY 157 

    0x4ad3f305,// 197 PAY 158 

    0x92ad4725,// 198 PAY 159 

    0x40efeebc,// 199 PAY 160 

    0xb17a7770,// 200 PAY 161 

    0xfcc65109,// 201 PAY 162 

    0x46df42b8,// 202 PAY 163 

    0x28a4d5a9,// 203 PAY 164 

    0x4cc6b6b5,// 204 PAY 165 

    0xf2eaaaee,// 205 PAY 166 

    0xa47f9818,// 206 PAY 167 

    0x64447c6c,// 207 PAY 168 

    0x52202afa,// 208 PAY 169 

    0x9774f130,// 209 PAY 170 

    0x6c6a6e1d,// 210 PAY 171 

    0x5c23c61b,// 211 PAY 172 

    0x979186f6,// 212 PAY 173 

    0xaf1ef0fd,// 213 PAY 174 

    0x839aa4af,// 214 PAY 175 

    0x8c03b0d6,// 215 PAY 176 

    0x6e3f7459,// 216 PAY 177 

    0xd96b208c,// 217 PAY 178 

    0x815daeb6,// 218 PAY 179 

    0x52bd56ac,// 219 PAY 180 

    0xe4fb2caf,// 220 PAY 181 

    0x92bdab92,// 221 PAY 182 

    0x949cd8ff,// 222 PAY 183 

    0xe5b3d6c8,// 223 PAY 184 

    0x1fdba3a7,// 224 PAY 185 

    0x2fef1630,// 225 PAY 186 

    0x1a2011df,// 226 PAY 187 

    0x15785472,// 227 PAY 188 

    0xf7c331c2,// 228 PAY 189 

    0x5362b00f,// 229 PAY 190 

    0x16158739,// 230 PAY 191 

    0x082e73bd,// 231 PAY 192 

    0x04c0f265,// 232 PAY 193 

    0xa829ef6e,// 233 PAY 194 

    0xaa9a5131,// 234 PAY 195 

    0x859a706e,// 235 PAY 196 

    0xaf6b8773,// 236 PAY 197 

    0xab0652ce,// 237 PAY 198 

    0x0eb0ba5b,// 238 PAY 199 

    0x3f81fb00,// 239 PAY 200 

/// STA is 1 words. 

/// STA num_pkts       : 55 

/// STA pkt_idx        : 141 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xb2 

    0x0234b237 // 240 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt34_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x0e 

/// ECH pdu_tag        : 0x00 

    0x000e0000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv insert_icv !check_icv !sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x00000015,// 3 SCX   1 

    0x8086484a,// 4 SCX   2 

    0x00006344,// 5 SCX   3 

    0xfa634ba9,// 6 SCX   4 

    0xdb5fd7e6,// 7 SCX   5 

    0x5624d51b,// 8 SCX   6 

    0xdd23dbed,// 9 SCX   7 

    0x44913200,// 10 SCX   8 

    0xe32f1946,// 11 SCX   9 

    0x79a82a58,// 12 SCX  10 

    0x1d0957b9,// 13 SCX  11 

    0x250df77e,// 14 SCX  12 

    0xdafc1e2c,// 15 SCX  13 

    0x2c3c1c4d,// 16 SCX  14 

    0x04c9667f,// 17 SCX  15 

    0xa4efcb21,// 18 SCX  16 

    0xc2a853d3,// 19 SCX  17 

    0x41a566b6,// 20 SCX  18 

    0xf4411b1d,// 21 SCX  19 

    0xbffbd64a,// 22 SCX  20 

    0x0791dccf,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 767 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 701 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 701 

/// BFD lencrypto      : 400 

/// BFD ofstcrypto     : 92 

/// BFD (ofst+len)cry  : 492 

/// BFD ofstiv         : 72 

/// BFD ofsticv        : 744 

    0x000002bd,// 24 BFD   1 

    0x005c0190,// 25 BFD   2 

    0x02e80048,// 26 BFD   3 

/// MFM is 14 words. 

/// MFM vldnibs        : 6a 

    0x6a00f48d,// 27 MFM   1 

    0x0ad9fe93,// 28 MFM   2 

    0x282f8285,// 29 MFM   3 

    0x024b35ef,// 30 MFM   4 

    0xa8f90b09,// 31 MFM   5 

    0x7055e6f6,// 32 MFM   6 

    0x524b0b1c,// 33 MFM   7 

    0x9230f1b3,// 34 MFM   8 

    0x94112406,// 35 MFM   9 

    0xf0fbcde2,// 36 MFM  10 

    0xe3505326,// 37 MFM  11 

    0x45bc16ae,// 38 MFM  12 

    0x2d7a1c62,// 39 MFM  13 

    0xfae01700,// 40 MFM  14 

/// BDA is 193 words. 

/// BDA size     is 767 (0x2ff) 

/// BDA id       is 0xaed0 

    0x02ffaed0,// 41 BDA   1 

/// PAY Generic Data size   : 767 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0x3d3c77be,// 42 PAY   1 

    0x206c8a93,// 43 PAY   2 

    0x92fe18bd,// 44 PAY   3 

    0xd66538b3,// 45 PAY   4 

    0xa50421ad,// 46 PAY   5 

    0xb3421882,// 47 PAY   6 

    0x947629a2,// 48 PAY   7 

    0xa58b039f,// 49 PAY   8 

    0x86a174ff,// 50 PAY   9 

    0x7e249d5b,// 51 PAY  10 

    0xca50768a,// 52 PAY  11 

    0xcc21cee2,// 53 PAY  12 

    0x46c6923c,// 54 PAY  13 

    0xb04808b2,// 55 PAY  14 

    0x7b474ed1,// 56 PAY  15 

    0x0e2c712b,// 57 PAY  16 

    0x963a6fbe,// 58 PAY  17 

    0xb985e166,// 59 PAY  18 

    0x7b76ca95,// 60 PAY  19 

    0x2a090c88,// 61 PAY  20 

    0xb44bcc6a,// 62 PAY  21 

    0x7055710b,// 63 PAY  22 

    0x2b27dfca,// 64 PAY  23 

    0x9fd309f8,// 65 PAY  24 

    0x720a8b4e,// 66 PAY  25 

    0x1dde4c6c,// 67 PAY  26 

    0x095a4fce,// 68 PAY  27 

    0xa8222878,// 69 PAY  28 

    0x91981468,// 70 PAY  29 

    0x61d3f66c,// 71 PAY  30 

    0x9497412b,// 72 PAY  31 

    0xf0a56c0f,// 73 PAY  32 

    0xed3437ec,// 74 PAY  33 

    0x529b5e97,// 75 PAY  34 

    0xacc493bf,// 76 PAY  35 

    0x9601a543,// 77 PAY  36 

    0xa54557ae,// 78 PAY  37 

    0x43c1bdc6,// 79 PAY  38 

    0x83b061e2,// 80 PAY  39 

    0xaf78be89,// 81 PAY  40 

    0xd4f341a8,// 82 PAY  41 

    0xee23a304,// 83 PAY  42 

    0x65b55944,// 84 PAY  43 

    0x674e28a4,// 85 PAY  44 

    0x5e65af9d,// 86 PAY  45 

    0x7f9cd279,// 87 PAY  46 

    0x03b54673,// 88 PAY  47 

    0x15400e68,// 89 PAY  48 

    0x7052a1f3,// 90 PAY  49 

    0xd403f9e6,// 91 PAY  50 

    0x42afff64,// 92 PAY  51 

    0x9b03fe3b,// 93 PAY  52 

    0xf4e1bfa9,// 94 PAY  53 

    0x0f81e0cd,// 95 PAY  54 

    0xb86b4d6e,// 96 PAY  55 

    0xd657bf90,// 97 PAY  56 

    0x8f8cd378,// 98 PAY  57 

    0xc4cd611b,// 99 PAY  58 

    0xc40c92aa,// 100 PAY  59 

    0x8f62cbb6,// 101 PAY  60 

    0x2ed36590,// 102 PAY  61 

    0xc411bcff,// 103 PAY  62 

    0x43b711a8,// 104 PAY  63 

    0xc27b0124,// 105 PAY  64 

    0x95fbb1b2,// 106 PAY  65 

    0xe481ab46,// 107 PAY  66 

    0x6dd00c31,// 108 PAY  67 

    0x55538eab,// 109 PAY  68 

    0x24f8524e,// 110 PAY  69 

    0x5070263b,// 111 PAY  70 

    0x46585401,// 112 PAY  71 

    0xf8c136b6,// 113 PAY  72 

    0xba4b824d,// 114 PAY  73 

    0x64f499e5,// 115 PAY  74 

    0x6c5a3cf9,// 116 PAY  75 

    0xbf28bae9,// 117 PAY  76 

    0x76e20b2e,// 118 PAY  77 

    0xcedbfa0c,// 119 PAY  78 

    0x41af46ef,// 120 PAY  79 

    0x2d368667,// 121 PAY  80 

    0x162baf31,// 122 PAY  81 

    0xa6a70eab,// 123 PAY  82 

    0x1ee347ee,// 124 PAY  83 

    0x4856648b,// 125 PAY  84 

    0x77b80cc6,// 126 PAY  85 

    0xbebe540f,// 127 PAY  86 

    0x79fadc60,// 128 PAY  87 

    0x170bb1e0,// 129 PAY  88 

    0xc864ba13,// 130 PAY  89 

    0xa8c89877,// 131 PAY  90 

    0x6d1a6c77,// 132 PAY  91 

    0xf2d669c3,// 133 PAY  92 

    0xd5ca3cf5,// 134 PAY  93 

    0xedf824c7,// 135 PAY  94 

    0x4074e41b,// 136 PAY  95 

    0x8620fa52,// 137 PAY  96 

    0xcfb9e226,// 138 PAY  97 

    0x31f3d023,// 139 PAY  98 

    0x6f4940c4,// 140 PAY  99 

    0x4340f787,// 141 PAY 100 

    0x2ad0f60d,// 142 PAY 101 

    0x6f7c0b3c,// 143 PAY 102 

    0x1dab4cd1,// 144 PAY 103 

    0xaf4269a4,// 145 PAY 104 

    0x2d6fd4b6,// 146 PAY 105 

    0x3179ec0e,// 147 PAY 106 

    0x83fea7b4,// 148 PAY 107 

    0x929ca3ac,// 149 PAY 108 

    0xa2c8d0a1,// 150 PAY 109 

    0xbeccd639,// 151 PAY 110 

    0xa3965f61,// 152 PAY 111 

    0x76d54e1f,// 153 PAY 112 

    0x9a2c26c4,// 154 PAY 113 

    0x5a1ec8d8,// 155 PAY 114 

    0x30ef825c,// 156 PAY 115 

    0x4106051c,// 157 PAY 116 

    0x0b7ffc2c,// 158 PAY 117 

    0xe5d05cb4,// 159 PAY 118 

    0x93f40a03,// 160 PAY 119 

    0xee805638,// 161 PAY 120 

    0x4264a90a,// 162 PAY 121 

    0x08c41ba0,// 163 PAY 122 

    0xdf383d1f,// 164 PAY 123 

    0x691c43c1,// 165 PAY 124 

    0xa65885e0,// 166 PAY 125 

    0xffa591fc,// 167 PAY 126 

    0x96f0e2ef,// 168 PAY 127 

    0x1a29f074,// 169 PAY 128 

    0x3ab6eefd,// 170 PAY 129 

    0x84f9a7b7,// 171 PAY 130 

    0xcd35e40b,// 172 PAY 131 

    0x0e91a600,// 173 PAY 132 

    0xac369f3b,// 174 PAY 133 

    0x28f1cf3b,// 175 PAY 134 

    0x47c8a888,// 176 PAY 135 

    0x9110e2cb,// 177 PAY 136 

    0xda37abf5,// 178 PAY 137 

    0xb1f0d06b,// 179 PAY 138 

    0xadef2028,// 180 PAY 139 

    0x86f89aa5,// 181 PAY 140 

    0x221eccae,// 182 PAY 141 

    0xd934998c,// 183 PAY 142 

    0x380e4b07,// 184 PAY 143 

    0x6e5b06f4,// 185 PAY 144 

    0xcba67db8,// 186 PAY 145 

    0x4cd1cca1,// 187 PAY 146 

    0x18ca567a,// 188 PAY 147 

    0x5ac66860,// 189 PAY 148 

    0x87176eb5,// 190 PAY 149 

    0xd52a7824,// 191 PAY 150 

    0xfb111683,// 192 PAY 151 

    0xedeb4af8,// 193 PAY 152 

    0x5eaa1644,// 194 PAY 153 

    0x0224e4ef,// 195 PAY 154 

    0x605a7d61,// 196 PAY 155 

    0xdfe84dc0,// 197 PAY 156 

    0xda5f8374,// 198 PAY 157 

    0x93ef05b2,// 199 PAY 158 

    0xe5da4f0a,// 200 PAY 159 

    0x3f8904d0,// 201 PAY 160 

    0x5b1459c9,// 202 PAY 161 

    0xe90c381d,// 203 PAY 162 

    0x21253887,// 204 PAY 163 

    0x83521b44,// 205 PAY 164 

    0x83ba30c3,// 206 PAY 165 

    0x96ae08b5,// 207 PAY 166 

    0xf2ce9e74,// 208 PAY 167 

    0xf602cf3c,// 209 PAY 168 

    0xbc87a4aa,// 210 PAY 169 

    0xa0e4f1f7,// 211 PAY 170 

    0xaa48762c,// 212 PAY 171 

    0xb7b3900a,// 213 PAY 172 

    0x839854d1,// 214 PAY 173 

    0xbf9a27d2,// 215 PAY 174 

    0x4009b783,// 216 PAY 175 

    0xc90f14b0,// 217 PAY 176 

    0x4d7408b7,// 218 PAY 177 

    0x420eead1,// 219 PAY 178 

    0x6900c8dd,// 220 PAY 179 

    0x7b3d59bd,// 221 PAY 180 

    0x9ee15267,// 222 PAY 181 

    0xdc172585,// 223 PAY 182 

    0xc7613b08,// 224 PAY 183 

    0x61c31ca0,// 225 PAY 184 

    0x0e0a8a9f,// 226 PAY 185 

    0xd7172dc6,// 227 PAY 186 

    0x6d821f91,// 228 PAY 187 

    0xd75c744b,// 229 PAY 188 

    0x5a0369b3,// 230 PAY 189 

    0x15349a13,// 231 PAY 190 

    0x613006ed,// 232 PAY 191 

    0xce29c200,// 233 PAY 192 

/// STA is 1 words. 

/// STA num_pkts       : 84 

/// STA pkt_idx        : 173 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x3d 

    0x02b53d54 // 234 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 80 (0x50) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt35_tmpl[] = {
    0xb8010050,// 1 CCH   1 

/// ECH cache_idx      : 0x05 

/// ECH pdu_tag        : 0x00 

    0x00050000,// 2 ECH   1 

/// SCX is 19 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x00000013,// 3 SCX   1 

    0x80814840,// 4 SCX   2 

    0x00002300,// 5 SCX   3 

    0x5fcc81fa,// 6 SCX   4 

    0x91a45d98,// 7 SCX   5 

    0x082e871b,// 8 SCX   6 

    0xa55d3466,// 9 SCX   7 

    0xe38ac5eb,// 10 SCX   8 

    0x98231ae1,// 11 SCX   9 

    0x1ad532d9,// 12 SCX  10 

    0x0fff690d,// 13 SCX  11 

    0x8abb4718,// 14 SCX  12 

    0x1913554e,// 15 SCX  13 

    0xe26d5473,// 16 SCX  14 

    0x14644a39,// 17 SCX  15 

    0x0891fc39,// 18 SCX  16 

    0x6f5c688a,// 19 SCX  17 

    0x57c0e47f,// 20 SCX  18 

    0x1070f80b,// 21 SCX  19 

/// BFD is 3 words. 

/// BFD tot_len        : 1085 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 1013 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1013 

/// BFD lencrypto      : 144 

/// BFD ofstcrypto     : 640 

/// BFD (ofst+len)cry  : 784 

/// BFD ofstiv         : 216 

/// BFD ofsticv        : 1040 

    0x000003f5,// 22 BFD   1 

    0x02800090,// 23 BFD   2 

    0x041000d8,// 24 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c004aec,// 25 MFM   1 

    0xe30f367d,// 26 MFM   2 

    0xbf35934e,// 27 MFM   3 

    0xb4210cd1,// 28 MFM   4 

    0x4b00d45b,// 29 MFM   5 

    0x82bba562,// 30 MFM   6 

    0x92131ef5,// 31 MFM   7 

    0xb0f15825,// 32 MFM   8 

    0x4ee86010,// 33 MFM   9 

    0xb019dab5,// 34 MFM  10 

    0xce5b997c,// 35 MFM  11 

    0x476aecd1,// 36 MFM  12 

    0x51a72160,// 37 MFM  13 

    0x811f75f3,// 38 MFM  14 

    0xef535cd4,// 39 MFM  15 

    0x29317cc1,// 40 MFM  16 

/// BDA is 273 words. 

/// BDA size     is 1085 (0x43d) 

/// BDA id       is 0x41dc 

    0x043d41dc,// 41 BDA   1 

/// PAY Generic Data size   : 1085 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0xf2c8a447,// 42 PAY   1 

    0xf6f06e9b,// 43 PAY   2 

    0xa26b1531,// 44 PAY   3 

    0x50537162,// 45 PAY   4 

    0x9ea65629,// 46 PAY   5 

    0xa8844f83,// 47 PAY   6 

    0x2aebe292,// 48 PAY   7 

    0xd3ee7c39,// 49 PAY   8 

    0x6b94f80d,// 50 PAY   9 

    0xbedfe334,// 51 PAY  10 

    0x278c36c8,// 52 PAY  11 

    0x963041b3,// 53 PAY  12 

    0x5e929bf7,// 54 PAY  13 

    0x9561fd77,// 55 PAY  14 

    0xcb388331,// 56 PAY  15 

    0x80e66b5a,// 57 PAY  16 

    0x70957cc3,// 58 PAY  17 

    0xd59a704b,// 59 PAY  18 

    0xc52b25cc,// 60 PAY  19 

    0x98b85508,// 61 PAY  20 

    0xfd00c1ec,// 62 PAY  21 

    0xe2820b1e,// 63 PAY  22 

    0x58920b9a,// 64 PAY  23 

    0x555ec779,// 65 PAY  24 

    0xddbcf506,// 66 PAY  25 

    0x12f849e0,// 67 PAY  26 

    0xc528711d,// 68 PAY  27 

    0x2c13cf87,// 69 PAY  28 

    0xd165b0d0,// 70 PAY  29 

    0x7b88587b,// 71 PAY  30 

    0xd519e896,// 72 PAY  31 

    0xa4638ea7,// 73 PAY  32 

    0x3e523fd6,// 74 PAY  33 

    0xa25693c0,// 75 PAY  34 

    0x5e97527c,// 76 PAY  35 

    0x78e2aa1b,// 77 PAY  36 

    0xcab75821,// 78 PAY  37 

    0x7e07a93d,// 79 PAY  38 

    0xd2ee6fbf,// 80 PAY  39 

    0xf81f72e0,// 81 PAY  40 

    0xa88e752f,// 82 PAY  41 

    0x25de4a22,// 83 PAY  42 

    0xb3a38224,// 84 PAY  43 

    0x718599a7,// 85 PAY  44 

    0x770fafd1,// 86 PAY  45 

    0x15d3cba9,// 87 PAY  46 

    0x04be3598,// 88 PAY  47 

    0x55ed6c06,// 89 PAY  48 

    0x61a6a77b,// 90 PAY  49 

    0xd4dce8a2,// 91 PAY  50 

    0x0169d013,// 92 PAY  51 

    0x309a3039,// 93 PAY  52 

    0x13f62cf5,// 94 PAY  53 

    0x6b694ef1,// 95 PAY  54 

    0x2e94b632,// 96 PAY  55 

    0xb09a2e78,// 97 PAY  56 

    0xc6e5243f,// 98 PAY  57 

    0x581f9cec,// 99 PAY  58 

    0x72e28cf8,// 100 PAY  59 

    0xbc3531e3,// 101 PAY  60 

    0xa3841a06,// 102 PAY  61 

    0xce355f7a,// 103 PAY  62 

    0x04585036,// 104 PAY  63 

    0x69433980,// 105 PAY  64 

    0x0f6f2ff7,// 106 PAY  65 

    0x98ff57cd,// 107 PAY  66 

    0x1a435129,// 108 PAY  67 

    0x7efff22e,// 109 PAY  68 

    0xf60640c9,// 110 PAY  69 

    0x1860c115,// 111 PAY  70 

    0x65c894a7,// 112 PAY  71 

    0xbd0feb8a,// 113 PAY  72 

    0x7684d49e,// 114 PAY  73 

    0x0e127fe6,// 115 PAY  74 

    0x1a7230b1,// 116 PAY  75 

    0x8fb6deda,// 117 PAY  76 

    0x937df72b,// 118 PAY  77 

    0x6f6b90a3,// 119 PAY  78 

    0xbad6632d,// 120 PAY  79 

    0x4751b736,// 121 PAY  80 

    0x0c1b7b87,// 122 PAY  81 

    0xfdce8b08,// 123 PAY  82 

    0x0157dafd,// 124 PAY  83 

    0x24cc714f,// 125 PAY  84 

    0xc96d64cd,// 126 PAY  85 

    0x8ae9eb60,// 127 PAY  86 

    0x7a178864,// 128 PAY  87 

    0xca2411ac,// 129 PAY  88 

    0x8ae76eb7,// 130 PAY  89 

    0x8c5f4653,// 131 PAY  90 

    0xdecba7b8,// 132 PAY  91 

    0xdb400265,// 133 PAY  92 

    0x961ea054,// 134 PAY  93 

    0xb1ab37a8,// 135 PAY  94 

    0x07f2565d,// 136 PAY  95 

    0xe49e6b04,// 137 PAY  96 

    0xf78c51ba,// 138 PAY  97 

    0x18ef07ae,// 139 PAY  98 

    0x36931b1b,// 140 PAY  99 

    0x47780ad6,// 141 PAY 100 

    0x1f3ca8e8,// 142 PAY 101 

    0x1ed896b1,// 143 PAY 102 

    0x0931f2e7,// 144 PAY 103 

    0xd3f1d907,// 145 PAY 104 

    0xb381a2ae,// 146 PAY 105 

    0x427716c7,// 147 PAY 106 

    0x4bceddc4,// 148 PAY 107 

    0x9bfdb80a,// 149 PAY 108 

    0x10689d23,// 150 PAY 109 

    0x144e3b02,// 151 PAY 110 

    0x66108c8f,// 152 PAY 111 

    0x85e58975,// 153 PAY 112 

    0x83d7ead5,// 154 PAY 113 

    0x8a2f73cf,// 155 PAY 114 

    0x1ba7ef5d,// 156 PAY 115 

    0x496f7266,// 157 PAY 116 

    0x2c558ad1,// 158 PAY 117 

    0xec00d638,// 159 PAY 118 

    0x2e5b410d,// 160 PAY 119 

    0x829ddd1a,// 161 PAY 120 

    0x4d4a8f62,// 162 PAY 121 

    0xdcf98780,// 163 PAY 122 

    0x1c29789f,// 164 PAY 123 

    0xcd0e9f6a,// 165 PAY 124 

    0x7a4c7717,// 166 PAY 125 

    0xcb6f7e7f,// 167 PAY 126 

    0xf3888f4f,// 168 PAY 127 

    0x554faecb,// 169 PAY 128 

    0x128705d0,// 170 PAY 129 

    0x13ba3ade,// 171 PAY 130 

    0xda232b3e,// 172 PAY 131 

    0xd1d6f636,// 173 PAY 132 

    0x14b433cb,// 174 PAY 133 

    0x1d9a9841,// 175 PAY 134 

    0x331ef720,// 176 PAY 135 

    0x4b3819bb,// 177 PAY 136 

    0x953dfb18,// 178 PAY 137 

    0x9d1aa90e,// 179 PAY 138 

    0xa7338743,// 180 PAY 139 

    0xc6a7fa6f,// 181 PAY 140 

    0x1f7e0aeb,// 182 PAY 141 

    0x651f4ac5,// 183 PAY 142 

    0x6b0d3f93,// 184 PAY 143 

    0xf790f411,// 185 PAY 144 

    0x1a45c3d4,// 186 PAY 145 

    0xed745e3e,// 187 PAY 146 

    0x694ed9be,// 188 PAY 147 

    0xae92141b,// 189 PAY 148 

    0xa4d4c325,// 190 PAY 149 

    0x77b561e3,// 191 PAY 150 

    0xc371b1e6,// 192 PAY 151 

    0x316af308,// 193 PAY 152 

    0x6c08a8a0,// 194 PAY 153 

    0x73bbd37a,// 195 PAY 154 

    0x0c477a45,// 196 PAY 155 

    0xdd784d0d,// 197 PAY 156 

    0xba7e5a55,// 198 PAY 157 

    0x85dea188,// 199 PAY 158 

    0x8a1f5ef7,// 200 PAY 159 

    0x99c25d80,// 201 PAY 160 

    0xc27fc5c2,// 202 PAY 161 

    0xcdf4c1f8,// 203 PAY 162 

    0xc3b5fdbf,// 204 PAY 163 

    0xc208ca29,// 205 PAY 164 

    0x1ee893a3,// 206 PAY 165 

    0x952d18da,// 207 PAY 166 

    0xfd8435e8,// 208 PAY 167 

    0xfc9337b5,// 209 PAY 168 

    0x27e58f99,// 210 PAY 169 

    0x01a959e8,// 211 PAY 170 

    0x903df7d6,// 212 PAY 171 

    0xf8a3c448,// 213 PAY 172 

    0x7086cefe,// 214 PAY 173 

    0x5b03c824,// 215 PAY 174 

    0x2acd940e,// 216 PAY 175 

    0xd21816ac,// 217 PAY 176 

    0xdb182e43,// 218 PAY 177 

    0x4e816b5c,// 219 PAY 178 

    0x79e08273,// 220 PAY 179 

    0xd6983f71,// 221 PAY 180 

    0xdd3b6e1d,// 222 PAY 181 

    0xb9357abf,// 223 PAY 182 

    0x648f536b,// 224 PAY 183 

    0xfe7452e1,// 225 PAY 184 

    0x5d210cb3,// 226 PAY 185 

    0x6505b377,// 227 PAY 186 

    0x1eb31093,// 228 PAY 187 

    0xe688194c,// 229 PAY 188 

    0x24be1ec7,// 230 PAY 189 

    0x6b67565b,// 231 PAY 190 

    0x8050248b,// 232 PAY 191 

    0xc6088768,// 233 PAY 192 

    0x53df854d,// 234 PAY 193 

    0xa0134488,// 235 PAY 194 

    0xfd1ba543,// 236 PAY 195 

    0xda050bbc,// 237 PAY 196 

    0x7b8f71d4,// 238 PAY 197 

    0xac42e979,// 239 PAY 198 

    0x85dc5db8,// 240 PAY 199 

    0xeac91e7d,// 241 PAY 200 

    0x0d54159c,// 242 PAY 201 

    0x120cb784,// 243 PAY 202 

    0xb85d2122,// 244 PAY 203 

    0xf3fa4659,// 245 PAY 204 

    0xb4e3473d,// 246 PAY 205 

    0x6f4ffb20,// 247 PAY 206 

    0xf06b0e4d,// 248 PAY 207 

    0x991ca390,// 249 PAY 208 

    0xa79a97f3,// 250 PAY 209 

    0xea2a36db,// 251 PAY 210 

    0x1c60908c,// 252 PAY 211 

    0x8b25f871,// 253 PAY 212 

    0x66e13c7c,// 254 PAY 213 

    0x7e06c6f6,// 255 PAY 214 

    0x72f10e16,// 256 PAY 215 

    0x5bc8eef4,// 257 PAY 216 

    0x7629a7f7,// 258 PAY 217 

    0x7865c839,// 259 PAY 218 

    0x4029f20f,// 260 PAY 219 

    0x29a4666d,// 261 PAY 220 

    0x2f60c4e4,// 262 PAY 221 

    0x26fd0bca,// 263 PAY 222 

    0x750a5e3c,// 264 PAY 223 

    0xc959bd49,// 265 PAY 224 

    0xdec68cba,// 266 PAY 225 

    0x13848c41,// 267 PAY 226 

    0xb726fa04,// 268 PAY 227 

    0x0929aea0,// 269 PAY 228 

    0x8deb2bc0,// 270 PAY 229 

    0x7e93a834,// 271 PAY 230 

    0x50f2dd78,// 272 PAY 231 

    0x8017f19f,// 273 PAY 232 

    0xee7539ec,// 274 PAY 233 

    0xbd91d663,// 275 PAY 234 

    0xbe04b1a6,// 276 PAY 235 

    0xe3f01bb2,// 277 PAY 236 

    0x2f5e1a6b,// 278 PAY 237 

    0xa1e27727,// 279 PAY 238 

    0x79549205,// 280 PAY 239 

    0x6cc0093a,// 281 PAY 240 

    0xbb083943,// 282 PAY 241 

    0xa1bf595a,// 283 PAY 242 

    0xed7b3a9f,// 284 PAY 243 

    0x732d7f59,// 285 PAY 244 

    0x7259a81c,// 286 PAY 245 

    0xadddfebd,// 287 PAY 246 

    0x3e954a97,// 288 PAY 247 

    0x54769ac1,// 289 PAY 248 

    0xa5c3777f,// 290 PAY 249 

    0x2bc7cd36,// 291 PAY 250 

    0x2dcb4226,// 292 PAY 251 

    0x963ff68d,// 293 PAY 252 

    0xfe924176,// 294 PAY 253 

    0x347f45db,// 295 PAY 254 

    0x0232b214,// 296 PAY 255 

    0xf9d9b90c,// 297 PAY 256 

    0xa3f82095,// 298 PAY 257 

    0xd0eb2cb3,// 299 PAY 258 

    0x3cccfa16,// 300 PAY 259 

    0x206c1497,// 301 PAY 260 

    0x14854a40,// 302 PAY 261 

    0xa0e76c85,// 303 PAY 262 

    0xf56532f0,// 304 PAY 263 

    0x84bc47bb,// 305 PAY 264 

    0xc99b2f9e,// 306 PAY 265 

    0x5c5e5c4d,// 307 PAY 266 

    0x9df5151a,// 308 PAY 267 

    0x2e3eaa04,// 309 PAY 268 

    0x0a00c275,// 310 PAY 269 

    0x00ed4b48,// 311 PAY 270 

    0xd4548018,// 312 PAY 271 

    0x39000000,// 313 PAY 272 

/// STA is 1 words. 

/// STA num_pkts       : 214 

/// STA pkt_idx        : 7 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xfa 

    0x001cfad6 // 314 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 96 (0x60) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt36_tmpl[] = {
    0xb8010060,// 1 CCH   1 

/// ECH cache_idx      : 0x03 

/// ECH pdu_tag        : 0x00 

    0x00030000,// 2 ECH   1 

/// SCX is 23 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000017,// 3 SCX   1 

    0x80914879,// 4 SCX   2 

    0x00005382,// 5 SCX   3 

    0x87405254,// 6 SCX   4 

    0x7a867b94,// 7 SCX   5 

    0x923d8a6f,// 8 SCX   6 

    0xee387601,// 9 SCX   7 

    0xe1ed32d5,// 10 SCX   8 

    0xa9ace4b5,// 11 SCX   9 

    0x361b7de5,// 12 SCX  10 

    0xe8d441b7,// 13 SCX  11 

    0x7082cb31,// 14 SCX  12 

    0xe7956b93,// 15 SCX  13 

    0xa3bb6f0a,// 16 SCX  14 

    0x559a6a49,// 17 SCX  15 

    0xce86cd63,// 18 SCX  16 

    0xf0e89783,// 19 SCX  17 

    0xb8fecd21,// 20 SCX  18 

    0x6cb97ecd,// 21 SCX  19 

    0x1595eb0c,// 22 SCX  20 

    0x2c1b75d7,// 23 SCX  21 

    0xe27d4027,// 24 SCX  22 

    0x6944f6e0,// 25 SCX  23 

/// BFD is 3 words. 

/// BFD tot_len        : 2011 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 997 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 997 

/// BFD lencrypto      : 224 

/// BFD ofstcrypto     : 100 

/// BFD (ofst+len)cry  : 324 

/// BFD ofstiv         : 84 

/// BFD ofsticv        : 1896 

    0x000003e5,// 26 BFD   1 

    0x006400e0,// 27 BFD   2 

    0x07680054,// 28 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c0050a3,// 29 MFM   1 

    0x106f8af2,// 30 MFM   2 

    0xbc953f3b,// 31 MFM   3 

    0xf4113d66,// 32 MFM   4 

    0xb62bf3ed,// 33 MFM   5 

    0xf822dbfa,// 34 MFM   6 

    0xd767031b,// 35 MFM   7 

    0xdf36e7c2,// 36 MFM   8 

    0x1d4f487f,// 37 MFM   9 

    0x0decc953,// 38 MFM  10 

    0xf18e5287,// 39 MFM  11 

    0xa7fd2a9b,// 40 MFM  12 

    0xc24e2f94,// 41 MFM  13 

    0xbd95447b,// 42 MFM  14 

    0x54561b2b,// 43 MFM  15 

    0x9bb29f2f,// 44 MFM  16 

/// BDA is 504 words. 

/// BDA size     is 2011 (0x7db) 

/// BDA id       is 0xda48 

    0x07dbda48,// 45 BDA   1 

/// PAY Generic Data size   : 2011 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0x96c6c923,// 46 PAY   1 

    0x242fc1bc,// 47 PAY   2 

    0xd72c3874,// 48 PAY   3 

    0x5d9e80fd,// 49 PAY   4 

    0xc6488417,// 50 PAY   5 

    0xdf21fc07,// 51 PAY   6 

    0x279ed917,// 52 PAY   7 

    0x13e878e6,// 53 PAY   8 

    0xcacdc0fa,// 54 PAY   9 

    0xebbefbc5,// 55 PAY  10 

    0xb8e08913,// 56 PAY  11 

    0x6ae3434d,// 57 PAY  12 

    0xd055ea99,// 58 PAY  13 

    0xb5d3230a,// 59 PAY  14 

    0xd611ea53,// 60 PAY  15 

    0x093ed743,// 61 PAY  16 

    0xd41734c8,// 62 PAY  17 

    0xa5f6fec5,// 63 PAY  18 

    0x31d12bd1,// 64 PAY  19 

    0xc66cef9a,// 65 PAY  20 

    0x1bd474c3,// 66 PAY  21 

    0xe167ce65,// 67 PAY  22 

    0x65d131f7,// 68 PAY  23 

    0xbc01a531,// 69 PAY  24 

    0x187c6667,// 70 PAY  25 

    0x9a4e2e06,// 71 PAY  26 

    0x76b0ba6e,// 72 PAY  27 

    0x2b802dec,// 73 PAY  28 

    0x4ff9a710,// 74 PAY  29 

    0xd4d393d0,// 75 PAY  30 

    0x07ac284f,// 76 PAY  31 

    0x15030c19,// 77 PAY  32 

    0x2b759696,// 78 PAY  33 

    0x1844a57c,// 79 PAY  34 

    0x59b66167,// 80 PAY  35 

    0xfd19bd12,// 81 PAY  36 

    0xa5b216b1,// 82 PAY  37 

    0x3fab2c80,// 83 PAY  38 

    0x4e8bb1fc,// 84 PAY  39 

    0x88adecbc,// 85 PAY  40 

    0x3deee97f,// 86 PAY  41 

    0x66ae52b8,// 87 PAY  42 

    0x425b5aba,// 88 PAY  43 

    0x57dbb611,// 89 PAY  44 

    0x1e447008,// 90 PAY  45 

    0xefa26fdc,// 91 PAY  46 

    0xbab5e34e,// 92 PAY  47 

    0x539596d6,// 93 PAY  48 

    0xd8ceca73,// 94 PAY  49 

    0xb29db78f,// 95 PAY  50 

    0x6c523acd,// 96 PAY  51 

    0x2c209048,// 97 PAY  52 

    0x7e023831,// 98 PAY  53 

    0x9dd93a52,// 99 PAY  54 

    0xd7cdcc6a,// 100 PAY  55 

    0xfcf2ec80,// 101 PAY  56 

    0x95be0ef5,// 102 PAY  57 

    0x1a292213,// 103 PAY  58 

    0x47a326f6,// 104 PAY  59 

    0x73184150,// 105 PAY  60 

    0x8be3f614,// 106 PAY  61 

    0xe2d7e732,// 107 PAY  62 

    0xf450baf4,// 108 PAY  63 

    0x3231a5c9,// 109 PAY  64 

    0x4317aa9c,// 110 PAY  65 

    0x9e1c3cbb,// 111 PAY  66 

    0x452ddd90,// 112 PAY  67 

    0xb64bb2d0,// 113 PAY  68 

    0x84ebe5a4,// 114 PAY  69 

    0x88e14ff4,// 115 PAY  70 

    0xd6cc6346,// 116 PAY  71 

    0x2c73edc0,// 117 PAY  72 

    0xb0e11f55,// 118 PAY  73 

    0x7c113bdd,// 119 PAY  74 

    0xf837aade,// 120 PAY  75 

    0x2959e1d0,// 121 PAY  76 

    0x938c059a,// 122 PAY  77 

    0x78e6a444,// 123 PAY  78 

    0xb398f2d7,// 124 PAY  79 

    0x9eceb2c3,// 125 PAY  80 

    0xc3d1da98,// 126 PAY  81 

    0x2893fc98,// 127 PAY  82 

    0x90dfa9bd,// 128 PAY  83 

    0xc6d2111f,// 129 PAY  84 

    0x32ac05de,// 130 PAY  85 

    0xa20b1dab,// 131 PAY  86 

    0x9347234e,// 132 PAY  87 

    0xadda82f5,// 133 PAY  88 

    0x9337ded1,// 134 PAY  89 

    0xc1927c13,// 135 PAY  90 

    0x38d7a3f0,// 136 PAY  91 

    0xc605437b,// 137 PAY  92 

    0x78b6c58b,// 138 PAY  93 

    0x7f860ded,// 139 PAY  94 

    0x6940d2b1,// 140 PAY  95 

    0x31508b08,// 141 PAY  96 

    0xe36f18ea,// 142 PAY  97 

    0x478520bc,// 143 PAY  98 

    0x6b1b68f4,// 144 PAY  99 

    0xb9c6a331,// 145 PAY 100 

    0xd34cae72,// 146 PAY 101 

    0xb2f31dee,// 147 PAY 102 

    0xde18beda,// 148 PAY 103 

    0xbf5d63f4,// 149 PAY 104 

    0xd8a26cea,// 150 PAY 105 

    0x224630bd,// 151 PAY 106 

    0xb9bc71c1,// 152 PAY 107 

    0x8b284107,// 153 PAY 108 

    0x90713570,// 154 PAY 109 

    0x969afc99,// 155 PAY 110 

    0x1dca7df7,// 156 PAY 111 

    0xc5204b46,// 157 PAY 112 

    0x285632af,// 158 PAY 113 

    0x1c8fbcf6,// 159 PAY 114 

    0xe36aea93,// 160 PAY 115 

    0x3b6b8eb6,// 161 PAY 116 

    0x27958877,// 162 PAY 117 

    0xb7ca9c97,// 163 PAY 118 

    0x630cc3e8,// 164 PAY 119 

    0xd467bb4a,// 165 PAY 120 

    0xd639a5f0,// 166 PAY 121 

    0xa5f2f909,// 167 PAY 122 

    0xf7d15f70,// 168 PAY 123 

    0x727d44f0,// 169 PAY 124 

    0xfb2b9e55,// 170 PAY 125 

    0xbb9b2d45,// 171 PAY 126 

    0x5ae8008b,// 172 PAY 127 

    0x0785d2b3,// 173 PAY 128 

    0x16452d8f,// 174 PAY 129 

    0xd8e67bb9,// 175 PAY 130 

    0x37314b27,// 176 PAY 131 

    0x96e1334a,// 177 PAY 132 

    0x45699698,// 178 PAY 133 

    0x9b8cbdf8,// 179 PAY 134 

    0xc63418c4,// 180 PAY 135 

    0xd92b1331,// 181 PAY 136 

    0x3cccb362,// 182 PAY 137 

    0x76688afa,// 183 PAY 138 

    0xa7eca16c,// 184 PAY 139 

    0x73b127af,// 185 PAY 140 

    0x38047244,// 186 PAY 141 

    0xe4c80ed9,// 187 PAY 142 

    0x33986ab5,// 188 PAY 143 

    0x363692d5,// 189 PAY 144 

    0xaf74a572,// 190 PAY 145 

    0x9c7a20f8,// 191 PAY 146 

    0x98eaa150,// 192 PAY 147 

    0x0262cb53,// 193 PAY 148 

    0xe409b369,// 194 PAY 149 

    0x03632373,// 195 PAY 150 

    0x9eeaef2c,// 196 PAY 151 

    0x12006d53,// 197 PAY 152 

    0x493742f8,// 198 PAY 153 

    0x07882d12,// 199 PAY 154 

    0x58458820,// 200 PAY 155 

    0xe9d4c55f,// 201 PAY 156 

    0x5a5778ea,// 202 PAY 157 

    0x7b065672,// 203 PAY 158 

    0x425b7288,// 204 PAY 159 

    0xfe5da59e,// 205 PAY 160 

    0xbf81c5b9,// 206 PAY 161 

    0x2cdd14d9,// 207 PAY 162 

    0x2e0d50d8,// 208 PAY 163 

    0x4338e6e0,// 209 PAY 164 

    0x5b771614,// 210 PAY 165 

    0x611fbf37,// 211 PAY 166 

    0x7e87142a,// 212 PAY 167 

    0x0547a45b,// 213 PAY 168 

    0x86431373,// 214 PAY 169 

    0x40e51aef,// 215 PAY 170 

    0xec5f839a,// 216 PAY 171 

    0x5cddd369,// 217 PAY 172 

    0x55d44b14,// 218 PAY 173 

    0x886abd97,// 219 PAY 174 

    0x3b4d1904,// 220 PAY 175 

    0xf127d206,// 221 PAY 176 

    0x462731e1,// 222 PAY 177 

    0xc5045ae9,// 223 PAY 178 

    0xcf1198ef,// 224 PAY 179 

    0x62403f0d,// 225 PAY 180 

    0x25007392,// 226 PAY 181 

    0x33f1e7ea,// 227 PAY 182 

    0x27869f27,// 228 PAY 183 

    0x8b9d6c2b,// 229 PAY 184 

    0x0885ce8e,// 230 PAY 185 

    0x30fd8788,// 231 PAY 186 

    0x640d05e3,// 232 PAY 187 

    0xdb2d701f,// 233 PAY 188 

    0xec94e48c,// 234 PAY 189 

    0xe3cfa226,// 235 PAY 190 

    0xe36c3633,// 236 PAY 191 

    0xbbbb9e69,// 237 PAY 192 

    0x8e8091b7,// 238 PAY 193 

    0xbc2491cb,// 239 PAY 194 

    0xc4566458,// 240 PAY 195 

    0xa2c61176,// 241 PAY 196 

    0x0f4d4b79,// 242 PAY 197 

    0xdb61fe45,// 243 PAY 198 

    0xfe26ee0c,// 244 PAY 199 

    0x0738dec7,// 245 PAY 200 

    0xe8317396,// 246 PAY 201 

    0xd1ba58e1,// 247 PAY 202 

    0x5245ec15,// 248 PAY 203 

    0xdaa0bed3,// 249 PAY 204 

    0xa2629e2b,// 250 PAY 205 

    0x3227d8aa,// 251 PAY 206 

    0x92f70ff2,// 252 PAY 207 

    0x8964c418,// 253 PAY 208 

    0x3f8e8932,// 254 PAY 209 

    0x4211f516,// 255 PAY 210 

    0xc6fde3a6,// 256 PAY 211 

    0x3e791c6a,// 257 PAY 212 

    0xd62724ae,// 258 PAY 213 

    0x076d3787,// 259 PAY 214 

    0xdc18dce3,// 260 PAY 215 

    0xc0f1fec2,// 261 PAY 216 

    0x28480a31,// 262 PAY 217 

    0x070a7449,// 263 PAY 218 

    0x9f2efb13,// 264 PAY 219 

    0x018b7a9b,// 265 PAY 220 

    0xbf2f2d42,// 266 PAY 221 

    0x40e4a6d2,// 267 PAY 222 

    0xee05fd1e,// 268 PAY 223 

    0xe60d5386,// 269 PAY 224 

    0x44b87038,// 270 PAY 225 

    0x174ac1e2,// 271 PAY 226 

    0x646bb304,// 272 PAY 227 

    0xa8390ea0,// 273 PAY 228 

    0xb66f97e5,// 274 PAY 229 

    0xea44a70c,// 275 PAY 230 

    0x637a84ba,// 276 PAY 231 

    0x43a64490,// 277 PAY 232 

    0x2244589b,// 278 PAY 233 

    0xdaee930b,// 279 PAY 234 

    0xbb708072,// 280 PAY 235 

    0xa95ba3af,// 281 PAY 236 

    0xc9ded651,// 282 PAY 237 

    0x4271f221,// 283 PAY 238 

    0xa7de8168,// 284 PAY 239 

    0x716072cb,// 285 PAY 240 

    0x4114987f,// 286 PAY 241 

    0x684ec04c,// 287 PAY 242 

    0xb93184ac,// 288 PAY 243 

    0x85eafe1e,// 289 PAY 244 

    0x5d75e417,// 290 PAY 245 

    0x79e2d91c,// 291 PAY 246 

    0xadfdea8a,// 292 PAY 247 

    0xedaf9584,// 293 PAY 248 

    0x8443e033,// 294 PAY 249 

    0xf000245d,// 295 PAY 250 

    0xdc5ec11a,// 296 PAY 251 

    0xd69318ae,// 297 PAY 252 

    0x9e74b65b,// 298 PAY 253 

    0x6630a630,// 299 PAY 254 

    0x3c334fb3,// 300 PAY 255 

    0x0223716c,// 301 PAY 256 

    0xb9db00f9,// 302 PAY 257 

    0xc60d2447,// 303 PAY 258 

    0x78847979,// 304 PAY 259 

    0x59854365,// 305 PAY 260 

    0x1d402266,// 306 PAY 261 

    0x36b057ba,// 307 PAY 262 

    0x228b9efc,// 308 PAY 263 

    0xfa7a7af2,// 309 PAY 264 

    0x4d391700,// 310 PAY 265 

    0x5205dc9e,// 311 PAY 266 

    0x199792e1,// 312 PAY 267 

    0x777e2a6d,// 313 PAY 268 

    0x0b8a6b71,// 314 PAY 269 

    0xecaa29ac,// 315 PAY 270 

    0x46e82704,// 316 PAY 271 

    0x7a3e7f99,// 317 PAY 272 

    0xe736a961,// 318 PAY 273 

    0x61356204,// 319 PAY 274 

    0xfbba9f5c,// 320 PAY 275 

    0xcebe95ad,// 321 PAY 276 

    0xb53e57b1,// 322 PAY 277 

    0xc0c4a3d2,// 323 PAY 278 

    0xffef571c,// 324 PAY 279 

    0x1f4d8558,// 325 PAY 280 

    0x3b30c0e9,// 326 PAY 281 

    0x9ca34205,// 327 PAY 282 

    0x7e5958ed,// 328 PAY 283 

    0xedd72295,// 329 PAY 284 

    0x7bc59782,// 330 PAY 285 

    0x0abecede,// 331 PAY 286 

    0x5b962dba,// 332 PAY 287 

    0xfdb7a062,// 333 PAY 288 

    0x69ebb806,// 334 PAY 289 

    0x35c90093,// 335 PAY 290 

    0xca3e3442,// 336 PAY 291 

    0x704d8928,// 337 PAY 292 

    0xe5062988,// 338 PAY 293 

    0xc85695a7,// 339 PAY 294 

    0x268f9cf4,// 340 PAY 295 

    0x6516aa45,// 341 PAY 296 

    0x4b092b04,// 342 PAY 297 

    0x713ae8f8,// 343 PAY 298 

    0xd8b15ff0,// 344 PAY 299 

    0x64511f90,// 345 PAY 300 

    0xe37a23e2,// 346 PAY 301 

    0x4c8c0526,// 347 PAY 302 

    0xb25b1b36,// 348 PAY 303 

    0x2e368e35,// 349 PAY 304 

    0x4cbd1c30,// 350 PAY 305 

    0x4966814a,// 351 PAY 306 

    0xb5c3984f,// 352 PAY 307 

    0x5c05895a,// 353 PAY 308 

    0xf5816f30,// 354 PAY 309 

    0x5c233c97,// 355 PAY 310 

    0x328aba75,// 356 PAY 311 

    0x2bbbb667,// 357 PAY 312 

    0x04a33793,// 358 PAY 313 

    0x91a9b728,// 359 PAY 314 

    0xa7afb07a,// 360 PAY 315 

    0x50ca47c0,// 361 PAY 316 

    0xd8b2434f,// 362 PAY 317 

    0x409ee1e2,// 363 PAY 318 

    0x498d0d13,// 364 PAY 319 

    0x824cf0ca,// 365 PAY 320 

    0xea73bf80,// 366 PAY 321 

    0x155fced0,// 367 PAY 322 

    0x16a0cfe6,// 368 PAY 323 

    0x8243fc51,// 369 PAY 324 

    0x4022fd2b,// 370 PAY 325 

    0x573cedfd,// 371 PAY 326 

    0xcb5ddbd1,// 372 PAY 327 

    0x785b0ed5,// 373 PAY 328 

    0x9dd0ac68,// 374 PAY 329 

    0xe836fbd4,// 375 PAY 330 

    0x4d1a0bdb,// 376 PAY 331 

    0x9f2dcff8,// 377 PAY 332 

    0x8b933536,// 378 PAY 333 

    0x7470cc67,// 379 PAY 334 

    0x62e77802,// 380 PAY 335 

    0xdc5e5832,// 381 PAY 336 

    0x476367aa,// 382 PAY 337 

    0xd802cbc4,// 383 PAY 338 

    0x08bf93f4,// 384 PAY 339 

    0xab9f5bd6,// 385 PAY 340 

    0x2108c7af,// 386 PAY 341 

    0x81a95649,// 387 PAY 342 

    0xff7bdcb1,// 388 PAY 343 

    0xc79c64eb,// 389 PAY 344 

    0xd7c393e6,// 390 PAY 345 

    0x28db3a6a,// 391 PAY 346 

    0x777fad5a,// 392 PAY 347 

    0x995bcf49,// 393 PAY 348 

    0x10021218,// 394 PAY 349 

    0x8a419795,// 395 PAY 350 

    0x04cf6c62,// 396 PAY 351 

    0x150bf2f1,// 397 PAY 352 

    0x4ea52386,// 398 PAY 353 

    0xf876e793,// 399 PAY 354 

    0xe1d5d29a,// 400 PAY 355 

    0xc9d67894,// 401 PAY 356 

    0x07427658,// 402 PAY 357 

    0xa9ea0d90,// 403 PAY 358 

    0xca014eba,// 404 PAY 359 

    0x12b15e2a,// 405 PAY 360 

    0x201f5fec,// 406 PAY 361 

    0xe3134bae,// 407 PAY 362 

    0x72130bf8,// 408 PAY 363 

    0x3cc924b4,// 409 PAY 364 

    0x76265101,// 410 PAY 365 

    0x0cfe5d03,// 411 PAY 366 

    0x651a6255,// 412 PAY 367 

    0x0629de60,// 413 PAY 368 

    0x6b053c20,// 414 PAY 369 

    0x93c2c846,// 415 PAY 370 

    0x3157ee89,// 416 PAY 371 

    0x522d2598,// 417 PAY 372 

    0xb3799ec3,// 418 PAY 373 

    0x980be56c,// 419 PAY 374 

    0x96f9f44a,// 420 PAY 375 

    0x80a92b71,// 421 PAY 376 

    0x5775e5e0,// 422 PAY 377 

    0xcef61f3c,// 423 PAY 378 

    0x4ddf05df,// 424 PAY 379 

    0xd04a4101,// 425 PAY 380 

    0xea59f074,// 426 PAY 381 

    0xcbdddeb6,// 427 PAY 382 

    0xe2714d19,// 428 PAY 383 

    0x8e3efa40,// 429 PAY 384 

    0x7236529d,// 430 PAY 385 

    0x6d74db25,// 431 PAY 386 

    0x2087dcb5,// 432 PAY 387 

    0xcbd87c15,// 433 PAY 388 

    0x30311473,// 434 PAY 389 

    0x49d723ce,// 435 PAY 390 

    0xddcc1723,// 436 PAY 391 

    0x391b5636,// 437 PAY 392 

    0xb2bdee3f,// 438 PAY 393 

    0x2d7fbc9d,// 439 PAY 394 

    0xae8c8fa1,// 440 PAY 395 

    0x8b353883,// 441 PAY 396 

    0x6ee0dc02,// 442 PAY 397 

    0x4b7f16e5,// 443 PAY 398 

    0x2d8f014c,// 444 PAY 399 

    0x609e3e79,// 445 PAY 400 

    0xf1a7405c,// 446 PAY 401 

    0x193b8f5f,// 447 PAY 402 

    0x64bd5ca0,// 448 PAY 403 

    0xe50938e2,// 449 PAY 404 

    0xcfc5b8e5,// 450 PAY 405 

    0xd8959317,// 451 PAY 406 

    0x2ed36dc3,// 452 PAY 407 

    0x7cfa32f3,// 453 PAY 408 

    0x60adc777,// 454 PAY 409 

    0x598eb1a3,// 455 PAY 410 

    0xaf49a61e,// 456 PAY 411 

    0x041193e7,// 457 PAY 412 

    0x11385dd0,// 458 PAY 413 

    0x4d6921b3,// 459 PAY 414 

    0xa0e68ddc,// 460 PAY 415 

    0x799e7c8f,// 461 PAY 416 

    0x2fd75c97,// 462 PAY 417 

    0x344253c6,// 463 PAY 418 

    0x45a9f4ae,// 464 PAY 419 

    0x8d669b85,// 465 PAY 420 

    0xac032eac,// 466 PAY 421 

    0x4482366b,// 467 PAY 422 

    0x6dfd82c6,// 468 PAY 423 

    0xbe39fdd8,// 469 PAY 424 

    0x8c5beff2,// 470 PAY 425 

    0x7ce14dc5,// 471 PAY 426 

    0x7b3b8f59,// 472 PAY 427 

    0x289e9d7e,// 473 PAY 428 

    0x6a5bf21e,// 474 PAY 429 

    0x5fcff832,// 475 PAY 430 

    0xa7af6f3a,// 476 PAY 431 

    0xf6be0584,// 477 PAY 432 

    0x456616a2,// 478 PAY 433 

    0x086744cb,// 479 PAY 434 

    0x7eeab153,// 480 PAY 435 

    0x39e32d65,// 481 PAY 436 

    0xd046cbcd,// 482 PAY 437 

    0xa7fed317,// 483 PAY 438 

    0x48f8101e,// 484 PAY 439 

    0x10bc5bb3,// 485 PAY 440 

    0xd3453575,// 486 PAY 441 

    0xae9e03c1,// 487 PAY 442 

    0x562d155b,// 488 PAY 443 

    0x85ce7503,// 489 PAY 444 

    0x9f2e65a9,// 490 PAY 445 

    0xf42d5c15,// 491 PAY 446 

    0x8b602445,// 492 PAY 447 

    0xa7cd6983,// 493 PAY 448 

    0x22c9988b,// 494 PAY 449 

    0x12765876,// 495 PAY 450 

    0x38784a36,// 496 PAY 451 

    0x89de0dfa,// 497 PAY 452 

    0x889fafe2,// 498 PAY 453 

    0x827188fb,// 499 PAY 454 

    0x3675cb2f,// 500 PAY 455 

    0x57f2af32,// 501 PAY 456 

    0x3cc0d9a1,// 502 PAY 457 

    0xa0d39adf,// 503 PAY 458 

    0x3b5fbbf3,// 504 PAY 459 

    0xd31c4544,// 505 PAY 460 

    0x0b236ed4,// 506 PAY 461 

    0xddeaea33,// 507 PAY 462 

    0x62f0fbff,// 508 PAY 463 

    0x5296a89b,// 509 PAY 464 

    0x9cb418f0,// 510 PAY 465 

    0xc4148163,// 511 PAY 466 

    0x2f105c27,// 512 PAY 467 

    0x660b7c07,// 513 PAY 468 

    0x01643565,// 514 PAY 469 

    0x9c9413d5,// 515 PAY 470 

    0xdc99ac87,// 516 PAY 471 

    0xb582ef6e,// 517 PAY 472 

    0xac083e08,// 518 PAY 473 

    0xed721e13,// 519 PAY 474 

    0x7c278727,// 520 PAY 475 

    0x25b54e66,// 521 PAY 476 

    0xc42eba64,// 522 PAY 477 

    0xac74e8cc,// 523 PAY 478 

    0x3c971f62,// 524 PAY 479 

    0x73bb0ff2,// 525 PAY 480 

    0xc368fe1a,// 526 PAY 481 

    0x89aacac6,// 527 PAY 482 

    0x818263ec,// 528 PAY 483 

    0xc770234f,// 529 PAY 484 

    0x8d15136c,// 530 PAY 485 

    0x37b995ff,// 531 PAY 486 

    0xd3f8f764,// 532 PAY 487 

    0x261ade06,// 533 PAY 488 

    0xf8868496,// 534 PAY 489 

    0x71e65046,// 535 PAY 490 

    0x6c1bd15c,// 536 PAY 491 

    0xd74da15c,// 537 PAY 492 

    0x3d4812ba,// 538 PAY 493 

    0x276a0159,// 539 PAY 494 

    0x4f676751,// 540 PAY 495 

    0x065e26da,// 541 PAY 496 

    0xd8260b87,// 542 PAY 497 

    0x89bd941f,// 543 PAY 498 

    0x50f97e4d,// 544 PAY 499 

    0x8d428774,// 545 PAY 500 

    0xbc55ea8a,// 546 PAY 501 

    0x94ccb5b2,// 547 PAY 502 

    0x1e82ad00,// 548 PAY 503 

/// STA is 1 words. 

/// STA num_pkts       : 178 

/// STA pkt_idx        : 254 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x32 

    0x03f932b2 // 549 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 80 (0x50) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt37_tmpl[] = {
    0xb8010050,// 1 CCH   1 

/// ECH cache_idx      : 0x0b 

/// ECH pdu_tag        : 0x00 

    0x000b0000,// 2 ECH   1 

/// SCX is 19 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000013,// 3 SCX   1 

    0x808148cd,// 4 SCX   2 

    0x00004100,// 5 SCX   3 

    0x1ca850d0,// 6 SCX   4 

    0xe74abff4,// 7 SCX   5 

    0x4ac3b173,// 8 SCX   6 

    0xadd0b928,// 9 SCX   7 

    0x1d629380,// 10 SCX   8 

    0x015e08e6,// 11 SCX   9 

    0x75f8749c,// 12 SCX  10 

    0xccc60f11,// 13 SCX  11 

    0x09d59da7,// 14 SCX  12 

    0xca85e5b3,// 15 SCX  13 

    0x1703b2d3,// 16 SCX  14 

    0x573534c0,// 17 SCX  15 

    0x8b65f9d8,// 18 SCX  16 

    0xc452f034,// 19 SCX  17 

    0x73fe2ee3,// 20 SCX  18 

    0xf8714a24,// 21 SCX  19 

/// BFD is 3 words. 

/// BFD tot_len        : 261 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 190 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 190 

/// BFD lencrypto      : 112 

/// BFD ofstcrypto     : 40 

/// BFD (ofst+len)cry  : 152 

/// BFD ofstiv         : 0 

/// BFD ofsticv        : 224 

    0x000000be,// 22 BFD   1 

    0x00280070,// 23 BFD   2 

    0x00e00000,// 24 BFD   3 

/// MFM is 5 words. 

/// MFM vldnibs        : 20 

    0x20008c7e,// 25 MFM   1 

    0xc39e7679,// 26 MFM   2 

    0x7e77c09f,// 27 MFM   3 

    0x58b7112e,// 28 MFM   4 

    0x03760000,// 29 MFM   5 

/// BDA is 67 words. 

/// BDA size     is 261 (0x105) 

/// BDA id       is 0x1608 

    0x01051608,// 30 BDA   1 

/// PAY Generic Data size   : 261 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x26f42cad,// 31 PAY   1 

    0x16bb4f67,// 32 PAY   2 

    0x71bcb186,// 33 PAY   3 

    0x75e59f9a,// 34 PAY   4 

    0xd165d466,// 35 PAY   5 

    0x56b7e8f2,// 36 PAY   6 

    0x46838d6d,// 37 PAY   7 

    0xc17766d1,// 38 PAY   8 

    0xde366c32,// 39 PAY   9 

    0x74d6a101,// 40 PAY  10 

    0x50fe625d,// 41 PAY  11 

    0x6730b20e,// 42 PAY  12 

    0xb8ba895b,// 43 PAY  13 

    0x4ae65f0a,// 44 PAY  14 

    0xb592af7a,// 45 PAY  15 

    0xb5d1137f,// 46 PAY  16 

    0xf43e6766,// 47 PAY  17 

    0x67298d96,// 48 PAY  18 

    0xda2ccc91,// 49 PAY  19 

    0x85993013,// 50 PAY  20 

    0xad398b3c,// 51 PAY  21 

    0x7405f902,// 52 PAY  22 

    0xc540210a,// 53 PAY  23 

    0xa85af2ec,// 54 PAY  24 

    0x9a63e0c6,// 55 PAY  25 

    0xd49f545c,// 56 PAY  26 

    0x26e99f79,// 57 PAY  27 

    0x3bcf7d62,// 58 PAY  28 

    0x44e78878,// 59 PAY  29 

    0xe680d19a,// 60 PAY  30 

    0x8d10ead5,// 61 PAY  31 

    0xa401fd6c,// 62 PAY  32 

    0x3a1c2fa9,// 63 PAY  33 

    0x19ba0d62,// 64 PAY  34 

    0xd1089c81,// 65 PAY  35 

    0x358a5334,// 66 PAY  36 

    0x1ecd4abb,// 67 PAY  37 

    0x4d37746d,// 68 PAY  38 

    0x12d3e180,// 69 PAY  39 

    0x4e27fea8,// 70 PAY  40 

    0x9c2a3f82,// 71 PAY  41 

    0x21665265,// 72 PAY  42 

    0xec1b3d84,// 73 PAY  43 

    0x409e2e81,// 74 PAY  44 

    0xc4924d39,// 75 PAY  45 

    0x6d10b6be,// 76 PAY  46 

    0xc3706033,// 77 PAY  47 

    0x7d6106e7,// 78 PAY  48 

    0x7e13c48f,// 79 PAY  49 

    0x6a86327c,// 80 PAY  50 

    0x672ac703,// 81 PAY  51 

    0xa2fe3488,// 82 PAY  52 

    0xf407aa95,// 83 PAY  53 

    0xc1dbfa38,// 84 PAY  54 

    0xadc0c315,// 85 PAY  55 

    0xa862de1d,// 86 PAY  56 

    0xc0f57c86,// 87 PAY  57 

    0x92d09a8f,// 88 PAY  58 

    0xb7cdc9c6,// 89 PAY  59 

    0xb95886a4,// 90 PAY  60 

    0x5e226bc8,// 91 PAY  61 

    0x344dc815,// 92 PAY  62 

    0xfd3d44a2,// 93 PAY  63 

    0x5cd7294c,// 94 PAY  64 

    0x91a5d416,// 95 PAY  65 

    0x2b000000,// 96 PAY  66 

/// STA is 1 words. 

/// STA num_pkts       : 164 

/// STA pkt_idx        : 88 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xbe 

    0x0161bea4 // 97 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc !incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt38_tmpl[] = {
    0xa8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x06 

/// ECH pdu_tag        : 0x00 

    0x00060000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000015,// 3 SCX   1 

    0x8084480c,// 4 SCX   2 

    0x000025c4,// 5 SCX   3 

    0x6f4a946a,// 6 SCX   4 

    0xcb60c496,// 7 SCX   5 

    0x1b3e5ed9,// 8 SCX   6 

    0x02d6bf71,// 9 SCX   7 

    0x2b1c463d,// 10 SCX   8 

    0x38598d95,// 11 SCX   9 

    0xd9df876d,// 12 SCX  10 

    0xe8537f3e,// 13 SCX  11 

    0x195d0fb5,// 14 SCX  12 

    0x681ff0ad,// 15 SCX  13 

    0x53adde40,// 16 SCX  14 

    0xae60f251,// 17 SCX  15 

    0x787b16c6,// 18 SCX  16 

    0xb1219c6b,// 19 SCX  17 

    0x7947b9d9,// 20 SCX  18 

    0x15f42467,// 21 SCX  19 

    0x00df5e97,// 22 SCX  20 

    0x31a46e1b,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 2019 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 1357 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1357 

/// BFD lencrypto      : 208 

/// BFD ofstcrypto     : 656 

/// BFD (ofst+len)cry  : 864 

/// BFD ofstiv         : 36 

/// BFD ofsticv        : 1692 

    0x0000054d,// 24 BFD   1 

    0x029000d0,// 25 BFD   2 

    0x069c0024,// 26 BFD   3 

/// BDA is 506 words. 

/// BDA size     is 2019 (0x7e3) 

/// BDA id       is 0x1528 

    0x07e31528,// 27 BDA   1 

/// PAY Generic Data size   : 2019 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0x53b7195f,// 28 PAY   1 

    0xb51e615f,// 29 PAY   2 

    0xd2df75e6,// 30 PAY   3 

    0x3acf6003,// 31 PAY   4 

    0x11493995,// 32 PAY   5 

    0x2cd21b65,// 33 PAY   6 

    0x623fe049,// 34 PAY   7 

    0x387c8b2e,// 35 PAY   8 

    0x10f56049,// 36 PAY   9 

    0xe6186814,// 37 PAY  10 

    0x296a24ff,// 38 PAY  11 

    0xc449402b,// 39 PAY  12 

    0x73c55340,// 40 PAY  13 

    0xed6f0ee3,// 41 PAY  14 

    0x4b4d2989,// 42 PAY  15 

    0x1d4a05e8,// 43 PAY  16 

    0xd25b03e1,// 44 PAY  17 

    0x693faf82,// 45 PAY  18 

    0x688edf7b,// 46 PAY  19 

    0x720add7c,// 47 PAY  20 

    0xe800ee21,// 48 PAY  21 

    0x3ab19435,// 49 PAY  22 

    0xa69f2859,// 50 PAY  23 

    0x006e247e,// 51 PAY  24 

    0x3b917cea,// 52 PAY  25 

    0x0222158e,// 53 PAY  26 

    0x89f82a52,// 54 PAY  27 

    0xe8a053fd,// 55 PAY  28 

    0x072c16a1,// 56 PAY  29 

    0x5d56af15,// 57 PAY  30 

    0x821e5e31,// 58 PAY  31 

    0x9ef7a70b,// 59 PAY  32 

    0xf509ac55,// 60 PAY  33 

    0xbcdc2e47,// 61 PAY  34 

    0x19e839f0,// 62 PAY  35 

    0x9d1ef204,// 63 PAY  36 

    0xd219283c,// 64 PAY  37 

    0x36594562,// 65 PAY  38 

    0x32e17291,// 66 PAY  39 

    0xd62f78c5,// 67 PAY  40 

    0xd141b980,// 68 PAY  41 

    0x66cab2ab,// 69 PAY  42 

    0xd9fae650,// 70 PAY  43 

    0xda460d6f,// 71 PAY  44 

    0xae8fb276,// 72 PAY  45 

    0x65e16c69,// 73 PAY  46 

    0x1e42b923,// 74 PAY  47 

    0xd11334d8,// 75 PAY  48 

    0xeeff41d9,// 76 PAY  49 

    0x71f186da,// 77 PAY  50 

    0x9294d02d,// 78 PAY  51 

    0xb701c2a5,// 79 PAY  52 

    0xe2b3eb0d,// 80 PAY  53 

    0x06907c6b,// 81 PAY  54 

    0x82302d8e,// 82 PAY  55 

    0x3c4fab63,// 83 PAY  56 

    0x4c7417d9,// 84 PAY  57 

    0x265850fa,// 85 PAY  58 

    0x97a84cd9,// 86 PAY  59 

    0x4115d20d,// 87 PAY  60 

    0x4a8fd5c4,// 88 PAY  61 

    0x03f1d461,// 89 PAY  62 

    0x3fe00874,// 90 PAY  63 

    0x23f810ee,// 91 PAY  64 

    0x02772939,// 92 PAY  65 

    0xf28163a0,// 93 PAY  66 

    0xd281652d,// 94 PAY  67 

    0x26caee56,// 95 PAY  68 

    0x4647be7c,// 96 PAY  69 

    0x7e48d899,// 97 PAY  70 

    0x9ffe818e,// 98 PAY  71 

    0xf1ad5475,// 99 PAY  72 

    0x85792f28,// 100 PAY  73 

    0x2e6578aa,// 101 PAY  74 

    0x780dc5ae,// 102 PAY  75 

    0xb73e9be6,// 103 PAY  76 

    0x3c2c7ea2,// 104 PAY  77 

    0x85292175,// 105 PAY  78 

    0x4c0de51d,// 106 PAY  79 

    0xa996d186,// 107 PAY  80 

    0xab372122,// 108 PAY  81 

    0xefd8a713,// 109 PAY  82 

    0x8d5adb3c,// 110 PAY  83 

    0xed60631d,// 111 PAY  84 

    0xe8ab2eb5,// 112 PAY  85 

    0x53f279bd,// 113 PAY  86 

    0x7633504d,// 114 PAY  87 

    0x6db0be43,// 115 PAY  88 

    0x468ce3a1,// 116 PAY  89 

    0x0c20627e,// 117 PAY  90 

    0x413d3dfa,// 118 PAY  91 

    0xfce2e5e0,// 119 PAY  92 

    0x78b13086,// 120 PAY  93 

    0xcff4181e,// 121 PAY  94 

    0x5c0bb034,// 122 PAY  95 

    0x153ca351,// 123 PAY  96 

    0xe57f88b1,// 124 PAY  97 

    0x9a8de605,// 125 PAY  98 

    0x2ce4f7eb,// 126 PAY  99 

    0x5bd20c2e,// 127 PAY 100 

    0xb0d75b35,// 128 PAY 101 

    0x87827035,// 129 PAY 102 

    0x60200d67,// 130 PAY 103 

    0x189dba77,// 131 PAY 104 

    0xe3073364,// 132 PAY 105 

    0xb670e29b,// 133 PAY 106 

    0x4715d7a1,// 134 PAY 107 

    0x64c562ee,// 135 PAY 108 

    0xdb864df9,// 136 PAY 109 

    0x6995f71e,// 137 PAY 110 

    0x28ee0cf7,// 138 PAY 111 

    0xe9720378,// 139 PAY 112 

    0xe741f744,// 140 PAY 113 

    0xcf38d564,// 141 PAY 114 

    0xf15b9367,// 142 PAY 115 

    0x033ca801,// 143 PAY 116 

    0x024bc96d,// 144 PAY 117 

    0x5c7a9c37,// 145 PAY 118 

    0x2d55fb40,// 146 PAY 119 

    0x93d42c3b,// 147 PAY 120 

    0x620881d9,// 148 PAY 121 

    0xdae23778,// 149 PAY 122 

    0x083d47fa,// 150 PAY 123 

    0xf43117d4,// 151 PAY 124 

    0x8cc59730,// 152 PAY 125 

    0x8ed6e7cf,// 153 PAY 126 

    0xdb8918c7,// 154 PAY 127 

    0xc7120b01,// 155 PAY 128 

    0xdb2ce2c1,// 156 PAY 129 

    0x7c57a491,// 157 PAY 130 

    0xe6b1892c,// 158 PAY 131 

    0xd6faba16,// 159 PAY 132 

    0x8a8b8d07,// 160 PAY 133 

    0xf44baee7,// 161 PAY 134 

    0x47b33743,// 162 PAY 135 

    0x9622831d,// 163 PAY 136 

    0xef61d23f,// 164 PAY 137 

    0xe6a63587,// 165 PAY 138 

    0xbf2eea9f,// 166 PAY 139 

    0x9089d1bd,// 167 PAY 140 

    0xfe66a3ef,// 168 PAY 141 

    0xe0d2e7fb,// 169 PAY 142 

    0x9753e0ba,// 170 PAY 143 

    0x4ced21bd,// 171 PAY 144 

    0x5402124b,// 172 PAY 145 

    0x0bebf9b7,// 173 PAY 146 

    0x6a4108a4,// 174 PAY 147 

    0x06e7a17c,// 175 PAY 148 

    0x8b66b2ad,// 176 PAY 149 

    0x5c6a9934,// 177 PAY 150 

    0x4f0da627,// 178 PAY 151 

    0x2d927650,// 179 PAY 152 

    0xbdb23acc,// 180 PAY 153 

    0x497cd366,// 181 PAY 154 

    0xd8c2ea06,// 182 PAY 155 

    0x63894e4b,// 183 PAY 156 

    0x234c5d2e,// 184 PAY 157 

    0xa1e6304b,// 185 PAY 158 

    0x897d49bc,// 186 PAY 159 

    0x5e99e37f,// 187 PAY 160 

    0xaa8d298d,// 188 PAY 161 

    0xae579db8,// 189 PAY 162 

    0xdbc952ff,// 190 PAY 163 

    0x307b1815,// 191 PAY 164 

    0xf369d759,// 192 PAY 165 

    0xd2ad246b,// 193 PAY 166 

    0x9f5b2a3d,// 194 PAY 167 

    0x19d932c5,// 195 PAY 168 

    0xe8af3fc0,// 196 PAY 169 

    0x97e45523,// 197 PAY 170 

    0xf311d0c9,// 198 PAY 171 

    0x203ad469,// 199 PAY 172 

    0x3d2fbc89,// 200 PAY 173 

    0x98631b58,// 201 PAY 174 

    0xe41209dd,// 202 PAY 175 

    0x62313012,// 203 PAY 176 

    0x731b1fcc,// 204 PAY 177 

    0x4f8f1ebf,// 205 PAY 178 

    0x2e74421a,// 206 PAY 179 

    0x20e759ec,// 207 PAY 180 

    0x0bfca01c,// 208 PAY 181 

    0xed7db011,// 209 PAY 182 

    0x53c28b3d,// 210 PAY 183 

    0x74c4c485,// 211 PAY 184 

    0x8e5dfae8,// 212 PAY 185 

    0x4ed2c345,// 213 PAY 186 

    0xb5ad88ae,// 214 PAY 187 

    0x8931d337,// 215 PAY 188 

    0x1c229df4,// 216 PAY 189 

    0xf59e2045,// 217 PAY 190 

    0x6741ecdd,// 218 PAY 191 

    0xe56e748c,// 219 PAY 192 

    0xa043f2ef,// 220 PAY 193 

    0x36a59fe7,// 221 PAY 194 

    0x1b708522,// 222 PAY 195 

    0xc3b5beb7,// 223 PAY 196 

    0x62d3c922,// 224 PAY 197 

    0x0b315adf,// 225 PAY 198 

    0x02255d33,// 226 PAY 199 

    0x92f7baf5,// 227 PAY 200 

    0x06561ebe,// 228 PAY 201 

    0x2d4b5b71,// 229 PAY 202 

    0x25f6a3e3,// 230 PAY 203 

    0xb58e3e5b,// 231 PAY 204 

    0xda69c638,// 232 PAY 205 

    0xa15c62db,// 233 PAY 206 

    0x8bb4c877,// 234 PAY 207 

    0x981094f5,// 235 PAY 208 

    0x5772c71f,// 236 PAY 209 

    0x25a75b8f,// 237 PAY 210 

    0xcc691b4f,// 238 PAY 211 

    0xfddf4c4c,// 239 PAY 212 

    0xfc41f5f9,// 240 PAY 213 

    0xd97f27f9,// 241 PAY 214 

    0xeb955fdb,// 242 PAY 215 

    0x4db580be,// 243 PAY 216 

    0xa1ac62ac,// 244 PAY 217 

    0x86fdc6b6,// 245 PAY 218 

    0xed34a507,// 246 PAY 219 

    0x51ffc841,// 247 PAY 220 

    0x42f3a3a2,// 248 PAY 221 

    0x5d6af412,// 249 PAY 222 

    0x80f123b9,// 250 PAY 223 

    0x4d5f1635,// 251 PAY 224 

    0x8dc374cc,// 252 PAY 225 

    0x3a774298,// 253 PAY 226 

    0x8ca436d3,// 254 PAY 227 

    0xe27f9a8c,// 255 PAY 228 

    0xd1a3e71d,// 256 PAY 229 

    0x26cf5109,// 257 PAY 230 

    0x591d7de6,// 258 PAY 231 

    0x6e6eabdf,// 259 PAY 232 

    0x20617b89,// 260 PAY 233 

    0x99f4a0e7,// 261 PAY 234 

    0x16e873b9,// 262 PAY 235 

    0x3e9f6816,// 263 PAY 236 

    0x3a4b732b,// 264 PAY 237 

    0x3373314e,// 265 PAY 238 

    0x631c0a70,// 266 PAY 239 

    0x4cc3d4b9,// 267 PAY 240 

    0x4b3ce583,// 268 PAY 241 

    0x10d1fc0e,// 269 PAY 242 

    0x46b0f5e0,// 270 PAY 243 

    0xc1042e76,// 271 PAY 244 

    0x97a9d63a,// 272 PAY 245 

    0x495ba8fd,// 273 PAY 246 

    0x770f3f78,// 274 PAY 247 

    0x02014a83,// 275 PAY 248 

    0x87f9b7d2,// 276 PAY 249 

    0x646bf453,// 277 PAY 250 

    0xfae483d6,// 278 PAY 251 

    0xde1d00c1,// 279 PAY 252 

    0xea8fd1f6,// 280 PAY 253 

    0xfc070852,// 281 PAY 254 

    0xb756e10e,// 282 PAY 255 

    0x5a04268f,// 283 PAY 256 

    0x819964c5,// 284 PAY 257 

    0x374a08cf,// 285 PAY 258 

    0xfca99a9f,// 286 PAY 259 

    0xc32d793b,// 287 PAY 260 

    0x24cc4e08,// 288 PAY 261 

    0x38acfc82,// 289 PAY 262 

    0x3cf85c8b,// 290 PAY 263 

    0x99c5c357,// 291 PAY 264 

    0x69fd49b5,// 292 PAY 265 

    0xc9a15161,// 293 PAY 266 

    0xed60056d,// 294 PAY 267 

    0x3d2378f7,// 295 PAY 268 

    0x334b542e,// 296 PAY 269 

    0xe226f81d,// 297 PAY 270 

    0x2a95778f,// 298 PAY 271 

    0x691ace4d,// 299 PAY 272 

    0x7d780527,// 300 PAY 273 

    0xbe79f979,// 301 PAY 274 

    0xc4c2c52e,// 302 PAY 275 

    0xc6e8b61c,// 303 PAY 276 

    0xde37f5da,// 304 PAY 277 

    0xafc9efd3,// 305 PAY 278 

    0xc5df0b4a,// 306 PAY 279 

    0x6a888dcd,// 307 PAY 280 

    0x57314a70,// 308 PAY 281 

    0xb959f31e,// 309 PAY 282 

    0x4bad0cd8,// 310 PAY 283 

    0x29b02a8a,// 311 PAY 284 

    0x7ac08633,// 312 PAY 285 

    0xb1d71bb3,// 313 PAY 286 

    0x1847b7ab,// 314 PAY 287 

    0xf7aee9cf,// 315 PAY 288 

    0xe70581f7,// 316 PAY 289 

    0x51d818bf,// 317 PAY 290 

    0x56f80f10,// 318 PAY 291 

    0x26eece91,// 319 PAY 292 

    0x20b82882,// 320 PAY 293 

    0xdbf58f62,// 321 PAY 294 

    0xc99140e1,// 322 PAY 295 

    0xaf8612cd,// 323 PAY 296 

    0x5288e3db,// 324 PAY 297 

    0x432e756e,// 325 PAY 298 

    0x3069ccc2,// 326 PAY 299 

    0x5f65bc1f,// 327 PAY 300 

    0x8ec92b04,// 328 PAY 301 

    0x626274fb,// 329 PAY 302 

    0xba5516ed,// 330 PAY 303 

    0x4c942479,// 331 PAY 304 

    0xc1802428,// 332 PAY 305 

    0x471987d9,// 333 PAY 306 

    0xa591a105,// 334 PAY 307 

    0x1e60b280,// 335 PAY 308 

    0x2cc44562,// 336 PAY 309 

    0x5d9df1a8,// 337 PAY 310 

    0x9ccfae6e,// 338 PAY 311 

    0x2e209636,// 339 PAY 312 

    0x96ccb8f6,// 340 PAY 313 

    0xe281d869,// 341 PAY 314 

    0x6c6ed117,// 342 PAY 315 

    0x0e6edc16,// 343 PAY 316 

    0x8c2ebd92,// 344 PAY 317 

    0xd51f5818,// 345 PAY 318 

    0xc4452bc9,// 346 PAY 319 

    0x49c671e0,// 347 PAY 320 

    0x6aba6f1b,// 348 PAY 321 

    0x12efe8d9,// 349 PAY 322 

    0x6f5ce336,// 350 PAY 323 

    0xf527c7a5,// 351 PAY 324 

    0x6512b0f5,// 352 PAY 325 

    0x58faf01d,// 353 PAY 326 

    0x212ce813,// 354 PAY 327 

    0x6a18f855,// 355 PAY 328 

    0x412ab56d,// 356 PAY 329 

    0xba33e98c,// 357 PAY 330 

    0x0e582869,// 358 PAY 331 

    0x6cda8c7a,// 359 PAY 332 

    0x308565ad,// 360 PAY 333 

    0xd229816c,// 361 PAY 334 

    0x1cdecb92,// 362 PAY 335 

    0x5e3f81c2,// 363 PAY 336 

    0x1d340b65,// 364 PAY 337 

    0x6dee13c9,// 365 PAY 338 

    0xd8015b72,// 366 PAY 339 

    0xa4753683,// 367 PAY 340 

    0x7006bd14,// 368 PAY 341 

    0x4204ad51,// 369 PAY 342 

    0x42ef2112,// 370 PAY 343 

    0x705207aa,// 371 PAY 344 

    0x2837ed3e,// 372 PAY 345 

    0x1d4b5cf2,// 373 PAY 346 

    0xb9870b2a,// 374 PAY 347 

    0xf24a3c9a,// 375 PAY 348 

    0x559acd96,// 376 PAY 349 

    0x59df7c98,// 377 PAY 350 

    0x29c20c84,// 378 PAY 351 

    0xfa34a94e,// 379 PAY 352 

    0xb88b19d8,// 380 PAY 353 

    0xb259b454,// 381 PAY 354 

    0xc89cc823,// 382 PAY 355 

    0x86f637c6,// 383 PAY 356 

    0xb2a4fb85,// 384 PAY 357 

    0x1212e9e4,// 385 PAY 358 

    0x4ccaf02f,// 386 PAY 359 

    0x198a8754,// 387 PAY 360 

    0xb0302c32,// 388 PAY 361 

    0xc52d7e9e,// 389 PAY 362 

    0xfe868d5c,// 390 PAY 363 

    0x01c6031c,// 391 PAY 364 

    0x902749fe,// 392 PAY 365 

    0xd5a40491,// 393 PAY 366 

    0x1c2596d5,// 394 PAY 367 

    0x19f9c37b,// 395 PAY 368 

    0xa7492430,// 396 PAY 369 

    0xf1e85075,// 397 PAY 370 

    0xaa4df9d2,// 398 PAY 371 

    0x5ae7dbb4,// 399 PAY 372 

    0xd22dc336,// 400 PAY 373 

    0x77d0778d,// 401 PAY 374 

    0xc77e7ba7,// 402 PAY 375 

    0x48668886,// 403 PAY 376 

    0x0444beba,// 404 PAY 377 

    0x7c1566b6,// 405 PAY 378 

    0x9572c369,// 406 PAY 379 

    0xc810c267,// 407 PAY 380 

    0xd718adea,// 408 PAY 381 

    0x9c884209,// 409 PAY 382 

    0x305bdc91,// 410 PAY 383 

    0x2c0c8663,// 411 PAY 384 

    0xda02427f,// 412 PAY 385 

    0x8ba8ae45,// 413 PAY 386 

    0x989fd775,// 414 PAY 387 

    0x10dc33d7,// 415 PAY 388 

    0x480b7cd4,// 416 PAY 389 

    0x91ddbd32,// 417 PAY 390 

    0x01349f76,// 418 PAY 391 

    0xd1a4bf0f,// 419 PAY 392 

    0x5486450c,// 420 PAY 393 

    0x88331135,// 421 PAY 394 

    0xee092f0a,// 422 PAY 395 

    0xaac08b19,// 423 PAY 396 

    0xf3e4ea32,// 424 PAY 397 

    0xc3df0597,// 425 PAY 398 

    0xac9332fa,// 426 PAY 399 

    0x239f682c,// 427 PAY 400 

    0x1612e6bd,// 428 PAY 401 

    0x2a83eeeb,// 429 PAY 402 

    0x7f013d6c,// 430 PAY 403 

    0xeeed0777,// 431 PAY 404 

    0x20286fd9,// 432 PAY 405 

    0xd1373d3e,// 433 PAY 406 

    0x1805507c,// 434 PAY 407 

    0x46dee1eb,// 435 PAY 408 

    0x01e52469,// 436 PAY 409 

    0x9eb9ed98,// 437 PAY 410 

    0x8aecffe6,// 438 PAY 411 

    0x44ba3826,// 439 PAY 412 

    0x15674a20,// 440 PAY 413 

    0xb834b7e0,// 441 PAY 414 

    0xba4a4238,// 442 PAY 415 

    0xac80f7aa,// 443 PAY 416 

    0xd433ec42,// 444 PAY 417 

    0xf2246953,// 445 PAY 418 

    0xfa42dc94,// 446 PAY 419 

    0x53bd4593,// 447 PAY 420 

    0xba2eafb6,// 448 PAY 421 

    0x82994f83,// 449 PAY 422 

    0xb068fca5,// 450 PAY 423 

    0x07b9eda2,// 451 PAY 424 

    0xaf72a1da,// 452 PAY 425 

    0xa028668e,// 453 PAY 426 

    0x5c22c8e8,// 454 PAY 427 

    0xb03aec0f,// 455 PAY 428 

    0x3a56b516,// 456 PAY 429 

    0x6882a949,// 457 PAY 430 

    0xb9cf85cf,// 458 PAY 431 

    0x6e8483a7,// 459 PAY 432 

    0x8cf77005,// 460 PAY 433 

    0xce894537,// 461 PAY 434 

    0x4135a621,// 462 PAY 435 

    0x2d4188ae,// 463 PAY 436 

    0x53531091,// 464 PAY 437 

    0x39688b60,// 465 PAY 438 

    0xdeb26d52,// 466 PAY 439 

    0x07d979cb,// 467 PAY 440 

    0xe0877ffa,// 468 PAY 441 

    0x18289aa9,// 469 PAY 442 

    0x5daa4897,// 470 PAY 443 

    0x36457bd8,// 471 PAY 444 

    0x825f9e83,// 472 PAY 445 

    0xeec0fbfe,// 473 PAY 446 

    0x3f5614cc,// 474 PAY 447 

    0x74c19545,// 475 PAY 448 

    0x652dc693,// 476 PAY 449 

    0xa9f9057d,// 477 PAY 450 

    0x40df5bda,// 478 PAY 451 

    0x808b2322,// 479 PAY 452 

    0x73a7e088,// 480 PAY 453 

    0xd822b923,// 481 PAY 454 

    0x9390b118,// 482 PAY 455 

    0xfefc8113,// 483 PAY 456 

    0xde9a557a,// 484 PAY 457 

    0x81d45911,// 485 PAY 458 

    0x49d76b35,// 486 PAY 459 

    0xa114ffb0,// 487 PAY 460 

    0xf38ded73,// 488 PAY 461 

    0x8843df54,// 489 PAY 462 

    0xc5a28a87,// 490 PAY 463 

    0x875e191b,// 491 PAY 464 

    0x76b5e462,// 492 PAY 465 

    0xb3e66ddd,// 493 PAY 466 

    0x28ae2489,// 494 PAY 467 

    0xa1a7366b,// 495 PAY 468 

    0xd5d0ab39,// 496 PAY 469 

    0x6e83c124,// 497 PAY 470 

    0x5993514a,// 498 PAY 471 

    0x9553f441,// 499 PAY 472 

    0xc44bbbab,// 500 PAY 473 

    0x3442c145,// 501 PAY 474 

    0xc1eb529e,// 502 PAY 475 

    0x1773ad36,// 503 PAY 476 

    0x4ba4287d,// 504 PAY 477 

    0xd9ff0b1a,// 505 PAY 478 

    0x86d6edc3,// 506 PAY 479 

    0x92c523fa,// 507 PAY 480 

    0x0702c7d0,// 508 PAY 481 

    0x24a2e98a,// 509 PAY 482 

    0xb63404c5,// 510 PAY 483 

    0x5eed8c33,// 511 PAY 484 

    0x79043bf6,// 512 PAY 485 

    0x898a2d9e,// 513 PAY 486 

    0xd2ab52c9,// 514 PAY 487 

    0x333576fe,// 515 PAY 488 

    0xf73de63b,// 516 PAY 489 

    0x26c89076,// 517 PAY 490 

    0x384d4737,// 518 PAY 491 

    0x0aea8c6e,// 519 PAY 492 

    0xf3dd237b,// 520 PAY 493 

    0x07cc9e31,// 521 PAY 494 

    0x8dd2e00c,// 522 PAY 495 

    0x736d7d18,// 523 PAY 496 

    0xba78ef0c,// 524 PAY 497 

    0x89e6a932,// 525 PAY 498 

    0x53742dc0,// 526 PAY 499 

    0xd7163e9c,// 527 PAY 500 

    0xd985138d,// 528 PAY 501 

    0xaa11c5a6,// 529 PAY 502 

    0xc91ff947,// 530 PAY 503 

    0xbae2cb00,// 531 PAY 504 

    0x8f9ac300,// 532 PAY 505 

/// STA is 1 words. 

/// STA num_pkts       : 229 

/// STA pkt_idx        : 76 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x4f 

    0x01314fe5 // 533 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt39_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x05 

/// ECH pdu_tag        : 0x00 

    0x00050000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv !insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x2 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x00000015,// 3 SCX   1 

    0x808248fb,// 4 SCX   2 

    0x00000200,// 5 SCX   3 

    0x125c18ad,// 6 SCX   4 

    0x26662ec4,// 7 SCX   5 

    0xefcf565f,// 8 SCX   6 

    0xbd6715fc,// 9 SCX   7 

    0xc80ad480,// 10 SCX   8 

    0xf6b7913b,// 11 SCX   9 

    0xcc84e040,// 12 SCX  10 

    0x09708e39,// 13 SCX  11 

    0xf613e8bf,// 14 SCX  12 

    0x4120d69e,// 15 SCX  13 

    0xd1d61987,// 16 SCX  14 

    0x25128ef4,// 17 SCX  15 

    0x05dfc472,// 18 SCX  16 

    0xf5de98e2,// 19 SCX  17 

    0xb79bf513,// 20 SCX  18 

    0x00c7ea2c,// 21 SCX  19 

    0x436f657e,// 22 SCX  20 

    0xdd4946de,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1638 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 311 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 311 

/// BFD lencrypto      : 80 

/// BFD ofstcrypto     : 44 

/// BFD (ofst+len)cry  : 124 

/// BFD ofstiv         : 8 

/// BFD ofsticv        : 644 

    0x00000137,// 24 BFD   1 

    0x002c0050,// 25 BFD   2 

    0x02840008,// 26 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : b 

    0x0b000d10,// 27 MFM   1 

    0x753c7f70,// 28 MFM   2 

/// BDA is 411 words. 

/// BDA size     is 1638 (0x666) 

/// BDA id       is 0xc25c 

    0x0666c25c,// 29 BDA   1 

/// PAY Generic Data size   : 1638 byte(s) 

/// PAD Buffer Data Pad size   : 2 byte(s) 

    0xd3cf96ff,// 30 PAY   1 

    0x4e5cde7d,// 31 PAY   2 

    0x9ea04124,// 32 PAY   3 

    0x2fce91de,// 33 PAY   4 

    0xb6f7a075,// 34 PAY   5 

    0xdf8bfc4d,// 35 PAY   6 

    0xc509743f,// 36 PAY   7 

    0x8b9ca1f7,// 37 PAY   8 

    0xaf07c95f,// 38 PAY   9 

    0x32941a74,// 39 PAY  10 

    0x2c52f2c5,// 40 PAY  11 

    0x026efbe0,// 41 PAY  12 

    0xf969cc01,// 42 PAY  13 

    0xf3ff97f3,// 43 PAY  14 

    0x51c07afa,// 44 PAY  15 

    0x1ec77f9a,// 45 PAY  16 

    0x8c4b2278,// 46 PAY  17 

    0xc8a43d4c,// 47 PAY  18 

    0xfb38c51c,// 48 PAY  19 

    0x2a6119c3,// 49 PAY  20 

    0xff201bab,// 50 PAY  21 

    0x75b7e6e3,// 51 PAY  22 

    0x90278251,// 52 PAY  23 

    0x4ef13818,// 53 PAY  24 

    0x935b51d8,// 54 PAY  25 

    0x4d1cb3f4,// 55 PAY  26 

    0x6ae61765,// 56 PAY  27 

    0x14d13383,// 57 PAY  28 

    0x5f0b399c,// 58 PAY  29 

    0x4a340216,// 59 PAY  30 

    0x86911595,// 60 PAY  31 

    0x9dd23d4d,// 61 PAY  32 

    0xd07f27a0,// 62 PAY  33 

    0x653eb63a,// 63 PAY  34 

    0x8f5e47e6,// 64 PAY  35 

    0xff8b6575,// 65 PAY  36 

    0xae439428,// 66 PAY  37 

    0xa8dc3f41,// 67 PAY  38 

    0x3cb02aa1,// 68 PAY  39 

    0x03a87d40,// 69 PAY  40 

    0xea7f6654,// 70 PAY  41 

    0x65e4922c,// 71 PAY  42 

    0x2c009cdd,// 72 PAY  43 

    0x3a3c6d14,// 73 PAY  44 

    0xbd49bf5e,// 74 PAY  45 

    0x78cc53e2,// 75 PAY  46 

    0x5fe4d9c1,// 76 PAY  47 

    0xcfef256d,// 77 PAY  48 

    0x9f981af0,// 78 PAY  49 

    0xb0c39104,// 79 PAY  50 

    0xbea3c705,// 80 PAY  51 

    0xdb4639a7,// 81 PAY  52 

    0xd18ea835,// 82 PAY  53 

    0x5f642f54,// 83 PAY  54 

    0xbc070c33,// 84 PAY  55 

    0xabeac319,// 85 PAY  56 

    0x28742c1f,// 86 PAY  57 

    0x25007546,// 87 PAY  58 

    0x6aef8421,// 88 PAY  59 

    0xcc583707,// 89 PAY  60 

    0x4b8fd347,// 90 PAY  61 

    0xa6f84765,// 91 PAY  62 

    0x8e24ff00,// 92 PAY  63 

    0xb73a024f,// 93 PAY  64 

    0x7339dac2,// 94 PAY  65 

    0x82454fb5,// 95 PAY  66 

    0xb1d5a7a9,// 96 PAY  67 

    0x7bdb4881,// 97 PAY  68 

    0x022b2576,// 98 PAY  69 

    0x95094dbb,// 99 PAY  70 

    0x3f111111,// 100 PAY  71 

    0xdeb69bb3,// 101 PAY  72 

    0x9f2c200f,// 102 PAY  73 

    0x0bc34b42,// 103 PAY  74 

    0xe1db7073,// 104 PAY  75 

    0x42202fe9,// 105 PAY  76 

    0xe2e6239b,// 106 PAY  77 

    0xa848980e,// 107 PAY  78 

    0x12dff5b0,// 108 PAY  79 

    0x57ac345c,// 109 PAY  80 

    0xedd0c5d6,// 110 PAY  81 

    0x26a9abb0,// 111 PAY  82 

    0xec7aaffd,// 112 PAY  83 

    0x0178ff7f,// 113 PAY  84 

    0xed9abe88,// 114 PAY  85 

    0x81f4e212,// 115 PAY  86 

    0x5dd891f4,// 116 PAY  87 

    0xded56a81,// 117 PAY  88 

    0x740df4bb,// 118 PAY  89 

    0x4db4d6a3,// 119 PAY  90 

    0x85fed43e,// 120 PAY  91 

    0x67585870,// 121 PAY  92 

    0x964f82db,// 122 PAY  93 

    0x3fb801c0,// 123 PAY  94 

    0x9cc0b9b0,// 124 PAY  95 

    0xaafa8223,// 125 PAY  96 

    0x06a08906,// 126 PAY  97 

    0xe28c8325,// 127 PAY  98 

    0xdf08eeb7,// 128 PAY  99 

    0x567483e8,// 129 PAY 100 

    0x030736ac,// 130 PAY 101 

    0xefcc2135,// 131 PAY 102 

    0xbb7d3f31,// 132 PAY 103 

    0xffb37f92,// 133 PAY 104 

    0x11f1c88e,// 134 PAY 105 

    0xebe800f0,// 135 PAY 106 

    0x12b291de,// 136 PAY 107 

    0x34686734,// 137 PAY 108 

    0xd783b8cc,// 138 PAY 109 

    0x2598f951,// 139 PAY 110 

    0x492d775d,// 140 PAY 111 

    0xee3cde4b,// 141 PAY 112 

    0xa59959d9,// 142 PAY 113 

    0xfec1b711,// 143 PAY 114 

    0xe62e02d6,// 144 PAY 115 

    0x5401be39,// 145 PAY 116 

    0x5debbbf3,// 146 PAY 117 

    0xc28506a3,// 147 PAY 118 

    0xf53cfdd8,// 148 PAY 119 

    0x7e510891,// 149 PAY 120 

    0xa104d296,// 150 PAY 121 

    0x2397ec11,// 151 PAY 122 

    0x5fd3649a,// 152 PAY 123 

    0xe54fb7a4,// 153 PAY 124 

    0x2928f4d9,// 154 PAY 125 

    0x7a09a43e,// 155 PAY 126 

    0xb5ac609d,// 156 PAY 127 

    0x6c31e37f,// 157 PAY 128 

    0x161f8682,// 158 PAY 129 

    0x9d0cc214,// 159 PAY 130 

    0x63e50d48,// 160 PAY 131 

    0xa52503d3,// 161 PAY 132 

    0x6e313d7d,// 162 PAY 133 

    0x5b485e1a,// 163 PAY 134 

    0xe1f560ab,// 164 PAY 135 

    0x64cedd1c,// 165 PAY 136 

    0xa22df970,// 166 PAY 137 

    0x2a90c8f0,// 167 PAY 138 

    0x6dc31282,// 168 PAY 139 

    0x8d1597ec,// 169 PAY 140 

    0x15212013,// 170 PAY 141 

    0xba4eb2de,// 171 PAY 142 

    0xa2707674,// 172 PAY 143 

    0xe0ce3b5c,// 173 PAY 144 

    0xf109400d,// 174 PAY 145 

    0x9cf96d32,// 175 PAY 146 

    0x9dbd1dc6,// 176 PAY 147 

    0x8b692d9f,// 177 PAY 148 

    0x996da97b,// 178 PAY 149 

    0x0efda48a,// 179 PAY 150 

    0xcae8a059,// 180 PAY 151 

    0xa27f3d92,// 181 PAY 152 

    0x2192016f,// 182 PAY 153 

    0x3d20ef65,// 183 PAY 154 

    0xa9e7faf5,// 184 PAY 155 

    0xfc617cb3,// 185 PAY 156 

    0x350b9baa,// 186 PAY 157 

    0x6b781076,// 187 PAY 158 

    0x1927911e,// 188 PAY 159 

    0xe851f8f8,// 189 PAY 160 

    0x23a98e5a,// 190 PAY 161 

    0x4de956b3,// 191 PAY 162 

    0x6675f404,// 192 PAY 163 

    0x5c3a7cac,// 193 PAY 164 

    0x9824cc67,// 194 PAY 165 

    0xc87c5357,// 195 PAY 166 

    0x9db729f9,// 196 PAY 167 

    0xa7c7650f,// 197 PAY 168 

    0x2364d5a9,// 198 PAY 169 

    0x72ad3e53,// 199 PAY 170 

    0xc66184ca,// 200 PAY 171 

    0xea6ae791,// 201 PAY 172 

    0x2b88423c,// 202 PAY 173 

    0xeb969def,// 203 PAY 174 

    0x02810c71,// 204 PAY 175 

    0xbdfd7e6d,// 205 PAY 176 

    0x8b6e33e0,// 206 PAY 177 

    0x5ed2a582,// 207 PAY 178 

    0x7ab8943c,// 208 PAY 179 

    0xb7d623c8,// 209 PAY 180 

    0x2381f7ae,// 210 PAY 181 

    0xaa006fcb,// 211 PAY 182 

    0x2aca73b8,// 212 PAY 183 

    0xd145258a,// 213 PAY 184 

    0xd85d0242,// 214 PAY 185 

    0xc4d9180b,// 215 PAY 186 

    0x63e2ac5c,// 216 PAY 187 

    0x9f74f83b,// 217 PAY 188 

    0x9acbd520,// 218 PAY 189 

    0x5777cb2d,// 219 PAY 190 

    0xfc0a1dab,// 220 PAY 191 

    0xde033032,// 221 PAY 192 

    0x8ab92833,// 222 PAY 193 

    0x0d048f83,// 223 PAY 194 

    0xf9a90fc1,// 224 PAY 195 

    0x3501139e,// 225 PAY 196 

    0xe00463be,// 226 PAY 197 

    0xde3308d0,// 227 PAY 198 

    0xa200cb7b,// 228 PAY 199 

    0xb7c2c1d3,// 229 PAY 200 

    0x2570a56c,// 230 PAY 201 

    0xdf35a264,// 231 PAY 202 

    0x853ed70d,// 232 PAY 203 

    0xd2a8830d,// 233 PAY 204 

    0x1160fc21,// 234 PAY 205 

    0x4ce74a7a,// 235 PAY 206 

    0xc2ba26ba,// 236 PAY 207 

    0xff9629dc,// 237 PAY 208 

    0xb9eb943f,// 238 PAY 209 

    0x2b719f3e,// 239 PAY 210 

    0x71063df3,// 240 PAY 211 

    0xfedc6920,// 241 PAY 212 

    0xadbd096e,// 242 PAY 213 

    0x5d1837bd,// 243 PAY 214 

    0xa24d5c07,// 244 PAY 215 

    0x71450c0c,// 245 PAY 216 

    0x15ad50db,// 246 PAY 217 

    0x61e30b17,// 247 PAY 218 

    0x392aae2a,// 248 PAY 219 

    0xb0080cd3,// 249 PAY 220 

    0xc050ccd9,// 250 PAY 221 

    0x8cf59bcf,// 251 PAY 222 

    0xc9a6a298,// 252 PAY 223 

    0x21f72e28,// 253 PAY 224 

    0xe312411e,// 254 PAY 225 

    0x9b67f630,// 255 PAY 226 

    0x796ff2ee,// 256 PAY 227 

    0x0c338a9c,// 257 PAY 228 

    0x542b9675,// 258 PAY 229 

    0xc2f449cf,// 259 PAY 230 

    0x150b61d3,// 260 PAY 231 

    0x744b9cd0,// 261 PAY 232 

    0xdf64042c,// 262 PAY 233 

    0x24d5be6c,// 263 PAY 234 

    0x18670690,// 264 PAY 235 

    0x72cdb890,// 265 PAY 236 

    0x2a7a9a32,// 266 PAY 237 

    0xde6dc020,// 267 PAY 238 

    0x4d2cb331,// 268 PAY 239 

    0xa6111a02,// 269 PAY 240 

    0xcba00077,// 270 PAY 241 

    0x3cea937f,// 271 PAY 242 

    0xb6dbffe4,// 272 PAY 243 

    0xe185d49d,// 273 PAY 244 

    0x203b7be6,// 274 PAY 245 

    0x57c800a3,// 275 PAY 246 

    0x05534371,// 276 PAY 247 

    0x7fbdebf3,// 277 PAY 248 

    0x21761c34,// 278 PAY 249 

    0x640b2b96,// 279 PAY 250 

    0x263ffa9d,// 280 PAY 251 

    0xdd91ca98,// 281 PAY 252 

    0x22762e0c,// 282 PAY 253 

    0xb6965bfd,// 283 PAY 254 

    0xc34d63d4,// 284 PAY 255 

    0xa50227d2,// 285 PAY 256 

    0x8d91f0ce,// 286 PAY 257 

    0x9758edf9,// 287 PAY 258 

    0xa9049b54,// 288 PAY 259 

    0xf10eb311,// 289 PAY 260 

    0x258a24f4,// 290 PAY 261 

    0x01aca27a,// 291 PAY 262 

    0x91864d1a,// 292 PAY 263 

    0xba83aee2,// 293 PAY 264 

    0x6fc71baf,// 294 PAY 265 

    0x42e99a96,// 295 PAY 266 

    0x4726736a,// 296 PAY 267 

    0xbb2e5108,// 297 PAY 268 

    0xda13aaac,// 298 PAY 269 

    0x6fce0a3e,// 299 PAY 270 

    0x2886eb68,// 300 PAY 271 

    0x82da17f7,// 301 PAY 272 

    0x48beb3cd,// 302 PAY 273 

    0x5eea6033,// 303 PAY 274 

    0x365521f5,// 304 PAY 275 

    0x015dd40a,// 305 PAY 276 

    0x0eea7dc6,// 306 PAY 277 

    0x7fa3949d,// 307 PAY 278 

    0xde551d52,// 308 PAY 279 

    0x739c5ca4,// 309 PAY 280 

    0x7df26ef2,// 310 PAY 281 

    0x74ffa896,// 311 PAY 282 

    0x4331d89a,// 312 PAY 283 

    0x7dbc09a0,// 313 PAY 284 

    0xc28fa981,// 314 PAY 285 

    0x42e8f73d,// 315 PAY 286 

    0x43cb69b4,// 316 PAY 287 

    0xc0b7421b,// 317 PAY 288 

    0x2eb5fe59,// 318 PAY 289 

    0x56590717,// 319 PAY 290 

    0x0a7ef424,// 320 PAY 291 

    0xe01dfc8d,// 321 PAY 292 

    0x13d4e9f7,// 322 PAY 293 

    0xc7394764,// 323 PAY 294 

    0xed7c8f6a,// 324 PAY 295 

    0x0996a4cd,// 325 PAY 296 

    0x11f3b0f0,// 326 PAY 297 

    0x2a6720ed,// 327 PAY 298 

    0x6f3ce026,// 328 PAY 299 

    0xbeaca972,// 329 PAY 300 

    0xaa3bce02,// 330 PAY 301 

    0x00c54c9c,// 331 PAY 302 

    0xd7b39983,// 332 PAY 303 

    0xfeafb6f4,// 333 PAY 304 

    0xb7224df8,// 334 PAY 305 

    0xb2a01604,// 335 PAY 306 

    0x1abae8eb,// 336 PAY 307 

    0x8e6f4512,// 337 PAY 308 

    0xc576693b,// 338 PAY 309 

    0x028468a2,// 339 PAY 310 

    0x00733a41,// 340 PAY 311 

    0xe612a0b4,// 341 PAY 312 

    0x592bfa14,// 342 PAY 313 

    0x3f312c6a,// 343 PAY 314 

    0xb0819426,// 344 PAY 315 

    0x01551127,// 345 PAY 316 

    0xd88252b2,// 346 PAY 317 

    0xa89c2afd,// 347 PAY 318 

    0xf327ae9e,// 348 PAY 319 

    0x7e65454d,// 349 PAY 320 

    0x4c46849e,// 350 PAY 321 

    0x18a46198,// 351 PAY 322 

    0x81b771b7,// 352 PAY 323 

    0x5916668b,// 353 PAY 324 

    0x94794211,// 354 PAY 325 

    0x494af2f6,// 355 PAY 326 

    0xdded6dc6,// 356 PAY 327 

    0x8ddaad4a,// 357 PAY 328 

    0x8ea71550,// 358 PAY 329 

    0x301331bd,// 359 PAY 330 

    0x5431392f,// 360 PAY 331 

    0x80b2e19a,// 361 PAY 332 

    0xace18dee,// 362 PAY 333 

    0xf55d9475,// 363 PAY 334 

    0xd1e7b5c7,// 364 PAY 335 

    0xd0d7a0f0,// 365 PAY 336 

    0xc5672787,// 366 PAY 337 

    0x27aebde2,// 367 PAY 338 

    0xf224ee94,// 368 PAY 339 

    0x3ee8b048,// 369 PAY 340 

    0x42651852,// 370 PAY 341 

    0x5edd75bb,// 371 PAY 342 

    0x1622b050,// 372 PAY 343 

    0xfb4563c6,// 373 PAY 344 

    0x370eaa38,// 374 PAY 345 

    0xdb7c2fc9,// 375 PAY 346 

    0xa5479248,// 376 PAY 347 

    0xb244ebd4,// 377 PAY 348 

    0xfb9f183e,// 378 PAY 349 

    0x45bb07d7,// 379 PAY 350 

    0xbb457979,// 380 PAY 351 

    0xb75839fd,// 381 PAY 352 

    0x179a7327,// 382 PAY 353 

    0x498d22a9,// 383 PAY 354 

    0x11afc316,// 384 PAY 355 

    0x64f5fe3f,// 385 PAY 356 

    0x7357e44e,// 386 PAY 357 

    0xc227d28d,// 387 PAY 358 

    0x879d98f7,// 388 PAY 359 

    0x3d029a42,// 389 PAY 360 

    0x5c04eaff,// 390 PAY 361 

    0x9280271b,// 391 PAY 362 

    0x41cfa267,// 392 PAY 363 

    0x88380466,// 393 PAY 364 

    0xc22e2638,// 394 PAY 365 

    0x4616b4ab,// 395 PAY 366 

    0xecdd5af7,// 396 PAY 367 

    0xb03e9e7b,// 397 PAY 368 

    0xf6ba4094,// 398 PAY 369 

    0x7092eafa,// 399 PAY 370 

    0x63d79767,// 400 PAY 371 

    0xe657bff9,// 401 PAY 372 

    0x95415bad,// 402 PAY 373 

    0x44930999,// 403 PAY 374 

    0x60c8e62a,// 404 PAY 375 

    0xf1fb2ed1,// 405 PAY 376 

    0xcbc33e52,// 406 PAY 377 

    0x5a2109f6,// 407 PAY 378 

    0xb6290f48,// 408 PAY 379 

    0x086218ad,// 409 PAY 380 

    0xcc27e0b7,// 410 PAY 381 

    0xa7edee42,// 411 PAY 382 

    0x15b7de73,// 412 PAY 383 

    0x78ba9c5c,// 413 PAY 384 

    0x989dcb2f,// 414 PAY 385 

    0x104c5d7f,// 415 PAY 386 

    0xa132e5c0,// 416 PAY 387 

    0xba0188ce,// 417 PAY 388 

    0x3398ce07,// 418 PAY 389 

    0x83c63447,// 419 PAY 390 

    0x932cf248,// 420 PAY 391 

    0x2f550b7b,// 421 PAY 392 

    0x47780c7f,// 422 PAY 393 

    0x51e1f472,// 423 PAY 394 

    0x9b2633d1,// 424 PAY 395 

    0x87b5d4f5,// 425 PAY 396 

    0x7a189d74,// 426 PAY 397 

    0x5d27403d,// 427 PAY 398 

    0xed46234f,// 428 PAY 399 

    0xeb9fcb4a,// 429 PAY 400 

    0xd93ae09a,// 430 PAY 401 

    0x159b02c8,// 431 PAY 402 

    0x9cf3f7b9,// 432 PAY 403 

    0xc6fef43b,// 433 PAY 404 

    0x613f3f5b,// 434 PAY 405 

    0x772a5491,// 435 PAY 406 

    0x29787519,// 436 PAY 407 

    0x11df8459,// 437 PAY 408 

    0xc442d45e,// 438 PAY 409 

    0x47d60000,// 439 PAY 410 

/// STA is 1 words. 

/// STA num_pkts       : 208 

/// STA pkt_idx        : 48 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x5f 

    0x00c05fd0 // 440 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt40_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x04 

/// ECH pdu_tag        : 0x00 

    0x00040000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv insert_icv !check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000019,// 3 SCX   1 

    0x80924891,// 4 SCX   2 

    0x00006582,// 5 SCX   3 

    0x6c1942fe,// 6 SCX   4 

    0x3d5afafd,// 7 SCX   5 

    0x0de06fd6,// 8 SCX   6 

    0x17e57864,// 9 SCX   7 

    0xa22e0653,// 10 SCX   8 

    0x51bcc426,// 11 SCX   9 

    0x850cc560,// 12 SCX  10 

    0x2060f867,// 13 SCX  11 

    0x4db3c84d,// 14 SCX  12 

    0xf6eff365,// 15 SCX  13 

    0x21c7dcc1,// 16 SCX  14 

    0x4e5ed2c9,// 17 SCX  15 

    0x712ca605,// 18 SCX  16 

    0xc621e1f9,// 19 SCX  17 

    0x5d79217b,// 20 SCX  18 

    0xad902ccf,// 21 SCX  19 

    0x70db4cbe,// 22 SCX  20 

    0xd8180831,// 23 SCX  21 

    0x5ae87264,// 24 SCX  22 

    0xe5e696a6,// 25 SCX  23 

    0xf9452129,// 26 SCX  24 

    0xe053d26a,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 620 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 89 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 89 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 68 

/// BFD (ofst+len)cry  : 84 

/// BFD ofstiv         : 44 

/// BFD ofsticv        : 356 

    0x00000059,// 28 BFD   1 

    0x00440010,// 29 BFD   2 

    0x0164002c,// 30 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : 7 

    0x07006e8c,// 31 MFM   1 

    0x95300000,// 32 MFM   2 

/// BDA is 156 words. 

/// BDA size     is 620 (0x26c) 

/// BDA id       is 0xd94d 

    0x026cd94d,// 33 BDA   1 

/// PAY Generic Data size   : 620 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0x075384a8,// 34 PAY   1 

    0x19234baa,// 35 PAY   2 

    0xf83613f2,// 36 PAY   3 

    0x92f3451e,// 37 PAY   4 

    0x7f79d209,// 38 PAY   5 

    0x9929350e,// 39 PAY   6 

    0x9266537e,// 40 PAY   7 

    0x1bc33237,// 41 PAY   8 

    0x8e1d01da,// 42 PAY   9 

    0xc972ce7e,// 43 PAY  10 

    0x449d4d3d,// 44 PAY  11 

    0xee7d3023,// 45 PAY  12 

    0x673e5e66,// 46 PAY  13 

    0x74b01187,// 47 PAY  14 

    0xd7128cf0,// 48 PAY  15 

    0x7e652ee6,// 49 PAY  16 

    0x4a83a48e,// 50 PAY  17 

    0xd53a3800,// 51 PAY  18 

    0x28ce65ae,// 52 PAY  19 

    0xbfeb5818,// 53 PAY  20 

    0x0627dc9f,// 54 PAY  21 

    0x4703cc08,// 55 PAY  22 

    0x91684bed,// 56 PAY  23 

    0xf1bb333a,// 57 PAY  24 

    0x7eac0f63,// 58 PAY  25 

    0xff0e0abe,// 59 PAY  26 

    0x9eec80af,// 60 PAY  27 

    0x7b8d9555,// 61 PAY  28 

    0x257e24cc,// 62 PAY  29 

    0x89afb42c,// 63 PAY  30 

    0x102dde2a,// 64 PAY  31 

    0x4114e332,// 65 PAY  32 

    0x4b576624,// 66 PAY  33 

    0x2fb7c050,// 67 PAY  34 

    0x6af28db9,// 68 PAY  35 

    0x5b4f0c3b,// 69 PAY  36 

    0x0b817188,// 70 PAY  37 

    0x38d0d8df,// 71 PAY  38 

    0x573560b6,// 72 PAY  39 

    0xcb422060,// 73 PAY  40 

    0xa0e8bcc2,// 74 PAY  41 

    0x8a99f6ad,// 75 PAY  42 

    0x33d997d9,// 76 PAY  43 

    0xc481042c,// 77 PAY  44 

    0x6698e850,// 78 PAY  45 

    0x96020607,// 79 PAY  46 

    0x9396a620,// 80 PAY  47 

    0xe790de9b,// 81 PAY  48 

    0x5637b632,// 82 PAY  49 

    0x5983082c,// 83 PAY  50 

    0x1eb62e30,// 84 PAY  51 

    0xe5f1c179,// 85 PAY  52 

    0xf7af0a39,// 86 PAY  53 

    0xae181fb8,// 87 PAY  54 

    0x7e59d283,// 88 PAY  55 

    0x87f1ce62,// 89 PAY  56 

    0x1a74cd16,// 90 PAY  57 

    0x355f9cf5,// 91 PAY  58 

    0xd1be7b8f,// 92 PAY  59 

    0x3320fe8e,// 93 PAY  60 

    0xc27245d9,// 94 PAY  61 

    0xd8aa0eba,// 95 PAY  62 

    0xa0d0d195,// 96 PAY  63 

    0xee1fa3bc,// 97 PAY  64 

    0x7a8aa1db,// 98 PAY  65 

    0x15df5880,// 99 PAY  66 

    0xfac994dc,// 100 PAY  67 

    0x6ea9038f,// 101 PAY  68 

    0x8ceeab39,// 102 PAY  69 

    0x071aa154,// 103 PAY  70 

    0xc69075f3,// 104 PAY  71 

    0x66f2e3c8,// 105 PAY  72 

    0x4ef51fa5,// 106 PAY  73 

    0x0d718378,// 107 PAY  74 

    0xcfbec60b,// 108 PAY  75 

    0xf5a35b0c,// 109 PAY  76 

    0x17fa8187,// 110 PAY  77 

    0x541b5b93,// 111 PAY  78 

    0x45e88be9,// 112 PAY  79 

    0x81c77d1a,// 113 PAY  80 

    0x71344bb6,// 114 PAY  81 

    0x9cd45da4,// 115 PAY  82 

    0x3805038b,// 116 PAY  83 

    0x052e8f84,// 117 PAY  84 

    0xcf4e0f53,// 118 PAY  85 

    0x07f43898,// 119 PAY  86 

    0x20323dde,// 120 PAY  87 

    0xb43b9857,// 121 PAY  88 

    0x7a636b28,// 122 PAY  89 

    0x9257fac9,// 123 PAY  90 

    0xc967d378,// 124 PAY  91 

    0xd06c78c0,// 125 PAY  92 

    0x2b3e871a,// 126 PAY  93 

    0x1ee41e1b,// 127 PAY  94 

    0xaebcd8ce,// 128 PAY  95 

    0x8418d6dd,// 129 PAY  96 

    0x8625ef5a,// 130 PAY  97 

    0x31c5cf17,// 131 PAY  98 

    0xed951a08,// 132 PAY  99 

    0x704da581,// 133 PAY 100 

    0x9576c1a6,// 134 PAY 101 

    0x5565d2e5,// 135 PAY 102 

    0xd32d9f6b,// 136 PAY 103 

    0x808e8dfa,// 137 PAY 104 

    0xeb8e28b5,// 138 PAY 105 

    0xa6011388,// 139 PAY 106 

    0xcbef1ed7,// 140 PAY 107 

    0x7fbfbcdf,// 141 PAY 108 

    0x0dae2ba1,// 142 PAY 109 

    0x05d2bb13,// 143 PAY 110 

    0x183d9040,// 144 PAY 111 

    0x04229b59,// 145 PAY 112 

    0x667c0178,// 146 PAY 113 

    0x97590318,// 147 PAY 114 

    0xbd1d1ce7,// 148 PAY 115 

    0xfcec4db1,// 149 PAY 116 

    0x9c9ac63c,// 150 PAY 117 

    0x42ddca50,// 151 PAY 118 

    0x79222d12,// 152 PAY 119 

    0x44a9b470,// 153 PAY 120 

    0x56be7cca,// 154 PAY 121 

    0xd4ada77f,// 155 PAY 122 

    0x1edbb7ec,// 156 PAY 123 

    0xe2ab521d,// 157 PAY 124 

    0xd75461f4,// 158 PAY 125 

    0x0b6f8d96,// 159 PAY 126 

    0xcf0c52d6,// 160 PAY 127 

    0xb1b42baa,// 161 PAY 128 

    0xacafbe95,// 162 PAY 129 

    0x2cd63657,// 163 PAY 130 

    0x8f995aa0,// 164 PAY 131 

    0x04e42d9e,// 165 PAY 132 

    0x616e8c45,// 166 PAY 133 

    0x1afeba4a,// 167 PAY 134 

    0x2b44bf29,// 168 PAY 135 

    0x008e3134,// 169 PAY 136 

    0x5e396341,// 170 PAY 137 

    0x3b54f090,// 171 PAY 138 

    0x7aab07bb,// 172 PAY 139 

    0x3afced4d,// 173 PAY 140 

    0xa6428b8d,// 174 PAY 141 

    0x71c7467c,// 175 PAY 142 

    0xd0670813,// 176 PAY 143 

    0xe7fcaa95,// 177 PAY 144 

    0xd313ab63,// 178 PAY 145 

    0x2715f1ed,// 179 PAY 146 

    0x6ec3b1d6,// 180 PAY 147 

    0xb8f9c968,// 181 PAY 148 

    0x3171b91e,// 182 PAY 149 

    0xce3aa591,// 183 PAY 150 

    0x36694164,// 184 PAY 151 

    0x7c55e7a1,// 185 PAY 152 

    0x1595ceb8,// 186 PAY 153 

    0xebd1e9db,// 187 PAY 154 

    0x8d5949a5,// 188 PAY 155 

/// STA is 1 words. 

/// STA num_pkts       : 120 

/// STA pkt_idx        : 243 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xdb 

    0x03ccdb78 // 189 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 96 (0x60) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt41_tmpl[] = {
    0xb8010060,// 1 CCH   1 

/// ECH cache_idx      : 0x00 

/// ECH pdu_tag        : 0x00 

    0x00000000,// 2 ECH   1 

/// SCX is 23 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv !insert_icv check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000017,// 3 SCX   1 

    0x8085482a,// 4 SCX   2 

    0x000014c4,// 5 SCX   3 

    0x62f7e0f3,// 6 SCX   4 

    0x16bd42ff,// 7 SCX   5 

    0x0c1b8de0,// 8 SCX   6 

    0xb75f6d98,// 9 SCX   7 

    0x8904d794,// 10 SCX   8 

    0x6dabb87b,// 11 SCX   9 

    0xb91c7e68,// 12 SCX  10 

    0x9eefb014,// 13 SCX  11 

    0x8c86e82e,// 14 SCX  12 

    0xb2d5b01b,// 15 SCX  13 

    0x4ef1d214,// 16 SCX  14 

    0xb517242a,// 17 SCX  15 

    0xd5096e3e,// 18 SCX  16 

    0x68bba52b,// 19 SCX  17 

    0x4b5ccc74,// 20 SCX  18 

    0x5dcbdae3,// 21 SCX  19 

    0x0b18898d,// 22 SCX  20 

    0x09298a41,// 23 SCX  21 

    0xaf9d2b49,// 24 SCX  22 

    0x7551eb50,// 25 SCX  23 

/// BFD is 3 words. 

/// BFD tot_len        : 1657 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 1145 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1145 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 936 

/// BFD (ofst+len)cry  : 952 

/// BFD ofstiv         : 144 

/// BFD ofsticv        : 1200 

    0x00000479,// 26 BFD   1 

    0x03a80010,// 27 BFD   2 

    0x04b00090,// 28 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c003af8,// 29 MFM   1 

    0x573eb963,// 30 MFM   2 

    0x9b52fe92,// 31 MFM   3 

    0x7cc7e503,// 32 MFM   4 

    0x5e9a88cc,// 33 MFM   5 

    0x2fa51c31,// 34 MFM   6 

    0xe524d44b,// 35 MFM   7 

    0xfab0a0f0,// 36 MFM   8 

    0xe14f12ae,// 37 MFM   9 

    0x6e1439e5,// 38 MFM  10 

    0x2552b049,// 39 MFM  11 

    0x220ecfdf,// 40 MFM  12 

    0x4d7900c1,// 41 MFM  13 

    0x454c99d1,// 42 MFM  14 

    0x257f1d6d,// 43 MFM  15 

    0xdc08e49e,// 44 MFM  16 

/// BDA is 416 words. 

/// BDA size     is 1657 (0x679) 

/// BDA id       is 0x4f88 

    0x06794f88,// 45 BDA   1 

/// PAY Generic Data size   : 1657 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x723b2094,// 46 PAY   1 

    0xeff2abdf,// 47 PAY   2 

    0x65c04c8c,// 48 PAY   3 

    0x595e6b90,// 49 PAY   4 

    0xf9edab8c,// 50 PAY   5 

    0x0bf30441,// 51 PAY   6 

    0x3cb3ea35,// 52 PAY   7 

    0xcf4f59ed,// 53 PAY   8 

    0x5a9a0b75,// 54 PAY   9 

    0x4e3a5fe6,// 55 PAY  10 

    0x50a8309d,// 56 PAY  11 

    0x177b23ab,// 57 PAY  12 

    0xc25c3456,// 58 PAY  13 

    0xfe445a1d,// 59 PAY  14 

    0xecf49b39,// 60 PAY  15 

    0x46f7db3b,// 61 PAY  16 

    0xf3216f6d,// 62 PAY  17 

    0xfca6a228,// 63 PAY  18 

    0x37eb7a0c,// 64 PAY  19 

    0x87bbba57,// 65 PAY  20 

    0xb7ef432e,// 66 PAY  21 

    0x9d2fbd28,// 67 PAY  22 

    0x42571dee,// 68 PAY  23 

    0x0e3fa8a6,// 69 PAY  24 

    0xd056e47f,// 70 PAY  25 

    0x2b4d6f53,// 71 PAY  26 

    0xf4f9a600,// 72 PAY  27 

    0x7c9a71b0,// 73 PAY  28 

    0xf05f5c9d,// 74 PAY  29 

    0x986df09d,// 75 PAY  30 

    0x9612070a,// 76 PAY  31 

    0x846d9e03,// 77 PAY  32 

    0x3d3189d2,// 78 PAY  33 

    0xd69113c6,// 79 PAY  34 

    0x46e96321,// 80 PAY  35 

    0xcd77c506,// 81 PAY  36 

    0xeace73bb,// 82 PAY  37 

    0xc23db1a8,// 83 PAY  38 

    0x2d19c117,// 84 PAY  39 

    0xd2fbd9cf,// 85 PAY  40 

    0x7d002c60,// 86 PAY  41 

    0x5ef12e92,// 87 PAY  42 

    0x8f724ecb,// 88 PAY  43 

    0xd9cc35c3,// 89 PAY  44 

    0x98f028ed,// 90 PAY  45 

    0x416b4b00,// 91 PAY  46 

    0x7b657cd2,// 92 PAY  47 

    0x4eb42f55,// 93 PAY  48 

    0x42fd467f,// 94 PAY  49 

    0xf354fb0b,// 95 PAY  50 

    0x6f67871b,// 96 PAY  51 

    0x50fd03ca,// 97 PAY  52 

    0xf4c545fb,// 98 PAY  53 

    0x21f5ba41,// 99 PAY  54 

    0xb8912662,// 100 PAY  55 

    0x5c43b598,// 101 PAY  56 

    0x7db326d9,// 102 PAY  57 

    0xbd5d831d,// 103 PAY  58 

    0xbe47e475,// 104 PAY  59 

    0x9651b6a1,// 105 PAY  60 

    0x13d56bcb,// 106 PAY  61 

    0xb83c5db9,// 107 PAY  62 

    0xc4ba4013,// 108 PAY  63 

    0xbdf91fc5,// 109 PAY  64 

    0x04e975ae,// 110 PAY  65 

    0xa715f342,// 111 PAY  66 

    0x58fb5c59,// 112 PAY  67 

    0xb4a94ef4,// 113 PAY  68 

    0xb57808db,// 114 PAY  69 

    0xb9f0954f,// 115 PAY  70 

    0x7f0b1982,// 116 PAY  71 

    0xa51e715b,// 117 PAY  72 

    0x863b5a91,// 118 PAY  73 

    0x2a36e648,// 119 PAY  74 

    0xb8f3b5ae,// 120 PAY  75 

    0xd712b213,// 121 PAY  76 

    0x8897dbad,// 122 PAY  77 

    0xa6704e48,// 123 PAY  78 

    0xc180bca4,// 124 PAY  79 

    0xe42515e6,// 125 PAY  80 

    0x3b35331d,// 126 PAY  81 

    0x02ddc18d,// 127 PAY  82 

    0x72421405,// 128 PAY  83 

    0xaeeae95f,// 129 PAY  84 

    0x106a572a,// 130 PAY  85 

    0x1db52d42,// 131 PAY  86 

    0x9985c3e0,// 132 PAY  87 

    0xa1d7289f,// 133 PAY  88 

    0x9ff2ba5f,// 134 PAY  89 

    0x2e6b8845,// 135 PAY  90 

    0x402fa060,// 136 PAY  91 

    0x6539fdf1,// 137 PAY  92 

    0x6d371090,// 138 PAY  93 

    0xf62ca997,// 139 PAY  94 

    0xefbb6f81,// 140 PAY  95 

    0x1ac35c89,// 141 PAY  96 

    0xcbcff5c7,// 142 PAY  97 

    0xf8551b6e,// 143 PAY  98 

    0x01a54f62,// 144 PAY  99 

    0xa4df2dc3,// 145 PAY 100 

    0xa4ec7f89,// 146 PAY 101 

    0x128321e4,// 147 PAY 102 

    0x2f54cd4d,// 148 PAY 103 

    0xfba3329e,// 149 PAY 104 

    0x31ba9861,// 150 PAY 105 

    0xd2c08dd3,// 151 PAY 106 

    0x9a8633ff,// 152 PAY 107 

    0xc15ce407,// 153 PAY 108 

    0x751763c9,// 154 PAY 109 

    0xceefcd67,// 155 PAY 110 

    0xc1b030f9,// 156 PAY 111 

    0x671bb721,// 157 PAY 112 

    0x90461d18,// 158 PAY 113 

    0xd48b59e0,// 159 PAY 114 

    0xc982cf49,// 160 PAY 115 

    0x31a3af60,// 161 PAY 116 

    0xaf69cf47,// 162 PAY 117 

    0xbffd78a6,// 163 PAY 118 

    0x320646a9,// 164 PAY 119 

    0x90227be8,// 165 PAY 120 

    0xb985c8f7,// 166 PAY 121 

    0xe883fd4b,// 167 PAY 122 

    0x63946c94,// 168 PAY 123 

    0x3e375400,// 169 PAY 124 

    0xf47218ca,// 170 PAY 125 

    0x510daf7f,// 171 PAY 126 

    0x6842311b,// 172 PAY 127 

    0xb8e0fb23,// 173 PAY 128 

    0xa33f8bb9,// 174 PAY 129 

    0x52522ac6,// 175 PAY 130 

    0x78286c9c,// 176 PAY 131 

    0x0c30da94,// 177 PAY 132 

    0xc371708b,// 178 PAY 133 

    0xbee2106c,// 179 PAY 134 

    0x4b549321,// 180 PAY 135 

    0x65cc8007,// 181 PAY 136 

    0x27239179,// 182 PAY 137 

    0x941fe5bf,// 183 PAY 138 

    0xc54d0cfe,// 184 PAY 139 

    0x7c3b82cc,// 185 PAY 140 

    0xba01751d,// 186 PAY 141 

    0x845f9860,// 187 PAY 142 

    0x8aae209e,// 188 PAY 143 

    0x552c50f2,// 189 PAY 144 

    0x5f9fa005,// 190 PAY 145 

    0x89cb7401,// 191 PAY 146 

    0xa9259a39,// 192 PAY 147 

    0x4184ab5c,// 193 PAY 148 

    0x280cfe83,// 194 PAY 149 

    0x647c26fd,// 195 PAY 150 

    0x82b51a97,// 196 PAY 151 

    0x626e9faf,// 197 PAY 152 

    0xa205824d,// 198 PAY 153 

    0xb36377ae,// 199 PAY 154 

    0x4dc38c26,// 200 PAY 155 

    0x841db16d,// 201 PAY 156 

    0xe1f3d655,// 202 PAY 157 

    0xe69224a0,// 203 PAY 158 

    0xa56a69c8,// 204 PAY 159 

    0x19b66163,// 205 PAY 160 

    0x99b430d0,// 206 PAY 161 

    0x10eedaa7,// 207 PAY 162 

    0x4a8378db,// 208 PAY 163 

    0xe2a5077b,// 209 PAY 164 

    0xd21d4b2a,// 210 PAY 165 

    0xd81e38d0,// 211 PAY 166 

    0xbc12a989,// 212 PAY 167 

    0xb9a868c3,// 213 PAY 168 

    0x635bb610,// 214 PAY 169 

    0x5b7dd459,// 215 PAY 170 

    0x134beba6,// 216 PAY 171 

    0xfbef10be,// 217 PAY 172 

    0x6792b7ce,// 218 PAY 173 

    0x457b9c67,// 219 PAY 174 

    0xb4eb98ea,// 220 PAY 175 

    0xd93ad498,// 221 PAY 176 

    0x0ed7aa63,// 222 PAY 177 

    0x378af3e3,// 223 PAY 178 

    0x246da7e8,// 224 PAY 179 

    0x60c3bf9c,// 225 PAY 180 

    0xed8fc041,// 226 PAY 181 

    0x1cb6eea2,// 227 PAY 182 

    0x8ff67d24,// 228 PAY 183 

    0xa749f975,// 229 PAY 184 

    0x7e1ab472,// 230 PAY 185 

    0x452f26a5,// 231 PAY 186 

    0x8580144f,// 232 PAY 187 

    0xa2f8fdd6,// 233 PAY 188 

    0xb4b9e9fa,// 234 PAY 189 

    0xe9f02e92,// 235 PAY 190 

    0x40ebe005,// 236 PAY 191 

    0x657fb197,// 237 PAY 192 

    0x88ad682e,// 238 PAY 193 

    0x1d5e2613,// 239 PAY 194 

    0x05b12924,// 240 PAY 195 

    0x9200e2b0,// 241 PAY 196 

    0xc90a63c8,// 242 PAY 197 

    0x573ea73b,// 243 PAY 198 

    0xea80b8f3,// 244 PAY 199 

    0x9e3f0770,// 245 PAY 200 

    0xb8639ebc,// 246 PAY 201 

    0xed92b507,// 247 PAY 202 

    0x586b7b98,// 248 PAY 203 

    0x4a84c136,// 249 PAY 204 

    0xdc5b0d49,// 250 PAY 205 

    0x2093998b,// 251 PAY 206 

    0x496b136c,// 252 PAY 207 

    0x6a364770,// 253 PAY 208 

    0x7414ec14,// 254 PAY 209 

    0x98f614ea,// 255 PAY 210 

    0x09dc3dae,// 256 PAY 211 

    0xbdd35e24,// 257 PAY 212 

    0x34f17e3b,// 258 PAY 213 

    0x06fc1dba,// 259 PAY 214 

    0x83ea8f80,// 260 PAY 215 

    0x72547452,// 261 PAY 216 

    0xc8eb1eec,// 262 PAY 217 

    0x44336a51,// 263 PAY 218 

    0xde0b6ad6,// 264 PAY 219 

    0x69d18f87,// 265 PAY 220 

    0x46c3fcd0,// 266 PAY 221 

    0xfb43da8f,// 267 PAY 222 

    0xe2cb8ceb,// 268 PAY 223 

    0x74c195e2,// 269 PAY 224 

    0x340d854a,// 270 PAY 225 

    0xc72f3ea1,// 271 PAY 226 

    0xa8d21eb7,// 272 PAY 227 

    0x7303ac0a,// 273 PAY 228 

    0x2393c376,// 274 PAY 229 

    0x6844046d,// 275 PAY 230 

    0x465ff82f,// 276 PAY 231 

    0x37ab40b2,// 277 PAY 232 

    0x7d6656ed,// 278 PAY 233 

    0xa8b298d9,// 279 PAY 234 

    0xffbb826b,// 280 PAY 235 

    0xc55c7c62,// 281 PAY 236 

    0x2d16afae,// 282 PAY 237 

    0xac355c5b,// 283 PAY 238 

    0x13ebace5,// 284 PAY 239 

    0x0085284a,// 285 PAY 240 

    0x88ef0ac2,// 286 PAY 241 

    0x2bbbafce,// 287 PAY 242 

    0x83b8cc0e,// 288 PAY 243 

    0xb2a9c31a,// 289 PAY 244 

    0x2b1427c4,// 290 PAY 245 

    0x69824443,// 291 PAY 246 

    0xf9513449,// 292 PAY 247 

    0x95db6ee7,// 293 PAY 248 

    0x13f84ec2,// 294 PAY 249 

    0x48038094,// 295 PAY 250 

    0x8e5775f9,// 296 PAY 251 

    0xde4f3a2d,// 297 PAY 252 

    0xeabb3574,// 298 PAY 253 

    0xb253c34f,// 299 PAY 254 

    0xdd1fab13,// 300 PAY 255 

    0xe210b23e,// 301 PAY 256 

    0x3255a8a1,// 302 PAY 257 

    0xa0b58898,// 303 PAY 258 

    0x4394f052,// 304 PAY 259 

    0xeac0213a,// 305 PAY 260 

    0xfd3e2632,// 306 PAY 261 

    0xfad57328,// 307 PAY 262 

    0xccc01b76,// 308 PAY 263 

    0x04b53b4c,// 309 PAY 264 

    0x75f5b7b4,// 310 PAY 265 

    0xb5a56f5c,// 311 PAY 266 

    0x1ca95ea9,// 312 PAY 267 

    0x9544d2f9,// 313 PAY 268 

    0xd7f2d3b8,// 314 PAY 269 

    0x419a5927,// 315 PAY 270 

    0x98a1c40f,// 316 PAY 271 

    0x9c03a582,// 317 PAY 272 

    0x81928413,// 318 PAY 273 

    0x94d3c29e,// 319 PAY 274 

    0xa415a90c,// 320 PAY 275 

    0x2fbbf626,// 321 PAY 276 

    0x94ec9d4a,// 322 PAY 277 

    0x73140ef0,// 323 PAY 278 

    0x36388186,// 324 PAY 279 

    0x2f760b03,// 325 PAY 280 

    0xdbcd6d38,// 326 PAY 281 

    0x874249f2,// 327 PAY 282 

    0x9d0e9500,// 328 PAY 283 

    0x65ee4efb,// 329 PAY 284 

    0x8b359578,// 330 PAY 285 

    0x40c152a6,// 331 PAY 286 

    0x3392567f,// 332 PAY 287 

    0x4568d00e,// 333 PAY 288 

    0x25b3fd25,// 334 PAY 289 

    0x6bf599fb,// 335 PAY 290 

    0x70fa504f,// 336 PAY 291 

    0xe1893820,// 337 PAY 292 

    0xcd9e0e9e,// 338 PAY 293 

    0xf30fab56,// 339 PAY 294 

    0xaf4ede84,// 340 PAY 295 

    0x2b200f1f,// 341 PAY 296 

    0xd5c67366,// 342 PAY 297 

    0x546dcd44,// 343 PAY 298 

    0x9dc8fcfa,// 344 PAY 299 

    0x1eceaf93,// 345 PAY 300 

    0x0cc503a7,// 346 PAY 301 

    0x43647930,// 347 PAY 302 

    0x32c28769,// 348 PAY 303 

    0x1ba63eeb,// 349 PAY 304 

    0x41b2a41b,// 350 PAY 305 

    0xa2b45ea6,// 351 PAY 306 

    0x4321a8f5,// 352 PAY 307 

    0xc15b1a06,// 353 PAY 308 

    0xf0528d15,// 354 PAY 309 

    0xb5b54bca,// 355 PAY 310 

    0xb8cb2cbf,// 356 PAY 311 

    0x9d5cacbe,// 357 PAY 312 

    0xd72e9175,// 358 PAY 313 

    0x9c1b997e,// 359 PAY 314 

    0xf5f7213d,// 360 PAY 315 

    0x8f8094de,// 361 PAY 316 

    0x13b0db4a,// 362 PAY 317 

    0x4a8a6c61,// 363 PAY 318 

    0x6fd00ed7,// 364 PAY 319 

    0xd3050f12,// 365 PAY 320 

    0xad7171f2,// 366 PAY 321 

    0x254b3c66,// 367 PAY 322 

    0x0f2e0264,// 368 PAY 323 

    0x508b5d96,// 369 PAY 324 

    0x5468db18,// 370 PAY 325 

    0xd94efff9,// 371 PAY 326 

    0xd704fe68,// 372 PAY 327 

    0xf775b442,// 373 PAY 328 

    0xb3086660,// 374 PAY 329 

    0x4f300e70,// 375 PAY 330 

    0x0b641801,// 376 PAY 331 

    0x185e4aee,// 377 PAY 332 

    0xe6d89cc8,// 378 PAY 333 

    0xa74d67cc,// 379 PAY 334 

    0x9fe2f1c9,// 380 PAY 335 

    0xe2f18e16,// 381 PAY 336 

    0x14a6c935,// 382 PAY 337 

    0xff60f44d,// 383 PAY 338 

    0x32dc9e3c,// 384 PAY 339 

    0xccea2558,// 385 PAY 340 

    0x3f80abc1,// 386 PAY 341 

    0xb887dbe5,// 387 PAY 342 

    0xac689cce,// 388 PAY 343 

    0xea63be28,// 389 PAY 344 

    0xc944481e,// 390 PAY 345 

    0x5b708629,// 391 PAY 346 

    0x0fdced9a,// 392 PAY 347 

    0xa7b24777,// 393 PAY 348 

    0xf35b72d7,// 394 PAY 349 

    0xf9fab108,// 395 PAY 350 

    0xe54ad67c,// 396 PAY 351 

    0x8eede568,// 397 PAY 352 

    0x87936013,// 398 PAY 353 

    0x636bf4cd,// 399 PAY 354 

    0x1fdf429a,// 400 PAY 355 

    0x18cd6bf0,// 401 PAY 356 

    0x837d3dcf,// 402 PAY 357 

    0x269b53df,// 403 PAY 358 

    0x519cbcc8,// 404 PAY 359 

    0x1d75ae91,// 405 PAY 360 

    0x1d59113a,// 406 PAY 361 

    0x9d10a68a,// 407 PAY 362 

    0xc6f8090b,// 408 PAY 363 

    0x77ba9787,// 409 PAY 364 

    0x249662e1,// 410 PAY 365 

    0xd056d907,// 411 PAY 366 

    0x33ebcc02,// 412 PAY 367 

    0x1f125093,// 413 PAY 368 

    0x9a3c2555,// 414 PAY 369 

    0x3010cf8d,// 415 PAY 370 

    0x880bee83,// 416 PAY 371 

    0x64d7fe8c,// 417 PAY 372 

    0xda57bd29,// 418 PAY 373 

    0x03399c68,// 419 PAY 374 

    0x616a361e,// 420 PAY 375 

    0x5274d41c,// 421 PAY 376 

    0xd8c648ff,// 422 PAY 377 

    0x970ecf15,// 423 PAY 378 

    0x03c3e089,// 424 PAY 379 

    0x09974a18,// 425 PAY 380 

    0xe57b6738,// 426 PAY 381 

    0xb6e9329e,// 427 PAY 382 

    0xb5ae25a8,// 428 PAY 383 

    0x57920b58,// 429 PAY 384 

    0x77eca008,// 430 PAY 385 

    0x034fd45e,// 431 PAY 386 

    0xe0dae201,// 432 PAY 387 

    0xf09b598a,// 433 PAY 388 

    0x208e2431,// 434 PAY 389 

    0x012f8dcc,// 435 PAY 390 

    0x419c18be,// 436 PAY 391 

    0x0ad11b4f,// 437 PAY 392 

    0xbcf60d2b,// 438 PAY 393 

    0x2ad5d77d,// 439 PAY 394 

    0x8636600d,// 440 PAY 395 

    0xdf820c1c,// 441 PAY 396 

    0x2a4a5a2e,// 442 PAY 397 

    0x2e0c7eb4,// 443 PAY 398 

    0x5d9a7ab5,// 444 PAY 399 

    0x3075e168,// 445 PAY 400 

    0xa877d249,// 446 PAY 401 

    0x819a62c4,// 447 PAY 402 

    0xa3ae7264,// 448 PAY 403 

    0x73d0e487,// 449 PAY 404 

    0xc41ce11a,// 450 PAY 405 

    0x600b7efd,// 451 PAY 406 

    0xf83f693d,// 452 PAY 407 

    0x6cd45fee,// 453 PAY 408 

    0x4596ed1f,// 454 PAY 409 

    0xf2550c1e,// 455 PAY 410 

    0xf9108178,// 456 PAY 411 

    0x6193b7c4,// 457 PAY 412 

    0x739a5681,// 458 PAY 413 

    0xea406fca,// 459 PAY 414 

    0x3b000000,// 460 PAY 415 

/// STA is 1 words. 

/// STA num_pkts       : 154 

/// STA pkt_idx        : 101 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x4a 

    0x01954a9a // 461 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt42_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x02 

/// ECH pdu_tag        : 0x00 

    0x00020000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv !check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x80844883,// 4 SCX   2 

    0x00004384,// 5 SCX   3 

    0xf719b0a0,// 6 SCX   4 

    0x31990205,// 7 SCX   5 

    0x92bdb2a9,// 8 SCX   6 

    0x3670d362,// 9 SCX   7 

    0xf5f788ed,// 10 SCX   8 

    0x045635f5,// 11 SCX   9 

    0x14726a21,// 12 SCX  10 

    0x94a07a91,// 13 SCX  11 

    0x9779a1e5,// 14 SCX  12 

    0x3e5f64cb,// 15 SCX  13 

    0x235c0545,// 16 SCX  14 

    0x931e6c4e,// 17 SCX  15 

    0xa87c5ba8,// 18 SCX  16 

    0xe571bc2a,// 19 SCX  17 

    0x646a2b65,// 20 SCX  18 

    0x3896bf7c,// 21 SCX  19 

    0xff52caaf,// 22 SCX  20 

    0xd1054286,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1753 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 1397 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1397 

/// BFD lencrypto      : 144 

/// BFD ofstcrypto     : 720 

/// BFD (ofst+len)cry  : 864 

/// BFD ofstiv         : 348 

/// BFD ofsticv        : 1620 

    0x00000575,// 24 BFD   1 

    0x02d00090,// 25 BFD   2 

    0x0654015c,// 26 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c00272d,// 27 MFM   1 

    0xa5d4a84e,// 28 MFM   2 

    0x22ea0655,// 29 MFM   3 

    0x50b975e7,// 30 MFM   4 

    0x53cb36f4,// 31 MFM   5 

    0xe3731124,// 32 MFM   6 

    0xe1026ae4,// 33 MFM   7 

    0xc7cd3038,// 34 MFM   8 

    0x746c0148,// 35 MFM   9 

    0x0e7e4dbf,// 36 MFM  10 

    0xedc27204,// 37 MFM  11 

    0xb24c5d77,// 38 MFM  12 

    0xe21a448d,// 39 MFM  13 

    0x65140ccc,// 40 MFM  14 

    0x434be412,// 41 MFM  15 

    0xeff58662,// 42 MFM  16 

/// BDA is 440 words. 

/// BDA size     is 1753 (0x6d9) 

/// BDA id       is 0x80ec 

    0x06d980ec,// 43 BDA   1 

/// PAY Generic Data size   : 1753 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x606442f4,// 44 PAY   1 

    0xbd82c5c1,// 45 PAY   2 

    0x69d399a4,// 46 PAY   3 

    0x2435d2fe,// 47 PAY   4 

    0x2ae65844,// 48 PAY   5 

    0x87fec28b,// 49 PAY   6 

    0x8e8f84ec,// 50 PAY   7 

    0x58c1ae6a,// 51 PAY   8 

    0xad5b7570,// 52 PAY   9 

    0x1470f8f8,// 53 PAY  10 

    0xfc62aefd,// 54 PAY  11 

    0xf8f88932,// 55 PAY  12 

    0xed17fbb6,// 56 PAY  13 

    0x62170f20,// 57 PAY  14 

    0x2eeb63a8,// 58 PAY  15 

    0x0f7ccb85,// 59 PAY  16 

    0xe53d7678,// 60 PAY  17 

    0xbb0d7fe4,// 61 PAY  18 

    0x75fb2de9,// 62 PAY  19 

    0xbaa84cf9,// 63 PAY  20 

    0x8e2a0e48,// 64 PAY  21 

    0x2aebd23e,// 65 PAY  22 

    0x3d476af6,// 66 PAY  23 

    0xddd0c8c3,// 67 PAY  24 

    0x6e56891f,// 68 PAY  25 

    0x95575c72,// 69 PAY  26 

    0x1a394e48,// 70 PAY  27 

    0x23a4db1f,// 71 PAY  28 

    0xd5b3ca05,// 72 PAY  29 

    0x0c27e32e,// 73 PAY  30 

    0x6d91bebb,// 74 PAY  31 

    0x059e7637,// 75 PAY  32 

    0x9627aa39,// 76 PAY  33 

    0x9a9fd5eb,// 77 PAY  34 

    0x88d3eace,// 78 PAY  35 

    0xbe475f02,// 79 PAY  36 

    0x27b3c6de,// 80 PAY  37 

    0x821e51a9,// 81 PAY  38 

    0x28e7b201,// 82 PAY  39 

    0x1a304335,// 83 PAY  40 

    0x7ebf4c1f,// 84 PAY  41 

    0xd3499f86,// 85 PAY  42 

    0xa36e08c6,// 86 PAY  43 

    0x96f30dfc,// 87 PAY  44 

    0xa0781fe9,// 88 PAY  45 

    0xd97cafb9,// 89 PAY  46 

    0xb852ea56,// 90 PAY  47 

    0x54b52cd7,// 91 PAY  48 

    0x5c522647,// 92 PAY  49 

    0x80989cef,// 93 PAY  50 

    0x0be5c9fb,// 94 PAY  51 

    0x8332218a,// 95 PAY  52 

    0x65751170,// 96 PAY  53 

    0x052ec9b5,// 97 PAY  54 

    0xd83221f0,// 98 PAY  55 

    0xcab13d49,// 99 PAY  56 

    0x74b4c246,// 100 PAY  57 

    0x2fea38ad,// 101 PAY  58 

    0xbfaab0a1,// 102 PAY  59 

    0x4852517f,// 103 PAY  60 

    0x79e9c175,// 104 PAY  61 

    0x60a52769,// 105 PAY  62 

    0x03c7015f,// 106 PAY  63 

    0xe8f972c9,// 107 PAY  64 

    0x7a769451,// 108 PAY  65 

    0xab85c362,// 109 PAY  66 

    0x828c5481,// 110 PAY  67 

    0x49e908e2,// 111 PAY  68 

    0x5c6be753,// 112 PAY  69 

    0x08f9db1a,// 113 PAY  70 

    0x776df91d,// 114 PAY  71 

    0x9b82f644,// 115 PAY  72 

    0x2a51273a,// 116 PAY  73 

    0xc2eb522d,// 117 PAY  74 

    0x4d13b374,// 118 PAY  75 

    0x1da02d85,// 119 PAY  76 

    0xa7eb9fc3,// 120 PAY  77 

    0x18164c29,// 121 PAY  78 

    0xd09ab380,// 122 PAY  79 

    0xd8670dc7,// 123 PAY  80 

    0x29b2142c,// 124 PAY  81 

    0xc57104e4,// 125 PAY  82 

    0x52f6fafd,// 126 PAY  83 

    0xc4587b88,// 127 PAY  84 

    0x3444da40,// 128 PAY  85 

    0x9e8a1889,// 129 PAY  86 

    0x6d172349,// 130 PAY  87 

    0xc89371c6,// 131 PAY  88 

    0x4af740d9,// 132 PAY  89 

    0xa09d7067,// 133 PAY  90 

    0xf55b827e,// 134 PAY  91 

    0xa67396d3,// 135 PAY  92 

    0x03b8f689,// 136 PAY  93 

    0x58ac7447,// 137 PAY  94 

    0x411e8840,// 138 PAY  95 

    0xc891a638,// 139 PAY  96 

    0x68352ffc,// 140 PAY  97 

    0xb3fd5412,// 141 PAY  98 

    0x0f4be509,// 142 PAY  99 

    0xfc2d704d,// 143 PAY 100 

    0x5ff84f1d,// 144 PAY 101 

    0x73535d3c,// 145 PAY 102 

    0x9d92ca43,// 146 PAY 103 

    0x75cf9c9b,// 147 PAY 104 

    0x6c672727,// 148 PAY 105 

    0x5e1d5a06,// 149 PAY 106 

    0x15523cd9,// 150 PAY 107 

    0xb318916f,// 151 PAY 108 

    0x1a2eff32,// 152 PAY 109 

    0xb143005e,// 153 PAY 110 

    0x33891402,// 154 PAY 111 

    0x58f8561b,// 155 PAY 112 

    0xd04a5c5e,// 156 PAY 113 

    0x5b4ed414,// 157 PAY 114 

    0x4cb381a3,// 158 PAY 115 

    0xdadb4fc1,// 159 PAY 116 

    0xe9392d33,// 160 PAY 117 

    0x672dd52e,// 161 PAY 118 

    0xe5f748af,// 162 PAY 119 

    0x2dd90b2e,// 163 PAY 120 

    0xc838bff6,// 164 PAY 121 

    0x9317accc,// 165 PAY 122 

    0x2ef95bf5,// 166 PAY 123 

    0x093b247a,// 167 PAY 124 

    0x251628f6,// 168 PAY 125 

    0xa36d3dd7,// 169 PAY 126 

    0x4b523195,// 170 PAY 127 

    0x735e52e9,// 171 PAY 128 

    0x79ff89ad,// 172 PAY 129 

    0xe6b5e732,// 173 PAY 130 

    0x2f0beabe,// 174 PAY 131 

    0x33659423,// 175 PAY 132 

    0x61bed9d7,// 176 PAY 133 

    0x4a0990e0,// 177 PAY 134 

    0x770ac170,// 178 PAY 135 

    0x738f3442,// 179 PAY 136 

    0x5192ea17,// 180 PAY 137 

    0xdb570626,// 181 PAY 138 

    0xe7e18f13,// 182 PAY 139 

    0x4997e9bd,// 183 PAY 140 

    0xb54ed83e,// 184 PAY 141 

    0xbe9877b5,// 185 PAY 142 

    0x3bc03980,// 186 PAY 143 

    0x69dac4ff,// 187 PAY 144 

    0xda700527,// 188 PAY 145 

    0x35ed8851,// 189 PAY 146 

    0x4cdb5f0d,// 190 PAY 147 

    0xd220030d,// 191 PAY 148 

    0xea525b2a,// 192 PAY 149 

    0xb3b61f25,// 193 PAY 150 

    0x8753929c,// 194 PAY 151 

    0x56482f98,// 195 PAY 152 

    0x98195ef3,// 196 PAY 153 

    0xb2efd6b4,// 197 PAY 154 

    0x32cf0272,// 198 PAY 155 

    0xe312050d,// 199 PAY 156 

    0x337eb2f1,// 200 PAY 157 

    0x7f8fa580,// 201 PAY 158 

    0x7d5662fe,// 202 PAY 159 

    0x9cd260ed,// 203 PAY 160 

    0x242ff5c5,// 204 PAY 161 

    0x4c34bcb9,// 205 PAY 162 

    0xb37fbf65,// 206 PAY 163 

    0x4a86c39f,// 207 PAY 164 

    0x2b50e0d0,// 208 PAY 165 

    0x9f59b91c,// 209 PAY 166 

    0xf0bb98db,// 210 PAY 167 

    0xca10c78b,// 211 PAY 168 

    0xfb4f5f5a,// 212 PAY 169 

    0xd71a630a,// 213 PAY 170 

    0x419b4365,// 214 PAY 171 

    0x840b11ba,// 215 PAY 172 

    0xf089c056,// 216 PAY 173 

    0x7bc67ff1,// 217 PAY 174 

    0x2d4deac5,// 218 PAY 175 

    0x323125f4,// 219 PAY 176 

    0x49ca802e,// 220 PAY 177 

    0xd2899370,// 221 PAY 178 

    0xad7da62f,// 222 PAY 179 

    0x5ad2c325,// 223 PAY 180 

    0xfee2b53c,// 224 PAY 181 

    0xc36fbea3,// 225 PAY 182 

    0x41a9c6bd,// 226 PAY 183 

    0x276666a0,// 227 PAY 184 

    0xf214f93c,// 228 PAY 185 

    0x96edd863,// 229 PAY 186 

    0x2c70b439,// 230 PAY 187 

    0xb24765d5,// 231 PAY 188 

    0x43b10eda,// 232 PAY 189 

    0xd1a5cb33,// 233 PAY 190 

    0x23b19701,// 234 PAY 191 

    0x151432ef,// 235 PAY 192 

    0x39fffe62,// 236 PAY 193 

    0xf4ee0ea0,// 237 PAY 194 

    0x65edc006,// 238 PAY 195 

    0x2b1d1ca7,// 239 PAY 196 

    0x27a1440b,// 240 PAY 197 

    0xf85779d8,// 241 PAY 198 

    0x26418a7f,// 242 PAY 199 

    0x1429ade9,// 243 PAY 200 

    0x4c1993c4,// 244 PAY 201 

    0xf500af8e,// 245 PAY 202 

    0x01f5726f,// 246 PAY 203 

    0x343ac4b6,// 247 PAY 204 

    0xa0f0d2d9,// 248 PAY 205 

    0xb6e5d669,// 249 PAY 206 

    0x77f3c25c,// 250 PAY 207 

    0x246654d1,// 251 PAY 208 

    0x54b50b39,// 252 PAY 209 

    0xb6c51cda,// 253 PAY 210 

    0x46dd8a72,// 254 PAY 211 

    0xb311c603,// 255 PAY 212 

    0x37f71e03,// 256 PAY 213 

    0x0f9d3f96,// 257 PAY 214 

    0xa674f004,// 258 PAY 215 

    0x6b8f1a4a,// 259 PAY 216 

    0x5a7d10c7,// 260 PAY 217 

    0xfcd8a41b,// 261 PAY 218 

    0x8fb02e4a,// 262 PAY 219 

    0x128729e9,// 263 PAY 220 

    0x0ad1bbcc,// 264 PAY 221 

    0x038d12cb,// 265 PAY 222 

    0x2d44c864,// 266 PAY 223 

    0x481ceb51,// 267 PAY 224 

    0x88b46af0,// 268 PAY 225 

    0x0bdac4d1,// 269 PAY 226 

    0x54fe8807,// 270 PAY 227 

    0xb15652d5,// 271 PAY 228 

    0xcb546537,// 272 PAY 229 

    0x47550286,// 273 PAY 230 

    0xd5c3f658,// 274 PAY 231 

    0x4bdfc735,// 275 PAY 232 

    0x6b7bf49d,// 276 PAY 233 

    0xb22ce27e,// 277 PAY 234 

    0xb533d98c,// 278 PAY 235 

    0xe09d937e,// 279 PAY 236 

    0x9435c7e9,// 280 PAY 237 

    0x3a5ee9c6,// 281 PAY 238 

    0x49a9fde6,// 282 PAY 239 

    0xc9f631a9,// 283 PAY 240 

    0xf7159bfc,// 284 PAY 241 

    0x6e1f876e,// 285 PAY 242 

    0x22a8c285,// 286 PAY 243 

    0xcc55c518,// 287 PAY 244 

    0x850e9696,// 288 PAY 245 

    0xc5ee261e,// 289 PAY 246 

    0xe8a3ab7e,// 290 PAY 247 

    0x0ea81a6f,// 291 PAY 248 

    0x5b234c36,// 292 PAY 249 

    0xdc078f8b,// 293 PAY 250 

    0x8d4c43f3,// 294 PAY 251 

    0xd06aa851,// 295 PAY 252 

    0x517ba95c,// 296 PAY 253 

    0x68a11158,// 297 PAY 254 

    0x9e92cf21,// 298 PAY 255 

    0xdcf095b5,// 299 PAY 256 

    0xe00de62d,// 300 PAY 257 

    0x31bfb95a,// 301 PAY 258 

    0x6e3bc80b,// 302 PAY 259 

    0xc0ef1de1,// 303 PAY 260 

    0xc212fef8,// 304 PAY 261 

    0xaad9846b,// 305 PAY 262 

    0x106c0ac7,// 306 PAY 263 

    0x3d3c741f,// 307 PAY 264 

    0xe1cd59a5,// 308 PAY 265 

    0x6665fd39,// 309 PAY 266 

    0x1d698f73,// 310 PAY 267 

    0x7cfafe0d,// 311 PAY 268 

    0x9984a7ec,// 312 PAY 269 

    0x14bdda69,// 313 PAY 270 

    0x0c897de9,// 314 PAY 271 

    0xc5f97ef8,// 315 PAY 272 

    0x16d6a05a,// 316 PAY 273 

    0xa5251d90,// 317 PAY 274 

    0xb6f60b18,// 318 PAY 275 

    0x7bf876c5,// 319 PAY 276 

    0x0ff409f4,// 320 PAY 277 

    0x40686cf0,// 321 PAY 278 

    0x816f28fa,// 322 PAY 279 

    0x86064804,// 323 PAY 280 

    0x956f8160,// 324 PAY 281 

    0x1974a401,// 325 PAY 282 

    0x2d10729c,// 326 PAY 283 

    0xf39322be,// 327 PAY 284 

    0xac4a8e57,// 328 PAY 285 

    0xbf3d28e4,// 329 PAY 286 

    0x2e694fce,// 330 PAY 287 

    0x94e040dc,// 331 PAY 288 

    0xdfa0d2ea,// 332 PAY 289 

    0x775b701f,// 333 PAY 290 

    0x92caa4e8,// 334 PAY 291 

    0x45878687,// 335 PAY 292 

    0x7ca4d36a,// 336 PAY 293 

    0x2c966c6e,// 337 PAY 294 

    0xc40b6678,// 338 PAY 295 

    0x95026812,// 339 PAY 296 

    0xdac8ba5d,// 340 PAY 297 

    0x5c95b489,// 341 PAY 298 

    0x93d5407a,// 342 PAY 299 

    0xef410f12,// 343 PAY 300 

    0x0ef40cb6,// 344 PAY 301 

    0x84021fbe,// 345 PAY 302 

    0x275046aa,// 346 PAY 303 

    0x47708193,// 347 PAY 304 

    0xb1218d46,// 348 PAY 305 

    0x6eeb429e,// 349 PAY 306 

    0x1007f54f,// 350 PAY 307 

    0x070c8406,// 351 PAY 308 

    0x3ab327b8,// 352 PAY 309 

    0x9feb80e0,// 353 PAY 310 

    0x9e02b7ba,// 354 PAY 311 

    0xe2c89538,// 355 PAY 312 

    0xfe034039,// 356 PAY 313 

    0x85b39f18,// 357 PAY 314 

    0xc9d6be77,// 358 PAY 315 

    0x6b92f385,// 359 PAY 316 

    0xb36fc9d4,// 360 PAY 317 

    0x63e6e51a,// 361 PAY 318 

    0x0d6ec531,// 362 PAY 319 

    0x85b1d929,// 363 PAY 320 

    0x3a85172c,// 364 PAY 321 

    0x4934a8c5,// 365 PAY 322 

    0x2631795f,// 366 PAY 323 

    0x2d449c70,// 367 PAY 324 

    0xe353e62e,// 368 PAY 325 

    0xe3cc215c,// 369 PAY 326 

    0x084def5a,// 370 PAY 327 

    0x529c2634,// 371 PAY 328 

    0x1f69a706,// 372 PAY 329 

    0x4ac55add,// 373 PAY 330 

    0x1c5162f9,// 374 PAY 331 

    0x01b5c3cf,// 375 PAY 332 

    0x6f431c5d,// 376 PAY 333 

    0xc19100c1,// 377 PAY 334 

    0x90d7be14,// 378 PAY 335 

    0x373ef6bc,// 379 PAY 336 

    0xdbae8d61,// 380 PAY 337 

    0xb5beb0f3,// 381 PAY 338 

    0x66bf9b13,// 382 PAY 339 

    0xd069ffdd,// 383 PAY 340 

    0x24f7f493,// 384 PAY 341 

    0x278519a1,// 385 PAY 342 

    0x0b7de29e,// 386 PAY 343 

    0x3008eaf0,// 387 PAY 344 

    0x2947b251,// 388 PAY 345 

    0x3659ade2,// 389 PAY 346 

    0x12f32cf4,// 390 PAY 347 

    0xc4188045,// 391 PAY 348 

    0xdd9c775a,// 392 PAY 349 

    0xb106ea68,// 393 PAY 350 

    0xf2be1c3e,// 394 PAY 351 

    0x7350e172,// 395 PAY 352 

    0x351bd32b,// 396 PAY 353 

    0x44523914,// 397 PAY 354 

    0x38976fe3,// 398 PAY 355 

    0x08c2966f,// 399 PAY 356 

    0x209e81b8,// 400 PAY 357 

    0x77d88166,// 401 PAY 358 

    0x21623941,// 402 PAY 359 

    0x0bcb92a9,// 403 PAY 360 

    0x6979f10f,// 404 PAY 361 

    0x0ac51b5e,// 405 PAY 362 

    0xa4fcabb8,// 406 PAY 363 

    0xbaf5ff6f,// 407 PAY 364 

    0xa04589eb,// 408 PAY 365 

    0xb2df75fb,// 409 PAY 366 

    0x10e9a13d,// 410 PAY 367 

    0x87b174eb,// 411 PAY 368 

    0xadcf5d54,// 412 PAY 369 

    0x4525fec0,// 413 PAY 370 

    0xcfc622d8,// 414 PAY 371 

    0xeaf135c0,// 415 PAY 372 

    0x42e2d2bd,// 416 PAY 373 

    0x4ad89730,// 417 PAY 374 

    0x53f90e8f,// 418 PAY 375 

    0xa49daced,// 419 PAY 376 

    0xdabe62a8,// 420 PAY 377 

    0x80a85c9f,// 421 PAY 378 

    0x276f5b84,// 422 PAY 379 

    0x878e20fc,// 423 PAY 380 

    0xf550e6a4,// 424 PAY 381 

    0xf5257d67,// 425 PAY 382 

    0xee3cb45c,// 426 PAY 383 

    0x45556dfe,// 427 PAY 384 

    0xeaab626f,// 428 PAY 385 

    0xe71d6952,// 429 PAY 386 

    0x64cd800f,// 430 PAY 387 

    0x6f073dd9,// 431 PAY 388 

    0x26bea21c,// 432 PAY 389 

    0x1d4f85f5,// 433 PAY 390 

    0x5cc9c378,// 434 PAY 391 

    0x361e6303,// 435 PAY 392 

    0x7b06e1b6,// 436 PAY 393 

    0x68b7a622,// 437 PAY 394 

    0xe8dd9874,// 438 PAY 395 

    0x0d48613f,// 439 PAY 396 

    0x9e66f609,// 440 PAY 397 

    0x85b97fbb,// 441 PAY 398 

    0x2480578c,// 442 PAY 399 

    0xf6400d34,// 443 PAY 400 

    0x2c907c46,// 444 PAY 401 

    0x5ae590a0,// 445 PAY 402 

    0x56f9d37c,// 446 PAY 403 

    0x44eab228,// 447 PAY 404 

    0x96146c02,// 448 PAY 405 

    0x81084d9c,// 449 PAY 406 

    0xa3478f9d,// 450 PAY 407 

    0x3c6ea128,// 451 PAY 408 

    0x68be9e23,// 452 PAY 409 

    0xf22c5f31,// 453 PAY 410 

    0xcbc23661,// 454 PAY 411 

    0xb0e71d8b,// 455 PAY 412 

    0x47badd97,// 456 PAY 413 

    0x1a14352b,// 457 PAY 414 

    0x1e3f706f,// 458 PAY 415 

    0x13cc8319,// 459 PAY 416 

    0x4bb124c4,// 460 PAY 417 

    0x61d86d24,// 461 PAY 418 

    0x2c4b4609,// 462 PAY 419 

    0x606cef7b,// 463 PAY 420 

    0xb7555e55,// 464 PAY 421 

    0x49d4960f,// 465 PAY 422 

    0xbc96e1e8,// 466 PAY 423 

    0x0e04a4af,// 467 PAY 424 

    0xc3ad5710,// 468 PAY 425 

    0x98ba79f2,// 469 PAY 426 

    0x2871d6ab,// 470 PAY 427 

    0x5f61e958,// 471 PAY 428 

    0x97123220,// 472 PAY 429 

    0xbc289ad2,// 473 PAY 430 

    0x9a7f319c,// 474 PAY 431 

    0xc1334e87,// 475 PAY 432 

    0xd9ac9db1,// 476 PAY 433 

    0xc92ff2fd,// 477 PAY 434 

    0xa83c6885,// 478 PAY 435 

    0x9ac3bfff,// 479 PAY 436 

    0x8e59430e,// 480 PAY 437 

    0xbf6408c0,// 481 PAY 438 

    0x6d000000,// 482 PAY 439 

/// STA is 1 words. 

/// STA num_pkts       : 45 

/// STA pkt_idx        : 54 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x8b 

    0x00d98b2d // 483 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt43_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x08 

/// ECH pdu_tag        : 0x00 

    0x00080000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x8082480d,// 4 SCX   2 

    0x00003300,// 5 SCX   3 

    0xa796de35,// 6 SCX   4 

    0xa5aa244d,// 7 SCX   5 

    0x66de7938,// 8 SCX   6 

    0xc3c63333,// 9 SCX   7 

    0x4538bc8a,// 10 SCX   8 

    0x78ab1325,// 11 SCX   9 

    0xb3a23583,// 12 SCX  10 

    0xa8c1d096,// 13 SCX  11 

    0x83e40d52,// 14 SCX  12 

    0x55ee068b,// 15 SCX  13 

    0x284c7275,// 16 SCX  14 

    0x8e532434,// 17 SCX  15 

    0x930f4c2a,// 18 SCX  16 

    0x8ddf9028,// 19 SCX  17 

    0x9574eef3,// 20 SCX  18 

    0x6a8a6185,// 21 SCX  19 

    0x77e88453,// 22 SCX  20 

    0x2813036b,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 947 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 777 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 777 

/// BFD lencrypto      : 48 

/// BFD ofstcrypto     : 616 

/// BFD (ofst+len)cry  : 664 

/// BFD ofstiv         : 56 

/// BFD ofsticv        : 868 

    0x00000309,// 24 BFD   1 

    0x02680030,// 25 BFD   2 

    0x03640038,// 26 BFD   3 

/// MFM is 9 words. 

/// MFM vldnibs        : 40 

    0x40006880,// 27 MFM   1 

    0xec3d8b7e,// 28 MFM   2 

    0xf5d0a4c8,// 29 MFM   3 

    0xf0a59dbe,// 30 MFM   4 

    0x9bf80c41,// 31 MFM   5 

    0xefd42e1d,// 32 MFM   6 

    0x349988f0,// 33 MFM   7 

    0xaa587874,// 34 MFM   8 

    0x9c960000,// 35 MFM   9 

/// BDA is 238 words. 

/// BDA size     is 947 (0x3b3) 

/// BDA id       is 0x6967 

    0x03b36967,// 36 BDA   1 

/// PAY Generic Data size   : 947 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0xf92c0258,// 37 PAY   1 

    0xc8773c86,// 38 PAY   2 

    0xd01b08a3,// 39 PAY   3 

    0x7ea7139a,// 40 PAY   4 

    0x9a8e2cc8,// 41 PAY   5 

    0xd53fda5a,// 42 PAY   6 

    0x8977cc8d,// 43 PAY   7 

    0x85413ce4,// 44 PAY   8 

    0xf1347bd6,// 45 PAY   9 

    0x1429e8b1,// 46 PAY  10 

    0x96a30568,// 47 PAY  11 

    0x6c4b2c00,// 48 PAY  12 

    0x1687d012,// 49 PAY  13 

    0x7aedffc9,// 50 PAY  14 

    0x1b7ddcbe,// 51 PAY  15 

    0xbf86778b,// 52 PAY  16 

    0xf47477e2,// 53 PAY  17 

    0x031457a0,// 54 PAY  18 

    0x682d2c2a,// 55 PAY  19 

    0x633b0d72,// 56 PAY  20 

    0x4f8a9541,// 57 PAY  21 

    0x38f993f3,// 58 PAY  22 

    0x919e1766,// 59 PAY  23 

    0x490850ad,// 60 PAY  24 

    0xe8fcbeb5,// 61 PAY  25 

    0x85016bb2,// 62 PAY  26 

    0xdd6b95f0,// 63 PAY  27 

    0xbf9844a3,// 64 PAY  28 

    0xfb4e8474,// 65 PAY  29 

    0x3fc333ac,// 66 PAY  30 

    0x4318a412,// 67 PAY  31 

    0xd80e1eeb,// 68 PAY  32 

    0x149f23d0,// 69 PAY  33 

    0x8d65f999,// 70 PAY  34 

    0xa8da2219,// 71 PAY  35 

    0xb6f95bdf,// 72 PAY  36 

    0x5f04b142,// 73 PAY  37 

    0xfc9e2c2a,// 74 PAY  38 

    0xb981bb24,// 75 PAY  39 

    0x94049ce7,// 76 PAY  40 

    0xe52ee97d,// 77 PAY  41 

    0x0d520d28,// 78 PAY  42 

    0x98b6ecb8,// 79 PAY  43 

    0xf9cd0b66,// 80 PAY  44 

    0x3c3d9691,// 81 PAY  45 

    0x4e2dd99e,// 82 PAY  46 

    0xb8646130,// 83 PAY  47 

    0xf5b9a8ac,// 84 PAY  48 

    0xd5bae249,// 85 PAY  49 

    0x4725ebdd,// 86 PAY  50 

    0x798821e7,// 87 PAY  51 

    0xc24f9d33,// 88 PAY  52 

    0xc5b57af3,// 89 PAY  53 

    0x748733fd,// 90 PAY  54 

    0xf9b47bd7,// 91 PAY  55 

    0x1a48a175,// 92 PAY  56 

    0xe1f92f33,// 93 PAY  57 

    0x61b09380,// 94 PAY  58 

    0x5458cef1,// 95 PAY  59 

    0xaefa3fe6,// 96 PAY  60 

    0xc7a5d1bc,// 97 PAY  61 

    0x3b43b4f5,// 98 PAY  62 

    0xf17bac12,// 99 PAY  63 

    0x12154555,// 100 PAY  64 

    0x25d260e8,// 101 PAY  65 

    0x663985eb,// 102 PAY  66 

    0x36fd0d18,// 103 PAY  67 

    0xe706e5a2,// 104 PAY  68 

    0x75dfa17c,// 105 PAY  69 

    0xb3e4dfa5,// 106 PAY  70 

    0x06186874,// 107 PAY  71 

    0xb35550b7,// 108 PAY  72 

    0xd0e6b4ea,// 109 PAY  73 

    0xabd0c323,// 110 PAY  74 

    0xd3845fc8,// 111 PAY  75 

    0x3bced460,// 112 PAY  76 

    0x1b120aeb,// 113 PAY  77 

    0x64ceb88e,// 114 PAY  78 

    0xb5b7a178,// 115 PAY  79 

    0x39727d0d,// 116 PAY  80 

    0x5e3113ae,// 117 PAY  81 

    0xc0d5c0c4,// 118 PAY  82 

    0x5f3742fc,// 119 PAY  83 

    0x91c19089,// 120 PAY  84 

    0xf60e9fc4,// 121 PAY  85 

    0xc98e15ad,// 122 PAY  86 

    0x4bf68e38,// 123 PAY  87 

    0x78336345,// 124 PAY  88 

    0x24e377b6,// 125 PAY  89 

    0x3bc8c968,// 126 PAY  90 

    0x94100819,// 127 PAY  91 

    0xae9961b3,// 128 PAY  92 

    0xf7055ead,// 129 PAY  93 

    0x1deea81d,// 130 PAY  94 

    0x655b5ab0,// 131 PAY  95 

    0x74383bca,// 132 PAY  96 

    0x28ecefe6,// 133 PAY  97 

    0x2751786a,// 134 PAY  98 

    0xc5f135a4,// 135 PAY  99 

    0x134cc6d6,// 136 PAY 100 

    0x885a417b,// 137 PAY 101 

    0x00eb711d,// 138 PAY 102 

    0x8e3bda80,// 139 PAY 103 

    0x3046d8d7,// 140 PAY 104 

    0x0f148944,// 141 PAY 105 

    0x503eedeb,// 142 PAY 106 

    0x06d8752f,// 143 PAY 107 

    0xb065f160,// 144 PAY 108 

    0x4427e07e,// 145 PAY 109 

    0x9773f6f4,// 146 PAY 110 

    0xa6a342da,// 147 PAY 111 

    0x0b66e3ee,// 148 PAY 112 

    0xcccd1d65,// 149 PAY 113 

    0xb8fee531,// 150 PAY 114 

    0xbe64894a,// 151 PAY 115 

    0xdbdc4bf5,// 152 PAY 116 

    0x87d0b47b,// 153 PAY 117 

    0x96ce3f15,// 154 PAY 118 

    0xdc762a91,// 155 PAY 119 

    0xd8669718,// 156 PAY 120 

    0xc26edd9e,// 157 PAY 121 

    0x1597794d,// 158 PAY 122 

    0x43f4bc25,// 159 PAY 123 

    0x56144b20,// 160 PAY 124 

    0xfc5f6e8b,// 161 PAY 125 

    0xb1b02a54,// 162 PAY 126 

    0xee6e8c85,// 163 PAY 127 

    0x6024739d,// 164 PAY 128 

    0xcfd4b883,// 165 PAY 129 

    0xfe635414,// 166 PAY 130 

    0xd02c28b6,// 167 PAY 131 

    0xc3b5ccf4,// 168 PAY 132 

    0xa1458a80,// 169 PAY 133 

    0x7be1b713,// 170 PAY 134 

    0x78a08153,// 171 PAY 135 

    0x32648c39,// 172 PAY 136 

    0x99b4ffdd,// 173 PAY 137 

    0x2cf784c5,// 174 PAY 138 

    0x7073c016,// 175 PAY 139 

    0x92339b1e,// 176 PAY 140 

    0x6a1587e8,// 177 PAY 141 

    0x3ed3c510,// 178 PAY 142 

    0xb5aa258c,// 179 PAY 143 

    0xfa2be0ac,// 180 PAY 144 

    0x7429e582,// 181 PAY 145 

    0x231f21a8,// 182 PAY 146 

    0xf96ef710,// 183 PAY 147 

    0xf9e02451,// 184 PAY 148 

    0xfcda6bab,// 185 PAY 149 

    0xaae43e17,// 186 PAY 150 

    0xc61bc7e6,// 187 PAY 151 

    0xe73b2580,// 188 PAY 152 

    0x50c53eba,// 189 PAY 153 

    0x078b442d,// 190 PAY 154 

    0x49146a24,// 191 PAY 155 

    0x60bc99d9,// 192 PAY 156 

    0xeffd9adc,// 193 PAY 157 

    0x03abba76,// 194 PAY 158 

    0xac487cac,// 195 PAY 159 

    0x2ac8ee02,// 196 PAY 160 

    0xcb03c52d,// 197 PAY 161 

    0xecb4a45b,// 198 PAY 162 

    0xd58e7bf1,// 199 PAY 163 

    0x742cea74,// 200 PAY 164 

    0x43d9c2a0,// 201 PAY 165 

    0x789a2e11,// 202 PAY 166 

    0x3d5b520e,// 203 PAY 167 

    0x5883ad68,// 204 PAY 168 

    0xe98440ad,// 205 PAY 169 

    0xdc26b77e,// 206 PAY 170 

    0x5eeb5653,// 207 PAY 171 

    0xb8353236,// 208 PAY 172 

    0xd9d1f67c,// 209 PAY 173 

    0x250fc03e,// 210 PAY 174 

    0x31747fe5,// 211 PAY 175 

    0x682b24aa,// 212 PAY 176 

    0x60cf1610,// 213 PAY 177 

    0x6015f3d3,// 214 PAY 178 

    0xaeb68296,// 215 PAY 179 

    0x357ca54a,// 216 PAY 180 

    0x07cbb48a,// 217 PAY 181 

    0x67b1592e,// 218 PAY 182 

    0x8bf18de5,// 219 PAY 183 

    0x591bb89c,// 220 PAY 184 

    0x45e9fa2a,// 221 PAY 185 

    0x37c1046b,// 222 PAY 186 

    0x441dc91d,// 223 PAY 187 

    0x51ba4c6a,// 224 PAY 188 

    0x3a328bf6,// 225 PAY 189 

    0x432de29b,// 226 PAY 190 

    0xdc699b56,// 227 PAY 191 

    0x23699d7d,// 228 PAY 192 

    0x96c53a94,// 229 PAY 193 

    0x451eec0e,// 230 PAY 194 

    0x535b87d4,// 231 PAY 195 

    0xb167d4aa,// 232 PAY 196 

    0xe65e9460,// 233 PAY 197 

    0x596704ca,// 234 PAY 198 

    0xf13b778f,// 235 PAY 199 

    0xef62e387,// 236 PAY 200 

    0x5647601c,// 237 PAY 201 

    0xb81a0e00,// 238 PAY 202 

    0x84425321,// 239 PAY 203 

    0x74ef25f6,// 240 PAY 204 

    0x8b4215a5,// 241 PAY 205 

    0xbb1dde38,// 242 PAY 206 

    0x06c2006b,// 243 PAY 207 

    0x702c4b95,// 244 PAY 208 

    0x939e7730,// 245 PAY 209 

    0x6e7d6048,// 246 PAY 210 

    0x872a7b3d,// 247 PAY 211 

    0xa8a20fd2,// 248 PAY 212 

    0x7c68f39d,// 249 PAY 213 

    0x5249f980,// 250 PAY 214 

    0x61407be3,// 251 PAY 215 

    0x6b327764,// 252 PAY 216 

    0x8582f093,// 253 PAY 217 

    0x85cc5d91,// 254 PAY 218 

    0x2c811701,// 255 PAY 219 

    0xeca97d3a,// 256 PAY 220 

    0x3c9f2e1e,// 257 PAY 221 

    0x806aecc7,// 258 PAY 222 

    0x17ea9029,// 259 PAY 223 

    0x8046532e,// 260 PAY 224 

    0xad0f0fe6,// 261 PAY 225 

    0x785d4727,// 262 PAY 226 

    0xadf3f019,// 263 PAY 227 

    0x705d9714,// 264 PAY 228 

    0x97e326cf,// 265 PAY 229 

    0x341ebac1,// 266 PAY 230 

    0x09c51616,// 267 PAY 231 

    0x60bbed38,// 268 PAY 232 

    0xa1c0b1c0,// 269 PAY 233 

    0x55aa6426,// 270 PAY 234 

    0x97e69b55,// 271 PAY 235 

    0x4def24b8,// 272 PAY 236 

    0x7d70a500,// 273 PAY 237 

/// STA is 1 words. 

/// STA num_pkts       : 133 

/// STA pkt_idx        : 232 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x79 

    0x03a07985 // 274 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt44_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x00 

/// ECH pdu_tag        : 0x00 

    0x00000000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv !insert_icv check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000019,// 3 SCX   1 

    0x808648dc,// 4 SCX   2 

    0x000011c4,// 5 SCX   3 

    0xd83ec8f8,// 6 SCX   4 

    0xb0a5ff21,// 7 SCX   5 

    0x22ffb6af,// 8 SCX   6 

    0x72df1bbe,// 9 SCX   7 

    0x87cb9076,// 10 SCX   8 

    0xec40f5fc,// 11 SCX   9 

    0x76bee800,// 12 SCX  10 

    0x5f95b0cd,// 13 SCX  11 

    0x468a7d8e,// 14 SCX  12 

    0x3ee071c8,// 15 SCX  13 

    0x56719ae1,// 16 SCX  14 

    0x79197cdf,// 17 SCX  15 

    0x7ac966cc,// 18 SCX  16 

    0xf5a721ce,// 19 SCX  17 

    0xab838e57,// 20 SCX  18 

    0x5375ab82,// 21 SCX  19 

    0xf9795535,// 22 SCX  20 

    0x0a823628,// 23 SCX  21 

    0xe9c6425f,// 24 SCX  22 

    0x95582069,// 25 SCX  23 

    0x16cec2d1,// 26 SCX  24 

    0x46c6019a,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 463 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 73 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 73 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 36 

/// BFD (ofst+len)cry  : 52 

/// BFD ofstiv         : 4 

/// BFD ofsticv        : 184 

    0x00000049,// 28 BFD   1 

    0x00240010,// 29 BFD   2 

    0x00b80004,// 30 BFD   3 

/// MFM is 3 words. 

/// MFM vldnibs        : 10 

    0x1000cbc6,// 31 MFM   1 

    0x7ded48e7,// 32 MFM   2 

    0xf1d30000,// 33 MFM   3 

/// BDA is 117 words. 

/// BDA size     is 463 (0x1cf) 

/// BDA id       is 0x4bfd 

    0x01cf4bfd,// 34 BDA   1 

/// PAY Generic Data size   : 463 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0x2618a4dd,// 35 PAY   1 

    0xd5ddb035,// 36 PAY   2 

    0x00ebd56d,// 37 PAY   3 

    0x8ace5a6f,// 38 PAY   4 

    0x5f31f803,// 39 PAY   5 

    0x98dcf9be,// 40 PAY   6 

    0xdcdb9913,// 41 PAY   7 

    0xea38b643,// 42 PAY   8 

    0xaa99e142,// 43 PAY   9 

    0x3b003668,// 44 PAY  10 

    0x62a8d6f1,// 45 PAY  11 

    0x08834a06,// 46 PAY  12 

    0xbeb2d6a0,// 47 PAY  13 

    0xcdd233bf,// 48 PAY  14 

    0xf272d8ad,// 49 PAY  15 

    0xc24c9cc1,// 50 PAY  16 

    0x2443bc6c,// 51 PAY  17 

    0xd6750736,// 52 PAY  18 

    0x7a133301,// 53 PAY  19 

    0x9e290e77,// 54 PAY  20 

    0x280bd5aa,// 55 PAY  21 

    0xe9496f3f,// 56 PAY  22 

    0x4dae7e30,// 57 PAY  23 

    0x31002a21,// 58 PAY  24 

    0x00809e82,// 59 PAY  25 

    0xdac06543,// 60 PAY  26 

    0xa507726e,// 61 PAY  27 

    0x6ebef936,// 62 PAY  28 

    0x74373e84,// 63 PAY  29 

    0x0883059e,// 64 PAY  30 

    0x5d36e54f,// 65 PAY  31 

    0x0633e8eb,// 66 PAY  32 

    0xc9229687,// 67 PAY  33 

    0xbbdd6890,// 68 PAY  34 

    0x6bd05a00,// 69 PAY  35 

    0x8c76642f,// 70 PAY  36 

    0x0c3a63e2,// 71 PAY  37 

    0x837cbf4c,// 72 PAY  38 

    0xbc9064a0,// 73 PAY  39 

    0xb67cebb7,// 74 PAY  40 

    0xc844604c,// 75 PAY  41 

    0x9718dd97,// 76 PAY  42 

    0x47bbb555,// 77 PAY  43 

    0x91a87709,// 78 PAY  44 

    0x5bd99efd,// 79 PAY  45 

    0x4bb723de,// 80 PAY  46 

    0x80cfaf76,// 81 PAY  47 

    0x38a2795b,// 82 PAY  48 

    0x6e542684,// 83 PAY  49 

    0x563bbeee,// 84 PAY  50 

    0xc4576dc1,// 85 PAY  51 

    0x87bec1b3,// 86 PAY  52 

    0x3bfc60de,// 87 PAY  53 

    0xb510db9c,// 88 PAY  54 

    0xeab051ff,// 89 PAY  55 

    0xb4f92ad2,// 90 PAY  56 

    0xba0ba322,// 91 PAY  57 

    0xbcc09c8e,// 92 PAY  58 

    0xfa26dfdb,// 93 PAY  59 

    0x4f511ca6,// 94 PAY  60 

    0x4602682a,// 95 PAY  61 

    0x50df3842,// 96 PAY  62 

    0x25e023ad,// 97 PAY  63 

    0x83c074e0,// 98 PAY  64 

    0x5ae44ce6,// 99 PAY  65 

    0x29ec93c8,// 100 PAY  66 

    0xc6365207,// 101 PAY  67 

    0x1dc71678,// 102 PAY  68 

    0x7df23dc5,// 103 PAY  69 

    0x0c689e60,// 104 PAY  70 

    0x19d72f5c,// 105 PAY  71 

    0xb2a50a6d,// 106 PAY  72 

    0x26ee061c,// 107 PAY  73 

    0x663c8ca9,// 108 PAY  74 

    0x2b4d3dd4,// 109 PAY  75 

    0x3e002986,// 110 PAY  76 

    0xf7a6b1ae,// 111 PAY  77 

    0xdee5f6d7,// 112 PAY  78 

    0xc2ea4f54,// 113 PAY  79 

    0x62cf7239,// 114 PAY  80 

    0x6b37f936,// 115 PAY  81 

    0x0141b240,// 116 PAY  82 

    0x3fe0c46c,// 117 PAY  83 

    0xa7152dca,// 118 PAY  84 

    0x13923f56,// 119 PAY  85 

    0x07d0788c,// 120 PAY  86 

    0x64b7c1ab,// 121 PAY  87 

    0xd5260a01,// 122 PAY  88 

    0x20456ea3,// 123 PAY  89 

    0xbc4a75e7,// 124 PAY  90 

    0x6c0160d1,// 125 PAY  91 

    0xefe1760f,// 126 PAY  92 

    0xd6438f2e,// 127 PAY  93 

    0x777c4f0b,// 128 PAY  94 

    0x9e07f9b0,// 129 PAY  95 

    0x00a9e900,// 130 PAY  96 

    0xd9ff0ada,// 131 PAY  97 

    0xa0ee2462,// 132 PAY  98 

    0xbd01670b,// 133 PAY  99 

    0xa3d808dd,// 134 PAY 100 

    0xf08cc747,// 135 PAY 101 

    0xb1d62a5a,// 136 PAY 102 

    0xd965f48e,// 137 PAY 103 

    0x108cda0f,// 138 PAY 104 

    0x69839443,// 139 PAY 105 

    0x8d167e87,// 140 PAY 106 

    0x489e143d,// 141 PAY 107 

    0x38443208,// 142 PAY 108 

    0x74c49891,// 143 PAY 109 

    0x01804072,// 144 PAY 110 

    0x74fa275d,// 145 PAY 111 

    0x211d34ad,// 146 PAY 112 

    0xb45e3c1f,// 147 PAY 113 

    0x5a09a78a,// 148 PAY 114 

    0xa28b2b94,// 149 PAY 115 

    0xe6782c00,// 150 PAY 116 

/// STA is 1 words. 

/// STA num_pkts       : 13 

/// STA pkt_idx        : 80 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x9a 

    0x01419a0d // 151 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 96 (0x60) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt45_tmpl[] = {
    0xb8010060,// 1 CCH   1 

/// ECH cache_idx      : 0x01 

/// ECH pdu_tag        : 0x00 

    0x00010000,// 2 ECH   1 

/// SCX is 23 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv insert_icv check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000017,// 3 SCX   1 

    0x809148fc,// 4 SCX   2 

    0x000034c2,// 5 SCX   3 

    0x9f78582e,// 6 SCX   4 

    0x62a432b2,// 7 SCX   5 

    0x7bc68d8e,// 8 SCX   6 

    0x580fded0,// 9 SCX   7 

    0x7d6fd60f,// 10 SCX   8 

    0x77167012,// 11 SCX   9 

    0xa16fbf75,// 12 SCX  10 

    0xbdd5bdb5,// 13 SCX  11 

    0x1a297495,// 14 SCX  12 

    0x5ab5cd7b,// 15 SCX  13 

    0x0be1a228,// 16 SCX  14 

    0x56a87430,// 17 SCX  15 

    0x9fa765ce,// 18 SCX  16 

    0x65eb2fa1,// 19 SCX  17 

    0xecfc5c15,// 20 SCX  18 

    0x30159e0f,// 21 SCX  19 

    0x431bf231,// 22 SCX  20 

    0x0853598b,// 23 SCX  21 

    0x814f0ec3,// 24 SCX  22 

    0x9121e575,// 25 SCX  23 

/// BFD is 3 words. 

/// BFD tot_len        : 1980 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 294 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 294 

/// BFD lencrypto      : 8 

/// BFD ofstcrypto     : 252 

/// BFD (ofst+len)cry  : 260 

/// BFD ofstiv         : 148 

/// BFD ofsticv        : 1728 

    0x00000126,// 26 BFD   1 

    0x00fc0008,// 27 BFD   2 

    0x06c00094,// 28 BFD   3 

/// MFM is 3 words. 

/// MFM vldnibs        : 10 

    0x1000594d,// 29 MFM   1 

    0x5c5048ff,// 30 MFM   2 

    0x53cc0000,// 31 MFM   3 

/// BDA is 496 words. 

/// BDA size     is 1980 (0x7bc) 

/// BDA id       is 0xae4b 

    0x07bcae4b,// 32 BDA   1 

/// PAY Generic Data size   : 1980 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0x88e19dc1,// 33 PAY   1 

    0xffeed6ae,// 34 PAY   2 

    0x231d9ee1,// 35 PAY   3 

    0xc0b43afe,// 36 PAY   4 

    0x3f113c37,// 37 PAY   5 

    0x16afc947,// 38 PAY   6 

    0xa5710d88,// 39 PAY   7 

    0x38646275,// 40 PAY   8 

    0x09182bc9,// 41 PAY   9 

    0x04bcf778,// 42 PAY  10 

    0x9a1fcaa3,// 43 PAY  11 

    0x53c7e99f,// 44 PAY  12 

    0xa14682ae,// 45 PAY  13 

    0x95bddc1d,// 46 PAY  14 

    0x8359be55,// 47 PAY  15 

    0xf8bf660c,// 48 PAY  16 

    0x88865217,// 49 PAY  17 

    0x1b527864,// 50 PAY  18 

    0x862a9560,// 51 PAY  19 

    0xfaa1434c,// 52 PAY  20 

    0xdc05bfae,// 53 PAY  21 

    0x01b32149,// 54 PAY  22 

    0x068e6936,// 55 PAY  23 

    0x28e81a03,// 56 PAY  24 

    0xa2c92664,// 57 PAY  25 

    0xb0676c52,// 58 PAY  26 

    0xd28d49e1,// 59 PAY  27 

    0x1566d34b,// 60 PAY  28 

    0x27850bfc,// 61 PAY  29 

    0x9322456a,// 62 PAY  30 

    0x6fbf0805,// 63 PAY  31 

    0x6ccb5ce2,// 64 PAY  32 

    0x83b55891,// 65 PAY  33 

    0x1d544d3b,// 66 PAY  34 

    0xc93798ae,// 67 PAY  35 

    0xbd716ea3,// 68 PAY  36 

    0xe06eb71c,// 69 PAY  37 

    0xe636e2fa,// 70 PAY  38 

    0xb29c3df7,// 71 PAY  39 

    0xc26b0f0c,// 72 PAY  40 

    0x73db8482,// 73 PAY  41 

    0xc192f0e4,// 74 PAY  42 

    0x2b612b41,// 75 PAY  43 

    0x40539195,// 76 PAY  44 

    0x124e9c7a,// 77 PAY  45 

    0xf29a2f0c,// 78 PAY  46 

    0xd0252688,// 79 PAY  47 

    0x4f9d81a6,// 80 PAY  48 

    0x6247c27c,// 81 PAY  49 

    0x753fc5d8,// 82 PAY  50 

    0x8aa250a5,// 83 PAY  51 

    0x48a787ed,// 84 PAY  52 

    0x20116542,// 85 PAY  53 

    0x6f4f5ba9,// 86 PAY  54 

    0xa4b3ee68,// 87 PAY  55 

    0x0b2e0e75,// 88 PAY  56 

    0xac5d25aa,// 89 PAY  57 

    0x18cac41a,// 90 PAY  58 

    0x9bff17bd,// 91 PAY  59 

    0x83192ab1,// 92 PAY  60 

    0x6c8a8a2a,// 93 PAY  61 

    0xb4e64037,// 94 PAY  62 

    0x83307ed9,// 95 PAY  63 

    0x051482c8,// 96 PAY  64 

    0x3094aa8c,// 97 PAY  65 

    0x03c738c4,// 98 PAY  66 

    0x75484455,// 99 PAY  67 

    0x6e267ec0,// 100 PAY  68 

    0x33c71bde,// 101 PAY  69 

    0x430792e9,// 102 PAY  70 

    0xbe8d7909,// 103 PAY  71 

    0x6ca11771,// 104 PAY  72 

    0x3751eb80,// 105 PAY  73 

    0x462e7996,// 106 PAY  74 

    0x018a3644,// 107 PAY  75 

    0x601a0c46,// 108 PAY  76 

    0xa7865d48,// 109 PAY  77 

    0xaeca0c96,// 110 PAY  78 

    0x3f33dd77,// 111 PAY  79 

    0x8a56814b,// 112 PAY  80 

    0xb0e5d7d9,// 113 PAY  81 

    0xfb9e76a0,// 114 PAY  82 

    0x0d296dbe,// 115 PAY  83 

    0x70d66675,// 116 PAY  84 

    0x0b339d7d,// 117 PAY  85 

    0xda0c6d03,// 118 PAY  86 

    0x882342bd,// 119 PAY  87 

    0xa584fdf0,// 120 PAY  88 

    0x5e5af58c,// 121 PAY  89 

    0x5e527623,// 122 PAY  90 

    0xc6fa3ba4,// 123 PAY  91 

    0xb31cb3ee,// 124 PAY  92 

    0x1a9427d1,// 125 PAY  93 

    0x1c0369f1,// 126 PAY  94 

    0x8fc11b13,// 127 PAY  95 

    0xf1114633,// 128 PAY  96 

    0x837a8c1e,// 129 PAY  97 

    0xc001845b,// 130 PAY  98 

    0x4841432a,// 131 PAY  99 

    0x8cca8ee3,// 132 PAY 100 

    0x5a2b403e,// 133 PAY 101 

    0x3dc04cba,// 134 PAY 102 

    0xd2ddf2f2,// 135 PAY 103 

    0x3ac8c6b5,// 136 PAY 104 

    0x09584cf5,// 137 PAY 105 

    0xa962d5ff,// 138 PAY 106 

    0x31902b71,// 139 PAY 107 

    0x07725c00,// 140 PAY 108 

    0xa82caebb,// 141 PAY 109 

    0x34ba885d,// 142 PAY 110 

    0x71c518ab,// 143 PAY 111 

    0x1e5bfda2,// 144 PAY 112 

    0x06ac37a2,// 145 PAY 113 

    0xf39e6bfd,// 146 PAY 114 

    0xaceede11,// 147 PAY 115 

    0xe19ffbe0,// 148 PAY 116 

    0x967e3415,// 149 PAY 117 

    0x10432d56,// 150 PAY 118 

    0x83b1412b,// 151 PAY 119 

    0x20eae470,// 152 PAY 120 

    0x778d758a,// 153 PAY 121 

    0xe6621fe2,// 154 PAY 122 

    0x720130a2,// 155 PAY 123 

    0xc6960519,// 156 PAY 124 

    0xf00d2ec6,// 157 PAY 125 

    0x1d541f3c,// 158 PAY 126 

    0x45481bea,// 159 PAY 127 

    0x883ce1d5,// 160 PAY 128 

    0xe86eb1da,// 161 PAY 129 

    0xc20fc8ac,// 162 PAY 130 

    0xdd0173df,// 163 PAY 131 

    0xb4beb262,// 164 PAY 132 

    0x6e137d33,// 165 PAY 133 

    0x21aec037,// 166 PAY 134 

    0x36c36f94,// 167 PAY 135 

    0xd938d6fa,// 168 PAY 136 

    0x8325edc1,// 169 PAY 137 

    0x7d0c7147,// 170 PAY 138 

    0x2c2c5b59,// 171 PAY 139 

    0x95d3a466,// 172 PAY 140 

    0xa94f6f4f,// 173 PAY 141 

    0x35f407e4,// 174 PAY 142 

    0xff748851,// 175 PAY 143 

    0x82f0f155,// 176 PAY 144 

    0x1f72623b,// 177 PAY 145 

    0x4ca78316,// 178 PAY 146 

    0xbcbd6178,// 179 PAY 147 

    0xc0d3d571,// 180 PAY 148 

    0x805e76c6,// 181 PAY 149 

    0x3853c1f3,// 182 PAY 150 

    0x2d5545ee,// 183 PAY 151 

    0xc6413356,// 184 PAY 152 

    0xddc34df7,// 185 PAY 153 

    0xd2375494,// 186 PAY 154 

    0x41f2ca6d,// 187 PAY 155 

    0xd4cecf9a,// 188 PAY 156 

    0x2eb9ea6a,// 189 PAY 157 

    0x9f7baa87,// 190 PAY 158 

    0xd01f4500,// 191 PAY 159 

    0xcaac825a,// 192 PAY 160 

    0xb6e3ce1d,// 193 PAY 161 

    0x670d2de9,// 194 PAY 162 

    0x7becc031,// 195 PAY 163 

    0x75e8f238,// 196 PAY 164 

    0x1677df86,// 197 PAY 165 

    0xe029a071,// 198 PAY 166 

    0x99cf901a,// 199 PAY 167 

    0x4d64c9ea,// 200 PAY 168 

    0x173463a0,// 201 PAY 169 

    0x832cc218,// 202 PAY 170 

    0x7975e392,// 203 PAY 171 

    0xc07bd3f0,// 204 PAY 172 

    0x418dae49,// 205 PAY 173 

    0x66525cfa,// 206 PAY 174 

    0x05dde32b,// 207 PAY 175 

    0xa245ddfb,// 208 PAY 176 

    0x8243887a,// 209 PAY 177 

    0x02b7c1c7,// 210 PAY 178 

    0x2406c00c,// 211 PAY 179 

    0x5ec64b14,// 212 PAY 180 

    0x76cd6788,// 213 PAY 181 

    0x2ce86154,// 214 PAY 182 

    0x599d02df,// 215 PAY 183 

    0xa674312c,// 216 PAY 184 

    0xd35bf9be,// 217 PAY 185 

    0xca88f3eb,// 218 PAY 186 

    0x1b5f3715,// 219 PAY 187 

    0xe1d8ab66,// 220 PAY 188 

    0xc5ed2a66,// 221 PAY 189 

    0x73e9675c,// 222 PAY 190 

    0x73455690,// 223 PAY 191 

    0x7fa7a3e3,// 224 PAY 192 

    0xc5a99723,// 225 PAY 193 

    0x39c27018,// 226 PAY 194 

    0xcf5833f3,// 227 PAY 195 

    0x1020b380,// 228 PAY 196 

    0x52ab6e0a,// 229 PAY 197 

    0x03693e52,// 230 PAY 198 

    0xbb5fc633,// 231 PAY 199 

    0xdffcb986,// 232 PAY 200 

    0x617401c2,// 233 PAY 201 

    0x9afbd51c,// 234 PAY 202 

    0x1727afdd,// 235 PAY 203 

    0xa9414f1e,// 236 PAY 204 

    0x14c604ab,// 237 PAY 205 

    0x4c2027d2,// 238 PAY 206 

    0x800d3a5e,// 239 PAY 207 

    0xd2f7b344,// 240 PAY 208 

    0x87245942,// 241 PAY 209 

    0xf24bd1eb,// 242 PAY 210 

    0x867ac9d6,// 243 PAY 211 

    0x2c126907,// 244 PAY 212 

    0x170e36cc,// 245 PAY 213 

    0x46daeb51,// 246 PAY 214 

    0xd04c7c41,// 247 PAY 215 

    0x91b5bd85,// 248 PAY 216 

    0x6415235b,// 249 PAY 217 

    0x5b609cea,// 250 PAY 218 

    0x6ff0d514,// 251 PAY 219 

    0x2f3c4b79,// 252 PAY 220 

    0xfb4154c9,// 253 PAY 221 

    0x4f8d0579,// 254 PAY 222 

    0x54620d3c,// 255 PAY 223 

    0x162cd13d,// 256 PAY 224 

    0x3386c545,// 257 PAY 225 

    0x2200d1df,// 258 PAY 226 

    0x9d68fd9c,// 259 PAY 227 

    0xa032c846,// 260 PAY 228 

    0x1fdde4e2,// 261 PAY 229 

    0x7c42303e,// 262 PAY 230 

    0x6e4e16ab,// 263 PAY 231 

    0x7717e87c,// 264 PAY 232 

    0x65ca5128,// 265 PAY 233 

    0x2b3361dd,// 266 PAY 234 

    0xd2b6d9d6,// 267 PAY 235 

    0xa15af49c,// 268 PAY 236 

    0x0ce2085d,// 269 PAY 237 

    0x19b744a7,// 270 PAY 238 

    0x65bb2432,// 271 PAY 239 

    0x0917cd97,// 272 PAY 240 

    0x07881b10,// 273 PAY 241 

    0x903d3f5f,// 274 PAY 242 

    0xbf6dfe0f,// 275 PAY 243 

    0xcde186b7,// 276 PAY 244 

    0x23d2629e,// 277 PAY 245 

    0x1d2c5b74,// 278 PAY 246 

    0x031b36ab,// 279 PAY 247 

    0x324b1ad9,// 280 PAY 248 

    0x8761d56f,// 281 PAY 249 

    0xdff1655a,// 282 PAY 250 

    0xbb469f91,// 283 PAY 251 

    0xc76c97f9,// 284 PAY 252 

    0xf765a067,// 285 PAY 253 

    0x73a65bea,// 286 PAY 254 

    0x295d0db6,// 287 PAY 255 

    0x45710d01,// 288 PAY 256 

    0xc134e0f7,// 289 PAY 257 

    0x265413c8,// 290 PAY 258 

    0xa36373ed,// 291 PAY 259 

    0xf8965251,// 292 PAY 260 

    0x2bb7a13f,// 293 PAY 261 

    0x8cd0ba22,// 294 PAY 262 

    0x4f083f1b,// 295 PAY 263 

    0x04dff404,// 296 PAY 264 

    0xbf4a9e93,// 297 PAY 265 

    0x9f5f4332,// 298 PAY 266 

    0x213c7590,// 299 PAY 267 

    0x8b1fac65,// 300 PAY 268 

    0x8a86a9eb,// 301 PAY 269 

    0x14debec7,// 302 PAY 270 

    0xd19f6544,// 303 PAY 271 

    0xd91abd1a,// 304 PAY 272 

    0x67c44cc2,// 305 PAY 273 

    0xb5a4f43d,// 306 PAY 274 

    0x7b58796b,// 307 PAY 275 

    0xb1786770,// 308 PAY 276 

    0x3e7c9daa,// 309 PAY 277 

    0x41049e14,// 310 PAY 278 

    0x16f96519,// 311 PAY 279 

    0xbac94e14,// 312 PAY 280 

    0xa4e576a2,// 313 PAY 281 

    0x6509b2f5,// 314 PAY 282 

    0x28ceeb74,// 315 PAY 283 

    0x914a3b7b,// 316 PAY 284 

    0x65b6d6d4,// 317 PAY 285 

    0x6c7e1dc3,// 318 PAY 286 

    0xdf255335,// 319 PAY 287 

    0x76afb062,// 320 PAY 288 

    0xddbb3c19,// 321 PAY 289 

    0xd72cff5c,// 322 PAY 290 

    0xc1202bde,// 323 PAY 291 

    0x3e40d739,// 324 PAY 292 

    0x25ff283d,// 325 PAY 293 

    0x53db243e,// 326 PAY 294 

    0x679f0626,// 327 PAY 295 

    0x7c4ccc3f,// 328 PAY 296 

    0xc8326ab1,// 329 PAY 297 

    0x9b209bea,// 330 PAY 298 

    0x7b7bec46,// 331 PAY 299 

    0x3d3227de,// 332 PAY 300 

    0x10ef2162,// 333 PAY 301 

    0x94d02d44,// 334 PAY 302 

    0xc85d4cc0,// 335 PAY 303 

    0xbe0e11e5,// 336 PAY 304 

    0xe0ccedc8,// 337 PAY 305 

    0x06a4d0fa,// 338 PAY 306 

    0x3872461a,// 339 PAY 307 

    0xc1ede095,// 340 PAY 308 

    0x2e7c275b,// 341 PAY 309 

    0x7abb90f2,// 342 PAY 310 

    0x594fd48f,// 343 PAY 311 

    0xb6d29c27,// 344 PAY 312 

    0x669e96c6,// 345 PAY 313 

    0x2c883f79,// 346 PAY 314 

    0xfca1d23c,// 347 PAY 315 

    0x3d817cbf,// 348 PAY 316 

    0xde1c845d,// 349 PAY 317 

    0x54becce8,// 350 PAY 318 

    0xd0db5fbf,// 351 PAY 319 

    0x8e5f63e8,// 352 PAY 320 

    0x06e49eb5,// 353 PAY 321 

    0x5e2cc574,// 354 PAY 322 

    0x1310581d,// 355 PAY 323 

    0x3e3849b4,// 356 PAY 324 

    0x023af647,// 357 PAY 325 

    0xc13c0966,// 358 PAY 326 

    0x5316037a,// 359 PAY 327 

    0x93e149ad,// 360 PAY 328 

    0x74bad2f0,// 361 PAY 329 

    0x89962fe0,// 362 PAY 330 

    0xad914cf7,// 363 PAY 331 

    0x3c073bf0,// 364 PAY 332 

    0xfa9780d6,// 365 PAY 333 

    0x760bf921,// 366 PAY 334 

    0xe9fac2a4,// 367 PAY 335 

    0xe26a0447,// 368 PAY 336 

    0x1acbd9d2,// 369 PAY 337 

    0xf0cd80ae,// 370 PAY 338 

    0xa640a73a,// 371 PAY 339 

    0x80e3c7c2,// 372 PAY 340 

    0xe3c75437,// 373 PAY 341 

    0xe010eb87,// 374 PAY 342 

    0xa192e6c8,// 375 PAY 343 

    0xf8c5641d,// 376 PAY 344 

    0x2f7ec1e6,// 377 PAY 345 

    0x19cd58dd,// 378 PAY 346 

    0x436c4eca,// 379 PAY 347 

    0xc045443a,// 380 PAY 348 

    0xb87e442e,// 381 PAY 349 

    0x698b7c0d,// 382 PAY 350 

    0x295be789,// 383 PAY 351 

    0xc0b30594,// 384 PAY 352 

    0xee20af2f,// 385 PAY 353 

    0xe2de8d91,// 386 PAY 354 

    0xdfea6f91,// 387 PAY 355 

    0xd3bed7c7,// 388 PAY 356 

    0xdf438663,// 389 PAY 357 

    0x52f167b4,// 390 PAY 358 

    0x41a40bee,// 391 PAY 359 

    0xd0fa1880,// 392 PAY 360 

    0x6012a883,// 393 PAY 361 

    0x6d72b18e,// 394 PAY 362 

    0xa763a1cc,// 395 PAY 363 

    0x8c44956b,// 396 PAY 364 

    0x7b7f61cf,// 397 PAY 365 

    0xa26e55d1,// 398 PAY 366 

    0x17a670e2,// 399 PAY 367 

    0x4eb88f52,// 400 PAY 368 

    0xe7c64b51,// 401 PAY 369 

    0x578a741c,// 402 PAY 370 

    0x2743e2ab,// 403 PAY 371 

    0x2c4a1e7c,// 404 PAY 372 

    0x7bbb9756,// 405 PAY 373 

    0x36e6157e,// 406 PAY 374 

    0xf952601b,// 407 PAY 375 

    0x8b3d3d21,// 408 PAY 376 

    0x52dbb36e,// 409 PAY 377 

    0x799a15e2,// 410 PAY 378 

    0xcfa1924d,// 411 PAY 379 

    0x24bc38f4,// 412 PAY 380 

    0x21e1bda5,// 413 PAY 381 

    0x3637a463,// 414 PAY 382 

    0x5b9ac262,// 415 PAY 383 

    0x090acfcd,// 416 PAY 384 

    0x1772b0e2,// 417 PAY 385 

    0x44247bd9,// 418 PAY 386 

    0xf802046f,// 419 PAY 387 

    0xb13e7f4e,// 420 PAY 388 

    0x3a04b4ff,// 421 PAY 389 

    0x1aaec2ad,// 422 PAY 390 

    0x58019a65,// 423 PAY 391 

    0x0247da2f,// 424 PAY 392 

    0x72be2f09,// 425 PAY 393 

    0x4ae88846,// 426 PAY 394 

    0x79b1add6,// 427 PAY 395 

    0x02e3d4e7,// 428 PAY 396 

    0xf2fad9c2,// 429 PAY 397 

    0x54e694fa,// 430 PAY 398 

    0x0a9718f5,// 431 PAY 399 

    0xf1fa0882,// 432 PAY 400 

    0x05e728b4,// 433 PAY 401 

    0xa5c2fa62,// 434 PAY 402 

    0x77e23a78,// 435 PAY 403 

    0x015fd9c1,// 436 PAY 404 

    0xd3fec01d,// 437 PAY 405 

    0x6561ac96,// 438 PAY 406 

    0x8bbd3b71,// 439 PAY 407 

    0x24bc3ca6,// 440 PAY 408 

    0x3b1cde94,// 441 PAY 409 

    0xa21e6cc1,// 442 PAY 410 

    0xafaa9f83,// 443 PAY 411 

    0xef848705,// 444 PAY 412 

    0x18dad722,// 445 PAY 413 

    0xeabdcb82,// 446 PAY 414 

    0xea3e4e85,// 447 PAY 415 

    0x200a745c,// 448 PAY 416 

    0xcff99c8d,// 449 PAY 417 

    0xc2674ff1,// 450 PAY 418 

    0x98d59988,// 451 PAY 419 

    0xb225edd6,// 452 PAY 420 

    0xd46838c6,// 453 PAY 421 

    0x1446bcd3,// 454 PAY 422 

    0x6293107e,// 455 PAY 423 

    0xb47e4b4f,// 456 PAY 424 

    0xb3799b76,// 457 PAY 425 

    0x4fb0f62e,// 458 PAY 426 

    0x5cff24a0,// 459 PAY 427 

    0x2af2cbdd,// 460 PAY 428 

    0x45dc0456,// 461 PAY 429 

    0x3388cb53,// 462 PAY 430 

    0x92381966,// 463 PAY 431 

    0xd8c574bb,// 464 PAY 432 

    0x5e788dfb,// 465 PAY 433 

    0x25f7b1eb,// 466 PAY 434 

    0x7bebde96,// 467 PAY 435 

    0xa8dfc78a,// 468 PAY 436 

    0xba300dd7,// 469 PAY 437 

    0x71d6ed5a,// 470 PAY 438 

    0x4aa52642,// 471 PAY 439 

    0x75908772,// 472 PAY 440 

    0xdb9f8a2c,// 473 PAY 441 

    0x494c8ffb,// 474 PAY 442 

    0xe304fc85,// 475 PAY 443 

    0x317f98fa,// 476 PAY 444 

    0x2c4e6721,// 477 PAY 445 

    0xca5177aa,// 478 PAY 446 

    0x726d4363,// 479 PAY 447 

    0x9e6d65d5,// 480 PAY 448 

    0xb760f9d3,// 481 PAY 449 

    0x7d5dffbb,// 482 PAY 450 

    0x158f3ed0,// 483 PAY 451 

    0x382aecb1,// 484 PAY 452 

    0xb8c8491a,// 485 PAY 453 

    0x079cd241,// 486 PAY 454 

    0xcd4c3fd1,// 487 PAY 455 

    0xb9b46b11,// 488 PAY 456 

    0x9dd9cc98,// 489 PAY 457 

    0x7f7da70d,// 490 PAY 458 

    0xcb1ba2ec,// 491 PAY 459 

    0x9d09a013,// 492 PAY 460 

    0xf9542abb,// 493 PAY 461 

    0x8a214241,// 494 PAY 462 

    0xfd48693c,// 495 PAY 463 

    0xd80b504d,// 496 PAY 464 

    0xa2d21b4e,// 497 PAY 465 

    0xc0d0d50a,// 498 PAY 466 

    0xe0ac183e,// 499 PAY 467 

    0xba54c014,// 500 PAY 468 

    0xfc3c6b37,// 501 PAY 469 

    0x4a13fd6b,// 502 PAY 470 

    0x329a3863,// 503 PAY 471 

    0x5c095a75,// 504 PAY 472 

    0x32017b59,// 505 PAY 473 

    0x5d3b4691,// 506 PAY 474 

    0xea619a28,// 507 PAY 475 

    0x3b2d849f,// 508 PAY 476 

    0xd4c7e015,// 509 PAY 477 

    0x21d10239,// 510 PAY 478 

    0xd9316041,// 511 PAY 479 

    0x9a0297dd,// 512 PAY 480 

    0xecb87ba1,// 513 PAY 481 

    0x8340a146,// 514 PAY 482 

    0x5c27ad28,// 515 PAY 483 

    0xdf2ab27e,// 516 PAY 484 

    0xcca40895,// 517 PAY 485 

    0x6f428cd8,// 518 PAY 486 

    0x83479e71,// 519 PAY 487 

    0x7535899e,// 520 PAY 488 

    0x3d37768a,// 521 PAY 489 

    0x0e7cb0e5,// 522 PAY 490 

    0x3b12cc6f,// 523 PAY 491 

    0xf5e1bbd6,// 524 PAY 492 

    0x35bd88de,// 525 PAY 493 

    0x364f54d5,// 526 PAY 494 

    0x85270d4d,// 527 PAY 495 

/// STA is 1 words. 

/// STA num_pkts       : 173 

/// STA pkt_idx        : 179 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x3f 

    0x02cd3fad // 528 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt46_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x04 

/// ECH pdu_tag        : 0x00 

    0x00040000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv insert_icv check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000019,// 3 SCX   1 

    0x809248c9,// 4 SCX   2 

    0x00007482,// 5 SCX   3 

    0x164a6cc4,// 6 SCX   4 

    0xa57e338e,// 7 SCX   5 

    0x2bea1d50,// 8 SCX   6 

    0xa0c6170f,// 9 SCX   7 

    0x50a52017,// 10 SCX   8 

    0x25280611,// 11 SCX   9 

    0x302645f8,// 12 SCX  10 

    0x91ec6519,// 13 SCX  11 

    0x113ecd18,// 14 SCX  12 

    0xce9ee378,// 15 SCX  13 

    0xb963115f,// 16 SCX  14 

    0x5c4a2aa6,// 17 SCX  15 

    0xbc1d97cd,// 18 SCX  16 

    0xb9c96f89,// 19 SCX  17 

    0xc641d8f0,// 20 SCX  18 

    0x21a4f0c5,// 21 SCX  19 

    0x6df460d0,// 22 SCX  20 

    0xddf46c1b,// 23 SCX  21 

    0xc1970402,// 24 SCX  22 

    0xf3b2cfb7,// 25 SCX  23 

    0x733c676e,// 26 SCX  24 

    0xa37dfd2c,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 1605 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 1490 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1490 

/// BFD lencrypto      : 752 

/// BFD ofstcrypto     : 20 

/// BFD (ofst+len)cry  : 772 

/// BFD ofstiv         : 0 

/// BFD ofsticv        : 1532 

    0x000005d2,// 28 BFD   1 

    0x001402f0,// 29 BFD   2 

    0x05fc0000,// 30 BFD   3 

/// MFM is 4 words. 

/// MFM vldnibs        : 17 

    0x17000bad,// 31 MFM   1 

    0xe2c39a90,// 32 MFM   2 

    0xfb7b3cd8,// 33 MFM   3 

    0x1bc00000,// 34 MFM   4 

/// BDA is 403 words. 

/// BDA size     is 1605 (0x645) 

/// BDA id       is 0x3c4b 

    0x06453c4b,// 35 BDA   1 

/// PAY Generic Data size   : 1605 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x0fb295dd,// 36 PAY   1 

    0x266ef1ab,// 37 PAY   2 

    0xb4eed800,// 38 PAY   3 

    0xcaadb61a,// 39 PAY   4 

    0x45be5225,// 40 PAY   5 

    0x19cc0ad4,// 41 PAY   6 

    0x018f02d9,// 42 PAY   7 

    0x3ea2ec4a,// 43 PAY   8 

    0x8d5b4b71,// 44 PAY   9 

    0xc652f526,// 45 PAY  10 

    0xb61ce836,// 46 PAY  11 

    0xcd47d192,// 47 PAY  12 

    0xb2b0fb17,// 48 PAY  13 

    0xd39bfe7f,// 49 PAY  14 

    0x7ee2ad48,// 50 PAY  15 

    0xe3790d00,// 51 PAY  16 

    0x749c37e1,// 52 PAY  17 

    0x208d91da,// 53 PAY  18 

    0xb5e55e4d,// 54 PAY  19 

    0xb5c5939c,// 55 PAY  20 

    0xc52884b5,// 56 PAY  21 

    0x2178feff,// 57 PAY  22 

    0xa3946fee,// 58 PAY  23 

    0xc059cb2c,// 59 PAY  24 

    0xef923fdb,// 60 PAY  25 

    0xfa5af633,// 61 PAY  26 

    0x3bbc8f3d,// 62 PAY  27 

    0x0e09225d,// 63 PAY  28 

    0xb1c9837d,// 64 PAY  29 

    0x30fd6888,// 65 PAY  30 

    0x5791a227,// 66 PAY  31 

    0xb23bd5d6,// 67 PAY  32 

    0xb39ec6eb,// 68 PAY  33 

    0xce8badea,// 69 PAY  34 

    0x88d1afe0,// 70 PAY  35 

    0xdd835e2b,// 71 PAY  36 

    0xf760116d,// 72 PAY  37 

    0xcb0765e1,// 73 PAY  38 

    0xaf6ad2d3,// 74 PAY  39 

    0x377b409e,// 75 PAY  40 

    0x8b9b5d9f,// 76 PAY  41 

    0xdf89285c,// 77 PAY  42 

    0x36b84dbb,// 78 PAY  43 

    0x018de250,// 79 PAY  44 

    0x44180a62,// 80 PAY  45 

    0x30b10aec,// 81 PAY  46 

    0x7202aa63,// 82 PAY  47 

    0xb0011cf8,// 83 PAY  48 

    0x9215e2a5,// 84 PAY  49 

    0x2f799694,// 85 PAY  50 

    0xdb436b5a,// 86 PAY  51 

    0x42076e52,// 87 PAY  52 

    0xf998f00c,// 88 PAY  53 

    0x0dde3e4d,// 89 PAY  54 

    0x794fa4fb,// 90 PAY  55 

    0xdcd5e663,// 91 PAY  56 

    0xc5e148ac,// 92 PAY  57 

    0x5cf3f3d8,// 93 PAY  58 

    0x7cb203f4,// 94 PAY  59 

    0x27bbed3e,// 95 PAY  60 

    0x63c5f052,// 96 PAY  61 

    0x3508186f,// 97 PAY  62 

    0x4838cbc1,// 98 PAY  63 

    0xb2339959,// 99 PAY  64 

    0x1b64c885,// 100 PAY  65 

    0x7d45de5e,// 101 PAY  66 

    0x9caba5e1,// 102 PAY  67 

    0xf3d9deac,// 103 PAY  68 

    0x4462e99c,// 104 PAY  69 

    0x1e9443b0,// 105 PAY  70 

    0x02cbbcd1,// 106 PAY  71 

    0x52e10011,// 107 PAY  72 

    0xf590ac13,// 108 PAY  73 

    0xe6082976,// 109 PAY  74 

    0x47b0c735,// 110 PAY  75 

    0xbaff9cd8,// 111 PAY  76 

    0xf6463058,// 112 PAY  77 

    0x7bcb82ce,// 113 PAY  78 

    0x41ba18a1,// 114 PAY  79 

    0x73601061,// 115 PAY  80 

    0x7cfab5c8,// 116 PAY  81 

    0x87d42e18,// 117 PAY  82 

    0x10b4192d,// 118 PAY  83 

    0x505988cb,// 119 PAY  84 

    0xd77c984d,// 120 PAY  85 

    0xa40e946e,// 121 PAY  86 

    0xf5030679,// 122 PAY  87 

    0xa0ffd7cb,// 123 PAY  88 

    0x39660cc6,// 124 PAY  89 

    0xbc713bf1,// 125 PAY  90 

    0xa0f50ad3,// 126 PAY  91 

    0xd2ffeb50,// 127 PAY  92 

    0x2be72400,// 128 PAY  93 

    0x72394fa6,// 129 PAY  94 

    0x39488ef8,// 130 PAY  95 

    0xdfa67a62,// 131 PAY  96 

    0xcd92a87e,// 132 PAY  97 

    0xb3f44d00,// 133 PAY  98 

    0xd1c2b35f,// 134 PAY  99 

    0x9697f247,// 135 PAY 100 

    0xd515bfd4,// 136 PAY 101 

    0x15bd0ee8,// 137 PAY 102 

    0xce4f4617,// 138 PAY 103 

    0x5e3c6705,// 139 PAY 104 

    0xabcd9683,// 140 PAY 105 

    0xa70cbb57,// 141 PAY 106 

    0xf15051af,// 142 PAY 107 

    0x0912135a,// 143 PAY 108 

    0xf1ece1ae,// 144 PAY 109 

    0xed511b28,// 145 PAY 110 

    0x6ede7c3d,// 146 PAY 111 

    0xc1cb4525,// 147 PAY 112 

    0x4812e724,// 148 PAY 113 

    0xad5d9ad4,// 149 PAY 114 

    0x602873ba,// 150 PAY 115 

    0x82904019,// 151 PAY 116 

    0x89824629,// 152 PAY 117 

    0x7ac4fa1b,// 153 PAY 118 

    0x30b1da28,// 154 PAY 119 

    0xc885144b,// 155 PAY 120 

    0xf9a1372a,// 156 PAY 121 

    0x0b03b757,// 157 PAY 122 

    0x2fb4708c,// 158 PAY 123 

    0x5c5901af,// 159 PAY 124 

    0x686a9a1d,// 160 PAY 125 

    0xcb9599b4,// 161 PAY 126 

    0xced70e03,// 162 PAY 127 

    0x418c6ac3,// 163 PAY 128 

    0xc87b08ef,// 164 PAY 129 

    0xc418143e,// 165 PAY 130 

    0x57a3f971,// 166 PAY 131 

    0x89b77f12,// 167 PAY 132 

    0x255c30db,// 168 PAY 133 

    0x1d52e5e1,// 169 PAY 134 

    0xe62044ac,// 170 PAY 135 

    0x2889cc31,// 171 PAY 136 

    0x2e90d3c2,// 172 PAY 137 

    0x39329376,// 173 PAY 138 

    0xc965fef0,// 174 PAY 139 

    0xbd06beca,// 175 PAY 140 

    0xe03aa135,// 176 PAY 141 

    0xaff49408,// 177 PAY 142 

    0x2d444081,// 178 PAY 143 

    0x10c1c731,// 179 PAY 144 

    0x5bd8410c,// 180 PAY 145 

    0x61af16bb,// 181 PAY 146 

    0x98d391a4,// 182 PAY 147 

    0x9e7cafe9,// 183 PAY 148 

    0x02cdfc1a,// 184 PAY 149 

    0x216a9953,// 185 PAY 150 

    0x507d7aac,// 186 PAY 151 

    0xc78ffe23,// 187 PAY 152 

    0x9fa57385,// 188 PAY 153 

    0xe372355a,// 189 PAY 154 

    0x15e9dab5,// 190 PAY 155 

    0xf1e4ea17,// 191 PAY 156 

    0xa758907c,// 192 PAY 157 

    0xe2a8af11,// 193 PAY 158 

    0x3bffff5e,// 194 PAY 159 

    0xb4adb507,// 195 PAY 160 

    0xd1c2304b,// 196 PAY 161 

    0xb8273b5e,// 197 PAY 162 

    0xf2f20adf,// 198 PAY 163 

    0x17b55c88,// 199 PAY 164 

    0xce218f1c,// 200 PAY 165 

    0x742b8dc7,// 201 PAY 166 

    0xef7df4f4,// 202 PAY 167 

    0x73c1cfad,// 203 PAY 168 

    0xfa06daf0,// 204 PAY 169 

    0xa4e29cb7,// 205 PAY 170 

    0x84c63f64,// 206 PAY 171 

    0xa98f8523,// 207 PAY 172 

    0x98804a30,// 208 PAY 173 

    0x56cdab29,// 209 PAY 174 

    0x2daabb50,// 210 PAY 175 

    0x60815253,// 211 PAY 176 

    0x55053b91,// 212 PAY 177 

    0xb907fcc0,// 213 PAY 178 

    0x9d1731bb,// 214 PAY 179 

    0x6188ffb4,// 215 PAY 180 

    0x1a71b3ce,// 216 PAY 181 

    0xbc93b984,// 217 PAY 182 

    0x189e3963,// 218 PAY 183 

    0x1358bb63,// 219 PAY 184 

    0xdd03dd0d,// 220 PAY 185 

    0x0660c8ec,// 221 PAY 186 

    0xae615e66,// 222 PAY 187 

    0x3aca3b9a,// 223 PAY 188 

    0x1ecc3bb7,// 224 PAY 189 

    0x80893498,// 225 PAY 190 

    0x7dfa2a8a,// 226 PAY 191 

    0xe0d01dc3,// 227 PAY 192 

    0xe20fca91,// 228 PAY 193 

    0x4c016402,// 229 PAY 194 

    0xf9522d34,// 230 PAY 195 

    0x06262be5,// 231 PAY 196 

    0x5ce91d5f,// 232 PAY 197 

    0xc8716726,// 233 PAY 198 

    0x291a35d5,// 234 PAY 199 

    0x75dbf21c,// 235 PAY 200 

    0x329e9eef,// 236 PAY 201 

    0x0a6497ad,// 237 PAY 202 

    0x4b69a1b9,// 238 PAY 203 

    0x8fadf5df,// 239 PAY 204 

    0x7cbf5db3,// 240 PAY 205 

    0x29b88a74,// 241 PAY 206 

    0x7a86b89b,// 242 PAY 207 

    0xec9c8a8b,// 243 PAY 208 

    0xb98cc125,// 244 PAY 209 

    0xcfff294a,// 245 PAY 210 

    0x81367acd,// 246 PAY 211 

    0xc0888b96,// 247 PAY 212 

    0x61e91564,// 248 PAY 213 

    0x17a240d0,// 249 PAY 214 

    0xcd7c8189,// 250 PAY 215 

    0xe0fbb189,// 251 PAY 216 

    0x9ef9a593,// 252 PAY 217 

    0x2e72e775,// 253 PAY 218 

    0x2aff25c4,// 254 PAY 219 

    0x0b05a63e,// 255 PAY 220 

    0xa3911b3c,// 256 PAY 221 

    0x79a0932e,// 257 PAY 222 

    0x37258685,// 258 PAY 223 

    0xbf703731,// 259 PAY 224 

    0xebad2936,// 260 PAY 225 

    0xc00d84b0,// 261 PAY 226 

    0x093cc8b1,// 262 PAY 227 

    0xbc37110f,// 263 PAY 228 

    0x6eab4d41,// 264 PAY 229 

    0x28885975,// 265 PAY 230 

    0xb42f1cde,// 266 PAY 231 

    0xe0171a5d,// 267 PAY 232 

    0xcb442bd7,// 268 PAY 233 

    0x6c9c495b,// 269 PAY 234 

    0xdf760b14,// 270 PAY 235 

    0x9227ae77,// 271 PAY 236 

    0xaa36882c,// 272 PAY 237 

    0x0131126a,// 273 PAY 238 

    0x121ca70b,// 274 PAY 239 

    0x694e6301,// 275 PAY 240 

    0xbca2f6f9,// 276 PAY 241 

    0xa14f2e0a,// 277 PAY 242 

    0xb08b1b64,// 278 PAY 243 

    0x1bb801fb,// 279 PAY 244 

    0xc37ab33d,// 280 PAY 245 

    0x3c71766d,// 281 PAY 246 

    0x7078ce20,// 282 PAY 247 

    0x9f72147a,// 283 PAY 248 

    0x4422d1b3,// 284 PAY 249 

    0x9622c299,// 285 PAY 250 

    0x77427dea,// 286 PAY 251 

    0xeaea4fbd,// 287 PAY 252 

    0xcad0f24f,// 288 PAY 253 

    0x8dd25f57,// 289 PAY 254 

    0x3eda24c4,// 290 PAY 255 

    0x1e453343,// 291 PAY 256 

    0xfdd14321,// 292 PAY 257 

    0x60727473,// 293 PAY 258 

    0xffa202f7,// 294 PAY 259 

    0x78f53966,// 295 PAY 260 

    0x8b08129c,// 296 PAY 261 

    0x82de429d,// 297 PAY 262 

    0x2373d9b2,// 298 PAY 263 

    0xa84d30d3,// 299 PAY 264 

    0x147d3b4f,// 300 PAY 265 

    0xbba408df,// 301 PAY 266 

    0x8703d41f,// 302 PAY 267 

    0x69ffe851,// 303 PAY 268 

    0xf8f96324,// 304 PAY 269 

    0xa3a610f4,// 305 PAY 270 

    0xa04bd362,// 306 PAY 271 

    0xe9323e70,// 307 PAY 272 

    0x1a4c2e05,// 308 PAY 273 

    0x4279bde6,// 309 PAY 274 

    0x6965fe18,// 310 PAY 275 

    0x9f921037,// 311 PAY 276 

    0x4f3ed37c,// 312 PAY 277 

    0x0295e8cd,// 313 PAY 278 

    0xe467b2f1,// 314 PAY 279 

    0x6f0b5c47,// 315 PAY 280 

    0x2bbd75da,// 316 PAY 281 

    0xb4191f6b,// 317 PAY 282 

    0xe4db4c4d,// 318 PAY 283 

    0x435ece79,// 319 PAY 284 

    0x7b2acf08,// 320 PAY 285 

    0x35b6408b,// 321 PAY 286 

    0x4db06547,// 322 PAY 287 

    0x6bc0ca96,// 323 PAY 288 

    0x17d4b2fd,// 324 PAY 289 

    0xf489974b,// 325 PAY 290 

    0x4e709f98,// 326 PAY 291 

    0x71f6e530,// 327 PAY 292 

    0xfcf22b6d,// 328 PAY 293 

    0x3af87161,// 329 PAY 294 

    0x5d533ebd,// 330 PAY 295 

    0xdce53db1,// 331 PAY 296 

    0x272f980e,// 332 PAY 297 

    0x882ace3e,// 333 PAY 298 

    0x0a55bbb8,// 334 PAY 299 

    0xc9abe753,// 335 PAY 300 

    0x984a44ca,// 336 PAY 301 

    0xae511ce0,// 337 PAY 302 

    0x2ffd2764,// 338 PAY 303 

    0x02d35c76,// 339 PAY 304 

    0x02f64cac,// 340 PAY 305 

    0x57a976e9,// 341 PAY 306 

    0x56d8cebe,// 342 PAY 307 

    0x5135e6bc,// 343 PAY 308 

    0x8ad9ddec,// 344 PAY 309 

    0xfb904e27,// 345 PAY 310 

    0x71794eeb,// 346 PAY 311 

    0x03e6bebc,// 347 PAY 312 

    0x5caa2de4,// 348 PAY 313 

    0xb81cc043,// 349 PAY 314 

    0x15c50535,// 350 PAY 315 

    0x4e844aac,// 351 PAY 316 

    0xa03bdda2,// 352 PAY 317 

    0x41af51a8,// 353 PAY 318 

    0x705c2ffe,// 354 PAY 319 

    0xcc7bf6fd,// 355 PAY 320 

    0xcda17fe3,// 356 PAY 321 

    0x4360056d,// 357 PAY 322 

    0xda1b716e,// 358 PAY 323 

    0x3c4a9bf0,// 359 PAY 324 

    0x3720ea01,// 360 PAY 325 

    0x712303f2,// 361 PAY 326 

    0x040e3783,// 362 PAY 327 

    0xf20e9366,// 363 PAY 328 

    0x163d04f0,// 364 PAY 329 

    0x1d41fe8e,// 365 PAY 330 

    0x08f0c411,// 366 PAY 331 

    0x9f239e23,// 367 PAY 332 

    0x23e75e58,// 368 PAY 333 

    0xfb557d4b,// 369 PAY 334 

    0x75e9a125,// 370 PAY 335 

    0x1a3c9dfe,// 371 PAY 336 

    0xe95342a4,// 372 PAY 337 

    0x920104b2,// 373 PAY 338 

    0x3a44ac4a,// 374 PAY 339 

    0x07e0aa4f,// 375 PAY 340 

    0x21aff1f5,// 376 PAY 341 

    0x097ef1f1,// 377 PAY 342 

    0x9628c829,// 378 PAY 343 

    0x72a6254e,// 379 PAY 344 

    0x3d8a4ae4,// 380 PAY 345 

    0x60280f20,// 381 PAY 346 

    0x7f4ca83b,// 382 PAY 347 

    0x89cc29b9,// 383 PAY 348 

    0x5e5d3017,// 384 PAY 349 

    0x94cb84d5,// 385 PAY 350 

    0x499857c5,// 386 PAY 351 

    0x2853d131,// 387 PAY 352 

    0xdd7d83ec,// 388 PAY 353 

    0x2fb23857,// 389 PAY 354 

    0x66f302e6,// 390 PAY 355 

    0x66da4973,// 391 PAY 356 

    0x1dc72e97,// 392 PAY 357 

    0x864f920a,// 393 PAY 358 

    0xd66e6564,// 394 PAY 359 

    0x2591a852,// 395 PAY 360 

    0x7b1a47a2,// 396 PAY 361 

    0x5d760790,// 397 PAY 362 

    0x7655855a,// 398 PAY 363 

    0x23b65073,// 399 PAY 364 

    0x0fb71e8d,// 400 PAY 365 

    0x1e96f0de,// 401 PAY 366 

    0xc46be294,// 402 PAY 367 

    0xfd7b39a2,// 403 PAY 368 

    0xbf5794de,// 404 PAY 369 

    0x0d45adb1,// 405 PAY 370 

    0x152b0148,// 406 PAY 371 

    0x1dae3041,// 407 PAY 372 

    0xec427c3b,// 408 PAY 373 

    0x4ce3a7e4,// 409 PAY 374 

    0xf484cc36,// 410 PAY 375 

    0xeaa08481,// 411 PAY 376 

    0xb99d731b,// 412 PAY 377 

    0x74c21f26,// 413 PAY 378 

    0x75e5460c,// 414 PAY 379 

    0x2e61e9c1,// 415 PAY 380 

    0x6e517c73,// 416 PAY 381 

    0x0b32d726,// 417 PAY 382 

    0x21cf0bc4,// 418 PAY 383 

    0x1b5e0ce2,// 419 PAY 384 

    0xe7100bbc,// 420 PAY 385 

    0xeee1c01a,// 421 PAY 386 

    0x67e272dd,// 422 PAY 387 

    0x5e824666,// 423 PAY 388 

    0x70451715,// 424 PAY 389 

    0x130952f9,// 425 PAY 390 

    0x4d6ff172,// 426 PAY 391 

    0x89362f4d,// 427 PAY 392 

    0x79434b51,// 428 PAY 393 

    0x88d768b4,// 429 PAY 394 

    0xeb9b8a45,// 430 PAY 395 

    0xe948ec2a,// 431 PAY 396 

    0x740092d5,// 432 PAY 397 

    0xaca97ca3,// 433 PAY 398 

    0xb642fcf8,// 434 PAY 399 

    0x352a432c,// 435 PAY 400 

    0x1e37b583,// 436 PAY 401 

    0x58000000,// 437 PAY 402 

/// STA is 1 words. 

/// STA num_pkts       : 100 

/// STA pkt_idx        : 152 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x6f 

    0x02616f64 // 438 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 72 (0x48) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt47_tmpl[] = {
    0xb8010048,// 1 CCH   1 

/// ECH cache_idx      : 0x07 

/// ECH pdu_tag        : 0x00 

    0x00070000,// 2 ECH   1 

/// SCX is 17 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv !insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x2 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x00000011,// 3 SCX   1 

    0x8080486b,// 4 SCX   2 

    0x00000200,// 5 SCX   3 

    0xb349069b,// 6 SCX   4 

    0xd96ff58e,// 7 SCX   5 

    0x6bae1076,// 8 SCX   6 

    0xe0cd9012,// 9 SCX   7 

    0x627069f5,// 10 SCX   8 

    0x6344b4ea,// 11 SCX   9 

    0x36e60ed3,// 12 SCX  10 

    0xd16b9a80,// 13 SCX  11 

    0x4a2ed480,// 14 SCX  12 

    0xdbb5a8e6,// 15 SCX  13 

    0xd7ec1e4a,// 16 SCX  14 

    0xf4af6bdb,// 17 SCX  15 

    0x7f08d63b,// 18 SCX  16 

    0x9818ec16,// 19 SCX  17 

/// BFD is 3 words. 

/// BFD tot_len        : 1945 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 1160 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1160 

/// BFD lencrypto      : 224 

/// BFD ofstcrypto     : 920 

/// BFD (ofst+len)cry  : 1144 

/// BFD ofstiv         : 816 

/// BFD ofsticv        : 1800 

    0x00000488,// 20 BFD   1 

    0x039800e0,// 21 BFD   2 

    0x07080330,// 22 BFD   3 

/// MFM is 13 words. 

/// MFM vldnibs        : 64 

    0x64002c40,// 23 MFM   1 

    0x0939118b,// 24 MFM   2 

    0x9ae64480,// 25 MFM   3 

    0xe2cdb8a4,// 26 MFM   4 

    0x2d89e63f,// 27 MFM   5 

    0x8f67315b,// 28 MFM   6 

    0xa0c91808,// 29 MFM   7 

    0x4a5924bc,// 30 MFM   8 

    0xca3e023f,// 31 MFM   9 

    0x8bbcc152,// 32 MFM  10 

    0xde66eb20,// 33 MFM  11 

    0x228f9069,// 34 MFM  12 

    0x83b93745,// 35 MFM  13 

/// BDA is 488 words. 

/// BDA size     is 1945 (0x799) 

/// BDA id       is 0x4ac8 

    0x07994ac8,// 36 BDA   1 

/// PAY Generic Data size   : 1945 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x17f35a00,// 37 PAY   1 

    0x0ded7f2e,// 38 PAY   2 

    0xb71a4020,// 39 PAY   3 

    0x5c393370,// 40 PAY   4 

    0xed06343d,// 41 PAY   5 

    0xd3741901,// 42 PAY   6 

    0x3cf8dd80,// 43 PAY   7 

    0x350f900c,// 44 PAY   8 

    0x321fb5c2,// 45 PAY   9 

    0xee83bb94,// 46 PAY  10 

    0x2685ebdc,// 47 PAY  11 

    0x31d7f6c7,// 48 PAY  12 

    0x8c2d5b2a,// 49 PAY  13 

    0x62f1a843,// 50 PAY  14 

    0x6ba8297a,// 51 PAY  15 

    0x2ed49060,// 52 PAY  16 

    0x4f38675b,// 53 PAY  17 

    0x8795a9fa,// 54 PAY  18 

    0x46b9c08b,// 55 PAY  19 

    0xa83a873e,// 56 PAY  20 

    0xd9acf3d3,// 57 PAY  21 

    0x400d34ec,// 58 PAY  22 

    0x2a059c1c,// 59 PAY  23 

    0x022d0f89,// 60 PAY  24 

    0xf6650390,// 61 PAY  25 

    0x9b2d98ec,// 62 PAY  26 

    0xcda10488,// 63 PAY  27 

    0xf22e50cd,// 64 PAY  28 

    0x19a7dd6b,// 65 PAY  29 

    0xc988a04f,// 66 PAY  30 

    0xd46db5d5,// 67 PAY  31 

    0x7b6a0882,// 68 PAY  32 

    0xa1c64a84,// 69 PAY  33 

    0x1c244e06,// 70 PAY  34 

    0x1e845345,// 71 PAY  35 

    0xefadf28d,// 72 PAY  36 

    0xc8b20def,// 73 PAY  37 

    0xc3affeef,// 74 PAY  38 

    0x0f36b879,// 75 PAY  39 

    0xf7275e36,// 76 PAY  40 

    0x6325b9c0,// 77 PAY  41 

    0x3986845a,// 78 PAY  42 

    0xd01f43f8,// 79 PAY  43 

    0x8a5ac832,// 80 PAY  44 

    0x78952ead,// 81 PAY  45 

    0x862b075d,// 82 PAY  46 

    0x4fb6941d,// 83 PAY  47 

    0xf5054872,// 84 PAY  48 

    0x742e8f9f,// 85 PAY  49 

    0xd30d52a7,// 86 PAY  50 

    0x3dfa95a6,// 87 PAY  51 

    0x5b1918d2,// 88 PAY  52 

    0x632d6b7f,// 89 PAY  53 

    0x1867ae34,// 90 PAY  54 

    0x62e0eb60,// 91 PAY  55 

    0x54832774,// 92 PAY  56 

    0x723f007a,// 93 PAY  57 

    0x4a291b7d,// 94 PAY  58 

    0xb18e3a0d,// 95 PAY  59 

    0x0e18628c,// 96 PAY  60 

    0x15efb77c,// 97 PAY  61 

    0xb6f850f1,// 98 PAY  62 

    0x1a494bb1,// 99 PAY  63 

    0x10285c1b,// 100 PAY  64 

    0x3b55d23f,// 101 PAY  65 

    0x77763c81,// 102 PAY  66 

    0xa94a418a,// 103 PAY  67 

    0x051087d8,// 104 PAY  68 

    0x791fd616,// 105 PAY  69 

    0xcc051808,// 106 PAY  70 

    0xfe2cf169,// 107 PAY  71 

    0x9a955c31,// 108 PAY  72 

    0x1b67283f,// 109 PAY  73 

    0xf15c78fe,// 110 PAY  74 

    0x92ebeb70,// 111 PAY  75 

    0x7480f49d,// 112 PAY  76 

    0x80370a37,// 113 PAY  77 

    0xae2b9984,// 114 PAY  78 

    0x010c8966,// 115 PAY  79 

    0x288f7b31,// 116 PAY  80 

    0xdec5b5ab,// 117 PAY  81 

    0x70542d20,// 118 PAY  82 

    0x29d06881,// 119 PAY  83 

    0x1734f7c1,// 120 PAY  84 

    0xfaa08535,// 121 PAY  85 

    0xca9345e1,// 122 PAY  86 

    0xfff691a2,// 123 PAY  87 

    0xe4c78df8,// 124 PAY  88 

    0x1f447709,// 125 PAY  89 

    0x5e938c9c,// 126 PAY  90 

    0xf8107fef,// 127 PAY  91 

    0x9a6a0ac2,// 128 PAY  92 

    0x9fe0c207,// 129 PAY  93 

    0xd7b35a65,// 130 PAY  94 

    0xfd6301df,// 131 PAY  95 

    0xc0b32da3,// 132 PAY  96 

    0x60964545,// 133 PAY  97 

    0x1948dbda,// 134 PAY  98 

    0x7b716c47,// 135 PAY  99 

    0x32a3eb97,// 136 PAY 100 

    0x7f0f46f6,// 137 PAY 101 

    0xfb6e53e7,// 138 PAY 102 

    0xeb426bc1,// 139 PAY 103 

    0xde8ae597,// 140 PAY 104 

    0x05531453,// 141 PAY 105 

    0x41f609b8,// 142 PAY 106 

    0x04cea21c,// 143 PAY 107 

    0x19068d00,// 144 PAY 108 

    0xc917ccc7,// 145 PAY 109 

    0x3d291894,// 146 PAY 110 

    0x91bd823d,// 147 PAY 111 

    0xf58b968b,// 148 PAY 112 

    0xce978ab3,// 149 PAY 113 

    0xa8d77d05,// 150 PAY 114 

    0xb9c0a016,// 151 PAY 115 

    0xa6a5fd63,// 152 PAY 116 

    0x93f0057d,// 153 PAY 117 

    0xd846882e,// 154 PAY 118 

    0xc926adb5,// 155 PAY 119 

    0x10ca82ca,// 156 PAY 120 

    0x49061f28,// 157 PAY 121 

    0x68c75ae2,// 158 PAY 122 

    0x5441c969,// 159 PAY 123 

    0x1c649dc8,// 160 PAY 124 

    0x7d99a73b,// 161 PAY 125 

    0x30b379cc,// 162 PAY 126 

    0xdbf77a7c,// 163 PAY 127 

    0x6c6f3bf1,// 164 PAY 128 

    0x4809dcbc,// 165 PAY 129 

    0x4bca84ff,// 166 PAY 130 

    0xbf5d1685,// 167 PAY 131 

    0xc3baa784,// 168 PAY 132 

    0x9ce4da13,// 169 PAY 133 

    0xa42b7eac,// 170 PAY 134 

    0xf7aea91f,// 171 PAY 135 

    0xbb7f6d1c,// 172 PAY 136 

    0xfa1cb82e,// 173 PAY 137 

    0x747988b5,// 174 PAY 138 

    0x2e2c688d,// 175 PAY 139 

    0xcba33a85,// 176 PAY 140 

    0xa44a2f73,// 177 PAY 141 

    0xcd217896,// 178 PAY 142 

    0x86349007,// 179 PAY 143 

    0xc4c3e7b2,// 180 PAY 144 

    0x0fd85f98,// 181 PAY 145 

    0x615a65c1,// 182 PAY 146 

    0xdc7e12f6,// 183 PAY 147 

    0xa6e3c618,// 184 PAY 148 

    0x64a2f546,// 185 PAY 149 

    0xfe779dca,// 186 PAY 150 

    0x8641e2e2,// 187 PAY 151 

    0xbbb65b9c,// 188 PAY 152 

    0x1b573d7d,// 189 PAY 153 

    0xd4c24ac8,// 190 PAY 154 

    0x9747b2ef,// 191 PAY 155 

    0xf5a7371c,// 192 PAY 156 

    0x3ef77425,// 193 PAY 157 

    0x8f9f3dd4,// 194 PAY 158 

    0x7687aee4,// 195 PAY 159 

    0x1bdb27fe,// 196 PAY 160 

    0x06014166,// 197 PAY 161 

    0xadec45b4,// 198 PAY 162 

    0x6a3973c6,// 199 PAY 163 

    0x41df9d10,// 200 PAY 164 

    0xf2268e6e,// 201 PAY 165 

    0x784893b1,// 202 PAY 166 

    0x8242c4b3,// 203 PAY 167 

    0xb171fd22,// 204 PAY 168 

    0x38ee964f,// 205 PAY 169 

    0x838479e7,// 206 PAY 170 

    0xd65f0cf1,// 207 PAY 171 

    0x47c896ef,// 208 PAY 172 

    0x5e41fd91,// 209 PAY 173 

    0xea4cb478,// 210 PAY 174 

    0xf3924d2f,// 211 PAY 175 

    0xb63fe9ce,// 212 PAY 176 

    0xfdca432e,// 213 PAY 177 

    0x0f326439,// 214 PAY 178 

    0x1143c356,// 215 PAY 179 

    0xaae994a6,// 216 PAY 180 

    0x1d3447e0,// 217 PAY 181 

    0x0b1a9a9c,// 218 PAY 182 

    0x53781d9e,// 219 PAY 183 

    0xf59f7fe0,// 220 PAY 184 

    0x9042a27b,// 221 PAY 185 

    0xf0e0737f,// 222 PAY 186 

    0x62d6d57f,// 223 PAY 187 

    0x24c6930f,// 224 PAY 188 

    0x726c6bf4,// 225 PAY 189 

    0xc8586970,// 226 PAY 190 

    0xe1992a2c,// 227 PAY 191 

    0x6f31a3cf,// 228 PAY 192 

    0xa9f2831b,// 229 PAY 193 

    0x1c1b8a89,// 230 PAY 194 

    0xd059bf35,// 231 PAY 195 

    0x8b269a02,// 232 PAY 196 

    0xd987e778,// 233 PAY 197 

    0xaf4ae694,// 234 PAY 198 

    0x1db17da6,// 235 PAY 199 

    0xf1c4dc01,// 236 PAY 200 

    0xe581f391,// 237 PAY 201 

    0x7d5a4e26,// 238 PAY 202 

    0x5af036f5,// 239 PAY 203 

    0xede7022b,// 240 PAY 204 

    0x0297c64c,// 241 PAY 205 

    0x1c7d3e76,// 242 PAY 206 

    0x7520d912,// 243 PAY 207 

    0xdd094c07,// 244 PAY 208 

    0xfd01914e,// 245 PAY 209 

    0x6c0e65c2,// 246 PAY 210 

    0x6de7e500,// 247 PAY 211 

    0x16afdfac,// 248 PAY 212 

    0xe428d327,// 249 PAY 213 

    0x76514834,// 250 PAY 214 

    0x15dc13b1,// 251 PAY 215 

    0xba0a1b1f,// 252 PAY 216 

    0xa2b5b1e8,// 253 PAY 217 

    0x452e3a3a,// 254 PAY 218 

    0x20fa34b5,// 255 PAY 219 

    0x67be082e,// 256 PAY 220 

    0x87c530e4,// 257 PAY 221 

    0x7302ec7c,// 258 PAY 222 

    0xbc79ad67,// 259 PAY 223 

    0x7c097852,// 260 PAY 224 

    0xa608a0ca,// 261 PAY 225 

    0xf2543939,// 262 PAY 226 

    0x71e42b03,// 263 PAY 227 

    0xf6b82f2a,// 264 PAY 228 

    0x75651669,// 265 PAY 229 

    0x6dff3192,// 266 PAY 230 

    0x075b30bc,// 267 PAY 231 

    0x81341a63,// 268 PAY 232 

    0x323b4cf6,// 269 PAY 233 

    0x8d24f81c,// 270 PAY 234 

    0xf5e0d2ae,// 271 PAY 235 

    0xbe0ed83d,// 272 PAY 236 

    0x919ce86d,// 273 PAY 237 

    0x5463dfc8,// 274 PAY 238 

    0x1d6fa303,// 275 PAY 239 

    0xb36da123,// 276 PAY 240 

    0x340ac3f6,// 277 PAY 241 

    0xd4dfa909,// 278 PAY 242 

    0x10bf5158,// 279 PAY 243 

    0xbf3ec17b,// 280 PAY 244 

    0xdf418da4,// 281 PAY 245 

    0xcb038b17,// 282 PAY 246 

    0x7cf74048,// 283 PAY 247 

    0x7a2188a1,// 284 PAY 248 

    0x955b03f5,// 285 PAY 249 

    0xe1d929d8,// 286 PAY 250 

    0xd5001bb1,// 287 PAY 251 

    0xb8702b07,// 288 PAY 252 

    0x6885fe9b,// 289 PAY 253 

    0x57cf9b7e,// 290 PAY 254 

    0x76bf2c1e,// 291 PAY 255 

    0x22d841ae,// 292 PAY 256 

    0x23aa14fe,// 293 PAY 257 

    0xfdf12643,// 294 PAY 258 

    0x88ff14ea,// 295 PAY 259 

    0x47205f63,// 296 PAY 260 

    0x56cdc041,// 297 PAY 261 

    0x3c24d501,// 298 PAY 262 

    0xc9383d3d,// 299 PAY 263 

    0x429e3c7a,// 300 PAY 264 

    0x0eb9b508,// 301 PAY 265 

    0x5f156e0c,// 302 PAY 266 

    0x719e2fe4,// 303 PAY 267 

    0xf6b13b17,// 304 PAY 268 

    0xa7f03ab6,// 305 PAY 269 

    0xd1951646,// 306 PAY 270 

    0xa175e5c8,// 307 PAY 271 

    0x2aca4f64,// 308 PAY 272 

    0x9ead57ae,// 309 PAY 273 

    0x1fb1632d,// 310 PAY 274 

    0xdc9a2570,// 311 PAY 275 

    0x300e6df1,// 312 PAY 276 

    0xd773efa5,// 313 PAY 277 

    0x0e5403ed,// 314 PAY 278 

    0x83d5182c,// 315 PAY 279 

    0x403b013d,// 316 PAY 280 

    0x3f7153ba,// 317 PAY 281 

    0x4ce2333a,// 318 PAY 282 

    0xe5d9f948,// 319 PAY 283 

    0x7c65e3c1,// 320 PAY 284 

    0x771a2ebf,// 321 PAY 285 

    0x9c131147,// 322 PAY 286 

    0xb9754d6b,// 323 PAY 287 

    0x2d39465e,// 324 PAY 288 

    0x69031601,// 325 PAY 289 

    0xe780a6fa,// 326 PAY 290 

    0xffb14adb,// 327 PAY 291 

    0x37b73ed4,// 328 PAY 292 

    0x88cdb3a5,// 329 PAY 293 

    0x1105974c,// 330 PAY 294 

    0x71b80376,// 331 PAY 295 

    0x3c2a7f0d,// 332 PAY 296 

    0x0741ff82,// 333 PAY 297 

    0x57bf746e,// 334 PAY 298 

    0x1ae91abf,// 335 PAY 299 

    0xf6d9962b,// 336 PAY 300 

    0xf4530633,// 337 PAY 301 

    0x250aae6b,// 338 PAY 302 

    0x30a43816,// 339 PAY 303 

    0x1e08d9ff,// 340 PAY 304 

    0xb4389376,// 341 PAY 305 

    0xa900c725,// 342 PAY 306 

    0xe902a5d6,// 343 PAY 307 

    0xba044446,// 344 PAY 308 

    0xad8c0ff7,// 345 PAY 309 

    0x2db40df7,// 346 PAY 310 

    0x2171e431,// 347 PAY 311 

    0x7b5fb96a,// 348 PAY 312 

    0x0a94724d,// 349 PAY 313 

    0x7d2c2aac,// 350 PAY 314 

    0xf4b999e1,// 351 PAY 315 

    0x8415e425,// 352 PAY 316 

    0x7347b2c8,// 353 PAY 317 

    0x6440c2f5,// 354 PAY 318 

    0x7ce57946,// 355 PAY 319 

    0xfbe70850,// 356 PAY 320 

    0x9ffb2cee,// 357 PAY 321 

    0xdb660e07,// 358 PAY 322 

    0x7245bd37,// 359 PAY 323 

    0x7da5a31d,// 360 PAY 324 

    0x31d9421d,// 361 PAY 325 

    0xd2adf2fd,// 362 PAY 326 

    0x2ca583e9,// 363 PAY 327 

    0xf21f34fe,// 364 PAY 328 

    0xed6db358,// 365 PAY 329 

    0xc266cfc1,// 366 PAY 330 

    0xa8c9a3ce,// 367 PAY 331 

    0xc9338271,// 368 PAY 332 

    0xf5ac9fec,// 369 PAY 333 

    0x050809b2,// 370 PAY 334 

    0x4ec47e52,// 371 PAY 335 

    0x7a1dcc48,// 372 PAY 336 

    0x23c028e6,// 373 PAY 337 

    0x04fc51d2,// 374 PAY 338 

    0xfaa03c58,// 375 PAY 339 

    0x4b068983,// 376 PAY 340 

    0xfe3b136e,// 377 PAY 341 

    0xd12556fc,// 378 PAY 342 

    0xd3e03137,// 379 PAY 343 

    0x3b658115,// 380 PAY 344 

    0x8e9d16b8,// 381 PAY 345 

    0x04e81e69,// 382 PAY 346 

    0xb0820219,// 383 PAY 347 

    0x396b4fbd,// 384 PAY 348 

    0x6baa3e73,// 385 PAY 349 

    0xafcbfac5,// 386 PAY 350 

    0x232c77f7,// 387 PAY 351 

    0x475cbc19,// 388 PAY 352 

    0xe89df8ee,// 389 PAY 353 

    0x272a6820,// 390 PAY 354 

    0x55c7e681,// 391 PAY 355 

    0x76a2f4d0,// 392 PAY 356 

    0x1bc14e5b,// 393 PAY 357 

    0xfabee65d,// 394 PAY 358 

    0x1d4fd39e,// 395 PAY 359 

    0x1228331a,// 396 PAY 360 

    0xb2cdc026,// 397 PAY 361 

    0xe07e5142,// 398 PAY 362 

    0x1361519c,// 399 PAY 363 

    0x3f572156,// 400 PAY 364 

    0x279afc36,// 401 PAY 365 

    0xc453117a,// 402 PAY 366 

    0x9f7bbdba,// 403 PAY 367 

    0xdc8ad25c,// 404 PAY 368 

    0x7d688183,// 405 PAY 369 

    0xe7660349,// 406 PAY 370 

    0x85434596,// 407 PAY 371 

    0x25c42d3c,// 408 PAY 372 

    0xa0f75c1c,// 409 PAY 373 

    0xb74e8619,// 410 PAY 374 

    0xd470183f,// 411 PAY 375 

    0x44b12bb7,// 412 PAY 376 

    0x1447508d,// 413 PAY 377 

    0x796b05eb,// 414 PAY 378 

    0x898cda80,// 415 PAY 379 

    0x18bc4030,// 416 PAY 380 

    0x69e51d20,// 417 PAY 381 

    0x4d597aea,// 418 PAY 382 

    0x32dfdff0,// 419 PAY 383 

    0x4c9c357f,// 420 PAY 384 

    0x175b8c5f,// 421 PAY 385 

    0x49c4bdec,// 422 PAY 386 

    0x73c12c22,// 423 PAY 387 

    0x87d8afd2,// 424 PAY 388 

    0x0cc37825,// 425 PAY 389 

    0xbcba6d08,// 426 PAY 390 

    0xed4815f2,// 427 PAY 391 

    0xffafc7ba,// 428 PAY 392 

    0x385d04d9,// 429 PAY 393 

    0x6c0bf8a1,// 430 PAY 394 

    0x326c1397,// 431 PAY 395 

    0xdd3ef823,// 432 PAY 396 

    0x964be5e7,// 433 PAY 397 

    0xf1ecda4e,// 434 PAY 398 

    0xf7a59f68,// 435 PAY 399 

    0x2120cd38,// 436 PAY 400 

    0xa8be8b0f,// 437 PAY 401 

    0xd7fe6476,// 438 PAY 402 

    0xc0dd664d,// 439 PAY 403 

    0x8ebcf7ab,// 440 PAY 404 

    0xeafec9d7,// 441 PAY 405 

    0xebd149f6,// 442 PAY 406 

    0xaa34a8ef,// 443 PAY 407 

    0x3686ed33,// 444 PAY 408 

    0xd6a2b890,// 445 PAY 409 

    0x89857fa0,// 446 PAY 410 

    0x8648caf0,// 447 PAY 411 

    0xef0ff8b2,// 448 PAY 412 

    0xe961a3d3,// 449 PAY 413 

    0x4888e893,// 450 PAY 414 

    0xf4272965,// 451 PAY 415 

    0xf7250e08,// 452 PAY 416 

    0xade4aaa4,// 453 PAY 417 

    0xb3e0f0ca,// 454 PAY 418 

    0xcb90f908,// 455 PAY 419 

    0xedeaa29b,// 456 PAY 420 

    0xd78fa992,// 457 PAY 421 

    0x7758d0d1,// 458 PAY 422 

    0x16024a96,// 459 PAY 423 

    0xbb519499,// 460 PAY 424 

    0x5db6ab48,// 461 PAY 425 

    0x28aad91a,// 462 PAY 426 

    0x2ed6df1f,// 463 PAY 427 

    0xb2e65132,// 464 PAY 428 

    0x436b96e4,// 465 PAY 429 

    0xa02a84bd,// 466 PAY 430 

    0x1c79f0f3,// 467 PAY 431 

    0xdae9aa38,// 468 PAY 432 

    0xbe251297,// 469 PAY 433 

    0x75b5f232,// 470 PAY 434 

    0xc85fc5e6,// 471 PAY 435 

    0x708e4bf5,// 472 PAY 436 

    0xb50997a0,// 473 PAY 437 

    0x54fac336,// 474 PAY 438 

    0xc95c423c,// 475 PAY 439 

    0xb91ef05b,// 476 PAY 440 

    0x44f99310,// 477 PAY 441 

    0x654b9a9a,// 478 PAY 442 

    0x6c527012,// 479 PAY 443 

    0x968416ee,// 480 PAY 444 

    0x126c236e,// 481 PAY 445 

    0x2d3b0a7b,// 482 PAY 446 

    0x90da20fc,// 483 PAY 447 

    0xb7c10c27,// 484 PAY 448 

    0x51e3462c,// 485 PAY 449 

    0x63dacada,// 486 PAY 450 

    0xe8a2b027,// 487 PAY 451 

    0x20af6b3e,// 488 PAY 452 

    0x588170e7,// 489 PAY 453 

    0xa42efb5c,// 490 PAY 454 

    0x698d4823,// 491 PAY 455 

    0xa02e5de6,// 492 PAY 456 

    0x8fb2e797,// 493 PAY 457 

    0x05973df7,// 494 PAY 458 

    0x86651f38,// 495 PAY 459 

    0x33c73096,// 496 PAY 460 

    0x515fbf78,// 497 PAY 461 

    0xca5c5cd8,// 498 PAY 462 

    0x9299a857,// 499 PAY 463 

    0x4a6a61d9,// 500 PAY 464 

    0x78977eae,// 501 PAY 465 

    0x8f485763,// 502 PAY 466 

    0x2b4d7a16,// 503 PAY 467 

    0x7d721c29,// 504 PAY 468 

    0xa7505e36,// 505 PAY 469 

    0xdba92987,// 506 PAY 470 

    0xe8a29aad,// 507 PAY 471 

    0xed9bc1ff,// 508 PAY 472 

    0xb9c6d742,// 509 PAY 473 

    0x1206646a,// 510 PAY 474 

    0x105d33cb,// 511 PAY 475 

    0xaf4725f3,// 512 PAY 476 

    0x4d1b748c,// 513 PAY 477 

    0xae55ebd8,// 514 PAY 478 

    0x9f5e646a,// 515 PAY 479 

    0x1974445a,// 516 PAY 480 

    0x66c906ab,// 517 PAY 481 

    0x7029a6cd,// 518 PAY 482 

    0xf6fb6cf8,// 519 PAY 483 

    0x39d28743,// 520 PAY 484 

    0xc1f3b39c,// 521 PAY 485 

    0x88fe148a,// 522 PAY 486 

    0xdd000000,// 523 PAY 487 

/// STA is 1 words. 

/// STA num_pkts       : 35 

/// STA pkt_idx        : 128 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xac 

    0x0200ac23 // 524 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt48_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x07 

/// ECH pdu_tag        : 0x00 

    0x00070000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv !insert_icv check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000015,// 3 SCX   1 

    0x80904814,// 4 SCX   2 

    0x000054c2,// 5 SCX   3 

    0xb15743af,// 6 SCX   4 

    0x4a858ebc,// 7 SCX   5 

    0x51def40a,// 8 SCX   6 

    0x5c4b1def,// 9 SCX   7 

    0xa6d5108e,// 10 SCX   8 

    0xf4b68ac4,// 11 SCX   9 

    0x2ea60d10,// 12 SCX  10 

    0x7afed544,// 13 SCX  11 

    0xcc5f565f,// 14 SCX  12 

    0x2f26e66c,// 15 SCX  13 

    0x48994281,// 16 SCX  14 

    0xca53f57b,// 17 SCX  15 

    0x677884ef,// 18 SCX  16 

    0xe15809e9,// 19 SCX  17 

    0xd0669ac3,// 20 SCX  18 

    0x15c23c0d,// 21 SCX  19 

    0x543964c6,// 22 SCX  20 

    0x109c15de,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1605 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 1551 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1551 

/// BFD lencrypto      : 116 

/// BFD ofstcrypto     : 716 

/// BFD (ofst+len)cry  : 832 

/// BFD ofstiv         : 504 

/// BFD ofsticv        : 1584 

    0x0000060f,// 24 BFD   1 

    0x02cc0074,// 25 BFD   2 

    0x063001f8,// 26 BFD   3 

/// MFM is 11 words. 

/// MFM vldnibs        : 52 

    0x52000ca6,// 27 MFM   1 

    0xbe0fb800,// 28 MFM   2 

    0x3169ebf8,// 29 MFM   3 

    0xa5c206c1,// 30 MFM   4 

    0x3f2cc7b0,// 31 MFM   5 

    0x4d4850ab,// 32 MFM   6 

    0xb6568d60,// 33 MFM   7 

    0x39feae7a,// 34 MFM   8 

    0x6d27873d,// 35 MFM   9 

    0xc074a4ad,// 36 MFM  10 

    0xc9cbe500,// 37 MFM  11 

/// BDA is 403 words. 

/// BDA size     is 1605 (0x645) 

/// BDA id       is 0x267c 

    0x0645267c,// 38 BDA   1 

/// PAY Generic Data size   : 1605 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0xfd8a6d05,// 39 PAY   1 

    0xb7f7937f,// 40 PAY   2 

    0x9044353c,// 41 PAY   3 

    0xbd0063ee,// 42 PAY   4 

    0x9b77f7c9,// 43 PAY   5 

    0x02691ac2,// 44 PAY   6 

    0x62205994,// 45 PAY   7 

    0x6c9615c4,// 46 PAY   8 

    0x10632f23,// 47 PAY   9 

    0xeba6508c,// 48 PAY  10 

    0xdd0f2b77,// 49 PAY  11 

    0x2136d884,// 50 PAY  12 

    0xcf547425,// 51 PAY  13 

    0x9c51664c,// 52 PAY  14 

    0x7652fb6b,// 53 PAY  15 

    0x06463ea4,// 54 PAY  16 

    0x31774c40,// 55 PAY  17 

    0xe3bd3206,// 56 PAY  18 

    0x731f357a,// 57 PAY  19 

    0x9e26b5d3,// 58 PAY  20 

    0xefbdfec7,// 59 PAY  21 

    0xa89d4c5a,// 60 PAY  22 

    0x977a205d,// 61 PAY  23 

    0x43f4288d,// 62 PAY  24 

    0x7e3283aa,// 63 PAY  25 

    0x2e9dbf83,// 64 PAY  26 

    0x9b254f1b,// 65 PAY  27 

    0x38386642,// 66 PAY  28 

    0x5f08fe9e,// 67 PAY  29 

    0xbfc1f3a6,// 68 PAY  30 

    0xd1185024,// 69 PAY  31 

    0x8bfaa05b,// 70 PAY  32 

    0x3da33c95,// 71 PAY  33 

    0x4edebd12,// 72 PAY  34 

    0xa530da24,// 73 PAY  35 

    0x89862e6b,// 74 PAY  36 

    0xf613f69b,// 75 PAY  37 

    0x24deab06,// 76 PAY  38 

    0x361ed05e,// 77 PAY  39 

    0xbd591020,// 78 PAY  40 

    0x03a4fe2e,// 79 PAY  41 

    0x4507e985,// 80 PAY  42 

    0x75702a5d,// 81 PAY  43 

    0x311d8d49,// 82 PAY  44 

    0xd09d1a42,// 83 PAY  45 

    0x3a7d8349,// 84 PAY  46 

    0x6c6412f2,// 85 PAY  47 

    0xf38c5ec5,// 86 PAY  48 

    0xb088fdef,// 87 PAY  49 

    0x2b8d67e2,// 88 PAY  50 

    0x420e98b4,// 89 PAY  51 

    0xd560d183,// 90 PAY  52 

    0x4e7739e4,// 91 PAY  53 

    0x7e0a9893,// 92 PAY  54 

    0x67ba2a95,// 93 PAY  55 

    0x0cf989d2,// 94 PAY  56 

    0x542f8ed6,// 95 PAY  57 

    0x35c5e8b2,// 96 PAY  58 

    0x8db2bbf2,// 97 PAY  59 

    0x057f245f,// 98 PAY  60 

    0x69192525,// 99 PAY  61 

    0x61044a67,// 100 PAY  62 

    0x9990a72c,// 101 PAY  63 

    0x5e3d6bad,// 102 PAY  64 

    0xe334ebb6,// 103 PAY  65 

    0xe6e8db5e,// 104 PAY  66 

    0x6875240e,// 105 PAY  67 

    0x8655b285,// 106 PAY  68 

    0x103909da,// 107 PAY  69 

    0x18a66106,// 108 PAY  70 

    0xbfa9f389,// 109 PAY  71 

    0xa22aa0b9,// 110 PAY  72 

    0x007fdeb7,// 111 PAY  73 

    0x8de72f78,// 112 PAY  74 

    0x5c4c4619,// 113 PAY  75 

    0xfbe3e0fa,// 114 PAY  76 

    0x0126c2b8,// 115 PAY  77 

    0xb3e39b74,// 116 PAY  78 

    0x0904992b,// 117 PAY  79 

    0x44c54f58,// 118 PAY  80 

    0x0e0870a3,// 119 PAY  81 

    0xc5043605,// 120 PAY  82 

    0x489fc72a,// 121 PAY  83 

    0x4fe12459,// 122 PAY  84 

    0x61b2a10b,// 123 PAY  85 

    0x69dd00cd,// 124 PAY  86 

    0x1173cf58,// 125 PAY  87 

    0xeac9da33,// 126 PAY  88 

    0xf37558d7,// 127 PAY  89 

    0x2ca5f6e5,// 128 PAY  90 

    0x1376a8f8,// 129 PAY  91 

    0xcdf9133e,// 130 PAY  92 

    0x134360c5,// 131 PAY  93 

    0x66105a34,// 132 PAY  94 

    0x06d6fafa,// 133 PAY  95 

    0x4207d9ed,// 134 PAY  96 

    0x92db5f1d,// 135 PAY  97 

    0xc87d3b48,// 136 PAY  98 

    0x3e26501d,// 137 PAY  99 

    0xb5be4a1e,// 138 PAY 100 

    0xbbd9804f,// 139 PAY 101 

    0xf92b461d,// 140 PAY 102 

    0x909ba325,// 141 PAY 103 

    0x3c3c1759,// 142 PAY 104 

    0xf825f482,// 143 PAY 105 

    0x8d461936,// 144 PAY 106 

    0xc9959efe,// 145 PAY 107 

    0x8d15949a,// 146 PAY 108 

    0xef6a90a4,// 147 PAY 109 

    0xab0822f8,// 148 PAY 110 

    0xc9696fde,// 149 PAY 111 

    0xf40e1d40,// 150 PAY 112 

    0xaa729350,// 151 PAY 113 

    0x12140b88,// 152 PAY 114 

    0x664051f4,// 153 PAY 115 

    0x24880281,// 154 PAY 116 

    0xd9023e99,// 155 PAY 117 

    0x0c30139d,// 156 PAY 118 

    0x7eb2d9c1,// 157 PAY 119 

    0x257b7c05,// 158 PAY 120 

    0x928f63ce,// 159 PAY 121 

    0x5c9d0533,// 160 PAY 122 

    0xb4830a20,// 161 PAY 123 

    0x6650b993,// 162 PAY 124 

    0xfc6bb893,// 163 PAY 125 

    0xf302b965,// 164 PAY 126 

    0x8dc0a0dd,// 165 PAY 127 

    0xdcba2c3b,// 166 PAY 128 

    0x40e697f0,// 167 PAY 129 

    0xb1b2c028,// 168 PAY 130 

    0x098939cb,// 169 PAY 131 

    0x4d5685f3,// 170 PAY 132 

    0xe4f3cfb1,// 171 PAY 133 

    0x74071fd2,// 172 PAY 134 

    0xcd664d61,// 173 PAY 135 

    0xc919ea4a,// 174 PAY 136 

    0xfc5d9446,// 175 PAY 137 

    0x868b99b4,// 176 PAY 138 

    0xcc07bcd8,// 177 PAY 139 

    0xd76d2abd,// 178 PAY 140 

    0x59a04541,// 179 PAY 141 

    0x2c13805e,// 180 PAY 142 

    0x11c0a8d7,// 181 PAY 143 

    0x71f3cd3a,// 182 PAY 144 

    0xb56fd72c,// 183 PAY 145 

    0xb2926990,// 184 PAY 146 

    0xcd4c5acb,// 185 PAY 147 

    0xcbf620fb,// 186 PAY 148 

    0x3b4cbd7f,// 187 PAY 149 

    0x48d728c5,// 188 PAY 150 

    0xc76a5cd9,// 189 PAY 151 

    0xad4f1522,// 190 PAY 152 

    0x6fb67422,// 191 PAY 153 

    0xd0b719b8,// 192 PAY 154 

    0x9a15fba9,// 193 PAY 155 

    0x3d6ca274,// 194 PAY 156 

    0x218fc112,// 195 PAY 157 

    0x30a7d83a,// 196 PAY 158 

    0x7e1db17a,// 197 PAY 159 

    0xa453d922,// 198 PAY 160 

    0x36dace76,// 199 PAY 161 

    0xdf1345b2,// 200 PAY 162 

    0x0dbf5b3d,// 201 PAY 163 

    0xee02bab8,// 202 PAY 164 

    0x9e65a2f7,// 203 PAY 165 

    0x09307173,// 204 PAY 166 

    0xfb15e4e0,// 205 PAY 167 

    0x68062d5f,// 206 PAY 168 

    0x19aa972d,// 207 PAY 169 

    0x0dcf41dc,// 208 PAY 170 

    0xadfc9fc3,// 209 PAY 171 

    0x3d6857cf,// 210 PAY 172 

    0xb6680e9f,// 211 PAY 173 

    0x0d29a7fe,// 212 PAY 174 

    0xb6b0affd,// 213 PAY 175 

    0xbaf1e349,// 214 PAY 176 

    0x4e5c5313,// 215 PAY 177 

    0xb99f0b67,// 216 PAY 178 

    0x4eb6b62b,// 217 PAY 179 

    0x499bb1cd,// 218 PAY 180 

    0xe77f033b,// 219 PAY 181 

    0x9f8270c4,// 220 PAY 182 

    0x1d4a41f6,// 221 PAY 183 

    0x2d3a4308,// 222 PAY 184 

    0x47ee9851,// 223 PAY 185 

    0x532ba18e,// 224 PAY 186 

    0x9dfd1984,// 225 PAY 187 

    0x34f54769,// 226 PAY 188 

    0xa5d73039,// 227 PAY 189 

    0xe67b70cc,// 228 PAY 190 

    0xce5f42df,// 229 PAY 191 

    0x2f856ca1,// 230 PAY 192 

    0x49c00ab2,// 231 PAY 193 

    0x2175a2a7,// 232 PAY 194 

    0x0cd50545,// 233 PAY 195 

    0xff8e8c31,// 234 PAY 196 

    0x6d512679,// 235 PAY 197 

    0x0310f232,// 236 PAY 198 

    0x230f4dd8,// 237 PAY 199 

    0x6372158e,// 238 PAY 200 

    0x6860d802,// 239 PAY 201 

    0xe262d946,// 240 PAY 202 

    0xd42edbe8,// 241 PAY 203 

    0x77352794,// 242 PAY 204 

    0x201b04c2,// 243 PAY 205 

    0xc9a2a53c,// 244 PAY 206 

    0xc5435d2e,// 245 PAY 207 

    0x49999d13,// 246 PAY 208 

    0x65f201af,// 247 PAY 209 

    0xb583dec7,// 248 PAY 210 

    0xbe8aa133,// 249 PAY 211 

    0x785c9cff,// 250 PAY 212 

    0x372b6871,// 251 PAY 213 

    0x3539a61e,// 252 PAY 214 

    0x4ce329ee,// 253 PAY 215 

    0x9a5db398,// 254 PAY 216 

    0x0e48abe2,// 255 PAY 217 

    0x245687be,// 256 PAY 218 

    0xce1ff15d,// 257 PAY 219 

    0xd089546c,// 258 PAY 220 

    0xb9730f9e,// 259 PAY 221 

    0x1b343d36,// 260 PAY 222 

    0xc800c15b,// 261 PAY 223 

    0xd3ea9de0,// 262 PAY 224 

    0xfbd7a42f,// 263 PAY 225 

    0x8b75fb41,// 264 PAY 226 

    0xfb7c8d90,// 265 PAY 227 

    0xb78c131d,// 266 PAY 228 

    0xe8b58efb,// 267 PAY 229 

    0x31561b4c,// 268 PAY 230 

    0xf41faff9,// 269 PAY 231 

    0x971af749,// 270 PAY 232 

    0x34bdf6f8,// 271 PAY 233 

    0xb23eda51,// 272 PAY 234 

    0x2d556bc8,// 273 PAY 235 

    0x32c7e3ff,// 274 PAY 236 

    0x4dddb3a4,// 275 PAY 237 

    0x993b8680,// 276 PAY 238 

    0xb63c4709,// 277 PAY 239 

    0x31ce7931,// 278 PAY 240 

    0xb88da4cd,// 279 PAY 241 

    0x98f4ef9b,// 280 PAY 242 

    0x5ddecf63,// 281 PAY 243 

    0xe6142c53,// 282 PAY 244 

    0x86c63222,// 283 PAY 245 

    0x827132b5,// 284 PAY 246 

    0x7d4c53cb,// 285 PAY 247 

    0x6ba27c80,// 286 PAY 248 

    0xc3b74cc8,// 287 PAY 249 

    0xc93082cb,// 288 PAY 250 

    0xad9461a1,// 289 PAY 251 

    0x0d43e94d,// 290 PAY 252 

    0xd699332a,// 291 PAY 253 

    0x80193bd3,// 292 PAY 254 

    0x2e2fe3d8,// 293 PAY 255 

    0xc8d233e9,// 294 PAY 256 

    0xaeeb88ec,// 295 PAY 257 

    0x039a0f4e,// 296 PAY 258 

    0x1ec15cab,// 297 PAY 259 

    0x9dd9e432,// 298 PAY 260 

    0xc94f8674,// 299 PAY 261 

    0x03808618,// 300 PAY 262 

    0x490a20ba,// 301 PAY 263 

    0xffcee243,// 302 PAY 264 

    0xa9d815e0,// 303 PAY 265 

    0xfe57d871,// 304 PAY 266 

    0xe1826c82,// 305 PAY 267 

    0xcbdf6c41,// 306 PAY 268 

    0x95faf059,// 307 PAY 269 

    0x22f06ad5,// 308 PAY 270 

    0x796dba96,// 309 PAY 271 

    0xcfffbeb7,// 310 PAY 272 

    0x6c206e63,// 311 PAY 273 

    0x9bb7fe60,// 312 PAY 274 

    0x7789a6c4,// 313 PAY 275 

    0xfaea8cb3,// 314 PAY 276 

    0xe42392cc,// 315 PAY 277 

    0x5b87e9b2,// 316 PAY 278 

    0x53edde08,// 317 PAY 279 

    0x263f41c3,// 318 PAY 280 

    0xdeafc8d9,// 319 PAY 281 

    0x26e526c0,// 320 PAY 282 

    0xf063924b,// 321 PAY 283 

    0xd413053f,// 322 PAY 284 

    0xa3ad8615,// 323 PAY 285 

    0xeb628b5f,// 324 PAY 286 

    0xbcacf7fe,// 325 PAY 287 

    0x7a90b9b2,// 326 PAY 288 

    0x93b2bd9a,// 327 PAY 289 

    0x312963db,// 328 PAY 290 

    0x1e46573d,// 329 PAY 291 

    0xdc0651d0,// 330 PAY 292 

    0x01267bcf,// 331 PAY 293 

    0x4a416639,// 332 PAY 294 

    0xcbdd60a9,// 333 PAY 295 

    0x69cdd288,// 334 PAY 296 

    0xcd6f637e,// 335 PAY 297 

    0x66e9d329,// 336 PAY 298 

    0x1f85979f,// 337 PAY 299 

    0x2d29d60b,// 338 PAY 300 

    0xf4d5387a,// 339 PAY 301 

    0x9925b0d3,// 340 PAY 302 

    0xb1b48d5d,// 341 PAY 303 

    0x9b27fa1c,// 342 PAY 304 

    0xb0a5aa2f,// 343 PAY 305 

    0xcec35821,// 344 PAY 306 

    0x1c9c9fe9,// 345 PAY 307 

    0xc2542d7b,// 346 PAY 308 

    0xbff41a63,// 347 PAY 309 

    0xdbb464e1,// 348 PAY 310 

    0xc2e2f861,// 349 PAY 311 

    0x59c0e5d9,// 350 PAY 312 

    0xb9c1af51,// 351 PAY 313 

    0x992ea003,// 352 PAY 314 

    0xcfc99dbf,// 353 PAY 315 

    0x2aef1860,// 354 PAY 316 

    0x29f8f580,// 355 PAY 317 

    0x1d3a4f0f,// 356 PAY 318 

    0xd15adc6e,// 357 PAY 319 

    0x26a0e74e,// 358 PAY 320 

    0x424a2cfa,// 359 PAY 321 

    0xd088901c,// 360 PAY 322 

    0x71269859,// 361 PAY 323 

    0xff737a8d,// 362 PAY 324 

    0x397d04f8,// 363 PAY 325 

    0xa52ae0aa,// 364 PAY 326 

    0xb883ace4,// 365 PAY 327 

    0x1f25e67e,// 366 PAY 328 

    0x11b29527,// 367 PAY 329 

    0xf0a27648,// 368 PAY 330 

    0x1bdae625,// 369 PAY 331 

    0x4cc5e173,// 370 PAY 332 

    0x1fc0279f,// 371 PAY 333 

    0xbb09934b,// 372 PAY 334 

    0xbe50f83c,// 373 PAY 335 

    0x2163faa5,// 374 PAY 336 

    0x5cb87f18,// 375 PAY 337 

    0xeab902dd,// 376 PAY 338 

    0xe9f51191,// 377 PAY 339 

    0x10d2e7ae,// 378 PAY 340 

    0x1502fd18,// 379 PAY 341 

    0x9d969f8e,// 380 PAY 342 

    0x412c06b4,// 381 PAY 343 

    0xc04d9788,// 382 PAY 344 

    0x14af3a4a,// 383 PAY 345 

    0xd400542f,// 384 PAY 346 

    0x91f919d1,// 385 PAY 347 

    0x0358fd8c,// 386 PAY 348 

    0x70f07c4d,// 387 PAY 349 

    0xebc6bf7a,// 388 PAY 350 

    0x82287cfa,// 389 PAY 351 

    0x1091f923,// 390 PAY 352 

    0xd0d34b95,// 391 PAY 353 

    0xd472c184,// 392 PAY 354 

    0xd4be5368,// 393 PAY 355 

    0xd6ca9570,// 394 PAY 356 

    0xf545f4fa,// 395 PAY 357 

    0xd9b6ef45,// 396 PAY 358 

    0x2d0301d2,// 397 PAY 359 

    0x7786cbb3,// 398 PAY 360 

    0x9e3bedcf,// 399 PAY 361 

    0x967632eb,// 400 PAY 362 

    0x0d7d444b,// 401 PAY 363 

    0xd52cf426,// 402 PAY 364 

    0xeb546712,// 403 PAY 365 

    0x2cd02de5,// 404 PAY 366 

    0x35ec7c70,// 405 PAY 367 

    0x142e66af,// 406 PAY 368 

    0x99b6aca6,// 407 PAY 369 

    0xc3fb6fbb,// 408 PAY 370 

    0xd657770e,// 409 PAY 371 

    0x6ba2668b,// 410 PAY 372 

    0x4e0b3e13,// 411 PAY 373 

    0xcc2c5090,// 412 PAY 374 

    0x34c7f10d,// 413 PAY 375 

    0xc7d909b7,// 414 PAY 376 

    0xdb8918c5,// 415 PAY 377 

    0xcf2b3789,// 416 PAY 378 

    0x364d1bb8,// 417 PAY 379 

    0xee129317,// 418 PAY 380 

    0x1f374f71,// 419 PAY 381 

    0x6533616f,// 420 PAY 382 

    0xee3b29ac,// 421 PAY 383 

    0x1a97a2a7,// 422 PAY 384 

    0xe4194674,// 423 PAY 385 

    0x7259005e,// 424 PAY 386 

    0x47541f9a,// 425 PAY 387 

    0xe36ee295,// 426 PAY 388 

    0x576c18e2,// 427 PAY 389 

    0xdf192761,// 428 PAY 390 

    0x5a073778,// 429 PAY 391 

    0x9980341f,// 430 PAY 392 

    0x4e380821,// 431 PAY 393 

    0x0da937c5,// 432 PAY 394 

    0x59d79ac8,// 433 PAY 395 

    0x69bf8c5a,// 434 PAY 396 

    0x7d134383,// 435 PAY 397 

    0xcb62d389,// 436 PAY 398 

    0x2e963eab,// 437 PAY 399 

    0x9889b195,// 438 PAY 400 

    0xef925fb0,// 439 PAY 401 

    0xd4000000,// 440 PAY 402 

/// STA is 1 words. 

/// STA num_pkts       : 144 

/// STA pkt_idx        : 108 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x1c 

    0x01b11c90 // 441 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt49_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x08 

/// ECH pdu_tag        : 0x00 

    0x00080000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x808448d6,// 4 SCX   2 

    0x000024c4,// 5 SCX   3 

    0x6ff5201a,// 6 SCX   4 

    0x582f24e3,// 7 SCX   5 

    0x07de19df,// 8 SCX   6 

    0xe58ddec5,// 9 SCX   7 

    0x8101776b,// 10 SCX   8 

    0x7e0c8986,// 11 SCX   9 

    0xd991c238,// 12 SCX  10 

    0xe3406364,// 13 SCX  11 

    0xe450215c,// 14 SCX  12 

    0x2de52ffe,// 15 SCX  13 

    0xa01a5cef,// 16 SCX  14 

    0xb340ed9d,// 17 SCX  15 

    0xf1157440,// 18 SCX  16 

    0x4afc1e6f,// 19 SCX  17 

    0x238b579d,// 20 SCX  18 

    0x16dfe21d,// 21 SCX  19 

    0xeb421aa0,// 22 SCX  20 

    0xb770f650,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 525 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 300 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 300 

/// BFD lencrypto      : 32 

/// BFD ofstcrypto     : 56 

/// BFD (ofst+len)cry  : 88 

/// BFD ofstiv         : 4 

/// BFD ofsticv        : 388 

    0x0000012c,// 24 BFD   1 

    0x00380020,// 25 BFD   2 

    0x01840004,// 26 BFD   3 

/// MFM is 7 words. 

/// MFM vldnibs        : 32 

    0x3200f655,// 27 MFM   1 

    0x0131464a,// 28 MFM   2 

    0x173da3b0,// 29 MFM   3 

    0x562fdf1f,// 30 MFM   4 

    0x8cf44431,// 31 MFM   5 

    0x696018fc,// 32 MFM   6 

    0x23913700,// 33 MFM   7 

/// BDA is 133 words. 

/// BDA size     is 525 (0x20d) 

/// BDA id       is 0x5630 

    0x020d5630,// 34 BDA   1 

/// PAY Generic Data size   : 525 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x541feb8f,// 35 PAY   1 

    0x5124c42a,// 36 PAY   2 

    0x2d3453fd,// 37 PAY   3 

    0xccf6eb4c,// 38 PAY   4 

    0x21bedbf6,// 39 PAY   5 

    0xa2bdebc1,// 40 PAY   6 

    0xe7f551bf,// 41 PAY   7 

    0xda5af626,// 42 PAY   8 

    0x603a69fd,// 43 PAY   9 

    0xb253c889,// 44 PAY  10 

    0xec7ec1fa,// 45 PAY  11 

    0x2b608290,// 46 PAY  12 

    0xc69d2d34,// 47 PAY  13 

    0xf2acb57b,// 48 PAY  14 

    0xb3d8bbb3,// 49 PAY  15 

    0x916dfc07,// 50 PAY  16 

    0x2d8925a8,// 51 PAY  17 

    0xfa99492b,// 52 PAY  18 

    0x0d445b13,// 53 PAY  19 

    0xee8b7cc0,// 54 PAY  20 

    0x3ad546e2,// 55 PAY  21 

    0xe9cef6a5,// 56 PAY  22 

    0x0dd58a81,// 57 PAY  23 

    0x692ff012,// 58 PAY  24 

    0x513baaeb,// 59 PAY  25 

    0xf778b767,// 60 PAY  26 

    0x66a487fb,// 61 PAY  27 

    0xfb3c5564,// 62 PAY  28 

    0xb8fac05f,// 63 PAY  29 

    0x84a2260d,// 64 PAY  30 

    0x229dad88,// 65 PAY  31 

    0x05078d99,// 66 PAY  32 

    0x0a56ab85,// 67 PAY  33 

    0x55baf04c,// 68 PAY  34 

    0xec255d5e,// 69 PAY  35 

    0x55d11901,// 70 PAY  36 

    0x4806ff07,// 71 PAY  37 

    0x264cbec0,// 72 PAY  38 

    0xbc74251a,// 73 PAY  39 

    0x55b4801b,// 74 PAY  40 

    0x76cf99ac,// 75 PAY  41 

    0x9c0ec0bf,// 76 PAY  42 

    0x617c74b1,// 77 PAY  43 

    0x94f0712b,// 78 PAY  44 

    0xe47460dc,// 79 PAY  45 

    0x58f2a2f2,// 80 PAY  46 

    0x820b7ebc,// 81 PAY  47 

    0x74d906e2,// 82 PAY  48 

    0xde1210a8,// 83 PAY  49 

    0xc0251594,// 84 PAY  50 

    0xa347b571,// 85 PAY  51 

    0x2d84c9a4,// 86 PAY  52 

    0xd9a392cd,// 87 PAY  53 

    0x111155c9,// 88 PAY  54 

    0xc063832f,// 89 PAY  55 

    0x943e77aa,// 90 PAY  56 

    0x3f052594,// 91 PAY  57 

    0x5e057a5b,// 92 PAY  58 

    0xac42bc5f,// 93 PAY  59 

    0x324d7084,// 94 PAY  60 

    0x449ca7d3,// 95 PAY  61 

    0x76fc9c5e,// 96 PAY  62 

    0x4c54e116,// 97 PAY  63 

    0x09ea6b90,// 98 PAY  64 

    0xd38cc668,// 99 PAY  65 

    0x5087a325,// 100 PAY  66 

    0x7a640920,// 101 PAY  67 

    0xd264d910,// 102 PAY  68 

    0x064329d6,// 103 PAY  69 

    0x0830c88c,// 104 PAY  70 

    0xae566630,// 105 PAY  71 

    0xdf2e5d8d,// 106 PAY  72 

    0x49f87ad6,// 107 PAY  73 

    0xeb068f2d,// 108 PAY  74 

    0x23039853,// 109 PAY  75 

    0xc1809163,// 110 PAY  76 

    0x6202cf6e,// 111 PAY  77 

    0xaa6d3fbc,// 112 PAY  78 

    0x5e6c39b4,// 113 PAY  79 

    0x40154798,// 114 PAY  80 

    0x8620b543,// 115 PAY  81 

    0x5666b9b4,// 116 PAY  82 

    0x11e15e40,// 117 PAY  83 

    0xa4a830c4,// 118 PAY  84 

    0x5e9a47ac,// 119 PAY  85 

    0x555e2c89,// 120 PAY  86 

    0xcd3343f1,// 121 PAY  87 

    0x486e3e84,// 122 PAY  88 

    0xc98980a2,// 123 PAY  89 

    0x4316e5fd,// 124 PAY  90 

    0xc6cb944e,// 125 PAY  91 

    0x9e993551,// 126 PAY  92 

    0x0ce39f1d,// 127 PAY  93 

    0xef686a2b,// 128 PAY  94 

    0xa5ee6b88,// 129 PAY  95 

    0xf7fb816c,// 130 PAY  96 

    0x36a2a7e9,// 131 PAY  97 

    0x16565df1,// 132 PAY  98 

    0x674e402c,// 133 PAY  99 

    0x83c02859,// 134 PAY 100 

    0xedba4396,// 135 PAY 101 

    0xfcae0978,// 136 PAY 102 

    0x7d76516d,// 137 PAY 103 

    0x8d95422d,// 138 PAY 104 

    0x17f71de5,// 139 PAY 105 

    0x75224a54,// 140 PAY 106 

    0xd39bfb6a,// 141 PAY 107 

    0xee31a0b8,// 142 PAY 108 

    0x39746012,// 143 PAY 109 

    0x5f3ec2c6,// 144 PAY 110 

    0x8a7624be,// 145 PAY 111 

    0x10950b22,// 146 PAY 112 

    0xf3683204,// 147 PAY 113 

    0x9acc281c,// 148 PAY 114 

    0x4cffa542,// 149 PAY 115 

    0x10d5185a,// 150 PAY 116 

    0x63a15a44,// 151 PAY 117 

    0x6acfa303,// 152 PAY 118 

    0x447aaf36,// 153 PAY 119 

    0x77e00163,// 154 PAY 120 

    0xc21fae96,// 155 PAY 121 

    0x48064ca1,// 156 PAY 122 

    0x3552b5f7,// 157 PAY 123 

    0x0cf50f6d,// 158 PAY 124 

    0x49bdbe1b,// 159 PAY 125 

    0xeca2dd89,// 160 PAY 126 

    0x792083c6,// 161 PAY 127 

    0x10f9d7bd,// 162 PAY 128 

    0x2f085e21,// 163 PAY 129 

    0x97c8dfa9,// 164 PAY 130 

    0xc04dc484,// 165 PAY 131 

    0x59000000,// 166 PAY 132 

/// STA is 1 words. 

/// STA num_pkts       : 101 

/// STA pkt_idx        : 196 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xce 

    0x0311ce65 // 167 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt50_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x0c 

/// ECH pdu_tag        : 0x00 

    0x000c0000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x2 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000019,// 3 SCX   1 

    0x808648d8,// 4 SCX   2 

    0x000052c4,// 5 SCX   3 

    0xe49e4c23,// 6 SCX   4 

    0x80ce95d7,// 7 SCX   5 

    0x678eb8fb,// 8 SCX   6 

    0xd26ec40d,// 9 SCX   7 

    0x6fd75bb2,// 10 SCX   8 

    0x3cf4e7c7,// 11 SCX   9 

    0xd87f753d,// 12 SCX  10 

    0xd1f2cd67,// 13 SCX  11 

    0x29bd030f,// 14 SCX  12 

    0x25b1063a,// 15 SCX  13 

    0xd5d265a4,// 16 SCX  14 

    0xa324d3dd,// 17 SCX  15 

    0x7d71a9f5,// 18 SCX  16 

    0xfc128d09,// 19 SCX  17 

    0x1ccb367b,// 20 SCX  18 

    0xe055472f,// 21 SCX  19 

    0x771631ca,// 22 SCX  20 

    0xad2abec0,// 23 SCX  21 

    0x397cae8b,// 24 SCX  22 

    0x61acf4d7,// 25 SCX  23 

    0x7ce8abed,// 26 SCX  24 

    0xf510246c,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 1143 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 302 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 302 

/// BFD lencrypto      : 224 

/// BFD ofstcrypto     : 32 

/// BFD (ofst+len)cry  : 256 

/// BFD ofstiv         : 12 

/// BFD ofsticv        : 1036 

    0x0000012e,// 28 BFD   1 

    0x002000e0,// 29 BFD   2 

    0x040c000c,// 30 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : 5 

    0x05005f49,// 31 MFM   1 

    0x60000000,// 32 MFM   2 

/// BDA is 287 words. 

/// BDA size     is 1143 (0x477) 

/// BDA id       is 0x3ee5 

    0x04773ee5,// 33 BDA   1 

/// PAY Generic Data size   : 1143 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0xa57f7cfd,// 34 PAY   1 

    0x587f72e6,// 35 PAY   2 

    0x3adadad5,// 36 PAY   3 

    0x318786dc,// 37 PAY   4 

    0x2f843933,// 38 PAY   5 

    0xff68ed61,// 39 PAY   6 

    0x564732b1,// 40 PAY   7 

    0xccf25fd6,// 41 PAY   8 

    0x9ea4b56b,// 42 PAY   9 

    0x9815e827,// 43 PAY  10 

    0xc955e146,// 44 PAY  11 

    0x590b9a84,// 45 PAY  12 

    0xf4b6df23,// 46 PAY  13 

    0x1bddf725,// 47 PAY  14 

    0x458db3c4,// 48 PAY  15 

    0xd2da09b6,// 49 PAY  16 

    0xb59a9099,// 50 PAY  17 

    0xd412c56e,// 51 PAY  18 

    0xb01bd8d2,// 52 PAY  19 

    0xf5f0a9f8,// 53 PAY  20 

    0x5b1c9661,// 54 PAY  21 

    0x6735bf6a,// 55 PAY  22 

    0xa53fe317,// 56 PAY  23 

    0x33a629a3,// 57 PAY  24 

    0x9b8cc550,// 58 PAY  25 

    0xf1ad2abc,// 59 PAY  26 

    0x905b416a,// 60 PAY  27 

    0x3fb42a86,// 61 PAY  28 

    0xbd1f5d35,// 62 PAY  29 

    0xc2a47cb8,// 63 PAY  30 

    0x6f0b0209,// 64 PAY  31 

    0xffa94225,// 65 PAY  32 

    0xe690336b,// 66 PAY  33 

    0x7db5fcf9,// 67 PAY  34 

    0xb35d2b8d,// 68 PAY  35 

    0x1e60c638,// 69 PAY  36 

    0xb68b9e06,// 70 PAY  37 

    0x6d2c7b2a,// 71 PAY  38 

    0x650279c9,// 72 PAY  39 

    0x65a78b44,// 73 PAY  40 

    0x7a802315,// 74 PAY  41 

    0xc6662761,// 75 PAY  42 

    0x46a006c8,// 76 PAY  43 

    0x3d596c28,// 77 PAY  44 

    0x69e18d19,// 78 PAY  45 

    0x40575d61,// 79 PAY  46 

    0xad35db82,// 80 PAY  47 

    0xff2c7f60,// 81 PAY  48 

    0xad5305da,// 82 PAY  49 

    0x52864e5e,// 83 PAY  50 

    0x1567dcba,// 84 PAY  51 

    0x72bc3215,// 85 PAY  52 

    0x8a51e2ad,// 86 PAY  53 

    0x5383fff6,// 87 PAY  54 

    0xcac11aa4,// 88 PAY  55 

    0x5f1a0375,// 89 PAY  56 

    0xf275d17f,// 90 PAY  57 

    0xe9d22cdb,// 91 PAY  58 

    0x31e15e7e,// 92 PAY  59 

    0xcdd47a31,// 93 PAY  60 

    0x6ec61cb6,// 94 PAY  61 

    0x03f196ff,// 95 PAY  62 

    0x1de6b0f3,// 96 PAY  63 

    0xf131d8b5,// 97 PAY  64 

    0x5a9e2d09,// 98 PAY  65 

    0xc42e3b80,// 99 PAY  66 

    0x17c53859,// 100 PAY  67 

    0xd2ad16d7,// 101 PAY  68 

    0x837b6ff4,// 102 PAY  69 

    0x6e2d8012,// 103 PAY  70 

    0xb1c35909,// 104 PAY  71 

    0x6c9d4c24,// 105 PAY  72 

    0x6aec00d4,// 106 PAY  73 

    0xdcd2b55b,// 107 PAY  74 

    0x4d525627,// 108 PAY  75 

    0x93b3026e,// 109 PAY  76 

    0xaaee6deb,// 110 PAY  77 

    0x43a71c32,// 111 PAY  78 

    0xd04d3b94,// 112 PAY  79 

    0x3567b004,// 113 PAY  80 

    0xccaf81ab,// 114 PAY  81 

    0xe61085a7,// 115 PAY  82 

    0x8a49097f,// 116 PAY  83 

    0x6de5574a,// 117 PAY  84 

    0x653efe2c,// 118 PAY  85 

    0xb8b31869,// 119 PAY  86 

    0xfc7748ba,// 120 PAY  87 

    0xb9fdd1f1,// 121 PAY  88 

    0x92e2655b,// 122 PAY  89 

    0x35165066,// 123 PAY  90 

    0x8e0c84a2,// 124 PAY  91 

    0x3bff525c,// 125 PAY  92 

    0x4fe8453b,// 126 PAY  93 

    0x78c3167e,// 127 PAY  94 

    0x4fe279a1,// 128 PAY  95 

    0x13865be1,// 129 PAY  96 

    0x108fae06,// 130 PAY  97 

    0x70f668c5,// 131 PAY  98 

    0x51ead9c5,// 132 PAY  99 

    0x57389b80,// 133 PAY 100 

    0xc2e3862e,// 134 PAY 101 

    0x41d55169,// 135 PAY 102 

    0xcdb06b10,// 136 PAY 103 

    0x7fc41f92,// 137 PAY 104 

    0x5220d11c,// 138 PAY 105 

    0xd97ce8ca,// 139 PAY 106 

    0x495f303d,// 140 PAY 107 

    0xf8822b61,// 141 PAY 108 

    0x0de57df1,// 142 PAY 109 

    0x7b7ab041,// 143 PAY 110 

    0xa573779e,// 144 PAY 111 

    0xb9dc42a2,// 145 PAY 112 

    0x2fbb9603,// 146 PAY 113 

    0x9a7991a5,// 147 PAY 114 

    0xfaa8cb32,// 148 PAY 115 

    0xa2190126,// 149 PAY 116 

    0x3dc4a6d6,// 150 PAY 117 

    0x5128f8cb,// 151 PAY 118 

    0xb6e5ad28,// 152 PAY 119 

    0xad418f52,// 153 PAY 120 

    0xeace4e52,// 154 PAY 121 

    0x37e6fdc1,// 155 PAY 122 

    0xc40a4616,// 156 PAY 123 

    0x55a5e48f,// 157 PAY 124 

    0xecfa8187,// 158 PAY 125 

    0xbbc502f9,// 159 PAY 126 

    0x3a0882a6,// 160 PAY 127 

    0x1ee73552,// 161 PAY 128 

    0x3b3e2dac,// 162 PAY 129 

    0xe7b84ad0,// 163 PAY 130 

    0xc18e1a66,// 164 PAY 131 

    0xbe7188d7,// 165 PAY 132 

    0x2be6e34c,// 166 PAY 133 

    0xe137b628,// 167 PAY 134 

    0xf5498044,// 168 PAY 135 

    0x0f01c7b9,// 169 PAY 136 

    0x2ae664f3,// 170 PAY 137 

    0xa7aecb6e,// 171 PAY 138 

    0xb0ae2a9d,// 172 PAY 139 

    0xffc26cc9,// 173 PAY 140 

    0x3002a9a0,// 174 PAY 141 

    0xb0158d5f,// 175 PAY 142 

    0xb9be1411,// 176 PAY 143 

    0xe8a7b9d3,// 177 PAY 144 

    0xa7ac7f5a,// 178 PAY 145 

    0x8b4a610f,// 179 PAY 146 

    0x490fde88,// 180 PAY 147 

    0x697be014,// 181 PAY 148 

    0x34d9426f,// 182 PAY 149 

    0x708d730e,// 183 PAY 150 

    0xd8dd7d9c,// 184 PAY 151 

    0x71e98634,// 185 PAY 152 

    0xe8295336,// 186 PAY 153 

    0x76a90e75,// 187 PAY 154 

    0xbd81a7f9,// 188 PAY 155 

    0x8f0f295f,// 189 PAY 156 

    0x09094749,// 190 PAY 157 

    0x4c49900d,// 191 PAY 158 

    0x4cab4de5,// 192 PAY 159 

    0xd80a98dd,// 193 PAY 160 

    0xde5fc984,// 194 PAY 161 

    0x896d15f6,// 195 PAY 162 

    0x5ba040ff,// 196 PAY 163 

    0xcf5723b1,// 197 PAY 164 

    0x053b1722,// 198 PAY 165 

    0xad3f1c32,// 199 PAY 166 

    0xac627e63,// 200 PAY 167 

    0xdacc808f,// 201 PAY 168 

    0xbb060679,// 202 PAY 169 

    0xc1511e28,// 203 PAY 170 

    0xdaca2b2c,// 204 PAY 171 

    0xf46cd823,// 205 PAY 172 

    0x7d7b1a6e,// 206 PAY 173 

    0x89b1eacd,// 207 PAY 174 

    0x7b9407ed,// 208 PAY 175 

    0x36a4a001,// 209 PAY 176 

    0xc041b05b,// 210 PAY 177 

    0xf173081d,// 211 PAY 178 

    0x6cd1aec8,// 212 PAY 179 

    0xdafb25a5,// 213 PAY 180 

    0x8eac9e9c,// 214 PAY 181 

    0x3f6d6875,// 215 PAY 182 

    0xf8c4761d,// 216 PAY 183 

    0xc5573e0a,// 217 PAY 184 

    0x3e24f40a,// 218 PAY 185 

    0x4a3b1da4,// 219 PAY 186 

    0x5178b30c,// 220 PAY 187 

    0x7dc974cf,// 221 PAY 188 

    0xb848850a,// 222 PAY 189 

    0x226b613a,// 223 PAY 190 

    0x6cb1496c,// 224 PAY 191 

    0xb550ce8b,// 225 PAY 192 

    0x9bb204f2,// 226 PAY 193 

    0xb2fe1b95,// 227 PAY 194 

    0xbce921d0,// 228 PAY 195 

    0x0526e159,// 229 PAY 196 

    0xe06494d3,// 230 PAY 197 

    0x38d1487f,// 231 PAY 198 

    0x80d75f6a,// 232 PAY 199 

    0xb3c1bce7,// 233 PAY 200 

    0x1629beb9,// 234 PAY 201 

    0x10182989,// 235 PAY 202 

    0x3e11d649,// 236 PAY 203 

    0x9a03bd93,// 237 PAY 204 

    0x956868d8,// 238 PAY 205 

    0x78e23e06,// 239 PAY 206 

    0x97b14ad4,// 240 PAY 207 

    0x8c9561ed,// 241 PAY 208 

    0x216688c3,// 242 PAY 209 

    0xa7322057,// 243 PAY 210 

    0xbe908ab2,// 244 PAY 211 

    0xc2c984d9,// 245 PAY 212 

    0xc269e076,// 246 PAY 213 

    0x9b9e61fc,// 247 PAY 214 

    0xe53841d8,// 248 PAY 215 

    0x01202404,// 249 PAY 216 

    0x6ac81979,// 250 PAY 217 

    0xe7d29f14,// 251 PAY 218 

    0x795e67d0,// 252 PAY 219 

    0x5eb7a000,// 253 PAY 220 

    0xcec54cec,// 254 PAY 221 

    0x2db59833,// 255 PAY 222 

    0x53adb8f2,// 256 PAY 223 

    0x121105bd,// 257 PAY 224 

    0x4f01b8c1,// 258 PAY 225 

    0x1307bf38,// 259 PAY 226 

    0x12dd6858,// 260 PAY 227 

    0xe07b9ae2,// 261 PAY 228 

    0x98d669dd,// 262 PAY 229 

    0x5d504ba2,// 263 PAY 230 

    0x8e2a6015,// 264 PAY 231 

    0x0607969e,// 265 PAY 232 

    0x3769237d,// 266 PAY 233 

    0xccae1960,// 267 PAY 234 

    0x1f5dce27,// 268 PAY 235 

    0x0785e138,// 269 PAY 236 

    0x6fb8f83d,// 270 PAY 237 

    0xb524c4ee,// 271 PAY 238 

    0xddc24e04,// 272 PAY 239 

    0x3b890b80,// 273 PAY 240 

    0xc2c24c5a,// 274 PAY 241 

    0x7fd338ff,// 275 PAY 242 

    0xb19b708b,// 276 PAY 243 

    0xe6657d63,// 277 PAY 244 

    0x1158a008,// 278 PAY 245 

    0xbacfc931,// 279 PAY 246 

    0xad6f2283,// 280 PAY 247 

    0xe803f986,// 281 PAY 248 

    0x15383164,// 282 PAY 249 

    0xf62568bd,// 283 PAY 250 

    0x3f34516f,// 284 PAY 251 

    0x6ef91f05,// 285 PAY 252 

    0xa1b75ebb,// 286 PAY 253 

    0xd93db0ec,// 287 PAY 254 

    0xcdd0cf95,// 288 PAY 255 

    0x81cb96bb,// 289 PAY 256 

    0x3f6ac714,// 290 PAY 257 

    0x69bd1f19,// 291 PAY 258 

    0x50ac9a0b,// 292 PAY 259 

    0x73ab64a2,// 293 PAY 260 

    0x4f3b73ac,// 294 PAY 261 

    0xc1e3317a,// 295 PAY 262 

    0x689ace55,// 296 PAY 263 

    0xd7b31fdb,// 297 PAY 264 

    0x304ea833,// 298 PAY 265 

    0xe68f2ca7,// 299 PAY 266 

    0x5080f08f,// 300 PAY 267 

    0xf1856405,// 301 PAY 268 

    0x9044e685,// 302 PAY 269 

    0xa3eb78e8,// 303 PAY 270 

    0xc91812a0,// 304 PAY 271 

    0x638ad762,// 305 PAY 272 

    0x467a3218,// 306 PAY 273 

    0xe55351c8,// 307 PAY 274 

    0x8913d81c,// 308 PAY 275 

    0xa7f59af2,// 309 PAY 276 

    0x51679b60,// 310 PAY 277 

    0x30bae111,// 311 PAY 278 

    0xad6e2ada,// 312 PAY 279 

    0xdee9eaa4,// 313 PAY 280 

    0xec220c53,// 314 PAY 281 

    0x2d62d201,// 315 PAY 282 

    0x4e5dfc0b,// 316 PAY 283 

    0x57a50617,// 317 PAY 284 

    0x59d0df95,// 318 PAY 285 

    0x3b18e800,// 319 PAY 286 

/// STA is 1 words. 

/// STA num_pkts       : 196 

/// STA pkt_idx        : 51 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x52 

    0x00cc52c4 // 320 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 80 (0x50) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt51_tmpl[] = {
    0xb8010050,// 1 CCH   1 

/// ECH cache_idx      : 0x0d 

/// ECH pdu_tag        : 0x00 

    0x000d0000,// 2 ECH   1 

/// SCX is 19 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x00000013,// 3 SCX   1 

    0x808148a8,// 4 SCX   2 

    0x00006100,// 5 SCX   3 

    0x38799bfb,// 6 SCX   4 

    0x3653cf33,// 7 SCX   5 

    0x09d0dcac,// 8 SCX   6 

    0x2efc2db1,// 9 SCX   7 

    0xef0adf8e,// 10 SCX   8 

    0x5a00ed55,// 11 SCX   9 

    0x6acd71d5,// 12 SCX  10 

    0xf2969c7f,// 13 SCX  11 

    0xafadf116,// 14 SCX  12 

    0xdfd37314,// 15 SCX  13 

    0xfd7fd772,// 16 SCX  14 

    0x862aee39,// 17 SCX  15 

    0xfd6acd70,// 18 SCX  16 

    0x9a5b3e85,// 19 SCX  17 

    0x0bb754cc,// 20 SCX  18 

    0x5e16a968,// 21 SCX  19 

/// BFD is 3 words. 

/// BFD tot_len        : 328 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 286 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 286 

/// BFD lencrypto      : 64 

/// BFD ofstcrypto     : 208 

/// BFD (ofst+len)cry  : 272 

/// BFD ofstiv         : 160 

/// BFD ofsticv        : 296 

    0x0000011e,// 22 BFD   1 

    0x00d00040,// 23 BFD   2 

    0x012800a0,// 24 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : 9 

    0x0900347c,// 25 MFM   1 

    0xb8946000,// 26 MFM   2 

/// BDA is 83 words. 

/// BDA size     is 328 (0x148) 

/// BDA id       is 0x30ad 

    0x014830ad,// 27 BDA   1 

/// PAY Generic Data size   : 328 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0x72424e02,// 28 PAY   1 

    0x505869ac,// 29 PAY   2 

    0xe428ede6,// 30 PAY   3 

    0x749af780,// 31 PAY   4 

    0x3ad02330,// 32 PAY   5 

    0x782348c1,// 33 PAY   6 

    0x87396b09,// 34 PAY   7 

    0x33673979,// 35 PAY   8 

    0x742fe244,// 36 PAY   9 

    0x52bd9e87,// 37 PAY  10 

    0x56255316,// 38 PAY  11 

    0x9fa33173,// 39 PAY  12 

    0xa6ee3b54,// 40 PAY  13 

    0x0622a4b2,// 41 PAY  14 

    0x251401ca,// 42 PAY  15 

    0x2e3f1d03,// 43 PAY  16 

    0x2f24c639,// 44 PAY  17 

    0x3708cc1d,// 45 PAY  18 

    0xe6d1f82d,// 46 PAY  19 

    0x18b8f69c,// 47 PAY  20 

    0xc327b403,// 48 PAY  21 

    0xbf304886,// 49 PAY  22 

    0x3c683791,// 50 PAY  23 

    0x07d52ddb,// 51 PAY  24 

    0xe12a0ccc,// 52 PAY  25 

    0x25a7a0be,// 53 PAY  26 

    0xb03e3236,// 54 PAY  27 

    0xd0020712,// 55 PAY  28 

    0x65dc1009,// 56 PAY  29 

    0xf2b5de87,// 57 PAY  30 

    0xc467506a,// 58 PAY  31 

    0x36910bf8,// 59 PAY  32 

    0x27d43052,// 60 PAY  33 

    0xa5d740c1,// 61 PAY  34 

    0xb5af7896,// 62 PAY  35 

    0xb2dd3808,// 63 PAY  36 

    0xcf8b572f,// 64 PAY  37 

    0x145be074,// 65 PAY  38 

    0x74495fff,// 66 PAY  39 

    0x89846acc,// 67 PAY  40 

    0xb74e8f91,// 68 PAY  41 

    0xbd36e972,// 69 PAY  42 

    0x3df8d168,// 70 PAY  43 

    0x21e29ede,// 71 PAY  44 

    0xfd66aa6c,// 72 PAY  45 

    0x38e33216,// 73 PAY  46 

    0x285b2ec9,// 74 PAY  47 

    0x1ac6476a,// 75 PAY  48 

    0x68f23c08,// 76 PAY  49 

    0x42200f8e,// 77 PAY  50 

    0xbd3bca15,// 78 PAY  51 

    0xbfa6c832,// 79 PAY  52 

    0xdd322a03,// 80 PAY  53 

    0xc4307873,// 81 PAY  54 

    0xe3631648,// 82 PAY  55 

    0xb62b7030,// 83 PAY  56 

    0x481bdf70,// 84 PAY  57 

    0x1ed1d2a4,// 85 PAY  58 

    0x26084a6f,// 86 PAY  59 

    0x67e2e7f8,// 87 PAY  60 

    0x17478bac,// 88 PAY  61 

    0xbf4bdcb8,// 89 PAY  62 

    0x7b3026ed,// 90 PAY  63 

    0xda108db6,// 91 PAY  64 

    0xaaca593e,// 92 PAY  65 

    0x763a875d,// 93 PAY  66 

    0x49f7e1a1,// 94 PAY  67 

    0xbe4fd4d7,// 95 PAY  68 

    0xfe031ccd,// 96 PAY  69 

    0xe76817ea,// 97 PAY  70 

    0x599a641f,// 98 PAY  71 

    0x73c872d7,// 99 PAY  72 

    0xad108d48,// 100 PAY  73 

    0x9b229f44,// 101 PAY  74 

    0x6262b922,// 102 PAY  75 

    0x16432c60,// 103 PAY  76 

    0xfdf2346c,// 104 PAY  77 

    0x72190c63,// 105 PAY  78 

    0x7fa6f6fb,// 106 PAY  79 

    0x8cd50632,// 107 PAY  80 

    0xeddabe69,// 108 PAY  81 

    0x2ea1a270,// 109 PAY  82 

/// STA is 1 words. 

/// STA num_pkts       : 59 

/// STA pkt_idx        : 20 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xb6 

    0x0050b63b // 110 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt52_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x0d 

/// ECH pdu_tag        : 0x00 

    0x000d0000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv insert_icv check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x809048db,// 4 SCX   2 

    0x000073c2,// 5 SCX   3 

    0xe4be789c,// 6 SCX   4 

    0x275687e3,// 7 SCX   5 

    0x7984b9ac,// 8 SCX   6 

    0x3904a025,// 9 SCX   7 

    0xdea4e1bc,// 10 SCX   8 

    0x033cc09b,// 11 SCX   9 

    0x360d16d8,// 12 SCX  10 

    0x31a6ef26,// 13 SCX  11 

    0x6256c358,// 14 SCX  12 

    0x15aa4d4d,// 15 SCX  13 

    0x1bdcff85,// 16 SCX  14 

    0x712c9479,// 17 SCX  15 

    0x5ee4dbf8,// 18 SCX  16 

    0x05800b46,// 19 SCX  17 

    0x08161d13,// 20 SCX  18 

    0x486c1be3,// 21 SCX  19 

    0xe82cea3f,// 22 SCX  20 

    0xf66d1add,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1714 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 908 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 908 

/// BFD lencrypto      : 388 

/// BFD ofstcrypto     : 116 

/// BFD (ofst+len)cry  : 504 

/// BFD ofstiv         : 88 

/// BFD ofsticv        : 1208 

    0x0000038c,// 24 BFD   1 

    0x00740184,// 25 BFD   2 

    0x04b80058,// 26 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c00570d,// 27 MFM   1 

    0x56d15c36,// 28 MFM   2 

    0x38efbe5f,// 29 MFM   3 

    0xb8350fac,// 30 MFM   4 

    0x2602e5c4,// 31 MFM   5 

    0x7c28f2b9,// 32 MFM   6 

    0x8c0923ab,// 33 MFM   7 

    0xcc6a6c08,// 34 MFM   8 

    0x44eeb11c,// 35 MFM   9 

    0x48dc4edf,// 36 MFM  10 

    0x3887a06a,// 37 MFM  11 

    0x434a89d2,// 38 MFM  12 

    0x1c729cb3,// 39 MFM  13 

    0xb6dd6d0e,// 40 MFM  14 

    0x13deebe3,// 41 MFM  15 

    0xa167ec20,// 42 MFM  16 

/// BDA is 430 words. 

/// BDA size     is 1714 (0x6b2) 

/// BDA id       is 0xa607 

    0x06b2a607,// 43 BDA   1 

/// PAY Generic Data size   : 1714 byte(s) 

/// PAD Buffer Data Pad size   : 2 byte(s) 

    0x33105f2e,// 44 PAY   1 

    0x7f19f843,// 45 PAY   2 

    0x23d8ce04,// 46 PAY   3 

    0x131ce033,// 47 PAY   4 

    0x11f9b668,// 48 PAY   5 

    0x5f52d663,// 49 PAY   6 

    0xd4250daa,// 50 PAY   7 

    0x0ada0740,// 51 PAY   8 

    0xb51f695d,// 52 PAY   9 

    0x2fc37156,// 53 PAY  10 

    0x9914a81f,// 54 PAY  11 

    0xc066b56d,// 55 PAY  12 

    0xda9be7b6,// 56 PAY  13 

    0x9c220504,// 57 PAY  14 

    0xab1ae513,// 58 PAY  15 

    0x22821948,// 59 PAY  16 

    0x4ab47baa,// 60 PAY  17 

    0xfe7d94aa,// 61 PAY  18 

    0x781d163a,// 62 PAY  19 

    0x5ad532c8,// 63 PAY  20 

    0x950f4f0d,// 64 PAY  21 

    0x752075a4,// 65 PAY  22 

    0x3a319640,// 66 PAY  23 

    0xa5a6301a,// 67 PAY  24 

    0x267611ae,// 68 PAY  25 

    0x09550b6e,// 69 PAY  26 

    0x7d5fdbec,// 70 PAY  27 

    0xcf492ce3,// 71 PAY  28 

    0x4440d03a,// 72 PAY  29 

    0x130f354c,// 73 PAY  30 

    0x19eb23a1,// 74 PAY  31 

    0x47ff09e4,// 75 PAY  32 

    0xee6ef749,// 76 PAY  33 

    0x04a78796,// 77 PAY  34 

    0x2f4b95b7,// 78 PAY  35 

    0xdfcdd3a3,// 79 PAY  36 

    0x0107bf51,// 80 PAY  37 

    0x87b5f227,// 81 PAY  38 

    0x850f5ae3,// 82 PAY  39 

    0x5a3361b0,// 83 PAY  40 

    0x84d288eb,// 84 PAY  41 

    0xaea0fe1a,// 85 PAY  42 

    0xde5499fa,// 86 PAY  43 

    0x4841e8c2,// 87 PAY  44 

    0xd529d3c7,// 88 PAY  45 

    0xc3a0045e,// 89 PAY  46 

    0x6e8a1bba,// 90 PAY  47 

    0x83a0f539,// 91 PAY  48 

    0x78560ff9,// 92 PAY  49 

    0xa0f21c5f,// 93 PAY  50 

    0xb7ad3468,// 94 PAY  51 

    0x4f815c5a,// 95 PAY  52 

    0x73fbad02,// 96 PAY  53 

    0x3796b1b7,// 97 PAY  54 

    0x0089af8d,// 98 PAY  55 

    0x9977a52f,// 99 PAY  56 

    0xab411856,// 100 PAY  57 

    0x8db63ea1,// 101 PAY  58 

    0x9eee11ed,// 102 PAY  59 

    0x8a40bfac,// 103 PAY  60 

    0x3d07a261,// 104 PAY  61 

    0x90f04d9d,// 105 PAY  62 

    0xcb6f2a61,// 106 PAY  63 

    0xf530b2e7,// 107 PAY  64 

    0x14c33b9f,// 108 PAY  65 

    0x307595e2,// 109 PAY  66 

    0xedda3909,// 110 PAY  67 

    0xef46e89e,// 111 PAY  68 

    0x6179ee2f,// 112 PAY  69 

    0x0f953211,// 113 PAY  70 

    0x2261f1df,// 114 PAY  71 

    0xc66bd1d6,// 115 PAY  72 

    0x65fb530e,// 116 PAY  73 

    0xf7ea12ac,// 117 PAY  74 

    0xab85e6f2,// 118 PAY  75 

    0x6e76e0b5,// 119 PAY  76 

    0xf45934ad,// 120 PAY  77 

    0xa0d47abc,// 121 PAY  78 

    0x08723ae9,// 122 PAY  79 

    0x6e4a95ba,// 123 PAY  80 

    0x6ee13d2b,// 124 PAY  81 

    0x2c20b7c5,// 125 PAY  82 

    0xc849db60,// 126 PAY  83 

    0xf2d32858,// 127 PAY  84 

    0xe725588f,// 128 PAY  85 

    0x5891c678,// 129 PAY  86 

    0x8502e8d2,// 130 PAY  87 

    0x889e84fa,// 131 PAY  88 

    0xd83469c0,// 132 PAY  89 

    0x287475d8,// 133 PAY  90 

    0x283ab57e,// 134 PAY  91 

    0xce1a205f,// 135 PAY  92 

    0x9f193a9d,// 136 PAY  93 

    0x02b427b4,// 137 PAY  94 

    0xd4dda071,// 138 PAY  95 

    0x3a1c3e52,// 139 PAY  96 

    0x21c1ab7a,// 140 PAY  97 

    0x1a228c89,// 141 PAY  98 

    0xf34fc6c7,// 142 PAY  99 

    0xeae5d311,// 143 PAY 100 

    0x44fc8f7e,// 144 PAY 101 

    0xd7c9e731,// 145 PAY 102 

    0x035f8180,// 146 PAY 103 

    0xe42ff123,// 147 PAY 104 

    0xa379038f,// 148 PAY 105 

    0x022d612a,// 149 PAY 106 

    0x05e59934,// 150 PAY 107 

    0x09557cf7,// 151 PAY 108 

    0x8d00f482,// 152 PAY 109 

    0x87f3779f,// 153 PAY 110 

    0x8401f299,// 154 PAY 111 

    0x8c746ce9,// 155 PAY 112 

    0x50fa3edd,// 156 PAY 113 

    0xe012e604,// 157 PAY 114 

    0x11344f5e,// 158 PAY 115 

    0x49a43ca6,// 159 PAY 116 

    0x4014a7f1,// 160 PAY 117 

    0xac73e352,// 161 PAY 118 

    0x24f1c30a,// 162 PAY 119 

    0xcbe6dac1,// 163 PAY 120 

    0x84bb1abd,// 164 PAY 121 

    0x290541e0,// 165 PAY 122 

    0x85c8b302,// 166 PAY 123 

    0xe979378e,// 167 PAY 124 

    0x6002b9d6,// 168 PAY 125 

    0x1c6c4478,// 169 PAY 126 

    0x70fe324e,// 170 PAY 127 

    0x895eed47,// 171 PAY 128 

    0x463a2bb2,// 172 PAY 129 

    0x029c2468,// 173 PAY 130 

    0x73b0c49d,// 174 PAY 131 

    0x6e33ed7c,// 175 PAY 132 

    0x682ec5e5,// 176 PAY 133 

    0xcfb7fd8d,// 177 PAY 134 

    0x79b18e37,// 178 PAY 135 

    0x73928311,// 179 PAY 136 

    0x17388abe,// 180 PAY 137 

    0x821562c0,// 181 PAY 138 

    0x9df7abc4,// 182 PAY 139 

    0x42d9a935,// 183 PAY 140 

    0x778a8d6c,// 184 PAY 141 

    0xafa8925d,// 185 PAY 142 

    0xd0738f1f,// 186 PAY 143 

    0xcea99eac,// 187 PAY 144 

    0x871c3261,// 188 PAY 145 

    0x7f092595,// 189 PAY 146 

    0xfdfd658d,// 190 PAY 147 

    0x83d42b41,// 191 PAY 148 

    0x023cc236,// 192 PAY 149 

    0x8f88f7f1,// 193 PAY 150 

    0x0e148636,// 194 PAY 151 

    0xad4e133c,// 195 PAY 152 

    0xac6449e8,// 196 PAY 153 

    0xbe776df8,// 197 PAY 154 

    0xb1b990f0,// 198 PAY 155 

    0xee8a2e3d,// 199 PAY 156 

    0xc64627b2,// 200 PAY 157 

    0x94846e3a,// 201 PAY 158 

    0x3358f984,// 202 PAY 159 

    0xf4218298,// 203 PAY 160 

    0x4e311b30,// 204 PAY 161 

    0x7a2b40ef,// 205 PAY 162 

    0x04463aae,// 206 PAY 163 

    0xc9e8c269,// 207 PAY 164 

    0xa46a3121,// 208 PAY 165 

    0x46944f5e,// 209 PAY 166 

    0x19fe819a,// 210 PAY 167 

    0xecd090da,// 211 PAY 168 

    0x5bec25a4,// 212 PAY 169 

    0x55f95002,// 213 PAY 170 

    0x8ad7854d,// 214 PAY 171 

    0xc4a0d347,// 215 PAY 172 

    0x9c0166b1,// 216 PAY 173 

    0xe61040b6,// 217 PAY 174 

    0xab88c6da,// 218 PAY 175 

    0xd6a0d29a,// 219 PAY 176 

    0x23142aa9,// 220 PAY 177 

    0x39976b94,// 221 PAY 178 

    0x931f7fbd,// 222 PAY 179 

    0x0a33e329,// 223 PAY 180 

    0x447c5408,// 224 PAY 181 

    0x2532bb54,// 225 PAY 182 

    0xa01846e7,// 226 PAY 183 

    0xe6ab66ef,// 227 PAY 184 

    0x16c332dc,// 228 PAY 185 

    0xa5c87361,// 229 PAY 186 

    0x848fce97,// 230 PAY 187 

    0xb8aa35a0,// 231 PAY 188 

    0x1cfd7feb,// 232 PAY 189 

    0xf6524c76,// 233 PAY 190 

    0x9beb5854,// 234 PAY 191 

    0x3f613d59,// 235 PAY 192 

    0xf7b811f5,// 236 PAY 193 

    0x3599d32f,// 237 PAY 194 

    0xa93f2e8b,// 238 PAY 195 

    0xc2ce43b0,// 239 PAY 196 

    0xb596b1e4,// 240 PAY 197 

    0x78401804,// 241 PAY 198 

    0x1dc586d5,// 242 PAY 199 

    0xd846dd7c,// 243 PAY 200 

    0xe13be88b,// 244 PAY 201 

    0xa5fcabeb,// 245 PAY 202 

    0x345232c3,// 246 PAY 203 

    0xd19b0e49,// 247 PAY 204 

    0xc7628c7e,// 248 PAY 205 

    0x5874e764,// 249 PAY 206 

    0xc7e01ca3,// 250 PAY 207 

    0x25bffc8b,// 251 PAY 208 

    0xe5456acc,// 252 PAY 209 

    0x37921523,// 253 PAY 210 

    0xeb59a883,// 254 PAY 211 

    0xb8ae060f,// 255 PAY 212 

    0x1aedccba,// 256 PAY 213 

    0xdf491617,// 257 PAY 214 

    0xcd805c9d,// 258 PAY 215 

    0x552ab502,// 259 PAY 216 

    0x6b8c1670,// 260 PAY 217 

    0x6a4b0d62,// 261 PAY 218 

    0x719e9780,// 262 PAY 219 

    0xb9016bdc,// 263 PAY 220 

    0x939dde8b,// 264 PAY 221 

    0x25c22281,// 265 PAY 222 

    0x74cfb3ac,// 266 PAY 223 

    0x94266d0c,// 267 PAY 224 

    0xfe787876,// 268 PAY 225 

    0xd9e7809a,// 269 PAY 226 

    0x19e28c4e,// 270 PAY 227 

    0x4affa8d5,// 271 PAY 228 

    0x18e76c95,// 272 PAY 229 

    0x0ad19475,// 273 PAY 230 

    0xe2cb05a4,// 274 PAY 231 

    0x72e3d475,// 275 PAY 232 

    0x5b0f0bf1,// 276 PAY 233 

    0xbe880ea9,// 277 PAY 234 

    0x520bbe77,// 278 PAY 235 

    0x6436cdcc,// 279 PAY 236 

    0x2d98941f,// 280 PAY 237 

    0xb09284ce,// 281 PAY 238 

    0xbb78c75c,// 282 PAY 239 

    0x13e8210d,// 283 PAY 240 

    0x7d3662fa,// 284 PAY 241 

    0x6c2331cf,// 285 PAY 242 

    0x20d58f1e,// 286 PAY 243 

    0x911418d2,// 287 PAY 244 

    0x88b99916,// 288 PAY 245 

    0x59562e49,// 289 PAY 246 

    0x261d00aa,// 290 PAY 247 

    0x99fc4b57,// 291 PAY 248 

    0x9cfb2630,// 292 PAY 249 

    0x12b63d5c,// 293 PAY 250 

    0x1aa200ec,// 294 PAY 251 

    0xbb4ba48b,// 295 PAY 252 

    0x16af669c,// 296 PAY 253 

    0x76820869,// 297 PAY 254 

    0x385a05f6,// 298 PAY 255 

    0xf9b4259c,// 299 PAY 256 

    0x9bad3109,// 300 PAY 257 

    0x4dcf7995,// 301 PAY 258 

    0x399bebd5,// 302 PAY 259 

    0xe52d04d4,// 303 PAY 260 

    0x1b51363a,// 304 PAY 261 

    0x0ff92493,// 305 PAY 262 

    0xed93c62b,// 306 PAY 263 

    0xaef2c1c5,// 307 PAY 264 

    0x89609835,// 308 PAY 265 

    0xade004ec,// 309 PAY 266 

    0xa6d67bed,// 310 PAY 267 

    0x45d0caa9,// 311 PAY 268 

    0xcecfc224,// 312 PAY 269 

    0x2854c413,// 313 PAY 270 

    0xd8076780,// 314 PAY 271 

    0x2036b372,// 315 PAY 272 

    0x793541c8,// 316 PAY 273 

    0x4e23283a,// 317 PAY 274 

    0xbb81e950,// 318 PAY 275 

    0xbbb1545b,// 319 PAY 276 

    0x81a5b24a,// 320 PAY 277 

    0x35edfbaa,// 321 PAY 278 

    0x33fe1a7f,// 322 PAY 279 

    0x41888c1e,// 323 PAY 280 

    0xf479fafc,// 324 PAY 281 

    0x92847917,// 325 PAY 282 

    0x324f3b60,// 326 PAY 283 

    0x4cca32f0,// 327 PAY 284 

    0xaab3b9cf,// 328 PAY 285 

    0x25f75d23,// 329 PAY 286 

    0xd7e3f09c,// 330 PAY 287 

    0x0b13752c,// 331 PAY 288 

    0x224a120f,// 332 PAY 289 

    0x9d4eb325,// 333 PAY 290 

    0x2bf17d19,// 334 PAY 291 

    0x0c675947,// 335 PAY 292 

    0x8bd83f65,// 336 PAY 293 

    0x54a8c2c6,// 337 PAY 294 

    0xba4acb91,// 338 PAY 295 

    0x43b02159,// 339 PAY 296 

    0x0fa7ac0c,// 340 PAY 297 

    0x61a36afd,// 341 PAY 298 

    0x5130fce5,// 342 PAY 299 

    0x86f87b61,// 343 PAY 300 

    0xca7f67db,// 344 PAY 301 

    0xb84825f0,// 345 PAY 302 

    0xea360a65,// 346 PAY 303 

    0xa21edc18,// 347 PAY 304 

    0xf5b333c8,// 348 PAY 305 

    0xf292a53a,// 349 PAY 306 

    0x85cb5325,// 350 PAY 307 

    0x86507b70,// 351 PAY 308 

    0x41fe111a,// 352 PAY 309 

    0xef7d4028,// 353 PAY 310 

    0xb97160de,// 354 PAY 311 

    0x240dc9d3,// 355 PAY 312 

    0xf58fdd8f,// 356 PAY 313 

    0x8a138fae,// 357 PAY 314 

    0x1b05579e,// 358 PAY 315 

    0x81b031ed,// 359 PAY 316 

    0x10ae0543,// 360 PAY 317 

    0x42d8087c,// 361 PAY 318 

    0x263dd099,// 362 PAY 319 

    0x516eb1d8,// 363 PAY 320 

    0x9deb2376,// 364 PAY 321 

    0x665243a9,// 365 PAY 322 

    0x0b24b82e,// 366 PAY 323 

    0x85aac5c0,// 367 PAY 324 

    0xa7617c4f,// 368 PAY 325 

    0x2d299fa3,// 369 PAY 326 

    0x7f774532,// 370 PAY 327 

    0x55f7b3f8,// 371 PAY 328 

    0x287f729f,// 372 PAY 329 

    0x94086ada,// 373 PAY 330 

    0xf2e4127c,// 374 PAY 331 

    0x722e7b8a,// 375 PAY 332 

    0xd5900bcf,// 376 PAY 333 

    0xb1952417,// 377 PAY 334 

    0xd795da30,// 378 PAY 335 

    0x5c6a82e2,// 379 PAY 336 

    0xac268884,// 380 PAY 337 

    0xc7a4f669,// 381 PAY 338 

    0xdf3ba2f8,// 382 PAY 339 

    0x0868c5e4,// 383 PAY 340 

    0x1a516d0a,// 384 PAY 341 

    0x7fa5bb87,// 385 PAY 342 

    0x202ed8e7,// 386 PAY 343 

    0xab6855b9,// 387 PAY 344 

    0x2b98f0ee,// 388 PAY 345 

    0xa849ec9d,// 389 PAY 346 

    0xf685442b,// 390 PAY 347 

    0x732727d9,// 391 PAY 348 

    0x63d29408,// 392 PAY 349 

    0x3a88a024,// 393 PAY 350 

    0xf08ef514,// 394 PAY 351 

    0x4dd8f103,// 395 PAY 352 

    0xe26442f7,// 396 PAY 353 

    0xb65a384e,// 397 PAY 354 

    0xb0e80ec9,// 398 PAY 355 

    0xb706da3b,// 399 PAY 356 

    0xe2d5f53d,// 400 PAY 357 

    0xa5dccd35,// 401 PAY 358 

    0x19524162,// 402 PAY 359 

    0xda1d1f37,// 403 PAY 360 

    0x24dd481c,// 404 PAY 361 

    0x0fd3a45c,// 405 PAY 362 

    0x46cab546,// 406 PAY 363 

    0x697159f0,// 407 PAY 364 

    0x35991265,// 408 PAY 365 

    0x24c60b3e,// 409 PAY 366 

    0xb607119e,// 410 PAY 367 

    0x516826da,// 411 PAY 368 

    0xc58f94be,// 412 PAY 369 

    0x1e38b218,// 413 PAY 370 

    0xb76de88d,// 414 PAY 371 

    0xbb9c9454,// 415 PAY 372 

    0x7a089d19,// 416 PAY 373 

    0x88a21c8b,// 417 PAY 374 

    0x0a46b515,// 418 PAY 375 

    0x03831bd5,// 419 PAY 376 

    0xda4dcd72,// 420 PAY 377 

    0x99e8335c,// 421 PAY 378 

    0x1f155f47,// 422 PAY 379 

    0xf1d81b16,// 423 PAY 380 

    0xc3e049ea,// 424 PAY 381 

    0x6f0fc1f4,// 425 PAY 382 

    0xd210ad12,// 426 PAY 383 

    0x093e0c1e,// 427 PAY 384 

    0xa680339b,// 428 PAY 385 

    0xcabe63d2,// 429 PAY 386 

    0x37291036,// 430 PAY 387 

    0xa0026072,// 431 PAY 388 

    0x35c834b8,// 432 PAY 389 

    0x4427e94c,// 433 PAY 390 

    0xc0a966b2,// 434 PAY 391 

    0x8d99cc57,// 435 PAY 392 

    0xf3ce67aa,// 436 PAY 393 

    0x5fb4a97d,// 437 PAY 394 

    0x6e10e075,// 438 PAY 395 

    0x6b7b762e,// 439 PAY 396 

    0x47b70c13,// 440 PAY 397 

    0x2e938d56,// 441 PAY 398 

    0xc454707b,// 442 PAY 399 

    0x4b3b8e71,// 443 PAY 400 

    0xed637217,// 444 PAY 401 

    0x76dc5bc2,// 445 PAY 402 

    0x49a57d50,// 446 PAY 403 

    0xe09cdce3,// 447 PAY 404 

    0xe026d10e,// 448 PAY 405 

    0x723a8197,// 449 PAY 406 

    0x3e14f691,// 450 PAY 407 

    0x74b9fc0c,// 451 PAY 408 

    0x4aa28a7e,// 452 PAY 409 

    0x99b2ecfd,// 453 PAY 410 

    0xa218e765,// 454 PAY 411 

    0x6a94aeb1,// 455 PAY 412 

    0xc5f724dd,// 456 PAY 413 

    0x629250b7,// 457 PAY 414 

    0xcbfd0a9d,// 458 PAY 415 

    0x4e76b4ff,// 459 PAY 416 

    0xe681f87e,// 460 PAY 417 

    0x5931b0dd,// 461 PAY 418 

    0x90c62ae5,// 462 PAY 419 

    0xc94bbeb2,// 463 PAY 420 

    0x8a88b534,// 464 PAY 421 

    0xbfec765f,// 465 PAY 422 

    0xec18c9a2,// 466 PAY 423 

    0x05d8e707,// 467 PAY 424 

    0xb963cb44,// 468 PAY 425 

    0x76d5cea8,// 469 PAY 426 

    0x6a0b9064,// 470 PAY 427 

    0x694549d4,// 471 PAY 428 

    0x45e90000,// 472 PAY 429 

/// STA is 1 words. 

/// STA num_pkts       : 163 

/// STA pkt_idx        : 246 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x58 

    0x03d958a3 // 473 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt53_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x04 

/// ECH pdu_tag        : 0x00 

    0x00040000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv !insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x8082483a,// 4 SCX   2 

    0x00000400,// 5 SCX   3 

    0xcfc283b0,// 6 SCX   4 

    0xbbd261a5,// 7 SCX   5 

    0x994a1eb3,// 8 SCX   6 

    0xecb95f2f,// 9 SCX   7 

    0x0f9248f0,// 10 SCX   8 

    0xcfc3a4be,// 11 SCX   9 

    0xdec3bf1a,// 12 SCX  10 

    0x2ed529f4,// 13 SCX  11 

    0xe8981b41,// 14 SCX  12 

    0x83500473,// 15 SCX  13 

    0xbf094d4e,// 16 SCX  14 

    0x674f05b4,// 17 SCX  15 

    0x3ece31ae,// 18 SCX  16 

    0xcf29ce5a,// 19 SCX  17 

    0xff05f7b5,// 20 SCX  18 

    0xd5f48651,// 21 SCX  19 

    0x28810fb0,// 22 SCX  20 

    0xd28cb6e6,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 818 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 442 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 442 

/// BFD lencrypto      : 288 

/// BFD ofstcrypto     : 120 

/// BFD (ofst+len)cry  : 408 

/// BFD ofstiv         : 96 

/// BFD ofsticv        : 652 

    0x000001ba,// 24 BFD   1 

    0x00780120,// 25 BFD   2 

    0x028c0060,// 26 BFD   3 

/// MFM is 13 words. 

/// MFM vldnibs        : 60 

    0x60005bdd,// 27 MFM   1 

    0x37703aab,// 28 MFM   2 

    0x52fe7c1d,// 29 MFM   3 

    0xee382dc7,// 30 MFM   4 

    0x9b0aeadd,// 31 MFM   5 

    0x28939858,// 32 MFM   6 

    0xdb99e7eb,// 33 MFM   7 

    0x72611b53,// 34 MFM   8 

    0x2b51600c,// 35 MFM   9 

    0x0e68b184,// 36 MFM  10 

    0xe90d1a28,// 37 MFM  11 

    0xda1118db,// 38 MFM  12 

    0x224d0000,// 39 MFM  13 

/// BDA is 206 words. 

/// BDA size     is 818 (0x332) 

/// BDA id       is 0x7e9d 

    0x03327e9d,// 40 BDA   1 

/// PAY Generic Data size   : 818 byte(s) 

/// PAD Buffer Data Pad size   : 2 byte(s) 

    0x031b1dab,// 41 PAY   1 

    0x833dc7a1,// 42 PAY   2 

    0x85352d53,// 43 PAY   3 

    0x4c4c9dc0,// 44 PAY   4 

    0x4ab0789c,// 45 PAY   5 

    0xb33ee669,// 46 PAY   6 

    0x4bc33486,// 47 PAY   7 

    0xca4bd54a,// 48 PAY   8 

    0x43b19d95,// 49 PAY   9 

    0xf4ccf62c,// 50 PAY  10 

    0x2e1a0b76,// 51 PAY  11 

    0x1e964558,// 52 PAY  12 

    0xc71249f9,// 53 PAY  13 

    0xd23ec784,// 54 PAY  14 

    0x82a930ed,// 55 PAY  15 

    0xe6ba09a0,// 56 PAY  16 

    0x1f4b475b,// 57 PAY  17 

    0x0f71042e,// 58 PAY  18 

    0xbbaa06ca,// 59 PAY  19 

    0xedc48898,// 60 PAY  20 

    0x438cbc30,// 61 PAY  21 

    0x9fe81316,// 62 PAY  22 

    0x05850868,// 63 PAY  23 

    0x9656b8f0,// 64 PAY  24 

    0x45cd27ed,// 65 PAY  25 

    0x319829d8,// 66 PAY  26 

    0x5e52f244,// 67 PAY  27 

    0x6ade11e3,// 68 PAY  28 

    0xeda5eeab,// 69 PAY  29 

    0xd19163d6,// 70 PAY  30 

    0xc52c9901,// 71 PAY  31 

    0xbd3eb14d,// 72 PAY  32 

    0x6bf4b446,// 73 PAY  33 

    0xd0189a6b,// 74 PAY  34 

    0xa8207b0b,// 75 PAY  35 

    0x49db6175,// 76 PAY  36 

    0xb4b57516,// 77 PAY  37 

    0x20ca60bc,// 78 PAY  38 

    0x3aebccce,// 79 PAY  39 

    0x6183ce89,// 80 PAY  40 

    0xdbb48511,// 81 PAY  41 

    0x8cad49e6,// 82 PAY  42 

    0x4a08439a,// 83 PAY  43 

    0x45fa3db0,// 84 PAY  44 

    0x219bcc3b,// 85 PAY  45 

    0x9ab4d6fd,// 86 PAY  46 

    0x673342f9,// 87 PAY  47 

    0x6b1cf9e5,// 88 PAY  48 

    0x8dc22f0c,// 89 PAY  49 

    0xae32fd95,// 90 PAY  50 

    0xd020093f,// 91 PAY  51 

    0xaf83b129,// 92 PAY  52 

    0xeec00d94,// 93 PAY  53 

    0xac24bd7a,// 94 PAY  54 

    0xf2b7e131,// 95 PAY  55 

    0x89164177,// 96 PAY  56 

    0x443d97d8,// 97 PAY  57 

    0x12cab866,// 98 PAY  58 

    0x8c3f6b0f,// 99 PAY  59 

    0x0f19aba9,// 100 PAY  60 

    0xaee11b06,// 101 PAY  61 

    0xc2452378,// 102 PAY  62 

    0x414c45f8,// 103 PAY  63 

    0x59d4bf61,// 104 PAY  64 

    0xed0fdf08,// 105 PAY  65 

    0xd6a2aadb,// 106 PAY  66 

    0x78e20505,// 107 PAY  67 

    0x6b96dd64,// 108 PAY  68 

    0xfca9d864,// 109 PAY  69 

    0x57cb0ffd,// 110 PAY  70 

    0x50a793b1,// 111 PAY  71 

    0x7d84ac63,// 112 PAY  72 

    0xf47cd18d,// 113 PAY  73 

    0xe1d321de,// 114 PAY  74 

    0x83e10c20,// 115 PAY  75 

    0x02fa1caa,// 116 PAY  76 

    0x62a313ef,// 117 PAY  77 

    0xc57fb2b3,// 118 PAY  78 

    0x1b23560d,// 119 PAY  79 

    0xce3d0dc3,// 120 PAY  80 

    0x530398ad,// 121 PAY  81 

    0x0bd87d48,// 122 PAY  82 

    0x3efdb9aa,// 123 PAY  83 

    0x83609cec,// 124 PAY  84 

    0x607e9978,// 125 PAY  85 

    0x402b1416,// 126 PAY  86 

    0xdc927c9e,// 127 PAY  87 

    0x00132dbb,// 128 PAY  88 

    0x5010ddfe,// 129 PAY  89 

    0xca2aa51c,// 130 PAY  90 

    0xf56e372f,// 131 PAY  91 

    0xb0dfb69b,// 132 PAY  92 

    0x582661e9,// 133 PAY  93 

    0x14d373d9,// 134 PAY  94 

    0x5f80c2a8,// 135 PAY  95 

    0x31d1ab5f,// 136 PAY  96 

    0x4b1d6e18,// 137 PAY  97 

    0x58a3e98a,// 138 PAY  98 

    0xf8211d1c,// 139 PAY  99 

    0x974cd048,// 140 PAY 100 

    0xfa78d51f,// 141 PAY 101 

    0x90ee1cc7,// 142 PAY 102 

    0x23a3f21f,// 143 PAY 103 

    0x1a290894,// 144 PAY 104 

    0x3e93ffef,// 145 PAY 105 

    0x832354d5,// 146 PAY 106 

    0xc59aab98,// 147 PAY 107 

    0x63e8f534,// 148 PAY 108 

    0x6aaac5d7,// 149 PAY 109 

    0xf2f91458,// 150 PAY 110 

    0x8d96e7cd,// 151 PAY 111 

    0x651c62ab,// 152 PAY 112 

    0x6d512444,// 153 PAY 113 

    0xcce5979c,// 154 PAY 114 

    0x849da775,// 155 PAY 115 

    0xb95d55eb,// 156 PAY 116 

    0xec0179c9,// 157 PAY 117 

    0x64b7c874,// 158 PAY 118 

    0x858970a0,// 159 PAY 119 

    0x1c25bee2,// 160 PAY 120 

    0x341d3781,// 161 PAY 121 

    0x9548c4d8,// 162 PAY 122 

    0xc738c4f0,// 163 PAY 123 

    0x270a4077,// 164 PAY 124 

    0xa65c81c4,// 165 PAY 125 

    0x96666b17,// 166 PAY 126 

    0x7c6e0b36,// 167 PAY 127 

    0x39f837a4,// 168 PAY 128 

    0xb1439c5a,// 169 PAY 129 

    0xd97757c4,// 170 PAY 130 

    0x318b920b,// 171 PAY 131 

    0x5abad888,// 172 PAY 132 

    0x6258dd9d,// 173 PAY 133 

    0x7753a323,// 174 PAY 134 

    0xa8100013,// 175 PAY 135 

    0x14943b07,// 176 PAY 136 

    0xfcf94c16,// 177 PAY 137 

    0xa3ba9af9,// 178 PAY 138 

    0x414b01e8,// 179 PAY 139 

    0xb89c3380,// 180 PAY 140 

    0x915927c0,// 181 PAY 141 

    0x765cbb92,// 182 PAY 142 

    0x35bb8027,// 183 PAY 143 

    0x230ced20,// 184 PAY 144 

    0x2f829af4,// 185 PAY 145 

    0x97450a54,// 186 PAY 146 

    0x7460ef16,// 187 PAY 147 

    0x07b408b3,// 188 PAY 148 

    0xc2812255,// 189 PAY 149 

    0x244e192c,// 190 PAY 150 

    0x327d3910,// 191 PAY 151 

    0xf8a146d7,// 192 PAY 152 

    0xfcc0e5c4,// 193 PAY 153 

    0xfb88670b,// 194 PAY 154 

    0x36005265,// 195 PAY 155 

    0xdf9f9e91,// 196 PAY 156 

    0x5a4ab589,// 197 PAY 157 

    0xa55d340d,// 198 PAY 158 

    0x15a47640,// 199 PAY 159 

    0xe7ca6b1e,// 200 PAY 160 

    0x282eeb22,// 201 PAY 161 

    0x63984a88,// 202 PAY 162 

    0xea3dee0b,// 203 PAY 163 

    0xf28c9bcc,// 204 PAY 164 

    0x2c302de4,// 205 PAY 165 

    0x835622cd,// 206 PAY 166 

    0x82251c8b,// 207 PAY 167 

    0x39480446,// 208 PAY 168 

    0xe56b3cfb,// 209 PAY 169 

    0xca72f7d1,// 210 PAY 170 

    0xd7096e10,// 211 PAY 171 

    0x13c1055a,// 212 PAY 172 

    0xec7a285a,// 213 PAY 173 

    0x836dea3a,// 214 PAY 174 

    0x772d65eb,// 215 PAY 175 

    0x5deb013f,// 216 PAY 176 

    0x08b859b1,// 217 PAY 177 

    0xa2f484ee,// 218 PAY 178 

    0x08eba95b,// 219 PAY 179 

    0xf4cd8fd2,// 220 PAY 180 

    0xa5382fa4,// 221 PAY 181 

    0x9aef4aa7,// 222 PAY 182 

    0xbb778058,// 223 PAY 183 

    0x4b41c88c,// 224 PAY 184 

    0x4446f180,// 225 PAY 185 

    0x8ac14022,// 226 PAY 186 

    0x73486841,// 227 PAY 187 

    0x81293da1,// 228 PAY 188 

    0x8e54e2fd,// 229 PAY 189 

    0xcbfdfd77,// 230 PAY 190 

    0xfb0c97f1,// 231 PAY 191 

    0x6fce7047,// 232 PAY 192 

    0x92fef02a,// 233 PAY 193 

    0x9f527108,// 234 PAY 194 

    0xcdf6ca38,// 235 PAY 195 

    0xbd16e3bd,// 236 PAY 196 

    0x9b07e073,// 237 PAY 197 

    0x8a5d7a06,// 238 PAY 198 

    0x08f486e3,// 239 PAY 199 

    0xcae69a19,// 240 PAY 200 

    0x8333749a,// 241 PAY 201 

    0xd119567d,// 242 PAY 202 

    0xdabed7b6,// 243 PAY 203 

    0xb8e6132c,// 244 PAY 204 

    0x3b490000,// 245 PAY 205 

/// STA is 1 words. 

/// STA num_pkts       : 6 

/// STA pkt_idx        : 44 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xf8 

    0x00b1f806 // 246 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 96 (0x60) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt54_tmpl[] = {
    0xb8010060,// 1 CCH   1 

/// ECH cache_idx      : 0x0e 

/// ECH pdu_tag        : 0x00 

    0x000e0000,// 2 ECH   1 

/// SCX is 23 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000017,// 3 SCX   1 

    0x8085484b,// 4 SCX   2 

    0x000063c4,// 5 SCX   3 

    0xba4cb14b,// 6 SCX   4 

    0x5a4a3f9e,// 7 SCX   5 

    0xa4138bef,// 8 SCX   6 

    0xcd76ac8e,// 9 SCX   7 

    0x21cd907a,// 10 SCX   8 

    0x5f716047,// 11 SCX   9 

    0x3ae8d06b,// 12 SCX  10 

    0x1320f093,// 13 SCX  11 

    0x3ac659b9,// 14 SCX  12 

    0x5d579d71,// 15 SCX  13 

    0x78d6a516,// 16 SCX  14 

    0xa7deca4c,// 17 SCX  15 

    0x35634db4,// 18 SCX  16 

    0xfc5cf70c,// 19 SCX  17 

    0xa6022630,// 20 SCX  18 

    0x843a67da,// 21 SCX  19 

    0xa3ae8422,// 22 SCX  20 

    0xc5ebaccf,// 23 SCX  21 

    0xe2f7dd5b,// 24 SCX  22 

    0x8da10717,// 25 SCX  23 

/// BFD is 3 words. 

/// BFD tot_len        : 1627 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 190 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 190 

/// BFD lencrypto      : 64 

/// BFD ofstcrypto     : 96 

/// BFD (ofst+len)cry  : 160 

/// BFD ofstiv         : 4 

/// BFD ofsticv        : 976 

    0x000000be,// 26 BFD   1 

    0x00600040,// 27 BFD   2 

    0x03d00004,// 28 BFD   3 

/// MFM is 6 words. 

/// MFM vldnibs        : 29 

    0x2900a143,// 29 MFM   1 

    0xf3546827,// 30 MFM   2 

    0xc2916462,// 31 MFM   3 

    0x32535cef,// 32 MFM   4 

    0x9fe1d050,// 33 MFM   5 

    0x16ba3000,// 34 MFM   6 

/// BDA is 408 words. 

/// BDA size     is 1627 (0x65b) 

/// BDA id       is 0x5aee 

    0x065b5aee,// 35 BDA   1 

/// PAY Generic Data size   : 1627 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0x34b149f4,// 36 PAY   1 

    0x0893b453,// 37 PAY   2 

    0xde108f3b,// 38 PAY   3 

    0xc77048ae,// 39 PAY   4 

    0xcda5d842,// 40 PAY   5 

    0x15625d34,// 41 PAY   6 

    0x3c7991fb,// 42 PAY   7 

    0x8bc66ef0,// 43 PAY   8 

    0x6cc44c50,// 44 PAY   9 

    0x4caddf4a,// 45 PAY  10 

    0x3bb9c417,// 46 PAY  11 

    0x34103ec8,// 47 PAY  12 

    0x0718b64e,// 48 PAY  13 

    0xb521271b,// 49 PAY  14 

    0x37785e81,// 50 PAY  15 

    0x2dd2e6b6,// 51 PAY  16 

    0x54edfa29,// 52 PAY  17 

    0x601a49a2,// 53 PAY  18 

    0x503b972f,// 54 PAY  19 

    0x4bf2f32d,// 55 PAY  20 

    0x83e8b926,// 56 PAY  21 

    0xf518f492,// 57 PAY  22 

    0x7c259850,// 58 PAY  23 

    0xba1a0c66,// 59 PAY  24 

    0x69336cd2,// 60 PAY  25 

    0x4c47c613,// 61 PAY  26 

    0x24847b37,// 62 PAY  27 

    0xfc97c008,// 63 PAY  28 

    0x0f7eab39,// 64 PAY  29 

    0x6cbf9a90,// 65 PAY  30 

    0x2a52a4ff,// 66 PAY  31 

    0x1d0a1a14,// 67 PAY  32 

    0x98c6ed57,// 68 PAY  33 

    0x2af1c394,// 69 PAY  34 

    0xdf7c1c81,// 70 PAY  35 

    0x36b1fc43,// 71 PAY  36 

    0xa694cf07,// 72 PAY  37 

    0xf2dcf56d,// 73 PAY  38 

    0xc0a622c9,// 74 PAY  39 

    0xf532d49b,// 75 PAY  40 

    0xad15c4bb,// 76 PAY  41 

    0x362fab60,// 77 PAY  42 

    0x58b178ed,// 78 PAY  43 

    0x6f2b381c,// 79 PAY  44 

    0xf1206006,// 80 PAY  45 

    0x565f1929,// 81 PAY  46 

    0x9c211359,// 82 PAY  47 

    0xbb85c0a3,// 83 PAY  48 

    0x2d8899c6,// 84 PAY  49 

    0xd1620b92,// 85 PAY  50 

    0xcb1cbd34,// 86 PAY  51 

    0x0a546adc,// 87 PAY  52 

    0x7f329a48,// 88 PAY  53 

    0x65f5c345,// 89 PAY  54 

    0xbbb475ec,// 90 PAY  55 

    0xdbb7c66e,// 91 PAY  56 

    0xa00951ed,// 92 PAY  57 

    0x51abebe9,// 93 PAY  58 

    0x2ba2bff0,// 94 PAY  59 

    0x95d9222a,// 95 PAY  60 

    0x84a54c20,// 96 PAY  61 

    0xb4bbfd8c,// 97 PAY  62 

    0xfbb495a9,// 98 PAY  63 

    0xc859983d,// 99 PAY  64 

    0x14abac79,// 100 PAY  65 

    0x570164ee,// 101 PAY  66 

    0xbae1f14c,// 102 PAY  67 

    0x1f56759c,// 103 PAY  68 

    0x4f2f3073,// 104 PAY  69 

    0xfcdbea45,// 105 PAY  70 

    0xb9521a34,// 106 PAY  71 

    0x568bc973,// 107 PAY  72 

    0x07170d01,// 108 PAY  73 

    0x2b418779,// 109 PAY  74 

    0x9df8c4f3,// 110 PAY  75 

    0x74638660,// 111 PAY  76 

    0xe2390ca0,// 112 PAY  77 

    0x331e4676,// 113 PAY  78 

    0xe5c01249,// 114 PAY  79 

    0x1c9ae511,// 115 PAY  80 

    0x0243124e,// 116 PAY  81 

    0x372fab29,// 117 PAY  82 

    0x51636147,// 118 PAY  83 

    0xa69a0bb2,// 119 PAY  84 

    0xd8028d9d,// 120 PAY  85 

    0x3de03004,// 121 PAY  86 

    0xe44eff91,// 122 PAY  87 

    0x52dea5f6,// 123 PAY  88 

    0xa058c052,// 124 PAY  89 

    0xdb85f737,// 125 PAY  90 

    0x3091e70a,// 126 PAY  91 

    0xee35e9b6,// 127 PAY  92 

    0x799ba375,// 128 PAY  93 

    0xb24e31f6,// 129 PAY  94 

    0xea66df9b,// 130 PAY  95 

    0x6b2caf27,// 131 PAY  96 

    0x3a3dccde,// 132 PAY  97 

    0xc50356f3,// 133 PAY  98 

    0x2902115b,// 134 PAY  99 

    0xe5559f0e,// 135 PAY 100 

    0x14093c5c,// 136 PAY 101 

    0xb78e919e,// 137 PAY 102 

    0x704065a5,// 138 PAY 103 

    0xe1664ec0,// 139 PAY 104 

    0x2a18f67f,// 140 PAY 105 

    0xed4f460d,// 141 PAY 106 

    0x7c5cfbbd,// 142 PAY 107 

    0xd07cbe76,// 143 PAY 108 

    0xbc01499c,// 144 PAY 109 

    0x4c8f69f1,// 145 PAY 110 

    0x846b01a8,// 146 PAY 111 

    0x6564d339,// 147 PAY 112 

    0x72a3a541,// 148 PAY 113 

    0xca9f8316,// 149 PAY 114 

    0xed78115a,// 150 PAY 115 

    0x31bc7eb8,// 151 PAY 116 

    0x1b3e1472,// 152 PAY 117 

    0xf521e154,// 153 PAY 118 

    0x8d183a2f,// 154 PAY 119 

    0x60916a25,// 155 PAY 120 

    0x58f773c6,// 156 PAY 121 

    0xa354c182,// 157 PAY 122 

    0x25b9df2a,// 158 PAY 123 

    0x927ac74b,// 159 PAY 124 

    0x093c8a95,// 160 PAY 125 

    0x30e1a09a,// 161 PAY 126 

    0x2c5b487b,// 162 PAY 127 

    0x41f86f40,// 163 PAY 128 

    0x440d9f5b,// 164 PAY 129 

    0x1d6baa44,// 165 PAY 130 

    0x9443395d,// 166 PAY 131 

    0xd5a6a006,// 167 PAY 132 

    0x8b1dd47d,// 168 PAY 133 

    0x66be5e5c,// 169 PAY 134 

    0x26fcd882,// 170 PAY 135 

    0x8b317986,// 171 PAY 136 

    0xbf9a0c5b,// 172 PAY 137 

    0x24226e19,// 173 PAY 138 

    0x7ea66bbe,// 174 PAY 139 

    0xb78f01ec,// 175 PAY 140 

    0xe4c597c7,// 176 PAY 141 

    0xe0c67425,// 177 PAY 142 

    0xaecb40d1,// 178 PAY 143 

    0xc701a0aa,// 179 PAY 144 

    0xad8aa9cf,// 180 PAY 145 

    0x53765bb3,// 181 PAY 146 

    0xead7f775,// 182 PAY 147 

    0xc862064a,// 183 PAY 148 

    0xaacb161f,// 184 PAY 149 

    0x29b7bd96,// 185 PAY 150 

    0x436e1ec7,// 186 PAY 151 

    0x25cade8f,// 187 PAY 152 

    0x372a07d3,// 188 PAY 153 

    0x3d1bd843,// 189 PAY 154 

    0x0e36ca37,// 190 PAY 155 

    0xd27b6518,// 191 PAY 156 

    0x762f6b2b,// 192 PAY 157 

    0xa5d22678,// 193 PAY 158 

    0x2a269adf,// 194 PAY 159 

    0xe8fe853a,// 195 PAY 160 

    0xdfaf1f9a,// 196 PAY 161 

    0xcc47ddd3,// 197 PAY 162 

    0x94c562e4,// 198 PAY 163 

    0xb258dad4,// 199 PAY 164 

    0xc6bc47ef,// 200 PAY 165 

    0x0bf21330,// 201 PAY 166 

    0x40efcb52,// 202 PAY 167 

    0x6a0c1c9e,// 203 PAY 168 

    0x4028a955,// 204 PAY 169 

    0xa211b234,// 205 PAY 170 

    0x2b4cfbbd,// 206 PAY 171 

    0x90b7a519,// 207 PAY 172 

    0x89a80d12,// 208 PAY 173 

    0x765e2b49,// 209 PAY 174 

    0x300d713c,// 210 PAY 175 

    0x663439d1,// 211 PAY 176 

    0xa0f4e67d,// 212 PAY 177 

    0xad86c10f,// 213 PAY 178 

    0x57bddc45,// 214 PAY 179 

    0x26946cf6,// 215 PAY 180 

    0xeb23201e,// 216 PAY 181 

    0xd0040ee2,// 217 PAY 182 

    0xcc0e81ef,// 218 PAY 183 

    0x047d57a5,// 219 PAY 184 

    0x336663a8,// 220 PAY 185 

    0x8cdcc7fe,// 221 PAY 186 

    0xefeefb18,// 222 PAY 187 

    0xd79f3741,// 223 PAY 188 

    0x3e0467d3,// 224 PAY 189 

    0xdcceb00c,// 225 PAY 190 

    0xf0bb588e,// 226 PAY 191 

    0xfe28b5a7,// 227 PAY 192 

    0x6829efb8,// 228 PAY 193 

    0x1e5aeb80,// 229 PAY 194 

    0xf739dddf,// 230 PAY 195 

    0x6cabdb76,// 231 PAY 196 

    0xf13eea99,// 232 PAY 197 

    0x72f55e78,// 233 PAY 198 

    0x059dc7a6,// 234 PAY 199 

    0xef432c35,// 235 PAY 200 

    0xb175c672,// 236 PAY 201 

    0x09e4360a,// 237 PAY 202 

    0x5f47cc1b,// 238 PAY 203 

    0x611666fa,// 239 PAY 204 

    0xc6055694,// 240 PAY 205 

    0x15ba1d21,// 241 PAY 206 

    0xedeefcc3,// 242 PAY 207 

    0x7d389f7d,// 243 PAY 208 

    0x3919e234,// 244 PAY 209 

    0xf4a962f3,// 245 PAY 210 

    0x6a445ee7,// 246 PAY 211 

    0xa039a10d,// 247 PAY 212 

    0xa98e23f4,// 248 PAY 213 

    0xe7cfe7e8,// 249 PAY 214 

    0x2455c6e2,// 250 PAY 215 

    0xf2423e8e,// 251 PAY 216 

    0xc17bbf6e,// 252 PAY 217 

    0x74b7ed6b,// 253 PAY 218 

    0x8ce1cbe5,// 254 PAY 219 

    0x1d276b95,// 255 PAY 220 

    0x83059754,// 256 PAY 221 

    0x3bea12b5,// 257 PAY 222 

    0xfdd8c924,// 258 PAY 223 

    0x537e2a26,// 259 PAY 224 

    0xc343612f,// 260 PAY 225 

    0x0d632e7c,// 261 PAY 226 

    0x424e9a2a,// 262 PAY 227 

    0xad6c552f,// 263 PAY 228 

    0x48797e51,// 264 PAY 229 

    0x93cf7f2b,// 265 PAY 230 

    0xa05977e8,// 266 PAY 231 

    0x6f376e88,// 267 PAY 232 

    0x76e09e46,// 268 PAY 233 

    0xaf98c4fb,// 269 PAY 234 

    0x5e0354d1,// 270 PAY 235 

    0x10e1c65b,// 271 PAY 236 

    0x26e713a1,// 272 PAY 237 

    0xc81203f5,// 273 PAY 238 

    0x2ee4b1ae,// 274 PAY 239 

    0x2c4e7110,// 275 PAY 240 

    0x08c50c82,// 276 PAY 241 

    0x8fb30aa4,// 277 PAY 242 

    0xcddb9653,// 278 PAY 243 

    0x25caa15d,// 279 PAY 244 

    0xf799ebef,// 280 PAY 245 

    0xb9a44399,// 281 PAY 246 

    0x5018d0b0,// 282 PAY 247 

    0x3042d401,// 283 PAY 248 

    0x7b791494,// 284 PAY 249 

    0x7accd9a8,// 285 PAY 250 

    0x53ea24bd,// 286 PAY 251 

    0x2c63bac6,// 287 PAY 252 

    0x4c5b0e62,// 288 PAY 253 

    0xa0df6f40,// 289 PAY 254 

    0x15c7e5fc,// 290 PAY 255 

    0x659c5c6b,// 291 PAY 256 

    0x2bafa06f,// 292 PAY 257 

    0x06d8442a,// 293 PAY 258 

    0x8ac77a33,// 294 PAY 259 

    0x1caf788f,// 295 PAY 260 

    0x29bfd3b0,// 296 PAY 261 

    0x2ef0a190,// 297 PAY 262 

    0xeccd1a8a,// 298 PAY 263 

    0x1c8af9c1,// 299 PAY 264 

    0xdd7bcd57,// 300 PAY 265 

    0x28917edd,// 301 PAY 266 

    0x2ad38c90,// 302 PAY 267 

    0xd607c043,// 303 PAY 268 

    0x99326c50,// 304 PAY 269 

    0xddc7efe6,// 305 PAY 270 

    0x4af2322d,// 306 PAY 271 

    0x677a82ba,// 307 PAY 272 

    0x589eedef,// 308 PAY 273 

    0xb73abb3b,// 309 PAY 274 

    0x7bb95ffa,// 310 PAY 275 

    0x8ab1bd4b,// 311 PAY 276 

    0x5bd25eef,// 312 PAY 277 

    0xaf384d14,// 313 PAY 278 

    0x9d9443df,// 314 PAY 279 

    0xb6a7b111,// 315 PAY 280 

    0x24dcf8c9,// 316 PAY 281 

    0x994ad3fe,// 317 PAY 282 

    0x4fdcef7e,// 318 PAY 283 

    0x39e7b392,// 319 PAY 284 

    0xf9a509cf,// 320 PAY 285 

    0xd647f1ff,// 321 PAY 286 

    0x6796bd2c,// 322 PAY 287 

    0x0853cdd4,// 323 PAY 288 

    0x06acf5e3,// 324 PAY 289 

    0x3965050b,// 325 PAY 290 

    0xc0ccb065,// 326 PAY 291 

    0xfc5a6715,// 327 PAY 292 

    0xdcb9bd85,// 328 PAY 293 

    0x3a3a355a,// 329 PAY 294 

    0x6b73aac9,// 330 PAY 295 

    0xd4a20c86,// 331 PAY 296 

    0xe351c63c,// 332 PAY 297 

    0x7689acff,// 333 PAY 298 

    0xcc2ab1c2,// 334 PAY 299 

    0x0146bf3d,// 335 PAY 300 

    0xc3b34387,// 336 PAY 301 

    0x97a4254e,// 337 PAY 302 

    0xdeed97f4,// 338 PAY 303 

    0xc20c9f43,// 339 PAY 304 

    0xa17154d2,// 340 PAY 305 

    0x912fe102,// 341 PAY 306 

    0xac97d1a2,// 342 PAY 307 

    0x270511cb,// 343 PAY 308 

    0x6f63a0d0,// 344 PAY 309 

    0xebc8ac04,// 345 PAY 310 

    0xdd2ee351,// 346 PAY 311 

    0xc069ed2d,// 347 PAY 312 

    0xa9b9803e,// 348 PAY 313 

    0x068fb93d,// 349 PAY 314 

    0x7ff58a9f,// 350 PAY 315 

    0x4d5ca911,// 351 PAY 316 

    0x0ca208cb,// 352 PAY 317 

    0x634bea88,// 353 PAY 318 

    0xcf0dfdc6,// 354 PAY 319 

    0xd712c825,// 355 PAY 320 

    0x76d0ddaa,// 356 PAY 321 

    0x9ab55f02,// 357 PAY 322 

    0xdffebf99,// 358 PAY 323 

    0xc28d730e,// 359 PAY 324 

    0xe436979c,// 360 PAY 325 

    0x65e1c112,// 361 PAY 326 

    0x65772785,// 362 PAY 327 

    0x122c6d8c,// 363 PAY 328 

    0x5d793523,// 364 PAY 329 

    0x733a1b4d,// 365 PAY 330 

    0xd6176b84,// 366 PAY 331 

    0xe86b0335,// 367 PAY 332 

    0xfad14dde,// 368 PAY 333 

    0x36777a3f,// 369 PAY 334 

    0x62774976,// 370 PAY 335 

    0x2f6d3b34,// 371 PAY 336 

    0xacbd237d,// 372 PAY 337 

    0x01d6b766,// 373 PAY 338 

    0x75e1ba9e,// 374 PAY 339 

    0x00239250,// 375 PAY 340 

    0x64b2db71,// 376 PAY 341 

    0x32ab4164,// 377 PAY 342 

    0x7a50d7aa,// 378 PAY 343 

    0xaa4c4289,// 379 PAY 344 

    0x161efa2e,// 380 PAY 345 

    0xda2e8dbd,// 381 PAY 346 

    0xf82f2157,// 382 PAY 347 

    0x15bda06a,// 383 PAY 348 

    0xa3b535c3,// 384 PAY 349 

    0x752a4ce1,// 385 PAY 350 

    0x4538a5d8,// 386 PAY 351 

    0xdd4e1f73,// 387 PAY 352 

    0x85c82fd0,// 388 PAY 353 

    0xfaa865d0,// 389 PAY 354 

    0x45ddf5a6,// 390 PAY 355 

    0x5f3cbe26,// 391 PAY 356 

    0x2d47d674,// 392 PAY 357 

    0xe6b16b3d,// 393 PAY 358 

    0x8be33066,// 394 PAY 359 

    0x788f4636,// 395 PAY 360 

    0xa80851b8,// 396 PAY 361 

    0x40c7d263,// 397 PAY 362 

    0xdc2db729,// 398 PAY 363 

    0x765269f1,// 399 PAY 364 

    0x98b6e39a,// 400 PAY 365 

    0xeccdd1de,// 401 PAY 366 

    0x51760d36,// 402 PAY 367 

    0x22210e8a,// 403 PAY 368 

    0xdf8c24a9,// 404 PAY 369 

    0x2f28d4fa,// 405 PAY 370 

    0x1b6cb558,// 406 PAY 371 

    0xc848f11c,// 407 PAY 372 

    0xb0fbef19,// 408 PAY 373 

    0x715ad0df,// 409 PAY 374 

    0x19ba9e99,// 410 PAY 375 

    0x435ba109,// 411 PAY 376 

    0xc406e7bf,// 412 PAY 377 

    0x8d606cea,// 413 PAY 378 

    0xfb3074da,// 414 PAY 379 

    0xc0e1aaf2,// 415 PAY 380 

    0x668a9cd2,// 416 PAY 381 

    0x5f429812,// 417 PAY 382 

    0x4d7a6f1e,// 418 PAY 383 

    0x1c98f45a,// 419 PAY 384 

    0x2cce5fd3,// 420 PAY 385 

    0xb319f5b8,// 421 PAY 386 

    0xc5a1aeff,// 422 PAY 387 

    0x509690b9,// 423 PAY 388 

    0xde179983,// 424 PAY 389 

    0x3920680b,// 425 PAY 390 

    0xa8945cce,// 426 PAY 391 

    0x47aa8fb9,// 427 PAY 392 

    0x36691774,// 428 PAY 393 

    0xfc93d479,// 429 PAY 394 

    0xa4dbc077,// 430 PAY 395 

    0x4e395a01,// 431 PAY 396 

    0x7d8734be,// 432 PAY 397 

    0xd756441a,// 433 PAY 398 

    0xaa54ac1e,// 434 PAY 399 

    0x24cb5e4d,// 435 PAY 400 

    0xf1c68c10,// 436 PAY 401 

    0xa1198d72,// 437 PAY 402 

    0xf006a015,// 438 PAY 403 

    0xaa3dd3d0,// 439 PAY 404 

    0xbd5979f4,// 440 PAY 405 

    0x6d304162,// 441 PAY 406 

    0x69e28300,// 442 PAY 407 

/// STA is 1 words. 

/// STA num_pkts       : 33 

/// STA pkt_idx        : 109 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x19 

    0x01b41921 // 443 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt55_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x03 

/// ECH pdu_tag        : 0x00 

    0x00030000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x808448b2,// 4 SCX   2 

    0x00003584,// 5 SCX   3 

    0x46b5dd68,// 6 SCX   4 

    0x3966cc0b,// 7 SCX   5 

    0x5b2535c0,// 8 SCX   6 

    0xa106ee22,// 9 SCX   7 

    0x7593644e,// 10 SCX   8 

    0xfeb0a335,// 11 SCX   9 

    0xa13e06f4,// 12 SCX  10 

    0xb276728c,// 13 SCX  11 

    0xf0915f1a,// 14 SCX  12 

    0x122e7aa6,// 15 SCX  13 

    0x87110f75,// 16 SCX  14 

    0xf57b477c,// 17 SCX  15 

    0xffa4d232,// 18 SCX  16 

    0x68e37ac6,// 19 SCX  17 

    0x579fd941,// 20 SCX  18 

    0x3a3cd34e,// 21 SCX  19 

    0x1bda53a5,// 22 SCX  20 

    0xe0a3270b,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1804 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 1578 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1578 

/// BFD lencrypto      : 1232 

/// BFD ofstcrypto     : 280 

/// BFD (ofst+len)cry  : 1512 

/// BFD ofstiv         : 136 

/// BFD ofsticv        : 1672 

    0x0000062a,// 24 BFD   1 

    0x011804d0,// 25 BFD   2 

    0x06880088,// 26 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c008681,// 27 MFM   1 

    0xa1e23c79,// 28 MFM   2 

    0xec3e4a2e,// 29 MFM   3 

    0xb79bfc28,// 30 MFM   4 

    0x6cdc9302,// 31 MFM   5 

    0xfc995c92,// 32 MFM   6 

    0xc07cd8ac,// 33 MFM   7 

    0x9ea070e8,// 34 MFM   8 

    0xa362a820,// 35 MFM   9 

    0x07bdfccf,// 36 MFM  10 

    0xb4e83127,// 37 MFM  11 

    0x503e3790,// 38 MFM  12 

    0x2129109e,// 39 MFM  13 

    0x8153318e,// 40 MFM  14 

    0x2a08634e,// 41 MFM  15 

    0xe3d3dfea,// 42 MFM  16 

/// BDA is 452 words. 

/// BDA size     is 1804 (0x70c) 

/// BDA id       is 0x49d1 

    0x070c49d1,// 43 BDA   1 

/// PAY Generic Data size   : 1804 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0x94f57c48,// 44 PAY   1 

    0x277a8a19,// 45 PAY   2 

    0xee558153,// 46 PAY   3 

    0x8fcbb7d2,// 47 PAY   4 

    0x88099a36,// 48 PAY   5 

    0x6d47157a,// 49 PAY   6 

    0xcb15cd71,// 50 PAY   7 

    0x5ae93a45,// 51 PAY   8 

    0xea012dfd,// 52 PAY   9 

    0xbf16031d,// 53 PAY  10 

    0x0e3b1bbf,// 54 PAY  11 

    0xeb38b04f,// 55 PAY  12 

    0x39ecbddb,// 56 PAY  13 

    0x33b1efc7,// 57 PAY  14 

    0xc78dff1b,// 58 PAY  15 

    0x5ab9b5ec,// 59 PAY  16 

    0x7dcc89ba,// 60 PAY  17 

    0x7456c910,// 61 PAY  18 

    0x2d5b279b,// 62 PAY  19 

    0x41aff120,// 63 PAY  20 

    0x2e5e5249,// 64 PAY  21 

    0x4368fde9,// 65 PAY  22 

    0x8c3d65c3,// 66 PAY  23 

    0xc6711a14,// 67 PAY  24 

    0xdd4f88dd,// 68 PAY  25 

    0x8dd3927e,// 69 PAY  26 

    0x92421c3f,// 70 PAY  27 

    0x038c566b,// 71 PAY  28 

    0x5d1a1fb7,// 72 PAY  29 

    0x6ddc4045,// 73 PAY  30 

    0x38461262,// 74 PAY  31 

    0x7ab9f94f,// 75 PAY  32 

    0xb4003ab5,// 76 PAY  33 

    0x1e35803e,// 77 PAY  34 

    0x2bd124e0,// 78 PAY  35 

    0x503eb667,// 79 PAY  36 

    0x40c454d3,// 80 PAY  37 

    0x698fc5fb,// 81 PAY  38 

    0xf6ef5726,// 82 PAY  39 

    0xb4b31e5b,// 83 PAY  40 

    0x905596ef,// 84 PAY  41 

    0x98319123,// 85 PAY  42 

    0xfad8ab2e,// 86 PAY  43 

    0x105898b7,// 87 PAY  44 

    0xeda103f8,// 88 PAY  45 

    0x8184953b,// 89 PAY  46 

    0x5b305945,// 90 PAY  47 

    0x517e6c46,// 91 PAY  48 

    0xafe29b3b,// 92 PAY  49 

    0xe12720f7,// 93 PAY  50 

    0x8d0c7a15,// 94 PAY  51 

    0xa396c7af,// 95 PAY  52 

    0x928a02e3,// 96 PAY  53 

    0x09f215a8,// 97 PAY  54 

    0xc7bcf216,// 98 PAY  55 

    0x4f7811aa,// 99 PAY  56 

    0x17834467,// 100 PAY  57 

    0x7b207636,// 101 PAY  58 

    0x922ad5ab,// 102 PAY  59 

    0x974d7ab6,// 103 PAY  60 

    0x1ae0739e,// 104 PAY  61 

    0xcf186b5d,// 105 PAY  62 

    0x3539a9da,// 106 PAY  63 

    0xa4668b9e,// 107 PAY  64 

    0xe0416142,// 108 PAY  65 

    0x65173df6,// 109 PAY  66 

    0x84af7802,// 110 PAY  67 

    0x08e54d8c,// 111 PAY  68 

    0xfc680977,// 112 PAY  69 

    0x2031b82b,// 113 PAY  70 

    0xfb7a483d,// 114 PAY  71 

    0x51c3e6cb,// 115 PAY  72 

    0xd73b6349,// 116 PAY  73 

    0xca23b6eb,// 117 PAY  74 

    0xef4a6ea3,// 118 PAY  75 

    0x89bb1bfa,// 119 PAY  76 

    0x3dfec0ee,// 120 PAY  77 

    0xb05575b8,// 121 PAY  78 

    0xbbc2a76b,// 122 PAY  79 

    0x26479f8a,// 123 PAY  80 

    0xd10c9171,// 124 PAY  81 

    0x6ec0b869,// 125 PAY  82 

    0x4660d73a,// 126 PAY  83 

    0x3c5a0b07,// 127 PAY  84 

    0xcaed508c,// 128 PAY  85 

    0x6207031b,// 129 PAY  86 

    0x5a54d481,// 130 PAY  87 

    0x45a28e5f,// 131 PAY  88 

    0x78d22c43,// 132 PAY  89 

    0x7af9ddbb,// 133 PAY  90 

    0xd05a6e8a,// 134 PAY  91 

    0xbca20a07,// 135 PAY  92 

    0xca4a048b,// 136 PAY  93 

    0x786a0a22,// 137 PAY  94 

    0x35efcb67,// 138 PAY  95 

    0xa7415a02,// 139 PAY  96 

    0xd4fcc897,// 140 PAY  97 

    0xf51557d8,// 141 PAY  98 

    0x79cba2f7,// 142 PAY  99 

    0x8beaf810,// 143 PAY 100 

    0x8d17b168,// 144 PAY 101 

    0xa4d3a7dd,// 145 PAY 102 

    0x671b1dad,// 146 PAY 103 

    0x9a33088c,// 147 PAY 104 

    0xb52bf356,// 148 PAY 105 

    0x4a0c75f4,// 149 PAY 106 

    0xaa859a11,// 150 PAY 107 

    0x980b8970,// 151 PAY 108 

    0xa2c01cda,// 152 PAY 109 

    0x59126296,// 153 PAY 110 

    0xee8cbf53,// 154 PAY 111 

    0x523171a0,// 155 PAY 112 

    0x8640fa14,// 156 PAY 113 

    0x9bc8f352,// 157 PAY 114 

    0xd9b1b3ba,// 158 PAY 115 

    0x6b3dc7f4,// 159 PAY 116 

    0xb13dd784,// 160 PAY 117 

    0xcc23e03e,// 161 PAY 118 

    0x3701f0fe,// 162 PAY 119 

    0xf2362272,// 163 PAY 120 

    0x6cfff145,// 164 PAY 121 

    0xb1324427,// 165 PAY 122 

    0x3f7cd04e,// 166 PAY 123 

    0x12fff0c9,// 167 PAY 124 

    0x2c225358,// 168 PAY 125 

    0xe5d5804c,// 169 PAY 126 

    0xd44b1912,// 170 PAY 127 

    0x16a62141,// 171 PAY 128 

    0x5a7eea4f,// 172 PAY 129 

    0x2173baf3,// 173 PAY 130 

    0xc0288211,// 174 PAY 131 

    0xdf19aedc,// 175 PAY 132 

    0x898a2a75,// 176 PAY 133 

    0x769b97a8,// 177 PAY 134 

    0xdb7a4b6e,// 178 PAY 135 

    0x3b965718,// 179 PAY 136 

    0x908d00cb,// 180 PAY 137 

    0x4b49cbf6,// 181 PAY 138 

    0xfc4dca0f,// 182 PAY 139 

    0x2571de1a,// 183 PAY 140 

    0xaae39e4c,// 184 PAY 141 

    0xe0cc6240,// 185 PAY 142 

    0x8f033dd7,// 186 PAY 143 

    0x75cf2f73,// 187 PAY 144 

    0x4923545d,// 188 PAY 145 

    0x0dec8fdb,// 189 PAY 146 

    0x299de746,// 190 PAY 147 

    0x8b919e44,// 191 PAY 148 

    0x258daf29,// 192 PAY 149 

    0x16ba26a5,// 193 PAY 150 

    0xab430b86,// 194 PAY 151 

    0x423d1bba,// 195 PAY 152 

    0xa477bee3,// 196 PAY 153 

    0x87174e2c,// 197 PAY 154 

    0x102ca91e,// 198 PAY 155 

    0x4a32eecd,// 199 PAY 156 

    0x912fb967,// 200 PAY 157 

    0xbfc38dbf,// 201 PAY 158 

    0x6ef4d387,// 202 PAY 159 

    0xc4f668ec,// 203 PAY 160 

    0xf588a5a4,// 204 PAY 161 

    0x32b4a686,// 205 PAY 162 

    0x5029d91c,// 206 PAY 163 

    0xf506e45b,// 207 PAY 164 

    0x5cde5df2,// 208 PAY 165 

    0xdea8f5a9,// 209 PAY 166 

    0xfb54df7e,// 210 PAY 167 

    0x8d3816e4,// 211 PAY 168 

    0x21d5585b,// 212 PAY 169 

    0xbf27f1fc,// 213 PAY 170 

    0x3a2308fe,// 214 PAY 171 

    0x43d4e770,// 215 PAY 172 

    0x8f2bdd66,// 216 PAY 173 

    0xe4b521d2,// 217 PAY 174 

    0x05079f02,// 218 PAY 175 

    0xdb073c27,// 219 PAY 176 

    0xaa505dbb,// 220 PAY 177 

    0xfc144226,// 221 PAY 178 

    0x45131d51,// 222 PAY 179 

    0x0dd849ca,// 223 PAY 180 

    0x9b296f66,// 224 PAY 181 

    0x330e7d14,// 225 PAY 182 

    0x9f0a8d4c,// 226 PAY 183 

    0xd10ddd99,// 227 PAY 184 

    0x387cf107,// 228 PAY 185 

    0x6f621c77,// 229 PAY 186 

    0x87aa6180,// 230 PAY 187 

    0x347d3e58,// 231 PAY 188 

    0x83be3cf2,// 232 PAY 189 

    0xf3651575,// 233 PAY 190 

    0x2e92af42,// 234 PAY 191 

    0xb796dbc1,// 235 PAY 192 

    0xaa77c818,// 236 PAY 193 

    0x9189bd39,// 237 PAY 194 

    0x4897f3e4,// 238 PAY 195 

    0xed5ea957,// 239 PAY 196 

    0xb47995ee,// 240 PAY 197 

    0xc2ea1b1b,// 241 PAY 198 

    0xc6386ff3,// 242 PAY 199 

    0xbfb92b8d,// 243 PAY 200 

    0x654601ae,// 244 PAY 201 

    0x26952a54,// 245 PAY 202 

    0x6c3ac064,// 246 PAY 203 

    0x59b3f086,// 247 PAY 204 

    0xd460674a,// 248 PAY 205 

    0xa42facda,// 249 PAY 206 

    0xf9b94024,// 250 PAY 207 

    0x76902122,// 251 PAY 208 

    0x92f24226,// 252 PAY 209 

    0x26da7860,// 253 PAY 210 

    0x8f076055,// 254 PAY 211 

    0x5351df94,// 255 PAY 212 

    0xdbc3fec5,// 256 PAY 213 

    0xd9b64ade,// 257 PAY 214 

    0xc570cd3d,// 258 PAY 215 

    0x1fd5aa5a,// 259 PAY 216 

    0xf6c732e9,// 260 PAY 217 

    0x44669a3c,// 261 PAY 218 

    0x24ce86cb,// 262 PAY 219 

    0xafb5a550,// 263 PAY 220 

    0x2395ac67,// 264 PAY 221 

    0xbe9bb8a3,// 265 PAY 222 

    0x289ff458,// 266 PAY 223 

    0xf2862ac8,// 267 PAY 224 

    0xe7406ff4,// 268 PAY 225 

    0x58d2390f,// 269 PAY 226 

    0x9229c706,// 270 PAY 227 

    0x24c7e829,// 271 PAY 228 

    0x0088955e,// 272 PAY 229 

    0x0d0bf024,// 273 PAY 230 

    0x5875a0c8,// 274 PAY 231 

    0x515153a4,// 275 PAY 232 

    0x592d392d,// 276 PAY 233 

    0xbb5d2cbf,// 277 PAY 234 

    0xd2037f00,// 278 PAY 235 

    0xb1d1ec18,// 279 PAY 236 

    0x41058f7c,// 280 PAY 237 

    0x6f745d12,// 281 PAY 238 

    0xd2268a70,// 282 PAY 239 

    0xd19afc40,// 283 PAY 240 

    0x2eabcb2d,// 284 PAY 241 

    0x6654f0f1,// 285 PAY 242 

    0x7b4e183c,// 286 PAY 243 

    0x152755ee,// 287 PAY 244 

    0x2f319aff,// 288 PAY 245 

    0x30751a7e,// 289 PAY 246 

    0x4ed095fe,// 290 PAY 247 

    0x292a12ff,// 291 PAY 248 

    0x3aac6f21,// 292 PAY 249 

    0xfa46a044,// 293 PAY 250 

    0x12a66109,// 294 PAY 251 

    0x9467c0ca,// 295 PAY 252 

    0x425dd28f,// 296 PAY 253 

    0xf6268d7c,// 297 PAY 254 

    0xb96f914e,// 298 PAY 255 

    0x9c2e41f6,// 299 PAY 256 

    0x7ea9d2e4,// 300 PAY 257 

    0x8e1debb7,// 301 PAY 258 

    0x648d783b,// 302 PAY 259 

    0x910e7357,// 303 PAY 260 

    0x9536726e,// 304 PAY 261 

    0x6d767a4f,// 305 PAY 262 

    0x36383cc5,// 306 PAY 263 

    0x46081149,// 307 PAY 264 

    0xd56c3447,// 308 PAY 265 

    0x7536c9c1,// 309 PAY 266 

    0xdf8ee2ef,// 310 PAY 267 

    0xa7dae322,// 311 PAY 268 

    0xbb4845b8,// 312 PAY 269 

    0x8df45ecf,// 313 PAY 270 

    0x1be06629,// 314 PAY 271 

    0x37b7b6ba,// 315 PAY 272 

    0xbb447056,// 316 PAY 273 

    0x62ab7f31,// 317 PAY 274 

    0x80f9556c,// 318 PAY 275 

    0x3d62f5a7,// 319 PAY 276 

    0xb88ac8b7,// 320 PAY 277 

    0xba28510d,// 321 PAY 278 

    0x5b143c6a,// 322 PAY 279 

    0x4558e543,// 323 PAY 280 

    0x02c5fefb,// 324 PAY 281 

    0xf7c2bd78,// 325 PAY 282 

    0xd7310f27,// 326 PAY 283 

    0x2ebc9200,// 327 PAY 284 

    0xb898684d,// 328 PAY 285 

    0xf21d0d8a,// 329 PAY 286 

    0x60d428cd,// 330 PAY 287 

    0x0edf784c,// 331 PAY 288 

    0x6dbfa4ec,// 332 PAY 289 

    0x133fa208,// 333 PAY 290 

    0xf491c15f,// 334 PAY 291 

    0x3b744065,// 335 PAY 292 

    0xd02cf3a5,// 336 PAY 293 

    0x3c376a04,// 337 PAY 294 

    0xbce2dbb5,// 338 PAY 295 

    0x771f99a1,// 339 PAY 296 

    0xc8daf9bc,// 340 PAY 297 

    0x3b124e77,// 341 PAY 298 

    0x342799d7,// 342 PAY 299 

    0x2a9b6c18,// 343 PAY 300 

    0x0056f6a7,// 344 PAY 301 

    0xd2dd7347,// 345 PAY 302 

    0xe06b0be5,// 346 PAY 303 

    0xc616ca9e,// 347 PAY 304 

    0x6c7a26bc,// 348 PAY 305 

    0xd4043f36,// 349 PAY 306 

    0x3d3c246c,// 350 PAY 307 

    0x234e948d,// 351 PAY 308 

    0x2d9c647b,// 352 PAY 309 

    0x805c3318,// 353 PAY 310 

    0xb2140ad6,// 354 PAY 311 

    0xe0e30fe6,// 355 PAY 312 

    0xf55accaf,// 356 PAY 313 

    0x0f2d2158,// 357 PAY 314 

    0x4cccf779,// 358 PAY 315 

    0x0f6f0651,// 359 PAY 316 

    0x97026f97,// 360 PAY 317 

    0x5aa703de,// 361 PAY 318 

    0xc2cb002d,// 362 PAY 319 

    0x756cdec0,// 363 PAY 320 

    0x6b83ebfb,// 364 PAY 321 

    0xe2a1a567,// 365 PAY 322 

    0x96134765,// 366 PAY 323 

    0x896afc2e,// 367 PAY 324 

    0xe6d9abec,// 368 PAY 325 

    0x58662b6c,// 369 PAY 326 

    0xd2ff8ee5,// 370 PAY 327 

    0xed0d35d4,// 371 PAY 328 

    0x580d74a8,// 372 PAY 329 

    0xf5e6c37f,// 373 PAY 330 

    0x95fcf8a8,// 374 PAY 331 

    0xf2bccb5b,// 375 PAY 332 

    0x8b835488,// 376 PAY 333 

    0x16c1015e,// 377 PAY 334 

    0xa76eb590,// 378 PAY 335 

    0x83e602c4,// 379 PAY 336 

    0x54d44ad3,// 380 PAY 337 

    0x7203cc52,// 381 PAY 338 

    0x9db509cf,// 382 PAY 339 

    0xa68c80a4,// 383 PAY 340 

    0x642425db,// 384 PAY 341 

    0xccc6d74a,// 385 PAY 342 

    0x75db52c3,// 386 PAY 343 

    0x6b89ef6d,// 387 PAY 344 

    0xf3724e80,// 388 PAY 345 

    0x6a98195f,// 389 PAY 346 

    0x15b1a3ba,// 390 PAY 347 

    0xd65a18f7,// 391 PAY 348 

    0xecf87345,// 392 PAY 349 

    0xb8b32b23,// 393 PAY 350 

    0xefcd6dbb,// 394 PAY 351 

    0xce57cd5b,// 395 PAY 352 

    0x685f1b40,// 396 PAY 353 

    0x0f9f7d28,// 397 PAY 354 

    0x6dd1fd34,// 398 PAY 355 

    0xb9b2be4f,// 399 PAY 356 

    0xf1aa92d0,// 400 PAY 357 

    0xcc035e6e,// 401 PAY 358 

    0xa892525c,// 402 PAY 359 

    0x0ae090f9,// 403 PAY 360 

    0x6020fb7f,// 404 PAY 361 

    0xc25241f4,// 405 PAY 362 

    0x2ac01250,// 406 PAY 363 

    0x5742c12b,// 407 PAY 364 

    0x59529cb5,// 408 PAY 365 

    0xc897d60b,// 409 PAY 366 

    0x7be5696f,// 410 PAY 367 

    0xa36ca485,// 411 PAY 368 

    0x88b5225e,// 412 PAY 369 

    0xfa1ab7b4,// 413 PAY 370 

    0xd5fe1b6b,// 414 PAY 371 

    0x9687ed01,// 415 PAY 372 

    0x752bb174,// 416 PAY 373 

    0xaf48c5dd,// 417 PAY 374 

    0x26dfd802,// 418 PAY 375 

    0x48a8bb12,// 419 PAY 376 

    0x3d8875fe,// 420 PAY 377 

    0x63d294b3,// 421 PAY 378 

    0xa572a5b0,// 422 PAY 379 

    0x34dae4bf,// 423 PAY 380 

    0xf858201f,// 424 PAY 381 

    0xb68a6c6c,// 425 PAY 382 

    0x71969a27,// 426 PAY 383 

    0xa788b181,// 427 PAY 384 

    0x56113af0,// 428 PAY 385 

    0x7cf10abd,// 429 PAY 386 

    0x43e7a022,// 430 PAY 387 

    0x69f17c4b,// 431 PAY 388 

    0x6db384b3,// 432 PAY 389 

    0x82d10f89,// 433 PAY 390 

    0xfd8be6f6,// 434 PAY 391 

    0x2de789d6,// 435 PAY 392 

    0x4f36b83d,// 436 PAY 393 

    0xf089fa2e,// 437 PAY 394 

    0x65d8de8d,// 438 PAY 395 

    0xbc9b7456,// 439 PAY 396 

    0xff30a335,// 440 PAY 397 

    0xe4298cbe,// 441 PAY 398 

    0x2b20e12d,// 442 PAY 399 

    0xf77c5f87,// 443 PAY 400 

    0xf3710784,// 444 PAY 401 

    0x500ff1e7,// 445 PAY 402 

    0x9cb00780,// 446 PAY 403 

    0xe8d90349,// 447 PAY 404 

    0x38233271,// 448 PAY 405 

    0xa69b83b7,// 449 PAY 406 

    0x2739cf11,// 450 PAY 407 

    0xc9a761a2,// 451 PAY 408 

    0xb80a4b43,// 452 PAY 409 

    0x9d4e32f9,// 453 PAY 410 

    0xe4f2e60c,// 454 PAY 411 

    0x3e278796,// 455 PAY 412 

    0xe7fae5d0,// 456 PAY 413 

    0xed97913e,// 457 PAY 414 

    0xe731d9cc,// 458 PAY 415 

    0xd4018388,// 459 PAY 416 

    0xc9f2bfd7,// 460 PAY 417 

    0x4f57b51e,// 461 PAY 418 

    0x129121ff,// 462 PAY 419 

    0xbc19fe1e,// 463 PAY 420 

    0xe0574b7c,// 464 PAY 421 

    0x0c324723,// 465 PAY 422 

    0x996dcd7d,// 466 PAY 423 

    0xcfb79292,// 467 PAY 424 

    0x1f0f59ab,// 468 PAY 425 

    0x18f4af23,// 469 PAY 426 

    0xa8dc4db3,// 470 PAY 427 

    0x3a1fdd22,// 471 PAY 428 

    0xb024c81b,// 472 PAY 429 

    0x750a171e,// 473 PAY 430 

    0x10fe5789,// 474 PAY 431 

    0xad824b91,// 475 PAY 432 

    0x61191ecc,// 476 PAY 433 

    0x4537f07a,// 477 PAY 434 

    0x36d2698d,// 478 PAY 435 

    0xfe55d967,// 479 PAY 436 

    0x9241ec95,// 480 PAY 437 

    0x771c2557,// 481 PAY 438 

    0xf629d164,// 482 PAY 439 

    0x3b475265,// 483 PAY 440 

    0x2769f0df,// 484 PAY 441 

    0xf5c98551,// 485 PAY 442 

    0x73c9f553,// 486 PAY 443 

    0x43dee9e4,// 487 PAY 444 

    0xf042e1e7,// 488 PAY 445 

    0xe95fc30d,// 489 PAY 446 

    0x7ddc6470,// 490 PAY 447 

    0xd3255d75,// 491 PAY 448 

    0x348f669c,// 492 PAY 449 

    0x96ac7849,// 493 PAY 450 

    0xe45026a5,// 494 PAY 451 

/// STA is 1 words. 

/// STA num_pkts       : 215 

/// STA pkt_idx        : 91 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xc4 

    0x016cc4d7 // 495 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 80 (0x50) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt56_tmpl[] = {
    0xb8010050,// 1 CCH   1 

/// ECH cache_idx      : 0x0b 

/// ECH pdu_tag        : 0x00 

    0x000b0000,// 2 ECH   1 

/// SCX is 19 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000013,// 3 SCX   1 

    0x80814840,// 4 SCX   2 

    0x00005500,// 5 SCX   3 

    0x5a85be8e,// 6 SCX   4 

    0x45292c97,// 7 SCX   5 

    0x1e8d56a0,// 8 SCX   6 

    0xc58b6cab,// 9 SCX   7 

    0x56ed1601,// 10 SCX   8 

    0x96021348,// 11 SCX   9 

    0xf5e2e378,// 12 SCX  10 

    0x104a5deb,// 13 SCX  11 

    0x82896ffe,// 14 SCX  12 

    0x895283e3,// 15 SCX  13 

    0xe60bc5cf,// 16 SCX  14 

    0xfe9b046a,// 17 SCX  15 

    0xf157bd37,// 18 SCX  16 

    0x184890c8,// 19 SCX  17 

    0xbed8b4ce,// 20 SCX  18 

    0x30e5c101,// 21 SCX  19 

/// BFD is 3 words. 

/// BFD tot_len        : 1974 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 1721 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1721 

/// BFD lencrypto      : 832 

/// BFD ofstcrypto     : 708 

/// BFD (ofst+len)cry  : 1540 

/// BFD ofstiv         : 672 

/// BFD ofsticv        : 1780 

    0x000006b9,// 22 BFD   1 

    0x02c40340,// 23 BFD   2 

    0x06f402a0,// 24 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c005a75,// 25 MFM   1 

    0x8d333bc3,// 26 MFM   2 

    0xec410063,// 27 MFM   3 

    0x717ab31a,// 28 MFM   4 

    0xeef1f9c0,// 29 MFM   5 

    0xdd9d33f8,// 30 MFM   6 

    0x1b049f2c,// 31 MFM   7 

    0x0e19f01a,// 32 MFM   8 

    0x28107b22,// 33 MFM   9 

    0x7181c1a0,// 34 MFM  10 

    0x028818a7,// 35 MFM  11 

    0xdd537d70,// 36 MFM  12 

    0x4f67b549,// 37 MFM  13 

    0xc81a32ac,// 38 MFM  14 

    0x037ce8a0,// 39 MFM  15 

    0x20a4776d,// 40 MFM  16 

/// BDA is 495 words. 

/// BDA size     is 1974 (0x7b6) 

/// BDA id       is 0x1b7b 

    0x07b61b7b,// 41 BDA   1 

/// PAY Generic Data size   : 1974 byte(s) 

/// PAD Buffer Data Pad size   : 2 byte(s) 

    0x5bd72f2e,// 42 PAY   1 

    0x67a442a8,// 43 PAY   2 

    0xe45bcb45,// 44 PAY   3 

    0xc358803f,// 45 PAY   4 

    0xbecd2918,// 46 PAY   5 

    0x4ec008a7,// 47 PAY   6 

    0xc3a61394,// 48 PAY   7 

    0xc07027d6,// 49 PAY   8 

    0x5ff9baec,// 50 PAY   9 

    0x5444b7b8,// 51 PAY  10 

    0xc44b144d,// 52 PAY  11 

    0xeeeec9ab,// 53 PAY  12 

    0xad1addc8,// 54 PAY  13 

    0x0c08558e,// 55 PAY  14 

    0x482a4c95,// 56 PAY  15 

    0xb9d49955,// 57 PAY  16 

    0xfee2211b,// 58 PAY  17 

    0x96f7e716,// 59 PAY  18 

    0xa30c406d,// 60 PAY  19 

    0xd45c71fe,// 61 PAY  20 

    0xcadb8f09,// 62 PAY  21 

    0x6a6aecf3,// 63 PAY  22 

    0x7519bede,// 64 PAY  23 

    0x35db1f2d,// 65 PAY  24 

    0xb32bea1c,// 66 PAY  25 

    0xe155336d,// 67 PAY  26 

    0x50f188fe,// 68 PAY  27 

    0xeb5089d1,// 69 PAY  28 

    0xc1f63d6c,// 70 PAY  29 

    0x351a98a9,// 71 PAY  30 

    0x99d31461,// 72 PAY  31 

    0xc6bb7582,// 73 PAY  32 

    0xcedaea63,// 74 PAY  33 

    0xcdb7ad95,// 75 PAY  34 

    0xf36341aa,// 76 PAY  35 

    0xf41ec9bf,// 77 PAY  36 

    0xd8dfc88b,// 78 PAY  37 

    0xc6e8cee7,// 79 PAY  38 

    0xdfba769d,// 80 PAY  39 

    0x6cbdea5c,// 81 PAY  40 

    0x5b5b72fe,// 82 PAY  41 

    0xc43f518a,// 83 PAY  42 

    0x8858da43,// 84 PAY  43 

    0x31cafc03,// 85 PAY  44 

    0xae64daa7,// 86 PAY  45 

    0xa5e9d1d9,// 87 PAY  46 

    0xba699f4f,// 88 PAY  47 

    0x305df8f6,// 89 PAY  48 

    0x927f1e99,// 90 PAY  49 

    0xf2a38eca,// 91 PAY  50 

    0x576bfaaa,// 92 PAY  51 

    0x1d81ca55,// 93 PAY  52 

    0x0323fdfb,// 94 PAY  53 

    0x31f0eb54,// 95 PAY  54 

    0x41f760ae,// 96 PAY  55 

    0x6fa731b2,// 97 PAY  56 

    0x8529bb1e,// 98 PAY  57 

    0x47160023,// 99 PAY  58 

    0x828f48de,// 100 PAY  59 

    0x3058d39c,// 101 PAY  60 

    0x0a19c99e,// 102 PAY  61 

    0x1545bfcc,// 103 PAY  62 

    0xc9cbb73d,// 104 PAY  63 

    0xf53eeaae,// 105 PAY  64 

    0x28dde8cc,// 106 PAY  65 

    0xf430e1f2,// 107 PAY  66 

    0xc6db1d86,// 108 PAY  67 

    0x024426b9,// 109 PAY  68 

    0x050fb297,// 110 PAY  69 

    0x555942df,// 111 PAY  70 

    0x5e3840ec,// 112 PAY  71 

    0x9183336e,// 113 PAY  72 

    0x14ef95b0,// 114 PAY  73 

    0x8b1b50da,// 115 PAY  74 

    0x2ca7f920,// 116 PAY  75 

    0x5e13fbab,// 117 PAY  76 

    0x703ddc6e,// 118 PAY  77 

    0x861fb14e,// 119 PAY  78 

    0x4bd0626c,// 120 PAY  79 

    0x7b9e2dda,// 121 PAY  80 

    0xe152bbce,// 122 PAY  81 

    0xc0d26413,// 123 PAY  82 

    0xc8877f47,// 124 PAY  83 

    0x11a1c308,// 125 PAY  84 

    0x35f6b4bc,// 126 PAY  85 

    0x3c1dd95e,// 127 PAY  86 

    0x00a281eb,// 128 PAY  87 

    0xf86d069e,// 129 PAY  88 

    0x15c0217c,// 130 PAY  89 

    0x42f34c5b,// 131 PAY  90 

    0xfe480bef,// 132 PAY  91 

    0xba4b3af3,// 133 PAY  92 

    0xe4735943,// 134 PAY  93 

    0x08e29004,// 135 PAY  94 

    0x73b3e91b,// 136 PAY  95 

    0x5bea4234,// 137 PAY  96 

    0x7c52b4c4,// 138 PAY  97 

    0x5835966a,// 139 PAY  98 

    0xbc2c5c08,// 140 PAY  99 

    0xf1054306,// 141 PAY 100 

    0xf154e9df,// 142 PAY 101 

    0x75c36da1,// 143 PAY 102 

    0xd4d98458,// 144 PAY 103 

    0xb25f32f9,// 145 PAY 104 

    0xcd300a82,// 146 PAY 105 

    0xe58222e7,// 147 PAY 106 

    0xc8f8fd38,// 148 PAY 107 

    0x8eef51f3,// 149 PAY 108 

    0x9408dec8,// 150 PAY 109 

    0x021c9a29,// 151 PAY 110 

    0x9e96115b,// 152 PAY 111 

    0x430e1fe2,// 153 PAY 112 

    0x0ad1dfbd,// 154 PAY 113 

    0xb0bd6eb4,// 155 PAY 114 

    0x4224dc8c,// 156 PAY 115 

    0xcfbd9185,// 157 PAY 116 

    0xca277e7c,// 158 PAY 117 

    0x5ba8c125,// 159 PAY 118 

    0xf71be716,// 160 PAY 119 

    0xd0c6df63,// 161 PAY 120 

    0x88e25534,// 162 PAY 121 

    0x2274d5b9,// 163 PAY 122 

    0x2cd5300e,// 164 PAY 123 

    0xc9b1a256,// 165 PAY 124 

    0x117150bc,// 166 PAY 125 

    0x0f6043b6,// 167 PAY 126 

    0x1af6e51b,// 168 PAY 127 

    0x312e7798,// 169 PAY 128 

    0xc0fae3c4,// 170 PAY 129 

    0x72f07f65,// 171 PAY 130 

    0x7277c874,// 172 PAY 131 

    0x7411d034,// 173 PAY 132 

    0xa01d056c,// 174 PAY 133 

    0xfa7b03f1,// 175 PAY 134 

    0x976b4f79,// 176 PAY 135 

    0x74c3bef1,// 177 PAY 136 

    0x476f65b8,// 178 PAY 137 

    0x22672bba,// 179 PAY 138 

    0x30d41b6c,// 180 PAY 139 

    0x0f5e67df,// 181 PAY 140 

    0x59a85e4c,// 182 PAY 141 

    0x3bcf1e8c,// 183 PAY 142 

    0x8cd5963f,// 184 PAY 143 

    0x22c84250,// 185 PAY 144 

    0x665def0a,// 186 PAY 145 

    0x1f3255c4,// 187 PAY 146 

    0x8ca46ce3,// 188 PAY 147 

    0x178f7830,// 189 PAY 148 

    0xbd9d28f1,// 190 PAY 149 

    0xe6eb7f7f,// 191 PAY 150 

    0x6c1d30df,// 192 PAY 151 

    0xcd766f75,// 193 PAY 152 

    0xbdb6aed1,// 194 PAY 153 

    0x56f4e868,// 195 PAY 154 

    0x71e837ee,// 196 PAY 155 

    0xa4d7a01b,// 197 PAY 156 

    0xb9aea520,// 198 PAY 157 

    0x0f7cbf1d,// 199 PAY 158 

    0xf823ed02,// 200 PAY 159 

    0xfb316ec9,// 201 PAY 160 

    0xe657dbe1,// 202 PAY 161 

    0x14ef46b0,// 203 PAY 162 

    0x726ebb79,// 204 PAY 163 

    0x6481234c,// 205 PAY 164 

    0x81fb295e,// 206 PAY 165 

    0xb60d212f,// 207 PAY 166 

    0x70f5066e,// 208 PAY 167 

    0x35dd8a09,// 209 PAY 168 

    0x355a1659,// 210 PAY 169 

    0x203ce37a,// 211 PAY 170 

    0x15836020,// 212 PAY 171 

    0xdbc81fd3,// 213 PAY 172 

    0x70c6b5fc,// 214 PAY 173 

    0xa16e15a8,// 215 PAY 174 

    0x53e39f71,// 216 PAY 175 

    0x001e4a41,// 217 PAY 176 

    0x55fa11d5,// 218 PAY 177 

    0xbe8df2cc,// 219 PAY 178 

    0xab6df26b,// 220 PAY 179 

    0x006fcd65,// 221 PAY 180 

    0xea56f2f0,// 222 PAY 181 

    0xaff43940,// 223 PAY 182 

    0xecb39650,// 224 PAY 183 

    0xaec1da63,// 225 PAY 184 

    0x9d002533,// 226 PAY 185 

    0x78fa4295,// 227 PAY 186 

    0xee2f99a7,// 228 PAY 187 

    0xeec38978,// 229 PAY 188 

    0x9570dcc7,// 230 PAY 189 

    0x37b72f06,// 231 PAY 190 

    0xe1a46eb3,// 232 PAY 191 

    0xd2276125,// 233 PAY 192 

    0x8cce6b7f,// 234 PAY 193 

    0x8aea3a79,// 235 PAY 194 

    0xff1a0735,// 236 PAY 195 

    0xc8f4f9bb,// 237 PAY 196 

    0x4dcda832,// 238 PAY 197 

    0xf38880e1,// 239 PAY 198 

    0x3effd1d1,// 240 PAY 199 

    0x417d0088,// 241 PAY 200 

    0x0a5bb1bc,// 242 PAY 201 

    0x741dfd96,// 243 PAY 202 

    0x1f0be622,// 244 PAY 203 

    0x2de1cc12,// 245 PAY 204 

    0x3cb2151f,// 246 PAY 205 

    0x0a03be97,// 247 PAY 206 

    0x92e2ebc6,// 248 PAY 207 

    0x02299eae,// 249 PAY 208 

    0xa21accfa,// 250 PAY 209 

    0x23cf9f56,// 251 PAY 210 

    0x45ea92c2,// 252 PAY 211 

    0x78f76eaa,// 253 PAY 212 

    0xc5cfe775,// 254 PAY 213 

    0xc9f9d559,// 255 PAY 214 

    0x3637b03e,// 256 PAY 215 

    0xe0a74758,// 257 PAY 216 

    0xdf7511f9,// 258 PAY 217 

    0x909c294c,// 259 PAY 218 

    0x3dc36de3,// 260 PAY 219 

    0xe1642ea5,// 261 PAY 220 

    0xe0c912b7,// 262 PAY 221 

    0x416d58fd,// 263 PAY 222 

    0x54678eec,// 264 PAY 223 

    0xd3897001,// 265 PAY 224 

    0xfed2cf29,// 266 PAY 225 

    0x8f58d709,// 267 PAY 226 

    0x5c8302f5,// 268 PAY 227 

    0x89d71709,// 269 PAY 228 

    0xef0dd784,// 270 PAY 229 

    0x7ca286e9,// 271 PAY 230 

    0x3701d548,// 272 PAY 231 

    0x08a8fbb1,// 273 PAY 232 

    0x4724407f,// 274 PAY 233 

    0x6a28ac1a,// 275 PAY 234 

    0x856b8c60,// 276 PAY 235 

    0x8b4a6336,// 277 PAY 236 

    0xc4551c8d,// 278 PAY 237 

    0x1ee89555,// 279 PAY 238 

    0xd65d8d90,// 280 PAY 239 

    0x21521437,// 281 PAY 240 

    0x9be3a67d,// 282 PAY 241 

    0xa8d7b412,// 283 PAY 242 

    0x718a907e,// 284 PAY 243 

    0x0c6dbfa2,// 285 PAY 244 

    0x2ef7a626,// 286 PAY 245 

    0xf66e8099,// 287 PAY 246 

    0x3bedca36,// 288 PAY 247 

    0xfb287037,// 289 PAY 248 

    0x6504486d,// 290 PAY 249 

    0xab26264d,// 291 PAY 250 

    0x3d155da3,// 292 PAY 251 

    0x3075ce61,// 293 PAY 252 

    0x30bb6a01,// 294 PAY 253 

    0x255fe926,// 295 PAY 254 

    0x4fa82895,// 296 PAY 255 

    0xd9a5bf88,// 297 PAY 256 

    0xf6d71f89,// 298 PAY 257 

    0x383674d5,// 299 PAY 258 

    0x20a863c2,// 300 PAY 259 

    0xe1dc21e9,// 301 PAY 260 

    0xafae946e,// 302 PAY 261 

    0x4f35d0bf,// 303 PAY 262 

    0x41eac00c,// 304 PAY 263 

    0xeaa0ec45,// 305 PAY 264 

    0x6079620f,// 306 PAY 265 

    0xbeed7e89,// 307 PAY 266 

    0x9c92a460,// 308 PAY 267 

    0x6e2c5e4b,// 309 PAY 268 

    0x658f3ca9,// 310 PAY 269 

    0xc3a1125d,// 311 PAY 270 

    0x3db13d73,// 312 PAY 271 

    0x4b538379,// 313 PAY 272 

    0x61a135c4,// 314 PAY 273 

    0xb29d6299,// 315 PAY 274 

    0x4c1305e8,// 316 PAY 275 

    0xde941fb5,// 317 PAY 276 

    0x6d1715ff,// 318 PAY 277 

    0x416cb72f,// 319 PAY 278 

    0xd9cced1a,// 320 PAY 279 

    0x968155af,// 321 PAY 280 

    0x08a78fa9,// 322 PAY 281 

    0x538fbb24,// 323 PAY 282 

    0x81bfbb50,// 324 PAY 283 

    0x7faf9c60,// 325 PAY 284 

    0x0d0df736,// 326 PAY 285 

    0x42eb63d7,// 327 PAY 286 

    0xf25d5aca,// 328 PAY 287 

    0x201555d8,// 329 PAY 288 

    0x4dba81d3,// 330 PAY 289 

    0x30131a2b,// 331 PAY 290 

    0x5a19b9af,// 332 PAY 291 

    0x275c7d1e,// 333 PAY 292 

    0x117a158e,// 334 PAY 293 

    0x0afe81fc,// 335 PAY 294 

    0x827e69bd,// 336 PAY 295 

    0x64050b53,// 337 PAY 296 

    0xe149ed95,// 338 PAY 297 

    0x7db8ddac,// 339 PAY 298 

    0xe24af6dd,// 340 PAY 299 

    0xa137b129,// 341 PAY 300 

    0xa30ec74e,// 342 PAY 301 

    0x14c2d35e,// 343 PAY 302 

    0x5d073305,// 344 PAY 303 

    0x0537d217,// 345 PAY 304 

    0x3d0a307f,// 346 PAY 305 

    0x92629fbc,// 347 PAY 306 

    0x3c05ee00,// 348 PAY 307 

    0x806e392c,// 349 PAY 308 

    0x348823de,// 350 PAY 309 

    0x81bac5db,// 351 PAY 310 

    0x722f2865,// 352 PAY 311 

    0x0525917b,// 353 PAY 312 

    0x0d3e41cd,// 354 PAY 313 

    0xda7e00d4,// 355 PAY 314 

    0x28d997bf,// 356 PAY 315 

    0x976dffb2,// 357 PAY 316 

    0x606080e6,// 358 PAY 317 

    0x895b4375,// 359 PAY 318 

    0xb8425775,// 360 PAY 319 

    0x98ff9c31,// 361 PAY 320 

    0x11874653,// 362 PAY 321 

    0xad17e768,// 363 PAY 322 

    0xc50cf65d,// 364 PAY 323 

    0x4d09f9dd,// 365 PAY 324 

    0xb67cc2e6,// 366 PAY 325 

    0x3ecf39c6,// 367 PAY 326 

    0x28b6f32b,// 368 PAY 327 

    0x34da2f8b,// 369 PAY 328 

    0x70808e7b,// 370 PAY 329 

    0x2d414bd8,// 371 PAY 330 

    0x81a7af30,// 372 PAY 331 

    0xa3101132,// 373 PAY 332 

    0x62ea6dd8,// 374 PAY 333 

    0xd39052d3,// 375 PAY 334 

    0x780453df,// 376 PAY 335 

    0x7b1ee9ac,// 377 PAY 336 

    0x0502b4a8,// 378 PAY 337 

    0x7aecbbca,// 379 PAY 338 

    0x71189a0f,// 380 PAY 339 

    0x5201a868,// 381 PAY 340 

    0xfa5a4aa2,// 382 PAY 341 

    0xa0797380,// 383 PAY 342 

    0xbf8ec631,// 384 PAY 343 

    0x900ccf3c,// 385 PAY 344 

    0x6d8f8461,// 386 PAY 345 

    0x70f1ace7,// 387 PAY 346 

    0xf381ef7f,// 388 PAY 347 

    0x520ab71b,// 389 PAY 348 

    0xe0891381,// 390 PAY 349 

    0x4ab660df,// 391 PAY 350 

    0xbddb5280,// 392 PAY 351 

    0x8c91f8bb,// 393 PAY 352 

    0x4c3754f6,// 394 PAY 353 

    0x4726a16a,// 395 PAY 354 

    0x5231c452,// 396 PAY 355 

    0x4d2603dd,// 397 PAY 356 

    0x505791dd,// 398 PAY 357 

    0x90436a4b,// 399 PAY 358 

    0x74863c6e,// 400 PAY 359 

    0x2364acd0,// 401 PAY 360 

    0x705de7a8,// 402 PAY 361 

    0xb39afb3f,// 403 PAY 362 

    0x3f24c2a8,// 404 PAY 363 

    0x21d199eb,// 405 PAY 364 

    0xafce35bc,// 406 PAY 365 

    0x27ce779d,// 407 PAY 366 

    0xeff17980,// 408 PAY 367 

    0x82e72d4a,// 409 PAY 368 

    0x77e1640c,// 410 PAY 369 

    0x15c6d6c8,// 411 PAY 370 

    0x4b8ddb87,// 412 PAY 371 

    0xe792ae60,// 413 PAY 372 

    0x3629238e,// 414 PAY 373 

    0x1bf77e04,// 415 PAY 374 

    0xcb2f310b,// 416 PAY 375 

    0x9c8a8d9a,// 417 PAY 376 

    0xc7ebc5ae,// 418 PAY 377 

    0xd01b19bd,// 419 PAY 378 

    0x32a9983e,// 420 PAY 379 

    0x0c871b66,// 421 PAY 380 

    0x1fec3bea,// 422 PAY 381 

    0xa82e2cb4,// 423 PAY 382 

    0x90c8f515,// 424 PAY 383 

    0x3f6db95f,// 425 PAY 384 

    0xbfa368d7,// 426 PAY 385 

    0xcefecb00,// 427 PAY 386 

    0x87b4e82d,// 428 PAY 387 

    0x1b005428,// 429 PAY 388 

    0x1ce73297,// 430 PAY 389 

    0x8efa7380,// 431 PAY 390 

    0x49748b50,// 432 PAY 391 

    0xfe78c01a,// 433 PAY 392 

    0xde222d0d,// 434 PAY 393 

    0x4dc44357,// 435 PAY 394 

    0xd7b80684,// 436 PAY 395 

    0x0cb1820f,// 437 PAY 396 

    0xd654cfdc,// 438 PAY 397 

    0x3d6fe4e1,// 439 PAY 398 

    0x3e313311,// 440 PAY 399 

    0xba56a4f8,// 441 PAY 400 

    0x972cd991,// 442 PAY 401 

    0x032d46dc,// 443 PAY 402 

    0x2611ac83,// 444 PAY 403 

    0x6d6d8dbf,// 445 PAY 404 

    0x3a9bfbc6,// 446 PAY 405 

    0x4862dc81,// 447 PAY 406 

    0x8f0bc642,// 448 PAY 407 

    0x998c94e5,// 449 PAY 408 

    0xe0c9e9b5,// 450 PAY 409 

    0x48eaf55c,// 451 PAY 410 

    0xc878b645,// 452 PAY 411 

    0x621bac64,// 453 PAY 412 

    0x70d85b30,// 454 PAY 413 

    0xf1e19aa5,// 455 PAY 414 

    0x8aacf431,// 456 PAY 415 

    0xc3f236f9,// 457 PAY 416 

    0xa1cee21e,// 458 PAY 417 

    0x9aeb0b4a,// 459 PAY 418 

    0x77e8109a,// 460 PAY 419 

    0x21e8bd52,// 461 PAY 420 

    0x6d4269cb,// 462 PAY 421 

    0xc5b4d05c,// 463 PAY 422 

    0x11989aa3,// 464 PAY 423 

    0x231aa71a,// 465 PAY 424 

    0xaa991ddc,// 466 PAY 425 

    0x5d858126,// 467 PAY 426 

    0x0f5e3184,// 468 PAY 427 

    0x0794e9aa,// 469 PAY 428 

    0xb2b13309,// 470 PAY 429 

    0xa363017d,// 471 PAY 430 

    0x130ccf41,// 472 PAY 431 

    0x632e0a70,// 473 PAY 432 

    0xbcbc45f2,// 474 PAY 433 

    0xb58fd149,// 475 PAY 434 

    0x5e01a9bc,// 476 PAY 435 

    0x940206de,// 477 PAY 436 

    0xdedd9f6d,// 478 PAY 437 

    0x9ec50555,// 479 PAY 438 

    0x06d3c20a,// 480 PAY 439 

    0x8469d27c,// 481 PAY 440 

    0xc7226afa,// 482 PAY 441 

    0x1149057b,// 483 PAY 442 

    0xd8d209f6,// 484 PAY 443 

    0xb4b46a2d,// 485 PAY 444 

    0xd9276abe,// 486 PAY 445 

    0xc49aa332,// 487 PAY 446 

    0x67990080,// 488 PAY 447 

    0xcef122f1,// 489 PAY 448 

    0x3cc15c7d,// 490 PAY 449 

    0x2b8af73c,// 491 PAY 450 

    0xc4f23457,// 492 PAY 451 

    0x199cdc6b,// 493 PAY 452 

    0xfebbab39,// 494 PAY 453 

    0x186042be,// 495 PAY 454 

    0x2166dc88,// 496 PAY 455 

    0xcec33723,// 497 PAY 456 

    0xa952dc42,// 498 PAY 457 

    0x9070acf3,// 499 PAY 458 

    0x6abc3d27,// 500 PAY 459 

    0xaa1ed7df,// 501 PAY 460 

    0x429d2869,// 502 PAY 461 

    0xff64792b,// 503 PAY 462 

    0xfe2dd280,// 504 PAY 463 

    0x808942ae,// 505 PAY 464 

    0xcc3b6660,// 506 PAY 465 

    0xb86ad204,// 507 PAY 466 

    0x261904ed,// 508 PAY 467 

    0x9ab102b9,// 509 PAY 468 

    0xdb1955c2,// 510 PAY 469 

    0xda281ccf,// 511 PAY 470 

    0xa485234c,// 512 PAY 471 

    0xa3ea2c8d,// 513 PAY 472 

    0xddba337c,// 514 PAY 473 

    0x40cc3b25,// 515 PAY 474 

    0xe59d8367,// 516 PAY 475 

    0x710dfe74,// 517 PAY 476 

    0x8e3a46f1,// 518 PAY 477 

    0xc798ed65,// 519 PAY 478 

    0x79e48fe0,// 520 PAY 479 

    0xe8010eef,// 521 PAY 480 

    0x1c2b3fc1,// 522 PAY 481 

    0x2a3945f9,// 523 PAY 482 

    0xee356bb6,// 524 PAY 483 

    0x4051512f,// 525 PAY 484 

    0x12265ef7,// 526 PAY 485 

    0xae595a9c,// 527 PAY 486 

    0xe11b9264,// 528 PAY 487 

    0x094dd352,// 529 PAY 488 

    0x301c1886,// 530 PAY 489 

    0x71144eee,// 531 PAY 490 

    0x764333de,// 532 PAY 491 

    0xc8f7bb7d,// 533 PAY 492 

    0xe289ec2a,// 534 PAY 493 

    0xcd490000,// 535 PAY 494 

/// STA is 1 words. 

/// STA num_pkts       : 160 

/// STA pkt_idx        : 180 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xf7 

    0x02d1f7a0 // 536 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 72 (0x48) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt57_tmpl[] = {
    0xb8010048,// 1 CCH   1 

/// ECH cache_idx      : 0x08 

/// ECH pdu_tag        : 0x00 

    0x00080000,// 2 ECH   1 

/// SCX is 17 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000011,// 3 SCX   1 

    0x80804821,// 4 SCX   2 

    0x00002400,// 5 SCX   3 

    0x12ac968c,// 6 SCX   4 

    0x39d405fd,// 7 SCX   5 

    0x79cd73d9,// 8 SCX   6 

    0xf557a38f,// 9 SCX   7 

    0xea6f08a9,// 10 SCX   8 

    0x68c189b3,// 11 SCX   9 

    0x44ee080c,// 12 SCX  10 

    0x1be25322,// 13 SCX  11 

    0x0fb0a62a,// 14 SCX  12 

    0x14e5b5fb,// 15 SCX  13 

    0x52806a86,// 16 SCX  14 

    0x76fb135f,// 17 SCX  15 

    0xad4d777a,// 18 SCX  16 

    0x1c33ef9e,// 19 SCX  17 

/// BFD is 3 words. 

/// BFD tot_len        : 117 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 63 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 63 

/// BFD lencrypto      : 32 

/// BFD ofstcrypto     : 16 

/// BFD (ofst+len)cry  : 48 

/// BFD ofstiv         : 0 

/// BFD ofsticv        : 72 

    0x0000003f,// 20 BFD   1 

    0x00100020,// 21 BFD   2 

    0x00480000,// 22 BFD   3 

/// MFM is 3 words. 

/// MFM vldnibs        : f 

    0x0f00d537,// 23 MFM   1 

    0x7a3f06b8,// 24 MFM   2 

    0xd6800000,// 25 MFM   3 

/// BDA is 31 words. 

/// BDA size     is 117 (0x75) 

/// BDA id       is 0xf427 

    0x0075f427,// 26 BDA   1 

/// PAY Generic Data size   : 117 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x8934aa3b,// 27 PAY   1 

    0xd1d61ebf,// 28 PAY   2 

    0xaf8cbe80,// 29 PAY   3 

    0x96ab63e8,// 30 PAY   4 

    0xbab742f5,// 31 PAY   5 

    0xec12bdd9,// 32 PAY   6 

    0x8963d23d,// 33 PAY   7 

    0x5bf3fada,// 34 PAY   8 

    0x9690b0cd,// 35 PAY   9 

    0xa577f00b,// 36 PAY  10 

    0x11808bc1,// 37 PAY  11 

    0xd869cda2,// 38 PAY  12 

    0x24bc6799,// 39 PAY  13 

    0xe762317a,// 40 PAY  14 

    0x4c3bb256,// 41 PAY  15 

    0xd29830bd,// 42 PAY  16 

    0x039ef5f8,// 43 PAY  17 

    0x1bb3ddf4,// 44 PAY  18 

    0xc8f9b61b,// 45 PAY  19 

    0x36a53fae,// 46 PAY  20 

    0xfa4e08a9,// 47 PAY  21 

    0x0c2b182c,// 48 PAY  22 

    0x5ad290b0,// 49 PAY  23 

    0xf22989bd,// 50 PAY  24 

    0xd0efa55c,// 51 PAY  25 

    0x077cac75,// 52 PAY  26 

    0x2890f826,// 53 PAY  27 

    0x6fd888cf,// 54 PAY  28 

    0xb2981635,// 55 PAY  29 

    0x63000000,// 56 PAY  30 

/// STA is 1 words. 

/// STA num_pkts       : 231 

/// STA pkt_idx        : 247 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x9 

    0x03dc09e7 // 57 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt58_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x0e 

/// ECH pdu_tag        : 0x00 

    0x000e0000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x2 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x8082482e,// 4 SCX   2 

    0x00003200,// 5 SCX   3 

    0x07276564,// 6 SCX   4 

    0x1cca43b9,// 7 SCX   5 

    0x9d771548,// 8 SCX   6 

    0x624915df,// 9 SCX   7 

    0x92daf3cb,// 10 SCX   8 

    0xf247849c,// 11 SCX   9 

    0x2a10472d,// 12 SCX  10 

    0x61c73f49,// 13 SCX  11 

    0xf3bb1358,// 14 SCX  12 

    0x3ac0bf69,// 15 SCX  13 

    0x71384438,// 16 SCX  14 

    0x5137f938,// 17 SCX  15 

    0xbfb7e273,// 18 SCX  16 

    0x22134e6b,// 19 SCX  17 

    0xc2f97996,// 20 SCX  18 

    0xf29ecad2,// 21 SCX  19 

    0x92107c04,// 22 SCX  20 

    0x29ed27b7,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1179 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 1000 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1000 

/// BFD lencrypto      : 320 

/// BFD ofstcrypto     : 600 

/// BFD (ofst+len)cry  : 920 

/// BFD ofstiv         : 352 

/// BFD ofsticv        : 1092 

    0x000003e8,// 24 BFD   1 

    0x02580140,// 25 BFD   2 

    0x04440160,// 26 BFD   3 

/// MFM is 12 words. 

/// MFM vldnibs        : 5c 

    0x5c00fc53,// 27 MFM   1 

    0x99e7d84f,// 28 MFM   2 

    0xcd002f5d,// 29 MFM   3 

    0xfb99be16,// 30 MFM   4 

    0x02c3d09c,// 31 MFM   5 

    0x13b8fae9,// 32 MFM   6 

    0xd283d053,// 33 MFM   7 

    0x08db37af,// 34 MFM   8 

    0x6fc3941d,// 35 MFM   9 

    0x9828be73,// 36 MFM  10 

    0xa73e7f2f,// 37 MFM  11 

    0x528657b9,// 38 MFM  12 

/// BDA is 296 words. 

/// BDA size     is 1179 (0x49b) 

/// BDA id       is 0x5042 

    0x049b5042,// 39 BDA   1 

/// PAY Generic Data size   : 1179 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0x2e16bc41,// 40 PAY   1 

    0xfbe99a09,// 41 PAY   2 

    0x2e91c8ad,// 42 PAY   3 

    0xcfd079d7,// 43 PAY   4 

    0x77e29276,// 44 PAY   5 

    0x7d336873,// 45 PAY   6 

    0x34602e75,// 46 PAY   7 

    0x8770d505,// 47 PAY   8 

    0x9bb96f8d,// 48 PAY   9 

    0x37bf307f,// 49 PAY  10 

    0xe42d1f41,// 50 PAY  11 

    0xba821e17,// 51 PAY  12 

    0xbd245575,// 52 PAY  13 

    0xa6c10db5,// 53 PAY  14 

    0x2de6e446,// 54 PAY  15 

    0xb5a02b80,// 55 PAY  16 

    0x70018e44,// 56 PAY  17 

    0x93a8194c,// 57 PAY  18 

    0x60fc5ed5,// 58 PAY  19 

    0xcea40a16,// 59 PAY  20 

    0x0f1e1d3c,// 60 PAY  21 

    0xae1ef164,// 61 PAY  22 

    0x63c7d7d1,// 62 PAY  23 

    0x3edd9313,// 63 PAY  24 

    0xe379355c,// 64 PAY  25 

    0xe742d5a4,// 65 PAY  26 

    0x645a792f,// 66 PAY  27 

    0xedc972df,// 67 PAY  28 

    0xcbe27842,// 68 PAY  29 

    0x2193a206,// 69 PAY  30 

    0xb1a270f7,// 70 PAY  31 

    0xc5413a7d,// 71 PAY  32 

    0x0784fd6c,// 72 PAY  33 

    0x39d336fb,// 73 PAY  34 

    0xc74a0f41,// 74 PAY  35 

    0x8b6594fe,// 75 PAY  36 

    0x66dcd55b,// 76 PAY  37 

    0xb989f1fc,// 77 PAY  38 

    0xe988e86c,// 78 PAY  39 

    0xe2ae6108,// 79 PAY  40 

    0xba85c8b1,// 80 PAY  41 

    0x3518d7db,// 81 PAY  42 

    0xe979a42e,// 82 PAY  43 

    0xc3ff24b5,// 83 PAY  44 

    0x35fdd523,// 84 PAY  45 

    0x6eab508c,// 85 PAY  46 

    0x1e9f3e99,// 86 PAY  47 

    0x3f8eab1e,// 87 PAY  48 

    0x32c3e8f3,// 88 PAY  49 

    0x7b5cd77e,// 89 PAY  50 

    0xd1878c7f,// 90 PAY  51 

    0x582d03e0,// 91 PAY  52 

    0x8389f62f,// 92 PAY  53 

    0xdbc07442,// 93 PAY  54 

    0x82079a64,// 94 PAY  55 

    0x9954c8e3,// 95 PAY  56 

    0x84a758c4,// 96 PAY  57 

    0x23564c9b,// 97 PAY  58 

    0x4715233a,// 98 PAY  59 

    0xbd30c208,// 99 PAY  60 

    0x0bd5a271,// 100 PAY  61 

    0xa2d6c257,// 101 PAY  62 

    0x9e07f740,// 102 PAY  63 

    0xcfaacf09,// 103 PAY  64 

    0x13b537dc,// 104 PAY  65 

    0x6cb86579,// 105 PAY  66 

    0x912af7dc,// 106 PAY  67 

    0xee671e50,// 107 PAY  68 

    0x516a8009,// 108 PAY  69 

    0x06c6cc23,// 109 PAY  70 

    0x819d4e59,// 110 PAY  71 

    0xf56ee244,// 111 PAY  72 

    0xad85a3d0,// 112 PAY  73 

    0xf89d49a2,// 113 PAY  74 

    0xc7b79690,// 114 PAY  75 

    0xf4d0c7e9,// 115 PAY  76 

    0xa513a7cb,// 116 PAY  77 

    0x0fef36e7,// 117 PAY  78 

    0xbbe7f192,// 118 PAY  79 

    0x5dd0142b,// 119 PAY  80 

    0xea7d8736,// 120 PAY  81 

    0x164c449f,// 121 PAY  82 

    0xef64360e,// 122 PAY  83 

    0x146ea541,// 123 PAY  84 

    0x3d5f8add,// 124 PAY  85 

    0xf925f206,// 125 PAY  86 

    0x74b9d0b0,// 126 PAY  87 

    0x36f26f72,// 127 PAY  88 

    0xceaebff5,// 128 PAY  89 

    0xf3dc85e3,// 129 PAY  90 

    0xeb941a7d,// 130 PAY  91 

    0x78d93de5,// 131 PAY  92 

    0xe4e6bcab,// 132 PAY  93 

    0x1160e408,// 133 PAY  94 

    0xb624948f,// 134 PAY  95 

    0xde6f2fe4,// 135 PAY  96 

    0xf09bccac,// 136 PAY  97 

    0x859d3277,// 137 PAY  98 

    0x11251992,// 138 PAY  99 

    0xb7278bf4,// 139 PAY 100 

    0x5e795bd0,// 140 PAY 101 

    0x8100ef6e,// 141 PAY 102 

    0xa3ceaccb,// 142 PAY 103 

    0xe0b8451a,// 143 PAY 104 

    0x88acedde,// 144 PAY 105 

    0xfe37c612,// 145 PAY 106 

    0x928b53a9,// 146 PAY 107 

    0x339f22ec,// 147 PAY 108 

    0x0ee37281,// 148 PAY 109 

    0xa1dd43e2,// 149 PAY 110 

    0xf2e43e7b,// 150 PAY 111 

    0xda2e75cc,// 151 PAY 112 

    0x6ae9371e,// 152 PAY 113 

    0x1dfa0f88,// 153 PAY 114 

    0xc747b41b,// 154 PAY 115 

    0x50cb46cb,// 155 PAY 116 

    0x93c1d803,// 156 PAY 117 

    0x4eaeab18,// 157 PAY 118 

    0x6cb0e54a,// 158 PAY 119 

    0xf2449d7b,// 159 PAY 120 

    0x32a37488,// 160 PAY 121 

    0xe1be2eed,// 161 PAY 122 

    0x55be92bf,// 162 PAY 123 

    0x6d26b208,// 163 PAY 124 

    0x2c73ad8d,// 164 PAY 125 

    0x914cc624,// 165 PAY 126 

    0x9964f42d,// 166 PAY 127 

    0x7cd441e5,// 167 PAY 128 

    0x78a82683,// 168 PAY 129 

    0xb170765e,// 169 PAY 130 

    0xa4cc694c,// 170 PAY 131 

    0x40322134,// 171 PAY 132 

    0xbc52fbce,// 172 PAY 133 

    0x2097bbcd,// 173 PAY 134 

    0x05829cd1,// 174 PAY 135 

    0xef8d3d69,// 175 PAY 136 

    0x38d6175b,// 176 PAY 137 

    0x9ef86122,// 177 PAY 138 

    0x4449e484,// 178 PAY 139 

    0x0563b74f,// 179 PAY 140 

    0xa847150c,// 180 PAY 141 

    0xf0cc4df0,// 181 PAY 142 

    0x62d9a1ae,// 182 PAY 143 

    0xd6c9577e,// 183 PAY 144 

    0x220c924f,// 184 PAY 145 

    0x6e4d1e2b,// 185 PAY 146 

    0x5234528f,// 186 PAY 147 

    0x5d4d4525,// 187 PAY 148 

    0x952377ae,// 188 PAY 149 

    0x0b877731,// 189 PAY 150 

    0xd17959a8,// 190 PAY 151 

    0xfd666ca9,// 191 PAY 152 

    0x3e95fe49,// 192 PAY 153 

    0xcbf8cb5e,// 193 PAY 154 

    0xb0c2d3f6,// 194 PAY 155 

    0xa2e322fc,// 195 PAY 156 

    0x204df250,// 196 PAY 157 

    0xfd05ef81,// 197 PAY 158 

    0xa422b028,// 198 PAY 159 

    0x6e1e9e6e,// 199 PAY 160 

    0x6bc21a1a,// 200 PAY 161 

    0xc55179e6,// 201 PAY 162 

    0x8bd3e95d,// 202 PAY 163 

    0x2bd2a43b,// 203 PAY 164 

    0x5bd8a0ba,// 204 PAY 165 

    0xa5013254,// 205 PAY 166 

    0xc4e38e6a,// 206 PAY 167 

    0x41fb52d7,// 207 PAY 168 

    0x2ecd9a8f,// 208 PAY 169 

    0x10a88028,// 209 PAY 170 

    0xaf0425ef,// 210 PAY 171 

    0x917bcce4,// 211 PAY 172 

    0x0eadd767,// 212 PAY 173 

    0xe5ac5c09,// 213 PAY 174 

    0x1a1742c0,// 214 PAY 175 

    0x1d7a6797,// 215 PAY 176 

    0xa12fef42,// 216 PAY 177 

    0xd5225006,// 217 PAY 178 

    0x513c9b7d,// 218 PAY 179 

    0xebd42c62,// 219 PAY 180 

    0x8268a95c,// 220 PAY 181 

    0xaf93a691,// 221 PAY 182 

    0x9e84cd1b,// 222 PAY 183 

    0xbc2171e4,// 223 PAY 184 

    0x7ae195d3,// 224 PAY 185 

    0x71c15050,// 225 PAY 186 

    0x75fa9f7d,// 226 PAY 187 

    0x418564b3,// 227 PAY 188 

    0x9e891d6f,// 228 PAY 189 

    0x94753170,// 229 PAY 190 

    0x34c0aa70,// 230 PAY 191 

    0x6338159c,// 231 PAY 192 

    0xf287cd22,// 232 PAY 193 

    0x68533e3c,// 233 PAY 194 

    0xcec3a58d,// 234 PAY 195 

    0xfff2be63,// 235 PAY 196 

    0x2b1aeef0,// 236 PAY 197 

    0xd47a81c4,// 237 PAY 198 

    0x0b847b21,// 238 PAY 199 

    0xdf4ef308,// 239 PAY 200 

    0x4893fa4a,// 240 PAY 201 

    0x0d4c66e4,// 241 PAY 202 

    0xbddceb0d,// 242 PAY 203 

    0x6cac74f2,// 243 PAY 204 

    0x672e0b26,// 244 PAY 205 

    0xa0acdd06,// 245 PAY 206 

    0x6fa2bd3c,// 246 PAY 207 

    0xa5502c5e,// 247 PAY 208 

    0xd9864cfc,// 248 PAY 209 

    0xb1af52d6,// 249 PAY 210 

    0x204b5844,// 250 PAY 211 

    0x41292879,// 251 PAY 212 

    0xb006f98c,// 252 PAY 213 

    0xfcf12137,// 253 PAY 214 

    0xbdb29f64,// 254 PAY 215 

    0x9cd5cfc5,// 255 PAY 216 

    0xf87ad4d4,// 256 PAY 217 

    0xf936a2c7,// 257 PAY 218 

    0x54a1d295,// 258 PAY 219 

    0x0c2f9c68,// 259 PAY 220 

    0xaaf39dec,// 260 PAY 221 

    0x2a21f9cf,// 261 PAY 222 

    0xb0d88f0d,// 262 PAY 223 

    0x6f1fa0e9,// 263 PAY 224 

    0xc802db52,// 264 PAY 225 

    0xd152a564,// 265 PAY 226 

    0x9008ce73,// 266 PAY 227 

    0xe69f6cf0,// 267 PAY 228 

    0x572325a6,// 268 PAY 229 

    0x64590037,// 269 PAY 230 

    0x63bee6fd,// 270 PAY 231 

    0x99ead7aa,// 271 PAY 232 

    0xb987615b,// 272 PAY 233 

    0x83e06833,// 273 PAY 234 

    0x25b4aefa,// 274 PAY 235 

    0x852d22ae,// 275 PAY 236 

    0x8a6eaf80,// 276 PAY 237 

    0xac7e6528,// 277 PAY 238 

    0x5db51095,// 278 PAY 239 

    0x82794e23,// 279 PAY 240 

    0x7344f0a7,// 280 PAY 241 

    0x0c88db72,// 281 PAY 242 

    0x73c2b790,// 282 PAY 243 

    0x64ffd0c8,// 283 PAY 244 

    0x620d591d,// 284 PAY 245 

    0x3e8c7cdf,// 285 PAY 246 

    0x12369bac,// 286 PAY 247 

    0xb4762d4e,// 287 PAY 248 

    0x47010767,// 288 PAY 249 

    0xfe6d5f1c,// 289 PAY 250 

    0xc21c05c7,// 290 PAY 251 

    0x3501223b,// 291 PAY 252 

    0xa027f453,// 292 PAY 253 

    0x8a79e95b,// 293 PAY 254 

    0xa09bbb46,// 294 PAY 255 

    0x732d382e,// 295 PAY 256 

    0x7b952202,// 296 PAY 257 

    0x976230c3,// 297 PAY 258 

    0xdb189bb6,// 298 PAY 259 

    0xdd211d83,// 299 PAY 260 

    0x8132b286,// 300 PAY 261 

    0x08c25a85,// 301 PAY 262 

    0x1cfa6397,// 302 PAY 263 

    0x83c76731,// 303 PAY 264 

    0x0742c10e,// 304 PAY 265 

    0xad892a86,// 305 PAY 266 

    0x46711935,// 306 PAY 267 

    0x1466c62e,// 307 PAY 268 

    0x9a775c02,// 308 PAY 269 

    0x7effe4e5,// 309 PAY 270 

    0xc698a934,// 310 PAY 271 

    0xcbe3e455,// 311 PAY 272 

    0x85d2b436,// 312 PAY 273 

    0x7b5d5c79,// 313 PAY 274 

    0xd130c6e4,// 314 PAY 275 

    0x5b88ddca,// 315 PAY 276 

    0xe5ce1e61,// 316 PAY 277 

    0x98e51ebe,// 317 PAY 278 

    0xa06b6235,// 318 PAY 279 

    0x879f7bc2,// 319 PAY 280 

    0xae66e25a,// 320 PAY 281 

    0x8bcc665b,// 321 PAY 282 

    0xdf655ad1,// 322 PAY 283 

    0x515d9ee8,// 323 PAY 284 

    0x4f011218,// 324 PAY 285 

    0x352da860,// 325 PAY 286 

    0xc5ff4d67,// 326 PAY 287 

    0xa7356eea,// 327 PAY 288 

    0xc0a83739,// 328 PAY 289 

    0x7fd30891,// 329 PAY 290 

    0xd040d325,// 330 PAY 291 

    0x0171ea95,// 331 PAY 292 

    0xf721cfcd,// 332 PAY 293 

    0x1a7e78bc,// 333 PAY 294 

    0x0955d900,// 334 PAY 295 

/// STA is 1 words. 

/// STA num_pkts       : 207 

/// STA pkt_idx        : 160 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x1e 

    0x02811ecf // 335 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt59_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x00 

/// ECH pdu_tag        : 0x00 

    0x00000000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000019,// 3 SCX   1 

    0x80924815,// 4 SCX   2 

    0x000044c2,// 5 SCX   3 

    0xa5f38c8a,// 6 SCX   4 

    0xc7f305ee,// 7 SCX   5 

    0x85b63aa9,// 8 SCX   6 

    0x9b71446d,// 9 SCX   7 

    0x3b500dd5,// 10 SCX   8 

    0x26e17181,// 11 SCX   9 

    0xc7d3f4d9,// 12 SCX  10 

    0xc06785b4,// 13 SCX  11 

    0x018431e6,// 14 SCX  12 

    0x21acc6dc,// 15 SCX  13 

    0x6edfbe95,// 16 SCX  14 

    0x3436291b,// 17 SCX  15 

    0x7201d009,// 18 SCX  16 

    0xc5c5cac9,// 19 SCX  17 

    0xb352f3f9,// 20 SCX  18 

    0x349f5b4a,// 21 SCX  19 

    0xdb349c1d,// 22 SCX  20 

    0xa351c28e,// 23 SCX  21 

    0x17eb9531,// 24 SCX  22 

    0xf0567d64,// 25 SCX  23 

    0x28c97a94,// 26 SCX  24 

    0x8583a598,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 517 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 101 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 101 

/// BFD lencrypto      : 40 

/// BFD ofstcrypto     : 56 

/// BFD (ofst+len)cry  : 96 

/// BFD ofstiv         : 16 

/// BFD ofsticv        : 280 

    0x00000065,// 28 BFD   1 

    0x00380028,// 29 BFD   2 

    0x01180010,// 30 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : a 

    0x0a000553,// 31 MFM   1 

    0x199d7d00,// 32 MFM   2 

/// BDA is 131 words. 

/// BDA size     is 517 (0x205) 

/// BDA id       is 0x1f49 

    0x02051f49,// 33 BDA   1 

/// PAY Generic Data size   : 517 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0xd2c9dfe6,// 34 PAY   1 

    0x1384c9dc,// 35 PAY   2 

    0x4b0428e2,// 36 PAY   3 

    0xc529a9dd,// 37 PAY   4 

    0x7c1aadc7,// 38 PAY   5 

    0xda01ac75,// 39 PAY   6 

    0xec621064,// 40 PAY   7 

    0x8a7a4d9b,// 41 PAY   8 

    0xb02a79d2,// 42 PAY   9 

    0xc0d65a8f,// 43 PAY  10 

    0x1c097008,// 44 PAY  11 

    0x5b0255a8,// 45 PAY  12 

    0x0520980b,// 46 PAY  13 

    0xb231b77c,// 47 PAY  14 

    0xf0a5db99,// 48 PAY  15 

    0x2fd08705,// 49 PAY  16 

    0x328385a0,// 50 PAY  17 

    0x3341749e,// 51 PAY  18 

    0x8a151ed7,// 52 PAY  19 

    0xff807dec,// 53 PAY  20 

    0x77405129,// 54 PAY  21 

    0xd66d7d19,// 55 PAY  22 

    0x25c06069,// 56 PAY  23 

    0xadad8618,// 57 PAY  24 

    0x823351d8,// 58 PAY  25 

    0x6d99fdcc,// 59 PAY  26 

    0x41936330,// 60 PAY  27 

    0x3486dd17,// 61 PAY  28 

    0xf28c563a,// 62 PAY  29 

    0x8f0858bb,// 63 PAY  30 

    0x03a7ef78,// 64 PAY  31 

    0x795bc02c,// 65 PAY  32 

    0x9ac87d81,// 66 PAY  33 

    0x0f3b729a,// 67 PAY  34 

    0xbc4067c1,// 68 PAY  35 

    0x47d5c5fd,// 69 PAY  36 

    0x6a805656,// 70 PAY  37 

    0xa7da2cad,// 71 PAY  38 

    0x10557b6d,// 72 PAY  39 

    0x7d1f6837,// 73 PAY  40 

    0x80324980,// 74 PAY  41 

    0x17faa5b8,// 75 PAY  42 

    0x6aa12720,// 76 PAY  43 

    0x458b0e78,// 77 PAY  44 

    0xbda0409f,// 78 PAY  45 

    0x5af3cd12,// 79 PAY  46 

    0x25397088,// 80 PAY  47 

    0x5cca54e0,// 81 PAY  48 

    0x1892c8f4,// 82 PAY  49 

    0xbfd0b2fe,// 83 PAY  50 

    0xd29a4b38,// 84 PAY  51 

    0x951c043c,// 85 PAY  52 

    0xf062be56,// 86 PAY  53 

    0xe6a4997d,// 87 PAY  54 

    0xa73df7fc,// 88 PAY  55 

    0x1bb7d39e,// 89 PAY  56 

    0x6fabe8aa,// 90 PAY  57 

    0x4a1bbecb,// 91 PAY  58 

    0x6c9c1c28,// 92 PAY  59 

    0x5e2bb4da,// 93 PAY  60 

    0xeaa0b09b,// 94 PAY  61 

    0x798fc14a,// 95 PAY  62 

    0x6d14ecf7,// 96 PAY  63 

    0xe3d5cfc8,// 97 PAY  64 

    0x868022d5,// 98 PAY  65 

    0x4ef5832f,// 99 PAY  66 

    0xe632d969,// 100 PAY  67 

    0x89da5e94,// 101 PAY  68 

    0xae4a68fc,// 102 PAY  69 

    0xc894e55f,// 103 PAY  70 

    0xa499b580,// 104 PAY  71 

    0xdf62a4aa,// 105 PAY  72 

    0x21abbbdc,// 106 PAY  73 

    0xe13458de,// 107 PAY  74 

    0x5f35a165,// 108 PAY  75 

    0x24cb9fde,// 109 PAY  76 

    0x2605e6b6,// 110 PAY  77 

    0x6622a2a2,// 111 PAY  78 

    0xa1884d71,// 112 PAY  79 

    0x78fd88c3,// 113 PAY  80 

    0x6aa1fd1c,// 114 PAY  81 

    0xb6f99946,// 115 PAY  82 

    0x07a07f92,// 116 PAY  83 

    0x00b3d27d,// 117 PAY  84 

    0x8cc41be3,// 118 PAY  85 

    0x0f34e924,// 119 PAY  86 

    0xf5388c93,// 120 PAY  87 

    0xf8ec9370,// 121 PAY  88 

    0x8576012a,// 122 PAY  89 

    0x568216d6,// 123 PAY  90 

    0x3f3c6432,// 124 PAY  91 

    0x706171b5,// 125 PAY  92 

    0x2a9ffa3e,// 126 PAY  93 

    0xd8592cd2,// 127 PAY  94 

    0x7168dbfa,// 128 PAY  95 

    0x5b6a9470,// 129 PAY  96 

    0x2666dbcb,// 130 PAY  97 

    0x6b851531,// 131 PAY  98 

    0xd38beeba,// 132 PAY  99 

    0x2f5f1582,// 133 PAY 100 

    0xe4cf79ff,// 134 PAY 101 

    0x966fb515,// 135 PAY 102 

    0xd863dec9,// 136 PAY 103 

    0xfe7ffd8f,// 137 PAY 104 

    0xf91c89a3,// 138 PAY 105 

    0x90a41af4,// 139 PAY 106 

    0x95150e94,// 140 PAY 107 

    0xdc042bc0,// 141 PAY 108 

    0x51a7148c,// 142 PAY 109 

    0xff64fcd5,// 143 PAY 110 

    0x68f99d48,// 144 PAY 111 

    0xceffb823,// 145 PAY 112 

    0x4081abb6,// 146 PAY 113 

    0xac379345,// 147 PAY 114 

    0x23e83215,// 148 PAY 115 

    0x014e5897,// 149 PAY 116 

    0x2a2cf6d8,// 150 PAY 117 

    0xedc52e96,// 151 PAY 118 

    0x2b82485c,// 152 PAY 119 

    0x99d8d8ae,// 153 PAY 120 

    0x936d18ae,// 154 PAY 121 

    0x98ad13a2,// 155 PAY 122 

    0xfd26a123,// 156 PAY 123 

    0x84cc4da3,// 157 PAY 124 

    0x9508ebc2,// 158 PAY 125 

    0xfb5f3edd,// 159 PAY 126 

    0xf7c1180e,// 160 PAY 127 

    0x4002ba26,// 161 PAY 128 

    0xb276b007,// 162 PAY 129 

    0xaf000000,// 163 PAY 130 

/// STA is 1 words. 

/// STA num_pkts       : 244 

/// STA pkt_idx        : 68 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x7a 

    0x01107af4 // 164 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt60_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x0d 

/// ECH pdu_tag        : 0x00 

    0x000d0000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv insert_icv !check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000015,// 3 SCX   1 

    0x80844869,// 4 SCX   2 

    0x00006384,// 5 SCX   3 

    0x2691ce61,// 6 SCX   4 

    0x55618799,// 7 SCX   5 

    0xf72ba21d,// 8 SCX   6 

    0x9825865e,// 9 SCX   7 

    0xdc1e2f68,// 10 SCX   8 

    0x4aa6b4b5,// 11 SCX   9 

    0x97d8b147,// 12 SCX  10 

    0xaf6c14b4,// 13 SCX  11 

    0x90241325,// 14 SCX  12 

    0x785e483b,// 15 SCX  13 

    0xb0f40997,// 16 SCX  14 

    0x2cbda3d3,// 17 SCX  15 

    0x52a883a6,// 18 SCX  16 

    0x6f232668,// 19 SCX  17 

    0x2a554549,// 20 SCX  18 

    0x5edac6dd,// 21 SCX  19 

    0x1155da83,// 22 SCX  20 

    0x2970c641,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 277 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 252 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 252 

/// BFD lencrypto      : 32 

/// BFD ofstcrypto     : 120 

/// BFD (ofst+len)cry  : 152 

/// BFD ofstiv         : 76 

/// BFD ofsticv        : 252 

    0x000000fc,// 24 BFD   1 

    0x00780020,// 25 BFD   2 

    0x00fc004c,// 26 BFD   3 

/// MFM is 1 words. 

/// MFM vldnibs        : 1 

    0x0100a000,// 27 MFM   1 

/// BDA is 71 words. 

/// BDA size     is 277 (0x115) 

/// BDA id       is 0x6d6b 

    0x01156d6b,// 28 BDA   1 

/// PAY Generic Data size   : 277 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0xd8949def,// 29 PAY   1 

    0x65ab970b,// 30 PAY   2 

    0x08f921a4,// 31 PAY   3 

    0x7e8b6c13,// 32 PAY   4 

    0x590a999f,// 33 PAY   5 

    0xa93a409e,// 34 PAY   6 

    0x70f111f0,// 35 PAY   7 

    0xdd46c662,// 36 PAY   8 

    0x081155ae,// 37 PAY   9 

    0x3bb1cf67,// 38 PAY  10 

    0x6e1260e4,// 39 PAY  11 

    0x0d5c75a9,// 40 PAY  12 

    0x06ab90e7,// 41 PAY  13 

    0x93711c5a,// 42 PAY  14 

    0x38bda3f0,// 43 PAY  15 

    0xfb7b0a3b,// 44 PAY  16 

    0x72b2e5cb,// 45 PAY  17 

    0x0e4a0d7a,// 46 PAY  18 

    0x5dd443d0,// 47 PAY  19 

    0x81782db8,// 48 PAY  20 

    0xd64ec731,// 49 PAY  21 

    0xdca0f562,// 50 PAY  22 

    0xc1bb70df,// 51 PAY  23 

    0x8093f14e,// 52 PAY  24 

    0x5421a821,// 53 PAY  25 

    0x9a3ad9fb,// 54 PAY  26 

    0xe4c38e2d,// 55 PAY  27 

    0xaa1951b5,// 56 PAY  28 

    0x15993a02,// 57 PAY  29 

    0x65ffc0c0,// 58 PAY  30 

    0xf15508c2,// 59 PAY  31 

    0xbebce43e,// 60 PAY  32 

    0x0f829be4,// 61 PAY  33 

    0x49d4ebd7,// 62 PAY  34 

    0x957f0e82,// 63 PAY  35 

    0x9039860e,// 64 PAY  36 

    0x3844c397,// 65 PAY  37 

    0xf255186a,// 66 PAY  38 

    0x82547ac0,// 67 PAY  39 

    0x6024d3ca,// 68 PAY  40 

    0x04ae6de5,// 69 PAY  41 

    0xc9750621,// 70 PAY  42 

    0x51e9ffad,// 71 PAY  43 

    0xc9af76f4,// 72 PAY  44 

    0xb27adb11,// 73 PAY  45 

    0x6972f129,// 74 PAY  46 

    0x5964ab03,// 75 PAY  47 

    0xc2a270b8,// 76 PAY  48 

    0x92723007,// 77 PAY  49 

    0x113c7a5b,// 78 PAY  50 

    0xd2b0fd61,// 79 PAY  51 

    0x430c0fac,// 80 PAY  52 

    0xc96660e3,// 81 PAY  53 

    0x94124a18,// 82 PAY  54 

    0x6fa4ca6b,// 83 PAY  55 

    0x52834ea6,// 84 PAY  56 

    0xcf57d3f8,// 85 PAY  57 

    0x97c981c1,// 86 PAY  58 

    0x5644f15e,// 87 PAY  59 

    0x98901130,// 88 PAY  60 

    0xe66ab173,// 89 PAY  61 

    0x8ccad062,// 90 PAY  62 

    0x2896f173,// 91 PAY  63 

    0x5740700f,// 92 PAY  64 

    0x2d9613b8,// 93 PAY  65 

    0x930b62d4,// 94 PAY  66 

    0x550e6299,// 95 PAY  67 

    0x4bdf023e,// 96 PAY  68 

    0x7d994681,// 97 PAY  69 

    0x9a000000,// 98 PAY  70 

/// STA is 1 words. 

/// STA num_pkts       : 18 

/// STA pkt_idx        : 20 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xda 

    0x0051da12 // 99 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt61_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x00 

/// ECH pdu_tag        : 0x00 

    0x00000000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000019,// 3 SCX   1 

    0x809248b0,// 4 SCX   2 

    0x000053c2,// 5 SCX   3 

    0x93662551,// 6 SCX   4 

    0x525c06f4,// 7 SCX   5 

    0xabe14617,// 8 SCX   6 

    0x6e0403ed,// 9 SCX   7 

    0x87a02cd9,// 10 SCX   8 

    0xe503bfee,// 11 SCX   9 

    0x22594197,// 12 SCX  10 

    0x1cf18f4b,// 13 SCX  11 

    0xe814dc87,// 14 SCX  12 

    0x946fcc75,// 15 SCX  13 

    0x7111cb4b,// 16 SCX  14 

    0x1008de2b,// 17 SCX  15 

    0x5bdc6c58,// 18 SCX  16 

    0xc3e3e7d8,// 19 SCX  17 

    0xaf0d0251,// 20 SCX  18 

    0x31b7f596,// 21 SCX  19 

    0x55671e3c,// 22 SCX  20 

    0xf3df3426,// 23 SCX  21 

    0x13d99a2c,// 24 SCX  22 

    0x34ae9a9d,// 25 SCX  23 

    0x22584a7f,// 26 SCX  24 

    0x74a1c828,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 694 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 619 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 619 

/// BFD lencrypto      : 52 

/// BFD ofstcrypto     : 404 

/// BFD (ofst+len)cry  : 456 

/// BFD ofstiv         : 296 

/// BFD ofsticv        : 628 

    0x0000026b,// 28 BFD   1 

    0x01940034,// 29 BFD   2 

    0x02740128,// 30 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c00af2f,// 31 MFM   1 

    0x77a1debb,// 32 MFM   2 

    0xd2896a38,// 33 MFM   3 

    0x2d5ae896,// 34 MFM   4 

    0x385bc129,// 35 MFM   5 

    0x5126f257,// 36 MFM   6 

    0xb0b5775d,// 37 MFM   7 

    0x9da9826d,// 38 MFM   8 

    0x366a2cce,// 39 MFM   9 

    0xc35ed23a,// 40 MFM  10 

    0xcfec49e7,// 41 MFM  11 

    0x934ab146,// 42 MFM  12 

    0xbd4e73bc,// 43 MFM  13 

    0x9399c7d5,// 44 MFM  14 

    0x3bbb8307,// 45 MFM  15 

    0x2076fe88,// 46 MFM  16 

/// BDA is 175 words. 

/// BDA size     is 694 (0x2b6) 

/// BDA id       is 0xb58b 

    0x02b6b58b,// 47 BDA   1 

/// PAY Generic Data size   : 694 byte(s) 

/// PAD Buffer Data Pad size   : 2 byte(s) 

    0x0e5ad5ff,// 48 PAY   1 

    0x19409564,// 49 PAY   2 

    0xb3540957,// 50 PAY   3 

    0xc73a6d89,// 51 PAY   4 

    0x14bcfdd1,// 52 PAY   5 

    0xbe04d062,// 53 PAY   6 

    0xfc1075ea,// 54 PAY   7 

    0xb4f0f79e,// 55 PAY   8 

    0xf6199306,// 56 PAY   9 

    0xe23ae645,// 57 PAY  10 

    0x82d97d8b,// 58 PAY  11 

    0x37010bdb,// 59 PAY  12 

    0xa11db938,// 60 PAY  13 

    0xfd22e970,// 61 PAY  14 

    0x0e15e0c4,// 62 PAY  15 

    0x28850c34,// 63 PAY  16 

    0x70505611,// 64 PAY  17 

    0xc18da583,// 65 PAY  18 

    0xd082dc58,// 66 PAY  19 

    0x4f053472,// 67 PAY  20 

    0xbdbb5850,// 68 PAY  21 

    0xd13ae5b3,// 69 PAY  22 

    0x707d824c,// 70 PAY  23 

    0x33f07fed,// 71 PAY  24 

    0xed7de9d1,// 72 PAY  25 

    0xc3151584,// 73 PAY  26 

    0x578fa83d,// 74 PAY  27 

    0xa2001963,// 75 PAY  28 

    0x9b399dc3,// 76 PAY  29 

    0x2f6fc91f,// 77 PAY  30 

    0x09e3fa92,// 78 PAY  31 

    0x0393938d,// 79 PAY  32 

    0xa122f2db,// 80 PAY  33 

    0x49858b4c,// 81 PAY  34 

    0xb78151b0,// 82 PAY  35 

    0x6a2e4037,// 83 PAY  36 

    0x7b2ddae7,// 84 PAY  37 

    0x3279bae0,// 85 PAY  38 

    0xb80ec4ed,// 86 PAY  39 

    0xd3e8c5bb,// 87 PAY  40 

    0xa27ba7d5,// 88 PAY  41 

    0xcba6384b,// 89 PAY  42 

    0x4ba7153f,// 90 PAY  43 

    0xa4412498,// 91 PAY  44 

    0x145efdbe,// 92 PAY  45 

    0xc1f39d3f,// 93 PAY  46 

    0x6ff5b67a,// 94 PAY  47 

    0xac694a2d,// 95 PAY  48 

    0x6609a13e,// 96 PAY  49 

    0xd34b0fb8,// 97 PAY  50 

    0x402f0853,// 98 PAY  51 

    0x86d30eb3,// 99 PAY  52 

    0x9400e4d5,// 100 PAY  53 

    0x88349a3e,// 101 PAY  54 

    0xbbf499a1,// 102 PAY  55 

    0x5a8222c4,// 103 PAY  56 

    0xca03dfa0,// 104 PAY  57 

    0x1764fdbc,// 105 PAY  58 

    0xaea2ff9b,// 106 PAY  59 

    0x8cf789d6,// 107 PAY  60 

    0x7866df99,// 108 PAY  61 

    0xb99639c6,// 109 PAY  62 

    0x654882ad,// 110 PAY  63 

    0x58897f3c,// 111 PAY  64 

    0x2dacadd4,// 112 PAY  65 

    0x6373352d,// 113 PAY  66 

    0x2269ccf3,// 114 PAY  67 

    0x8ca73f64,// 115 PAY  68 

    0x3e4b9986,// 116 PAY  69 

    0xa2debe5b,// 117 PAY  70 

    0x1fac72ea,// 118 PAY  71 

    0xf21a5427,// 119 PAY  72 

    0x3de13454,// 120 PAY  73 

    0x2c000232,// 121 PAY  74 

    0x91041352,// 122 PAY  75 

    0x70b1457b,// 123 PAY  76 

    0xa5e6d12e,// 124 PAY  77 

    0x56aba714,// 125 PAY  78 

    0x9493528a,// 126 PAY  79 

    0x88d87c00,// 127 PAY  80 

    0x02677010,// 128 PAY  81 

    0x25b31ba1,// 129 PAY  82 

    0x06c0c5be,// 130 PAY  83 

    0x54bffb0f,// 131 PAY  84 

    0x62daeec5,// 132 PAY  85 

    0x1d9295f2,// 133 PAY  86 

    0x20c7f86a,// 134 PAY  87 

    0x678bd828,// 135 PAY  88 

    0x26709867,// 136 PAY  89 

    0x7e7d8ebd,// 137 PAY  90 

    0x5ba17a7e,// 138 PAY  91 

    0x0edf6aef,// 139 PAY  92 

    0x095704af,// 140 PAY  93 

    0x3c5baa5d,// 141 PAY  94 

    0xa86dff65,// 142 PAY  95 

    0xec70f1cf,// 143 PAY  96 

    0xb22228cf,// 144 PAY  97 

    0x6b16748f,// 145 PAY  98 

    0x26d538e6,// 146 PAY  99 

    0x0ab5eb05,// 147 PAY 100 

    0x4c779145,// 148 PAY 101 

    0xa8856ce0,// 149 PAY 102 

    0xc10ce855,// 150 PAY 103 

    0x54bcd92a,// 151 PAY 104 

    0x1929bddf,// 152 PAY 105 

    0x82dcecab,// 153 PAY 106 

    0xb1c2f09f,// 154 PAY 107 

    0x6049be43,// 155 PAY 108 

    0x3f61e166,// 156 PAY 109 

    0x1046767a,// 157 PAY 110 

    0x2d300f42,// 158 PAY 111 

    0xbb12e0a0,// 159 PAY 112 

    0x0c51d168,// 160 PAY 113 

    0x5d593721,// 161 PAY 114 

    0xf4324f61,// 162 PAY 115 

    0x333efb2e,// 163 PAY 116 

    0x5bf91726,// 164 PAY 117 

    0x29acacb1,// 165 PAY 118 

    0x50ac9fdb,// 166 PAY 119 

    0xbfb86510,// 167 PAY 120 

    0x89460451,// 168 PAY 121 

    0x281d5c5c,// 169 PAY 122 

    0x7c9f070b,// 170 PAY 123 

    0xbd929316,// 171 PAY 124 

    0xe1cf6232,// 172 PAY 125 

    0xd224ff01,// 173 PAY 126 

    0x27973b9f,// 174 PAY 127 

    0x9b7a09f7,// 175 PAY 128 

    0xc5ff4be6,// 176 PAY 129 

    0x5838bc54,// 177 PAY 130 

    0x610e3a89,// 178 PAY 131 

    0x94fcd911,// 179 PAY 132 

    0x26314d66,// 180 PAY 133 

    0xf81f90fc,// 181 PAY 134 

    0xc96deab1,// 182 PAY 135 

    0x4837eddc,// 183 PAY 136 

    0x968ad125,// 184 PAY 137 

    0x489ff91a,// 185 PAY 138 

    0xe835a642,// 186 PAY 139 

    0xcb8dea08,// 187 PAY 140 

    0x7b991d53,// 188 PAY 141 

    0xe65ea6b7,// 189 PAY 142 

    0x6cf7e9dc,// 190 PAY 143 

    0xb0e8fa30,// 191 PAY 144 

    0xa5f7dc25,// 192 PAY 145 

    0x75930657,// 193 PAY 146 

    0x85ec7315,// 194 PAY 147 

    0x9e237082,// 195 PAY 148 

    0x725d69b9,// 196 PAY 149 

    0xcc510b93,// 197 PAY 150 

    0x4823a89e,// 198 PAY 151 

    0xe504af1e,// 199 PAY 152 

    0xdc8255db,// 200 PAY 153 

    0x7e20f22e,// 201 PAY 154 

    0x8f9f0916,// 202 PAY 155 

    0xde8b0926,// 203 PAY 156 

    0x82363779,// 204 PAY 157 

    0x5002f992,// 205 PAY 158 

    0xf37ba8a7,// 206 PAY 159 

    0x4093c10f,// 207 PAY 160 

    0xf34e231d,// 208 PAY 161 

    0xa3c9124a,// 209 PAY 162 

    0x841e088b,// 210 PAY 163 

    0xcd5f68ed,// 211 PAY 164 

    0xd0412a76,// 212 PAY 165 

    0x3e96a588,// 213 PAY 166 

    0x2a7889f9,// 214 PAY 167 

    0xdbbb6467,// 215 PAY 168 

    0x8e972452,// 216 PAY 169 

    0xef9bcee0,// 217 PAY 170 

    0xf83f45a9,// 218 PAY 171 

    0x85c146fa,// 219 PAY 172 

    0xa75a16c5,// 220 PAY 173 

    0x95c20000,// 221 PAY 174 

/// STA is 1 words. 

/// STA num_pkts       : 178 

/// STA pkt_idx        : 214 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x6e 

    0x03586eb2 // 222 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 80 (0x50) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt62_tmpl[] = {
    0xb8010050,// 1 CCH   1 

/// ECH cache_idx      : 0x02 

/// ECH pdu_tag        : 0x00 

    0x00020000,// 2 ECH   1 

/// SCX is 19 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv !insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x00000013,// 3 SCX   1 

    0x80814870,// 4 SCX   2 

    0x00001500,// 5 SCX   3 

    0x41a9c246,// 6 SCX   4 

    0x0f4f23a7,// 7 SCX   5 

    0xeccdda71,// 8 SCX   6 

    0x6bab3886,// 9 SCX   7 

    0x432081a7,// 10 SCX   8 

    0x243f7d43,// 11 SCX   9 

    0x1aac986c,// 12 SCX  10 

    0xd91f4982,// 13 SCX  11 

    0xe3d9434f,// 14 SCX  12 

    0xfe607322,// 15 SCX  13 

    0x3e3f0d6a,// 16 SCX  14 

    0x8e2c3233,// 17 SCX  15 

    0xa2556ff7,// 18 SCX  16 

    0xa98fe084,// 19 SCX  17 

    0x880bde4d,// 20 SCX  18 

    0xcb3bd9c0,// 21 SCX  19 

/// BFD is 3 words. 

/// BFD tot_len        : 1921 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 714 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 714 

/// BFD lencrypto      : 192 

/// BFD ofstcrypto     : 36 

/// BFD (ofst+len)cry  : 228 

/// BFD ofstiv         : 8 

/// BFD ofsticv        : 1520 

    0x000002ca,// 22 BFD   1 

    0x002400c0,// 23 BFD   2 

    0x05f00008,// 24 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 78 

    0x7800f300,// 25 MFM   1 

    0xf5d40544,// 26 MFM   2 

    0x413b83e5,// 27 MFM   3 

    0xed8c0c41,// 28 MFM   4 

    0xa368b421,// 29 MFM   5 

    0xf32fb5f8,// 30 MFM   6 

    0x6ddb7c11,// 31 MFM   7 

    0x6ae20e02,// 32 MFM   8 

    0x614815a2,// 33 MFM   9 

    0x38cf176d,// 34 MFM  10 

    0xac6f2f16,// 35 MFM  11 

    0xdfbdca27,// 36 MFM  12 

    0xf01e54c3,// 37 MFM  13 

    0xf64f1e99,// 38 MFM  14 

    0xc7bddca2,// 39 MFM  15 

    0xe7de0000,// 40 MFM  16 

/// BDA is 482 words. 

/// BDA size     is 1921 (0x781) 

/// BDA id       is 0x8eca 

    0x07818eca,// 41 BDA   1 

/// PAY Generic Data size   : 1921 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x82f087f5,// 42 PAY   1 

    0xf5e15740,// 43 PAY   2 

    0x8bda2bc7,// 44 PAY   3 

    0xc3012014,// 45 PAY   4 

    0x0f6dd83c,// 46 PAY   5 

    0xcbe9ab0b,// 47 PAY   6 

    0x6e66390b,// 48 PAY   7 

    0xb392d028,// 49 PAY   8 

    0xa3d9678d,// 50 PAY   9 

    0xebd4787d,// 51 PAY  10 

    0x2996e6bf,// 52 PAY  11 

    0x54a23640,// 53 PAY  12 

    0x2f622985,// 54 PAY  13 

    0xda49211b,// 55 PAY  14 

    0x8969d241,// 56 PAY  15 

    0xc93a7277,// 57 PAY  16 

    0xb0c8bf3e,// 58 PAY  17 

    0x080017f3,// 59 PAY  18 

    0xbf8ef17e,// 60 PAY  19 

    0x170aafd9,// 61 PAY  20 

    0xe3532ae4,// 62 PAY  21 

    0xca772a8a,// 63 PAY  22 

    0x94b78e83,// 64 PAY  23 

    0xbc99f9d5,// 65 PAY  24 

    0x973a491c,// 66 PAY  25 

    0x5697816a,// 67 PAY  26 

    0x1aed2b8b,// 68 PAY  27 

    0x89f1e9f7,// 69 PAY  28 

    0x8f03764b,// 70 PAY  29 

    0x197afcf7,// 71 PAY  30 

    0x38832c92,// 72 PAY  31 

    0x7e00e7ba,// 73 PAY  32 

    0x7c7ed686,// 74 PAY  33 

    0xb8011733,// 75 PAY  34 

    0x30ebad06,// 76 PAY  35 

    0xf6dd55f1,// 77 PAY  36 

    0xeca4282e,// 78 PAY  37 

    0x948f84c3,// 79 PAY  38 

    0x2dc2cb83,// 80 PAY  39 

    0x27dcff6c,// 81 PAY  40 

    0xc810e44d,// 82 PAY  41 

    0xcea1138c,// 83 PAY  42 

    0xb7446e7a,// 84 PAY  43 

    0xddf13926,// 85 PAY  44 

    0xd6c88529,// 86 PAY  45 

    0xecfeae04,// 87 PAY  46 

    0xc04ddec1,// 88 PAY  47 

    0xbb66425d,// 89 PAY  48 

    0x69028fbb,// 90 PAY  49 

    0x20a5e4f2,// 91 PAY  50 

    0x735875c4,// 92 PAY  51 

    0x019f8ec4,// 93 PAY  52 

    0x06ba9c1d,// 94 PAY  53 

    0xf8e31816,// 95 PAY  54 

    0x70be68b1,// 96 PAY  55 

    0xed144edb,// 97 PAY  56 

    0x09961356,// 98 PAY  57 

    0x8cb52d2f,// 99 PAY  58 

    0x4d56ff49,// 100 PAY  59 

    0xf4dcbe7f,// 101 PAY  60 

    0x8a5bcb40,// 102 PAY  61 

    0x91e1b7b9,// 103 PAY  62 

    0x57a57a77,// 104 PAY  63 

    0x809306eb,// 105 PAY  64 

    0x7d7eb05b,// 106 PAY  65 

    0xf02d3e9e,// 107 PAY  66 

    0x1b644cfd,// 108 PAY  67 

    0x6c3fbdd0,// 109 PAY  68 

    0x838df044,// 110 PAY  69 

    0x9fffd2b5,// 111 PAY  70 

    0xd0ef8228,// 112 PAY  71 

    0x92635d5d,// 113 PAY  72 

    0xdeb903fb,// 114 PAY  73 

    0xa7aa4c1a,// 115 PAY  74 

    0xfd2336e9,// 116 PAY  75 

    0xeb2bb83b,// 117 PAY  76 

    0xaead477a,// 118 PAY  77 

    0xf4cec541,// 119 PAY  78 

    0x0c561435,// 120 PAY  79 

    0xa346e9d7,// 121 PAY  80 

    0x42f3730c,// 122 PAY  81 

    0x81156901,// 123 PAY  82 

    0xbd9e0c5b,// 124 PAY  83 

    0xbc0b7c9d,// 125 PAY  84 

    0x19e87875,// 126 PAY  85 

    0x3c8b9dcd,// 127 PAY  86 

    0x946ad01e,// 128 PAY  87 

    0xc8174c24,// 129 PAY  88 

    0x8d52ca88,// 130 PAY  89 

    0xd7bf79f1,// 131 PAY  90 

    0xebaeb6eb,// 132 PAY  91 

    0xfc69193d,// 133 PAY  92 

    0x50d4255e,// 134 PAY  93 

    0xf8c11df0,// 135 PAY  94 

    0x0cddb64f,// 136 PAY  95 

    0x1512b3a6,// 137 PAY  96 

    0xef5a5496,// 138 PAY  97 

    0x6c46cb42,// 139 PAY  98 

    0x75abdc37,// 140 PAY  99 

    0x615fbf01,// 141 PAY 100 

    0xb453ce46,// 142 PAY 101 

    0x6ef5c9c5,// 143 PAY 102 

    0x7469bae7,// 144 PAY 103 

    0xb3039008,// 145 PAY 104 

    0xef35ba43,// 146 PAY 105 

    0x2dfd819b,// 147 PAY 106 

    0xb014ff2d,// 148 PAY 107 

    0xa7a6895b,// 149 PAY 108 

    0x1240ca2d,// 150 PAY 109 

    0xc2438c03,// 151 PAY 110 

    0x0d0f308b,// 152 PAY 111 

    0x2e8490bb,// 153 PAY 112 

    0xeaf0dc33,// 154 PAY 113 

    0x6347f7bc,// 155 PAY 114 

    0xcd924fce,// 156 PAY 115 

    0x11342387,// 157 PAY 116 

    0x55e15928,// 158 PAY 117 

    0xb86ef830,// 159 PAY 118 

    0x8d0bf526,// 160 PAY 119 

    0xbdc3e285,// 161 PAY 120 

    0xa7ac4118,// 162 PAY 121 

    0x8a62e01b,// 163 PAY 122 

    0x2e729289,// 164 PAY 123 

    0xc2e5dbc0,// 165 PAY 124 

    0x81117162,// 166 PAY 125 

    0xcdbede80,// 167 PAY 126 

    0x3a4070d5,// 168 PAY 127 

    0xa2521532,// 169 PAY 128 

    0x64749177,// 170 PAY 129 

    0x7d57ad4e,// 171 PAY 130 

    0xbffefa86,// 172 PAY 131 

    0x127a7db5,// 173 PAY 132 

    0x24dc8d94,// 174 PAY 133 

    0x7f684b34,// 175 PAY 134 

    0x182c34d2,// 176 PAY 135 

    0x0cfea711,// 177 PAY 136 

    0xbbe9e334,// 178 PAY 137 

    0xa0173da6,// 179 PAY 138 

    0x7d402f59,// 180 PAY 139 

    0x21314374,// 181 PAY 140 

    0x96fb7c71,// 182 PAY 141 

    0x333c57f3,// 183 PAY 142 

    0xdb6ef879,// 184 PAY 143 

    0x946e3d46,// 185 PAY 144 

    0xb1486c4d,// 186 PAY 145 

    0x0ec1567d,// 187 PAY 146 

    0x2a5e3740,// 188 PAY 147 

    0x9e7bc7b4,// 189 PAY 148 

    0x5827303a,// 190 PAY 149 

    0xdf5f7b6b,// 191 PAY 150 

    0xea60e4b1,// 192 PAY 151 

    0x1bdd61a2,// 193 PAY 152 

    0xf8d7b82c,// 194 PAY 153 

    0xd9268b16,// 195 PAY 154 

    0x161d628a,// 196 PAY 155 

    0xe89c910c,// 197 PAY 156 

    0x1930f47c,// 198 PAY 157 

    0xd00b646e,// 199 PAY 158 

    0x7d426960,// 200 PAY 159 

    0x8c225bcb,// 201 PAY 160 

    0x249f5f56,// 202 PAY 161 

    0xbc050cef,// 203 PAY 162 

    0x1621cb9c,// 204 PAY 163 

    0x5f6974cf,// 205 PAY 164 

    0x75103e06,// 206 PAY 165 

    0x0eecbf7b,// 207 PAY 166 

    0xafecce96,// 208 PAY 167 

    0x30351dc8,// 209 PAY 168 

    0x9815a223,// 210 PAY 169 

    0xdb69fdb1,// 211 PAY 170 

    0x4fa3d17d,// 212 PAY 171 

    0x03bf9ad1,// 213 PAY 172 

    0x868cd9d7,// 214 PAY 173 

    0xf6e83e7f,// 215 PAY 174 

    0x4f53080a,// 216 PAY 175 

    0xb9c49c1e,// 217 PAY 176 

    0xc65f1df8,// 218 PAY 177 

    0x1dd02148,// 219 PAY 178 

    0x8b257aa4,// 220 PAY 179 

    0x01f34199,// 221 PAY 180 

    0xedf7c76e,// 222 PAY 181 

    0xda83caac,// 223 PAY 182 

    0x20211849,// 224 PAY 183 

    0x1ec6f82e,// 225 PAY 184 

    0x88605c61,// 226 PAY 185 

    0xe361ece8,// 227 PAY 186 

    0x0a3e80f8,// 228 PAY 187 

    0x675794e5,// 229 PAY 188 

    0xe3ae603a,// 230 PAY 189 

    0x18deeba8,// 231 PAY 190 

    0xfa862d7b,// 232 PAY 191 

    0x7f9472ec,// 233 PAY 192 

    0x5a51afe5,// 234 PAY 193 

    0x180a1b5b,// 235 PAY 194 

    0x201f85f5,// 236 PAY 195 

    0xeeb5484f,// 237 PAY 196 

    0xe397b86a,// 238 PAY 197 

    0xce7dbce2,// 239 PAY 198 

    0xefd1c76b,// 240 PAY 199 

    0x74004e85,// 241 PAY 200 

    0x5a93397d,// 242 PAY 201 

    0x4a8d184b,// 243 PAY 202 

    0xbaf0859c,// 244 PAY 203 

    0xea3f3e51,// 245 PAY 204 

    0x150ef2d3,// 246 PAY 205 

    0x73a00d7b,// 247 PAY 206 

    0xff49544a,// 248 PAY 207 

    0xe36086ca,// 249 PAY 208 

    0x0300176c,// 250 PAY 209 

    0x62167ebf,// 251 PAY 210 

    0x5f97be52,// 252 PAY 211 

    0xea7c10bd,// 253 PAY 212 

    0x77a4bfc1,// 254 PAY 213 

    0xd8c6c480,// 255 PAY 214 

    0x7c3bdf7b,// 256 PAY 215 

    0x1a1cac43,// 257 PAY 216 

    0xfe605f76,// 258 PAY 217 

    0x70b1a8a8,// 259 PAY 218 

    0x6bf6b68d,// 260 PAY 219 

    0x1a386d6e,// 261 PAY 220 

    0x49d2bcb1,// 262 PAY 221 

    0x354a7f9b,// 263 PAY 222 

    0x6594a061,// 264 PAY 223 

    0x177e37b4,// 265 PAY 224 

    0x0f24df63,// 266 PAY 225 

    0xd955d051,// 267 PAY 226 

    0xc9883dad,// 268 PAY 227 

    0x6adc18c5,// 269 PAY 228 

    0x20b9fef3,// 270 PAY 229 

    0x14e386f8,// 271 PAY 230 

    0x900691e7,// 272 PAY 231 

    0x5157d6ca,// 273 PAY 232 

    0xa422db62,// 274 PAY 233 

    0x3041ba11,// 275 PAY 234 

    0x0d2a2259,// 276 PAY 235 

    0x7185159a,// 277 PAY 236 

    0x172f5028,// 278 PAY 237 

    0x22d049f0,// 279 PAY 238 

    0xe042d4c1,// 280 PAY 239 

    0xdca1ec3e,// 281 PAY 240 

    0x47ddb0f5,// 282 PAY 241 

    0x0e98b5f5,// 283 PAY 242 

    0x7ba019f2,// 284 PAY 243 

    0x3c270035,// 285 PAY 244 

    0x396c696b,// 286 PAY 245 

    0x6f4dc860,// 287 PAY 246 

    0x18e57c6b,// 288 PAY 247 

    0xfb2c7163,// 289 PAY 248 

    0xd5b94708,// 290 PAY 249 

    0x0bb83ade,// 291 PAY 250 

    0x1b6cd5de,// 292 PAY 251 

    0xe176877a,// 293 PAY 252 

    0x49b54f04,// 294 PAY 253 

    0x1eaf6a0f,// 295 PAY 254 

    0x73a72007,// 296 PAY 255 

    0xf95b74b5,// 297 PAY 256 

    0x3fe5808b,// 298 PAY 257 

    0x4f14694f,// 299 PAY 258 

    0x4a616166,// 300 PAY 259 

    0x3c302cbd,// 301 PAY 260 

    0xc2350110,// 302 PAY 261 

    0x5233893b,// 303 PAY 262 

    0xb1ee28a3,// 304 PAY 263 

    0x388be92d,// 305 PAY 264 

    0x86df4643,// 306 PAY 265 

    0xe97765f5,// 307 PAY 266 

    0x1b929276,// 308 PAY 267 

    0x71b076be,// 309 PAY 268 

    0xea44479e,// 310 PAY 269 

    0x9ad99973,// 311 PAY 270 

    0x7a33159b,// 312 PAY 271 

    0xf9efaf52,// 313 PAY 272 

    0x9134de94,// 314 PAY 273 

    0xb1b3383e,// 315 PAY 274 

    0xfad291f2,// 316 PAY 275 

    0x28f256a1,// 317 PAY 276 

    0x435be923,// 318 PAY 277 

    0x2e50deac,// 319 PAY 278 

    0x8ecaf827,// 320 PAY 279 

    0x687d1f21,// 321 PAY 280 

    0xbb8dcd98,// 322 PAY 281 

    0x3e6afef4,// 323 PAY 282 

    0xac1741b9,// 324 PAY 283 

    0xd8d64cef,// 325 PAY 284 

    0x6e76cd06,// 326 PAY 285 

    0xadff46ba,// 327 PAY 286 

    0xb0371407,// 328 PAY 287 

    0x4f20b434,// 329 PAY 288 

    0x76263706,// 330 PAY 289 

    0xaad04c69,// 331 PAY 290 

    0x85bc5806,// 332 PAY 291 

    0xc0bdda8c,// 333 PAY 292 

    0xa5d25216,// 334 PAY 293 

    0x1835cd74,// 335 PAY 294 

    0xff1755ea,// 336 PAY 295 

    0x5168c6f3,// 337 PAY 296 

    0x59695415,// 338 PAY 297 

    0x61f610b0,// 339 PAY 298 

    0x6d749f10,// 340 PAY 299 

    0x825ec621,// 341 PAY 300 

    0xdaf2f2b4,// 342 PAY 301 

    0x63d3ddd3,// 343 PAY 302 

    0xcf758e13,// 344 PAY 303 

    0xae7ef4a8,// 345 PAY 304 

    0xf2c7ce3b,// 346 PAY 305 

    0xbeb267ea,// 347 PAY 306 

    0x9f7d3fa3,// 348 PAY 307 

    0x3ea13910,// 349 PAY 308 

    0x7259aaeb,// 350 PAY 309 

    0xfe4b2fd9,// 351 PAY 310 

    0x1ee6732c,// 352 PAY 311 

    0x44de99e0,// 353 PAY 312 

    0x0bf3fa32,// 354 PAY 313 

    0x329fa948,// 355 PAY 314 

    0xf66bc465,// 356 PAY 315 

    0xe80bad9e,// 357 PAY 316 

    0x3eb366cc,// 358 PAY 317 

    0x25b4af18,// 359 PAY 318 

    0x5a2496ea,// 360 PAY 319 

    0xe6da103a,// 361 PAY 320 

    0x0b987f8d,// 362 PAY 321 

    0xc2ac1ad4,// 363 PAY 322 

    0x3c179081,// 364 PAY 323 

    0x7c0aa866,// 365 PAY 324 

    0x81747d01,// 366 PAY 325 

    0x08a8d8a3,// 367 PAY 326 

    0xd2b37d47,// 368 PAY 327 

    0x89283747,// 369 PAY 328 

    0x3be2a085,// 370 PAY 329 

    0x2a01a738,// 371 PAY 330 

    0x896ba867,// 372 PAY 331 

    0xafbecacf,// 373 PAY 332 

    0xae2c30a9,// 374 PAY 333 

    0xc2d74d32,// 375 PAY 334 

    0x5b98cbe0,// 376 PAY 335 

    0xf8d70943,// 377 PAY 336 

    0xa88a55fb,// 378 PAY 337 

    0x9a1f59fa,// 379 PAY 338 

    0xa7c3c53f,// 380 PAY 339 

    0xd219a679,// 381 PAY 340 

    0x1e2aef06,// 382 PAY 341 

    0x7189c4d2,// 383 PAY 342 

    0x9d1f08fe,// 384 PAY 343 

    0xeff20426,// 385 PAY 344 

    0xdb809944,// 386 PAY 345 

    0xaa384c6c,// 387 PAY 346 

    0x41854823,// 388 PAY 347 

    0x617ea640,// 389 PAY 348 

    0x398f4214,// 390 PAY 349 

    0xbfa32f71,// 391 PAY 350 

    0xb2b16a74,// 392 PAY 351 

    0xb71ac2d9,// 393 PAY 352 

    0x55e4c41b,// 394 PAY 353 

    0x15bf2063,// 395 PAY 354 

    0x1567b75a,// 396 PAY 355 

    0x3037114d,// 397 PAY 356 

    0x0b09e608,// 398 PAY 357 

    0x616f4d2a,// 399 PAY 358 

    0xda9cfb36,// 400 PAY 359 

    0x0bde2276,// 401 PAY 360 

    0xd732f25e,// 402 PAY 361 

    0xc72a8fab,// 403 PAY 362 

    0x0a19e79e,// 404 PAY 363 

    0x5031cb0b,// 405 PAY 364 

    0x16b69711,// 406 PAY 365 

    0xe04af3a0,// 407 PAY 366 

    0x57b6b17c,// 408 PAY 367 

    0xf3d21c04,// 409 PAY 368 

    0xe71e516f,// 410 PAY 369 

    0xaf2219ea,// 411 PAY 370 

    0xb06001ce,// 412 PAY 371 

    0xc16d1050,// 413 PAY 372 

    0xfeb8a2a6,// 414 PAY 373 

    0x9d5fe557,// 415 PAY 374 

    0x13003d56,// 416 PAY 375 

    0xa7da9661,// 417 PAY 376 

    0x67ff0e49,// 418 PAY 377 

    0x89c0407b,// 419 PAY 378 

    0xaf164825,// 420 PAY 379 

    0x915840bc,// 421 PAY 380 

    0x22d8557e,// 422 PAY 381 

    0x36ace5c3,// 423 PAY 382 

    0x726d85ef,// 424 PAY 383 

    0xdbe95140,// 425 PAY 384 

    0x878ebb64,// 426 PAY 385 

    0x80794160,// 427 PAY 386 

    0xd96bf2c9,// 428 PAY 387 

    0x1a18729b,// 429 PAY 388 

    0xa21227b3,// 430 PAY 389 

    0x64007c09,// 431 PAY 390 

    0x9a43dbc3,// 432 PAY 391 

    0xea619be6,// 433 PAY 392 

    0x8d7bc6ef,// 434 PAY 393 

    0x945b972f,// 435 PAY 394 

    0x4d8c6523,// 436 PAY 395 

    0xeaa281fa,// 437 PAY 396 

    0x72321f6d,// 438 PAY 397 

    0xae2b28cc,// 439 PAY 398 

    0xb3c0c592,// 440 PAY 399 

    0xfb3c1ad0,// 441 PAY 400 

    0xf552d133,// 442 PAY 401 

    0x43498309,// 443 PAY 402 

    0x210cabc9,// 444 PAY 403 

    0xfa4c7656,// 445 PAY 404 

    0xb042350f,// 446 PAY 405 

    0x10132caf,// 447 PAY 406 

    0x906089ab,// 448 PAY 407 

    0x1cdb67b5,// 449 PAY 408 

    0xdfbd2d1b,// 450 PAY 409 

    0x166a11ed,// 451 PAY 410 

    0xbfa3f52d,// 452 PAY 411 

    0x40a38b81,// 453 PAY 412 

    0xbbcf2b0e,// 454 PAY 413 

    0x1b039620,// 455 PAY 414 

    0x11416c7e,// 456 PAY 415 

    0x81d4c306,// 457 PAY 416 

    0x6940c259,// 458 PAY 417 

    0x65ff1a25,// 459 PAY 418 

    0x278b7040,// 460 PAY 419 

    0x208c336c,// 461 PAY 420 

    0xf3c61f25,// 462 PAY 421 

    0xb05c15c6,// 463 PAY 422 

    0x8a099682,// 464 PAY 423 

    0x2a57ea29,// 465 PAY 424 

    0x482860a2,// 466 PAY 425 

    0x32b6e0f3,// 467 PAY 426 

    0xf549e2ba,// 468 PAY 427 

    0xea951c23,// 469 PAY 428 

    0xa6e1c0e4,// 470 PAY 429 

    0x92a5cf89,// 471 PAY 430 

    0xa224c498,// 472 PAY 431 

    0xf04fe31d,// 473 PAY 432 

    0x1a5069ba,// 474 PAY 433 

    0x5297a829,// 475 PAY 434 

    0x2dcdd0da,// 476 PAY 435 

    0xf192ba8a,// 477 PAY 436 

    0x362e8bc4,// 478 PAY 437 

    0x0f0b6ca3,// 479 PAY 438 

    0x006216ec,// 480 PAY 439 

    0x6a01b669,// 481 PAY 440 

    0x05e27b48,// 482 PAY 441 

    0x9d4415f4,// 483 PAY 442 

    0x0ef0f7f5,// 484 PAY 443 

    0xdc2aabab,// 485 PAY 444 

    0xdfc28db4,// 486 PAY 445 

    0x4aaa78f4,// 487 PAY 446 

    0xcfc9903f,// 488 PAY 447 

    0x5363de60,// 489 PAY 448 

    0xded86830,// 490 PAY 449 

    0xb8673ac1,// 491 PAY 450 

    0xf065fe14,// 492 PAY 451 

    0x66ef507c,// 493 PAY 452 

    0xde037e83,// 494 PAY 453 

    0xdff4acb6,// 495 PAY 454 

    0xd2830599,// 496 PAY 455 

    0xd75018e1,// 497 PAY 456 

    0xa997a1dd,// 498 PAY 457 

    0x5384c4db,// 499 PAY 458 

    0x0a5dd3df,// 500 PAY 459 

    0x98275b0e,// 501 PAY 460 

    0xd1cfac36,// 502 PAY 461 

    0xb815a395,// 503 PAY 462 

    0xac8aa5b0,// 504 PAY 463 

    0xfc60c30b,// 505 PAY 464 

    0x0cc68f2f,// 506 PAY 465 

    0xd843e03d,// 507 PAY 466 

    0xc4788323,// 508 PAY 467 

    0x0139a4d7,// 509 PAY 468 

    0x19d812d9,// 510 PAY 469 

    0x5a9d2074,// 511 PAY 470 

    0xbfba43ae,// 512 PAY 471 

    0x9ee6750e,// 513 PAY 472 

    0xf066af2a,// 514 PAY 473 

    0xe39fa706,// 515 PAY 474 

    0xd85db270,// 516 PAY 475 

    0x227f7448,// 517 PAY 476 

    0xeb4a0ebf,// 518 PAY 477 

    0x2ff54b7c,// 519 PAY 478 

    0x809465a2,// 520 PAY 479 

    0x1a6b15d3,// 521 PAY 480 

    0x65000000,// 522 PAY 481 

/// STA is 1 words. 

/// STA num_pkts       : 128 

/// STA pkt_idx        : 187 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xdd 

    0x02ecdd80 // 523 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt63_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x0c 

/// ECH pdu_tag        : 0x00 

    0x000c0000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x808248d8,// 4 SCX   2 

    0x00002300,// 5 SCX   3 

    0xa1d66f6a,// 6 SCX   4 

    0x997072f9,// 7 SCX   5 

    0xe2db2c84,// 8 SCX   6 

    0xa88ce90e,// 9 SCX   7 

    0xdea63dfb,// 10 SCX   8 

    0x892e6578,// 11 SCX   9 

    0xa92fba19,// 12 SCX  10 

    0x99ff7411,// 13 SCX  11 

    0xb2e9a30b,// 14 SCX  12 

    0x28df1edb,// 15 SCX  13 

    0xfd7ce633,// 16 SCX  14 

    0x400fe7a9,// 17 SCX  15 

    0x48f2afe2,// 18 SCX  16 

    0xc0d4bd87,// 19 SCX  17 

    0xa426f223,// 20 SCX  18 

    0xbc689ebd,// 21 SCX  19 

    0x6a1d731e,// 22 SCX  20 

    0x1a4e5cab,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 664 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 336 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 336 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 316 

/// BFD (ofst+len)cry  : 332 

/// BFD ofstiv         : 52 

/// BFD ofsticv        : 600 

    0x00000150,// 24 BFD   1 

    0x013c0010,// 25 BFD   2 

    0x02580034,// 26 BFD   3 

/// MFM is 10 words. 

/// MFM vldnibs        : 4c 

    0x4c00d948,// 27 MFM   1 

    0xb0f137f9,// 28 MFM   2 

    0xaf29cc6d,// 29 MFM   3 

    0x840ac3b5,// 30 MFM   4 

    0x5f666a75,// 31 MFM   5 

    0x2f111b6e,// 32 MFM   6 

    0xf9d82fc9,// 33 MFM   7 

    0x84c1e9b6,// 34 MFM   8 

    0xb3efe5e7,// 35 MFM   9 

    0x7f6a716f,// 36 MFM  10 

/// BDA is 167 words. 

/// BDA size     is 664 (0x298) 

/// BDA id       is 0xad27 

    0x0298ad27,// 37 BDA   1 

/// PAY Generic Data size   : 664 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0x99021180,// 38 PAY   1 

    0x2ee4f095,// 39 PAY   2 

    0xdf2fef4e,// 40 PAY   3 

    0x9fcf0407,// 41 PAY   4 

    0xf81c60f6,// 42 PAY   5 

    0x13618706,// 43 PAY   6 

    0xebd99b8f,// 44 PAY   7 

    0x1cca8ba3,// 45 PAY   8 

    0x23a4add8,// 46 PAY   9 

    0x897cca7c,// 47 PAY  10 

    0x7298199c,// 48 PAY  11 

    0xb32377a1,// 49 PAY  12 

    0x2f488067,// 50 PAY  13 

    0x079341aa,// 51 PAY  14 

    0x0ff4218e,// 52 PAY  15 

    0x434d57f4,// 53 PAY  16 

    0x42fefe84,// 54 PAY  17 

    0x839bacc1,// 55 PAY  18 

    0x34ab628f,// 56 PAY  19 

    0x9411986c,// 57 PAY  20 

    0x823e8e4d,// 58 PAY  21 

    0x1556d949,// 59 PAY  22 

    0xd15bc2e8,// 60 PAY  23 

    0xdc4957f7,// 61 PAY  24 

    0x5ec52f45,// 62 PAY  25 

    0xb4b54a1f,// 63 PAY  26 

    0x2c0748c8,// 64 PAY  27 

    0x99c0c1a0,// 65 PAY  28 

    0xdceb45bb,// 66 PAY  29 

    0x2733aeaa,// 67 PAY  30 

    0x98ad3ee7,// 68 PAY  31 

    0x8bfbb958,// 69 PAY  32 

    0xf7b871d5,// 70 PAY  33 

    0xb0570023,// 71 PAY  34 

    0x05506f32,// 72 PAY  35 

    0x9a0ea1aa,// 73 PAY  36 

    0xce071eaf,// 74 PAY  37 

    0xadf710bb,// 75 PAY  38 

    0x8cd3c69f,// 76 PAY  39 

    0xaef8ba7d,// 77 PAY  40 

    0x3af1d56c,// 78 PAY  41 

    0xf78598bf,// 79 PAY  42 

    0x37d65432,// 80 PAY  43 

    0xcbf0bcd0,// 81 PAY  44 

    0xd28e5fe5,// 82 PAY  45 

    0x628c0e7a,// 83 PAY  46 

    0x2392ccab,// 84 PAY  47 

    0x53fba7e2,// 85 PAY  48 

    0x2f853e42,// 86 PAY  49 

    0xb3337629,// 87 PAY  50 

    0xc8a32c7b,// 88 PAY  51 

    0x9c35fe3f,// 89 PAY  52 

    0x2d75de84,// 90 PAY  53 

    0xf7b1a724,// 91 PAY  54 

    0x34b92d38,// 92 PAY  55 

    0x6ffc1464,// 93 PAY  56 

    0xe2c9b65c,// 94 PAY  57 

    0xd263f67f,// 95 PAY  58 

    0xfed5d062,// 96 PAY  59 

    0xf1e14076,// 97 PAY  60 

    0x37d40c42,// 98 PAY  61 

    0x5d1c4b4e,// 99 PAY  62 

    0xb5ead67b,// 100 PAY  63 

    0x1aef8948,// 101 PAY  64 

    0x76b21cd9,// 102 PAY  65 

    0xb7a866cf,// 103 PAY  66 

    0x4f865e49,// 104 PAY  67 

    0x2a76f432,// 105 PAY  68 

    0x1795a166,// 106 PAY  69 

    0xc7bf2d08,// 107 PAY  70 

    0x57322dbd,// 108 PAY  71 

    0xe8a6ed40,// 109 PAY  72 

    0xfc8d80ce,// 110 PAY  73 

    0xbae85405,// 111 PAY  74 

    0x4c065006,// 112 PAY  75 

    0xef41e2c8,// 113 PAY  76 

    0xda322e29,// 114 PAY  77 

    0xa15e6d40,// 115 PAY  78 

    0x230ec301,// 116 PAY  79 

    0x7dfb2164,// 117 PAY  80 

    0x24b4b756,// 118 PAY  81 

    0xab0f2a5c,// 119 PAY  82 

    0xebd220ab,// 120 PAY  83 

    0x8d2e43d5,// 121 PAY  84 

    0xf2e948ff,// 122 PAY  85 

    0x563d25cf,// 123 PAY  86 

    0xbc2866ce,// 124 PAY  87 

    0x4e2c6c54,// 125 PAY  88 

    0x8a5ed2f1,// 126 PAY  89 

    0xf7385b5c,// 127 PAY  90 

    0xa4873908,// 128 PAY  91 

    0x763fe3a8,// 129 PAY  92 

    0x4e428e9a,// 130 PAY  93 

    0x0a0d4a5a,// 131 PAY  94 

    0x7019a37d,// 132 PAY  95 

    0xe9454a42,// 133 PAY  96 

    0xef0fb731,// 134 PAY  97 

    0xbc1e62f6,// 135 PAY  98 

    0x1593cb15,// 136 PAY  99 

    0x66244d47,// 137 PAY 100 

    0x9f71de81,// 138 PAY 101 

    0x6a81b063,// 139 PAY 102 

    0x90f71a12,// 140 PAY 103 

    0x0f9b6b63,// 141 PAY 104 

    0x9eff9917,// 142 PAY 105 

    0x3c8327de,// 143 PAY 106 

    0xe4dc128d,// 144 PAY 107 

    0x5fbe0921,// 145 PAY 108 

    0x4f510848,// 146 PAY 109 

    0xed18ee20,// 147 PAY 110 

    0xbf1ec2ba,// 148 PAY 111 

    0xb095d27e,// 149 PAY 112 

    0x9c5d4df8,// 150 PAY 113 

    0x8dc541c6,// 151 PAY 114 

    0xb69c6081,// 152 PAY 115 

    0x1a36fa94,// 153 PAY 116 

    0x37f7fce4,// 154 PAY 117 

    0x2fe0cfee,// 155 PAY 118 

    0xf2352f37,// 156 PAY 119 

    0x76363170,// 157 PAY 120 

    0xa0661cad,// 158 PAY 121 

    0x59335573,// 159 PAY 122 

    0xe407081d,// 160 PAY 123 

    0x0d77aa9b,// 161 PAY 124 

    0x17eade5a,// 162 PAY 125 

    0xac998893,// 163 PAY 126 

    0xb073bdc1,// 164 PAY 127 

    0xbf0b7915,// 165 PAY 128 

    0xd3a9fbd2,// 166 PAY 129 

    0x958b266b,// 167 PAY 130 

    0x4ea19f8a,// 168 PAY 131 

    0x5b12fb3b,// 169 PAY 132 

    0x382ea45c,// 170 PAY 133 

    0xe2efd7b3,// 171 PAY 134 

    0xae393e88,// 172 PAY 135 

    0xf0d611d5,// 173 PAY 136 

    0x5c58117c,// 174 PAY 137 

    0x4976c2e2,// 175 PAY 138 

    0x917ebf4a,// 176 PAY 139 

    0x0481f5e8,// 177 PAY 140 

    0x24fa4c03,// 178 PAY 141 

    0xd36d5b5c,// 179 PAY 142 

    0x1abe0bb9,// 180 PAY 143 

    0x36617332,// 181 PAY 144 

    0xde1a5bf5,// 182 PAY 145 

    0x46c540c3,// 183 PAY 146 

    0xafa35254,// 184 PAY 147 

    0x7c7b7e59,// 185 PAY 148 

    0x9fd0e49f,// 186 PAY 149 

    0x9e6691aa,// 187 PAY 150 

    0x900fd842,// 188 PAY 151 

    0x4014392e,// 189 PAY 152 

    0x51148d5d,// 190 PAY 153 

    0x285556f9,// 191 PAY 154 

    0xf52a6697,// 192 PAY 155 

    0xaaa92d91,// 193 PAY 156 

    0xa4f0bd91,// 194 PAY 157 

    0x9fb46dda,// 195 PAY 158 

    0x6a3613ca,// 196 PAY 159 

    0x0e84d81a,// 197 PAY 160 

    0x01ee3ad5,// 198 PAY 161 

    0x5e593379,// 199 PAY 162 

    0x53382346,// 200 PAY 163 

    0xe2191127,// 201 PAY 164 

    0x83e9c57b,// 202 PAY 165 

    0x04fe0c60,// 203 PAY 166 

/// STA is 1 words. 

/// STA num_pkts       : 83 

/// STA pkt_idx        : 218 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x25 

    0x03682553 // 204 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 96 (0x60) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt64_tmpl[] = {
    0xb8010060,// 1 CCH   1 

/// ECH cache_idx      : 0x08 

/// ECH pdu_tag        : 0x00 

    0x00080000,// 2 ECH   1 

/// SCX is 23 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv !insert_icv check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000017,// 3 SCX   1 

    0x8085488e,// 4 SCX   2 

    0x000014c4,// 5 SCX   3 

    0xb6496f6e,// 6 SCX   4 

    0xcb0e07d3,// 7 SCX   5 

    0xf047cdaf,// 8 SCX   6 

    0x769546c1,// 9 SCX   7 

    0xdca4c844,// 10 SCX   8 

    0x12561828,// 11 SCX   9 

    0xe783c154,// 12 SCX  10 

    0x08c6be86,// 13 SCX  11 

    0xb9adf4eb,// 14 SCX  12 

    0xc4478bf9,// 15 SCX  13 

    0x3becb9c0,// 16 SCX  14 

    0x891ea087,// 17 SCX  15 

    0x499d27d2,// 18 SCX  16 

    0x87394112,// 19 SCX  17 

    0x32b24415,// 20 SCX  18 

    0x10038b4d,// 21 SCX  19 

    0xf51bb58e,// 22 SCX  20 

    0x34bb40c3,// 23 SCX  21 

    0xa941b843,// 24 SCX  22 

    0x1de08f02,// 25 SCX  23 

/// BFD is 3 words. 

/// BFD tot_len        : 545 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 385 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 385 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 292 

/// BFD (ofst+len)cry  : 308 

/// BFD ofstiv         : 116 

/// BFD ofsticv        : 488 

    0x00000181,// 26 BFD   1 

    0x01240010,// 27 BFD   2 

    0x01e80074,// 28 BFD   3 

/// MFM is 5 words. 

/// MFM vldnibs        : 24 

    0x2400a9d9,// 29 MFM   1 

    0x22cd6445,// 30 MFM   2 

    0x8b9cc068,// 31 MFM   3 

    0xef4bd6b4,// 32 MFM   4 

    0x0d1ce0f4,// 33 MFM   5 

/// BDA is 138 words. 

/// BDA size     is 545 (0x221) 

/// BDA id       is 0x770a 

    0x0221770a,// 34 BDA   1 

/// PAY Generic Data size   : 545 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x849b0bcf,// 35 PAY   1 

    0xc5fbde3c,// 36 PAY   2 

    0x550eb7b4,// 37 PAY   3 

    0x5e0e8faf,// 38 PAY   4 

    0x7b02df0e,// 39 PAY   5 

    0x491496a7,// 40 PAY   6 

    0xf0da445d,// 41 PAY   7 

    0xf7ba2066,// 42 PAY   8 

    0xe145a31d,// 43 PAY   9 

    0x02db19e0,// 44 PAY  10 

    0x7c316baa,// 45 PAY  11 

    0xbe14d815,// 46 PAY  12 

    0x61e5f84a,// 47 PAY  13 

    0x0deabcf7,// 48 PAY  14 

    0x2c5545df,// 49 PAY  15 

    0xf6fd771c,// 50 PAY  16 

    0x5ec99562,// 51 PAY  17 

    0x73b178f8,// 52 PAY  18 

    0xaf448ec5,// 53 PAY  19 

    0x6bf01503,// 54 PAY  20 

    0xf02c5462,// 55 PAY  21 

    0x19733cca,// 56 PAY  22 

    0xc2e84d71,// 57 PAY  23 

    0x4e015165,// 58 PAY  24 

    0xae608a64,// 59 PAY  25 

    0x046b6bdc,// 60 PAY  26 

    0x03eca4a0,// 61 PAY  27 

    0xbc01920e,// 62 PAY  28 

    0x51e696e8,// 63 PAY  29 

    0x07bcac02,// 64 PAY  30 

    0x313e4714,// 65 PAY  31 

    0x15a5a4f0,// 66 PAY  32 

    0x825991ce,// 67 PAY  33 

    0x52be061e,// 68 PAY  34 

    0x2d41272b,// 69 PAY  35 

    0xcd57b6a4,// 70 PAY  36 

    0x97094558,// 71 PAY  37 

    0xb9d6a156,// 72 PAY  38 

    0x60909b34,// 73 PAY  39 

    0xfac89954,// 74 PAY  40 

    0x9a807624,// 75 PAY  41 

    0x53041191,// 76 PAY  42 

    0xdf004a14,// 77 PAY  43 

    0x5f4b5fd6,// 78 PAY  44 

    0xfa3868dd,// 79 PAY  45 

    0xf707879c,// 80 PAY  46 

    0xdbce37f5,// 81 PAY  47 

    0x75c67f28,// 82 PAY  48 

    0x1adb3ceb,// 83 PAY  49 

    0xa399d93c,// 84 PAY  50 

    0xee16131e,// 85 PAY  51 

    0x159b5d66,// 86 PAY  52 

    0x963dd9ad,// 87 PAY  53 

    0x5c4c73af,// 88 PAY  54 

    0x8864f8ab,// 89 PAY  55 

    0xb1b3b2c7,// 90 PAY  56 

    0xc6c887f8,// 91 PAY  57 

    0x30a2c6ce,// 92 PAY  58 

    0x3c3c7bf6,// 93 PAY  59 

    0x22b60f10,// 94 PAY  60 

    0xe603f780,// 95 PAY  61 

    0x51863e3b,// 96 PAY  62 

    0xe8d19e1f,// 97 PAY  63 

    0x4a923399,// 98 PAY  64 

    0x8e141f08,// 99 PAY  65 

    0x97e10788,// 100 PAY  66 

    0x21e5aebd,// 101 PAY  67 

    0xc1bc9ae3,// 102 PAY  68 

    0x78f2c5b2,// 103 PAY  69 

    0x92aad564,// 104 PAY  70 

    0x1f41c1b4,// 105 PAY  71 

    0xa822231f,// 106 PAY  72 

    0x3f021c0d,// 107 PAY  73 

    0x111b6c6b,// 108 PAY  74 

    0x26c1503a,// 109 PAY  75 

    0xfe590621,// 110 PAY  76 

    0xe0f961a6,// 111 PAY  77 

    0x4fbed9b3,// 112 PAY  78 

    0x7e64b87f,// 113 PAY  79 

    0xa2ace290,// 114 PAY  80 

    0x9a9c5100,// 115 PAY  81 

    0x5c422b68,// 116 PAY  82 

    0x5b881e1f,// 117 PAY  83 

    0xc2619e8f,// 118 PAY  84 

    0x0a770239,// 119 PAY  85 

    0x6858fcfb,// 120 PAY  86 

    0xafd162d6,// 121 PAY  87 

    0x8ec34452,// 122 PAY  88 

    0xbcce85d8,// 123 PAY  89 

    0x77c1b7cd,// 124 PAY  90 

    0x0e9a4f21,// 125 PAY  91 

    0x28c3d7f0,// 126 PAY  92 

    0xdf3b9cfe,// 127 PAY  93 

    0x5c370029,// 128 PAY  94 

    0x62901b66,// 129 PAY  95 

    0xa05f358a,// 130 PAY  96 

    0x7b5bc37b,// 131 PAY  97 

    0xb1d192a7,// 132 PAY  98 

    0xf2ae481a,// 133 PAY  99 

    0x23455cce,// 134 PAY 100 

    0x49707280,// 135 PAY 101 

    0x87c0496f,// 136 PAY 102 

    0x37bbebf6,// 137 PAY 103 

    0xa79c743b,// 138 PAY 104 

    0x01893203,// 139 PAY 105 

    0x638db109,// 140 PAY 106 

    0x173fb2de,// 141 PAY 107 

    0x25296538,// 142 PAY 108 

    0x589d3279,// 143 PAY 109 

    0x2dd8261b,// 144 PAY 110 

    0xecdd88b6,// 145 PAY 111 

    0x3b91ee07,// 146 PAY 112 

    0xd1f3bd82,// 147 PAY 113 

    0x769ac3c3,// 148 PAY 114 

    0x6afdef3c,// 149 PAY 115 

    0x2efc44da,// 150 PAY 116 

    0x342a8f39,// 151 PAY 117 

    0x640b054a,// 152 PAY 118 

    0x6833da95,// 153 PAY 119 

    0x55704c16,// 154 PAY 120 

    0x1473e804,// 155 PAY 121 

    0xcc4634f7,// 156 PAY 122 

    0x1bc24df0,// 157 PAY 123 

    0x616e5ed1,// 158 PAY 124 

    0x983d03f9,// 159 PAY 125 

    0xbe3e07ad,// 160 PAY 126 

    0xce372a2c,// 161 PAY 127 

    0x4270a9e3,// 162 PAY 128 

    0x40136ff2,// 163 PAY 129 

    0x2d9accc8,// 164 PAY 130 

    0xb33e6af3,// 165 PAY 131 

    0x12d769f5,// 166 PAY 132 

    0xc223e967,// 167 PAY 133 

    0x3f96c765,// 168 PAY 134 

    0xa5dcfdbd,// 169 PAY 135 

    0xdf253a4a,// 170 PAY 136 

    0x66000000,// 171 PAY 137 

/// STA is 1 words. 

/// STA num_pkts       : 51 

/// STA pkt_idx        : 131 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xbb 

    0x020cbb33 // 172 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt65_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x08 

/// ECH pdu_tag        : 0x00 

    0x00080000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv insert_icv !check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000015,// 3 SCX   1 

    0x80844849,// 4 SCX   2 

    0x00006584,// 5 SCX   3 

    0xcec20a19,// 6 SCX   4 

    0x137a53f9,// 7 SCX   5 

    0xb81adaa1,// 8 SCX   6 

    0x2dee0860,// 9 SCX   7 

    0x25964cc2,// 10 SCX   8 

    0x3c3ff92f,// 11 SCX   9 

    0xe78f277c,// 12 SCX  10 

    0x0a12a933,// 13 SCX  11 

    0xea2d365d,// 14 SCX  12 

    0x71461512,// 15 SCX  13 

    0xa9ca4468,// 16 SCX  14 

    0x5ed019e3,// 17 SCX  15 

    0xa0108428,// 18 SCX  16 

    0x85948c7d,// 19 SCX  17 

    0x7d5c1585,// 20 SCX  18 

    0x38478736,// 21 SCX  19 

    0x89296c82,// 22 SCX  20 

    0xdaa41816,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1816 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 1605 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 1605 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 1520 

/// BFD (ofst+len)cry  : 1536 

/// BFD ofstiv         : 1236 

/// BFD ofsticv        : 1768 

    0x00000645,// 24 BFD   1 

    0x05f00010,// 25 BFD   2 

    0x06e804d4,// 26 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c00bfc3,// 27 MFM   1 

    0x76eac2f8,// 28 MFM   2 

    0x5acf5c1b,// 29 MFM   3 

    0xc32b3949,// 30 MFM   4 

    0x9a0dfd7c,// 31 MFM   5 

    0xfbd51ff8,// 32 MFM   6 

    0xf0198b9a,// 33 MFM   7 

    0xddf3e2f9,// 34 MFM   8 

    0x908433d9,// 35 MFM   9 

    0x0b61f306,// 36 MFM  10 

    0x77c6b3fc,// 37 MFM  11 

    0x1d08bf12,// 38 MFM  12 

    0x222a34b4,// 39 MFM  13 

    0xcec70dba,// 40 MFM  14 

    0x3895f3df,// 41 MFM  15 

    0x6f8094eb,// 42 MFM  16 

/// BDA is 455 words. 

/// BDA size     is 1816 (0x718) 

/// BDA id       is 0x5fa4 

    0x07185fa4,// 43 BDA   1 

/// PAY Generic Data size   : 1816 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0xbfd9397f,// 44 PAY   1 

    0x6d04d6ed,// 45 PAY   2 

    0xee156db3,// 46 PAY   3 

    0xc6b3d068,// 47 PAY   4 

    0xf0586530,// 48 PAY   5 

    0x107d5ca5,// 49 PAY   6 

    0x350bed4c,// 50 PAY   7 

    0x9712c11d,// 51 PAY   8 

    0xf1933926,// 52 PAY   9 

    0x43d3391c,// 53 PAY  10 

    0x2874cdae,// 54 PAY  11 

    0x06fb1d5e,// 55 PAY  12 

    0x658dd663,// 56 PAY  13 

    0x12f18691,// 57 PAY  14 

    0xe1e83b96,// 58 PAY  15 

    0xac41b903,// 59 PAY  16 

    0xa634229f,// 60 PAY  17 

    0x9fc9ff1b,// 61 PAY  18 

    0x6ee412c3,// 62 PAY  19 

    0xd8ac86fd,// 63 PAY  20 

    0x13692168,// 64 PAY  21 

    0x7f7865e0,// 65 PAY  22 

    0xd6bd6e2a,// 66 PAY  23 

    0x500ccb23,// 67 PAY  24 

    0xa2f5eb38,// 68 PAY  25 

    0x9ce96c9f,// 69 PAY  26 

    0x36db1e76,// 70 PAY  27 

    0x301189a2,// 71 PAY  28 

    0x3c6bcc78,// 72 PAY  29 

    0x8da09311,// 73 PAY  30 

    0xd320dfdc,// 74 PAY  31 

    0x1948ee69,// 75 PAY  32 

    0xd4e8c936,// 76 PAY  33 

    0xba918cf6,// 77 PAY  34 

    0xd83f236f,// 78 PAY  35 

    0x720bbb66,// 79 PAY  36 

    0xc8f08686,// 80 PAY  37 

    0x40254c85,// 81 PAY  38 

    0xf60ed8e5,// 82 PAY  39 

    0x8dafbaea,// 83 PAY  40 

    0x056a0b9d,// 84 PAY  41 

    0xdb03feac,// 85 PAY  42 

    0x8fc113d4,// 86 PAY  43 

    0xb5966d3a,// 87 PAY  44 

    0xbdfdc0ff,// 88 PAY  45 

    0xace19ea0,// 89 PAY  46 

    0x5069d9bb,// 90 PAY  47 

    0xd05995db,// 91 PAY  48 

    0x126eff2d,// 92 PAY  49 

    0x2f97c239,// 93 PAY  50 

    0x752a1ee3,// 94 PAY  51 

    0xb1896c54,// 95 PAY  52 

    0x95fbd1d3,// 96 PAY  53 

    0x89f6d493,// 97 PAY  54 

    0x5ab83eec,// 98 PAY  55 

    0x86f48574,// 99 PAY  56 

    0xf0fe39ad,// 100 PAY  57 

    0x9c6c514b,// 101 PAY  58 

    0x5960b42e,// 102 PAY  59 

    0xc15ddc68,// 103 PAY  60 

    0x93d097cc,// 104 PAY  61 

    0x8c0a02f8,// 105 PAY  62 

    0x99a20910,// 106 PAY  63 

    0x95f6f49a,// 107 PAY  64 

    0x613c7fcf,// 108 PAY  65 

    0xd24368f1,// 109 PAY  66 

    0xd1b6112f,// 110 PAY  67 

    0x9dfcb027,// 111 PAY  68 

    0xbc8519bc,// 112 PAY  69 

    0xf2f3ab07,// 113 PAY  70 

    0xfc908edf,// 114 PAY  71 

    0xa472cf5c,// 115 PAY  72 

    0xeee49859,// 116 PAY  73 

    0xbfb8f865,// 117 PAY  74 

    0xc0362c5e,// 118 PAY  75 

    0xc08c0e90,// 119 PAY  76 

    0x8f738b53,// 120 PAY  77 

    0xfcdd7ee8,// 121 PAY  78 

    0x8a36879b,// 122 PAY  79 

    0x28de31da,// 123 PAY  80 

    0x1dbc9ef8,// 124 PAY  81 

    0x6a88ba7d,// 125 PAY  82 

    0xff3929a3,// 126 PAY  83 

    0xf2b4a4a4,// 127 PAY  84 

    0x39968a66,// 128 PAY  85 

    0x667c774e,// 129 PAY  86 

    0xbce425cf,// 130 PAY  87 

    0x19ee2e71,// 131 PAY  88 

    0x9d40b322,// 132 PAY  89 

    0x285f68a7,// 133 PAY  90 

    0xa368a411,// 134 PAY  91 

    0x71a4e664,// 135 PAY  92 

    0xb1f4bcb7,// 136 PAY  93 

    0x22a9bcba,// 137 PAY  94 

    0xccc93608,// 138 PAY  95 

    0xa737aa1d,// 139 PAY  96 

    0x0562fbbc,// 140 PAY  97 

    0xb851cd93,// 141 PAY  98 

    0x94989f55,// 142 PAY  99 

    0xc1d0c72a,// 143 PAY 100 

    0x84114788,// 144 PAY 101 

    0xa1faa567,// 145 PAY 102 

    0x5d812d80,// 146 PAY 103 

    0xba78fbb0,// 147 PAY 104 

    0x3e938c2c,// 148 PAY 105 

    0x62aa1334,// 149 PAY 106 

    0xda850d93,// 150 PAY 107 

    0xab488022,// 151 PAY 108 

    0x73e3e90e,// 152 PAY 109 

    0x19d898ca,// 153 PAY 110 

    0xcf94c55c,// 154 PAY 111 

    0x9c7d7d7b,// 155 PAY 112 

    0x9998307f,// 156 PAY 113 

    0xfca893cd,// 157 PAY 114 

    0x575dc9d6,// 158 PAY 115 

    0xcd72645d,// 159 PAY 116 

    0x0d191124,// 160 PAY 117 

    0xf5ca1ce3,// 161 PAY 118 

    0xf996f2d0,// 162 PAY 119 

    0x3370df6d,// 163 PAY 120 

    0xf113b63e,// 164 PAY 121 

    0xee4ad4b8,// 165 PAY 122 

    0x8ac7ad07,// 166 PAY 123 

    0x50fff347,// 167 PAY 124 

    0x3cde91ec,// 168 PAY 125 

    0xac10a702,// 169 PAY 126 

    0xd73f3f54,// 170 PAY 127 

    0x9b66fc60,// 171 PAY 128 

    0xa5da83b9,// 172 PAY 129 

    0x58cdaab5,// 173 PAY 130 

    0x1b17cfba,// 174 PAY 131 

    0x6d6067ab,// 175 PAY 132 

    0xbb282136,// 176 PAY 133 

    0xf0187f3f,// 177 PAY 134 

    0x4b8db4cb,// 178 PAY 135 

    0x5e88c1ec,// 179 PAY 136 

    0xfe6c3ecc,// 180 PAY 137 

    0xaf3efef8,// 181 PAY 138 

    0x19d1a1e1,// 182 PAY 139 

    0x8c85173e,// 183 PAY 140 

    0xe4cd2c8c,// 184 PAY 141 

    0xebb746e9,// 185 PAY 142 

    0xbc2e7ca9,// 186 PAY 143 

    0xf4c7c123,// 187 PAY 144 

    0x5310d75c,// 188 PAY 145 

    0xc299c910,// 189 PAY 146 

    0x9c760877,// 190 PAY 147 

    0x862d8817,// 191 PAY 148 

    0xf3c50a50,// 192 PAY 149 

    0xac2845b4,// 193 PAY 150 

    0x5bb8c238,// 194 PAY 151 

    0x3bdfee3f,// 195 PAY 152 

    0x677a75ab,// 196 PAY 153 

    0x78a8c9b5,// 197 PAY 154 

    0x8de39588,// 198 PAY 155 

    0xa6a45847,// 199 PAY 156 

    0xce31358a,// 200 PAY 157 

    0x5662bf6a,// 201 PAY 158 

    0x5dff60bf,// 202 PAY 159 

    0x5e6c1d73,// 203 PAY 160 

    0x0976b9cb,// 204 PAY 161 

    0x725b7da1,// 205 PAY 162 

    0x9edf4407,// 206 PAY 163 

    0x3a183ece,// 207 PAY 164 

    0xcb4098a9,// 208 PAY 165 

    0xcdcd3137,// 209 PAY 166 

    0x11eb6029,// 210 PAY 167 

    0xf154bd00,// 211 PAY 168 

    0xf23392ee,// 212 PAY 169 

    0x22c08c3c,// 213 PAY 170 

    0xcdc6320f,// 214 PAY 171 

    0x04bd868a,// 215 PAY 172 

    0xb750ecdb,// 216 PAY 173 

    0x4b6086be,// 217 PAY 174 

    0xcc5e4f73,// 218 PAY 175 

    0xb2e9e0ab,// 219 PAY 176 

    0x1755aa9d,// 220 PAY 177 

    0x0ac6eaeb,// 221 PAY 178 

    0x94c3770b,// 222 PAY 179 

    0x86cb6e81,// 223 PAY 180 

    0xb8cd8e4f,// 224 PAY 181 

    0x719efe6c,// 225 PAY 182 

    0xa58cfe9b,// 226 PAY 183 

    0x04fd16fe,// 227 PAY 184 

    0xae28e062,// 228 PAY 185 

    0x80d1b8dc,// 229 PAY 186 

    0x7f2e3748,// 230 PAY 187 

    0xe2850d58,// 231 PAY 188 

    0x14dd0e3b,// 232 PAY 189 

    0xedd78376,// 233 PAY 190 

    0x13200c6c,// 234 PAY 191 

    0x8fae6e7e,// 235 PAY 192 

    0x8cf7c6d2,// 236 PAY 193 

    0xc2b7917b,// 237 PAY 194 

    0x3def94f5,// 238 PAY 195 

    0x64292426,// 239 PAY 196 

    0x69308a20,// 240 PAY 197 

    0xdbf5468a,// 241 PAY 198 

    0x11060698,// 242 PAY 199 

    0xbd98a504,// 243 PAY 200 

    0x32856b2a,// 244 PAY 201 

    0x82512337,// 245 PAY 202 

    0x631cd115,// 246 PAY 203 

    0xa3829d5f,// 247 PAY 204 

    0x7210f4ea,// 248 PAY 205 

    0xbbcd4b7f,// 249 PAY 206 

    0x921ec853,// 250 PAY 207 

    0xef599a2e,// 251 PAY 208 

    0xd8d32fc7,// 252 PAY 209 

    0x5c317332,// 253 PAY 210 

    0xdc0de57f,// 254 PAY 211 

    0x25589b45,// 255 PAY 212 

    0xe9408766,// 256 PAY 213 

    0xc538b8f5,// 257 PAY 214 

    0x643968e3,// 258 PAY 215 

    0x074dd7fe,// 259 PAY 216 

    0xbda0d605,// 260 PAY 217 

    0x951653e1,// 261 PAY 218 

    0xacfe4281,// 262 PAY 219 

    0x504095f8,// 263 PAY 220 

    0xcc2bf28e,// 264 PAY 221 

    0x807ad5d0,// 265 PAY 222 

    0x1f9ac667,// 266 PAY 223 

    0xc86dce25,// 267 PAY 224 

    0x546ce476,// 268 PAY 225 

    0xa4a0e82f,// 269 PAY 226 

    0xab0ee756,// 270 PAY 227 

    0xb1835b2f,// 271 PAY 228 

    0xce58dc28,// 272 PAY 229 

    0xf51a0485,// 273 PAY 230 

    0x5f2cfa9f,// 274 PAY 231 

    0xe52acb63,// 275 PAY 232 

    0x8bbab1db,// 276 PAY 233 

    0xa47f62e4,// 277 PAY 234 

    0xd8e451be,// 278 PAY 235 

    0x7a5dc3cc,// 279 PAY 236 

    0x21d01003,// 280 PAY 237 

    0x2bcc46a2,// 281 PAY 238 

    0xcdd1e62e,// 282 PAY 239 

    0x698ce63f,// 283 PAY 240 

    0xe12c6916,// 284 PAY 241 

    0x97815667,// 285 PAY 242 

    0x338d115d,// 286 PAY 243 

    0x5e39e127,// 287 PAY 244 

    0xf0137165,// 288 PAY 245 

    0x4c927e3a,// 289 PAY 246 

    0x6229763b,// 290 PAY 247 

    0x23e6729b,// 291 PAY 248 

    0xfc1baf54,// 292 PAY 249 

    0x0ec882e6,// 293 PAY 250 

    0x04dd45e9,// 294 PAY 251 

    0x8a00b89c,// 295 PAY 252 

    0xb467c55f,// 296 PAY 253 

    0x97cc827b,// 297 PAY 254 

    0x6cb49af5,// 298 PAY 255 

    0x9420ddff,// 299 PAY 256 

    0x483673d7,// 300 PAY 257 

    0x0292ca91,// 301 PAY 258 

    0x7ffe2232,// 302 PAY 259 

    0x0da3e6af,// 303 PAY 260 

    0x44fdd90f,// 304 PAY 261 

    0xfe80eda8,// 305 PAY 262 

    0xf8774d66,// 306 PAY 263 

    0x9b58d42f,// 307 PAY 264 

    0xe813eaf9,// 308 PAY 265 

    0x92925096,// 309 PAY 266 

    0xaa453f90,// 310 PAY 267 

    0x0d26fa07,// 311 PAY 268 

    0x2831ace5,// 312 PAY 269 

    0x7feae921,// 313 PAY 270 

    0x1956d12f,// 314 PAY 271 

    0x8b4e5dc6,// 315 PAY 272 

    0x74a7bb57,// 316 PAY 273 

    0xba364712,// 317 PAY 274 

    0x441bfbdb,// 318 PAY 275 

    0xecb157d8,// 319 PAY 276 

    0x28f3ca5a,// 320 PAY 277 

    0x603057fd,// 321 PAY 278 

    0x3350180e,// 322 PAY 279 

    0x66bb53d5,// 323 PAY 280 

    0x7c24ae5e,// 324 PAY 281 

    0x809e3794,// 325 PAY 282 

    0xe119fa65,// 326 PAY 283 

    0xd03fef41,// 327 PAY 284 

    0xfde217af,// 328 PAY 285 

    0xb227efb5,// 329 PAY 286 

    0x702de9fe,// 330 PAY 287 

    0x2533aa55,// 331 PAY 288 

    0xdc6e2666,// 332 PAY 289 

    0xb9a5911a,// 333 PAY 290 

    0xb36e2685,// 334 PAY 291 

    0xd5781efa,// 335 PAY 292 

    0xed9264db,// 336 PAY 293 

    0x0dd615e4,// 337 PAY 294 

    0xde487623,// 338 PAY 295 

    0xbb2a1fd7,// 339 PAY 296 

    0xa29f902a,// 340 PAY 297 

    0xb61666ac,// 341 PAY 298 

    0x40958204,// 342 PAY 299 

    0xa5f15d01,// 343 PAY 300 

    0x51c7a2cf,// 344 PAY 301 

    0x4451a5e4,// 345 PAY 302 

    0x81c2c4a6,// 346 PAY 303 

    0x20b66d68,// 347 PAY 304 

    0xb6fd4ab9,// 348 PAY 305 

    0xc5b1df31,// 349 PAY 306 

    0x7f597e6f,// 350 PAY 307 

    0x958ed55b,// 351 PAY 308 

    0x8283bf05,// 352 PAY 309 

    0x305b07d7,// 353 PAY 310 

    0xacc4ac7b,// 354 PAY 311 

    0x5a102c1a,// 355 PAY 312 

    0x2f317eca,// 356 PAY 313 

    0x476ebec1,// 357 PAY 314 

    0xc4cdeae4,// 358 PAY 315 

    0x9ce9379e,// 359 PAY 316 

    0x5ba5744c,// 360 PAY 317 

    0x2f9e8660,// 361 PAY 318 

    0x625abb80,// 362 PAY 319 

    0xf7c95a16,// 363 PAY 320 

    0x668984a0,// 364 PAY 321 

    0x6a0df220,// 365 PAY 322 

    0x174f2da4,// 366 PAY 323 

    0x230b3b7b,// 367 PAY 324 

    0xe875f6d4,// 368 PAY 325 

    0x2e6f0cb9,// 369 PAY 326 

    0x4df9b04f,// 370 PAY 327 

    0xff09c357,// 371 PAY 328 

    0xe542a357,// 372 PAY 329 

    0xc6d69e9c,// 373 PAY 330 

    0xd110b587,// 374 PAY 331 

    0x9939fa84,// 375 PAY 332 

    0x72d8be95,// 376 PAY 333 

    0x9409c231,// 377 PAY 334 

    0x1eb59329,// 378 PAY 335 

    0x50ebc1b2,// 379 PAY 336 

    0x3f67c727,// 380 PAY 337 

    0x15ebf306,// 381 PAY 338 

    0x811a1944,// 382 PAY 339 

    0x0ddffac3,// 383 PAY 340 

    0xd0b8c3fa,// 384 PAY 341 

    0xd9203f33,// 385 PAY 342 

    0x4126c8ab,// 386 PAY 343 

    0xacbc17b3,// 387 PAY 344 

    0x275bacc1,// 388 PAY 345 

    0x2bb5138e,// 389 PAY 346 

    0x720b2ebb,// 390 PAY 347 

    0xb39d2a08,// 391 PAY 348 

    0xe37889a8,// 392 PAY 349 

    0xac178152,// 393 PAY 350 

    0xcba8a454,// 394 PAY 351 

    0xaa6e06ea,// 395 PAY 352 

    0x3b9957bb,// 396 PAY 353 

    0x6e54741b,// 397 PAY 354 

    0x19668985,// 398 PAY 355 

    0xd6c80017,// 399 PAY 356 

    0x91794403,// 400 PAY 357 

    0xc4725b1e,// 401 PAY 358 

    0x394c3b03,// 402 PAY 359 

    0x22daa953,// 403 PAY 360 

    0xb8981fad,// 404 PAY 361 

    0x1eecb365,// 405 PAY 362 

    0x28f0f3e0,// 406 PAY 363 

    0x34136528,// 407 PAY 364 

    0x66c1b337,// 408 PAY 365 

    0x31d6adb1,// 409 PAY 366 

    0x6375eca1,// 410 PAY 367 

    0xbac0a31f,// 411 PAY 368 

    0xe95a25d8,// 412 PAY 369 

    0x5ae149c1,// 413 PAY 370 

    0x626ebe48,// 414 PAY 371 

    0xbfc2a4c0,// 415 PAY 372 

    0x4de886f3,// 416 PAY 373 

    0x403fc764,// 417 PAY 374 

    0x1df0dc02,// 418 PAY 375 

    0x820d411b,// 419 PAY 376 

    0xe4a43fa9,// 420 PAY 377 

    0x7be0d1ee,// 421 PAY 378 

    0xc0f29671,// 422 PAY 379 

    0x7a65f2f2,// 423 PAY 380 

    0xc1b2cab5,// 424 PAY 381 

    0x554f5dbf,// 425 PAY 382 

    0xa042c7e4,// 426 PAY 383 

    0x152cb3c8,// 427 PAY 384 

    0x0ce1de85,// 428 PAY 385 

    0x1bc2733f,// 429 PAY 386 

    0xa8b33c78,// 430 PAY 387 

    0x19186a7b,// 431 PAY 388 

    0x160ad993,// 432 PAY 389 

    0xcd7e5a53,// 433 PAY 390 

    0x10860e25,// 434 PAY 391 

    0xeb784f10,// 435 PAY 392 

    0x8b9ce717,// 436 PAY 393 

    0xd82fb8bf,// 437 PAY 394 

    0x227f3794,// 438 PAY 395 

    0xd9b0a02a,// 439 PAY 396 

    0xec98b5a1,// 440 PAY 397 

    0x0717eede,// 441 PAY 398 

    0x2039556c,// 442 PAY 399 

    0x136cf73a,// 443 PAY 400 

    0x9c1cb330,// 444 PAY 401 

    0x09b36b23,// 445 PAY 402 

    0x37633550,// 446 PAY 403 

    0xf1d2cdbf,// 447 PAY 404 

    0x6bb62cd6,// 448 PAY 405 

    0xf1b52bca,// 449 PAY 406 

    0x94c2fa72,// 450 PAY 407 

    0x777d6851,// 451 PAY 408 

    0x18fdc77d,// 452 PAY 409 

    0xb70d6978,// 453 PAY 410 

    0x42666066,// 454 PAY 411 

    0xf02b166f,// 455 PAY 412 

    0xf9792596,// 456 PAY 413 

    0xbac941b6,// 457 PAY 414 

    0x6b595863,// 458 PAY 415 

    0x9352c8b4,// 459 PAY 416 

    0x178ae6d2,// 460 PAY 417 

    0xc144aa6d,// 461 PAY 418 

    0x882a3745,// 462 PAY 419 

    0xe00ab5f4,// 463 PAY 420 

    0xe1300040,// 464 PAY 421 

    0xf1e5a1e3,// 465 PAY 422 

    0x4f3964a5,// 466 PAY 423 

    0x4b282b63,// 467 PAY 424 

    0x0ad39ddc,// 468 PAY 425 

    0x97cea0b2,// 469 PAY 426 

    0xaff4aec5,// 470 PAY 427 

    0x258ff127,// 471 PAY 428 

    0x6730ced8,// 472 PAY 429 

    0x9f964874,// 473 PAY 430 

    0x5e240f0d,// 474 PAY 431 

    0x5692f505,// 475 PAY 432 

    0x976ba2d1,// 476 PAY 433 

    0xa5973739,// 477 PAY 434 

    0xffcad24c,// 478 PAY 435 

    0xbac6aac8,// 479 PAY 436 

    0x1afa6510,// 480 PAY 437 

    0x65824008,// 481 PAY 438 

    0xf25af4ba,// 482 PAY 439 

    0x8af86ca7,// 483 PAY 440 

    0xdebfe2b8,// 484 PAY 441 

    0x49ebcba6,// 485 PAY 442 

    0xfe6cc425,// 486 PAY 443 

    0x577ec22c,// 487 PAY 444 

    0x762feadb,// 488 PAY 445 

    0x3ef15f1c,// 489 PAY 446 

    0xab39a1bc,// 490 PAY 447 

    0x7eafc247,// 491 PAY 448 

    0x8a60ec84,// 492 PAY 449 

    0x82e3947f,// 493 PAY 450 

    0x280933f1,// 494 PAY 451 

    0x559f3f0a,// 495 PAY 452 

    0x7a660f52,// 496 PAY 453 

    0x266cd26d,// 497 PAY 454 

/// STA is 1 words. 

/// STA num_pkts       : 51 

/// STA pkt_idx        : 53 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x45 

    0x00d44533 // 498 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 72 (0x48) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt66_tmpl[] = {
    0xb8010048,// 1 CCH   1 

/// ECH cache_idx      : 0x0a 

/// ECH pdu_tag        : 0x00 

    0x000a0000,// 2 ECH   1 

/// SCX is 17 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv !insert_icv !check_icv !sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x00000011,// 3 SCX   1 

    0x8084481d,// 4 SCX   2 

    0x00004344,// 5 SCX   3 

    0xfd097baa,// 6 SCX   4 

    0x1401f307,// 7 SCX   5 

    0x0e35b84d,// 8 SCX   6 

    0x232fe176,// 9 SCX   7 

    0xf579977e,// 10 SCX   8 

    0xa9f1e2ae,// 11 SCX   9 

    0x03b9050b,// 12 SCX  10 

    0x61a888e3,// 13 SCX  11 

    0xb032fd3c,// 14 SCX  12 

    0xf7c85129,// 15 SCX  13 

    0xfcfb860e,// 16 SCX  14 

    0xdd010728,// 17 SCX  15 

    0x04558d6d,// 18 SCX  16 

    0xb2577588,// 19 SCX  17 

/// BFD is 3 words. 

/// BFD tot_len        : 390 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 134 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 134 

/// BFD lencrypto      : 64 

/// BFD ofstcrypto     : 44 

/// BFD (ofst+len)cry  : 108 

/// BFD ofstiv         : 4 

/// BFD ofsticv        : 324 

    0x00000086,// 20 BFD   1 

    0x002c0040,// 21 BFD   2 

    0x01440004,// 22 BFD   3 

/// MFM is 5 words. 

/// MFM vldnibs        : 1e 

    0x1e009562,// 23 MFM   1 

    0xa6d8353e,// 24 MFM   2 

    0x91e2e261,// 25 MFM   3 

    0x83f45670,// 26 MFM   4 

    0x4c000000,// 27 MFM   5 

/// BDA is 99 words. 

/// BDA size     is 390 (0x186) 

/// BDA id       is 0xb717 

    0x0186b717,// 28 BDA   1 

/// PAY Generic Data size   : 390 byte(s) 

/// PAD Buffer Data Pad size   : 2 byte(s) 

    0x3ff158a8,// 29 PAY   1 

    0xe134f01d,// 30 PAY   2 

    0x51fd036b,// 31 PAY   3 

    0x803364d1,// 32 PAY   4 

    0xa0381744,// 33 PAY   5 

    0x96594988,// 34 PAY   6 

    0x0cead9c0,// 35 PAY   7 

    0x9f8f7033,// 36 PAY   8 

    0xa871c9bc,// 37 PAY   9 

    0x5655fc46,// 38 PAY  10 

    0x55cdbf54,// 39 PAY  11 

    0x478601c5,// 40 PAY  12 

    0x09b62fae,// 41 PAY  13 

    0x5b4d299e,// 42 PAY  14 

    0xbded2c5f,// 43 PAY  15 

    0x974c6f19,// 44 PAY  16 

    0x5b61d5c0,// 45 PAY  17 

    0x09acc003,// 46 PAY  18 

    0x44fd340b,// 47 PAY  19 

    0x47ba1a1e,// 48 PAY  20 

    0xf93b1544,// 49 PAY  21 

    0xe4c34850,// 50 PAY  22 

    0xf4dc1226,// 51 PAY  23 

    0x9614a7ae,// 52 PAY  24 

    0x46068b5b,// 53 PAY  25 

    0xe9ed9a70,// 54 PAY  26 

    0x4d7ac6cc,// 55 PAY  27 

    0x3f4888cb,// 56 PAY  28 

    0x56403f25,// 57 PAY  29 

    0x9e92171e,// 58 PAY  30 

    0xefa85b9b,// 59 PAY  31 

    0x326fe355,// 60 PAY  32 

    0x6ceb6e20,// 61 PAY  33 

    0x778cb3e7,// 62 PAY  34 

    0xd36b9772,// 63 PAY  35 

    0x602891c6,// 64 PAY  36 

    0xc207658d,// 65 PAY  37 

    0x3d212ead,// 66 PAY  38 

    0xa7d619f2,// 67 PAY  39 

    0x2616e394,// 68 PAY  40 

    0xbfe7ad24,// 69 PAY  41 

    0x8e6d0bac,// 70 PAY  42 

    0x5d00317d,// 71 PAY  43 

    0x6f48a1f7,// 72 PAY  44 

    0xe2ce266b,// 73 PAY  45 

    0x4ff4a92b,// 74 PAY  46 

    0x1cfd7fd4,// 75 PAY  47 

    0xcb2cba90,// 76 PAY  48 

    0x4251e762,// 77 PAY  49 

    0x6db075a9,// 78 PAY  50 

    0xd6bbc8af,// 79 PAY  51 

    0x177e284b,// 80 PAY  52 

    0x75d3d8bb,// 81 PAY  53 

    0x899938d6,// 82 PAY  54 

    0x1f374566,// 83 PAY  55 

    0xcd5d78ef,// 84 PAY  56 

    0x1ad7c31a,// 85 PAY  57 

    0xefcafd26,// 86 PAY  58 

    0x4c8b7e68,// 87 PAY  59 

    0xa2c38a6a,// 88 PAY  60 

    0xa9a9ba39,// 89 PAY  61 

    0x964d0e83,// 90 PAY  62 

    0x7281077b,// 91 PAY  63 

    0x33a7509b,// 92 PAY  64 

    0xc187ca2a,// 93 PAY  65 

    0x531e7512,// 94 PAY  66 

    0x9510a407,// 95 PAY  67 

    0x626a7b3b,// 96 PAY  68 

    0xa9069a01,// 97 PAY  69 

    0xf0f01534,// 98 PAY  70 

    0x19841239,// 99 PAY  71 

    0x55af6c9e,// 100 PAY  72 

    0x0b1c1f67,// 101 PAY  73 

    0xd3af9e49,// 102 PAY  74 

    0x52e5f12f,// 103 PAY  75 

    0xf3f3c25c,// 104 PAY  76 

    0xf315d661,// 105 PAY  77 

    0xd1f168eb,// 106 PAY  78 

    0x48e3c554,// 107 PAY  79 

    0x774c698d,// 108 PAY  80 

    0x5b576c5f,// 109 PAY  81 

    0x024d824e,// 110 PAY  82 

    0xd8be758a,// 111 PAY  83 

    0xa9eeb0b0,// 112 PAY  84 

    0xc13a386f,// 113 PAY  85 

    0xcbf81839,// 114 PAY  86 

    0x1202e478,// 115 PAY  87 

    0xe52ed787,// 116 PAY  88 

    0x5cd180cf,// 117 PAY  89 

    0xe7f4ff41,// 118 PAY  90 

    0x4afb77e7,// 119 PAY  91 

    0xfa6c750a,// 120 PAY  92 

    0x85e86d16,// 121 PAY  93 

    0xc3075d99,// 122 PAY  94 

    0xcfe904bd,// 123 PAY  95 

    0x3b09a799,// 124 PAY  96 

    0x74365f0b,// 125 PAY  97 

    0x53cd0000,// 126 PAY  98 

/// STA is 1 words. 

/// STA num_pkts       : 91 

/// STA pkt_idx        : 122 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x83 

    0x01e8835b // 127 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 96 (0x60) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt67_tmpl[] = {
    0xb8010060,// 1 CCH   1 

/// ECH cache_idx      : 0x09 

/// ECH pdu_tag        : 0x00 

    0x00090000,// 2 ECH   1 

/// SCX is 23 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x2 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000017,// 3 SCX   1 

    0x8085480a,// 4 SCX   2 

    0x000042c4,// 5 SCX   3 

    0xc939c3fd,// 6 SCX   4 

    0x1e093ebb,// 7 SCX   5 

    0x4a7c784d,// 8 SCX   6 

    0x68e38a76,// 9 SCX   7 

    0xacece110,// 10 SCX   8 

    0x10bc101e,// 11 SCX   9 

    0xf9d7e510,// 12 SCX  10 

    0x8ccdbe1d,// 13 SCX  11 

    0x5f747f5c,// 14 SCX  12 

    0x5f3b1b3d,// 15 SCX  13 

    0x360f846d,// 16 SCX  14 

    0xe5b47dbb,// 17 SCX  15 

    0x179dfed2,// 18 SCX  16 

    0x86954276,// 19 SCX  17 

    0xd4726524,// 20 SCX  18 

    0xf4c32e9e,// 21 SCX  19 

    0x244a0e0d,// 22 SCX  20 

    0x2402bdfe,// 23 SCX  21 

    0x7773feca,// 24 SCX  22 

    0xbd620155,// 25 SCX  23 

/// BFD is 3 words. 

/// BFD tot_len        : 548 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 505 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 505 

/// BFD lencrypto      : 416 

/// BFD ofstcrypto     : 84 

/// BFD (ofst+len)cry  : 500 

/// BFD ofstiv         : 40 

/// BFD ofsticv        : 516 

    0x000001f9,// 26 BFD   1 

    0x005401a0,// 27 BFD   2 

    0x02040028,// 28 BFD   3 

/// MFM is 4 words. 

/// MFM vldnibs        : 16 

    0x16004737,// 29 MFM   1 

    0x2d270c83,// 30 MFM   2 

    0x01c00678,// 31 MFM   3 

    0xdb000000,// 32 MFM   4 

/// BDA is 138 words. 

/// BDA size     is 548 (0x224) 

/// BDA id       is 0xa522 

    0x0224a522,// 33 BDA   1 

/// PAY Generic Data size   : 548 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0x46171e7e,// 34 PAY   1 

    0xa47bb997,// 35 PAY   2 

    0x3051d3bd,// 36 PAY   3 

    0x5c06709d,// 37 PAY   4 

    0xc46f8176,// 38 PAY   5 

    0x2492b0c5,// 39 PAY   6 

    0x9723028c,// 40 PAY   7 

    0x891ff451,// 41 PAY   8 

    0x1dccd13f,// 42 PAY   9 

    0x00eb2dd8,// 43 PAY  10 

    0x5ce548e0,// 44 PAY  11 

    0xb57fc470,// 45 PAY  12 

    0x1f5e45c0,// 46 PAY  13 

    0x0e3bd5b4,// 47 PAY  14 

    0x40f8c8c6,// 48 PAY  15 

    0x040b1128,// 49 PAY  16 

    0xd08ceee5,// 50 PAY  17 

    0x5ccb141d,// 51 PAY  18 

    0x6918058c,// 52 PAY  19 

    0x489f9869,// 53 PAY  20 

    0xe15f9111,// 54 PAY  21 

    0x79a5a017,// 55 PAY  22 

    0xab073fc2,// 56 PAY  23 

    0x567d9b7d,// 57 PAY  24 

    0xc16fdf20,// 58 PAY  25 

    0xc9efd330,// 59 PAY  26 

    0x5be7c397,// 60 PAY  27 

    0xb64eb260,// 61 PAY  28 

    0x06e60c9b,// 62 PAY  29 

    0x24c5164b,// 63 PAY  30 

    0x3b21f14d,// 64 PAY  31 

    0x61e2065e,// 65 PAY  32 

    0xc4b71cc8,// 66 PAY  33 

    0x67ee6949,// 67 PAY  34 

    0xfa9b0849,// 68 PAY  35 

    0xabbac92f,// 69 PAY  36 

    0x59d6688b,// 70 PAY  37 

    0x7f885aa7,// 71 PAY  38 

    0x84d6980f,// 72 PAY  39 

    0xe7ca1dfd,// 73 PAY  40 

    0x0d769163,// 74 PAY  41 

    0x7f7cd281,// 75 PAY  42 

    0xa2b4f133,// 76 PAY  43 

    0xaefadab2,// 77 PAY  44 

    0x939a5767,// 78 PAY  45 

    0x49537348,// 79 PAY  46 

    0x75c30bf7,// 80 PAY  47 

    0x3ef889df,// 81 PAY  48 

    0xfbab1752,// 82 PAY  49 

    0xddb8d388,// 83 PAY  50 

    0x5cfdbd86,// 84 PAY  51 

    0xcd8ae2ee,// 85 PAY  52 

    0x67a11675,// 86 PAY  53 

    0xded6401e,// 87 PAY  54 

    0xb33252e1,// 88 PAY  55 

    0x9ef3cc4e,// 89 PAY  56 

    0x4d879a21,// 90 PAY  57 

    0xfd042940,// 91 PAY  58 

    0xbda86380,// 92 PAY  59 

    0x37630461,// 93 PAY  60 

    0x235fc540,// 94 PAY  61 

    0xab82754d,// 95 PAY  62 

    0x5632cb63,// 96 PAY  63 

    0x819f08e3,// 97 PAY  64 

    0xbee12cc4,// 98 PAY  65 

    0x03fefe68,// 99 PAY  66 

    0xaf1686bf,// 100 PAY  67 

    0x63e168e1,// 101 PAY  68 

    0xe1fa9886,// 102 PAY  69 

    0x8ed24055,// 103 PAY  70 

    0x05e3e85a,// 104 PAY  71 

    0x6f9a8494,// 105 PAY  72 

    0x12dff99c,// 106 PAY  73 

    0x32c2696e,// 107 PAY  74 

    0xd844ee31,// 108 PAY  75 

    0x92e4a454,// 109 PAY  76 

    0x187f4534,// 110 PAY  77 

    0x17708237,// 111 PAY  78 

    0xa41520e4,// 112 PAY  79 

    0xde33a7b0,// 113 PAY  80 

    0x06b8de38,// 114 PAY  81 

    0xab1283f9,// 115 PAY  82 

    0x106e319c,// 116 PAY  83 

    0x7d736957,// 117 PAY  84 

    0x6d4e2488,// 118 PAY  85 

    0xdbd14015,// 119 PAY  86 

    0xcc3b805b,// 120 PAY  87 

    0xf3518e7f,// 121 PAY  88 

    0x488a7e52,// 122 PAY  89 

    0x2b6244d5,// 123 PAY  90 

    0xd538d9c3,// 124 PAY  91 

    0xd19c1c47,// 125 PAY  92 

    0x29a35f39,// 126 PAY  93 

    0xb1c67dc9,// 127 PAY  94 

    0xb0992838,// 128 PAY  95 

    0xc5e5443f,// 129 PAY  96 

    0x6256ef5b,// 130 PAY  97 

    0xa16e0054,// 131 PAY  98 

    0xea7b0815,// 132 PAY  99 

    0xb1da5934,// 133 PAY 100 

    0xa5fe801d,// 134 PAY 101 

    0x3f076d01,// 135 PAY 102 

    0xa5c8ea74,// 136 PAY 103 

    0xd9e047cd,// 137 PAY 104 

    0xc08b3f21,// 138 PAY 105 

    0x29caea71,// 139 PAY 106 

    0xf8fcb879,// 140 PAY 107 

    0x01af0e6e,// 141 PAY 108 

    0x4259d8e4,// 142 PAY 109 

    0x8d895e04,// 143 PAY 110 

    0xf0a83c2d,// 144 PAY 111 

    0xc423a593,// 145 PAY 112 

    0xb32bb402,// 146 PAY 113 

    0x4a668ebe,// 147 PAY 114 

    0xabb34f52,// 148 PAY 115 

    0xca07c3f4,// 149 PAY 116 

    0xccb71aca,// 150 PAY 117 

    0x61e785b1,// 151 PAY 118 

    0x7ccf2014,// 152 PAY 119 

    0x3cf5dd26,// 153 PAY 120 

    0x514daf3d,// 154 PAY 121 

    0x3ceef3b6,// 155 PAY 122 

    0x889710a2,// 156 PAY 123 

    0x67cb4065,// 157 PAY 124 

    0x14be8d1f,// 158 PAY 125 

    0x3b1920c3,// 159 PAY 126 

    0x26497a2e,// 160 PAY 127 

    0x3686955a,// 161 PAY 128 

    0x6b54016e,// 162 PAY 129 

    0x2e16e3cf,// 163 PAY 130 

    0x417e0d86,// 164 PAY 131 

    0xd2375ffc,// 165 PAY 132 

    0xf48292e3,// 166 PAY 133 

    0xf22d2879,// 167 PAY 134 

    0x8b344cbe,// 168 PAY 135 

    0x4fd3c65a,// 169 PAY 136 

    0xd1701901,// 170 PAY 137 

/// STA is 1 words. 

/// STA num_pkts       : 221 

/// STA pkt_idx        : 35 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xd4 

    0x008cd4dd // 171 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt68_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x00 

/// ECH pdu_tag        : 0x00 

    0x00000000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv !insert_icv !check_icv !sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x00000015,// 3 SCX   1 

    0x80864898,// 4 SCX   2 

    0x00004544,// 5 SCX   3 

    0x53f286fa,// 6 SCX   4 

    0xc972c1f7,// 7 SCX   5 

    0xfefe4c44,// 8 SCX   6 

    0x05e70119,// 9 SCX   7 

    0x723322cb,// 10 SCX   8 

    0x8bcd8063,// 11 SCX   9 

    0xd978be64,// 12 SCX  10 

    0x7ef4e82f,// 13 SCX  11 

    0xd5202638,// 14 SCX  12 

    0x26226b5a,// 15 SCX  13 

    0x6b03534e,// 16 SCX  14 

    0x7acf2baf,// 17 SCX  15 

    0x3de64a8e,// 18 SCX  16 

    0x2aa9a18b,// 19 SCX  17 

    0x1bd3bfba,// 20 SCX  18 

    0xf725afdf,// 21 SCX  19 

    0x73ed1d77,// 22 SCX  20 

    0x08230f0b,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 925 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 740 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 740 

/// BFD lencrypto      : 416 

/// BFD ofstcrypto     : 60 

/// BFD (ofst+len)cry  : 476 

/// BFD ofstiv         : 12 

/// BFD ofsticv        : 888 

    0x000002e4,// 24 BFD   1 

    0x003c01a0,// 25 BFD   2 

    0x0378000c,// 26 BFD   3 

/// MFM is 14 words. 

/// MFM vldnibs        : 66 

    0x6600a34a,// 27 MFM   1 

    0x228a232c,// 28 MFM   2 

    0x5a01dbdc,// 29 MFM   3 

    0xce3e359f,// 30 MFM   4 

    0x550f2bf8,// 31 MFM   5 

    0xb4b52e6a,// 32 MFM   6 

    0x5c8e534e,// 33 MFM   7 

    0xfccef143,// 34 MFM   8 

    0x27b9cbad,// 35 MFM   9 

    0x4f95a28b,// 36 MFM  10 

    0x605565cf,// 37 MFM  11 

    0xe4e9ae3b,// 38 MFM  12 

    0xfb72f69b,// 39 MFM  13 

    0x62000000,// 40 MFM  14 

/// BDA is 233 words. 

/// BDA size     is 925 (0x39d) 

/// BDA id       is 0x7985 

    0x039d7985,// 41 BDA   1 

/// PAY Generic Data size   : 925 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0xa80643cf,// 42 PAY   1 

    0xf59b8586,// 43 PAY   2 

    0x875480de,// 44 PAY   3 

    0xc8392996,// 45 PAY   4 

    0xa268d1de,// 46 PAY   5 

    0xcffb293f,// 47 PAY   6 

    0x0383b8b5,// 48 PAY   7 

    0xcd0f788a,// 49 PAY   8 

    0x46879c46,// 50 PAY   9 

    0x70c4d894,// 51 PAY  10 

    0x3020ce6b,// 52 PAY  11 

    0x6d49ff2e,// 53 PAY  12 

    0x22d33768,// 54 PAY  13 

    0xf079e834,// 55 PAY  14 

    0x6a862af7,// 56 PAY  15 

    0x9381ba1b,// 57 PAY  16 

    0xdb6b278f,// 58 PAY  17 

    0x426569e4,// 59 PAY  18 

    0x860dbb04,// 60 PAY  19 

    0x13453066,// 61 PAY  20 

    0xfb40027c,// 62 PAY  21 

    0x8c8d7249,// 63 PAY  22 

    0x338e8607,// 64 PAY  23 

    0x2a94592b,// 65 PAY  24 

    0x2e71d1d4,// 66 PAY  25 

    0x460a9175,// 67 PAY  26 

    0x26e399a1,// 68 PAY  27 

    0x2ac07ff6,// 69 PAY  28 

    0x5cca8441,// 70 PAY  29 

    0x2c87e97a,// 71 PAY  30 

    0xf145ce15,// 72 PAY  31 

    0xd5e4cb40,// 73 PAY  32 

    0xd04d1b28,// 74 PAY  33 

    0xb84a22cf,// 75 PAY  34 

    0x188528c6,// 76 PAY  35 

    0xfc230380,// 77 PAY  36 

    0xe364e5c7,// 78 PAY  37 

    0xa3d78d35,// 79 PAY  38 

    0x991e6e51,// 80 PAY  39 

    0x4685bbf4,// 81 PAY  40 

    0x78e4cbcb,// 82 PAY  41 

    0xd9f96c97,// 83 PAY  42 

    0xf865e2d7,// 84 PAY  43 

    0x90e14220,// 85 PAY  44 

    0x29e6d942,// 86 PAY  45 

    0x7cd8ea8c,// 87 PAY  46 

    0xf3746d83,// 88 PAY  47 

    0xd5ed456e,// 89 PAY  48 

    0xd564ec63,// 90 PAY  49 

    0xb34b3eb6,// 91 PAY  50 

    0x5414e4c3,// 92 PAY  51 

    0xdf696fac,// 93 PAY  52 

    0xe0dbe759,// 94 PAY  53 

    0x58d8ff7b,// 95 PAY  54 

    0xb07cc4af,// 96 PAY  55 

    0x31b13c4b,// 97 PAY  56 

    0x30553bf1,// 98 PAY  57 

    0x976116ac,// 99 PAY  58 

    0xb3beb995,// 100 PAY  59 

    0x28a897c6,// 101 PAY  60 

    0xe4cf2fef,// 102 PAY  61 

    0xd0e167a9,// 103 PAY  62 

    0x7e792fcf,// 104 PAY  63 

    0xff1776e4,// 105 PAY  64 

    0x0765a024,// 106 PAY  65 

    0xa7be5454,// 107 PAY  66 

    0xa634da26,// 108 PAY  67 

    0xf1b8ec8d,// 109 PAY  68 

    0x9ae9c3cd,// 110 PAY  69 

    0x6f39998e,// 111 PAY  70 

    0x028648d4,// 112 PAY  71 

    0x9950fe33,// 113 PAY  72 

    0xb9a49aaa,// 114 PAY  73 

    0xa2d7bd05,// 115 PAY  74 

    0xa2f286f4,// 116 PAY  75 

    0x91931695,// 117 PAY  76 

    0x857646a3,// 118 PAY  77 

    0xb5625881,// 119 PAY  78 

    0xa8bcb099,// 120 PAY  79 

    0x637e2eb9,// 121 PAY  80 

    0x340ddd93,// 122 PAY  81 

    0x42935cf5,// 123 PAY  82 

    0x88588604,// 124 PAY  83 

    0xd36ddf7b,// 125 PAY  84 

    0x1ffc7e3c,// 126 PAY  85 

    0x5def5430,// 127 PAY  86 

    0x5a4024f6,// 128 PAY  87 

    0xfe678e13,// 129 PAY  88 

    0x54cc5010,// 130 PAY  89 

    0xdae2c2c2,// 131 PAY  90 

    0x634e5d65,// 132 PAY  91 

    0xceada664,// 133 PAY  92 

    0xd1fafb7e,// 134 PAY  93 

    0xe90b7a41,// 135 PAY  94 

    0x114e7c56,// 136 PAY  95 

    0xf73412dc,// 137 PAY  96 

    0x4b261272,// 138 PAY  97 

    0x124e1eff,// 139 PAY  98 

    0xb5b09c28,// 140 PAY  99 

    0x0c236416,// 141 PAY 100 

    0x11f6e946,// 142 PAY 101 

    0x1de4de24,// 143 PAY 102 

    0x202979c5,// 144 PAY 103 

    0xcd589df4,// 145 PAY 104 

    0xd6afa813,// 146 PAY 105 

    0xd6169b79,// 147 PAY 106 

    0x0f895445,// 148 PAY 107 

    0xf2df5cc5,// 149 PAY 108 

    0x367bc7d0,// 150 PAY 109 

    0xf14b4fb4,// 151 PAY 110 

    0x64608504,// 152 PAY 111 

    0x25afe0c1,// 153 PAY 112 

    0xef9cd73d,// 154 PAY 113 

    0x23575cac,// 155 PAY 114 

    0x68a49482,// 156 PAY 115 

    0xcc5dee46,// 157 PAY 116 

    0x8f09dc0e,// 158 PAY 117 

    0x2284b836,// 159 PAY 118 

    0x71fbc18f,// 160 PAY 119 

    0x81ab79af,// 161 PAY 120 

    0xca0efd89,// 162 PAY 121 

    0x2c3568a9,// 163 PAY 122 

    0x7f9da731,// 164 PAY 123 

    0xafbd3865,// 165 PAY 124 

    0x60220cf6,// 166 PAY 125 

    0x7191ead8,// 167 PAY 126 

    0xf1778e43,// 168 PAY 127 

    0x54704fff,// 169 PAY 128 

    0x8886b4c6,// 170 PAY 129 

    0x87062bb0,// 171 PAY 130 

    0x16787071,// 172 PAY 131 

    0xee1fefb9,// 173 PAY 132 

    0x311fde05,// 174 PAY 133 

    0x699bda3c,// 175 PAY 134 

    0x7ebb60ae,// 176 PAY 135 

    0xd44c3cad,// 177 PAY 136 

    0xb8a9ea69,// 178 PAY 137 

    0xfd67a068,// 179 PAY 138 

    0xa89e6325,// 180 PAY 139 

    0x25c0aba8,// 181 PAY 140 

    0x7026efd2,// 182 PAY 141 

    0xb87c8ef0,// 183 PAY 142 

    0xadc41a98,// 184 PAY 143 

    0x90b1d040,// 185 PAY 144 

    0xcfd156d9,// 186 PAY 145 

    0x20598222,// 187 PAY 146 

    0x8553f289,// 188 PAY 147 

    0xb70d46d7,// 189 PAY 148 

    0x24fae6fd,// 190 PAY 149 

    0xc91c07f9,// 191 PAY 150 

    0xd7021beb,// 192 PAY 151 

    0x154e5022,// 193 PAY 152 

    0xd167a9c7,// 194 PAY 153 

    0xa7322074,// 195 PAY 154 

    0x92d5d6a2,// 196 PAY 155 

    0xaa9e64fd,// 197 PAY 156 

    0xc0b64a48,// 198 PAY 157 

    0xe466719a,// 199 PAY 158 

    0x7568733f,// 200 PAY 159 

    0x22670696,// 201 PAY 160 

    0x463d9c66,// 202 PAY 161 

    0x46e824ac,// 203 PAY 162 

    0xcfaf32cd,// 204 PAY 163 

    0x52728a83,// 205 PAY 164 

    0xda19917e,// 206 PAY 165 

    0xf8d782f7,// 207 PAY 166 

    0x1c9f370d,// 208 PAY 167 

    0xee2f8891,// 209 PAY 168 

    0xdc4dfa28,// 210 PAY 169 

    0x15d9a557,// 211 PAY 170 

    0xaf7747d0,// 212 PAY 171 

    0xa8b854f6,// 213 PAY 172 

    0x634aceac,// 214 PAY 173 

    0xcc4e6971,// 215 PAY 174 

    0x8c79c1f7,// 216 PAY 175 

    0x122a2bff,// 217 PAY 176 

    0xa2d6f5cd,// 218 PAY 177 

    0xa6046036,// 219 PAY 178 

    0xab05865d,// 220 PAY 179 

    0x2b5dc5f2,// 221 PAY 180 

    0xd24118ae,// 222 PAY 181 

    0xc89d1408,// 223 PAY 182 

    0x9f889d83,// 224 PAY 183 

    0xbfc95864,// 225 PAY 184 

    0xa85ad47e,// 226 PAY 185 

    0x00519353,// 227 PAY 186 

    0xf0f67131,// 228 PAY 187 

    0xe898f752,// 229 PAY 188 

    0x84b29145,// 230 PAY 189 

    0x89e395fb,// 231 PAY 190 

    0x12d12a40,// 232 PAY 191 

    0x3e3b5045,// 233 PAY 192 

    0x1b819aa9,// 234 PAY 193 

    0xdfdd3fb2,// 235 PAY 194 

    0xb038e4e7,// 236 PAY 195 

    0x4af1c2ce,// 237 PAY 196 

    0x3eaa5454,// 238 PAY 197 

    0x8d87c8fb,// 239 PAY 198 

    0x92c58333,// 240 PAY 199 

    0x62e166d8,// 241 PAY 200 

    0xaf5e09d1,// 242 PAY 201 

    0xab980f01,// 243 PAY 202 

    0x0e5498ba,// 244 PAY 203 

    0xf4dd4325,// 245 PAY 204 

    0x82de3936,// 246 PAY 205 

    0xd2a2cd20,// 247 PAY 206 

    0x389737ee,// 248 PAY 207 

    0x013f44e8,// 249 PAY 208 

    0x8f4c7f2f,// 250 PAY 209 

    0x9e9e7669,// 251 PAY 210 

    0x90eef5d1,// 252 PAY 211 

    0x911be171,// 253 PAY 212 

    0xd13e73d9,// 254 PAY 213 

    0xb39961b2,// 255 PAY 214 

    0xf40257f5,// 256 PAY 215 

    0xa1fa7760,// 257 PAY 216 

    0xa27593fe,// 258 PAY 217 

    0x1392fe83,// 259 PAY 218 

    0x6d70a643,// 260 PAY 219 

    0xc1f0288c,// 261 PAY 220 

    0x2f82e4ce,// 262 PAY 221 

    0x759df7db,// 263 PAY 222 

    0x55435e6d,// 264 PAY 223 

    0xe21488a8,// 265 PAY 224 

    0x726a3d6d,// 266 PAY 225 

    0x6b0f417b,// 267 PAY 226 

    0x6490ef49,// 268 PAY 227 

    0x435d6722,// 269 PAY 228 

    0x52294bf1,// 270 PAY 229 

    0x17eadfeb,// 271 PAY 230 

    0xf5e893e0,// 272 PAY 231 

    0xd6000000,// 273 PAY 232 

/// STA is 1 words. 

/// STA num_pkts       : 198 

/// STA pkt_idx        : 217 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x9d 

    0x03659dc6 // 274 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 80 (0x50) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt69_tmpl[] = {
    0xb8010050,// 1 CCH   1 

/// ECH cache_idx      : 0x04 

/// ECH pdu_tag        : 0x00 

    0x00040000,// 2 ECH   1 

/// SCX is 19 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv !insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000013,// 3 SCX   1 

    0x808148ec,// 4 SCX   2 

    0x00001500,// 5 SCX   3 

    0x71aec469,// 6 SCX   4 

    0xb41e5663,// 7 SCX   5 

    0xfbc25b15,// 8 SCX   6 

    0x391e2e24,// 9 SCX   7 

    0x29024265,// 10 SCX   8 

    0x0fa9a5c8,// 11 SCX   9 

    0x4fda150d,// 12 SCX  10 

    0xb8b7374b,// 13 SCX  11 

    0x9ba67fb5,// 14 SCX  12 

    0x1a42cc87,// 15 SCX  13 

    0x45a8e699,// 16 SCX  14 

    0x76258abd,// 17 SCX  15 

    0x9a367729,// 18 SCX  16 

    0x50f73d9d,// 19 SCX  17 

    0x0bc24397,// 20 SCX  18 

    0xc2406e7b,// 21 SCX  19 

/// BFD is 3 words. 

/// BFD tot_len        : 1001 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 700 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 700 

/// BFD lencrypto      : 432 

/// BFD ofstcrypto     : 264 

/// BFD (ofst+len)cry  : 696 

/// BFD ofstiv         : 108 

/// BFD ofsticv        : 728 

    0x000002bc,// 22 BFD   1 

    0x010801b0,// 23 BFD   2 

    0x02d8006c,// 24 BFD   3 

/// MFM is 9 words. 

/// MFM vldnibs        : 42 

    0x42001a2e,// 25 MFM   1 

    0x961877e4,// 26 MFM   2 

    0x22fe1ce2,// 27 MFM   3 

    0x83da98b3,// 28 MFM   4 

    0xf52a87fb,// 29 MFM   5 

    0xaa2e0f92,// 30 MFM   6 

    0xcd13f89c,// 31 MFM   7 

    0xac25d42e,// 32 MFM   8 

    0xbdf83900,// 33 MFM   9 

/// BDA is 252 words. 

/// BDA size     is 1001 (0x3e9) 

/// BDA id       is 0xe834 

    0x03e9e834,// 34 BDA   1 

/// PAY Generic Data size   : 1001 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0xe0cbd582,// 35 PAY   1 

    0x899f358b,// 36 PAY   2 

    0x77287992,// 37 PAY   3 

    0x9a8be002,// 38 PAY   4 

    0x7ef280e4,// 39 PAY   5 

    0xff1926ab,// 40 PAY   6 

    0xd241b86e,// 41 PAY   7 

    0xb277cacc,// 42 PAY   8 

    0x23b7182c,// 43 PAY   9 

    0xab05adc2,// 44 PAY  10 

    0xf6af014a,// 45 PAY  11 

    0xe8773a15,// 46 PAY  12 

    0xa76917f3,// 47 PAY  13 

    0x370d0225,// 48 PAY  14 

    0x224b76f1,// 49 PAY  15 

    0xec70922d,// 50 PAY  16 

    0x03f03973,// 51 PAY  17 

    0x69e0c98e,// 52 PAY  18 

    0xa5b11733,// 53 PAY  19 

    0xfd325efb,// 54 PAY  20 

    0xd6103059,// 55 PAY  21 

    0x7265d6bf,// 56 PAY  22 

    0xf066d8ef,// 57 PAY  23 

    0x0e39ee4d,// 58 PAY  24 

    0x8190daff,// 59 PAY  25 

    0x21880f02,// 60 PAY  26 

    0xbeda5f6a,// 61 PAY  27 

    0x1e4bfade,// 62 PAY  28 

    0x5b34237f,// 63 PAY  29 

    0xf9681429,// 64 PAY  30 

    0x71e81557,// 65 PAY  31 

    0x72239c35,// 66 PAY  32 

    0x5832f0e4,// 67 PAY  33 

    0x79d8b242,// 68 PAY  34 

    0x408f8288,// 69 PAY  35 

    0xbcc16df5,// 70 PAY  36 

    0x75ceb821,// 71 PAY  37 

    0x0b76d7c7,// 72 PAY  38 

    0x0affc07a,// 73 PAY  39 

    0x65358d8d,// 74 PAY  40 

    0xc46b0ac7,// 75 PAY  41 

    0x14462f43,// 76 PAY  42 

    0x836bc9b7,// 77 PAY  43 

    0x94067df0,// 78 PAY  44 

    0x53cf69e6,// 79 PAY  45 

    0x14cd8886,// 80 PAY  46 

    0xfe258da3,// 81 PAY  47 

    0xa3938772,// 82 PAY  48 

    0x6e5bfae0,// 83 PAY  49 

    0x7943758a,// 84 PAY  50 

    0x9143ef99,// 85 PAY  51 

    0x1bb70b28,// 86 PAY  52 

    0x69c23c78,// 87 PAY  53 

    0x13bde055,// 88 PAY  54 

    0x01b1b7d0,// 89 PAY  55 

    0xdd16643e,// 90 PAY  56 

    0x35e24993,// 91 PAY  57 

    0x9e2097a8,// 92 PAY  58 

    0x2aefc1bc,// 93 PAY  59 

    0xe83d4106,// 94 PAY  60 

    0x83ee2a62,// 95 PAY  61 

    0xef970178,// 96 PAY  62 

    0x8838ad4a,// 97 PAY  63 

    0x7c99fd4a,// 98 PAY  64 

    0x40e62d81,// 99 PAY  65 

    0xb74a9ad3,// 100 PAY  66 

    0x750788c9,// 101 PAY  67 

    0xcd9a57de,// 102 PAY  68 

    0xd240b21e,// 103 PAY  69 

    0x329403b3,// 104 PAY  70 

    0x7ca746fb,// 105 PAY  71 

    0xf0ad5fac,// 106 PAY  72 

    0xbe662e99,// 107 PAY  73 

    0x06e377f8,// 108 PAY  74 

    0xd252a347,// 109 PAY  75 

    0x7f8e144d,// 110 PAY  76 

    0x9c223d6e,// 111 PAY  77 

    0x3ccbc262,// 112 PAY  78 

    0xab0671d5,// 113 PAY  79 

    0xc59712c3,// 114 PAY  80 

    0xcecadee4,// 115 PAY  81 

    0x96205ce2,// 116 PAY  82 

    0x5852bc25,// 117 PAY  83 

    0x00ff9c20,// 118 PAY  84 

    0xf5aa18db,// 119 PAY  85 

    0x9a9c02b0,// 120 PAY  86 

    0x77bed297,// 121 PAY  87 

    0x815c941e,// 122 PAY  88 

    0x6d7d9c29,// 123 PAY  89 

    0x0ffb5751,// 124 PAY  90 

    0xe37c0aa1,// 125 PAY  91 

    0x04691430,// 126 PAY  92 

    0x84012f9c,// 127 PAY  93 

    0x3df83cba,// 128 PAY  94 

    0xccebff6d,// 129 PAY  95 

    0xce03eb2d,// 130 PAY  96 

    0xa662188c,// 131 PAY  97 

    0xbcb58b3e,// 132 PAY  98 

    0x2a7eb89a,// 133 PAY  99 

    0xc8e1a7ee,// 134 PAY 100 

    0xfdffc2b9,// 135 PAY 101 

    0x79e35e03,// 136 PAY 102 

    0x688d41db,// 137 PAY 103 

    0x027b2b4c,// 138 PAY 104 

    0x8ebe80ff,// 139 PAY 105 

    0x9ed784ee,// 140 PAY 106 

    0xda9caacd,// 141 PAY 107 

    0x133b0b78,// 142 PAY 108 

    0x309b8548,// 143 PAY 109 

    0xc2b2e946,// 144 PAY 110 

    0x5abe3825,// 145 PAY 111 

    0xd0124cdc,// 146 PAY 112 

    0x4ded46df,// 147 PAY 113 

    0xffdebb67,// 148 PAY 114 

    0xb9149c31,// 149 PAY 115 

    0x301d9f49,// 150 PAY 116 

    0x01381165,// 151 PAY 117 

    0xd0bce6e4,// 152 PAY 118 

    0xb7962b3b,// 153 PAY 119 

    0x6734da35,// 154 PAY 120 

    0xf31e9ee0,// 155 PAY 121 

    0xb7a7ebb8,// 156 PAY 122 

    0x00697584,// 157 PAY 123 

    0xb6ea63c2,// 158 PAY 124 

    0xb8851085,// 159 PAY 125 

    0xea01b3b0,// 160 PAY 126 

    0x45a2480f,// 161 PAY 127 

    0xa653c19a,// 162 PAY 128 

    0xdda46c0f,// 163 PAY 129 

    0xdd7d03f2,// 164 PAY 130 

    0x5ac3fb75,// 165 PAY 131 

    0xa897b660,// 166 PAY 132 

    0x80eddc71,// 167 PAY 133 

    0x4700d599,// 168 PAY 134 

    0x0ccdcf56,// 169 PAY 135 

    0x091e3165,// 170 PAY 136 

    0x6b08bc74,// 171 PAY 137 

    0xcdfa7092,// 172 PAY 138 

    0xe12c32c7,// 173 PAY 139 

    0x9e0b0d1f,// 174 PAY 140 

    0x9c45fc1e,// 175 PAY 141 

    0x34a4f2b6,// 176 PAY 142 

    0xe4f7c907,// 177 PAY 143 

    0xa5a2ed66,// 178 PAY 144 

    0xd4060169,// 179 PAY 145 

    0x1946f563,// 180 PAY 146 

    0x178e766d,// 181 PAY 147 

    0xd6d9f757,// 182 PAY 148 

    0x29de5828,// 183 PAY 149 

    0x2f2fe6ab,// 184 PAY 150 

    0x171f9e7c,// 185 PAY 151 

    0x19d181b0,// 186 PAY 152 

    0x6c03dd90,// 187 PAY 153 

    0xb430c00c,// 188 PAY 154 

    0x76409b43,// 189 PAY 155 

    0x70593a24,// 190 PAY 156 

    0x34f3463f,// 191 PAY 157 

    0x40f0288e,// 192 PAY 158 

    0x3241df6d,// 193 PAY 159 

    0x5efc3cdb,// 194 PAY 160 

    0xc3529927,// 195 PAY 161 

    0xb13395e4,// 196 PAY 162 

    0x96073f5f,// 197 PAY 163 

    0x92d93724,// 198 PAY 164 

    0x8751f64d,// 199 PAY 165 

    0xe514e364,// 200 PAY 166 

    0x107bf499,// 201 PAY 167 

    0xd5b99cc5,// 202 PAY 168 

    0x0ffaf311,// 203 PAY 169 

    0xadc98f52,// 204 PAY 170 

    0x11fcaca2,// 205 PAY 171 

    0xdbf12f5d,// 206 PAY 172 

    0x6e4dd371,// 207 PAY 173 

    0x6903b1cd,// 208 PAY 174 

    0x488a4e58,// 209 PAY 175 

    0x5cc51821,// 210 PAY 176 

    0x821767e8,// 211 PAY 177 

    0x9e3953e3,// 212 PAY 178 

    0x5f74da4d,// 213 PAY 179 

    0x76263571,// 214 PAY 180 

    0xbf462c2e,// 215 PAY 181 

    0xe7e6aeea,// 216 PAY 182 

    0xbaef91cd,// 217 PAY 183 

    0x8764c22f,// 218 PAY 184 

    0x37642ab5,// 219 PAY 185 

    0xf99396c1,// 220 PAY 186 

    0x3f9b68f4,// 221 PAY 187 

    0x07d06c73,// 222 PAY 188 

    0x1cf306aa,// 223 PAY 189 

    0xf33b3c4b,// 224 PAY 190 

    0xce1851fe,// 225 PAY 191 

    0x98044f00,// 226 PAY 192 

    0x8f51c7a5,// 227 PAY 193 

    0xfdf461a8,// 228 PAY 194 

    0x818108f1,// 229 PAY 195 

    0xabf7dd2d,// 230 PAY 196 

    0xb66cbfd2,// 231 PAY 197 

    0x449a5c9d,// 232 PAY 198 

    0x20042617,// 233 PAY 199 

    0xac075975,// 234 PAY 200 

    0x53cdae0e,// 235 PAY 201 

    0xc4bb1c38,// 236 PAY 202 

    0x881e13a2,// 237 PAY 203 

    0xeb850728,// 238 PAY 204 

    0xce7a7577,// 239 PAY 205 

    0xff981773,// 240 PAY 206 

    0x3dd24e80,// 241 PAY 207 

    0x92df9fe7,// 242 PAY 208 

    0xab22d160,// 243 PAY 209 

    0xa4500997,// 244 PAY 210 

    0x93535ef4,// 245 PAY 211 

    0x31b37ca3,// 246 PAY 212 

    0xaf8633d3,// 247 PAY 213 

    0x4fc3bc01,// 248 PAY 214 

    0x9ee538a3,// 249 PAY 215 

    0x28c621b9,// 250 PAY 216 

    0x09a89d27,// 251 PAY 217 

    0xde451940,// 252 PAY 218 

    0xf3e0e9db,// 253 PAY 219 

    0xeab308c7,// 254 PAY 220 

    0x3f454e35,// 255 PAY 221 

    0xf1e3d20d,// 256 PAY 222 

    0x803d2386,// 257 PAY 223 

    0x67d61b83,// 258 PAY 224 

    0x384bdbeb,// 259 PAY 225 

    0xf472a74b,// 260 PAY 226 

    0x325b01b5,// 261 PAY 227 

    0xf574cc3a,// 262 PAY 228 

    0x7e9a3c27,// 263 PAY 229 

    0xbece69ff,// 264 PAY 230 

    0x9502f31c,// 265 PAY 231 

    0x02c84a34,// 266 PAY 232 

    0x503b3557,// 267 PAY 233 

    0xc753a40b,// 268 PAY 234 

    0x77bdc6b6,// 269 PAY 235 

    0xe1979a55,// 270 PAY 236 

    0xfbfedba7,// 271 PAY 237 

    0x14dc3fec,// 272 PAY 238 

    0xf4d74a73,// 273 PAY 239 

    0xced3855b,// 274 PAY 240 

    0x1dc6c491,// 275 PAY 241 

    0xc9aa6366,// 276 PAY 242 

    0x459f3af9,// 277 PAY 243 

    0xb61c1b52,// 278 PAY 244 

    0x9fe39dee,// 279 PAY 245 

    0x2268b24e,// 280 PAY 246 

    0x04f85423,// 281 PAY 247 

    0x4a155942,// 282 PAY 248 

    0x4398f0f6,// 283 PAY 249 

    0x0eb7bdc8,// 284 PAY 250 

    0xa5000000,// 285 PAY 251 

/// STA is 1 words. 

/// STA num_pkts       : 24 

/// STA pkt_idx        : 247 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xed 

    0x03dded18 // 286 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt70_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x04 

/// ECH pdu_tag        : 0x00 

    0x00040000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000019,// 3 SCX   1 

    0x809248c3,// 4 SCX   2 

    0x000063c2,// 5 SCX   3 

    0x4a8aaee1,// 6 SCX   4 

    0xbe65b87c,// 7 SCX   5 

    0x456705fe,// 8 SCX   6 

    0x3390247f,// 9 SCX   7 

    0xf80e910a,// 10 SCX   8 

    0xb7e3a781,// 11 SCX   9 

    0xb1592764,// 12 SCX  10 

    0x691c59f0,// 13 SCX  11 

    0xef92cbdc,// 14 SCX  12 

    0x858caf69,// 15 SCX  13 

    0x0e0cd394,// 16 SCX  14 

    0xe2ccc261,// 17 SCX  15 

    0xfa0a6498,// 18 SCX  16 

    0xac76feac,// 19 SCX  17 

    0x336c033d,// 20 SCX  18 

    0x6ade1c84,// 21 SCX  19 

    0x1e1a6e47,// 22 SCX  20 

    0x99e6b271,// 23 SCX  21 

    0xd7e82654,// 24 SCX  22 

    0xa9fe612f,// 25 SCX  23 

    0x56940dff,// 26 SCX  24 

    0x7132332d,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 171 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 68 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 68 

/// BFD lencrypto      : 4 

/// BFD ofstcrypto     : 40 

/// BFD (ofst+len)cry  : 44 

/// BFD ofstiv         : 20 

/// BFD ofsticv        : 72 

    0x00000044,// 28 BFD   1 

    0x00280004,// 29 BFD   2 

    0x00480014,// 30 BFD   3 

/// MFM is 3 words. 

/// MFM vldnibs        : 10 

    0x10000ec7,// 31 MFM   1 

    0x7e7328bc,// 32 MFM   2 

    0x47c00000,// 33 MFM   3 

/// BDA is 44 words. 

/// BDA size     is 171 (0xab) 

/// BDA id       is 0x8e57 

    0x00ab8e57,// 34 BDA   1 

/// PAY Generic Data size   : 171 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0x1cbedd36,// 35 PAY   1 

    0x6a6e0d7f,// 36 PAY   2 

    0x6761ff41,// 37 PAY   3 

    0x5f357407,// 38 PAY   4 

    0x31d98b7e,// 39 PAY   5 

    0x0607cb12,// 40 PAY   6 

    0xcdfcdc7d,// 41 PAY   7 

    0xb7ba3106,// 42 PAY   8 

    0x094cc94e,// 43 PAY   9 

    0x0810326a,// 44 PAY  10 

    0x5e6e257e,// 45 PAY  11 

    0x2c98545b,// 46 PAY  12 

    0xfea1d8fb,// 47 PAY  13 

    0x8dd10c4f,// 48 PAY  14 

    0x1cd86ae7,// 49 PAY  15 

    0x42eb08e4,// 50 PAY  16 

    0x3677b8d9,// 51 PAY  17 

    0x0ad6d40d,// 52 PAY  18 

    0xa8ed0fea,// 53 PAY  19 

    0x204e6612,// 54 PAY  20 

    0x84debfec,// 55 PAY  21 

    0x6c12ba9f,// 56 PAY  22 

    0x6d9b0c72,// 57 PAY  23 

    0x1e6fe4c7,// 58 PAY  24 

    0x7e4bb708,// 59 PAY  25 

    0x5da758f6,// 60 PAY  26 

    0x4a3a488e,// 61 PAY  27 

    0x3a2621c9,// 62 PAY  28 

    0xd2fed722,// 63 PAY  29 

    0xa3514fc2,// 64 PAY  30 

    0xac4b4043,// 65 PAY  31 

    0x48bd84fd,// 66 PAY  32 

    0xda4020bd,// 67 PAY  33 

    0xb30fb395,// 68 PAY  34 

    0x1a399574,// 69 PAY  35 

    0x977c1f7d,// 70 PAY  36 

    0x6fe580be,// 71 PAY  37 

    0x8f39299c,// 72 PAY  38 

    0xc98ea1eb,// 73 PAY  39 

    0x7d34a112,// 74 PAY  40 

    0x04bee801,// 75 PAY  41 

    0x70fe27f1,// 76 PAY  42 

    0x3fd01f00,// 77 PAY  43 

/// STA is 1 words. 

/// STA num_pkts       : 20 

/// STA pkt_idx        : 132 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x13 

    0x02111314 // 78 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt71_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x09 

/// ECH pdu_tag        : 0x00 

    0x00090000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv !insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000015,// 3 SCX   1 

    0x808448b2,// 4 SCX   2 

    0x000001c4,// 5 SCX   3 

    0xf2686228,// 6 SCX   4 

    0xd0c46652,// 7 SCX   5 

    0xc4b7899b,// 8 SCX   6 

    0xfe6d5c66,// 9 SCX   7 

    0xac0d13c9,// 10 SCX   8 

    0xb3b0dbf0,// 11 SCX   9 

    0xfd0aa8cd,// 12 SCX  10 

    0x5803ee5d,// 13 SCX  11 

    0xf94c15c6,// 14 SCX  12 

    0x86e1176e,// 15 SCX  13 

    0xeebe293f,// 16 SCX  14 

    0x1706710b,// 17 SCX  15 

    0xeaee0523,// 18 SCX  16 

    0x9ab6cb36,// 19 SCX  17 

    0xeaaba274,// 20 SCX  18 

    0x918e7422,// 21 SCX  19 

    0xaa7b3aa3,// 22 SCX  20 

    0xfe63e2cf,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1919 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 424 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 424 

/// BFD lencrypto      : 272 

/// BFD ofstcrypto     : 152 

/// BFD (ofst+len)cry  : 424 

/// BFD ofstiv         : 32 

/// BFD ofsticv        : 964 

    0x000001a8,// 24 BFD   1 

    0x00980110,// 25 BFD   2 

    0x03c40020,// 26 BFD   3 

/// MFM is 12 words. 

/// MFM vldnibs        : 59 

    0x5900b16c,// 27 MFM   1 

    0xe0ca58be,// 28 MFM   2 

    0xcd4d5e55,// 29 MFM   3 

    0xd68628b0,// 30 MFM   4 

    0x6d0e0fc4,// 31 MFM   5 

    0x2c495dce,// 32 MFM   6 

    0x6374fe87,// 33 MFM   7 

    0x60854bb8,// 34 MFM   8 

    0xe057b2c1,// 35 MFM   9 

    0xebbab592,// 36 MFM  10 

    0x5f870981,// 37 MFM  11 

    0x8284c000,// 38 MFM  12 

/// BDA is 481 words. 

/// BDA size     is 1919 (0x77f) 

/// BDA id       is 0xc9c9 

    0x077fc9c9,// 39 BDA   1 

/// PAY Generic Data size   : 1919 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0x0790e05e,// 40 PAY   1 

    0x0c3902ea,// 41 PAY   2 

    0x676a4738,// 42 PAY   3 

    0xc84002a0,// 43 PAY   4 

    0xdf770a3c,// 44 PAY   5 

    0x4a26abc6,// 45 PAY   6 

    0x13c8bf28,// 46 PAY   7 

    0x8444d2a1,// 47 PAY   8 

    0x49939dd8,// 48 PAY   9 

    0xc97e9961,// 49 PAY  10 

    0xbab85138,// 50 PAY  11 

    0x8a07b77b,// 51 PAY  12 

    0x5603aac4,// 52 PAY  13 

    0x7a4062e3,// 53 PAY  14 

    0xa73abf15,// 54 PAY  15 

    0x67ce8cb2,// 55 PAY  16 

    0x49fb5cc3,// 56 PAY  17 

    0xdf0f087b,// 57 PAY  18 

    0xc03460f3,// 58 PAY  19 

    0xfe3b6f01,// 59 PAY  20 

    0x4bbb968d,// 60 PAY  21 

    0x6818f886,// 61 PAY  22 

    0x5bb26ab2,// 62 PAY  23 

    0x6356c1a5,// 63 PAY  24 

    0x1bd9f2aa,// 64 PAY  25 

    0xbf7351c0,// 65 PAY  26 

    0xd950425b,// 66 PAY  27 

    0x3d1d7045,// 67 PAY  28 

    0x8f55fa0f,// 68 PAY  29 

    0xc01e8a2c,// 69 PAY  30 

    0x022e8f97,// 70 PAY  31 

    0xd757e94b,// 71 PAY  32 

    0x50bd56e3,// 72 PAY  33 

    0x3aa199b1,// 73 PAY  34 

    0x84d7fb12,// 74 PAY  35 

    0x24aadf41,// 75 PAY  36 

    0x48e14b14,// 76 PAY  37 

    0x150a5ce7,// 77 PAY  38 

    0x834a0358,// 78 PAY  39 

    0x01943d88,// 79 PAY  40 

    0x906e0c68,// 80 PAY  41 

    0xa4ec7c47,// 81 PAY  42 

    0x0156a5ee,// 82 PAY  43 

    0x65f4da33,// 83 PAY  44 

    0xe8086cf4,// 84 PAY  45 

    0x007b8438,// 85 PAY  46 

    0x4ef535c3,// 86 PAY  47 

    0xa08cf64d,// 87 PAY  48 

    0xfbc05e09,// 88 PAY  49 

    0x5df11324,// 89 PAY  50 

    0x631ed388,// 90 PAY  51 

    0x5d2102cc,// 91 PAY  52 

    0xb1b5e045,// 92 PAY  53 

    0xa5c9eb0f,// 93 PAY  54 

    0x14c3883b,// 94 PAY  55 

    0x26d882a7,// 95 PAY  56 

    0x66d7eb9b,// 96 PAY  57 

    0xb3071fb7,// 97 PAY  58 

    0xc1a3b1fa,// 98 PAY  59 

    0x2595a171,// 99 PAY  60 

    0x928316f4,// 100 PAY  61 

    0x7560b713,// 101 PAY  62 

    0xec1687ea,// 102 PAY  63 

    0x9a114278,// 103 PAY  64 

    0xd6198c07,// 104 PAY  65 

    0x13c27f1a,// 105 PAY  66 

    0x4a1f9f88,// 106 PAY  67 

    0xae160c51,// 107 PAY  68 

    0xc0a3ec1d,// 108 PAY  69 

    0x3a82d44b,// 109 PAY  70 

    0x29c269c5,// 110 PAY  71 

    0xcd1a2326,// 111 PAY  72 

    0x6769937c,// 112 PAY  73 

    0x5206a327,// 113 PAY  74 

    0x23626dde,// 114 PAY  75 

    0xb05d0043,// 115 PAY  76 

    0xa8c60262,// 116 PAY  77 

    0x9fd4c68d,// 117 PAY  78 

    0x6f7bc1a4,// 118 PAY  79 

    0x68a57d67,// 119 PAY  80 

    0x9297f366,// 120 PAY  81 

    0x36688e80,// 121 PAY  82 

    0x67fbe8fb,// 122 PAY  83 

    0xe25065e1,// 123 PAY  84 

    0xf39a0339,// 124 PAY  85 

    0x633cf61c,// 125 PAY  86 

    0x40ac4f06,// 126 PAY  87 

    0x55de6a7b,// 127 PAY  88 

    0x8896009a,// 128 PAY  89 

    0xe5076738,// 129 PAY  90 

    0x2749be72,// 130 PAY  91 

    0x1d113873,// 131 PAY  92 

    0x5c73bd1c,// 132 PAY  93 

    0x2bbf0676,// 133 PAY  94 

    0x48f47007,// 134 PAY  95 

    0x314507da,// 135 PAY  96 

    0xcec3ee87,// 136 PAY  97 

    0x27930e85,// 137 PAY  98 

    0xdd9c65de,// 138 PAY  99 

    0xaad204fd,// 139 PAY 100 

    0xf822357f,// 140 PAY 101 

    0x4974d979,// 141 PAY 102 

    0x6858cb05,// 142 PAY 103 

    0x2134446d,// 143 PAY 104 

    0x76188587,// 144 PAY 105 

    0x0138091e,// 145 PAY 106 

    0xa1558c42,// 146 PAY 107 

    0x90f0e0a6,// 147 PAY 108 

    0xb1b0513f,// 148 PAY 109 

    0xbd4ef02b,// 149 PAY 110 

    0xeecb15d6,// 150 PAY 111 

    0x53cccbb2,// 151 PAY 112 

    0x1213de38,// 152 PAY 113 

    0xb5d3f8f4,// 153 PAY 114 

    0x9530499a,// 154 PAY 115 

    0xb83f7e27,// 155 PAY 116 

    0xbb52d86e,// 156 PAY 117 

    0x084b0295,// 157 PAY 118 

    0x0e22523e,// 158 PAY 119 

    0x3fc7f8dc,// 159 PAY 120 

    0x55d3a3de,// 160 PAY 121 

    0x63f29116,// 161 PAY 122 

    0x3767f3ac,// 162 PAY 123 

    0x1fe2d3d0,// 163 PAY 124 

    0x14f7a05a,// 164 PAY 125 

    0xb35d1c4e,// 165 PAY 126 

    0x90c04c7b,// 166 PAY 127 

    0x550fbac0,// 167 PAY 128 

    0x9ec983a6,// 168 PAY 129 

    0xe9341f9a,// 169 PAY 130 

    0x48e5fcbf,// 170 PAY 131 

    0xc784808d,// 171 PAY 132 

    0x58ad39bd,// 172 PAY 133 

    0x5c37a590,// 173 PAY 134 

    0xc28b6b3e,// 174 PAY 135 

    0x8175e897,// 175 PAY 136 

    0xc72330d2,// 176 PAY 137 

    0x480c3e2c,// 177 PAY 138 

    0x7b56e608,// 178 PAY 139 

    0x5f0f760a,// 179 PAY 140 

    0x3e29a181,// 180 PAY 141 

    0x0b6ea9c3,// 181 PAY 142 

    0x30d2fc2c,// 182 PAY 143 

    0x63392f72,// 183 PAY 144 

    0x4d868d74,// 184 PAY 145 

    0x7bfbb405,// 185 PAY 146 

    0x1c85f184,// 186 PAY 147 

    0xadf1180d,// 187 PAY 148 

    0x4dc09921,// 188 PAY 149 

    0x8fe3515e,// 189 PAY 150 

    0x3c97b5cd,// 190 PAY 151 

    0xfe7de79a,// 191 PAY 152 

    0x4d2dd0d4,// 192 PAY 153 

    0xa626bfa2,// 193 PAY 154 

    0x18a9442b,// 194 PAY 155 

    0xdb7809d1,// 195 PAY 156 

    0xdb9fb619,// 196 PAY 157 

    0xfc79c2f1,// 197 PAY 158 

    0x0d96622f,// 198 PAY 159 

    0x6926cdf8,// 199 PAY 160 

    0x1522f7fb,// 200 PAY 161 

    0x869966ef,// 201 PAY 162 

    0xadb3d940,// 202 PAY 163 

    0x80da5716,// 203 PAY 164 

    0x1937167a,// 204 PAY 165 

    0x62d6e10a,// 205 PAY 166 

    0xb55e574a,// 206 PAY 167 

    0xbc09c30c,// 207 PAY 168 

    0x2a1d079a,// 208 PAY 169 

    0x3e06e2aa,// 209 PAY 170 

    0xa3e92ebf,// 210 PAY 171 

    0x09f9da06,// 211 PAY 172 

    0x62c8ac4f,// 212 PAY 173 

    0x5540cd62,// 213 PAY 174 

    0x8647dca5,// 214 PAY 175 

    0xd8e1e8e2,// 215 PAY 176 

    0x186d0ca7,// 216 PAY 177 

    0xe67662aa,// 217 PAY 178 

    0xccab7d6f,// 218 PAY 179 

    0xf48bf12b,// 219 PAY 180 

    0xfbdca24d,// 220 PAY 181 

    0x12b7cdec,// 221 PAY 182 

    0x1bafddf2,// 222 PAY 183 

    0x3f46de0b,// 223 PAY 184 

    0xe85a3cb3,// 224 PAY 185 

    0x4812e1c3,// 225 PAY 186 

    0x0fdb476a,// 226 PAY 187 

    0x27bc447b,// 227 PAY 188 

    0xa0e446dd,// 228 PAY 189 

    0x3c7e8259,// 229 PAY 190 

    0x16cbed18,// 230 PAY 191 

    0xdb2b171e,// 231 PAY 192 

    0x175b765d,// 232 PAY 193 

    0xd56b8f39,// 233 PAY 194 

    0x822ab482,// 234 PAY 195 

    0xc2f58efb,// 235 PAY 196 

    0xc7d11716,// 236 PAY 197 

    0x626d9739,// 237 PAY 198 

    0x6074098b,// 238 PAY 199 

    0xa85c1758,// 239 PAY 200 

    0xe231a294,// 240 PAY 201 

    0x2edc088f,// 241 PAY 202 

    0xfc0068a6,// 242 PAY 203 

    0x40939411,// 243 PAY 204 

    0xf84c3f99,// 244 PAY 205 

    0xa3af96c4,// 245 PAY 206 

    0x6df24224,// 246 PAY 207 

    0x6c37fed2,// 247 PAY 208 

    0x3de39fa1,// 248 PAY 209 

    0xa7cba219,// 249 PAY 210 

    0x9d34bf76,// 250 PAY 211 

    0xe2e8428f,// 251 PAY 212 

    0x1e6991b2,// 252 PAY 213 

    0xa8092cf9,// 253 PAY 214 

    0x2a15cbaf,// 254 PAY 215 

    0xe4aec899,// 255 PAY 216 

    0x667434af,// 256 PAY 217 

    0xc052efef,// 257 PAY 218 

    0x8a10ed3c,// 258 PAY 219 

    0x405d23ea,// 259 PAY 220 

    0xca19a5ef,// 260 PAY 221 

    0x9c7e9fe1,// 261 PAY 222 

    0x0d092e4c,// 262 PAY 223 

    0x8f44845e,// 263 PAY 224 

    0x6a3223b3,// 264 PAY 225 

    0x6b2b3497,// 265 PAY 226 

    0x8cb947ed,// 266 PAY 227 

    0x8be40ca5,// 267 PAY 228 

    0x5f531346,// 268 PAY 229 

    0x0391e257,// 269 PAY 230 

    0x145d3034,// 270 PAY 231 

    0xa7e3b420,// 271 PAY 232 

    0x26b0514e,// 272 PAY 233 

    0xf3a63d6c,// 273 PAY 234 

    0x22f18208,// 274 PAY 235 

    0xe2ce0835,// 275 PAY 236 

    0x95eccb2f,// 276 PAY 237 

    0x7c82364f,// 277 PAY 238 

    0xf57fe107,// 278 PAY 239 

    0x8ddd1f35,// 279 PAY 240 

    0x9af74a17,// 280 PAY 241 

    0xf1292140,// 281 PAY 242 

    0x93baa022,// 282 PAY 243 

    0xd889c15a,// 283 PAY 244 

    0x381898fc,// 284 PAY 245 

    0xab8c72c7,// 285 PAY 246 

    0x22e0f06c,// 286 PAY 247 

    0xefa68f50,// 287 PAY 248 

    0x159c4632,// 288 PAY 249 

    0xf1149571,// 289 PAY 250 

    0x2a17d39f,// 290 PAY 251 

    0xa6b19785,// 291 PAY 252 

    0x537bb3d4,// 292 PAY 253 

    0x5582d983,// 293 PAY 254 

    0x52921999,// 294 PAY 255 

    0x705ca01f,// 295 PAY 256 

    0xc4df5b02,// 296 PAY 257 

    0x7eb02e24,// 297 PAY 258 

    0xcd76d848,// 298 PAY 259 

    0x63801ee4,// 299 PAY 260 

    0x35f2ed30,// 300 PAY 261 

    0x6bc4804e,// 301 PAY 262 

    0xd16a3c7c,// 302 PAY 263 

    0x3f01b1c6,// 303 PAY 264 

    0xd7c41b18,// 304 PAY 265 

    0xa79a2569,// 305 PAY 266 

    0x869eedba,// 306 PAY 267 

    0x49a2581b,// 307 PAY 268 

    0x928ccfa9,// 308 PAY 269 

    0xf29ebcf3,// 309 PAY 270 

    0x351f4ca4,// 310 PAY 271 

    0xb7e5d945,// 311 PAY 272 

    0x59066568,// 312 PAY 273 

    0x7bfe764e,// 313 PAY 274 

    0xdbdc9669,// 314 PAY 275 

    0xdc9bec84,// 315 PAY 276 

    0xaebde1f9,// 316 PAY 277 

    0x182a2923,// 317 PAY 278 

    0xc4aa871e,// 318 PAY 279 

    0xb7c19f41,// 319 PAY 280 

    0xf983cd05,// 320 PAY 281 

    0xafad39d5,// 321 PAY 282 

    0x762ba32e,// 322 PAY 283 

    0xb4cc6c2e,// 323 PAY 284 

    0x4714bd3c,// 324 PAY 285 

    0xba54b963,// 325 PAY 286 

    0x613a7520,// 326 PAY 287 

    0x3433113d,// 327 PAY 288 

    0xa8a762a9,// 328 PAY 289 

    0x40749acb,// 329 PAY 290 

    0xfd530b69,// 330 PAY 291 

    0x2a4ee7f3,// 331 PAY 292 

    0xac1874be,// 332 PAY 293 

    0x4beef707,// 333 PAY 294 

    0xc4d18805,// 334 PAY 295 

    0xc4704f37,// 335 PAY 296 

    0xc9be9f82,// 336 PAY 297 

    0x39a274de,// 337 PAY 298 

    0x69de2cf8,// 338 PAY 299 

    0x15c820db,// 339 PAY 300 

    0xb7ccd921,// 340 PAY 301 

    0x8a3479fe,// 341 PAY 302 

    0xe165c96c,// 342 PAY 303 

    0x537ee4f6,// 343 PAY 304 

    0x1c1aee5a,// 344 PAY 305 

    0x4340d233,// 345 PAY 306 

    0x9bec2138,// 346 PAY 307 

    0xab1e15d8,// 347 PAY 308 

    0x8abd0451,// 348 PAY 309 

    0xeaf35917,// 349 PAY 310 

    0x72b0af5e,// 350 PAY 311 

    0x50c444b9,// 351 PAY 312 

    0xb0e82c97,// 352 PAY 313 

    0x922640cb,// 353 PAY 314 

    0x835962fd,// 354 PAY 315 

    0xae522b80,// 355 PAY 316 

    0x8aa64481,// 356 PAY 317 

    0x7ea18dcc,// 357 PAY 318 

    0x98a937bd,// 358 PAY 319 

    0xecc8286f,// 359 PAY 320 

    0x31a4bad9,// 360 PAY 321 

    0x0edd2e6d,// 361 PAY 322 

    0xfd7fc345,// 362 PAY 323 

    0x592b25b9,// 363 PAY 324 

    0x87f23a29,// 364 PAY 325 

    0x3d6883e9,// 365 PAY 326 

    0xf655347c,// 366 PAY 327 

    0xecb9f0aa,// 367 PAY 328 

    0x4076a3fd,// 368 PAY 329 

    0x259078f8,// 369 PAY 330 

    0xbb309c1a,// 370 PAY 331 

    0xcba123c8,// 371 PAY 332 

    0x46e7684e,// 372 PAY 333 

    0x704b8164,// 373 PAY 334 

    0x639e6fb2,// 374 PAY 335 

    0x989a5ae0,// 375 PAY 336 

    0x0fa0d68f,// 376 PAY 337 

    0x8d8e4fb3,// 377 PAY 338 

    0xf92e6e23,// 378 PAY 339 

    0x2355b339,// 379 PAY 340 

    0x36da1cad,// 380 PAY 341 

    0xf46db92f,// 381 PAY 342 

    0x67d90d58,// 382 PAY 343 

    0xf2c75b48,// 383 PAY 344 

    0x1b019897,// 384 PAY 345 

    0x62ff8ee5,// 385 PAY 346 

    0x50f2b0e9,// 386 PAY 347 

    0x1581a56f,// 387 PAY 348 

    0x2c563c95,// 388 PAY 349 

    0x7b1b7473,// 389 PAY 350 

    0xd6ae261e,// 390 PAY 351 

    0xaf06d348,// 391 PAY 352 

    0x50e63144,// 392 PAY 353 

    0x4d716264,// 393 PAY 354 

    0x95443caf,// 394 PAY 355 

    0x2bbd243e,// 395 PAY 356 

    0x5ceb5cd1,// 396 PAY 357 

    0x18cb1648,// 397 PAY 358 

    0x9fb90fb3,// 398 PAY 359 

    0x080a9a3d,// 399 PAY 360 

    0xe689802e,// 400 PAY 361 

    0x6100ce43,// 401 PAY 362 

    0x93a47abe,// 402 PAY 363 

    0x2e7fe68a,// 403 PAY 364 

    0xc8a4bf4c,// 404 PAY 365 

    0xa50297b0,// 405 PAY 366 

    0x83be43aa,// 406 PAY 367 

    0xa914beab,// 407 PAY 368 

    0x49bfdeab,// 408 PAY 369 

    0x60cd44bf,// 409 PAY 370 

    0x54940b9c,// 410 PAY 371 

    0x32be4ae8,// 411 PAY 372 

    0x5f490423,// 412 PAY 373 

    0x034fbcc4,// 413 PAY 374 

    0xfc99ccdc,// 414 PAY 375 

    0xc124e4f0,// 415 PAY 376 

    0x8bb7f0da,// 416 PAY 377 

    0xccf4fd43,// 417 PAY 378 

    0x1b65f7a9,// 418 PAY 379 

    0xa11abecb,// 419 PAY 380 

    0xbf2658fd,// 420 PAY 381 

    0x3a588b20,// 421 PAY 382 

    0x86da69a0,// 422 PAY 383 

    0x5a2193a1,// 423 PAY 384 

    0x41404cd7,// 424 PAY 385 

    0x00ae2751,// 425 PAY 386 

    0xf0c47be8,// 426 PAY 387 

    0xb910f75a,// 427 PAY 388 

    0xe2f2472f,// 428 PAY 389 

    0xf78ccf67,// 429 PAY 390 

    0x16b7ca33,// 430 PAY 391 

    0xa4a6c25a,// 431 PAY 392 

    0xf151f161,// 432 PAY 393 

    0x90953ea3,// 433 PAY 394 

    0xc726edaa,// 434 PAY 395 

    0xeb55fa60,// 435 PAY 396 

    0x36391185,// 436 PAY 397 

    0xd6a89a3e,// 437 PAY 398 

    0xea05a23b,// 438 PAY 399 

    0x9d11bc77,// 439 PAY 400 

    0xc351bc60,// 440 PAY 401 

    0x3d67b971,// 441 PAY 402 

    0x814272dd,// 442 PAY 403 

    0xa0e1e0ce,// 443 PAY 404 

    0x52444a76,// 444 PAY 405 

    0x07a0c2bf,// 445 PAY 406 

    0xa80626e3,// 446 PAY 407 

    0x4f558f74,// 447 PAY 408 

    0x87cc03eb,// 448 PAY 409 

    0xc37daf70,// 449 PAY 410 

    0x48fb3909,// 450 PAY 411 

    0x81bb2025,// 451 PAY 412 

    0xf23f1d96,// 452 PAY 413 

    0xa86af1d7,// 453 PAY 414 

    0x5e9370d6,// 454 PAY 415 

    0x93eaa366,// 455 PAY 416 

    0xe9fd64a0,// 456 PAY 417 

    0x8016063d,// 457 PAY 418 

    0xeba1370f,// 458 PAY 419 

    0xa7ef736b,// 459 PAY 420 

    0x7d55f99b,// 460 PAY 421 

    0x23a25191,// 461 PAY 422 

    0x511042e3,// 462 PAY 423 

    0x29106f0c,// 463 PAY 424 

    0x1fb99d29,// 464 PAY 425 

    0x97cb4e0f,// 465 PAY 426 

    0xf9e0233b,// 466 PAY 427 

    0x0bdad38f,// 467 PAY 428 

    0x2360c613,// 468 PAY 429 

    0xf025436c,// 469 PAY 430 

    0x56d1400c,// 470 PAY 431 

    0xb8e5690b,// 471 PAY 432 

    0x9f6796f6,// 472 PAY 433 

    0xc2b3dc7c,// 473 PAY 434 

    0xc3f8de71,// 474 PAY 435 

    0xf7856764,// 475 PAY 436 

    0x0147a782,// 476 PAY 437 

    0x817f8c3b,// 477 PAY 438 

    0x1ea1153c,// 478 PAY 439 

    0x4dd39879,// 479 PAY 440 

    0x9afaced9,// 480 PAY 441 

    0x92723fef,// 481 PAY 442 

    0x0fd30606,// 482 PAY 443 

    0x75131e45,// 483 PAY 444 

    0xd32cd00b,// 484 PAY 445 

    0xc1d077a3,// 485 PAY 446 

    0x7f8541d1,// 486 PAY 447 

    0x38facef4,// 487 PAY 448 

    0x37a619db,// 488 PAY 449 

    0xbc2c98e4,// 489 PAY 450 

    0x156a2e4b,// 490 PAY 451 

    0xb72bcf4d,// 491 PAY 452 

    0x4a70aedb,// 492 PAY 453 

    0xe741544c,// 493 PAY 454 

    0x62549c67,// 494 PAY 455 

    0xe2f45535,// 495 PAY 456 

    0x641d2594,// 496 PAY 457 

    0xb87d5ce8,// 497 PAY 458 

    0xcb2e09eb,// 498 PAY 459 

    0x10738417,// 499 PAY 460 

    0x9727a8a0,// 500 PAY 461 

    0x54912e26,// 501 PAY 462 

    0xc25d30eb,// 502 PAY 463 

    0x60b7e1fe,// 503 PAY 464 

    0x83e8eea1,// 504 PAY 465 

    0x2ae54ba2,// 505 PAY 466 

    0xf204cf46,// 506 PAY 467 

    0xaf547b67,// 507 PAY 468 

    0x3d7f34e5,// 508 PAY 469 

    0xca05b218,// 509 PAY 470 

    0xa4e796f2,// 510 PAY 471 

    0xd1a6c848,// 511 PAY 472 

    0x785f5577,// 512 PAY 473 

    0x49aca4f4,// 513 PAY 474 

    0x2d5cff46,// 514 PAY 475 

    0x457534ce,// 515 PAY 476 

    0xadcb3f79,// 516 PAY 477 

    0x1e63b7de,// 517 PAY 478 

    0xac314dda,// 518 PAY 479 

    0x39d96800,// 519 PAY 480 

/// STA is 1 words. 

/// STA num_pkts       : 85 

/// STA pkt_idx        : 179 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xf5 

    0x02ccf555 // 520 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 96 (0x60) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt72_tmpl[] = {
    0xb8010060,// 1 CCH   1 

/// ECH cache_idx      : 0x06 

/// ECH pdu_tag        : 0x00 

    0x00060000,// 2 ECH   1 

/// SCX is 23 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv !insert_icv !check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000017,// 3 SCX   1 

    0x8085484d,// 4 SCX   2 

    0x00004584,// 5 SCX   3 

    0x42c8da38,// 6 SCX   4 

    0x09d2422f,// 7 SCX   5 

    0xf20b9ee1,// 8 SCX   6 

    0xe0f0bebe,// 9 SCX   7 

    0x6e1293bf,// 10 SCX   8 

    0xe10f7ec1,// 11 SCX   9 

    0x53ad5877,// 12 SCX  10 

    0xa17addd8,// 13 SCX  11 

    0xed62eb26,// 14 SCX  12 

    0xff8e9482,// 15 SCX  13 

    0x83f961ac,// 16 SCX  14 

    0xdf5e5f4c,// 17 SCX  15 

    0x36e7a47e,// 18 SCX  16 

    0xf6dffe3f,// 19 SCX  17 

    0x5118b941,// 20 SCX  18 

    0xccfe693c,// 21 SCX  19 

    0x8e341009,// 22 SCX  20 

    0x8aea13cb,// 23 SCX  21 

    0x89206bbf,// 24 SCX  22 

    0x555ed925,// 25 SCX  23 

/// BFD is 3 words. 

/// BFD tot_len        : 565 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 157 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 157 

/// BFD lencrypto      : 48 

/// BFD ofstcrypto     : 36 

/// BFD (ofst+len)cry  : 84 

/// BFD ofstiv         : 20 

/// BFD ofsticv        : 384 

    0x0000009d,// 26 BFD   1 

    0x00240030,// 27 BFD   2 

    0x01800014,// 28 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : 8 

    0x08009fe3,// 29 MFM   1 

    0x7f550000,// 30 MFM   2 

/// BDA is 143 words. 

/// BDA size     is 565 (0x235) 

/// BDA id       is 0xdad4 

    0x0235dad4,// 31 BDA   1 

/// PAY Generic Data size   : 565 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x1e3cf271,// 32 PAY   1 

    0xb75681eb,// 33 PAY   2 

    0x8ca0bfdd,// 34 PAY   3 

    0x9c48921e,// 35 PAY   4 

    0x1c2fa72a,// 36 PAY   5 

    0xb4dd5f0f,// 37 PAY   6 

    0x0d35f45d,// 38 PAY   7 

    0x667838d2,// 39 PAY   8 

    0x54619c80,// 40 PAY   9 

    0x49034321,// 41 PAY  10 

    0xec730281,// 42 PAY  11 

    0xccf35a8b,// 43 PAY  12 

    0x263c6ba8,// 44 PAY  13 

    0x78778ca8,// 45 PAY  14 

    0x8e7507e1,// 46 PAY  15 

    0x90afb72d,// 47 PAY  16 

    0x4e3535ba,// 48 PAY  17 

    0x93530d3e,// 49 PAY  18 

    0xd1468264,// 50 PAY  19 

    0x84e3dc23,// 51 PAY  20 

    0xf8e79f95,// 52 PAY  21 

    0x838955fa,// 53 PAY  22 

    0x427db4ec,// 54 PAY  23 

    0x7ba8b7f6,// 55 PAY  24 

    0xf4f54f21,// 56 PAY  25 

    0xa5b0e53b,// 57 PAY  26 

    0x4a9487ac,// 58 PAY  27 

    0x8444efce,// 59 PAY  28 

    0x69f7cb3e,// 60 PAY  29 

    0xdfedab48,// 61 PAY  30 

    0x9494d575,// 62 PAY  31 

    0xdc076036,// 63 PAY  32 

    0x0898197e,// 64 PAY  33 

    0xea18e49c,// 65 PAY  34 

    0xe216a3ee,// 66 PAY  35 

    0xc54f3fe7,// 67 PAY  36 

    0x07858af5,// 68 PAY  37 

    0xfd682dff,// 69 PAY  38 

    0xf0931886,// 70 PAY  39 

    0xbb99c5cb,// 71 PAY  40 

    0xbba2a92c,// 72 PAY  41 

    0x68c5c443,// 73 PAY  42 

    0x6048a463,// 74 PAY  43 

    0x7da69e31,// 75 PAY  44 

    0x6e590599,// 76 PAY  45 

    0x76328fb7,// 77 PAY  46 

    0xc7df8299,// 78 PAY  47 

    0xef875760,// 79 PAY  48 

    0xea36655f,// 80 PAY  49 

    0xa70b8ba8,// 81 PAY  50 

    0x31054f3a,// 82 PAY  51 

    0x60a1d4aa,// 83 PAY  52 

    0xb2eb1bf5,// 84 PAY  53 

    0x53fc757f,// 85 PAY  54 

    0xc4142f3c,// 86 PAY  55 

    0xec510fec,// 87 PAY  56 

    0xae9a60b6,// 88 PAY  57 

    0x69472267,// 89 PAY  58 

    0x959a3eec,// 90 PAY  59 

    0xf956bc92,// 91 PAY  60 

    0x6fa1e3d3,// 92 PAY  61 

    0x7da77457,// 93 PAY  62 

    0x3fdde558,// 94 PAY  63 

    0x3c6c7c3f,// 95 PAY  64 

    0xf67ad2aa,// 96 PAY  65 

    0x53f8dbfc,// 97 PAY  66 

    0x7653849e,// 98 PAY  67 

    0xb8c29261,// 99 PAY  68 

    0xc6c601c3,// 100 PAY  69 

    0x79dcad30,// 101 PAY  70 

    0x48b10d6a,// 102 PAY  71 

    0x0fa4eba6,// 103 PAY  72 

    0x0c10764e,// 104 PAY  73 

    0xbdbaec3c,// 105 PAY  74 

    0xb7cc5c89,// 106 PAY  75 

    0x64681ccd,// 107 PAY  76 

    0x07b6fa58,// 108 PAY  77 

    0x8fa8b261,// 109 PAY  78 

    0xa581f4d1,// 110 PAY  79 

    0xa90aeece,// 111 PAY  80 

    0x991ff9c5,// 112 PAY  81 

    0x467887d2,// 113 PAY  82 

    0x39eea243,// 114 PAY  83 

    0x0abe22a1,// 115 PAY  84 

    0x95f15c2d,// 116 PAY  85 

    0xdc53597e,// 117 PAY  86 

    0x09e5a5bc,// 118 PAY  87 

    0x0319194c,// 119 PAY  88 

    0xf78309b1,// 120 PAY  89 

    0xd463ca95,// 121 PAY  90 

    0x6950fcc7,// 122 PAY  91 

    0xbfc34eac,// 123 PAY  92 

    0x2c02549b,// 124 PAY  93 

    0x2c1b07c1,// 125 PAY  94 

    0x1659acf8,// 126 PAY  95 

    0x09ce6be8,// 127 PAY  96 

    0x4dc2e961,// 128 PAY  97 

    0x5ea5e86f,// 129 PAY  98 

    0xc375db1f,// 130 PAY  99 

    0x7ea55912,// 131 PAY 100 

    0x2f8b8bf9,// 132 PAY 101 

    0x14a9b336,// 133 PAY 102 

    0x78b15929,// 134 PAY 103 

    0x8f87a1c5,// 135 PAY 104 

    0x65931bec,// 136 PAY 105 

    0x127025c4,// 137 PAY 106 

    0x40016f8e,// 138 PAY 107 

    0x81d2ce9e,// 139 PAY 108 

    0x2a3235fc,// 140 PAY 109 

    0x45ce43c8,// 141 PAY 110 

    0x9c5a3a7c,// 142 PAY 111 

    0x85ced3db,// 143 PAY 112 

    0x63284e87,// 144 PAY 113 

    0xe8030ebd,// 145 PAY 114 

    0xda9203a3,// 146 PAY 115 

    0x3cfcb832,// 147 PAY 116 

    0xe0110d4c,// 148 PAY 117 

    0x1d7e1e20,// 149 PAY 118 

    0x2416c5a4,// 150 PAY 119 

    0x951a584b,// 151 PAY 120 

    0x01a49c5d,// 152 PAY 121 

    0x70fc4867,// 153 PAY 122 

    0x50e5ed4d,// 154 PAY 123 

    0xdd5701ab,// 155 PAY 124 

    0x6949123b,// 156 PAY 125 

    0x734bd37a,// 157 PAY 126 

    0x76f57699,// 158 PAY 127 

    0x881f9df0,// 159 PAY 128 

    0xfde9693a,// 160 PAY 129 

    0x2ecf6c36,// 161 PAY 130 

    0xe47766ff,// 162 PAY 131 

    0x24162075,// 163 PAY 132 

    0x354b1f51,// 164 PAY 133 

    0x569e088a,// 165 PAY 134 

    0xc978fd50,// 166 PAY 135 

    0x86907b09,// 167 PAY 136 

    0x80685308,// 168 PAY 137 

    0x5c4ec09a,// 169 PAY 138 

    0x210a3fd5,// 170 PAY 139 

    0xcf219441,// 171 PAY 140 

    0x4940084d,// 172 PAY 141 

    0xfa000000,// 173 PAY 142 

/// STA is 1 words. 

/// STA num_pkts       : 44 

/// STA pkt_idx        : 45 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x94 

    0x00b5942c // 174 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt73_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x04 

/// ECH pdu_tag        : 0x00 

    0x00040000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x2 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x80824853,// 4 SCX   2 

    0x00004200,// 5 SCX   3 

    0x29e1087d,// 6 SCX   4 

    0x8a9acb9d,// 7 SCX   5 

    0xcf95c4cf,// 8 SCX   6 

    0x8cb5f41d,// 9 SCX   7 

    0xa1f34199,// 10 SCX   8 

    0x954d6ada,// 11 SCX   9 

    0x867e4891,// 12 SCX  10 

    0x012adfed,// 13 SCX  11 

    0x4e7f2276,// 14 SCX  12 

    0x6a624005,// 15 SCX  13 

    0xba60962c,// 16 SCX  14 

    0x407e0e3f,// 17 SCX  15 

    0x79e46655,// 18 SCX  16 

    0xd8fcccbe,// 19 SCX  17 

    0x8bc460ab,// 20 SCX  18 

    0xe6781985,// 21 SCX  19 

    0x7e9c9ae3,// 22 SCX  20 

    0xc263d0ae,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 1905 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 41 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 41 

/// BFD lencrypto      : 16 

/// BFD ofstcrypto     : 24 

/// BFD (ofst+len)cry  : 40 

/// BFD ofstiv         : 0 

/// BFD ofsticv        : 1840 

    0x00000029,// 24 BFD   1 

    0x00180010,// 25 BFD   2 

    0x07300000,// 26 BFD   3 

/// MFM is 1 words. 

/// MFM vldnibs        : 1 

    0x0100a000,// 27 MFM   1 

/// BDA is 478 words. 

/// BDA size     is 1905 (0x771) 

/// BDA id       is 0xb041 

    0x0771b041,// 28 BDA   1 

/// PAY Generic Data size   : 1905 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x7ade8c5f,// 29 PAY   1 

    0x47ae005f,// 30 PAY   2 

    0x8b08cd18,// 31 PAY   3 

    0xe7747e41,// 32 PAY   4 

    0xc434a1a7,// 33 PAY   5 

    0x4be3b573,// 34 PAY   6 

    0xf9adf409,// 35 PAY   7 

    0xedf30494,// 36 PAY   8 

    0x8556bb89,// 37 PAY   9 

    0xf586606c,// 38 PAY  10 

    0xc4d1fa5b,// 39 PAY  11 

    0x3c9ccfe6,// 40 PAY  12 

    0xf96be32c,// 41 PAY  13 

    0x94cb32c5,// 42 PAY  14 

    0x914d0a12,// 43 PAY  15 

    0x5e746b05,// 44 PAY  16 

    0xa188f8eb,// 45 PAY  17 

    0xed97b84c,// 46 PAY  18 

    0x7e191d23,// 47 PAY  19 

    0xe01e2df2,// 48 PAY  20 

    0xa1a77f68,// 49 PAY  21 

    0x0852fd48,// 50 PAY  22 

    0xf3523617,// 51 PAY  23 

    0x5108f46f,// 52 PAY  24 

    0x7c5e737e,// 53 PAY  25 

    0x59987233,// 54 PAY  26 

    0x777478a4,// 55 PAY  27 

    0x1034605a,// 56 PAY  28 

    0xb796e67e,// 57 PAY  29 

    0x11ab7e7a,// 58 PAY  30 

    0xb23bda64,// 59 PAY  31 

    0x0d81845d,// 60 PAY  32 

    0x0e54bf65,// 61 PAY  33 

    0x180eddc0,// 62 PAY  34 

    0x4357768e,// 63 PAY  35 

    0x13765849,// 64 PAY  36 

    0x26fd3949,// 65 PAY  37 

    0xd5d30d73,// 66 PAY  38 

    0xac3b2c22,// 67 PAY  39 

    0x253ee495,// 68 PAY  40 

    0xbb7689e4,// 69 PAY  41 

    0xfcfd595d,// 70 PAY  42 

    0xcd1055bc,// 71 PAY  43 

    0xed9bc390,// 72 PAY  44 

    0xf5ed6739,// 73 PAY  45 

    0x5cb92cf2,// 74 PAY  46 

    0x33520483,// 75 PAY  47 

    0x9dbbb7fb,// 76 PAY  48 

    0x985a13b9,// 77 PAY  49 

    0x50645dc6,// 78 PAY  50 

    0xe5752864,// 79 PAY  51 

    0x5da47299,// 80 PAY  52 

    0x113a2391,// 81 PAY  53 

    0xc3a565ff,// 82 PAY  54 

    0x046b34b3,// 83 PAY  55 

    0x2dc89e23,// 84 PAY  56 

    0xb5fb9ddb,// 85 PAY  57 

    0xc1ac1bc4,// 86 PAY  58 

    0x46a345ea,// 87 PAY  59 

    0x6f42c6ce,// 88 PAY  60 

    0x54ee0304,// 89 PAY  61 

    0x9c45443e,// 90 PAY  62 

    0xe24c4d24,// 91 PAY  63 

    0x9b588071,// 92 PAY  64 

    0x0b5aeaf5,// 93 PAY  65 

    0x6c056462,// 94 PAY  66 

    0x22abaf9f,// 95 PAY  67 

    0x38e66dbb,// 96 PAY  68 

    0x3167cd72,// 97 PAY  69 

    0x21094064,// 98 PAY  70 

    0xf3a46c21,// 99 PAY  71 

    0x968cbe51,// 100 PAY  72 

    0xa323ea3b,// 101 PAY  73 

    0xacc772f3,// 102 PAY  74 

    0x63bc447f,// 103 PAY  75 

    0x2bdcc64d,// 104 PAY  76 

    0xdc20f80f,// 105 PAY  77 

    0x611e0178,// 106 PAY  78 

    0x1f3aa337,// 107 PAY  79 

    0x2629bcc1,// 108 PAY  80 

    0x62d2fb14,// 109 PAY  81 

    0x384417c2,// 110 PAY  82 

    0x2f5b797c,// 111 PAY  83 

    0x614db4d1,// 112 PAY  84 

    0xb5b061be,// 113 PAY  85 

    0x38dfc035,// 114 PAY  86 

    0x15b05609,// 115 PAY  87 

    0x936a27e1,// 116 PAY  88 

    0x946fd56c,// 117 PAY  89 

    0xe8626c78,// 118 PAY  90 

    0x7c47244f,// 119 PAY  91 

    0x6fd290e0,// 120 PAY  92 

    0xd40df44f,// 121 PAY  93 

    0x41ca1b3b,// 122 PAY  94 

    0xe03d8b15,// 123 PAY  95 

    0x2097f288,// 124 PAY  96 

    0xfb49f753,// 125 PAY  97 

    0x2aa486d3,// 126 PAY  98 

    0xaf55b21f,// 127 PAY  99 

    0x34a39c1b,// 128 PAY 100 

    0xc9d7bedf,// 129 PAY 101 

    0xe443048f,// 130 PAY 102 

    0xa9489540,// 131 PAY 103 

    0x92192063,// 132 PAY 104 

    0x3a5b8a62,// 133 PAY 105 

    0xe60e380b,// 134 PAY 106 

    0x85250d9d,// 135 PAY 107 

    0x145927b4,// 136 PAY 108 

    0xc967e939,// 137 PAY 109 

    0x0b0fcbaa,// 138 PAY 110 

    0x0100daca,// 139 PAY 111 

    0xd86886d4,// 140 PAY 112 

    0x1bdb8650,// 141 PAY 113 

    0x5a7e3775,// 142 PAY 114 

    0xb2bda177,// 143 PAY 115 

    0x276db8c4,// 144 PAY 116 

    0x16c629cd,// 145 PAY 117 

    0x38bee713,// 146 PAY 118 

    0x2556ea74,// 147 PAY 119 

    0x3b48e94c,// 148 PAY 120 

    0x10c8316d,// 149 PAY 121 

    0x3fc92b4d,// 150 PAY 122 

    0x0c88b02e,// 151 PAY 123 

    0xe113bbbf,// 152 PAY 124 

    0x7b0c63b9,// 153 PAY 125 

    0x55f5438e,// 154 PAY 126 

    0x12191ac5,// 155 PAY 127 

    0xa36937d3,// 156 PAY 128 

    0xaa6c6a38,// 157 PAY 129 

    0xa241ce17,// 158 PAY 130 

    0x9e7545c6,// 159 PAY 131 

    0x3d9ced0f,// 160 PAY 132 

    0xab78f534,// 161 PAY 133 

    0xf62d7e8e,// 162 PAY 134 

    0x6457d20b,// 163 PAY 135 

    0x7e2d2322,// 164 PAY 136 

    0x5d3a965e,// 165 PAY 137 

    0x3fd9c0b1,// 166 PAY 138 

    0x12baea22,// 167 PAY 139 

    0x9008b121,// 168 PAY 140 

    0xc1115367,// 169 PAY 141 

    0x69407d77,// 170 PAY 142 

    0xee559f81,// 171 PAY 143 

    0xd32b7c56,// 172 PAY 144 

    0x73746090,// 173 PAY 145 

    0x9cb95a44,// 174 PAY 146 

    0xdd67b5de,// 175 PAY 147 

    0xa3d14182,// 176 PAY 148 

    0xb62945e4,// 177 PAY 149 

    0xb2c53f79,// 178 PAY 150 

    0x4277b122,// 179 PAY 151 

    0x8b043f88,// 180 PAY 152 

    0x90c43bac,// 181 PAY 153 

    0x7b2ea867,// 182 PAY 154 

    0xf27064b6,// 183 PAY 155 

    0x5a1e1a92,// 184 PAY 156 

    0x00dc00b1,// 185 PAY 157 

    0x8f216257,// 186 PAY 158 

    0xa0e3d751,// 187 PAY 159 

    0x5be66629,// 188 PAY 160 

    0xa81dd09a,// 189 PAY 161 

    0x7c5352f4,// 190 PAY 162 

    0xfe11c291,// 191 PAY 163 

    0x1ab0d8fc,// 192 PAY 164 

    0xbdbfac1c,// 193 PAY 165 

    0x24dfadea,// 194 PAY 166 

    0x1284b541,// 195 PAY 167 

    0xc8b4f65e,// 196 PAY 168 

    0x2eb70400,// 197 PAY 169 

    0x207c48d2,// 198 PAY 170 

    0x5d2875e1,// 199 PAY 171 

    0x6f283785,// 200 PAY 172 

    0x830de6f7,// 201 PAY 173 

    0xef0c99c4,// 202 PAY 174 

    0x43a05b6a,// 203 PAY 175 

    0x24aa0f2a,// 204 PAY 176 

    0x0ea68045,// 205 PAY 177 

    0xe8e5dce7,// 206 PAY 178 

    0xeb9fb12d,// 207 PAY 179 

    0xdc9d5720,// 208 PAY 180 

    0xfff8abe7,// 209 PAY 181 

    0xb753aee6,// 210 PAY 182 

    0x01207b90,// 211 PAY 183 

    0x84530973,// 212 PAY 184 

    0x072838b3,// 213 PAY 185 

    0x777a9d5e,// 214 PAY 186 

    0x6b46a34e,// 215 PAY 187 

    0xb4abaddf,// 216 PAY 188 

    0xd3e49609,// 217 PAY 189 

    0x12555f7f,// 218 PAY 190 

    0x572fb596,// 219 PAY 191 

    0x1a230aa1,// 220 PAY 192 

    0x8ee60f57,// 221 PAY 193 

    0xa1404a1e,// 222 PAY 194 

    0x4a53e79a,// 223 PAY 195 

    0x02d908a2,// 224 PAY 196 

    0x44210caf,// 225 PAY 197 

    0x934b7306,// 226 PAY 198 

    0x72c85721,// 227 PAY 199 

    0x7d0ed246,// 228 PAY 200 

    0x5b3f079d,// 229 PAY 201 

    0xcf2a29ba,// 230 PAY 202 

    0xc8a05856,// 231 PAY 203 

    0x39c86f69,// 232 PAY 204 

    0x6e01f1e7,// 233 PAY 205 

    0x1b820798,// 234 PAY 206 

    0x691494f6,// 235 PAY 207 

    0x48b06b7a,// 236 PAY 208 

    0xd3d10396,// 237 PAY 209 

    0xf6c29c2a,// 238 PAY 210 

    0x26d336c2,// 239 PAY 211 

    0x097981df,// 240 PAY 212 

    0x17a32dc3,// 241 PAY 213 

    0x38c82837,// 242 PAY 214 

    0x1ae6f6d0,// 243 PAY 215 

    0x69de543d,// 244 PAY 216 

    0x4d07eb09,// 245 PAY 217 

    0xa2c976da,// 246 PAY 218 

    0x0d608312,// 247 PAY 219 

    0x0e961ff6,// 248 PAY 220 

    0x3663b84e,// 249 PAY 221 

    0x05297ae8,// 250 PAY 222 

    0xa415eb95,// 251 PAY 223 

    0x55a23651,// 252 PAY 224 

    0xf616a6ad,// 253 PAY 225 

    0x2f01ee30,// 254 PAY 226 

    0xf979c810,// 255 PAY 227 

    0x231daeaa,// 256 PAY 228 

    0x55d3b72b,// 257 PAY 229 

    0x4958415c,// 258 PAY 230 

    0xcb89b432,// 259 PAY 231 

    0xf7c11c81,// 260 PAY 232 

    0xfa97c7fa,// 261 PAY 233 

    0xe273df96,// 262 PAY 234 

    0x2fd9a6fe,// 263 PAY 235 

    0x71e0405a,// 264 PAY 236 

    0xbc360ad6,// 265 PAY 237 

    0xe8ed31ec,// 266 PAY 238 

    0x660527f7,// 267 PAY 239 

    0xbe31859d,// 268 PAY 240 

    0x2bdbdc92,// 269 PAY 241 

    0xd3366938,// 270 PAY 242 

    0xd1c3ef76,// 271 PAY 243 

    0xa541d86d,// 272 PAY 244 

    0xf547dea1,// 273 PAY 245 

    0x7f8c6425,// 274 PAY 246 

    0xcc8184cd,// 275 PAY 247 

    0xd12eeeed,// 276 PAY 248 

    0x8270e563,// 277 PAY 249 

    0x31f0fea4,// 278 PAY 250 

    0xf5d1af29,// 279 PAY 251 

    0x3ce6e97c,// 280 PAY 252 

    0x44decd7f,// 281 PAY 253 

    0x4f082f64,// 282 PAY 254 

    0xb546f6aa,// 283 PAY 255 

    0x69b6dcb7,// 284 PAY 256 

    0x1168bab8,// 285 PAY 257 

    0xf1bb57d5,// 286 PAY 258 

    0xee01625f,// 287 PAY 259 

    0xf6e4310f,// 288 PAY 260 

    0x96647447,// 289 PAY 261 

    0xcbf7a517,// 290 PAY 262 

    0x698b9956,// 291 PAY 263 

    0xd52576be,// 292 PAY 264 

    0x2f85125a,// 293 PAY 265 

    0x84cd1d3d,// 294 PAY 266 

    0x77ec6f9b,// 295 PAY 267 

    0xc390ac71,// 296 PAY 268 

    0xc85cb8e8,// 297 PAY 269 

    0x0ca504f7,// 298 PAY 270 

    0x4fd65a3a,// 299 PAY 271 

    0xa35fc19a,// 300 PAY 272 

    0xdc5b8f3b,// 301 PAY 273 

    0xc89d1633,// 302 PAY 274 

    0x6f0c7a35,// 303 PAY 275 

    0x5bae64af,// 304 PAY 276 

    0x0a55fdec,// 305 PAY 277 

    0x35d4ab7f,// 306 PAY 278 

    0x2e3ea78c,// 307 PAY 279 

    0xf70ccc1e,// 308 PAY 280 

    0x79f1529c,// 309 PAY 281 

    0x462430db,// 310 PAY 282 

    0x3a95fe05,// 311 PAY 283 

    0x3af0d4f4,// 312 PAY 284 

    0x6da3c152,// 313 PAY 285 

    0xc14b69eb,// 314 PAY 286 

    0x96412c56,// 315 PAY 287 

    0xce8a29d9,// 316 PAY 288 

    0x03f2ca58,// 317 PAY 289 

    0xc7795aa1,// 318 PAY 290 

    0xf2f4e83d,// 319 PAY 291 

    0xad58d374,// 320 PAY 292 

    0x7f2d7588,// 321 PAY 293 

    0x363454cf,// 322 PAY 294 

    0xc709465d,// 323 PAY 295 

    0x5fc402b9,// 324 PAY 296 

    0x7bb9e6d0,// 325 PAY 297 

    0x47665145,// 326 PAY 298 

    0x93e86d5a,// 327 PAY 299 

    0x50019dd9,// 328 PAY 300 

    0x2b0f5f83,// 329 PAY 301 

    0x9c8cd746,// 330 PAY 302 

    0x3b237ef7,// 331 PAY 303 

    0xdb7ee634,// 332 PAY 304 

    0xd8cdcd48,// 333 PAY 305 

    0xfad5e45e,// 334 PAY 306 

    0x598d8941,// 335 PAY 307 

    0x6bcec74e,// 336 PAY 308 

    0x002f4dfe,// 337 PAY 309 

    0xce6025b6,// 338 PAY 310 

    0x61a235e2,// 339 PAY 311 

    0xbe80506a,// 340 PAY 312 

    0xda4aa89d,// 341 PAY 313 

    0x856e3ed8,// 342 PAY 314 

    0x55fcc3bf,// 343 PAY 315 

    0x1397b5db,// 344 PAY 316 

    0xa28a056a,// 345 PAY 317 

    0x8e30937d,// 346 PAY 318 

    0x479e152e,// 347 PAY 319 

    0x99629b4b,// 348 PAY 320 

    0x158d0b98,// 349 PAY 321 

    0x96b22da9,// 350 PAY 322 

    0x24497bfb,// 351 PAY 323 

    0x15cf157a,// 352 PAY 324 

    0xcbc444c6,// 353 PAY 325 

    0xe7169ea8,// 354 PAY 326 

    0xe63711c8,// 355 PAY 327 

    0xcb31e4a0,// 356 PAY 328 

    0xb65c115e,// 357 PAY 329 

    0x351f696a,// 358 PAY 330 

    0xe8a6879d,// 359 PAY 331 

    0x449b1b10,// 360 PAY 332 

    0x9e06a2a2,// 361 PAY 333 

    0xdb90462f,// 362 PAY 334 

    0x66252a6d,// 363 PAY 335 

    0x7556ad78,// 364 PAY 336 

    0x9c3e4d79,// 365 PAY 337 

    0x0bd0c981,// 366 PAY 338 

    0xd5e94b71,// 367 PAY 339 

    0x9fdfbdcd,// 368 PAY 340 

    0x798e5d1e,// 369 PAY 341 

    0x3ca240f9,// 370 PAY 342 

    0xa928c390,// 371 PAY 343 

    0xbcdd28e0,// 372 PAY 344 

    0x948443e5,// 373 PAY 345 

    0xac604b3a,// 374 PAY 346 

    0xe0def22e,// 375 PAY 347 

    0xb8633ea6,// 376 PAY 348 

    0x700e5a3b,// 377 PAY 349 

    0x54397cc8,// 378 PAY 350 

    0xb60fc621,// 379 PAY 351 

    0x085baf12,// 380 PAY 352 

    0xbf5dcade,// 381 PAY 353 

    0x557bc8d6,// 382 PAY 354 

    0x7b6412cd,// 383 PAY 355 

    0xafa13f68,// 384 PAY 356 

    0x76648053,// 385 PAY 357 

    0xd026c099,// 386 PAY 358 

    0x092e8fbd,// 387 PAY 359 

    0x0cc55c4f,// 388 PAY 360 

    0xfda16cad,// 389 PAY 361 

    0x20b4da78,// 390 PAY 362 

    0xd8956566,// 391 PAY 363 

    0xca532164,// 392 PAY 364 

    0xdcef7af3,// 393 PAY 365 

    0xb1237fae,// 394 PAY 366 

    0x9c518591,// 395 PAY 367 

    0xcd703820,// 396 PAY 368 

    0xfb8e78f1,// 397 PAY 369 

    0xb4a3079e,// 398 PAY 370 

    0x2de7ca94,// 399 PAY 371 

    0x31cbb286,// 400 PAY 372 

    0x6964dcf8,// 401 PAY 373 

    0x554ba1d3,// 402 PAY 374 

    0x6996a4c6,// 403 PAY 375 

    0x31a4d1ec,// 404 PAY 376 

    0xd319ff6d,// 405 PAY 377 

    0x64a4168d,// 406 PAY 378 

    0x8bba94fb,// 407 PAY 379 

    0xb9b3c23d,// 408 PAY 380 

    0xfbc0f715,// 409 PAY 381 

    0xb97de7b2,// 410 PAY 382 

    0x9d9f8b1d,// 411 PAY 383 

    0x5ca03371,// 412 PAY 384 

    0xdf66cdac,// 413 PAY 385 

    0xaca427ba,// 414 PAY 386 

    0x20771d99,// 415 PAY 387 

    0xd0d58363,// 416 PAY 388 

    0xf120effc,// 417 PAY 389 

    0xd87fea26,// 418 PAY 390 

    0x79a952b8,// 419 PAY 391 

    0xa574c610,// 420 PAY 392 

    0xe4e619ee,// 421 PAY 393 

    0xc8d52012,// 422 PAY 394 

    0x97c8cadf,// 423 PAY 395 

    0x3fb66276,// 424 PAY 396 

    0xc27a8454,// 425 PAY 397 

    0x4b128300,// 426 PAY 398 

    0xbd454a36,// 427 PAY 399 

    0x9fc379a7,// 428 PAY 400 

    0x03f5988f,// 429 PAY 401 

    0xd9fe1c8e,// 430 PAY 402 

    0xde8ad789,// 431 PAY 403 

    0x560e1d33,// 432 PAY 404 

    0xb639bdcc,// 433 PAY 405 

    0x26c89300,// 434 PAY 406 

    0xccce9495,// 435 PAY 407 

    0xd21282fa,// 436 PAY 408 

    0x706d9c07,// 437 PAY 409 

    0x624f33ad,// 438 PAY 410 

    0x4c96eb5f,// 439 PAY 411 

    0xdabfda44,// 440 PAY 412 

    0x4c9d1e87,// 441 PAY 413 

    0x8f351168,// 442 PAY 414 

    0xe676f3d8,// 443 PAY 415 

    0xc292146e,// 444 PAY 416 

    0xcb79ddcb,// 445 PAY 417 

    0xbf524c5e,// 446 PAY 418 

    0x5a740b52,// 447 PAY 419 

    0x9dbf7ebc,// 448 PAY 420 

    0x9f61b7de,// 449 PAY 421 

    0xe1526c9e,// 450 PAY 422 

    0x37f3708b,// 451 PAY 423 

    0x444dc7ec,// 452 PAY 424 

    0x48b501a1,// 453 PAY 425 

    0xdb0b045e,// 454 PAY 426 

    0x5bc9a037,// 455 PAY 427 

    0x14c92e01,// 456 PAY 428 

    0xedfc9cb8,// 457 PAY 429 

    0x82e70bef,// 458 PAY 430 

    0xb83b4dee,// 459 PAY 431 

    0x41fd0a57,// 460 PAY 432 

    0xdc0d3c01,// 461 PAY 433 

    0xa48ef85a,// 462 PAY 434 

    0x9c089a02,// 463 PAY 435 

    0x3edf4eb7,// 464 PAY 436 

    0xf4423e97,// 465 PAY 437 

    0x151d6115,// 466 PAY 438 

    0xf9f3080e,// 467 PAY 439 

    0xa43d573a,// 468 PAY 440 

    0x408a0824,// 469 PAY 441 

    0x1f9d0c1b,// 470 PAY 442 

    0xa14a4f18,// 471 PAY 443 

    0xcd0dbfeb,// 472 PAY 444 

    0x67cce776,// 473 PAY 445 

    0x64a3534e,// 474 PAY 446 

    0x9848aaf7,// 475 PAY 447 

    0x2eb42f85,// 476 PAY 448 

    0xcdc93192,// 477 PAY 449 

    0xb929bd14,// 478 PAY 450 

    0xdf0a404a,// 479 PAY 451 

    0x3993afb8,// 480 PAY 452 

    0x03881c18,// 481 PAY 453 

    0x2eca40b8,// 482 PAY 454 

    0x4ebbdd90,// 483 PAY 455 

    0x7731608a,// 484 PAY 456 

    0x08c58daf,// 485 PAY 457 

    0xd6ed142f,// 486 PAY 458 

    0x045ccdcb,// 487 PAY 459 

    0xed1eedf6,// 488 PAY 460 

    0xc1c32077,// 489 PAY 461 

    0xc93dca43,// 490 PAY 462 

    0x1f0b7f50,// 491 PAY 463 

    0x3409fbde,// 492 PAY 464 

    0x7e5f9352,// 493 PAY 465 

    0x30fe0127,// 494 PAY 466 

    0x7f0b6efd,// 495 PAY 467 

    0xdc10830a,// 496 PAY 468 

    0x7469b829,// 497 PAY 469 

    0xf93a2825,// 498 PAY 470 

    0x5fb17c88,// 499 PAY 471 

    0x7d1b5c75,// 500 PAY 472 

    0xc1cba335,// 501 PAY 473 

    0x874dd758,// 502 PAY 474 

    0xd5c3ff1a,// 503 PAY 475 

    0x2c8692dd,// 504 PAY 476 

    0x14000000,// 505 PAY 477 

/// STA is 1 words. 

/// STA num_pkts       : 218 

/// STA pkt_idx        : 241 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x44 

    0x03c544da // 506 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 72 (0x48) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt74_tmpl[] = {
    0xb8010048,// 1 CCH   1 

/// ECH cache_idx      : 0x0c 

/// ECH pdu_tag        : 0x00 

    0x000c0000,// 2 ECH   1 

/// SCX is 17 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv !check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x2 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000011,// 3 SCX   1 

    0x8080487e,// 4 SCX   2 

    0x00004200,// 5 SCX   3 

    0x92ab5b2a,// 6 SCX   4 

    0x4dbd6c52,// 7 SCX   5 

    0x46acd331,// 8 SCX   6 

    0x77883071,// 9 SCX   7 

    0x7d4f5a47,// 10 SCX   8 

    0x2ba11cb0,// 11 SCX   9 

    0xd65d6e7b,// 12 SCX  10 

    0xc805bc1e,// 13 SCX  11 

    0x5c6e8987,// 14 SCX  12 

    0xd1b0a35e,// 15 SCX  13 

    0xb5e4797a,// 16 SCX  14 

    0x94d975ed,// 17 SCX  15 

    0x26010b0d,// 18 SCX  16 

    0xcc25b7b8,// 19 SCX  17 

/// BFD is 3 words. 

/// BFD tot_len        : 1050 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 992 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 992 

/// BFD lencrypto      : 176 

/// BFD ofstcrypto     : 752 

/// BFD (ofst+len)cry  : 928 

/// BFD ofstiv         : 476 

/// BFD ofsticv        : 1028 

    0x000003e0,// 20 BFD   1 

    0x02f000b0,// 21 BFD   2 

    0x040401dc,// 22 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7c 

    0x7c009afa,// 23 MFM   1 

    0xb5754f92,// 24 MFM   2 

    0xca9497f0,// 25 MFM   3 

    0x669542fe,// 26 MFM   4 

    0xf3d2c3bd,// 27 MFM   5 

    0x33de4e00,// 28 MFM   6 

    0xfe92b2ff,// 29 MFM   7 

    0x9be20cc5,// 30 MFM   8 

    0xbef4af33,// 31 MFM   9 

    0xb37fbb44,// 32 MFM  10 

    0x5d1ced18,// 33 MFM  11 

    0xf9bca279,// 34 MFM  12 

    0xabf0d6d7,// 35 MFM  13 

    0x96dc5fd7,// 36 MFM  14 

    0x1a8d974e,// 37 MFM  15 

    0xbe86dc50,// 38 MFM  16 

/// BDA is 264 words. 

/// BDA size     is 1050 (0x41a) 

/// BDA id       is 0xa0be 

    0x041aa0be,// 39 BDA   1 

/// PAY Generic Data size   : 1050 byte(s) 

/// PAD Buffer Data Pad size   : 2 byte(s) 

    0x81d412a6,// 40 PAY   1 

    0x2cc85308,// 41 PAY   2 

    0x812f2d65,// 42 PAY   3 

    0x80734e93,// 43 PAY   4 

    0x9b75e249,// 44 PAY   5 

    0xfe071e25,// 45 PAY   6 

    0xaf6646b9,// 46 PAY   7 

    0x61cf071a,// 47 PAY   8 

    0xb4e15e21,// 48 PAY   9 

    0xae119cc6,// 49 PAY  10 

    0x0ae46ecb,// 50 PAY  11 

    0xc59f929a,// 51 PAY  12 

    0x9e25402f,// 52 PAY  13 

    0x1247c380,// 53 PAY  14 

    0xeb34367e,// 54 PAY  15 

    0x7a22c6aa,// 55 PAY  16 

    0xfa47f032,// 56 PAY  17 

    0x02703359,// 57 PAY  18 

    0xc48349da,// 58 PAY  19 

    0xaf2e7bb4,// 59 PAY  20 

    0xaa3aaa60,// 60 PAY  21 

    0x2f74bac2,// 61 PAY  22 

    0x91ccac29,// 62 PAY  23 

    0xf54f44d5,// 63 PAY  24 

    0xbae23c5a,// 64 PAY  25 

    0x34cd7a28,// 65 PAY  26 

    0x8700f19d,// 66 PAY  27 

    0xbcd2f877,// 67 PAY  28 

    0x37175925,// 68 PAY  29 

    0x04cfdf73,// 69 PAY  30 

    0x0562638e,// 70 PAY  31 

    0x9b3e0207,// 71 PAY  32 

    0xe094e3c7,// 72 PAY  33 

    0xad67c4c5,// 73 PAY  34 

    0x2d8344b0,// 74 PAY  35 

    0xdfeabc5a,// 75 PAY  36 

    0x01ce7cf6,// 76 PAY  37 

    0x4934a073,// 77 PAY  38 

    0xb58a4b75,// 78 PAY  39 

    0xc74c15b6,// 79 PAY  40 

    0xee40a6c4,// 80 PAY  41 

    0x296e92bd,// 81 PAY  42 

    0xa5a8d7b3,// 82 PAY  43 

    0x579b7fa7,// 83 PAY  44 

    0xd4f44efd,// 84 PAY  45 

    0x4d5c1e44,// 85 PAY  46 

    0x7ef776ad,// 86 PAY  47 

    0x3dff29ea,// 87 PAY  48 

    0x7c7fae64,// 88 PAY  49 

    0xbae1540f,// 89 PAY  50 

    0x5dc9c42f,// 90 PAY  51 

    0x71443a6d,// 91 PAY  52 

    0x8d997fa8,// 92 PAY  53 

    0x1eda9222,// 93 PAY  54 

    0x5263bddb,// 94 PAY  55 

    0x21a9be3e,// 95 PAY  56 

    0xbdc6aea4,// 96 PAY  57 

    0xf97edb48,// 97 PAY  58 

    0xaa84707f,// 98 PAY  59 

    0x72d86587,// 99 PAY  60 

    0xd4f82320,// 100 PAY  61 

    0xb9c960a6,// 101 PAY  62 

    0xa9cb221b,// 102 PAY  63 

    0x651f0b2f,// 103 PAY  64 

    0x056dcf9f,// 104 PAY  65 

    0x4c47917e,// 105 PAY  66 

    0x5b3a0c5e,// 106 PAY  67 

    0x47ffab1f,// 107 PAY  68 

    0xd8175afb,// 108 PAY  69 

    0x04476140,// 109 PAY  70 

    0x85f9b020,// 110 PAY  71 

    0x1db35e27,// 111 PAY  72 

    0x72a9e3a8,// 112 PAY  73 

    0x27eb06bc,// 113 PAY  74 

    0x5ebfc441,// 114 PAY  75 

    0xecd048f9,// 115 PAY  76 

    0x037173c4,// 116 PAY  77 

    0x856c289c,// 117 PAY  78 

    0x27df5db0,// 118 PAY  79 

    0x8cee0092,// 119 PAY  80 

    0xe44b3ad0,// 120 PAY  81 

    0x365c1329,// 121 PAY  82 

    0xff382457,// 122 PAY  83 

    0x4afb0eee,// 123 PAY  84 

    0x41859ac5,// 124 PAY  85 

    0x2f3160f7,// 125 PAY  86 

    0x191305e8,// 126 PAY  87 

    0x4e00ea46,// 127 PAY  88 

    0xa2acbf15,// 128 PAY  89 

    0x5ecfdeec,// 129 PAY  90 

    0x00e83d82,// 130 PAY  91 

    0x1599638e,// 131 PAY  92 

    0xdfa9f1eb,// 132 PAY  93 

    0x3ec4f585,// 133 PAY  94 

    0x3e47b551,// 134 PAY  95 

    0x92f53c2b,// 135 PAY  96 

    0x96d2a57c,// 136 PAY  97 

    0x2b5b1bd7,// 137 PAY  98 

    0xdaf2bc51,// 138 PAY  99 

    0xbc935cc2,// 139 PAY 100 

    0xdcc967a6,// 140 PAY 101 

    0xd49c5cdc,// 141 PAY 102 

    0xd2b180b4,// 142 PAY 103 

    0x9127d59b,// 143 PAY 104 

    0x0031e187,// 144 PAY 105 

    0xe7a78cb3,// 145 PAY 106 

    0x33c3be7f,// 146 PAY 107 

    0xc920afdc,// 147 PAY 108 

    0x8169cd65,// 148 PAY 109 

    0xf26870f0,// 149 PAY 110 

    0x256245ee,// 150 PAY 111 

    0x6e87c2d3,// 151 PAY 112 

    0x0c7e4f1d,// 152 PAY 113 

    0xaee75cd0,// 153 PAY 114 

    0xcce57dc4,// 154 PAY 115 

    0x6a9b304e,// 155 PAY 116 

    0x6994b8dd,// 156 PAY 117 

    0xc616d8ff,// 157 PAY 118 

    0xfef3d0cc,// 158 PAY 119 

    0x3ae5304b,// 159 PAY 120 

    0xdb545a6b,// 160 PAY 121 

    0x171a6f04,// 161 PAY 122 

    0x32b5f5f0,// 162 PAY 123 

    0xf1466242,// 163 PAY 124 

    0x5f5ea4c6,// 164 PAY 125 

    0x94eaca01,// 165 PAY 126 

    0x1e100f3b,// 166 PAY 127 

    0xd3816c4a,// 167 PAY 128 

    0x0746d15c,// 168 PAY 129 

    0x1f53a79a,// 169 PAY 130 

    0xd79a854d,// 170 PAY 131 

    0x83cd4161,// 171 PAY 132 

    0xd57bbd2b,// 172 PAY 133 

    0x65368ca0,// 173 PAY 134 

    0xb0586a82,// 174 PAY 135 

    0xcd46b67c,// 175 PAY 136 

    0x6230717e,// 176 PAY 137 

    0x69bb35ae,// 177 PAY 138 

    0x75b59ae3,// 178 PAY 139 

    0x790465ab,// 179 PAY 140 

    0x1eea1cd9,// 180 PAY 141 

    0x26c7670f,// 181 PAY 142 

    0x9d34de4e,// 182 PAY 143 

    0xcbffd58f,// 183 PAY 144 

    0xf679d2f9,// 184 PAY 145 

    0x9be9a20e,// 185 PAY 146 

    0x98b0b8e7,// 186 PAY 147 

    0xf49fb0e7,// 187 PAY 148 

    0x6081bcaf,// 188 PAY 149 

    0x6df5f018,// 189 PAY 150 

    0x6e1971cb,// 190 PAY 151 

    0xb0cfbfa8,// 191 PAY 152 

    0x83506234,// 192 PAY 153 

    0xba898c05,// 193 PAY 154 

    0xb54983cb,// 194 PAY 155 

    0x2b81b82c,// 195 PAY 156 

    0x33e3f069,// 196 PAY 157 

    0x00317e1c,// 197 PAY 158 

    0xf4a79466,// 198 PAY 159 

    0x2705e3d6,// 199 PAY 160 

    0x49793e51,// 200 PAY 161 

    0xf66bfc85,// 201 PAY 162 

    0x52fcd4c0,// 202 PAY 163 

    0x8fb3de97,// 203 PAY 164 

    0x9a30fa54,// 204 PAY 165 

    0xda2581ef,// 205 PAY 166 

    0x1650eccc,// 206 PAY 167 

    0xa8c8b39c,// 207 PAY 168 

    0x38355013,// 208 PAY 169 

    0x3311889e,// 209 PAY 170 

    0xdb08c74a,// 210 PAY 171 

    0xa058fa12,// 211 PAY 172 

    0x96b80012,// 212 PAY 173 

    0xc1e412aa,// 213 PAY 174 

    0xe947de80,// 214 PAY 175 

    0x47141fc3,// 215 PAY 176 

    0x44268174,// 216 PAY 177 

    0xc32cc647,// 217 PAY 178 

    0x98abbe7f,// 218 PAY 179 

    0x14f1743d,// 219 PAY 180 

    0xe9a4a329,// 220 PAY 181 

    0xb52a08e6,// 221 PAY 182 

    0x18eeadd3,// 222 PAY 183 

    0x66bbf8ae,// 223 PAY 184 

    0x6c9f2a31,// 224 PAY 185 

    0xb68419b5,// 225 PAY 186 

    0x72349853,// 226 PAY 187 

    0x3061dd4e,// 227 PAY 188 

    0x8fad47e5,// 228 PAY 189 

    0x2adf78fe,// 229 PAY 190 

    0xae51c0b4,// 230 PAY 191 

    0xf66bc72b,// 231 PAY 192 

    0x3212c2b1,// 232 PAY 193 

    0xcacd3ca2,// 233 PAY 194 

    0x2bc0d8c7,// 234 PAY 195 

    0xf344bf70,// 235 PAY 196 

    0x357b4a6c,// 236 PAY 197 

    0x5eb43b07,// 237 PAY 198 

    0x5865c17f,// 238 PAY 199 

    0x39769632,// 239 PAY 200 

    0x2ca769a0,// 240 PAY 201 

    0xad797812,// 241 PAY 202 

    0xd69b3b2f,// 242 PAY 203 

    0xbce697ab,// 243 PAY 204 

    0x7d378156,// 244 PAY 205 

    0xa38dea97,// 245 PAY 206 

    0xa9c31bed,// 246 PAY 207 

    0x299f36b1,// 247 PAY 208 

    0x2e4cb310,// 248 PAY 209 

    0x84a79eb6,// 249 PAY 210 

    0xfd5df1a4,// 250 PAY 211 

    0x0c33700e,// 251 PAY 212 

    0x0465e8da,// 252 PAY 213 

    0xc78dcf68,// 253 PAY 214 

    0x4ed427d3,// 254 PAY 215 

    0x99166c3c,// 255 PAY 216 

    0x563a52a1,// 256 PAY 217 

    0xa8f273f6,// 257 PAY 218 

    0xf519cfe7,// 258 PAY 219 

    0x9d33935d,// 259 PAY 220 

    0xdff233b4,// 260 PAY 221 

    0xf12cd30c,// 261 PAY 222 

    0x50f88b42,// 262 PAY 223 

    0x72910d28,// 263 PAY 224 

    0x46f11825,// 264 PAY 225 

    0xce87d293,// 265 PAY 226 

    0x2addc913,// 266 PAY 227 

    0xd5c98420,// 267 PAY 228 

    0x4771ce6f,// 268 PAY 229 

    0xff279a31,// 269 PAY 230 

    0x3e105f09,// 270 PAY 231 

    0x8092c098,// 271 PAY 232 

    0xb9bfe2b9,// 272 PAY 233 

    0xdedf8d50,// 273 PAY 234 

    0xa98732f7,// 274 PAY 235 

    0xf7ee8896,// 275 PAY 236 

    0xa3ab4bf2,// 276 PAY 237 

    0x969641f4,// 277 PAY 238 

    0xe14fe560,// 278 PAY 239 

    0x2606912b,// 279 PAY 240 

    0x84ee38c1,// 280 PAY 241 

    0xaa121dd3,// 281 PAY 242 

    0xb0f532ec,// 282 PAY 243 

    0xf93b7e43,// 283 PAY 244 

    0x7b635909,// 284 PAY 245 

    0x60460fb4,// 285 PAY 246 

    0x6115df7b,// 286 PAY 247 

    0x73fd209a,// 287 PAY 248 

    0x81850ba7,// 288 PAY 249 

    0xd4835109,// 289 PAY 250 

    0x0e6da804,// 290 PAY 251 

    0x149ee413,// 291 PAY 252 

    0x68c31c4a,// 292 PAY 253 

    0x489dda12,// 293 PAY 254 

    0xf071e4ae,// 294 PAY 255 

    0x2c3743d7,// 295 PAY 256 

    0xce2b72a3,// 296 PAY 257 

    0xd1e010a2,// 297 PAY 258 

    0x3f28f888,// 298 PAY 259 

    0x1156fac5,// 299 PAY 260 

    0x139a93a6,// 300 PAY 261 

    0x35500adb,// 301 PAY 262 

    0x88150000,// 302 PAY 263 

/// STA is 1 words. 

/// STA num_pkts       : 111 

/// STA pkt_idx        : 124 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x4d 

    0x01f04d6f // 303 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt75_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x02 

/// ECH pdu_tag        : 0x00 

    0x00020000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv insert_icv check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000019,// 3 SCX   1 

    0x80924898,// 4 SCX   2 

    0x00003582,// 5 SCX   3 

    0xe8295049,// 6 SCX   4 

    0x7667f126,// 7 SCX   5 

    0x1906c421,// 8 SCX   6 

    0xccc90b69,// 9 SCX   7 

    0xa3b7f3f4,// 10 SCX   8 

    0xd408c780,// 11 SCX   9 

    0x30cb3452,// 12 SCX  10 

    0x3b17cce8,// 13 SCX  11 

    0x92b1b8f2,// 14 SCX  12 

    0xf34968ef,// 15 SCX  13 

    0xe301e4b5,// 16 SCX  14 

    0x257520e6,// 17 SCX  15 

    0x9004011e,// 18 SCX  16 

    0xb29d66a3,// 19 SCX  17 

    0x257dead4,// 20 SCX  18 

    0x77bd714f,// 21 SCX  19 

    0xceb39b2a,// 22 SCX  20 

    0x4ceb23ed,// 23 SCX  21 

    0xc4de7c3e,// 24 SCX  22 

    0x843134b0,// 25 SCX  23 

    0x0940ac50,// 26 SCX  24 

    0x25fa5d4c,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 1754 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 417 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 417 

/// BFD lencrypto      : 28 

/// BFD ofstcrypto     : 372 

/// BFD (ofst+len)cry  : 400 

/// BFD ofstiv         : 292 

/// BFD ofsticv        : 872 

    0x000001a1,// 28 BFD   1 

    0x0174001c,// 29 BFD   2 

    0x03680124,// 30 BFD   3 

/// MFM is 14 words. 

/// MFM vldnibs        : 65 

    0x6500c0a3,// 31 MFM   1 

    0x2bbac793,// 32 MFM   2 

    0x4f8ffcde,// 33 MFM   3 

    0xee986b3a,// 34 MFM   4 

    0x1f959478,// 35 MFM   5 

    0x43ccf251,// 36 MFM   6 

    0xf3cc131e,// 37 MFM   7 

    0x9fea44a2,// 38 MFM   8 

    0x36fb6d00,// 39 MFM   9 

    0x2543ef1e,// 40 MFM  10 

    0x5a812fd3,// 41 MFM  11 

    0x16cd0d8d,// 42 MFM  12 

    0x22f29644,// 43 MFM  13 

    0xe0000000,// 44 MFM  14 

/// BDA is 440 words. 

/// BDA size     is 1754 (0x6da) 

/// BDA id       is 0xec5d 

    0x06daec5d,// 45 BDA   1 

/// PAY Generic Data size   : 1754 byte(s) 

/// PAD Buffer Data Pad size   : 2 byte(s) 

    0x01c8d7ac,// 46 PAY   1 

    0x74048048,// 47 PAY   2 

    0xc12fea9a,// 48 PAY   3 

    0xb93c9e5a,// 49 PAY   4 

    0x848fdf48,// 50 PAY   5 

    0x033ee831,// 51 PAY   6 

    0xf316f7d1,// 52 PAY   7 

    0x1b4f84a6,// 53 PAY   8 

    0xa0e9f697,// 54 PAY   9 

    0xc7f6b567,// 55 PAY  10 

    0xcbdb3466,// 56 PAY  11 

    0x78b306c7,// 57 PAY  12 

    0xe82d37d2,// 58 PAY  13 

    0xff3a6934,// 59 PAY  14 

    0x69f16c49,// 60 PAY  15 

    0x1d73230f,// 61 PAY  16 

    0x9ea291d7,// 62 PAY  17 

    0x07c7ec22,// 63 PAY  18 

    0xdfdc0c6e,// 64 PAY  19 

    0xa055e028,// 65 PAY  20 

    0xe6286730,// 66 PAY  21 

    0x273cc1e9,// 67 PAY  22 

    0x4241c85c,// 68 PAY  23 

    0xbb090f39,// 69 PAY  24 

    0x0a903727,// 70 PAY  25 

    0x02f28f50,// 71 PAY  26 

    0x49654a69,// 72 PAY  27 

    0x991ecbe5,// 73 PAY  28 

    0xccc0724e,// 74 PAY  29 

    0x766e22a1,// 75 PAY  30 

    0xdcc1ed99,// 76 PAY  31 

    0x81a7efea,// 77 PAY  32 

    0x5296cf73,// 78 PAY  33 

    0x9cc13b28,// 79 PAY  34 

    0x8c04ea9d,// 80 PAY  35 

    0x6049be21,// 81 PAY  36 

    0x0628b9d4,// 82 PAY  37 

    0x7d6a2649,// 83 PAY  38 

    0x576ac4ce,// 84 PAY  39 

    0x7d268f65,// 85 PAY  40 

    0x2a11e3b0,// 86 PAY  41 

    0x156eb59a,// 87 PAY  42 

    0x05da577a,// 88 PAY  43 

    0xd9593655,// 89 PAY  44 

    0x7a8b8247,// 90 PAY  45 

    0xdd0d85fb,// 91 PAY  46 

    0xd70447fb,// 92 PAY  47 

    0xd89278ea,// 93 PAY  48 

    0x9f7ae760,// 94 PAY  49 

    0xfac4046d,// 95 PAY  50 

    0x6798d58c,// 96 PAY  51 

    0x79f1af43,// 97 PAY  52 

    0x4e5d13a6,// 98 PAY  53 

    0x55134754,// 99 PAY  54 

    0x04e4692c,// 100 PAY  55 

    0x87a576fa,// 101 PAY  56 

    0xb3ae88ad,// 102 PAY  57 

    0x46684fde,// 103 PAY  58 

    0x77ee3484,// 104 PAY  59 

    0xa95396dc,// 105 PAY  60 

    0x79cfdbda,// 106 PAY  61 

    0xc9171cb9,// 107 PAY  62 

    0xc06e3208,// 108 PAY  63 

    0xb1072a52,// 109 PAY  64 

    0x211e95ed,// 110 PAY  65 

    0x3114258e,// 111 PAY  66 

    0x3e0d0c38,// 112 PAY  67 

    0xfdb9e7ab,// 113 PAY  68 

    0xb1691085,// 114 PAY  69 

    0x37fb6479,// 115 PAY  70 

    0x637e8d3e,// 116 PAY  71 

    0x0a2d83a5,// 117 PAY  72 

    0x9ab66010,// 118 PAY  73 

    0xf9b988ed,// 119 PAY  74 

    0x9c665b04,// 120 PAY  75 

    0xf8b69799,// 121 PAY  76 

    0x60c693cc,// 122 PAY  77 

    0xcc8cbaf1,// 123 PAY  78 

    0x6a2197bd,// 124 PAY  79 

    0x22ee16e1,// 125 PAY  80 

    0x6ff8ede5,// 126 PAY  81 

    0x6360056f,// 127 PAY  82 

    0xfce3c065,// 128 PAY  83 

    0xab6a0261,// 129 PAY  84 

    0xaf63f9f1,// 130 PAY  85 

    0x859b1fb2,// 131 PAY  86 

    0x01dc02be,// 132 PAY  87 

    0x0ba26857,// 133 PAY  88 

    0x4d6dcc72,// 134 PAY  89 

    0x7c9b7dba,// 135 PAY  90 

    0x99aaa779,// 136 PAY  91 

    0x74e7056d,// 137 PAY  92 

    0xccc142f4,// 138 PAY  93 

    0x374935e9,// 139 PAY  94 

    0x0e657988,// 140 PAY  95 

    0x4538f3a6,// 141 PAY  96 

    0xc5444401,// 142 PAY  97 

    0xb14a36d6,// 143 PAY  98 

    0x97a33285,// 144 PAY  99 

    0x9b0e3a5b,// 145 PAY 100 

    0xb9e8d83c,// 146 PAY 101 

    0x3635ccba,// 147 PAY 102 

    0x16299061,// 148 PAY 103 

    0xbb34579c,// 149 PAY 104 

    0x102f6a1b,// 150 PAY 105 

    0x0863feee,// 151 PAY 106 

    0x6c611e82,// 152 PAY 107 

    0x324144a7,// 153 PAY 108 

    0x8042743a,// 154 PAY 109 

    0xa4ca96ed,// 155 PAY 110 

    0x08c49431,// 156 PAY 111 

    0x3169a774,// 157 PAY 112 

    0xfda07886,// 158 PAY 113 

    0x6ed2d6ae,// 159 PAY 114 

    0x85130d27,// 160 PAY 115 

    0x48a1f0ac,// 161 PAY 116 

    0xcf3dc58c,// 162 PAY 117 

    0xed46fc5b,// 163 PAY 118 

    0xb603259c,// 164 PAY 119 

    0x4389e559,// 165 PAY 120 

    0xed7d6e53,// 166 PAY 121 

    0xbb222be8,// 167 PAY 122 

    0xe80a3c60,// 168 PAY 123 

    0x25dd6bd3,// 169 PAY 124 

    0xfa996443,// 170 PAY 125 

    0xdd68b91a,// 171 PAY 126 

    0xfd12653b,// 172 PAY 127 

    0xb3d4d4f4,// 173 PAY 128 

    0xf7f3b4cb,// 174 PAY 129 

    0x51863a67,// 175 PAY 130 

    0xf95ecb32,// 176 PAY 131 

    0x4e5292ff,// 177 PAY 132 

    0x1078a75c,// 178 PAY 133 

    0xf4b16e9c,// 179 PAY 134 

    0xc761e40d,// 180 PAY 135 

    0x718da36c,// 181 PAY 136 

    0xd36d1814,// 182 PAY 137 

    0x7144bde2,// 183 PAY 138 

    0x0b2cb55d,// 184 PAY 139 

    0x902b34db,// 185 PAY 140 

    0xcd395b34,// 186 PAY 141 

    0x7060f384,// 187 PAY 142 

    0xdfc1f9ce,// 188 PAY 143 

    0xe5921e99,// 189 PAY 144 

    0x2a9239a8,// 190 PAY 145 

    0x9b4a7837,// 191 PAY 146 

    0x6fe45c67,// 192 PAY 147 

    0x0ca631c1,// 193 PAY 148 

    0x51850fbe,// 194 PAY 149 

    0xe9954492,// 195 PAY 150 

    0x11b06f85,// 196 PAY 151 

    0xbc3ef2f0,// 197 PAY 152 

    0x2b6ecd20,// 198 PAY 153 

    0x59a0a286,// 199 PAY 154 

    0x1e9ec3b3,// 200 PAY 155 

    0x78ad21a6,// 201 PAY 156 

    0x6434626c,// 202 PAY 157 

    0xe982e302,// 203 PAY 158 

    0x93a87232,// 204 PAY 159 

    0x995eecc0,// 205 PAY 160 

    0x34a89ed5,// 206 PAY 161 

    0x542cc95d,// 207 PAY 162 

    0xa09039df,// 208 PAY 163 

    0x634ac035,// 209 PAY 164 

    0x16ab99c4,// 210 PAY 165 

    0x7cbc23d9,// 211 PAY 166 

    0x64978232,// 212 PAY 167 

    0x028d2da0,// 213 PAY 168 

    0x8685f3d8,// 214 PAY 169 

    0x408d0cfc,// 215 PAY 170 

    0x164dfdc3,// 216 PAY 171 

    0xcdde7500,// 217 PAY 172 

    0xfaaf99de,// 218 PAY 173 

    0xd6c91923,// 219 PAY 174 

    0x56a4413c,// 220 PAY 175 

    0xcfc34069,// 221 PAY 176 

    0x03a6d173,// 222 PAY 177 

    0x43ff130a,// 223 PAY 178 

    0x9546f30e,// 224 PAY 179 

    0xf429e2d2,// 225 PAY 180 

    0xf3ca7342,// 226 PAY 181 

    0x9f789bf9,// 227 PAY 182 

    0xfcd9e583,// 228 PAY 183 

    0xeb714614,// 229 PAY 184 

    0xfe9aa0fd,// 230 PAY 185 

    0xc0e7ee1e,// 231 PAY 186 

    0x86febbaf,// 232 PAY 187 

    0x762605f0,// 233 PAY 188 

    0x3db7f61b,// 234 PAY 189 

    0x18fe7652,// 235 PAY 190 

    0xd511bc0e,// 236 PAY 191 

    0xe92347d4,// 237 PAY 192 

    0x81b7ec0f,// 238 PAY 193 

    0x8952300b,// 239 PAY 194 

    0x8488a0c5,// 240 PAY 195 

    0x48ba0f5a,// 241 PAY 196 

    0x7987d5d7,// 242 PAY 197 

    0xf4e0f882,// 243 PAY 198 

    0xcfffe034,// 244 PAY 199 

    0x41b6e3a8,// 245 PAY 200 

    0x7fc5ae6e,// 246 PAY 201 

    0x58419727,// 247 PAY 202 

    0x84c0cb4a,// 248 PAY 203 

    0x1d6000fc,// 249 PAY 204 

    0x60aa8138,// 250 PAY 205 

    0x84d97585,// 251 PAY 206 

    0x72f70149,// 252 PAY 207 

    0x4e5c5a00,// 253 PAY 208 

    0xd10d5fe7,// 254 PAY 209 

    0x68713a3f,// 255 PAY 210 

    0x5dc95f23,// 256 PAY 211 

    0xaca17107,// 257 PAY 212 

    0x1baae811,// 258 PAY 213 

    0xbdd6f988,// 259 PAY 214 

    0xa7bc68e2,// 260 PAY 215 

    0xd0c47522,// 261 PAY 216 

    0xeaab7163,// 262 PAY 217 

    0x079f277c,// 263 PAY 218 

    0x753a4492,// 264 PAY 219 

    0x2d2e92f2,// 265 PAY 220 

    0x21c13608,// 266 PAY 221 

    0x747cebab,// 267 PAY 222 

    0x131c0f82,// 268 PAY 223 

    0x7993633c,// 269 PAY 224 

    0x627bff5a,// 270 PAY 225 

    0x9c1be560,// 271 PAY 226 

    0x6c14b4dc,// 272 PAY 227 

    0x54bbd15f,// 273 PAY 228 

    0xa18cdab7,// 274 PAY 229 

    0x267cd62f,// 275 PAY 230 

    0xa46942be,// 276 PAY 231 

    0x7cd425c3,// 277 PAY 232 

    0x8ac45d72,// 278 PAY 233 

    0xa8c5b12a,// 279 PAY 234 

    0x165073df,// 280 PAY 235 

    0x7895da27,// 281 PAY 236 

    0x74c56897,// 282 PAY 237 

    0x18f50289,// 283 PAY 238 

    0x29055093,// 284 PAY 239 

    0x9da5a4ac,// 285 PAY 240 

    0xb0708275,// 286 PAY 241 

    0x2b8970e0,// 287 PAY 242 

    0x4e264700,// 288 PAY 243 

    0x7337d99e,// 289 PAY 244 

    0xb8eddaa8,// 290 PAY 245 

    0xcf3c8e15,// 291 PAY 246 

    0xb99ef9df,// 292 PAY 247 

    0xac629c70,// 293 PAY 248 

    0x40633ce5,// 294 PAY 249 

    0xf2b7f80c,// 295 PAY 250 

    0xb854bab7,// 296 PAY 251 

    0x74110381,// 297 PAY 252 

    0x56c4c116,// 298 PAY 253 

    0x28672516,// 299 PAY 254 

    0xd276d20d,// 300 PAY 255 

    0x8dbd196e,// 301 PAY 256 

    0x4bfaded0,// 302 PAY 257 

    0x00def49c,// 303 PAY 258 

    0xb4ebbd80,// 304 PAY 259 

    0xff3c7459,// 305 PAY 260 

    0x36f5fe95,// 306 PAY 261 

    0x62435af1,// 307 PAY 262 

    0xe2e25157,// 308 PAY 263 

    0x172034d2,// 309 PAY 264 

    0x7e0edced,// 310 PAY 265 

    0x5faf6659,// 311 PAY 266 

    0x41223389,// 312 PAY 267 

    0x5f033623,// 313 PAY 268 

    0xc5c0aa31,// 314 PAY 269 

    0xf8deec3b,// 315 PAY 270 

    0x4f6f75a3,// 316 PAY 271 

    0x0f760e69,// 317 PAY 272 

    0xec743082,// 318 PAY 273 

    0xaa397094,// 319 PAY 274 

    0xd941c36e,// 320 PAY 275 

    0x446ca146,// 321 PAY 276 

    0x35af4cc7,// 322 PAY 277 

    0x381dc555,// 323 PAY 278 

    0xdabcf880,// 324 PAY 279 

    0x82040dd6,// 325 PAY 280 

    0x11b4b910,// 326 PAY 281 

    0xf53a5a8e,// 327 PAY 282 

    0x3c078c11,// 328 PAY 283 

    0x8ebe6c43,// 329 PAY 284 

    0x02fbb658,// 330 PAY 285 

    0xbdb95197,// 331 PAY 286 

    0xee282435,// 332 PAY 287 

    0x4a509933,// 333 PAY 288 

    0x2b2dab1b,// 334 PAY 289 

    0x3b6b133c,// 335 PAY 290 

    0x952092cf,// 336 PAY 291 

    0x93b0d4c4,// 337 PAY 292 

    0x26c46f2c,// 338 PAY 293 

    0x0e713b04,// 339 PAY 294 

    0xcb773a52,// 340 PAY 295 

    0xe88a24da,// 341 PAY 296 

    0x9e41ff70,// 342 PAY 297 

    0x6533f0cc,// 343 PAY 298 

    0xb1c43086,// 344 PAY 299 

    0x797484ad,// 345 PAY 300 

    0xd517fe5e,// 346 PAY 301 

    0x643583a0,// 347 PAY 302 

    0x834d81a6,// 348 PAY 303 

    0x8fe74c29,// 349 PAY 304 

    0xdbe5e2e4,// 350 PAY 305 

    0x67e72da5,// 351 PAY 306 

    0xc42125cb,// 352 PAY 307 

    0x03cb6e75,// 353 PAY 308 

    0xcb9a6624,// 354 PAY 309 

    0xbbe5dd3f,// 355 PAY 310 

    0x05d5e2fe,// 356 PAY 311 

    0x6017179d,// 357 PAY 312 

    0x60649b74,// 358 PAY 313 

    0xf2837982,// 359 PAY 314 

    0xc9deaf13,// 360 PAY 315 

    0xcc5c822c,// 361 PAY 316 

    0x41144892,// 362 PAY 317 

    0xc113d1ba,// 363 PAY 318 

    0x632ebfe0,// 364 PAY 319 

    0x2ff6587f,// 365 PAY 320 

    0x3d5b7d3a,// 366 PAY 321 

    0x09eec3cb,// 367 PAY 322 

    0xf1deb2b4,// 368 PAY 323 

    0x9f993a5c,// 369 PAY 324 

    0xe3d0ddb5,// 370 PAY 325 

    0x3817c5f6,// 371 PAY 326 

    0x98ceb0c6,// 372 PAY 327 

    0x766113dd,// 373 PAY 328 

    0xcdab5bad,// 374 PAY 329 

    0xec1e7096,// 375 PAY 330 

    0x479cdab4,// 376 PAY 331 

    0x31aa2213,// 377 PAY 332 

    0x2a544efb,// 378 PAY 333 

    0x78a1a822,// 379 PAY 334 

    0xd82d4567,// 380 PAY 335 

    0xd8fdadcf,// 381 PAY 336 

    0xa030b99a,// 382 PAY 337 

    0x16c3192f,// 383 PAY 338 

    0x3a547823,// 384 PAY 339 

    0x74aac38a,// 385 PAY 340 

    0xb60de313,// 386 PAY 341 

    0xd71835f8,// 387 PAY 342 

    0x6c920af3,// 388 PAY 343 

    0x217782e0,// 389 PAY 344 

    0x09e8397f,// 390 PAY 345 

    0x47abbdde,// 391 PAY 346 

    0x42ca9f58,// 392 PAY 347 

    0x6cef5265,// 393 PAY 348 

    0x54a9aabe,// 394 PAY 349 

    0x9bb72479,// 395 PAY 350 

    0x64ed60da,// 396 PAY 351 

    0xddf3b35f,// 397 PAY 352 

    0x9480271c,// 398 PAY 353 

    0x6f8b9959,// 399 PAY 354 

    0x4f59ec9f,// 400 PAY 355 

    0xbc5145fe,// 401 PAY 356 

    0x8cb55043,// 402 PAY 357 

    0x89317868,// 403 PAY 358 

    0x836899a6,// 404 PAY 359 

    0xa891d6ae,// 405 PAY 360 

    0x0b86cce6,// 406 PAY 361 

    0xe9eb057b,// 407 PAY 362 

    0x6b0bffba,// 408 PAY 363 

    0xc9fc98de,// 409 PAY 364 

    0xa3de6a84,// 410 PAY 365 

    0x92a91bb6,// 411 PAY 366 

    0xc50a3d44,// 412 PAY 367 

    0x1997fdda,// 413 PAY 368 

    0x88272f7b,// 414 PAY 369 

    0xf6883a3b,// 415 PAY 370 

    0xd15af502,// 416 PAY 371 

    0x4a971ae3,// 417 PAY 372 

    0xb805b529,// 418 PAY 373 

    0xaa10e06b,// 419 PAY 374 

    0x710610f6,// 420 PAY 375 

    0x3436aec4,// 421 PAY 376 

    0xdd50ccf5,// 422 PAY 377 

    0x4ec43d8e,// 423 PAY 378 

    0x71d3ba3a,// 424 PAY 379 

    0x63e8e08e,// 425 PAY 380 

    0xa8f3a476,// 426 PAY 381 

    0x9f962bd8,// 427 PAY 382 

    0xfa233a8d,// 428 PAY 383 

    0xc2da2794,// 429 PAY 384 

    0x0cee2ec5,// 430 PAY 385 

    0xa1de9b66,// 431 PAY 386 

    0xe2c30d53,// 432 PAY 387 

    0x7614c910,// 433 PAY 388 

    0xe62497ee,// 434 PAY 389 

    0xb4995084,// 435 PAY 390 

    0x35c15f31,// 436 PAY 391 

    0x7017f65b,// 437 PAY 392 

    0xed7c2e18,// 438 PAY 393 

    0xd3dc05e4,// 439 PAY 394 

    0x5fb695ab,// 440 PAY 395 

    0xa8c7062e,// 441 PAY 396 

    0x8baa42bc,// 442 PAY 397 

    0x418d1931,// 443 PAY 398 

    0xfad492cc,// 444 PAY 399 

    0xeb9f3ebe,// 445 PAY 400 

    0x143f8810,// 446 PAY 401 

    0xb9d5270d,// 447 PAY 402 

    0xe0615aeb,// 448 PAY 403 

    0xeb30cc52,// 449 PAY 404 

    0x1486cf9a,// 450 PAY 405 

    0xf00c27fb,// 451 PAY 406 

    0x78c2d862,// 452 PAY 407 

    0x3585e71f,// 453 PAY 408 

    0x508a3576,// 454 PAY 409 

    0x730218d1,// 455 PAY 410 

    0x317ab156,// 456 PAY 411 

    0x7f10e41b,// 457 PAY 412 

    0x36c02d08,// 458 PAY 413 

    0xe016a3eb,// 459 PAY 414 

    0x7e44bf63,// 460 PAY 415 

    0x6e253d43,// 461 PAY 416 

    0x96da5ac1,// 462 PAY 417 

    0x81ea9a2d,// 463 PAY 418 

    0x3b57abd2,// 464 PAY 419 

    0x2a02f90a,// 465 PAY 420 

    0x8f224017,// 466 PAY 421 

    0xc18144c3,// 467 PAY 422 

    0xe0ada1ad,// 468 PAY 423 

    0x3c52aac9,// 469 PAY 424 

    0x39adc753,// 470 PAY 425 

    0xa7c5f334,// 471 PAY 426 

    0x3e3eac07,// 472 PAY 427 

    0xfa9ac5df,// 473 PAY 428 

    0x9d4abf1a,// 474 PAY 429 

    0xa063a1e8,// 475 PAY 430 

    0x8ed1e4c3,// 476 PAY 431 

    0x4f2b5333,// 477 PAY 432 

    0xd1018462,// 478 PAY 433 

    0x3cbec1d5,// 479 PAY 434 

    0xdbca9d94,// 480 PAY 435 

    0x24da9978,// 481 PAY 436 

    0x58b77315,// 482 PAY 437 

    0x097ee72f,// 483 PAY 438 

    0x8d850000,// 484 PAY 439 

/// STA is 1 words. 

/// STA num_pkts       : 147 

/// STA pkt_idx        : 180 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x96 

    0x02d09693 // 485 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 72 (0x48) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt76_tmpl[] = {
    0xb8010048,// 1 CCH   1 

/// ECH cache_idx      : 0x05 

/// ECH pdu_tag        : 0x00 

    0x00050000,// 2 ECH   1 

/// SCX is 17 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv !insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000011,// 3 SCX   1 

    0x8080483a,// 4 SCX   2 

    0x00001500,// 5 SCX   3 

    0x014c8dc1,// 6 SCX   4 

    0x855a7b27,// 7 SCX   5 

    0xd210aede,// 8 SCX   6 

    0x8805dc62,// 9 SCX   7 

    0xfe73a041,// 10 SCX   8 

    0x96bd2bbc,// 11 SCX   9 

    0x7547e3d5,// 12 SCX  10 

    0x83ef82cb,// 13 SCX  11 

    0x747f81d8,// 14 SCX  12 

    0xc2b3ad7a,// 15 SCX  13 

    0x9b274780,// 16 SCX  14 

    0x96efac3a,// 17 SCX  15 

    0xaa472b78,// 18 SCX  16 

    0xc021cf6f,// 19 SCX  17 

/// BFD is 3 words. 

/// BFD tot_len        : 1206 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 303 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 303 

/// BFD lencrypto      : 160 

/// BFD ofstcrypto     : 32 

/// BFD (ofst+len)cry  : 192 

/// BFD ofstiv         : 4 

/// BFD ofsticv        : 512 

    0x0000012f,// 20 BFD   1 

    0x002000a0,// 21 BFD   2 

    0x02000004,// 22 BFD   3 

/// MFM is 9 words. 

/// MFM vldnibs        : 3d 

    0x3d002e3f,// 23 MFM   1 

    0x437add57,// 24 MFM   2 

    0xefed61b4,// 25 MFM   3 

    0x229e914a,// 26 MFM   4 

    0xbd8902f7,// 27 MFM   5 

    0xb73f29d8,// 28 MFM   6 

    0xb47525a8,// 29 MFM   7 

    0xc733972c,// 30 MFM   8 

    0x60000000,// 31 MFM   9 

/// BDA is 303 words. 

/// BDA size     is 1206 (0x4b6) 

/// BDA id       is 0xd76a 

    0x04b6d76a,// 32 BDA   1 

/// PAY Generic Data size   : 1206 byte(s) 

/// PAD Buffer Data Pad size   : 2 byte(s) 

    0xb70bd23b,// 33 PAY   1 

    0x88602dbd,// 34 PAY   2 

    0x285e8169,// 35 PAY   3 

    0xf3e9bd9b,// 36 PAY   4 

    0xdf9754d2,// 37 PAY   5 

    0xb9db87a2,// 38 PAY   6 

    0x86040217,// 39 PAY   7 

    0xd16007e4,// 40 PAY   8 

    0xadefe844,// 41 PAY   9 

    0x64ce8e6d,// 42 PAY  10 

    0xb9af821e,// 43 PAY  11 

    0x07b8f7f1,// 44 PAY  12 

    0xf3c35db9,// 45 PAY  13 

    0x867baa63,// 46 PAY  14 

    0x07178ba2,// 47 PAY  15 

    0x9e416f10,// 48 PAY  16 

    0x71e62928,// 49 PAY  17 

    0xb9e0f25f,// 50 PAY  18 

    0xff6c1060,// 51 PAY  19 

    0x6d4de737,// 52 PAY  20 

    0x63448c70,// 53 PAY  21 

    0xeec8eab1,// 54 PAY  22 

    0x41215e13,// 55 PAY  23 

    0xbbce3c80,// 56 PAY  24 

    0xb3b288f7,// 57 PAY  25 

    0x4ff8cb22,// 58 PAY  26 

    0xff7213e4,// 59 PAY  27 

    0x99cc2609,// 60 PAY  28 

    0x5bd5964c,// 61 PAY  29 

    0x1b7a45e4,// 62 PAY  30 

    0x140d79b7,// 63 PAY  31 

    0x6e56ebc4,// 64 PAY  32 

    0x51d4ee1f,// 65 PAY  33 

    0xd2a1f286,// 66 PAY  34 

    0x2b437c49,// 67 PAY  35 

    0xaf43bb8c,// 68 PAY  36 

    0xeeffcc56,// 69 PAY  37 

    0x7ad480e4,// 70 PAY  38 

    0xeb7ab620,// 71 PAY  39 

    0xe7edd351,// 72 PAY  40 

    0x088fb0c0,// 73 PAY  41 

    0x7bf8341e,// 74 PAY  42 

    0x70390d5f,// 75 PAY  43 

    0x58b6a63b,// 76 PAY  44 

    0x9435e18f,// 77 PAY  45 

    0x623c6b63,// 78 PAY  46 

    0xbe37a851,// 79 PAY  47 

    0xde6d54a0,// 80 PAY  48 

    0x9dbedcfc,// 81 PAY  49 

    0xadb4988c,// 82 PAY  50 

    0xa4e92bd7,// 83 PAY  51 

    0xdee07436,// 84 PAY  52 

    0xd17fffcb,// 85 PAY  53 

    0xe2ef5730,// 86 PAY  54 

    0x17080d11,// 87 PAY  55 

    0x9ef9ff22,// 88 PAY  56 

    0x99459a19,// 89 PAY  57 

    0x9d48c20e,// 90 PAY  58 

    0xb7257d77,// 91 PAY  59 

    0xa8baf3f9,// 92 PAY  60 

    0xe762f1ba,// 93 PAY  61 

    0x5affb523,// 94 PAY  62 

    0x54a2b300,// 95 PAY  63 

    0xee7e71d9,// 96 PAY  64 

    0x2857a653,// 97 PAY  65 

    0xfc7e6cdb,// 98 PAY  66 

    0x118f31c6,// 99 PAY  67 

    0xe88ea549,// 100 PAY  68 

    0xa46a3709,// 101 PAY  69 

    0xd650139e,// 102 PAY  70 

    0xc41a7d2b,// 103 PAY  71 

    0xb838011b,// 104 PAY  72 

    0x5ce2d841,// 105 PAY  73 

    0x996c8b92,// 106 PAY  74 

    0xd918350f,// 107 PAY  75 

    0xe74866d1,// 108 PAY  76 

    0x276cf890,// 109 PAY  77 

    0x0590eb8d,// 110 PAY  78 

    0xa2f86e69,// 111 PAY  79 

    0xd45ef1e0,// 112 PAY  80 

    0x4c2017db,// 113 PAY  81 

    0x8189c25b,// 114 PAY  82 

    0xa0bfbe7e,// 115 PAY  83 

    0x29548b55,// 116 PAY  84 

    0xc6eb2328,// 117 PAY  85 

    0xbaaa31d7,// 118 PAY  86 

    0xca024a53,// 119 PAY  87 

    0x475973ad,// 120 PAY  88 

    0x06c8fe74,// 121 PAY  89 

    0x31450756,// 122 PAY  90 

    0x5c7098f2,// 123 PAY  91 

    0x3663d52e,// 124 PAY  92 

    0xc1522d50,// 125 PAY  93 

    0xad5217ba,// 126 PAY  94 

    0xc8755afa,// 127 PAY  95 

    0x368c7622,// 128 PAY  96 

    0x2e87a51b,// 129 PAY  97 

    0xfa97cbb9,// 130 PAY  98 

    0x1986a696,// 131 PAY  99 

    0x3cd0a802,// 132 PAY 100 

    0x00d3ac23,// 133 PAY 101 

    0xb258a197,// 134 PAY 102 

    0xe29b1f2f,// 135 PAY 103 

    0xf73a015d,// 136 PAY 104 

    0x7611c9e1,// 137 PAY 105 

    0xa29d69b3,// 138 PAY 106 

    0x896a57ac,// 139 PAY 107 

    0x3eaee271,// 140 PAY 108 

    0xf0872f02,// 141 PAY 109 

    0x68da8af5,// 142 PAY 110 

    0x0149de5e,// 143 PAY 111 

    0x7a4aa272,// 144 PAY 112 

    0x2fcf4cc5,// 145 PAY 113 

    0xa32e6034,// 146 PAY 114 

    0xf939e570,// 147 PAY 115 

    0x5ae9709a,// 148 PAY 116 

    0x37290729,// 149 PAY 117 

    0xe27d6154,// 150 PAY 118 

    0x573dbb0e,// 151 PAY 119 

    0x7fe132d0,// 152 PAY 120 

    0x469e6318,// 153 PAY 121 

    0x0cf2b0f9,// 154 PAY 122 

    0xa72977d2,// 155 PAY 123 

    0x7d37d0d4,// 156 PAY 124 

    0xac9d1a77,// 157 PAY 125 

    0xfbbaabdb,// 158 PAY 126 

    0x00e75740,// 159 PAY 127 

    0xac1a0f9d,// 160 PAY 128 

    0xbf44b522,// 161 PAY 129 

    0x77026dd9,// 162 PAY 130 

    0x8c76ade3,// 163 PAY 131 

    0x20e8ced3,// 164 PAY 132 

    0x07ff145d,// 165 PAY 133 

    0xab0d6ec3,// 166 PAY 134 

    0x393b4d33,// 167 PAY 135 

    0xc0f2ed49,// 168 PAY 136 

    0x4459f623,// 169 PAY 137 

    0x1c41e7e4,// 170 PAY 138 

    0x49232bc0,// 171 PAY 139 

    0x2f774fc4,// 172 PAY 140 

    0xc57af5da,// 173 PAY 141 

    0x5a64080f,// 174 PAY 142 

    0x9794249d,// 175 PAY 143 

    0x7659b79e,// 176 PAY 144 

    0x8edfa118,// 177 PAY 145 

    0xe3a3039a,// 178 PAY 146 

    0x5e71a979,// 179 PAY 147 

    0x35e6b41d,// 180 PAY 148 

    0xb9db8b76,// 181 PAY 149 

    0x00220556,// 182 PAY 150 

    0x601a3a3e,// 183 PAY 151 

    0x406b2fcb,// 184 PAY 152 

    0x9ba5f5e5,// 185 PAY 153 

    0x0d0b97da,// 186 PAY 154 

    0xbc40269c,// 187 PAY 155 

    0xa6bc5c69,// 188 PAY 156 

    0x1f84b679,// 189 PAY 157 

    0xf675352e,// 190 PAY 158 

    0xa16c0b27,// 191 PAY 159 

    0x9d2b06bf,// 192 PAY 160 

    0x3a801c45,// 193 PAY 161 

    0xbf0f16b1,// 194 PAY 162 

    0x0e4de8bc,// 195 PAY 163 

    0x8f63df05,// 196 PAY 164 

    0xbf2ba1bd,// 197 PAY 165 

    0xda616aec,// 198 PAY 166 

    0x1cf31104,// 199 PAY 167 

    0xcb59afa8,// 200 PAY 168 

    0x48baafbe,// 201 PAY 169 

    0x4e1ca358,// 202 PAY 170 

    0x398a480f,// 203 PAY 171 

    0xdd6bd614,// 204 PAY 172 

    0xd1c818d7,// 205 PAY 173 

    0xa8765f23,// 206 PAY 174 

    0xaaf16b14,// 207 PAY 175 

    0x19240aa0,// 208 PAY 176 

    0xea66c591,// 209 PAY 177 

    0xc2f33cb0,// 210 PAY 178 

    0x1aae809b,// 211 PAY 179 

    0x39e47c36,// 212 PAY 180 

    0xcec22f86,// 213 PAY 181 

    0x64581cb3,// 214 PAY 182 

    0xea1a5844,// 215 PAY 183 

    0xb91cfb8e,// 216 PAY 184 

    0xa1005c4c,// 217 PAY 185 

    0x4e36621c,// 218 PAY 186 

    0x063a8cdd,// 219 PAY 187 

    0x9a488820,// 220 PAY 188 

    0x5c4dbd85,// 221 PAY 189 

    0xdedfc6f7,// 222 PAY 190 

    0xad661a33,// 223 PAY 191 

    0xe21ddd97,// 224 PAY 192 

    0xa041aa06,// 225 PAY 193 

    0x7ac8703f,// 226 PAY 194 

    0x4bda2cc5,// 227 PAY 195 

    0x15e98f13,// 228 PAY 196 

    0x96a715bc,// 229 PAY 197 

    0x3ac6e9dd,// 230 PAY 198 

    0x7ea8a8d2,// 231 PAY 199 

    0xd7c14b90,// 232 PAY 200 

    0x037ccff0,// 233 PAY 201 

    0x6688ba51,// 234 PAY 202 

    0x025a28f2,// 235 PAY 203 

    0x4c2cb6c1,// 236 PAY 204 

    0x461b90dd,// 237 PAY 205 

    0x949721a4,// 238 PAY 206 

    0x97a08994,// 239 PAY 207 

    0xf48e479e,// 240 PAY 208 

    0x21527ad6,// 241 PAY 209 

    0xe91437a4,// 242 PAY 210 

    0xf89f161f,// 243 PAY 211 

    0xff154feb,// 244 PAY 212 

    0xdd0c7a92,// 245 PAY 213 

    0x1b2af819,// 246 PAY 214 

    0x06f19ce8,// 247 PAY 215 

    0x318ee3e9,// 248 PAY 216 

    0x3aa7f6f4,// 249 PAY 217 

    0xfe48d50f,// 250 PAY 218 

    0x9b7b950f,// 251 PAY 219 

    0x6b9859f8,// 252 PAY 220 

    0x3167f33a,// 253 PAY 221 

    0x362e2ad7,// 254 PAY 222 

    0x20cabdd3,// 255 PAY 223 

    0xe8052a12,// 256 PAY 224 

    0x362c3327,// 257 PAY 225 

    0x97c1ca03,// 258 PAY 226 

    0x23a59869,// 259 PAY 227 

    0xa22c3794,// 260 PAY 228 

    0x9fce7470,// 261 PAY 229 

    0x12f8e275,// 262 PAY 230 

    0x24547ca1,// 263 PAY 231 

    0x5ab73dd8,// 264 PAY 232 

    0x0786db4e,// 265 PAY 233 

    0x701f0304,// 266 PAY 234 

    0x95ebf6e7,// 267 PAY 235 

    0x24531661,// 268 PAY 236 

    0x9c7f1382,// 269 PAY 237 

    0x54974523,// 270 PAY 238 

    0x868c3e98,// 271 PAY 239 

    0x96bea438,// 272 PAY 240 

    0xbe40792f,// 273 PAY 241 

    0xdde9a14f,// 274 PAY 242 

    0x1635f810,// 275 PAY 243 

    0x8df2c9a7,// 276 PAY 244 

    0xcc977c7e,// 277 PAY 245 

    0xf94b7ee1,// 278 PAY 246 

    0x54a60ca1,// 279 PAY 247 

    0xa1b51829,// 280 PAY 248 

    0x5151653e,// 281 PAY 249 

    0xe6b087a9,// 282 PAY 250 

    0x6946f6ee,// 283 PAY 251 

    0x4984ad57,// 284 PAY 252 

    0x0cb07cd3,// 285 PAY 253 

    0xd0f9dd2f,// 286 PAY 254 

    0xeb8a6421,// 287 PAY 255 

    0xef9e5467,// 288 PAY 256 

    0xc010ec8c,// 289 PAY 257 

    0x0ceee0a8,// 290 PAY 258 

    0xb0f22e8e,// 291 PAY 259 

    0x058da70b,// 292 PAY 260 

    0x342d974a,// 293 PAY 261 

    0x3dbee534,// 294 PAY 262 

    0xdc77a295,// 295 PAY 263 

    0x603532d4,// 296 PAY 264 

    0x11b10792,// 297 PAY 265 

    0xedff7e1d,// 298 PAY 266 

    0x2157167e,// 299 PAY 267 

    0xde4b82c1,// 300 PAY 268 

    0x2579e5f0,// 301 PAY 269 

    0xe9b7e567,// 302 PAY 270 

    0x98447156,// 303 PAY 271 

    0x1f0b96b0,// 304 PAY 272 

    0xcf60922c,// 305 PAY 273 

    0xc7343df9,// 306 PAY 274 

    0xd9729f25,// 307 PAY 275 

    0x23fec0dc,// 308 PAY 276 

    0x78dbb687,// 309 PAY 277 

    0xf5f0f495,// 310 PAY 278 

    0x194e1e14,// 311 PAY 279 

    0xd156e853,// 312 PAY 280 

    0x253f2e30,// 313 PAY 281 

    0xbae375a7,// 314 PAY 282 

    0xd6424856,// 315 PAY 283 

    0xbf404e82,// 316 PAY 284 

    0x8852c00c,// 317 PAY 285 

    0x2bb59f01,// 318 PAY 286 

    0x3d87d386,// 319 PAY 287 

    0xb89a331e,// 320 PAY 288 

    0x3f279d83,// 321 PAY 289 

    0xda5c4c3a,// 322 PAY 290 

    0x20595838,// 323 PAY 291 

    0x1c40f492,// 324 PAY 292 

    0x51989775,// 325 PAY 293 

    0x7d53a98f,// 326 PAY 294 

    0x19054e49,// 327 PAY 295 

    0x33812981,// 328 PAY 296 

    0x3f00df34,// 329 PAY 297 

    0x77ea94bc,// 330 PAY 298 

    0x7e15ce08,// 331 PAY 299 

    0x66c27f93,// 332 PAY 300 

    0x92c7b865,// 333 PAY 301 

    0xac530000,// 334 PAY 302 

/// STA is 1 words. 

/// STA num_pkts       : 235 

/// STA pkt_idx        : 178 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x1c 

    0x02c81ceb // 335 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 96 (0x60) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt77_tmpl[] = {
    0xb8010060,// 1 CCH   1 

/// ECH cache_idx      : 0x08 

/// ECH pdu_tag        : 0x00 

    0x00080000,// 2 ECH   1 

/// SCX is 23 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv insert_icv check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000017,// 3 SCX   1 

    0x809148ab,// 4 SCX   2 

    0x00007182,// 5 SCX   3 

    0xa65a25b3,// 6 SCX   4 

    0x49cd7633,// 7 SCX   5 

    0x3bf24f47,// 8 SCX   6 

    0x68056339,// 9 SCX   7 

    0x5e1db01c,// 10 SCX   8 

    0xe7d86b9c,// 11 SCX   9 

    0xb04b6752,// 12 SCX  10 

    0xd9c24c37,// 13 SCX  11 

    0x21b59304,// 14 SCX  12 

    0x610a306d,// 15 SCX  13 

    0xb2f68dff,// 16 SCX  14 

    0x4e1c8b2e,// 17 SCX  15 

    0xe0e78f94,// 18 SCX  16 

    0x396230a6,// 19 SCX  17 

    0xdabfa876,// 20 SCX  18 

    0xc3f000c4,// 21 SCX  19 

    0x48dca982,// 22 SCX  20 

    0x0541c691,// 23 SCX  21 

    0xf03d9ecb,// 24 SCX  22 

    0xda0d4b35,// 25 SCX  23 

/// BFD is 3 words. 

/// BFD tot_len        : 914 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 773 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 773 

/// BFD lencrypto      : 316 

/// BFD ofstcrypto     : 416 

/// BFD (ofst+len)cry  : 732 

/// BFD ofstiv         : 312 

/// BFD ofsticv        : 840 

    0x00000305,// 26 BFD   1 

    0x01a0013c,// 27 BFD   2 

    0x03480138,// 28 BFD   3 

/// MFM is 5 words. 

/// MFM vldnibs        : 1d 

    0x1d004029,// 29 MFM   1 

    0x3cb52bcb,// 30 MFM   2 

    0x0db86895,// 31 MFM   3 

    0x1b43a8b2,// 32 MFM   4 

    0xa0000000,// 33 MFM   5 

/// BDA is 230 words. 

/// BDA size     is 914 (0x392) 

/// BDA id       is 0xaa5 

    0x03920aa5,// 34 BDA   1 

/// PAY Generic Data size   : 914 byte(s) 

/// PAD Buffer Data Pad size   : 2 byte(s) 

    0xc18f5c2a,// 35 PAY   1 

    0x00af5b06,// 36 PAY   2 

    0x4d91d0ba,// 37 PAY   3 

    0x474c0bd1,// 38 PAY   4 

    0x852ae63c,// 39 PAY   5 

    0xae2e3b9a,// 40 PAY   6 

    0x207571df,// 41 PAY   7 

    0xafa28488,// 42 PAY   8 

    0xbfd2fd3c,// 43 PAY   9 

    0xfda6d462,// 44 PAY  10 

    0xbb7f2da2,// 45 PAY  11 

    0xef825697,// 46 PAY  12 

    0x25e4ceb6,// 47 PAY  13 

    0x25ebb385,// 48 PAY  14 

    0x5efbefbd,// 49 PAY  15 

    0x57465be8,// 50 PAY  16 

    0xc62eccbb,// 51 PAY  17 

    0xd8f4740e,// 52 PAY  18 

    0xde70b080,// 53 PAY  19 

    0x37aa34bf,// 54 PAY  20 

    0xe763f7d8,// 55 PAY  21 

    0x2c60419c,// 56 PAY  22 

    0xb77aaf6b,// 57 PAY  23 

    0x07030f71,// 58 PAY  24 

    0xa9e0c1fc,// 59 PAY  25 

    0x16af5290,// 60 PAY  26 

    0xfad0e040,// 61 PAY  27 

    0x4d7117fc,// 62 PAY  28 

    0xad76ed0e,// 63 PAY  29 

    0x52ac3ca3,// 64 PAY  30 

    0x9cfa711a,// 65 PAY  31 

    0x06ba1d61,// 66 PAY  32 

    0x171d9438,// 67 PAY  33 

    0x1136e9e4,// 68 PAY  34 

    0xc8bf672a,// 69 PAY  35 

    0xc84ddbf0,// 70 PAY  36 

    0x50aa7dea,// 71 PAY  37 

    0xe7fab572,// 72 PAY  38 

    0x4488688c,// 73 PAY  39 

    0x566ade33,// 74 PAY  40 

    0x04b6b263,// 75 PAY  41 

    0xf8bbf3d7,// 76 PAY  42 

    0x294ebfed,// 77 PAY  43 

    0x49694676,// 78 PAY  44 

    0xe17145dd,// 79 PAY  45 

    0x795993cb,// 80 PAY  46 

    0x1093867c,// 81 PAY  47 

    0xd5471a81,// 82 PAY  48 

    0xf0705c8e,// 83 PAY  49 

    0x999e2a9e,// 84 PAY  50 

    0x94730033,// 85 PAY  51 

    0xfb580dd8,// 86 PAY  52 

    0x1fe3bf69,// 87 PAY  53 

    0x59841b14,// 88 PAY  54 

    0xc428db12,// 89 PAY  55 

    0xfca66c24,// 90 PAY  56 

    0x9250c07a,// 91 PAY  57 

    0x63746feb,// 92 PAY  58 

    0x90817ea6,// 93 PAY  59 

    0xfd5a283f,// 94 PAY  60 

    0x95411166,// 95 PAY  61 

    0x6c5738c8,// 96 PAY  62 

    0x9f41cc90,// 97 PAY  63 

    0x42b5993a,// 98 PAY  64 

    0x1e6551e9,// 99 PAY  65 

    0xcba0a303,// 100 PAY  66 

    0x1b6a29a4,// 101 PAY  67 

    0x24814d27,// 102 PAY  68 

    0xff2ddce5,// 103 PAY  69 

    0x6b9c5b6e,// 104 PAY  70 

    0x42ce5930,// 105 PAY  71 

    0x903048a5,// 106 PAY  72 

    0xd4bac7d6,// 107 PAY  73 

    0x70a0b83d,// 108 PAY  74 

    0x96dc2828,// 109 PAY  75 

    0x78d1733c,// 110 PAY  76 

    0x0f4af923,// 111 PAY  77 

    0xe892aa0e,// 112 PAY  78 

    0xf708a57c,// 113 PAY  79 

    0x7787b579,// 114 PAY  80 

    0x36e4218d,// 115 PAY  81 

    0xa0aa2b15,// 116 PAY  82 

    0x6a7fd9ef,// 117 PAY  83 

    0x9a97b9ac,// 118 PAY  84 

    0x02a9b47c,// 119 PAY  85 

    0xbbbbac6b,// 120 PAY  86 

    0x5fe8ff30,// 121 PAY  87 

    0xd560f6bf,// 122 PAY  88 

    0x8b66d100,// 123 PAY  89 

    0xe96a19c0,// 124 PAY  90 

    0x51078bb5,// 125 PAY  91 

    0xea2651b0,// 126 PAY  92 

    0x0bd2c585,// 127 PAY  93 

    0x57e4e379,// 128 PAY  94 

    0x239c1167,// 129 PAY  95 

    0x157d14d5,// 130 PAY  96 

    0x17b08f07,// 131 PAY  97 

    0x00fd8b2d,// 132 PAY  98 

    0x9e483079,// 133 PAY  99 

    0x7c373aa8,// 134 PAY 100 

    0x17f447c1,// 135 PAY 101 

    0x4a0ee021,// 136 PAY 102 

    0x6858a7dd,// 137 PAY 103 

    0x5e73874f,// 138 PAY 104 

    0x0e65d485,// 139 PAY 105 

    0x9f03b607,// 140 PAY 106 

    0x55a6ca00,// 141 PAY 107 

    0x46bc82fd,// 142 PAY 108 

    0x53b732e3,// 143 PAY 109 

    0xf34281c6,// 144 PAY 110 

    0x611b7bec,// 145 PAY 111 

    0x6ffa7223,// 146 PAY 112 

    0x311a7889,// 147 PAY 113 

    0x1959a3a8,// 148 PAY 114 

    0x214fffe5,// 149 PAY 115 

    0xf799c897,// 150 PAY 116 

    0x8bccea64,// 151 PAY 117 

    0x3b7c0691,// 152 PAY 118 

    0x826f163c,// 153 PAY 119 

    0x076bf044,// 154 PAY 120 

    0x13a7f3d1,// 155 PAY 121 

    0xe6ec8836,// 156 PAY 122 

    0xa43f15ab,// 157 PAY 123 

    0xa85e8290,// 158 PAY 124 

    0x4777c941,// 159 PAY 125 

    0x95538755,// 160 PAY 126 

    0x1c7f20f9,// 161 PAY 127 

    0x67059d14,// 162 PAY 128 

    0xa654ae90,// 163 PAY 129 

    0xe6e63a0c,// 164 PAY 130 

    0x6f6ebf47,// 165 PAY 131 

    0x821daab1,// 166 PAY 132 

    0xa444e950,// 167 PAY 133 

    0xf2c938cc,// 168 PAY 134 

    0x7372e5fb,// 169 PAY 135 

    0x1a616979,// 170 PAY 136 

    0x3325b2bc,// 171 PAY 137 

    0x06b9dd32,// 172 PAY 138 

    0x2b2b2a24,// 173 PAY 139 

    0xb5a5db99,// 174 PAY 140 

    0x7304f670,// 175 PAY 141 

    0x89c09b9b,// 176 PAY 142 

    0x9ec2e9d2,// 177 PAY 143 

    0xcc739b7e,// 178 PAY 144 

    0xe912f149,// 179 PAY 145 

    0xdbfc41b3,// 180 PAY 146 

    0x264296a6,// 181 PAY 147 

    0x55bf2ce5,// 182 PAY 148 

    0xebd5d9d2,// 183 PAY 149 

    0xf88d3b6b,// 184 PAY 150 

    0x968c60f2,// 185 PAY 151 

    0xa42dc846,// 186 PAY 152 

    0x947f645e,// 187 PAY 153 

    0x6ceee935,// 188 PAY 154 

    0x42e86267,// 189 PAY 155 

    0xc00bfb29,// 190 PAY 156 

    0xd3165107,// 191 PAY 157 

    0xa0691874,// 192 PAY 158 

    0x28e86171,// 193 PAY 159 

    0x4fa045e4,// 194 PAY 160 

    0x1b84410c,// 195 PAY 161 

    0x9ea7c2b6,// 196 PAY 162 

    0xd8211bbf,// 197 PAY 163 

    0xe4cc7884,// 198 PAY 164 

    0x68879612,// 199 PAY 165 

    0xdc7af4ab,// 200 PAY 166 

    0x016f9d1a,// 201 PAY 167 

    0xe38c0f1d,// 202 PAY 168 

    0x3f7af87c,// 203 PAY 169 

    0x93ff666e,// 204 PAY 170 

    0x4e18f921,// 205 PAY 171 

    0xec21d098,// 206 PAY 172 

    0x2d743128,// 207 PAY 173 

    0x8cb9e81d,// 208 PAY 174 

    0x27960121,// 209 PAY 175 

    0x6434ca8b,// 210 PAY 176 

    0x0f712fcf,// 211 PAY 177 

    0xf3145824,// 212 PAY 178 

    0x0e8b40e3,// 213 PAY 179 

    0x71f36867,// 214 PAY 180 

    0x1d813b23,// 215 PAY 181 

    0x58ebf956,// 216 PAY 182 

    0x9ee6261a,// 217 PAY 183 

    0x02b419e6,// 218 PAY 184 

    0x31f68080,// 219 PAY 185 

    0x39ed5859,// 220 PAY 186 

    0x7b2db9e6,// 221 PAY 187 

    0x3dece79b,// 222 PAY 188 

    0xa792193a,// 223 PAY 189 

    0x98e40185,// 224 PAY 190 

    0xe734ffb1,// 225 PAY 191 

    0xb5151117,// 226 PAY 192 

    0xe0d84119,// 227 PAY 193 

    0xeefee000,// 228 PAY 194 

    0xec93acdd,// 229 PAY 195 

    0xf1f16cdb,// 230 PAY 196 

    0x5a683189,// 231 PAY 197 

    0x54e427cb,// 232 PAY 198 

    0x669d7a51,// 233 PAY 199 

    0xaa2b9705,// 234 PAY 200 

    0xd3df2694,// 235 PAY 201 

    0xcd72a0fc,// 236 PAY 202 

    0xc600ccd9,// 237 PAY 203 

    0x4411dff2,// 238 PAY 204 

    0xe8e0ebc8,// 239 PAY 205 

    0x7e88e415,// 240 PAY 206 

    0xfeacf916,// 241 PAY 207 

    0x4741a800,// 242 PAY 208 

    0x90f38208,// 243 PAY 209 

    0x91771327,// 244 PAY 210 

    0x3eddb84f,// 245 PAY 211 

    0x0e1c7a93,// 246 PAY 212 

    0x344c9291,// 247 PAY 213 

    0x9e9b6a4f,// 248 PAY 214 

    0xe7620d50,// 249 PAY 215 

    0x1787f7f0,// 250 PAY 216 

    0x0a736e27,// 251 PAY 217 

    0x0bc8e65f,// 252 PAY 218 

    0x869e4f2a,// 253 PAY 219 

    0xb92333c9,// 254 PAY 220 

    0x322aa4d9,// 255 PAY 221 

    0x69698dad,// 256 PAY 222 

    0x229be6ba,// 257 PAY 223 

    0xaf19c359,// 258 PAY 224 

    0x0822641e,// 259 PAY 225 

    0xcc0289f9,// 260 PAY 226 

    0xcc6031ef,// 261 PAY 227 

    0x92aeebc2,// 262 PAY 228 

    0x80770000,// 263 PAY 229 

/// STA is 1 words. 

/// STA num_pkts       : 254 

/// STA pkt_idx        : 71 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xbe 

    0x011dbefe // 264 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt78_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x00 

/// ECH pdu_tag        : 0x00 

    0x00000000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound save_icv insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000019,// 3 SCX   1 

    0x809248af,// 4 SCX   2 

    0x000061c2,// 5 SCX   3 

    0x90351699,// 6 SCX   4 

    0x61129b68,// 7 SCX   5 

    0x8f793ab3,// 8 SCX   6 

    0xe18a3f7e,// 9 SCX   7 

    0x5fb6fe6c,// 10 SCX   8 

    0x0b1d1aa6,// 11 SCX   9 

    0x79e94c0e,// 12 SCX  10 

    0xa0c25db3,// 13 SCX  11 

    0x825da7f1,// 14 SCX  12 

    0xbe4f9f79,// 15 SCX  13 

    0xf112447b,// 16 SCX  14 

    0x1dbe92b7,// 17 SCX  15 

    0xc3a91a68,// 18 SCX  16 

    0x1a354c12,// 19 SCX  17 

    0x6745138a,// 20 SCX  18 

    0x3c62f524,// 21 SCX  19 

    0xd8dcbe5e,// 22 SCX  20 

    0x26b2532c,// 23 SCX  21 

    0x99c4cff9,// 24 SCX  22 

    0xd997c306,// 25 SCX  23 

    0xa62b843e,// 26 SCX  24 

    0x2e52661b,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 1867 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 801 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 801 

/// BFD lencrypto      : 156 

/// BFD ofstcrypto     : 636 

/// BFD (ofst+len)cry  : 792 

/// BFD ofstiv         : 608 

/// BFD ofsticv        : 1080 

    0x00000321,// 28 BFD   1 

    0x027c009c,// 29 BFD   2 

    0x04380260,// 30 BFD   3 

/// MFM is 16 words. 

/// MFM vldnibs        : 7a 

    0x7a00dc8f,// 31 MFM   1 

    0x0ef18a94,// 32 MFM   2 

    0x4129902d,// 33 MFM   3 

    0xca029e44,// 34 MFM   4 

    0x5f628602,// 35 MFM   5 

    0xb6b16dc4,// 36 MFM   6 

    0x39384716,// 37 MFM   7 

    0xc958a178,// 38 MFM   8 

    0xde2044b8,// 39 MFM   9 

    0x26a37dc4,// 40 MFM  10 

    0x48e441f1,// 41 MFM  11 

    0x151c4ca4,// 42 MFM  12 

    0x814fffbf,// 43 MFM  13 

    0xd86adfe5,// 44 MFM  14 

    0x5db73dcf,// 45 MFM  15 

    0xf06e0100,// 46 MFM  16 

/// BDA is 468 words. 

/// BDA size     is 1867 (0x74b) 

/// BDA id       is 0xdef3 

    0x074bdef3,// 47 BDA   1 

/// PAY Generic Data size   : 1867 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0xc36d0202,// 48 PAY   1 

    0xaf50a402,// 49 PAY   2 

    0x379e75ec,// 50 PAY   3 

    0x882d29ed,// 51 PAY   4 

    0xfc20d619,// 52 PAY   5 

    0x3a46b6e1,// 53 PAY   6 

    0x52f48fb6,// 54 PAY   7 

    0x14b718da,// 55 PAY   8 

    0x96321fff,// 56 PAY   9 

    0x2c06312d,// 57 PAY  10 

    0xca284945,// 58 PAY  11 

    0x804a72e9,// 59 PAY  12 

    0x39a65ab2,// 60 PAY  13 

    0x25ca096c,// 61 PAY  14 

    0x90649540,// 62 PAY  15 

    0x55e408bd,// 63 PAY  16 

    0xe3b7a4b3,// 64 PAY  17 

    0x3d552aaa,// 65 PAY  18 

    0x56404f62,// 66 PAY  19 

    0xc902b875,// 67 PAY  20 

    0x841cc291,// 68 PAY  21 

    0xf118d9cd,// 69 PAY  22 

    0x6ac39bdc,// 70 PAY  23 

    0x6bfaa1a7,// 71 PAY  24 

    0xe3a5f167,// 72 PAY  25 

    0xda098f67,// 73 PAY  26 

    0x5e03fc13,// 74 PAY  27 

    0x2567c89b,// 75 PAY  28 

    0xb4c358d6,// 76 PAY  29 

    0x256d53f4,// 77 PAY  30 

    0xc279fbe6,// 78 PAY  31 

    0xf8814ce0,// 79 PAY  32 

    0x51f52eb3,// 80 PAY  33 

    0xa2d05c20,// 81 PAY  34 

    0xb625f3dd,// 82 PAY  35 

    0x497ed5fe,// 83 PAY  36 

    0x7de7bdba,// 84 PAY  37 

    0xab08a209,// 85 PAY  38 

    0xd8d62b09,// 86 PAY  39 

    0xcdbacb1c,// 87 PAY  40 

    0x9480147e,// 88 PAY  41 

    0xabce81bd,// 89 PAY  42 

    0xd346676d,// 90 PAY  43 

    0x12883534,// 91 PAY  44 

    0x933532ec,// 92 PAY  45 

    0x2f07df39,// 93 PAY  46 

    0x7db6f826,// 94 PAY  47 

    0x214287e8,// 95 PAY  48 

    0x4ca95985,// 96 PAY  49 

    0x655109af,// 97 PAY  50 

    0x926b400e,// 98 PAY  51 

    0x45acc4b7,// 99 PAY  52 

    0xfe7dfed3,// 100 PAY  53 

    0x60bda922,// 101 PAY  54 

    0x5efab7e4,// 102 PAY  55 

    0x32998e3d,// 103 PAY  56 

    0x3439883c,// 104 PAY  57 

    0x6f0c6ca6,// 105 PAY  58 

    0x560a3cc9,// 106 PAY  59 

    0x09e3bc8f,// 107 PAY  60 

    0xe09e90a8,// 108 PAY  61 

    0xbf78699d,// 109 PAY  62 

    0xcc085612,// 110 PAY  63 

    0xcd75c6b1,// 111 PAY  64 

    0x230124bf,// 112 PAY  65 

    0x350e94f3,// 113 PAY  66 

    0x3c06ff0e,// 114 PAY  67 

    0x992bbe68,// 115 PAY  68 

    0x026cfabe,// 116 PAY  69 

    0xb00c00d9,// 117 PAY  70 

    0xd5b44625,// 118 PAY  71 

    0x1495aee2,// 119 PAY  72 

    0x1ebe6595,// 120 PAY  73 

    0x3f1c051e,// 121 PAY  74 

    0x8b801897,// 122 PAY  75 

    0xfea26028,// 123 PAY  76 

    0x99d8ab51,// 124 PAY  77 

    0xb54a3f71,// 125 PAY  78 

    0x56a0d332,// 126 PAY  79 

    0x01ecaca6,// 127 PAY  80 

    0xfba62d7c,// 128 PAY  81 

    0xc4da2c11,// 129 PAY  82 

    0xb339373a,// 130 PAY  83 

    0x9637ef94,// 131 PAY  84 

    0x6e21db34,// 132 PAY  85 

    0x08c3c3f1,// 133 PAY  86 

    0x0881d705,// 134 PAY  87 

    0x315d62bc,// 135 PAY  88 

    0x13598c90,// 136 PAY  89 

    0x8b54ca15,// 137 PAY  90 

    0xd65ef1de,// 138 PAY  91 

    0x5abfad2d,// 139 PAY  92 

    0x2fb85e81,// 140 PAY  93 

    0xc7b0e368,// 141 PAY  94 

    0x74a7cca4,// 142 PAY  95 

    0x9354869c,// 143 PAY  96 

    0x1232b3cc,// 144 PAY  97 

    0x1d6b7d68,// 145 PAY  98 

    0xb9e53086,// 146 PAY  99 

    0x1a881009,// 147 PAY 100 

    0xd13a71a5,// 148 PAY 101 

    0x8b299e86,// 149 PAY 102 

    0x333f53d2,// 150 PAY 103 

    0xfd224ee6,// 151 PAY 104 

    0x1054a4d0,// 152 PAY 105 

    0x5ebe1444,// 153 PAY 106 

    0x9e84756a,// 154 PAY 107 

    0x47d23ee5,// 155 PAY 108 

    0x970ad201,// 156 PAY 109 

    0xb36c4f11,// 157 PAY 110 

    0xbdefb119,// 158 PAY 111 

    0x1293beda,// 159 PAY 112 

    0x3842030f,// 160 PAY 113 

    0x1b0b11bd,// 161 PAY 114 

    0x76503752,// 162 PAY 115 

    0x03f5504f,// 163 PAY 116 

    0xa5eaee5c,// 164 PAY 117 

    0x66493bb7,// 165 PAY 118 

    0xff3a15e5,// 166 PAY 119 

    0x54d93522,// 167 PAY 120 

    0xaefd6e13,// 168 PAY 121 

    0xb2c7114b,// 169 PAY 122 

    0xe5ab40ac,// 170 PAY 123 

    0xe4fca1a2,// 171 PAY 124 

    0x723b88b3,// 172 PAY 125 

    0xda3a8ea3,// 173 PAY 126 

    0x9e525f5d,// 174 PAY 127 

    0x829026b8,// 175 PAY 128 

    0x969c1faf,// 176 PAY 129 

    0x59f42ddf,// 177 PAY 130 

    0x1acc5a92,// 178 PAY 131 

    0xd8019c38,// 179 PAY 132 

    0x897b749a,// 180 PAY 133 

    0x25214dbb,// 181 PAY 134 

    0x4fc6b04b,// 182 PAY 135 

    0x5bfdd9d7,// 183 PAY 136 

    0xd590ea2e,// 184 PAY 137 

    0x48bb6885,// 185 PAY 138 

    0xc1086529,// 186 PAY 139 

    0x4ced6c8b,// 187 PAY 140 

    0xe1b73007,// 188 PAY 141 

    0xac7eacc5,// 189 PAY 142 

    0x3174c44e,// 190 PAY 143 

    0x267279aa,// 191 PAY 144 

    0x71015e2b,// 192 PAY 145 

    0x9a611578,// 193 PAY 146 

    0x73dbb5f9,// 194 PAY 147 

    0xb1e0ebd9,// 195 PAY 148 

    0xdfa974fd,// 196 PAY 149 

    0x99370a1b,// 197 PAY 150 

    0x2c33fc93,// 198 PAY 151 

    0x20844c07,// 199 PAY 152 

    0x5bdfc355,// 200 PAY 153 

    0x8a20cda7,// 201 PAY 154 

    0x00cdf8a0,// 202 PAY 155 

    0xf3ecf1a6,// 203 PAY 156 

    0xb214722f,// 204 PAY 157 

    0xbc6cdbf3,// 205 PAY 158 

    0x7a0009c2,// 206 PAY 159 

    0x3e3079cd,// 207 PAY 160 

    0x1194028e,// 208 PAY 161 

    0x9614ba1f,// 209 PAY 162 

    0x1e3a97c0,// 210 PAY 163 

    0xb16115e0,// 211 PAY 164 

    0xbb9ebcfd,// 212 PAY 165 

    0x6cef26a9,// 213 PAY 166 

    0xcf761281,// 214 PAY 167 

    0x3f82f4f6,// 215 PAY 168 

    0x5d38504c,// 216 PAY 169 

    0x33c0ec2c,// 217 PAY 170 

    0xea82fd74,// 218 PAY 171 

    0x1fd331a9,// 219 PAY 172 

    0xac1747bb,// 220 PAY 173 

    0xfe0de254,// 221 PAY 174 

    0xec14c993,// 222 PAY 175 

    0x94ee108a,// 223 PAY 176 

    0x47d0b03a,// 224 PAY 177 

    0x3bb6dd0b,// 225 PAY 178 

    0x0e2f1bbf,// 226 PAY 179 

    0x76990639,// 227 PAY 180 

    0x2c697000,// 228 PAY 181 

    0x888d5069,// 229 PAY 182 

    0x27c47735,// 230 PAY 183 

    0x4d0e2d53,// 231 PAY 184 

    0x8430eb45,// 232 PAY 185 

    0x8e6024a3,// 233 PAY 186 

    0xec30854d,// 234 PAY 187 

    0x7aa727d3,// 235 PAY 188 

    0x7deb6efb,// 236 PAY 189 

    0xa2c10705,// 237 PAY 190 

    0xb9f14366,// 238 PAY 191 

    0x9301d24d,// 239 PAY 192 

    0xdccba2cc,// 240 PAY 193 

    0xdb3f97a3,// 241 PAY 194 

    0x3e891e76,// 242 PAY 195 

    0xe086fdbb,// 243 PAY 196 

    0x4d9de01e,// 244 PAY 197 

    0x78ea2542,// 245 PAY 198 

    0x212e4832,// 246 PAY 199 

    0x7e247031,// 247 PAY 200 

    0xfc788128,// 248 PAY 201 

    0x04f9b128,// 249 PAY 202 

    0xb2098eca,// 250 PAY 203 

    0x133e8e39,// 251 PAY 204 

    0x13980642,// 252 PAY 205 

    0xae4a2b03,// 253 PAY 206 

    0xacfda3c8,// 254 PAY 207 

    0x8df92c07,// 255 PAY 208 

    0x46ef107a,// 256 PAY 209 

    0xff09cf2a,// 257 PAY 210 

    0x31b3d890,// 258 PAY 211 

    0x1bff3ae0,// 259 PAY 212 

    0x98f81b5d,// 260 PAY 213 

    0x5fe9ad1e,// 261 PAY 214 

    0x6b76f8f5,// 262 PAY 215 

    0x241ef953,// 263 PAY 216 

    0x18d2efcd,// 264 PAY 217 

    0x6568cdac,// 265 PAY 218 

    0x554cffce,// 266 PAY 219 

    0x896e9da1,// 267 PAY 220 

    0xa8af9529,// 268 PAY 221 

    0x482bbb00,// 269 PAY 222 

    0x810e569c,// 270 PAY 223 

    0x27929e59,// 271 PAY 224 

    0xd3a16a9f,// 272 PAY 225 

    0x26bffebf,// 273 PAY 226 

    0xac204502,// 274 PAY 227 

    0x417dbaf8,// 275 PAY 228 

    0xde61d800,// 276 PAY 229 

    0x92125885,// 277 PAY 230 

    0xbca8c964,// 278 PAY 231 

    0x7a60b449,// 279 PAY 232 

    0x3643243d,// 280 PAY 233 

    0x5eccdebc,// 281 PAY 234 

    0x3d766f24,// 282 PAY 235 

    0xe23063bd,// 283 PAY 236 

    0x89330b94,// 284 PAY 237 

    0x6ec683ef,// 285 PAY 238 

    0x235eaede,// 286 PAY 239 

    0x92cc7510,// 287 PAY 240 

    0xd96c65ff,// 288 PAY 241 

    0x2e16d36f,// 289 PAY 242 

    0xdfd5cdc3,// 290 PAY 243 

    0xb1c5da2f,// 291 PAY 244 

    0x3bd65595,// 292 PAY 245 

    0xaacf4a2f,// 293 PAY 246 

    0xed414d37,// 294 PAY 247 

    0x68a5a55e,// 295 PAY 248 

    0xaacb4ec9,// 296 PAY 249 

    0xf68a19a2,// 297 PAY 250 

    0x368ec880,// 298 PAY 251 

    0x1f430927,// 299 PAY 252 

    0xde40c4ab,// 300 PAY 253 

    0x8bd860df,// 301 PAY 254 

    0xe6a80a9b,// 302 PAY 255 

    0xa76d3715,// 303 PAY 256 

    0x475da44e,// 304 PAY 257 

    0xb991ea21,// 305 PAY 258 

    0xeb45289a,// 306 PAY 259 

    0xb71bd0c1,// 307 PAY 260 

    0x41ce5298,// 308 PAY 261 

    0x2cb33dd1,// 309 PAY 262 

    0xf213dfde,// 310 PAY 263 

    0x137e42a3,// 311 PAY 264 

    0xa4723141,// 312 PAY 265 

    0x04653491,// 313 PAY 266 

    0xfbe01c74,// 314 PAY 267 

    0x91d24ffc,// 315 PAY 268 

    0xac545033,// 316 PAY 269 

    0xe5e08d51,// 317 PAY 270 

    0x941915b1,// 318 PAY 271 

    0xc37dc514,// 319 PAY 272 

    0x9b1d8da9,// 320 PAY 273 

    0x0d64312d,// 321 PAY 274 

    0x59911a09,// 322 PAY 275 

    0xdf1c8020,// 323 PAY 276 

    0xb64133e0,// 324 PAY 277 

    0xd04a9a3b,// 325 PAY 278 

    0x48c33dca,// 326 PAY 279 

    0x9bc45ed9,// 327 PAY 280 

    0xc4178d9b,// 328 PAY 281 

    0x3e3aaa22,// 329 PAY 282 

    0x6e029919,// 330 PAY 283 

    0x62416fed,// 331 PAY 284 

    0x8bc0c722,// 332 PAY 285 

    0x3205bc2b,// 333 PAY 286 

    0x1411aa0e,// 334 PAY 287 

    0x84890dba,// 335 PAY 288 

    0x8ee2c07c,// 336 PAY 289 

    0xd2a4e6f5,// 337 PAY 290 

    0x9b479f0c,// 338 PAY 291 

    0xa4125868,// 339 PAY 292 

    0x5b4e4656,// 340 PAY 293 

    0x6cd4342c,// 341 PAY 294 

    0x09f617f0,// 342 PAY 295 

    0x3722bcfc,// 343 PAY 296 

    0x824f6bf2,// 344 PAY 297 

    0x8c54e5c0,// 345 PAY 298 

    0x17bc86ac,// 346 PAY 299 

    0x8c6db3e3,// 347 PAY 300 

    0x4b1f8b8b,// 348 PAY 301 

    0x0bb9944e,// 349 PAY 302 

    0x085c1402,// 350 PAY 303 

    0x5487d7dc,// 351 PAY 304 

    0x6d82734e,// 352 PAY 305 

    0x90cda1b2,// 353 PAY 306 

    0xd00a3bef,// 354 PAY 307 

    0x63d9efa2,// 355 PAY 308 

    0xa6b7e711,// 356 PAY 309 

    0x6dfab344,// 357 PAY 310 

    0x2ba5ce6f,// 358 PAY 311 

    0xc95f3fdf,// 359 PAY 312 

    0xcda654ec,// 360 PAY 313 

    0x39e0f41f,// 361 PAY 314 

    0x3a044e3c,// 362 PAY 315 

    0x295cc25e,// 363 PAY 316 

    0x1a6f0962,// 364 PAY 317 

    0xab9cab75,// 365 PAY 318 

    0x2ebb7097,// 366 PAY 319 

    0x3dcfd74d,// 367 PAY 320 

    0xd6bb4493,// 368 PAY 321 

    0x2023f1d9,// 369 PAY 322 

    0x05a13803,// 370 PAY 323 

    0xf51ea95a,// 371 PAY 324 

    0x2ba36fed,// 372 PAY 325 

    0x935d542d,// 373 PAY 326 

    0x8883da02,// 374 PAY 327 

    0x6a27fd08,// 375 PAY 328 

    0x3ca56a32,// 376 PAY 329 

    0xaa5c32bb,// 377 PAY 330 

    0x9c173f3a,// 378 PAY 331 

    0x08d19e2d,// 379 PAY 332 

    0x4ad8b0d1,// 380 PAY 333 

    0x23a5eedc,// 381 PAY 334 

    0xee9e7409,// 382 PAY 335 

    0x23366316,// 383 PAY 336 

    0x32c9dddb,// 384 PAY 337 

    0xf3677bc0,// 385 PAY 338 

    0x30e13f29,// 386 PAY 339 

    0x9402a188,// 387 PAY 340 

    0xeee51612,// 388 PAY 341 

    0xafb7632e,// 389 PAY 342 

    0x5e2a4d31,// 390 PAY 343 

    0x5e33da30,// 391 PAY 344 

    0x6697c81f,// 392 PAY 345 

    0x0d7e1555,// 393 PAY 346 

    0x95e7880a,// 394 PAY 347 

    0xb7d6d931,// 395 PAY 348 

    0x2d170932,// 396 PAY 349 

    0x993af291,// 397 PAY 350 

    0x7a946bfe,// 398 PAY 351 

    0xa16f84a6,// 399 PAY 352 

    0xa76973fb,// 400 PAY 353 

    0x7aa3df6e,// 401 PAY 354 

    0xe810b230,// 402 PAY 355 

    0xbb06b735,// 403 PAY 356 

    0xa63287b6,// 404 PAY 357 

    0x2d07cf70,// 405 PAY 358 

    0xa856882d,// 406 PAY 359 

    0x878ffba0,// 407 PAY 360 

    0x9a9126ea,// 408 PAY 361 

    0x3f10ef6e,// 409 PAY 362 

    0x75131e15,// 410 PAY 363 

    0xf97e8457,// 411 PAY 364 

    0x47e34b0f,// 412 PAY 365 

    0x136fc20e,// 413 PAY 366 

    0xe2f535a7,// 414 PAY 367 

    0x9c0f8d88,// 415 PAY 368 

    0x22274a2f,// 416 PAY 369 

    0x0890e860,// 417 PAY 370 

    0xa79dd23b,// 418 PAY 371 

    0xcb7e2ecf,// 419 PAY 372 

    0xe28aef6e,// 420 PAY 373 

    0xa9fd3e00,// 421 PAY 374 

    0xf32d64c4,// 422 PAY 375 

    0xaab19862,// 423 PAY 376 

    0x181e4a87,// 424 PAY 377 

    0xd2153315,// 425 PAY 378 

    0x1bd1eab7,// 426 PAY 379 

    0xa3999928,// 427 PAY 380 

    0x858b173a,// 428 PAY 381 

    0x1f90e031,// 429 PAY 382 

    0x344b21ac,// 430 PAY 383 

    0x2f4fd924,// 431 PAY 384 

    0x9200aee9,// 432 PAY 385 

    0x59bc5b57,// 433 PAY 386 

    0xde65021a,// 434 PAY 387 

    0x58612b9c,// 435 PAY 388 

    0xe1d9526e,// 436 PAY 389 

    0x2f4934ea,// 437 PAY 390 

    0xf4f784d3,// 438 PAY 391 

    0x33315e22,// 439 PAY 392 

    0x85c2ec6e,// 440 PAY 393 

    0x28555107,// 441 PAY 394 

    0x0a71e3a8,// 442 PAY 395 

    0x27f2e494,// 443 PAY 396 

    0xf5c5960f,// 444 PAY 397 

    0xcc2d95f0,// 445 PAY 398 

    0xa51fe2fd,// 446 PAY 399 

    0xd87304bd,// 447 PAY 400 

    0xb5c46c87,// 448 PAY 401 

    0xf6c2be0a,// 449 PAY 402 

    0xcc324ed1,// 450 PAY 403 

    0x26869d9b,// 451 PAY 404 

    0x29a924dc,// 452 PAY 405 

    0x56f79c92,// 453 PAY 406 

    0x71c2161a,// 454 PAY 407 

    0xdddb6875,// 455 PAY 408 

    0xeb60adb5,// 456 PAY 409 

    0x3449c59c,// 457 PAY 410 

    0x0467fa44,// 458 PAY 411 

    0xa79b1550,// 459 PAY 412 

    0x7b8ee55f,// 460 PAY 413 

    0xda2535f8,// 461 PAY 414 

    0x6520aac7,// 462 PAY 415 

    0xcb596df1,// 463 PAY 416 

    0x6d4c22e5,// 464 PAY 417 

    0xd80ce3fa,// 465 PAY 418 

    0x30b09b60,// 466 PAY 419 

    0xcacfb2b9,// 467 PAY 420 

    0xed5b0c59,// 468 PAY 421 

    0x45afec8c,// 469 PAY 422 

    0x227fa658,// 470 PAY 423 

    0x1243d9c9,// 471 PAY 424 

    0x391a2a9f,// 472 PAY 425 

    0x16d9ba47,// 473 PAY 426 

    0x7727e89b,// 474 PAY 427 

    0x456e94c5,// 475 PAY 428 

    0x8fcb5008,// 476 PAY 429 

    0x81a7151b,// 477 PAY 430 

    0xa1a18065,// 478 PAY 431 

    0x3fbd32f4,// 479 PAY 432 

    0xa14aff75,// 480 PAY 433 

    0x164d7e8f,// 481 PAY 434 

    0x1bb1b336,// 482 PAY 435 

    0xdf1a14e0,// 483 PAY 436 

    0x004036ba,// 484 PAY 437 

    0x763e9e09,// 485 PAY 438 

    0x9e3825dc,// 486 PAY 439 

    0xbe96f7e7,// 487 PAY 440 

    0x6db32d12,// 488 PAY 441 

    0xb3724b12,// 489 PAY 442 

    0x9c6fc1fe,// 490 PAY 443 

    0x39f2f85f,// 491 PAY 444 

    0x516aaaf1,// 492 PAY 445 

    0x3bd84c7f,// 493 PAY 446 

    0x35627b58,// 494 PAY 447 

    0x66da6db5,// 495 PAY 448 

    0xfd6fdaa9,// 496 PAY 449 

    0x566d09fc,// 497 PAY 450 

    0xd691de97,// 498 PAY 451 

    0x3c62c31f,// 499 PAY 452 

    0x61bfa746,// 500 PAY 453 

    0xc05d5177,// 501 PAY 454 

    0x78077788,// 502 PAY 455 

    0x2e0e05a6,// 503 PAY 456 

    0xe7465b26,// 504 PAY 457 

    0xa2ac4240,// 505 PAY 458 

    0x191eec52,// 506 PAY 459 

    0x5a0f491e,// 507 PAY 460 

    0x70806509,// 508 PAY 461 

    0xe4b85ba1,// 509 PAY 462 

    0xa35abf9b,// 510 PAY 463 

    0xf2f55ec7,// 511 PAY 464 

    0x2df3f1e5,// 512 PAY 465 

    0x1d8a9f46,// 513 PAY 466 

    0xec4f7d00,// 514 PAY 467 

/// STA is 1 words. 

/// STA num_pkts       : 55 

/// STA pkt_idx        : 168 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xf4 

    0x02a0f437 // 515 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt79_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x0c 

/// ECH pdu_tag        : 0x00 

    0x000c0000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x809048d1,// 4 SCX   2 

    0x00005482,// 5 SCX   3 

    0x82f6736e,// 6 SCX   4 

    0x2a5033c7,// 7 SCX   5 

    0xfdfcde9e,// 8 SCX   6 

    0x0f8bafc4,// 9 SCX   7 

    0xde7ee046,// 10 SCX   8 

    0x30128220,// 11 SCX   9 

    0xe9d5b9c8,// 12 SCX  10 

    0x08b4d540,// 13 SCX  11 

    0xa77b24c0,// 14 SCX  12 

    0xadc089e3,// 15 SCX  13 

    0x9d0b491b,// 16 SCX  14 

    0x9cdef69c,// 17 SCX  15 

    0x8b4ef2ef,// 18 SCX  16 

    0x7bd52f98,// 19 SCX  17 

    0xcc490d35,// 20 SCX  18 

    0xfad6da2e,// 21 SCX  19 

    0x614ad6d7,// 22 SCX  20 

    0x9d814009,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 725 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 255 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 255 

/// BFD lencrypto      : 40 

/// BFD ofstcrypto     : 96 

/// BFD (ofst+len)cry  : 136 

/// BFD ofstiv         : 8 

/// BFD ofsticv        : 272 

    0x000000ff,// 24 BFD   1 

    0x00600028,// 25 BFD   2 

    0x01100008,// 26 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : 7 

    0x0700e2aa,// 27 MFM   1 

    0x03e00000,// 28 MFM   2 

/// BDA is 183 words. 

/// BDA size     is 725 (0x2d5) 

/// BDA id       is 0x4d3 

    0x02d504d3,// 29 BDA   1 

/// PAY Generic Data size   : 725 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0xf8852ac5,// 30 PAY   1 

    0x0a9cb98f,// 31 PAY   2 

    0xcb1b6bae,// 32 PAY   3 

    0x1c3c6759,// 33 PAY   4 

    0x2b0bede6,// 34 PAY   5 

    0xcc57fea4,// 35 PAY   6 

    0x8a3c1008,// 36 PAY   7 

    0x61bc2290,// 37 PAY   8 

    0xc50fc322,// 38 PAY   9 

    0x16dbe889,// 39 PAY  10 

    0x9df4feeb,// 40 PAY  11 

    0x13146578,// 41 PAY  12 

    0x388ba55a,// 42 PAY  13 

    0x31e5dce8,// 43 PAY  14 

    0x2e583c85,// 44 PAY  15 

    0xc9b14c48,// 45 PAY  16 

    0x1eabfe90,// 46 PAY  17 

    0x8bbaf334,// 47 PAY  18 

    0x407089ce,// 48 PAY  19 

    0xb240381c,// 49 PAY  20 

    0xa462509a,// 50 PAY  21 

    0xf437c5c6,// 51 PAY  22 

    0x26908ef2,// 52 PAY  23 

    0x3a2e40c5,// 53 PAY  24 

    0x5aaffa27,// 54 PAY  25 

    0xc7552d3d,// 55 PAY  26 

    0xd3d4f57a,// 56 PAY  27 

    0xd0bd9c79,// 57 PAY  28 

    0xfa9eb2a7,// 58 PAY  29 

    0x9ff11d13,// 59 PAY  30 

    0x3ed8be66,// 60 PAY  31 

    0x1e49cd9a,// 61 PAY  32 

    0x713e4d5c,// 62 PAY  33 

    0x8302773c,// 63 PAY  34 

    0x1f4cd2fc,// 64 PAY  35 

    0x498bea34,// 65 PAY  36 

    0x64d254ba,// 66 PAY  37 

    0xb70fecc9,// 67 PAY  38 

    0x6dcb28cc,// 68 PAY  39 

    0x2642a8b2,// 69 PAY  40 

    0x06d6efc6,// 70 PAY  41 

    0x6069eff2,// 71 PAY  42 

    0xd3575b2f,// 72 PAY  43 

    0x6478bd8f,// 73 PAY  44 

    0x640926ff,// 74 PAY  45 

    0x4bd0de10,// 75 PAY  46 

    0x0ff5300a,// 76 PAY  47 

    0x84876017,// 77 PAY  48 

    0x44126d12,// 78 PAY  49 

    0xe6d2851c,// 79 PAY  50 

    0xc427bc98,// 80 PAY  51 

    0x1716ea80,// 81 PAY  52 

    0x1746be75,// 82 PAY  53 

    0x271ca9c4,// 83 PAY  54 

    0xa76a7a0c,// 84 PAY  55 

    0x0ddbb3c7,// 85 PAY  56 

    0x181eb68c,// 86 PAY  57 

    0x0b3f09a9,// 87 PAY  58 

    0xfecbaf63,// 88 PAY  59 

    0xed760ee7,// 89 PAY  60 

    0xe80f305a,// 90 PAY  61 

    0xfa9013fd,// 91 PAY  62 

    0x8d4732d5,// 92 PAY  63 

    0xcccdfe0e,// 93 PAY  64 

    0xf4b4cf94,// 94 PAY  65 

    0x45b41eb5,// 95 PAY  66 

    0x6ec22e4a,// 96 PAY  67 

    0xafb15c94,// 97 PAY  68 

    0x541d96f9,// 98 PAY  69 

    0x56faaac6,// 99 PAY  70 

    0x5086bb06,// 100 PAY  71 

    0x6f268a5c,// 101 PAY  72 

    0x1c05bb10,// 102 PAY  73 

    0x29ae52a2,// 103 PAY  74 

    0x3cf52bde,// 104 PAY  75 

    0xfa23ef33,// 105 PAY  76 

    0xfd79d597,// 106 PAY  77 

    0x9137b6fd,// 107 PAY  78 

    0xf95b8fd8,// 108 PAY  79 

    0x8c1fbf0d,// 109 PAY  80 

    0x374eca03,// 110 PAY  81 

    0xa947a92f,// 111 PAY  82 

    0x98f33f08,// 112 PAY  83 

    0x8d7803ad,// 113 PAY  84 

    0x711ca66c,// 114 PAY  85 

    0xc23de4ad,// 115 PAY  86 

    0x17d924dc,// 116 PAY  87 

    0x9ce3d29f,// 117 PAY  88 

    0x33b46195,// 118 PAY  89 

    0x0b629d67,// 119 PAY  90 

    0x42b81b9f,// 120 PAY  91 

    0xa1cc8730,// 121 PAY  92 

    0xc3966d05,// 122 PAY  93 

    0xad6e8510,// 123 PAY  94 

    0x0d8063c5,// 124 PAY  95 

    0x4be0c034,// 125 PAY  96 

    0x0fdb991d,// 126 PAY  97 

    0x9a64780a,// 127 PAY  98 

    0xcfd6c24f,// 128 PAY  99 

    0x033c5bcf,// 129 PAY 100 

    0x08bcc024,// 130 PAY 101 

    0x443a2f05,// 131 PAY 102 

    0xc19208b9,// 132 PAY 103 

    0x99213359,// 133 PAY 104 

    0xbd078312,// 134 PAY 105 

    0x41944a21,// 135 PAY 106 

    0xc7fae7b8,// 136 PAY 107 

    0x447658ac,// 137 PAY 108 

    0x643e1bfa,// 138 PAY 109 

    0x324e4124,// 139 PAY 110 

    0xc99f7974,// 140 PAY 111 

    0x7ae8cc50,// 141 PAY 112 

    0x0337e98d,// 142 PAY 113 

    0x61ba634c,// 143 PAY 114 

    0xda544797,// 144 PAY 115 

    0xbc1c97ff,// 145 PAY 116 

    0x7c5fd6a3,// 146 PAY 117 

    0x8b1e548b,// 147 PAY 118 

    0x5b1420b7,// 148 PAY 119 

    0x5f1730ba,// 149 PAY 120 

    0x6400ddd4,// 150 PAY 121 

    0x3c1e387e,// 151 PAY 122 

    0x7571abb1,// 152 PAY 123 

    0x71c2950b,// 153 PAY 124 

    0xb682e986,// 154 PAY 125 

    0xc476b87f,// 155 PAY 126 

    0x8eea0018,// 156 PAY 127 

    0x406740c7,// 157 PAY 128 

    0x4f9548bd,// 158 PAY 129 

    0xcf13660f,// 159 PAY 130 

    0x8a5fdb28,// 160 PAY 131 

    0x890ab3a4,// 161 PAY 132 

    0xec216813,// 162 PAY 133 

    0x792db5b7,// 163 PAY 134 

    0xf189dff1,// 164 PAY 135 

    0x28006226,// 165 PAY 136 

    0x42c2872f,// 166 PAY 137 

    0x284481af,// 167 PAY 138 

    0xfe590fba,// 168 PAY 139 

    0x94a13399,// 169 PAY 140 

    0x0d4397e8,// 170 PAY 141 

    0x913e5173,// 171 PAY 142 

    0x4ad3fb8a,// 172 PAY 143 

    0xb4eb83bd,// 173 PAY 144 

    0xc52ad38b,// 174 PAY 145 

    0x84834d59,// 175 PAY 146 

    0x1778f8c3,// 176 PAY 147 

    0x2e5410fc,// 177 PAY 148 

    0xa49dbcf4,// 178 PAY 149 

    0x392b1124,// 179 PAY 150 

    0x2553d300,// 180 PAY 151 

    0xfc0305a7,// 181 PAY 152 

    0xe4fd922d,// 182 PAY 153 

    0xe5b0379c,// 183 PAY 154 

    0xdc0221ed,// 184 PAY 155 

    0xaf163ab8,// 185 PAY 156 

    0x95fe0955,// 186 PAY 157 

    0x915949b5,// 187 PAY 158 

    0x78814b58,// 188 PAY 159 

    0x604973c0,// 189 PAY 160 

    0x052fd3bd,// 190 PAY 161 

    0xc4d4f180,// 191 PAY 162 

    0xa6438492,// 192 PAY 163 

    0x64f00779,// 193 PAY 164 

    0x57551ac0,// 194 PAY 165 

    0xb079e2b8,// 195 PAY 166 

    0xb4f04480,// 196 PAY 167 

    0x6f06b6e4,// 197 PAY 168 

    0xef5ca4b9,// 198 PAY 169 

    0x24edc366,// 199 PAY 170 

    0xa76548c3,// 200 PAY 171 

    0xf2118ec4,// 201 PAY 172 

    0xb88c6795,// 202 PAY 173 

    0x990d6ffc,// 203 PAY 174 

    0x4a70e0c6,// 204 PAY 175 

    0x92471cd5,// 205 PAY 176 

    0xf59d1f45,// 206 PAY 177 

    0x71b21bb8,// 207 PAY 178 

    0x2823ed7b,// 208 PAY 179 

    0xac26dddf,// 209 PAY 180 

    0x8b60d2af,// 210 PAY 181 

    0xa4000000,// 211 PAY 182 

/// STA is 1 words. 

/// STA num_pkts       : 45 

/// STA pkt_idx        : 90 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xf 

    0x01690f2d // 212 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt80_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x0a 

/// ECH pdu_tag        : 0x00 

    0x000a0000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en !lock_en  

/// SCX inbound !save_icv insert_icv check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x00000019,// 3 SCX   1 

    0x80924842,// 4 SCX   2 

    0x00003382,// 5 SCX   3 

    0xa799d1a3,// 6 SCX   4 

    0x72e92d8b,// 7 SCX   5 

    0xcc930e2c,// 8 SCX   6 

    0xd437e6da,// 9 SCX   7 

    0x47a1288b,// 10 SCX   8 

    0x499636fc,// 11 SCX   9 

    0xca2e54ad,// 12 SCX  10 

    0xfde7129d,// 13 SCX  11 

    0x21e3155d,// 14 SCX  12 

    0x588d88a6,// 15 SCX  13 

    0x68e8e32f,// 16 SCX  14 

    0xd791b64d,// 17 SCX  15 

    0x070d8b5c,// 18 SCX  16 

    0xe2381f44,// 19 SCX  17 

    0xd7ebb111,// 20 SCX  18 

    0xdeccf843,// 21 SCX  19 

    0xa0e0d3ef,// 22 SCX  20 

    0x644e8481,// 23 SCX  21 

    0xdd465d33,// 24 SCX  22 

    0x09a5f40c,// 25 SCX  23 

    0xebe8aaff,// 26 SCX  24 

    0x2449cbc1,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 665 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 201 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 201 

/// BFD lencrypto      : 8 

/// BFD ofstcrypto     : 192 

/// BFD (ofst+len)cry  : 200 

/// BFD ofstiv         : 104 

/// BFD ofsticv        : 416 

    0x000000c9,// 28 BFD   1 

    0x00c00008,// 29 BFD   2 

    0x01a00068,// 30 BFD   3 

/// MFM is 6 words. 

/// MFM vldnibs        : 2c 

    0x2c004ddd,// 31 MFM   1 

    0x366313ca,// 32 MFM   2 

    0x7e830464,// 33 MFM   3 

    0x71b5a09d,// 34 MFM   4 

    0x006b950c,// 35 MFM   5 

    0x26771704,// 36 MFM   6 

/// BDA is 168 words. 

/// BDA size     is 665 (0x299) 

/// BDA id       is 0xcf5d 

    0x0299cf5d,// 37 BDA   1 

/// PAY Generic Data size   : 665 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x112fb103,// 38 PAY   1 

    0xef887df9,// 39 PAY   2 

    0xe0ca6ffc,// 40 PAY   3 

    0x6855b46a,// 41 PAY   4 

    0x6a9070b0,// 42 PAY   5 

    0xa7fc897b,// 43 PAY   6 

    0x312a179b,// 44 PAY   7 

    0x476e8d63,// 45 PAY   8 

    0x5ef5fb7e,// 46 PAY   9 

    0x005764ba,// 47 PAY  10 

    0x4f58cdb3,// 48 PAY  11 

    0x4a3965b4,// 49 PAY  12 

    0xf6900a8d,// 50 PAY  13 

    0xd6423a49,// 51 PAY  14 

    0x8e7469be,// 52 PAY  15 

    0xc7443611,// 53 PAY  16 

    0x2f4d2943,// 54 PAY  17 

    0xc8f26b56,// 55 PAY  18 

    0x58bdcd04,// 56 PAY  19 

    0xd52db8dd,// 57 PAY  20 

    0xd4f0bb7e,// 58 PAY  21 

    0xb4c14021,// 59 PAY  22 

    0xf3e11b10,// 60 PAY  23 

    0xa3de78a4,// 61 PAY  24 

    0xd2fd495d,// 62 PAY  25 

    0xe48fb4cb,// 63 PAY  26 

    0x3696e254,// 64 PAY  27 

    0xe37cf27c,// 65 PAY  28 

    0xaec10fe6,// 66 PAY  29 

    0x81a2d3b2,// 67 PAY  30 

    0x8af770c8,// 68 PAY  31 

    0xe73cb39d,// 69 PAY  32 

    0x490dfbc9,// 70 PAY  33 

    0x835f77b1,// 71 PAY  34 

    0x35105e96,// 72 PAY  35 

    0x3f40b00a,// 73 PAY  36 

    0xdfd1e824,// 74 PAY  37 

    0x110ba00e,// 75 PAY  38 

    0xbbb908c2,// 76 PAY  39 

    0xa3adb4fd,// 77 PAY  40 

    0x2a4bc648,// 78 PAY  41 

    0x7a822d15,// 79 PAY  42 

    0xd4458b6d,// 80 PAY  43 

    0xa151dbcc,// 81 PAY  44 

    0xd536a8be,// 82 PAY  45 

    0xa0ed7077,// 83 PAY  46 

    0xd984cbfb,// 84 PAY  47 

    0xc4851837,// 85 PAY  48 

    0x5d27977b,// 86 PAY  49 

    0x86751087,// 87 PAY  50 

    0xabb432e4,// 88 PAY  51 

    0xb01db8fc,// 89 PAY  52 

    0xc5bc3a0c,// 90 PAY  53 

    0xa183e3f4,// 91 PAY  54 

    0x7344fe49,// 92 PAY  55 

    0x897c0588,// 93 PAY  56 

    0xada5b8f3,// 94 PAY  57 

    0x14181eae,// 95 PAY  58 

    0xf96f9905,// 96 PAY  59 

    0x56e75513,// 97 PAY  60 

    0xaef59fcf,// 98 PAY  61 

    0x52f6d1f5,// 99 PAY  62 

    0x864032e2,// 100 PAY  63 

    0x182e8803,// 101 PAY  64 

    0xea68f07a,// 102 PAY  65 

    0x1945b9c9,// 103 PAY  66 

    0xe1d9b0c8,// 104 PAY  67 

    0xd4f6262a,// 105 PAY  68 

    0x94a0f6ec,// 106 PAY  69 

    0xb4abb6a3,// 107 PAY  70 

    0x289bb28f,// 108 PAY  71 

    0x0e14c402,// 109 PAY  72 

    0xa3ef2e26,// 110 PAY  73 

    0xc3d52946,// 111 PAY  74 

    0xe42245b0,// 112 PAY  75 

    0x4ec3fbd5,// 113 PAY  76 

    0x3d44e06b,// 114 PAY  77 

    0x12ea2e9e,// 115 PAY  78 

    0x2164aba6,// 116 PAY  79 

    0x9cebfc8a,// 117 PAY  80 

    0xbc5de34b,// 118 PAY  81 

    0x5d54c7c9,// 119 PAY  82 

    0x1eeb1d8b,// 120 PAY  83 

    0x54adb716,// 121 PAY  84 

    0x91595072,// 122 PAY  85 

    0xbb416e7c,// 123 PAY  86 

    0x4a562c2a,// 124 PAY  87 

    0xebb2d9ef,// 125 PAY  88 

    0x38d4d8eb,// 126 PAY  89 

    0x48bcd044,// 127 PAY  90 

    0x0665d844,// 128 PAY  91 

    0x79189ee0,// 129 PAY  92 

    0x1def1323,// 130 PAY  93 

    0x44ffdc79,// 131 PAY  94 

    0xade654d7,// 132 PAY  95 

    0x9efc6494,// 133 PAY  96 

    0xf8c77b68,// 134 PAY  97 

    0x66bb7e0c,// 135 PAY  98 

    0x4dd25f69,// 136 PAY  99 

    0x0812de14,// 137 PAY 100 

    0xd3d3e3f2,// 138 PAY 101 

    0x821bcf82,// 139 PAY 102 

    0xe15e6e90,// 140 PAY 103 

    0x4e6fa30d,// 141 PAY 104 

    0x1e8b4b0c,// 142 PAY 105 

    0xf947239b,// 143 PAY 106 

    0xb0b2b466,// 144 PAY 107 

    0x7aef5ae3,// 145 PAY 108 

    0x17b4e94d,// 146 PAY 109 

    0xd933da6e,// 147 PAY 110 

    0x4fd95c06,// 148 PAY 111 

    0xa1623311,// 149 PAY 112 

    0x75601988,// 150 PAY 113 

    0xb225ade6,// 151 PAY 114 

    0x4ee01029,// 152 PAY 115 

    0x10003ca7,// 153 PAY 116 

    0xaae10b5a,// 154 PAY 117 

    0xe26bc0a3,// 155 PAY 118 

    0xd11f6e9c,// 156 PAY 119 

    0xf91533ed,// 157 PAY 120 

    0x060d7413,// 158 PAY 121 

    0x1d3dae7b,// 159 PAY 122 

    0x294a23d8,// 160 PAY 123 

    0x76ac0404,// 161 PAY 124 

    0xc9c5f018,// 162 PAY 125 

    0xb9b78485,// 163 PAY 126 

    0xa9756d9a,// 164 PAY 127 

    0xec6cd481,// 165 PAY 128 

    0x6cbbf150,// 166 PAY 129 

    0xc848a996,// 167 PAY 130 

    0xf30ca2b7,// 168 PAY 131 

    0x1d232061,// 169 PAY 132 

    0x57654e31,// 170 PAY 133 

    0x34479af6,// 171 PAY 134 

    0x3c3b7cbb,// 172 PAY 135 

    0xcf5730c3,// 173 PAY 136 

    0xd750d82a,// 174 PAY 137 

    0x4df92c08,// 175 PAY 138 

    0xfaf839f7,// 176 PAY 139 

    0x40e4c1e3,// 177 PAY 140 

    0xd278fc96,// 178 PAY 141 

    0x2da20403,// 179 PAY 142 

    0x3476ba39,// 180 PAY 143 

    0xf6c41f30,// 181 PAY 144 

    0x74978845,// 182 PAY 145 

    0x74b6635f,// 183 PAY 146 

    0x18c7de26,// 184 PAY 147 

    0x4c774732,// 185 PAY 148 

    0xb8623b91,// 186 PAY 149 

    0xf0ddc803,// 187 PAY 150 

    0x12c20915,// 188 PAY 151 

    0xcc143594,// 189 PAY 152 

    0x3c20995f,// 190 PAY 153 

    0x6c935059,// 191 PAY 154 

    0x4e514b5d,// 192 PAY 155 

    0x8f2e56fb,// 193 PAY 156 

    0xc12d944b,// 194 PAY 157 

    0x7ebc51c2,// 195 PAY 158 

    0xd709d9d9,// 196 PAY 159 

    0x5426cba0,// 197 PAY 160 

    0x0c6263c0,// 198 PAY 161 

    0xe9790a02,// 199 PAY 162 

    0x88825991,// 200 PAY 163 

    0x1d538121,// 201 PAY 164 

    0x7b4e78c5,// 202 PAY 165 

    0x68c0e96d,// 203 PAY 166 

    0xf7000000,// 204 PAY 167 

/// STA is 1 words. 

/// STA num_pkts       : 133 

/// STA pkt_idx        : 255 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x4 

    0x03fc0485 // 205 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 80 (0x50) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt81_tmpl[] = {
    0xb8010050,// 1 CCH   1 

/// ECH cache_idx      : 0x0e 

/// ECH pdu_tag        : 0x00 

    0x000e0000,// 2 ECH   1 

/// SCX is 19 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x1 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000013,// 3 SCX   1 

    0x8081481c,// 4 SCX   2 

    0x00003100,// 5 SCX   3 

    0x2b97ce31,// 6 SCX   4 

    0x6880199f,// 7 SCX   5 

    0xbf4c01b2,// 8 SCX   6 

    0x23d2faf2,// 9 SCX   7 

    0xf3b5bc4e,// 10 SCX   8 

    0x66bf601c,// 11 SCX   9 

    0x21035ad7,// 12 SCX  10 

    0x7e2cfba9,// 13 SCX  11 

    0xfb880789,// 14 SCX  12 

    0xf17a91e8,// 15 SCX  13 

    0xdfcdcf30,// 16 SCX  14 

    0x5dde79c8,// 17 SCX  15 

    0x397dca45,// 18 SCX  16 

    0xa82025c0,// 19 SCX  17 

    0x95fb358b,// 20 SCX  18 

    0xcb929bb1,// 21 SCX  19 

/// BFD is 3 words. 

/// BFD tot_len        : 619 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 419 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 419 

/// BFD lencrypto      : 48 

/// BFD ofstcrypto     : 164 

/// BFD (ofst+len)cry  : 212 

/// BFD ofstiv         : 104 

/// BFD ofsticv        : 440 

    0x000001a3,// 22 BFD   1 

    0x00a40030,// 23 BFD   2 

    0x01b80068,// 24 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : 6 

    0x0600f63c,// 25 MFM   1 

    0xb2000000,// 26 MFM   2 

/// BDA is 156 words. 

/// BDA size     is 619 (0x26b) 

/// BDA id       is 0xe599 

    0x026be599,// 27 BDA   1 

/// PAY Generic Data size   : 619 byte(s) 

/// PAD Buffer Data Pad size   : 1 byte(s) 

    0x1e6fd184,// 28 PAY   1 

    0xf5c0b2e6,// 29 PAY   2 

    0x6d967f18,// 30 PAY   3 

    0xd7edadc5,// 31 PAY   4 

    0x9a2ddec2,// 32 PAY   5 

    0xe515affa,// 33 PAY   6 

    0xe755b4eb,// 34 PAY   7 

    0x93656266,// 35 PAY   8 

    0x107336cc,// 36 PAY   9 

    0x0cc9ad16,// 37 PAY  10 

    0xff0bd07e,// 38 PAY  11 

    0x979a7b90,// 39 PAY  12 

    0x24853716,// 40 PAY  13 

    0x0362db59,// 41 PAY  14 

    0x7b3a7e30,// 42 PAY  15 

    0x8661bf6e,// 43 PAY  16 

    0x5ba02c50,// 44 PAY  17 

    0x44787274,// 45 PAY  18 

    0x2087cbf0,// 46 PAY  19 

    0xd08e9cd4,// 47 PAY  20 

    0x949251fc,// 48 PAY  21 

    0x02df3435,// 49 PAY  22 

    0xb8163cac,// 50 PAY  23 

    0x0bda4a97,// 51 PAY  24 

    0x3dcbedd2,// 52 PAY  25 

    0x00988fe3,// 53 PAY  26 

    0x770b4849,// 54 PAY  27 

    0xaf774cd3,// 55 PAY  28 

    0x2c40d3cc,// 56 PAY  29 

    0xff9a8e57,// 57 PAY  30 

    0x75f27f59,// 58 PAY  31 

    0x5015a05e,// 59 PAY  32 

    0xec399f06,// 60 PAY  33 

    0x15a33a46,// 61 PAY  34 

    0x5c9ecf67,// 62 PAY  35 

    0xc776eb66,// 63 PAY  36 

    0xcdee9cbd,// 64 PAY  37 

    0x6230f2e9,// 65 PAY  38 

    0x18b8d48a,// 66 PAY  39 

    0x57dbe6ba,// 67 PAY  40 

    0x68cbdffe,// 68 PAY  41 

    0x864fa83c,// 69 PAY  42 

    0x5d358058,// 70 PAY  43 

    0xc684c23f,// 71 PAY  44 

    0x67304dec,// 72 PAY  45 

    0x584204f1,// 73 PAY  46 

    0x36f0d199,// 74 PAY  47 

    0xd6de484f,// 75 PAY  48 

    0x0ba89abb,// 76 PAY  49 

    0x7bb186fb,// 77 PAY  50 

    0x8dd56d10,// 78 PAY  51 

    0x4ab820d2,// 79 PAY  52 

    0xe4ffff82,// 80 PAY  53 

    0x1ebc7565,// 81 PAY  54 

    0xdb094193,// 82 PAY  55 

    0x0f8012c2,// 83 PAY  56 

    0x6ddae70e,// 84 PAY  57 

    0x3e9dc1f3,// 85 PAY  58 

    0xe63acc4c,// 86 PAY  59 

    0x365c3be3,// 87 PAY  60 

    0x7a3abdaa,// 88 PAY  61 

    0x8464bfe7,// 89 PAY  62 

    0x09c0e809,// 90 PAY  63 

    0xe5307516,// 91 PAY  64 

    0xa8c84596,// 92 PAY  65 

    0x03246ea4,// 93 PAY  66 

    0xcbc7592a,// 94 PAY  67 

    0x36dc0f5c,// 95 PAY  68 

    0xe4c8b61b,// 96 PAY  69 

    0x31d91536,// 97 PAY  70 

    0xb016bbf4,// 98 PAY  71 

    0x90a5f955,// 99 PAY  72 

    0x88d4e711,// 100 PAY  73 

    0x9db17ab5,// 101 PAY  74 

    0xad449f9e,// 102 PAY  75 

    0x292e7b21,// 103 PAY  76 

    0x7486dcc0,// 104 PAY  77 

    0xe0fa86d8,// 105 PAY  78 

    0x9b72939b,// 106 PAY  79 

    0x99402dee,// 107 PAY  80 

    0x93804a5d,// 108 PAY  81 

    0xda3217e6,// 109 PAY  82 

    0x97d7c005,// 110 PAY  83 

    0xe3d6095a,// 111 PAY  84 

    0xcf884b0f,// 112 PAY  85 

    0xd0095a68,// 113 PAY  86 

    0xb528602a,// 114 PAY  87 

    0x59d290b7,// 115 PAY  88 

    0x490dcc6c,// 116 PAY  89 

    0x1eb91476,// 117 PAY  90 

    0x17f09b38,// 118 PAY  91 

    0x2a5b3e7f,// 119 PAY  92 

    0x8e342218,// 120 PAY  93 

    0xcab2b610,// 121 PAY  94 

    0x113c97cc,// 122 PAY  95 

    0x08ee2f74,// 123 PAY  96 

    0xb3b7f18b,// 124 PAY  97 

    0x64242487,// 125 PAY  98 

    0xbf23fc13,// 126 PAY  99 

    0x9d7b9bb6,// 127 PAY 100 

    0x684782d2,// 128 PAY 101 

    0xea416f87,// 129 PAY 102 

    0x3edc4314,// 130 PAY 103 

    0xa13040a7,// 131 PAY 104 

    0x372b5406,// 132 PAY 105 

    0x135757ff,// 133 PAY 106 

    0x52cbb5dc,// 134 PAY 107 

    0x83006b8f,// 135 PAY 108 

    0xe18c914c,// 136 PAY 109 

    0x13fc0b6c,// 137 PAY 110 

    0xb6d21180,// 138 PAY 111 

    0xf232d9c4,// 139 PAY 112 

    0x2d251337,// 140 PAY 113 

    0xf1c7a9f1,// 141 PAY 114 

    0xb9c1fd46,// 142 PAY 115 

    0xf82ea63a,// 143 PAY 116 

    0xbe41a74c,// 144 PAY 117 

    0x007c799e,// 145 PAY 118 

    0x876ca738,// 146 PAY 119 

    0xca5862f5,// 147 PAY 120 

    0x6566ac5e,// 148 PAY 121 

    0xcb259acf,// 149 PAY 122 

    0xeeafdf22,// 150 PAY 123 

    0x3b39706d,// 151 PAY 124 

    0x23e5c72b,// 152 PAY 125 

    0xbd5edce5,// 153 PAY 126 

    0xda6488d8,// 154 PAY 127 

    0xaf8ed06d,// 155 PAY 128 

    0xfa992f35,// 156 PAY 129 

    0x6935044b,// 157 PAY 130 

    0xdcf6f4a9,// 158 PAY 131 

    0xf925f9d9,// 159 PAY 132 

    0xb6642cbe,// 160 PAY 133 

    0x1654f63f,// 161 PAY 134 

    0xdedb3b57,// 162 PAY 135 

    0x31dc8ee6,// 163 PAY 136 

    0x9e7e3505,// 164 PAY 137 

    0x23ad48a1,// 165 PAY 138 

    0x464cb102,// 166 PAY 139 

    0x4c82bd54,// 167 PAY 140 

    0x42484f9c,// 168 PAY 141 

    0xfead2285,// 169 PAY 142 

    0x11ffbd75,// 170 PAY 143 

    0x88c85ebb,// 171 PAY 144 

    0xce497c5b,// 172 PAY 145 

    0xc7649772,// 173 PAY 146 

    0x6dc01a2c,// 174 PAY 147 

    0x86dcebb5,// 175 PAY 148 

    0x941c5b30,// 176 PAY 149 

    0x7dc771bc,// 177 PAY 150 

    0x8324547b,// 178 PAY 151 

    0x318d0a90,// 179 PAY 152 

    0x662c14f7,// 180 PAY 153 

    0x769c77f8,// 181 PAY 154 

    0x11acf300,// 182 PAY 155 

/// STA is 1 words. 

/// STA num_pkts       : 210 

/// STA pkt_idx        : 251 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x1f 

    0x03ed1fd2 // 183 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt82_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x06 

/// ECH pdu_tag        : 0x00 

    0x00060000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv !insert_icv !check_icv sctx_iv  

/// SCX exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CBC 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x4 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000019,// 3 SCX   1 

    0x808648ab,// 4 SCX   2 

    0x000004c4,// 5 SCX   3 

    0xf5e22d6c,// 6 SCX   4 

    0xe5f8da85,// 7 SCX   5 

    0xef2714fc,// 8 SCX   6 

    0xc95c8924,// 9 SCX   7 

    0x8d886b35,// 10 SCX   8 

    0xb8b4fe93,// 11 SCX   9 

    0x75140ae2,// 12 SCX  10 

    0x4ba6cc6a,// 13 SCX  11 

    0x40cae6e1,// 14 SCX  12 

    0x71c18d5d,// 15 SCX  13 

    0x19adfa66,// 16 SCX  14 

    0xd74b6797,// 17 SCX  15 

    0xc5023848,// 18 SCX  16 

    0x7a3e0acb,// 19 SCX  17 

    0xfce1f836,// 20 SCX  18 

    0x7c96e04e,// 21 SCX  19 

    0x6973b00c,// 22 SCX  20 

    0xf8751509,// 23 SCX  21 

    0x84bdecb2,// 24 SCX  22 

    0xaba3a179,// 25 SCX  23 

    0xcbc75ce5,// 26 SCX  24 

    0x913c6a41,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 1034 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 484 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 484 

/// BFD lencrypto      : 48 

/// BFD ofstcrypto     : 408 

/// BFD (ofst+len)cry  : 456 

/// BFD ofstiv         : 236 

/// BFD ofsticv        : 524 

    0x000001e4,// 28 BFD   1 

    0x01980030,// 29 BFD   2 

    0x020c00ec,// 30 BFD   3 

/// MFM is 8 words. 

/// MFM vldnibs        : 3a 

    0x3a00b6fb,// 31 MFM   1 

    0xab7c83c1,// 32 MFM   2 

    0x64ff6369,// 33 MFM   3 

    0x059b04ff,// 34 MFM   4 

    0x76c24377,// 35 MFM   5 

    0x15bae691,// 36 MFM   6 

    0xf52cace8,// 37 MFM   7 

    0x08c65c00,// 38 MFM   8 

/// BDA is 260 words. 

/// BDA size     is 1034 (0x40a) 

/// BDA id       is 0x8517 

    0x040a8517,// 39 BDA   1 

/// PAY Generic Data size   : 1034 byte(s) 

/// PAD Buffer Data Pad size   : 2 byte(s) 

    0x5c7865cf,// 40 PAY   1 

    0xe1bf0fa5,// 41 PAY   2 

    0x0ec9ba25,// 42 PAY   3 

    0xe906f9da,// 43 PAY   4 

    0x7b8d2a24,// 44 PAY   5 

    0xfb741fe8,// 45 PAY   6 

    0xefa61b68,// 46 PAY   7 

    0x8df342b2,// 47 PAY   8 

    0x69c92aa1,// 48 PAY   9 

    0xb2f92f4e,// 49 PAY  10 

    0x4f3e3a3b,// 50 PAY  11 

    0xd67949c1,// 51 PAY  12 

    0x2a5f2927,// 52 PAY  13 

    0x16fdf7fc,// 53 PAY  14 

    0xc7e5a0c9,// 54 PAY  15 

    0xc8bcd42d,// 55 PAY  16 

    0xfab67935,// 56 PAY  17 

    0xf48c16ba,// 57 PAY  18 

    0xd988788a,// 58 PAY  19 

    0x88697738,// 59 PAY  20 

    0x96c0e8bf,// 60 PAY  21 

    0x18834df7,// 61 PAY  22 

    0xad5b163f,// 62 PAY  23 

    0xa20a9405,// 63 PAY  24 

    0xc4e3530b,// 64 PAY  25 

    0xa4815b32,// 65 PAY  26 

    0x06220567,// 66 PAY  27 

    0xc83b3e39,// 67 PAY  28 

    0xe4840966,// 68 PAY  29 

    0x7e18622e,// 69 PAY  30 

    0xddde866c,// 70 PAY  31 

    0x8e448dc9,// 71 PAY  32 

    0xfb8d51a3,// 72 PAY  33 

    0xf07b7470,// 73 PAY  34 

    0xee2e661b,// 74 PAY  35 

    0xc56bf53f,// 75 PAY  36 

    0x551aaf17,// 76 PAY  37 

    0x92327589,// 77 PAY  38 

    0xd4a59a11,// 78 PAY  39 

    0x1432fe7d,// 79 PAY  40 

    0x2ca9256a,// 80 PAY  41 

    0x12443a61,// 81 PAY  42 

    0x2e543867,// 82 PAY  43 

    0x38b0535a,// 83 PAY  44 

    0xefaf3f9e,// 84 PAY  45 

    0xba340ac8,// 85 PAY  46 

    0x2d488251,// 86 PAY  47 

    0x370da4a3,// 87 PAY  48 

    0xbd2f6847,// 88 PAY  49 

    0x688d5a54,// 89 PAY  50 

    0x3ee28453,// 90 PAY  51 

    0xbcf2d16d,// 91 PAY  52 

    0x308cdf6e,// 92 PAY  53 

    0x95cb0436,// 93 PAY  54 

    0xa1cc0897,// 94 PAY  55 

    0x578dce5f,// 95 PAY  56 

    0x9e14e78f,// 96 PAY  57 

    0x2c046c5f,// 97 PAY  58 

    0x3d9d21db,// 98 PAY  59 

    0x484309f9,// 99 PAY  60 

    0x1c54143c,// 100 PAY  61 

    0x3242af52,// 101 PAY  62 

    0x7ed3a3e7,// 102 PAY  63 

    0x182a9e19,// 103 PAY  64 

    0x3870b9e1,// 104 PAY  65 

    0xcac12dc2,// 105 PAY  66 

    0xc8a2d2c8,// 106 PAY  67 

    0x6a8bb317,// 107 PAY  68 

    0xe792e2f7,// 108 PAY  69 

    0x762bccff,// 109 PAY  70 

    0x3cc91118,// 110 PAY  71 

    0x47578617,// 111 PAY  72 

    0x8c742c85,// 112 PAY  73 

    0x2acbf70f,// 113 PAY  74 

    0xf5f4378b,// 114 PAY  75 

    0xdd4c9b92,// 115 PAY  76 

    0xf64d9c6b,// 116 PAY  77 

    0x1f0877c4,// 117 PAY  78 

    0x17316e4e,// 118 PAY  79 

    0xbd9f60ae,// 119 PAY  80 

    0xe168efe8,// 120 PAY  81 

    0x201e18ea,// 121 PAY  82 

    0xb6be696b,// 122 PAY  83 

    0x26d1bf9b,// 123 PAY  84 

    0x56c3bfa0,// 124 PAY  85 

    0xcf302eb4,// 125 PAY  86 

    0x0e30f959,// 126 PAY  87 

    0x44220191,// 127 PAY  88 

    0x72ffcca6,// 128 PAY  89 

    0x85e8e7e4,// 129 PAY  90 

    0x26a36b52,// 130 PAY  91 

    0x9d4660d7,// 131 PAY  92 

    0x7106584a,// 132 PAY  93 

    0xb7a77bf4,// 133 PAY  94 

    0xb03aec67,// 134 PAY  95 

    0x9583e68e,// 135 PAY  96 

    0x6c761c7c,// 136 PAY  97 

    0xa721fb50,// 137 PAY  98 

    0xd482ed86,// 138 PAY  99 

    0x4095d279,// 139 PAY 100 

    0x85e1000c,// 140 PAY 101 

    0xc04a1a5c,// 141 PAY 102 

    0x2979aca2,// 142 PAY 103 

    0xd502712e,// 143 PAY 104 

    0x64aab9f6,// 144 PAY 105 

    0x0803df12,// 145 PAY 106 

    0x82417d75,// 146 PAY 107 

    0x48e9417c,// 147 PAY 108 

    0xed58c3f4,// 148 PAY 109 

    0x563befda,// 149 PAY 110 

    0xd60f23c8,// 150 PAY 111 

    0x3f5827da,// 151 PAY 112 

    0x0378dfb6,// 152 PAY 113 

    0x7fabf939,// 153 PAY 114 

    0x274fba59,// 154 PAY 115 

    0xa93e9ee2,// 155 PAY 116 

    0x71dcb54c,// 156 PAY 117 

    0x01980e08,// 157 PAY 118 

    0x66ab7e5a,// 158 PAY 119 

    0x2174e03c,// 159 PAY 120 

    0x6f7719ae,// 160 PAY 121 

    0x51d6f47f,// 161 PAY 122 

    0x48b6d299,// 162 PAY 123 

    0xe0117d0c,// 163 PAY 124 

    0xacb1c578,// 164 PAY 125 

    0x1be9aad3,// 165 PAY 126 

    0x54d806f7,// 166 PAY 127 

    0x9b01eac1,// 167 PAY 128 

    0x02edebd4,// 168 PAY 129 

    0x3ef34c60,// 169 PAY 130 

    0x9be1fbf7,// 170 PAY 131 

    0x272d4779,// 171 PAY 132 

    0x7d3ba83b,// 172 PAY 133 

    0xb40cbf9b,// 173 PAY 134 

    0xc39927d1,// 174 PAY 135 

    0x49043f9b,// 175 PAY 136 

    0xa0ed345d,// 176 PAY 137 

    0xc19299e8,// 177 PAY 138 

    0xda82b3d5,// 178 PAY 139 

    0xd1798287,// 179 PAY 140 

    0xae7cae37,// 180 PAY 141 

    0x4b9c1051,// 181 PAY 142 

    0x3cecf81c,// 182 PAY 143 

    0x2a46f716,// 183 PAY 144 

    0x884b2474,// 184 PAY 145 

    0xa13a5776,// 185 PAY 146 

    0x799451c1,// 186 PAY 147 

    0x5ddb1714,// 187 PAY 148 

    0xd6328035,// 188 PAY 149 

    0x40ee3941,// 189 PAY 150 

    0x18f8c0be,// 190 PAY 151 

    0x609ffd5e,// 191 PAY 152 

    0xd465c598,// 192 PAY 153 

    0x8273755b,// 193 PAY 154 

    0x437afbc1,// 194 PAY 155 

    0x94d7f7f4,// 195 PAY 156 

    0xc73104ed,// 196 PAY 157 

    0xcc60bd6b,// 197 PAY 158 

    0x3217fed0,// 198 PAY 159 

    0x6c015a9d,// 199 PAY 160 

    0x691bed09,// 200 PAY 161 

    0xd487584e,// 201 PAY 162 

    0x36ce2fb7,// 202 PAY 163 

    0x960ddaac,// 203 PAY 164 

    0x1a38e754,// 204 PAY 165 

    0x4f85cd47,// 205 PAY 166 

    0x3b7769a3,// 206 PAY 167 

    0x3c292992,// 207 PAY 168 

    0x1c596e3e,// 208 PAY 169 

    0x5d72d9bb,// 209 PAY 170 

    0xe949f9de,// 210 PAY 171 

    0x7d9238ec,// 211 PAY 172 

    0x8d20709b,// 212 PAY 173 

    0xf16ba776,// 213 PAY 174 

    0x37ee35f7,// 214 PAY 175 

    0xfce72a3f,// 215 PAY 176 

    0x62c00fe9,// 216 PAY 177 

    0xd93f44a1,// 217 PAY 178 

    0x88a0675a,// 218 PAY 179 

    0x3cb21dc2,// 219 PAY 180 

    0x348db55e,// 220 PAY 181 

    0x538f88c5,// 221 PAY 182 

    0x894437d1,// 222 PAY 183 

    0xfb553156,// 223 PAY 184 

    0xf702b54c,// 224 PAY 185 

    0x197211a8,// 225 PAY 186 

    0xedd9af4a,// 226 PAY 187 

    0xbc28328d,// 227 PAY 188 

    0xd86f9873,// 228 PAY 189 

    0x773cbc0b,// 229 PAY 190 

    0x01f161b5,// 230 PAY 191 

    0x89614a0f,// 231 PAY 192 

    0x8fa6b2ad,// 232 PAY 193 

    0x1b7f8bf2,// 233 PAY 194 

    0x87ffd5f5,// 234 PAY 195 

    0xb88715cd,// 235 PAY 196 

    0x71a43545,// 236 PAY 197 

    0xcd6e2561,// 237 PAY 198 

    0x60223309,// 238 PAY 199 

    0x48c53c8a,// 239 PAY 200 

    0xac0c211b,// 240 PAY 201 

    0x624ee381,// 241 PAY 202 

    0xc0097bc3,// 242 PAY 203 

    0x3c1d74a8,// 243 PAY 204 

    0x6f89b449,// 244 PAY 205 

    0xec0018fd,// 245 PAY 206 

    0x977a52ef,// 246 PAY 207 

    0xe3bb7cfc,// 247 PAY 208 

    0x2e56a8d4,// 248 PAY 209 

    0xef5e05f8,// 249 PAY 210 

    0xfddd61e9,// 250 PAY 211 

    0x84322ed4,// 251 PAY 212 

    0x56e1fff9,// 252 PAY 213 

    0x634f1d73,// 253 PAY 214 

    0xb6f042f8,// 254 PAY 215 

    0x9c754e20,// 255 PAY 216 

    0xa527b7e4,// 256 PAY 217 

    0x64097978,// 257 PAY 218 

    0xf27caa08,// 258 PAY 219 

    0x7fb9ceba,// 259 PAY 220 

    0x762e4eb3,// 260 PAY 221 

    0x1dd1b64a,// 261 PAY 222 

    0x3f55444b,// 262 PAY 223 

    0xdb92f00a,// 263 PAY 224 

    0x1c973711,// 264 PAY 225 

    0x52652dff,// 265 PAY 226 

    0xe03fd1c8,// 266 PAY 227 

    0x5f9ccdc3,// 267 PAY 228 

    0x24c13386,// 268 PAY 229 

    0x9fd22ac0,// 269 PAY 230 

    0xa8b84ffc,// 270 PAY 231 

    0xb02e9a3b,// 271 PAY 232 

    0x2cc0ed1f,// 272 PAY 233 

    0x666ba837,// 273 PAY 234 

    0xd234d0d9,// 274 PAY 235 

    0xbe96a59c,// 275 PAY 236 

    0x70b3a743,// 276 PAY 237 

    0xccb088ff,// 277 PAY 238 

    0x56cd3919,// 278 PAY 239 

    0xa3946e78,// 279 PAY 240 

    0x9fe74185,// 280 PAY 241 

    0xd2e8070a,// 281 PAY 242 

    0x8d95a628,// 282 PAY 243 

    0x39edc4fd,// 283 PAY 244 

    0xc2578bd0,// 284 PAY 245 

    0xa521599c,// 285 PAY 246 

    0x320f5694,// 286 PAY 247 

    0x91ffe11f,// 287 PAY 248 

    0xeaf8a0fd,// 288 PAY 249 

    0x9792a92d,// 289 PAY 250 

    0x68d157fb,// 290 PAY 251 

    0x95633d51,// 291 PAY 252 

    0x354e53b8,// 292 PAY 253 

    0xa4211ba7,// 293 PAY 254 

    0x4d725ce4,// 294 PAY 255 

    0x66e420e8,// 295 PAY 256 

    0x09096b85,// 296 PAY 257 

    0xac0bbd21,// 297 PAY 258 

    0xc0190000,// 298 PAY 259 

/// STA is 1 words. 

/// STA num_pkts       : 81 

/// STA pkt_idx        : 247 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xdc 

    0x03dcdc51 // 299 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 88 (0x58) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt83_tmpl[] = {
    0xb8010058,// 1 CCH   1 

/// ECH cache_idx      : 0x0f 

/// ECH pdu_tag        : 0x00 

    0x000f0000,// 2 ECH   1 

/// SCX is 21 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv insert_icv !check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000015,// 3 SCX   1 

    0x80904853,// 4 SCX   2 

    0x00002382,// 5 SCX   3 

    0xeb6454c7,// 6 SCX   4 

    0x02b9fa5f,// 7 SCX   5 

    0x8685e038,// 8 SCX   6 

    0x45d32e24,// 9 SCX   7 

    0x4e2366c1,// 10 SCX   8 

    0x0ab13862,// 11 SCX   9 

    0xeeed615f,// 12 SCX  10 

    0xe92ebc57,// 13 SCX  11 

    0xc538e765,// 14 SCX  12 

    0x7e39a1bf,// 15 SCX  13 

    0xbcf77dde,// 16 SCX  14 

    0xf1ab0f72,// 17 SCX  15 

    0xfc085ac8,// 18 SCX  16 

    0x810e69fa,// 19 SCX  17 

    0xab6ba3c1,// 20 SCX  18 

    0x8e641d2c,// 21 SCX  19 

    0xc78cbbe1,// 22 SCX  20 

    0xc1532387,// 23 SCX  21 

/// BFD is 3 words. 

/// BFD tot_len        : 248 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 209 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 209 

/// BFD lencrypto      : 32 

/// BFD ofstcrypto     : 152 

/// BFD (ofst+len)cry  : 184 

/// BFD ofstiv         : 44 

/// BFD ofsticv        : 216 

    0x000000d1,// 24 BFD   1 

    0x00980020,// 25 BFD   2 

    0x00d8002c,// 26 BFD   3 

/// MFM is 2 words. 

/// MFM vldnibs        : b 

    0x0b004ab6,// 27 MFM   1 

    0xd7b09580,// 28 MFM   2 

/// BDA is 63 words. 

/// BDA size     is 248 (0xf8) 

/// BDA id       is 0x8d6d 

    0x00f88d6d,// 29 BDA   1 

/// PAY Generic Data size   : 248 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0x3d345847,// 30 PAY   1 

    0x75cf24ed,// 31 PAY   2 

    0xbbba0272,// 32 PAY   3 

    0x7f218899,// 33 PAY   4 

    0x323773d8,// 34 PAY   5 

    0x34227fef,// 35 PAY   6 

    0x742d53b5,// 36 PAY   7 

    0xc17677f9,// 37 PAY   8 

    0x0ceb32b4,// 38 PAY   9 

    0x54cb7777,// 39 PAY  10 

    0xeb13bccb,// 40 PAY  11 

    0x8d257e35,// 41 PAY  12 

    0x3d16a20b,// 42 PAY  13 

    0x2a8efe05,// 43 PAY  14 

    0x09567af1,// 44 PAY  15 

    0x2d5ddb01,// 45 PAY  16 

    0x57702a3b,// 46 PAY  17 

    0xd3e6c183,// 47 PAY  18 

    0x79c4f58f,// 48 PAY  19 

    0x203e4abd,// 49 PAY  20 

    0x62ef77c1,// 50 PAY  21 

    0x9357281e,// 51 PAY  22 

    0x7f0fb911,// 52 PAY  23 

    0x659ae8fc,// 53 PAY  24 

    0x9c431cb1,// 54 PAY  25 

    0x1e91a8d1,// 55 PAY  26 

    0xb3b344ca,// 56 PAY  27 

    0x6b8d17d0,// 57 PAY  28 

    0x5106272c,// 58 PAY  29 

    0xbd9eb1a9,// 59 PAY  30 

    0x91463475,// 60 PAY  31 

    0x85ae7c11,// 61 PAY  32 

    0xe3e99b37,// 62 PAY  33 

    0x9108b5c5,// 63 PAY  34 

    0x82b0eaa1,// 64 PAY  35 

    0x314ac907,// 65 PAY  36 

    0xae06ac7f,// 66 PAY  37 

    0x2bbd51ed,// 67 PAY  38 

    0xa528c2d2,// 68 PAY  39 

    0x06e29501,// 69 PAY  40 

    0x6e851829,// 70 PAY  41 

    0xc16ef1cb,// 71 PAY  42 

    0x2986decd,// 72 PAY  43 

    0xddb34b9d,// 73 PAY  44 

    0x51930764,// 74 PAY  45 

    0xbd00be06,// 75 PAY  46 

    0xd0bf1b28,// 76 PAY  47 

    0x63a0dcc3,// 77 PAY  48 

    0x97773b16,// 78 PAY  49 

    0xf4e2beff,// 79 PAY  50 

    0xef330c9d,// 80 PAY  51 

    0x0fd2a971,// 81 PAY  52 

    0xbe1a9f7b,// 82 PAY  53 

    0x187196bd,// 83 PAY  54 

    0xca644892,// 84 PAY  55 

    0xd902fa54,// 85 PAY  56 

    0xed91cf0b,// 86 PAY  57 

    0x9bbf0d02,// 87 PAY  58 

    0x25f84150,// 88 PAY  59 

    0x2c9168c6,// 89 PAY  60 

    0x11e4eb6e,// 90 PAY  61 

    0x94230425,// 91 PAY  62 

/// STA is 1 words. 

/// STA num_pkts       : 73 

/// STA pkt_idx        : 206 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x16 

    0x03391649 // 92 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 72 (0x48) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt84_tmpl[] = {
    0xb8010048,// 1 CCH   1 

/// ECH cache_idx      : 0x0e 

/// ECH pdu_tag        : 0x00 

    0x000e0000,// 2 ECH   1 

/// SCX is 17 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv !insert_icv check_icv !sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : NORMAL_RC4INIT_AES128 

/// SCX aes_mode        : ECB 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x3 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x0 

/// SCX cryptokey_size  : 16 

/// SCX cryptoiv_size   : 0 

/// SCX authctx_size    : 40 

    0x08000011,// 3 SCX   1 

    0x8080487c,// 4 SCX   2 

    0x00005300,// 5 SCX   3 

    0x690a687b,// 6 SCX   4 

    0xb297f845,// 7 SCX   5 

    0x3b528274,// 8 SCX   6 

    0x398863f3,// 9 SCX   7 

    0xd348ea02,// 10 SCX   8 

    0xbbd5774c,// 11 SCX   9 

    0xed268dea,// 12 SCX  10 

    0x9e2bd57e,// 13 SCX  11 

    0xaef2e50f,// 14 SCX  12 

    0xa7c3e964,// 15 SCX  13 

    0x0c4f67a4,// 16 SCX  14 

    0xb1ea9b73,// 17 SCX  15 

    0x646987f1,// 18 SCX  16 

    0x41d21022,// 19 SCX  17 

/// BFD is 3 words. 

/// BFD tot_len        : 909 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCBC 

/// BFD lenmac         : 574 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 574 

/// BFD lencrypto      : 48 

/// BFD ofstcrypto     : 524 

/// BFD (ofst+len)cry  : 572 

/// BFD ofstiv         : 488 

/// BFD ofsticv        : 736 

    0x0000023e,// 20 BFD   1 

    0x020c0030,// 21 BFD   2 

    0x02e001e8,// 22 BFD   3 

/// MFM is 8 words. 

/// MFM vldnibs        : 3a 

    0x3a00e27d,// 23 MFM   1 

    0xa02b0a18,// 24 MFM   2 

    0x941163fb,// 25 MFM   3 

    0xd0879d6b,// 26 MFM   4 

    0xf8555f5c,// 27 MFM   5 

    0x160f060c,// 28 MFM   6 

    0x046a46af,// 29 MFM   7 

    0xc6899600,// 30 MFM   8 

/// BDA is 229 words. 

/// BDA size     is 909 (0x38d) 

/// BDA id       is 0x8ef 

    0x038d08ef,// 31 BDA   1 

/// PAY Generic Data size   : 909 byte(s) 

/// PAD Buffer Data Pad size   : 3 byte(s) 

    0x8bcc3884,// 32 PAY   1 

    0x43b24b86,// 33 PAY   2 

    0xda18df92,// 34 PAY   3 

    0x0289e5a1,// 35 PAY   4 

    0x30429588,// 36 PAY   5 

    0x0083015f,// 37 PAY   6 

    0x8dd84a57,// 38 PAY   7 

    0xff187053,// 39 PAY   8 

    0xc84c1a22,// 40 PAY   9 

    0x5ddf92f3,// 41 PAY  10 

    0x575e80d5,// 42 PAY  11 

    0x506bb79b,// 43 PAY  12 

    0x498e56aa,// 44 PAY  13 

    0xf465763f,// 45 PAY  14 

    0x51643cc0,// 46 PAY  15 

    0x0cacac93,// 47 PAY  16 

    0xb60e1ab5,// 48 PAY  17 

    0x96f2e49b,// 49 PAY  18 

    0xc0ec5b55,// 50 PAY  19 

    0xe49ac39e,// 51 PAY  20 

    0x2466371d,// 52 PAY  21 

    0x2fa965db,// 53 PAY  22 

    0x5e997376,// 54 PAY  23 

    0x412bf2eb,// 55 PAY  24 

    0x0b2483f3,// 56 PAY  25 

    0xf9b941ec,// 57 PAY  26 

    0xebc5d1a9,// 58 PAY  27 

    0x1e8c3287,// 59 PAY  28 

    0xa68a1469,// 60 PAY  29 

    0xc2a85e9f,// 61 PAY  30 

    0xd1871512,// 62 PAY  31 

    0x760fb4b5,// 63 PAY  32 

    0x415d2b4f,// 64 PAY  33 

    0xce6c9445,// 65 PAY  34 

    0x9f143d6f,// 66 PAY  35 

    0x76a89f3a,// 67 PAY  36 

    0x4ba3485c,// 68 PAY  37 

    0xf66e7cf0,// 69 PAY  38 

    0xc646dc8d,// 70 PAY  39 

    0xfd79d453,// 71 PAY  40 

    0xfd7d0d46,// 72 PAY  41 

    0xd79d722a,// 73 PAY  42 

    0x97ebbad4,// 74 PAY  43 

    0xffefd700,// 75 PAY  44 

    0x9fab533d,// 76 PAY  45 

    0xf91feefb,// 77 PAY  46 

    0xde531f5c,// 78 PAY  47 

    0x008d2522,// 79 PAY  48 

    0xf7a4aa2c,// 80 PAY  49 

    0x3f4de058,// 81 PAY  50 

    0xb36a15d0,// 82 PAY  51 

    0xbdfef8a6,// 83 PAY  52 

    0xabb190eb,// 84 PAY  53 

    0x27e11e59,// 85 PAY  54 

    0xfc4f1ced,// 86 PAY  55 

    0x85a9ead2,// 87 PAY  56 

    0xb6cd7379,// 88 PAY  57 

    0x9a5d61e0,// 89 PAY  58 

    0x56aeaa35,// 90 PAY  59 

    0x7f8a31d7,// 91 PAY  60 

    0xec6a8435,// 92 PAY  61 

    0xb8599bef,// 93 PAY  62 

    0x4ef20e68,// 94 PAY  63 

    0x677b1079,// 95 PAY  64 

    0xe7d1f895,// 96 PAY  65 

    0x8ce1a764,// 97 PAY  66 

    0xa0fe3268,// 98 PAY  67 

    0x1d81b6a9,// 99 PAY  68 

    0xf3abda71,// 100 PAY  69 

    0x4defc312,// 101 PAY  70 

    0xe7029aed,// 102 PAY  71 

    0xdcda25ad,// 103 PAY  72 

    0x37dcdc98,// 104 PAY  73 

    0xa1480b78,// 105 PAY  74 

    0x3d1bc612,// 106 PAY  75 

    0x311cf992,// 107 PAY  76 

    0xbb71d30a,// 108 PAY  77 

    0xbd4e0751,// 109 PAY  78 

    0x1a45a1ea,// 110 PAY  79 

    0xfe6be178,// 111 PAY  80 

    0xba9ccefb,// 112 PAY  81 

    0xc0c7bb84,// 113 PAY  82 

    0x27a61327,// 114 PAY  83 

    0xf5892ce6,// 115 PAY  84 

    0x2661b36f,// 116 PAY  85 

    0x2d63f449,// 117 PAY  86 

    0x527b9628,// 118 PAY  87 

    0x7b2b74ab,// 119 PAY  88 

    0x2ca7c009,// 120 PAY  89 

    0x38a645c1,// 121 PAY  90 

    0x8ff1fd64,// 122 PAY  91 

    0x6c6c8276,// 123 PAY  92 

    0xb1d57ddb,// 124 PAY  93 

    0x86a77899,// 125 PAY  94 

    0x2c6ffe4f,// 126 PAY  95 

    0x6ec91b2f,// 127 PAY  96 

    0x045ee6a3,// 128 PAY  97 

    0x2a56fbda,// 129 PAY  98 

    0x0ea239c5,// 130 PAY  99 

    0x19621cd4,// 131 PAY 100 

    0x8ab58366,// 132 PAY 101 

    0x407d869b,// 133 PAY 102 

    0xcdc3fee0,// 134 PAY 103 

    0x7a8bdcc2,// 135 PAY 104 

    0x5534f69c,// 136 PAY 105 

    0x3851b234,// 137 PAY 106 

    0x91a0cd44,// 138 PAY 107 

    0xc768ff08,// 139 PAY 108 

    0xf18bc453,// 140 PAY 109 

    0xc019f04c,// 141 PAY 110 

    0xab9e7d37,// 142 PAY 111 

    0xa884f9a5,// 143 PAY 112 

    0x3e135742,// 144 PAY 113 

    0x0112284e,// 145 PAY 114 

    0xd7d08d2a,// 146 PAY 115 

    0x964ac898,// 147 PAY 116 

    0xc630b07b,// 148 PAY 117 

    0xc2bca704,// 149 PAY 118 

    0xcfc317fc,// 150 PAY 119 

    0x1ce5de6e,// 151 PAY 120 

    0x036a891a,// 152 PAY 121 

    0x9ce7e9ab,// 153 PAY 122 

    0x26edeab2,// 154 PAY 123 

    0x9391010c,// 155 PAY 124 

    0x3a352344,// 156 PAY 125 

    0x0e1b4e63,// 157 PAY 126 

    0x3d6f8567,// 158 PAY 127 

    0xb98601a2,// 159 PAY 128 

    0xccbee3fc,// 160 PAY 129 

    0x863b9d04,// 161 PAY 130 

    0x93c2f1e8,// 162 PAY 131 

    0x21fcffcf,// 163 PAY 132 

    0x03457108,// 164 PAY 133 

    0xe32dcce0,// 165 PAY 134 

    0xbd6f6d39,// 166 PAY 135 

    0x9e6973c9,// 167 PAY 136 

    0x444b9cd9,// 168 PAY 137 

    0xfcf2793f,// 169 PAY 138 

    0xf60996a3,// 170 PAY 139 

    0x42cebc4c,// 171 PAY 140 

    0x555815ab,// 172 PAY 141 

    0x6b69df63,// 173 PAY 142 

    0x6cd12393,// 174 PAY 143 

    0x3eb135c3,// 175 PAY 144 

    0x027e2249,// 176 PAY 145 

    0xe9f2df3f,// 177 PAY 146 

    0x20be0f4a,// 178 PAY 147 

    0x5860f194,// 179 PAY 148 

    0x558a0c66,// 180 PAY 149 

    0xd48a0cc0,// 181 PAY 150 

    0xb0b2c9c9,// 182 PAY 151 

    0xbdec6f50,// 183 PAY 152 

    0xfba84aff,// 184 PAY 153 

    0xfb7de1c2,// 185 PAY 154 

    0x3bb6da6b,// 186 PAY 155 

    0xd7e5bab1,// 187 PAY 156 

    0x9780b2d0,// 188 PAY 157 

    0x8d3fdeac,// 189 PAY 158 

    0x9f8aad85,// 190 PAY 159 

    0xa236977b,// 191 PAY 160 

    0x719f9e79,// 192 PAY 161 

    0xde39bcde,// 193 PAY 162 

    0xe43a7e3a,// 194 PAY 163 

    0xf4fd7e32,// 195 PAY 164 

    0x3876d059,// 196 PAY 165 

    0xf642b889,// 197 PAY 166 

    0x40edb4b2,// 198 PAY 167 

    0xcffda78a,// 199 PAY 168 

    0xa0a7882a,// 200 PAY 169 

    0x0fafc609,// 201 PAY 170 

    0x642262a9,// 202 PAY 171 

    0xb3cfdf80,// 203 PAY 172 

    0x61ae36b1,// 204 PAY 173 

    0xf4ab69e8,// 205 PAY 174 

    0x0eee852d,// 206 PAY 175 

    0xb26279d5,// 207 PAY 176 

    0x50e4ca4f,// 208 PAY 177 

    0x9346777a,// 209 PAY 178 

    0x9f3c3309,// 210 PAY 179 

    0x61d5a722,// 211 PAY 180 

    0xfabbb03d,// 212 PAY 181 

    0x76dd7a13,// 213 PAY 182 

    0xeae999a1,// 214 PAY 183 

    0xfd140e9d,// 215 PAY 184 

    0x88a0e68b,// 216 PAY 185 

    0xf141e819,// 217 PAY 186 

    0x3bd0ccbe,// 218 PAY 187 

    0xe487ec4b,// 219 PAY 188 

    0x0194aee0,// 220 PAY 189 

    0xf84e5460,// 221 PAY 190 

    0x1cf868af,// 222 PAY 191 

    0xf7d71474,// 223 PAY 192 

    0x5610afdb,// 224 PAY 193 

    0x20ddf83f,// 225 PAY 194 

    0xbecfefef,// 226 PAY 195 

    0xc9aae30b,// 227 PAY 196 

    0x202a3b0e,// 228 PAY 197 

    0xf7a38702,// 229 PAY 198 

    0xa2c0259c,// 230 PAY 199 

    0x57ed21bf,// 231 PAY 200 

    0x4bf1aad9,// 232 PAY 201 

    0x3993e1f3,// 233 PAY 202 

    0x4ce29a6e,// 234 PAY 203 

    0xfe0d8f60,// 235 PAY 204 

    0x825ff14f,// 236 PAY 205 

    0x72bf4b3a,// 237 PAY 206 

    0x114a0abb,// 238 PAY 207 

    0x2cd7dad8,// 239 PAY 208 

    0xd31723dc,// 240 PAY 209 

    0x9db7195a,// 241 PAY 210 

    0x5eae8e1a,// 242 PAY 211 

    0x5e9b9b67,// 243 PAY 212 

    0x0092600b,// 244 PAY 213 

    0x6b5ff530,// 245 PAY 214 

    0x8aa2dfe7,// 246 PAY 215 

    0x33cc0ba3,// 247 PAY 216 

    0x93335d39,// 248 PAY 217 

    0xf9acb386,// 249 PAY 218 

    0xf1311540,// 250 PAY 219 

    0xb06392af,// 251 PAY 220 

    0x5851efff,// 252 PAY 221 

    0x50520ac2,// 253 PAY 222 

    0x08aad551,// 254 PAY 223 

    0xa76c5366,// 255 PAY 224 

    0x15a92790,// 256 PAY 225 

    0xc62b9b5a,// 257 PAY 226 

    0x7b2da50b,// 258 PAY 227 

    0x72000000,// 259 PAY 228 

/// STA is 1 words. 

/// STA num_pkts       : 53 

/// STA pkt_idx        : 49 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0xb4 

    0x00c4b435 // 260 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 96 (0x60) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt85_tmpl[] = {
    0xb8010060,// 1 CCH   1 

/// ECH cache_idx      : 0x04 

/// ECH pdu_tag        : 0x00 

    0x00040000,// 2 ECH   1 

/// SCX is 23 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv !insert_icv check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : RC4UPDT_AES192 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 24 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000017,// 3 SCX   1 

    0x8091487f,// 4 SCX   2 

    0x00001582,// 5 SCX   3 

    0x03827bd8,// 6 SCX   4 

    0x68aef0d9,// 7 SCX   5 

    0xede1d273,// 8 SCX   6 

    0xa9da4a0d,// 9 SCX   7 

    0x4cdbd704,// 10 SCX   8 

    0xec0815db,// 11 SCX   9 

    0x236b37db,// 12 SCX  10 

    0x41283be6,// 13 SCX  11 

    0xd79770ad,// 14 SCX  12 

    0x30955d90,// 15 SCX  13 

    0x884dae2d,// 16 SCX  14 

    0x78d220fa,// 17 SCX  15 

    0x18d8b55a,// 18 SCX  16 

    0x997133dc,// 19 SCX  17 

    0x19b9791c,// 20 SCX  18 

    0x0247d78a,// 21 SCX  19 

    0x6938a9a5,// 22 SCX  20 

    0x9d151e11,// 23 SCX  21 

    0x0501133b,// 24 SCX  22 

    0xda79cdce,// 25 SCX  23 

/// BFD is 3 words. 

/// BFD tot_len        : 320 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 180 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 180 

/// BFD lencrypto      : 4 

/// BFD ofstcrypto     : 144 

/// BFD (ofst+len)cry  : 148 

/// BFD ofstiv         : 84 

/// BFD ofsticv        : 264 

    0x000000b4,// 26 BFD   1 

    0x00900004,// 27 BFD   2 

    0x01080054,// 28 BFD   3 

/// MFM is 6 words. 

/// MFM vldnibs        : 2c 

    0x2c00a95e,// 29 MFM   1 

    0xcc138544,// 30 MFM   2 

    0x49ea920c,// 31 MFM   3 

    0xc104de8d,// 32 MFM   4 

    0x7434d0f6,// 33 MFM   5 

    0x9e4d145a,// 34 MFM   6 

/// BDA is 81 words. 

/// BDA size     is 320 (0x140) 

/// BDA id       is 0xca9 

    0x01400ca9,// 35 BDA   1 

/// PAY Generic Data size   : 320 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0xe1a2d3a3,// 36 PAY   1 

    0xa4ae1a85,// 37 PAY   2 

    0x715d1c2f,// 38 PAY   3 

    0x527f5a14,// 39 PAY   4 

    0xbdde675b,// 40 PAY   5 

    0x66494114,// 41 PAY   6 

    0x908e957b,// 42 PAY   7 

    0x90c7f957,// 43 PAY   8 

    0x2bf2816d,// 44 PAY   9 

    0x20cdbae3,// 45 PAY  10 

    0x00eda6e9,// 46 PAY  11 

    0x9619b3d5,// 47 PAY  12 

    0xf82c60cd,// 48 PAY  13 

    0x22178c5c,// 49 PAY  14 

    0x882a41ef,// 50 PAY  15 

    0x8adbab1d,// 51 PAY  16 

    0x92e4795e,// 52 PAY  17 

    0x7bab02f1,// 53 PAY  18 

    0xb77e7b5c,// 54 PAY  19 

    0x340b2f28,// 55 PAY  20 

    0x060ae5de,// 56 PAY  21 

    0xb3d968cd,// 57 PAY  22 

    0x5d8249ed,// 58 PAY  23 

    0x15cd0d6f,// 59 PAY  24 

    0xf70ccb11,// 60 PAY  25 

    0xeed59214,// 61 PAY  26 

    0x20e20b4e,// 62 PAY  27 

    0xe685694a,// 63 PAY  28 

    0x57d9e6a2,// 64 PAY  29 

    0xe4ce15a6,// 65 PAY  30 

    0x6870f1b0,// 66 PAY  31 

    0x87f8926a,// 67 PAY  32 

    0x33c84392,// 68 PAY  33 

    0x8afdb54d,// 69 PAY  34 

    0x09487e56,// 70 PAY  35 

    0xffea3e55,// 71 PAY  36 

    0x9868f573,// 72 PAY  37 

    0x98968a5c,// 73 PAY  38 

    0x618c12ba,// 74 PAY  39 

    0xdf01f985,// 75 PAY  40 

    0x4ee71f7e,// 76 PAY  41 

    0x3264d1c5,// 77 PAY  42 

    0xcac47846,// 78 PAY  43 

    0x092d9ea2,// 79 PAY  44 

    0x481faa0e,// 80 PAY  45 

    0xf623077a,// 81 PAY  46 

    0x4a3ccd68,// 82 PAY  47 

    0x44ae72fe,// 83 PAY  48 

    0xee50ef4a,// 84 PAY  49 

    0x0bcee416,// 85 PAY  50 

    0x69c85e12,// 86 PAY  51 

    0xc125ea04,// 87 PAY  52 

    0x245e8843,// 88 PAY  53 

    0xc09e2ef5,// 89 PAY  54 

    0x986b0f6b,// 90 PAY  55 

    0x84db9c50,// 91 PAY  56 

    0x1297b421,// 92 PAY  57 

    0x395d6c5c,// 93 PAY  58 

    0xbd27924f,// 94 PAY  59 

    0x2cd0ac9e,// 95 PAY  60 

    0x1399f1ae,// 96 PAY  61 

    0x9723f5c7,// 97 PAY  62 

    0xe3c21aa7,// 98 PAY  63 

    0x8da1031b,// 99 PAY  64 

    0x7baef824,// 100 PAY  65 

    0x8243f1b8,// 101 PAY  66 

    0xb8367ebd,// 102 PAY  67 

    0xa027faee,// 103 PAY  68 

    0x197d793f,// 104 PAY  69 

    0x21893224,// 105 PAY  70 

    0xe2e6e261,// 106 PAY  71 

    0x8a2d8d44,// 107 PAY  72 

    0x7d00b943,// 108 PAY  73 

    0x040e94cd,// 109 PAY  74 

    0x3ab1a727,// 110 PAY  75 

    0x0b2187f4,// 111 PAY  76 

    0xfd052d1c,// 112 PAY  77 

    0x4732be9c,// 113 PAY  78 

    0xd233acf0,// 114 PAY  79 

    0xf685114f,// 115 PAY  80 

/// STA is 1 words. 

/// STA num_pkts       : 126 

/// STA pkt_idx        : 53 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x5e 

    0x00d55e7e // 116 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt86_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x0e 

/// ECH pdu_tag        : 0x00 

    0x000e0000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound !save_icv !insert_icv !check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x4 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000019,// 3 SCX   1 

    0x8092489e,// 4 SCX   2 

    0x00000482,// 5 SCX   3 

    0xc9a76afd,// 6 SCX   4 

    0xf4b02d06,// 7 SCX   5 

    0xee86f5b0,// 8 SCX   6 

    0x5b7fd85b,// 9 SCX   7 

    0xf776db48,// 10 SCX   8 

    0xc31a02a8,// 11 SCX   9 

    0xdb356e6b,// 12 SCX  10 

    0x391b80df,// 13 SCX  11 

    0x2926545b,// 14 SCX  12 

    0xbc7dd194,// 15 SCX  13 

    0x5bfac282,// 16 SCX  14 

    0x231963de,// 17 SCX  15 

    0x7196c9cd,// 18 SCX  16 

    0xbd010e90,// 19 SCX  17 

    0x93423fc2,// 20 SCX  18 

    0x572ff4ed,// 21 SCX  19 

    0x84bf6a30,// 22 SCX  20 

    0x4b12b1b0,// 23 SCX  21 

    0x2f6769cc,// 24 SCX  22 

    0x42717199,// 25 SCX  23 

    0x4f6baf3b,// 26 SCX  24 

    0x500d48a8,// 27 SCX  25 

/// BFD is 3 words. 

/// BFD tot_len        : 664 

/// BFD hdr_len        : 0 

/// BFD sad_type       : ESP_BOTH 

/// BFD crypto_type    : AESCTR 

/// BFD lenmac         : 251 

/// BFD ofstmac        : 0 

/// BFD (ofst+len)mac  : 251 

/// BFD lencrypto      : 52 

/// BFD ofstcrypto     : 192 

/// BFD (ofst+len)cry  : 244 

/// BFD ofstiv         : 136 

/// BFD ofsticv        : 480 

    0x000000fb,// 28 BFD   1 

    0x00c00034,// 29 BFD   2 

    0x01e00088,// 30 BFD   3 

/// MFM is 8 words. 

/// MFM vldnibs        : 36 

    0x3600fb88,// 31 MFM   1 

    0xd697f2cd,// 32 MFM   2 

    0xaa99ecce,// 33 MFM   3 

    0x59f903da,// 34 MFM   4 

    0xaa56a5eb,// 35 MFM   5 

    0x95fb7060,// 36 MFM   6 

    0x26485034,// 37 MFM   7 

    0x6c000000,// 38 MFM   8 

/// BDA is 167 words. 

/// BDA size     is 664 (0x298) 

/// BDA id       is 0xf6c2 

    0x0298f6c2,// 39 BDA   1 

/// PAY Generic Data size   : 664 byte(s) 

/// PAD Buffer Data Pad size   : 0 byte(s) 

    0xdbbed9dd,// 40 PAY   1 

    0x12625417,// 41 PAY   2 

    0x3ba11e02,// 42 PAY   3 

    0x18fd13ee,// 43 PAY   4 

    0x3fcdfca0,// 44 PAY   5 

    0xe32d175f,// 45 PAY   6 

    0x4b32557f,// 46 PAY   7 

    0x82140a07,// 47 PAY   8 

    0x3bfb6992,// 48 PAY   9 

    0x6f2cef1d,// 49 PAY  10 

    0xc55959f7,// 50 PAY  11 

    0xdaed788a,// 51 PAY  12 

    0x96bc6719,// 52 PAY  13 

    0x72a95d9e,// 53 PAY  14 

    0x4d4a3e4d,// 54 PAY  15 

    0xa874d11c,// 55 PAY  16 

    0xc43f31a3,// 56 PAY  17 

    0x59341228,// 57 PAY  18 

    0x4260dcd2,// 58 PAY  19 

    0x93ded0fc,// 59 PAY  20 

    0x72aa71e3,// 60 PAY  21 

    0x25dfc285,// 61 PAY  22 

    0x21ee6f8c,// 62 PAY  23 

    0x8eb6ff63,// 63 PAY  24 

    0x3c4556f8,// 64 PAY  25 

    0x4a2c1f97,// 65 PAY  26 

    0x05bad142,// 66 PAY  27 

    0xf485909c,// 67 PAY  28 

    0x79e86bd0,// 68 PAY  29 

    0x46d6d21d,// 69 PAY  30 

    0x2feae521,// 70 PAY  31 

    0xf8c388e5,// 71 PAY  32 

    0xa38bd9b9,// 72 PAY  33 

    0x220729ec,// 73 PAY  34 

    0xa6e0e6e1,// 74 PAY  35 

    0xa72346e9,// 75 PAY  36 

    0x44e2f6a9,// 76 PAY  37 

    0xdfd1fb15,// 77 PAY  38 

    0x042536a1,// 78 PAY  39 

    0xc73d1c12,// 79 PAY  40 

    0xf23b4a7d,// 80 PAY  41 

    0x8386b044,// 81 PAY  42 

    0x47114a19,// 82 PAY  43 

    0x588c51c8,// 83 PAY  44 

    0x19cdd18c,// 84 PAY  45 

    0xa433baed,// 85 PAY  46 

    0x1e5e2317,// 86 PAY  47 

    0x0e0c59f3,// 87 PAY  48 

    0xe698d84a,// 88 PAY  49 

    0x9d63ad35,// 89 PAY  50 

    0x6d61fcd1,// 90 PAY  51 

    0x9061a2bb,// 91 PAY  52 

    0xfeb94084,// 92 PAY  53 

    0xbd46e44e,// 93 PAY  54 

    0xe5fc18e6,// 94 PAY  55 

    0xd5a840e8,// 95 PAY  56 

    0x70822437,// 96 PAY  57 

    0xa6ac6d16,// 97 PAY  58 

    0x053fb2ef,// 98 PAY  59 

    0x51fc04c6,// 99 PAY  60 

    0x5ca68f12,// 100 PAY  61 

    0x8aa9f34f,// 101 PAY  62 

    0x09bab02d,// 102 PAY  63 

    0xd9384ea7,// 103 PAY  64 

    0x4df80cf4,// 104 PAY  65 

    0x9eef6e81,// 105 PAY  66 

    0x6aa80b32,// 106 PAY  67 

    0x234fee70,// 107 PAY  68 

    0x1258c433,// 108 PAY  69 

    0xfd045260,// 109 PAY  70 

    0xb796052a,// 110 PAY  71 

    0xde5b41a9,// 111 PAY  72 

    0x66ad8510,// 112 PAY  73 

    0x5bc77597,// 113 PAY  74 

    0xdb59bd96,// 114 PAY  75 

    0x0b349a86,// 115 PAY  76 

    0xb8bd938f,// 116 PAY  77 

    0x18d5a502,// 117 PAY  78 

    0xa7ed1c74,// 118 PAY  79 

    0xeb5a62f2,// 119 PAY  80 

    0x73d837fa,// 120 PAY  81 

    0x9063ed9f,// 121 PAY  82 

    0x424af5a9,// 122 PAY  83 

    0x70fe5f16,// 123 PAY  84 

    0x5cc4e16a,// 124 PAY  85 

    0x270c0b3c,// 125 PAY  86 

    0x2733d574,// 126 PAY  87 

    0x5bb80ee0,// 127 PAY  88 

    0x0a280673,// 128 PAY  89 

    0x3a55428b,// 129 PAY  90 

    0x743274d2,// 130 PAY  91 

    0x3e012be5,// 131 PAY  92 

    0x61258a40,// 132 PAY  93 

    0x0792028a,// 133 PAY  94 

    0xe596b208,// 134 PAY  95 

    0x75b3c00b,// 135 PAY  96 

    0xf0662147,// 136 PAY  97 

    0x75326226,// 137 PAY  98 

    0x1918d33b,// 138 PAY  99 

    0x9a9fd0d3,// 139 PAY 100 

    0xab74b1d2,// 140 PAY 101 

    0x216913de,// 141 PAY 102 

    0xc11e3931,// 142 PAY 103 

    0x8545e6e4,// 143 PAY 104 

    0x505b941f,// 144 PAY 105 

    0xf45e6606,// 145 PAY 106 

    0x3f3a1504,// 146 PAY 107 

    0x66df181c,// 147 PAY 108 

    0xe2cd4a52,// 148 PAY 109 

    0xa3a89c7f,// 149 PAY 110 

    0x3a54e520,// 150 PAY 111 

    0x31d9d5d0,// 151 PAY 112 

    0x53b7fa09,// 152 PAY 113 

    0xad0922cc,// 153 PAY 114 

    0xfadcda04,// 154 PAY 115 

    0x17bf791e,// 155 PAY 116 

    0x92a1f21c,// 156 PAY 117 

    0x84b94734,// 157 PAY 118 

    0x3679dc29,// 158 PAY 119 

    0x91b89800,// 159 PAY 120 

    0x66ed7d79,// 160 PAY 121 

    0x68d2bfb6,// 161 PAY 122 

    0x9f8ab1dd,// 162 PAY 123 

    0x83a2c170,// 163 PAY 124 

    0xacb872b7,// 164 PAY 125 

    0x46bdd9a0,// 165 PAY 126 

    0xe1950c67,// 166 PAY 127 

    0x69e99743,// 167 PAY 128 

    0xa9c55ce5,// 168 PAY 129 

    0xe36881c8,// 169 PAY 130 

    0x3c238558,// 170 PAY 131 

    0x720bde03,// 171 PAY 132 

    0x5db5578c,// 172 PAY 133 

    0x71dc0bbb,// 173 PAY 134 

    0x207f971f,// 174 PAY 135 

    0x810c51b1,// 175 PAY 136 

    0x97963451,// 176 PAY 137 

    0xcf20e181,// 177 PAY 138 

    0xa70ff795,// 178 PAY 139 

    0x03adb374,// 179 PAY 140 

    0x7ef840bb,// 180 PAY 141 

    0x958772c9,// 181 PAY 142 

    0x2e6ec2a4,// 182 PAY 143 

    0xe70ae758,// 183 PAY 144 

    0x05b10736,// 184 PAY 145 

    0x6d59d136,// 185 PAY 146 

    0x4d5cc948,// 186 PAY 147 

    0xb566aba2,// 187 PAY 148 

    0xc65c9b22,// 188 PAY 149 

    0xceb09612,// 189 PAY 150 

    0x20600395,// 190 PAY 151 

    0xe37870cc,// 191 PAY 152 

    0xe60eb481,// 192 PAY 153 

    0x7395b4c3,// 193 PAY 154 

    0x760be11f,// 194 PAY 155 

    0x99ccd646,// 195 PAY 156 

    0x78667297,// 196 PAY 157 

    0x5ebf2132,// 197 PAY 158 

    0x2092bbea,// 198 PAY 159 

    0x0325167e,// 199 PAY 160 

    0xd5dfd0ad,// 200 PAY 161 

    0x3359d6a5,// 201 PAY 162 

    0xbf4533a8,// 202 PAY 163 

    0x421b006d,// 203 PAY 164 

    0xccbd4598,// 204 PAY 165 

    0x35f267ca,// 205 PAY 166 

/// STA is 1 words. 

/// STA num_pkts       : 233 

/// STA pkt_idx        : 239 

/// STA err_code       : SUCCESS 

/// STA error_details  : 0x5b 

    0x03bc5be9 // 206 STA   1 

};

//

/// CCH is 1 words  

/// CCH is NEW format  

/// CCH Opcode      = GENERIC (0x1) 

/// CCH CCTX length = 104 (0x68) 

/// CCH pipe select = 0 

/// CCH incl_sctx !incl_bct incl_bdesc incl_mfm  

/// CCH incl_bdata !incl_hash !incl_supdt !incl_sps !drop_bdata  

uint32 tx_aes_sha1_pkt87_tmpl[] = {
    0xb8010068,// 1 CCH   1 

/// ECH cache_idx      : 0x0e 

/// ECH pdu_tag        : 0x00 

    0x000e0000,// 2 ECH   1 

/// SCX is 25 words. 

/// SCX SA Type (sa_type) GENERIC  

/// SCX !cacheable !update_en lock_en  

/// SCX inbound save_icv insert_icv check_icv sctx_iv  

/// SCX !exp_iv !gen_iv  

/// SCX order           : ENC_AUTH 

/// SCX encralg         : AES 

/// SCX authalg         : SHA1 

/// SCX aes_size        : AES256 

/// SCX aes_mode        : CTR 

/// SCX authmode        : HMAC 

/// SCX authtype        : NORMAL_AES128 

/// SCX icv_size        : 0x5 

/// SCX iv_ovr_ofst     : 0x0 

/// SCX exp_iv_size     : 0x2 

/// SCX cryptokey_size  : 32 

/// SCX cryptoiv_size   : 16 

/// SCX authctx_size    : 40 

    0x08000019,// 3 SCX   1 

    0x809248c1,// 4 SCX   2 

    0x00007582,// 5 SCX   3 

    0x50aa5fdf,// 6 SCX   4 

    0xfc339b3c,// 7 SCX   5 

    0xd9f1ac38,// 8 SCX   6 

    0xa9f8d163,// 9 SCX   7 

    0x99b872e4,// 10 SCX   8 

    0x02e272ff,// 11 SCX   9 

    0x64174364,// 12 SCX  10 

    0xc590938d,// 13 SCX  11 

    0xaf0e5121,// 14 SCX  12 

    0x4ae5b26d,// 15 SCX  13 

    0xd507d074,// 16 SCX  14 

    0x9611fa12,// 17 SCX  15 

    0x2952e6fb,// 18 SCX  16 



