// for (int i = 0; i < jScene["gameObjects"].size(); i++)
//     {
//         // Check if the gameObject being created is not the World because World is created already on Scene constructor
//         if (jScene["gameObjects"][i]["name"] != "World" && !jScene["gameObjects"][i]["name"].is_null())
//         {
//             GameObject* gameObject = new GameObject();
//             gameObject->name = jScene["gameObjects"][i]["name"];
//             Guid gameObjectGuid;
//             gameObjectGuid.FromString(jScene["gameObjects"][i]["guid"]);
//             gameObject->guid = gameObjectGuid;
//             
//             // Setup components
//             for (int j = 0; j < jScene["gameObjects"][i]["components"].size(); j++)
//             {
//                 // Setup each component
//                 
//                 // Setup transform component
//                 if (jScene["gameObjects"][i]["components"][j]["name"] == "transform")
//                 {
//                     Guid gameObjectGuid;
//                     gameObjectGuid.FromString(jScene["gameObjects"][i]["components"][j]["data"]["guid"]);
//                     gameObject->transform->guid = gameObjectGuid;
//                     gameObject->transform->localPosition = jScene["gameObjects"][i]["components"][j]["data"]["localPosition"];
//                     gameObject->transform->rotation = jScene["gameObjects"][i]["components"][j]["data"]["rotation"];
//                     gameObject->transform->scaling = jScene["gameObjects"][i]["components"][j]["data"]["scaling"];
//                 }
//                 // Setup directionalLight component
//                 // std::cout << jScene["gameObjects"][i]["components"][j]["name"] << std::endl;
//                 if (jScene["gameObjects"][i]["components"][j]["name"] == "directionalLight")
//                 {
//                     gameObject->AddComponent<DirectionalLight>();
//                     gameObject->GetComponent<DirectionalLight>()->id = jScene["gameObjects"][i]["components"][j]["data"]["id"];
//                     gameObject->GetComponent<DirectionalLight>()->diffuseColor = jScene["gameObjects"][i]["components"][j]["data"]["diffuseColor"];
//                     gameObject->GetComponent<DirectionalLight>()->ambientColor = jScene["gameObjects"][i]["components"][j]["data"]["ambientColor"];
//                     gameObject->GetComponent<DirectionalLight>()->specularColor = jScene["gameObjects"][i]["components"][j]["data"]["specularColor"];
//                     gameObject->GetComponent<DirectionalLight>()->direction = jScene["gameObjects"][i]["components"][j]["data"]["direction"];
//                 }
//                 
//                 // Setup pointLight component
//                 if (jScene["gameObjects"][i]["components"][j]["name"] == "pointLight")
//                 {
//                     gameObject->AddComponent<PointLight>();
//                     gameObject->GetComponent<PointLight>()->id = jScene["gameObjects"][i]["components"][j]["data"]["id"];
//                     gameObject->GetComponent<PointLight>()->diffuseColor = jScene["gameObjects"][i]["components"][j]["data"]["diffuseColor"];
//                     gameObject->GetComponent<PointLight>()->ambientColor = jScene["gameObjects"][i]["components"][j]["data"]["ambientColor"];
//                     gameObject->GetComponent<PointLight>()->specularColor = jScene["gameObjects"][i]["components"][j]["data"]["specularColor"];
//                     gameObject->GetComponent<PointLight>()->position = jScene["gameObjects"][i]["components"][j]["data"]["position"];
//                     gameObject->GetComponent<PointLight>()->constant = jScene["gameObjects"][i]["components"][j]["data"]["constant"];
//                     gameObject->GetComponent<PointLight>()->linear = jScene["gameObjects"][i]["components"][j]["data"]["linear"];
//                     gameObject->GetComponent<PointLight>()->quadratic = jScene["gameObjects"][i]["components"][j]["data"]["quadratic"];
//                 }
//                 
//                 // Setup spotLight component
//                 if (jScene["gameObjects"][i]["components"][j]["name"] == "spotLight")
//                 {
//                     gameObject->AddComponent<SpotLight>();
//                     gameObject->GetComponent<SpotLight>()->id = jScene["gameObjects"][i]["components"][j]["data"]["id"];
//                     gameObject->GetComponent<SpotLight>()->diffuseColor = jScene["gameObjects"][i]["components"][j]["data"]["diffuseColor"];
//                     gameObject->GetComponent<SpotLight>()->ambientColor = jScene["gameObjects"][i]["components"][j]["data"]["ambientColor"];
//                     gameObject->GetComponent<SpotLight>()->specularColor = jScene["gameObjects"][i]["components"][j]["data"]["specularColor"];
//                     gameObject->GetComponent<SpotLight>()->position = jScene["gameObjects"][i]["components"][j]["data"]["position"];
//                     gameObject->GetComponent<SpotLight>()->direction = jScene["gameObjects"][i]["components"][j]["data"]["direction"];
//                     gameObject->GetComponent<SpotLight>()->constant = jScene["gameObjects"][i]["components"][j]["data"]["constant"];
//                     gameObject->GetComponent<SpotLight>()->linear = jScene["gameObjects"][i]["components"][j]["data"]["linear"];
//                     gameObject->GetComponent<SpotLight>()->quadratic = jScene["gameObjects"][i]["components"][j]["data"]["quadratic"];
//                     gameObject->GetComponent<SpotLight>()->cutOff = jScene["gameObjects"][i]["components"][j]["data"]["cutOff"];
//                     gameObject->GetComponent<SpotLight>()->outerCutOff = jScene["gameObjects"][i]["components"][j]["data"]["outerCutOff"];
//                 }
//
//                 // Setup audio component
//                 if (jScene["gameObjects"][i]["components"][j]["name"] == "audio")
//                 {
//                     gameObject->AddComponent<Audio>();
//                     gameObject->GetComponent<Audio>()->musicPath = Tools::GetPathFromJsonString(jScene["gameObjects"][i]["components"][j]["data"]["musicPath"]);
//                     gameObject->GetComponent<Audio>()->SetVolume(jScene["gameObjects"][i]["components"][j]["data"]["volume"]);
//                     gameObject->GetComponent<Audio>()->SetLoop(jScene["gameObjects"][i]["components"][j]["data"]["isLooping"]);
//                     gameObject->GetComponent<Audio>()->StopMusic(jScene["gameObjects"][i]["components"][j]["data"]["isPlaying"]);
//                 }
//
//                 // Setup meshRenderer component
//                 if (jScene["gameObjects"][i]["components"][j]["name"] == "meshRenderer")
//                 {
//                     Shader* shader = resourceManager->Get<Shader>(ResourceManager::GetDefaultShader());
//                     Texture* texture = resourceManager->Get<Texture>(ResourceManager::GetDefaultTexture());
//                     Model* model = resourceManager->Get<Model>(ResourceManager::GetDefaultModel());
//                     gameObject->AddComponent(new MeshRenderer(new Mesh(model, texture, shader)));
//                 }
//             }
//         }
//         else if (jScene["gameObjects"][i]["name"] == "World")    // Setup World seperatly
//         {
//             // Setup guids
//             Guid worldGuid;
//             worldGuid.FromString(jScene["gameObjects"][i]["guid"]);
//             scene->GetWorld()->guid = worldGuid;
//             Guid worldTransformGuid;
//             worldTransformGuid.FromString(jScene["gameObjects"][i]["components"][0]["data"]["guid"]);
//             scene->GetWorld()->transform->guid = worldTransformGuid;
//             
//             scene->GetWorld()->transform->localPosition = jScene["gameObjects"][i]["components"][0]["data"]["localPosition"];
//             scene->GetWorld()->transform->rotation = jScene["gameObjects"][i]["components"][0]["data"]["rotation"];
//             scene->GetWorld()->transform->scaling = jScene["gameObjects"][i]["components"][0]["data"]["scaling"];
//
//             // Setup world directionalLight
//             if (jScene["gameObjects"][i]["components"].size() > 1)
//             {
//                 for (int j = 0; j < jScene["gameObjects"][j]["components"].size(); j++)
//                 {
//                     if (jScene["gameObjects"][i]["components"][j]["name"] == "directionalLight")
//                     {
//                         scene->GetWorld()->AddComponent<DirectionalLight>();
//                         scene->GetWorld()->GetComponent<DirectionalLight>()->id = jScene["gameObjects"][i]["components"][j]["data"]["id"];
//                         scene->GetWorld()->GetComponent<DirectionalLight>()->diffuseColor = jScene["gameObjects"][i]["components"][j]["data"]["diffuseColor"];
//                         scene->GetWorld()->GetComponent<DirectionalLight>()->ambientColor = jScene["gameObjects"][i]["components"][j]["data"]["ambientColor"];
//                         scene->GetWorld()->GetComponent<DirectionalLight>()->specularColor = jScene["gameObjects"][i]["components"][j]["data"]["specularColor"];
//                         scene->GetWorld()->GetComponent<DirectionalLight>()->direction = jScene["gameObjects"][i]["components"][j]["data"]["direction"];
//                     }
//                 }
//             }
//         }
//
//     for (int i = 0; i < jScene["terrains"].size(); i++)
//     {
//         // If the terrain is a default terrain
//         if (Tools::GetPathFromJsonString(jScene["terrains"][i]["noisemapPath"]) == "")
//         {
//             std::string name = "terraind";
//             Transform* transform = new Transform();
//             DefaultTerrain* terrain = new DefaultTerrain(name, transform);
//             terrain->Init(
//                 jScene["terrains"][i]["xResolution"],
//                 jScene["terrains"][i]["zResolution"]
//             );
//             CreateTerrainFromFile(terrain, scene, jScene, i);
//         }
//         // If the terrain is a noisemap terrain
//         else
//         {
//             std::string name = "terrainn";
//             Transform* transform = new Transform();
//             NoisemapTerrain* terrain = new NoisemapTerrain(name, transform);
//             terrain->Init(
//                 Tools::GetPathFromJsonString(jScene["terrains"][i]["noisemapPath"]).c_str()
//             );
//             CreateTerrainFromFile(terrain, scene, jScene, i);
//         }
//     }
//     
//     m_scenes.push_back(scene);    