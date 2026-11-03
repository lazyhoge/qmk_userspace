// 7sKB のキーマップ。普段使いの Cornix（ZMK、github.com/lazyhoge/zmk-keyboard-cornix の
// config/cornix.keymap）と同じ指の動きで打てるように寄せている。
//
// 対応の決め方（2026-11-03 に本人と決めた）:
// - Cornix と同じ位置にあるキー（英字の3段・左右の端・親指）は Cornix に合わせる
// - Cornix に無い 7sKB だけのキー（数字の段・右端の列）は、普通のキーボードのまま残す
// - 7sKB の親指キーは片手2つなので、左は「記号」と Space にし、Cornix の
//   「押すと数字・叩くと ESC」は外す（数字は数字の段で、ESC は左上とコンボで打つ）
// - 右下の Fn の位置を RGUI にし、アプリのレイヤーは Navi を押したまま Fn で出す
// - Cornix の Bluetooth のレイヤー（Adjust）と ONISHI のレイヤーは持ってこない
#include QMK_KEYBOARD_H

enum layers {
    BASE = 0, // Cornix の QWERTY
    SYM,      // Cornix の Symbol_layer（3）
    NAVI,     // Cornix の Navi_layer（4）
    MOVE,     // Cornix の MOVE（5）
    APPS,     // Cornix の appswin（7）
};

// QMK の基本キーコードに無い consumer の usage を送るキー（Cornix の appswin 用）
enum custom_keycodes {
    CK_FILES = SAFE_RANGE, // AL File Browser（0x1B4）。ZMK の C_AL_FILE_BROWSER
    CK_EDITOR,             // AL Text Editor（0x185）。ZMK の C_AL_TEXT_EDITOR
    CK_LOCK,               // AL Terminal Lock/Screensaver（0x19E）。ZMK の K_SCREENSAVER の代わり
};

// Cornix の printscreen_win マクロ（&kp LG(LS(S))）
#define PSCR_WIN LGUI(LSFT(KC_S))

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // 右端の列: 1段目 [ ] BS、2段目 - Enter、3段目 Shift RGUI。
    // 右の Shift は Cornix に合わせて LSFT（Shift で形が変わるキーは LSFT だけに反応する）
    [BASE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_MINS, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT, KC_RGUI,
                 KC_LGUI, KC_LALT, MO(SYM), KC_SPC,                 KC_ENT,  KC_BSPC, MO(NAVI), KC_RALT
    ),

    // 括弧と < > は「左 Shift で閉じる側」（下の key_overrides）
    [SYM] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, KC_CIRC, KC_GRV,  KC_LBRC, KC_PAST, KC_PSLS, _______, _______,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       KC_EQL,  KC_AMPR, KC_QUOT, KC_LPRN, KC_PPLS, KC_PMNS, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, KC_PIPE, KC_GRV,  KC_LCBR, KC_BSLS, XXXXXXX, XXXXXXX,
                 _______, _______, _______, _______,                _______, _______, _______, KC_LT
    ),

    // 左の親指（記号の位置）で MOVE。右下（Fn の位置）で APPS
    [NAVI] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_ESC,  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,        XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,
        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,        XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(APPS),
                 _______, XXXXXXX, MO(MOVE), _______,               _______, _______, _______, XXXXXXX
    ),

    [MOVE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______,
        XXXXXXX, XXXXXXX, MS_BTN1, MS_UP,   MS_BTN3, MS_WHLU,       XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,
        XXXXXXX, XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLD,       XXXXXXX, KC_HOME, KC_PGDN, KC_END,  XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 KC_CAPS, XXXXXXX, _______, _______,                _______, _______, _______, XXXXXXX
    ),

    // 左上の Esc の位置（Cornix には無いキー）に QK_BOOT。リセットスイッチを押さずに書き込める
    [APPS] = LAYOUT(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_KB_POWER, XXXXXXX, XXXXXXX, CK_FILES, XXXXXXX, CK_EDITOR,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, PSCR_WIN, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, CK_LOCK, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_CALC, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                XXXXXXX, XXXXXXX, _______, XXXXXXX
    ),
};
// clang-format on

// Cornix の combos（どれも base のレイヤーだけで効く）
const uint16_t PROGMEM combo_esc[]  = {KC_W, KC_R, COMBO_END};
const uint16_t PROGMEM combo_lng2[] = {KC_S, KC_F, COMBO_END};
const uint16_t PROGMEM combo_lng1[] = {KC_J, KC_L, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_esc, KC_ESC),   // W+R → ESC
    COMBO(combo_lng2, KC_LNG2), // S+F → 英数
    COMBO(combo_lng1, KC_LNG1), // J+L → かな
};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    return get_highest_layer(layer_state) == BASE;
}

// Cornix の mod-morph。ZMK の定義が MOD_LSFT だけなので、左 Shift だけに反応させる
#define LSFT_ONLY MOD_BIT(KC_LSFT)
const key_override_t ko_bspc_del  = ko_make_basic(LSFT_ONLY, KC_BSPC, KC_DEL);  // shift_backspace
const key_override_t ko_paren     = ko_make_basic(LSFT_ONLY, KC_LPRN, KC_RPRN); // shift_Parenthesis
const key_override_t ko_bracket   = ko_make_basic(LSFT_ONLY, KC_LBRC, KC_RBRC); // shift_bracket
const key_override_t ko_brace     = ko_make_basic(LSFT_ONLY, KC_LCBR, KC_RCBR); // shift_brace
const key_override_t ko_than      = ko_make_basic(LSFT_ONLY, KC_LT, KC_GT);     // shift_than

const key_override_t *key_overrides[] = {
    &ko_bspc_del, &ko_paren, &ko_bracket, &ko_brace, &ko_than,
};

static uint16_t consumer_usage(uint16_t keycode) {
    switch (keycode) {
        case CK_FILES:
            return 0x1B4;
        case CK_EDITOR:
            return 0x185;
        case CK_LOCK:
            return AL_LOCK;
        default:
            return 0;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t usage = consumer_usage(keycode);
    if (usage) {
        host_consumer_send(record->event.pressed ? usage : 0);
        return false;
    }
    return true;
}
