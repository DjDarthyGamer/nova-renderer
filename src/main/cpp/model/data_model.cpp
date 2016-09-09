/*!
 * \brief
 *
 * \author ddubois 
 * \date 04-Sep-16.
 */

#include "data_model.h"

#include "loaders/loaders.h"

namespace nova {
    namespace model {
        data_model::data_model() : render_settings("config/config.json") {
            render_settings.register_change_listener(this);

            render_settings.update_config_loaded();
            render_settings.update_config_changed();
        }

        gl_shader_program &data_model::get_shader_program(const std::string &program_name) {
            return loaded_shaderpack[program_name];
        }

        void data_model::on_config_change(nlohmann::json &config) {
            load_new_shaderpack(config["loadedShaderpack"]);
            load_new_resourcepack(config["loadedResourcepacks"]);
        }

        void data_model::on_config_loaded(nlohmann::json &config) {}

        void data_model::load_new_shaderpack(const std::string &new_shaderpack_name) noexcept {
            if(new_shaderpack_name != loaded_shaderpack_name) {
                try {
                    LOG(INFO) << "Loading shaderpack " << new_shaderpack_name;
                    loaded_shaderpack = load_shaderpack(new_shaderpack_name);
                    loaded_shaderpack_name = new_shaderpack_name;

                } catch(std::exception e) {
                    LOG(ERROR) << "Could not load shaderpack " << new_shaderpack_name << ". Reason: " << e.what();
                    loaded_shaderpack_name = "default";
                    loaded_shaderpack = load_shaderpack(loaded_shaderpack_name);
                }
            }
        }

        std::vector<gl_shader_program*> data_model::get_all_shaders() {
            auto all_shaders = std::vector<gl_shader_program*>{};
            for(auto& shader : loaded_shaderpack) {
                all_shaders.push_back(&shader.second);
            }

            return all_shaders;
        }

        void data_model::load_new_resourcepack(const std::vector<std::string>& resourcepack_names) {
            if(resourcepack_names != loaded_resourcepack_names) {
                try {
                    LOG(INFO) << "Loading resourcepacks: ";
                    for(auto& name : resourcepack_names) {
                        LOG(INFO) << "\t" << name;
                    }

                    loaded_textures = load_textures(resourcepack_names);
                    loaded_resourcepack_names = resourcepack_names;

                } catch(std::runtime_error& e) {
                    LOG(ERROR) << "Could not load specified resourcepacks: " << e.what();
                    loaded_resourcepack_names = {"/versions/1.10/1.10.jar"};
                    loaded_textures = load_textures(loaded_resourcepack_names);
                }
            }
        }
    }
}
