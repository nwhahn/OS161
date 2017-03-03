/*
 * Copyright (c) 2000, 2001, 2002, 2003, 2004, 2005, 2008, 2009
 *	The President and Fellows of Harvard College.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
M
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Basic vnode ops functions.
 */
#include <types.h>
#include <kern/errno.h>
#include <lib.h>
#include <synch.h>
#include <vfs.h>
#include <vnode.h>
#include <proc.h>
#define O_READONLY 0
#define O_WRITEONLY 1

int vop_read(struct vnode *file, struct uio *uio){
	(void) file;
	(void) uio;
//	vfs_open(vfs_getcwd(uio), int openflags,mode_t mode,file);	
//	uio->uio_resid=0;
//	uio->uio_offset = uio->uio_resid + uio->uio_offset;

//	vfs_close();
	return 0;

}


int vop_write(struct vnode *file, struct uio *uio){
	(void) file;
	(void) uio;
//	uio->uio_resid=0;
//	uio->uio_offset = uio->uio_resid + uio->uio_offset;
		
	
load_segment(getas(),file,uio->uio_offset, vaddr_t vaddr, size_t memsize, size_t filesize,0)

	
	vfs_open(vfs_getcwd(uio),O_WRITEONLY,0,file);
	
//	uio_move(void *ptr, uio->uio_resid, uio);			
			
	return 0;

}


int vop_isseekable(struct vnode *object){
	(void) object;
	return 0;

}



