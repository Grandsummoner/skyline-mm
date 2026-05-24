#include "plugin.hpp"

struct Skyline : Module {
    enum ParamIds {
        LEVEL_PARAM,
        NUM_PARAMS
    };
    enum InputIds {
        AUDIO_INPUT,
        CV_INPUT,
        GATE_INPUT,
        NUM_INPUTS
    };
    enum OutputIds {
        AUDIO_OUTPUT,
        CV_OUTPUT,
        GATE_OUTPUT,
        NUM_OUTPUTS
    };
    enum LightIds {
        NUM_LIGHTS
    };

    Skyline() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        configParam(LEVEL_PARAM, 0.f, 1.f, 0.5f, "Level");
        configInput(AUDIO_INPUT, "Audio");
        configInput(CV_INPUT, "CV");
        configInput(GATE_INPUT, "Gate");
        configOutput(AUDIO_OUTPUT, "Audio");
        configOutput(CV_OUTPUT, "CV");
        configOutput(GATE_OUTPUT, "Gate");
    }

    void process(const ProcessArgs& args) override {
        float level = params[LEVEL_PARAM].getValue();
        outputs[AUDIO_OUTPUT].setVoltage(inputs[AUDIO_INPUT].getVoltage() * level);
        outputs[CV_OUTPUT].setVoltage(inputs[CV_INPUT].getVoltage());
        outputs[GATE_OUTPUT].setVoltage(inputs[GATE_INPUT].getVoltage());
    }
};

struct SkylineWidget : ModuleWidget {
    SkylineWidget(Skyline* module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Skyline.svg")));

        addParam(createParamCentered<RoundBlackKnob>(Vec(30, 123), module, Skyline::LEVEL_PARAM));

        addInput(createInputCentered<PJ301MPort>(Vec(15, 200), module, Skyline::AUDIO_INPUT));
        addInput(createInputCentered<PJ301MPort>(Vec(15, 225), module, Skyline::CV_INPUT));
        addInput(createInputCentered<PJ301MPort>(Vec(15, 250), module, Skyline::GATE_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(Vec(15, 343), module, Skyline::AUDIO_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(Vec(45, 343), module, Skyline::CV_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(Vec(15, 368), module, Skyline::GATE_OUTPUT));
    }
};

Model* modelSkyline = createModel<Skyline, SkylineWidget>("Skyline");
