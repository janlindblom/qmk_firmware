# Spacemouse Wireless MacroPad

![Spacemouse Wireless MacroPad](https://i.imgur.com/DXIBOps.jpg)

QMK firmware for "Spacemouse Wireless MacroPad" by [Arron Craig](https://www.thingiverse.com/ajcraig/), available [on Thingiverse](https://www.thingiverse.com/thing:3562600).

> A 2 part macro pad print for use with the 3D Conexxion Wireless Spacemouse, mechanical keyboard switches and a Pro Micro controller.
>
> The Spacemouse simply snaps in place and can be easily removed if needed.

* Keyboard Maintainer: [Jan Lindblom](https://github.com/janlindblom)
* Hardware Supported:
  * Any ProMicro controller **with Micro USB, USB-C won't fit**
  * Any MX-sized switches and keycaps
* Hardware Availability: Printable parts available on Thingiverse: <https://www.thingiverse.com/thing:3562600>

Make example for this keyboard (after setting up your build environment):

    make 7button_3dx_macropad:default

Flashing example for this keyboard:

    make 7button_3dx_macropad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

* **Physical reset button**: Briefly press the button on microcontroller - or short RST and GND twice
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
