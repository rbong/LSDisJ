;;;;;;;;;;;;;;;
;; Constants ;;
;;;;;;;;;;;;;;;

;; gbdk 2.9.5 libc/gb/global.ms definitions ;;

_G_MODE       EQU $01
_T_MODE       EQU $02
_T_MODE_OUT   EQU $02
_T_MODE_INOUT EQU $03

;  Status codes for IO
_IO_IDLE      EQU $00
_IO_SENDING   EQU $01
_IO_RECEIVING EQU $02
_IO_ERROR     EQU $04

; IO transfer request byte for rSC
_IO_TRANSFER_REQUESTED EQU $81

; Type of IO data
_DT_IDLE      EQU $66
_DT_RECEIVING EQU $55

;; gbdk 2.9.5 libc/gb/font.ms definitions ;;

_SFONT_HANDLE_FIRST_TILE EQU 0
_SFONT_HANDLE_FONT       EQU 1
_SFONT_HANDLE_SIZEOF     EQU 3

;; Interrupt Constants ;;

_INTERRUPT_DISABLE EQU $f3
_INTERRUPT_ENABLE  EQU $fb

;; Draw Constants ;;

_TILE_MAP_SIZE EQU $20

_TILE_ROWS EQU $12
_TILE_COLS EQU $14

;; GameBoy Types ;;

_GAMEBOY       EQU $00
_GAMEBOY_COLOR EQU $01

;; DMG Color Types ;;

_DMG_COLOR_BACKGROUND EQU $00
_DMG_COLOR_SECONDARY  EQU $01
_DMG_COLOR_FOREGROUND EQU $02

;; Buttons ;;

_BUTTON_RIGHT  EQU %00000001
_BUTTON_LEFT   EQU %00000010
_BUTTON_UP     EQU %00000100
_BUTTON_DOWN   EQU %00001000
_BUTTON_A      EQU %00010000
_BUTTON_B      EQU %00100000
_BUTTON_SELECT EQU %01000000
_BUTTON_START  EQU %10000000

;; ASCII Codes ;;

_EMPTY_ROW_ASCII_CODE 		  EQU $2d
_BACKSPACE_ASCII_CODE       EQU $3e
_OUTPUT_L_ON_ASCII_CODE     EQU $4c
_OUTPUT_R_ON_ASCII_CODE     EQU $52
_PULSE_WAVE_50_ASCII_CODE   EQU $61
_PULSE_WAVE_25_ASCII_CODE   EQU $62
_PULSE_WAVE_12_5_ASCII_CODE EQU $63
_PULSE_WAVE_FLAT_ASCII_CODE EQU $64
_PULSE_WAVE_75_ASCII_CODE_1 EQU $65
_PULSE_WAVE_75_ASCII_CODE_2 EQU $66
_OUTPUT_L_OFF_ASCII_CODE    EQU $67
_OUTPUT_R_OFF_ASCII_CODE    EQU $68
_OKAY_ASCII_CODE            EQU $77
_SPECIAL_ASCII_CODE         EQU $78

;; Screens ;;

_PHRASE_SCREEN      EQU $01
_GROOVE_SCREEN      EQU $02
_CHAIN_SCREEN       EQU $03
_SONG_SCREEN        EQU $04
_TABLE_SCREEN       EQU $05
_INSTRUMENT_SCREEN  EQU $06
_CRASH_SCREEN       EQU $07
_WAVE_EDITOR_SCREEN EQU $08
_PROJECT_SCREEN     EQU $09
_SYNTH_SCREEN       EQU $0a
_TALK_SCREEN        EQU $0b
_WORD_SCREEN        EQU $0c
_FILE_SCREEN        EQU $0d
_HELP_SCREEN        EQU $0e

;; Screen Constants ;;

_SCREEN_ROWS EQU 3

_SCREEN_ROW_1_WIDTH EQU 4

_SCREEN_MOVE_NONE  EQU 0
_SCREEN_MOVE_UP    EQU 1
_SCREEN_MOVE_RIGHT EQU 2
_SCREEN_MOVE_DOWN  EQU 3
_SCREEN_MOVE_LEFT  EQU 4

;; Cursor Modes ;;

_NO_CURSOR_MODE     EQU $01
_NORMAL_CURSOR_MODE EQU $02
_SELECT_CURSOR_MODE EQU $04

;; Commands ;;

