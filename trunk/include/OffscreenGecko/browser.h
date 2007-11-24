/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is OffscreenGecko code.
 *
 * The Initial Developer of the Original Code is
 * Frank Richter <frank.richter@gmail.com>.
 * Portions created by the Initial Developer are Copyright (C) 2007
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef __OFFSCREENGECKO_BROWSER_H__
#define __OFFSCREENGECKO_BROWSER_H__

/**\file
 * Browser object
 */

#include "embedding.h"

/**
 * Browser - encapsulates the display of content.
 */
typedef OSGK_BaseObject OSGK_Browser;

/**
 * Create a new browser object. Browsers encapsulate the display of content.
 * \param embedding Parent embedding object.
 * \param width Width of the display area.
 * \param height Height of the display area.
 */
OSGK_EXTERN_C OSGK_API OSGK_Browser* osgk_browser_create (
  OSGK_Embedding* embedding, int width, int height);

/**
 * Navigate a browser to a given URI.
 * \param browser The browser object.
 * \param uri The URI to navigate to. Encoding is UTF-8.
 */
OSGK_EXTERN_C OSGK_API void osgk_browser_navigate (OSGK_Browser* browser,
  const char* uri);

/**\name Pixel data acquisition
 * @{ */
/**
 * Query if a browser object is 'dirty' (if the displayed data has changed
 * since the last time the data was requested).
 * \param browser The browser object.
 * \returns 0 if data is unchanged, 1 if changed.
 */
OSGK_EXTERN_C OSGK_API int osgk_browser_query_dirty (OSGK_Browser* browser);

/**
 * Lock the pixel data for a browser object.
 * \param browser The browser object.
 * \param isDirty Returns whether the browser is 'dirty' (ie the displayed 
 *   data has changed since the last time the data was requested). Can be 0.
 * \returns A pointer to the pixel data, in BGRA byte order. Alpha is
 *   premultiplied.
 * \remarks You need to call osgk_browser_unlock_data() after finishing
 *   processing the returned data.
 */
OSGK_EXTERN_C OSGK_API const unsigned char* osgk_browser_lock_data (
  OSGK_Browser* browser, int* isDirty OSGK_DEFAULT_ARG(0));

/**
 * Unlock the pixel data for a browser object obtained by an earlier 
 * osgk_browser_lock_data() call.
 * \param browser The browser object.
 * \param data The data pointer as returned  by osgk_browser_lock_data().
 * \warning Do not use the data after this function!
 */
OSGK_EXTERN_C OSGK_API void osgk_browser_unlock_data (OSGK_Browser* browser,
  const unsigned char* data);

/** @} */

/**\name Mouse events
 * @{ */
 
/// Mouse button ID
enum OSGK_MouseButton
{
  /// Left mouse button
  mbLeft, 
  /// Right mouse button
  mbRight, 
  /// Middle mouse button
  mbMiddle
};

/// Type of mouse button event
enum OSGK_MouseButtonEventType
{
  /// Mouse button was pressed
  meDown,
  /// Mouse button was released
  meUp,
  /// Mouse button was double-clicked
  meDoubleClick
};

/**
 * Send a mouse move event to a browser object.
 * \param browser The browser object.
 * \param x The X coordinate of the new mouse cursor position.
 * \param y The Y coordinate of the new mouse cursor position.
 */
OSGK_EXTERN_C OSGK_API void osgk_browser_event_mouse_move (
  OSGK_Browser* browser, int x, int y);

/**
 * Send a mouse button event to a browser object.
 * \param browser The browser object.
 * \param button The affected button.
 * \param eventType The type of event.
 */
OSGK_EXTERN_C OSGK_API void osgk_browser_event_mouse_button (
  OSGK_Browser* browser, OSGK_MouseButton button, 
  OSGK_MouseButtonEventType eventType);

/** @} */

/**\name Keyboard events
 * \sa \ref KeyboardInputNotes "Keyboard input notes"
 * @{ */
 
/// Type of keyboard event
enum OSGK_KeyboardEventType
{
  /// Key was pressed
  keDown,
  /// Key was released
  keUp,
  /// Key was pressed
  kePress
};

/// Supported keys for up/down keyboard events
enum
{
  ///\internal Code of first OffscreenGecko key code
  OSGKKey_First = 0x110000,

  OSGKKey_Backspace = OSGKKey_First,
  OSGKKey_Tab,
  OSGKKey_Return,
  OSGKKey_Shift,
  OSGKKey_Control,
  OSGKKey_Alt,
  OSGKKey_CapsLock,
  OSGKKey_Escape,
  OSGKKey_Space,
  OSGKKey_PageUp,
  OSGKKey_PageDown,
  OSGKKey_End,
  OSGKKey_Home,
  OSGKKey_Left,
  OSGKKey_Up,
  OSGKKey_Right,
  OSGKKey_Down,
  OSGKKey_Insert,
  OSGKKey_Delete,
  OSGKKey_F1,
  OSGKKey_F2,
  OSGKKey_F3,
  OSGKKey_F4,
  OSGKKey_F5,
  OSGKKey_F6,
  OSGKKey_F7,
  OSGKKey_F8,
  OSGKKey_F9,
  OSGKKey_F10,
  OSGKKey_F11,
  OSGKKey_F12,
  OSGKKey_NumLock,
  OSGKKey_ScrollLock,
  OSGKKey_Meta
};

