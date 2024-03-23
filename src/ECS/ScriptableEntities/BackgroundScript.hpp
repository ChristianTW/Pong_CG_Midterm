#pragma once
#include <string>
#include <vector>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>

class BackgroundScript: public Canis::ScriptableEntity
{
    bool moving = false;
    float weirdMoveX;
    float weirdMoveY;
    bool flagTempX = false;
    int secretCount = 0;
    bool doOnce = false;

public:

    void OnCreate()
    {
        weirdMoveX = GetWindow().GetScreenWidth();
        weirdMoveY = GetWindow().GetScreenHeight();
    }

    void OnReady()
    {
        
    }
    
    void OnDestroy()
    {

    }

    void OnUpdate(float _dt)
    {
       auto& rect = GetComponent<Canis::RectTransformComponent>();
       
       if(!moving)
       {
        rect.size.x = GetWindow().GetScreenWidth();
        rect.size.y = GetWindow().GetScreenHeight();
        weirdMoveX = GetWindow().GetScreenWidth();
        weirdMoveY = GetWindow().GetScreenHeight();
       }
       else
       {
        rect.size.x = weirdMoveX;
        rect.size.y = weirdMoveY;
       }
       if(moving){
       //start of x math
       if (weirdMoveX <= GetWindow().GetScreenWidth() + (GetWindow().GetScreenWidth() / 2) && !flagTempX)
       {
            weirdMoveX = weirdMoveX + 2.5f;
       }
       if (weirdMoveX >= GetWindow().GetScreenWidth() + (GetWindow().GetScreenWidth() / 2))
       {
            flagTempX = true;
       }
       if (flagTempX && weirdMoveX >= GetWindow().GetScreenWidth())
       {
            weirdMoveX = weirdMoveX - 3.5f;
       }
       if (weirdMoveX <= GetWindow().GetScreenWidth())
       {
            flagTempX = false;
       }
       //start of y math
       if (flagTempX && weirdMoveY <= GetWindow().GetScreenHeight() + (GetWindow().GetScreenHeight() / 2))
       {
            weirdMoveY = weirdMoveY + 2.5f;
       }

       if (!flagTempX && weirdMoveY >= GetWindow().GetScreenHeight())
       {
            weirdMoveY = weirdMoveY - 2.5f;
       }


       }



        if(GetInputManager().GetKey(SDL_SCANCODE_K))
        {
            if (secretCount != 0)
            {
                secretCount = 0;
            }
            secretCount = 1;
            doOnce = false;
        }
        if(GetInputManager().GetKey(SDL_SCANCODE_N))
        {
            if (secretCount != 1)
            {
                secretCount = 0;
            }
            secretCount = 2;
        }
        if(GetInputManager().GetKey(SDL_SCANCODE_U))
        {
            if (secretCount != 2)
            {
                secretCount = 0;
            }
            secretCount = 3;
        }
        if(GetInputManager().GetKey(SDL_SCANCODE_X))
        {
            if (secretCount != 3)
            {
                secretCount = 0;
            }
            secretCount = 4;
        }
        if(secretCount == 4 && doOnce == false)
        {
            doOnce = true;
            if(!moving && secretCount == 4)  //i know the doOnce and moving checks thing is ugly and could be cleaner, but hey, it works and doesnt fire more than once
            {
                moving = true;
                Canis::Log("ON");
                secretCount = 0;
            }
            if(moving && secretCount == 4)
            {
                moving = false;
                Canis::Log("OFF");
                secretCount = 0;
            }
            
        }






    }
};

bool DecodeBackgroundScript(const std::string &_name, Canis::Entity &_entity)
{
    if (_name == "BackgroundScript")
    {
        Canis::ScriptComponent scriptComponent = {};
        scriptComponent.Bind<BackgroundScript>();
        _entity.AddComponent<Canis::ScriptComponent>(scriptComponent);

        

        return true;
    }
    return false;
}