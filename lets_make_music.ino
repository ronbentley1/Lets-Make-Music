//
// let's make music
//
// Ron D Bentley, Stafford, UK, August 2021
//
// This example and code is in the public domain and
// may be used without restriction and without warranty.
//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// % music/tone data and functions...                                      %
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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

#define speaker       11               // digital pin number for speaker/buzzer

float default_tempo = float(animato); // default tempo - beats per minute
float current_tempo = default_tempo;
float timings[6];                     // holds timings for each defined note/rest time value

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
}

//
// Play given note for given duration in seconds, or part thereof.
// Observe that this function is 'blocking', although the tone
// function is 'non-blocking', ie control stays with the function
// until note has completed.
//
void play(int note, float duration) {
  tone(speaker, note, duration * 1000); // play the given note for the given duration
  wait(duration);                       // wait for note to complete
}

//
// rest for given duration in seconds, or part thereof.
//
void rest(float duration) {
  noTone(speaker); // ensure no tone is currently playing
  wait(duration);  // wait for given rest to complete
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

  ditty_1(); // music with lights
  wait(3);

  door_bell_1(); // music with lights
  wait(3);

  door_bell_2(); // music with lights
  wait(3);

  ode_to_joy();
  wait(3);

  penny_lane();
  wait(3);

  yesterday();
  wait(3);

  annies_song();
  wait(3);

  black_velvet_band();
  wait(3);

  // and back to the beginning...
}












//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %        Example out-of-the-box 'shrink-wrapped' music commands         %
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void middle_C() {
  // C major scale - up
  play(C3, crot);
  play(D3, crot);
  play(E3, crot);
  play(F3, crot);
  play(G3, crot);
  play(A3, crot);
  play(B3, crot);
  play(C4, crot);
  rest(crot);
  // C major scale - down
  play(C4, crot);
  play(B3, crot);
  play(A3, crot);
  play(G3, crot);
  play(F3, crot);
  play(E3, crot);
  play(D3, crot);
  play(C3, crot);
  rest(crot);
}

void twinkle_twinkle() {
  set_tempo(default_tempo * 2);

  //Twinkle, twinkle, little star, C' C' G' G' A' A' G'
  play(C4, minim);
  play(C4, minim);
  play(G4, minim);
  play(G4, minim);
  play(A4, minim);
  play(A4, minim);
  play(G4, minim);
  rest(minim);

  //How I wonder what you are, F' F' E' E' D' D' C'
  play(F4, minim);
  play(F4, minim);
  play(E4, minim);
  play(E4, minim);
  play(D4, minim);
  play(D4, minim);
  play(C4, minim);
  rest(minim);

  //Up above the world so high, G' G' F' F' E' E' D'
  play(G4, minim);
  play(G4, minim);
  play(F4, minim);
  play(F4, minim);
  play(E4, minim);
  play(E4, minim);
  play(D4, minim);
  rest(minim);

  //Like a diamond in the sky, G' G' F' F' E' E' D'
  play(G4, minim);
  play(G4, minim);
  play(F4, minim);
  play(F4, minim);
  play(E4, minim);
  play(E4, minim);
  play(D4, minim);
  rest(minim);

  //Twinkle, twinkle, little star, C' C' G' G' A' A' G'
  play(C4, minim);
  play(C4, minim);
  play(G4, minim);
  play(G4, minim);
  play(A4, minim);
  play(A4, minim);
  play(G4, minim);
  rest(minim);

  //How I wonder what you are, F' F' E' E' D' D' C'
  play(F4, minim);
  play(F4, minim);
  play(E4, minim);
  play(E4, minim);
  play(D4, minim);
  play(D4, minim);
  play(C4, minim);

  rest(crot);

  set_tempo(default_tempo);  // reset tempo
}

