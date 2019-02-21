# What is this?
This is the testing directory of TI LaunchPad CC3220SF EVM Kit. All the codes written for it are present here.

# Table of contents
- [What is this?](#what-is-this)
- [Table of contents](#table-of-contents)
- [Files and Folders](#files-and-folders)
- [Softwares used](#softwares-used)
  - [Energia](#energia)
    - [Getting Started](#getting-started)
- [Resources](#resources)
  - [CC3220SF LaunchPad](#cc3220sf-launchpad)
  - [Energia](#energia-1)

# Files and Folders

# Softwares used
We've used the following software for our application

## Energia
Energia is an IDE built on Arduino and is specially for developers who're familiar with Arduino IDE but want to use TI products. You can find everything on their official website [here](http://energia.nu/). It's simple and easy to learn.

### Getting Started
To get started, do the following
- [Download](http://energia.nu/download/) Install Energia IDE as instructed [here](http://energia.nu/guide/) (choose your operating system there). All links are present in the [resources section](#resources).
- Open Energia and install the CC3220SF board
  - Go to **Tools** -> **Board** -> **Boards Manager...**
  - Search for `CC3220SF` and install `Energia CC3220SF EMT boards` package by *Energia*. Make sure that you have a stable internet connection.
  - Once the installation is done, it must look like this
    ![Energia installed image](../.media/photos/CC3220SF_board_energia.png)
- Connect the board, select the correct port and board under **Tools** -> **Board** and **Port**
- Upload the code under **File** -> **Examples** -> **01. Basics** -> **Blink** and see the results.
  - The red LED at D10 (bottom right of the board) must start blinking.
- Next, open a new window and try the [Blinks.ino](./Blinks/Blinks.ino) code. Upload it, and open the serial monitor when done.

The pinout of the board can be found in the resources section
[![Energia Pinout](../.media/photos/CC3220SF-LAUNCHXL-Energia_pinout.jpg)](https://energia.nu/pinmaps/cc3220sf-launchxl/)

# Resources
## CC3220SF LaunchPad
- **Official Website**: [ti/CC3220SF-LAUNCHXL][cc3220sf-Website]
- **Buy** from: [TI Store][cc3220sf-buy-ti_store]; [Tanotis][cc3220sf-buy-tanotis]
- **Datasheets** and **Reading Material**
  - [User Guide][cc3220sf-user_guide]
  - [Data sheet][cc3220sf-datasheet]
  - [Out-of-Box Application][cc3220sf-out_of_box_doc]
  - [CC3220SF LaunchXL **Energia** Pinout](http://energia.nu/pinmaps/cc3220sf-launchxl/)

[cc3220sf-out_of_box_doc]: http://www.ti.com/lit/ug/swru473a/swru473a.pdf
[cc3220sf-datasheet]: http://www.ti.com/lit/pdf/swas035
[cc3220sf-website]: http://www.ti.com/tool/CC3220SF-LAUNCHXL
[cc3220sf-buy-ti_store]: https://www.ti.com/store/ti/en/p/product/?p=CC3220SF-LAUNCHXL&HQS=epd-mcu-simp-slmcu-pr-storeevm-cc3220-tw
[cc3220sf-buy-tanotis]: https://www.tanotis.com/products/texas-instruments-cc3220sf-launchxl-development-kit-simplelink-trade-wi-fi-reg-cc3220sf-launchpad-256kb-of-ram-enhanced-security-features?gclid=Cj0KCQiAtbnjBRDBARIsAO3zDl8s9y9HivqBG4KFEib-s_GI1bvbnzsRK1MmtcFR9M7jcDPUSLMoGl0aAtyLEALw_wcB
[cc3220sf-user_guide]: http://www.ti.com/lit/pdf/swru463

## Energia
- **Official Website**: [energia.nu](http://energia.nu/)
- **Download**: [Energia/Download](http://energia.nu/download/)
- **Language Reference**: [Energia Language Reference](http://energia.nu/reference/)
- **Boards**
  - [Pin maps](http://energia.nu/pinmaps/)
  - [CC3220SF LaunchXL Pinout](http://energia.nu/pinmaps/cc3220sf-launchxl/)
- **Guides**
  - [Boards](http://energia.nu/guide/boards/)
  - [Environment](http://energia.nu/guide/environment/)
  - Installation
    - [Linux](http://energia.nu/guide/install/linux/)
    - [MacOS](http://energia.nu/guide/install/macos/)
    - [Windows](http://energia.nu/guide/install/windows/)
- **Libraries**: [Core Libraries](http://energia.nu/guide/libraries/)

[![TheProjectsGuy developer shield][TheProjectsGuy-dev-shield]][TheProjectsGuy-dev-profile]

[TheProjectsGuy-dev-shield]: https://img.shields.io/badge/Dev-TheProjectsGuy-0061ff.svg
[TheProjectsGuy-dev-profile]: https://github.com/TheProjectsGuy

