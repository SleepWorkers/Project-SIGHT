# Contributing to Project SIGHT

:pray::thumbsup: First off, thanks for taking the time to contribute! :thumbsup::pray:

The following are the guidelines for contributing to Project SIGHT and it's various packages, which are hosted in the [Sleep Workers Organization](https://github.com/SleepWorkers) on GitHub. These are mostly guidelines, not rules. Use your best judgment, and feel free to propose changes to this document in a pull request.

## Table of Contents
- [Contributing to Project SIGHT](#contributing-to-project-sight)
  - [Table of Contents](#table-of-contents)
  - [Code of Conduct](#code-of-conduct)
  - [Have a question, feedback or suggestion ?](#have-a-question-feedback-or-suggestion)
- [Before Getting started](#before-getting-started)
  - [Suggestions to developers](#suggestions-to-developers)
- [Getting Started](#getting-started)
  - [Note to Developers](#note-to-developers)
    - [References](#references)
  - [Project guidelines](#project-guidelines)

## Code of Conduct
This project and everyone participating in it is governed by this code of conduct. By participating, you are expected to uphold and abide by this code. Please report any unacceptable behavior to 123avneesh@gmail.com. Thank you and enjoy :confetti_ball:

## Have a question, feedback or suggestion ?
This organization maintains a [Gitter community](https://gitter.im/Sleep-Workers/). We can't guarantee immediate response, we'll try our best to respond as soon as possible.

Any public questions, feature requests, suggestions and feedback can be done through [this Gitter chat room](https://gitter.im/Sleep-Workers/SIGHT-Doc), you can join it by clicking [here](https://gitter.im/Sleep-Workers/SIGHT-Doc?utm_source=share-link&utm_medium=link&utm_campaign=share-link). Please don't spam on this chat room and keep your points as brief as possible.

You can also create an issue using the `feature_request` template.

# Before Getting started
Before you get started, you're suggested to go through the following documents:
- [Code of conduct](./CODE_OF_CONDUCT.md) for this project.
- [License](./../LICENSE): Everything's open, you're free to fork and customize as much as you want.
- [Issue templates](./ISSUE_TEMPLATE/) of this project. Any issues that are opened must follow these templates.
- [README template](./README_TEMPLATE.md) for documentation.
- **About this documentation**
  - The documentation of this library contains _quoted sections_ for assistance. For example
    > **Note**: This is a note.

    > **Tip**: This is a tip.

## Suggestions to developers
Here are a few suggestions for the developers of this project. You're recommended to follow these:
- There's a [Gitter chatroom for developers](https://gitter.im/Sleep-Workers/SIGHT-Dev) of this project, which you can join by clicking [here](https://gitter.im/Sleep-Workers/SIGHT-Dev?utm_source=share-link&utm_medium=link&utm_campaign=share-link). No spamming, only formal developer chat.
- You're suggested to use a modern text editor or IDE for documentation and coding. Here's what we've used:
  - [Visual Studio Code](https://code.visualstudio.com/): Used for documentation and simple scripting.
- If you're using MacOS or Windows, [GitHub Desktop](https://desktop.github.com) is recommended.
- We've used the following operating systems in the development of this project. Note that not all operating systems might support all packages of the project.
  - [Ubuntu Xenial](http://releases.ubuntu.com/16.04/)
  - [MacOS Mojave](https://www.apple.com/in/macos/mojave/)
- Developers are suggested to append their developer shields at the end of their documents, just so that we know who's contributed for what. You can use [this website](https://shields.io/#/) for creating your developer shields.
- Your work is useful only if others understand it, kindly do the commenting, documentation and code presentation work neatly.

# Getting Started

## Note to Developers
You're strongly suggested to understand items under this note. Please go through the following:
- There are two types of developers for this project:
  - **Core Developers**: These are developers of the Sleep Workers organization. This is a private and closed group for the core people directly involved in this project. Joining this group requires approval from Sleep Workers organization ([Gitter chatroom](https://gitter.im/Sleep-Workers/GitHub-Core-Developers)). 
    - All core developers must have a shield like what's shown below (color #0061ff) and it must link to their GitHub profile:

        ![Core Developer shield](https://img.shields.io/badge/Dev-GitHub--Username-0061ff.svg)
  - **Open Developers**: These are voluntary developers who might or might not belong to the Sleep Workers organization. You could be an open developer for the entire organization ([Gitter chatroom](https://gitter.im/Sleep-Workers/GitHub-Developers) and join [here](https://gitter.im/Sleep-Workers/GitHub-Developers?utm_source=share-link&utm_medium=link&utm_campaign=share-link)) or just for this project ([Gitter chatroom](https://gitter.im/Sleep-Workers/SIGHT-Dev) and join [here](https://gitter.im/Sleep-Workers/SIGHT-Dev?utm_source=share-link&utm_medium=link&utm_campaign=share-link)).
    - All open developers must have a shield like what's shown below (color #0098bf) and it must link to their GitHub profile: 
        
        ![Open Developers shield](https://img.shields.io/badge/Dev-GitHub--Username-0098bf.svg)
    > **Tip**: You can use [shields.io](https://shields.io/#/) to create developers shields
- All your work must be well documented. `README.md` files are a good way of creating useful documentation for your work. You're urged to follow [this README template](./README_TEMPLATE.md), just to maintain uniformity.
- This project follows _pull request_ workflow. Here's a step-by-step briefing of how work is done:
    1. An issue is created using one of the [templates](./ISSUE_TEMPLATE/).
    2. A branch is created from the `dev` branch under the name `issue-NUMBER`. For example, `issue-3`.
       > **Tip**: You could use another name if it's more descriptive but still short and brief
    3. Work is done on the branch 
    4. Changes are pushed to the branch
    5. Step 3 and 4 are repeated till the issue is solved and is tested.
    6. A pull request is made to the _dev_ branch. 
       > **Note**: Make sure that `dev` branch is the base branch, _not_ `master`.
    7. After the pull request is approved and merge is successful, the branch may be deleted.
- Throughout development process, developers test the work on `dev` branch in regular intervals. If an agreement is made, a pull request to `master` is created. This way, `master` always has the _working_ and _tested_ version of the project.

### References
- [GitHub Help](https://help.github.com/)
  - [Creating a Pull Request](https://help.github.com/articles/creating-a-pull-request/)
  - [Changing the base branch of a pull request](https://help.github.com/articles/changing-the-base-branch-of-a-pull-request/)

## Project guidelines
- All work is compartmentalized into a well defined file structure. You're supposed to follow the same. This makes navigation easy.
- A documentation for all your work is a **must** for the pull request to be accepted.

[![TheProjectsGuy developer shield](https://img.shields.io/badge/Dev-TheProjectsGuy-0061ff.svg)](https://github.com/TheProjectsGuy)
