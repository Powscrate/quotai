Run ./gradlew assembleDebug --stacktrace

Welcome to Gradle 9.5.1!

Here are the highlights of this release:
 - Task provenance in reports and failure messages
 - Type-safe accessors for precompiled Kotlin Settings plugins

For more details see https://docs.gradle.org/9.5.1/release-notes.html

Starting a Gradle Daemon (subsequent builds will be faster)
Calculating task graph as no cached configuration is available for tasks: assembleDebug
> Task :app:generateDebugAssets UP-TO-DATE
> Task :app:preBuild UP-TO-DATE
> Task :app:preDebugBuild UP-TO-DATE
> Task :app:mergeDebugNativeDebugMetadata NO-SOURCE
> Task :app:generateDebugResources FROM-CACHE
> Task :app:generateDebugBuildConfig FROM-CACHE
> Task :app:javaPreCompileDebug FROM-CACHE
> Task :app:packageDebugResources FROM-CACHE
> Task :app:processDebugNavigationResources FROM-CACHE
> Task :app:mergeDebugAssets
> Task :app:compressDebugAssets FROM-CACHE
> Task :app:desugarDebugFileDependencies FROM-CACHE
> Task :app:checkDebugDuplicateClasses
> Task :app:checkDebugAarMetadata
> Task :app:mergeLibDexDebug FROM-CACHE
> Task :app:mapDebugSourceSetPaths
> Task :app:compileDebugNavigationResources FROM-CACHE
> Task :app:mergeDebugResources FROM-CACHE
> Task :app:createDebugCompatibleScreenManifests
> Task :app:extractDeepLinksDebug FROM-CACHE
> Task :app:parseDebugLocalResources FROM-CACHE
> Task :app:generateDebugRFile FROM-CACHE
> Task :app:mergeExtDexDebug FROM-CACHE
> Task :app:processDebugMainManifest FROM-CACHE
> Task :app:processDebugManifest FROM-CACHE
> Task :app:processDebugManifestForPackage FROM-CACHE
> Task :app:processDebugResources FROM-CACHE

> Task :app:configureCMakeDebug[arm64-v8a]
Checking the license for package CMake 3.22.1 in /usr/local/lib/android/sdk/licenses
License for package CMake 3.22.1 accepted.
Preparing "Install CMake 3.22.1 v.3.22.1".
"Install CMake 3.22.1 v.3.22.1" ready.
Installing CMake 3.22.1 in /usr/local/lib/android/sdk/cmake/3.22.1
"Install CMake 3.22.1 v.3.22.1" complete.
"Install CMake 3.22.1 v.3.22.1" finished.

> Task :app:kspDebugKotlin
> Task :app:configureCMakeDebug[armeabi-v7a]
> Task :app:configureCMakeDebug[x86]

> Task :app:buildCMakeDebug[x86] FAILED
C/C++: ninja: Entering directory `/home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/x86'
C/C++: /usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ --target=i686-none-linux-android24 --sysroot=/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/sysroot -Dquotai_jni_EXPORTS  -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -D_FORTIFY_SOURCE=2 -Wformat -Werror=format-security   -fno-limit-debug-info  -fPIC -MD -MT CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -MF CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o.d -o CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -c /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp
C/C++: In file included from /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp:10:
C/C++: /home/runner/work/quotai/quotai/app/src/main/cpp/llama.h:5:10: fatal error: 'ggml-cpu.h' file not found
C/C++:     5 | #include "ggml-cpu.h"
C/C++:       |          ^~~~~~~~~~~~
C/C++: 1 error generated.

> Task :app:buildCMakeDebug[armeabi-v7a] FAILED
C/C++: ninja: Entering directory `/home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/armeabi-v7a'
C/C++: /usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ --target=armv7-none-linux-androideabi24 --sysroot=/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/sysroot -Dquotai_jni_EXPORTS  -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -D_FORTIFY_SOURCE=2 -march=armv7-a -mthumb -Wformat -Werror=format-security   -fno-limit-debug-info  -fPIC -MD -MT CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -MF CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o.d -o CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -c /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp
C/C++: In file included from /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp:10:
C/C++: /home/runner/work/quotai/quotai/app/src/main/cpp/llama.h:5:10: fatal error: 'ggml-cpu.h' file not found
C/C++:     5 | #include "ggml-cpu.h"
C/C++:       |          ^~~~~~~~~~~~
C/C++: 1 error generated.

> Task :app:buildCMakeDebug[arm64-v8a] FAILED
C/C++: ninja: Entering directory `/home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/arm64-v8a'
C/C++: /usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ --target=aarch64-none-linux-android24 --sysroot=/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/sysroot -Dquotai_jni_EXPORTS  -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -D_FORTIFY_SOURCE=2 -Wformat -Werror=format-security   -fno-limit-debug-info  -fPIC -MD -MT CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -MF CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o.d -o CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -c /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp
C/C++: In file included from /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp:10:
C/C++: /home/runner/work/quotai/quotai/app/src/main/cpp/llama.h:5:10: fatal error: 'ggml-cpu.h' file not found
C/C++:     5 | #include "ggml-cpu.h"
C/C++:       |          ^~~~~~~~~~~~
C/C++: 1 error generated.

> Task :app:compileDebugKotlin
w: file:///home/runner/work/quotai/quotai/app/src/main/java/com/example/db/QuoteDatabase.kt:23:18 'fun fallbackToDestructiveMigration(): RoomDatabase.Builder<QuoteDatabase>' is deprecated. Replace by overloaded version with parameter to indicate if all tables should be dropped or not.
w: file:///home/runner/work/quotai/quotai/app/src/main/java/com/example/llama/GgufMetadataReader.kt:156:91 'fun String.capitalize(): String' is deprecated. Use replaceFirstChar instead.

FAILURE: Build completed with 3 failures.

1: Task failed with an exception.
-----------
* What went wrong:
Execution failed for task ':app:buildCMakeDebug[x86]' (registered by plugin 'com.android.internal.application').
> com.android.ide.common.process.ProcessException: ninja: Entering directory `/home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/x86'
  [1/2] Building CXX object CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o
  FAILED: CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o 
  /usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ --target=i686-none-linux-android24 --sysroot=/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/sysroot -Dquotai_jni_EXPORTS  -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -D_FORTIFY_SOURCE=2 -Wformat -Werror=format-security   -fno-limit-debug-info  -fPIC -MD -MT CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -MF CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o.d -o CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -c /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp
  In file included from /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp:10:
  /home/runner/work/quotai/quotai/app/src/main/cpp/llama.h:5:10: fatal error: 'ggml-cpu.h' file not found
      5 | #include "ggml-cpu.h"
        |          ^~~~~~~~~~~~
  1 error generated.
  ninja: build stopped: subcommand failed.
  
  C++ build system [build] failed while executing:
      /usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja \
        -C \
        /home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/x86 \
        quotai-jni
    from /home/runner/work/quotai/quotai/app

* Try:
> Run with --info or --debug option to get more log output.
> Run with --scan to get full insights from a Build Scan (powered by Develocity).
> Get more help at https://help.gradle.org.

* Exception is:
org.gradle.api.tasks.TaskExecutionException: Execution failed for task ':app:buildCMakeDebug[x86]' (registered by plugin 'com.android.internal.application').
	at org.gradle.api.internal.tasks.execution.ExecuteActionsTaskExecuter.lambda$executeIfValid$1(ExecuteActionsTaskExecuter.java:135)
	at org.gradle.internal.Try$Failure.ifSuccessfulOrElse(Try.java:288)
	at org.gradle.api.internal.tasks.execution.ExecuteActionsTaskExecuter.executeIfValid(ExecuteActionsTaskExecuter.java:133)
	at org.gradle.api.internal.tasks.execution.ExecuteActionsTaskExecuter.execute(ExecuteActionsTaskExecuter.java:121)
	at org.gradle.api.internal.tasks.execution.ProblemsTaskPathTrackingTaskExecuter.execute(ProblemsTaskPathTrackingTaskExecuter.java:41)
	at org.gradle.api.internal.tasks.execution.ResolveTaskExecutionModeExecuter.execute(ResolveTaskExecutionModeExecuter.java:51)
	at org.gradle.api.internal.tasks.execution.FinalizePropertiesTaskExecuter.execute(FinalizePropertiesTaskExecuter.java:46)
	at org.gradle.api.internal.tasks.execution.SkipTaskWithNoActionsExecuter.execute(SkipTaskWithNoActionsExecuter.java:57)
	at org.gradle.api.internal.tasks.execution.SkipOnlyIfTaskExecuter.execute(SkipOnlyIfTaskExecuter.java:74)
	at org.gradle.api.internal.tasks.execution.CatchExceptionTaskExecuter.execute(CatchExceptionTaskExecuter.java:36)
	at org.gradle.api.internal.tasks.execution.EventFiringTaskExecuter$1.executeTask(EventFiringTaskExecuter.java:77)
	at org.gradle.api.internal.tasks.execution.EventFiringTaskExecuter$1.call(EventFiringTaskExecuter.java:55)
	at org.gradle.api.internal.tasks.execution.EventFiringTaskExecuter$1.call(EventFiringTaskExecuter.java:52)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$CallableBuildOperationWorker.execute(DefaultBuildOperationRunner.java:210)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$CallableBuildOperationWorker.execute(DefaultBuildOperationRunner.java:205)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:67)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:167)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.call(DefaultBuildOperationRunner.java:54)
	at org.gradle.api.internal.tasks.execution.EventFiringTaskExecuter.execute(EventFiringTaskExecuter.java:52)
	at org.gradle.execution.plan.DefaultNodeExecutor.executeLocalTaskNode(DefaultNodeExecutor.java:55)
	at org.gradle.execution.plan.DefaultNodeExecutor.execute(DefaultNodeExecutor.java:34)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$InvokeNodeExecutorsAction.execute(DefaultTaskExecutionGraph.java:355)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$InvokeNodeExecutorsAction.execute(DefaultTaskExecutionGraph.java:343)
