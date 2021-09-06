# Lets-Make-Music

**Let's Make Music in a Nut Shell**

If you love Arduino and have a rudimentary understanding of music then why not have some fun with Let's Make Music?

With a very basic kit list and using very few, very short and basic functions, it is possible to craft quite detailed musical scores to play on a simply configured Arduino and speaker. The results can be quite startling and rewarding!

**Origins**

This article, and the accompanying sketch, originates from a previously published article called "Music & Lights Workbench" which I developed to introduce my grandchildren to the concepts of computer programming. We had so much fun in using the Workbench that I have decided to strip it down, remodel and represent it as a sketch exclusively comprising its music elements; one that can be readily used by anyone wishing to explore crafting musical scores on Arduino.

**The Hardware**

Couldn't be simpler - all you will need is an Arduino microcontroller (any should be okay), a 100 ohm resistor, a small bread board, some wires and, preferably, an 8 ohm 0.25 watt speaker (or a buzzer if you don't have a speaker to hand).

The wiring diagram is as shown below at Schematics, but it is a very simple circuit to put together. I should advise that the microcontroller should not be connected to anything but a speaker/buzzer as outlined, otherwise you may damage your microcontroller.

**Capabilities**

To give you some idea of the 'lets make music' sketch capabilities, I crafted several quite complex scores by a number of legendary popular artists all of which played faithfully.  Unfortunately, I am not able to publish these due to copyright.  I have, though, included other examples out-of-the-box (OOTB) which provide helpful demonstrations of capability and guidance to help you get started on your own scores.

**Let's Make Music**

The sketch includes everything needed to put together your own musical scores and compositions using basic and standard musical terms and concepts. For example, the sketch includes a comprehensive set of standard tempos, preset notes covering several octaves and user variable note/rest time values based on the selected tempo.

The sketch provides five functions you can use for creating and playing music. These are:

- **set_tempo** - sets the tempo (pace) of a musical piece in beats per minute (i.e. crotchets per minute), eg set_tempo(allegro), set_tempo(144), etc. The value of a crotchet is calculated as 60/tempo seconds. All other note durations are then determined from this calculated value. At sketch start up, the tempo is set to the default_tempo (animato, or 120 beats (crotchets) per minute). The tempo will remain at this setting until changed by the user code.

- **play** - will play the given note for the given duration, eg play(C4, minim) will play middle C for the duration of a minim, play(FS2, crot + quav) will play F2 sharp for the duration of a crotchet + a quaver, etc.

- **rest** - rests for the given duration, during which time silence is maintained, eg rest(quav), rest(0.5), etc.

- **trill** - performs a trill with the given two notes continually one after the other for the given duration, eg trill(C4, CS4, minim), trill(E3, F3, quav), etc. By default and OOTB, the trill performs eight note changes per crotchet, or part thereof, depending on the trill/note duration given in its function call, irrespective of the tempo set. If fewer or more note changes per crotchet are required then reset the definition 'trills_per_crotchet'.

- **wait** - waits for the given duration (seconds or part thereof) , eg wait(5.5) waits for 5.5 seconds, wait(minim) waits for the duration of a minim, etc. This function is used by the play and rest functions but it is may also for used in the end user code.


Let's look at an example of a familiar tune (Happy Birthday):


 // Happy Birthday
 
 set_tempo(default_tempo);
 
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
 
 
To notice about the above example is:

- the tempo for the score has been set to default_tempo (120 beats per minute)
- the score has been structured in bars. In this example there are three beats to the bar (3/4 time). This is a helpful approach when you are entering your own scores as it allows you to follow the music and easily pick out the incorrect notes and/or time durations that you will undoubtedly introduce in error!
- the notes are played one after the next (single channel design) and reference note values from the sketch's note definitions (see the Crib Sheet for a readily accessible list of these and other useful bits and pieces)
- each note is played for a specified time/duration using standard musical notation, eg crot(chet), minim, quav(er), etc. Again, use the Crib Sheet for easy access to these.

Let's look at another short example, one you will know when you play it:

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


To notice about the above example is:

- we up the tempo to twice the default - 240 beats per minute
- we introduce a short rest in the middle of the piece at bar 3 worth one crot(chet)
- we reset the tempo to default when the piece finishes.

And, finally in this section, let's look back at Happy Birthday, this time we will add a trill at the start of each odd bar:

// Happy trill Birthday

set_tempo(default_tempo);

// 3/4 time

// bar 1

trill(G3, GS3, quav);

play(G3, quav);

play(A3, crot);

play(G3, crot);

// bar 2

play(C4, crot);

play(B3, minim);

// bar 3

trill(G3, GS3, quav);

