#include "PCH.hpp"

namespace
{
	class MainMenuCommands_Help : public mainmenu_commands
	{
	public:
		uint32_t get_command_count() final
		{
			return 1;
		}

		GUID get_command(uint32_t p_index) final
		{
			if (p_index != 0)
				FB2K_BugCheck();

			return smp::guid::menu_help;
		}

		void get_name(uint32_t p_index, pfc::string_base& p_out) final
		{
			if (p_index != 0)
				FB2K_BugCheck();

			p_out = "Spider Monkey Panel help";
		}

		bool get_description(uint32_t p_index, pfc::string_base& p_out) final
		{
			if (p_index != 0)
				FB2K_BugCheck();

			p_out = "View Spider Monkey Panel documentation files";
			return true;
		}

		GUID get_parent() final
		{
			return mainmenu_groups::help;
		}

		void execute(uint32_t p_index, service_ptr_t<service_base>) final
		{
			if (p_index != 0)
				FB2K_BugCheck();

			ShellExecuteW(nullptr, L"open", smp::path::JsDocsIndex().c_str(), nullptr, nullptr, SW_SHOW);
		}

		bool get_display(uint32_t p_index, pfc::string_base& p_out, uint32_t& p_flags) final
		{
			if (p_index != 0)
				FB2K_BugCheck();

			get_name(p_index, p_out);
			p_flags = mainmenu_commands::sort_priority_dontcare;
			return true;
		}
	};

	FB2K_SERVICE_FACTORY(MainMenuCommands_Help);
}