31 actionable tasks: 13 executed, 18 from cache
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$BuildOperationAwareExecutionAction.lambda$execute$0(DefaultTaskExecutionGraph.java:339)
	at org.gradle.internal.operations.CurrentBuildOperationRef.with(CurrentBuildOperationRef.java:84)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$BuildOperationAwareExecutionAction.execute(DefaultTaskExecutionGraph.java:339)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$BuildOperationAwareExecutionAction.execute(DefaultTaskExecutionGraph.java:328)
	at org.gradle.execution.plan.DefaultPlanExecutor$ExecutorWorker.execute(DefaultPlanExecutor.java:459)
	at org.gradle.execution.plan.DefaultPlanExecutor$ExecutorWorker.run(DefaultPlanExecutor.java:376)
	at org.gradle.internal.concurrent.ExecutorPolicy$CatchAndRecordFailures.onExecute(ExecutorPolicy.java:64)
	at org.gradle.internal.concurrent.AbstractManagedExecutor$1.run(AbstractManagedExecutor.java:47)
Caused by: org.gradle.internal.UncheckedException: com.android.ide.common.process.ProcessException: ninja: Entering directory `/home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/x86'
[1/2] Building CXX object CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o
FAILED: CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o 
/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ --target=i686-none-linux-android24 --sysroot=/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/sysroot -Dquotai_jni_EXPORTS  -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -D_FORTIFY_SOURCE=2 -Wformat -Werror=format-security   -fno-limit-debug-info  -fPIC -MD -MT CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -MF CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o.d -o CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -c /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp
In file included from /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp:10:
/home/runner/work/quotai/quotai/app/src/main/cpp/llama.h:5:10: fatal error: 'ggml-cpu.h' file not found
    5 | #include "ggml-cpu.h"
      |          ^~~~~~~~~~~~
1 error generated.
ninja: build stopped: subcommand failed.

C++ build system [build] failed while executing:
    /usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja \
Configuration cache entry stored.
      -C \
      /home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/x86 \
      quotai-jni
  from /home/runner/work/quotai/quotai/app
	at org.gradle.internal.UncheckedException.throwAsUncheckedException(UncheckedException.java:69)
	at org.gradle.internal.UncheckedException.throwAsUncheckedException(UncheckedException.java:42)
	at org.gradle.internal.reflect.JavaMethod.invoke(JavaMethod.java:129)
	at org.gradle.api.internal.project.taskfactory.StandardTaskAction.doExecute(StandardTaskAction.java:58)
	at org.gradle.api.internal.project.taskfactory.StandardTaskAction.execute(StandardTaskAction.java:51)
	at org.gradle.api.internal.project.taskfactory.StandardTaskAction.execute(StandardTaskAction.java:29)
	at org.gradle.api.internal.tasks.execution.TaskExecution$3.run(TaskExecution.java:259)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$1.execute(DefaultBuildOperationRunner.java:30)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$1.execute(DefaultBuildOperationRunner.java:27)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:67)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:167)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.run(DefaultBuildOperationRunner.java:48)
	at org.gradle.api.internal.tasks.execution.TaskExecution.executeAction(TaskExecution.java:244)
	at org.gradle.api.internal.tasks.execution.TaskExecution.executeActions(TaskExecution.java:227)
	at org.gradle.api.internal.tasks.execution.TaskExecution.executeWithPreviousOutputFiles(TaskExecution.java:210)
	at org.gradle.api.internal.tasks.execution.TaskExecution.execute(TaskExecution.java:176)
	at org.gradle.internal.execution.steps.ExecuteStep.executeInternal(ExecuteStep.java:167)
	at org.gradle.internal.execution.steps.ExecuteStep.access$000(ExecuteStep.java:47)
	at org.gradle.internal.execution.steps.ExecuteStep$1.call(ExecuteStep.java:137)
	at org.gradle.internal.execution.steps.ExecuteStep$1.call(ExecuteStep.java:134)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$CallableBuildOperationWorker.execute(DefaultBuildOperationRunner.java:210)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$CallableBuildOperationWorker.execute(DefaultBuildOperationRunner.java:205)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:67)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:167)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.call(DefaultBuildOperationRunner.java:54)
	at org.gradle.internal.execution.steps.ExecuteStep.execute(ExecuteStep.java:134)
	at org.gradle.internal.execution.steps.ExecuteStep$Mutable.execute(ExecuteStep.java:80)
	at org.gradle.internal.execution.steps.CancelExecutionStep.execute(CancelExecutionStep.java:42)
	at org.gradle.internal.execution.steps.TimeoutStep.executeWithoutTimeout(TimeoutStep.java:75)
	at org.gradle.internal.execution.steps.TimeoutStep.execute(TimeoutStep.java:55)
	at org.gradle.internal.execution.steps.PreCreateOutputParentsStep.execute(PreCreateOutputParentsStep.java:51)
	at org.gradle.internal.execution.steps.PreCreateOutputParentsStep.execute(PreCreateOutputParentsStep.java:29)
	at org.gradle.internal.execution.steps.RemovePreviousOutputsStep.executeMutable(RemovePreviousOutputsStep.java:67)
	at org.gradle.internal.execution.steps.RemovePreviousOutputsStep.executeMutable(RemovePreviousOutputsStep.java:39)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.BroadcastChangingOutputsStep.execute(BroadcastChangingOutputsStep.java:42)
	at org.gradle.internal.execution.steps.BroadcastChangingOutputsStep.execute(BroadcastChangingOutputsStep.java:24)
	at org.gradle.internal.execution.steps.CaptureOutputsAfterExecutionStep.execute(CaptureOutputsAfterExecutionStep.java:69)
	at org.gradle.internal.execution.steps.CaptureOutputsAfterExecutionStep.execute(CaptureOutputsAfterExecutionStep.java:46)
	at org.gradle.internal.execution.steps.ResolveInputChangesStep.executeMutable(ResolveInputChangesStep.java:39)
	at org.gradle.internal.execution.steps.ResolveInputChangesStep.executeMutable(ResolveInputChangesStep.java:28)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.BuildCacheStep.executeWithoutCache(BuildCacheStep.java:189)
	at org.gradle.internal.execution.steps.BuildCacheStep.lambda$execute$1(BuildCacheStep.java:76)
	at org.gradle.internal.Either$Right.fold(Either.java:176)
	at org.gradle.internal.execution.caching.CachingState.fold(CachingState.java:62)
	at org.gradle.internal.execution.steps.BuildCacheStep.execute(BuildCacheStep.java:74)
	at org.gradle.internal.execution.steps.BuildCacheStep.execute(BuildCacheStep.java:49)
	at org.gradle.internal.execution.steps.StoreExecutionStateStep.executeMutable(StoreExecutionStateStep.java:46)
	at org.gradle.internal.execution.steps.StoreExecutionStateStep.executeMutable(StoreExecutionStateStep.java:35)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.SkipUpToDateStep.executeBecause(SkipUpToDateStep.java:75)
	at org.gradle.internal.execution.steps.SkipUpToDateStep.lambda$execute$2(SkipUpToDateStep.java:53)
	at org.gradle.internal.execution.steps.SkipUpToDateStep.execute(SkipUpToDateStep.java:53)
	at org.gradle.internal.execution.steps.SkipUpToDateStep.execute(SkipUpToDateStep.java:35)
	at org.gradle.internal.execution.steps.legacy.MarkSnapshottingInputsFinishedStep.execute(MarkSnapshottingInputsFinishedStep.java:37)
	at org.gradle.internal.execution.steps.legacy.MarkSnapshottingInputsFinishedStep.execute(MarkSnapshottingInputsFinishedStep.java:27)
	at org.gradle.internal.execution.steps.ResolveMutableCachingStateStep.executeDelegate(ResolveMutableCachingStateStep.java:70)
	at org.gradle.internal.execution.steps.ResolveMutableCachingStateStep.executeDelegate(ResolveMutableCachingStateStep.java:32)
	at org.gradle.internal.execution.steps.AbstractResolveCachingStateStep.execute(AbstractResolveCachingStateStep.java:69)
	at org.gradle.internal.execution.steps.AbstractResolveCachingStateStep.execute(AbstractResolveCachingStateStep.java:37)
	at org.gradle.internal.execution.steps.ResolveChangesStep.executeMutable(ResolveChangesStep.java:63)
	at org.gradle.internal.execution.steps.ResolveChangesStep.executeMutable(ResolveChangesStep.java:34)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.ValidateStep$Mutable.executeDelegate(ValidateStep.java:79)
	at org.gradle.internal.execution.steps.ValidateStep$Mutable.executeDelegate(ValidateStep.java:65)
	at org.gradle.internal.execution.steps.ValidateStep.execute(ValidateStep.java:99)
	at org.gradle.internal.execution.steps.ValidateStep$Mutable.execute(ValidateStep.java:65)
	at org.gradle.internal.execution.steps.CaptureMutableStateBeforeExecutionStep.executeMutable(CaptureMutableStateBeforeExecutionStep.java:86)
	at org.gradle.internal.execution.steps.CaptureMutableStateBeforeExecutionStep.execute(CaptureMutableStateBeforeExecutionStep.java:65)
	at org.gradle.internal.execution.steps.CaptureMutableStateBeforeExecutionStep.execute(CaptureMutableStateBeforeExecutionStep.java:45)
	at org.gradle.internal.execution.steps.SkipEmptyMutableWorkStep.executeWithNonEmptySources(SkipEmptyMutableWorkStep.java:210)
	at org.gradle.internal.execution.steps.SkipEmptyMutableWorkStep.executeMutable(SkipEmptyMutableWorkStep.java:85)
	at org.gradle.internal.execution.steps.SkipEmptyMutableWorkStep.executeMutable(SkipEmptyMutableWorkStep.java:53)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.legacy.MarkSnapshottingInputsStartedStep.execute(MarkSnapshottingInputsStartedStep.java:38)
	at org.gradle.internal.execution.steps.LoadPreviousExecutionStateStep.executeMutable(LoadPreviousExecutionStateStep.java:36)
	at org.gradle.internal.execution.steps.LoadPreviousExecutionStateStep.executeMutable(LoadPreviousExecutionStateStep.java:23)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.HandleStaleOutputsStep.executeMutable(HandleStaleOutputsStep.java:77)
	at org.gradle.internal.execution.steps.HandleStaleOutputsStep.executeMutable(HandleStaleOutputsStep.java:43)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.AssignMutableWorkspaceStep.lambda$executeMutable$0(AssignMutableWorkspaceStep.java:34)
	at org.gradle.api.internal.tasks.execution.TaskExecution$4.withWorkspace(TaskExecution.java:305)
	at org.gradle.internal.execution.steps.AssignMutableWorkspaceStep.executeMutable(AssignMutableWorkspaceStep.java:30)
	at org.gradle.internal.execution.steps.AssignMutableWorkspaceStep.executeMutable(AssignMutableWorkspaceStep.java:21)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.ChoosePipelineStep.execute(ChoosePipelineStep.java:40)
	at org.gradle.internal.execution.steps.ChoosePipelineStep.execute(ChoosePipelineStep.java:23)
	at org.gradle.internal.execution.steps.ExecuteWorkBuildOperationFiringStep.lambda$execute$2(ExecuteWorkBuildOperationFiringStep.java:67)
	at org.gradle.internal.execution.steps.ExecuteWorkBuildOperationFiringStep.execute(ExecuteWorkBuildOperationFiringStep.java:67)
	at org.gradle.internal.execution.steps.ExecuteWorkBuildOperationFiringStep.execute(ExecuteWorkBuildOperationFiringStep.java:39)
	at org.gradle.internal.execution.steps.IdentityCacheStep.execute(IdentityCacheStep.java:46)
	at org.gradle.internal.execution.steps.IdentityCacheStep.execute(IdentityCacheStep.java:34)
	at org.gradle.internal.execution.steps.IdentifyStep.execute(IdentifyStep.java:56)
	at org.gradle.internal.execution.steps.IdentifyStep.execute(IdentifyStep.java:38)
	at org.gradle.internal.execution.impl.DefaultExecutionEngine$1.execute(DefaultExecutionEngine.java:68)
	at org.gradle.api.internal.tasks.execution.ExecuteActionsTaskExecuter.executeIfValid(ExecuteActionsTaskExecuter.java:132)
	... 30 more
Caused by: com.android.ide.common.process.ProcessException: ninja: Entering directory `/home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/x86'
[1/2] Building CXX object CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o
FAILED: CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o 
/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ --target=i686-none-linux-android24 --sysroot=/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/sysroot -Dquotai_jni_EXPORTS  -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -D_FORTIFY_SOURCE=2 -Wformat -Werror=format-security   -fno-limit-debug-info  -fPIC -MD -MT CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -MF CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o.d -o CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -c /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp
In file included from /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp:10:
/home/runner/work/quotai/quotai/app/src/main/cpp/llama.h:5:10: fatal error: 'ggml-cpu.h' file not found
    5 | #include "ggml-cpu.h"
      |          ^~~~~~~~~~~~
