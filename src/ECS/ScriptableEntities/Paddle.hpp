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
        leftPaddlePositionX = (GetWindow().GetScreenWidth() / -2.0f) + 32; // set paddle's x position to 32 before whatever edge of the screen its on
        rightPaddlePositionX = (GetWindow().GetScreenWidth() / 2.0f) - 32;
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
        auto &rect = GetComponent<Canis::RectTransformComponent>();

        if (GetInputManager().GetKey(SDL_SCANCODE_W) && !GetInputManager().GetKey(SDL_SCANCODE_S))
        {
            if (leftPaddlePositionY <= (360 - (leftPaddle.GetComponent<Canis::RectTransformComponent>().size.y / 2)))
            {
                leftPaddlePositionY = leftPaddlePositionY + (1500 * _dt); // put some sort of speed up to this, 3 pixels a frame is slow, but have it be fps independant.
            }
        }
        if (GetInputManager().GetKey(SDL_SCANCODE_S) && !GetInputManager().GetKey(SDL_SCANCODE_W))
        {
            if (leftPaddlePositionY >= (-360 + (leftPaddle.GetComponent<Canis::RectTransformComponent>().size.y / 2)))
            {
                leftPaddlePositionY = leftPaddlePositionY - (1500 * _dt);
            }
        }
        if (GetInputManager().GetKey(SDL_SCANCODE_UP) && !GetInputManager().GetKey(SDL_SCANCODE_DOWN))
        {
            if (rightPaddlePositionY <= (360 - (rightPaddle.GetComponent<Canis::RectTransformComponent>().size.y / 2)))
            {
                rightPaddlePositionY = rightPaddlePositionY + (1500 * _dt); // put some sort of speed up to this, 1 pixel a frame is slow.
            }
        }
        if (GetInputManager().GetKey(SDL_SCANCODE_DOWN) && !GetInputManager().GetKey(SDL_SCANCODE_UP))
        {
            if (rightPaddlePositionY >= (-360 + (rightPaddle.GetComponent<Canis::RectTransformComponent>().size.y / 2)))
            {
                rightPaddlePositionY = rightPaddlePositionY - (1500 * _dt);
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