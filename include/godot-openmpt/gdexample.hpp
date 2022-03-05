
#ifndef GODOT_OPENMPT_EXAMPLE_HPP
#define GODOT_OPENMPT_EXAMPLE_HPP

#include <Godot.hpp>
#include <Sprite.hpp>

namespace godot
{
    class GDExample : public Sprite
    {
        GODOT_CLASS(GDExample, Sprite)
       public:
        static void
          _register_methods();
        GDExample();
        ~GDExample();

        void
          _init();
        void
          _process(float delta);

       private:
        float m_time_passed;
    };
}  // namespace godot

#endif  // GODOT_OPENMPT_EXAMPLE_HPP