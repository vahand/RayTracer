# 🎇 RayTracer EPITECH Project

![french_chess_3000_1920_1080](https://github.com/vahand/RayTracer/assets/97789425/1f8431e3-1561-4001-a979-bae59001aa6a)

This project was carried out during our second year at EPITECH in **C++**.

## Launch the program
To launch the raytracer program, follow these commands from the root directory of the repository:

```
make fclean
make
```

```
./raytracer [options] > [output_imahe_path]
```

**Available options:**</br>
- (`-h` / `--help`): Display the help menu</br>
- (`-s` / `--scene`) `[configuration_file_path]`: Specify the path of the target configuration file (required)</br>
- (`-t` / `--threads`) `[threads_number]`: Specify the number of threads (1 by default)</br>
- (`-q` / `--quality`) `[samples_number]`: Specify the number of samples to adjust the quality (100 by default)</br>
- (`-g` / `--gui`): Launch the program with the Graphic User Interface</br>

> **_NOTE_**: If GUI flag is specified, no output_image_path is required.</br>

## Configure a scene file
Each scene rendered in RayTracer program is described in an config file with the `.scene` extension, stored in the `/scenes` directory.</br>

The config file includes:</br>
- Camera's settings</br>
- Materials used for shapes rendering</br>
- Shape to render</br>
- Potential transformations applied to shapes</br>

> **_NOTE_**: Some comments could be added in the config file with the `#` caracter

### Camera configuration

**Here an example of camera configuration:**
```
camera:
{
    resolution:
    {
        width = 1920;
        height = 1080;
    }
    position:
    {
        x = 0.0;
        y = 6.0;
        z = -40.0;
    }
    fieldOfView = 60.0; # In degree
    maxDepth = 50;
    focusPoint:
    {
        x = 0.0;
        y = 5.0;
        z = 0.0;
    }
    sceneBackground:
    {
        r = 0.0;
        g = 0.0;
        b = 0.0;
    }
    samples = 100;
}
```
The camera's settings are:</br>
- `resolution`: Required</br>
- `position`: Required</br>
- `fieldOfView`: In degree. Optional, 45° by default</br>
- `maxDepth`: Optional, 50 by default</br>
- `focusPoint`: Optional, (0, 2, 0) by default</br>
- `sceneBackground`: (the background color). Optional, (0, 0, 0) by default</br>
- `samples`: Optional, 100 by default</br>

### Materials configuration

**Here an example of materials configuration:**
```
materials:
{
    lambertian_material:
    {
        type = "lambertian";
        color = { r = 255.0; g = 255.0; b = 0.0; }
    }
    metal_material:
    {
        type = "metal";
        fuzziness = 0.8;
        color = { r = 128.0; g = 128.0; b = 128.0; }
    }
    light_material:
    {
        type = "lightDiffuse";
        color = { r = 255.0; g = 255.0; b = 255.0; }
    }
    chessboard:
    {
        type = "chessBoard";
        color1 = { r = 255.0; g = 255.0; b = 255.0; }
        color2 = { r = 0.0; g = 0.0; b = 0.0; }
    }
}
```
All materials used to render primitives must be defined in this section.</br>
The material's settings are:
- `name`: Material name (name of the section. Example `lambertian_material`)
- `type`: Material type (`lambertian`, `metal`, `lightDiffuse` or `chessBoard`)
- `color`: Material color (or `color1` and `color2` for `chessBoard`)
- `fuzziness`: Only for `metal` type

### Primitives configuration

**Here an example of primitives configuration:**
```
primitives:
{
    wall:
    {
        type = 5;
        origin = { x = 0.0; y = 24.99; z = 0.0; };
        material = "light_material";
        axis = "Y";
        height = 5.0;
        width = 5.0;
    }
    sphere:
    {
        type = 0;
        origin = { x = 8.0; y = 2.0; z = 2.0; };
        material = "metal_material";
        radius = 2.0;
    }
    plane:
    {
        type = 1;
        origin = { x = 0.0; y = 0.0; z = 0.0; };
        material = "lambertian_material";
        axis = "Y"
    }
```
All rendered primitives are defined in this section.</br>
The primitive's settings are:
- `name`: Primitive name (name of the section. Example `wall`)
- `type`: Primitive type
  - **0** for a sphere
  - **1** for a plane
  - **2** for a cone
  - **3** for a cylinder
  - **4** for a cube
  - **5** for a wall
- `origin`: Primitive position
- `material`: Assigned material (specified by its name)
- Additonal properties specific to a primitive
  - `radius` for **sphere** type
  - `axis` for **plane** type
  - `axis`, `radius` and `angle` for **cone** type
  - `axis` and `radius` for **cylinder** type
  - `xDim`, `yDim` and `zDim` for **cube** type
  - `axis`, `width` and `height` for **wall** type

### Transformations configuration

**Here an example of transformations configuration:**
```
transformations:
{
    sphere: { type = "translate" ; vector: { x = 12.0 ; y = 67.0 ; z = 34.0 } } # a translation transfo. applied to sphere
    wall: { type = "rotate" ; vector: { x = 0.0 ; y = 0.0 ; z = 45.0 } } # a rotation transfo. applied to wall
}
```
All transformations applied to primitives are defined in this section.</br>
The transformation's settings are:</br>
- `name`: Target primitive name (name of the section. Example `sphere`)
- `type`: Transformation type (`rotate` or `translate`)
- `vector`: Transformation vector

> **_NOTE_**: Modifying the config file during execution will automatically update the scene rendering.

## GUI
![image](https://github.com/vahand/RayTracer/assets/97789425/8672ebc2-d7da-420c-bb18-874044ec5bab)

The GUI is enabled with the `-g` / `--gui` flags.
This GUI enables to modify several parameters at run-time like FOV, number of samples or camera focus point.
The **Fast Render** button displays the scene render, without light calculations to have a preview of the scene.

## Screenshots
![demo_colored_light_5000_1080p](https://github.com/vahand/RayTracer/assets/97789425/ae22c052-27c6-4b7f-b844-cbfdcdc36231)
![image](https://github.com/vahand/RayTracer/assets/97789425/0ae0c113-9a10-45aa-a214-51845f27c00a)
![image](https://github.com/vahand/RayTracer/assets/97789425/67c3cadc-0274-4c18-886c-91bfc7f8a4c1)

## ⚠️ Warning
This project was developed as part of our second year at EPITECH.</br>
It is forbidden for **EPITECH students** to use this code. Any attempt to render this code will be considered as cheating, and mark will be -42.
