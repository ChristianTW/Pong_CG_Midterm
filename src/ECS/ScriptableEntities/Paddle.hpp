#pragma once
#include <string>
#include <vector>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>

class Paddle : public Canis::ScriptableEntity
{
    int leftPaddlePositionX;
    int rightPaddlePositionX;
    int leftPaddlePositionY;
    int rightPaddlePositionY;

    Canis::Entity leftPaddle;
    Canis::Entity rightPaddle;

public:
    void OnCreate()
    {
        Canis::Log("Paddle Loaded");
        leftPaddlePositionX = -608;
        rightPaddlePositionX = 608;
        leftPaddle = entity.GetEntityWithTag("paddleLeft");
        rightPaddle = entity.GetEntityWithTag("paddleRight");
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

        if(GetInputManager().GetKey(SDL_SCANCODE_W))
        {
            if (leftPaddlePositionY <= (360 - (leftPaddle.GetComponent<Canis::RectTransformComponent>().size.y / 2)))
            {
                leftPaddlePositionY= leftPaddlePositionY + 3; //put some sort of speed up to this, 1 pixel a frame is slow.
            }
        }
        if(GetInputManager().GetKey(SDL_SCANCODE_S))
        {
            if (leftPaddlePositionY >= (-360 + (leftPaddle.GetComponent<Canis::RectTransformComponent>().size.y / 2)))
            {
                leftPaddlePositionY = leftPaddlePositionY - 3;
            }
        }
        if(GetInputManager().GetKey(SDL_SCANCODE_UP))
        {
            if (rightPaddlePositionY <= (360 - (rightPaddle.GetComponent<Canis::RectTransformComponent>().size.y / 2)))
            {
                rightPaddlePositionY= rightPaddlePositionY + 3; //put some sort of speed up to this, 1 pixel a frame is slow.
            }
        }
        if(GetInputManager().GetKey(SDL_SCANCODE_DOWN))
        {
            if (rightPaddlePositionY >= (-360 + (rightPaddle.GetComponent<Canis::RectTransformComponent>().size.y / 2)))
            {
                rightPaddlePositionY = rightPaddlePositionY - 3;
            }
        }




        
            leftPaddle.GetComponent<Canis::RectTransformComponent>().position.x = leftPaddlePositionX;
            leftPaddle.GetComponent<Canis::RectTransformComponent>().position.y = leftPaddlePositionY;

        
            rightPaddle.GetComponent<Canis::RectTransformComponent>().position.x = rightPaddlePositionX;
            rightPaddle.GetComponent<Canis::RectTransformComponent>().position.y = rightPaddlePositionY;
    }
};

bool DecodePaddle(const std::string &_name, Canis::Entity &_entity)
{
    if (_name == "Paddle")
    {
        Canis::ScriptComponent scriptComponent = {};
        scriptComponent.Bind<Paddle>();
        _entity.AddComponent<Canis::ScriptComponent>(scriptComponent);
        return true;
    }
    return false;
}