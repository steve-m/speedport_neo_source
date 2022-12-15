#include <sys/types.h>
#include <arpa/nameser.h>  /* NS_INT16SZ, NS_CMPRSFLGS */

/* Melinda, 2014/06/26, ++++ Start ++++*/
/*************************** ns_get32 *******************************/
#undef NS_GET32
#define NS_GET32(l, cp) do { \
	register u_char *t_cp = (u_char *)(cp); \
	(l) = ((u_int32_t)t_cp[0] << 24) \
	    | ((u_int32_t)t_cp[1] << 16) \
	    | ((u_int32_t)t_cp[2] << 8) \
	    | ((u_int32_t)t_cp[3]) \
	    ; \
	(cp) += NS_INT32SZ; \
} while (0)
u_long
ns_get32(const u_char *src) {
	u_long dst;

	NS_GET32(dst, src);
	return (dst);
}
/* Melinda, 2014/06/26, ++++ End ++++*/

/*************************** ns_get16 *******************************/

#undef NS_GET16
#if 0
#define NS_GET16(s, cp) \
  do {									      \
    const uint16 *t_cp = (const uint16 *) (cp);			      \
    (s) = ntohs (*t_cp);						      \
    (cp) += NS_INT16SZ;							      \
  } while (0)
#else
#define NS_GET16(s, cp) do { \
	register const u_char *t_cp = (const u_char *)(cp); \
	(s) = ((u_int16_t)t_cp[0] << 8) \
	    | ((u_int16_t)t_cp[1]) \
	    ; \
	(cp) += NS_INT16SZ; \
} while (0)
#endif
u_int
ns_get16(const u_char *src) {
	u_int dst;

	NS_GET16(dst, src);
	return (dst);
}


/*************************** dn_skipname *******************************/

#define NS_TYPE_ELT			0x40 /*%< EDNS0 extended label type */
#define DNS_LABELTYPE_BITSTRING		0x41

static int
labellen(const u_char *lp)
{
	int bitlen;
	u_char l = *lp;

	if ((l & NS_CMPRSFLGS) == NS_CMPRSFLGS) {
		/* should be avoided by the caller */
		return(-1);
	}

	if ((l & NS_CMPRSFLGS) == NS_TYPE_ELT) {
		if (l == DNS_LABELTYPE_BITSTRING) {
			if ((bitlen = *(lp + 1)) == 0)
				bitlen = 256;
			return((bitlen + 7 ) / 8 + 1);
		}
		return(-1);	/*%< unknwon ELT */
	}
	return(l);
}

/*%
 *	Advance *ptrptr to skip over the compressed name it points at.
 *
 * return:
 *\li	0 on success, -1 (with errno set) on failure.
 */
int
ns_name_skip(const u_char **ptrptr, const u_char *eom)
{
	const u_char *cp;
	u_int n;
	int l;

	cp = *ptrptr;
	while (cp < eom && (n = *cp++) != 0) {
		/* Check for indirection. */
		switch (n & NS_CMPRSFLGS) {
		case 0:			/*%< normal case, n == len */
			cp += n;
			continue;
		case NS_TYPE_ELT: /*%< EDNS0 extended label */
			if ((l = labellen(cp - 1)) < 0) {
				//__set_errno (EMSGSIZE);
				return(-1);
			}
			cp += l;
			continue;
		case NS_CMPRSFLGS:	/*%< indirection */
			cp++;
			break;
		default:		/*%< illegal type */
			//__set_errno (EMSGSIZE);
			return (-1);
		}
		break;
	}
	if (cp > eom) {
		//__set_errno (EMSGSIZE);
		return (-1);
	}
	*ptrptr = cp;
	return (0);
}

/*
 * Skip over a compressed domain name. Return the size or -1.
 */
int
__dn_skipname(const u_char *ptr, const u_char *eom) {
	const u_char *saveptr = ptr;

	if (ns_name_skip(&ptr, eom) == -1)
		return (-1);
	return (ptr - saveptr);
}
