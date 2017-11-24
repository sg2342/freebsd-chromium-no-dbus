--- ./services/device/wake_lock/power_save_blocker/power_save_blocker_x11.cc.orig	2017-11-24 04:17:40.308866000 +0000
+++ ./services/device/wake_lock/power_save_blocker/power_save_blocker_x11.cc	2017-11-24 04:27:12.853187000 +0000
@@ -29,10 +29,12 @@
 #include "base/nix/xdg_util.h"
 #include "base/single_thread_task_runner.h"
 #include "base/synchronization/lock.h"
+#ifndef DEVICE_POWER_SAVE_BLOCKER_DUMMY
 #include "dbus/bus.h"
 #include "dbus/message.h"
 #include "dbus/object_path.h"
 #include "dbus/object_proxy.h"
+#endif
 #include "ui/gfx/switches.h"
 #include "ui/gfx/x/x11_types.h"
 
@@ -40,10 +42,14 @@
 
 enum DBusAPI {
   NO_API,           // Disable. No supported API available.
+#ifndef DEVICE_POWER_SAVE_BLOCKER_DUMMY
   GNOME_API,        // Use the GNOME API. (Supports more features.)
   FREEDESKTOP_API,  // Use the FreeDesktop API, for KDE4, KDE5, and XFCE.
+#endif
 };
 
+
+#ifndef DEVICE_POWER_SAVE_BLOCKER_DUMMY
 // Inhibit flags defined in the org.gnome.SessionManager interface.
 // Can be OR'd together and passed as argument to the Inhibit() method
 // to specify which power management features we want to suspend.
@@ -68,6 +74,7 @@
 const char kFreeDesktopAPIScreenServiceName[] = "org.freedesktop.ScreenSaver";
 const char kFreeDesktopAPIScreenInterfaceName[] = "org.freedesktop.ScreenSaver";
 const char kFreeDesktopAPIScreenObjectPath[] = "/org/freedesktop/ScreenSaver";
+#endif
 
 }  // namespace
 
@@ -110,10 +117,12 @@
   void ApplyBlock();
   void RemoveBlock();
 
+#ifndef DEVICE_POWER_SAVE_BLOCKER_DUMMY
   // Asynchronous callback functions for ApplyBlock and RemoveBlock.
   // Functions do not receive ownership of |response|.
   void ApplyBlockFinished(dbus::Response* response);
   void RemoveBlockFinished(dbus::Response* response);
+#endif
 
   // Wrapper for XScreenSaverSuspend. Checks whether the X11 Screen Saver
   // Extension is available first. If it isn't, this is a no-op.
@@ -157,7 +166,9 @@
   // after ApplyBlock() has finished.
   bool enqueue_unblock_;
 
+#ifndef DEVICE_POWER_SAVE_BLOCKER_DUMMY
   scoped_refptr<dbus::Bus> bus_;
+#endif
 
   // The cookie that identifies our inhibit request,
   // or 0 if there is no active inhibit request.
@@ -236,9 +247,14 @@
 }
 
 bool PowerSaveBlocker::Delegate::ShouldBlock() const {
+#ifndef DEVICE_POWER_SAVE_BLOCKER_DUMMY
   return freedesktop_only_ ? api_ == FREEDESKTOP_API : api_ != NO_API;
+#else
+  return false;
+#endif
 }
-
+ 
+#ifndef DEVICE_POWER_SAVE_BLOCKER_DUMMY
 void PowerSaveBlocker::Delegate::ApplyBlock() {
   DCHECK(blocking_task_runner_->RunsTasksInCurrentSequence());
   DCHECK(!bus_);  // ApplyBlock() should only be called once.
@@ -413,6 +429,7 @@
   bus_->ShutdownAndBlock();
   bus_ = nullptr;
 }
+#endif
 
 void PowerSaveBlocker::Delegate::XSSSuspendSet(bool suspend) {
   DCHECK(ui_task_runner_->RunsTasksInCurrentSequence());
@@ -460,6 +477,7 @@
   // Power saving APIs are not accessible in headless mode.
   if (base::CommandLine::ForCurrentProcess()->HasSwitch(switches::kHeadless))
     return NO_API;
+#ifndef DEVICE_POWER_SAVE_BLOCKER_DUMMY
   std::unique_ptr<base::Environment> env(base::Environment::Create());
   switch (base::nix::GetDesktopEnvironment(env.get())) {
     case base::nix::DESKTOP_ENVIRONMENT_GNOME:
@@ -478,6 +496,7 @@
       // Not supported.
       break;
   }
+#endif
   return NO_API;
 }
 
