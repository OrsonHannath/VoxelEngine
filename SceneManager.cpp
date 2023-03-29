//
// Created by User on 26/03/2023.
//

#include "SceneManager.h"

SceneManager::SceneManager(float* deltaTime_) {

    std::cout << "Created Scene Manager" << std::endl;
    deltaTimePtr = deltaTime_;
}

void SceneManager::RenderScene(Scene* scene_) {

    scene_->RenderScene(deltaTimePtr);
}

void SceneManager::AddScene(Scene* scene_) {

    sceneMap[scene_->GetName()] = scene_;
}

void SceneManager::SetCurrentScene(Scene *scene_) {

    currentScene = scene_;
}

Scene* SceneManager::GetScene(std::string name) {

    return sceneMap[name];
}

Scene* SceneManager::GetCurrentScene() {

    return currentScene;
}