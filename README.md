# blog-project
### 项目说明
本项目支持显示静态博客，加法计算，trust游戏。

 - include
	 - conf.h 一些常量宏定义和debug宏定义
	 - Type.h 是对多数文件类型与对应Content-Type的定义 
	 - mytcp.h 是对socket的包装
	 - myhttp.h 是对于http请求的响应

 - src
	 - test.cpp main函数定义
 
 - website 相关网页资源

### 编译以及运行
编译请用支持`c++11`的`g++`编译器。在`blog-project`目录下，
```
make        #仅编译
make run    #编译且运行
```

### 效果

 - 博客 : http://127.0.0.1:8080
 - 加法，如 : http://127.0.0.1:8080/add/222/333
 - trust : http://127.0.0.1:8080/trust/index.html

### 注意
博客原内容来自 https://purecss.io/layouts/blog/ 。其中有两张图片引自[flickr](https://www.flickr.com/)，可能会出现无法访问的情况。
