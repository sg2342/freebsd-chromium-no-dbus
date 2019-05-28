--- content/public/app/content_packaged_services_manifest.cc.orig	2019-04-30 22:22:47 UTC
+++ content/public/app/content_packaged_services_manifest.cc
@@ -23,7 +23,7 @@
 #include "services/video_capture/public/cpp/manifest.h"
 #include "services/viz/public/cpp/manifest.h"
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
 #include "components/services/font/public/cpp/manifest.h"  // nogncheck
 #endif
 
@@ -67,7 +67,7 @@ const service_manager::Manifest& GetContentPackagedSer
         .PackageService(tracing::GetManifest())
         .PackageService(video_capture::GetManifest())
         .PackageService(viz::GetManifest())
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
         .PackageService(font_service::GetManifest())
 #endif
 #if defined(OS_CHROMEOS)
