## [v0.6.0] - 2025-07-30
### Added
- `Mat2x2` and `Mat3x3` with full operator overloads and matrix utilities
- `Determinant()` and `Inverse()` member functions for all matrices
- Static `TryInverse()` methods for safe inversion
- Generic `Determinant` and `TryInverse` templates for any matrix type with `[][]` access
- Math utilities: `Floor`, `Ceil`, `Round`, `WrapPi`, `ToRadians`, `ToDegrees`, `Sin`, `Cos`, `Tan`, `Sign`, etc.
- Global constants in `DropMath::F` and `DropMath::D` (e.g., `Pi`, `Epsilon`, `Infinity`, `Deg2Rad`)
- Support for `constexpr` functions and constants with `DM_CONSTEXPR_14` and `DM_CONSTEXPR_17`
- `.inl` inline file structure per vector and matrix type
- New test files: `Test_Mat2x2.cpp`, `Test_Mat3x3.cpp`, `Test_Utils.cpp`

### Changed
- Unified math utility function signatures using full overloads (`float`, `double`, `int`)
- Directory structure updated: added `ext/utils/DM_Utils.h/.inl`

---

## [v0.5.0] - 2025-07-28
### Added
- SIMD-accelerated Vec2, Vec3, Vec4, and Mat4x4
- Unit tests per feature (Test_VecX.cpp)
- Premake script and batch file for VS2022

### Notes
- Initial alpha release to gather community feedback.
