//
// let's make music
//
// Ron D Bentley, Stafford, UK, August 2021
// Modified:
//   Oct 2022 to remove compliler warning re redfinition
//   of macros for some macro locally defined notes, eg B0, B1, etc. 
//   Local naming convention for notes now prefixed with "note_".
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
#define note_B0  31
#define note_C1  33
#define note_CS1 35
#define note_DF1 35
#define note_D1  37
#define note_DS1 39
#define note_EF1 39
#define note_E1  41
#define note_F1  44
#define note_FS1 46
#define note_GF1 46
#define note_G1  49
#define note_GS1 52
#define note_AF1 52
#define note_A1  55
#define note_AS1 58
#define note_BF1 58
#define note_b1  62
#define note_C2  65
#define note_CS2 69
#define note_DF2 69
#define note_D2  73
#define note_DS2 78
#define note_EF2 78
#define note_E2  82
#define note_F2  87
#define note_FS2 93
#define note_GF2 93
#define note_G2  98
#define note_GS2 104
#define note_AF2 104
#define note_A2  110
#define note_as2 117
#define note_BF2 117
#define note_B2  123
#define note_C3  131
#define note_CS3 139
#define note_DF3 139
#define note_D3  147
#define note_DS3 156
#define note_EF3 156
#define note_E3  165
#define note_F3  175
#define note_FS3 185
#define note_GF3 185
#define note_G3  196
#define note_GS3 208
#define note_AF3 208
#define note_A3  220
#define note_AS3 233
#define note_BF3 233
#define note_B3  247
#define note_C4  262 // <--------- middle C
#define note_CS4 277
#define note_DF4 277
#define note_D4  294
#define note_DS4 311
#define note_EF4 311
#define note_E4  330
#define note_F4  349
#define note_FS4 370
#define note_GF4 370
#define note_G4  392
#define note_GS4 415
#define note_AF4 415
#define note_A4  440
#define note_AS4 466
#define note_BF4 466
#define note_B4  494
#define note_C5  523
#define note_CS5 554
#define note_DF5 554
#define note_D5  587
#define note_DS5 622
#define note_EF5 622
#define note_E5  659
#define note_F5  698
#define note_FS5 740
#define note_GF5 740
#define note_G5  784
#define note_GS5 831
#define note_AF5 831
#define note_A5  880
#define note_AS5 932
#define note_BF5 932
#define note_B5  988
#define note_C6  1047
#define note_CS6 1109
#define note_DF6 1109
#define note_D6  1175
#define note_DS6 1245
#define note_EF6 1245
#define note_E6  1319
#define note_F6  1397
#define note_FS6 1480
#define note_GF6 1480
#define note_G6  1568
#define note_GS6 1661
#define note_AF6 1661
#define note_A6  1760
#define note_AS6 1865
#define note_BF6 1865
#define note_B6  1976
#define note_C7  2093
#define note_CS7 2217
#define note_DF7 2217
#define note_D7  2349
#define note_DS7 2489
#define note_EF7 2489
#define note_E7  2637
#define note_F7  2794
#define note_FS7 2960
#define note_GF7 2960
#define note_G7  3136
#define note_GS7 3322
#define note_AF7 3322
#define note_A7  3520
#define note_AS7 3729
#define note_BF7 3729
#define note_B7  3951
#define note_C8  4186
#define note_CS8 4435
#define note_DF8 4435
#define note_D8  4699
#define note_DS8 4978
#define note_EF8 4978

#define speaker                11     // digital pin number for speaker/buzzer

float default_tempo = float(animato); // default tempo - beats per minute
float current_tempo = default_tempo;
float timings[7];                     // holds timings for each defined note/rest time value
#define trills_per_crotchet     8     // number of note changes in a trill per crotchet
float trill_duration;                 // set depending on the tempo selected