1 error generated.
ninja: build stopped: subcommand failed.

C++ build system [build] failed while executing:
    /usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja \
      -C \
      /home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/x86 \
      quotai-jni
  from /home/runner/work/quotai/quotai/app
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt.execute(ExecuteProcess.kt:271)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt$executeProcess$1.invoke(ExecuteProcess.kt:98)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt$executeProcess$1.invoke(ExecuteProcess.kt:96)
	at com.android.build.gradle.internal.cxx.timing.TimingEnvironmentKt.time(TimingEnvironment.kt:28)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt.executeProcess(ExecuteProcess.kt:96)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt.executeProcess$default(ExecuteProcess.kt:73)
	at com.android.build.gradle.internal.cxx.build.CxxRegularBuilder.executeProcessBatch(CxxRegularBuilder.kt:283)
	at com.android.build.gradle.internal.cxx.build.CxxRegularBuilder.build(CxxRegularBuilder.kt:107)
	at com.android.build.gradle.tasks.ExternalNativeBuildTask.doTaskAction(ExternalNativeBuildTask.kt:61)
	at com.android.build.gradle.internal.tasks.UnsafeOutputsTask$taskAction$$inlined$recordTaskAction$1.invoke(BaseTask.kt:71)
	at com.android.build.gradle.internal.tasks.Blocks.recordSpan(Blocks.java:51)
	at com.android.build.gradle.internal.tasks.UnsafeOutputsTask.taskAction(UnsafeOutputsTask.kt:72)
	at org.gradle.internal.reflect.JavaMethod.invoke(JavaMethod.java:125)
	... 129 more
Caused by: com.android.ide.common.process.ProcessException: Error while executing process /usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja with arguments {-C /home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/x86 quotai-jni}
	at com.android.build.gradle.internal.process.GradleProcessResult.buildProcessException(GradleProcessResult.java:73)
	at com.android.build.gradle.internal.process.GradleProcessResult.assertNormalExitValue(GradleProcessResult.java:48)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt.execute(ExecuteProcess.kt:258)
	... 141 more
Caused by: org.gradle.process.ProcessExecutionException: Process 'command '/usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja'' finished with non-zero exit value 1
	at org.gradle.process.internal.DefaultExecHandle$ExecResultImpl.assertNormalExitValue(DefaultExecHandle.java:459)
	at com.android.build.gradle.internal.process.GradleProcessResult.assertNormalExitValue(GradleProcessResult.java:46)
	... 142 more

==============================================================================

