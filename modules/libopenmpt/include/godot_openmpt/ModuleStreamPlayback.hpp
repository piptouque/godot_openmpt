

#ifndef GODOT_OPENMPT_MPTAUDIOSTREAMPLAYBACK_HPP
#define GODOT_OPENMPT_MPTAUDIOSTREAMPLAYBACK_HPP

#include <core/reference.h>

namespace godot
{
    class ModuleStream;

    class ModuleStreamPlayback : public AudioStreamPlayback
    {
        GDCLASS(ModuleStreamPlayback, AudioStreamPlayback)
        friend class MptAudioStream;

       public:
        ModuleStreamPlayback();
        ~ModuleStreamPlayback();

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
          get_length() const;

       private:
        // consts and structs
        constexpr static int C_PCM_BUFFER_MAX_SIZE = 4096;
        enum
        {
            E_MIX_FRAC_BITS = 13,
            E_MIX_FRAC_LEN  = (1 << E_MIX_FRAC_BITS),
            E_MIX_FRAC_MASK = E_MIX_FRAC_LEN - 1
        };

        Ref<ModuleStream> m_base;
        void *            m_pcm_buffer;
        bool              m_active;
    }
}  // namespace godot

#endif  // GODOT_OPENMPT_MPTAUDIOSTREAMPLAYBACK_HPP
