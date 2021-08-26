//
// let's make music
//
// Ron D Bentley, Stafford, UK, August 2021
//
// This example and code is in the public domain and
// may be used without restriction and without warranty.
//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// % music/tone data and functions... %
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//
// Tempos, by common musical names
//
#define  grave          40
#define  largo          46
#define  lento          52
#define  adagio         56
#define  larghetto      60
#define  adagietto      66
#define  andante        72
#define  andantino      80
#define  maestroso      88
#define  moderato      100
#define  allegretto    104
#define  animato       120
#define  allegro       132
#define  allegro_assai 144
#define  vivace        160
#define  presto        184
#define  prestissimo   208

//
// Public constants - reflects the 'pitches.h' file,
// but with a different (shortened) note naming convention.
// The values are the frequencies (hz) of the notes.
//
#define B0  31
#define C1  33
#define CS1 35
#define D1  37
#define DS1 39
#define E1  41
#define F1  44
#define FS1 46
#define G1  49
#define GS1 52
#define A1  55
#define AS1 58
#define B1  62
#define C2  65
#define CS2 69
#define D2  73
#define DS2 78
#define E2  82
#define F2  87
#define FS2 93
#define G2  98
#define GS2 104
#define A2  110
#define AS2 117
#define B2  123
#define C3  131
#define CS3 139
#define D3  147
#define DS3 156
#define E3  165
#define F3  175
#define FS3 185
#define G3  196
#define GS3 208
#define A3  220
#define AS3 233
#define B3  247
#define C4  262 // <--------- middle C
#define CS4 277
#define D4  294
#define DS4 311
#define E4  330
#define F4  349
#define FS4 370
#define G4  392
#define GS4 415
#define A4  440
#define AS4 466
#define B4  494
#define C5  523
#define CS5 554
#define D5  587
#define DS5 622
#define E5  659
#define F5  698
#define FS5 740
#define G5  784
#define GS5 831
#define A5  880
#define AS5 932
#define B5  988
#define C6  1047
#define CS6 1109
#define D6  1175
#define DS6 1245
#define E6  1319
#define F6  1397
#define FS6 1480
#define G6  1568
#define GS6 1661
#define A6  1760
#define AS6 1865
#define B6  1976
#define C7  2093
#define CS7 2217
#define D7  2349
#define DS7 2489
#define E7  2637
#define F7  2794
#define FS7 2960
#define G7  3136
#define GS7 3322
#define A7  3520
#define AS7 3729
#define B7  3951
#define C8  4186
#define CS8 4435
#define D8  4699
#define DS8 4978

#define speaker                11     // digital pin number for speaker/buzzer

float default_tempo = float(animato); // default tempo - beats per minute
float current_tempo = default_tempo;
float timings[6];                     // holds timings for each defined note/rest time value
#define trills_per_crotchet     8     // number of note changes in a trill per crotchet
float trill_duration;                 // set depending on the tempo selected

//
// Standard note/rest duration definitions, set in the set_tempo function
//
#define semib     timings[0] // 4 beats
#define dot_minim timings[1] // 3 beats
#define minim     timings[2] // 2 beats
#define crot      timings[3] // 1 beat
#define quav      timings[4] // 1/2 beat
#define semiq     timings[5] // 1/4 beat

//
// Function waits for the given time in seconds, or part thereof.
//
void wait(float duration) {
  uint32_t start;
  start = millis();
  duration = duration * 1000; // convert to milliseconds
  do {
  } while (millis() - start <= duration);
}

//
// Set tempo by adjusting durations of note/rest timings
//
void set_tempo(float new_tempo) {
  float crotchet_duration;
  current_tempo = new_tempo;         // keep current tempo up to date in case it needs to be queried
  crotchet_duration = 60 / new_tempo;// timing in seconds for 1 beat
  semib     = crotchet_duration * 4; // semibrieve, 4 beats
  dot_minim = crotchet_duration * 3; // dotted mimin, 3 beats
  minim     = crotchet_duration * 2; // minim, 2 beats
  crot      = crotchet_duration;     // crotchet, 1 beat
  quav      = crotchet_duration / 2; // quaver, 1/2 beat
  semiq     = crotchet_duration / 4; // semiquaver, 1/4 beat

  // Set the note duration time for one note in a trill depending on the
  // defined number of note changes in a trill per crotchet.
  trill_duration = crot / trills_per_crotchet;
}

