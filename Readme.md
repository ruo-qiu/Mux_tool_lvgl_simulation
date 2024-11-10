1. 进入ubuntu系统

2. 安装必要库

~~~
sudo apt-get update && sudo apt-get install -y build-essential libsdl2-dev cmake
~~~

3. 进入mux_tool_lvgl\build文件
4. 执行

~~~
cmake ..
~~~

5. 执行编译

~~~
make -j
~~~

6. 如果使用vscode的话，先回到mux_tool_lvgl目录，然后code .即可

~~~
code .
~~~

