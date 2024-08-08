#include <solanaceae/plugin/solana_plugin_v1.h>

#include <imgui.h>

#include <solanaceae/vcg/vcg.hpp>
#include <solanaceae/vcg/vcg_sp_gui.hpp>
//#include <solanaceae/toxcore/tox_interface.hpp>

#include <memory>
#include <limits>
#include <iostream>

static std::unique_ptr<VCG> g_vcg = nullptr;
static std::unique_ptr<VCGSPGUI> g_vcgspgui = nullptr;

constexpr const char* plugin_name = "VCG";

extern "C" {

SOLANA_PLUGIN_EXPORT const char* solana_plugin_get_name(void) {
	return plugin_name;
}

SOLANA_PLUGIN_EXPORT uint32_t solana_plugin_get_version(void) {
	return SOLANA_PLUGIN_VERSION;
}

SOLANA_PLUGIN_EXPORT uint32_t solana_plugin_start(struct SolanaAPI* solana_api) {
	std::cout << "PLUGIN " << plugin_name << " START()\n";

	if (solana_api == nullptr) {
		return 1;
	}

	try {
		auto* imguic = PLUG_RESOLVE_INSTANCE_VERSIONED(ImGuiContext, ImGui::GetVersion());
		auto* imguimemaf = PLUG_RESOLVE_INSTANCE_VERSIONED(ImGuiMemAllocFunc, ImGui::GetVersion());
		auto* imguimemff = PLUG_RESOLVE_INSTANCE_VERSIONED(ImGuiMemFreeFunc, ImGui::GetVersion());
		auto* imguimemud = plug_resolveInstanceOptional<void*>(solana_api, "ImGuiMemUserData", ImGui::GetVersion());

		ImGui::SetCurrentContext(imguic);
		ImGui::SetAllocatorFunctions(imguimemaf, imguimemff, imguimemud);

		//auto* tox_i = PLUG_RESOLVE_INSTANCE(ToxI);
		//auto* tep_i = PLUG_RESOLVE_INSTANCE(ToxEventProviderI);
		//auto* tcm = PLUG_RESOLVE_INSTANCE(ToxContactModel2);

		// static store, could be anywhere tho
		// construct with fetched dependencies
		g_vcg = std::make_unique<VCG>();
		g_vcgspgui = std::make_unique<VCGSPGUI>();

		// register types
		PLUG_PROVIDE_INSTANCE(VCG, plugin_name, g_vcg.get());
		PLUG_PROVIDE_INSTANCE(VCGSPGUI, plugin_name, g_vcgspgui.get());
	} catch (const ResolveException& e) {
		std::cerr << "PLUGIN " << plugin_name << " " << e.what << "\n";
		return 2;
	}

	return 0;
}

SOLANA_PLUGIN_EXPORT void solana_plugin_stop(void) {
	std::cout << "PLUGIN " << plugin_name << " STOP()\n";

	g_vcg.reset();
}

SOLANA_PLUGIN_EXPORT float solana_plugin_tick(float) {
	return std::numeric_limits<float>::max();
}

SOLANA_PLUGIN_EXPORT float solana_plugin_render(float delta) {
	return g_vcgspgui->render(delta);
}

} // extern C

