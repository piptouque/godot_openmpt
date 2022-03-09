
#ifndef GODOT_OPENMPT_MODULE_HPP
#define GODOT_OPENMPT_MODULE_HPP

#include <stddef.h>
#include <memory>

#include <core/reference.h>

namespace openmpt
{
    class module_ext;
    namespace ext
    {
        class interactive;
        class interactive2;
        class interactive3;
    }  // namespace ext
}  // namespace openmpt

namespace godot::openmpt
{

    class Module : public Reference
    {
        GDCLASS(Module, Reference)
       public:
        [[nodiscard]] double
          get_current_tempo() const;

        [[nodiscard]] double
          get_tempo_factor() const;

        void
          set_tempo_factor(double factor);

        /**
         * @brief Get the current speed in ticks per row
         *
         * @return int
         */
        [[nodiscard]] std::int32_t
          get_current_speed() const;

        [[nodiscard]] std::int32_t
          get_current_row() const;

        [[nodiscard]] std::int32_t
          get_num_channels() const;
        [[nodiscard]] std::int32_t
          get_num_instruments() const;

        [[nodiscard]] String
          get_metadata(String key) const;

        void
          set_repeat_count(int count);
        [[nodiscard]] std::int32_t
          get_repeat_count() const;

        void
          set_position_seconds(double seconds);
        [[nodiscard]] double
          get_position_seconds() const;

        [[nodiscard]] double
          get_duration_seconds() const;

        void
          set_position_order_row(std::int32_t order, std::int32_t row);
        [[nodiscard]] std::int32_t
          get_current_order() const;
        [[nodiscard]] std::int32_t
          get_current_row() const;

        virtual void
          reset();

       protected:
        Module(void const * data, std::size_t size);

        static void
          _bind_methods();

       private:
        void
          read(std::int16_t * pcm_buffer, std::size_t count, std::int32_t sample_rate);

        std::unique_ptr<::openmpt::module_ext> m_mod;

        ::openmpt::ext::interactive *  m_interactive;
        ::openmpt::ext::interactive2 * m_interactive2;
        ::openmpt::ext::interactive3 * m_interactive3;
    };

}  // namespace godot::openmpt

#endif  // GODOT_OPENMPT_MODULE_HPP