#pragma once
#include <string>
#include <vector>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>

class PongBall : public Canis::ScriptableEntity
{
private:
    glm::vec2   m_direction;
    float       m_speed;
    float       m_timeBetweenAnimation = 3.0f;
    float       m_countDown = 0.0f;
    unsigned int m_animIndex = 0;
    std::vector<glm::vec2> m_spawnPoints = {};
public:
    void OnCreate()
    {
        m_countDown = m_timeBetweenAnimation;
    }

    void OnReady()
    {
        m_direction = glm::vec2(1.0f, 0.4f);
        m_speed = 150.0f;
    }
    
    void OnDestroy()
    {

    }

    void OnUpdate(float _dt)
    {
        using namespace Canis; //if you're sick of using "Canis::" before all canis things.
        Canis::Entity leftPaddle = entity.GetEntityWithTag("paddleLeft");
        Canis::Entity rightPaddle = entity.GetEntityWithTag("paddleRight");
        auto& rectLeftPaddle = leftPaddle.GetComponent<Canis::RectTransformComponent>();
        auto& rectRightPaddle = rightPaddle.GetComponent<Canis::RectTransformComponent>();
        auto& colorLeftPaddle = leftPaddle.GetComponent<Canis::ColorComponent>();

        //Log(std::to_string(rectLeftPaddle.position.x));

        auto& rect = GetComponent<Canis::RectTransformComponent>();

        float halfSizeX = rect.size.x/2.0f;
        float halfSizeY = rect.size.y/2.0f;

        /*if (rect.position.x + halfSizeX >= GetWindow().GetScreenWidth()/2.0f ||
                rect.position.x - halfSizeX <= GetWindow().GetScreenWidth()/-2.0f)
            m_direction.x *= -1.0f; //invert the direction its going, when hit left side and right side*/

        if (
            //left paddle if
            rect.position.x - halfSizeX <= rectLeftPaddle.position.x + (rectLeftPaddle.size.x /2.0f) && 
            rect.position.y <= rectLeftPaddle.position.y + (224/2) && 
            rect.position.y >= rectLeftPaddle.position.y - (224/2)|| 
            //start of right paddle if
            rect.position.x + halfSizeX >= rectRightPaddle.position.x - (rectRightPaddle.size.x /2.0f) &&
            rect.position.y <= rectRightPaddle.position.y + (224/2) && 
            rect.position.y >= rectRightPaddle.position.y - (224/2) )
            //end if parameters
        {
            m_direction.x *= -1.0f;
        }

        if (rect.position.y + halfSizeY >= GetWindow().GetScreenHeight()/2.0f ||
                rect.position.y - halfSizeY <= GetWindow().GetScreenHeight()/-2.0f)
            m_direction.y *= -1.0f; //bounce off the top and bottom
        
        rect.position += (m_direction * (m_speed * _dt));

        if (GetInputManager().JustPressedKey(SDLK_p))
            m_speed += 50.0f;
        
        if (GetInputManager().JustPressedKey(SDLK_r))
            m_speed = 150.0f;
        
        if (GetInputManager().JustPressedKey(SDLK_d))
        {
            //GetScene().Instantiate("assets/prefebs/test_character.scene");
        }
        
        if(GetInputManager().GetKey(SDL_SCANCODE_W))
        {
            //Canis::Log("W IS DOWN");
        }
        else
        {
            //Canis::Log("UP");
        }
    }
};

bool DecodePongBall(const std::string &_name, Canis::Entity &_entity)
{
    if (_name == "PongBall")
    {
        Canis::ScriptComponent scriptComponent = {};
        scriptComponent.Bind<PongBall>();
        _entity.AddComponent<Canis::ScriptComponent>(scriptComponent);
        return true;
    }
    return false;
}