/*
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

#include "chat_window.h"
#include "../commands.h"
#include "../chat.h"

#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

void command_box_activated_handler(GtkEntry * entry,
                                   struct sqchat_buffer * buffer) {
    char * input = strdup(gtk_entry_get_text(entry));
    guint16 input_len = gtk_entry_get_text_length(entry);
    // If the input is a blank message or a blank command, do nothing
    switch (input_len) {
        case 0:
            return;
            break;
        case 1:
            if (input[0] == '/')
                return;
            break;
        case 2:
            if (input[0] == '/' && input[1] == '/')
                return;
            break;
    }

    // Check whether or not the input is a command and act accordingly
    if (input[0] == '/' && input[1] != '/') {
        char * param_start;
        char * command_end;
        char * command;
        char * cursor;

        // Start the cursor right after the /
        cursor = input + 1;

        // Extract the name of the command
        command_end = strchr(input, ' ');
        if (command_end == NULL) {
            command = cursor;
            param_start = NULL;
        }
        else {
            *command_end = '\0';
            command = cursor;
            cursor = command_end + 1;

            // Extract the parameters
            for (param_start = cursor; *param_start == ' '; ++param_start);
        }

        sqchat_call_command(buffer, command, param_start);
    } else {
        if (buffer->type == NETWORK)
            sqchat_buffer_print(buffer,
                                "You can't say stuff in this buffer!\n");
        else if (buffer->network->status != CONNECTED)
            sqchat_buffer_print(buffer,
                                "Not connected!\n");
        else {
            sqchat_send_privmsg(buffer->network,
                         buffer->buffer_name,
                         input);
            sqchat_buffer_print(buffer, "<%s> %s\n",
                                buffer->network->nickname,
                                input);
        }
    }

    free(input);
    gtk_entry_set_text(entry, "");
}

GtkWidget * sqchat_command_box_new(GtkEntryBuffer * entry_buffer,
                                   struct sqchat_buffer * buffer) {
    GtkWidget * command_box = gtk_entry_new_with_buffer(entry_buffer);
    g_signal_connect(command_box, "activate",
                     G_CALLBACK(command_box_activated_handler), buffer);
    return command_box;
}

// vim: set expandtab tw=80 shiftwidth=4 softtabstop=4 cinoptions=(0,W4:
