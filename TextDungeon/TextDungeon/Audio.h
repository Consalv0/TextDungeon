#pragma once
ref class Audio {
public:
	enum class Tone {
		REST = 0,
		GbelowC = 196,
		A = 220,
		Asharp = 233,
		B = 247,
		C = 262,
		Csharp = 277,
		D = 294,
		Dsharp = 311,
		E = 330,
		F = 349,
		Fsharp = 370,
		G = 392,
		Gsharp = 415
	};

	enum class Duration {
		WHOLE = 1600,
		HALF = Duration::WHOLE / 2,
		QUARTER = Duration::HALF / 2,
		EIGHTH = Duration::QUARTER / 2,
		SIXTEENTH = Duration::EIGHTH / 2
	};

	value struct Note {
	public:
		Tone toneVal;
		Duration durVal;

		// Define a constructor to create a specific note.
		Note(Tone frequency, Duration time) {
			toneVal = frequency;
			durVal = time;
		}

		property Tone NoteTone {
			// Define properties to return the note's tone and duration.
			Tone get() {
				return toneVal;
			}
		}

		property Duration NoteDuration {
			Duration get() {
				return durVal;
			}
		}
	};

	// Play the notes in a song.
	static void Play(array<Note>^ tune);

	// Here are the sounds.
	static void MainTheme();
};

