#include "musicClip.h"
#define TML_IMPLEMENTATION
#define TSF_IMPLEMENTATION
#include <tml.h>
#include <tsf.h>
#include <iostream>

tsf* MusicClip::g_TinySoundFont;
tml_message* MusicClip::g_MidiMessage = NULL;
tml_message* MusicClip::g_MidiMessageStart = NULL;
double MusicClip::g_Msec = 0;

SDL_mutex* MusicClip::mutex = NULL;

int MusicClip::repeatFlag = 0;

SDL_AudioSpec MusicClip::OutputAudioSpec;

MusicClip::MusicClip(std::string _filePath)
    : path(_filePath)
{
    //Load music
    music = tml_load_filename(_filePath.c_str());
    //music = Mix_LoadMUS(path.c_str());
    if (music == NULL)
    {
        printf("Failed to load midi file");
        //printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

MusicClip::~MusicClip()
{
    if (music)
        tml_free(music);
}

// Callback function called by the audio thread, function provided by Bernhard Scheilling in examples for TinySoundFont https://github.com/schellingb/TinySoundFont.
//License is provided below
/* Copyright (C) 2017-2018 Bernhard Schelling (Based on SFZero, Copyright (C) 2012 Steve Folta, https://github.com/stevefolta/SFZero)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/
void MusicClip::AudioCallback(void* data, uint8_t *stream, int len)
{
    if (SDL_LockMutex(mutex) == 0) {

        //Number of samples to process
        int SampleBlock, SampleCount = (len / (2 * sizeof(float))); //2 output channels
        for (SampleBlock = TSF_RENDER_EFFECTSAMPLEBLOCK; SampleCount; SampleCount -= SampleBlock, stream += (SampleBlock * (2 * sizeof(float))))
        {

            //We progress the MIDI playback and then process TSF_RENDER_EFFECTSAMPLEBLOCK samples at once
            if (SampleBlock > SampleCount) SampleBlock = SampleCount;

            //Loop through all MIDI messages which need to be played up until the current playback time
            for (g_Msec += SampleBlock * (1000.0 / 44100.0); g_MidiMessage && g_Msec >= g_MidiMessage->time; g_MidiMessage = g_MidiMessage->next)
            {
                switch (g_MidiMessage->type)
                {
                case TML_PROGRAM_CHANGE: //channel program (preset) change (special handling for 10th MIDI channel with drums)
                    tsf_channel_set_presetnumber(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->program, (g_MidiMessage->channel == 9));
                    break;
                case TML_NOTE_ON: //play a note
                    tsf_channel_note_on(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->key, g_MidiMessage->velocity / 127.0f);
                    break;
                case TML_NOTE_OFF: //stop a note
                    tsf_channel_note_off(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->key);
                    break;
                case TML_PITCH_BEND: //pitch wheel modification
                    tsf_channel_set_pitchwheel(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->pitch_bend);
                    break;
                case TML_CONTROL_CHANGE: //MIDI controller messages
                    tsf_channel_midi_control(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->control, g_MidiMessage->control_value);
                    break;
                }
            }

            // Render the block of audio samples in float format
            tsf_render_float(g_TinySoundFont, (float*)stream, SampleBlock, 0);

            //Should midi-clip repeat?
            if (!g_MidiMessage && (repeatFlag > 0 || repeatFlag == -1)) {
                g_MidiMessage = g_MidiMessageStart;
                g_Msec = 0;
                if (repeatFlag > 0) repeatFlag--;
            }
        }

        SDL_UnlockMutex(mutex);
    }
}


void MusicClip::play(int repeat) const
{
    if (SDL_LockMutex(mutex) == 0) {

        for (int i = 0; i < 128; i++) {
            tsf_channel_midi_control(g_TinySoundFont, i, TML_ALL_SOUND_OFF, 0);
        }

        repeatFlag = repeat;

        //Set up the global MidiMessage pointer to the first MIDI message
        g_MidiMessage = music;
        g_MidiMessageStart = music;
        g_Msec = 0;
        SDL_UnlockMutex(mutex);
    }

    // Start the actual audio playback here
    // The audio thread will begin to call our AudioCallback function
    SDL_PauseAudio(0);

    //Wait until the entire MIDI file has been played back (until the end of the linked message list is reached)
    //while (g_MidiMessage != NULL) SDL_Delay(100);

    // We could call tsf_close(g_TinySoundFont) and tml_free(TinyMidiLoader)
    // here to free the memory and resources but we just let the OS clean up
    // because the process ends here.
}

void MusicClip::stop()
{
    if (SDL_LockMutex(mutex) == 0) {
        g_MidiMessage = NULL;
        g_MidiMessageStart = NULL;

        for (int i = 0; i < 128; i++) {
            tsf_channel_midi_control(g_TinySoundFont, i, TML_ALL_SOUND_OFF, 0);
        }
        SDL_UnlockMutex(mutex);
    }
}

void MusicClip::pause()
{
    if (SDL_LockMutex(mutex) == 0) {

        SDL_PauseAudio(1);

        SDL_UnlockMutex(mutex);
    }
}

void MusicClip::unpause()
{
    if (SDL_LockMutex(mutex) == 0) {

        SDL_PauseAudio(0);

        SDL_UnlockMutex(mutex);
    }
}

bool MusicClip::initialize()
{
    // Define the desired audio output format we request
    OutputAudioSpec.freq = 44100;
    OutputAudioSpec.format = AUDIO_F32;
    OutputAudioSpec.channels = 2;
    OutputAudioSpec.samples = 4096;
    OutputAudioSpec.callback = AudioCallback;

    // Load the SoundFont from a file
    g_TinySoundFont = tsf_load_filename("Assets/Sound/sound_fonts/PRT.SF2");
    if (!g_TinySoundFont)
    {
        fprintf(stderr, "Could not load SoundFont\n");
        return false;
    }

    // Request the desired audio output format
    if (SDL_OpenAudio(&OutputAudioSpec, TSF_NULL) < 0)
    {
        fprintf(stderr, "Could not open the audio hardware or the desired audio output format\n");
        return false;
    }

    // Set the SoundFont rendering output mode
    tsf_set_output(g_TinySoundFont, TSF_STEREO_INTERLEAVED, OutputAudioSpec.freq, 0.0f);

    //Initialize preset on special 10th MIDI channel to use percussion sound bank (128) if available
    tsf_channel_set_bank_preset(g_TinySoundFont, 9, 128, 0);

    mutex = SDL_CreateMutex();

    return true;
}