//
// Play given note for given duration in seconds, or part thereof.
// Observe that this function is 'blocking', although the tone
// function is 'non-blocking', ie control stays with the function
// until note has completed.
//
void play(int note, float note_duration) {
  tone(speaker, note, note_duration * 1000); // play the given note for the given duration
  wait(note_duration);                       // wait for note to complete
}

//
// Function performs a basic trill with given two notes for the given duration
//
void trill(int note_1, int note_2, float note_duration) {
  note_duration = note_duration * 1000; // convert to milliseconds
  uint32_t start = millis();
  do {
    play(note_1, trill_duration);
    play(note_2, trill_duration);
  } while (millis() - start < note_duration);
}

//
// Rest for given duration in seconds, or part thereof.
//
void rest(float rest_duration) {
  noTone(speaker);      // ensure no tone is currently playing
  wait(rest_duration);  // wait for given rest to complete
}

void setup() {
  // set up speaker
  pinMode(speaker, OUTPUT);
  // set up note/rest timings, based on the default unit beat time (default_tempo)
  set_tempo(default_tempo);
}

void loop() {
  // some music examples...

  middle_C();
  wait(3);

  twinkle_twinkle();
  wait(3);

  jingle_bells();
  wait(3);

  happy_birthday();
  wait(3);

  ditty_1();
  wait(3);

  door_bell_1();
  wait(3);

  door_bell_2();
  wait(3);

  ode_to_joy();
  wait(3);

  canon_in_D();
  wait(3);
  // and back to the beginning...
}

//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %        Example out-of-the-box 'shrink-wrapped' music commands         %
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void middle_C() {
  // 4/4 time
  // C major scale - up
  // bar 1
  play(C3, crot);
  play(D3, crot);
  play(E3, crot);
  play(F3, crot);
  // bar 2
  play(G3, crot);
  play(A3, crot);
  play(B3, crot);
  play(C4, crot);
  // bar 3
  rest(semib);
  // C major scale - down
  // bar 4
  play(C4, crot);
  play(B3, crot);
  play(A3, crot);
  play(G3, crot);
  // bar 5
  play(F3, crot);
  play(E3, crot);
  play(D3, crot);
  play(C3, crot);
}

void twinkle_twinkle() {
  set_tempo(default_tempo);
  // 4/4 time
  // bar 1 - Twinkle, twinkle
  play(C4, crot);
  play(C4, crot);
  play(G4, crot);
  play(G4, crot);
  // bar 2 - little star
  play(A4, crot);
  play(A4, crot);
  play(G4, crot);
  rest(crot);
  // bar 3 - How I wonder
  play(F4, crot);
  play(F4, crot);
  play(E4, crot);
  play(E4, crot);
  // bar 4 - what you are
  play(D4, crot);
  play(D4, crot);
  play(C4, crot);
  rest(crot);
  // bar 5 - Up above the
  play(G4, crot);
  play(G4, crot);
  play(F4, crot);
  play(F4, crot);
  // bar 6 - world so high
  play(E4, crot);
  play(E4, crot);
  play(D4, crot);
  rest(crot);
  // bar 7 - Like a diamond
  play(G4, crot);
  play(G4, crot);
  play(F4, crot);
  play(F4, crot);
  // bar 8 - in the sky
  play(E4, crot);
  play(E4, crot);
  play(D4, crot);
  rest(crot);
  // bar 9 - Twinkle, twinkle
  play(C4, crot);
  play(C4, crot);
  play(G4, crot);
  play(G4, crot);
  // bar 10 - little star
  play(A4, crot);
  play(A4, crot);
  play(G4, crot);
  rest(crot);
  // bar 11 - How I wonder
  play(F4, crot);
  play(F4, crot);
  play(E4, crot);
  play(E4, crot);
  // bar 12 - what you are
  play(D4, crot);
  play(D4, crot);
  play(C4, crot);
  rest(crot);
}

void jingle_bells() {
  set_tempo(default_tempo * 2); // very lively
  // 4/4 time
  // bar 1
  play(B3, crot);
  play(B3, crot);
  play(B3, minim);
  // bar 2
  play(B3, crot);
  play(B3, crot);
  play(B3, minim);
  // bar 3
  play(B3, crot);
  play(D4, crot);
  play(G3, crot);
  play(A3, crot);
  // bar 4
  play(B3, semib);
  // bar 5
  play(C4, crot);
  play(C4, crot);
  play(C4, crot);
  play(C4, crot);
  // bar 6
  play(C4, crot);
  play(B3, crot);
  play(B3, crot);
  play(B3, crot);
  // bar 7
  play(B3, crot);
  play(A3, crot);
  play(A3, crot);
  play(B3, crot);
  // bar 8
  play(A3, minim);
  play(D4, minim);
  // bar 9
  play(B3, crot);
  play(B3, crot);
  play(B3, minim);
  // bar 10
  play(B3, crot);
  play(B3, crot);
  play(B3, minim);
  // bar 11
  play(B3, crot);
  play(D4, crot);
  play(G3, crot);
  play(A3, crot);
  // bar 12
  play(B3, semib);
  // bar 13
  play(C4, crot);
  play(C4, crot);
  play(C4, crot);
  play(C4, crot);
  // bar 14
  play(C4, crot);
  play(B3, crot);
  play(B3, crot);
  play(B3, crot);
  // bar 15
  play(D4, crot);
  play(D4, crot);
  play(C4, crot);
  play(A3, crot);
  // bar 16
  play(G3, semib);
  set_tempo(default_tempo); // reset tempo
}

