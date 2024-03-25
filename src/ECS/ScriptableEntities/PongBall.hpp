#pragma once
#include <string>
#include <vector>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>


class PongBall : public Canis::ScriptableEntity
{
private:
   
    
    float       m_timeBetweenAnimation = 3.0f;
    float       m_countDown = 0.0f;
    std::vector<glm::vec2> m_spawnPoints = {};
public:
    bool gameStarted= false;
    glm::vec2   m_direction;
    float       m_speed;
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
        Canis::Entity scoreCounter = entity.GetEntityWithTag("ScoreCounter");
        auto& rectLeftPaddle = leftPaddle.GetComponent<Canis::RectTransformComponent>();
        auto& rectRightPaddle = rightPaddle.GetComponent<Canis::RectTransformComponent>();
        //auto& colorLeftPaddle = leftPaddle.GetComponent<Canis::ColorComponent>();
        auto& scoreScriptComp = scoreCounter.GetComponent<Canis::ScriptComponent>();

        //Log(std::to_string(rectLeftPaddle.position.x));

        auto& rect = GetComponent<Canis::RectTransformComponent>();
        auto& colorComp = GetComponent<Canis::ColorComponent>();

        float halfSizeX = rect.size.x/2.0f;
        float halfSizeY = rect.size.y/2.0f;


        if (rect.position.x + halfSizeX >= GetWindow().GetScreenWidth()/2.0f) // right if
        {
            rect.position = vec2(0.0, 0.0); //Instead of inverting direction, Ill reset the ball position
            m_speed = 150.0f; //reset speed
            colorComp.color = glm::vec4(255.0f / 255, 255.0f / 255, 255.0f / 255, 1.0f); //set color to white
            //CALL SCOREBOARD SCRIPT HERE, THE FUNCTION THAT ADDS POINTS BLUE = +1 point
            //static_cast<ScoreCounter*>(scoreCounter.GetComponent<Canis::ScriptComponent>().Instance)->UpdateScore(int m_leftScore = 1, int m_rightScore = 1);
                
        }
        if (rect.position.x - halfSizeX <= GetWindow().GetScreenWidth()/-2.0f) // left if
            {
            rect.position = vec2(0.0, 0.0); //Instead of inverting direction, Ill reset the ball position
            m_speed = 150.0f; //reset speed
            colorComp.color = glm::vec4(255.0f / 255, 255.0f / 255, 255.0f / 255, 1.0f); //set color to white
            //CALL SCOREBOARD SCRIPT HERE, THE FUNCTION THAT ADDS POINTS BLUE = +1 point
            //static_cast<ScoreCounter*>(scoreCounter.GetComponent<Canis::ScriptComponent>().Instance)->UpdateScore(int m_leftScore = 1, int m_rightScore = 1);
            }

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
            if (m_speed <= 500.0f)
            {
                m_speed += 10.0f;
            }
            if (rect.position.x <= -1.0f) // if left side
            {
                colorComp.color = glm::vec4(68.0f / 255, 143.0f / 255, 255.0f / 255,1.0f); //set color to blue (68,143,255)
            }
            if (rect.position.x >= 1.0f) // if right side
            {
                colorComp.color = glm::vec4(255.0f / 255, 68.0f / 255, 68.0f / 255,1.0f); //set color to red (255,68,68)
            }
            
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
        if (GetInputManager().JustPressedKey(SDLK_RETURN))
        {
            //StartGame();
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

    void StartGame()
    {
       // m_direction = glm::vec2(1.0f, 0.4f);
       // m_speed = 150.0f;
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