#include "w_render_pch.h"
#include "w_shapes.h"
#include "w_mesh.h"
#include "w_pipeline.h"
#include "w_shader.h"
#include "w_uniform.h"
#include "w_command_buffer.h"

namespace wolf
{
    namespace graphics
    {
		class w_shapes_pimp
		{
		public:
			w_shapes_pimp(_In_ wolf::system::w_bounding_box& pBoundingBox, _In_ const w_color& pColor) :
				_name("w_shapes"),
				_gDevice(nullptr),
                _bounding_box(pBoundingBox),
                _shape_type(shape_type::BOX)
			{
			}

			HRESULT load(
				_In_ const std::shared_ptr<w_graphics_device>& pGDevice,
				_In_ const wolf::graphics::w_render_pass& pRenderPass,
				_In_ const wolf::graphics::w_viewport& pViewport,
				_In_ const wolf::graphics::w_viewport_scissor& pViewportScissor)
			{
				const std::string _trace_info = this->_name + "::load";

				this->_gDevice = pGDevice;
                
                std::vector<float> _vertices;
                switch(_shape_type)
                {
                    case shape_type::BOX:
                        _generate_bounding_box_vertices(_vertices);
                    break;
                };

				this->_shape_drawer.set_vertex_binding_attributes(w_vertex_declaration::VERTEX_POSITION_COLOR);
				auto _hr = this->_shape_drawer.load(
					this->_gDevice,
					_vertices.data(),
					static_cast<uint32_t>(_vertices.size() * sizeof(float)),
					(uint32_t)64,
					nullptr,
					0);
				if (_hr == S_FALSE)
				{
					release();
					V(S_FALSE, "loading mesh", _trace_info, 3, true);
					return S_FALSE;
				}

				//loading vertex shaders
				_hr = this->_shader.load(_gDevice,
					content_path + L"shaders/shader.vert.spv",
					w_shader_stage::VERTEX_SHADER);
				if (_hr == S_FALSE)
				{
					release();
					V(S_FALSE, "loading vertex shader", _trace_info, 3, true);
					return S_FALSE;
				}

				//loading fragment shader
				_hr = this->_shader.load(_gDevice,
					content_path + L"shaders/shader.frag.spv",
					w_shader_stage::FRAGMENT_SHADER);
				if (_hr == S_FALSE)
				{
					release();
					V(S_FALSE, "loading fragment shader", _trace_info, 3, true);
					return S_FALSE;
				}

				//load vertex shader uniform
				_hr = this->_u0.load(_gDevice);
				if (_hr == S_FALSE)
				{
					release();
					V(S_FALSE, "loading vertex shader uniform", _trace_info, 3, true);
				}

				std::vector<w_shader_binding_param> _shader_params;

				w_shader_binding_param _shader_param;
				_shader_param.index = 0;
				_shader_param.type = w_shader_binding_type::UNIFORM;
				_shader_param.stage = w_shader_stage::VERTEX_SHADER;
				_shader_param.buffer_info = this->_u0.get_descriptor_info();
				_shader_params.push_back(_shader_param);

				_hr = this->_shader.set_shader_binding_params(_shader_params);
				if (_hr == S_FALSE)
				{
					release();
					V(S_FALSE, "setting shader binding param", _trace_info, 3, true);
				}

				//loading pipeline cache
				std::string _pipeline_cache_name = "line_pipeline_cache";
				if (w_pipeline::create_pipeline_cache(_gDevice, _pipeline_cache_name) == S_FALSE)
				{
					logger.error("could not create pipeline cache for w_shapes: line_pipeline_cache");
					_pipeline_cache_name.clear();
				}

				auto _descriptor_set_layout_binding = this->_shader.get_descriptor_set_layout();
				_hr = this->_pipeline.load(_gDevice,
					this->_shape_drawer.get_vertex_binding_attributes(),
					VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
					pRenderPass.get_handle(),
					this->_shader.get_shader_stages(),
					_descriptor_set_layout_binding ? &_descriptor_set_layout_binding : nullptr,
					{ pViewport },
					{ pViewportScissor });
				if (_hr == S_FALSE)
				{
					release();
					V(S_FALSE, "creating solid pipeline", _trace_info, 3, true);
					return S_FALSE;
				}

				return S_OK;
			}

