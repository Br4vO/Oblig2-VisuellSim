#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_

#include <al.h>
#include <alc.h>
//#include <alext.h>
#include <string>
#include <vector>
#include "SoundSource.h"
#include "vector3.h"

/// Class handling OpenAL setup and management of sound sources.
/**
    Singleton class that creates and destroys sound sources.
**/
class SoundManager
{
public:
    struct listener_t
    {
        Vector3 pos;
        Vector3 vel;
        Vector3 dir;
        Vector3 up;
        listener_t()
        {
            pos = Vector3(0.0f, 0.0f, 0.0f);
            vel = Vector3(0.0f, 0.0f, 0.0f);
            dir = Vector3(0.0f, 0.0f, 1.0f);
            up = Vector3(0.0f, 1.0f, 0.0f);
            //Was like this, but Vector3-class does not support it now:
            //pos = Vector3::ZERO;
            //vel = Vector3::ZERO;
            //dir = Vector3::UNIT_Z;
            //up = Vector3::UNIT_Y;
        }
    };

    static SoundManager* getInstance()          ///< Get pointer to singleton instance.
    {
        if (!mInstance)
            mInstance = new SoundManager();
        return mInstance;
    }

    /// Initialises OpenAL.
    bool init();
    /// Cleans up and shuts down OpenAl.
    void cleanUp();

    /// Creates a new SoundSource with the given parameters.
    /**
        \param The name of the sound. (Not in use.)
        \param The source position as Vector3.
        \param File path relative to execution directory.
        \param Boolean to see if sound should loop or not.
    **/
    SoundSource* createSource(std::string name, Vector3 pos, std::string filePath = "", bool loop = false, float gain = 1.0);
    void updateListener(Vector3 pos, Vector3 vel, Vector3 dir, Vector3 up);

private:
    SoundManager();                         ///< Private constructor.
    SoundManager(SoundManager const&);      ///< Private copy constructor.
    void operator=(SoundManager const&);    ///< Private class assignment operator.
    static SoundManager* mInstance;         ///< Singleton instance pointer.
    /// Debug function.
    /**
        Checks for and outputs OpenAL errors.
    **/
    bool checkError();

    ALCdevice* mDevice;                 ///< Pointer to the ALC Device.
    ALCcontext* mContext;               ///< Pointer to the ALC Context.

    listener_t mListener;               ///< The listener data structure. (Temporary)
};

#endif
