
#include <godot_openmpt/ModuleStream.hpp>
#include <godot_openmpt/ModuleStreamPlayback.hpp>

#include <cstring>

#include <core/math/math_funcs.h>
#include <core/print_string.h>
#include <core/reference.h>
#include <core/resource.h>
#include <servers/audio/audio_stream.h>

namespace godot::openmpt
{
    ModuleStreamPlayback::ModuleStreamPlayback() : m_active(false)
    {
        AudioServer::get_singleton()->lock();
        m_pcm_buffer = AudioServer::get_singleton()->audio_data_alloc(C_PCM_BUFFER_MAX_SIZE);
        std::memset(m_pcm_buffer, 0, C_PCM_BUFFER_MAX_SIZE);
        AudioServer::get_singleton()->unlock();
    }

    ModuleStreamPlayback::~ModuleStreamPlayback()
    {
        if (m_pcm_buffer)
        {
            AudioServer::get_singleton()->audio_data_free(m_pcm_buffer);
            m_pcm_buffer = nullptr;
        }
    }

    void
      ModuleStreamPlayback::stop()
    {
        m_active = false;
        m_base->get_module()->reset();
    }

    void
      ModuleStreamPlayback::start(float p_from_pos)
    {
        m_active               = true;
        auto       mod         = m_base->get_module();
        auto const current_pos = mod->get_position_seconds();
        mod->set_position_seconds(current_pos + p_from_pos);
    }

    int
      ModuleStreamPlayback::get_loop_count() const
    {
        // TODO: times it looped,
        // so not just return mod->get_repeat_count();
        auto mod = m_base->get_module();
        return 0;
    }

    void
      ModuleStreamPlayback::seek(float p_time)
    {
        m_base->get_module()->set_position_seconds(p_time);
    }

    void
      ModuleStreamPlayback::mix(AudioFrame * p_buffer, float p_rate, int p_frames)
    {
        ERR_FAIL_COND(!m_active);
        if (!m_active)
        {
            return;
        }
        std::memset(m_pcm_buffer, 0, C_PCM_BUFFER_MAX_SIZE);
        int16_t * buffer = (int16_t *)m_pcm_buffer;
    }
    float
      ModuleStreamPlayback::get_length() const
    {
        return m_base->get_module()->get_duration_seconds();
    }

}  // namespace godot::openmpt