//
// Standard note/rest duration definitions, set in the set_tempo function
//
#define semib       timings[0] // 4 beats
#define dot_minim   timings[1] // 3 beats
#define minim       timings[2] // 2 beats
#define crot        timings[3] // 1 beat
#define quav        timings[4] // 1/2 beat
#define semiq       timings[5] // 1/4 beat
#define demi_semiq  timings[6] // 1/8 beat

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
  current_tempo = new_tempo;           // keep current tempo up to date in case it needs to be queried
  crotchet_duration = 60 / new_tempo;  // timing in seconds for 1 beat
  semib      = crotchet_duration * 4;  // semibrieve, 4 beats
  dot_minim  = crotchet_duration * 3;  // dotted mimin, 3 beats
  minim      = crotchet_duration * 2;  // minim, 2 beats
  crot       = crotchet_duration;      // crotchet, 1 beat
  quav       = crotchet_duration / 2;  // quaver, 1/2 beat
  semiq      = crotchet_duration / 4;  // semiquaver, 1/4 beat
  demi_semiq = crotchet_duration / 8;  // demi-semi-quaver, 1/8 beat

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

  silent_night();
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

  scarborough_fair();
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
  play(note_C4, crot);
  play(note_D4, crot);
  play(note_E4, crot);
  play(note_F4, crot);
  // bar 2
  play(note_G4, crot);
  play(note_A4, crot);
  play(note_B4, crot);
  play(note_C5, crot);
  // bar 3
  rest(semib);
  // C major scale - down
  // bar 4
  play(note_C5, crot);
  play(note_B4, crot);
  play(note_A4, crot);
  play(note_G4, crot);
  // bar 5
  play(note_F4, crot);
  play(note_E4, crot);
  play(note_D4, crot);
  play(note_C4, crot);
}

void twinkle_twinkle() {
  set_tempo(default_tempo);
  // 4/4 time
  // bar 1 - Twinkle, twinkle
  play(note_C4, crot);
  play(note_C4, crot);
  play(note_G4, crot);
  play(note_G4, crot);
  // bar 2 - little star
  play(note_A4, crot);
  play(note_A4, crot);
  play(note_G4, crot);
  rest(crot);
  // bar 3 - How I wonder
  play(note_F4, crot);
  play(note_F4, crot);
  play(note_E4, crot);
  play(note_E4, crot);
  // bar 4 - what you are
  play(note_D4, crot);
  play(note_D4, crot);
  play(note_C4, crot);
  rest(crot);
  // bar 5 - Up above the
  play(note_G4, crot);
  play(note_G4, crot);
  play(note_F4, crot);
  play(note_F4, crot);
  // bar 6 - world so high
  play(note_E4, crot);
  play(note_E4, crot);
  play(note_D4, crot);
  rest(crot);
  // bar 7 - Like a diamond
  play(note_G4, crot);
  play(note_G4, crot);
  play(note_F4, crot);
  play(note_F4, crot);
  // bar 8 - in the sky
  play(note_E4, crot);
  play(note_E4, crot);
  play(note_D4, crot);
  rest(crot);
  // bar 9 - Twinkle, twinkle
  play(note_C4, crot);
  play(note_C4, crot);
  play(note_G4, crot);
  play(note_G4, crot);
  // bar 10 - little star
  play(note_A4, crot);
  play(note_A4, crot);
  play(note_G4, crot);
  rest(crot);
  // bar 11 - How I wonder
  play(note_F4, crot);
  play(note_F4, crot);
  play(note_E4, crot);
  play(note_E4, crot);
  // bar 12 - what you are
  play(note_D4, crot);
  play(note_D4, crot);
  play(note_C4, crot);
  rest(crot);
}

