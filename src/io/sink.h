/*
  Copyright (C) 2012-2014 Paul Brossier <piem@aubio.org>

  This file is part of aubio.

  aubio is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  aubio is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with aubio.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef AUBIO_SINK_H
#define AUBIO_SINK_H

/** \file

  Media sink to write blocks of consecutive audio samples to file.

  To read from file, use ::aubio_source_t.

  Depending on how aubio was compiled, the following sinks will be available.

  When creating a new sink using ::new_aubio_sink, the new function of each of
  the compiled-in sinks will be attempted, in the following order, until one of
  them gets successfully created. If all sinks returned 0, ::new_aubio_sink
  will return 0.

  \b \p sink_apple_audio : ExtAudioFileRef

  This sink uses CoreAudio [Extended Audio File Services]
  (https://developer.apple.com/library/mac/documentation/MusicAudio/Reference/ExtendedAudioFileServicesReference/Reference/reference.html)
  to write 16-bits encoded WAV files.

  \b \p sink_sndfile : libsndfile

  This sink uses [libsndfile](http://www.mega-nerd.com/libsndfile/) to write
  16-bits encoded WAV files.

  \b \p sink_wavwrite : native WAV write

  A simple sink to write 16-bits PCM RIFF encoded WAV files.

  \example io/test-sink.c

*/

#ifdef __cplusplus
extern "C" {
#endif

/** media sink object */
typedef struct _aubio_sink_t aubio_sink_t;

/**

  create new ::aubio_sink_t

  \param uri the file path or uri to write to
  \param samplerate sample rate to write the file at

  \return newly created ::aubio_sink_t

  Creates a new sink object.

  If samplerate is set to 0, the creation of the file will be delayed until
  both ::aubio_sink_preset_samplerate and ::aubio_sink_preset_channels have
  been called.

*/
aubio_sink_t * new_aubio_sink(const char_t * uri, uint_t samplerate);

/**

  preset sink samplerate

  \param s sink, created with ::new_aubio_sink
  \param samplerate samplerate to preset the sink to, in Hz

  \return 0 on success, 1 on error

  Preset the samplerate of the sink. The file should have been created using a
  samplerate of 0.

  The file will be opened only when both samplerate and channels have been set.

*/
uint_t aubio_sink_preset_samplerate(aubio_sink_t *s, uint_t samplerate);

/**

  preset sink channels

  \param s sink, created with ::new_aubio_sink
  \param channels number of channels to preset the sink to

  \return 0 on success, 1 on error

  Preset the samplerate of the sink. The file should have been created using a
  samplerate of 0.

  The file will be opened only when both samplerate and channels have been set.

*/
uint_t aubio_sink_preset_channels(aubio_sink_t *s, uint_t channels);

/**

  get samplerate of sink object

  \param s sink object, created with ::new_aubio_sink
  \return samplerate, in Hz

*/
uint_t aubio_sink_get_samplerate(const aubio_sink_t *s);

/**

  get channels of sink object

  \param s sink object, created with ::new_aubio_sink
  \return number of channels

*/
uint_t aubio_sink_get_channels(const aubio_sink_t *s);

/**

  write monophonic vector of length hop_size to sink

  \param s sink, created with ::new_aubio_sink
  \param write_data ::fvec_t samples to write to sink
  \param write number of frames to write

*/
void aubio_sink_do(aubio_sink_t * s, fvec_t * write_data, uint_t write);

/**

  write polyphonic vector of length hop_size to sink

  \param s sink, created with ::new_aubio_sink
  \param write_data ::fmat_t samples to write to sink
  \param write number of frames to write

*/
void aubio_sink_do_multi(aubio_sink_t * s, fmat_t * write_data, uint_t write);

/**

  close sink

  \param s sink object, created with ::new_aubio_sink

  \return 0 on success, non-zero on failure

*/
uint_t aubio_sink_close(aubio_sink_t * s);

/**

  close sink and cleanup memory

  \param s sink object, created with ::new_aubio_sink

*/
void del_aubio_sink(aubio_sink_t * s);

#ifdef __cplusplus
}
#endif

#endif /* AUBIO_SINK_H */
