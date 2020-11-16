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
#define BUF_SIZE 8


long buf[BUF_SIZE];
size_t n = 0;
size_t in = 0;
size_t out = 0;
struct condition not_full;
struct condition not_empty;
struct lock lock;

struct semaphore sem;

void consumer_body(void *param)
{
    lock_acquire(&lock);
    while(n == 0)
        cond_wait(&not_empty,&lock);
    long c;
    //
    while(buf[out++ % BUF_SIZE]==0)
        out++;
    //if(c != 0)
    //{
        //buf[out++ % BUF_SIZE] = 0;
    //out = (out + 1)/n;
    c = buf[out++ % BUF_SIZE];
    printf("\nCONSUMER with id %ld has consumed data: %ld\n",(long)thread_tid(),c);
    //}
    n--;
    cond_signal(&not_full,&lock);
    lock_release(&lock);

    sema_up(&sem);
}

void producer_body(void *param)
{
    lock_acquire(&lock);
    while( n == BUF_SIZE)
        cond_wait(&not_full,&lock);
    long l = 0;
    l = (long) thread_tid();
    //char c = (char)l;
    buf[in++ % BUF_SIZE] = l;
    //in = (in + 1)/n;
    printf("\nPRODUCER with id %ld has produced data: %ld\n",(long)thread_tid(),l);
    n++;
    cond_signal(&not_empty,&lock);
    lock_release(&lock);

    //sema_up(&sem);
}

void my_test_producer_consumer(void)
{
    printf("\n PRODUCER - CONSUMER \n");
    
    sema_init(&sem,2);

    cond_init(&not_empty);
    cond_init(&not_full);
    lock_init(&lock);

    tid_t producers[8];
    tid_t consumers[8];

    for(int i=0;i<8;i++){
        producers[i] = thread_create("",PRI_DEFAULT,producer_body,NULL);
        consumers[i] = thread_create("",PRI_DEFAULT,consumer_body,NULL);
        for(int j=0;j< BUF_SIZE;j++)
        {
            printf("[%d] = %ld, ",j,buf[j]);
        }
    }

    sema_down(&sem);
    return NULL;
}