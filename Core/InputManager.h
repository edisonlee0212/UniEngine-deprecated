#pragma once
#include "Core.h"
namespace UniEngine {
    class UECORE_API InputManager : public ManagerBase
    {
    public:
        static void Init();
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        static void MouseScrollCallback(GLFWwindow* window, double xpos, double ypos);
        static bool GetKeyDown(int key);
        static bool GetKeyUp(int key);
        static bool GetKey(int key);
        static bool GetMouseDown(int button);
        static bool GetMouseUp(int button);
        static bool GetMouse(int button);
        static glm::vec2 GetMousePosition();
        static glm::vec2 GetMouseScroll();
        static bool GetMouseScrolled();
        static bool GetMouseMoved();
        static void Update();
    private:
        friend class InputSystem;
        static bool _KeyPressed[349];
        static bool _KeyDown[349];
        static bool _KeyUp[349];
        static bool _KeyDownChecked[349];
        static bool _KeyUpChecked[349];

        static bool _MousePressed[8];
        static bool _MouseDown[8];
        static bool _MouseUp[8];
        static bool _MouseDownChecked[8];
        static bool _MouseUpChecked[8];
        static double _CursorX; 
        static double _CursorY;
        static double _CursorScrollX;
        static double _CursorScrollY;
        static bool _CursorMoved;
        static bool _CursorScrolled;
        static bool _CursorMovedChecked;
        static bool _CursorScrolledChecked;
    };

}
