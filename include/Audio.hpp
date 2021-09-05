//
// Created by tag43 on 6/16/21.
//

#ifndef BOMBERMAN_AUDIO_HPP
#define BOMBERMAN_AUDIO_HPP

#include <SFML/Audio.hpp>

class Audio {
private:
    sf::SoundBuffer exploBuffer;
    sf::Sound exploSound;
    sf::SoundBuffer backBuffer;
    sf::Sound backSound;
    sf::SoundBuffer backBuffer2;
    sf::Sound backSound2;
    sf::SoundBuffer allahBuffer;
    sf::Sound allahSound;
    sf::SoundBuffer powerUpBuffer;
    sf::Sound powerUpSound;
    sf::SoundBuffer powerUpBuffer2;
    sf::Sound powerUpSound2;
    sf::SoundBuffer powerUpBuffer3;
    sf::Sound powerUpSound3;


public:
    Audio()
    {
        exploBuffer.loadFromFile("media/sounds/explos.ogg");
        exploSound.setBuffer(exploBuffer);
        exploSound.setVolume(18);
        backBuffer.loadFromFile("media/sounds/arabic.ogg");
        backSound.setBuffer(backBuffer);
        backBuffer2.loadFromFile("media/sounds/arabic2.ogg");
        backSound2.setBuffer(backBuffer2);
        backSound.setLoop(true);
        backSound.setVolume(5);
        backSound2.setVolume(10);
        backSound2.setLoop(true);
        allahBuffer.loadFromFile("media/sounds/allah.ogg");
        allahSound.setBuffer(allahBuffer);
        allahSound.setVolume(10);
        powerUpBuffer.loadFromFile("media/sounds/magic.ogg");
        powerUpBuffer2.loadFromFile("media/sounds/fairy2.ogg");
        powerUpSound2.setBuffer(powerUpBuffer2);
        powerUpSound2.setVolume(30);
        powerUpSound.setBuffer(powerUpBuffer);
        powerUpSound.setVolume(30);
        powerUpBuffer3.loadFromFile("media/sounds/aura.ogg");
        powerUpSound3.setBuffer(powerUpBuffer3);
        powerUpSound3.setVolume(30);

    }

    void MuteMusic(bool mute)
    {
        if (mute) {
            backSound.setVolume(0);
            backSound2.setVolume(0);
        }
        else {
            backSound.setVolume(5);
            backSound2.setVolume(10);
        }
    }

    void MuteSound(bool mute)
    {
        if (mute) {
            exploSound.setVolume(0);
            allahSound.setVolume(0);
            powerUpSound.setVolume(0);
            powerUpSound2.setVolume(0);
            powerUpSound3.setVolume(0);
        }
        else {
            exploSound.setVolume(18);
            allahSound.setVolume(10);
            powerUpSound.setVolume(30);
            powerUpSound2.setVolume(30);
            powerUpSound3.setVolume(30);
        }

    }

    void explode()
    {
        exploSound.play();       // Play queued audio
    }

    void backMusic()
    {
        backSound.play();
    }

    void stopBackMusic()
    {
        backSound.stop();
    }

    void allah()
    {
        allahSound.play();
    }

    void backMusic2()
    {
        backSound2.play();
    }

    void stopBackMusic2()
    {
        backSound2.stop();
    }

    void powerUp()
    {
        powerUpSound.play();
    }

    void powerUp2()
    {
        powerUpSound2.play();
    }
    void powerUp3()
    {
        powerUpSound3.play();
    }
};


#endif //BOMBERMAN_AUDIO_HPP
