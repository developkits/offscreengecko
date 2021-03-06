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

#ifndef __OFFSCREENGECKO_REF_H__
#define __OFFSCREENGECKO_REF_H__

#ifdef __cplusplus

/**\file
 * General reference counting template
 */

#include "OffscreenGecko/baseobj.h"

namespace OSGK
{
  template<typename T>
  class Ref
  {
    T* obj;
  public:
    Ref() : obj (0) {}
    Ref (T* obj) : obj (obj)
    {
      if (obj != 0) obj->AddRef ();
    }
    Ref (const Ref& other) : obj (other.obj)
    {
      if (obj != 0) obj->AddRef ();
    }
    ~Ref()
    {
      if (obj != 0) obj->Release ();
    }
    
    Ref& operator=(T* otherObj)
    {
      if (otherObj != 0) otherObj->AddRef();
      if (obj != 0) obj->Release ();
      obj = otherObj;
      return *this;
    }
    
    Ref& operator=(const Ref& other)
    {
      return operator=(other.obj);
    }

    operator T* ()
    {
      return obj;
    }

    T* operator-> ()
    {
      return obj;
    }
    
    void AttachNew (T* obj)
    {
      OSGK_ASSERT(obj != this->obj);
      if (this->obj != 0) this->obj->Release ();
      this->obj = obj;
    }
  };
} // namespace OSGK

#endif // __cplusplus

#endif // __OFFSCREENGECKO_REF_H__
