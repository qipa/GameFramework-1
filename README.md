GameFramework
=============
includeフォルダ:
この中に基本的に全部ある. 今の所cppファイルもここにおいてる.
glfwフォルダの下に,cppファイルがあるからこれを
"g++ -std=c++0x -c *.cpp"
で, 全部コンパイルする
んで,
"ar r libGLFWGame.a *.o"
で, libGLFWGame.a というライブラリにまとめる.
できた, libGLFWGame.a GameFramework直下にあるbinフォルダの下におく.

srcフォルダ:
特に何も入れてない, のちのちここにフレームワークのcppファイルをおく予定

libフォルダ:
作成した.aファイルを置く場所.


testフォルダ:
フレームワークテスト用のプログラムをおいている.
cmakeでビルドする. 
ビルドするときは, 作成したlibファイルと, glfw, glut, openglをリンカしないといけない.(今の所glewは無くてもokぽい)










