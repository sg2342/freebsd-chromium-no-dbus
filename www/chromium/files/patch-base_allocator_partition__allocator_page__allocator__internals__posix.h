--- base/allocator/partition_allocator/page_allocator_internals_posix.h.orig	2019-04-30 22:22:27 UTC
+++ base/allocator/partition_allocator/page_allocator_internals_posix.h
@@ -14,7 +14,7 @@
 #if defined(OS_MACOSX)
 #include <mach/mach.h>
 #endif
-#if defined(OS_LINUX)
+#if defined(OS_BSD) || defined(OS_LINUX)
 #include <sys/resource.h>
 
 #include <algorithm>
@@ -48,7 +48,7 @@ int GetAccessFlags(PageAccessibilityConfiguration acce
   }
 }
 
-#if defined(OS_LINUX) && defined(ARCH_CPU_64_BITS)
+#if (defined(OS_BSD) || defined(OS_LINUX)) && defined(ARCH_CPU_64_BITS)
 
 // Multiple guarded memory regions may exceed the process address space limit.
 // This function will raise or lower the limit by |amount|.
@@ -68,7 +68,7 @@ bool AdjustAddressSpaceLimit(int64_t amount) {
 // schemes that reduce that to 4 GiB.
 constexpr size_t kMinimumGuardedMemorySize = 1ULL << 32;  // 4 GiB
 
-#endif  // defined(OS_LINUX) && defined(ARCH_CPU_64_BITS)
+#endif  // (defined(OS_BSD) || defined(OS_LINUX)) && defined(ARCH_CPU_64_BITS)
 
 void* SystemAllocPagesInternal(void* hint,
                                size_t length,
@@ -144,7 +144,7 @@ void SetSystemPagesAccessInternal(
 void FreePagesInternal(void* address, size_t length) {
   CHECK(!munmap(address, length));
 
-#if defined(OS_LINUX) && defined(ARCH_CPU_64_BITS)
+#if (defined(OS_BSD) || defined(OS_LINUX)) && defined(ARCH_CPU_64_BITS)
   // Restore the address space limit.
   if (length >= kMinimumGuardedMemorySize) {
     CHECK(AdjustAddressSpaceLimit(-base::checked_cast<int64_t>(length)));
