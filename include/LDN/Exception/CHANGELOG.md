# Changelog — LDN::Exception

This file documents all the changes and updates of the library LDN::Exception.

The format follows the standard [Keep a Changelog](https://keepachangelog.com/it/1.1.0/) and [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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