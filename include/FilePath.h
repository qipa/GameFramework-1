#ifndef FILE_PATH_H_2013_12_24
#define FILE_PATH_H_2013_12_24

#include <string>
using namespace std;


class FilePath
{
  string& Path()
  {
    static string path = "";
    return path;    
  }  
public:
  FilePath() {   }    
  ~FilePath() {  }
  void setPath(string path)
  {
    Path() = path;    
  }

  string getPath()
  {
    return Path();    
  }  
};

#endif
