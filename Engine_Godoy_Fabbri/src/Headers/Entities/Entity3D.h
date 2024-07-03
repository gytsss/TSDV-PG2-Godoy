#pragma once

#include "Entity.h"
#include "../Exports.h"

namespace ToToEng
{
    class TOTO_API Entity3D :
        public Entity
    {
    
    public:
		
        Entity3D(Renderer* renderer);
        ~Entity3D() override;

        void draw() override;
    };
}
