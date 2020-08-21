
# 拓灵离线自定义唤醒词使用文档

## 使用说明

1. 在拓灵开放平台[官网](http://yun.twirlingvr.com/index.php/home/sdkdownload/index.html)下载对应版本的 SDK 工具包，并完成注册和购买(试用)操作，获取自己的`token`和密码，在接口调用时需要用到
2. 在唤醒词定制[网页](http://yun.twirlingvr.com/index.php/home/index/interaction.html)根据提示配置自己的唤醒词，下载对应的资源，并放入目录`bin/res`里
3. 在`samples`文件夹里，简单阅读和修改`awaken_offline_sample.c`:将`keyword_file`修改为自己配置的唤醒词资源，将`audio_pcm_file`修改为自己测试的**16k采样，16 bit量化，单通道，pcm 文件**的具体路径
4. 代码实时处理 PCM，可通过`wakeupProcess`返回值来区分不同唤醒词；从`1:N`表示自定义的`N`个唤醒词中的某一个
5. `samples`的代码运行时需要添加动态库位置，假设生成的可执行程序拷贝到`bin`目录，则`cd bin; export LD_LIBRARY_PATH=../libs:$LD_LIBRARY_PATH; ./awaken_offline_sample`

## 头文件接口说明

1. `void *wakeupInit(const char *keyword_file, const char *model_file, const char *appid, const char *pwd)`
 - `keyword_file[IN]` 自定义的唤醒词文件路径
 - `model_file[IN]` SDK 自带的模型资源，随 SDK 包给到用户
 - `appid[IN]` 拓灵账号注册后的`token`
 - `pwd[IN]` 拓灵账号注册的的密码
 - 返回值: 初始化后下一步处理需要的指针
 - 功能: 初始化操作

2. `int wakeupProcess(void *obj, const float *input_data)`
 - `obj[IN]` wakeupInit 函数返回的指针
 - `input_data[IN]` 输入采样点的指针，默认一次传入 50ms
 - 返回值: 1:N 标志的唤醒词序号 
 - 功能: 判断是否唤醒接口

3. `void wakeupRelease(void *obj)`
 - `obj[IN]` wakeupInit 函数返回的指针
 - 功能: 销毁唤醒指针，释放资源