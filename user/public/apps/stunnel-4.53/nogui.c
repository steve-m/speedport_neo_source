/*
 *   stunnel       Universal SSL tunnel
 *   Copyright (C) 1998-2012 Michal Trojnara <Michal.Trojnara@mirt.net>
 *
 *   This program is free software; you can redistribute it and/or modify it
 *   under the terms of the GNU General Public License as published by the
 *   Free Software Foundation; either version 2 of the License, or (at your
 *   option) any later version.
 * 
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *   See the GNU General Public License for more details.
 * 
 *   You should have received a copy of the GNU General Public License along
 *   with this program; if not, see <http://www.gnu.org/licenses>.
 * 
 *   Linking stunnel statically or dynamically with other modules is making
 *   a combined work based on stunnel. Thus, the terms and conditions of
 *   the GNU General Public License cover the whole combination.
 * 
 *   In addition, as a special exception, the copyright holder of stunnel
 *   gives you permission to combine stunnel with free software programs or
 *   libraries that are released under the GNU LGPL and with code included
 *   in the standard release of OpenSSL under the OpenSSL License (or
 *   modified versions of such code, with unchanged license). You may copy
 *   and distribute such a system following the terms of the GNU GPL for
 *   stunnel and the licenses of the other code concerned.
 * 
 *   Note that people who make modified versions of stunnel are not obligated
 *   to grant this special exception for their modified versions; it is their
 *   choice whether to do so. The GNU General Public License gives permission
 *   to release a modified version without this exception; this exception
 *   also makes it possible to release a modified version which carries
 *   forward this exception.
 */

#include "common.h"
#include "prototypes.h"

int main(int argc, char *argv[]) {
    static struct WSAData wsa_state;

    if(WSAStartup(MAKEWORD(1, 1), &wsa_state))
        return 1;
    main_initialize();
    if(main_configure(argc>1 ? argv[1] : NULL, argc>2 ? argv[2] : NULL))
        return 1;
    main_execute();
    return 0;
}

int passwd_cb(char *buf, int size, int rwflag, void *userdata) {
    return 0; /* not implemented */
}

#ifdef HAVE_OSSL_ENGINE_H
int pin_cb(UI *ui, UI_STRING *uis) {
    return 0; /* not implemented */
}
#endif

/* end of nogui.c */
