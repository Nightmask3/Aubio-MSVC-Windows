// Aubio.cpp : Defines the functions for the static library.

#define WIN32_LEAN_AND_MEAN
#include "aubio.h"
#include "tempo/tempo.h"
#include "io/source.h"

// TODO: This is an example of a library function
int main()
{
	// open audio file
	aubio_source_t *source = new_aubio_source("track.wav", 0, 512);
	if (!source) {
		// handle error
	}

	// clean up
	del_aubio_source(source);
	return 0;
}