_A_COMMAND EQU $01
_B_COMMAND EQU $02
_C_COMMAND EQU $03
_D_COMMAND EQU $04
_E_COMMAND EQU $05
_F_COMMAND EQU $06
_G_COMMAND EQU $07
_H_COMMAND EQU $08
_K_COMMAND EQU $09
_L_COMMAND EQU $0a
_M_COMMAND EQU $0b
_O_COMMAND EQU $0c
_P_COMMAND EQU $0d
_R_COMMAND EQU $0e
_S_COMMAND EQU $0f
_T_COMMAND EQU $10
_V_COMMAND EQU $11
_W_COMMAND EQU $12
_Z_COMMAND EQU $13

;; File Action Types ;;

_LOAD_FILE_ACTION_TYPE  EQU $00
_SAVE_FILE_ACTION_TYPE  EQU $01
_ERASE_FILE_ACTION_TYPE EQU $02

;; Output Types ;;

_OUTPUT_L_ON_R_ON_VALUE   EQU $00
_OUTPUT_L_ON_R_OFF_VALUE  EQU $01
_OUTPUT_L_OFF_R_ON_VALUE  EQU $02
_OUTPUT_L_OFF_R_OFF_VALUE EQU $03

;; Oscilloscope Draw Types ;;

_NO_DRAW_OSCILLOSCOPE     EQU $00
_UPDATE_DRAW_OSCILLOSCOPE EQU $01
_CLEAR_DRAW_OSCILLOSCOPE  EQU $02

;; Instrument Types ;;

_PULSE_INSTRUMENT_TYPE EQU 0
_WAVE_INSTRUMENT_TYPE  EQU 1
_KIT_INSTRUMENT_TYPE   EQU 2
_NOISE_INSTRUMENT_TYPE EQU 3

_INSTRUMENT_TYPES EQU 4

;; Instrument Constants ;;

_SPEECH_INSTRUMENT EQU $40

;; Pitch Types ;;

_PITCH_SPEED_DRUM EQU %0100
_PITCH_SPEED_FAST EQU %0000
_PITCH_SPEED_TICK EQU %0001
_PITCH_SPEED_STEP EQU %1000

_PITCH_SHAPE_FALLING_TRI    EQU %000
_PITCH_SHAPE_FALLING_SAW    EQU %010
_PITCH_SHAPE_FALLING_SQUARE EQU %100
_PITCH_SHAPE_RISING_TRI     EQU %001
_PITCH_SHAPE_RISING_SAW     EQU %011
_PITCH_SHAPE_RISING_SQUARE  EQU %101

_NOISE_PITCH_FREE EQU 0
_NOISE_PITCH_SAFE EQU 1

;; Pulse Wave Types ;;

_PULSE_WAVE_12_5 EQU 0
_PULSE_WAVE_25   EQU 1
_PULSE_WAVE_50   EQU 2
_PULSE_WAVE_75   EQU 3

;; Wave Play Types ;;

_PLAY_MANUAL   EQU 0
_PLAY_ONCE     EQU 1
_PLAY_LOOP     EQU 2
_PLAY_PINGPONG EQU 3
_PLAY_RESYNC   EQU 4

;; Kit Constants ;;

; Every defined kit starts with these two bytes
_KIT_CHECK_1 EQU $60
_KIT_CHECK_2 EQU $40

_MAX_KIT_BANK EQU $3f

;; Speech Kits ;;

_SPEECH_KIT_START EQU $12
_SPEECH_KITS      EQU 4

;; Kit Clip Types ;;

; Any values not listed here are noise
_KIT_CLIP_HARD EQU $d0
_KIT_CLIP_SOFT EQU $d1
_KIT_CLIP_FOLD EQU $d2
_KIT_CLIP_WRAP EQU $d3

;; Synth Signal Types ;;

_SAW_SYNTH_SIGNAL      EQU $00
_SQUARE_SYNTH_SIGNAL   EQU $01
_TRIANGLE_SYNTH_SIGNAL EQU $02
_FRAME_SYNTH_SIGNAL    EQU $03

;; Synth Filters ;;

_LOWPASS_FILTER  EQU $00
_HIGHPASS_FILTER EQU $01
_BANDPASS_FILTER EQU $02
_ALLPASS_FILTER  EQU $03

;; Synth Dist Types ;;