2: Task failed with an exception.
-----------
* What went wrong:
Execution failed for task ':app:buildCMakeDebug[armeabi-v7a]' (registered by plugin 'com.android.internal.application').
> com.android.ide.common.process.ProcessException: ninja: Entering directory `/home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/armeabi-v7a'
  [1/2] Building CXX object CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o
  FAILED: CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o 
  /usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ --target=armv7-none-linux-androideabi24 --sysroot=/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/sysroot -Dquotai_jni_EXPORTS  -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -D_FORTIFY_SOURCE=2 -march=armv7-a -mthumb -Wformat -Werror=format-security   -fno-limit-debug-info  -fPIC -MD -MT CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -MF CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o.d -o CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -c /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp
  In file included from /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp:10:
  /home/runner/work/quotai/quotai/app/src/main/cpp/llama.h:5:10: fatal error: 'ggml-cpu.h' file not found
      5 | #include "ggml-cpu.h"
        |          ^~~~~~~~~~~~
  1 error generated.
  ninja: build stopped: subcommand failed.
  
  C++ build system [build] failed while executing:
      /usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja \
        -C \
        /home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/armeabi-v7a \
        quotai-jni
    from /home/runner/work/quotai/quotai/app

* Try:
> Run with --info or --debug option to get more log output.
> Run with --scan to get full insights from a Build Scan (powered by Develocity).
> Get more help at https://help.gradle.org.

* Exception is:
org.gradle.api.tasks.TaskExecutionException: Execution failed for task ':app:buildCMakeDebug[armeabi-v7a]' (registered by plugin 'com.android.internal.application').
	at org.gradle.api.internal.tasks.execution.ExecuteActionsTaskExecuter.lambda$executeIfValid$1(ExecuteActionsTaskExecuter.java:135)
	at org.gradle.internal.Try$Failure.ifSuccessfulOrElse(Try.java:288)
	at org.gradle.api.internal.tasks.execution.ExecuteActionsTaskExecuter.executeIfValid(ExecuteActionsTaskExecuter.java:133)
	at org.gradle.api.internal.tasks.execution.ExecuteActionsTaskExecuter.execute(ExecuteActionsTaskExecuter.java:121)
	at org.gradle.api.internal.tasks.execution.ProblemsTaskPathTrackingTaskExecuter.execute(ProblemsTaskPathTrackingTaskExecuter.java:41)
	at org.gradle.api.internal.tasks.execution.ResolveTaskExecutionModeExecuter.execute(ResolveTaskExecutionModeExecuter.java:51)
	at org.gradle.api.internal.tasks.execution.FinalizePropertiesTaskExecuter.execute(FinalizePropertiesTaskExecuter.java:46)
	at org.gradle.api.internal.tasks.execution.SkipTaskWithNoActionsExecuter.execute(SkipTaskWithNoActionsExecuter.java:57)
	at org.gradle.api.internal.tasks.execution.SkipOnlyIfTaskExecuter.execute(SkipOnlyIfTaskExecuter.java:74)
	at org.gradle.api.internal.tasks.execution.CatchExceptionTaskExecuter.execute(CatchExceptionTaskExecuter.java:36)
	at org.gradle.api.internal.tasks.execution.EventFiringTaskExecuter$1.executeTask(EventFiringTaskExecuter.java:77)
	at org.gradle.api.internal.tasks.execution.EventFiringTaskExecuter$1.call(EventFiringTaskExecuter.java:55)
	at org.gradle.api.internal.tasks.execution.EventFiringTaskExecuter$1.call(EventFiringTaskExecuter.java:52)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$CallableBuildOperationWorker.execute(DefaultBuildOperationRunner.java:210)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$CallableBuildOperationWorker.execute(DefaultBuildOperationRunner.java:205)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:67)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:167)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.call(DefaultBuildOperationRunner.java:54)
	at org.gradle.api.internal.tasks.execution.EventFiringTaskExecuter.execute(EventFiringTaskExecuter.java:52)
	at org.gradle.execution.plan.DefaultNodeExecutor.executeLocalTaskNode(DefaultNodeExecutor.java:55)
	at org.gradle.execution.plan.DefaultNodeExecutor.execute(DefaultNodeExecutor.java:34)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$InvokeNodeExecutorsAction.execute(DefaultTaskExecutionGraph.java:355)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$InvokeNodeExecutorsAction.execute(DefaultTaskExecutionGraph.java:343)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$BuildOperationAwareExecutionAction.lambda$execute$0(DefaultTaskExecutionGraph.java:339)
	at org.gradle.internal.operations.CurrentBuildOperationRef.with(CurrentBuildOperationRef.java:84)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$BuildOperationAwareExecutionAction.execute(DefaultTaskExecutionGraph.java:339)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$BuildOperationAwareExecutionAction.execute(DefaultTaskExecutionGraph.java:328)
	at org.gradle.execution.plan.DefaultPlanExecutor$ExecutorWorker.execute(DefaultPlanExecutor.java:459)
	at org.gradle.execution.plan.DefaultPlanExecutor$ExecutorWorker.run(DefaultPlanExecutor.java:376)
	at org.gradle.internal.concurrent.ExecutorPolicy$CatchAndRecordFailures.onExecute(ExecutorPolicy.java:64)
	at org.gradle.internal.concurrent.AbstractManagedExecutor$1.run(AbstractManagedExecutor.java:47)
	at java.base/java.util.concurrent.ThreadPoolExecutor.runWorker(ThreadPoolExecutor.java:1136)
	at java.base/java.util.concurrent.ThreadPoolExecutor$Worker.run(ThreadPoolExecutor.java:635)
	at java.base/java.lang.Thread.run(Thread.java:840)
Caused by: org.gradle.internal.UncheckedException: com.android.ide.common.process.ProcessException: ninja: Entering directory `/home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/armeabi-v7a'
[1/2] Building CXX object CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o
FAILED: CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o 
/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ --target=armv7-none-linux-androideabi24 --sysroot=/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/sysroot -Dquotai_jni_EXPORTS  -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -D_FORTIFY_SOURCE=2 -march=armv7-a -mthumb -Wformat -Werror=format-security   -fno-limit-debug-info  -fPIC -MD -MT CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -MF CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o.d -o CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -c /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp
In file included from /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp:10:
/home/runner/work/quotai/quotai/app/src/main/cpp/llama.h:5:10: fatal error: 'ggml-cpu.h' file not found
    5 | #include "ggml-cpu.h"
      |          ^~~~~~~~~~~~
1 error generated.
ninja: build stopped: subcommand failed.

