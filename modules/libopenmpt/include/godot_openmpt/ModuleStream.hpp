
#ifndef GODOT_OPENMPT_OPENMPTTRACK_HPP
#define GODOT_OPENMPT_OPENMPTTRACK_HPP

#include <core/math/audio_frame.h>
#include <servers/audio/audio_stream.h>

#include <godot_openmpt/Module.hpp>

namespace godot
{
    namespace openmpt
    {
        class Module;
    }

    class ModuleStream : public AudioStream
    {
        GDCLASS(ModuleStream, AudioStream)
        friend class ModuleStreamPlayback;

       public:
        explicit ModuleStream(Ref<openmpt::Module> mod);

        [[nodiscard]] Ref<AudioStreamPlayback>
          instance_playback() override;
        [[nodiscard]] String
          get_stream_name() const override;

        [[nodiscard]] float
          get_length() const override;

        [[nodiscard]] bool
          is_monophonic() const;

        [[nodiscard]] Ref<openmpt::Module>
          get_module();
        [[nodiscard]] Ref<openmpt::Module> const
          get_module() const;

       protected:
        static void
          _bind_methods();

       private:
        Ref<openmpt::Module> m_mod;
    };

}  // namespace godot

#endif  // GODOT_OPENMPT_OPENMPTTRACK_HPP