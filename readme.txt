一、在 WIN32 平台下如何编译 polarssl.1.2.11
1、必须得用 VC2010 编译（当用 VC2012 打开时不要更新工程文件）
2、若使用 ACL 的静态库方式，则 polarssl
也必须采用静态库编译方式（如：Multi-threaded Debug (/MTd) 或 Multi-threaded
(/MT)）
3、若想在 lib_acl_cpp/src/stream/polarssl_io.cpp 中使用 havege_init
的随机生成算法，则需打开 include/polarssl/config.h 中，打开 "#define
POLARSSL_HAVEGE_C" 的编译开关
4、现在 polarssl_conf & polarssl_io 支持动态加载 polarssl 的动态库，编译 polarssl
动态库的方法：
make lib SHARED=yes
注：polarssl 库将 ssl_list_ciphersuites 函数的实现放在 ssl.h 头文件中，导致无法
动态加载，所以需要把其实现代码放在 ssl_tls.c 中，在 ssl.h 中仅留下函数声明

