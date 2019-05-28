--- chrome/browser/sync/chrome_sync_client.cc.orig	2019-04-30 22:22:36 UTC
+++ chrome/browser/sync/chrome_sync_client.cc
@@ -427,7 +427,7 @@ ChromeSyncClient::CreateDataTypeControllers(syncer::Sy
   }
 #endif  // BUILDFLAG(ENABLE_APP_LIST)
 
-#if defined(OS_LINUX) || defined(OS_WIN)
+#if defined(OS_LINUX) || defined(OS_WIN) || defined(OS_BSD)
   // Dictionary sync is enabled by default.
   if (!disabled_types.Has(syncer::DICTIONARY)) {
     if (base::FeatureList::IsEnabled(switches::kSyncPseudoUSSDictionary)) {
@@ -443,7 +443,7 @@ ChromeSyncClient::CreateDataTypeControllers(syncer::Sy
           base::CreateSingleThreadTaskRunnerWithTraits({BrowserThread::UI})));
     }
   }
-#endif  // defined(OS_LINUX) || defined(OS_WIN)
+#endif  // defined(OS_LINUX) || defined(OS_WIN) || defined(OS_BSD)
 
 #if defined(OS_CHROMEOS)
   if (arc::IsArcAllowedForProfile(profile_) &&
