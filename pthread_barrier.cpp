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

void *wakeUp(void *args){

    cout << "I wait for 3 sec.." << endl;
    sleep(3);
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
    
    pthread_exit(0);
}


/*
 * 
 */
int main(int argc, char** argv) {
 
    pthread_t tid1, tid2, tid3;
    int t1, t2, t3;
    
    pid_t pid = getpid();
    FILE *f = fopen("main.pid", "w");
    fprintf(f, "%u", pid);
    cout << "PID:" << pid << endl;
    fclose(f);

    t1 = pthread_create(&tid1, NULL, helloCond, NULL);
    t2 = pthread_create(&tid2, NULL, helloBarrier, NULL);
    t3 = pthread_create(&tid3, NULL, wakeUp, NULL);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mLock);
    
    return 0;
}

