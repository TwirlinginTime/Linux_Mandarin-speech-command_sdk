#ifndef __WAKEUP_API_H__
#define __WAKEUP_API_H__

#ifdef __cplusplus
extern "C"
{
#endif

    void *wakeupInit(const char *keyword_file, const char *model_file, const char *appid, const char *pwd);

    int wakeupProcess(void *obj, const float *input_data);

    void wakeupRelease(void *obj);

#ifdef __cplusplus
};
#endif

#endif // __WAKEUP_API_H__
