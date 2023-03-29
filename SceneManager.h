//
// Created by User on 26/03/2023.
//

#ifndef VOXELENGINE_SCENEMANAGER_H
#define VOXELENGINE_SCENEMANAGER_H

#include <map>
#include <iostream>
#include "Scene.h"

class SceneManager {
private:
    Scene* currentScene;
    std::map<std::string, Scene*> sceneMap;
    float* deltaTimePtr;
public:

    SceneManager(float* deltaTime_);

    void RenderScene(Scene* scene_);
    void AddScene(Scene* scene_);
    void SetCurrentScene(Scene* scene_);

    Scene* GetScene(std::string name);
    Scene* GetCurrentScene();
};


#endif //VOXELENGINE_SCENEMANAGER_H
