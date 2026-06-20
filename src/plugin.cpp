#include "plugin.hpp"

// Initialize the plugin instance
Plugin* pluginInstance;

void init(Plugin* p) {
    pluginInstance = p;

    // Register our models
    p->addModel(modelSkyline);
}
