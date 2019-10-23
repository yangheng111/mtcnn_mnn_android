# MNN_Android

阿里移动框架Android实例，包含了模型转换工具，算法JNI封装流程，Android Demo


## Step 1 MNN模型转换
确保系统安装了adb 
1. 进入converter目录，修改convert_tf.sh脚本,将模型路径修改成自己的模型路径
2. 转换工具是在linux下编译的，可以直接拷贝到服务器上，直接运行./convert_tf.sh
假设这里转换后的模型是mobilenet_v1.mnn
3. 将转换后的模型通过adb push 拷贝到手机相应目录
   adb push XXXX.mnn /sdcard/mnn
注意这里的路径名后续算法模块需要读入，确保模型路径名正确，如/sdcard/mnn/mobilenet_v1.mnn, 算法里面直接写
'mobilenet_v1.mnn'即可，已经默认在/sdcard/mnn目录下
![image](./docs/model_convert.png)

## Step 2 增加自己算法C++处理模块
确保自己系统安装ndk-15
1. 可以参考./mnn_jni/jni/alg 封装自己的算法模块
2. 删除原来./mnn_jni/libs ./mnn_jni/obj目录
3. 修改完成后修改 Android.mk, 在/mnn_jni/jni 目录下执行ndk-build 命令
就可以在/mnn_jni/libs 下发现自己编译出来的so库了 如libMNN.so, libDetectMNN.so
![image](./docs/ndk.png)

## Step3 修改Android 工程 代码
确保安装Android Studio
1. 将/mnn_jni/libs 下编译出来的so库如libMNN.so, libDetectMNN.so 拷贝到
Android 工程的libs目录
2. 编译android 工程，最后在build/output下就可以看到apk
<img src="./docs/android.png" width="400" height="200"/>
