#ifndef LOCK_H_2013_12_22
#define LOCK_H_2013_12_22

#include <pthread.h>

//スレッドのロック, アンロックをするクラス
class Lock
{
  pthread_mutex_t *mtx;
public:
  //コンストラクタでロックする
  explicit Lock(pthread_mutex_t *pm)
    :mtx(pm)
  {
    pthread_mutex_lock(mtx);
  }

  //デストラクタでアンロックする
  ~Lock()
  {
    pthread_mutex_unlock(mtx);    
  }
};

#endif
