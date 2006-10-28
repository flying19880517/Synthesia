// Piano Hero
// Copyright (c)2006 Nicholas Piegdon
// See license.txt for license information

#ifndef __SHARED_STATE_H
#define __SHARED_STATE_H

#include <string>
#include <vector>
#include "TrackProperties.h"

class Midi;
class MidiCommOut;

struct SharedState
{
   SharedState(const std::wstring &title)
      : midi(0), midi_out(0), song_title(title)
   { }

   Midi *midi;
   MidiCommOut *midi_out;

   std::vector<TrackProperties> track_properties;
   const std::wstring song_title;
};

#endif