void jingle_bells() {
  set_tempo(default_tempo * 2); // very lively

  play(B3, crot);
  play(B3, crot);
  play(B3, minim);

  play(B3, crot);
  play(B3, crot);
  play(B3, minim);

  play(B3, crot);
  play(D4, crot);
  play(G3, crot);
  play(A3, crot);

  play(B3, semib);

  play(C4, crot);
  play(C4, crot);
  play(C4, crot);
  play(C4, crot);

  play(C4, crot);
  play(B3, crot);
  play(B3, crot);
  play(B3, crot);

  play(B3, crot);
  play(A3, crot);
  play(A3, crot);
  play(B3, crot);

  play(A3, minim);
  play(D4, minim);

  play(B3, crot);
  play(B3, crot);
  play(B3, minim);

  play(B3, crot);
  play(B3, crot);
  play(B3, minim);

  play(B3, crot);
  play(D4, crot);
  play(G3, crot);
  play(A3, crot);

  play(B3, semib);

  play(C4, crot);
  play(C4, crot);
  play(C4, crot);
  play(C4, crot);

  play(C4, crot);
  play(B3, crot);
  play(B3, crot);
  play(B3, crot);

  play(D4, crot);
  play(D4, crot);
  play(C4, crot);
  play(A3, crot);

  play(G3, semib);

  set_tempo(default_tempo); // reset tempo
}

void happy_birthday() {
  play(G3, quav);
  play(G3, quav);
  play(A3, crot);
  play(G3, crot);

  play(C4, crot);
  play(B3, minim);

  play(G3, quav);
  play(G3, quav);
  play(A3, crot);
  play(G3, crot);

  play(D4, crot);
  play(C4, minim);

  play(G3, quav);
  play(G3, quav);
  play(G4, crot);
  play(E4, crot);

  play(C4, crot);
  play(B3, crot);
  play(A3, crot);

  play(F4, quav);
  play(F4, quav);
  play(E4, crot);
  play(C4, crot);

  play(D4, crot);
  play(C4, minim);

  rest(crot);
}

void ditty_1() {
  set_tempo(default_tempo * 2); // lively pace

  play(C4, minim);
  play(G3, crot);
  play(G3, crot);
  play(GS3, minim);
  play(G3, minim);
  rest(crot + quav);
  play(B3, minim);
  play(C4, crot);

  rest(crot);

  set_tempo(default_tempo); // reset tempo
}

void door_bell_1() {
  play(E4, minim);
  play(C4, minim);
  play(D4, minim);
  play(G3, minim);

  rest(minim);

  play(G3, minim);
  play(D4, minim);
  play(E4, minim);
  play(C4, minim);

  rest(crot);
}

void door_bell_2() {// basic bing/bong door chime
  set_tempo(default_tempo * 2); // lively pace

  play(E5, dot_minim);
  play(C5, dot_minim);

  rest(dot_minim);

  play(E5, dot_minim);
  play(C5, dot_minim);

  rest(crot);

  set_tempo(default_tempo);   // reset tempo
}

void ode_to_joy() {
  set_tempo(allegro);

  //bar 1 - B B C' D'
  play(B3, crot);
  play(B3, crot);
  play(C4, crot);
  play(D4, crot);
  //bar 2 - D' C' B A
  play(D4, crot);
  play(C4, crot);
  play(B3, crot);
  play(A3, crot);
  //bar 3 - G G A B
  play(G3, crot);
  play(G3, crot);
  play(A3, crot);
  play(B3, crot);
  //bar 4 - B. AQ AM
  play(B3, crot + quav);
  play(A3, quav);
  play(A3, minim);
  //bar 5 - B B C' D'
  play(B3, crot);
  play(B3, crot);
  play(C4, crot);
  play(D4, crot);
  //bar 6 - D' C' B A
  play(D4, crot);
  play(C4, crot);
  play(B3, crot);
  play(A3, crot);
  //bar 7 - G G A B
  play(G3, crot);
  play(G3, crot);
  play(A3, crot);
  play(B3, crot);
  //bar 8 - A. GQ GM
  play(A3, crot + quav);
  play(G3, quav);
  play(G3, minim);
  //
  //bar 9 - A A B G
  play(A3, crot);
  play(A3, crot);
  play(B3, crot);
  play(G3, crot);
  //bar 10 - A BQ C'Q B G
  play(A3, crot);
  play(B3, quav);
  play(C4, quav);
  play(B3, crot);
  play(G3, crot);
  //bar 11 - A BQ C'Q B A
  play(A3, crot);
  play(B3, quav);
  play(C4, quav);
  play(B3, crot);
  play(A3, crot);
  //bar 12 - G A DM
  play(G3, crot);
  play(A3, crot);
  play(D3, minim);
  //
  //bar 13 - B B C' D'
  play(B3, crot);
  play(B3, crot);
  play(C4, crot);
  play(D4, crot);
  //bar 14 - D' C' B A
  play(D4, crot);
  play(C4, crot);
  play(B3, crot);
  play(A3, crot);
  //bar 15 - G G A B
  play(G3, crot);
  play(G3, crot);
  play(A3, crot);
  play(B3, crot);
  //bar 16 - A. GQ GM
  play(A3, crot + quav);
  play(G3, quav);
  play(G3, minim);
  rest(minim);
}

