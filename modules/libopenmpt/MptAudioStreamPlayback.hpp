

#ifndef GODOT_OPENMPT_MPTAUDIOSTREAMPLAYBACK_HPP
#define GODOT_OPENMPT_MPTAUDIOSTREAMPLAYBACK_HPP

#include "MptAudioStream.hpp"

namespace godot
{
    class MptAudioStreamPlayback : public AudioStreamPlayback
    {
        GDCLASS(MptAudioStreamPlayback, AudioStreamPlayback)
        friend class MptAudioStream;

       public:
        MptAudioStreamPlayback();
        ~MptAudioStreamPlayback();

        void
          start(float p_from_pos = 0.0) override;
        void
          stop() override;
        [[nodiscard]] bool
          is_playing() const override;
        [[nodiscard]] int
          get_loop_count() const override;
        [[nodiscard]] float
          get_playback_position() const override;
        void
          seek(float p_time) override;
        void
          mix(AudioFrame * p_buffer, float p_rate_scale, int p_frames) override;
        [[nodiscard]] float
          get_length() const override;

       private:
        void *              pcm_buffer;
        Ref<MptAudioStream> base;
        bool                active;
    }
}  // namespace godot

#endif  // GODOT_OPENMPT_MPTAUDIOSTREAMPLAYBACK_HPP