void jingle_bells() {
  set_tempo(default_tempo * 2); // very lively
  // 4/4 time
  // bar 1
  play(note_B3, crot);
  play(note_B3, crot);
  play(note_B3, minim);
  // bar 2
  play(note_B3, crot);
  play(note_B3, crot);
  play(note_B3, minim);
  // bar 3
  play(note_B3, crot);
  play(note_D4, crot);
  play(note_G3, crot);
  play(note_A3, crot);
  // bar 4
  play(note_B3, semib);
  // bar 5
  play(note_C4, crot);
  play(note_C4, crot);
  play(note_C4, crot);
  play(note_C4, crot);
  // bar 6
  play(note_C4, crot);
  play(note_B3, crot);
  play(note_B3, crot);
  play(note_B3, crot);
  // bar 7
  play(note_B3, crot);
  play(note_A3, crot);
  play(note_A3, crot);
  play(note_B3, crot);
  // bar 8
  play(note_A3, minim);
  play(note_D4, minim);
  // bar 9
  play(note_B3, crot);
  play(note_B3, crot);
  play(note_B3, minim);
  // bar 10
  play(note_B3, crot);
  play(note_B3, crot);
  play(note_B3, minim);
  // bar 11
  play(note_B3, crot);
  play(note_D4, crot);
  play(note_G3, crot);
  play(note_A3, crot);
  // bar 12
  play(note_B3, semib);
  // bar 13
  play(note_C4, crot);
  play(note_C4, crot);
  play(note_C4, crot);
  play(note_C4, crot);
  // bar 14
  play(note_C4, crot);
  play(note_B3, crot);
  play(note_B3, crot);
  play(note_B3, crot);
  // bar 15
  play(note_D4, crot);
  play(note_D4, crot);
  play(note_C4, crot);
  play(note_A3, crot);
  // bar 16
  play(note_G3, semib);
  set_tempo(default_tempo); // reset tempo
}

void happy_birthday() {
  set_tempo(default_tempo);
  // 3/4 time
  // bar 1
  play(note_G3, quav);
  play(note_G3, quav);
  play(note_A3, crot);
  play(note_G3, crot);
  // bar 2
  play(note_C4, crot);
  play(note_B3, minim);
  // bar 3
  play(note_G3, quav);
  play(note_G3, quav);
  play(note_A3, crot);
  play(note_G3, crot);
  // bar 4
  play(note_D4, crot);
  play(note_C4, minim);
  // bar 5
  play(note_G3, quav);
  play(note_G3, quav);
  play(note_G4, crot);
  play(note_E4, crot);
  // bar 6
  play(note_C4, crot);
  play(note_B3, crot);
  play(note_A3, crot);
  // bar 7
  play(note_F4, quav);
  play(note_F4, quav);
  play(note_E4, crot);
  play(note_C4, crot);
  // bar 8
  play(note_D4, crot);
  play(note_C4, minim);
}

void ditty_1() {
  set_tempo(default_tempo * 2); // lively pace
  // 3/4 time
  // bar 1
  play(note_C4, minim);
  play(note_G3, crot);
  // bar 2
  play(note_G3, crot);
  play(note_GS3, minim);
  // bar 3
  play(note_G3, minim);
  rest(crot);
  // bar 4
  play(note_B3, minim);
  play(note_C4, crot);
  set_tempo(default_tempo); // reset tempo
}

void door_bell_1() {
  set_tempo(default_tempo);
  // 4/4 time
  // bar 1
  play(note_E4, minim);
  play(note_C4, minim);
  // bar 2
  play(note_D4, minim);
  play(note_G3, minim);
  // bar 3
  rest(semib);
  // bar 4
  play(note_G3, minim);
  play(note_D4, minim);
  // bar 5
  play(note_E4, minim);
  play(note_C4, minim);
}

void door_bell_2() {// basic bing/bong door chime
  set_tempo(default_tempo * 2); // lively pace
  // 3/4 time
  // bar 1
  play(note_E5, dot_minim);
  // bar 2
  play(note_C5, dot_minim);
  // bar 3
  rest(dot_minim);
  // bar 4
  play(note_E5, dot_minim);
  // bar 5
  play(note_C5, dot_minim);
  set_tempo(default_tempo);   // reset tempo
}

