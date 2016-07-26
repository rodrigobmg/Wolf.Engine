/*
	Project			 : Wolf Engine. Copyright(c) Pooya Eimandar (http://PooyaEimandar.com) . All rights reserved.
	Source			 : Please direct any bug to https://github.com/PooyaEimandar/Wolf.Engine/issues
	Website			 : http://WolfSource.io
	Name			 : w_control.h
	Description		 : The base control class for gui controls. This class modified and improved based on Microsoft DXUT library https://github.com/Microsoft/DXUT

	Comment          :
*/

#ifndef __W_CONTROL__
#define __W_CONTROL__

#include <w_object.h> 
#include "w_element.h"
#include "w_graphics_device_manager.h"

namespace wolf
{
	namespace gui
	{
		enum W_GUI_CONTROL_TYPE
		{
			W_GUI_CONTROL_BUTTON,
			W_GUI_CONTROL_LABEL,
			W_GUI_CONTROL_IMAGE,
			W_GUI_CONTROL_CHECKBOX,
			W_GUI_CONTROL_RADIOBUTTON,
			W_GUI_CONTROL_COMBOBOX,
			W_GUI_CONTROL_SLIDER,
			W_GUI_CONTROL_EDITBOX,
			W_GUI_CONTROL_IMEEDITBOX,
			W_GUI_CONTROL_LISTBOX,
			W_GUI_CONTROL_SCROLLBAR,
			W_GUI_CONTROL_TAB,
		};

		class w_widget; //forward decleration instead of include this header, because w_widget includes this header too.
		class w_control : public system::w_object
		{
		public:
			w_control(_In_opt_ w_widget* pParent);
			virtual ~w_control();

			virtual HRESULT on_initialize(const std::shared_ptr<wolf::graphics::w_graphics_device>& pGDevice);
			virtual void refresh();
			virtual void render(const std::shared_ptr<wolf::graphics::w_graphics_device>& pGDevice, _In_ float pElapsedTime);

			// Windows message handler
			virtual bool on_msg_proc(_In_ UINT pMsg, _In_ WPARAM pWParam, _In_ LPARAM pLParam);
			virtual bool handle_keyboard(_In_ UINT pMsg, _In_ WPARAM pWParam, _In_ LPARAM pLParam);
			virtual bool handle_mouse(_In_ UINT pMsg, _In_ const POINT& pPoint, _In_ WPARAM pWParam, _In_ LPARAM pLParam);

			virtual bool can_have_focus()								{ return false; }
			
			//Events
			virtual void on_focus_in()									{ this->has_focus = true; }
			virtual void on_focus_out()									{ this->has_focus = false; }
			virtual void on_mouse_enter()								{ this->mouse_over = true; }
			virtual void on_mouse_leave()								{ this->mouse_over = false; }
			virtual void on_hotKey()									{ }

			virtual bool contains_point(_In_ const POINT& pPoint)		{ return PtInRect(&this->boundingBox, pPoint) != 0; }


#pragma region Getters

			virtual bool get_visible() const							{ return this->visible; }
			virtual bool get_enabled() const							{ return this->enabled; }
			UINT get_type() const										{ return this->type; }
			int get_ID() const											{ return this->id; }
			UINT get_hotKey() const										{ return this->hotkey; }
			void* get_tag() const										{ return this->tag; }
			w_element* get_element(_In_ UINT pIndex) const				{ return this->elements[pIndex]; }

#pragma endregion
			
#pragma region Setters

			virtual void set_enabled(_In_ bool pEnabled)				{ this->enabled = pEnabled; }
			virtual void set_visible(_In_ bool pVisible)				{ this->visible = pVisible; }
			void set_ID(_In_ int pID)									{ this->id = pID; }
			void set_location(_In_ int pX, _In_ int pY)					{ this->x = pX; this->y = pY; update_rects(); }
			void set_size(int pWidth, int pHeight)						{ this->width = pWidth; this->height = pHeight; update_rects();}
			void set_hotKey(_In_ UINT pHotkey)							{ this->hotkey = pHotkey; }
			void set_tag(_In_opt_ void* pUserData)						{ this->tag = pUserData; }

			HRESULT set_element(_In_ UINT pIndexElement, _In_ w_element* pElement);

#pragma endregion

			bool visible;// Shown/hidden flag
			bool mouse_over;// Mouse pointer is above control
			bool has_focus;// Control has input focus
			bool is_default;// Is the default control

			// Size, scale, and positioning members
			int x;
			int y;
			int width;
			int height;

			// Parent container
			w_widget* parent_widget;
			UINT index;

			std::vector<w_element*> elements;// All display elements

		protected:
			virtual void update_rects();

			int id;// ID number                 
			W_GUI_CONTROL_TYPE type;// Control type, set once in constructor    
			UINT hotkey;// Virtual key code for this control's hotkey                
			bool enabled;// Enabled/disabled flag           
			RECT boundingBox;// Rectangle defining the active region of the control
			void* tag;// Data associated with this control that is set by user.     

		private:
			typedef system::w_object			_super;
		};
	}
}

#endif