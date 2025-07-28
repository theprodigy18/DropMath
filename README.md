# 🚀 DropMath

![Version](https://img.shields.io/badge/version-0.5.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

📐 High-performance SIMD-accelerated Math Library for C++  
🎯 Designed for Game Engines, Simulations, and Real-Time Applications  
🧠 Minimalistic, Fast, and Extensible

---

## ⚙️ Features

- `Vec2`, `Vec3`, `Vec4` with full arithmetic and utility functions
- `Mat4x4` with SIMD matrix-vector and matrix-matrix multiplication
- SSE-accelerated operations with `alignas(16)`
- No external dependencies — pure C++ and intrinsics
- Lightweight and easy to integrate
- Full assert-based unit tests
- Modular source structure

> ⚠️ Note: All SIMD types (`Vec4`, `Mat4x4`) use `alignas(16)` and must be properly aligned if allocated manually (e.g., on heap).

---

## 📁 Project Structure

```
DropMath/
├── Lib/
│   └── include/
│       ├── ext/
│       │   ├── mat/
│       │   │   └── DM_Mat4x4.h
│       │   ├── vec/
│       │   │   ├── DM_Vec2.h
│       │   │   ├── DM_Vec3.h
│       │   │   └── DM_Vec4.h
│       │   ├── DM_Common.h
│       │   ├── DM_Constant.h
│       │   └── DM_Enum.h
│       └── DropMath.h
├── Test/
│   ├── mat/
│   │   └── Test_Mat4x4.cpp
│   └── vec/
│       ├── Test_Vec2.cpp
│       ├── Test_Vec3.cpp
│       └── Test_Vec4.cpp
├── premake5.lua
├── premake_vs2022.bat
└── vendor/
    ├── bin/
    └── premake/
        └── premake5.exe
```


---

## 🛠️ Getting Started

## ✅ Requirements

- **Compiler**: C++11-compatible (GCC, Clang, MSVC)
- **CPU**: SSE4.1-capable processor
- **OS**: Windows 7+ or Linux
- **IDE/Text Editor**: Optional — use any IDE/Text Editor (e.g., Visual Studio, VS Code, CLion)
- **Build System (optional)**: [Premake5](https://premake.github.io/) — only needed to build and run unit tests. But you can use it as your main build system if you want.

> 💡 You can use the DropMath library standalone by simply including the headers.  
> No build system required unless you're running the test suite.
> You can delete Test folder and the premake file if you are using this library for your own project.


---

## 🚀 Example Usage

```cpp
#include <DropMath.h>

using namespace DropMath;

Vec2 uv = Vec2(0.5f, 1.0f).Normalized();

Vec3 a(1.0f, 2.0f, 3.0f);
Vec3 b(4.0f, 5.0f, 6.0f);
Vec3 result = a + b;

Vec4 color = Vec4(1.0f, 0.5f, 0.0f, 1.0f);

Mat4x4 mat = Mat4x4::Identity();
Vec4 v(1, 2, 3, 1);
Vec4 transformed = mat * v;
```

---

## ✅ Testing

All unit tests use `assert()` and can be executed in `Test` project:

- `Test_Vec2.cpp`
- `Test_Vec3.cpp`
- `Test_Vec4.cpp`
- `Test_Mat4x4.cpp`

The output will be the executing time and pass all the test without hit any assertion.

---

## 📘 API Coverage

- `Vec2`: +, -, *, /, length, normalize, dot, lerp, and static helpers
- `Vec3`: same as `Vec2` + cross
- `Vec4`: full SSE operations + component swizzle
- `Mat4x4`: identity, transpose, matrix-vector and matrix-matrix multiplication, and Can be stored as float[16] in row- or column-major layout

---

## 🧭 Roadmap

| Version  | Target Features														 |
|----------|-------------------------------------------------------------------------|
| v0.5.0   | Vec2, Vec3, Vec4, Mat4x4, Test coverage								 |
| 🔜	   | Coming soon — more matrix types, quaternion, and SIMD batch operations. |

---

## 📄 License

MIT License — free to use and modify.

---

## 👤 Author

**Febri Andika (theprodigy18)**  
Game Engine & Low-Level Developer  
Focus on performance, control, and clean architecture.

## 💬 Feedback & Contribution

This project is in early development. Feedback and contributions are welcome — feel free to open an issue or PR.
