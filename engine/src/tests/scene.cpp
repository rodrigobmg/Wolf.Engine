#include "pch.h"
#include "scene.h"
#include <w_graphics/w_shader.h>
#include <w_graphics/w_command_buffers.h>
#include <w_graphics/w_texture.h>
#include <w_graphics/w_shader_buffer.h>
#include <glm/glm.hpp>
#include <glm_extention.h>

#include <w_content_manager.h>
#include <w_scene.h>


using namespace wolf::system;
using namespace wolf::graphics;
using namespace wolf::framework;
using namespace wolf::content_pipeline;

struct vertex_data
{
    float position[4];
    //float uv[2];
};

#if defined(__WIN32)
scene::scene(_In_z_ const std::wstring& pRunningDirectory, _In_z_ const std::wstring& pAppName):
	w_game(pRunningDirectory, pAppName)
#elif defined(__UWP)
scene::scene(_In_z_ const std::wstring& pAppName):
	w_game(pAppName)
#else
scene::scene(_In_z_ const std::string& pRunningDirectory, _In_z_ const std::string& pAppName):
	w_game(pRunningDirectory, pAppName)
#endif
{
    w_game::set_fixed_time_step(false);
}

scene::~scene()
{
    release();
}

void scene::initialize(_In_ std::map<int, std::vector<w_window_info>> pOutputWindowsInfo)
{
    // TODO: Add your pre-initialization logic here
    w_game::initialize(pOutputWindowsInfo);
}