			HRESULT draw(_In_ VkCommandBuffer pCommandBuffer,
				_In_ const wolf::system::w_game_time pGameTime)
			{
				const std::string _trace_info = this->_name + "::draw";

//                //we must update uniform
//                this->_u0.data.wvp = glm::mat4(1);//identity
//                auto _hr = this->_u0.update();
//                if (_hr == S_FALSE)
//                {
//                    V(S_FALSE, "updating uniform", _trace_info, 3, false);
//                    return S_FALSE;
//                }
//
//                //Calculate the total number of vertices of active shapes
//                int _vertex_count = 0;
//                for (auto shape : this->_active_shapes)
//                {
//                    _vertex_count += shape->line_count * 2;
//                }
//
//                //If we have some vertices to draw
//                if (_vertex_count > 0)
//                {
//                    // Make sure our array is large enough
//                    if (_vertices.size() < _vertex_count)
//                    {
//                        //resize buffer
//                        _vertices.resize(_vertex_count * 2);
//                    }
//
//                    // Now go through the shapes again to move the vertices to our array
//                    int _line_count = 0;
//                    int _vert_index = 0;
//                    for (auto shape : this->_active_shapes)
//                    {
//                        _line_count += shape->line_count;
//                        int _shape_verts = shape->line_count * 2;
//                        for (int i = 0; i < _shape_verts; i++, _vert_index += 7)
//                        {
//                            _vertices[_vert_index] = shape->vertices[i]->data[0];
//                            _vertices[_vert_index + 1] = shape->vertices[i]->data[1];
//                            _vertices[_vert_index + 2] = shape->vertices[i]->data[2];
//                            _vertices[_vert_index + 3] = shape->vertices[i]->data[3];
//                            _vertices[_vert_index + 4] = shape->vertices[i]->data[4];
//                            _vertices[_vert_index + 5] = shape->vertices[i]->data[5];
//                            _vertices[_vert_index + 6] = shape->vertices[i]->data[6];
//                            _vertices[_vert_index + 7] = shape->vertices[i]->data[7];
//                        }
//                    }
//
//                    auto _description_set = this->_shader.get_descriptor_set();
//                    this->_pipeline.bind(pCommandBuffer, &_description_set);
//
//                    /*
//                        We draw in a loop because the Reach profile only supports 65,535 primitives. While it's
//                        not incredibly likely, if a game tries to render more than 65,535 lines we don't want to
//                        crash. We handle this by doing a loop and drawing as many lines as we can at a time, capped
//                        at our limit. We then move ahead in our vertex array and draw the next set of lines.
//                    */
//                    int _vertex_offset = 0;
//                    while (_line_count > 0)
//                    {
//                        //figure out how many lines we're going to draw
//                        int _lines_to_draw = std::min(_line_count, 65535);
//
//                        // Draw the lines
//                        this->_shapes_drawer.update_dynamic_buffer(
//                            this->_gDevice,
//                            this->_vertices.data(),
//                            sizeof(vertex_position_color),
//                            _lines_to_draw,
//                            nullptr,
//                            0);
//
//                        _hr = this->_shapes_drawer.draw(pCommandBuffer, nullptr, 0, false, _vertex_offset);
//                        if (_hr == S_FALSE)
//                        {
//                            V(S_FALSE, "drawing mesh", _trace_info, 3, false);
//                        }
//
//                        //move our vertex offset ahead based on the lines we drew
//                        _vertex_offset += _lines_to_draw * 2;
//
//                        //remove these lines from our total line count
//                        _line_count -= _lines_to_draw;
//                    }
//                }
//
//                //go through our active shapes and retire any shapes that have expired to the cache list.
//                bool _resort = false;
//                for (int i = (int)this->_active_shapes.size() - 1; i >= 0; i--)
//                {
//                    auto _shape = this->_active_shapes[i];
//                    _shape->life_time -= wolf::system::w_time_span::from_seconds(pGameTime.get_total_seconds());
//                    if (_shape->life_time <= wolf::system::w_time_span::zero())
//                    {
//                        this->_cached_shapes.push_back(_shape);
//                        this->_active_shapes.erase(this->_active_shapes.begin() + i);
//                        _resort = true;
//                    }
//                }
//
//                //if we move any shapes around, we need to resort the cached list to ensure that the smallest shapes are first in the list.
//                if (_resort)
//                {
//                    std::sort(this->_cached_shapes.begin(), this->_cached_shapes.end(), [](_In_ const shape* pS1, _In_ const shape* pS2)
//                    {
//                        return pS1 && pS2 && pS1->vertices.size() > pS2->vertices.size();
//                    });
//                }

                return S_OK;//_hr;
			}
            
			void release()
			{
				this->_name.clear();
                
				this->_shape_drawer.release();
				this->_shader.release();
				this->_pipeline.release();
				this->_u0.release();

				this->_gDevice = nullptr;
			}