_CLIP_DIST EQU $00
_FOLD_DIST EQU $01
_WRAP_DIST EQU $02

;; Synth Phase Types ;;

_PINCH_PHASE   EQU $00
_WARP_PHASE    EQU $01
_RESYNC_PHASE  EQU $02
_RESYNC2_PHASE EQU $03

;; Sync Types ;;

_SYNC_OFF        EQU $00
_SYNC_LSDJ       EQU $01
_SYNC_MIDI       EQU $03
_SYNC_KEYBOARD   EQU $05
_SYNC_ANALOG_IN  EQU $06
_SYNC_ANALOG_OUT EQU $07

;; Clone Types ;;

_CLONE_DEEP EQU $00
_CLONE_SLIM EQU $01

;; Overclock Types ;;

_OVERCLOCK_OFF EQU $00
_OVERCLOCK_2X  EQU $01
_OVERCLOCK_3X  EQU $02
_OVERCLOCK_6X  EQU $03

;; Shared Instrument Params ;;

_INSTRUMENT_TYPE_INSTRUMENT_PARAM EQU $00

;; Pulse Type Instrument Params ;;

_ENV_STAGE_1_INSTRUMENT_PARAM   EQU $01 ; 8 bits
_PU2_TRANSPOSE_INSTRUMENT_PARAM EQU $02 ; 8 bits
_LENGTH_INSTRUMENT_PARAM        EQU $03 ; 7 bits (0 through 6) (unlim: 0, other: 0x7f - value)
_SWEEP_INSTRUMENT_PARAM         EQU $04 ; 7 bits (0 through 6)
_PITCH_SHAPE_INSTRUMENT_PARAM   EQU $05 ; 3 bits (0, 1, 2)     (see above)
_TABLE_STEP_INSTRUMENT_PARAM    EQU $05 ; 1 bit  (3)           (bool)
_PITCH_SPEED_INSTRUMENT_PARAM   EQU $05 ; 3 bits (4, 6, 7)     (see above)
_TRANSPOSE_INSTRUMENT_PARAM     EQU $05 ; 1 bit  (5)           (on: 0, off: 1)
_TABLE_ON_INSTRUMENT_PARAM      EQU $06 ; 1 bit  (5)
_TABLE_INSTRUMENT_PARAM         EQU $06 ; 4 bits (0, 1, 2, 3)
_OUTPUT_INSTRUMENT_PARAM        EQU $07 ; 2 bits (0, 1)        (L: bit 0, R: bit 1)
_PULSE_WAVE_INSTRUMENT_PARAM    EQU $07 ; 2 bits (6, 7)        (see above)
_COMMAND_RATE_INSTRUMENT_PARAM  EQU $08 ; 4 bits (0, 1, 2, 3)
_ENV_STAGE_2_INSTRUMENT_PARAM   EQU $09 ; 8 bits
_ENV_STAGE_3_INSTRUMENT_PARAM   EQU $0a ; 8 bits
_FINETUNE_INSTRUMENT_PARAM      EQU $0b ; 8 bits

;; Wave Type Instrument Params ;;

_WAVE_VOLUME_INSTRUMENT_PARAM   EQU $01 ; 2 bits (5, 6)       (0 - value)
_WAVE_LOOP_POS_INSTRUMENT_PARAM EQU $02 ; 4 bits (0, 1, 2, 3)
_WAVE_FRAME_INSTRUMENT_PARAM    EQU $03 ; 8 bits
_WAVE_SYNTH_INSTRUMENT_PARAM    EQU $03 ; 4 bits (4, 5, 6, 7)
_WAVE_PLAY_INSTRUMENT_PARAM     EQU $09 ; 3 bits (0, 1, 2)    (see above)
_WAVE_LENGTH_INSTRUMENT_PARAM   EQU $0a ; 4 bits (0, 1, 2, 3) (0xf - value)
_WAVE_SPEED_INSTRUMENT_PARAM    EQU $0b ; 8 bits              (value - 4)
_WAVE_FINETUNE_INSTRUMENT_PARAM EQU $0c ; 8 bits

;; Kit Type Instrument Params ;;

