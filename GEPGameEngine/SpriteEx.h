#pragma once
#include "SDL.h"
#include <iostream>
#include <map>
#define FLIPPED_HORIZONTAL(flipped) flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
#define FLIPPED_VERTICAL(flipped) flipped ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE
//this base class will render just one static sprite

class SpriteEx
{
protected:
    SDL_Rect spriteSrcRect; //which part of the spritesheet we would like to render
    SDL_Rect spriteDestRect; //the position on the screen we would like to render this sprite at
    SDL_Texture* texture;
    //first for horizontal second for vertical
    std::pair<bool, bool> flippedDimensions;
    bool isFlipped;
    double angle;//the angle to display sprite (in degrees)
    double m_X, //x coord
        m_Y, //Y coord
        m_DX, //the change in x coord
        m_DY, //the change in Y coordinate
        m_dSpeed; //speed in pixels to move per change
    double m_dRadius; //radius of the sprite's circle bounds
public:
    SpriteEx() {}
    SpriteEx(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect dstRect)
    {
        isFlipped = false;
        texture = tex;
        spriteSrcRect = srcRect;
        spriteDestRect = dstRect;
    }
    void Render();
    void UpdateDestRect();
    double GetRadius() { return m_dRadius; }
    double GetX() { return m_X; }
    double GetY() { return m_Y; }
};
/*Lab Exercise 2
Modify SpriteExAnimated such that:
1. the class allows you to
play a range of frames from within a spritesheet.
Something like: AnimateRange(0,7) -> this should loop and play between frame 0 to 7.
-> Come up with a system to play a range.
-> The system should also allow speed control. Think of ways you could do.
   Simplest could be using sleep but you should explore further such as using
   SDL's timetick functionality and possibly using speed multiplier...
-> Once you come up with a theoretical solution, you can go ahead implement
this if you have time.
->WE will choose one of the proposed solutions and implement it in class as well next week.
*/
struct AnimStateDefinition
{
    short rowIndex;
    short frames;
    short time;
    AnimStateDefinition() {}
    AnimStateDefinition(short ri, short f, short t) : rowIndex(ri), frames(f), time(t) {}
};
//this is the animated version of the Sprite class
class SpriteExAnimated : public SpriteEx
{
private:
    void AnimateRange(AnimStateDefinition asd);
    void Animate();
protected:
    int
        // m_iSprite = 0, //which sprite to display for animation
        // m_iSpriteMax, //how many sprites in total for this animation
        m_iFrame = 0, //which frame we are at now
        m_iFrameMax; //number of frames for this sprite
    Uint32 lastUpdate;
    std::string currentState;
    //Stores various animation states for this spritesheet
    std::map<std::string, AnimStateDefinition> animStates;  
public:
    void AddAnimState(std::string stateName, AnimStateDefinition asd);
    void PlayState(std::string stateName);
    SpriteExAnimated(SDL_Texture* tex, double x, double y,
        double a);
};