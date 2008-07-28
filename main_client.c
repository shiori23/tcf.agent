/*******************************************************************************
 * Copyright (c) 2007, 2008 Wind River Systems, Inc. and others.
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Eclipse Public License v1.0 
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 * The Eclipse Public License is available at
 * http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at 
 * http://www.eclipse.org/org/documents/edl-v10.php.
 *  
 * Contributors:
 *     Wind River Systems - initial API and implementation
 *******************************************************************************/

/*
 * Agent main module.
 */

#include "mdep.h"
#define CONFIG_MAIN
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <signal.h>
#include "asyncreq.h"
#include "events.h"
#include "trace.h"
#include "cmdline.h"
#include "channel.h"
#include "protocol.h"
#include "proxy.h"
#include "discovery.h"
#include "discovery_help.h"

static char * progname;

/* 
 * main entry point for TCF client
 * 
 * The client is a simple shell permitting communication with the TCF agent.
 * By default the client will run in interactive mode. The client accepts
 * 3 command line options:
 * -L <log_file>        : specify a log file
 * -l <log_mode>        : logging level see trace.c for more details
 * -S <script_file>     : script of commands to run - non-interactive mode
 */
 
#if defined(_WRS_KERNEL)
int tcf_client(void) {
#else   
int main(int argc, char ** argv) {
#endif
    int c;
    int ind;
    int error;
    int interactive = 1;
    char * s;
    char * log_name = 0;
    char * script_name = 0;
    char * node = NULL;
    Protocol * proto;

    ini_mdep();
    ini_trace();
    ini_asyncreq();
    ini_events_queue();

#if defined(_WRS_KERNEL)
    
    progname = "tcf";
    open_log_file("-");
    log_mode = 0;
    
#else
    
    progname = argv[0];

    /* Parse arguments */
    for (ind = 1; ind < argc; ind++) {
        s = argv[ind];
        if (*s != '-') {
            break;
        }
        s++;
        while ((c = *s++) != '\0') {
            switch (c) {
            case 'l':
            case 'L':
            case 'S':
                if (*s == '\0') {
                    if (++ind >= argc) {
                        fprintf(stderr, "%s: error: no argument given to option '%c'\n", progname, c);
                        exit(1);
                    }
                    s = argv[ind];
                }
                switch (c) {
                case 'l':
                    log_mode = strtol(s, 0, 0);
                    break;

                case 'L':
                    log_name = s;
                    break;

                case 'S':
                    script_name = s;
                    interactive = 0;
                    break;

                default:
                    fprintf(stderr, "%s: error: illegal option '%c'\n", progname, c);
                    exit(1);
                }
                s = "";
                break;

            default:
                fprintf(stderr, "%s: error: illegal option '%c'\n", progname, c);
                exit(1);
            }
        }
    }
    
    open_log_file(log_name);
    
#endif

    discovery_start(create_default_discovery_master);
    if (script_name != NULL) open_script_file(script_name);
    ini_cmdline_handler(interactive);

    /* Process events - must run on the initial thread since ptrace()
     * returns ECHILD otherwise, thinking we are not the owner. */
    run_event_loop();
    return 0;
}
