#pragma once
#include <string>
#include <vector>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>

class ScoreCounter: public Canis::ScriptableEntity
{

public:
    int leftScore = 0;
    int rightScore = 0;
    void OnCreate()
    {
        auto& textComp = GetComponent<Canis::TextComponent>();
        textComp.text = ("Press Enter");
    }

    void OnReady()
    {
        
    }
    
    void OnDestroy()
    {

    }

    void OnUpdate(float _dt)
    {
        //auto& textComp = GetComponent<Canis::TextComponent>();
        //testInt ++;
        //textComp.text = (std::to_string(testInt));

       auto& rect = GetComponent<Canis::RectTransformComponent>();
       //UpdateScore(leftScore,rightScore);
    }
    
    void UpdateScore(int m_leftScoreAdd = 0, int m_rightScoreAdd = 0, std::string m_textOverride = "", int m_textOverrideTimer = 5) //first two are for updating score, second two are if you want to just print text, the string is what you want to display and the timer int is for how long (in seconds)
    {
        leftScore = leftScore + m_leftScoreAdd;
        rightScore = rightScore + m_rightScoreAdd;
        auto& textComp = GetComponent<Canis::TextComponent>();
        if (m_textOverride == "")
        {
            textComp.text = (std::to_string(leftScore) + " : " + std::to_string(rightScore));
        }
        else
        {
            textComp.text = (m_textOverride);
        }
    }
};

bool DecodeScoreCounter(const std::string &_name, Canis::Entity &_entity)
{
    if (_name == "ScoreCounter")
    {
        Canis::ScriptComponent scriptComponent = {};
        scriptComponent.Bind<ScoreCounter>();
        _entity.AddComponent<Canis::ScriptComponent>(scriptComponent);

        

        return true;
    }
    return false;
}