/*!
 * \author ddubois 
 * \date 03-Dec-17.
 */

#ifndef RENDERER_DESCRIPTOR_SET_MANAGER_H
#define RENDERER_DESCRIPTOR_SET_MANAGER_H

#include <vulkan/vulkan.hpp>

namespace nova {
    /*!
     * \brief Creates and provides access to many of the resources that a shader might need
     */
    class shader_resource_manager {
    public:
        shader_resource_manager();

    private:
        vk::Device device;

        vk::DescriptorSetLayout block_textures_dsl;
        vk::DescriptorSetLayout custom_textures_dsl;
        vk::DescriptorSetLayout shadow_textures_dsl;
        vk::DescriptorSetLayout depth_textures_dsl;
        vk::DescriptorSetLayout common_dsl;
        vk::DescriptorSetLayout framebuffer_top_dsl;
        vk::DescriptorSetLayout framebuffer_bottom_dsl;
        vk::DescriptorSetLayout block_light_dsl;
        vk::DescriptorSetLayout per_model_dsl;

        vk::DescriptorPool descriptor_pool;

        vk::DescriptorSet block_textures;
        vk::DescriptorSet custom_textures;
        vk::DescriptorSet shadow_textures;
        vk::DescriptorSet depth_textures;
        vk::DescriptorSet common_descriptors;
        vk::DescriptorSet framebuffer_top;
        vk::DescriptorSet framebuffer_bottom;
        vk::DescriptorSet block_light;
        vk::DescriptorSet per_model_descriptors;

        /*
         * DESCRIPTOR SET LAYOUTS
         */
        void create_block_textures_dsl();

        void create_custom_textures_dsl();

        void create_shadow_textures_dsl();

        void create_depth_textures_dsl();

        void create_common_ds();

        void create_framebuffer_top_dsl();

        void create_framebuffer_bottom_dsl();

        void create_block_light_dsl();

        void create_per_model_dsl();

        /*
         * DESCRIPTOR SETS
         */

        void create_descriptor_pool();

        void create_desriptor_sets();

        /*
         * SAMPLERS
         */

        void create_point_sampler();

        void create_bilinear_sampler();

        void create_aniso_filter();


    };
}


#endif //RENDERER_DESCRIPTOR_SET_MANAGER_H