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
 * Local memory heap manager.
 */

#include "mdep.h"
#include <string.h>
#include "trace.h"
#include "myalloc.h"

void * loc_alloc(size_t size) {
    void * p;

    if (size == 0) {
        size = 1;
    }
    if ((p = malloc(size)) == NULL) {
        perror("malloc");
        exit(1);
    }
    trace(LOG_ALLOC, "loc_alloc(%d) = %#x", size, p);
    return p;
}

void * loc_alloc_zero(size_t size) {
    void * p;

    if (size == 0) {
        size = 1;
    }
    if ((p = malloc(size)) == NULL) {
        perror("malloc");
        exit(1);
    }
    memset(p, 0, size);
    trace(LOG_ALLOC, "loc_alloc_zero(%d) = %#x", size, p);
    return p;
}

void * loc_realloc(void * ptr, size_t size) {
    void * p;

    if (size == 0) {
        size = 1;
    }
    if ((p = realloc(ptr, size)) == NULL) {
        perror("realloc");
        exit(1);
    }
    trace(LOG_ALLOC, "loc_realloc(%#x, %d) = %#x", ptr, size, p);
    return p;
}

void loc_free(void *p) {
    trace(LOG_ALLOC, "loc_free %#x", p);
    free(p);
}


/*
 * strdup() with end-of-memory checking.
 */
char * loc_strdup(const char * s) {
    char * rval = loc_alloc(strlen(s) + 1);
    strcpy(rval, s);
    return rval;
}


/*
 * strdup2() with concatenation and  end-of-memory checking.
 */
char * loc_strdup2(const char * s1, const char * s2) {
    char * rval = loc_alloc(strlen(s1) + strlen(s2) + 1);
    strcpy(rval, s1);
    strcat(rval, s2);
    return rval;
}


/*
 * strndup() with end-of-memory checking.
 */
char * loc_strndup(const char * s, size_t len) {
    char * rval = loc_alloc(len + 1);
    strncpy(rval, s, len);
    rval[len] = '\0';
    return rval;
}
