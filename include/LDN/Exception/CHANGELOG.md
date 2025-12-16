# Changelog — LDN::Exception

This file documents all the changes and updates of the library LDN::Exception.

The format follows the standard [Keep a Changelog](https://keepachangelog.com/it/1.1.0/) and [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.1.0] - 2025-12-16
### Added
- Implemented Exception Classes:
    - `LDN::exception::Dimension` for verifing the compatibility of the dimension of two Data-Structure
- New versioned documentation folder: `docs/Exception/v1.1/`

### Changed
- Nothing changed in this release

### Fixed
- Nothing fixed in this release

### Deprecated
- Nothing deprecated in this release

### Removed
- Nothing removed in this release

### Security
- No security fixes

---

## [1.0.1] - 2025-12-09
### Fixed
- Add attributes [[ ]] to the getter of `LDN::Exception`

---

## [1.0.0] - 2025-11-05
### Added
- First release of the library `Exception`
- Core Exception Interface `LDN::Exception`
- Implemented Exception Classes:
    - `LDN::exception::Index` for out-of-bounds Data-Structure access
    - `LDN::exception::Size` for filling an already full Data-Structure
    - `LDN::exception::File` for FileStreams opening errors
- Utility functions for Exception catching
- Header-only implementation with C++20 support

### Documentation
- Full API documentation
- Test examples for each Exception
- Release with the `.deb` package

### Requires
- C++20 compatible compiler
- Header-only library, no additional dependencies