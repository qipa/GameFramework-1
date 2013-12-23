#ifndef LOCK_H_2013_12_22
#define LOCK_H_2013_12_22

#include <pthread.h>

class Lock
{
  pthread_mutex_t *mtx;
public:
  explicit Lock(pthread_mutex_t *pm)
    :mtx(pm)
  {
    pthread_mutex_lock(mtx);
  }  
  ~Lock()
  {
    pthread_mutex_unlock(mtx);    
  }
};

#endif
