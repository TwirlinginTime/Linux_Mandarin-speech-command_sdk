#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/wakeupApi.h"

#define SAMPLERATE (16000)
#define STRIDE_MS (10)
#define FRAMElEN (SAMPLERATE * STRIDE_MS / 1000) //50ms
#define MAXABS16S (32768)

int main(int argc, char *argv[])
{
	const char *keyword_file = "./res/wordlist.dat";               // SET
	const char *audio_pcm_file = "./audio/test.pcm";               // SET
	const char *appid = "cc715ac4d0e68e0fce15152e0069115a";        // SET
	const char *pwd = "123";                                       // SET

	const char *model_bin_file = "./res/model.bin";   // DEFAULT

	FILE *fpInput = NULL;
	void *wakeupObj = NULL;

	int stride_len = FRAMElEN;
	int wakeupStatus;
	int wakeupCount = 0;
	int samplesNum = 0;
	int framenum = 0;

	short inputData16s[FRAMElEN];
	short outData16s[FRAMElEN];
	float inputData32f[FRAMElEN];
	float outputData32f[FRAMElEN];

	printf("Process start! Model file( %s ), audio file ( %s )\n", model_bin_file, audio_pcm_file);
	if ((fpInput = fopen(audio_pcm_file, "rb")) == NULL)
	{
		printf("Error: input audio file could not be opened.\n");
		goto end;
	}

	wakeupObj = wakeupInit(keyword_file, model_bin_file, appid, pwd);
	if (!wakeupObj)
	{
		printf("Error: failed to initialize wakeup object.\n");
		goto end;
	}

	static const float scale = 1.f / (float)(MAXABS16S);

	while ((samplesNum = (short)fread(inputData16s, sizeof(short), stride_len, fpInput)) > 0)
	{

		for (int i = 0; i < stride_len; i++)
		{
			inputData32f[i] = (float)inputData16s[i] * scale;
		}

		wakeupStatus = wakeupProcess(wakeupObj, inputData32f);
		if (wakeupStatus == -1)
		{
			continue;
		}
		else if (wakeupStatus > 0)
		{
			wakeupCount++;
			printf("\nWakeup! Index is %d\n", wakeupStatus);
		}
		framenum++;

		usleep(STRIDE_MS * 1000);
	}
	usleep(1000 * 1000);

end:
	if (NULL != wakeupObj)
	{
		wakeupRelease(wakeupObj);
		wakeupObj = NULL;
	}

	if (!fpInput)
	{
		fclose(fpInput);
		fpInput = NULL;
	}
	printf("\n Wakeup count = %d ! \n", wakeupCount);
	printf("process end!\n");

	return 0;
}