//
// MLWB additional music scores....
//

void penny_lane() {
  // key of G Major, arranged by D F Smith
  set_tempo(110);
  //intro bar, 1.1 ................
  play(D5, crot / 3);
  play(G5, crot / 3);
  play(A5, crot / 3);

  // D S al Coda point
  // bar 1.2
  play(B5, quav);
  play(A5, quav);
  play(G5, quav);
  play(FS5, quav);
  play(G5, quav);
  play(FS5, quav);
  play(E5, quav);
  play(D5, quav);
  // bar 1.3
  play(E5, quav);
  play(D5, quav);
  play(C5, crot);
  rest(quav);
  play(D5, quav);
  play(G5, quav);
  play(A5, quav);
  // bar 2.1 ...................
  play(B5, quav);
  play(A5, quav);
  play(G5, quav);
  play(FS5, quav);
  play(G5, quav);
  play(D5, quav);
  play(E5, quav);
  play(G5, quav);
  // bar 2.2
  play(F5, minim);
  rest(quav);
  play(D5, quav);
  play(G5, quav);
  play(A5, quav);
  // bar 2.3
  play(A5, quav);
  play(G5, quav);
  play(G5, quav);
  play(G5, quav);
  play(G5, quav);
  play(A5, crot + quav);
  // bar 2.4
  play(AS5, dot_minim);
  play(G5, quav);
  play(A5, quav);
  // bar 3.1 .................
  play(AS5, quav);
  play(G5, quav);
  play(A5, dot_minim);
  // bar 3.2
  play(A5, crot);
  play(D5, minim);
  play(D5, crot / 3);
  play(G5, crot / 3);
  play(A5, crot / 3);
  // bar 3.3 : start of 1st repeat
  play(B5, quav);
  play(A5, quav);
  play(G5, quav);
  play(FS5, quav);
  play(G5, quav);
  play(FS5, quav);
  play(E5, quav);
  play(D5, quav);
  // bar 4.1 ..............
  play(E5, quav);
  play(D5, quav);
  play(C5, crot);
  rest(quav);
  play(D5, quav);
  play(G5, quav);
  play(A5, quav);
  // bar 4.2
  play(B5, quav);
  play(A5, quav);
  play(G5, quav);
  play(FS5, quav);

  play(G5, quav);
  play(D5, quav);
  play(E5, quav);
  play(G5, quav);
  // bar 4.3
  play(F5, minim);
  rest(quav);
  play(D5, quav);
  play(G5, quav);
  play(A5, quav);
  // bar 5.1 .....................
  play(A5, quav);
  play(G5, quav);
  play(G5, quav);
  play(G5, quav);

  play(G5, quav);

  play(A5, crot + quav);
  // bar 5.2
  play(AS5, dot_minim);
  play(G5, quav);
  play(A5, quav);
  // bar 5.3
  play(AS5, quav);
  play(G5, quav);
  play(A5, dot_minim);
  // bar 5.4
  play(A5, quav);
  play(E5, quav);
  play(G5, minim);

  // chorus...
  play(A5, quav);
  play(AS5, quav);
  // bar 5.5
  play(C6, crot + quav);
  play(AS5, quav);
  play(A5, quav);
  play(AS5, crot + quav);
  // bar 6.1 .....................
  play(C6, crot + quav);
  play(AS5, quav);
  play(A5, quav);
  play(G5, crot + quav);
  // bar 6.2/6.3
  play(F5, semib + semib );
  // bar 6.4
  play(C6, crot + quav);
  play(AS5, quav);
  play(A5, quav);
  play(AS5, crot + quav);
  // bar 6.5
  play(C6, crot + quav);
  play(AS5, quav);
  play(A5, quav);
  play(G5, crot + quav);
  // bar 6.6
  play(F5, crot);
  play(G5, crot);
  play(A5, crot);
  play(AS5, crot);
  // bar 7.1
  play(A5, crot);
  play(FS5, crot);
  play(D5, quav);
  play(D5, quav);
  play(G5, quav);
  play(A5, quav);
  // *************************************
  // repeat from :
  // bar 3.3
  play(B5, quav);
  play(A5, quav);
  play(G5, quav);
  play(FS5, quav);
  play(G5, quav);
  play(FS5, quav);
  play(E5, quav);
  play(D5, quav);
  // bar 4.1 ..............
  play(E5, quav);
  play(D5, quav);
  play(C5, crot);
  rest(quav);
  play(D5, quav);
  play(G5, quav);
  play(A5, quav);
  // bar 4.2
  play(B5, quav);
  play(A5, quav);
  play(G5, quav);
  play(FS5, quav);
  play(G5, quav);
  play(D5, quav);
  play(E5, quav);
  play(G5, quav);
  // bar 4.3
  play(F5, minim);
  rest(quav);
  play(D5, quav);
  play(G5, quav);
  play(A5, quav);
  // bar 5.1 .....................
  play(A5, quav);
  play(G5, quav);
  play(G5, quav);
  play(G5, quav);
  play(G5, quav);
  play(A5, crot + quav);
  // bar 5.2
  play(AS5, dot_minim);
  play(G5, quav);
  play(A5, quav);
  // bar 5.3
  play(AS5, quav);
  play(G5, quav);
  play(A5, dot_minim);
  // bar 5.4
  play(A5, quav);
  play(E5, quav);
  play(G5, minim);

  // chorus...
  play(A5, quav);
  play(AS5, quav);
  // bar 5.5
  play(C6, crot + quav);
  play(AS5, quav);
  play(A5, quav);
  play(AS5, crot + quav);
  // bar 6.1 .....................
  play(C6, crot + quav);
  play(AS5, quav);
  play(A5, quav);
  play(G5, crot + quav);
  // bar 6.2/6.3
  play(F5, semib + semib );
  // bar 6.4
  play(C6, crot + quav);
  play(AS5, quav);
  play(A5, quav);
  play(AS5, crot + quav);
  // bar 6.5
  play(C6, crot + quav);
  play(AS5, quav);
  play(A5, quav);
  play(G5, crot + quav);
  // bar 6.6
  play(F5, crot);
  play(G5, crot);
  play(A5, crot);
  play(AS5, crot);
  // bar 7.1
  play(A5, crot);
  play(FS5, crot);
  play(D5, quav);
  play(D5, quav);
  play(G5, quav);
  play(A5, quav);
  // **********************************
  // al coda repeat
  // D S al Coda point
  // bar 1.2
  play(B5, quav);
  play(A5, quav);
  play(G5, quav);
  play(FS5, quav);
  play(G5, quav);
  play(FS5, quav);
  play(E5, quav);
  play(D5, quav);
  // bar 1.3
  play(E5, quav);
  play(D5, quav);
  play(C5, crot);
  rest(quav);
  play(D5, quav);
  play(G5, quav);
  play(A5, quav);
  // bar 2.1 ...................
  play(B5, quav);
  play(A5, quav);
  play(G5, quav);
  play(FS5, quav);
  play(G5, quav);
  play(D5, quav);
  play(E5, quav);
  play(G5, quav);
  // bar 2.2
  play(F5, minim);
  rest(quav);
  play(D5, quav);
  play(G5, quav);
  play(A5, quav);
  // bar 2.3
  play(A5, quav);
  play(G5, quav);
  play(G5, quav);
  play(G5, quav);
  play(G5, quav);
  play(A5, crot + quav);
  // bar 2.4
  play(AS5, dot_minim);
  play(G5, quav);
  play(A5, quav);
  // bar 3.1 .................
  play(AS5, quav);
  play(G5, quav);
  play(A5, dot_minim);
  // bar 3.2
  play(A5, crot);
  play(D5, minim);
  play(D5, crot / 3);
  play(G5, crot / 3);
  play(A5, crot / 3);
  // bar 3.3
  play(B5, quav);
  play(A5, quav);
  play(G5, quav);
  play(FS5, quav);
  play(G5, quav);
  play(FS5, quav);
  play(E5, quav);
  play(D5, quav);
  // bar 4.1 ..............
  play(E5, quav);
  play(D5, quav);
  play(C5, crot);
  rest(quav);
  play(D5, quav);
  play(G5, quav);
  play(A5, quav);
  // bar 4.2
  play(B5, quav);
  play(A5, quav);
  play(G5, quav);
  play(FS5, quav);
  play(G5, quav);
  play(D5, quav);
  play(E5, quav);
  play(G5, quav);
  // bar 4.3
  play(F5, minim);
  rest(quav);
  play(D5, quav);
  play(G5, quav);
  play(A5, quav);
  // bar 5.1 .....................
  play(A5, quav);
  play(G5, quav);
  play(G5, quav);
  play(G5, quav);
  play(G5, quav);
  play(A5, crot + quav);
  // bar 5.2
  play(AS5, dot_minim);
  play(G5, quav);
  play(A5, quav);
  // bar 5.3
  play(AS5, quav);
  play(G5, quav);
  play(A5, dot_minim);
  // bar 5.4
  play(A5, quav);
  play(E5, quav);
  play(G5, minim);

  // chorus...
  play(A5, quav);
  play(AS5, quav);
  // bar 5.5
  play(C6, crot + quav);
  play(AS5, quav);
  play(A5, quav);
  play(AS5, crot + quav);
  // bar 6.1 .....................
  play(C6, crot + quav);
  play(AS5, quav);
  play(A5, quav);
  play(G5, crot + quav);
  // bar 6.2/6.3
  play(F5, semib + semib );
  // bar 6.4
  play(C6, crot + quav);
  play(AS5, quav);
  play(A5, quav);
  play(AS5, crot + quav);
  // bar 6.5
  play(C6, crot + quav);
  play(AS5, quav);
  play(A5, quav);
  play(G5, crot + quav);
  // bar 6.6
  play(F5, crot);
  play(G5, crot);
  play(A5, crot);
  play(AS5, crot);
  // bar 7.1
  play(A5, crot);
  play(FS5, crot);
  play(D5, quav);// 1/3?
  play(D5, quav);// 1/3?
  play(G5, quav);
  play(A5, quav);
  // ******************************************

  // continuing from D S al coda
  // bar 7.3
  play(A5, crot);
  play(FS5, crot);
  play(D5, crot);
  play(B5, quav);
  play(C6, quav);
  // bar 7.4
  play(D6, crot + quav);
  play(C6, quav);
  play(B5, quav);
  play(C6, crot + quav);
  // bar 8.1
  play(D6, crot + quav);
  play(C6, quav);
  play(B5, quav);
  play(A5, crot + quav);
  // bar 8.2/8.3
  play(G5, semib + semib);
  // bar 8.4
  play(D6, crot + quav);
  play(C6, quav);
  play(B5, quav);
  play(C6, crot + quav);
  // bar 8.5
  play(D6, crot + quav);
  play(C6, quav);
  play(B5, quav);
  play(A5, crot + quav);
  // bar 8.6/8.7
  play(G5, semib + semib);
  // bar 9.1
  rest(minim);
  play(D6, quav);
  play(B5, quav);
  play(D6, quav);
  play(A5, quav);
  // bar 9.2
  play(B5, semib);
}


