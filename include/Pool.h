#ifndef POOL_H_2013_12_16
#define POOL_H_2013_12_16

#include <stack>
using namespace std;

//メモリプールのクラス
//PoolObjectFactoryクラスを継承して, 必要なクラスを生成するFactoryクラスを作成し, 引数として送る
template<class T>
class PoolObjectFactory
{
public:
  PoolObjectFactory(){}
  virtual ~PoolObjectFactory(){}
  virtual inline T* createObject()=0;                  //クラスを生成する
  virtual inline void initializeObject(T *object)=0;  //クラスを初期化する
};

template<class T>
class Pool
{
public:  
  Pool( PoolObjectFactory<T> *_factory, int _maxSize)
    :maxSize(_maxSize), factory(_factory)
  {
  }

  ~Pool()
  {
    delete factory;
  }

  inline T* newObject()
  {
    T* object = NULL;

    if(freeObjects.empty())
    {
      object = factory->createObject();
    }
    else
    {      
      object = freeObjects.top();
      freeObjects.pop();
    }
    factory->initializeObject(object);  //初期化する
    return object;
  }

  void inline freeObject(T *object)
  {
    if(freeObjects.size() < maxSize)
      freeObjects.push(object);
    else
      delete object;    //再大容量を超えた場合はしょうがないので削除
  }
private:
  stack<T*> freeObjects;
  PoolObjectFactory<T> *const factory;
  const int maxSize;
};

#endif
