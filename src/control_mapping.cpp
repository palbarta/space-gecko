#include "control_mapping.h"
#include <string>

using namespace sf;

std::map<std::string, Keyboard::Key> cfg_entry_to_key = { 
	{ "left",	Keyboard::Key::Left },
	{ "right",	Keyboard::Key::Right },
	{ "up",		Keyboard::Key::Up },
	{ "down",	Keyboard::Key::Down },
	{ "space",	Keyboard::Key::Space },

	{ "A",	Keyboard::Key::A },
	{ "B",	Keyboard::Key::B },
	{ "C",	Keyboard::Key::C },
	{ "D",	Keyboard::Key::D },
	{ "E",	Keyboard::Key::E },
	{ "F",	Keyboard::Key::F },
	{ "G",	Keyboard::Key::G },
	{ "H",	Keyboard::Key::H },
	{ "I",	Keyboard::Key::I },
	{ "J",	Keyboard::Key::J },
	{ "K",	Keyboard::Key::K },
	{ "L",	Keyboard::Key::L },
	{ "M",	Keyboard::Key::M },
	{ "N",	Keyboard::Key::N },
	{ "O",	Keyboard::Key::O },
	{ "P",	Keyboard::Key::P },
	{ "Q",	Keyboard::Key::Q },
	{ "R",	Keyboard::Key::R },
	{ "S",	Keyboard::Key::S },
	{ "T",	Keyboard::Key::T },
	{ "U",	Keyboard::Key::U },
	{ "V",	Keyboard::Key::V },
	{ "W",	Keyboard::Key::W },
	{ "X",	Keyboard::Key::X },
	{ "Y",	Keyboard::Key::Y },
	{ "Z",	Keyboard::Key::Z },
	{ "num0",	Keyboard::Key::Num0 },
	{ "num1",	Keyboard::Key::Num1 },
	{ "num2",	Keyboard::Key::Num2 },
	{ "num3",	Keyboard::Key::Num3 },
	{ "num4",	Keyboard::Key::Num4 },
	{ "num5",	Keyboard::Key::Num5 },
	{ "num6",	Keyboard::Key::Num6 },
	{ "num7",	Keyboard::Key::Num7 },
	{ "num8",	Keyboard::Key::Num8 },
	{ "num9",	Keyboard::Key::Num9 },
	{ "lcontrol",	Keyboard::Key::LControl },
	{ "lshift",		Keyboard::Key::LShift },
	{ "lalt",		Keyboard::Key::LAlt },
	{ "lsystem",	Keyboard::Key::LSystem },
	{ "rcontrol",	Keyboard::Key::RControl },
	{ "rshift",		Keyboard::Key::RShift },
	{ "ralt",		Keyboard::Key::RAlt },
	{ "rsystem",	Keyboard::Key::RSystem },
};