void ode_to_joy() {
  set_tempo(allegro);
  // 4/4 time
  //bar 1
  play(note_B4, crot);
  play(note_B4, crot);
  play(note_C5, crot);
  play(note_D5, crot);
  //bar 2
  play(note_D5, crot);
  play(note_C5, crot);
  play(note_B4, crot);
  play(note_A4, crot);
  //bar 3
  play(note_G4, crot);
  play(note_G4, crot);
  play(note_A4, crot);
  play(note_B4, crot);
  //bar 4
  play(note_B4, crot + quav);
  play(note_A4, quav);
  play(note_A4, minim);
  //bar 5
  play(note_B4, crot);
  play(note_B4, crot);
  play(note_C5, crot);
  play(note_D5, crot);
  //bar 6
  play(note_D5, crot);
  play(note_C5, crot);
  play(note_B4, crot);
  play(note_A4, crot);
  //bar 7
  play(note_G4, crot);
  play(note_G4, crot);
  play(note_A4, crot);
  play(note_B4, crot);
  //bar 8
  play(note_A4, crot + quav);
  play(note_G4, quav);
  play(note_G4, minim);
  //bar 9
  play(note_A4, crot);
  play(note_A4, crot);
  play(note_B4, crot);
  play(note_G4, crot);
  //bar 10
  play(note_A4, crot);
  play(note_B4, quav);
  play(note_C5, quav);
  play(note_B4, crot);
  play(note_G4, crot);
  //bar 11
  play(note_A4, crot);
  play(note_B4, quav);
  play(note_C5, quav);
  play(note_B4, crot);
  play(note_A4, crot);
  //bar 12
  play(note_G4, crot);
  play(note_A4, crot);
  play(note_D4, minim);
  //bar 13
  play(note_B4, crot);
  play(note_B4, crot);
  play(note_C5, crot);
  play(note_D5, crot);
  //bar 14
  play(note_D5, crot);
  play(note_C5, crot);
  play(note_B4, crot);
  play(note_A4, crot);
  //bar 15
  play(note_G4, crot);
  play(note_G4, crot);
  play(note_A4, crot);
  play(note_B4, crot);
  //bar 16
  play(note_A4, crot + quav);
  play(note_G4, quav);
  play(note_G4, minim);
}

