# Changelog — LDN::Hash

This file documents all the changes and updates of the library LDN::Hash.

The format follows the standard [Keep a Changelog](https://keepachangelog.com/it/1.1.0/) and [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [1.0.0] - 2025-11-16
### Added
- First release of the library `Hash`
- Core Hash Interface `LDN::Hash`
- Implemented Hash Abstract Class `LDN::HashSet` 
- Implemented Specification Classes:
    - `LDN::hash_set::Open` for Hash-Sets with Open hashing
    - `LDN::hash_set::Close` for Hash-Sets with Close hashing
- Operator << for Hash-Structures
- Header-only implementation with C++20 support
- Shared Library `libLDN_Hash.so` for Explicit Template Instantations

### Documentation
- Full API documentation
- Test examples for each Hash-Set Specification
- Release with the `.deb` package

### Requires
- C++20 compatible compiler
- Header-only library, no additional dependencies
- For primitive types avaible pre-compiled Shared Library