_KIT_NUMBER_1_INSTRUMENT_PARAM      EQU $02 ; 6 bits (0 through 5) (value + 1)
_KIT_SPEED_INSTRUMENT_PARAM         EQU $02 ; 1 bit  (6)           (1x: 0, 0.5x: 1)
_KIT_1_LOOP_ATTACK_INSTRUMENT_PARAM EQU $02 ; 1 bit  (7)           (bool)
_KIT_1_LENGTH_INSTRUMENT_PARAM      EQU $03 ; 8 bits               (all: 0, other: value)
_KIT_1_LOOP_ON_INSTRUMENT_PARAM     EQU $05 ; 1 bit  (6)           (bool)
_KIT_2_LOOP_ON_INSTRUMENT_PARAM     EQU $05 ; 1 bit  (7)           (bool)
_KIT_FINETUNE_INSTRUMENT_PARAM      EQU $08 ; 8 bits
_KIT_NUMBER_2_INSTRUMENT_PARAM      EQU $09 ; 6 bits (0 through 5) (value + 1)
_KIT_2_LOOP_ATTACK_INSTRUMENT_PARAM EQU $09 ; 1 bit  (7)           (bool)
_KIT_CLIP_INSTRUMENT_PARAM          EQU $a0 ; 8 bits               (see above)
_KIT_1_OFFSET_INSTRUMENT_PARAM      EQU $0c ; 8 bits
_KIT_2_LENGTH_INSTRUMENT_PARAM      EQU $0b ; 8 bits               (all: 0, other: value)
_KIT_2_OFFSET_INSTRUMENT_PARAM      EQU $0d ; 8 bits

;; Noise Type Instrument Params ;;

_NOISE_PITCH_INSTRUMENT_PARAM EQU $02 ; 1 bit (0) (see above)

;; Synth Params ;;

_SIGNAL_SYNTH_PARAM      EQU $00 ; 8 bits              (see above)
_FILTER_SYNTH_PARAM      EQU $01 ; 8 bits              (see above)
_RESONANCE_2_SYNTH_PARAM EQU $02 ; 4 bits (0, 1, 2, 3)
_RESONANCE_1_SYNTH_PARAM EQU $02 ; 4 bits (4, 5, 6, 7)
_DIST_SYNTH_PARAM        EQU $03 ; 8 bits              (see above)
_PHASE_TYPE_SYNTH_PARAM  EQU $04 ; 8 bits              (see above)
_VOLUME_1_SYNTH_PARAM    EQU $05 ; 8 bits
_CUTOFF_1_SYNTH_PARAM    EQU $06 ; 8 bits
_PHASE_1_SYNTH_PARAM     EQU $07 ; 8 bits              (max 0x1f)
_VSHIFT_1_SYNTH_PARAM    EQU $08 ; 8 bits
_VOLUME_2_SYNTH_PARAM    EQU $09 ; 8 bits
_CUTOFF_2_SYNTH_PARAM    EQU $0a ; 8 bits
_PHASE_2_SYNTH_PARAM     EQU $0b ; 8 bits              (max 0x1f)
_VSHIFT_2_SYNTH_PARAM    EQU $0c ; 8 bits
_LIMIT_1_SYNTH_PARAM     EQU $0d ; 8 bits              (0x0f - value)
_LIMIT_2_SYNTH_PARAM     EQU $0e ; 8 bits              (0x0f - value)

;; SRAM Constants ;;

_PHRASES      EQU $ff
_PHRASE_NOTES EQU $10

_BOOKMARKS     EQU $10

_GROOVES     EQU $20
_GROOVE_ROWS EQU $10

_SONG_ROWS EQU $c0
_SONG_COLS EQU $04

_CHANNELS EQU 4

_PULSE1_CHANNEL EQU 0
_PULSE2_CHANNEL EQU 1
_WAVE_CHANNEL   EQU 2
_NOISE_CHANNEL  EQU 3

_TABLES     EQU $20
_TABLE_ROWS EQU $10

_SPEECH_WORDS     EQU $0e
_SPEECH_WORD_ROWS EQU $10
_SPEECH_WORD_COLS EQU $02

_SPEECH_WORD_SYLLABLE_COL EQU $00
_SPEECH_WORD_LENGTH_COL   EQU $00

_SPEECH_WORD_NAME_LENGTH EQU $03

_SRAM_CHECK_1 EQU $72
_SRAM_CHECK_2 EQU $62

_SRAM_FILE_CHECK_1 EQU $6a
_SRAM_FILE_CHECK_2 EQU $6b

_INSTRUMENTS            EQU $40
_INSTRUMENT_NAME_LENGTH EQU $05