void canon_in_D() {
  set_tempo(110);
  // 4/4 time
  // melody starts at bar 5
  // bar 5
  play(note_FS5, minim);
  play(note_E5, minim);
  // bar 6
  play(note_D5, minim);
  play(note_CS5, minim);
  // bar 7
  play(note_B4, minim);
  play(note_A4, minim);
  // bar 8
  play(note_B4, minim);
  play(note_CS5, minim);
  // bar 9
  play(note_FS5, minim);
  play(note_E5, minim);
  // bar 10
  play(note_D5, minim);
  play(note_CS5, minim);
  // bar 11
  play(note_B4, minim);
  play(note_A4, minim);
  // bar 12
  play(note_B4, minim);
  play(note_CS5, minim);
  // bar 13
  play(note_D4, crot);
  play(note_FS4, crot);
  play(note_A4, crot);
  play(note_G4, crot);
  // bar 14
  play(note_FS4, crot);
  play(note_D4, crot);
  play(note_FS4, crot);
  play(note_E4, crot);
  // bar 15
  play(note_D4, crot);
  play(note_B3, crot);
  play(note_D4, crot);
  play(note_A4, crot);
  // bar 16
  play(note_G4, crot);
  play(note_B4, crot);
  play(note_A4, crot);
  play(note_G4, crot);
  // bar 17
  play(note_FS4, crot);
  play(note_D4, crot);
  play(note_E4, crot);
  play(note_CS5, crot);
  // bar 18
  play(note_D5, crot);
  play(note_FS5, crot);
  play(note_A5, crot);
  play(note_A4, crot);
  // bar 19
  play(note_B4, crot);
  play(note_G4, crot);
  play(note_A4, crot);
  play(note_FS4, crot);
  // bar 20
  play(note_E4, crot);
  play(note_D5, crot);
  play(note_D5, crot + quav);
  play(note_CS5, quav);
  // bar 21
  play(note_D5, quav);
  play(note_CS5, quav);
  play(note_D5, quav);
  play(note_D4, quav);

  play(note_CS4, quav);
  play(note_A4, quav);
  play(note_E4, quav);
  play(note_FS4, quav);
  // bar 22
  play(note_D4, quav);
  play(note_D5, quav);
  play(note_CS5, quav);
  play(note_B4, quav);

  play(note_CS5, quav);
  play(note_FS5, quav);
  play(note_A5, quav);
  play(note_B5, quav);
  // bar 23
  play(note_G5, quav);
  play(note_FS5, quav);
  play(note_E5, quav);
  play(note_G5, quav);

  play(note_FS5, quav);
  play(note_E5, quav);
  play(note_D5, quav);
  play(note_CS5, quav);
  // bar 24
  play(note_B4, quav);
  play(note_A4, quav);
  play(note_G4, quav);
  play(note_FS4, quav);

  play(note_E4, quav);
  play(note_G4, quav);
  play(note_FS4, quav);
  play(note_E4, quav);
  // bar 25
  play(note_D4, quav);
  play(note_E4, quav);
  play(note_FS4, quav);
  play(note_G4, quav);

  play(note_A4, quav);
  play(note_E4, quav);
  play(note_A4, quav);
  play(note_G4, quav);
  // bar 26
  play(note_FS4, quav);
  play(note_B4, quav);
  play(note_A4, quav);
  play(note_G4, quav);

  play(note_A4, quav);
  play(note_G4, quav);
  play(note_FS4, quav);
  play(note_E4, quav);
  // bar 27
  play(note_D4, quav);
  play(note_B3, quav);
  play(note_B4, quav);
  play(note_CS5, quav);

  play(note_D5, quav);
  play(note_CS5, quav);
  play(note_B4, quav);
  play(note_A4, quav);
  // bar 28
  play(note_G4, quav);
  play(note_FS4, quav);
  play(note_E4, quav);
  play(note_B4, quav);

  play(note_A4, quav);
  play(note_B4, quav);
  play(note_A4, quav);
  play(note_G4, quav);
  // bar 29
  play(note_FS4, crot);
  play(note_FS5, crot);
  play(note_E5, minim);
  // bar 30
  rest(crot);
  play(note_D5, crot);
  play(note_FS5, minim);
  // bar 31
  play(note_B5, minim);
  play(note_A5, minim);
  // bar 32
  play(note_B5, minim);
  play(note_CS6, minim);
  // bar 33
  play(note_D6, crot);
  play(note_D5, crot);
  play(note_CS5, minim);
  // bar 34
  rest(crot);
  play(note_B5, crot);
  play(note_D5, minim);
  // bar 35
  play(note_D5, dot_minim);
  play(note_D5, crot);
  // bar 36
  play(note_D5, crot);
  play(note_G5, crot);
  play(note_E5, crot);
  play(note_A5, crot);
  // bar 37
  play(note_A5, quav);
  play(note_FS5, semiq);
  play(note_G5, semiq);

  play(note_A5, quav);
  play(note_FS5, semiq);
  play(note_G5, semiq);

  play(note_A5, semiq);
  play(note_A4, semiq);
  play(note_B4, semiq);
  play(note_CS5, semiq);

  play(note_D5, semiq);
  play(note_E5, semiq);
  play(note_FS5, semiq);
  play(note_G5, semiq);
  // bar 38
  play(note_FS5, quav);
  play(note_D5, semiq);
  play(note_E5, semiq);

  play(note_FS5, quav);
  play(note_FS4, semiq);
  play(note_G4, semiq);

  play(note_A4, semiq);
  play(note_B4, semiq);
  play(note_A4, semiq);
  play(note_G4, semiq);

  play(note_A4, semiq);
  play(note_FS4, semiq);
  play(note_G4, semiq);
  play(note_A4, semiq);
  // bar 39
  play(note_G4, quav);
  play(note_B4, semiq);
  play(note_A4, semiq);

  play(note_G4, quav);
  play(note_FS4, semiq);
  play(note_E4, semiq);

  play(note_FS4, semiq);
  play(note_E4, semiq);
  play(note_D4, semiq);
  play(note_E4, semiq);

  play(note_FS4, semiq);
  play(note_G4, semiq);
  play(note_A4, semiq);
  play(note_B4, semiq);
  // bar 40
  play(note_G4, quav);
  play(note_B4, semiq);
  play(note_A4, semiq);

  play(note_B4, quav);
  play(note_CS5, semiq);
  play(note_D5, semiq);

  play(note_A4, semiq);
  play(note_B4, semiq);
  play(note_CS5, semiq);
  play(note_D5, semiq);

  play(note_E5, semiq);
  play(note_FS5, semiq);
  play(note_G5, semiq);
  play(note_A5, semiq);
  // bar 41
  play(note_FS5, quav);
  play(note_D5, semiq);
  play(note_E5, semiq);

  play(note_FS5, quav);
  play(note_E4, semiq);
  play(note_D5, semiq);

  play(note_E5, semiq);
  play(note_CS5, semiq);
  play(note_D5, semiq);
  play(note_E5, semiq);

  play(note_FS5, semiq);
  play(note_E5, semiq);
  play(note_D5, semiq);
  play(note_CS5, semiq);
  // bar 42
  play(note_D5, quav);
  play(note_B5, semiq);
  play(note_CS5, semiq);

  play(note_D5, quav);
  play(note_D4, semiq);
  play(note_E4, semiq);

  play(note_FS4, semiq);
  play(note_G4, semiq);
  play(note_FS4, semiq);
  play(note_E4, semiq);

  play(note_FS4, semiq);
  play(note_D5, semiq);
  play(note_CS5, semiq);
  play(note_D5, semiq);
  // bar 43
  play(note_B4, quav);
  play(note_D5, semiq);
  play(note_CS5, semiq);

  play(note_B4, quav);
  play(note_A4, semiq);
  play(note_G4, semiq);

  play(note_A4, semiq);
  play(note_G4, semiq);
  play(note_FS4, semiq);
  play(note_G4, semiq);

  play(note_A4, semiq);
  play(note_B4, semiq);
  play(note_CS5, semiq);
  play(note_D5, semiq);
  // bar 44
  play(note_B4, quav);
  play(note_D5, semiq);
  play(note_CS5, semiq);

  play(note_D5, quav);
  play(note_D5, semiq);
  play(note_CS5, semiq);

  play(note_CS5, semiq);
  play(note_D5, semiq);
  play(note_E5, semiq);
  play(note_D5, semiq);

  play(note_CS5, semiq);
  play(note_D5, semiq);
  play(note_B4, semiq);
  play(note_CS5, semiq);
  // bar 45
  play(note_D5, crot + quav);
  play(note_FS5, quav);
  play(note_FS5, quav);
  play(note_G5, quav);
  play(note_FS5, quav);
  play(note_E5, quav);
  // bar 46
  play(note_D5, crot + quav);
  play(note_D5, quav);
  play(note_D5, quav);
  play(note_E5, quav);
  play(note_D5, quav);
  play(note_CS5, quav);
  // bar 47
  play(note_B4, minim);
  play(note_D5, minim);
  // bar 48
  play(note_D5, quav);
  play(note_C5, quav);
  play(note_B4, quav);
  play(note_C5, quav);
  play(note_A4, crot);
  play(note_CS5, crot);
  // bar 49
  play(note_D5, crot + quav);
  play(note_A5, quav);
  play(note_A5, quav);
  play(note_B5, quav);
  play(note_A5, quav);
  play(note_G5, quav);
  // bar 50
  play(note_FS5, crot + quav);
  play(note_FS5, quav);
  play(note_FS5, quav);
  play(note_G5, quav);
  play(note_FS5, quav);
  play(note_E5, quav);
  // bar 51
  play(note_D5, quav);
  play(note_C5, quav);
  play(note_B4, quav);
  play(note_C5, quav);
  play(note_A4, crot + quav);
  play(note_A4, quav);
  // bar 52
  play(note_G4, crot);
  play(note_D5, crot);
  play(note_CS5, crot + quav);
  play(note_CS5, quav);
  // bar 53
  play(note_D5, semib);
}