w_texture* _texture = nullptr;
w_shader_buffer<glm::mat4x4> _view_projection_uniform;
w_shader _shader;
void scene::load()
{
    auto _gDevice =  this->graphics_devices[0];
    auto _output_window = &(_gDevice->output_presentation_windows[0]);
    
    
    w_game::load();
    
    //auto _scene = w_content_manager::load<w_scene>(content_path + L"models/inst_max_oc.dae");
    auto _scene = w_content_manager::load<w_scene>(content_path + L"models/test_instance.wscene");
    this->_renderable_scene = new w_renderable_scene(_scene);
    this->_renderable_scene->load(_gDevice);
    this->_renderable_scene->get_first_or_default_camera(&this->_camera);
    
    
    auto _hr = _view_projection_uniform.load(_gDevice);
    
    this->_camera->set_aspect_ratio((float)_output_window->width / (float)_output_window->height);
    this->_camera->update_view();
    this->_camera->update_projection();
    
	glm::mat4x4 _translate = glm::translate(glm::mat4x4(1.0f), glm::vec3(1.5f, 0.0f, 0.0f));
	glm::mat4x4 _rotate = glm::rotate(glm::mat4x4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4x4 _scale = glm::scale(glm::mat4x4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	auto _world = _scale * _rotate * _translate;
	_view_projection_uniform.data = this->_camera->get_projection() * this->_camera->get_view() *_world;
    _hr = _view_projection_uniform.update();
    
    //load shaders
    _hr = _shader.load(_gDevice, content_path + L"shaders/test/shader.vs.spv", w_shader_stage::VERTEX_SHADER);
    _hr = _shader.load(_gDevice, content_path + L"shaders/test/shader.fs.spv", w_shader_stage::FRAGMENT_SHADER);
    
    std::vector<VkDescriptorPoolSize> _descriptor_pool_sizes =
    {
//        {
//            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,          // Type
//            1                                                   // DescriptorCount
//        },
        {
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,                  // Type
            1                                                   // DescriptorCount
        }
    };
    _hr = _shader.create_descriptor_pool(_descriptor_pool_sizes);
    
    std::vector<VkDescriptorSetLayoutBinding> _layout_bindings =
    {
//        {
//            0,                                                  // Binding
//            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,          // DescriptorType
//            1,                                                  // DescriptorCount
//            VK_SHADER_STAGE_FRAGMENT_BIT,                       // StageFlags
//            nullptr                                             // ImmutableSamplers
//        },
        {
            0,                                                  // Binding
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,                  // DescriptorType
            1,                                                  // DescriptorCount
            VK_SHADER_STAGE_VERTEX_BIT,                         // StageFlags
            nullptr                                             // ImmutableSamplers
        }
    };
    _hr = _shader.create_description_set_layout_binding(_layout_bindings);
    
    
    //load texture
//    _texture = new w_texture();
//    _hr = _texture->load(_gDevice);
//    _hr = _texture->initialize_texture_2D_from_file("/Users/pooyaeimandar/Documents/github/WolfSource/Wolf.Engine/Logo.jpg", true);
    
   // const VkDescriptorImageInfo _image_info = _texture->get_descriptor_info();
    const VkDescriptorBufferInfo _buffer_info = _view_projection_uniform.get_descriptor_info();
    
    auto _descriptor_set = _shader.get_descriptor_set();
    std::vector<VkWriteDescriptorSet> _write_descriptor_sets =
    {
//        {
//            VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,         // Type
//            nullptr,                                        // Next
//            _descriptor_set,                                // DstSet
//            0,                                              // DstBinding
//            0,                                              // DstArrayElement
//            1,                                              // DescriptorCount
//            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,      // DescriptorType
//            &_image_info,                                   // ImageInfo
//            nullptr,
//        },
        {
            VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,         // Type
            nullptr,                                        // Next
            _descriptor_set,                                // DstSet
            0,                                              // DstBinding
            0,                                              // DstArrayElement
            1,                                              // DescriptorCount
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,              // DescriptorType
            nullptr,                                        // ImageInfo
            &_buffer_info,                                  // BufferInfo
            nullptr                                         // TexelBufferView
        }
    };
    _shader.update_descriptor_sets(_write_descriptor_sets);
    
    //create render pass
    _render_pass.load(_gDevice);
    auto _render_pass_handle = _render_pass.get_handle();
    
    //create frame buffers
    this->_frame_buffers.load(_gDevice,
                              _render_pass_handle,
                              _output_window->vk_swap_chain_image_views.size(),
                              _output_window->vk_swap_chain_image_views.data(),
                              _output_window->width,
                              _output_window->height,
                              1);
    
//    std::vector<vertex_data> _vertex_data =
//    {
//        { {-0.7f, -0.7f, 0.0f, 1.0f }},
//        { {-0.7f,  0.7f, 0.0f, 1.0f }},
//        { { 0.7f, -0.7f, 0.0f, 1.0f }},
//        { { 0.7f,  0.7f, 0.0f, 1.0f }}
//    };


//    this->_mesh = new w_mesh();
//    this->_mesh->load(_gDevice,
//                     _vertex_data.data(),
//                     static_cast<UINT>(_vertex_data.size()),
//                     static_cast<UINT>(_vertex_data.size() * sizeof(vertex_data)),
//                     nullptr,
//                     0,
//                     nullptr,
//                     0,
//                     true);
    
    std::vector<VkVertexInputBindingDescription> _vertex_binding_descriptions =
    {
        {
            0,                                                          // Binding
            sizeof(vertex_data),                                        // Stride
            VK_VERTEX_INPUT_RATE_VERTEX                                 // InputRate
        }
    };
    
    std::vector<VkVertexInputAttributeDescription> _vertex_attribute_descriptions =
    {
        {
            0,                                                          // Location
            _vertex_binding_descriptions[0].binding,                    // Binding
            VK_FORMAT_R32G32B32A32_SFLOAT,                                 // Format
            offsetof(vertex_data, position)                             // Offset
        }//,
//        {
//            1,                                                          // Location
//            _vertex_binding_descriptions[0].binding,                    // Binding
//            VK_FORMAT_R32G32_SFLOAT,                                    // Format
//            offsetof(vertex_data, uv)                                // Offset
//        }
    };
    
    VkPipelineVertexInputStateCreateInfo _vertex_input_state_create_info =
    {
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,    // Type
        nullptr,                                                      // Next
        0,                                                            // Flags
        static_cast<uint32_t>(_vertex_binding_descriptions.size()),   // VertexBindingDescriptionCount
        &_vertex_binding_descriptions[0],                             // VertexBindingDescriptions
        static_cast<uint32_t>(_vertex_attribute_descriptions.size()), // VertexAttributeDescriptionCount
        &_vertex_attribute_descriptions[0]                            // VertexAttributeDescriptions
    };
    
    VkPipelineInputAssemblyStateCreateInfo _input_assembly_state_create_info =
    {
        VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,    // Type
        nullptr,                                                        // Next
        0,                                                              // Flags
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,//VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,                           // Topology
        VK_FALSE                                                        // Enable restart primitive
    };
    
    std::vector<VkDynamicState> _dynamic_states =
    {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR,
    };
    
    VkPipelineDynamicStateCreateInfo _dynamic_state_create_info =
    {
        VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,                   // Type
        nullptr,                                                                // Next
        0,                                                                      // Flags
        static_cast<uint32_t>(_dynamic_states.size()),                          // DynamicStateCount
        &_dynamic_states[0]                                                     // DynamicStates
    };
    
    //create view port
    w_viewport _wp;
    _wp.x = 0.0f;
    _wp.y = 0.0f;
    _wp.width = _output_window->width;
    _wp.height =  _output_window->height;
    _wp.minDepth = 0.0f;
    _wp.maxDepth = 1.0f;
    
    w_viewport_scissor _wp_sc;
    _wp_sc.offset.x = 0.0f;
    _wp_sc.offset.y = 0.0f;
    _wp_sc.extent.width = _output_window->width;
    _wp_sc.extent.height = _output_window->height;
    
    auto _descriptor_set_layout = _shader.get_descriptor_set_layout_binding();
    VkPipelineLayoutCreateInfo _pipeline_layout_create_info =
    {
        VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,  // Type
        nullptr,                                        // Next
        0,                                              // Flags
        1,                                              // SetLayoutCount
        &_descriptor_set_layout,                        // SetLayouts
        0,                                              // PushConstantRangeCount
        nullptr                                         // PushConstantRanges
    };
    
    _hr = this->_pipeline.load(_gDevice,
                         _render_pass_handle,
                         _shader.get_shader_stages(),
                         { _wp }, //viewports
                         { _wp_sc },
                         &_pipeline_layout_create_info,
                         &_vertex_input_state_create_info,
                         &_input_assembly_state_create_info,
                         nullptr,
                         nullptr,
                         nullptr,
                         &_dynamic_state_create_info);
    if (_hr)
    {
        logger.error("Error creating pipeline");
        return;
    }
    
    //now assign new command buffers
    this->_command_buffers = new w_command_buffers();
    this->_command_buffers->set_enable(true);
    this->_command_buffers->set_order(1);
    this->_command_buffers->load(_gDevice, _output_window->vk_swap_chain_image_views.size());
    
    _hr = _gDevice->store_to_global_command_buffers("render_quad_with_texture",
                                                  this->_command_buffers,
                                                  _output_window->index);
    if (_hr)
    {
        logger.error("Error creating command buffer");
        return;
    }
    
    VkImageSubresourceRange _sub_resource_range = {};
    _sub_resource_range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    _sub_resource_range.baseMipLevel = 0;
    _sub_resource_range.levelCount = 1;
    _sub_resource_range.baseArrayLayer = 0;
    _sub_resource_range.layerCount = 1;
    

    _output_window->command_buffers.at("clear_color_screen")->set_enable(false);

    
    auto _pipeline = this->_pipeline.get_handle();
    auto _pipeline_layout = this->_pipeline.get_layout_handle();
    
    //record clear screen command buffer for every swap chain image
    for (uint32_t i = 0; i < this->_command_buffers->get_commands_size(); ++i)
    {
        this->_command_buffers->begin(i);
        {
            auto _command_buffer = this->_command_buffers->get_command_at(i);
        
            VkImageMemoryBarrier _present_to_render_barrier =
            {
                VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,                                         // Type
                nullptr,                                                                        // Next
                VK_ACCESS_MEMORY_READ_BIT,                                                      // SrcAccessMask
                VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,                                           // DstAccessMask
                VK_IMAGE_LAYOUT_UNDEFINED,                                                      // OldLayout
                VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,                                       // NewLayout
                _gDevice->vk_present_queue_family_index,                                        // SrcQueueFamilyIndex
                _gDevice->vk_graphics_queue_family_index,                // DstQueueFamilyIndex
                _output_window->vk_swap_chain_image_views[i].image,                             // Image
                _sub_resource_range                                                             // subresourceRange
            };
            
            vkCmdPipelineBarrier(_command_buffer,
                                 VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                                 VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                                 0,
                                 0,
                                 nullptr,
                                 0,
                                 nullptr,
                                 1,
                                 &_present_to_render_barrier);
        
            
            this->_render_pass.begin(_command_buffer,
                                     this->_frame_buffers.get_frame_buffer_at(i));
            
            vkCmdBindPipeline( _command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipeline);
    
            vkCmdSetViewport(_command_buffer, 0, 1, &_wp);
            vkCmdSetScissor(_command_buffer, 0, 1, &_wp_sc);
    
            vkCmdBindDescriptorSets(_command_buffer,
                                    VK_PIPELINE_BIND_POINT_GRAPHICS,
                                    _pipeline_layout,
                                    0,
                                    1,
                                    &_descriptor_set,
                                    0,
                                    nullptr);
            
            VkDeviceSize _offset = 0;
            auto _vertex_buffer_handle = this->_renderable_scene->get_vertex_buffer_handle(0);
            vkCmdBindVertexBuffers( _command_buffer, 0, 1, &_vertex_buffer_handle, &_offset );
        
            auto _index_buffer_handle = this->_renderable_scene->get_index_buffer_handle(0);
            vkCmdBindIndexBuffer( _command_buffer, _index_buffer_handle, 0, VK_INDEX_TYPE_UINT32 );

            //auto _v_c = this->_renderable_scene->get_vertices_count();
            auto _i_c = this->_renderable_scene->get_indices_count(0);
            
            //vkCmdDraw( _command_buffer, _v_c, 1, 0, 0 );
            vkCmdDrawIndexed(_command_buffer, _i_c, 1, 0, 0, 0);
            
            
            //draw second one
            
            _offset = 0;
            _vertex_buffer_handle = this->_renderable_scene->get_vertex_buffer_handle(1);
            vkCmdBindVertexBuffers( _command_buffer, 0, 1, &_vertex_buffer_handle, &_offset );
            
            _index_buffer_handle = this->_renderable_scene->get_index_buffer_handle(1);
            vkCmdBindIndexBuffer( _command_buffer, _index_buffer_handle, 0, VK_INDEX_TYPE_UINT32 );
            
            //auto _v_c = this->_renderable_scene->get_vertices_count();
            _i_c = this->_renderable_scene->get_indices_count(1);
            
            //vkCmdDraw( _command_buffer, _v_c, 1, 0, 0 );
            vkCmdDrawIndexed(_command_buffer, _i_c, 1, 0, 0, 0);
            
            
            //draw third one
            
//            _offset = 0;
//            _vertex_buffer_handle = this->_renderable_scene->get_vertex_buffer_handle(2);
//            vkCmdBindVertexBuffers( _command_buffer, 0, 1, &_vertex_buffer_handle, &_offset );
//            
//            _index_buffer_handle = this->_renderable_scene->get_index_buffer_handle(2);
//            vkCmdBindIndexBuffer( _command_buffer, _index_buffer_handle, 0, VK_INDEX_TYPE_UINT32 );
            
            //auto _v_c = this->_renderable_scene->get_vertices_count();
            //_i_c = this->_renderable_scene->get_indices_count(2);
            
            //vkCmdDraw( _command_buffer, _v_c, 1, 0, 0 );
           // vkCmdDrawIndexed(_command_buffer, _i_c, 1, 0, 0, 0);
            
            this->_render_pass.end(_command_buffer);
            
            //_vertex_buffer_handle = nullptr;
        
            VkImageMemoryBarrier _barrier_from_render_to_present =
            {
                VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,                     // Type
                nullptr,                                                    // Next
                VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,                       // SrcAccessMask
                VK_ACCESS_MEMORY_READ_BIT,                                  // DstAccessMask
                VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,                   // OldLayout
                VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,                            // NewLayout
                _gDevice->vk_graphics_queue_family_index,                    // SrcQueueFamilyIndex
                _gDevice->vk_present_queue_family_index,                   // DstQueueFamilyIndex
                _output_window->vk_swap_chain_image_views[i].image,         // Image
                _sub_resource_range                                         // SubresourceRange
            };
            
            vkCmdPipelineBarrier(_command_buffer,
                             VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                             VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
                             0,
                             0,
                             nullptr,
                             0,
                             nullptr,
                             1,
                             &_barrier_from_render_to_present );
        }
        this->_command_buffers->end(i);
    }
}

static float _jjj = 0;
void scene::update(_In_ const wolf::system::w_game_time& pGameTime)
{
    if (w_game::exiting) return;
    
	glm::mat4x4 _translate = glm::translate(glm::mat4x4(1.0f), glm::vec3(0, 0, 0.0f));
	glm::mat4x4 _rotate = glm::rotate(glm::mat4x4(1.0f), _jjj, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4x4 _scale = glm::scale(glm::mat4x4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    auto _world = glm::mat4(1);// _scale * _rotate * _translate;
	_view_projection_uniform.data = this->_camera->get_projection() * this->_camera->get_view() *_world;
	_view_projection_uniform.update();

	_jjj += 0.01f;
     w_game::update(pGameTime);
}

HRESULT scene::render(_In_ const wolf::system::w_game_time& pGameTime)
{
    return w_game::render(pGameTime);
}

void scene::on_window_resized(_In_ UINT pIndex)
{
    w_game::on_window_resized(pIndex);
}

void scene::on_device_lost()
{
    w_game::on_device_lost();
}

ULONG scene::release()
{
    if (this->get_is_released()) return 0;
    
   _render_pass.release();
    
    //_texture->release();
    _view_projection_uniform.release();
    _shader.release();
    this->_pipeline.release();
    this->_frame_buffers.release();
    
    return w_game::release();
}
