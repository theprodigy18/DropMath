# 🚀 DropMath

![Version](https://img.shields.io/badge/version-0.5.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

📐 High-performance SIMD-accelerated Math Library for C++  
🎯 Designed for Game Engines, Simulations, and Real-Time Applications  
🧠 Minimalistic, Fast, and Extensible

---

## ⚙️ Features

### 🧮 Vector Types
- `Vec2`, `Vec3`: standard float-based vectors with full arithmetic and utility operations (`Length`, `Normalize`, `Dot`, `Lerp`), with `Vec3` supporting `Cross`
- `Vec4`: 128-bit SIMD-accelerated vector using `__m128` and `alignas(16)`, with fast arithmetic, `Dot`, `Lerp`, and `Store`

### 🧊 Matrix Types
- `Mat2x2`, `Mat3x3`: lightweight scalar matrices with full arithmetic support, member `Determinant()` and `Inverse()`, and safe static `TryInverse()`
- `Mat4x4`: SIMD-accelerated 4x4 matrix built from `Vec4` rows, supporting:
  - Matrix × Vector and Matrix × Matrix multiplication (SSE)
  - `Determinant()`, `Inverse()`, static `TryInverse()`
  - `Transposed()` and static `Transpose()`
  - `StoreRowMajor()`, `StoreColMajor()`, and flexible `Store()` with alignment mode
  - Identity constructor and float* access via `Data()`

### 🧰 Utility Functions

- Common math helpers: `Floor`, `Ceil`, `Round`, `WrapPi`, `ToRadians`, `ToDegrees`, `Sin`, `Cos`, `Tan`, `Sign`
- Safe generic math: `Lerp`, `Abs`, `Min`, `Max`, `Clamp`, `Sqrt`, `IsZero`
- Overload-based API for `float`, `double`, and `int` types
- Generic matrix operations:
  - `Determinant2x2`, `Determinant3x3`, `Determinant4x4`
  - `TryInverse2x2`, `TryInverse3x3`, `TryInverse4x4`
  - Supports any type with 2D `[][]` indexing
- Many functions are `constexpr` when compiled with C++14 or newer

### 📐 Constants and Compile-Time Support

- Global `constexpr` constants for float (`F::`) and double (`D::`) domains:
  - `PI`, `TWO_PI`, `HALF_PI`, `INV_PI`, `INV_TWO_PI`, `TO_DEG`, `TO_RAD`, `EPSILON`, `SIGN_MASK`
- `DM_INFINITY_F` and `DM_INFINITY` defined via bit-level union reinterpretation
- Adaptive `DM_CONSTEXPR_14` / `DM_CONSTEXPR_17` macros for enabling `constexpr` features based on C++ version
- Many math functions automatically leverage `constexpr` where available (C++14+)

### 🔧 Core Principles
- No external dependencies — pure C++11/14+ with intrinsics
- Lightweight, modular, and engine-friendly
- Fully assert-based unit tests
- Clean separation of SIMD and scalar logic

> ⚠️ Note: All SIMD types (`Vec4`, `Mat4x4`) use `alignas(16)` and must be properly aligned if allocated manually (e.g., on heap).

---

## 📁 Directory Structure

## 📁 Directory Structure

```
DropMath/
├── Lib/
│   └── include/
│       ├── ext/
│       │   ├── mat/
│       │   │   ├── DM_Mat2x2.h
│       │   │   ├── DM_Mat3x3.h
│       │   │   ├── DM_Mat4x4.h
│       │   │   ├── DM_Mat2x2.inl
│       │   │   ├── DM_Mat3x3.inl
│       │   │   └── DM_Mat4x4.inl
│       │   ├── vec/
│       │   │   ├── DM_Vec2.h
│       │   │   ├── DM_Vec3.h
│       │   │   ├── DM_Vec4.h
│       │   │   ├── DM_Vec2.inl
│       │   │   ├── DM_Vec3.inl
│       │   │   └── DM_Vec4.inl
│       │   ├── utils/
│       │   │   ├── DM_Utils.h
│       │   │   └── DM_Utils.inl
│       │   ├── DM_Common.h
│       │   ├── DM_Constant.h
│       │   └── DM_Enum.h
│       └── DropMath.h
├── Test/
│   ├── mat/
│   │   ├── Test_Mat2x2.cpp
│   │   ├── Test_Mat3x3.cpp
│   │   └── Test_Mat4x4.cpp
│   ├── vec/
│   │   ├── Test_Vec2.cpp
│   │   ├── Test_Vec3.cpp
│   │   └── Test_Vec4.cpp
│   └── utils/
│       └── Test_Utils.cpp
├── premake5.lua
├── premake_vs2022.bat
└── vendor/
    ├── bin/
    └── premake/
        └── premake5.exe
```

### 🆕 Structure Highlights
- `mat/`: Now includes `Mat2x2`, `Mat3x3`, and `Mat4x4` with `.inl` implementation files.
- `vec/`: All vector types (`Vec2`, `Vec3`, `Vec4`) have dedicated `.inl` files.
- `utils/`: New folder for generic math functions (`DM_Utils.h` + `DM_Utils.inl`).
- All implementations are now separated from declarations for better organization and compile-time optimization.

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

int main()
{
    // Normalize UV coordinate.
    Vec2 uv(128.0f, 64.0f);
    uv.Normalize();

    // Vector operations.
    Vec3 forward(0.0f, 0.0f, 1.0f);
    Vec3 up(0.0f, 1.0f, 0.0f);
    Vec3 right = Vec3::Cross(up, forward);

    // Matrix transform.
    Mat4x4 transform = Mat4x4::Identity();
    Vec4 point(1.0f, 2.0f, 3.0f, 1.0f);
    Vec4 result = transform * point;

    // Utility functions.
    float angleDeg = 45.0f;
    float angleRad = ToRadians(angleDeg);
    float wrapped = WrapPi(angleRad * 10.0f); // Wrap to [-pi, pi].

    float value = -5.3f;
    int rounded = Round(value);  // -5.
    int clamped = Clamp(rounded, -2, 2); // -2.

    // Generic functions.
    float lerpVal = Lerp(0.0f, 10.0f, 0.25f); // 2.5.

    // Matrix inverse check.
    Mat3x3 m(
        Vec3(3.0f, 0.0f, 2.0f),
        Vec3(2.0f, 0.0f, -2.0f),
        Vec3(0.0f, 1.0f, 1.0f)
    );
    Mat3x3 inv;
    if (Mat3x3::TryInverse(m, inv))
    {
        // Inversion successful.
    }

    return 0;
}
```

---

## ✅ Testing

All unit tests use `assert()` and can be executed via the `Test` project:

- `Test_Vec2.cpp`
- `Test_Vec3.cpp`
- `Test_Vec4.cpp`
- `Test_Mat2x2.cpp`
- `Test_Mat3x3.cpp`
- `Test_Mat4x4.cpp`
- `Test_Utils.cpp`

The test output will include execution time and will complete silently as long as all assertions pass.

> 💡 The tests are lightweight and fast, with no external dependencies — just compile and run.

### ⚠️ Entry Point Conflict Warning

Since each test file defines its own `main()` function, you **must only compile one test file at a time**.

#### 🔹 Visual Studio Users:
You can right-click on unused test files and select **"Exclude from Build"** to avoid duplicate `main()` errors.

#### 🔹 Other Toolchains (GCC/Clang/etc.):
Rename `main()` to something like `test_main()` in the other test files you are not using,  
or only compile one test file at a time manually:

```sh
# You can use higher version of C++ if you want.
g++ -std=c++11 -ILib/include Test/vec/Test_Vec3.cpp -o TestVec3
```

---

## 📘 API Coverage

- `Vec2`: +, -, *, /, length, squared length, normalize, dot, lerp, and utility accessors
- `Vec3`: same as `Vec2` + cross product
- `Vec4`: full SSE operations, swizzle accessors (x/y/z/w and r/g/b/a), dot, lerp, and aligned store/load
- `Mat2x2`, `Mat3x3`, `Mat4x4`:
  - Arithmetic support: matrix × vector and matrix × matrix
  - Determinant, transpose, and inverse
  - Static `TryInverse()` for safe inversion
  - Row-major and column-major data layout support via `Store()` and `Data()`
- `Utils`:
  - Generic math: `Lerp`, `Clamp`, `Min`, `Max`, `Abs`, `Sign`, `Sqrt`
  - Angle conversions: `ToRadians`, `ToDegrees`, `WrapPi`
  - Rounding: `Floor`, `Ceil`, `Round`
  - Matrix utilities: `Determinant` and `TryInverse` for any matrix type with `[][]` access
- `Constants`:
  - Global constants in `DropMath::F` and `DropMath::D`: `PI`, `HALF_PI`, `TO_DEG`, `EPSILON`, etc.
  - Full support for `constexpr` functions and constants under C++14 and newer

---

## 🧭 Roadmap

| Version  | Target Features														 |
|----------|-------------------------------------------------------------------------|
| v0.5.0   | Vec2, Vec3, Vec4, Mat4x4, Test coverage								 |
| v0.6.0   | Added Mat2x2 and Mat3x3, full matrix Determinant/Inverse API, math utilities (`Floor`, `Ceil`, `WrapPi`, `ToRadians`, etc.), global constants, generic `TryInverse`/`Determinant`, per-type `.inl` split, better test coverage                  |
| 🔜	   | Planned: more math utilities, quaternion support, render-related helpers such as `LookAt`, projection matrices, and SIMD batch operations  |

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
