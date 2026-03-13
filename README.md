#keyboard #qmk #vial

# QMK/VIAL Setup
- Using `WSL2` on the PC to set up and build `QMK/VIAL` environments. 
- QMK and VIAL use there own github repositories so need to clone both on the the WSL2 instance.
	QMK = `/home/amcfarlaa/qmk_firmware` 
	VIAL = `/home/amcfarlaa/vial-qmk`
- Use `qmk doctor` to repair missing directory's and submodules 

## QMK
[QMK Doco](https://docs.qmk.fm/)
QMK set up is pretty easy. just need a Linux distro and run `curl -fsSL https://install.qmk.fm | sh` which downloads everything needed and then pulls the qmk repository. 
- Using [qmk_userspaces](https://docs.qmk.fm/newbs_external_userspace) to house the keymaps external to the repository. 
	- `~/qmk_userspace`
	- Basically symlinks the user space folder to the repo so you can upload the configs to [github](https://github.com/ashm1988/qmk_userspace) without the full repository 
	- Need to set the userspace as the overlay `user.overlay_dir=/home/amcfarlaa/qmk_userspace`
### Useful setup commands
```sh
# Add a new keymap 
qmk new-keymap -kb gmmk/pro/rev1/ansi -km test
```

```sh
#qmk config commands (e.g qmk config user.keyboard=)
amcfarlaa@DESKTOP-2T7T6SI:~/qmk_userspace$ qmk config
#set default keyboard
user.keyboard=gmmk/pro/rev1/ansi
#set userspace location
user.overlay_dir=/home/amcfarlaa/qmk_userspace
```

## Vial
[Vial Doco](https://get.vial.today/manual/first-use.htm)
For the Vial set up, follow the QMK installation and then clone the [vial-qmk repository](https://github.com/vial-kb/vial-qmk)
- Need to `cd ~/vial-qmk` changes the `QMK_HOME` to `vial-qmk` directory
- Works with QMK User spaces

# GMMK Pro
- Currently using QMK for the `GMMK PRO` 
- Compile: `qmk compile -kb gmmk/pro/rev1/ansi -km ashm1988`
- Flash: Easier to just use the QMK Toolbox. 
	- Grab the `bin` file the compiler creates and flash with the toolbox
	- Can use `qmk flash` but not tested it (tested now and works well. Will be the new default)

# kbd67
- Currently using vial-qmk (lets me change it easy at work)
- Compile `qmk compile -kb kbdfans/kbd67/mkiirgb/v3 -km ashm1988`
- Flash: Grab the `bin` file and rename `FLASH.bin`. 
	- Putting the keyboard into DFU mode is basically a usb drive that you copy the `flash.bin` file to.
