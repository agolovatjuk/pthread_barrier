/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pthread_barrier.cpp
 * Author: golo
 *
 * Created on 14 февраля 2016 г., 0:17
 */

/*
 Напишите многопоточную программу (POSIX Threads).

Должны быть как минимум:

    Один поток, ожидающий события по условной переменной.
    Один поток, ожидающий достижения барьера.

Текст программы должен находиться в файле /home/box/main.cpp
PID запущенного процесса должен быть сохранен в файле /home/box/main.pid
 */
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

pthread_mutex_t   mLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t    cond = PTHREAD_COND_INITIALIZER;
pthread_barrier_t bLock;

void *wakeUp(void *args){

    cout << "I wait for 2 sec.." << endl;
    sleep(2);
    cout << "Wake up, helloCond!" << endl;
    pthread_cond_signal(&cond);
//    sleep(1);
    pthread_exit(0);    
}

void *helloCond(void *args){
    
    cout << "helloCond is sleeping.." << endl;
    pthread_cond_wait(&cond, &mLock);
    
    cout << "helloCond got signal and woked up" << endl;
    pthread_mutex_unlock(&mLock);
    
    pthread_exit(0);
}

void *helloBarrier(void *args){
    
    cout << "helloBarrier is wait Barrier and sleeping 3 s.." << endl;
    pthread_barrier_wait(&bLock);
    sleep(3);
    cout << "helloBarrier is over Barrier" << endl;

    pthread_exit(0);
}


/*
 * 
 */
int main(int argc, char** argv) {
 
    pthread_t tid1, tid2, tid3, tid4;
    int t1, t2, t3, t4;
    
    pid_t pid = getpid();
    FILE *f = fopen("main.pid", "w");
    fprintf(f, "%u", pid);
    cout << "PID:" << pid << endl;
    fclose(f);

    pthread_barrier_init(&bLock, NULL, 2);
    
    t1 = pthread_create(&tid1, NULL, helloCond, NULL);
    t2 = pthread_create(&tid2, NULL, helloBarrier, NULL);
    t3 = pthread_create(&tid3, NULL, wakeUp, NULL);
    t4 = pthread_create(&tid4, NULL, helloBarrier, NULL);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mLock);
    pthread_barrier_destroy(&bLock);
    
    return 0;
}

