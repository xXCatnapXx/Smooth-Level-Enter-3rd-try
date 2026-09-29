# Smooth Level Enter — GD 2.2074 unofficial port

This is an unofficial compatibility port of **Smooth Level Enter v1.0.9** by **undefined0**.
The original author and mod ID are preserved.

## 2.2074 fixes in this branch

- Targets Geode 4.10.2 / GD 2.2074.
- Uses C++20 and a standard-library RNG replacement for the Geode 5 random helper.
- Keeps the outgoing level-info scene alive until the transition has finished. On GD 2.2074, calling `onExitTransitionDidStart()` at the beginning can hide or tear down the level-page background (including backgrounds provided by other mods).
- Adds null guards around optional PlayLayer / ShaderLayer nodes to avoid crashes on unusual levels.
- Guards pixelate shader scale values against zero to prevent invalid scaling and disappearing / corrupted transition rendering.
- Clamps object animation delays for objects that begin outside the visible screen.
- Only advertises Windows and Android in `mod.json`; the included workflow builds Windows, Android32 and Android64. macOS/iOS are intentionally not advertised until they have a working 2.2074 build.
- Uses Node IDs v1.23.3, which is used by other Geode 4 / GD 2.2074 mods.

## Testing

Primary target: Windows x64, GD 2.2074, Geode 4.10.2.

Please test:

1. Online LevelInfoLayer -> Play.
2. Official level selection -> Play.
3. Editor level -> Play/Test.
4. Platformer and classic levels.
5. Levels with and without start-position shaders.
6. With Menu Shaders enabled and disabled.
7. Enter, exit, and re-enter several levels to catch lifecycle issues.

If a problem remains, keep the Geode log and a short screen recording with the exact level / mod combination.
