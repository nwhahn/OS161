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

#include <types.h>
//#include <unistd.h>
#include <copyinout.h>
#include <syscall.h>
#include <file_syscall.h>
#include <proc.h>
#include <current.h>
#include <uio.h>
#include <vnode.h>
#include <thread.h>


/*
 * Example system call: get the time of day.
 */

int
sys_open(const char *filename, int flags, mode_t mode){
	(void) filename;
	(void) flags;
	(void) mode;
	return 0;
}

ssize_t
sys_write(int fd, const void *buf, size_t buflen,int *retval)
{
//take the int fd and create the vnode from the corresponding filehandler
//call vop write
//handle errors on output 
	int result;
	(void) retval;
	struct proc *proc = curproc;
	struct filehandler *fh= proc->filetable[fd];
	struct iovec iov;
        struct uio myuio;
        struct addrspace *as;

		
        as = proc_getas();

	//fd not valid file descriptor
	if(proc->filetable[fd]==NULL){
		retval=(int *)(30);
		return -1;
	}
	//address space invalid
	if(as==NULL){
		retval=(int *)(6);
		return -1;
	}	
        uio_kinit(&iov, &myuio,(void *)buf,buflen,(off_t)fh->offset, UIO_WRITE);
        result = VOP_WRITE(fh->fileobject, &myuio);
        if (result) {
                return result;
        }



	//error catching
	//No free space in filesystem
/*	if(){
		retval=36;
		return -1;
	}*/
	//Hardware I/O error occured while writing data	
/*	if(){
		retval=32;
		return -1;
	}*/
	return (ssize_t)0;
}

void _exit(int exitcode){
	(void) exitcode;
	thread_exit();		
		
}
ssize_t read(int fd, const void *buf, size_t buflen, int *retval){
		
	int result;
	(void) retval;
	struct proc *proc = curproc;
	struct filehandler *fh= proc->filetable[fd];
	struct iovec iov;
        struct uio myuio;
        struct addrspace *as;

			
        as = proc_getas();

	//fd not valid file descriptor
	if(proc->filetable[fd]==NULL){
		retval=(int *)(30);
		return -1;
	}
	//address space invalid
	if(as==NULL){
		retval=(int *)(6);
		return -1;
	}	
        uio_kinit(&iov, &myuio,(void *)buf,buflen,(off_t)fh->offset, UIO_READ);
        result = VOP_READ(fh->fileobject, &myuio);
        if (result) {
                return result;
        }



	//error catching
	//Hardware I/O error occured while writing data	
/*	if(){
		retval=32;
		return -1;
	}*/
	return 0;
}



