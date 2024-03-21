#pragma once
#include "Animation.h"
#include "Entity2D.h"

namespace ToToEng
{
    class TOTO_API Sprite :
        public Entity2D
    {
    private:
        unsigned int texture;
        bool hasAnimation;

    protected:
        void update() override;
        
    public:
        Animation* animation;
        Sprite(Renderer* renderer);
        ~Sprite() override;
        
        void draw() override;
        void loadTexture(const char* filePath);
        void addAnimation(float duration, int frameQty, int animQty, const char* filePath, vec2 offset, vec2 frameSize);

        void setHasAnimation(bool hasAnimation);
    };
}