void happy_birthday() {
  set_tempo(default_tempo);
  // 3/4 time
  // bar 1
  play(G3, quav);
  play(G3, quav);
  play(A3, crot);
  play(G3, crot);
  // bar 2
  play(C4, crot);
  play(B3, minim);
  // bar 3
  play(G3, quav);
  play(G3, quav);
  play(A3, crot);
  play(G3, crot);
  // bar 4
  play(D4, crot);
  play(C4, minim);
  // bar 5
  play(G3, quav);
  play(G3, quav);
  play(G4, crot);
  play(E4, crot);
  // bar 6
  play(C4, crot);
  play(B3, crot);
  play(A3, crot);
  // bar 7
  play(F4, quav);
  play(F4, quav);
  play(E4, crot);
  play(C4, crot);
  // bar 8
  play(D4, crot);
  play(C4, minim);
}

void ditty_1() {
  set_tempo(default_tempo * 2); // lively pace
  // 3/4 time
  // bar 1
  play(C4, minim);
  play(G3, crot);
  // bar 2
  play(G3, crot);
  play(GS3, minim);
  // bar 3
  play(G3, minim);
  rest(crot);
  // bar 4
  play(B3, minim);
  play(C4, crot);
  set_tempo(default_tempo); // reset tempo
}

void door_bell_1() {
  set_tempo(default_tempo);
  // 4/4 time
  // bar 1
  play(E4, minim);
  play(C4, minim);
  // bar 2
  play(D4, minim);
  play(G3, minim);
  // bar 3
  rest(semib);
  // bar 4
  play(G3, minim);
  play(D4, minim);
  // bar 5
  play(E4, minim);
  play(C4, minim);
}

void door_bell_2() {// basic bing/bong door chime
  set_tempo(default_tempo * 2); // lively pace
  // 3/4 time
  // bar 1
  play(E5, dot_minim);
  // bar 2
  play(C5, dot_minim);
  // bar 3
  rest(dot_minim);
  // bar 4
  play(E5, dot_minim);
  // bar 5
  play(C5, dot_minim);
  set_tempo(default_tempo);   // reset tempo
}

void ode_to_joy() {
  set_tempo(allegro);
  // 4/4 time
  //bar 1 
  play(B3, crot);
  play(B3, crot);
  play(C4, crot);
  play(D4, crot);
  //bar 2 
  play(D4, crot);
  play(C4, crot);
  play(B3, crot);
  play(A3, crot);
  //bar 3 
  play(G3, crot);
  play(G3, crot);
  play(A3, crot);
  play(B3, crot);
  //bar 4 
  play(B3, crot + quav);
  play(A3, quav);
  play(A3, minim);
  //bar 5 
  play(B3, crot);
  play(B3, crot);
  play(C4, crot);
  play(D4, crot);
  //bar 6 
  play(D4, crot);
  play(C4, crot);
  play(B3, crot);
  play(A3, crot);
  //bar 7 
  play(G3, crot);
  play(G3, crot);
  play(A3, crot);
  play(B3, crot);
  //bar 8 
  play(A3, crot + quav);
  play(G3, quav);
  play(G3, minim);
  //bar 9 
  play(A3, crot);
  play(A3, crot);
  play(B3, crot);
  play(G3, crot);
  //bar 10 
  play(A3, crot);
  play(B3, quav);
  play(C4, quav);
  play(B3, crot);
  play(G3, crot);
  //bar 11 
  play(A3, crot);
  play(B3, quav);
  play(C4, quav);
  play(B3, crot);
  play(A3, crot);
  //bar 12 
  play(G3, crot);
  play(A3, crot);
  play(D3, minim);
  //bar 13 
  play(B3, crot);
  play(B3, crot);
  play(C4, crot);
  play(D4, crot);
  //bar 14 
  play(D4, crot);
  play(C4, crot);
  play(B3, crot);
  play(A3, crot);
  //bar 15 
  play(G3, crot);
  play(G3, crot);
  play(A3, crot);
  play(B3, crot);
  //bar 16 
  play(A3, crot + quav);
  play(G3, quav);
  play(G3, minim);
}

