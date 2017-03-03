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
/*
 * Example system call: get the time of day.
 */
int
sys_write(int fd, const void *buf, size_t buflen,int *retval)
{
	
//	int result;
	(void) fd;
	(void) buf;
	(void) buflen;
	(void) retval;
//	result=1;
	struct proc *proc = curproc;
	struct filehandler *fh= proc->filetable[fd];

	

	(void)fh;


//	if (result) {
//		return result;
//	}
	//error catching
	//fd not valid file descriptor
/*	if(fd==NULL){
		retval=30;
		return -1;
	}*/
	//address space invalid
/*	if(){
		retval=6;
		return -1;
	}*/	
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
	return 0;
}

void sys_exit(int exitcode){
	(void) exitcode;
		

	struct proc *proc = curproc;	
	proc_destroy(proc);
}