void scarborough_fair() {
  // B flat / A sharp, 3/4 time
  // bar 1
  // run through twice
  for (uint8_t pass = 1; pass <= 2; pass++) {
    set_tempo(180);
    play(note_D4, minim);
    play(note_D4, crot);
    // bar 2
    play(note_A4, minim);
    play(note_A4, crot);
    // bar 3
    play(note_E4, crot + quav);
    play(note_F4, quav);
    play(note_E4, crot);
    // bar 4
    play(note_D4, dot_minim);
    // bar 5
    rest(crot);
    play(note_A4, crot);
    play(note_C5, crot);
    // bar 6
    play(note_D5, minim);
    play(note_C5, crot);
    // bar 7
    play(note_A4, crot);
    play(note_B4, crot);
    play(note_G4, crot);
    // bar 8 & 9
    play(note_A4, dot_minim + minim);
    play(note_D5, crot);
    // bar 10
    play(note_D5, minim);
    play(note_D5, crot);
    // bar 11
    play(note_C5, minim);
    play(note_A4, crot);
    // bar 12
    play(note_A4, crot);
    play(note_G4, crot);
    play(note_F4, crot);
    // bar 13
    play(note_E4, minim );
    play(note_A4, crot);
    // bar 14
    play(note_D4, minim);
    play(note_A4, crot);
    // bar 15
    play(note_G4, minim);
    play(note_F4, crot);
    // bar 16
    play(note_E4, crot);
    play(note_D4, crot);
    play(note_C4, crot);
    // bar 17 & 18
    play(note_D4, dot_minim + dot_minim);
    rest(dot_minim);
  }

}

