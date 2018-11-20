#pragma once
#include <string>
#include <SDL.h>

struct tml_message;
struct tsf;

class MusicClip {
public:
    //Create musicClip from file at file path. Only supports .mid currently
    MusicClip(std::string _filePath = "Assets/Sound/music/default/default.mid");
    ~MusicClip();

    //initialize audio output, should be called by soundManager
    static bool initialize();

    //Plays this clip
    void play(int repeat = -1) const;
    //Stops currently playing clip
    static void stop();
    //Pauses currently playing clip. The clip may be resumed
    static void pause();
    //Unpauses the currently paused clip
    static void unpause();

private:
    //Protects critical function AudioCallback
    static SDL_mutex* mutex;

    tml_message *music;
    //path where music is stored
    const std::string path;

    // Holds the global instance pointer
    static tsf* g_TinySoundFont;
    // Holds global MIDI playback state
    static double g_Msec;               //current playback time
    static tml_message* g_MidiMessageStart; //start of most recently played musicClip
    static tml_message* g_MidiMessage;  //next message to be played

    //Audio output
    static SDL_AudioSpec OutputAudioSpec;

    //Tells AudioCallback() how many times to repeat. 
    static int repeatFlag;

    static void AudioCallback(void* data, uint8_t *stream, int len);
};
