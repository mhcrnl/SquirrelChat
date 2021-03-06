/* Data structures for storing information and buffers for an IRC network, and
 * functions for handling said structures
 *
 * Copyright (C) 2013 Stephen Chandler Paul
 *
 * This file is free software: you may copy it, redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of this License or (at your option) any
 * later version.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __IRC_NETWORK_H__
#define __IRC_NETWORK_H__

#include "macros.h"
#include "trie.h"

#include <gtk/gtk.h>
#include <glib.h>
#include <netdb.h>
#include <stdbool.h>
#include <string.h>

#include <gnutls/gnutls.h>

struct sqchat_server {
    char * address;
    char * port;
    bool ssl;
};

typedef struct sqchat_server sqchat_server;

struct sqchat_network {
    // Network information
    GSList * servers;
    GSList * current_server;
    char * name;
    char * password;
    // TODO: Add flags here

    char * nickname;
    char * username;
    char * real_name;

    // ISUPPORT and CAP info
    char * chantypes;
    char * server_name;
    char * version;
    char * chanmodes;
    char * usermodes;
    char * chanmodes_a; // See http://www.irc.org/tech_docs/005.html for info
    char * chanmodes_b;
    char * chanmodes_c;
    char * chanmodes_d;
    char * prefix_chars;
    char * prefix_symbols;
    void (*casemap_lower)(char *);
    void (*casemap_upper)(char *);
    int (*casecmp)(const char *, const char *);
    bool excepts                        : 1;
    bool invex                          : 1;
    bool callerid                       : 1;
    bool elist_mask_supported           : 1;
    bool elist_negate_mask_supported    : 1;
    bool elist_usercount_supported      : 1;
    bool elist_creation_time_supported  : 1;
    bool elist_topic_search_supported   : 1;
    bool multi_prefix                   : 1;
    bool sasl                           : 1;

    bool away                           : 1;

    bool destroy_on_disconnect          : 1;
    bool                                : 0;

    gnutls_session_t ssl_session;
    gnutls_certificate_credentials_t ssl_cred;
    int socket;
    GThread * addr_res_thread;

    enum {
        DISCONNECTED,
        ADDR_RES,
        HANDSHAKE,
        CONNECTED,
        REHANDSHAKE
    } status;

    char recv_buffer[SQCHAT_MSG_BUF_LEN];
    int buffer_cursor;
    size_t buffer_fill_len;
    GIOChannel * input_channel;

    struct sqchat_chat_window * window;

    struct sqchat_buffer * buffer;
    sqchat_trie * buffers;
    struct sqchat_cmd_response_claim * claimed_responses;
};

extern sqchat_server * sqchat_parse_server_string(char * input)
    _attr_nonnull(1);

extern struct sqchat_network * sqchat_network_new();
extern void sqchat_network_destroy(struct sqchat_network * network)
    _attr_nonnull(1);

extern void sqchat_network_connect(struct sqchat_network * network)
    _attr_nonnull(1);
extern void sqchat_network_disconnect(struct sqchat_network * network,
                                      const char * msg)
    _attr_nonnull(1);

#define SQCHAT_IS_CHAN(_network, _str) (strchr((_network)->chantypes, *(_str)))

#endif /* __IRC_NETWORK_H__ */
// vim: set expandtab tw=80 shiftwidth=4 softtabstop=4 cinoptions=(0,W4:
