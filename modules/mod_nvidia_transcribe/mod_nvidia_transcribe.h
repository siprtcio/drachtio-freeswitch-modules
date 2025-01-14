#ifndef __MOD_NVIDIA_TRANSCRIBE_H__
#define __MOD_NVIDIA_TRANSCRIBE_H__

#include <switch.h>
#include <speex/speex_resampler.h>

#include <unistd.h>

#define MAX_SESSION_ID (256)
#define MAX_BUG_LEN (64)
#define MY_BUG_NAME "nvidia_transcribe"
#define TRANSCRIBE_EVENT_RESULTS "nvidia_transcribe::transcription"
#define TRANSCRIBE_EVENT_START_OF_SPEECH "nvidia_transcribe::start_of_speech"
#define TRANSCRIBE_EVENT_TRANSCRIPTION_COMPLETE "nvidia_transcribe::end_of_transcription"
#define TRANSCRIBE_EVENT_ERROR "nvidia_transcribe::error"
#define TRANSCRIBE_EVENT_VAD_DETECTED "nvidia_transcribe::vad_detected"


/* per-channel data */
typedef void (*responseHandler_t)(switch_core_session_t* session, 
	const char* json, const char* bugname, 
	const char* details);

struct cap_cb {
	switch_mutex_t *mutex;
	char bugname[MAX_BUG_LEN+1];
	char sessionId[MAX_SESSION_ID+1];
	char *base;
  SpeexResamplerState *resampler;
	void* streamer;
	responseHandler_t responseHandler;
	switch_thread_t* thread;
	int end_of_utterance;
	switch_vad_t * vad;
	uint32_t samples_per_second;
};

#endif