void yesterday() {
  int pass = 0;
  set_tempo(98);
  ////bar 1
  //rest(semib);
  ////bar 2
  //rest(semib);
  //bar 3
  play(G3, quav);
  play(F3, quav / 2);
  play(F3, quav / 2 + minim);
  rest(crot);
  //bar 4
  play(A3, quav);
  play(B3, quav);
  play(CS4, quav / 2);
  play(D4, quav * 1.5);
  play(E4, quav);
  play(F4, quav);
  // bar 5
  play(E4, crot + quav);
  play(D4, quav);
  play(D4, minim);
  // bar 6
  rest(crot);
  play(D4, quav / 2);
  play(D4, quav * 1.5);
  play(C4, quav);
  play(AS3, quav);
  play(A3, quav);
  play(G3, quav);
  // bar 7
  play(AS3, crot);
  play(A3, quav);
  play(A3, quav + crot);
  rest(quav);
  play(G3, quav);
  // bar 8
  play(F3, crot);
  play(A3, quav);
  play(G3, quav + crot);
  rest(quav);
  play(D3, quav);
  // bar 9
  play(F3, crot);
  play(A3, quav);
  play(A3, quav + crot);
  rest(quav);
repeat:
  //bar 10 - start of repeat
  play(G3, quav / 2);
  play(F3, quav / 2);
  play(F3, quav + crot);
  rest(minim);
  // bar 11
  rest(crot);
  play(A3, quav);
  play(B3, quav);
  play(CS4, quav);
  play(D4, quav);
  play(E4, quav);
  play(F4, quav);
  // bar 12
  play(E4, quav * 1.5);
  play(D4, quav / 2);
  play(D4, minim);
  rest(crot);
  // bar 13
  rest(crot);
  play(D4, quav / 2);
  play(D4, quav * 1.5);
  play(C4, quav / 2);
  play(AS3, quav * 1.5);
  play(A3, quav);
  play(G3, quav);
  // bar 14
  play(AS3, crot);
  play(A3, quav);
  play(A3, quav + crot);
  rest(quav);
  play(G3, quav);
  // bar 15
  play(F3, crot);
  play(A3, quav);
  play(G3, quav + crot);
  rest(quav);
  play(D3, quav);
  // bar 16
  play(F3, crot);
  play(A3, quav);
  play(A3, quav + crot); // tie into bar 17
  rest(crot);
  // bar 17
  play(A3, minim);
  play(A3, minim);
  // bar 18
  play(D4, crot);
  play(E4, crot);
  play(F4, crot);
  play(E4, quav);
  play(D4, quav + quav);
  // bar 19
  play(E4, crot);
  play(D4, quav);
  play(C4, crot);
  play(D4, quav);
  play(A3, quav + minim); // tie into bar 20
  // bar 20
  rest(minim);
  // bar 21
  play(A3, minim);
  play(A3, minim);
  // bar 22
  play(D4, crot);
  play(E4, crot);
  play(F4, crot);
  play(E4, quav);
  play(D4, quav + quav); // tie into bar 23
  // bar 23
  play(E4, crot);
  play(D4, quav);
  play(C4, crot);
  play(E4, crot);
  //bar 24
  play(F4, minim + crot);
  rest(crot);
  if (pass == 0) {
    pass = 1;
    goto repeat; // repeat from bar 10
  }
  // bar 25
  play(F4, crot); // sould tie to 4th crot of this bar
  play(C4, crot);
  play(AS3, crot);
  play(A3, crot);
  // bar 26
  play(G3, quav);
  play(F3, quav / 2);
  play(F3, quav / 2 + minim);
  rest(crot);
  // bar 27
  rest(crot);
  play(A3, quav);
  play(B3, quav);
  play(CS4, quav);
  play(D4, quav / 2);
  play(E4, quav / 2 + quav);
  play(F4, quav);
  // bar 28
  play(E4, crot);
  play(D4, quav);
  play(D4, quav + minim);
  // bar 29
  rest(crot);
  play(D4, quav);
  play(D4, quav);
  play(C4, quav);
  play(AS3, quav);
  play(A3, quav);
  play(G3, quav);
  // bar 30
  play(AS3, crot);
  play(A3, quav);
  play(A3, quav + crot);
  rest(quav);
  play(G3, quav);
  // bar 31
  play(F3, crot);
  play(A3, quav);
  play(G3, quav + crot);
  rest(quav);
  play(D3, quav);
  //  bar 32
  play(F3, crot);
  play(A3, quav);
  play(A3, quav + crot);
  rest(crot);
  // bar 33
  play(F3, crot);// should be tied to D3 this bar
  play(A3, crot);
  play(G3, crot);
  play(D3, crot);
  // bar 34
  play(F3, crot);
  play(A3, quav);
  play(A3, quav + crot);
  rest(crot);
}

