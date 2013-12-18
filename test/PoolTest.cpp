#include "../include/Pool.h"
#include <iostream>
using namespace std;
int main()
{
  class IntFactory: public PoolObjectFactory<int>
  {
    inline int* createObject()
    {
      int *i = new int;
      *i = 5;
      return i;
    }

    inline void initializeObject(int *object)
    {
    }
  };

  IntFactory *f = new IntFactory();
  Pool<int> pool(f, 100);

  cout << *pool.newObject() << endl;
  
  return 0;
}