_CHAINS     EQU $80
_CHAIN_ROWS EQU $10

_INSTRUMENT_PARAMS_SIZE EQU $10

_SYNTHS            EQU $10
_SYNTH_PARAMS_SIZE EQU $10

_MIN_TEMPO EQU 40

_SYNTH_FRAMES     EQU $10
_SYNTH_FRAME_SIZE EQU $10

_FRAME_SAMPLES EQU $20

_MAX_FILES        EQU $20
_FILE_NAME_LENGTH EQU $08

_BLOCKS EQU $bf

;;;;;;;;;;;;;;;;;;;;;
;; Memory Sections ;;
;;;;;;;;;;;;;;;;;;;;;

; gbdk 2.95 libc/gb/global.s:OAM
_OAM EQU $dd

;; SRAM Banks ;;

_SRAM_PHRASE_NOTES_BANK      EQU $00
_SRAM_BOOKMARKS_BANK         EQU $00
_SRAM_GROOVES_BANK           EQU $00
_SRAM_SONG_CHAINS_BANK       EQU $00
_SRAM_TABLE_VOLS_BANK        EQU $00
_SRAM_SPEECH_WORDS_BANK      EQU $00
_SRAM_SPEECH_WORD_NAMES_BANK EQU $00
_SRAM_INIT_FLAG_1_BANK       EQU $00
_SRAM_INSTRUMENT_NAMES_BANK  EQU $00

_SRAM_INSTRUMENT_ALLOC_BANK       EQU $01
_SRAM_CHAIN_PHRASES_BANK          EQU $01
_SRAM_CHAIN_TRANSPOSES_BANK       EQU $01
_SRAM_INSTRUMENT_PARAMS_BANK      EQU $01
_SRAM_TABLE_TRANSPOSE_BANK        EQU $01
_SRAM_TABLE_COMMANDS_1_BANK       EQU $01
_SRAM_TABLE_COMMAND_VALUES_1_BANK EQU $01
_SRAM_TABLE_COMMANDS_2_BANK       EQU $01
_SRAM_TABLE_COMMAND_VALUES_2_BANK EQU $01
_SRAM_INIT_FLAG_2_BANK            EQU $01
_SRAM_PHRASE_ALLOC_BANK           EQU $01
_SRAM_CHAIN_ALLOC_BANK            EQU $01
_SRAM_SYNTH_PARAMS_BANK           EQU $01
_SRAM_WORK_TIME_HOURS_BANK        EQU $01
_SRAM_WORK_TIME_MINUTES_BANK      EQU $01
_SRAM_TEMPO_BANK                  EQU $01
_SRAM_TRANSPOSE_BANK              EQU $01
_SRAM_TOTAL_TIME_DAYS_BANK        EQU $01
_SRAM_TOTAL_TIME_HOURS_BANK       EQU $01
_SRAM_TOTAL_TIME_MINUTES_BANK     EQU $01
_SRAM_TOTAL_TIME_CHECKSUM_BANK    EQU $01
_SRAM_KEY_DELAY_BANK              EQU $01
_SRAM_KEY_REPEAT_BANK             EQU $01
_SRAM_FONT_BANK                   EQU $01
_SRAM_SYNC_BANK                   EQU $01
_SRAM_PALETTE_NUM_BANK            EQU $01
_SRAM_PS2_DELAY_BANK              EQU $01
_SRAM_TICKS_PER_STEP_BANK         EQU $01
_SRAM_CLONE_TYPE_BANK             EQU $01
_SRAM_FILE_CHANGED_BANK           EQU $01
_SRAM_PRELISTEN_BANK              EQU $01
_SRAM_SYNTH_LOCK_BANK             EQU $01
_SRAM_LAST_USED_INSTRUMENT_BANK   EQU $01
_SRAM_LAST_SAVED_HOURS_BANK       EQU $01
_SRAM_LAST_SAVED_MINUTES_BANK     EQU $01
_SRAM_OVERCLOCK_BANK              EQU $01

_SRAM_PHRASE_COMMANDS_BANK       EQU $02
_SRAM_PHRASE_COMMAND_VALUES_BANK EQU $02

_SRAM_WAVE_FRAMES_BANK        EQU $03
_SRAM_PHRASE_INSTRUMENTS_BANK EQU $03
_SRAM_INIT_FLAG_3_BANK        EQU $03
_SRAM_VERSION_FLAG_BANK       EQU $03