void silent_night() {
  // 3/4 time
  set_tempo(default_tempo);
  // bar 1
  play(note_G4, crot + quav);
  play(note_A4, quav);
  play(note_G4, crot);
  // bar 2
  play(note_E4, dot_minim);
  // bar 3
  play(note_G4, crot + quav);
  play(note_A4, quav);
  play(note_G4, crot);
  // bar 4
  play(note_E4, dot_minim);
  // bar 5
  play(note_D5, minim);
  play(note_D5, crot);
  // bar 6
  play(note_B4, dot_minim);
  // bar 7
  play(note_C5, minim);
  play(note_C5, crot);
  // bar 8
  play(note_G4, dot_minim);
  // bars 9-12 and 13-16 are identical so repeat twice
  for (uint8_t pass = 1; pass <= 2; pass++) {
    // bar 9, bar 13
    play(note_A4, minim);
    play(note_A4, crot);
    // bar 10, bar 14
    play(note_C5, crot + quav);
    play(note_B4, quav);
    play(note_A4, crot);
    // bar 11, bar 15
    play(note_G4, crot + quav);
    play(note_A4, quav);
    play(note_G4, crot);
    // bar 12, bar 16
    play(note_E4, dot_minim);
  }
  // bar 17
  play(note_D5, minim);
  play(note_D5, crot);
  // bar 18
  play(note_F5, crot + quav);
  play(note_D5, quav);
  play(note_B4, crot);
  // bar 19
  play(note_C5, dot_minim);
  // bar 20
  play(note_E5, dot_minim);
  // bar 21
  play(note_C5, crot);
  play(note_G4, crot);
  play(note_E4, crot);
  // bar 22
  play(note_G4, crot + quav);
  play(note_F4, quav);
  play(note_D4, crot);
  // bars 23 & 24
  play(note_C4, dot_minim + dot_minim);
}
