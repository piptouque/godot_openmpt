
#include <godot_openmpt/ModuleStream.hpp>

namespace godot
{
    ModuleStream::ModuleStream(Ref<openmpt::Module> mod) : m_mod(mod) {}

    void
      ModuleStream::_bind_methods()
    {
        ClassDB::bind_method(D_METHOD("get_stream_name"), &ModuleStream::get_stream_name);
        ClassDB::bind_method(D_METHOD("get_module"), &ModuleStream::get_module);
        //
    }

    String
      ModuleStream::get_stream_name() const
    {
        return "ModuleStream";
    }

    bool
      ModuleStream::is_monophonic() const
    {
        // TODO: for now.
        return true;
    }

    Ref<openmpt::Module>
      ModuleStream::get_module()
    {
        return m_mod;
    }

    Ref<openmpt::Module> const
      ModuleStream::get_module() const
    {
        return m_mod;
    }

}  // namespace godot