_SRAM_FILE_NAMES_BANK     EQU $04
_SRAM_FILE_VERSIONS_BANK  EQU $04
_SRAM_FILE_INIT_FLAG_BANK EQU $04
_SRAM_CURRENT_FILE_BANK   EQU $04

_SRAM_BLOCKS_BANK_START EQU $04
_SRAM_BLOCKS_MAX_BANK   EQU $0f

;; SRAM Addresses ;;

_SRAM_PHRASE_NOTES      EQU $a000 ; 00:a000 - 00:afef (0xff phrases x 16 notes)
_SRAM_BOOKMARKS         EQU $aff0 ; 00:aff0 - 00:afff (16 bookmarks)
                                  ; 00:b000 - 00:b08f (empty)
_SRAM_GROOVES           EQU $b090 ; 00:b090 - 00:b28f (0x20 grooves x 16 rows)
_SRAM_SONG_CHAINS       EQU $b290 ; 00:b290 - 00:b58f (0xc0 rows x 4 channels) (pulse1, pulse2, wave, noise repeating)
                                  ; 00:b590 - 00:b68f (empty)
_SRAM_TABLE_VOLS        EQU $b690 ; 00:b690 - 00:b88f (0x20 tables x 16 rows)
_SRAM_SPEECH_WORDS      EQU $b890 ; 00:b890 - 00:ba4f (0x0e words x 0x10 rows x 2 cols) (vowel, length repeating)
                                  ; 00:ba50 - 00:bdd0 (empty)
_SRAM_SPEECH_WORD_NAMES EQU $bdd0 ; 00:bdd0 - 00:bdf9 (0xe words x 3 chars)
                                  ; 00:bdfa - 00:be77 (empty)
_SRAM_INIT_FLAG_1       EQU $be78 ; 00:be78 - 00:be79 (2 special bytes)
_SRAM_INSTRUMENT_NAMES  EQU $be7a ; 00:be7a - 00:bfb9 (0x40 instruments x 5 chars)
                                  ; 00:bfba - 00:bfff (empty)

                                       ; 01:a000 - 01:a03f (empty)
_SRAM_INSTRUMENT_ALLOC       EQU $a040 ; 01:a040 - 01:a07f (0x40 instruments x 1 bit)
_SRAM_CHAIN_PHRASES          EQU $a080 ; 01:a080 - 01:a87f (0x80 chains x 0x10 phrases)
_SRAM_CHAIN_TRANSPOSES       EQU $a880 ; 01:a880 - 01:b07f (0x80 chains x 0x10 rows)
_SRAM_INSTRUMENT_PARAMS      EQU $b080 ; 01:b080 - 01:b47f (0x40 instruments x 0x10 size) (see above)
_SRAM_TABLE_TRANSPOSE        EQU $b480 ; 01:b480 - 01:b67f (0x20 tables x 0x10 rows)
_SRAM_TABLE_COMMANDS_1       EQU $b680 ; 01:b680 - 01:b87f (0x20 tables x 0x10 rows)
_SRAM_TABLE_COMMAND_VALUES_1 EQU $b880 ; 01:b880 - 01:ba7f (0x20 tables x 0x10 rows)
_SRAM_TABLE_COMMANDS_2       EQU $ba80 ; 01:ba80 - 01:bc7f (0x20 tables x 0x10 rows)
_SRAM_TABLE_COMMAND_VALUES_2 EQU $bc80 ; 01:bc80 - 01:be7f (0x20 tables x 0x10 rows)
_SRAM_INIT_FLAG_2            EQU $be80 ; 01:be80 - 01:be81 (2 special bytes)
_SRAM_PHRASE_ALLOC           EQU $be82 ; 01:be82 - 01:bea1 (0xff phrases x 1 bit)
_SRAM_CHAIN_ALLOC            EQU $bea2 ; 01:bea2 - 01:beb1 (0x80 chains x 1 bit)
_SRAM_SYNTH_PARAMS           EQU $beb2 ; 01:beb2 - 01:bfb1 (0x10 synths x 0x10 size)
_SRAM_WORK_TIME_HOURS        EQU $bfb2 ; 01:bfb2 - 01:bfb2
_SRAM_WORK_TIME_MINUTES      EQU $bfb3 ; 01:bfb3 - 01:bfb3
_SRAM_TEMPO                  EQU $bfb4 ; 01:bfb4 - 01:bfb4 (40-255: value, 256-295: value - 256)
_SRAM_TRANSPOSE              EQU $bfb5 ; 01:bfb5 - 01:bfb5
_SRAM_TOTAL_TIME_DAYS        EQU $bfb6 ; 01:bfb6 - 01:bfb6
_SRAM_TOTAL_TIME_HOURS       EQU $bfb7 ; 01:bfb7 - 01:bfb7
_SRAM_TOTAL_TIME_MINUTES     EQU $bfb8 ; 01:bfb8 - 01:bfb8
_SRAM_TOTAL_TIME_CHECKSUM    EQU $bfb9 ; 01:bfb9 - 01:bfb9
_SRAM_KEY_DELAY              EQU $bfba ; 01:bfba - 01:bfba
_SRAM_KEY_REPEAT             EQU $bfbb ; 01:bfbb - 01:bfbb
_SRAM_FONT                   EQU $bfbc ; 01:bfbc - 01:bfbc
_SRAM_SYNC                   EQU $bfbd ; 01:bfbd - 01:bfbd
_SRAM_PALETTE_NUM            EQU $bfbe ; 01:bfbe - 01:bfbe
_SRAM_PS2_DELAY              EQU $bfbf ; 01:bfbf - 01:bfbf
_SRAM_TICKS_PER_STEP         EQU $bfbf ; 01:bfbf - 01:bfbf
_SRAM_CLONE_TYPE             EQU $bfc0 ; 01:bfc0 - 01:bfc0
_SRAM_FILE_CHANGED           EQU $bfc1 ; 01:bfc1 - 01:bfc1 (first 4 bits) (unchanged: 0, changed: 1)
                                       ; 01:bfc2 - 01:bfc2 (empty)
