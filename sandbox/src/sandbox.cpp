#include<reviv.h>

Entity *player, *camera, *stanic, *light, *platform, *sphere, *cube, *sun, *lamp;
Entity* container;
Entity* map;

ModelLoader modelLoaderBackpack, modelLoaderMap;

bool useMap = false;

//Texture2D tex, texFramebuffer;
Texture2D tex;
//Framebuffer framebuffer;

Perlin2D perlin;

class Sandbox : public Application
{
public:

    void initBeforeEngine() override
    {

    }

    void initAfterEngine() override
    {
        glEnable(GL_FRAMEBUFFER_SRGB);

        int voxelMapSize = 11;
        perlin.init(voxelMapSize, voxelMapSize);
        for(int i=-voxelMapSize/2; i<voxelMapSize/2; i++)
        {
            for(int j=-voxelMapSize/2; j<voxelMapSize/2; j++)
            {
                Entity* entity = Scene::createEntity("voxel");
                Vec2f tempVec;
                tempVec.a[0] = i * 0.3;
                tempVec.a[1] = j * 0.3;
                float perlinResult = perlin.get(tempVec);
                cout << "perlin: " << perlinResult << endl;

                entity->get<TransformComponent>()->position.a[0] = i;
                entity->get<TransformComponent>()->position.a[1] = j;
                entity->get<TransformComponent>()->position.a[2] = 5 + perlinResult * 10;
                
                entity->get<TransformComponent>()->scale = {0.5, 0.5, 0.5};

                entity->add<ModelComponent>(&AssetManager::get()->modelLoaderCube, &AssetManager::get()->materialGold);
            }
        }
        
        tex.load("assets/textures/floor.png");
        tex.bind(0);

        camera = Scene::setCameraEntity(Scene::createEntity("Camera"));
        camera->add<CameraComponent>(0.01f, 5000.f, degreesToRadians(100.f));

        player = Scene::setPlayerEntity(Scene::createEntity("Player"));
        player->get<TransformComponent>()->position = {0, 0, 3};

        if(useMap)
        {
            map = Scene::createEntity("Sponza");
            map->get<TransformComponent>()->position.a[2] = 2;
            map->get<TransformComponent>()->scale = {0.005f, 0.005f, 0.005f};
            map->get<TransformComponent>()->rotation.roll = degreesToRadians(90);
            modelLoaderMap.load("assets/sponza/scene.gltf");
            map->add<ModelComponent>(&modelLoaderMap, &AssetManager::get()->materialTurquoise);
        }

        stanic = Scene::createEntity("Stanic");
        stanic->get<TransformComponent>()->position = {1, 0, 2};
        modelLoaderBackpack.load("assets/models/backpack/backpack.obj");
        stanic->add<ModelComponent>(&modelLoaderBackpack, &AssetManager::get()->materialEmerald);

        light = Scene::createEntity("Light");
        light->get<TransformComponent>()->scale = {0.2f, 0.2f, 0.2f};
        light->add<PointLightComponent>();
        light->add<ModelComponent>          (&AssetManager::get()->modelLoaderSphere);
        light->get<ModelComponent>()->model.addMaterialFromShader(AssetManager::get()->shaderMonochroma);
        light->get<ModelComponent>()->model.pMaterials[0]->set("u_Color", Vec3f(1, 1, 1));
        auto* pLightComp = &light->get<PointLightComponent>()->light;

        //pLightComp->constant = 0.1f;
        //pLightComp->linear = 0;
        //pLightComp->quadratic = 1.8f;

        //pLightComp->ambient = Vec3f(0, 0, 0);
        //pLightComp->diffuse = Vec3f(1, 1, 1);
        //pLightComp->specular = Vec3f(0.0, 0.1, 0.1);

        //lamp = Scene::createEntity("Lamp");
        //lamp->get<TransformComponent>()->scale = {0.4f, 0.1f, 0.2f};
        //lamp->add<ModelComponent>           (&AssetManager::get()->modelLoaderSphere);
        //lamp->get<ModelComponent>()->model.addMaterialFromShader(AssetManager::get()->shaderMonochroma);
        //lamp->get<ModelComponent>()->model.pMaterials[0]->set("u_Color", Vec3f(1, 1, 1));
        //lamp->add<PointLightComponent>();

        platform = Scene::createEntity("Platform");
        platform->get<TransformComponent>()->scale = {7, 14, 0.4};
        platform->add<ModelComponent>       (&AssetManager::get()->modelLoaderCube,     &AssetManager::get()->materialGold);
        //auto* platformModel = platform->add<ModelComponent>(&AssetManager::get()->modelLoaderCube, &AssetManager::get()->shaderTexture);
        //platformModel->model.pMaterials[0]->addTexture(tex);

        sphere = Scene::createEntity("Sphere");
        sphere->get<TransformComponent>()->position = {1, 6, 2};
        sphere->get<TransformComponent>()->scale = {0.3f, 0.3f, 0.3f};
        sphere->add<ModelComponent>         (&AssetManager::get()->modelLoaderSphere,   &AssetManager::get()->materialRuby);

        cube = Scene::createEntity("Cube");
        cube->get<TransformComponent>()->position = {10, 0, 3};
        cube->get<TransformComponent>()->scale = {0.3, 0.3, 0.3};
        cube->add<ModelComponent>           (&AssetManager::get()->modelLoaderCube,     &AssetManager::get()->materialChrome);

        //sun = Scene::createEntity("Sun");
        //float sunHeight = 30;
        //sun->get<TransformComponent>()->position = {sunHeight * 2.f, 0 , sunHeight * 2};
        //sun->get<TransformComponent>()->scale={sunHeight, sunHeight, sunHeight};
        //sun->add<PointLightComponent>();
        //sun->add<ModelComponent>            (&AssetManager::get()->modelLoaderSphere);
        //sun->get<ModelComponent>()->model.addMaterialFromShader(AssetManager::get()->shaderMonochroma);
        //sun->get<ModelComponent>()->model.pMaterials[0]->set("u_Color", Vec3f(1, 1, 0));

        //container = Scene::createEntity("Container");
        //container->get<TransformComponent>()->position = Vec3f(5, 5, 5);
        //container->add<ModelComponent>(&AssetManager::get()->modelLoaderCube);
        //container->get<ModelComponent>()->model.addMaterialFromShader(AssetManager::get()->shaderTexture);
        //container->get<ModelComponent>()->model.pMaterials[0]->addTexture(tex);
    }