        private:
            void _generate_bounding_box_vertices(_Inout_ std::vector<float>& pVertices)
            {
                std::array<glm::vec3, 8> _corners;
                this->_bounding_box.get_corners(_corners);
                
//                //Fill in the vertices for the bottom of the box
//                _shape->vertices[0] = new (std::nothrow) vertex_position_color(_corners[0], pColor);
//                if (!_shape->vertices[0]) return S_FALSE;
//                _shape->vertices[1] = new (std::nothrow) vertex_position_color(_corners[1], pColor);
//                if (!_shape->vertices[1]) return S_FALSE;
//                _shape->vertices[2] = new (std::nothrow) vertex_position_color(_corners[1], pColor);
//                if (!_shape->vertices[2]) return S_FALSE;
//                _shape->vertices[3] = new (std::nothrow) vertex_position_color(_corners[2], pColor);
//                if (!_shape->vertices[3]) return S_FALSE;
//                _shape->vertices[4] = new (std::nothrow) vertex_position_color(_corners[2], pColor);
//                if (!_shape->vertices[4]) return S_FALSE;
//                _shape->vertices[5] = new (std::nothrow) vertex_position_color(_corners[3], pColor);
//                if (!_shape->vertices[5]) return S_FALSE;
//                _shape->vertices[6] = new (std::nothrow) vertex_position_color(_corners[3], pColor);
//                if (!_shape->vertices[6]) return S_FALSE;
//                _shape->vertices[7] = new (std::nothrow) vertex_position_color(_corners[0], pColor);
//                if (!_shape->vertices[7]) return S_FALSE;
                
                //                //Fill in the vertices for the top of the box
                //                _shape->vertices[8] = new (std::nothrow) vertex_position_color(_corners[4], pColor);
                //                if (!_shape->vertices[8]) return S_FALSE;
                //                _shape->vertices[9] = new (std::nothrow) vertex_position_color(_corners[5], pColor);
                //                if (!_shape->vertices[9]) return S_FALSE;
                //                _shape->vertices[10] = new (std::nothrow) vertex_position_color(_corners[5], pColor);
                //                if (!_shape->vertices[10]) return S_FALSE;
                //                _shape->vertices[11] = new (std::nothrow) vertex_position_color(_corners[6], pColor);
                //                if (!_shape->vertices[11]) return S_FALSE;
                //                _shape->vertices[12] = new (std::nothrow) vertex_position_color(_corners[6], pColor);
                //                if (!_shape->vertices[12]) return S_FALSE;
                //                _shape->vertices[13] = new (std::nothrow) vertex_position_color(_corners[7], pColor);
                //                if (!_shape->vertices[13]) return S_FALSE;
                //                _shape->vertices[14] = new (std::nothrow) vertex_position_color(_corners[7], pColor);
                //                if (!_shape->vertices[14]) return S_FALSE;
                //                _shape->vertices[15] = new (std::nothrow) vertex_position_color(_corners[4], pColor);
                //                if (!_shape->vertices[15]) return S_FALSE;
                //
                //                //Fill in the vertices for the vertical sides of the box
                //                _shape->vertices[16] = new (std::nothrow) vertex_position_color(_corners[0], pColor);
                //                if (!_shape->vertices[16]) return S_FALSE;
                //                _shape->vertices[17] = new (std::nothrow) vertex_position_color(_corners[4], pColor);
                //                if (!_shape->vertices[17]) return S_FALSE;
                //                _shape->vertices[18] = new (std::nothrow) vertex_position_color(_corners[1], pColor);
                //                if (!_shape->vertices[18]) return S_FALSE;
                //                _shape->vertices[19] = new (std::nothrow) vertex_position_color(_corners[5], pColor);
                //                if (!_shape->vertices[19]) return S_FALSE;
                //                _shape->vertices[20] = new (std::nothrow) vertex_position_color(_corners[2], pColor);
                //                if (!_shape->vertices[20]) return S_FALSE;
                //                _shape->vertices[21] = new (std::nothrow) vertex_position_color(_corners[6], pColor);
                //                if (!_shape->vertices[21]) return S_FALSE;
                //                _shape->vertices[22] = new (std::nothrow) vertex_position_color(_corners[3], pColor);
                //                if (!_shape->vertices[22]) return S_FALSE;
                //                _shape->vertices[23] = new (std::nothrow) vertex_position_color(_corners[7], pColor);
                //                if (!_shape->vertices[23]) return S_FALSE;
            }
            
            enum shape_type
            {
                BOX
            } _shape_type;
			std::string                                             _name;
			std::shared_ptr<w_graphics_device>                      _gDevice;
			w_mesh													_shape_drawer;
			wolf::graphics::w_pipeline                              _pipeline;		
			wolf::graphics::w_shader                                _shader;

			struct U0
			{
				glm::mat4	wvp;
			};
			wolf::graphics::w_uniform<U0>                           _u0;
            
            wolf::system::w_bounding_box                            _bounding_box;

        };
    }
}

using namespace wolf::system;
using namespace wolf::graphics;

w_shapes::w_shapes(_In_ wolf::system::w_bounding_box& pBoundingBox, _In_ const w_color& pColor) :
    _pimp(new w_shapes_pimp(pBoundingBox, pColor))
{
    _super::set_class_name("w_shapes");
}

w_shapes::~w_shapes()
{
    release();
}

HRESULT w_shapes::load(_In_ const std::shared_ptr<w_graphics_device>& pGDevice,
	_In_ const w_render_pass& pRenderPass,
	_In_ const w_viewport& pViewport,
	_In_ const w_viewport_scissor& pViewportScissor)
{
	return (!this->_pimp) ? S_FALSE : this->_pimp->load(pGDevice, pRenderPass, pViewport, pViewportScissor);
}

HRESULT w_shapes::draw(
    _In_ VkCommandBuffer pCommandBuffer,
    _In_ const w_game_time pGameTime)
{
    return (!this->_pimp) ? S_FALSE : this->_pimp->draw(pCommandBuffer, pGameTime);
}

ULONG w_shapes::release()
{
    if (_super::get_is_released()) return 1;
 
    //release the private implementation
    SAFE_RELEASE(this->_pimp);
    
    return _super::release();
}