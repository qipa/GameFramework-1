GameFramework
=============

必要なライブラリ
freeglut ?
glfw3
glew たぶん必要ない
freetype2
FTGL

includeフォルダ:
ヘッダファイル置き場
include直下には, 基本的なインターフェースだけおいてある.
大体使うのはその下にある, glfwフォルダの下のファイル.
さらにそこにあるGLFW, GLフォルダの中には, glfw3.h やfreeglut.hが置いてあるので,
それぞれのライブラリの関数を使いたいときはここからインクルードする(自分のGLFWやfreeglutの場所からインクルードしても良い)

srcフォルダ:
フレームワーク用のcppファイルを入れてある. 
"cmake ."
"make"
で, 何も無ければ, libGLFWGame.aがつくられる.
一つ上のlibフォルダに入っているのは、ここで作られたライブラリファイル

libフォルダ:
作成した.aファイルを置く場所.















