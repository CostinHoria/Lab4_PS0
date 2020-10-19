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

void thread_body(void *param){
    print_thread_info(thread_current());
}

void my_test_create_threads(void *param){
    tid_t t[6];
    for(int i=1;i<=5;i++)
    {
        int id = (int)t;
        printf("\n id-ul %d\n",id);
        char* c= "DA";
        t[i] = thread_create(c,PRI_DEFAULT,thread_body,NULL);

    }
}