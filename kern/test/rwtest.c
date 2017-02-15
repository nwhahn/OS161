/*
 * All the contents of this file are overwritten during automated
 * testing. Please consider this before changing anything in this file.
 */

#include <types.h>
#include <lib.h>
#include <clock.h>
#include <thread.h>
#include <synch.h>
#include <test.h>
#include <kern/test161.h>
#include <spinlock.h>


#define CREATELOOPS 8
#define NRWLOCKLOOPS 12
#define NTHREADS 32

static volatile unsigned long testval1;
static volatile unsigned long testval2;
static volatile unsigned long testval3;
//static struct semaphore *testsem = NULL;
static struct rwlock *testrw = NULL;
static struct semaphore *donesem = NULL;

struct spinlock status_lock;
static bool test_status = TEST161_FAIL;
/*
 * Use these stubs to test your reader-writer locks.
 */
//void 
//rwtestthread(void *junk,unsigned long num){
//	(void) junk;
  //      int i;
        
       // for(i=0;i<NRWLOCKLOOPS;i++){


         
//	}


//}
int rwtest(int nargs, char **args) {
	(void)nargs;
	(void)args;
        
        
        
//rwlock_acquire_read,rwlock_release_read,rwlock_acquire_write,rwlock_release_write         

 
        
	kprintf_n("rwt1 unimplemented\n");
	success(TEST161_FAIL, SECRET, "rwt1");

	return 0;
}

static
void
readtestthread(void *junk, unsigned long num)
{
	(void) junk;
        int i;

	for(i=0;i<NRWLOCKLOOPS;i++){
        	kprintf_t(".");
        	rwlock_acquire_read(testrw);
                random_yielder(4);

		testval1 = num;
		testval2= num*num;
		testval3= num%3;

		if (testval2 != testval1*testval1) {
			goto fail;
		}
		random_yielder(4);
 //               kprintf_n("pass1");
		if (testval2%3 != (testval3*testval3)%3) {
			goto fail;
		}
    //            kprintf_n("pass2");
		random_yielder(4);

		if (testval3 != testval1%3) {
			goto fail;
		}
		random_yielder(4);
  //              kprintf_n("pass3");
		if (testval1 != num) {
			goto fail;
		}
		random_yielder(4);
//		kprintf_n("pass4");
		if (testval2 != num*num) {
			goto fail;
		}
		random_yielder(4);
//                kprintf_n("pass5");

		if (testval3 != num%3) {
			goto fail;
		}
		random_yielder(4);
               // kprintf_n("pass6");
//                bool x = !(lock_do_i_hold(testlock));
        //        kprintf_n("%d\n",x);
	//	if (!(lock_do_i_hold(testlock))) {
		//	kprintf_n("sad");
		//	goto fail;
                        
	//	}
           //     kprintf_n("pass7/n");
	//	random_yielder(4);
		
	}

	V(donesem);
  
	return;

fail:
	rwlock_release_read(testrw);
        kprintf_n("fail1\n");


}
int rwtest2(int nargs, char **args) {
	(void)nargs;
	(void)args;
        
        int i,result;
        kprintf_n("starting rwt2...\n");
        for(i=0;i<CREATELOOPS;i++){
	        kprintf_t(".");      testrw = rwlock_create("test read/write");
 
                if(testrw == NULL){

                	panic("rwt2: rwlock_create failed\n");
		}
                donesem = sem_create("donesem",0);
                if(donesem == NULL){
			panic("rwt2:sem_create failed\n");

		}
                if(i!=CREATELOOPS-1){
                	rwlock_destroy(testrw);
                        sem_destroy(donesem);
                }
               
        }
        test_status = TEST161_SUCCESS;
        for(i=0;i<NTHREADS;i++){
		kprintf_t(".");
                result= thread_fork("rwtest",NULL,readtestthread,NULL,i);
                if(result){
			panic("rwt2:thread_fork failed: %s\n", strerror(result));

		}
	}
	for(i=0;i<NTHREADS;i++){
		kprintf_t(".");
                KASSERT(donesem!=NULL);
                P(donesem);	
	}
         
        rwlock_destroy(testrw); 
        sem_destroy(donesem);
        testrw= NULL;
        donesem= NULL;
        kprintf_t("\n");       
//	kprintf_n("rwt2 unimplemented\n");
	success(test_status, SECRET, "rwt2");
         
	return 0;
}

int rwtest3(int nargs, char **args) {
	(void)nargs;
	(void)args;

	kprintf_n("rwt3 unimplemented\n");
	success(TEST161_FAIL, SECRET, "rwt3");

	return 0;
}

int rwtest4(int nargs, char **args) {
	(void)nargs;
	(void)args;

	kprintf_n("rwt4 unimplemented\n");
	success(TEST161_FAIL, SECRET, "rwt4");

	return 0;
}

int rwtest5(int nargs, char **args) {
	(void)nargs;
	(void)args;

	kprintf_n("rwt5 unimplemented\n");
	success(TEST161_FAIL, SECRET, "rwt5");

	return 0;
}
