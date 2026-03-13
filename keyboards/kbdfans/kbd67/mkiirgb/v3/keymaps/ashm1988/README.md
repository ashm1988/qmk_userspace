#qmk #vial #keyboard
# Keyboard Firmware Documentation

This document describes the custom QMK/Vial configuration used in this firmware, including tap‑dance behaviour, custom macros, layers, and keymap structure.

---

## 1. Overview

This keymap extends standard QMK functionality with:

- Custom **tap‑dance** **double tap** actions (pipe on `;`, Shift+Insert on `V`)
- A custom **macro keycode** (`SS_PANE`)
- Multiple **layers** (Colemak, QWERTY, FN)
- Integration with **Vial dynamic tap‑dance entries**

The configuration is designed for a 65% ANSI blocker layout.

---

## 2. Tap Dance Configuration

### Tap‑Dance Timing

A custom tapping term is defined:

```
#define TAP_TAPPING_TERM 200
```

This sets a 200ms window to detect taps vs holds.

### Tap‑Dance Entries

Two tap‑dance entries are installed at keyboard startup:

| TD Slot | Base Key        | Hold Action | Double Tap Action               | Notes                                               |
| ------- | --------------- | ----------- | ------------------------------- | --------------------------------------------------- |
| `TD(0)` | `;` (`KC_SCLN`) | —           | `\|` `(KC_PIPE)`                | Produces a ';' when tapped; '\|' when double tapped |
| `TD(1)` | `V` (`KC_V`)    | —           | `Shift+Insert` (`LSFT(KC_INS)`) | Useful for paste operations in Linux                |

These are registered using Vial’s `dynamic_keymap_set_tap_dance()` inside `keyboard_post_init_user()`.

### Tap‑Dance Aliases

To simplify keymap usage:

```
#define TD_PIPE   TD(0)
#define TD_Insert TD(1)
```
These aliases appear directly in the keymap definitions.

---

## 3. Custom Macro: `SS_PANE`

A custom keycode is defined:
```
enum custom_keycodes {
    SS_PANE = SAFE_RANGE,
};
```

### Behavior

When pressed, `SS_PANE` sends:
- `Ctrl + A`
- `Shift + '`

This is implemented using QMK’s `SEND_STRING()` API:s
```
SEND_STRING(SS_LCTL("a") SS_LSFT(SS_TAP(X_QUOTE)));
```
This macro is placed on the **FN layer** for quick access.
Used for opening a new **pane** in **tmux**

---

## 4. Layer Structure

Three layers are defined:

|Layer|Name|Purpose|
|---|---|---|
|`_COLEMAK`|Base Layer|Primary typing layer using Colemak layout|
|`_QWERTY`|Alternate Base|Standard QWERTY layout|
|`_FN`|Function Layer|Navigation, F‑keys, bootloader, macro, and system controls|

Layer switching is handled via:
- `LT(_FN, key)` for momentary FN access
- `MO(_FN)` for FN momentary layer toggle
- `TO(layer)` for permanent layer switching

---

## 5. Keymap Summary

### Colemak Layer (`_COLEMAK`)

- Standard Colemak alpha layout
- `TD_PIPE` replaces `;`
- `TD_Insert` replaces `V` in the bottom row
- FN access via `LT(_FN, KC_R)` and `LT(_FN, KC_I)`
- Navigation keys on the right column
    

### QWERTY Layer (`_QWERTY`)

- Mirrors the Colemak layer structure but with QWERTY alpha positions
- Tap‑dance keys remain in the same physical positions

### Function Layer (`_FN`)

Includes:
- Full F‑row (`F1`–`F12`)
- Arrow keys
- Print Screen, Scroll Lock, Pause
- `QK_BOOT` for bootloader entry
- `SS_PANE` macro
- `EE_CLR` for EEPROM reset    
- Layer switching (`TO(_COLEMAK)`, `TO(_QWERTY)`)
    

---

## 6. Initialization

At startup, QMK calls:

```
keyboard_post_init_user()
```

This function installs all tap‑dance entries so they are available immediately when the keyboard becomes active.

---

## 7. File Structure Notes

- All tap‑dance logic is centralized in `install_tap_dance_entries()`
- Macros are handled in `process_record_user()`
- Layer enums and keymaps are grouped for readability
- Tap‑dance aliases (`TD_PIPE`, `TD_Insert`) keep the keymap clean and readable
