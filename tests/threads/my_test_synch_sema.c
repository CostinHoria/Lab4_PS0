#include "threads/thread.h"
#include <debug.h>
#include <stddef.h>
#include <random.h>
#include <stdio.h>
#include <string.h>
#include "threads/flags.h"
#include "threads/interrupt.h"
#include "threads/intr-stubs.h"
#include "threads/palloc.h"
#include "threads/switch.h"
#include "threads/synch.h"
#include "threads/vaddr.h"
#include "threads/thread.h"

struct semaphore sem;
struct semaphore sem2;
int nr=0;

void thread_body1(void *param){

    sema_down(&sem2);
    //print_thread_info(thread_current());
    printf(" \n Id: %ld si status %d\n",(long)thread_tid(),thread_current()->status);
    nr=nr+2;
    sema_up(&sem2);


    //thread_exit();
    //printf(" \n Id: %ld si status %d\n",(long)thread_tid(),thread_current()->status);

    //return NULL;
    sema_up(&sem);
    print_thread_info(thread_current());
}

void my_test_synch_sema(void){
    sema_init_name(&sem,0,"THE_test_semaphore");
    sema_init(&sem2,1);
  /*char *s="noname";
  char *sin;
  strcpy(sin,s);
  printf("\n-%s-\n",sin);
  printf("\nMERGE SEMAFORUL!\n");*/
  
  tid_t t[10];
    for(int i=0;i<10;i++)
    {
        
        //int id = (int)t;
        //printf("\n id-ul %d\n",id);
        char ci = (char)i;
        char	*s = "Thread-ul nr:", p[50],	buf[30];
        //printf("\n The string for the num is %c", ci);
	   //strlcpy(buf, s, sizeof(buf));
       //strlcat(buf, p, sizeof(buf));
       //printf("\n_____________%s______\n",buf);
	   //(void)strlcat(buf, p, sizeof(buf));


        //tid_t t;
        t[i] = thread_create(s,PRI_DEFAULT,thread_body1,NULL);
        sema_down(&sem);

        //printf(" \n Id: %ld si status %d\n",(long)thread_tid(),thread_current()->status);

    }
    printf(" \n Id-ul thread-ului principal: %ld si nr = %d\n",(long)thread_tid(), nr);

    return NULL;
}
