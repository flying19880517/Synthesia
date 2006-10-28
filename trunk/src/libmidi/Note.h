// Piano Hero
// Copyright (c)2006 Nicholas Piegdon
// See license.txt for license information

#ifndef __MIDI_NOTE_H
#define __MIDI_NOTE_H

#include <set>

// Range of all 128 MIDI notes possible
typedef unsigned int NoteId;

// Arbitrary value outside the usual range
const static NoteId InvalidNoteId = 2048;

template <class T>
struct GenericNote
{
   bool operator()(const GenericNote<T> &lhs, const GenericNote<T> &rhs)
   {
      if (lhs.start < rhs.start) return true;
      if (lhs.start > rhs.start) return false;

      if (lhs.end < rhs.end) return true;
      if (lhs.end > rhs.end) return false;

      if (lhs.note_id < rhs.note_id) return true;
      return false;
   }

   T start;
   T end;
   NoteId note_id;
   size_t track_id;
};

// Note keeps the internal pulses found in the MIDI file which are
// independent of tempo or playback speed.  TranslatedNote contains
// the exact (translated) microsecond that notes start and stop on
// based on a given playback speed, after dereferencing tempo changes.
typedef GenericNote<unsigned long> Note;
typedef GenericNote<unsigned long long> TranslatedNote;

typedef std::set<Note, Note> NoteSet;
typedef std::set<TranslatedNote, TranslatedNote> TranslatedNoteSet;

#endif