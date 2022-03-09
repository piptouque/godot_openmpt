
#include <godot_openmpt/Module.hpp>

#include <stddef.h>
#include <string>

#include <core/ustring.h>

#include <libopenmpt/libopenmpt_ext_impl.hpp>

namespace godot::openmpt
{
    Module::Module(void const * module_data, std::size_t size)
        : m_mod(std::make_unique<::openmpt::module_ext>(module_data, size))
    {
        m_interactive = static_cast<::openmpt::ext::interactive *>(
          m_mod->get_interface(::openmpt::ext::interactive_id));
        m_interactive2 = static_cast<::openmpt::ext::interactive2 *>(
          m_mod->get_interface(::openmpt::ext::interactive2_id));
        m_interactive3 = static_cast<::openmpt::ext::interactive3 *>(
          m_mod->get_interface(::openmpt::ext::interactive3_id));
    }

    void
      Module::_bind_methods()
    {
        ClassDB::bind_method(D_METHOD("get_tempo"), &Module::get_current_tempo);
        ClassDB::bind_method(D_METHOD("get_tempo_factor"), &Module::get_tempo_factor);
        ClassDB::bind_method(D_METHOD("set_tempo_factor", "factor"), &Module::set_tempo_factor);
        //
        ClassDB::bind_method(D_METHOD("get_repeat_count"), &Module::get_repeat_count);
        ClassDB::bind_method(D_METHOD("set_repeat_count", "count"), &Module::get_repeat_count);
        //
        ClassDB::bind_method(D_METHOD("get_current_speed"), &Module::get_current_speed);
        ClassDB::bind_method(D_METHOD("get_current_row"), &Module::get_current_row);
        ClassDB::bind_method(D_METHOD("get_number_channels"), &Module::get_num_channels);
        ClassDB::bind_method(D_METHOD("get_number_instruments"), &Module::get_num_channels);
        //
        ClassDB::bind_method(D_METHOD("get_position_seconds"), &Module::get_position_seconds);
        ClassDB::bind_method(D_METHOD("set_position_seconds", "seconds"), &Module::set_position_seconds);
        ClassDB::bind_method(D_METHOD("get_duration_seconds"), &Module::get_duration_seconds);
        //
        ClassDB::bind_method(D_METHOD("get_current_order"), &Module::get_current_order);
        ClassDB::bind_method(D_METHOD("get_current_row"), &Module::get_current_row);
        ClassDB::bind_method(D_METHOD("set_position_order_row", "order", "row"), &Module::set_position_order_row);
        //
        ClassDB::bind_method(D_METHOD("get_metadata"), &Module::get_metadata);
        //
        ClassDB::bind_method(D_METHOD("reset"), &Module::reset);
        //
    }

    double
      Module::get_current_tempo() const
    {
        return m_mod->get_current_tempo2();
    }

    double
      Module::get_tempo_factor() const
    {
        return m_interactive->get_tempo_factor();
    }

    void
      Module::set_tempo_factor(double factor)
    {
        return m_interactive->set_tempo_factor(factor);
    }

    std::int32_t
      Module::get_current_speed() const
    {
        return m_mod->get_current_speed();
    }

    std::int32_t
      Module::get_current_order() const
    {
        return m_mod->get_current_order();
    }

    std::int32_t
      Module::get_current_row() const
    {
        return m_mod->get_current_row();
    }

    std::int32_t
      Module::get_num_channels() const
    {
        return m_mod->get_num_channels();
    }
    std::int32_t
      Module::get_num_instruments() const
    {
        return m_mod->get_num_instruments();
    }

    String
      Module::get_metadata(String key) const
    {
        std::string str_key;
        std::copy(key.c_str(), key.c_str() + key.length(), str_key.begin());
        auto const str_metadata = m_mod->get_metadata(str_key);
        String     metadata     = str_metadata.c_str();
        return metadata;
    }

    void
      Module::set_repeat_count(std::int32_t count)
    {
        m_mod->set_repeat_count(count);
    }
    std::int32_t
      Module::get_repeat_count() const
    {
        m_mod->get_repeat_count();
    }

    void
      Module::set_position_order_row(std::int32_t order, std::int32_t row)
    {
        m_mod->set_position_order_row(order, row);
    }

    double
      Module::get_duration_seconds() const
    {
        return m_mod->get_duration_seconds();
    }

    void
      Module::set_position_seconds(double seconds)
    {
        m_mod->set_position_seconds(seconds);
    }

    double
      Module::get_position_seconds() const
    {
        return m_mod->get_position_seconds();
    }

    void
      Module::reset()
    {
        set_position_order_row(0, 0);
        set_repeat_count(0);
    }

    void
      Module::read(std::int16_t * pcm_buffer, std::size_t count, std::int32_t sample_rate)
    {
        m_mod->read(sample_rate, count, pcm_buffer);
    }
}  // namespace godot::openmpt