/*
 * Copyright (c) 2001, 2002, 2009
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

/*
 * Driver code is in kern/tests/synchprobs.c We will
 * replace that file. This file is yours to modify as you see fit.
 *
 * You should implement your solution to the whalemating problem below.
 */

#include <types.h>
#include <lib.h>
#include <thread.h>
#include <test.h>
#include <synch.h>

/*
 * Called by the driver during initialization.
 */
//static struct cv *match_cv=NULL;
static struct cv *male_cv=NULL;
static struct cv *female_cv=NULL;
//static struct lock *whale_lock=NULL;
static struct lock *male_lock=NULL;
static struct lock *female_lock= NULL;
static struct lock *match_lock=NULL;
//static int males=0;
//static int females=0;
static struct semaphore *male_sem = NULL;
static struct semaphore *female_sem=NULL;



void whalemating_init() {
	male_cv=cv_create("whale cv");
	female_cv=cv_create("whale cv");
//	match_cv=cv_create("whale cv");
//	whale_lock=lock_create("whale lock");	
	male_lock=lock_create("whale lock");
	female_lock=lock_create("whale lock");		
	match_lock=lock_create("whale lock");

	male_sem=sem_create("whale sem",0);
	female_sem=sem_create("whale sem",0);
	return;
}

/*
 * Called by the driver during teardown.
 */

void
whalemating_cleanup() {
	cv_destroy(male_cv);
	cv_destroy(female_cv);
//	cv_destroy(match_cv);
//	lock_destroy(whale_lock);	
	lock_destroy(male_lock);
	lock_destroy(female_lock);
	lock_destroy(match_lock);

	sem_destroy(male_sem);
	sem_destroy(female_sem);

	male_cv=NULL;
	female_cv=NULL;
	male_lock=NULL;
	female_lock=NULL;
	match_lock=NULL;
	male_sem=NULL;
	female_sem=NULL;
	return;
}

void
male(uint32_t index)
{
//	(void)index;
	/*
	 * Implement this function by calling male_start and male_end when
	 * appropriate.
	 */
//	struct lock *male=NULL;
        male_start(index);
//	male=lock_create("sa");
//	males++;
	V(male_sem);
	lock_acquire(male_lock);
	cv_wait(male_cv,male_lock);
	lock_release(male_lock);
//	panic("gets jegere");
//	lock_destroy(male);
	P(male_sem);

//	lock_acquire(match_lock);
//	cv_signal(match_cv,match_lock);
//	males--;
  	male_end(index); 

    	 
	return;
}

void
female(uint32_t index)
{
	(void)index;
	/*
	 * Implement this function by calling female_start and female_end when
	 * appropriate.
	 */
	female_start(index);
//	females++;
  	V(female_sem);
	lock_acquire(female_lock);      
	cv_wait(female_cv,female_lock);
	lock_release(female_lock);
	P(female_sem);

//	females--;	
//	lock_acquire(match_lock);
//	cv_signal(match_cv,match_lock);

	female_end(index);
	return;
}

void
matchmaker(uint32_t index)
{
	(void)index;
	/*
	 * Implement this function by calling matchmaker_start and matchmaker_end
	 * when appropriate.
	 */
	matchmaker_start(index);

//	cv_wait(female_cv);
//	while(male_sem->sem_count>0 && female_sem->sem_count>0){
		lock_acquire(match_lock);
		cv_signal(male_cv,match_lock);
		lock_release(match_lock);
//		lock_acquire(match_lock);
//		cv_wait(match_cv,match_lock);
	//	lock_release(match_lock);
		
//	panic("%d %d\n",male_sem->sem_count,female_sem->sem_count);		
		lock_acquire(match_lock);
		cv_signal(female_cv,match_lock);
		lock_release(match_lock);
//		lock_acquire(match_lock);
//		cv_wait(match_cv,match_lock);
	//	lock_release(match_lock);
//	}					
	
//panic("%d %d\n",male_sem->sem_count,female_sem->sem_count);		
	
	matchmaker_end(index);

	

//	panic("%d %d\n",male_sem->sem_count,female_sem->sem_count);		
	return;
}
