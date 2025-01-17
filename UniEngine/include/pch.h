// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"
#include <type_traits>
#include <optional>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <list>
#include <set>
#include <vector>
#include <queue>
#include <memory>
#include <utility>
#include <unordered_map>
#include <cstddef>
#include <cstdarg>
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <exception>
#include <future>
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <gtx/closest_point.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/random.hpp>
#include <gtx/rotate_vector.hpp>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"

#define STBI_MSC_SECURE_CRT
#include <stb_image.h>
#include <stb_image_write.h>
#include <stb_image_resize.h>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include <commdlg.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "yaml-cpp/yaml.h"

#include "ImGuizmo/ImGuizmo.h"

#include "PxPhysicsAPI.h"
#endif //PCH_H
