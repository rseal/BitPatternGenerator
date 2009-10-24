#ifndef STHREAD_H
#define STHREAD_H

#include <iostream>
#include <sys/time.h>
#include <errno.h>
#include <pthread.h>
#include <bpg-v2/Common/Lock.hpp>

using std::cerr;
using std::endl;

class SThread
{
  
public:

    SThread() {  
	pthread_mutex_init(&mutex_,NULL);
	pthread_attr_init(&attr_);
	pthread_cond_init(&condition_, NULL);
    }

    virtual ~SThread(){
    }

    virtual void Run()=0;
 
    static void* Init(void* ptr){
	SThread* p_object = reinterpret_cast<SThread*>(ptr);
	p_object->Run();
	return NULL;
    }

    void StartThread(){
	if((pthread_create(&p_sthread_, NULL, Init, this)) < 0)
	    cerr << "STHREAD: thread creation failed" << endl;
    }    
 
    void Wait(){ pthread_join(p_sthread_, NULL);}

    void Detach(){pthread_detach(p_sthread_);}

    void Destroy(){
	int status;
	pthread_exit(reinterpret_cast<void*>(&status));
    }

    void Pause(){
	ScopedPThreadLock Lock(mutex_);
	pthread_cond_wait(&condition_, &mutex_);
    }

    void Wake(){ pthread_cond_signal(&condition_);}
  
    void Sleep(int type = USEC, long value = 1000){
	int status=0;

	gettimeofday(&time_now_, NULL);

	switch(type){
	case USEC:
	    timeout_.tv_sec = time_now_.tv_sec;
	    timeout_.tv_nsec = time_now_.tv_usec + 1000*value;
	    break;
	case MSEC:
		timeout_.tv_sec = time_now_.tv_sec;
		timeout_.tv_nsec = time_now_.tv_usec + static_cast<long>(1e6*value);
	    

	    break;
	case SEC:
	    timeout_.tv_sec = time_now_.tv_sec + value;
	    timeout_.tv_nsec = time_now_.tv_usec*1000;
	    break;
	default:
	    cerr << "STHREAD: invalid sleep value. default to 1 sec" << endl;
	    timeout_.tv_sec = time_now_.tv_sec + 1;
	    timeout_.tv_nsec = time_now_.tv_usec*1000;
	}
	
	while(status != ETIMEDOUT)
	    status  = pthread_cond_timedwait(&condition_, &mutex_, &timeout_);
    }  

    void Priority(int value);
    void SetCondition(int value);

    enum{ USEC, MSEC, SEC};
protected:
    pthread_t p_sthread_;
    pthread_mutex_t mutex_;
    pthread_attr_t attr_;
    pthread_cond_t condition_;
    timeval time_now_;
    timespec timeout_;
};

#endif