void annies_song() {
  int pass = 0;
  set_tempo(allegro);
  // bars 1-6 intro, ignored
  // bar 7
  rest(crot);
  rest(crot);
  play(D4, crot);
  // bar 8
  play(D4, crot);
  play(CS4, crot);
  play(B3, crot);
  // bar 9
  play(D4, dot_minim);
  // bar 10
  play(CS4, dot_minim + minim); // into bar 11
  //bar 11
  play(B3, quav);
  play(B3, quav);
  // bar 12
  play(B3, crot);
  play(CS4, crot);
  play(D4, crot);
  //bar 13, 14 and into 15
  play(A3, crot);
  play(FS3, minim + dot_minim + minim);
  //bar 15
  play(A3, quav);
  play(A3, quav);
  // bar 16
  play(A3, crot);
  play(B3, crot);
  play(CS4, crot);
  // bar 17
  play(D4, dot_minim);
  // bar 18 and into 19
  play(CS4, dot_minim + minim); // into bar 19
  // bar 19
  play(B3, quav);
  play(B3, quav);
  //bar 20
  play(B3, crot);
  play(CS4, crot);
  play(D4, crot);
  // bar 21/22 and into 23
  play(CS4, dot_minim + dot_minim + crot);
  rest(crot);
  play(D4, quav);
  play(D4, quav);
  // bar 24
  play(D4, crot);
  play(CS4, crot);
  play(B3, crot);
  // bar 25
  play(D4, dot_minim);
  // bar 26 and into 27
  play(CS4, dot_minim + minim); //into bar 27
  play(B3, quav);
  play(B3, quav);
  // bar 28
  play(B3, crot);
  play(CS4, crot);
  play(D4, crot);
  // bar 29 and 30 and into 31
  play(A3, crot);
  play(FS3, minim + dot_minim + quav);
  // bar 31
  rest(crot);
  play(A3, crot);
  // bar 32
  play(A3, crot);
  play(B3, crot);
  play(CS4, crot);
  // bar 33
  play(D4, dot_minim);
  // bar 34 and into 35
  play(CS4, dot_minim + minim); // into 35
  // bar 35
  play(B3, crot);
  // bar 36
  play(CS4, crot);
  play(D4, crot);
  play(E4, crot);
  // bar 37 and 38
  play(D4, dot_minim + dot_minim + crot); // into 39
  rest(crot);
  rest(crot);
  // bar 40
  play(D4, crot);
  play(CS4, crot);
  play(B3, crot);
repeat:
  // bar 41
  play(D4, dot_minim);
  // bar 42 and into 43
  play(CS4, dot_minim + minim);
  // bar 43
  play(B3, quav);
  play(B3, quav);
  // bar 44
  play(B3, crot);
  play(CS4, crot);
  play(D4, crot);
  // bar 45, 46 and into 47
  play(A3, crot);
  play(FS3, minim + dot_minim + crot);
  // bar 47
  rest(crot);
  play(A3, quav);
  play(A3, quav);
  // bar 48
  play(A3, crot);
  play(B3, crot);
  play(CS4, crot);
  // bar 49
  play(D4, dot_minim);
  // bar 50 into 51
  play(CS4, dot_minim + minim);
  // bar 51
  play(B3, quav);
  play(B3, quav);
  // bar 52
  play(B3, crot);
  play(CS4, crot);
  play(D4, crot);
  // bar 53, 54 into 55
  play(E4, dot_minim + dot_minim + minim);
  // bar 55
  play(D4, quav);
  play(D4, quav);
  // bar 56
  play(D4, crot);
  play(CS4, crot);
  play(B3, crot);
  // bar 57
  play(D4, dot_minim);
  // bar 58 into 59
  play(E4, dot_minim + minim);
  // bar 59
  play(D4, quav);
  play(D4, quav);
  // bar 60
  play(D4, crot);
  play(CS4, crot);
  play(B3, crot);
  // bar 61, 62 into 63
  play(A3, crot);
  play(FS3, minim + dot_minim + minim);
  // bar 63
  rest(crot);
  // bar 64
  play(A3, crot);
  play(B3, crot);
  play(CS4, crot);
  // bar 65
  play(D4, dot_minim);
  // bar 66 into 67
  play(CS4, dot_minim + minim);
  //bar 67
  play(B3, crot);
  // bar 68
  play(CS4, crot);
  play(D4, crot + quav);
  play(E4, quav);
  if (pass == 0) {
    // bar 69, 70 into 71
    play(D4, dot_minim + dot_minim + crot);
    // bar 71
    rest(crot);
    play(D4, crot);
    // bar 72
    play(D4, crot);
    play(CS4, crot);
    play(B3, crot);
    if (pass == 0) {
      pass = 1;
      goto repeat;
    }
  }
  // continue from bar 73 after repeat
  // bar 73, 74, 75 and 76
  play(D4, dot_minim + dot_minim + dot_minim + dot_minim);
  // bar 77
  rest(semib);
  // bar 78
  rest(semib);
}

