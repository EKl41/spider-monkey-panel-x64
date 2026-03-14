#include "PCH.hpp"

namespace
{
	class MainMenuCallback : public mainmenu_commands
	{
	public:
		GUID get_command(uint32_t index) final
		{
			switch (index)
			{
			case 0u: return smp::guid::menu_1;
			case 1u: return smp::guid::menu_2;
			case 2u: return smp::guid::menu_3;
			case 3u: return smp::guid::menu_4;
			case 4u: return smp::guid::menu_5;
			case 5u: return smp::guid::menu_6;
			case 6u: return smp::guid::menu_7;
			case 7u: return smp::guid::menu_8;
			case 8u: return smp::guid::menu_9;
			case 9u: return smp::guid::menu_10;
			default: FB2K_BugCheck();
			}
		}

		GUID get_parent() final
		{
			return smp::guid::mainmenu_group;
		}

		bool get_description(uint32_t index, pfc::string_base& out) final
		{
			if (index >= count)
				FB2K_BugCheck();

			out = fmt::format("Invoke on_main_menu({})", ++index).c_str();
			return true;
		}

		bool get_display(uint32_t index, pfc::string_base& out, uint32_t& flags) final
		{
			if (index >= count)
				FB2K_BugCheck();

			get_name(index, out);
			flags = mainmenu_commands::flag_defaulthidden;
			return true;
		}

		uint32_t get_command_count() final
		{
			return count;
		}

		void execute(uint32_t index, service_ptr_t<service_base>) final
		{
			if (index >= count)
				FB2K_BugCheck();

			smp::EventDispatcher::Get().PutEventToAll(smp::GenerateEvent_JsCallback(smp::EventId::kStaticMainMenu, ++index), smp::EventPriority::kInput);
		}

		void get_name(uint32_t index, pfc::string_base& out) final
		{
			if (index >= count)
				FB2K_BugCheck();

			out = pfc::format_uint(++index);
		}

	private:
		static constexpr auto count = 10u;
	};

	static auto mainmenu_group = mainmenu_group_popup_factory(
		smp::guid::mainmenu_group,
		mainmenu_groups::file,
		mainmenu_commands::sort_priority_base,
		Component::name.data()
	);

	FB2K_SERVICE_FACTORY(MainMenuCallback);
}
