#include <alsa/asoundlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LEN 48000
#define DEFAULT_FREQ 600
#define DEFAULT_DURATION 3

int main(int argc, char *argv[]) {
	const static char *device = "default";
	snd_output_t *output = NULL;
	float buffer[BUFFER_LEN];
	int err;
	int k;

	snd_pcm_t *handle;
	snd_pcm_sframes_t frames;

	if ((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
		fprintf(stderr, "AlsaTone: Playback open error: %s\n", snd_strerror(err));
		return EXIT_FAILURE;
	}

	if ((err = snd_pcm_set_params(handle,
			SND_PCM_FORMAT_FLOAT,
			SND_PCM_ACCESS_RW_INTERLEAVED,
			1,
			BUFFER_LEN,
			1,
			500000)) < 0) {	 
		fprintf(stderr, "AlsaTone: Playback open error: %s\n", snd_strerror(err));
		return EXIT_FAILURE;
	}

	// SINE WAVE
	int freq = (argc > 1) ? strtol(argv[1], NULL, 10) : DEFAULT_FREQ;
	if (freq == 0) {
		fprintf(stderr, "AlsaTone: Invalid frequency.\n");
		return EXIT_FAILURE;
	}
	int duration = (argc > 2) ? strtol(argv[2], NULL, 10) : DEFAULT_DURATION;
	if (duration == 0) {
		fprintf(stderr, "AlsaTone: Invalid duration.\n");
		return EXIT_FAILURE;
	}
	printf("Sine tone at %dHz during %d seconds.\n", freq, duration);
	
	for (k=0 ; k<BUFFER_LEN ; k++)
		buffer[k] = sin(2*M_PI * freq / BUFFER_LEN * k); // Creating the sinusoid
	
	for (k=0 ; k < duration ; k++)
		frames = snd_pcm_writei(handle, buffer, BUFFER_LEN); // Sending the sound

	snd_pcm_close(handle);
	return EXIT_SUCCESS;
}