_SRAM_PRELISTEN              EQU $bfc3 ; 01:bfc3 - 01:bfc3
_SRAM_SYNTH_LOCK             EQU $bfc4 ; 01:bfc4 - 01:bfc5 (0x10 synths x 1 bit)
_SRAM_LAST_USED_INSTRUMENT   EQU $bfc6 ; 01:bfc6 - 01:bfc9 (4 channels)
_SRAM_LAST_SAVED_HOURS       EQU $bfca ; 01:bfca - 01:bfca
_SRAM_LAST_SAVED_MINUTES     EQU $bfcb ; 01:bfcb - 01:bfcb
_SRAM_OVERCLOCK              EQU $bfcc ; 01:bfcc - 01:bfcc
                                       ; 01:bfcd - 01:bfff (empty)

_SRAM_PHRASE_COMMANDS       EQU $a000 ; 02:a000 - 02:afef (0xff phrases x 0x10 rows)
_SRAM_PHRASE_COMMAND_VALUES EQU $aff0 ; 02:aff0 - 02:bfdf (0xff phrases x 0x10 rows)
                                      ; 02:bfe0 - 02:bfff (empty)

_SRAM_WAVE_FRAMES        EQU $a000 ; 03:a000 - 03:afff (0x10 synths x 0x10 frames x 0x10 samples) (1 sample = 1 char)
_SRAM_PHRASE_INSTRUMENTS EQU $b000 ; 03:b000 - 03:bfef (0xff phrases x 0x10 rows)
_SRAM_INIT_FLAG_3        EQU $bff0 ; 03:bff0 - 03:bff1 (2 special bytes)
                                   ; 03:bff2 - 03:bffe (empty)
_SRAM_VERSION_FLAG       EQU $bfff ; 03:bfff - 03:bfff

_SRAM_FILE_NAMES       EQU $a000 ; 04:a000 - 04:a0ff (0x20 songs x 8 chars)
_SRAM_FILE_VERSIONS    EQU $a100 ; 04:a100 - 04:a11f (0x20 songs x 1 byte)
                                 ; 04:a120 - 04:a13d (empty)
_SRAM_FILE_INIT_FLAG   EQU $a13e ; 04:a13e - 04:a13f (2 special bytes)
_SRAM_CURRENT_FILE     EQU $a140 ; 04:a140 - 04:a140
_SRAM_BLOCK_ALLOCATION EQU $a141 ; 04:a141 - 04:a1ff (0xbf blocks)
_SRAM_BLOCKS           EQU $a200 ; 04:a200 - 0f:bfff