C++ build system [build] failed while executing:
    /usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja \
      -C \
      /home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/armeabi-v7a \
      quotai-jni
  from /home/runner/work/quotai/quotai/app
	at org.gradle.internal.UncheckedException.throwAsUncheckedException(UncheckedException.java:69)
	at org.gradle.internal.UncheckedException.throwAsUncheckedException(UncheckedException.java:42)
	at org.gradle.internal.reflect.JavaMethod.invoke(JavaMethod.java:129)
	at org.gradle.api.internal.project.taskfactory.StandardTaskAction.doExecute(StandardTaskAction.java:58)
	at org.gradle.api.internal.project.taskfactory.StandardTaskAction.execute(StandardTaskAction.java:51)
	at org.gradle.api.internal.project.taskfactory.StandardTaskAction.execute(StandardTaskAction.java:29)
	at org.gradle.api.internal.tasks.execution.TaskExecution$3.run(TaskExecution.java:259)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$1.execute(DefaultBuildOperationRunner.java:30)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$1.execute(DefaultBuildOperationRunner.java:27)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:67)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:167)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.run(DefaultBuildOperationRunner.java:48)
	at org.gradle.api.internal.tasks.execution.TaskExecution.executeAction(TaskExecution.java:244)
	at org.gradle.api.internal.tasks.execution.TaskExecution.executeActions(TaskExecution.java:227)
	at org.gradle.api.internal.tasks.execution.TaskExecution.executeWithPreviousOutputFiles(TaskExecution.java:210)
	at org.gradle.api.internal.tasks.execution.TaskExecution.execute(TaskExecution.java:176)
	at org.gradle.internal.execution.steps.ExecuteStep.executeInternal(ExecuteStep.java:167)
	at org.gradle.internal.execution.steps.ExecuteStep.access$000(ExecuteStep.java:47)
	at org.gradle.internal.execution.steps.ExecuteStep$1.call(ExecuteStep.java:137)
	at org.gradle.internal.execution.steps.ExecuteStep$1.call(ExecuteStep.java:134)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$CallableBuildOperationWorker.execute(DefaultBuildOperationRunner.java:210)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$CallableBuildOperationWorker.execute(DefaultBuildOperationRunner.java:205)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:67)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:167)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.call(DefaultBuildOperationRunner.java:54)
	at org.gradle.internal.execution.steps.ExecuteStep.execute(ExecuteStep.java:134)
	at org.gradle.internal.execution.steps.ExecuteStep$Mutable.execute(ExecuteStep.java:80)
	at org.gradle.internal.execution.steps.CancelExecutionStep.execute(CancelExecutionStep.java:42)
	at org.gradle.internal.execution.steps.TimeoutStep.executeWithoutTimeout(TimeoutStep.java:75)
	at org.gradle.internal.execution.steps.TimeoutStep.execute(TimeoutStep.java:55)
	at org.gradle.internal.execution.steps.PreCreateOutputParentsStep.execute(PreCreateOutputParentsStep.java:51)
	at org.gradle.internal.execution.steps.PreCreateOutputParentsStep.execute(PreCreateOutputParentsStep.java:29)
	at org.gradle.internal.execution.steps.RemovePreviousOutputsStep.executeMutable(RemovePreviousOutputsStep.java:67)
	at org.gradle.internal.execution.steps.RemovePreviousOutputsStep.executeMutable(RemovePreviousOutputsStep.java:39)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.BroadcastChangingOutputsStep.execute(BroadcastChangingOutputsStep.java:42)
	at org.gradle.internal.execution.steps.BroadcastChangingOutputsStep.execute(BroadcastChangingOutputsStep.java:24)
	at org.gradle.internal.execution.steps.CaptureOutputsAfterExecutionStep.execute(CaptureOutputsAfterExecutionStep.java:69)
	at org.gradle.internal.execution.steps.CaptureOutputsAfterExecutionStep.execute(CaptureOutputsAfterExecutionStep.java:46)
	at org.gradle.internal.execution.steps.ResolveInputChangesStep.executeMutable(ResolveInputChangesStep.java:39)
	at org.gradle.internal.execution.steps.ResolveInputChangesStep.executeMutable(ResolveInputChangesStep.java:28)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.BuildCacheStep.executeWithoutCache(BuildCacheStep.java:189)
	at org.gradle.internal.execution.steps.BuildCacheStep.lambda$execute$1(BuildCacheStep.java:76)
	at org.gradle.internal.Either$Right.fold(Either.java:176)
	at org.gradle.internal.execution.caching.CachingState.fold(CachingState.java:62)
	at org.gradle.internal.execution.steps.BuildCacheStep.execute(BuildCacheStep.java:74)
	at org.gradle.internal.execution.steps.BuildCacheStep.execute(BuildCacheStep.java:49)
	at org.gradle.internal.execution.steps.StoreExecutionStateStep.executeMutable(StoreExecutionStateStep.java:46)
	at org.gradle.internal.execution.steps.StoreExecutionStateStep.executeMutable(StoreExecutionStateStep.java:35)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.SkipUpToDateStep.executeBecause(SkipUpToDateStep.java:75)
	at org.gradle.internal.execution.steps.SkipUpToDateStep.lambda$execute$2(SkipUpToDateStep.java:53)
	at java.base/java.util.Optional.orElseGet(Optional.java:364)
	at org.gradle.internal.execution.steps.SkipUpToDateStep.execute(SkipUpToDateStep.java:53)
	at org.gradle.internal.execution.steps.SkipUpToDateStep.execute(SkipUpToDateStep.java:35)
	at org.gradle.internal.execution.steps.legacy.MarkSnapshottingInputsFinishedStep.execute(MarkSnapshottingInputsFinishedStep.java:37)
	at org.gradle.internal.execution.steps.legacy.MarkSnapshottingInputsFinishedStep.execute(MarkSnapshottingInputsFinishedStep.java:27)
	at org.gradle.internal.execution.steps.ResolveMutableCachingStateStep.executeDelegate(ResolveMutableCachingStateStep.java:70)
	at org.gradle.internal.execution.steps.ResolveMutableCachingStateStep.executeDelegate(ResolveMutableCachingStateStep.java:32)
	at org.gradle.internal.execution.steps.AbstractResolveCachingStateStep.execute(AbstractResolveCachingStateStep.java:69)
	at org.gradle.internal.execution.steps.AbstractResolveCachingStateStep.execute(AbstractResolveCachingStateStep.java:37)
	at org.gradle.internal.execution.steps.ResolveChangesStep.executeMutable(ResolveChangesStep.java:63)
	at org.gradle.internal.execution.steps.ResolveChangesStep.executeMutable(ResolveChangesStep.java:34)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.ValidateStep$Mutable.executeDelegate(ValidateStep.java:79)
	at org.gradle.internal.execution.steps.ValidateStep$Mutable.executeDelegate(ValidateStep.java:65)
	at org.gradle.internal.execution.steps.ValidateStep.execute(ValidateStep.java:99)
	at org.gradle.internal.execution.steps.ValidateStep$Mutable.execute(ValidateStep.java:65)
	at org.gradle.internal.execution.steps.CaptureMutableStateBeforeExecutionStep.executeMutable(CaptureMutableStateBeforeExecutionStep.java:86)
	at org.gradle.internal.execution.steps.CaptureMutableStateBeforeExecutionStep.execute(CaptureMutableStateBeforeExecutionStep.java:65)
	at org.gradle.internal.execution.steps.CaptureMutableStateBeforeExecutionStep.execute(CaptureMutableStateBeforeExecutionStep.java:45)
	at org.gradle.internal.execution.steps.SkipEmptyMutableWorkStep.executeWithNonEmptySources(SkipEmptyMutableWorkStep.java:210)
	at org.gradle.internal.execution.steps.SkipEmptyMutableWorkStep.executeMutable(SkipEmptyMutableWorkStep.java:85)
	at org.gradle.internal.execution.steps.SkipEmptyMutableWorkStep.executeMutable(SkipEmptyMutableWorkStep.java:53)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.legacy.MarkSnapshottingInputsStartedStep.execute(MarkSnapshottingInputsStartedStep.java:38)
	at org.gradle.internal.execution.steps.LoadPreviousExecutionStateStep.executeMutable(LoadPreviousExecutionStateStep.java:36)
	at org.gradle.internal.execution.steps.LoadPreviousExecutionStateStep.executeMutable(LoadPreviousExecutionStateStep.java:23)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.HandleStaleOutputsStep.executeMutable(HandleStaleOutputsStep.java:77)
	at org.gradle.internal.execution.steps.HandleStaleOutputsStep.executeMutable(HandleStaleOutputsStep.java:43)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.AssignMutableWorkspaceStep.lambda$executeMutable$0(AssignMutableWorkspaceStep.java:34)
	at org.gradle.api.internal.tasks.execution.TaskExecution$4.withWorkspace(TaskExecution.java:305)
	at org.gradle.internal.execution.steps.AssignMutableWorkspaceStep.executeMutable(AssignMutableWorkspaceStep.java:30)
	at org.gradle.internal.execution.steps.AssignMutableWorkspaceStep.executeMutable(AssignMutableWorkspaceStep.java:21)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.ChoosePipelineStep.execute(ChoosePipelineStep.java:40)
	at org.gradle.internal.execution.steps.ChoosePipelineStep.execute(ChoosePipelineStep.java:23)
	at org.gradle.internal.execution.steps.ExecuteWorkBuildOperationFiringStep.lambda$execute$2(ExecuteWorkBuildOperationFiringStep.java:67)
	at java.base/java.util.Optional.orElseGet(Optional.java:364)
	at org.gradle.internal.execution.steps.ExecuteWorkBuildOperationFiringStep.execute(ExecuteWorkBuildOperationFiringStep.java:67)
	at org.gradle.internal.execution.steps.ExecuteWorkBuildOperationFiringStep.execute(ExecuteWorkBuildOperationFiringStep.java:39)
	at org.gradle.internal.execution.steps.IdentityCacheStep.execute(IdentityCacheStep.java:46)
	at org.gradle.internal.execution.steps.IdentityCacheStep.execute(IdentityCacheStep.java:34)
	at org.gradle.internal.execution.steps.IdentifyStep.execute(IdentifyStep.java:56)
	at org.gradle.internal.execution.steps.IdentifyStep.execute(IdentifyStep.java:38)
	at org.gradle.internal.execution.impl.DefaultExecutionEngine$1.execute(DefaultExecutionEngine.java:68)
	at org.gradle.api.internal.tasks.execution.ExecuteActionsTaskExecuter.executeIfValid(ExecuteActionsTaskExecuter.java:132)
	... 33 more
