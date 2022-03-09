
#include <core/class_db.h>

#include <godot_openmpt/Module.hpp>
#include <godot_openmpt/ModuleStream.hpp>
#include <godot_openmpt/ModuleStreamPlayback.hpp>

#include "register_types.hpp"

void
  register_godot_openmpt_types()
{
    ClassDB::register_class<godot::openmpt::Module>();
    ClassDB::register_class<godot::ModuleStream>();
    ClassDB::register_class<godot::ModuleStreamPlayback>();
}

void
  unregister_godot_openmpt_types()
{}