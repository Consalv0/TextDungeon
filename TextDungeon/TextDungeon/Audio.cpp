#include "stdafx.h"
#include "Audio.h"

// Play the notes in a song.
void Audio::Play(array<Note>^ tune) {
	System::Collections::IEnumerator^ myEnum = tune->GetEnumerator();
	while (myEnum->MoveNext()) {
		Note n = *safe_cast<Note ^>(myEnum->Current);
		if (n.NoteTone == Tone::REST)
			Thread::Sleep((int)n.NoteDuration);
		else
			Console::Beep((int)n.NoteTone, (int)n.NoteDuration);
	}
}

void Audio::MainTheme() {
	// Declare the first few notes of the song, "Mary Had A Little Lamb".
	array<Note>^ Mary = { Note(Tone::C, Duration::QUARTER),Note(Tone::B, Duration::QUARTER),Note(Tone::GbelowC, Duration::QUARTER),Note(Tone::B, Duration::QUARTER),Note(Tone::C, Duration::QUARTER),Note(Tone::C, Duration::QUARTER),Note(Tone::C, Duration::HALF),Note(Tone::B, Duration::QUARTER),Note(Tone::B, Duration::QUARTER),Note(Tone::B, Duration::HALF),Note(Tone::C, Duration::QUARTER),Note(Tone::E, Duration::QUARTER),Note(Tone::E, Duration::HALF) };

	// Play the song
	Play(Mary);
}