Caused by: com.android.ide.common.process.ProcessException: ninja: Entering directory `/home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/armeabi-v7a'
[1/2] Building CXX object CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o
FAILED: CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o 
/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ --target=armv7-none-linux-androideabi24 --sysroot=/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/sysroot -Dquotai_jni_EXPORTS  -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -D_FORTIFY_SOURCE=2 -march=armv7-a -mthumb -Wformat -Werror=format-security   -fno-limit-debug-info  -fPIC -MD -MT CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -MF CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o.d -o CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -c /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp
In file included from /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp:10:
/home/runner/work/quotai/quotai/app/src/main/cpp/llama.h:5:10: fatal error: 'ggml-cpu.h' file not found
    5 | #include "ggml-cpu.h"
      |          ^~~~~~~~~~~~
1 error generated.
ninja: build stopped: subcommand failed.

C++ build system [build] failed while executing:
    /usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja \
      -C \
      /home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/armeabi-v7a \
      quotai-jni
  from /home/runner/work/quotai/quotai/app
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt.execute(ExecuteProcess.kt:271)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt$executeProcess$1.invoke(ExecuteProcess.kt:98)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt$executeProcess$1.invoke(ExecuteProcess.kt:96)
	at com.android.build.gradle.internal.cxx.timing.TimingEnvironmentKt.time(TimingEnvironment.kt:28)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt.executeProcess(ExecuteProcess.kt:96)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt.executeProcess$default(ExecuteProcess.kt:73)
	at com.android.build.gradle.internal.cxx.build.CxxRegularBuilder.executeProcessBatch(CxxRegularBuilder.kt:283)
	at com.android.build.gradle.internal.cxx.build.CxxRegularBuilder.build(CxxRegularBuilder.kt:107)
	at com.android.build.gradle.tasks.ExternalNativeBuildTask.doTaskAction(ExternalNativeBuildTask.kt:61)
	at com.android.build.gradle.internal.tasks.UnsafeOutputsTask$taskAction$$inlined$recordTaskAction$1.invoke(BaseTask.kt:71)
	at com.android.build.gradle.internal.tasks.Blocks.recordSpan(Blocks.java:51)
	at com.android.build.gradle.internal.tasks.UnsafeOutputsTask.taskAction(UnsafeOutputsTask.kt:72)
	at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
	at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:77)
	at java.base/jdk.internal.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:43)
	at java.base/java.lang.reflect.Method.invoke(Method.java:569)
	at org.gradle.internal.reflect.JavaMethod.invoke(JavaMethod.java:125)
	... 134 more
Caused by: com.android.ide.common.process.ProcessException: Error while executing process /usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja with arguments {-C /home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/armeabi-v7a quotai-jni}
	at com.android.build.gradle.internal.process.GradleProcessResult.buildProcessException(GradleProcessResult.java:73)
	at com.android.build.gradle.internal.process.GradleProcessResult.assertNormalExitValue(GradleProcessResult.java:48)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt.execute(ExecuteProcess.kt:258)
	... 150 more
Caused by: org.gradle.process.ProcessExecutionException: Process 'command '/usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja'' finished with non-zero exit value 1
	at org.gradle.process.internal.DefaultExecHandle$ExecResultImpl.assertNormalExitValue(DefaultExecHandle.java:459)
	at com.android.build.gradle.internal.process.GradleProcessResult.assertNormalExitValue(GradleProcessResult.java:46)
	... 151 more

==============================================================================

3: Task failed with an exception.
-----------
* What went wrong:
Execution failed for task ':app:buildCMakeDebug[arm64-v8a]' (registered by plugin 'com.android.internal.application').
> com.android.ide.common.process.ProcessException: ninja: Entering directory `/home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/arm64-v8a'
  [1/2] Building CXX object CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o
  FAILED: CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o 
  /usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ --target=aarch64-none-linux-android24 --sysroot=/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/sysroot -Dquotai_jni_EXPORTS  -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -D_FORTIFY_SOURCE=2 -Wformat -Werror=format-security   -fno-limit-debug-info  -fPIC -MD -MT CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -MF CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o.d -o CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -c /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp
  In file included from /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp:10:
  /home/runner/work/quotai/quotai/app/src/main/cpp/llama.h:5:10: fatal error: 'ggml-cpu.h' file not found
      5 | #include "ggml-cpu.h"
        |          ^~~~~~~~~~~~
  1 error generated.
  ninja: build stopped: subcommand failed.
  
  C++ build system [build] failed while executing:
      /usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja \
        -C \
        /home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/arm64-v8a \
        quotai-jni
    from /home/runner/work/quotai/quotai/app

* Try:
> Run with --info or --debug option to get more log output.
> Run with --scan to get full insights from a Build Scan (powered by Develocity).
> Get more help at https://help.gradle.org.

* Exception is:
org.gradle.api.tasks.TaskExecutionException: Execution failed for task ':app:buildCMakeDebug[arm64-v8a]' (registered by plugin 'com.android.internal.application').
	at org.gradle.api.internal.tasks.execution.ExecuteActionsTaskExecuter.lambda$executeIfValid$1(ExecuteActionsTaskExecuter.java:135)
	at org.gradle.internal.Try$Failure.ifSuccessfulOrElse(Try.java:288)
	at org.gradle.api.internal.tasks.execution.ExecuteActionsTaskExecuter.executeIfValid(ExecuteActionsTaskExecuter.java:133)
	at org.gradle.api.internal.tasks.execution.ExecuteActionsTaskExecuter.execute(ExecuteActionsTaskExecuter.java:121)
	at org.gradle.api.internal.tasks.execution.ProblemsTaskPathTrackingTaskExecuter.execute(ProblemsTaskPathTrackingTaskExecuter.java:41)
	at org.gradle.api.internal.tasks.execution.ResolveTaskExecutionModeExecuter.execute(ResolveTaskExecutionModeExecuter.java:51)
	at org.gradle.api.internal.tasks.execution.FinalizePropertiesTaskExecuter.execute(FinalizePropertiesTaskExecuter.java:46)
	at org.gradle.api.internal.tasks.execution.SkipTaskWithNoActionsExecuter.execute(SkipTaskWithNoActionsExecuter.java:57)
	at org.gradle.api.internal.tasks.execution.SkipOnlyIfTaskExecuter.execute(SkipOnlyIfTaskExecuter.java:74)
	at org.gradle.api.internal.tasks.execution.CatchExceptionTaskExecuter.execute(CatchExceptionTaskExecuter.java:36)
	at org.gradle.api.internal.tasks.execution.EventFiringTaskExecuter$1.executeTask(EventFiringTaskExecuter.java:77)
	at org.gradle.api.internal.tasks.execution.EventFiringTaskExecuter$1.call(EventFiringTaskExecuter.java:55)
	at org.gradle.api.internal.tasks.execution.EventFiringTaskExecuter$1.call(EventFiringTaskExecuter.java:52)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$CallableBuildOperationWorker.execute(DefaultBuildOperationRunner.java:210)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$CallableBuildOperationWorker.execute(DefaultBuildOperationRunner.java:205)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:67)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:167)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.call(DefaultBuildOperationRunner.java:54)
	at org.gradle.api.internal.tasks.execution.EventFiringTaskExecuter.execute(EventFiringTaskExecuter.java:52)
	at org.gradle.execution.plan.DefaultNodeExecutor.executeLocalTaskNode(DefaultNodeExecutor.java:55)
	at org.gradle.execution.plan.DefaultNodeExecutor.execute(DefaultNodeExecutor.java:34)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$InvokeNodeExecutorsAction.execute(DefaultTaskExecutionGraph.java:355)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$InvokeNodeExecutorsAction.execute(DefaultTaskExecutionGraph.java:343)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$BuildOperationAwareExecutionAction.lambda$execute$0(DefaultTaskExecutionGraph.java:339)
	at org.gradle.internal.operations.CurrentBuildOperationRef.with(CurrentBuildOperationRef.java:84)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$BuildOperationAwareExecutionAction.execute(DefaultTaskExecutionGraph.java:339)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph$BuildOperationAwareExecutionAction.execute(DefaultTaskExecutionGraph.java:328)
	at org.gradle.execution.plan.DefaultPlanExecutor$ExecutorWorker.execute(DefaultPlanExecutor.java:459)
	at org.gradle.execution.plan.DefaultPlanExecutor$ExecutorWorker.run(DefaultPlanExecutor.java:376)
	at org.gradle.execution.plan.DefaultPlanExecutor.process(DefaultPlanExecutor.java:111)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph.executeWithServices(DefaultTaskExecutionGraph.java:146)
	at org.gradle.execution.taskgraph.DefaultTaskExecutionGraph.execute(DefaultTaskExecutionGraph.java:131)
	at org.gradle.execution.SelectedTaskExecutionAction.execute(SelectedTaskExecutionAction.java:35)
	at org.gradle.execution.BuildOperationFiringBuildWorkerExecutor$ExecuteTasks.call(BuildOperationFiringBuildWorkerExecutor.java:54)
	at org.gradle.execution.BuildOperationFiringBuildWorkerExecutor$ExecuteTasks.call(BuildOperationFiringBuildWorkerExecutor.java:43)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$CallableBuildOperationWorker.execute(DefaultBuildOperationRunner.java:210)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$CallableBuildOperationWorker.execute(DefaultBuildOperationRunner.java:205)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:67)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:167)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.call(DefaultBuildOperationRunner.java:54)
	at org.gradle.execution.BuildOperationFiringBuildWorkerExecutor.execute(BuildOperationFiringBuildWorkerExecutor.java:40)
	at org.gradle.internal.build.DefaultBuildLifecycleController.lambda$executeTasks$11(DefaultBuildLifecycleController.java:323)
	at org.gradle.internal.model.StateTransitionController.doTransition(StateTransitionController.java:304)
	at org.gradle.internal.model.StateTransitionController.lambda$tryTransition$9(StateTransitionController.java:215)
	at org.gradle.internal.work.DefaultSynchronizer.withLock(DefaultSynchronizer.java:45)
	at org.gradle.internal.model.StateTransitionController.tryTransition(StateTransitionController.java:215)
	at org.gradle.internal.build.DefaultBuildLifecycleController.executeTasks(DefaultBuildLifecycleController.java:314)
	at org.gradle.internal.build.DefaultBuildWorkGraphController$DefaultBuildWorkGraph.runWork(DefaultBuildWorkGraphController.java:220)
	at org.gradle.internal.work.DefaultWorkerLeaseService.lambda$runAndReleaseLocks$0(DefaultWorkerLeaseService.java:300)
	at org.gradle.internal.work.ResourceLockStatistics$1.measure(ResourceLockStatistics.java:43)
	at org.gradle.internal.work.DefaultWorkerLeaseService.runAndReleaseLocks(DefaultWorkerLeaseService.java:298)
	at org.gradle.internal.work.DefaultWorkerLeaseService.withLocksAcquired(DefaultWorkerLeaseService.java:294)
	at org.gradle.internal.work.DefaultWorkerLeaseService.withLocks(DefaultWorkerLeaseService.java:286)
	at org.gradle.internal.work.DefaultWorkerLeaseService.runAsWorkerThread(DefaultWorkerLeaseService.java:130)
	at org.gradle.composite.internal.DefaultBuildController.doRun(DefaultBuildController.java:182)
	at org.gradle.composite.internal.DefaultBuildController$BuildOpRunnable.lambda$run$0(DefaultBuildController.java:199)
	at org.gradle.internal.operations.CurrentBuildOperationRef.with(CurrentBuildOperationRef.java:84)
	at org.gradle.composite.internal.DefaultBuildController$BuildOpRunnable.run(DefaultBuildController.java:199)
	at java.base/java.util.concurrent.Executors$RunnableAdapter.call(Executors.java:539)
	at java.base/java.util.concurrent.FutureTask.run(FutureTask.java:264)
	at org.gradle.internal.concurrent.ExecutorPolicy$CatchAndRecordFailures.onExecute(ExecutorPolicy.java:64)
	at org.gradle.internal.concurrent.AbstractManagedExecutor$1.run(AbstractManagedExecutor.java:47)
	at java.base/java.util.concurrent.ThreadPoolExecutor.runWorker(ThreadPoolExecutor.java:1136)
	at java.base/java.util.concurrent.ThreadPoolExecutor$Worker.run(ThreadPoolExecutor.java:635)
	at java.base/java.lang.Thread.run(Thread.java:840)
