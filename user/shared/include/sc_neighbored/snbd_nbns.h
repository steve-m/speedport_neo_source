#ifndef _SNBD_NBNS_H_
#define _SNBD_NBNS_H_

#include <stdint.h>

#define NBNS_QUERY_NAME_LEN 34
struct nbns_hdr {
    uint16_t name_trn_id;
    uint16_t flags;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
} __attribute__((packed));
#define NBNS_HDR(x) ((struct nbns_hdr *)(x))
#define NBNS_HDR_SIZE   (sizeof(struct nbns_hdr))

struct nbns_hdr_info {
    uint16_t name_trn_id;

    /* flags */
    uint16_t r:1;
#define R_SHIFT 15
#define R_MASK (1 << R_SHIFT)
#define R(flags) (((flags) & R_MASK) >> R_SHIFT)
    uint16_t opcode:4;
#define OPCODE_SHIFT 11
#define OPCODE_MASK (0xf << OPCODE_SHIFT)
#define OPCODE(flags) (((flags) & OPCODE_MASK) >> OPCODE_SHIFT)
#define OPCODE_QUERY        0
#define OPCODE_REGISTRATION 5
#define OPCODE_RELEASE      6
#define OPCODE_WACK         7
#define OPCODE_REFRESH      8
    uint16_t aa:1;
    uint16_t tc:1;
    uint16_t rd:1;
    uint16_t ra:1;
    uint16_t reserved_1:1;
    uint16_t reserved_2:1;
    uint16_t b:1;
    uint16_t rcode:4;

    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
};

struct nbns_query {
    uint8_t  name[NBNS_QUERY_NAME_LEN];
    uint16_t type;
    uint16_t cls;
} __attribute__((packed));
#define NBNS_QUERY_SIZE (sizeof(struct nbns_query))

struct nbns_additional_rr {
    uint8_t  id;
    uint8_t  rr_name;
    uint16_t rr_type;
    uint16_t rr_class;
    uint32_t ttl;
    uint16_t rdlength; /* 0x0006 */
    uint16_t nb_flags;
#define NB_FLAGS_G_SHIFT 15
#define NB_FLAGS_G_MASK  (1 << NB_FLAGS_G_SHIFT)
#define NB_FLAGS_G(f) (((f) & NB_FLAGS_G_MASK) >> NB_FLAGS_G_SHIFT)
#define NB_FLAGS_ONT_SHIFT 12
#define NB_FLAGS_ONT_MASK  (0x3 << NB_FLAGS_ONT_SHIFT)
#define NB_FLAGS_ONT(f) (((f) & NB_FLAGS_ONT_MASK) >> NB_FLAGS_ONT_SHIFT)
    uint32_t nb_address;
} __attribute__((packed));

struct nbns_registration_request {
    struct nbns_hdr hdr;
    struct nbns_query qhdr;
    struct nbns_additional_rr rr;
} __attribute__((packed));
#define NBNS_REGISTRATION_REQUEST(x) ((struct nbns_registration_request *)(x))

int snbd_nbns_socket_init(char *ifname);
int snbd_nbns_socket_handle(int fd);

#endif /* _SNBD_NBNS_H_ */
