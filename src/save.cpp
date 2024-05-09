/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-vahan.ducher
** File description:
** Save
*/

#include "../includes/Core.hpp"
#include "../includes/Parser.hpp"

void saveCamera(RayTracer::Core &core, libconfig::Setting &camera)
{
    camera.add("resolution", libconfig::Setting::TypeGroup);
    camera["resolution"].add("width", libconfig::Setting::TypeInt) = core._camera._viewWidth;
    camera["resolution"].add("height", libconfig::Setting::TypeInt) = core._camera._viewHeight;

    camera.add("position", libconfig::Setting::TypeGroup);
    camera["position"].add("x", libconfig::Setting::TypeFloat) = core._camera._position.x();
    camera["position"].add("y", libconfig::Setting::TypeFloat) = core._camera._position.y();
    camera["position"].add("z", libconfig::Setting::TypeFloat) = core._camera._position.z();

    camera.add("fieldOfView", libconfig::Setting::TypeFloat) = core._camera._fovInDegrees;

    camera.add("maxDepth", libconfig::Setting::TypeInt) = core._maxDepth;
    camera.add("samples", libconfig::Setting::TypeInt) = core._camera._samples;

    camera.add("focusPoint", libconfig::Setting::TypeGroup);
    camera["focusPoint"].add("x", libconfig::Setting::TypeFloat) = core._camera._focusPoint.x();
    camera["focusPoint"].add("y", libconfig::Setting::TypeFloat) = core._camera._focusPoint.y();
    camera["focusPoint"].add("z", libconfig::Setting::TypeFloat) = core._camera._focusPoint.z();

    camera.add("sceneBackground", libconfig::Setting::TypeGroup);
    camera["sceneBackground"].add("r", libconfig::Setting::TypeFloat) = core.sceneBackground.r();
    camera["sceneBackground"].add("g", libconfig::Setting::TypeFloat) = core.sceneBackground.g();
    camera["sceneBackground"].add("b", libconfig::Setting::TypeFloat) = core.sceneBackground.b();
}

void saveLights(RayTracer::Core &core, libconfig::Setting &lights)
{
    return;
}

void saveMaterials(RayTracer::Core &core, libconfig::Setting &materials)
{
    return;
}

void savePrimitives(RayTracer::Core &core, libconfig::Setting &primitives)
{
    return;
}

void saveTransformations(RayTracer::Core &core, libconfig::Setting &transformations)
{
    return;
}

void saveMergeScene(RayTracer::Core &core, const std::string path)
{
    libconfig::Config cfg;
    libconfig::Setting &root = cfg.getRoot();
    libconfig::Setting &primitives = root.add("primitives", libconfig::Setting::TypeGroup);
    libconfig::Setting &lights = root.add("lights", libconfig::Setting::TypeGroup);
    libconfig::Setting &camera = root.add("camera", libconfig::Setting::TypeGroup);
    libconfig::Setting &materials = root.add("materials", libconfig::Setting::TypeGroup);
    libconfig::Setting &transformations = root.add("transformations", libconfig::Setting::TypeGroup);
    saveLights(core, lights);
    saveCamera(core, camera);
    savePrimitives(core, primitives);
    saveMaterials(core, materials);
    saveTransformations(core, transformations);
    cfg.writeFile(path.c_str());
    return;
}
