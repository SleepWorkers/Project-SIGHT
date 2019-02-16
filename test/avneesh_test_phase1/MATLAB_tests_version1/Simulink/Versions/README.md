# What is this ?
This folder contains the same files as the parent folder but for different versions of MATLAB. This is just to extend support.

# Table of contents
- [What is this ?](#what-is-this)
- [Table of contents](#table-of-contents)
- [Versions](#versions)
  - [R2016a](#r2016a)
- [Issues](#issues)
  - [Font rendering error - Ω](#font-rendering-error---%CF%89)
  - [Module not existing](#module-not-existing)

# Versions
## [R2016a](./R2016a/)
Files for MATLAB R2016a installations.

# Issues
The files in the main parent directory are made on MATLAB R2017b. Some files may have backward compatibility issues. We've mentioned a few below, but in case you find a bug, please [create an issue using the feature request template](https://github.com/SleepWorkers/Project-SIGHT/issues/new?template=feature_request.md), your effort is most appreciated.

## Font rendering error - Ω
Some MATLAB installations aren't rendering the _ohm_ character (which looks like Ω). In case this gives you issues, please remove it from everywhere in the file.

## Module not existing
A few models used might not be available on older version of MATLAB, in case they're not important, then please remove them, or [create an issue](https://github.com/SleepWorkers/Project-SIGHT/issues/new?template=feature_request.md) and we'll look into it.

The edit field functionality in Simulink doesn't exist in MATLAB 2016b or below, so the files depending upon that are not ported.

[![TheProjectsGuy developer shield](https://img.shields.io/badge/Dev-TheProjectsGuy-0061ff.svg)](https://github.com/TheProjectsGuy)