Caused by: org.gradle.internal.UncheckedException: com.android.ide.common.process.ProcessException: ninja: Entering directory `/home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/arm64-v8a'
[1/2] Building CXX object CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o
FAILED: CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o 
/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ --target=aarch64-none-linux-android24 --sysroot=/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/sysroot -Dquotai_jni_EXPORTS  -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -D_FORTIFY_SOURCE=2 -Wformat -Werror=format-security   -fno-limit-debug-info  -fPIC -MD -MT CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -MF CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o.d -o CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -c /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp
In file included from /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp:10:
/home/runner/work/quotai/quotai/app/src/main/cpp/llama.h:5:10: fatal error: 'ggml-cpu.h' file not found
    5 | #include "ggml-cpu.h"
      |          ^~~~~~~~~~~~
1 error generated.
ninja: build stopped: subcommand failed.

C++ build system [build] failed while executing:
    /usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja \
      -C \
      /home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/arm64-v8a \
      quotai-jni
  from /home/runner/work/quotai/quotai/app
	at org.gradle.internal.UncheckedException.throwAsUncheckedException(UncheckedException.java:69)
	at org.gradle.internal.UncheckedException.throwAsUncheckedException(UncheckedException.java:42)
	at org.gradle.internal.reflect.JavaMethod.invoke(JavaMethod.java:129)
	at org.gradle.api.internal.project.taskfactory.StandardTaskAction.doExecute(StandardTaskAction.java:58)
	at org.gradle.api.internal.project.taskfactory.StandardTaskAction.execute(StandardTaskAction.java:51)
	at org.gradle.api.internal.project.taskfactory.StandardTaskAction.execute(StandardTaskAction.java:29)
	at org.gradle.api.internal.tasks.execution.TaskExecution$3.run(TaskExecution.java:259)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$1.execute(DefaultBuildOperationRunner.java:30)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$1.execute(DefaultBuildOperationRunner.java:27)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:67)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:167)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.run(DefaultBuildOperationRunner.java:48)
	at org.gradle.api.internal.tasks.execution.TaskExecution.executeAction(TaskExecution.java:244)
	at org.gradle.api.internal.tasks.execution.TaskExecution.executeActions(TaskExecution.java:227)
	at org.gradle.api.internal.tasks.execution.TaskExecution.executeWithPreviousOutputFiles(TaskExecution.java:210)
	at org.gradle.api.internal.tasks.execution.TaskExecution.execute(TaskExecution.java:176)
	at org.gradle.internal.execution.steps.ExecuteStep.executeInternal(ExecuteStep.java:167)
	at org.gradle.internal.execution.steps.ExecuteStep.access$000(ExecuteStep.java:47)
	at org.gradle.internal.execution.steps.ExecuteStep$1.call(ExecuteStep.java:137)
	at org.gradle.internal.execution.steps.ExecuteStep$1.call(ExecuteStep.java:134)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$CallableBuildOperationWorker.execute(DefaultBuildOperationRunner.java:210)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$CallableBuildOperationWorker.execute(DefaultBuildOperationRunner.java:205)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:67)
	at org.gradle.internal.operations.DefaultBuildOperationRunner$2.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:167)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.execute(DefaultBuildOperationRunner.java:60)
	at org.gradle.internal.operations.DefaultBuildOperationRunner.call(DefaultBuildOperationRunner.java:54)
	at org.gradle.internal.execution.steps.ExecuteStep.execute(ExecuteStep.java:134)
	at org.gradle.internal.execution.steps.ExecuteStep$Mutable.execute(ExecuteStep.java:80)
	at org.gradle.internal.execution.steps.CancelExecutionStep.execute(CancelExecutionStep.java:42)
	at org.gradle.internal.execution.steps.TimeoutStep.executeWithoutTimeout(TimeoutStep.java:75)
	at org.gradle.internal.execution.steps.TimeoutStep.execute(TimeoutStep.java:55)
	at org.gradle.internal.execution.steps.PreCreateOutputParentsStep.execute(PreCreateOutputParentsStep.java:51)
	at org.gradle.internal.execution.steps.PreCreateOutputParentsStep.execute(PreCreateOutputParentsStep.java:29)
	at org.gradle.internal.execution.steps.RemovePreviousOutputsStep.executeMutable(RemovePreviousOutputsStep.java:67)
	at org.gradle.internal.execution.steps.RemovePreviousOutputsStep.executeMutable(RemovePreviousOutputsStep.java:39)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.BroadcastChangingOutputsStep.execute(BroadcastChangingOutputsStep.java:42)
	at org.gradle.internal.execution.steps.BroadcastChangingOutputsStep.execute(BroadcastChangingOutputsStep.java:24)
	at org.gradle.internal.execution.steps.CaptureOutputsAfterExecutionStep.execute(CaptureOutputsAfterExecutionStep.java:69)
	at org.gradle.internal.execution.steps.CaptureOutputsAfterExecutionStep.execute(CaptureOutputsAfterExecutionStep.java:46)
	at org.gradle.internal.execution.steps.ResolveInputChangesStep.executeMutable(ResolveInputChangesStep.java:39)
	at org.gradle.internal.execution.steps.ResolveInputChangesStep.executeMutable(ResolveInputChangesStep.java:28)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.BuildCacheStep.executeWithoutCache(BuildCacheStep.java:189)
	at org.gradle.internal.execution.steps.BuildCacheStep.lambda$execute$1(BuildCacheStep.java:76)
	at org.gradle.internal.Either$Right.fold(Either.java:176)
	at org.gradle.internal.execution.caching.CachingState.fold(CachingState.java:62)
	at org.gradle.internal.execution.steps.BuildCacheStep.execute(BuildCacheStep.java:74)
	at org.gradle.internal.execution.steps.BuildCacheStep.execute(BuildCacheStep.java:49)
	at org.gradle.internal.execution.steps.StoreExecutionStateStep.executeMutable(StoreExecutionStateStep.java:46)
	at org.gradle.internal.execution.steps.StoreExecutionStateStep.executeMutable(StoreExecutionStateStep.java:35)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.SkipUpToDateStep.executeBecause(SkipUpToDateStep.java:75)
	at org.gradle.internal.execution.steps.SkipUpToDateStep.lambda$execute$2(SkipUpToDateStep.java:53)
	at java.base/java.util.Optional.orElseGet(Optional.java:364)
	at org.gradle.internal.execution.steps.SkipUpToDateStep.execute(SkipUpToDateStep.java:53)
	at org.gradle.internal.execution.steps.SkipUpToDateStep.execute(SkipUpToDateStep.java:35)
	at org.gradle.internal.execution.steps.legacy.MarkSnapshottingInputsFinishedStep.execute(MarkSnapshottingInputsFinishedStep.java:37)
	at org.gradle.internal.execution.steps.legacy.MarkSnapshottingInputsFinishedStep.execute(MarkSnapshottingInputsFinishedStep.java:27)
	at org.gradle.internal.execution.steps.ResolveMutableCachingStateStep.executeDelegate(ResolveMutableCachingStateStep.java:70)
	at org.gradle.internal.execution.steps.ResolveMutableCachingStateStep.executeDelegate(ResolveMutableCachingStateStep.java:32)
	at org.gradle.internal.execution.steps.AbstractResolveCachingStateStep.execute(AbstractResolveCachingStateStep.java:69)
	at org.gradle.internal.execution.steps.AbstractResolveCachingStateStep.execute(AbstractResolveCachingStateStep.java:37)
	at org.gradle.internal.execution.steps.ResolveChangesStep.executeMutable(ResolveChangesStep.java:63)
	at org.gradle.internal.execution.steps.ResolveChangesStep.executeMutable(ResolveChangesStep.java:34)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.ValidateStep$Mutable.executeDelegate(ValidateStep.java:79)
	at org.gradle.internal.execution.steps.ValidateStep$Mutable.executeDelegate(ValidateStep.java:65)
	at org.gradle.internal.execution.steps.ValidateStep.execute(ValidateStep.java:99)
	at org.gradle.internal.execution.steps.ValidateStep$Mutable.execute(ValidateStep.java:65)
	at org.gradle.internal.execution.steps.CaptureMutableStateBeforeExecutionStep.executeMutable(CaptureMutableStateBeforeExecutionStep.java:86)
	at org.gradle.internal.execution.steps.CaptureMutableStateBeforeExecutionStep.execute(CaptureMutableStateBeforeExecutionStep.java:65)
	at org.gradle.internal.execution.steps.CaptureMutableStateBeforeExecutionStep.execute(CaptureMutableStateBeforeExecutionStep.java:45)
	at org.gradle.internal.execution.steps.SkipEmptyMutableWorkStep.executeWithNonEmptySources(SkipEmptyMutableWorkStep.java:210)
	at org.gradle.internal.execution.steps.SkipEmptyMutableWorkStep.executeMutable(SkipEmptyMutableWorkStep.java:85)
	at org.gradle.internal.execution.steps.SkipEmptyMutableWorkStep.executeMutable(SkipEmptyMutableWorkStep.java:53)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.legacy.MarkSnapshottingInputsStartedStep.execute(MarkSnapshottingInputsStartedStep.java:38)
	at org.gradle.internal.execution.steps.LoadPreviousExecutionStateStep.executeMutable(LoadPreviousExecutionStateStep.java:36)
	at org.gradle.internal.execution.steps.LoadPreviousExecutionStateStep.executeMutable(LoadPreviousExecutionStateStep.java:23)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.HandleStaleOutputsStep.executeMutable(HandleStaleOutputsStep.java:77)
	at org.gradle.internal.execution.steps.HandleStaleOutputsStep.executeMutable(HandleStaleOutputsStep.java:43)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.AssignMutableWorkspaceStep.lambda$executeMutable$0(AssignMutableWorkspaceStep.java:34)
	at org.gradle.api.internal.tasks.execution.TaskExecution$4.withWorkspace(TaskExecution.java:305)
	at org.gradle.internal.execution.steps.AssignMutableWorkspaceStep.executeMutable(AssignMutableWorkspaceStep.java:30)
	at org.gradle.internal.execution.steps.AssignMutableWorkspaceStep.executeMutable(AssignMutableWorkspaceStep.java:21)
	at org.gradle.internal.execution.steps.MutableStep.execute(MutableStep.java:26)
	at org.gradle.internal.execution.steps.ChoosePipelineStep.execute(ChoosePipelineStep.java:40)
	at org.gradle.internal.execution.steps.ChoosePipelineStep.execute(ChoosePipelineStep.java:23)
	at org.gradle.internal.execution.steps.ExecuteWorkBuildOperationFiringStep.lambda$execute$2(ExecuteWorkBuildOperationFiringStep.java:67)
	at java.base/java.util.Optional.orElseGet(Optional.java:364)
	at org.gradle.internal.execution.steps.ExecuteWorkBuildOperationFiringStep.execute(ExecuteWorkBuildOperationFiringStep.java:67)
	at org.gradle.internal.execution.steps.ExecuteWorkBuildOperationFiringStep.execute(ExecuteWorkBuildOperationFiringStep.java:39)
	at org.gradle.internal.execution.steps.IdentityCacheStep.execute(IdentityCacheStep.java:46)
	at org.gradle.internal.execution.steps.IdentityCacheStep.execute(IdentityCacheStep.java:34)
	at org.gradle.internal.execution.steps.IdentifyStep.execute(IdentifyStep.java:56)
	at org.gradle.internal.execution.steps.IdentifyStep.execute(IdentifyStep.java:38)
	at org.gradle.internal.execution.impl.DefaultExecutionEngine$1.execute(DefaultExecutionEngine.java:68)
	at org.gradle.api.internal.tasks.execution.ExecuteActionsTaskExecuter.executeIfValid(ExecuteActionsTaskExecuter.java:132)
	... 66 more
Caused by: com.android.ide.common.process.ProcessException: ninja: Entering directory `/home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/arm64-v8a'
[1/2] Building CXX object CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o
FAILED: CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o 
/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ --target=aarch64-none-linux-android24 --sysroot=/usr/local/lib/android/sdk/ndk/28.2.13676358/toolchains/llvm/prebuilt/linux-x86_64/sysroot -Dquotai_jni_EXPORTS  -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -D_FORTIFY_SOURCE=2 -Wformat -Werror=format-security   -fno-limit-debug-info  -fPIC -MD -MT CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -MF CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o.d -o CMakeFiles/quotai-jni.dir/src/main/cpp/quotai-jni.cpp.o -c /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp
In file included from /home/runner/work/quotai/quotai/app/src/main/cpp/quotai-jni.cpp:10:
/home/runner/work/quotai/quotai/app/src/main/cpp/llama.h:5:10: fatal error: 'ggml-cpu.h' file not found
    5 | #include "ggml-cpu.h"
      |          ^~~~~~~~~~~~
