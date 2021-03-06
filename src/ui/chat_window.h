/* Functions for creating and managing chat windows
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

#ifndef CHAT_WINDOW_H
#define CHAT_WINDOW_H

#include "../irc_network.h"
#include "buffer.h"

#include <gtk/gtk.h>

/* Struct containing all the important widgets for a window, passed to most
 * controlling the widgets in each window
 */
struct sqchat_chat_window {
    GtkWidget * window;
    GtkWidget * top_vertical_container;

    GtkWidget * main_menu_bar;
    GtkWidget * main_menu;
    GtkWidget * main_menu_item;
    GtkWidget * connect_menu_item;
    GtkWidget * new_server_buffer_menu_item;
    GtkWidget * exit_menu_item;

    GtkWidget * tools_menu;
    GtkWidget * tools_menu_item;
    GtkWidget * preferences_menu_item;

    GtkWidget * help_menu_item;
    GtkWidget * help_menu;
    GtkWidget * about_menu_item;

    GtkWidget * network_tree_and_buffer_pane;

    GtkWidget * scrolled_window_for_network_tree;
    GtkWidget * network_tree;
    GtkTreeStore * network_tree_store;
    GtkTreeIter network_tree_toplevel;

    GtkWidget * chat_viewer_and_user_list_pane;

    GtkWidget * buffer_and_command_box_container;

    GtkWidget * scrolled_window_for_user_list;
    GtkWidget * user_list;

    struct sqchat_buffer * current_buffer;
};

// TODO: Remove the "create_" part in the function name
extern struct sqchat_chat_window * sqchat_chat_window_new(struct sqchat_network * network);

extern void sqchat_chat_window_change_active_buffer(struct sqchat_chat_window * window,
                                                    struct sqchat_buffer * new_buffer)
    _attr_nonnull(1, 2);

#endif // CHAT_WINDOW_H

// vim: set expandtab tw=80 shiftwidth=4 softtabstop=4 cinoptions=(0,W4:
