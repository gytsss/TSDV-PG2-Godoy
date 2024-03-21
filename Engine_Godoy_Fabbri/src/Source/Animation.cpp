#include "Animation.h"

#include "Entity.h"
#include "GameTime.h"

void Animation::updateFrame()
{
    curFrame = static_cast<int>(curTime / frameTime) ;
}

void Animation::updateOffset()
{
    curOffset.x = (static_cast<float>(curFrame) * frameSize.x) + animOffset.x;
    curOffset.y = static_cast<float>(curAnim) * frameSize.y + animOffset.y;
}

Animation::Animation(float duration, int frameQty, int animQty, glm::vec2 offset, glm::vec2 frameSize)
{
    this->duration = duration;
    this->frameQty = frameQty;
    this->animQty = animQty;

    this->frameSize.x = frameSize.x;
    this->frameSize.y = frameSize.y;

    curOffset.x = 0;
    curOffset.y = 0;
    animOffset.x = offset.x;
    animOffset.y = offset.y;

    curTime = 0;
    frameTime = duration / static_cast<float>(frameQty);
    curFrame = 0;
    curAnim = 0;
    playAnimation = true;
}

Animation::~Animation()
{
}

void Animation::update()
{
    curTime += ToToEng::GameTime::getDelta();
    
    if (!playAnimation)
        return;


    while (curTime >= duration)
        curTime -= duration;

    updateFrame();
    updateOffset();
}

void Animation::setAnimByIndex(int animNumber)
{
    if (animNumber >= 0 && animNumber < animQty)
        curAnim = animNumber;
}

void Animation::setPlayAnim(bool playAnim)
{
    this->playAnimation = playAnim;
}

int Animation::getAnimIndex()
{
    return curAnim;
}

glm::vec2 Animation::getOffset()
{
    return curOffset;
}

glm::vec2 Animation::getFrameSize()
{
    return frameSize;
}