1 error generated.
ninja: build stopped: subcommand failed.

C++ build system [build] failed while executing:
    /usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja \
      -C \
      /home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/arm64-v8a \
      quotai-jni
  from /home/runner/work/quotai/quotai/app
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt.execute(ExecuteProcess.kt:271)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt$executeProcess$1.invoke(ExecuteProcess.kt:98)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt$executeProcess$1.invoke(ExecuteProcess.kt:96)
	at com.android.build.gradle.internal.cxx.timing.TimingEnvironmentKt.time(TimingEnvironment.kt:28)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt.executeProcess(ExecuteProcess.kt:96)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt.executeProcess$default(ExecuteProcess.kt:73)
	at com.android.build.gradle.internal.cxx.build.CxxRegularBuilder.executeProcessBatch(CxxRegularBuilder.kt:283)
	at com.android.build.gradle.internal.cxx.build.CxxRegularBuilder.build(CxxRegularBuilder.kt:107)
	at com.android.build.gradle.tasks.ExternalNativeBuildTask.doTaskAction(ExternalNativeBuildTask.kt:61)
	at com.android.build.gradle.internal.tasks.UnsafeOutputsTask$taskAction$$inlined$recordTaskAction$1.invoke(BaseTask.kt:71)
	at com.android.build.gradle.internal.tasks.Blocks.recordSpan(Blocks.java:51)
	at com.android.build.gradle.internal.tasks.UnsafeOutputsTask.taskAction(UnsafeOutputsTask.kt:72)
	at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
	at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:77)
	at java.base/jdk.internal.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:43)
	at java.base/java.lang.reflect.Method.invoke(Method.java:569)
	at org.gradle.internal.reflect.JavaMethod.invoke(JavaMethod.java:125)
	... 167 more
Caused by: com.android.ide.common.process.ProcessException: Error while executing process /usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja with arguments {-C /home/runner/work/quotai/quotai/app/.cxx/Debug/3q401p2g/arm64-v8a quotai-jni}
	at com.android.build.gradle.internal.process.GradleProcessResult.buildProcessException(GradleProcessResult.java:73)
	at com.android.build.gradle.internal.process.GradleProcessResult.assertNormalExitValue(GradleProcessResult.java:48)
	at com.android.build.gradle.internal.cxx.process.ExecuteProcessKt.execute(ExecuteProcess.kt:258)
	... 183 more
Caused by: org.gradle.process.ProcessExecutionException: Process 'command '/usr/local/lib/android/sdk/cmake/3.22.1/bin/ninja'' finished with non-zero exit value 1
	at org.gradle.process.internal.DefaultExecHandle$ExecResultImpl.assertNormalExitValue(DefaultExecHandle.java:459)
	at com.android.build.gradle.internal.process.GradleProcessResult.assertNormalExitValue(GradleProcessResult.java:46)
	... 184 more

==============================================================================

BUILD FAILED in 44s
Error: Process completed with exit code 1.