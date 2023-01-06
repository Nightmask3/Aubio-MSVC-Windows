/*
  Copyright (C) 2016 Paul Brossier <piem@aubio.org>

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

#include "aubio_priv.h"
#include "fmat.h"

uint_t
aubio_io_validate_samplerate(const char_t *kind, const char_t *path, uint_t samplerate)
{
  if ((sint_t)(samplerate) <= 0) {
    AUBIO_ERR("%s: failed creating %s, samplerate should be positive, not %d\n",
        kind, path, samplerate);
    return AUBIO_FAIL;
  }
  if ((sint_t)samplerate > AUBIO_MAX_SAMPLERATE) {
    AUBIO_ERR("%s: failed creating %s, samplerate %dHz is too large\n",
        kind, path, samplerate);
    return AUBIO_FAIL;
  }
  return AUBIO_OK;
}

uint_t
aubio_io_validate_channels(const char_t *kind, const char_t *path, uint_t channels)
{
  if ((sint_t)(channels) <= 0) {
    AUBIO_ERR("sink_%s: failed creating %s, channels should be positive, not %d\n",
        kind, path, channels);
    return AUBIO_FAIL;
  }
  if (channels > AUBIO_MAX_CHANNELS) {
    AUBIO_ERR("sink_%s: failed creating %s, too many channels (%d but %d available)\n",
        kind, path, channels, AUBIO_MAX_CHANNELS);
    return AUBIO_FAIL;
  }
  return AUBIO_OK;
}


uint_t
aubio_sink_validate_input_length(const char_t *kind, const char_t *path,
    uint_t max_size, uint_t write_data_length, uint_t write)
{
  uint_t can_write = write;

  if (write > max_size) {
    AUBIO_WRN("%s: partial write to %s, trying to write %d frames,"
        " at most %d can be written at once\n", kind, path, write, max_size);
    can_write = max_size;
  }

  if (can_write > write_data_length) {
    AUBIO_WRN("%s: partial write to %s, trying to write %d frames,"
        " but found input of length %d\n", kind, path, write,
        write_data_length);
    can_write = write_data_length;
  }

  return can_write;
}

uint_t
aubio_sink_validate_input_channels(const char_t *kind, const char_t *path,
    uint_t sink_channels, uint_t write_data_height)
{
  uint_t channels = sink_channels;
  if (write_data_height < sink_channels) {
    AUBIO_WRN("%s: partial write to %s, trying to write %d channels,"
        " but found input of height %d\n", kind, path, sink_channels,
        write_data_height);
    channels = write_data_height;
  }
  return channels;
}