play(G3, quav);

play(A3, crot);

play(G3, crot);

// bar 4

play(D4, crot);

play(C4, minim);

// bar 5

trill(G3, GS3, quav);

play(G3, quav);

play(G4, crot);

play(E4, crot);

// bar 6

play(C4, crot);

play(B3, crot);

play(A3, crot);

// bar 7

trill(F4, FS4, quav);

play(F4, quav);

play(E4, crot);

play(C4, crot);

// bar 8

play(D4, crot);

play(C4, minim);


It is the same melody we are used to but with a little twist. The trill function is a simple implementation of a trill, but should provide some interest in your scores.

Hopefully, by this point you understand the principles being applied?

**A Few Useful Ideas and Techniques...**

**_Triplets_**

A triplet is a single beat of the score's time signature divided into three notes of equal time duration and is normally indicated by a '3' above the triplet notes. This is easily modelled, for example if we have the following three notes defined as a triplet - A3, AS3 and B3 then we would simply transcribe this as:

// crotchet triplet

play(A3, crot/3);

play(AS3, crot/3); 

play(B3, crot/3);


The same idea would apply for any division.

**_Ties_**

A tied note is a musical notation represented by a curved line that connects two notes of the same pitch. In a tie, the second note is not played but its duration value is added to the first note. So, for example, if a score shows two tied notes, say AF3 with duration of a crotchet and the second also with duration a crotchet then we would represent this as play(AF3, crot + crot), or play(AF3, minim). The first representation is better as it infers we are playing a tied note.

Another example might be two notes, say F4 the first with a duration value of a crotchet and the second with a duration value of a quaver. We would represent this as play(F4, crot + quav). And so on.

**_Compounded Note & Rest Durations_**

We saw in the above techniques how we were able to compound and manipulate note durations to represent the precise needs of a score to represent triplets and ties. This same technique is equally applicable to the rest and trill functions where note durations are required. In fact, any arithmetic combination is permissible so long as it makes sense, for example play(D5, minim + crot + quav), rest(crot + quav), trill(G2, GS2, dot_minim + quav/2), etc.

**_Tempos_**

Whilst the sketch provides a list of standard tempo definitions, any value may be specified by the set_tempo function. So, if you need a tempo that is not in the standard list then simply specify your own. For example set_tempo(95) which is between maestroso (88 beats per minute) and moderato (100 beats per minute), and so on.

**_Repeats_**

Often a section of a score is repeated. Rather than duplicating the same set and series of notes/rests it can be helpful to use labels and the (dreaded) goto statement. To do this it will be necessary to detect if a section of the score has already been repeated or not. This can be managed using a simple variable which has one of two states - 'false' if the repeat section has not yet been repeated and 'true' otherwise. For example:

...

bool repeated = false;

...
repeat_1:

play(B3, crot);

rest(quav);

play(C4, quav);

play(D4, crot+quav);  // dotted crotchet

play(C4, quav);

...

If (repeated == false){

repeated = true; 

play(A3, crot);

rest(crot);

play(C4, crot);

play(D4, crot);

goto repeat;

}

// continue with the rest of the score...


My apologies to the purists amongst you but in this instance the use of a goto is simple, clear and easily implemented, even with scores having multiple repeated sections.

**_Transcribing a Score_**

It helps to be neat and tidy when coding a musical score into commands. Work bar by bar according to the score's time signature, commenting each bar with its bar number and adding any other comments that may be helpful. This approach assists in debugging your code as I can guarantee that you will introduce incorrect notes and/or note/rest durations. Listening to the score playing for accuracy whilst reading through the code bar by bar soon identifies where things are wrong.

**Out of the Box**

The Let's Make Music sketch includes all of the musical data and functions needed to put together your own scores. Also included are a number of musical score examples so you can see how the various functions are used and also so that you may play music on your Arduino straight away. 
The example scores are provided as functions, for convenience, and may be referenced directly from the main void loop in any order. If assembling several score functions, one after the other, then add a wait(..) function call between each so that you get a short break between one ending and the next starting, eg wait(3) will wait for three seconds.

The music score functions provided OOTB are:

- middle_C
- twinkle_twinkle (little star)
- silent_night
- jingle_bells
- happy_birthday
- ditty_1
- door_bell_1
- door_bell_2
- ode_to_joy (Beethoven)
- canon_in_D (Pachelbel)


**Finally**

The Let's Make Music sketch is all about having some fun making music with Arduino. It is not overly sophisticated, but provides a few simple and basic commands that yield very good results. Download the Crib Sheet as a handy and quick reference to all of the sketch's musical data definitions and functions.

Above all, enjoy making music on Arduino and have fun!
