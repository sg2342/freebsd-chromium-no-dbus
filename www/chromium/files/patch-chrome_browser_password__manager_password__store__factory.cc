--- chrome/browser/password_manager/password_store_factory.cc.orig	2017-11-24 03:55:09.720600000 +0000
+++ chrome/browser/password_manager/password_store_factory.cc	2017-11-24 03:58:14.093427000 +0000
@@ -53,7 +53,9 @@
 #if defined(USE_LIBSECRET)
 #include "chrome/browser/password_manager/native_backend_libsecret.h"
 #endif
+#ifndef KWALLET_DBUS_DUMMY
 #include "chrome/browser/password_manager/native_backend_kwallet_x.h"
+#endif
 #include "chrome/browser/password_manager/password_store_x.h"
 #endif
 
@@ -203,6 +205,7 @@
   std::unique_ptr<PasswordStoreX::NativeBackend> backend;
   if (selected_backend == os_crypt::SelectedLinuxBackend::KWALLET ||
       selected_backend == os_crypt::SelectedLinuxBackend::KWALLET5) {
+#ifndef KWALLET_DBUS_DUMMY
     VLOG(1) << "Trying KWallet for password storage.";
     base::nix::DesktopEnvironment used_desktop_env =
         selected_backend == os_crypt::SelectedLinuxBackend::KWALLET
@@ -215,6 +218,7 @@
     } else {
       backend.reset();
     }
+#endif
   } else if (selected_backend == os_crypt::SelectedLinuxBackend::GNOME_ANY ||
              selected_backend ==
                  os_crypt::SelectedLinuxBackend::GNOME_KEYRING ||
