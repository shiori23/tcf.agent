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
 * Double linked list support.
 */

#ifndef D_link
#define D_link

typedef struct LINK LINK;

struct LINK {
    LINK * next;
    LINK * prev;
};

#define list_init(list) do { \
            (list)->next = (list)->prev = (list);   \
        } while(0)

#define list_is_empty(list) ((list)->next == (list) && (list)->prev == (list))

#define list_remove(item) do { \
            (item)->prev->next = (item)->next;         \
            (item)->next->prev = (item)->prev;         \
        } while(0)

#define list_add_first(item,list) do { \
            (item)->next = (list)->next; (item)->prev = (list);         \
            (list)->next->prev = (item); (list)->next = (item);         \
        } while(0)

#define list_add_last(item,list) do { \
            (item)->next = (list); (item)->prev = (list)->prev; \
            (list)->prev->next = (item); (list)->prev = (item); \
        } while(0)

#define list_concat(item,list) if (!list_is_empty(list)) { \
            (item)->prev->next = (list)->next; \
            (list)->next->prev = (item)->prev; \
            (item)->prev = (list)->prev; \
            (list)->prev->next = (item); \
        }

#endif
