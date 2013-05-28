//	IrrBull is a very simple engine integrating Irrlicht and Bullet.
//	Copyright (C) 2013 Alejandro Seguí Díaz <alesegdia at gmail dot com>
//
//	IrrBull is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	IrrBull is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with IrrBull.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __CDEBUGDRAW__
#define __CDEBUGDRAW__

#include "common.h"

class CDebugDraw : public btIDebugDraw
{

public:

   CDebugDraw(irr::IrrlichtDevice* const device) :
      mode(DBG_NoDebug), driver(device->getVideoDriver()), logger(device->getLogger())
   {

   }

   void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
   {
      //workaround to bullet's inconsistent debug colors which are either from 0.0 - 1.0 or from 0.0 - 255.0
      irr::video::SColor newColor(255, (irr::u32)color[0], (irr::u32)color[1], (irr::u32)color[2]);
      if (color[0] <= 1.0 && color[0] > 0.0)
         newColor.setRed((irr::u32)(color[0]*255.0));
      if (color[1] <= 1.0 && color[1] > 0.0)
         newColor.setGreen((irr::u32)(color[1]*255.0));
      if (color[2] <= 1.0 && color[2] > 0.0)
         newColor.setBlue((irr::u32)(color[2]*255.0));

      this->driver->draw3DLine(
         irr::core::vector3df(from[0], from[1], from[2]),
         irr::core::vector3df(to[0], to[1], to[2]),
         newColor);
   }

   void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
   {
      static const irr::video::SColor CONTACTPOINT_COLOR(255, 255, 255, 0); //bullet's are black :(

   //   this->drawLine(PointOnB, PointOnB + normalOnB*distance, CONTACTPOINT_COLOR);

      const btVector3 to(PointOnB + normalOnB*distance);

      this->driver->draw3DLine(
         irr::core::vector3df(PointOnB[0], PointOnB[1], PointOnB[2]),
         irr::core::vector3df(to[0], to[1], to[2]),
         CONTACTPOINT_COLOR);
   }

   void reportErrorWarning(const char* text)
   {
      this->logger->log(text, irr::ELL_ERROR);
   }

   void draw3dText(const btVector3& location, const char* text) { }

   void setDebugMode(int mode) { this->mode = mode; }

   int getDebugMode() const { return this->mode; }

private:

   int mode;

   irr::video::IVideoDriver* const driver;

   irr::ILogger* logger;
};


#endif