    void onUpdate() override
    {
        for(stls::StableVector<Entity>::Iterator it = Scene::getEntityList()->begin(); it != Scene::getEntityList()->end(); it++)
        {
            if(it->entityName != "voxel")
                continue;
            float help = (sin(Time::getTime() / 2) + 1) / 2;
            it->get<TransformComponent>()->scale = Vec3f(help/2, help/2, help/2);
        }

        light->get<TransformComponent>()->position = Vec3f(sin(Time::getTime() / 2) * 2, cos(Time::getTime() / 2) * 3, 2 + sin(Time::getTime() / 5));

        //cube->get<TransformComponent>()->rotation.yaw = Time::getTime() * 7;
        //cube->get<TransformComponent>()->rotation.pitch = Time::getTime() * 11;
        //cube->get<TransformComponent>()->rotation.roll = Time::getTime() * 3;

        cube->get<TransformComponent>()->rotation.yaw = 1;
        cube->get<TransformComponent>()->rotation.pitch = 1;
        cube->get<TransformComponent>()->rotation.roll = 1;
        
        //lamp->get<TransformComponent>()->position = Vec3f(sin(Time::getTime() * 2) * 3.5, cos(Time::getTime() / 1.3) * 7, 3);

        //lamp->get<TransformComponent>()->rotation = Vec3f(Time::getTime() * 5, Time::getTime() * 3, Time::getTime() * 10);
        //lamp->get<TransformComponent>()->rotation.roll = Time::getTime() * 5;
        //lamp->get<TransformComponent>()->rotation.pitch = Time::getTime() * 3;
        //lamp->get<TransformComponent>()->rotation.yaw = Time::getTime() * 10;
         //= Vec3f(Time::getTime() * 5, Time::getTime() * 3, Time::getTime() * 10);

        if(Time::isOneSecond())
        {
            cout << "FPS: " << 1 / Time::getDelta() << endl;
            cout << "Position: ";
            log(Scene::getPlayerEntity()->get<TransformComponent>()->position);
            cout << "Rotation: ";
            log(Scene::getPlayerEntity()->get<TransformComponent>()->rotation);
        }
    }
};

Application* createApplication()
{
    return new Sandbox();
}