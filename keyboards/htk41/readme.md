# htk41

A 41-key custom keyboard.

* Keyboard Maintainer: [htrkdk](https://github.com/htrkdk)
* Hardware Supported: htk41, Pro Micro
* Hardware Availability: *Not available right now*

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb htk41 -km default

Flashing example for this keyboard:

    qmk flash -kb htk41 -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