/**\page KeyboardInputNotes Notes on keyboard input
 * For a key you should either send one (or more) keDown events and a one
 * keUp event or a single kePress event, but not both.
 */

/**
 * Send keyboard input to a browser object.
 * \param browser The browser object.
 * \param key The code of the affected key. It can be either one of the 
 *   OSGKKey_ codes are a Unicode character.
 * \param eventType The type of event.
 * \returns Whether the key was handled (non-zero) or not (zero).
 * \sa \ref KeyboardInputNotes, OSGKKey_Backspace
 */
OSGK_EXTERN_C OSGK_API int osgk_browser_event_key (
  OSGK_Browser* browser, unsigned int key,
  OSGK_KeyboardEventType eventType);

/** @} */

#ifdef __cplusplus
namespace OSGK
{
  /**
   * Browser - encapsulates the display of content.
   * \sa \ref BasicsCXX
   */
  struct Browser : public CXXAPI::Wrap<OSGK_Browser>
  {
    /**
     * Create a new browser object. Browsers encapsulate the display of content.
     * \param embedding Parent embedding object.
     * \param width Width of the display area.
     * \param height Height of the display area.
     */
    Browser (Embedding& embedding, int width, int height) : 
      WrapperType (osgk_browser_create (embedding.GetObject(),
        width, height)) { }

    explicit Browser (WrappedType* obj) : WrapperType (obj) {}
    Browser& operator=(const Browser& other)
    {
      WrapperType::operator=(other);
      return *this;
    }
    
    /**
     * Navigate a given URI.
     * \param uri The URI to navigate to. Encoding is UTF-8.
     */
    void Navigate (const char* uri)
    {
      osgk_browser_navigate (GetObject(), uri);
    }
    
    /**\name Pixel data acquisition
     * @{ */
    /**
     * Query if the browser object is 'dirty' (if the displayed data has changed
     * since the last time the data was requested).
     * \returns \c false if data is unchanged, \c true if changed.
     */
    bool IsDirty()
    {
      return osgk_browser_query_dirty (GetObject()) != 0;
    }
    /**
     * Lock the pixel data for the browser object.
     * \returns A pointer to the pixel data, in BGRA byte order. Alpha is
     *   premultiplied.
     * \remarks You need to call UnlockData() after finishing
     *   processing the returned data.
     */
    const unsigned char* LockData()
    {
      return osgk_browser_lock_data (GetObject ());
    }
    /**
     * Lock the pixel data for the browser object.
     * \param isDirty Returns whether the browser is 'dirty' (ie the displayed 
     *   data has changed since the last time the data was requested).
     * \returns A pointer to the pixel data, in BGRA byte order. Alpha is
     *   premultiplied.
     * \remarks You need to call UnlockData() after finishing
     *   processing the returned data.
     */
    const unsigned char* LockData(bool& isDirty)
    {
      int d;
      const unsigned char* p = osgk_browser_lock_data (GetObject (), &d);
      isDirty = d != 0;
      return p;
    }
    /**
     * Unlock the pixel data for the browser object obtained by an earlier 
     * LockData() call.
     * \param data The data pointer as returned by LockData().
     * \warning Do not use the data after this function!
     */
    void UnlockData (const unsigned char* data)
    {
      osgk_browser_unlock_data (GetObject (), data);
    }
    /** @} */

    /**\name Mouse events
     * @{ */
    /**
     * Send a mouse move event to the browser object.
     * \param x The X coordinate of the new mouse cursor position.
     * \param y The Y coordinate of the new mouse cursor position.
     */
    void EventMouseMove (int x, int y)
    {
      osgk_browser_event_mouse_move (GetObject(), x, y);
    }

    /**
     * Send a mouse button event to the browser object.
     * \param button The affected button.
     * \param eventType The type of event.
     */
    void EventMouseButton (OSGK_MouseButton button, 
      OSGK_MouseButtonEventType eventType)
    {
      osgk_browser_event_mouse_button (GetObject(), button, eventType);
    }
    /** @} */

    /**\name Keyboard events
     * \sa \ref KeyboardInputNotes "Keyboard input notes"
     * @{ */
    /**
     * Send keyboard input to the browser object.
     * \param key The code of the affected key. It can be either one of the 
     *   OSGKKey_ codes are a Unicode character.
     * \param eventType The type of event.
     * \returns Whether the key was handled (non-zero) or not (zero).
     * \sa \ref KeyboardInputNotes, OSGKKey_Backspace
     */
    bool EventKey (unsigned int key, OSGK_KeyboardEventType eventType)
    {
      return osgk_browser_event_key (GetObject(), key, eventType) != 0;
    }
    /** @} */
  };
  
} // namespace OSGK
#endif

#endif // __OFFSCREENGECKO_BROWSER_H__