void black_velvet_band() {
  int pass = 0;
  set_tempo(170); // briskly
  // bar 1 - intro
  play(G4, quav);
  play(G4, quav);
  // bar 2
  play(G4, crot);
  play(G4, crot);
  play(G4, crot);
  // bar 3
  play(E4, crot);
  play(F4, crot);
  play(G4, crot);
  // bar 4 into 5
  play(F4, crot);
  play(E4, minim + crot);
  // bar 5
  rest(crot);
  play(D4, crot);
  // bar 6
  play(C4, crot);
  play(D4, crot);
  play(E4, crot);
  // bar 7
  play(C4, crot);
  play(B3, crot);
  play(A3, crot);
  // bar 8 into 9
  play(G3, dot_minim + crot);
  // bar 9
  play(G4, crot);
  play(F4, crot);
  // bar 10
  play(E4, crot);
  play(E4, crot);
  play(E4, crot);
  // bar 11
  play(G3, crot);
  play(A3, crot);
  play(B3, crot);
  // bar 12
  play(C4, minim);
  play(D4, crot);
  // bar 13
  play(E4, minim);
  play(C4, quav);
  play(C4, quav);
  // bar 14
  play(D4, crot);
  play(E4, crot);
  play(F4, crot);
  // bar 15
  play(B3, crot);
  play(C4, crot);
  play(D4, crot);
  // bar 16 into 17
  play(C4, dot_minim + crot);
  // bar 17
  rest(crot);
  play(G4, crot);
  // bar 18
  play(G4, minim);
  play(G4, crot);
  // bar 19
  play(E4, crot);
  play(F4, crot);
  play(G4, crot);
  // bar 20
  play(F4, minim);
  play(F4, crot);
  // bar 21
  play(E4, minim);
  play(D4, crot);
  // bar 22
  play(C4, crot);
  play(D4, crot);
  play(E4, crot);
  // bar 23
  play(C4, crot);
  play(B3, crot);
  play(A3, crot);
  // bar 24 into 25
  play(G3, dot_minim + crot);
  // bar 25
  rest(crot);
  play(G4, quav);
  play(G4, quav);
  // bar 26
  play(E4, crot);
  play(E4, crot);
  play(E4, crot);
  // bar 27
  play(G3, crot);
  play(A3, crot);
  play(B3, crot);
  // bar 28
  play(C4, minim);
  play(D4, crot);
  // bar 29
  play(E4, minim);
  play(C4, crot);
  // bar 30
  play(D4, crot);
  play(E4, crot);
  play(F4, crot);
  // bar 31
  play(B3, crot);
  play(C4, crot);
  play(D4, crot);
  // bar 32 into 33
  play(C4, dot_minim + crot);
  // bar 33
  rest(crot);
  play(G4, crot);
repeat:
  // bar 34
  play(G4, minim);
  play(G4, crot);
  // bar 35
  play(E4, crot);
  play(F4, crot);
  play(G4, crot);
  // bar 36 into 37
  play(F4, crot);
  play(E4, minim + crot);
  // bar 37
  rest(crot);
  play(D4, crot);
  // bar 38
  play(C4, crot);
  play(D4, crot);
  play(E4, crot);
  // bar 39
  play(C4, crot);
  play(B3, crot);
  play(A3, crot);
  // bar 40 into 41
  play(G3, dot_minim + crot);
  // bar 41
  play(G4, crot);
  play(G4, crot);
  // bar 42
  play(E4, minim);
  play(E4, crot);
  // bar 43
  play(G3, crot);
  play(A3, crot);
  play(B3, crot);
  // bar 44
  play(C4, minim);
  play(D4, crot);
  // bar 45
  play(E4, minim);
  play(C4, crot);
  // bar 46
  play(D4, crot);
  play(E4, crot);
  play(F4, crot);
  // bar 47
  play(B3, crot);
  play(C4, crot);
  play(D4, crot);
  // bar 48 into 49
  play(C4, dot_minim);
  if (pass == 1)goto finish;
  // bar 49
  rest(crot);
  play(G4, crot);
  if (pass == 0) {
    pass = 1;
    goto repeat;
  }
  // bar 50
finish:
  play(C4, crot);
  rest(crot);
  rest(crot);
}