void canon_in_D() {
  set_tempo(110);
  // 4/4 time
  // melody starts at bar 5
  // bar 5
  play(FS4, minim);
  play(E4, minim);
  // bar 6
  play(D4, minim);
  play(CS4, minim);
  // bar 7
  play(B3, minim);
  play(A3, minim);
  // bar 8
  play(B3, minim);
  play(CS4, minim);
  // bar 9
  play(FS4, minim);
  play(E4, minim);
  // bar 10
  play(D4, minim);
  play(CS4, minim);
  // bar 11
  play(B3, minim);
  play(A3, minim);
  // bar 12
  play(B3, minim);
  play(CS4, minim);
  // bar 13
  play(D3, crot);
  play(FS3, crot);
  play(A3, crot);
  play(G3, crot);
  // bar 14
  play(FS3, crot);
  play(D3, crot);
  play(FS3, crot);
  play(E3, crot);
  // bar 15
  play(D3, crot);
  play(B2, crot);
  play(D3, crot);
  play(A3, crot);
  // bar 16
  play(G3, crot);
  play(B3, crot);
  play(A3, crot);
  play(G3, crot);
  // bar 17
  play(FS3, crot);
  play(D3, crot);
  play(E3, crot);
  play(CS4, crot);
  // bar 18
  play(D4, crot);
  play(FS4, crot);
  play(A4, crot);
  play(A3, crot);
  // bar 19
  play(B3, crot);
  play(G3, crot);
  play(A3, crot);
  play(FS3, crot);
  // bar 20
  play(E3, crot);
  play(D4, crot);
  play(D3, crot + quav);
  play(CS4, quav);
  // bar 21
  play(D4, quav);
  play(CS4, quav);
  play(D4, quav);
  play(D3, quav);

  play(CS3, quav);
  play(A3, quav);
  play(E3, quav);
  play(FS3, quav);
  // bar 22
  play(D3, quav);
  play(D4, quav);
  play(CS4, quav);
  play(B3, quav);

  play(CS4, quav);
  play(FS4, quav);
  play(A4, quav);
  play(B4, quav);
  // bar 23
  play(G4, quav);
  play(FS4, quav);
  play(E4, quav);
  play(G4, quav);

  play(FS4, quav);
  play(E4, quav);
  play(D4, quav);
  play(CS4, quav);
  // bar 24
  play(B3, quav);
  play(A3, quav);
  play(G3, quav);
  play(FS3, quav);

  play(E3, quav);
  play(G3, quav);
  play(FS3, quav);
  play(E3, quav);
  // bar 25
  play(D3, quav);
  play(E3, quav);
  play(FS3, quav);
  play(G3, quav);

  play(A3, quav);
  play(E3, quav);
  play(A3, quav);
  play(G3, quav);
  // bar 26
  play(FS3, quav);
  play(B3, quav);
  play(A3, quav);
  play(G3, quav);

  play(A3, quav);
  play(G3, quav);
  play(FS3, quav);
  play(E3, quav);
  // bar 27
  play(D3, quav);
  play(B2, quav);
  play(B3, quav);
  play(CS4, quav);

  play(D4, quav);
  play(CS4, quav);
  play(B3, quav);
  play(A3, quav);
  // bar 28
  play(G3, quav);
  play(FS3, quav);
  play(E3, quav);
  play(B3, quav);

  play(A3, quav);
  play(B3, quav);
  play(A3, quav);
  play(G3, quav);
  // bar 29
  play(FS3, crot);
  play(FS4, crot);
  play(E4, minim);
  // bar 30
  rest(crot);
  play(D4, crot);
  play(FS4, minim);
  // bar 31
  play(B4, minim);
  play(A4, minim);
  // bar 32
  play(B4, minim);
  play(CS5, minim);
  // bar 33
  play(D5, crot);
  play(D4, crot);
  play(CS4, minim);
  // bar 34
  rest(crot);
  play(B4, crot);
  play(D4, minim);
  // bar 35
  play(D4, dot_minim);
  play(D4, crot);
  // bar 36
  play(D4, crot);
  play(G4, crot);
  play(E4, crot);
  play(A4, crot);
  // bar 37
  play(A4, quav);
  play(FS4, semiq);
  play(G4, semiq);

  play(A4, quav);
  play(FS4, semiq);
  play(G4, semiq);

  play(A4, semiq);
  play(A3, semiq);
  play(B3, semiq);
  play(CS4, semiq);

  play(D4, semiq);
  play(E4, semiq);
  play(FS4, semiq);
  play(G4, semiq);
  // bar 38
  play(FS4, quav);
  play(D4, semiq);
  play(E4, semiq);

  play(FS4, quav);
  play(FS3, semiq);
  play(G3, semiq);

  play(A3, semiq);
  play(B3, semiq);
  play(A3, semiq);
  play(G3, semiq);

  play(A3, semiq);
  play(FS3, semiq);
  play(G3, semiq);
  play(A3, semiq);
  // bar 39
  play(G3, quav);
  play(B3, semiq);
  play(A3, semiq);

  play(G3, quav);
  play(FS3, semiq);
  play(E3, semiq);

  play(FS3, semiq);
  play(E3, semiq);
  play(D3, semiq);
  play(E3, semiq);

  play(FS3, semiq);
  play(G3, semiq);
  play(A3, semiq);
  play(B3, semiq);
  // bar 40
  play(G3, quav);
  play(B3, semiq);
  play(A3, semiq);

  play(B3, quav);
  play(CS4, semiq);
  play(D4, semiq);

  play(A3, semiq);
  play(B3, semiq);
  play(CS4, semiq);
  play(D4, semiq);

  play(E4, semiq);
  play(FS4, semiq);
  play(G4, semiq);
  play(A4, semiq);
  // bar 41
  play(FS4, quav);
  play(D4, semiq);
  play(E4, semiq);

  play(FS4, quav);
  play(E3, semiq);
  play(D4, semiq);

  play(E4, semiq);
  play(CS4, semiq);
  play(D4, semiq);
  play(E4, semiq);

  play(FS4, semiq);
  play(E4, semiq);
  play(D4, semiq);
  play(CS4, semiq);
  // bar 42
  play(D4, quav);
  play(B4, semiq);
  play(CS4, semiq);

  play(D4, quav);
  play(D3, semiq);
  play(E3, semiq);

  play(FS3, semiq);
  play(G3, semiq);
  play(FS3, semiq);
  play(E3, semiq);

  play(FS3, semiq);
  play(D4, semiq);
  play(CS4, semiq);
  play(D4, semiq);
  // bar 43
  play(B3, quav);
  play(D4, semiq);
  play(CS4, semiq);

  play(B3, quav);
  play(A3, semiq);
  play(G3, semiq);

  play(A3, semiq);
  play(G3, semiq);
  play(FS3, semiq);
  play(G3, semiq);

  play(A3, semiq);
  play(B3, semiq);
  play(CS4, semiq);
  play(D4, semiq);
  // bar 44
  play(B3, quav);
  play(D4, semiq);
  play(CS4, semiq);

  play(D4, quav);
  play(D4, semiq);
  play(CS4, semiq);

  play(CS4, semiq);
  play(D4, semiq);
  play(E4, semiq);
  play(D4, semiq);

  play(CS4, semiq);
  play(D4, semiq);
  play(B3, semiq);
  play(CS4, semiq);
  // bar 45
  play(D4, crot + quav);
  play(FS4, quav);
  play(FS4, quav);
  play(G4, quav);
  play(FS4, quav);
  play(E4, quav);
  // bar 46
  play(D4, crot + quav);
  play(D4, quav);
  play(D4, quav);
  play(E4, quav);
  play(D4, quav);
  play(CS4, quav);
  // bar 47
  play(B3, minim);
  play(D4, minim);
  // bar 48
  play(D4, quav);
  play(C4, quav);
  play(B3, quav);
  play(C4, quav);
  play(A3, crot);
  play(CS4, crot);
  // bar 49
  play(D4, crot + quav);
  play(A4, quav);
  play(A4, quav);
  play(B4, quav);
  play(A4, quav);
  play(G4, quav);
  // bar 50
  play(FS4, crot + quav);
  play(FS4, quav);
  play(FS4, quav);
  play(G4, quav);
  play(FS4, quav);
  play(E4, quav);
  // bar 51
  play(D4, quav);
  play(C4, quav);
  play(B3, quav);
  play(C4, quav);
  play(A4, crot + quav);
  play(A4, quav);
  // bar 52
  play(G3, crot);
  play(D4, crot);
  play(CS4, crot + quav);
  play(CS4, quav);
  // bar 53
  play(D4, semib);
}
