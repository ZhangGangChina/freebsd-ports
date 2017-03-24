--- sql/wsrep_utils.cc.orig	2017-03-19 22:33:42.769864000 +0100
+++ sql/wsrep_utils.cc	2017-03-19 22:34:12.295629000 +0100
@@ -26,6 +26,7 @@
 #include <sql_class.h>
 #include <socket_connection.h>
 
+#include <signal.h>
 #include <spawn.h>    // posix_spawn()
 #include <unistd.h>   // pipe()
 #include <errno.h>    // errno
