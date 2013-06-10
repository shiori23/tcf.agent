/*******************************************************************************
 * Copyright (c) 2010, 2012 Wind River Systems, Inc. and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 * The Eclipse Public License is available at
 * http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 * http://www.eclipse.org/org/documents/edl-v10.php.
 * You may elect to redistribute this code under either of these licenses.
 *
 * Contributors:
 *     Wind River Systems - initial API and implementation
 *******************************************************************************/

/*
 * This module implements ELF relocation records handling for reading DWARF debug information.
 *
 * Functions in this module use exceptions to report errors, see exceptions.h
 */

#ifndef D_dwarfreloc
#define D_dwarfreloc

#include <tcf/config.h>

#if ENABLE_ELF

#include <tcf/services/tcf_elf.h>

/* Apply relocation for a vulue in 'buf' that is taken from section 's' at offset 'offset' and
 * has size of 'size' bytes. 'dst' is set to relocation target section.
 * Note: 'buf' has host endianness.
 */
extern void drl_relocate(ELF_Section * s, U8_T offset, void * buf, size_t size, ELF_Section ** dst);

#endif /* ENABLE_ELF */

#endif /* D_dwarfreloc */
