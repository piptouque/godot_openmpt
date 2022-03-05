
#ifndef GODOT_OPENMPT_MPTAUDIOSTREAM_HPP
#define GODOT_OPENMPT_MPTAUDIOSTREAM_HPP

#include <core/reference.h>

namespace godot
{
    class MptAudioStream : public AudioStream
    {
        GDCLASS(MptAudioStream, AudioStream)

       public:
        MptAudioStream();
        ~MptAudioStream();

        Ref<AudioStreamPlayback>
          instance_playback() override;
        String
          get_stream_name() override const;
        float
          get_length() override const
        {
            return 0;
        }  // if supported, otherwise return 0

       protected:
        static void
          _bind_methods();

       private:
        friend class MptAudioStreamPlayback;
    }
}  // namespace godot

#endif  // GODOT_OPENMPT_MPTAUDIOSTREAM_HPP