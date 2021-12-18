# myrmidex
I will insert Image later, I swear


7*3 split keyboard with two encoders above the thumb cluster, agressive pinky stagger and pads for power switch and battery. This keyboard is a mix of jorne and kyria keyboards. 

* Keyboard Maintainer: [hexagramg](https://github.com/hexagramg)
* Hardware Supported: All the pro-micro layout compatible micro controllers
* Hardware Availability: DIY as in do it yourself, [gerbers here](https://github.com/hexagramg/myrmidex-keeb)

Make example for this keyboard (after setting up your build environment):

    make myrmidex:default

Flashing example for this keyboard:

    make myrmidex:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: There are two through hole pads above the first row near the pro-micro. Short it twice to reboot.
* **Keycode in layout**: Press the key mapped to `RESET`, you can find it in layout.
