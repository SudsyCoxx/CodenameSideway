# CodenameSideway
Like Codename: Kids Next Door, but better!

FYI : You need to add glew32s.lib to the build directory. i.e. ./Codename/Sideway/Release/ and ./Codename/Sideway/Debug 
  otherwise, the program won't run.

# TODO:
1. Implement Graphic Components
  - 2D Rendering
  - Shaders
  - Textures
  - Lighting
2. Audio
  - Find an audio library
3. Networking
  - Basic threaded networking
4. Basic AI
5. Basic AABB Collision
6. Basic Keyboard/Mouse Controller

# Formatting Scheme (WIP)
- Class UpperCaseCamelCase
- Private Member Variables are to be names "m_" + variable name. i.e. int m_Int
- Solution Explorer should resemble actual directory 
  -- Class .hpp and .cpp should be in correct folders
- C++ classes should have .hpp headers
- C exclusive classes should have .h headers
- Use namespaces where appropriate to prevent conflicts
