/************************************************************************
 *                                                                      *
 *  FreeSynd - a remake of the classic Bullfrog game "Syndicate".       *
 *                                                                      *
 *   Copyright (C) 2005  Stuart Binge  <skbinge@gmail.com>              *
 *   Copyright (C) 2005  Joost Peters  <joostp@users.sourceforge.net>   *
 *   Copyright (C) 2006  Trent Waddington <qg@biodome.org>              *
 *   Copyright (C) 2006  Tarjei Knapstad <tarjei.knapstad@gmail.com>    *
 *   Copyright (C) 2010  Benoit Blancard <benblan@users.sourceforge.net>*
 *                                                                      *
 *    This program is free software;  you can redistribute it and / or  *
 *  modify it  under the  terms of the  GNU General  Public License as  *
 *  published by the Free Software Foundation; either version 2 of the  *
 *  License, or (at your option) any later version.                     *
 *                                                                      *
 *    This program is  distributed in the hope that it will be useful,  *
 *  but WITHOUT  ANY WARRANTY;  without even  the implied  warranty of  *
 *  MERCHANTABILITY  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  *
 *  General Public License for more details.                            *
 *                                                                      *
 *    You can view the GNU  General Public License, online, at the GNU  *
 *  project's  web  site;  see <http://www.gnu.org/licenses/gpl.html>.  *
 *  The full text of the license is also included in the file COPYING.  *
 *                                                                      *
 ************************************************************************/

#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <memory>

#include "fs-utils/common.h"
#include "fs-engine/sound/sound.h"
#include "fs-engine/sound/music.h"


//! Abstraction of the sound subsystem.
/*!
 * This class defines the interface to the real audio subsystem.
 * At this date, there are 2 implementations : a dummy one that does nothing
 * and an implementation using SDL_Mixer.<br/>
 * The Audio class is used to initialize and destroy the audio system, and
 * offers common API to access the underlying implementation.
 */
class Audio {
public:
    /*!
     * A list of supported frequencies.
     */
    enum EFrequency {
        FRQ_DEFAULT = 0,
        FRQ_11025 = 1,
        FRQ_22050 = 2,
        FRQ_44100 = 3
    };

    /*!
     * A list of supported formats.
     */
    enum EFormat {
        FMT_DEFAULT = 0
    };

    /*!
     * A list of supported channels (mono or stereo).
     */
    enum EChannel {
        CHN_DEFAULT = 0,
        MONO = 1,
        STEREO = 2
    };

public:
    virtual ~Audio() {}

    //! Initialize the audio underneath implementation
    virtual bool init(EFrequency frequency = FRQ_DEFAULT,
                     EFormat format = FMT_DEFAULT,
                     EChannel channels = CHN_DEFAULT,
                     int chunksize = 1024) = 0;

    //! Returns true if the audio system has been initialized with success
    virtual bool isInitialized() = 0;
    //! Terminates the audio system
    virtual bool quit() = 0;

    //! Returns the maximum volume possible
    virtual int getMaxVolume() = 0;

    //! Sets the music volume to the given level
    virtual void setMusicVolume(int volume) = 0;
    //! Returns the music volume
    virtual int getMusicVolume() = 0;

    //! Sets the sound volume on the given channel to the given level
    virtual void setSoundVolume(int volume, int channel = 0) = 0;
    //! Returns the sound volume of the given channel
    virtual int getSoundVolume(int channel = 0) = 0;

    //! Instanciate an implementation of Sound based on the implementation of Audio
    virtual std::unique_ptr<Sound> createSound() = 0;

    //! Instanciate an implementation of Music based on the implementation of Audio
    virtual std::unique_ptr<Music> createMusic() = 0;
};

#ifndef HAVE_SDL_MIXER

/*!
 * Dummy class that does not initialize sound.
 */
class DefaultAudio : public Audio {
public:
    DefaultAudio();

    ~DefaultAudio();

    //! Initialize the audio underneath implementation
    bool init(EFrequency frequency = FRQ_DEFAULT,
                     EFormat format = FMT_DEFAULT,
                     EChannel channels = CHN_DEFAULT,
                     int chunksize = 1024);

    //! Returns true if the audio system has been initialized with success
    bool isInitialized();
    //! Terminates the audio system
    bool quit();

    //! Returns the maximum volume possible
    int getMaxVolume();

    //! Sets the music volume to the given level
    void setMusicVolume(int volume);
    //! Returns the music volume
    int getMusicVolume();

    //! Sets the sound volume on the given channel to the given level
    void setSoundVolume(int volume, int channel = 0);
    //! Returns the sound volume of the given channel
    int getSoundVolume(int channel = 0);

    //! Returns a basic implementation of Sound
    std::unique_ptr<Sound> createSound();

    //! Returns a basic implementation of Sound
    std::unique_ptr<Music> createMusic();
};

#endif //HAVE_SDL_MIXER

#endif
