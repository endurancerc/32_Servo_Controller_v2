// ─────────────────────────────────────────────────────────────
//  ST7789 172x320 TFT — SPLIT SCREEN: OV5640 VIEWFINDER + BNO085 ATTITUDE
//                       + MLX90640 THERMAL + microSD read/write + self-test
//
//  Two panels are supported off the SAME five pins — pick with PANEL_ST7796:
//    0 = ST7789  1.47" 172x320 -> landscape 320x172, 160px camera pane
//    1 = ST7796S 4.0"  320x480 -> landscape 480x320, 320px camera pane
//
//  The panel runs in LANDSCAPE and is split into a camera pane and a fixed
//  160-wide instrument pane:
//    LEFT  — live camera. RGB565 frames stream row-for-row into the pane
//            with no scaling or rotation, letterboxed. The sensor is asked
//            for exactly the pane size (QQVGA on the ST7789, QVGA on the
//            ST7796), so a camera row is one contiguous SPI run.
//            CAM_PANE_LEFT swaps the sides.
//    RIGHT — switchable, "pane imu|thermal|both" on the console:
//            BOTH    — the default on the 4in panel: MLX90640 image at 4x
//                      with max/centre/min beside it, then the yaw/pitch/
//                      roll readout, the attitude cube and a compass.
//                      Everything at once; the thermal drops to 4x to fit.
//            IMU     — BNO085 attitude: a wireframe cube rotated by
//                      yaw/pitch/roll, plus a full-size compass rose.
//            THERMAL — MLX90640 false-colour image full pane, 32x24
//                      upscaled 5x to 160x120, with Ta / min / max / centre.
//            Both render into one GFXcanvas16 and are blitted in a single
//            push; see drawInstruments() for why.
//
//  The two panes are independent — the camera runs as fast as it can, the
//  instruments refresh at INST_REDRAW_MS, and neither waits for the other.
//
//  ── REQUIRES PSRAM ──
//    Tools -> PSRAM -> "OPI PSRAM". Camera frame buffers live there.
//    Without PSRAM the screen goes solid RED and the reason is printed
//    to serial.
//
//  ── BNO085 wiring (UART-RVC, receive-only) ──
//    Sensor TX -> GPIO14, 115200 8N1. Nothing is sent to the sensor.
//    TWO THINGS CATCH PEOPLE OUT ON THE ADAFRUIT BNO085 BREAKOUT:
//
//    1. The data line is the pad silkscreened **SDA**, not one marked TX.
//       In RVC mode the sensor streams out of SDA. Adafruit's own UART-RVC
//       wiring is: 3V->Vin, GND->GND, SDA->board RX, and 3V->P0.
//    2. **P0 goes to 3.3V** — not P1. The raw Hillcrest datasheet describes
//       RVC as PS1=1/PS0=0, but this breakout's pads do not map to that
//       naming, and Adafruit's guide for THIS board says tie P0 high. Both
//       pads are pulled low on board, so I2C is the default and an
//       unstrapped sensor sits silent on SDA.
//
//    Mode is latched at RESET, so power-cycle after changing the strap.
//    Note SDA carries an I2C pull-up, so the line reads HIGH whether or not
//    the sensor is in RVC — "it's high, so it must be working" is wrong.
//    The panel auto-probes GPIO14 and reports the verdict on screen; "bno"
//    on the console re-runs it, "fps" shows the raw byte counter. rx=0
//    means nothing is arriving at all — wiring or strapping, not parsing.
//
//  ── MLX90640 wiring (I2C, 4 wires) ──
//    VIN->3V3   GND->GND   SDA->GPIO1   SCL->GPIO2
//    The breakout carries its own pull-ups; do not add more. Address is
//    fixed at 0x33 and cannot be changed, so one sensor per bus — it does
//    not clash with a PCA9685 (0x40) or an SSD1306 (0x3C) hung on the same
//    two wires.
//
//    ****GPIO1 AND GPIO2 ARE THE COLLISION****
//    LCD_PINSET 1 and 2 use GPIO1 as display MOSI and GPIO2 as display RES.
//    The MLX90640 therefore CANNOT run until the panel is rewired to the
//    target pins (SCK 47, MOSI 21, RES 48) and LCD_PINSET is set to 0.
//    Setting MLX_ENABLE 1 with any other pinset is a compile error rather
//    than a mystery — see the guard next to MLX_ENABLE below.
//
//  ── Camera wiring (OV5640, pins unchanged from the OV5640 sketch) ──
//    XCLK->15  SIOD->4  SIOC->5  VSYNC->6  HREF->7  PCLK->13
//    Y2->11  Y3->9  Y4->8  Y5->10  Y6->12  Y7->18  Y8->17  Y9->16
//    PWDN and RESET are not wired (-1) — the sensor is always powered.
//
//  ── Display wiring (ESP32-S3) — IDENTICAL FOR BOTH PANELS ──
//    SCL/SCK->GPIO47  SDA/MOSI->GPIO21  RES->GPIO48  DC->GPIO42  CS->GPIO41
//    BLK/LED->GPIO46 (PWM)   GND->GND
//
//    ST7789 1.47": VCC->3V3.
//    ST7796 4.0" lcdwiki module: VCC->5V. The board has onboard level
//      conversion, so 3.3V logic into a 5V-powered module is what it is
//      built for. Run VCC from 5V, NOT from the 3V3 rail — the backlight
//      alone is ~103 mA and this board's 3V3 already sags far enough under
//      camera inrush that the brownout detector has to be disabled (see
//      setup()). Its SDO(MISO) and SD_CS stay unconnected: nothing reads
//      the panel and the card is on native SDMMC, not this SPI bus.
//      CTP_SDA->GPIO1 and CTP_SCL->GPIO2 join the existing I2C bus when
//      touch gets wired up (FT6336U at 0x38, no clash with the MLX at 0x33).
//
//  ── Reserved pins on this board — do not reuse ──
//    GPIO18  camera SCK        GPIO1  I2C SDA        GPIO2  I2C SCL
//    GPIO14  BNO085 UART RX    GPIO19/20  USB        GPIO43/44  USB-serial
//    GPIO35/36/37  OCTAL PSRAM (N16R8) — internal to the module, they
//      look unconnected on the schematic but are NOT usable as GPIO.
//    GPIO0/3/45/46  strapping pins — usable, but avoid for clocks.
//    Remaining free: GPIO3, 46 (strapping) — everything else is spoken for.
//
//    ****NOTE****
//    MICRO SD CARDS MUST BE FORMATTED AS FAT32. MY CARD WAS exFAT by default.
//    USE A PROGRAM CALLED RUFUS TO FORMAT IN FAT32
//
//  ── microSD wiring (native SDMMC, 1-bit — matches the schematic) ──
//    SD_CLK->GPIO39   SD_CMD->GPIO38   SD_DATA(DAT0)->GPIO40
//    VCC->3V3         GND->GND
//    This is the SD peripheral, NOT SPI — the card socket's CMD/CLK/
//    DAT0 pins go straight to the SDMMC host via the S3's GPIO matrix.
//    PULL-UPS: CMD, DAT0 and DAT3 each want 10k to 3V3. DAT3 matters
//    even though it isn't wired to the MCU — left floating the card can
//    fall into SPI mode and never answer. If mount fails, suspect these.
//    Card must be FAT32 (or FAT16). exFAT is NOT supported, so
//    reformat any 64 GB+ card as FAT32 or it will refuse to mount.
//
//  ── How to test the card ──
//    1. A self-test runs at boot: mount, text write/read, append,
//       mkdir/rename/remove, then a 64 KB binary write+verify with
//       throughput. Results go to USB serial @115200 (on-screen status
//       text is commented out so the panel stays pure video).
//    2. Type commands on the serial console while the preview runs:
//         help  info  test  bench  ls [dir]  cat <f>
//         write <f> <text>   append <f> <text>   rm <f>
//         mkdir <d>  rmdir <d>  mount  unmount  fps  log on|off
//         pane imu|thermal   mlx        (right-hand pane / sensor status)
//
//  ── BNO085 CSV logging ──
//    With a card present, yaw/pitch/roll/accel are appended to
//    /imulog.csv at IMU_LOG_HZ from boot. Rows are only written while the
//    sensor is actually reporting, so a missing BNO085 leaves an empty
//    file rather than hours of zeroes. "log off" flushes and stops;
//    "unmount" does too, so pull the card that way rather than yanking it.
//
//  ── If the picture looks wrong ──
//    colours inverted / blue<->orange ... flip CAM_SWAP_BYTES
//    image mirrored or upside down .... try the other PANEL_MADCTL value,
//                                       or CAM_VFLIP / CAM_HMIRROR
//    photographic negative ............ flip PANEL_INVERT
//    washed out / ghosted on ST7796 ... the command-set-2 unlock in begin()
//                                       did not take; check MOSI and SCK
//    thermal disagrees with the video . THERM_VFLIP / THERM_HMIRROR — they
//                                       only rotate the thermal pane, so
//                                       match it to the camera, not vice versa
//
//  ── READING THE BOOT PATTERN (blank-screen triage) ──
//    Set BOOT_TEST_PATTERN 1 and the panel shows red/green/blue/white
//    vertical bars inside a white border for 2 s before the camera
//    starts. It is OFF by default so the feed comes up immediately, but
//    turn it back on the moment anything looks wrong — it separates a
//    display fault from a camera fault in one boot:
//
//    bars, then live video ....... everything works
//    bars, then black ............ camera is initialising but frames are
//                                  not arriving — check serial for drops
//    bars fine, video flashes .... the display path is PROVEN by the bars,
//                                  so suspect the sensor module itself —
//                                  a faulty OV5640 did exactly this once
//    bars, then solid RED ........ camera init failed; serial says why
//                                  (usually PSRAM off, or error 0x105)
//    NOTHING AT ALL .............. the display is not being driven at all.
//                                  Check LCD_PINSET matches how the board
//                                  is ACTUALLY wired right now, then the
//                                  backlight (BLK->3V3) and RES.
//    bars are horizontal ......... PANEL_MADCTL orientation is wrong
//    board reboots every ~1 s .... brownout; see setup() and check the
//                                  camera's 3V3 rail under load
//
//    Serial @115200 prints the reset reason on every boot. Reason 6/7
//    (task WDT) or 5 (brownout) means it is resetting, not hanging.
// ─────────────────────────────────────────────────────────────

#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <FS.h>
#include <SD_MMC.h>
#include <WiFi.h>          // listen-only AP scanner view
#include <HTTPClient.h>    // radar + map fetches (up here: Arduino's generated
#include <WiFiClientSecure.h> //   prototypes for the map's fetch code need these types)
#include <PNGdec.h>          // map tiles (MapTiler's JPEGs are progressive; JPEGDEC can't)
#undef local                 // PNGdec's zlib defines local as static; NimBLE has a field named local
//  One satellite heard by the GNSS (GSV), declared up here so the generated
//  prototypes of the GPS sky functions can see it.
struct GpsSat { char sys; uint8_t id, sig, cno; int8_t elev; uint16_t az; uint32_t ms; };
#include <Preferences.h>   // NVS-backed settings persistence
static Preferences prefs;

//  BLE tracker/surveillance scanner (NimBLE). Library Manager: "NimBLE-Arduino".
#define BLE_ENABLE 1
#if BLE_ENABLE
  #include <NimBLEDevice.h>
#endif

//  GNSS receiver (u-blox MAX-M10M-20B on the shared I2C bus at 0x42). Set
//  here, with the other feature switches, because the console near the top
//  of the file also tests it.
#define GPS_ENABLE 1

//  Sensirion SCD40 CO2 / temperature / humidity sensor on the shared I2C bus
//  (0x62): GAS SENSORS page.
#define GAS_ENABLE 1

//  Sensirion SEN69C-SIN-T air-quality module (PM, temperature, humidity, VOC,
//  NOx, formaldehyde, CO2) on the shared I2C bus (0x6B): AIR QUALITY page.
#define AIR_ENABLE 1

//  Music player + sound recorder: the v6 board's two MAX98357A amps + DMM-4026
//  I2S mic on GPIO 44 (BCLK) / 3 (LRC) / 45 (amp DIN) / 43 (mic SD)
//  (ESP8266Audio 1.9.7 decodes MP3 / WAV).
#define AUDIO_ENABLE 1
//  0: screens and logic only - GPIO 3/43/44/45 are never touched (no I2S
//  driver, no pin drive). Playback runs in real time but silently; the mic
//  reads as not connected. 1 on boards with the amps + mic fitted (v6).
#define AUDIO_PINS 1
#if AUDIO_ENABLE
  #include <driver/i2s.h>
  #include "AudioFileSourceFS.h"
  #include "AudioFileSourceBuffer.h"
  #include "AudioGeneratorMP3.h"
  #include "AudioGeneratorWAV.h"
  #include "AudioOutput.h"
#endif
#include "esp_camera.h"
#include "img_converters.h"   // frame2jpg / fmt2jpg for SD snapshots
#include "esp_system.h"        // esp_reset_reason()
#include "esp_task_wdt.h"      // esp_task_wdt_delete()
#include "soc/soc.h"           // WRITE_PERI_REG
#include "soc/rtc_cntl_reg.h"  // RTC_CNTL_BROWN_OUT_REG
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
//  pocket-tank (FISH TANK view): plain C sources under src/pockettank.
extern "C" {
#include "src/pockettank/tank.h"
#include "src/pockettank/render.h"
#include "src/pockettank/progression.h"
#include "src/pockettank/advisor.h"
}
//  DOOM is a separate firmware in app1; this one only launches it.
#include "esp_ota_ops.h"
#include "esp_partition.h"

// ── Bring-up switches ──
//  Set CAM_ENABLE 0 to run the panel with no camera at all: if the test
//  pattern appears with it off but not with it on, the fault is the
//  camera (power, pins, init), not the display.
#define CAM_ENABLE        1
//  Colour bars + white border at boot, held BOOT_PATTERN_MS. Off by
//  default so the camera comes up as fast as possible — set to 1 to get
//  the display's proof of life back (see the triage notes at the top).
#define BOOT_TEST_PATTERN 0
#define BOOT_PATTERN_MS   2000

//  The full SD suite writes and verifies 64 KB, which costs a noticeable
//  chunk of a second before the first frame. At 0 the card is still
//  mounted at boot — so the console commands work immediately — but the
//  suite only runs when you type "test". Set to 1 to run it at boot.
#define SD_SELFTEST_AT_BOOT 0

//  ── WHICH PANEL IS ON THE BENCH? ──
//    0 = ST7789  1.47" 172x320  (the original panel)
//    1 = ST7796S 4.0"  320x480  (lcdwiki capacitive SPI module)
//  Both hang off the SAME five pins — SCK 47, MOSI 21, RES 48, DC 42, CS 41 —
//  so switching panels is this one define plus moving the jumpers. Everything
//  downstream (frame size, pane widths, CGRAM offset, init sequence,
//  inversion) keys off it.
#define PANEL_ST7796 0

//  MLX90640 thermal camera on the I2C bus. OFF by default because the bus
//  pins (GPIO1/2) are still the display's MOSI/RES under LCD_PINSET 1 and 2
//  — see the guard below. Once the panel is on 47/21/48, set LCD_PINSET 0
//  and MLX_ENABLE 1 and the right-hand pane comes up thermal.
#define MLX_ENABLE 1

//  Included here rather than with the others at the top because it has to
//  follow MLX_ENABLE — with the sensor switched off the sketch still builds
//  on a machine that has never installed the library.
//  Library Manager: "Adafruit MLX90640" (pulls in Adafruit BusIO).
#if MLX_ENABLE
  //  The per-subpage calls (GetFrameData / GetTa / CalculateTo) are private
  //  in this library, but mlxReadFrame() needs them so it can let go of the
  //  shared I2C bus between subpages — getFrame() holds it ~250 ms and starves
  //  the button pad. Opening the class up here is a compile-time-only change
  //  (access does not affect linking). Its own includes go first so the
  //  redefinition touches nothing but this one header.
  #include <Adafruit_I2CDevice.h>
  #define private public
  #include <Adafruit_MLX90640.h>
  #undef private
#endif

//  Motion-JPEG playback off the SD card. Library Manager: "JPEGDEC".
#define VIDEO_ENABLE 1
#if VIDEO_ENABLE
  #include <JPEGDEC.h>
  #define VIDEO_DEFAULT_FILE "/intro.rdm"
  //  Play the intro once at power-up, then hand the panel over to the
  //  camera and instrument panes. Deliberately ONE pass, not a loop —
  //  an intro that never ends is just a screensaver, and nothing else
  //  can draw while it runs. "play" on the console replays it, and
  //  "vloop on" first if you do want it to repeat.
  #define VIDEO_AT_BOOT 1
#endif

// ── Display pins ──
//  SCK/MOSI/RES moved off 18/1/2 — those are now camera SCK, I2C SDA
//  and I2C SCL respectively. Routed through the GPIO matrix (none of
//  these are FSPI IOMUX pins), which caps SPI at 40 MHz — already the
//  clock this sketch uses, so no speed is lost.
#define PIN_SCK  47
#define PIN_MOSI 21
//  Set PIN_RES to -1 to skip the hardware reset and rely on the panel's
//  power-on reset plus the SWRESET command. Worth trying if the screen
//  is blank: an unconnected RES that floats LOW holds the ST7789 in
//  reset forever, and no amount of correct pixel data will show up.
#define PIN_RES  48                     // least timing-critical of the three
#define PIN_DC   42
#define PIN_CS   41

// ── Backlight (BLK) on a GPIO instead of hard-wired to 3V3 ──
//  Set PIN_BL to -1 if BLK is still tied to 3V3 — everything still works, the
//  panel is just always on and the brightness controls become no-ops.
//
//  GPIO46 is the right choice of the two pins left: it is a strapping pin with
//  an internal PULL-DOWN at reset, so the panel comes up dark and stays dark
//  until firmware lights it. That removes the flash of random panel RAM at
//  power-on for free. It also leaves GPIO3 free, which is the only ADC1 pin
//  you have and therefore the one a 5-button resistor ladder needs.
#define PIN_BL   46

//  LEDC channel 4 maps to timer 2 (Arduino derives timer = (chan/2) % 4).
//  Channels 0 and 1 would land on timer 0, which the camera driver already
//  owns for XCLK — sharing it would fight over the frequency.
#define BL_PWM_CH   4
#define BL_PWM_HZ   20000               // above audible; some panels whine at 1-5 kHz
#define BL_BITS     8                   // 0..255
#define BL_DEFAULT  200                 // ~78% — dim costs almost nothing to try

// ── Idle dimming ──
//  Drop the backlight when the board has been sitting still and untouched.
//  "Untouched" means all three of: no button, no console command, and no
//  movement from the IMU — a bench instrument that dims while you are
//  reading it is worse than one that never dims, so the motion test has to
//  be a primary signal rather than an afterthought.
#define BL_IDLE_MS      10000           // 0 disables; "idle <sec>" changes it live
#define BL_IDLE_LEVEL   16              // dim, deliberately not off
#define BL_IDLE_FADE_MS 700             // fade down; waking is instant
//  Attitude change that counts as movement. Below about 2 degrees the
//  BNO085's own noise starts tripping it while the board sits still.
#define IDLE_MOVE_DEG   3.0f
//  Acceleration departure from 1 g, so a knock that does not rotate the
//  board still counts as being handled.
#define IDLE_BUMP_MS2   1.5f

//  ── WHICH PHYSICAL WIRING IS ON THE BENCH? ──
//    0 = TARGET   SCK 47  MOSI 21  RES 48   final board, all 3 moved
//    1 = LEGACY   SCK 18  MOSI  1  RES  2   original wiring, DISPLAY ONLY
//                 (GPIO18 is camera Y7 — requires CAM_ENABLE 0)
//    2 = ONE-WIRE SCK 47  MOSI  1  RES  2   move only the clock
//
//  Mode 2 is the useful one mid-transition: GPIO18 is the *only* hard
//  conflict between the panel and the camera, so moving just SCK to 47
//  lets both run today. It assumes nothing is wired to GPIO1/2 yet —
//  the moment the I2C bus lands there, go to mode 0.
#define LCD_PINSET 0

#if LCD_PINSET == 1
  #if CAM_ENABLE
    #error "LCD_PINSET 1 needs CAM_ENABLE 0 — GPIO18 is the camera's Y7"
  #endif
  #undef  PIN_SCK
  #undef  PIN_MOSI
  #undef  PIN_RES
  #define PIN_SCK  18
  #define PIN_MOSI 1
  #define PIN_RES  2
#elif LCD_PINSET == 2
  #undef  PIN_MOSI
  #undef  PIN_RES
  #define PIN_MOSI 1
  #define PIN_RES  2
#endif

//  The I2C bus lands on GPIO1/2, which pinsets 1 and 2 are still using for
//  the panel. Catch it here rather than at 2 a.m. on the bench: two drivers
//  fighting over MOSI looks like a corrupt display AND a dead sensor, and
//  neither symptom points at the pins.
//  The ST7796 is wired to the target display pins. Building it against a
//  transitional pinset would drive MOSI/RES onto GPIO1/2, which are the I2C
//  bus — the panel would stay dark AND the sensors would drop off at once.
#if PANEL_ST7796 && (LCD_PINSET != 0)
  #error "PANEL_ST7796 needs LCD_PINSET 0 - the 4.0in module is wired to SCK 47 / MOSI 21 / RES 48"
#endif

#if MLX_ENABLE && (LCD_PINSET != 0)
  #error "MLX_ENABLE 1 needs LCD_PINSET 0 - GPIO1/2 are the I2C bus, but pinsets 1 and 2 drive them as display MOSI/RES"
#endif

// ── microSD pins (native SDMMC host, 1-bit mode) ──
#define SD_CLK  39                      // schematic: SD_CLK
#define SD_CMD  38                      // schematic: SD_CMD   (host -> card)
#define SD_D0   40                      // schematic: SD_DATA  (card -> host)

// ── BNO085 CSV logging ──
//  20 Hz rather than the sensor's full 100 Hz: attitude at 20 Hz is plenty
//  to reconstruct motion, and it is a fifth of the card writes and power.
//  Raise IMU_LOG_HZ to 100 to capture every RVC frame (~4 KB/s, 14 MB/hour).
#define IMU_LOGGING   1                 // start logging automatically if a card is in
#define IMU_LOG_FILE  "/imulog.csv"
#define IMU_LOG_HZ    20
#define IMU_LOG_MS    (1000 / IMU_LOG_HZ)
//  The file handle is held open and flushed periodically instead of being
//  reopened per row — an open/close per row costs milliseconds on SDMMC. The
//  trade is that a power cut loses up to this much data.
#define IMU_FLUSH_MS  2000

#define SD_TEST_FILE  "/sdtest.txt"
#define SD_BENCH_FILE "/sdbench.bin"
#define SD_TEST_DIR   "/sdtestd"
#define SD_BENCH_KB   64                // binary read/write test size

// ── Camera pins (OV5640) — identical to 32_Servo_Controller_OV5640 ──
#define PWDN_GPIO_NUM   -1              // not wired: sensor is always powered
#define RESET_GPIO_NUM  -1
#define XCLK_GPIO_NUM   15
#define SIOD_GPIO_NUM    4              // camera SCCB SDA (its own bus)
#define SIOC_GPIO_NUM    5              // camera SCCB SCL
#define Y2_GPIO_NUM     11
#define Y3_GPIO_NUM      9
#define Y4_GPIO_NUM      8
#define Y5_GPIO_NUM     10
#define Y6_GPIO_NUM     12
#define Y7_GPIO_NUM     18
#define Y8_GPIO_NUM     17
#define Y9_GPIO_NUM     16
#define VSYNC_GPIO_NUM   6
#define HREF_GPIO_NUM    7
#define PCLK_GPIO_NUM   13

#define CAM_XCLK_HZ  24000000           // OV5640 optimal (OV2640 wants 20 MHz)
//  Ask the sensor for exactly the pane it is going into, so a camera row is
//  one contiguous run of bytes and there is no scaling, cropping or rotation
//  anywhere in the hot path. Cropping a wider frame would throw away field of
//  view; downscaling in software would cost per-pixel CPU we do not have.
//    ST7789 172x320 -> 160-wide pane -> QQVGA
//    ST7796 320x480 -> 320-wide pane -> QVGA
//  Views are full screen now, so the camera is asked for QVGA on both
//  panels and showFrame() centre-crops whatever does not fit. On the
//  320x172 panel that is a full-width feed with 34 rows trimmed top and
//  bottom, rather than a 160-wide window in the corner.
#define CAM_W          320
#define CAM_H          240
#define CAM_FRAMESIZE  FRAMESIZE_QVGA

// esp32-camera emits RGB565 big-endian, which is already the order the
// ST7789 wants — so raw writeBytes() is correct. Set this to 1 to route
// through writePixels() instead, which byte-swaps each 16-bit pixel in
// the SPI registers for free. Symptom of getting it wrong: blue and
// orange trade places while greys stay grey.
#define CAM_SWAP_BYTES 0

//  Both set = 180 degrees, which compensates for the panel being rotated
//  180 in PANEL_MADCTL. Done in the OV5640 itself rather than in the blit:
//  the sensor reads its array out flipped, so it costs no CPU and the frame
//  still arrives as contiguous rows.
//  If PANEL_MADCTL ever goes back to 0xA0's counterpart, clear these too.
#define CAM_VFLIP    1                  // sensor-side flips
#define CAM_HMIRROR  1

// ── Panel geometry — LANDSCAPE for the camera ──
//  Both panels are portrait natively and are turned on their side with
//  MADCTL's MV bit, so a camera row becomes a panel row: one address window
//  per frame, then a straight sequential push.
//
//  ST7789 1.47": 172x320 portrait with a 34-COLUMN offset. Rotating moves
//  that offset onto the ROW address, hence ROW_OFFSET 34.
//  ST7796 4.0" : 320x480 portrait, full panel, so no CGRAM offset at all.
#if PANEL_ST7796
  #define TFT_W        480
  #define TFT_H        320
  #define COL_OFFSET   0
  #define ROW_OFFSET   0
  //  MV (0x20) is what makes it landscape; MX (0x40) and MY (0x80) then
  //  mirror the two screen axes, and 0x08 is BGR colour order. With MV set
  //  the axes are swapped, so MX mirrors the screen VERTICALLY and MY
  //  mirrors it HORIZONTALLY — which is why "text reads backwards" is fixed
  //  by toggling one of them, not by rotating.
  //
  //  All four landscape orientations — try them live with "madctl <hex>"
  //  on the console rather than reflashing for each guess:
  //      0x28  MV            0x68  MX|MV
  //      0xA8  MY|MV         0xE8  MX|MY|MV
  //  Clear the 0x08 bit in any of them if red and blue trade places while
  //  greys stay grey (BGR -> RGB).
  #define PANEL_MADCTL 0xE8
  //  ST7796 panels are normally NOT inverted, unlike the ST7789 IPS. If the
  //  picture comes up as a photographic negative, set this to 1.
  #define PANEL_INVERT 0
#else
  #define TFT_W        320
  #define TFT_H        172
  #define COL_OFFSET   0
  #define ROW_OFFSET   34
  //  Rotated 180 degrees from the original 0x60 (MX|MV): with MV set, MX
  //  and MY are the two screen-axis mirrors, so flipping BOTH is a
  //  rotation rather than a mirror. 0x60 is the other way up.
  #define PANEL_MADCTL 0xA0
  //  This IPS panel REQUIRES inversion on — without it the screen is blank
  //  or washed white even though every pixel is being written correctly.
  #define PANEL_INVERT 1
#endif

// ── MLX90640 thermal camera (I2C, address 0x33) ──
//  32x24 is exactly 1/5 of the 160x120 camera pane, so the upscale is a
//  clean integer 5x block fill — no interpolation, no fractional stepping,
//  and the thermal image occupies the identical letterboxed band as the
//  video on the other side of the panel.
#define MLX_SDA        1
#define MLX_SCL        2
//  400 kHz is the practical floor: a subpage is 1664 bytes, so at 100 kHz a
//  single read alone costs ~150 ms and the sensor can never be kept up with.
//  1 MHz works on the S3 but wants short leads and stiffer pull-ups.
#define MLX_I2C_HZ     400000UL
#define MLX_ADDR       0x33
//  8 Hz refresh = 4 full images/s, because chess mode fills half the pixels
//  per subpage and getFrame() waits for both. Do NOT drop this to 1 or
//  0.5 Hz: the Melexis driver busy-polls the status register with no yield,
//  so a slow refresh turns getFrame() into seconds of unyielding I2C.
#define MLX_REFRESH    MLX90640_8_HZ
#define MLX_STALE_MS   2000                     // no frame for this long = dead

//  getFrame() blocks for two refresh periods (~250 ms at 8 Hz). Calling it
//  from loop() would drag the camera down to 4 fps, so it runs in its own
//  task on core 0 and loop() only ever renders the newest completed frame.
//  Core 0's idle task is already unsubscribed from the WDT in setup().
#define MLX_TASK_CORE  0
#define MLX_TASK_STACK 8192                     // getFrame 1668 B + begin() 1664 B
#define MLX_TASK_PRIO  1

#define THERM_W        32
#define THERM_H        24
#define THERM_SCALE    5                        // 32x24 -> 160x120
#define THERM_Y        ((TFT_H - THERM_H * THERM_SCALE) / 2)   // centred in the pane

//  Orientation, set by eye against the camera pane on the bench. The two
//  sensors are mounted independently, so nothing guarantees they agree —
//  these exist so matching them up is a define, not a code edit. Same idea
//  as CAM_VFLIP / CAM_HMIRROR, but done in the render loop rather than in
//  the sensor, because the MLX90640 has no orientation registers.
//    thermal mirrored vs the video ....... flip THERM_HMIRROR
//    thermal upside down vs the video .... flip THERM_VFLIP
//  Cleared from 1/1 to rotate the thermal image 180 with the panel. Toggling
//  BOTH axes is a rotation; toggling one would mirror it and the text-like
//  shapes of a scene would read backwards.
#define THERM_HMIRROR  0
#define THERM_VFLIP    0

//  Runtime, persisted camera/thermal orientation (SETTINGS -> CAMERA / IR).
//  The visible flips are applied in the OV5640 sensor; the thermal flips are
//  applied in the render loop (the MLX90640 has no orientation registers).
//  Initialised from the compile-time defaults above.
static bool camFlipH   = CAM_HMIRROR,  camFlipV   = CAM_VFLIP;
static bool thermFlipH = THERM_HMIRROR, thermFlipV = THERM_VFLIP;

// ── IR/visible fusion (MSX-style) ──
//  The thermal image says WHAT temperature; the visible camera's edges say
//  WHERE things are. 32x24 thermal upscaled is unreadable blobs on its own,
//  so the fusion view paints the thermal false-colour and embosses the
//  visible camera's outlines onto it in black.
//
//  The MLX90640 (55x35 deg here) sees a NARROWER cone than the camera, so
//  its data only covers a rectangle in the middle of the frame. FUS_X/Y/W/H
//  place that rectangle in 320x172 display coordinates. They are RUNTIME
//  values (the "fus" console command nudges them live); these are just the
//  power-on defaults. Outside the rectangle the view shows the dimmed
//  grayscale camera for context.
//
//  Calibrate once: point both cameras at a hot object at your working
//  distance, open the fusion view, and use "fus" over serial to slide the
//  rectangle until the coloured blob sits on the object. Then bake the
//  numbers back into these defines. The lenses being close together means a
//  single fixed rectangle holds across distance (little parallax).
#define FUS_X_DEF     20
#define FUS_Y_DEF      0
#define FUS_W_DEF    280
#define FUS_H_DEF    172
#define FUS_EDGE_GAIN  3        // visible-edge emphasis; higher = darker outlines
#define FUS_EDGE_MAX 235        // cap, so an outline never goes fully black
#define FUS_CTX_DIM  110        // brightness (/256) of the grayscale context ring
#define FUS_OUTLINE  1         // draw a thin box round the thermal-covered region

// ── BNO085 in UART-RVC mode ──
//  One-way 115200 stream, nothing is sent to the sensor. On the Adafruit
//  BNO085 breakout: sensor **SDA** -> BNO_RX_PIN, and **P0 -> 3.3V** to
//  select RVC. Latched at reset, so power-cycle after strapping.
#define BNO_RX_PIN    14
#define BNO_BAUD      115200

//  OPTIONAL reset line to the sensor's RST pad. -1 = not wired.
//
//  Why it is worth a jumper: the BNO08x latches its protocol (I2C / UART /
//  UART-RVC / SPI) from its mode pads *at reset only*. If the sensor shares
//  this board's 3V3 rail, then pressing the ESP32's reset button does NOT
//  reset the sensor — the rail never drops, so the BNO keeps whatever mode
//  it latched whenever it last saw power. That makes "I set the strap and
//  rebooted" fail silently, which is the single most confusing way this
//  sensor goes wrong.
//
//  Wire RST to GPIO3 (the last free pin — strapping, but this is a slow
//  output driven after boot, which is exactly what it is still good for)
//  and set this to 3. Firmware then resets the sensor on every boot and
//  the straps take effect without touching the power.
#define BNO_RST_PIN   -1
#define IMU_STALE_MS  1000                      // no frame for this long = dead
#define INST_REDRAW_MS 66                       // ~15 Hz instrument refresh

// ── User interface ──
//  One button for now: BOOT on GPIO0, already fitted and already pulled up.
//  It is a strapping pin, but only at reset — as a runtime input it is free.
//
//  Everything routes through UiAction rather than reading the pin directly,
//  so the 5-button panel drops in later by feeding the same five actions
//  from five GPIOs (or from a PCAL9538A on the I2C bus) without touching a
//  line of view code.
#define BTN_BOOT_PIN    0
#define BTN_DEBOUNCE_MS 25
#define BTN_LONG_MS     600                     // held this long = select/back

// ── PCF8574 gamepad — 5 buttons on the I2C bus ──
//  A D-pad + ENTER wired to a PCF8574's P0..P4, each button pulling its pin
//  to GND (active low). The '574 has weak internal pull-ups, so no external
//  resistors are needed; just never WRITE a 0 to a pin being read, which the
//  read-only code below never does.
//
//  ADDRESS: 0x21 = A0->VCC, A1->GND, A2->GND on a plain PCF8574 (base
//  0100 A2 A1 A0). The 'A' variant (PCF8574A) would be 0x39 with the same
//  strapping — this part is the RGYR (non-A), so 0x21. No clash with the
//  MLX90640 at 0x33.
//
//  BUS SHARING: the MLX90640 hogs this 400 kHz bus from a core-0 task, so
//  every I2C access now goes through i2cMutex, and the thermal scan only runs
//  while a thermal/fusion view is up (mlxScanOn). That keeps the bus free for
//  fast button polling everywhere else. The '574's own 100 kHz rating is
//  exceeded at 400 kHz — usually fine over short traces; suspect it first if
//  presses are erratic.
#define PCF_ENABLE   1
#define PCF_ADDR     0x21
#define PCF_UP       0                          // P0
#define PCF_LEFT     1                          // P1
#define PCF_DOWN     2                          // P2
#define PCF_ENTER    3                          // P3
#define PCF_RIGHT    4                          // P4
#define PCF_POLL_MS         20                  // ~50 Hz button scan
//  Slowed 2026-09-23 — presses felt twitchy: a normal tap could land two
//  steps. Longer debounce rejects contact chatter; the longer hold delay
//  keeps an ordinary press from tipping into auto-repeat; the slower repeat
//  makes a held D-pad scroll at a followable pace. Raise to slow further.
#define PCF_DEBOUNCE_MS     35
#define PCF_REPEAT_DELAY_MS 650                 // hold before auto-repeat starts
#define PCF_REPEAT_MS       250                 // then repeat this often (D-pad)
#define UI_REDRAW_MS    66                      // ~15 Hz for the drawn views
#define CYBER_SCANLINE  0                       // dark row every Nth line, 0 = off

// ── ST7789 commands ──
#define ST_SWRESET 0x01
#define ST_SLPOUT  0x11
#define ST_NORON   0x13
#define ST_INVOFF  0x20
#define ST_INVON   0x21
#define ST_DISPON  0x29
#define ST_CASET   0x2A
#define ST_RASET   0x2B
#define ST_RAMWR   0x2C
#define ST_MADCTL  0x36
#define ST_COLMOD  0x3A

// ── Colours (RGB565) ──
//  The RealDriver theme (realdriver.html :root): neon blue/cyan #00ffe7 as
//  the main accent, neon red #ff3c5f as the second, on a blue-black #050709
//  with cyan-tinted rules and blue-grey text. The names are historical —
//  NEON_MAGENTA is now RealDriver's red (headers, primary plates) and
//  NEON_PINK a lighter tint of it (secondary highlights) — kept so every
//  view picks the theme up without being touched.
#define BLACK        0x0000
#define WHITE        0xFFFF
#define DIM          0x4B0E                     // #4a6272  muted blue-grey
#define HDR_BG       0x0208
#define NEON_CYAN    0x07FC                     // #00ffe7  RealDriver --accent
#define NEON_GREEN   0x07F1                     // #00ff88  --green
#define NEON_RED     0xF9EB                     // #ff3c5f  --accent2 (also errors)
#define NEON_YELLOW  0xFEA0                     // #ffd600  --accent3
//  Menu palette. RGB565 is 5/6/5, so the dark tones have to stay very low
//  or they wash out to grey once the panel's inversion is applied.
#define NEON_MAGENTA 0xF9EB                     // #ff3c5f  --accent2: headers, primary
#define NEON_PINK    0xFBD1                     // #ff7a8f  lighter red: secondary
#define NEON_ORANGE  0xFCC7                     // #ff9a3c
#define CYBER_BG     0x0021                     // #050709  --bg, blue-black
#define CYBER_GRID   0x09C7                     // #0f3a3c  cyan-tinted rules (--border)
#define CYBER_DIMTXT 0x6C53                     // #6f8b9b  dim text, --text toward --dim

//  40 MHz is fine over PCB traces but marginal down a flying jumper —
//  and SCK has just moved onto one. A clock that doesn't survive the
//  wire shows up as corrupted pixels / flashing, not a dead screen.
//  Drop to 20000000 or 10000000 to test; the frame rate barely moves
//  because the CPU-driven SPI path, not the clock, is the bottleneck.
#define LCD_SPI_HZ 40000000

static const SPISettings LCD_SPI(LCD_SPI_HZ, MSBFIRST, SPI_MODE0);

// ─────────────────────────────────────────────────────────
//  UI types, declared HERE and not next to the UI code, because the
//  .ino preprocessor inserts its generated prototypes immediately above
//  the first function in the file. uiEnter() and uiAction() take these
//  types, so declaring them any later means those prototypes reference
//  types that do not exist yet — which shows up as the baffling
//  "variable or field declared void".
// ─────────────────────────────────────────────────────────
// Which view owns the panel, and where the menu highlight sits. Declared
// up here for the same reason as the block below: the serial console
// references them long before the UI code is defined.
//  Menu order follows this enum.
enum UiView   : uint8_t { UI_MENU, UI_CAMERA, UI_THERMAL, UI_CUBE,
                          UI_COMPASS, UI_GAS, UI_AIR, UI_FILES, UI_WIFI, UI_BLE, UI_GPS, UI_CLOCK, UI_MUSIC, UI_RECORDER, UI_RADAR,
                          UI_SEQ, UI_SERVO, UI_IMUSERVO, UI_GAME, UI_BLOCKS, UI_TANK, UI_SAND, UI_DOOM, UI_SETTINGS,
                          //  Everything after UI_SETTINGS is reached from inside
                          //  another view, not the menu (UI_ITEMS stops at
                          //  SETTINGS): the enhanced (camera + IR) thermal view
                          //  from THERMAL CAMERA's ENTER, the image viewer from
                          //  the file browser, the network picker and keyboard
                          //  from Settings > WIFI.
                          UI_FUSION, UI_IMAGE, UI_NETPICK, UI_KEYB, UI_COUNT };
enum UiAction : uint8_t { ACT_NONE, ACT_NEXT, ACT_PREV, ACT_SELECT, ACT_BACK, ACT_RIGHT };

//  Surveillance-detection types, declared here for the same reason as the UI
//  enums: the .ino preprocessor emits prototypes for detName()/lookupOui()
//  at the top of the file, so the types they use must exist before then.
enum DetType : uint8_t {
  DET_NONE = 0, DET_FLOCK, DET_AXON, DET_ALPR, DET_CAMERA, DET_RING,
  DET_SKIMMER, DET_HACKER, DET_EVILTWIN,
  //  BLE categories (below use the same confidence + detName machinery)
  DET_AIRTAG, DET_META, DET_DRONE, DET_TILE, DET_SAMSUNG, DET_GOOGLE,
  DET_RAVEN, DET_IBEACON
};
enum DetConf : uint8_t { CONF_LOW, CONF_MED, CONF_HIGH };
struct OuiRow  { uint8_t b[3]; DetType type; DetConf conf; };
struct SsidRow { const char* prefix; DetType type; };

//  One owner at a time for the shared I2C bus (MLX task on core 0, buttons on
//  core 1). Created in setup() before the MLX task is spawned.
static SemaphoreHandle_t i2cMutex = nullptr;
//  The MLX only scans while a thermal or fusion view is showing; otherwise it
//  leaves the bus alone so button polling stays snappy.
static volatile bool     mlxScanOn = false;

//  Debounced PCF8574 port (active low: a 0 bit = that button is DOWN).
//  The menus only need press events; the game needs to know what is held.
static volatile uint8_t pcfStable = 0xFF;

// ── I2C diagnostics ──
//  Bus speed, saved in NVS ("i2chz") so a speed set with "i2c hz <n>" also
//  applies from the very next boot — the start-up is where faults show up.
//  Per-device failure counters and worst transfer times, reported by the
//  "i2c" console command; each failure is also logged with its timestamp
//  (rate-limited) so a boot log shows when the bus went bad.
static uint32_t          i2cHz = 400000;
static volatile uint32_t i2cErrPcf = 0, i2cErrPca = 0, i2cErrGps = 0, i2cBusyPcf = 0;
static volatile uint32_t i2cMaxUsPcf = 0, i2cMaxUsPca = 0;
//  Each transfer gives up after this long. The core's default is about a
//  second, so one device holding the bus froze the UI (the intro video
//  stalled a second in). 20 ms is ~800 bytes at 400 kHz: plenty for any
//  transfer here, and short enough that a stuck bus only stutters.
#define I2C_TIMEOUT_MS 20

static void i2cBusStart() {
  Wire.begin(MLX_SDA, MLX_SCL, i2cHz);
  Wire.setTimeOut(I2C_TIMEOUT_MS);
}

//  Look at the bare lines, and free a device stuck mid-byte. With the I2C
//  peripheral detached, SDA and SCL are read as inputs. If SDA is low with
//  SCL high, a device is waiting to finish a byte: clock SCL (up to 9 times)
//  until it lets go, then send a STOP. Then the bus is restarted. A line
//  that is still low afterwards is being held electrically (an unpowered
//  device, a short, swapped wires), which no clocking can fix.
//  Returns true when both lines end up high.
static bool i2cRecover(bool verbose) {
  bool locked = i2cMutex && xSemaphoreTake(i2cMutex, pdMS_TO_TICKS(2000)) == pdTRUE;
  Wire.end();
  pinMode(MLX_SDA, INPUT_PULLUP);
  pinMode(MLX_SCL, INPUT_PULLUP);
  delayMicroseconds(20);
  bool sda0 = digitalRead(MLX_SDA), scl0 = digitalRead(MLX_SCL);
  int pulses = 0;
  if (scl0 && !sda0) {
    pinMode(MLX_SCL, OUTPUT_OPEN_DRAIN);
    digitalWrite(MLX_SCL, HIGH);
    for (; pulses < 9 && !digitalRead(MLX_SDA); pulses++) {
      digitalWrite(MLX_SCL, LOW);  delayMicroseconds(5);
      digitalWrite(MLX_SCL, HIGH); delayMicroseconds(5);
    }
    pinMode(MLX_SDA, OUTPUT_OPEN_DRAIN);                 // STOP: SDA rises while SCL is high
    digitalWrite(MLX_SDA, LOW);  delayMicroseconds(5);
    digitalWrite(MLX_SCL, HIGH); delayMicroseconds(5);
    digitalWrite(MLX_SDA, HIGH); delayMicroseconds(5);
    pinMode(MLX_SDA, INPUT_PULLUP);
    pinMode(MLX_SCL, INPUT_PULLUP);
    delayMicroseconds(20);
  }
  bool sda1 = digitalRead(MLX_SDA), scl1 = digitalRead(MLX_SCL);
  i2cBusStart();
  if (locked) xSemaphoreGive(i2cMutex);

  bool ok = sda1 && scl1;
  if (verbose || !ok || pulses)
    Serial.printf("I2C lines: SDA%d %s, SCL%d %s%s%s\n",
                  MLX_SDA, sda1 ? "high" : "LOW", MLX_SCL, scl1 ? "high" : "LOW",
                  pulses ? " (freed with clock pulses)" : "",
                  (!sda0 || !scl0) && !pulses ? " (was low)" : "");
  if (!ok)
    Serial.printf("I2C: %s held low - something on the bus is pulling it down "
                  "(an unpowered device, swapped SDA/SCL, a short). Unplug devices "
                  "one at a time to find it.\n",
                  !sda1 && !scl1 ? "SDA and SCL" : !sda1 ? "SDA" : "SCL");
  return ok;
}

static void i2cNoteFail(const char* who, volatile uint32_t& n) {
  n++;
  if (n <= 5 || n % 50 == 0)                // first few, then every 50th
    Serial.printf("I2C: %s transfer failed (#%lu) at %lu ms\n", who,
                  (unsigned long)n, (unsigned long)millis());
}

#define UI_ITEMS ((int)UI_SETTINGS)             // menu = CAMERA .. SETTINGS

static const char* const kUiName[UI_COUNT] = {
  "MENU", "CAMERA", "THERMAL CAMERA", "GYROSCOPE",
  "COMPASS", "GAS SENSORS", "AIR QUALITY", "FILE BROWSER", "WIFI", "BLUETOOTH", "GPS", "CLOCK", "MUSIC PLAYER", "SOUND RECORDER", "PLANE RADAR", "SEQUENCES", "SERVO TESTER", "IMU TO SERVO", "NEON RUNNER", "NEON BLOCKS", "FISH TANK", "SAND PHYSICS", "DOOM", "SETTINGS",
  "ENHANCED THERMAL", "IMAGE", "JOIN NETWORK", "KEYBOARD"
};

static UiView   uiView     = UI_MENU;
static uint8_t  uiSel      = 0;                 // menu highlight, 0..UI_ITEMS-1
static uint32_t uiLastDraw = 0;

//  Web page feeds. Each /capture or /thermal request stamps its time here;
//  while a stamp is recent, the camera is grabbed and JPEG-encoded for the
//  page (even with no camera view on the LCD) and the thermal sensor keeps
//  scanning (even with no thermal view). Declared up here because loop(),
//  the MLX task and the web handlers all read them.
//  Set once the Bluetooth controller is starting/up. Wi-Fi modem sleep must
//  then stay ON (coexistence aborts otherwise), so the web server only turns
//  sleep off while this is false. Declared up here for the web code's sake.
static volatile bool btActive = false;

#define WEB_FEED_HOLD_MS 3000                   // page gone this long = stop
#define WEB_CAM_MS       150                    // ~6 fps, the page's own poll rate
#define WEB_JPEG_Q       60                     // lower than snapshots: size over detail
static volatile uint32_t webCamReqMs = 0, webThermReqMs = 0;
static bool webWantsCam()   { return webCamReqMs   && millis() - webCamReqMs   < WEB_FEED_HOLD_MS; }
static bool webWantsTherm() { return webThermReqMs && millis() - webThermReqMs < WEB_FEED_HOLD_MS; }

//  Latest camera JPEG for the page. loop() replaces it; the web task sends
//  it. webJpgMux guards the swap and the send, and loop() never waits on
//  it — if a send is in progress, that frame is simply not published.
static SemaphoreHandle_t webJpgMux = nullptr;
static uint8_t*          webJpg    = nullptr;
static size_t            webJpgLen = 0;
static volatile uint32_t webJpgMs  = 0;

//  Gyroscope cube. The cube is an object fixed in the room, seen through the
//  screen: its "UP" face always points at the real sky (absolute tilt from
//  the IMU), and it holds its heading while the board turns (see cubeMatrix).
//  RESET only re-aims the heading - the horizontal direction "away from the
//  viewer" at the press, stored in world coordinates - so the cube faces you
//  straight-on again. Tilt is never captured, so UP can never be locked
//  pointing sideways. Runtime only; set on the first frame if never pressed.
static float    cubeFwdX = 0, cubeFwdY = 1;
static bool     cubeFwdSet = false;
static uint32_t cubeResetMs = 0;          // for the button's "DONE" flash


// ─────────────────────────────────────────────────────────────
//  Minimal ST7789 driver (proven working) — inherits Adafruit_GFX
// ─────────────────────────────────────────────────────────────
class ST7789Mini : public Adafruit_GFX {
public:
  ST7789Mini() : Adafruit_GFX(TFT_W, TFT_H) {}

  void begin() {
    pinMode(PIN_DC, OUTPUT); pinMode(PIN_CS, OUTPUT);
    digitalWrite(PIN_CS, HIGH);
    SPI.begin(PIN_SCK, -1, PIN_MOSI, -1);
#if PIN_RES >= 0
    pinMode(PIN_RES, OUTPUT);
    digitalWrite(PIN_RES, HIGH); delay(10);
    digitalWrite(PIN_RES, LOW);  delay(10);
    digitalWrite(PIN_RES, HIGH); delay(120);
#else
    delay(140);                  // let the panel's power-on reset settle
#endif
    writeCmd(ST_SWRESET);        delay(150);
    writeCmd(ST_SLPOUT);         delay(120);

#if PANEL_ST7796
    // The ST7796S keeps its power, gamma and display-function registers
    // behind a locked "command set 2". F0/C3 then F0/96 unlocks it; F0/3C
    // then F0/69 locks it again. Writing the registers without unlocking
    // first is silently ignored — the panel lights up but the image is
    // washed out or ghosted, which reads like a bad supply, not a missing
    // unlock.
    writeCmd(0xF0); writeData(0xC3);
    writeCmd(0xF0); writeData(0x96);
#endif

    writeCmd(ST_COLMOD); writeData(0x55);         // 16-bit RGB565
    writeCmd(ST_MADCTL); writeData(PANEL_MADCTL); // landscape

#if PANEL_ST7796
    writeCmd(0xB4); writeData(0x01);              // 1-dot inversion
    writeCmd(0xB6); writeData(0x80); writeData(0x02); writeData(0x3B);

    static const uint8_t kDoca[] = { 0x40, 0x8A, 0x00, 0x00, 0x29,
                                     0x19, 0xA5, 0x33 };
    writeCmd(0xE8);                               // display output ctrl adjust
    for (uint8_t i = 0; i < sizeof(kDoca); i++) writeData(kDoca[i]);

    writeCmd(0xC1); writeData(0x06);              // power control 2
    writeCmd(0xC2); writeData(0xA7);              // power control 3
    writeCmd(0xC5); writeData(0x18);              // VCOM control
    delay(120);

    static const uint8_t kPGamma[] = { 0xF0, 0x09, 0x0B, 0x06, 0x04, 0x15,
                                       0x2F, 0x54, 0x42, 0x3C, 0x17, 0x14,
                                       0x18, 0x1B };
    static const uint8_t kNGamma[] = { 0xE0, 0x09, 0x0B, 0x06, 0x04, 0x03,
                                       0x2B, 0x43, 0x42, 0x3B, 0x16, 0x14,
                                       0x17, 0x1B };
    writeCmd(0xE0);
    for (uint8_t i = 0; i < sizeof(kPGamma); i++) writeData(kPGamma[i]);
    writeCmd(0xE1);
    for (uint8_t i = 0; i < sizeof(kNGamma); i++) writeData(kNGamma[i]);
    delay(120);

    writeCmd(0xF0); writeData(0x3C);              // relock command set 2
    writeCmd(0xF0); writeData(0x69);
    delay(120);
#endif

#if PANEL_INVERT
    writeCmd(ST_INVON);          delay(10);
#else
    writeCmd(ST_INVOFF);         delay(10);
#endif
    writeCmd(ST_NORON);          delay(10);
    writeCmd(ST_DISPON);         delay(120);
  }

  //  Orientation is the one panel setting that cannot be worked out from a
  //  datasheet — it depends on how the glass is mounted. Exposing it at
  //  runtime turns a four-guess, four-rebuild hunt into four keystrokes.
  void setMadctl(uint8_t v) { writeCmd(ST_MADCTL); writeData(v); }

  void drawPixel(int16_t x, int16_t y, uint16_t color) override {
    if (x < 0 || y < 0 || x >= _width || y >= _height) return;
    setAddrWindow(x, y, 1, 1); beginBlit(); pushColor(color, 1); endBlit();
  }
  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override {
    if (y < 0 || y >= _height || w <= 0) return;
    if (x < 0) { w += x; x = 0; }
    if (x + w > _width) w = _width - x;
    if (w <= 0) return;
    setAddrWindow(x, y, w, 1); beginBlit(); pushColor(color, w); endBlit();
  }
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override {
    if (x < 0 || x >= _width || h <= 0) return;
    if (y < 0) { h += y; y = 0; }
    if (y + h > _height) h = _height - y;
    if (h <= 0) return;
    setAddrWindow(x, y, 1, h); beginBlit(); pushColor(color, h); endBlit();
  }
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override {
    if (w <= 0 || h <= 0) return;
    if (x < 0) { w += x; x = 0; }
    if (y < 0) { h += y; y = 0; }
    if (x + w > _width)  w = _width  - x;
    if (y + h > _height) h = _height - y;
    if (w <= 0 || h <= 0) return;
    setAddrWindow(x, y, w, h); beginBlit(); pushColor(color, (uint32_t)w * h); endBlit();
  }
  void fillScreen(uint16_t color) override { fillRect(0, 0, _width, _height, color); }

  // ── Bulk blit path, for video ──
  //  The Adafruit_GFX entry points above cost two SPI.transfer() calls
  //  per pixel, which is ~2 fps at this frame size. Instead: open one
  //  address window for the whole frame, hold CS low, and hand whole
  //  rows to the SPI FIFO.
  void beginFrame(int16_t x, int16_t y, int16_t w, int16_t h) {
    setAddrWindow(x, y, w, h);
    SPI.beginTransaction(LCD_SPI);
    digitalWrite(PIN_CS, LOW);
    digitalWrite(PIN_DC, HIGH);         // pixel data, not command
  }
  void pushBytes(const uint8_t* d, uint32_t n) {
#if CAM_SWAP_BYTES
    SPI.writePixels(d, n);              // swaps each 16-bit pixel
#else
    SPI.writeBytes(d, n);               // memory order, straight through
#endif
  }
  //  For GFXcanvas16, which stores uint16_t in the ESP32's native little-endian
  //  order. The panel wants high byte first, so this path always swaps —
  //  independent of CAM_SWAP_BYTES, which only describes the sensor's output.
  void pushPixels16(const uint16_t* px, uint32_t count) {
    SPI.writePixels(px, count * 2);
  }
  void endFrame() { digitalWrite(PIN_CS, HIGH); SPI.endTransaction(); }

private:
  void beginBlit() { SPI.beginTransaction(LCD_SPI); digitalWrite(PIN_CS, LOW); }
  void endBlit()   { digitalWrite(PIN_CS, HIGH); SPI.endTransaction(); }
  void writeCmd(uint8_t c) {
    SPI.beginTransaction(LCD_SPI); digitalWrite(PIN_DC, LOW); digitalWrite(PIN_CS, LOW);
    SPI.transfer(c); digitalWrite(PIN_CS, HIGH); SPI.endTransaction();
  }
  void writeData(uint8_t d) {
    SPI.beginTransaction(LCD_SPI); digitalWrite(PIN_DC, HIGH); digitalWrite(PIN_CS, LOW);
    SPI.transfer(d); digitalWrite(PIN_CS, HIGH); SPI.endTransaction();
  }
  void pushColor(uint16_t color, uint32_t count) {
    uint8_t hi = color >> 8, lo = color & 0xFF;
    digitalWrite(PIN_DC, HIGH);
    while (count--) { SPI.transfer(hi); SPI.transfer(lo); }
  }
  void setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    uint16_t x0 = x + COL_OFFSET, x1 = x + w - 1 + COL_OFFSET;
    uint16_t y0 = y + ROW_OFFSET, y1 = y + h - 1 + ROW_OFFSET;
    writeCmd(ST_CASET); writeData(x0 >> 8); writeData(x0 & 0xFF); writeData(x1 >> 8); writeData(x1 & 0xFF);
    writeCmd(ST_RASET); writeData(y0 >> 8); writeData(y0 & 0xFF); writeData(y1 >> 8); writeData(y1 & 0xFF);
    writeCmd(ST_RAMWR);
  }
};

ST7789Mini tft;

void printLeft(const char* s, int x, int yTop, uint8_t size, uint16_t color) {
  tft.setTextSize(size); tft.setTextWrap(false); tft.setTextColor(color);
  tft.setCursor(x, yTop); tft.print(s);
}
void printBg(const char* s, int x, int yTop, uint8_t size, uint16_t fg, uint16_t bg) {
  tft.setTextSize(size); tft.setTextWrap(false); tft.setTextColor(fg, bg);
  tft.setCursor(x, yTop); tft.print(s);
}

// ─────────────────────────────────────────────────────────────
//  Backlight — PWM brightness on PIN_BL
// ─────────────────────────────────────────────────────────────
static uint8_t blLevel = 0;
//  The level to sit at while awake, as distinct from what is on the
//  panel right now — the idle dimmer drives blLevel down and needs to
//  know what to come back to.
static uint8_t blActiveLevel = BL_DEFAULT;

void blSet(uint8_t level) {
#if PIN_BL >= 0
  ledcWrite(BL_PWM_CH, level);
#endif
  blLevel = level;
}

void blBegin() {
#if PIN_BL >= 0
  ledcSetup(BL_PWM_CH, BL_PWM_HZ, BL_BITS);
  ledcAttachPin(PIN_BL, BL_PWM_CH);
#endif
  blSet(0);                        // dark until the panel has been cleared
}

// ── Brightness demo sweep: 90% down to 10%, then full ─────────
//  Deliberately a non-blocking state machine rather than a delay() loop, so
//  the camera and instruments keep updating underneath it. Brightness can
//  only be judged against real moving content — stepping a black screen
//  through nine levels tells you nothing — and it means the sweep costs
//  nothing in time-to-first-frame.
#define BL_DEMO_AT_BOOT 0               // 1 = sweep at boot; "bldemo" runs it any time
#define BL_DEMO_MS      2500            // dwell per step

static const uint8_t kBlDemoPct[] = { 90, 80, 70, 60, 50, 40, 30, 20, 10 };
static bool     blDemoActive = false;
static uint8_t  blDemoIdx    = 0;
static uint32_t blDemoNextMs = 0;

void blDemoStart() {
  blDemoActive = true;
  blDemoIdx    = 0;
  blDemoNextMs = 0;                // 0 = advance on the very next poll
}

/** Percentage currently being shown, or 0 when the sweep is not running. */
uint8_t blDemoPct() {
  return (blDemoActive && blDemoIdx) ? kBlDemoPct[blDemoIdx - 1] : 0;
}

void blDemoPoll() {
  if (!blDemoActive) return;
  uint32_t now = millis();
  if (blDemoNextMs && now < blDemoNextMs) return;

  if (blDemoIdx >= sizeof(kBlDemoPct)) {   // swept them all — settle at full
    blSet(255);
    blActiveLevel = 255;                   // and that is now the awake level
    blDemoActive = false;
    Serial.println("backlight demo finished - 100%");
    return;
  }
  uint8_t pct = kBlDemoPct[blDemoIdx++];
  blSet((uint8_t)((pct * 255 + 50) / 100));    // rounded, so 10% -> 26 not 25
  Serial.printf("backlight demo: %u%%  (%u/255)\n", pct, blLevel);
  blDemoNextMs = now + BL_DEMO_MS;
}

// ─────────────────────────────────────────────────────────────
//  Boot / test log — SERIAL ONLY.
//
//  The on-screen version is commented out so the TFT stays a pure
//  waterfall; results still go to USB serial @115200. To put the text
//  back on the panel, uncomment the three lines in logLine() and the
//  body of logClear() below (and the two blocks marked "status text"
//  in drawHeader() and setup()).
// ─────────────────────────────────────────────────────────────
#define LOG_LH  10                      // line pitch, px
static int logY __attribute__((unused)) = 0;   // only used by the commented code

void logClear() { /* status text: tft.fillScreen(BLACK); logY = 0; */ }

void logLine(uint16_t color, const char* fmt, ...) {
  char b[80];
  va_list ap; va_start(ap, fmt);
  vsnprintf(b, sizeof(b), fmt, ap);
  va_end(ap);
  Serial.println(b);
  (void)color;
  // status text:
  // if (logY + LOG_LH > TFT_H) logClear();  // wrap back to the top
  // printLeft(b, 2, logY, 1, color);
  // logY += LOG_LH;
}

// ─────────────────────────────────────────────────────────────
//  microSD — mount, helpers, self-test, benchmark
// ─────────────────────────────────────────────────────────────
static bool     sdMounted  = false;
static uint32_t sdClockKHz = 0;

// Frame counters, reported by the "fps" console command.
static uint32_t camFrames = 0;
static uint32_t camDrops  = 0;

// MLX90640 state. The frame buffers are double-buffered because the sensor
// task on core 0 writes one while loop() on core 1 renders the other.
#if MLX_ENABLE
static Adafruit_MLX90640 mlx;
static volatile bool mlxReady = false;   // set by mlxTask once begin() lands
static float    mlxBuf[2][THERM_W * THERM_H];    // 2 x 3 KB
static volatile uint8_t  mlxWriteIdx = 0;
static volatile uint8_t  mlxReadIdx  = 0xFF;     // 0xFF = no complete frame yet
static volatile uint32_t mlxFrames = 0, mlxErrs = 0, mlxLastMs = 0, mlxFrameMs = 0;
static volatile float    mlxTa = 0, mlxMin = 0, mlxMax = 0, mlxCentre = 0;
//  IR-fusion overlay rectangle, in display coords. Declared here (not by
//  fuseFrame) because the "fus" console command adjusts them and lives
//  far above the renderer.
static int fusX = FUS_X_DEF, fusY = FUS_Y_DEF, fusW = FUS_W_DEF, fusH = FUS_H_DEF;
#endif

//  Display units. Everything INTERNAL stays in degrees C — the sensor, the
//  palette, the eased auto-range, the min/max search. Only the numbers put
//  in front of a human are converted, so no downstream maths has to care
//  which unit is selected and switching at runtime cannot drift the image.
#define TEMP_F_DEFAULT 1                        // 1 = Fahrenheit, 0 = Celsius
static bool tempF = TEMP_F_DEFAULT;
static inline float tconv(float c) { return tempF ? c * 1.8f + 32.0f : c; }
static inline char  tunit(void)    { return tempF ? 'F' : 'C'; }

// BNO085 state. Declared up here rather than beside imuPoll() because the
// serial console below references the counters, and .ino auto-prototyping
// covers functions but not variables.
static float    imuYaw = 0, imuPitch = 0, imuRoll = 0;
static float    imuAx = 0, imuAy = 0, imuAz = 0;  // m/s^2
static uint32_t imuFrames = 0, imuBadSum = 0, imuLastMs = 0;
static uint32_t imuRawBytes = 0;                 // the key "is it wired?" counter

// How the BNO085 sits on THIS board, relative to the orientation the rest of
// the firmware was tuned for (the original breakout): degrees counter-
// clockwise looking down on the chip - 0, 90, 180 or 270. imuPoll() turns
// every frame by it, so the cube, compass, idle dimmer, CSV log and tilt
// views all see the same axes on every board. 0 leaves the data untouched.
// The v6 PCB (32SC V2) needs 270: measured 2026-11-21 with the board held
// upright (UI reading normally) and tilted - screen up = chip +X, screen
// right = chip -Y - which is the breakout's frame turned 270 in this sense.
// NVS key "imurot"; "imurot" console command or SETTINGS > IMU/COMP > MOUNT.
static uint16_t imuMountDeg = 0;

// Filled in by bnoProbe(). Shown ON THE PANEL when the sensor is dead, so the
// fault is readable without a serial console attached.
static char imuVerdict[16] = "";
static char imuHint[28]    = "";
static bool imuProbed      = false;

// CSV logger state.
static bool     imuLogging   = false;
static File     imuLogFile;
static uint32_t imuLogRows   = 0;
static uint32_t imuLogLastMs = 0, imuLogFlushMs = 0;

// Cards vary wildly in how fast a bus they tolerate, and 1-bit SDMMC on
// flying leads is worse still — walk the clock down (kHz) until one
// speed initialises rather than failing outright at high speed.
static const int kSdSpeeds[] = { SDMMC_FREQ_HIGHSPEED,   // 40 MHz
                                 SDMMC_FREQ_DEFAULT,     // 20 MHz
                                 10000,
                                 SDMMC_FREQ_PROBING };   // 400 kHz

const char* sdTypeName() {
  switch (SD_MMC.cardType()) {
    case CARD_NONE: return "none";
    case CARD_MMC:  return "MMC";
    case CARD_SD:   return "SDSC";
    case CARD_SDHC: return "SDHC/XC";
    default:        return "unknown";
  }
}

bool sdMount() {
  if (sdMounted) return true;

  for (uint8_t i = 0; i < sizeof(kSdSpeeds) / sizeof(kSdSpeeds[0]); i++) {
    // setPins must precede every begin() — end() clears the card handle.
    if (!SD_MMC.setPins(SD_CLK, SD_CMD, SD_D0)) {
      logLine(NEON_RED, "setPins rejected");
      return false;
    }
    // mode1bit = true: only DAT0 is wired, so never ask for 4-bit.
    if (SD_MMC.begin("/sdcard", true, false, kSdSpeeds[i])) {
      if (SD_MMC.cardType() != CARD_NONE) {
        sdMounted  = true;
        sdClockKHz = kSdSpeeds[i];
        return true;
      }
    }
    SD_MMC.end();
    delay(20);
  }
  sdClockKHz = 0;
  return false;
}

void sdUnmount() {
  if (!sdMounted) return;
  imuLogClose();                   // flush before the filesystem goes away
  imuLogging = false;
  SD_MMC.end();
  sdMounted  = false;
  sdClockKHz = 0;
}

void sdShowInfo() {
  if (!sdMounted) { logLine(NEON_RED, "SD: not mounted"); return; }
  logLine(NEON_CYAN, "%s 1-bit @ %lukHz", sdTypeName(), (unsigned long)sdClockKHz);
  logLine(NEON_CYAN, "card %luMB  vol %luMB",
          (unsigned long)(SD_MMC.cardSize()  / (1024ULL * 1024ULL)),
          (unsigned long)(SD_MMC.totalBytes() / (1024ULL * 1024ULL)));
  logLine(NEON_CYAN, "used %luMB  free %luMB",
          (unsigned long)(SD_MMC.usedBytes() / (1024ULL * 1024ULL)),
          (unsigned long)((SD_MMC.totalBytes() - SD_MMC.usedBytes()) / (1024ULL * 1024ULL)));
}

// ── Write / read primitives ───────────────────────────────────
bool sdWriteText(const char* path, const char* text, bool append) {
  if (!sdMounted) return false;
  File f = SD_MMC.open(path, append ? FILE_APPEND : FILE_WRITE);
  if (!f) return false;
  size_t n = f.print(text);
  f.close();
  return n == strlen(text);
}

// Reads up to (len-1) bytes into buf, NUL-terminated. -1 on failure.
int sdReadText(const char* path, char* buf, size_t len) {
  if (!sdMounted) return -1;
  File f = SD_MMC.open(path, FILE_READ);
  if (!f) return -1;
  size_t n = f.read((uint8_t*)buf, len - 1);
  f.close();
  buf[n] = '\0';
  return (int)n;
}

// ── BNO085 CSV logger ─────────────────────────────────────────
//  Appends to IMU_LOG_FILE, writing a header only when creating it, so runs
//  accumulate across power cycles instead of overwriting.
bool imuLogOpen() {
  if (!sdMounted) return false;
  if (imuLogFile) return true;
  bool fresh = !SD_MMC.exists(IMU_LOG_FILE);
  imuLogFile = SD_MMC.open(IMU_LOG_FILE, FILE_APPEND);
  if (!imuLogFile) return false;
  if (fresh) imuLogFile.println("ms,yaw,pitch,roll,ax,ay,az");
  return true;
}

void imuLogClose() {
  if (imuLogFile) {
    imuLogFile.flush();
    imuLogFile.close();
  }
}

void imuLogPoll() {
  if (!imuLogging || !sdMounted) return;

  uint32_t now = millis();
  if (now - imuLogLastMs < IMU_LOG_MS) return;
  imuLogLastMs = now;

  // Nothing worth recording while the sensor is silent — otherwise a missing
  // BNO085 quietly fills the card with zeroes.
  if (!imuAlive()) return;

  if (!imuLogOpen()) {
    logLine(NEON_RED, "log open failed - logging off");
    imuLogging = false;
    return;
  }
  if (imuLogFile.printf("%lu,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                        (unsigned long)now, imuYaw, imuPitch, imuRoll,
                        imuAx, imuAy, imuAz) == 0) {
    logLine(NEON_RED, "log write failed - logging off");   // card pulled mid-run
    imuLogging = false;
    imuLogClose();
    return;
  }
  imuLogRows++;

  if (now - imuLogFlushMs >= IMU_FLUSH_MS) {
    imuLogFile.flush();
    imuLogFlushMs = now;
  }
}

void sdListDir(const char* path, uint8_t depth) {
  if (!sdMounted) { logLine(NEON_RED, "SD: not mounted"); return; }
  File dir = SD_MMC.open(path);
  if (!dir) { logLine(NEON_RED, "open fail %s", path); return; }
  if (!dir.isDirectory()) {
    logLine(WHITE, "%s  %lu B", path, (unsigned long)dir.size());
    dir.close();
    return;
  }
  File e;
  while ((e = dir.openNextFile())) {
    const char* nm = e.name();
    if (e.isDirectory()) {
      logLine(NEON_CYAN, "%*s<%s>", depth * 2, "", nm);
      if (depth < 2) sdListDir(e.path(), depth + 1);
    } else {
      logLine(WHITE, "%*s%-14s %lu", depth * 2, "", nm, (unsigned long)e.size());
    }
    e.close();
  }
  dir.close();
}

// ── Throughput test: writes SD_BENCH_KB of a known pattern, reads
//    it back and verifies every byte. Returns true if data matched.
bool sdBench() {
  if (!sdMounted) { logLine(NEON_RED, "bench: no card"); return false; }

  const uint32_t blocks = SD_BENCH_KB * 2;      // 512-byte blocks
  uint8_t buf[512];
  for (int i = 0; i < 512; i++) buf[i] = (uint8_t)(i * 7 + 13);

  File f = SD_MMC.open(SD_BENCH_FILE, FILE_WRITE);
  if (!f) { logLine(NEON_RED, "bench: create fail"); return false; }
  uint32_t t0 = millis();
  for (uint32_t b = 0; b < blocks; b++) {
    if (f.write(buf, sizeof(buf)) != sizeof(buf)) {
      logLine(NEON_RED, "bench: short write @%lu", (unsigned long)b);
      f.close();
      return false;
    }
  }
  f.flush();
  uint32_t wms = millis() - t0;
  f.close();

  f = SD_MMC.open(SD_BENCH_FILE, FILE_READ);
  if (!f) { logLine(NEON_RED, "bench: reopen fail"); return false; }
  bool match = (f.size() == (size_t)blocks * sizeof(buf));
  if (!match) logLine(NEON_RED, "bench: size %lu", (unsigned long)f.size());
  uint8_t rd[512];
  t0 = millis();
  for (uint32_t b = 0; b < blocks && match; b++) {
    if (f.read(rd, sizeof(rd)) != sizeof(rd)) { match = false; break; }
    if (memcmp(rd, buf, sizeof(rd)) != 0) {
      logLine(NEON_RED, "bench: mismatch blk %lu", (unsigned long)b);
      match = false;
    }
  }
  uint32_t rms = millis() - t0;
  f.close();
  SD_MMC.remove(SD_BENCH_FILE);

  if (wms == 0) wms = 1;
  if (rms == 0) rms = 1;
  logLine(NEON_YELLOW, "wr %luKB/s  rd %luKB/s",
          (unsigned long)((uint32_t)SD_BENCH_KB * 1000 / wms),
          (unsigned long)((uint32_t)SD_BENCH_KB * 1000 / rms));
  return match;
}

// ── Self-test ─────────────────────────────────────────────────
static uint8_t sdPass = 0, sdFail = 0;

bool sdStep(const char* what, bool ok) {
  logLine(ok ? NEON_GREEN : NEON_RED, "%s %s", ok ? "[OK] " : "[FAIL]", what);
  if (ok) sdPass++; else sdFail++;
  return ok;
}

// Runs the whole read/write suite. Leaves the card mounted and clean.
void sdSelfTest() {
  char buf[128];
  sdPass = sdFail = 0;

  logLine(NEON_CYAN, "-- microSD self-test --");

  if (!sdStep("mount", sdMount())) {
    logLine(DIM, "CLK%d CMD%d D0%d", SD_CLK, SD_CMD, SD_D0);
    logLine(DIM, "need 10k pullups on");
    logLine(DIM, "CMD, DAT0 AND DAT3");
    logLine(DIM, "card must be FAT32");
    return;
  }
  sdShowInfo();

  // 1. create + read back
  const char* line1 = "RealDriver SD test\n";
  sdStep("write text", sdWriteText(SD_TEST_FILE, line1, false));
  int n = sdReadText(SD_TEST_FILE, buf, sizeof(buf));
  sdStep("read back", n > 0 && strcmp(buf, line1) == 0);
  sdStep("exists()", SD_MMC.exists(SD_TEST_FILE));

  // 2. append + verify both halves survived
  const char* line2 = "second line\n";
  sdStep("append", sdWriteText(SD_TEST_FILE, line2, true));
  n = sdReadText(SD_TEST_FILE, buf, sizeof(buf));
  sdStep("append verify",
         n == (int)(strlen(line1) + strlen(line2)) &&
         strncmp(buf, line1, strlen(line1)) == 0 &&
         strcmp(buf + strlen(line1), line2) == 0);

  // 3. directories + rename + delete
  sdStep("mkdir", SD_MMC.mkdir(SD_TEST_DIR));
  sdStep("file in dir", sdWriteText(SD_TEST_DIR "/a.txt", "nested\n", false));
  sdStep("rename", SD_MMC.rename(SD_TEST_DIR "/a.txt", SD_TEST_DIR "/b.txt"));
  sdStep("read renamed", sdReadText(SD_TEST_DIR "/b.txt", buf, sizeof(buf)) == 7);
  sdStep("remove", SD_MMC.remove(SD_TEST_DIR "/b.txt"));
  sdStep("rmdir", SD_MMC.rmdir(SD_TEST_DIR));

  // 4. bulk binary write/read + throughput
  sdStep("bulk bin verify", sdBench());

  sdStep("cleanup", SD_MMC.remove(SD_TEST_FILE));

  logLine(sdFail ? NEON_RED : NEON_GREEN, "== %u pass, %u fail ==", sdPass, sdFail);
}

// ─────────────────────────────────────────────────────────────
//  RDMJ video player — Motion JPEG off the SD card
//
//  Why a container rather than a folder of .jpg files: opening a file per
//  frame costs milliseconds on SDMMC, and at 24 fps there are only ~41 ms
//  to spend in total. One file, opened once, with a length table on the
//  front means each frame is a seek plus a single read.
//
//  File layout, little endian (built by scratchpad/vid/mkrdmj.py):
//     0  4s   'RDMJ'
//     4  u16  version = 1
//     6  u16  width          8  u16  height
//    10  u16  fps           12  u16  frame count
//    14  u32  largest frame in bytes    18  u16  reserved
//    20  frameCount x u32 frame lengths
//        JPEG payloads, back to back
//
//  Frames decode into an off-screen buffer and land on the panel as ONE
//  bulk push. JPEGDEC hands back 16x16 MCU blocks, and pushing those
//  straight to the panel would mean ~200 separate address-window writes
//  per frame instead of one.
// ─────────────────────────────────────────────────────────────
#if VIDEO_ENABLE

struct __attribute__((packed)) RdmjHeader {
  char     magic[4];
  uint16_t version;
  uint16_t width;
  uint16_t height;
  uint16_t fps;
  uint16_t frames;
  uint32_t maxFrame;
  uint16_t reserved;
};

//  The Python writer packs this with no padding, so a compiler that pads it
//  would silently misread every field. Catch that here, not on the bench.
static_assert(sizeof(RdmjHeader) == 20, "RdmjHeader must be packed to 20 bytes");

static JPEGDEC    vidDec;
static File       vidFile;
static RdmjHeader vidHdr;
static uint32_t*  vidLen  = nullptr;      // per-frame compressed length
static uint32_t*  vidOff  = nullptr;      // absolute file offset per frame
static uint8_t*   vidJpeg = nullptr;      // one compressed frame
static uint16_t*  vidFB   = nullptr;      // decoded RGB565, whole panel
static int        vidOffX = 0, vidOffY = 0;
static uint16_t   vidIdx  = 0;
static uint32_t   vidNextMs = 0;
static uint32_t   vidShown = 0, vidDropped = 0;
static bool       vidPlaying = false;
static bool       vidLoop    = true;

void vidFree() {
  if (vidFile) vidFile.close();
  free(vidLen);  vidLen  = nullptr;
  free(vidOff);  vidOff  = nullptr;
  free(vidJpeg); vidJpeg = nullptr;
  free(vidFB);   vidFB   = nullptr;
}

void vidStop() {
  if (!vidPlaying) return;
  vidPlaying = false;
  vidFree();
  tft.fillScreen(BLACK);                  // panes repaint on the next pass
  logLine(NEON_CYAN, "video stopped - %lu shown, %lu dropped",
          (unsigned long)vidShown, (unsigned long)vidDropped);
}

//  JPEGDEC calls this per MCU block. Clipped against the framebuffer rather
//  than trusted, because a block at the right or bottom edge can overhang
//  the image.
static int vidDraw(JPEGDRAW* pDraw) {
  uint16_t* fb = (uint16_t*)pDraw->pUser;
  for (int row = 0; row < pDraw->iHeight; row++) {
    int y = vidOffY + pDraw->y + row;
    if (y < 0 || y >= TFT_H) continue;
    int x = vidOffX + pDraw->x;
    int w = pDraw->iWidth;
    if (x < 0)          { w += x; x = 0; }
    if (x + w > TFT_W)  { w = TFT_W - x; }
    if (w <= 0) continue;
    memcpy(&fb[y * TFT_W + x], &pDraw->pPixels[row * pDraw->iWidth], w * 2);
  }
  return 1;
}

bool vidPlay(const char* path) {
  vidStop();
  if (!sdMounted) { logLine(NEON_RED, "video: no card"); return false; }

  vidFile = SD_MMC.open(path, FILE_READ);
  if (!vidFile) { logLine(NEON_RED, "video: cannot open %s", path); return false; }

  if (vidFile.read((uint8_t*)&vidHdr, sizeof(vidHdr)) != (int)sizeof(vidHdr) ||
      memcmp(vidHdr.magic, "RDMJ", 4) != 0 || vidHdr.version != 1) {
    logLine(NEON_RED, "video: not an RDMJ file");
    vidFree();
    return false;
  }
  if (vidHdr.width > TFT_W || vidHdr.height > TFT_H || !vidHdr.frames) {
    logLine(NEON_RED, "video: %ux%u does not fit %dx%d",
            vidHdr.width, vidHdr.height, TFT_W, TFT_H);
    vidFree();
    return false;
  }

  size_t tbl = (size_t)vidHdr.frames * sizeof(uint32_t);
  vidLen  = (uint32_t*)malloc(tbl);
  vidOff  = (uint32_t*)malloc(tbl);
  vidJpeg = (uint8_t*)malloc(vidHdr.maxFrame);
  //  110 KB at 320x172. Internal DRAM is faster to push from, but only take
  //  it when VID_DRAM_RESERVE stays free afterwards: the I2S audio driver
  //  (DMA buffers + task stacks, ~52 KB), SD-card DMA bounce buffers and
  //  WiFi all need internal RAM, and the boot intro starving them made
  //  "AUDIO: I2S start FAILED" and failed SD reads. Otherwise PSRAM.
  const size_t VID_DRAM_RESERVE = 72 * 1024;
  size_t fbBytes = (size_t)TFT_W * TFT_H * 2;
  vidFB = nullptr;
  if (heap_caps_get_free_size(MALLOC_CAP_INTERNAL) >= fbBytes + VID_DRAM_RESERVE)
    vidFB = (uint16_t*)heap_caps_malloc(fbBytes, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  bool internal = (vidFB != nullptr);
  if (!vidFB) vidFB = (uint16_t*)ps_malloc(fbBytes);

  if (!vidLen || !vidOff || !vidJpeg || !vidFB) {
    logLine(NEON_RED, "video: out of memory (%u B fb, %lu B jpeg)",
            (unsigned)fbBytes, (unsigned long)vidHdr.maxFrame);
    vidFree();
    return false;
  }

  if (vidFile.read((uint8_t*)vidLen, tbl) != (int)tbl) {
    logLine(NEON_RED, "video: truncated index");
    vidFree();
    return false;
  }
  uint32_t pos = sizeof(vidHdr) + tbl;
  for (uint16_t i = 0; i < vidHdr.frames; i++) { vidOff[i] = pos; pos += vidLen[i]; }

  memset(vidFB, 0, fbBytes);                   // letterbox stays black
  vidOffX = (TFT_W - vidHdr.width)  / 2;
  vidOffY = (TFT_H - vidHdr.height) / 2;

  vidIdx = 0;
  vidShown = vidDropped = 0;
  vidNextMs = millis();
  vidPlaying = true;

  logLine(NEON_CYAN, "playing %s", path);
  logLine(DIM, "%ux%u %ufps %u frames, fb in %s",
          vidHdr.width, vidHdr.height, vidHdr.fps, vidHdr.frames,
          internal ? "DRAM" : "PSRAM");
  return true;
}

void vidPoll() {
  if (!vidPlaying) return;

  uint32_t now = millis();
  if ((int32_t)(now - vidNextMs) < 0) return;         // not this frame's turn yet

  //  Behind schedule by more than a whole frame: skip decoding this one
  //  rather than letting an 8-second clip stretch. Reading nothing and
  //  seeking is almost free, so the clip keeps its real duration.
  bool late = ((int32_t)(now - vidNextMs) > (int32_t)(1000 / vidHdr.fps));

  if (!late) {
    uint32_t n = vidLen[vidIdx];
    if (!vidFile.seek(vidOff[vidIdx]) ||
        vidFile.read(vidJpeg, n) != (int)n) {
      logLine(NEON_RED, "video: read failed at frame %u", vidIdx);
      vidStop();
      return;
    }
    if (vidDec.openRAM(vidJpeg, n, vidDraw)) {
      vidDec.setPixelType(RGB565_BIG_ENDIAN);   // matches the panel's byte order
      vidDec.setUserPointer(vidFB);
      vidDec.decode(0, 0, 0);
      vidDec.close();

      tft.beginFrame(0, 0, TFT_W, TFT_H);
      tft.pushBytes((const uint8_t*)vidFB, (uint32_t)TFT_W * TFT_H * 2);
      tft.endFrame();
      vidShown++;
    } else {
      vidDropped++;
    }
  } else {
    vidDropped++;
  }

  vidNextMs += 1000 / vidHdr.fps;
  if ((int32_t)(millis() - vidNextMs) > (int32_t)(1000 / vidHdr.fps)) {
    vidNextMs = millis();                            // resync after a long stall
  }

  if (++vidIdx >= vidHdr.frames) {
    vidIdx = 0;
    if (!vidLoop) { vidStop(); return; }
  }
}
#endif  // VIDEO_ENABLE

// ─────────────────────────────────────────────────────────────
//  Idle dimming
//
//  Three things count as activity: a button press, a console command, and
//  the board being moved. The movement test compares current attitude
//  against a reference snapshot taken at the last activity, rather than
//  against the previous sample — at 100 Hz, sample-to-sample noise would
//  either trip constantly or need a threshold so coarse that real movement
//  slips under it.
// ─────────────────────────────────────────────────────────────
static uint32_t idleTimeoutMs  = BL_IDLE_MS;    // 0 = never dim
static uint32_t idleLastActive = 0;
static float    idleRefYaw = 0, idleRefPitch = 0, idleRefRoll = 0;
static bool     idleRefValid = false;

void uiNoteActivity() { idleLastActive = millis(); }

/** Sets the level the panel sits at while awake. */
void blSetActive(uint8_t level) {
  blActiveLevel = level;
  blSet(level);
  uiNoteActivity();
}

static float wrapDeg(float d) {
  while (d >  180.0f) d -= 360.0f;
  while (d < -180.0f) d += 360.0f;
  return d;
}

void idlePoll() {
#if PIN_BL < 0
  return;                          // backlight hard-wired: nothing to dim
#else
  uint32_t now = millis();

  //  The brightness sweep owns the backlight while it runs, and a video is
  //  something you are watching — neither should be dimmed out from under.
  if (blDemoActive) { idleLastActive = now; return; }
#if VIDEO_ENABLE
  if (vidPlaying)   { idleLastActive = now; return; }
#endif

  // ── movement, checked at 10 Hz ──
  static uint32_t lastCheck = 0;
  if (now - lastCheck >= 100) {
    lastCheck = now;
    if (imuAlive()) {
      if (!idleRefValid) {
        idleRefYaw = imuYaw; idleRefPitch = imuPitch; idleRefRoll = imuRoll;
        idleRefValid = true;
      } else {
        float accel = sqrtf(imuAx * imuAx + imuAy * imuAy + imuAz * imuAz);
        if (fabsf(wrapDeg(imuYaw - idleRefYaw)) > IDLE_MOVE_DEG ||
            fabsf(imuPitch - idleRefPitch)      > IDLE_MOVE_DEG ||
            fabsf(imuRoll  - idleRefRoll)       > IDLE_MOVE_DEG ||
            fabsf(accel - 9.81f)                > IDLE_BUMP_MS2) {
          idleRefYaw = imuYaw; idleRefPitch = imuPitch; idleRefRoll = imuRoll;
          idleLastActive = now;
        }
      }
    } else {
      //  No IMU: button and console are the only activity there is. Drop the
      //  reference rather than holding one from a sensor that has stopped
      //  reporting, or the first frame after it recovers reads as a jump.
      idleRefValid = false;
    }
  }

  // ── ramp toward whichever level applies ──
  bool wantDim = idleTimeoutMs && blActiveLevel > BL_IDLE_LEVEL &&
                 (now - idleLastActive) >= idleTimeoutMs;
  uint8_t target = wantDim ? BL_IDLE_LEVEL : blActiveLevel;

  static uint32_t lastRamp = 0;
  if (blLevel == target || now - lastRamp < 20) return;
  lastRamp = now;

  if (target > blLevel) {
    blSet(target);                 // waking up is instant, on purpose
  } else {
    int span  = (int)blActiveLevel - (int)BL_IDLE_LEVEL;
    int steps = BL_IDLE_FADE_MS / 20;
    int step  = (steps > 0) ? span / steps : span;
    if (step < 1) step = 1;
    int next = (int)blLevel - step;
    if (next < target) next = target;
    blSet((uint8_t)next);
  }
#endif
}


// ─────────────────────────────────────────────────────────────
//  Servo output — 32 channels on two PCA9685s (0x40 = ch 1-16,
//  0x41 = ch 17-32), ported from 32_Servo_Controller_OV5640_UDP.
//
//  Same model as that sketch so a board moves between the two firmwares
//  unchanged: every channel takes a 0-255 value, mapped through per-channel
//  endpoints (min/mid/max us, 127 = mid) to a 50 Hz pulse, and holds a
//  per-channel boot value from power-up until something commands it. The
//  endpoints and boot values live in the same NVS namespace ("ep") with the
//  same keys, so values set under the UDP firmware carry over.
//
//  The chips sit on the shared bus (GPIO1/2) with the MLX90640 and the
//  button pad, so every access takes i2cMutex. The PCA9685 is driven with
//  raw register writes rather than Adafruit_PWMServoDriver: the library's
//  writeMicroseconds() reads the prescaler back on every call (64 bus
//  transactions per update), where one auto-increment burst per chip does
//  all 16 channels in ~1.5 ms — short enough to fit between thermal reads.
// ─────────────────────────────────────────────────────────────
#define SERVO_ENABLE   1
#if SERVO_ENABLE
#define NUM_SERVOS     32
#define SERVO_FREQ     50
#define SERVO_OSC_HZ   27000000UL               // as the UDP sketch calibrates it
#define SERVO_UPDATE_MS 20                      // one pulse period; faster is pointless
#define SERVO_REFRESH_MS 1000                   // full rewrite even when unchanged
#define SERVO_PROBE_MS 2000                     // re-look for an absent chip
static const uint8_t kPcaAddr[2] = { 0x40, 0x41 };

struct ChannelConfig {
  int16_t epMin = 600;
  int16_t epMid = 1500;
  int16_t epMax = 2400;
  //  Value (0-255) this channel holds from power-up until commanded. 127 ->
  //  epMid (~1500 us neutral), which a bidirectional ESC needs to arm. Set 0
  //  for a plain servo or a unidirectional ESC that arms on low throttle.
  int16_t bootVal = 127;
};
static ChannelConfig    chCfg[NUM_SERVOS];
static volatile uint8_t servoVal[NUM_SERVOS];
static volatile bool    servoDirty = false;
static bool             pcaOk[2]   = { false, false };

//  0-255 through the channel's endpoints -> microseconds (UDP sketch maths).
uint32_t applyEndpoints(int val, int ch) {
  int16_t lo = chCfg[ch].epMin, md = chCfg[ch].epMid, hi = chCfg[ch].epMax;
  long us = (val <= 127) ? (long)lo + (long)(md - lo) * val / 127
                         : (long)md + (long)(hi - md) * (val - 127) / 128;
  if (us < 500)  us = 500;
  if (us > 2500) us = 2500;
  return (uint32_t)us;
}

//  Prescale as Adafruit computes it (131 at 27 MHz / 50 Hz), and the tick
//  length that follows from it, so pulse widths match the UDP firmware.
static uint8_t servoPrescale() {
  return (uint8_t)(SERVO_OSC_HZ / (4096.0f * SERVO_FREQ) + 0.5f - 1.0f);
}
static uint16_t servoTicks(uint32_t us) {
  uint32_t div = 1000000UL * (servoPrescale() + 1UL);
  return (uint16_t)((us * (uint64_t)SERVO_OSC_HZ + div / 2) / div);
}

static bool pcaWrite8(uint8_t addr, uint8_t reg, uint8_t v) {
  Wire.beginTransmission(addr);
  Wire.write(reg); Wire.write(v);
  return Wire.endTransmission() == 0;
}

//  Probe and configure one chip. Caller holds i2cMutex.
static bool pcaInit(uint8_t chip) {
  uint8_t a = kPcaAddr[chip];
  Wire.beginTransmission(a);
  if (Wire.endTransmission() != 0) return false;
  bool ok = pcaWrite8(a, 0x00, 0x10)                    // MODE1: sleep (prescale is only writable asleep)
         && pcaWrite8(a, 0xFE, servoPrescale())         // PRE_SCALE
         && pcaWrite8(a, 0x01, 0x04)                    // MODE2: totem-pole outputs
         && pcaWrite8(a, 0x00, 0x20);                   // MODE1: wake, register auto-increment
  delayMicroseconds(600);                               // oscillator settle (500 us min)
  return ok && pcaWrite8(a, 0x00, 0xA0);                // + RESTART
}

//  All 16 channels of one chip in a single auto-increment burst from LED0.
//  Caller holds i2cMutex.
static bool pcaWriteAll(uint8_t chip) {
  Wire.beginTransmission(kPcaAddr[chip]);
  Wire.write(0x06);                                     // LED0_ON_L
  for (int i = 0; i < 16; i++) {
    int ch = chip * 16 + i;
    uint16_t off = servoTicks(applyEndpoints(servoVal[ch], ch));
    Wire.write(0); Wire.write(0);                       // ON at tick 0
    Wire.write(off & 0xFF); Wire.write(off >> 8);       // OFF after the pulse
  }
  return Wire.endTransmission() == 0;
}

void loadChannelConfigs() {
  prefs.begin("ep", true);
  for (int i = 0; i < NUM_SERVOS; i++) {
    char kl[6], km[6], kh[6], kb[6];
    snprintf(kl, sizeof(kl), "e%dl", i);
    snprintf(km, sizeof(km), "e%dm", i);
    snprintf(kh, sizeof(kh), "e%dh", i);
    snprintf(kb, sizeof(kb), "e%db", i);
    chCfg[i].epMin = prefs.getShort(kl, 600);
    chCfg[i].epMid = prefs.getShort(km, 1500);
    chCfg[i].epMax = prefs.getShort(kh, 2400);
    int16_t bv = prefs.getShort(kb, 127);   // temp: constrain() is multi-eval
    chCfg[i].bootVal = constrain(bv, 0, 255);
  }
  prefs.end();
}

void saveChannelConfig(int ch) {
  prefs.begin("ep", false);
  char kl[6], km[6], kh[6], kb[6];
  snprintf(kl, sizeof(kl), "e%dl", ch);
  snprintf(km, sizeof(km), "e%dm", ch);
  snprintf(kh, sizeof(kh), "e%dh", ch);
  snprintf(kb, sizeof(kb), "e%db", ch);
  prefs.putShort(kl, chCfg[ch].epMin);
  prefs.putShort(km, chCfg[ch].epMid);
  prefs.putShort(kh, chCfg[ch].epMax);
  prefs.putShort(kb, chCfg[ch].bootVal);
  prefs.end();
}

//  Command one channel (0-based). Anything that drives servos calls this;
//  the actual bus write happens in servoService().
void servoSet(int ch, int val) {
  if (ch < 0 || ch >= NUM_SERVOS) return;
  servoVal[ch] = (uint8_t)constrain(val, 0, 255);
  servoDirty = true;
}

//  setup(): load endpoints, seed every channel with its boot value, bring
//  both chips up and put the boot pulses out straight away.
void servoBegin() {
  loadChannelConfigs();
  for (int i = 0; i < NUM_SERVOS; i++) servoVal[i] = (uint8_t)chCfg[i].bootVal;
  xSemaphoreTake(i2cMutex, portMAX_DELAY);
  for (uint8_t c = 0; c < 2; c++) {
    pcaOk[c] = pcaInit(c);
    if (pcaOk[c]) pcaOk[c] = pcaWriteAll(c);
  }
  xSemaphoreGive(i2cMutex);
  for (uint8_t c = 0; c < 2; c++)
    Serial.printf("PCA9685 0x%02X (servos %d-%d) %s\n", kPcaAddr[c],
                  c * 16 + 1, c * 16 + 16, pcaOk[c] ? "ready, boot PWM out" : "NOT FOUND");
}

//  loop(): push changes out at most once per pulse period, rewrite
//  everything once a second anyway (recovers a chip that browned out), and
//  keep looking for a chip that is missing. Never blocks on the bus — if the
//  thermal reader has it, the write simply goes out on a later pass.
void servoService() {
  static uint32_t lastWrite = 0, lastFull = 0, lastProbe = 0;
  uint32_t now = millis();
  bool full  = (now - lastFull)  >= SERVO_REFRESH_MS;
  bool probe = (!pcaOk[0] || !pcaOk[1]) && (now - lastProbe) >= SERVO_PROBE_MS;
  if (!full && !probe && !(servoDirty && (now - lastWrite) >= SERVO_UPDATE_MS)) return;
  if (xSemaphoreTake(i2cMutex, pdMS_TO_TICKS(5)) != pdTRUE) return;

  if (probe) {
    lastProbe = now;
    for (uint8_t c = 0; c < 2; c++)
      if (!pcaOk[c] && pcaInit(c)) {
        pcaOk[c] = true;
        Serial.printf("PCA9685 0x%02X found\n", kPcaAddr[c]);
      }
  }
  servoDirty = false;                       // cleared BEFORE the write, so a
  for (uint8_t c = 0; c < 2; c++) {         // servoSet() racing it re-arms it
    if (!pcaOk[c]) continue;
    uint32_t t0 = micros();
    bool ok = pcaWriteAll(c);
    uint32_t dt = micros() - t0;
    if (dt > i2cMaxUsPca) i2cMaxUsPca = dt;
    if (!ok) {
      pcaOk[c] = false;                     // no ACK: unplugged, go probe
      i2cNoteFail(c ? "PCA9685 0x41" : "PCA9685 0x40", i2cErrPca);
      Serial.printf("PCA9685 0x%02X lost\n", kPcaAddr[c]);
    }
  }
  xSemaphoreGive(i2cMutex);
  lastWrite = now;
  if (full) lastFull = now;
}
#endif  // SERVO_ENABLE

// ─────────────────────────────────────────────────────────────
//  Wi-Fi web servo control — the same page, network setup and HTTP API
//  as 32_Servo_Controller_OV5640_UDP, so the same browser page (and any
//  app that calls /servo) drives this board unchanged.
//
//    AP mode (default): network "32_SC", password 12345678, open
//      http://192.168.4.1/ (a captive-portal DNS sends any URL there).
//    STA mode: pick a network on the page's WiFi setup screen; the board
//      reboots, joins it, and serves on its DHCP address and
//      http://32servo.local/. Falls back to AP if it cannot connect.
//    Credentials/mode use the UDP sketch's NVS namespace ("wifi"), and the
//    page's saved layout its "webcfg" — both carry over between firmwares.
//
//  Feeds: the page's LIVE FEED panel shows this board's camera (JPEGs from
//  /capture, grabbed by loop() while the page polls), and a THERMAL panel
//  added to web_page.h beside it draws the MLX90640 grid from /thermal.
//  Camera *settings* (/set) are accepted and ignored — the camera stays at
//  the LCD's QVGA RGB565 setup, which the LCD views depend on.
//
//  The server runs in its own task on core 0. /servo only calls servoSet(),
//  so a request never touches the I2C bus — servoService() in loop() does.
// ─────────────────────────────────────────────────────────────
#define WEB_ENABLE     1
#if WEB_ENABLE && SERVO_ENABLE
#include <WebServer.h>
#include <DNSServer.h>
#include <ESPmDNS.h>
#include "web_page.h"

#define AP_SSID        "32_SC"
#define AP_PASSWORD    "12345678"
#define AP_IP          IPAddress(192, 168, 4, 1)
#define WEB_TASK_STACK 8192
#define WEB_TASK_CORE  0

static WebServer server(80);
static DNSServer dns;
static volatile bool webApMode  = true;
static volatile bool webRunning = false;   // radio owned by the web server
//  Set by the device's JOIN NETWORK once the new network has accepted the
//  password: the web task then drops the hotspot and its captive portal and
//  carries on as a joined controller, with no restart (see webTask).
static volatile bool webGoSta   = false;
//  The reverse, set by Settings > WIFI > USE HOTSPOT / FORGET: leave the
//  joined network and bring the 32_SC hotspot back, live.
static volatile bool webGoAp    = false;

//  ── servo + endpoint API (identical to the UDP sketch) ──
void handleServo() {
  if (!server.hasArg("num") || !server.hasArg("val")) {
    server.send(400, "text/plain", "Bad Request");
    return;
  }
  int num = server.arg("num").toInt();
  int val = constrain(server.arg("val").toInt(), 0, 255);
  if (num >= 0 && num < NUM_SERVOS) servoSet(num, val);
  server.send(200, "text/plain", "OK");
}

void handleGetEndpoints() {
  String json = "[";
  for (int i = 0; i < NUM_SERVOS; i++) {
    if (i > 0) json += ",";
    json += "{\"ch\":" + String(i) +
            ",\"min\":" + String(chCfg[i].epMin) +
            ",\"mid\":" + String(chCfg[i].epMid) +
            ",\"max\":" + String(chCfg[i].epMax) +
            ",\"boot\":" + String(chCfg[i].bootVal) + "}";
  }
  json += "]";
  server.send(200, "application/json", json);
}

void handleSetEndpoint() {
  if (!server.hasArg("num") || !server.hasArg("min") ||
      !server.hasArg("mid") || !server.hasArg("max")) {
    server.send(400, "text/plain", "Bad Request");
    return;
  }
  int ch = server.arg("num").toInt();
  if (ch < 0 || ch >= NUM_SERVOS) { server.send(400, "text/plain", "Bad channel"); return; }
  int mn = server.arg("min").toInt(), md = server.arg("mid").toInt(),
      mx = server.arg("max").toInt();
  chCfg[ch].epMin = (int16_t)constrain(mn, 500, 2500);
  chCfg[ch].epMid = (int16_t)constrain(md, 500, 2500);
  chCfg[ch].epMax = (int16_t)constrain(mx, 500, 2500);
  //  Optional: the endpoint sliders POST min/mid/max only and must not
  //  clobber the boot value.
  if (server.hasArg("boot")) {
    int bv = server.arg("boot").toInt();
    chCfg[ch].bootVal = (int16_t)constrain(bv, 0, 255);
  }
  saveChannelConfig(ch);
  servoDirty = true;                        // re-map the live value now
  Serial.printf("Ch %2d endpoints: min=%d mid=%d max=%d boot=%d\n", ch + 1,
                chCfg[ch].epMin, chCfg[ch].epMid, chCfg[ch].epMax, chCfg[ch].bootVal);
  server.send(200, "text/plain", "OK");
}

//  ── page layout blob (mappings etc.) — opaque JSON the page owns ──
void handleLoadCfg() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  prefs.begin("webcfg", true);
  String s = prefs.getString("cfg", "{}");
  prefs.end();
  server.send(200, "application/json", s);
}
void handleSaveCfg() {
  String body = server.hasArg("cfg")   ? server.arg("cfg")
              : server.hasArg("plain") ? server.arg("plain") : "";
  if (body.length() == 0) { server.send(400, "text/plain", "No body"); return; }
  prefs.begin("webcfg", false);
  prefs.putString("cfg", body);
  prefs.end();
  server.send(200, "text/plain", "OK");
}

//  ── camera feed ──
//  The page's own preview loop polls /capture at ~6 fps once /camstatus
//  says a camera is there. Each request keeps loop() producing frames (see
//  webCamDue); the first one after idle may wait for the camera to start.
void handleCamStatus() {
  //  Not started yet counts as available — the first /capture starts it.
  bool ok = camWebState() != 2;
  server.send(200, "application/json",
              ok ? "{\"available\":true,\"sensor\":\"OV5640 QVGA\",\"res\":\"QVGA\"}"
                 : "{\"available\":false}");
}
void handleCapture() {
  webCamReqMs = millis();
  if (camWebState() == 2) { server.send(503, "text/plain", "No camera"); return; }
  //  Wait for a fresh frame: up to 1.5 s covers the camera's cold start.
  uint32_t t0 = millis();
  while ((!webJpg || millis() - webJpgMs > 1000) && millis() - t0 < 1500)
    vTaskDelay(pdMS_TO_TICKS(10));
  if (xSemaphoreTake(webJpgMux, pdMS_TO_TICKS(200)) != pdTRUE) {
    server.send(503, "text/plain", "Busy");
    return;
  }
  if (!webJpg) {
    xSemaphoreGive(webJpgMux);
    server.send(503, "text/plain", "No frame");
    return;
  }
  //  Sent while holding the mutex, so loop() cannot free it mid-send; it
  //  just skips publishing for the few ms this takes.
  server.sendHeader("Cache-Control", "no-store");
  server.setContentLength(webJpgLen);
  server.send(200, "image/jpeg", "");
  server.sendContent((const char*)webJpg, webJpgLen);
  xSemaphoreGive(webJpgMux);
}

//  ── thermal feed ──
//  The raw 32x24 grid, not an image: ~3 KB of JSON the page colours and
//  scales itself. Temperatures are tenths of a degree in the LCD's unit
//  (C or F), already flipped the way the LCD shows them.
void handleThermal() {
  webThermReqMs = millis();
#if MLX_ENABLE
  if (!mlxAlive()) {
    const char* st = !mlxReady ? "none" : (mlxReadIdx > 1) ? "starting" : "stalled";
    server.send(200, "application/json", String("{\"ok\":false,\"state\":\"") + st + "\"}");
    return;
  }
  const float* f = mlxBuf[mlxReadIdx & 1];
  char u = tunit();
  String s;
  s.reserve(4300);
  s += "{\"ok\":true,\"w\":32,\"h\":24,\"unit\":\""; s += u;
  s += "\",\"max\":";    s += String(tconv(mlxMax), 1);
  s += ",\"min\":";      s += String(tconv(mlxMin), 1);
  s += ",\"centre\":";   s += String(tconv(mlxCentre), 1);
  s += ",\"ambient\":";  s += String(tconv(mlxTa), 1);
  //  Where the thermal cone sits in the camera frame, for the page's
  //  ENHANCED overlay — the LCD fusion rectangle ("fus" console command),
  //  moved from its 320x172 crop into the full 320x240 frame /capture sends.
  s += ",\"fus\":[";     s += fusX; s += ','; s += fusY + (CAM_H - TFT_H) / 2;
  s += ',';              s += fusW; s += ','; s += fusH; s += ']';
  s += ",\"d\":[";
  for (int y = 0; y < THERM_H; y++) {
    const float* row = f + (thermFlipV ? (THERM_H - 1 - y) : y) * THERM_W;
    for (int x = 0; x < THERM_W; x++) {
      if (x || y) s += ',';
      s += (int)lroundf(tconv(row[thermFlipH ? (THERM_W - 1 - x) : x]) * 10.0f);
    }
  }
  s += "]}";
  server.sendHeader("Cache-Control", "no-store");
  server.send(200, "application/json", s);
#else
  server.send(200, "application/json", "{\"ok\":false,\"state\":\"disabled\"}");
#endif
}

//  ── telemetry stubs: keep the page happy, do nothing ──
void handleStats()     { server.send(200, "application/json", "{\"fps\":0,\"kbps\":0}"); }
void handleSyslog()    { server.send(200, "application/json", "{\"msgs\":[],\"total\":0}"); }
void handleCtrlCfg() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", "{\"lcdflip\":false}");
}
void handleSet()       { server.send(200, "text/plain", "OK"); }   // camera is fixed at LCD settings

//  ── network setup (identical behaviour to the UDP sketch) ──
void handleMainPage()  { server.send_P(200, "text/html", CAMERA_HTML); }
void handleWifiSetup() { server.send_P(200, "text/html", SETUP_HTML); }

void handleScan() {
  int n = WiFi.scanNetworks(false, false, false, 200);
  String json = "[";
  for (int i = 0; i < n; i++) {
    if (i) json += ",";
    json += "{\"ssid\":\"" + WiFi.SSID(i) + "\",\"rssi\":" + WiFi.RSSI(i) +
            ",\"secure\":" + (WiFi.encryptionType(i) != WIFI_AUTH_OPEN ? "true" : "false") + "}";
  }
  json += "]";
  WiFi.scanDelete();
  server.send(200, "application/json", json);
}

void handleSave() {
  if (!server.hasArg("ssid") || server.arg("ssid").isEmpty()) {
    server.send(400, "text/plain", "Missing SSID");
    return;
  }
  prefs.begin("wifi", false);
  prefs.putString("ssid",    server.arg("ssid"));
  prefs.putString("pass",    server.hasArg("pass") ? server.arg("pass") : "");
  prefs.putString("netmode", "sta");
  prefs.end();
  Serial.printf("Credentials saved for: %s - rebooting into STA mode.\n", server.arg("ssid").c_str());
  server.send(200, "text/plain", "Saved! Switching to infrastructure mode...");
  delay(1200);
  ESP.restart();
}

void handleSetAP() {
  prefs.begin("wifi", false);
  prefs.putString("netmode", "ap");
  prefs.end();
  server.send(200, "text/plain", "Switching to Access Point mode...");
  delay(1200);
  ESP.restart();
}

void handleForget() {
  prefs.begin("wifi", false);
  prefs.clear();
  prefs.end();
  server.send(200, "text/plain", "Credentials cleared - rebooting into setup mode");
  delay(1500);
  ESP.restart();
}

//  Tell each OS the network "has internet" so it does not pop a captive
//  portal sheet over the controller, and send stray URLs to the page.
void handleNCSI_Windows()  { server.send(200, "text/plain", "Microsoft Connect Test"); }
void handleNCSI_Windows2() { server.send(200, "text/plain", "Microsoft NCSI"); }
void handleGenerate204()   { server.send(204, "text/plain", ""); }
void handleHotspotDetect() {
  server.send(200, "text/html",
    "<HTML><HEAD><TITLE>Success</TITLE></HEAD><BODY>Success</BODY></HTML>");
}
void handleCaptivePortal() {
  server.sendHeader("Location", "http://192.168.4.1/", true);
  server.send(302, "text/html",
    "<!DOCTYPE html><html><head>"
    "<meta http-equiv='refresh' content='0;url=http://192.168.4.1/'>"
    "</head><body><a href='http://192.168.4.1/'>Open Controller</a></body></html>");
}

static void webRoutes() {
  server.on("/",           HTTP_GET,  handleMainPage);
  server.on("/wifi-setup", HTTP_GET,  handleWifiSetup);
  server.on("/scan",       HTTP_GET,  handleScan);
  server.on("/save",       HTTP_POST, handleSave);
  server.on("/setap",      HTTP_GET,  handleSetAP);
  server.on("/forget",     HTTP_GET,  handleForget);
  server.on("/servo",      HTTP_GET,  handleServo);
  server.on("/endpoints",  HTTP_GET,  handleGetEndpoints);
  server.on("/endpoint",   HTTP_POST, handleSetEndpoint);
  server.on("/loadcfg",    HTTP_GET,  handleLoadCfg);
  server.on("/savecfg",    HTTP_POST, handleSaveCfg);
  server.on("/ctrlcfg",    HTTP_GET,  handleCtrlCfg);
  server.on("/camstatus",  HTTP_GET,  handleCamStatus);
  server.on("/stats",      HTTP_GET,  handleStats);
  server.on("/syslog",     HTTP_GET,  handleSyslog);
  server.on("/set",        HTTP_GET,  handleSet);
  server.on("/capture",    HTTP_GET,  handleCapture);
  server.on("/thermal",    HTTP_GET,  handleThermal);
}

static void startAPMode() {
  webApMode = true;
  //  AP+STA rather than plain AP: the STA side sits idle but lets the
  //  WIFI SCAN view keep scanning without tearing the access point down.
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(AP_IP, AP_IP, IPAddress(255, 255, 255, 0));
  strlen(AP_PASSWORD) > 0 ? WiFi.softAP(AP_SSID, AP_PASSWORD) : WiFi.softAP(AP_SSID);
  if (!btActive) WiFi.setSleep(false);      // modem sleep adds latency; must stay on once BT is up
  Serial.printf("AP started - SSID \"%s\" pass \"%s\" -> http://192.168.4.1/\n",
                AP_SSID, AP_PASSWORD);
  dns.start(53, "*", AP_IP);
  webRoutes();
  server.on("/generate_204",              handleGenerate204);
  server.on("/connecttest.txt",           handleNCSI_Windows);
  server.on("/ncsi.txt",                  handleNCSI_Windows2);
  server.on("/hotspot-detect.html",       handleHotspotDetect);
  server.on("/library/test/success.html", handleHotspotDetect);
  server.on("/fwlink",                    handleCaptivePortal);
  server.on("/redirect",                  handleCaptivePortal);
  server.onNotFound(handleCaptivePortal);
}

static bool startSTAMode(const String& ssid, const String& pass) {
  webApMode = false;
  WiFi.mode(WIFI_STA);
  if (!btActive) WiFi.setSleep(false);      // see startAPMode
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.printf("WiFi: connecting to \"%s\"", ssid.c_str());
  for (uint8_t t = 0; WiFi.status() != WL_CONNECTED && t < 40; t++) {
    vTaskDelay(pdMS_TO_TICKS(500));         // web task: the rest of the board runs on
    Serial.print('.');
  }
  Serial.println();
  if (WiFi.status() != WL_CONNECTED) { Serial.println("WiFi: connection failed"); return false; }
  Serial.printf("WiFi: connected - http://%s/  RSSI %d dBm\n",
                WiFi.localIP().toString().c_str(), WiFi.RSSI());
  webRoutes();
  server.onNotFound([]() { server.send(404, "text/plain", "Not found"); });
  return true;
}

static void webTask(void*) {
  prefs.begin("wifi", true);
  String ssid = prefs.getString("ssid", ""), pass = prefs.getString("pass", "");
  String mode = prefs.getString("netmode", "ap");
  prefs.end();

  webRunning = true;                        // from here the radio is ours
  if (!(mode == "sta" && ssid.length() > 0 && startSTAMode(ssid, pass))) {
    if (mode == "sta") { WiFi.disconnect(true); Serial.println("WiFi: falling back to AP"); }
    startAPMode();
  }
  server.begin();
  if (MDNS.begin("32servo")) MDNS.addService("http", "tcp", 80);
  Serial.println("Web servo control on port 80 (also http://32servo.local/)");

  for (;;) {
    //  Live switch hotspot -> joined network (device menu, after a tested
    //  join). Done here because this task owns the server, DNS and mDNS.
    //  The server itself needs nothing: it already answers on the STA
    //  address. What a reboot used to change is exactly these steps.
    if (webGoSta) {
      webGoSta = false;
      if (webApMode) {
        webApMode = false;                  // stop feeding the captive DNS first
        dns.stop();
        server.onNotFound([]() { server.send(404, "text/plain", "Not found"); });
        WiFi.softAPdisconnect(true);        // AP+STA -> STA, as a joined boot has
      }
      MDNS.end();                           // re-announce on the new network
      if (MDNS.begin("32servo")) MDNS.addService("http", "tcp", 80);
      Serial.printf("Web servo control now at http://%s/ (and 32servo.local)\n",
                    WiFi.localIP().toString().c_str());
    }
    //  Live switch joined network -> hotspot: the same state startAPMode()
    //  sets up at boot, minus the routes, which are already registered.
    if (webGoAp) {
      webGoAp = false;
      if (!webApMode) {
        //  Leave the network, keep the radio, and wipe the driver's own copy
        //  of it so nothing auto-reconnects. Our "wifi" prefs are what pick
        //  the mode, and USE HOTSPOT keeps the network there for later.
        WiFi.disconnect(false, true);
        WiFi.mode(WIFI_AP_STA);
        WiFi.softAPConfig(AP_IP, AP_IP, IPAddress(255, 255, 255, 0));
        strlen(AP_PASSWORD) > 0 ? WiFi.softAP(AP_SSID, AP_PASSWORD) : WiFi.softAP(AP_SSID);
        dns.start(53, "*", AP_IP);
        server.onNotFound(handleCaptivePortal);
        webApMode = true;                   // start feeding the captive DNS
        MDNS.end();
        if (MDNS.begin("32servo")) MDNS.addService("http", "tcp", 80);
        Serial.printf("Back on hotspot \"%s\" -> http://192.168.4.1/\n", AP_SSID);
      }
    }
    if (webApMode) dns.processNextRequest();
    server.handleClient();
    vTaskDelay(1);
  }
}

void webBegin() {
  webJpgMux = xSemaphoreCreateMutex();      // before the server can take a request
  xTaskCreatePinnedToCore(webTask, "web", WEB_TASK_STACK, nullptr, 1, nullptr, WEB_TASK_CORE);
}
#endif  // WEB_ENABLE && SERVO_ENABLE

// ─────────────────────────────────────────────────────────────
//  Serial console — interactive read/write testing while running
// ─────────────────────────────────────────────────────────────
void sdConsoleHelp() {
  Serial.println(F("commands:"));
  Serial.println(F("  help                 this list"));
  Serial.println(F("  info                 card type / size / free"));
  Serial.println(F("  test                 run the full self-test"));
  Serial.println(F("  bench                write+read throughput"));
  Serial.println(F("  ls [dir]             list (default /)"));
  Serial.println(F("  cat <file>           dump text (first 2KB)"));
  Serial.println(F("  write <file> <text>  overwrite"));
  Serial.println(F("  append <file> <text> append + newline"));
  Serial.println(F("  rm <file>            delete"));
  Serial.println(F("  mkdir <dir>          create dir"));
  Serial.println(F("  rmdir <dir>          remove empty dir"));
  Serial.println(F("  log on|off           BNO085 CSV logging"));
  Serial.println(F("  bl <0-255>|on|off    backlight brightness"));
  Serial.println(F("  bldemo               sweep 90%..10%, then full"));
  Serial.println(F("  idle <sec>|off       dim the panel when left alone"));
  Serial.println(F("  log on|off           CSV sweep logging"));
  Serial.println(F("  view menu|cam|ir|cube|compass|files|wifi|fusion  pick a screen"));
#if MLX_ENABLE
  Serial.println(F("  fus [x|y|w|h <n>]|reset   align the IR fusion overlay"));
#endif
  Serial.println(F("  mlx                  MLX90640 status"));
  Serial.println(F("  bno                  probe the BNO085 line (why rx=0)"));
  Serial.println(F("  imurot [0|90|180|270]  BNO085 turned CCW on this board (v6 = 270)"));
  Serial.println(F("  resets               uptime + why the last few boots happened"));
  Serial.println(F("  units c|f            temperature display units"));
#if VIDEO_ENABLE
  Serial.println(F("  play [file]          play an RDMJ video (default "
                   VIDEO_DEFAULT_FILE ")"));
  Serial.println(F("  stop                 stop playback"));
  Serial.println(F("  vloop on|off         repeat when it reaches the end"));
#endif
  Serial.println(F("  madctl <hex>         panel orientation, live (28 68 A8 E8)"));
  Serial.println(F("  cube [reset]         where the cube's UP face points; reset re-aims it"));
#if SERVO_ENABLE
  Serial.println(F("  servo [<1-32|all> <0-255>]  show / set servo outputs"));
  Serial.println(F("  servo boot           all servos back to their boot values"));
  Serial.println(F("  ep <1-32> [min mid max [boot]]  show / save endpoints (us)"));
  Serial.println(F("  seq [ls|play <n|file>|stop]  SD sequence playback"));
  Serial.println(F("  i2c [hz <n>|reset|lines]  scan bus, error counts; set speed; check/free SDA+SCL"));
  Serial.println(F("  gps [sky]            GNSS receiver status; sky: satellites + signal strength"));
#endif
#if GAS_ENABLE
  Serial.println(F("  gas [frc <ppm>|asc on|off]  SCD40 CO2 sensor; frc = recalibrate (~420 outdoors)"));
#endif
#if AIR_ENABLE
  Serial.println(F("  air [help|clean|heat|asc|frc|alt|hpa|toff|voc|nox|clear|reset]  SEN69C air quality"));
#endif
#if AUDIO_ENABLE
  Serial.println(F("  music [ls|play [n]|pause|next|stop|vol 0-20]  MP3/WAV player (/MUSIC)"));
  Serial.println(F("  rec [start|stop|play|gain 0-48]  sound recorder (/REC/RECnnn.WAV)"));
  Serial.println(F("  audio [drive 0-3]    I2S amp + mic status / pin drive strength"));
#endif
  Serial.println(F("  mount | unmount      re-init / release card"));
}

// Splits "cmd rest..." — returns rest (may be empty, never null).
static char* splitArg(char* s) {
  char* sp = strchr(s, ' ');
  if (!sp) return s + strlen(s);
  *sp = '\0';
  while (*++sp == ' ') {}
  return sp;
}

void sdConsoleExec(char* line) {
  while (*line == ' ') line++;
  if (!*line) return;
  uiNoteActivity();                // typing at the console is interaction
  char* arg = splitArg(line);

  if (!strcmp(line, "help") || !strcmp(line, "?")) { sdConsoleHelp(); return; }
  if (!strcmp(line, "info"))    { logClear(); sdShowInfo(); return; }
  if (!strcmp(line, "test"))    { logClear(); sdSelfTest(); return; }
  if (!strcmp(line, "bench"))   { logClear(); sdBench();   return; }
  if (!strcmp(line, "mount"))   { logClear(); sdStep("mount", sdMount()); return; }
  if (!strcmp(line, "unmount")) { sdUnmount(); logLine(DIM, "SD released"); return; }

  if (!strcmp(line, "bldemo")) {
    blDemoStart();
    logLine(NEON_CYAN, "backlight sweep 90%%..10%%, then full");
    return;
  }
  if (!strcmp(line, "bl")) {
    blDemoActive = false;          // a manual level cancels the sweep
    if (!strcmp(arg, "on"))        blSetActive(BL_DEFAULT);
    else if (!strcmp(arg, "off"))  blSetActive(0);
    else if (*arg)                 blSetActive((uint8_t)atoi(arg));
    logLine(NEON_CYAN, "backlight %u/255%s", blLevel,
            (PIN_BL < 0) ? "  (BLK hard-wired, no pin)" : "");
    return;
  }
  if (!strcmp(line, "log")) {
    if (!strcmp(arg, "on")) {
      if (!sdMounted) logLine(NEON_RED, "no card - mount first");
      else imuLogging = true;
    } else if (!strcmp(arg, "off")) {
      imuLogging = false;
      imuLogClose();               // land what is buffered right now
    }
    logLine(NEON_CYAN, "log %s  %lu rows -> %s", imuLogging ? "ON" : "OFF",
            (unsigned long)imuLogRows, IMU_LOG_FILE);
    return;
  }
#if VIDEO_ENABLE
  if (!strcmp(line, "play")) {
    logClear();
    vidPlay(*arg ? arg : VIDEO_DEFAULT_FILE);
    return;
  }
  if (!strcmp(line, "stop")) {
    if (vidPlaying) vidStop();
    else            logLine(DIM, "not playing");
    return;
  }
  if (!strcmp(line, "vloop")) {
    if (!strcmp(arg, "on"))       vidLoop = true;
    else if (!strcmp(arg, "off")) vidLoop = false;
    logLine(NEON_CYAN, "video loop %s", vidLoop ? "ON" : "OFF");
    return;
  }
#endif
  if (!strcmp(line, "idle")) {
    if (!strcmp(arg, "off"))  idleTimeoutMs = 0;
    else if (*arg)            idleTimeoutMs = (uint32_t)atoi(arg) * 1000UL;
    if (idleTimeoutMs) {
      logLine(NEON_CYAN, "idle dim after %lus, to %u/255",
              (unsigned long)(idleTimeoutMs / 1000), BL_IDLE_LEVEL);
    } else {
      logLine(NEON_CYAN, "idle dimming OFF");
    }
    return;
  }
  if (!strcmp(line, "units")) {
    if (!strcmp(arg, "f"))      tempF = true;
    else if (!strcmp(arg, "c")) tempF = false;
    else if (*arg) { Serial.println(F("units c|f")); return; }
    logLine(NEON_CYAN, "temperatures in %c", tunit());
    return;
  }
  if (!strcmp(line, "madctl")) {
    if (!*arg) {
      logLine(NEON_CYAN, "madctl <hex> - landscape: 28 68 A8 E8");
      logLine(DIM, "compile default 0x%02X. clear bit 08 for RGB.", PANEL_MADCTL);
      return;
    }
    uint8_t v = (uint8_t)strtol(arg, nullptr, 16);
    tft.setMadctl(v);
    tft.fillScreen(BLACK);          // panes repaint themselves on the next pass
    logLine(NEON_CYAN, "MADCTL 0x%02X (default 0x%02X)", v, PANEL_MADCTL);
    logLine(DIM, "bake the keeper into PANEL_MADCTL");
    return;
  }
#if MLX_ENABLE
  if (!strcmp(line, "fus")) {
    char* val = splitArg(arg);
    int   n   = atoi(val);
    if      (!strcmp(arg, "x")) fusX = n;
    else if (!strcmp(arg, "y")) fusY = n;
    else if (!strcmp(arg, "w")) fusW = (n > 1) ? n : 1;
    else if (!strcmp(arg, "h")) fusH = (n > 1) ? n : 1;
    else if (!strcmp(arg, "reset")) {
      fusX = FUS_X_DEF; fusY = FUS_Y_DEF; fusW = FUS_W_DEF; fusH = FUS_H_DEF;
    } else if (*arg) { Serial.println(F("fus x|y|w|h <n> | reset")); return; }
    logLine(NEON_CYAN, "fus X%d Y%d W%d H%d", fusX, fusY, fusW, fusH);
    return;
  }
#endif
#if SERVO_ENABLE
  //  servo                 list all 32 values
  //  servo <1-32> <0-255>  set one channel
  //  servo all <0-255>     set every channel
  //  servo boot            put every channel back to its boot value
  if (!strcmp(line, "servo")) {
    char* val = splitArg(arg);
    if (!*arg) {
      Serial.printf("PCA 0x40 %s  0x41 %s\n", pcaOk[0] ? "ok" : "MISSING",
                    pcaOk[1] ? "ok" : "MISSING");
      for (int i = 0; i < NUM_SERVOS; i++)
        Serial.printf("%2d:%3u%s", i + 1, servoVal[i], (i % 8 == 7) ? "\n" : "  ");
      return;
    }
    if (!strcmp(arg, "boot")) {
      for (int i = 0; i < NUM_SERVOS; i++) servoSet(i, chCfg[i].bootVal);
      logLine(NEON_CYAN, "servos -> boot values");
      return;
    }
    if (!*val) { Serial.println(F("servo <1-32|all> <0-255> | servo boot")); return; }
    int v = constrain(atoi(val), 0, 255);
    if (!strcmp(arg, "all")) {
      for (int i = 0; i < NUM_SERVOS; i++) servoSet(i, v);
      logLine(NEON_CYAN, "servo all = %d", v);
    } else {
      int ch = atoi(arg);
      if (ch < 1 || ch > NUM_SERVOS) { Serial.println(F("channel 1-32")); return; }
      servoSet(ch - 1, v);
      logLine(NEON_CYAN, "servo %d = %d (%lu us)", ch, v,
              (unsigned long)applyEndpoints(v, ch - 1));
    }
    return;
  }
  if (!strcmp(line, "seq")) { seqConsole(arg); return; }
  //  ep <1-32>                          show a channel's endpoints
  //  ep <1-32> <min> <mid> <max> [boot] set and save them (us, boot 0-255)
  if (!strcmp(line, "ep")) {
    int ch = atoi(arg);
    if (ch < 1 || ch > NUM_SERVOS) {
      Serial.println(F("ep <1-32> [<min> <mid> <max> [boot]]"));
      return;
    }
    ChannelConfig& c = chCfg[ch - 1];
    char* rest = splitArg(arg);
    if (*rest) {
      int mn = 0, md = 0, mx = 0, bv = -1;
      int n = sscanf(rest, "%d %d %d %d", &mn, &md, &mx, &bv);
      if (n < 3) { Serial.println(F("ep <ch> <min> <mid> <max> [boot]")); return; }
      c.epMin = (int16_t)constrain(mn, 500, 2500);
      c.epMid = (int16_t)constrain(md, 500, 2500);
      c.epMax = (int16_t)constrain(mx, 500, 2500);
      if (n >= 4) c.bootVal = (int16_t)constrain(bv, 0, 255);
      saveChannelConfig(ch - 1);
      servoDirty = true;                  // re-map the current value now
    }
    logLine(NEON_CYAN, "ep %d: min %d mid %d max %d boot %d", ch,
            c.epMin, c.epMid, c.epMax, c.bootVal);
    return;
  }
#endif
  if (!strcmp(line, "cube")) {
    //  Where the cube's UP face points on screen (x right, y up, z into the
    //  glass): flat face-up reads 0 0 -1, upright reads 0 1 0. "reset" re-aims.
    if (!strcmp(arg, "reset")) cubeAimHere();
    else if (*arg) { Serial.println(F("cube [reset]")); return; }
    float M[3][3];
    cubeMatrix(M);
    logLine(NEON_CYAN, "cube UP -> %+.2f %+.2f %+.2f  aim %+.2f %+.2f%s",
            -M[0][2], -M[1][2], -M[2][2], cubeFwdX, cubeFwdY,
            imuAlive() ? "" : "  (IMU silent)");
    return;
  }
  if (!strcmp(line, "bno")) { logClear(); bnoProbe(); return; }
  if (!strcmp(line, "imurot")) { imuMountConsole(arg); return; }
  if (!strcmp(line, "resets")) { resetConsole(); return; }
  if (!strcmp(line, "view")) {
    if      (!strcmp(arg, "menu"))    uiEnter(UI_MENU);
    else if (!strcmp(arg, "cam"))     uiEnter(UI_CAMERA);
    else if (!strcmp(arg, "ir"))      uiEnter(UI_THERMAL);
    else if (!strcmp(arg, "cube"))    uiEnter(UI_CUBE);
    else if (!strcmp(arg, "compass")) uiEnter(UI_COMPASS);
    else if (!strcmp(arg, "files"))   uiEnter(UI_FILES);
    else if (!strcmp(arg, "wifi"))    uiEnter(UI_WIFI);
    else if (!strcmp(arg, "fusion"))  uiEnter(UI_FUSION);
    else if (!strcmp(arg, "ble"))     uiEnter(UI_BLE);
    else if (!strcmp(arg, "gps"))     uiEnter(UI_GPS);
    else if (!strcmp(arg, "seq"))     uiEnter(UI_SEQ);
    else if (!strcmp(arg, "game"))    uiEnter(UI_GAME);
    else if (!strcmp(arg, "blocks"))  uiEnter(UI_BLOCKS);
    else if (!strcmp(arg, "tester"))  uiEnter(UI_SERVO);
    else if (!strcmp(arg, "imuservo")) uiEnter(UI_IMUSERVO);
    else if (!strcmp(arg, "tank"))    uiEnter(UI_TANK);
    else if (!strcmp(arg, "sand"))    uiEnter(UI_SAND);
    else if (!strcmp(arg, "clock"))   uiEnter(UI_CLOCK);
#if GAS_ENABLE
    else if (!strcmp(arg, "gas"))     uiEnter(UI_GAS);
#endif
#if AIR_ENABLE
    else if (!strcmp(arg, "air"))     uiEnter(UI_AIR);
#endif
#if AUDIO_ENABLE
    else if (!strcmp(arg, "music"))   uiEnter(UI_MUSIC);
    else if (!strcmp(arg, "rec"))     uiEnter(UI_RECORDER);
#endif
    else if (!strcmp(arg, "radar"))   uiEnter(UI_RADAR);
    else if (*arg) {
      Serial.println(F("view ...|wifi|fusion|ble|gps|seq|tester|imuservo|game|blocks|tank|sand|radar"));
      return;
    }
    logLine(NEON_CYAN, "view %s", kUiName[uiView]);
    return;
  }
  //  i2c            scan the shared bus + error counters + worst transfer times
  //  i2c hz <n>     set the bus speed now AND for every later boot (NVS)
  //  i2c reset      zero the counters
  if (!strcmp(line, "i2c")) {
    char* val = splitArg(arg);
    if (!strcmp(arg, "hz")) {
      uint32_t hz = strtoul(val, nullptr, 10);
      if (hz < 10000 || hz > 1000000) { Serial.println(F("i2c hz <10000..1000000>")); return; }
      i2cHz = hz;
      if (xSemaphoreTake(i2cMutex, pdMS_TO_TICKS(500)) == pdTRUE) {
        Wire.setClock(i2cHz);
        xSemaphoreGive(i2cMutex);
      }
      prefs.begin("servoctl", false); prefs.putUInt("i2chz", i2cHz); prefs.end();
      Serial.printf("I2C now %lu kHz (saved - also used from the next boot)\n",
                    (unsigned long)(i2cHz / 1000));
      return;
    }
    if (!strcmp(arg, "reset")) {
      i2cErrPcf = i2cErrPca = i2cErrGps = i2cBusyPcf = i2cMaxUsPcf = i2cMaxUsPca = 0;
      Serial.println("I2C counters cleared");
      return;
    }
    if (!strcmp(arg, "lines")) { i2cRecover(true); return; }
    if (*arg) { Serial.println(F("i2c [hz <n> | reset | lines]")); return; }

    Serial.printf("I2C bus SDA%d SCL%d @ %lu kHz - scanning...\n", MLX_SDA, MLX_SCL,
                  (unsigned long)(i2cHz / 1000));
    if (xSemaphoreTake(i2cMutex, pdMS_TO_TICKS(1000)) != pdTRUE) {
      Serial.println("  bus busy (MLX mid-frame?) - try again"); return;
    }
    int found = 0;
    for (uint8_t a = 1; a < 127; a++) {
      uint32_t t0 = micros();
      Wire.beginTransmission(a);
      uint8_t rc = Wire.endTransmission();
      uint32_t dt = micros() - t0;
      const char* nm = (a == 0x21) ? "PCF8574 buttons" : (a == 0x33) ? "MLX90640 thermal"
                     : (a == 0x40) ? "PCA9685 servos 1-16" : (a == 0x41) ? "PCA9685 servos 17-32"
                     : (a == 0x42) ? "GNSS (u-blox MAX-M10M)" : (a == 0x62) ? "SCD40 CO2 sensor"
                     : (a == 0x6B) ? "SEN69C air quality" : (a == 0x70) ? "PCA9685 all-call" : "?";
      if (rc == 0) { Serial.printf("  0x%02X  %-24s %lu us\n", a, nm, (unsigned long)dt); found++; }
      else if (rc != 2 && rc != 3)          // 2/3 = plain NACK; anything else is a bus fault
        Serial.printf("  0x%02X  BUS ERROR rc=%u after %lu us\n", a, rc, (unsigned long)dt);
      if (dt > 20000) Serial.printf("  0x%02X  probe took %lu us (bus stalled?)\n", a, (unsigned long)dt);
    }
    xSemaphoreGive(i2cMutex);
    Serial.printf("  %d device(s)\n", found);
    Serial.printf("failures: PCF %lu (bus busy %lu)  PCA %lu  GPS %lu  MLX %lu\n",
                  (unsigned long)i2cErrPcf, (unsigned long)i2cBusyPcf, (unsigned long)i2cErrPca,
                  (unsigned long)i2cErrGps,
#if MLX_ENABLE
                  (unsigned long)mlxErrs
#else
                  0UL
#endif
                  );
    Serial.printf("worst transfer: PCF %lu us  PCA %lu us\n",
                  (unsigned long)i2cMaxUsPcf, (unsigned long)i2cMaxUsPca);
    return;
  }
#if GAS_ENABLE
  if (!strcmp(line, "gas")) { gasConsole(arg); return; }
#endif
#if AIR_ENABLE
  if (!strcmp(line, "air")) { airConsole(arg); return; }
#endif
#if AUDIO_ENABLE
  if (!strcmp(line, "music") || !strcmp(line, "rec") || !strcmp(line, "audio")) { audioConsole(line, arg); return; }
#endif
#if GPS_ENABLE
  if (!strcmp(line, "gps")) { if (!strcmp(arg, "sky")) gpsSkyReport(); else gpsReport(); return; }
  if (!strcmp(line, "tank")) { tankConsole(arg); return; }
  if (!strcmp(line, "axes")) { imuAxesConsole(arg); return; }
  if (!strcmp(line, "doom")) { doomConsole(arg); return; }
  if (!strcmp(line, "radar")) { radarConsole(arg); return; }
#if GPS_ENABLE
  if (!strcmp(line, "map")) { mapConsole(arg); return; }
#endif
#endif
  if (!strcmp(line, "mlx")) {
#if MLX_ENABLE
    logLine(NEON_CYAN, "MLX %s  SDA%d SCL%d @%lukHz",
            mlxReady ? (mlxAlive() ? "live" : "STALLED") : "NOT FOUND",
            MLX_SDA, MLX_SCL, (unsigned long)(i2cHz / 1000));
    logLine(NEON_CYAN, "frames %lu  errs %lu  %lums/frame",
            (unsigned long)mlxFrames, (unsigned long)mlxErrs,
            (unsigned long)mlxFrameMs);
    logLine(NEON_CYAN, "Ta %.1f  min %.1f  max %.1f  ctr %.1f  (%c)",
            tconv(mlxTa), tconv(mlxMin), tconv(mlxMax), tconv(mlxCentre),
            tunit());
#else
    logLine(DIM, "MLX90640 not built - MLX_ENABLE 0 (needs LCD_PINSET 0)");
#endif
    return;
  }
  if (!strcmp(line, "fps")) {
    logLine(NEON_CYAN, "cam %lu frames, %lu drops", (unsigned long)camFrames,
            (unsigned long)camDrops);
    // rx=0 means nothing is arriving on BNO_RX_PIN at all — wrong pin, sensor
    // not in RVC mode, or the pin is loaded by something else. rx>0 with
    // frames=0 means the bytes are there but never checksum.
    logLine(NEON_CYAN, "imu rx=%lu ok=%lu bad=%lu", (unsigned long)imuRawBytes,
            (unsigned long)imuFrames, (unsigned long)imuBadSum);
    return;
  }
  if (!strcmp(line, "ls")) {
    logClear();
    sdListDir(*arg ? arg : "/", 0);
    return;
  }
  if (!strcmp(line, "cat")) {
    if (!*arg) { Serial.println(F("cat <file>")); return; }
    static char buf[2048];
    int n = sdReadText(arg, buf, sizeof(buf));
    if (n < 0) { logLine(NEON_RED, "cat: no %s", arg); return; }
    Serial.printf("---- %s (%d bytes) ----\n%s\n----\n", arg, n, buf);
    return;
  }
  if (!strcmp(line, "write") || !strcmp(line, "append")) {
    char* path = arg;
    char* text = splitArg(path);
    if (!*path || !*text) { Serial.println(F("<file> <text>")); return; }
    bool app = (line[0] == 'a');
    char tmp[192];
    snprintf(tmp, sizeof(tmp), "%s\n", text);
    bool ok = sdWriteText(path, tmp, app);
    logLine(ok ? NEON_GREEN : NEON_RED, "%s %s %s", app ? "append" : "write",
            path, ok ? "ok" : "FAIL");
    return;
  }
  if (!strcmp(line, "rm")) {
    if (!sdMounted || !*arg) { Serial.println(F("rm <file>")); return; }
    logLine(SD_MMC.remove(arg) ? NEON_GREEN : NEON_RED, "rm %s", arg);
    return;
  }
  if (!strcmp(line, "mkdir")) {
    if (!sdMounted || !*arg) { Serial.println(F("mkdir <dir>")); return; }
    logLine(SD_MMC.mkdir(arg) ? NEON_GREEN : NEON_RED, "mkdir %s", arg);
    return;
  }
  if (!strcmp(line, "rmdir")) {
    if (!sdMounted || !*arg) { Serial.println(F("rmdir <dir>")); return; }
    logLine(SD_MMC.rmdir(arg) ? NEON_GREEN : NEON_RED, "rmdir %s", arg);
    return;
  }
  Serial.printf("? %s  (try 'help')\n", line);
}

// Non-blocking line reader — safe to call from inside the sweep loop.
void sdConsolePoll() {
  static char buf[224];
  static uint8_t len = 0;
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\r') continue;
    if (c == '\n') {
      buf[len] = '\0';
      len = 0;
      Serial.printf("> %s\n", buf);
      sdConsoleExec(buf);
      continue;
    }
    if (c == 8 || c == 127) { if (len) len--; continue; }
    if (len < sizeof(buf) - 1) buf[len++] = c;
  }
}

// ─────────────────────────────────────────────────────────────
//  OV5640 — init and frame-to-panel blit
// ─────────────────────────────────────────────────────────────
static bool camReady = false;

bool initCamera() {
  // An RGB565 frame is CAM_W*CAM_H*2 bytes — 153,600 at QVGA on the ST7796.
  // Two of those plus the driver's own buffers will not fit in internal
  // DRAM. Fail loudly rather than limping along with a mystery 0x101.
  if (!psramFound()) {
    logLine(NEON_RED, "NO PSRAM - set Tools/PSRAM to 'OPI PSRAM'");
    return false;
  }

  camera_config_t cfg = {};             // zero first: the struct has fields
  cfg.ledc_channel = LEDC_CHANNEL_0;    // this sketch never touches
  cfg.ledc_timer   = LEDC_TIMER_0;
  cfg.pin_d0       = Y2_GPIO_NUM;     cfg.pin_d1       = Y3_GPIO_NUM;
  cfg.pin_d2       = Y4_GPIO_NUM;     cfg.pin_d3       = Y5_GPIO_NUM;
  cfg.pin_d4       = Y6_GPIO_NUM;     cfg.pin_d5       = Y7_GPIO_NUM;
  cfg.pin_d6       = Y8_GPIO_NUM;     cfg.pin_d7       = Y9_GPIO_NUM;
  cfg.pin_xclk     = XCLK_GPIO_NUM;   cfg.pin_pclk     = PCLK_GPIO_NUM;
  cfg.pin_vsync    = VSYNC_GPIO_NUM;  cfg.pin_href     = HREF_GPIO_NUM;
  cfg.pin_sccb_sda = SIOD_GPIO_NUM;   cfg.pin_sccb_scl = SIOC_GPIO_NUM;
  cfg.pin_pwdn     = PWDN_GPIO_NUM;   cfg.pin_reset    = RESET_GPIO_NUM;
  cfg.xclk_freq_hz = CAM_XCLK_HZ;

  // RGB565 straight to the panel — no JPEG decode in the hot path.
  cfg.pixel_format = PIXFORMAT_RGB565;
  cfg.frame_size   = CAM_FRAMESIZE;     // sized to the camera pane
  cfg.fb_count     = 2;                 // one filling while one is drawn
  cfg.grab_mode    = CAMERA_GRAB_LATEST;
  cfg.fb_location  = CAMERA_FB_IN_PSRAM;

  esp_err_t err = esp_camera_init(&cfg);
  if (err != ESP_OK) {
    logLine(NEON_RED, "camera init FAILED 0x%x", err);
    logLine(DIM, "0x105 = try XCLK on another pin");
    return false;
  }

  sensor_t* s = esp_camera_sensor_get();
  if (s) {
    logLine(NEON_CYAN, "sensor PID 0x%04X", s->id.PID);
    s->set_vflip(s, camFlipV);
    s->set_hmirror(s, camFlipH);
    s->set_whitebal(s, 1);      s->set_awb_gain(s, 1);
    s->set_exposure_ctrl(s, 1); s->set_gain_ctrl(s, 1);
    s->set_brightness(s, 0);    s->set_contrast(s, 0);   s->set_saturation(s, 0);
  }
  return true;
}

//  Stream the frame onto the panel, centre-cropping whatever does not fit
//  rather than scaling. The sensor gives 320x240 and the panel is 320x172,
//  so 34 rows come off the top and bottom and every remaining row is still
//  one contiguous run of bytes — no per-pixel work anywhere.
void showFrame(const camera_fb_t* fb) {
  const int dstW = (CAM_W < TFT_W) ? CAM_W : TFT_W;
  const int dstH = (CAM_H < TFT_H) ? CAM_H : TFT_H;
  const int srcX = (CAM_W - dstW) / 2, srcY = (CAM_H - dstH) / 2;
  const int dstX = (TFT_W - dstW) / 2, dstY = (TFT_H - dstH) / 2;

  tft.beginFrame(dstX, dstY, dstW, dstH);
  for (int y = 0; y < dstH; y++) {
    tft.pushBytes(fb->buf + ((size_t)(srcY + y) * CAM_W + srcX) * 2, dstW * 2);
  }
  tft.endFrame();
}

// ─────────────────────────────────────────────────────────────
//  MLX90640 — init, background reader task
//
//  getFrame() blocks for two refresh periods and busy-polls I2C the whole
//  time, so it gets its own task on core 0. loop() never waits on it: it
//  renders whatever the last completed frame was, or "NO MLX" if there
//  has not been one recently.
// ─────────────────────────────────────────────────────────────
#if MLX_ENABLE

bool mlxAlive() {
  return mlxReady && mlxReadIdx < 2 && (millis() - mlxLastMs) < MLX_STALE_MS;
}

//  Hot-plug support: the sensor is looked for at boot, and again every
//  MLX_PROBE_MS for as long as a thermal view is open and it is missing. A
//  run of MLX_LOST_ERRS failed frames in a row is taken as "unplugged" and
//  drops back to searching, so it recovers from being pulled and replaced.
#define MLX_PROBE_MS  1000
#define MLX_LOST_ERRS 5

//  One detection attempt. A bare address ACK is checked first so that an
//  empty socket costs one short transaction, not begin()'s full EEPROM dump
//  (1664 words) — that matters because it holds the bus the buttons share.
static bool mlxProbe() {
  xSemaphoreTake(i2cMutex, portMAX_DELAY);
  Wire.beginTransmission(MLX_ADDR);
  bool ok = (Wire.endTransmission() == 0) && mlx.begin(MLX_ADDR, &Wire);
  if (ok) {
    mlx.setMode(MLX90640_CHESS);           // chess is the accurate pattern
    mlx.setResolution(MLX90640_ADC_18BIT);
    mlx.setRefreshRate(MLX_REFRESH);
    Wire.setClock(i2cHz);                  // Adafruit begin() leaves it unset
  }
  xSemaphoreGive(i2cMutex);
  if (ok) Serial.printf("MLX90640 %04X-%04X-%04X\n", mlx.serialNumber[0],
                        mlx.serialNumber[1], mlx.serialNumber[2]);
  return ok;
}

//  One full frame (both chess subpages) into dst — getFrame()'s job, but
//  without camping on the bus. getFrame() busy-polls the data-ready flag
//  while holding i2cMutex, ~250 ms a frame at 8 Hz, so the button poller
//  (10 ms timeout) almost never got in and the D-pad seemed dead in the
//  thermal views. Here the ready flag is polled with the mutex taken per
//  2-byte read and released during the sleeps, and the mutex is only held
//  for the actual subpage transfer (~40 ms).
static int mlxReadFrame(float* dst) {
  static uint16_t raw[834];                // static: keeps 1.7 KB off the stack
  for (int page = 0; page < 2; page++) {
    uint32_t t0 = millis();
    for (;;) {
      uint8_t b[2] = { 0, 0 };
      xSemaphoreTake(i2cMutex, portMAX_DELAY);
      Wire.beginTransmission(MLX_ADDR);
      Wire.write(0x80); Wire.write(0x00);  // status register 0x8000
      bool ok = (Wire.endTransmission(false) == 0) &&
                (Wire.requestFrom((int)MLX_ADDR, 2) == 2);
      if (ok) { b[0] = Wire.read(); b[1] = Wire.read(); }
      xSemaphoreGive(i2cMutex);
      if (!ok) return -1;
      if (b[1] & 0x08) break;              // new subpage ready
      if (millis() - t0 > 1000) return -2; // sensor stopped producing
      vTaskDelay(pdMS_TO_TICKS(5));
    }
    xSemaphoreTake(i2cMutex, portMAX_DELAY);
    int e = mlx.MLX90640_GetFrameData(0, raw);   // ready, so no wait inside
    xSemaphoreGive(i2cMutex);
    if (e < 0) return e;
    //  The rest is maths on the captured words — no bus needed.
    mlx.ta = mlx.MLX90640_GetTa(raw, &mlx._params);
    mlx.MLX90640_CalculateTo(raw, &mlx._params, 0.95f,
                             mlx.ta - OPENAIR_TA_SHIFT, dst);
  }
  return 0;
}

static void mlxTask(void*) {
  //  Detection runs here rather than in setup() so it stays off the boot
  //  critical path. Wire.begin() itself is in setup() so the bus is up for
  //  the buttons even if this sensor is absent; every bus access here is
  //  fenced by i2cMutex against the button poller.
  mlxReady = mlxProbe();
  if (!mlxReady)
    Serial.printf("MLX90640 not found @0x%02X (SDA%d SCL%d) - will retry "
                  "when a thermal view opens\n", MLX_ADDR, MLX_SDA, MLX_SCL);

  uint8_t failRun = 0;
  for (;;) {
    //  Idle unless a thermal/fusion view or the web page wants data — leaves
    //  the shared bus free for fast button polling the rest of the time.
    if (!mlxScanOn && !webWantsTherm()) { vTaskDelay(pdMS_TO_TICKS(40)); continue; }

    if (!mlxReady) {
      if (mlxProbe()) { mlxErrs = 0; failRun = 0; mlxReady = true; }
      else            vTaskDelay(pdMS_TO_TICKS(MLX_PROBE_MS));
      continue;
    }

    float* dst = mlxBuf[mlxWriteIdx];

    uint32_t t0 = millis();
    int frameErr = mlxReadFrame(dst);      // takes/releases i2cMutex itself
    if (frameErr != 0) {
      mlxErrs++;
      if (++failRun >= MLX_LOST_ERRS) {    // unplugged: go back to searching
        Serial.println("MLX90640 lost - searching");
        mlxReady   = false;
        mlxReadIdx = 0xFF;                 // no stale frame shown on return
        failRun    = 0;
      }
      vTaskDelay(pdMS_TO_TICKS(50));       // bus glitch — back off, then retry
      continue;
    }
    failRun = 0;

    float lo = dst[0], hi = dst[0];
    for (int i = 1; i < THERM_W * THERM_H; i++) {
      if (dst[i] < lo) lo = dst[i];
      if (dst[i] > hi) hi = dst[i];
    }
    mlxMin     = lo;
    mlxMax     = hi;
    mlxCentre  = dst[(THERM_H / 2) * THERM_W + (THERM_W / 2)];
    mlxTa      = mlx.getTa(false);         // cached from this frame, no extra read
    mlxFrameMs = millis() - t0;

    // Publish by flipping the index. The renderer may be part-way through
    // the buffer it is reading, but it is reading the OTHER one — and by
    // the time this task comes back round to it, a whole frame period has
    // passed. Worst case is one torn image, which is invisible at 4 fps.
    mlxReadIdx  = mlxWriteIdx;
    mlxWriteIdx ^= 1;
    mlxFrames++;
    mlxLastMs = millis();

    vTaskDelay(1);                          // never hog the core outright
  }
}

//  Spawn only — everything that talks to the sensor now happens inside the
//  task, so this returns in microseconds.
bool mlxBegin() {
  return xTaskCreatePinnedToCore(mlxTask, "mlx", MLX_TASK_STACK, nullptr,
                                 MLX_TASK_PRIO, nullptr, MLX_TASK_CORE) == pdPASS;
}

// ── False colour ──────────────────────────────────────────────
//  Ironbow-ish ramp: black -> purple -> red -> orange -> white. Five stops
//  linearly interpolated, which is enough to read shape and gradient and
//  costs two multiplies a pixel — and there are only 768 of them.
//  Palette lookup to 8-bit RGB. Split out of thermColor() so the readings
//  column can colour its numbers with exactly the colour that temperature
//  has in the image.
static void thermRGB(float t, float lo, float hi, uint8_t* out) {
  static const uint8_t stop[5][3] = {
    {   0,   0,   0 },   // coldest
    {  60,   0, 120 },
    { 200,  40,  60 },
    { 255, 160,   0 },
    { 255, 255, 220 },   // hottest
  };

  float u = (t - lo) / (hi - lo);
  if (u < 0) u = 0;
  if (u > 1) u = 1;
  u *= 4.0f;                                 // 0..4 across the five stops
  int   i = (int)u;
  if (i > 3) i = 3;
  float f = u - i;

  out[0] = stop[i][0] + (int)((stop[i + 1][0] - stop[i][0]) * f);
  out[1] = stop[i][1] + (int)((stop[i + 1][1] - stop[i][1]) * f);
  out[2] = stop[i][2] + (int)((stop[i + 1][2] - stop[i][2]) * f);
}

static uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

static uint16_t thermColor(float t, float lo, float hi) {
  uint8_t c[3];
  thermRGB(t, lo, hi, c);
  return rgb565(c[0], c[1], c[2]);
}

//  The same colour, made readable as TEXT. The cold end of the palette is
//  black, and black numbers on a near-black background cannot be read, so
//  anything too dark keeps its hue but is lifted to a minimum brightness.
//  Pure black has no hue to keep, so it borrows the next stop up — the deep
//  purple the image shows just above its coldest pixels.
#define THERM_TXT_MIN 170
static uint16_t thermTextColor(float t, float lo, float hi) {
  uint8_t c[3];
  thermRGB(t, lo, hi, c);
  uint8_t m = c[0] > c[1] ? (c[0] > c[2] ? c[0] : c[2]) : (c[1] > c[2] ? c[1] : c[2]);
  if (m == 0) { c[0] = 60; c[1] = 0; c[2] = 120; m = 120; }
  if (m < THERM_TXT_MIN) {
    for (int k = 0; k < 3; k++) c[k] = (uint8_t)((uint16_t)c[k] * THERM_TXT_MIN / m);
  }
  return rgb565(c[0], c[1], c[2]);
}
#endif  // MLX_ENABLE

// ─────────────────────────────────────────────────────────────
//  BNO085 UART-RVC receiver
//
//  19-byte frames: 0xAA 0xAA, then index, 6 x int16 little-endian
//  (yaw, pitch, roll, ax, ay, az), 3 reserved, and a checksum that is the
//  8-bit sum of the 16 bytes before it. Angles are 0.01 deg, accel is mg.
//  One-way — nothing is ever sent to the sensor.
// ─────────────────────────────────────────────────────────────
bool imuAlive() { return imuFrames > 0 && (millis() - imuLastMs) < IMU_STALE_MS; }

//  THE RVC ANGLE FRAME IS NOT THE ACCELEROMETER FRAME (measured 2026-11-21
//  on the v6 board, tilts of 26-88 deg). The angles are Z-Y-X (yaw +/-180
//  "since reset", pitch +/-90, roll +/-180, per the CEVA datasheet) but in a
//  Z-DOWN frame whose X/Y are the accelerometer's Y/X:
//      X_angles = Y_accel,  Y_angles = X_accel,  Z_angles = -Z_accel
//  Evidence: world-up in accel axes = (-sin roll * cos pitch, sin pitch,
//  cos roll * cos pitch) matched every pose to +/-0.3 m/s^2, and yaw grows
//  when the board turns CLOCKWISE seen from above. See imuAttitudeA().
//
//  Re-express one RVC frame in the board's frame when the chip is mounted
//  turned about its Z axis (imuMountDeg). Accel is a plain X/Y rotation by
//  +mount. The attitude goes through a rotation matrix conjugated by the
//  mount turn (B = M R M^T) - NOT a pitch/roll swap, which breaks past 90 deg
//  - and because the angle frame's Z points down, M there is Rz(-mount).
//  Conjugation keeps the heading at power-up reading the same (yaw is
//  relative to reset, not to north).
static void imuMountRotate(float* yaw, float* pitch, float* roll, float* ax, float* ay) {
  int c, s;                                   // cos/sin of the mount angle
  switch (imuMountDeg) {
    case 90:  c =  0; s =  1; break;
    case 180: c = -1; s =  0; break;
    case 270: c =  0; s = -1; break;
    default:  return;                         // 0: leave the frame untouched
  }
  const int sa = -s;                          // attitude turns the other way (Z down)
  const float d = (float)M_PI / 180.0f;
  const float cy = cosf(*yaw * d),   sy = sinf(*yaw * d);
  const float cp = cosf(*pitch * d), sp = sinf(*pitch * d);
  const float cr = cosf(*roll * d),  sr = sinf(*roll * d);
  const float R[3][3] = {                     // Rz(yaw) * Ry(pitch) * Rx(roll)
    { cy * cp, cy * sp * sr - sy * cr, cy * sp * cr + sy * sr },
    { sy * cp, sy * sp * sr + cy * cr, sy * sp * cr - cy * sr },
    { -sp,     cp * sr,                cp * cr                } };
  float T[3][3], B[3][3];
  for (int i = 0; i < 3; i++) {               // T = R * M^T, M = Rz(-mount)
    T[i][0] = R[i][0] * c - R[i][1] * sa;
    T[i][1] = R[i][0] * sa + R[i][1] * c;
    T[i][2] = R[i][2];
  }
  for (int j = 0; j < 3; j++) {               // B = M * T
    B[0][j] = c * T[0][j] - sa * T[1][j];
    B[1][j] = sa * T[0][j] + c * T[1][j];
    B[2][j] = T[2][j];
  }
  float sinP = -B[2][0];
  if (sinP > 1.0f) sinP = 1.0f; else if (sinP < -1.0f) sinP = -1.0f;
  *yaw   = atan2f(B[1][0], B[0][0]) / d;
  *pitch = asinf(sinP) / d;
  *roll  = atan2f(B[2][1], B[2][2]) / d;
  const float x = *ax, y = *ay;
  *ax = c * x - s * y;
  *ay = s * x + c * y;
}

//  Which accelerometer axis runs along the panel, for the views that react
//  to tilt (FISH TANK, SAND PHYSICS): imuScrX runs left -> right, imuScrY
//  top -> bottom, each 0 +X, 1 -X, 2 +Y, 3 -Y, 4 +Z, 5 -Z. Saved in NVS
//  ("imx" / "imy") and set with the "axes" console command.
static uint8_t imuScrX = 1, imuScrY = 2;
static bool    imuScrLoaded = false;
static const char* const kImuAxName[6] = { "+X", "-X", "+Y", "-Y", "+Z", "-Z" };
void imuScrLoad() {
  if (imuScrLoaded) return;
  prefs.begin("servoctl", true);
  imuScrX = prefs.getUChar("imx", 1) % 6;
  imuScrY = prefs.getUChar("imy", 2) % 6;
  prefs.end();
  imuScrLoaded = true;
}
static inline float imuPick(uint8_t sel, float x, float y, float z) {
  float v = sel < 2 ? x : sel < 4 ? y : z;
  return (sel & 1) ? -v : v;
}
//  The latest accelerometer sample (gravity + motion) in screen axes, m/s^2.
void imuScreenAccel(float* gx, float* gy) {
  imuScrLoad();
  *gx = imuPick(imuScrX, imuAx, imuAy, imuAz);
  *gy = imuPick(imuScrY, imuAx, imuAy, imuAz);
}
static int imuAxParse(const char* t) {
  for (int i = 0; i < 6; i++) if (!strncasecmp(t, kImuAxName[i], 2)) return i;
  return -1;
}
//  Console "axes [<x> <y>]", e.g. "axes -x +y".
void imuAxesConsole(const char* arg) {
  imuScrLoad();
  while (*arg == ' ') arg++;
  if (*arg) {
    const char* b = strchr(arg, ' ');
    int x = imuAxParse(arg), y = b ? imuAxParse(b + 1) : -1;
    if (x < 0 || y < 0 || (x >> 1) == (y >> 1)) {
      Serial.println("axes <x> <y>: two different axes from +x -x +y -y +z -z, e.g. axes -x +y");
      return;
    }
    imuScrX = x; imuScrY = y;
    prefs.begin("servoctl", false); prefs.putUChar("imx", x); prefs.putUChar("imy", y); prefs.end();
  }
  float gx, gy; imuScreenAccel(&gx, &gy);
  Serial.printf("axes: screen right = %s, screen down = %s | accel %.1f %.1f %.1f -> screen %.1f, %.1f%s\n",
                kImuAxName[imuScrX], kImuAxName[imuScrY], imuAx, imuAy, imuAz, gx, gy,
                imuAlive() ? "" : " (IMU silent)");
}

//  Save the BNO085 mount turn (see imuMountDeg). Shared by the console and
//  SETTINGS > IMU/COMP > MOUNT.
void imuMountSet(uint16_t deg) {
  imuMountDeg = deg % 360;
  prefs.begin("servoctl", false);
  prefs.putUShort("imurot", imuMountDeg);
  prefs.end();
}
//  Console "imurot [0|90|180|270]" - how the chip is turned on this board,
//  counter-clockwise looking down on it. Takes effect on the next frame.
void imuMountConsole(const char* arg) {
  while (*arg == ' ') arg++;
  if (*arg) {
    int v = atoi(arg);
    if (v != 0 && v != 90 && v != 180 && v != 270) {
      Serial.println("imurot 0|90|180|270  (CCW looking down on the chip; v6 board = 270)");
      return;
    }
    imuMountSet((uint16_t)v);
  }
  Serial.printf("imurot: chip turned %u deg CCW | yaw %.1f pitch %.1f roll %.1f | accel %.1f %.1f %.1f%s\n",
                imuMountDeg, imuYaw, imuPitch, imuRoll, imuAx, imuAy, imuAz,
                imuAlive() ? "" : " (IMU silent)");
  if (*arg) Serial.println("  tilts reversed? use the opposite turn (90 <-> 270). Re-zero the cube after changing.");
}

// ── Line-level probe on BNO_RX_PIN ────────────────────────────────
//  "rx=0" has three completely different causes and the byte counter cannot
//  tell them apart. Driving the pad's own pull resistors can: a powered,
//  connected sensor holds its TX line HIGH strongly enough to beat an
//  internal pull-DOWN, while a disconnected pin simply follows whichever
//  pull is enabled.
//
//    beats the pull-down ........ something is actively driving the line, so
//                                 the sensor has power and the wire is on
//                                 the right pin. If no edges follow, it is
//                                 silent -> RVC mode was never latched:
//                                 P0 -> 3V3, then POWER-CYCLE.
//    follows both pulls ......... pin is floating. Nothing is connected to
//                                 GPIO14, or the sensor has no power/ground.
//                                 Check you reconnected TX and not RX.
//    held LOW against pull-up ... actively driven low - shorted to GND, or
//                                 the wire is on the wrong pin.
//    edges but no valid frames .. bytes are arriving; wrong baud, or the
//                                 sensor is in I2C/SPI mode rather than RVC.
void bnoProbe() {
  logLine(NEON_CYAN, "-- BNO085 probe on GPIO%d --", BNO_RX_PIN);

  // Hand the pad back from the UART for the duration of the test.
  Serial1.end();

  pinMode(BNO_RX_PIN, INPUT_PULLDOWN); delay(5);
  int withPd = digitalRead(BNO_RX_PIN);
  pinMode(BNO_RX_PIN, INPUT_PULLUP);   delay(5);
  int withPu = digitalRead(BNO_RX_PIN);
  pinMode(BNO_RX_PIN, INPUT);          delay(5);

  // Count transitions on the undriven pad — a live 115200 stream shows
  // thousands of edges in 50 ms, a silent line shows none.
  uint32_t t0 = millis(), edges = 0, high = 0, n = 0;
  int last = digitalRead(BNO_RX_PIN);
  while (millis() - t0 < 50) {
    int v = digitalRead(BNO_RX_PIN);
    if (v != last) { edges++; last = v; }
    if (v) high++;
    n++;
  }

  // Put the UART back and see whether anything lands in the next 250 ms.
  Serial1.begin(BNO_BAUD, SERIAL_8N1, BNO_RX_PIN, -1);
  uint32_t before = imuRawBytes;
  t0 = millis();
  while (millis() - t0 < 250) { imuPoll(); delay(1); }
  uint32_t arrived = imuRawBytes - before;

  logLine(NEON_CYAN, "pulldown=%d pullup=%d  edges=%lu high=%lu%%",
          withPd, withPu, (unsigned long)edges,
          (unsigned long)(n ? high * 100 / n : 0));
  logLine(NEON_CYAN, "rx +%lu in 250ms  (total %lu ok %lu bad %lu)",
          (unsigned long)arrived, (unsigned long)imuRawBytes,
          (unsigned long)imuFrames, (unsigned long)imuBadSum);

  if (arrived && imuFrames) {
    strcpy(imuVerdict, "");                  // nothing to report - it works
    strcpy(imuHint,    "");
    logLine(NEON_GREEN, "VERDICT: sensor live and parsing");
  } else if (arrived || edges > 4) {
    strcpy(imuVerdict, "NO FRAMES");
    strcpy(imuHint,    "wrong baud or not RVC");
    logLine(NEON_YELLOW, "VERDICT: traffic but no valid frames");
    logLine(DIM, "wrong baud, or not in RVC mode");
  } else if (withPd == HIGH) {
    strcpy(imuVerdict, "SILENT");
    strcpy(imuHint,    "P0->3V3, SDA->G14, cut pwr");
    logLine(NEON_YELLOW, "VERDICT: line held HIGH but SILENT");
    logLine(DIM, "something is holding GPIO%d high, so the", BNO_RX_PIN);
    logLine(DIM, "wire and power are there - but SDA has an");
    logLine(DIM, "I2C pull-up, so high does NOT prove RVC.");
    logLine(DIM, "Adafruit BNO085: tie **P0 to 3.3V** (not");
    logLine(DIM, "P1), and take the data off the **SDA** pad.");
    logLine(DIM, "Mode latches at RESET, and the ESP32 reset");
    logLine(DIM, "button does NOT reset the sensor if it");
    logLine(DIM, "shares the 3V3 rail - REMOVE POWER, or");
    logLine(DIM, "wire RST (see BNO_RST_PIN).");
  } else if (withPu == HIGH) {
    strcpy(imuVerdict, "FLOATING");
    snprintf(imuHint, sizeof(imuHint), "wire TX->G%d, 3V3, GND", BNO_RX_PIN);
    logLine(NEON_RED, "VERDICT: GPIO%d is FLOATING", BNO_RX_PIN);
    logLine(DIM, "nothing connected, or sensor unpowered.");
    logLine(DIM, "check 3V3+GND, and that you wired the");
    logLine(DIM, "sensor's TX (not RX) to GPIO%d.", BNO_RX_PIN);
  } else {
    strcpy(imuVerdict, "HELD LOW");
    strcpy(imuHint,    "shorted, or wrong pin");
    logLine(NEON_RED, "VERDICT: line held LOW");
    logLine(DIM, "shorted to GND, or wrong pin.");
  }
  imuProbed = true;
}

// Runs the probe ONCE, a few seconds in, if not one byte has ever arrived.
// The panel is the only interface most of the time, so the diagnosis should
// appear there by itself rather than waiting to be asked for on a console.
#define IMU_AUTOPROBE_MS 3000
void imuAutoProbe() {
  if (imuProbed || imuRawBytes || millis() < IMU_AUTOPROBE_MS) return;
  Serial.println("no IMU bytes after 3s - probing GPIO14 automatically");
  bnoProbe();
}

void imuPoll() {
  // Resync on the 0xAA 0xAA header rather than assuming frame alignment: at
  // 115200 with no flow control we can join the stream mid-frame.
  static uint8_t buf[19];
  static uint8_t have = 0;

  while (Serial1.available()) {
    uint8_t b = Serial1.read();
    imuRawBytes++;

    if (have == 0) { if (b == 0xAA) buf[have++] = b; continue; }
    if (have == 1) { if (b == 0xAA) buf[have++] = b; else have = (b == 0xAA) ? 1 : 0; continue; }

    buf[have++] = b;
    if (have < 19) continue;
    have = 0;

    uint8_t sum = 0;
    for (uint8_t i = 2; i < 18; i++) sum += buf[i];   // index + payload + reserved
    if (sum != buf[18]) { imuBadSum++; continue; }

    int16_t y  = (int16_t)(buf[3]  | (buf[4]  << 8));
    int16_t p  = (int16_t)(buf[5]  | (buf[6]  << 8));
    int16_t r  = (int16_t)(buf[7]  | (buf[8]  << 8));
    int16_t ax = (int16_t)(buf[9]  | (buf[10] << 8));
    int16_t ay = (int16_t)(buf[11] | (buf[12] << 8));
    int16_t az = (int16_t)(buf[13] | (buf[14] << 8));
    float fy  = y * 0.01f;              // 0.01 deg per count
    float fp  = p * 0.01f;
    float fr  = r * 0.01f;
    float fax = ax * 0.0098f;           // mg -> m/s^2
    float fay = ay * 0.0098f;
    imuMountRotate(&fy, &fp, &fr, &fax, &fay);   // chip frame -> board frame
    imuYaw   = fy;
    imuPitch = fp;
    imuRoll  = fr;
    imuAx    = fax;
    imuAy    = fay;
    imuAz    = az * 0.0098f;
    imuFrames++;
    imuLastMs = millis();
  }
}

// ─────────────────────────────────────────────────────────────
//  Instrument pane — attitude cube + compass rose
//
//  Drawn into a RAM canvas and blitted in one go. Drawing straight to the
//  panel would be unusable: Adafruit_GFX renders diagonal lines through
//  drawPixel(), and every drawPixel here is a full SPI transaction with its
//  own address window — a 12-edge cube would cost tens of milliseconds.
// ─────────────────────────────────────────────────────────────
//  The pane is a fixed 160 wide on both panels but its HEIGHT follows the
//  panel — 172 on the ST7789, 320 on the ST7796. The cube and compass are
//  therefore placed and sized per panel rather than hard-coded, or the tall
//  panel would draw the ST7789 layout crammed into its top half with the
//  heading stranded 140 px below the compass.
//  Views are full screen, and both instruments size themselves from the
//  panel rather than from hard-coded numbers.
//
//  CUBE: corners sit at distance sqrt(3) from the centre and are projected
//  with s = sz*4/(4+z). The worst case on either screen axis is not sqrt(3)
//  times anything simple — it peaks when the corner is tipped toward the
//  viewer at z = -0.75, giving 4*sqrt(2.4375)/3.25 = 1.9215 x sz. That was
//  checked against 400,000 random orientations and matches to four places.
//  The earlier formula assumed 2.307 x sz, which left the cube ~20% smaller
//  than the panel allowed.
#define CUBE_CX      (TFT_W / 2 - 34)           // left of centre: RESET sits at the right
#define CUBE_CY      (TFT_H / 2)
#define CUBE_REACH_K 1922                       // worst-case reach x1000
#define CUBE_FIT     (((TFT_H < TFT_W) ? TFT_H : TFT_W) / 2 - 3)
#define CUBE_SZ      ((CUBE_FIT * 1000) / CUBE_REACH_K)
#define CUBE_REACH   ((CUBE_SZ * CUBE_REACH_K + 999) / 1000)

//  COMPASS: the dial takes the full panel height on the left; a readout
//  panel on the right holds the heading, its cardinal, and the CALIBRATE
//  button. The index triangle sits 8 px above the rim.
#define COMP_R       ((TFT_H - 6 - 10) / 2)
#define COMP_CX      (8 + COMP_R)
#define COMP_CY      (TFT_H / 2 + 5)
#define COMP_TOP     2                          // top of the index triangle's reach
#define COMP_PANEL_X (COMP_CX + COMP_R + 12)    // readout panel, right of the dial
#define COMP_PANEL_W (TFT_W - 14 - COMP_PANEL_X)
#define COMP_BTN_H   26

static_assert(CUBE_CY - CUBE_REACH >= 2 && CUBE_CY + CUBE_REACH <= TFT_H - 3,
              "cube taller than the panel");
static_assert(CUBE_CX - CUBE_REACH >= 2 && CUBE_CX + CUBE_REACH <= TFT_W - 3,
              "cube wider than the panel");
static_assert(COMP_CY - COMP_R - 8 >= COMP_TOP,
              "compass index triangle runs off the top of the panel");
static_assert(COMP_CY + COMP_R <= TFT_H - 3,
              "compass runs off the bottom of the panel");
//  The panel must fit "CALIBRATE" at size 2 (9 x 12 px) with some margin.
static_assert(COMP_PANEL_W >= 9 * 12 + 12,
              "compass readout panel too narrow for the CALIBRATE button");

//  Sense of each rotation axis, cube only. Which way each one reads depends
//  on how the sensor ends up mounted, so all three are knobs rather than
//  baked into the rotation maths.
//
//  Settled on the bench 2026-08-18: PITCH alone is inverted, yaw and roll
//  read straight through. Getting there took several passes because a cube
//  rotating the wrong way looks much the same whichever axis is at fault —
//  yaw and roll were each tried and reverted before pitch turned out to be
//  the only one. One inverted axis is also the sane answer: it means the
//  sensor is mounted flipped about that axis, not that the maths is wrong.
//
//  If it needs revisiting, change ONE sign at a time and watch a SINGLE
//  axis while moving the board only in that axis. All three at +1 is the
//  original, unmodified behaviour.
//  The compass is NOT affected — it takes the heading separately.
//  Bearing added to the sensor's yaw before it reaches the compass, so the
//  rose and the HDG number stay in agreement — offsetting only the graphic
//  would leave the dial and the digits disagreeing by this much. 180 means
//  the sensor faces opposite the board's front.
#define COMP_HDG_OFFSET 180

//  Runtime, persisted settings (SETTINGS view + the NVS helpers below).
//  scrFlipX/Y overlay the panel's compile-time MADCTL; compassOffset is the
//  heading added to raw yaw, tared by "SET NORTH HERE".
static bool  scrFlipX = false, scrFlipY = false;
static float compassOffset = COMP_HDG_OFFSET;
static uint32_t compCalMs = 0;   // when CALIBRATE was last pressed, for its confirm flash

static GFXcanvas16* inst = nullptr;

//  Heading the compass should show: sensor yaw, offset for how the board is
//  mounted, wrapped to 0..360. The cube deliberately does NOT use this — it
//  works from the full attitude matrix (cubeMatrix).
static float compassHeading() {
  float h = fmodf(imuYaw + compassOffset, 360.0f);
  if (h < 0) h += 360.0f;
  return h;
}

// Bearing in degrees clockwise from straight up -> canvas point.
static void polar(int cx, int cy, float r, float bearingDeg, int* x, int* y) {
  float a = bearingDeg * 0.017453292f;
  *x = cx + (int)lroundf(r * sinf(a));
  *y = cy - (int)lroundf(r * cosf(a));
}

//  ── Gyroscope cube geometry ──
//  Vectors here are in the BOARD's accelerometer axes after the mount turn
//  (X/Y in the board plane, +Z out of the glass when it lies face-up), and
//  "world" uses the same style with Z up.

//  Unit vector for one of the "axes" selections (0 +X, 1 -X, 2 +Y, ...).
void imuAxisVec(uint8_t sel, float v[3]) {
  v[0] = v[1] = v[2] = 0;
  v[(sel >> 1) % 3] = (sel & 1) ? -1.0f : 1.0f;
}
//  Screen right / up / out-of-glass in board axes, from the same "axes"
//  setting the tilt views use, so the cube and FISH TANK always agree.
void imuScreenFrame(float er[3], float eu[3], float eo[3]) {
  imuScrLoad();
  float ed[3];
  imuAxisVec(imuScrX, er);
  imuAxisVec(imuScrY, ed);
  for (int i = 0; i < 3; i++) eu[i] = -ed[i];
  eo[0] = er[1] * eu[2] - er[2] * eu[1];        // right x up = out of the glass
  eo[1] = er[2] * eu[0] - er[0] * eu[2];
  eo[2] = er[0] * eu[1] - er[1] * eu[0];
}
//  Board attitude as a matrix in accelerometer-style axes (board -> world,
//  world Z up). The RVC angles live in the Z-down, X/Y-swapped frame noted
//  above imuMountRotate(), so A = P * N * P with P swapping X/Y and negating
//  Z: A[i][j] = g(i) g(j) N[p(i)][p(j)], p = (1, 0, 2), g = (+1, +1, -1).
//  Built as a whole matrix, never from single angles, so it stays smooth
//  through pitch +/-90 (board upright) where yaw and roll alone are not.
void imuAttitudeA(float A[3][3]) {
  const float d = 0.017453292f;
  const float cy = cosf(imuYaw * d),   sy = sinf(imuYaw * d);
  const float cp = cosf(imuPitch * d), sp = sinf(imuPitch * d);
  const float cr = cosf(imuRoll * d),  sr = sinf(imuRoll * d);
  const float N[3][3] = {                       // Rz(yaw) Ry(pitch) Rx(roll)
    { cy * cp, cy * sp * sr - sy * cr, cy * sp * cr + sy * sr },
    { sy * cp, sy * sp * sr + cy * cr, sy * sp * cr - cy * sr },
    { -sp,     cp * sr,                cp * cr                } };
  static const uint8_t p[3] = { 1, 0, 2 };
  static const float   g[3] = { 1.0f, 1.0f, -1.0f };
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) A[i][j] = g[i] * g[j] * N[p[i]][p[j]];
}
//  RESET: remember which horizontal direction is "away from the viewer" right
//  now, in world axes. Screen-up minus out-of-glass works whether the board
//  lies flat (screen-up is then horizontal) or stands upright (out-of-glass
//  is then horizontal) and anywhere between.
void cubeAimHere() {
  float A[3][3], er[3], eu[3], eo[3];
  imuAttitudeA(A);
  imuScreenFrame(er, eu, eo);
  const float b[3] = { eu[0] - eo[0], eu[1] - eo[1], eu[2] - eo[2] };
  const float fx = A[0][0] * b[0] + A[0][1] * b[1] + A[0][2] * b[2];
  const float fy = A[1][0] * b[0] + A[1][1] * b[1] + A[1][2] * b[2];
  const float n = sqrtf(fx * fx + fy * fy);
  if (n < 1e-3f) return;                        // degenerate; keep the old aim
  cubeFwdX = fx / n; cubeFwdY = fy / n; cubeFwdSet = true;
}
//  Cube -> screen rotation. Cube-local axes are the screen's at rest (x
//  right, y up, z into the glass, "UP" painted on the -z face).
//  M = RB * A^T * WL:
//    WL   cube -> world: -z on world UP, +y along the RESET aim.
//    A^T  world -> board: the inverse attitude, because the screen moves
//         and the cube does not.
//    RB   board -> screen: rows are screen right, up, into-glass.
//  Lying flat, face-up, at the RESET aim, M is the identity - the cube is
//  drawn exactly as it always was at rest - and from there the UP face
//  tracks the real sky whatever the board does. Checked against logged
//  poses (flat, 26/44 deg tilts, upright both ways, 80 deg turn).
void cubeMatrix(float M[3][3]) {
  if (!cubeFwdSet) cubeAimHere();
  float A[3][3], er[3], eu[3], eo[3];
  imuAttitudeA(A);
  imuScreenFrame(er, eu, eo);
  const float ei[3] = { -eo[0], -eo[1], -eo[2] };  // into the glass
  const float* RB[3] = { er, eu, ei };
  const float Lx[3] = { cubeFwdY, -cubeFwdX, 0 };  // aim x world-up
  const float Ly[3] = { cubeFwdX,  cubeFwdY, 0 };
  const float Lz[3] = { 0, 0, -1 };
  const float* L[3] = { Lx, Ly, Lz };
  for (int c = 0; c < 3; c++) {
    float w[3];                                    // board coords: A^T * L[c]
    for (int i = 0; i < 3; i++)
      w[i] = A[0][i] * L[c][0] + A[1][i] * L[c][1] + A[2][i] * L[c][2];
    for (int r = 0; r < 3; r++)
      M[r][c] = RB[r][0] * w[0] + RB[r][1] * w[1] + RB[r][2] * w[2];
  }
}

//  Takes its geometry rather than reading the macros, so it can be drawn
//  at any size. M is the cube -> screen rotation from cubeMatrix().
void drawCube(const float M[3][3], int cx, int cy, int sz) {
  const float d = 4.0f;                          // eye distance, in cube half-widths

  // Rotate by M, then weak perspective so the near face reads as nearer
  // (eye at z = -d looking down +z). Used for the corners and for the "UP"
  // lettering, so both move as one body.
  auto xform = [&](float x, float y, float z, int* sx, int* sy, float* rz,
                   float* rx, float* ry) {
    float x3 = M[0][0] * x + M[0][1] * y + M[0][2] * z;
    float y3 = M[1][0] * x + M[1][1] * y + M[1][2] * z;
    float z3 = M[2][0] * x + M[2][1] * y + M[2][2] * z;
    float s = sz * d / (d + z3);
    *sx = cx + (int)lroundf(x3 * s);
    *sy = cy - (int)lroundf(y3 * s);
    if (rz) *rz = z3;
    if (rx) *rx = x3;
    if (ry) *ry = y3;
  };

  int   px[8], py[8];
  float vx[8], vy[8], vz[8];                     // rotated 3D, for face shading
  for (int i = 0; i < 8; i++)
    xform((i & 1) ? 1.f : -1.f, (i & 2) ? 1.f : -1.f, (i & 4) ? 1.f : -1.f,
          &px[i], &py[i], &vz[i], &vx[i], &vy[i]);

  //  Solid faces. Each face is four vertices in perimeter order (vertex bit
  //  1 = +x, 2 = +y, 4 = +z). The cube is convex and centred on the origin,
  //  so a face's centre c is also its outward normal, and it faces the eye
  //  when c . (c - eye) < 0, which works out to c.z < -1/d. Only those are
  //  drawn — at most three, never overlapping, so no depth sort is needed.
  static const uint8_t face[6][4] = {
    {0, 2, 6, 4}, {1, 3, 7, 5},                  // -x, +x
    {0, 1, 5, 4}, {2, 3, 7, 6},                  // -y, +y
    {0, 1, 3, 2}, {4, 5, 7, 6},                  // -z, +z
  };
  //  Light from the upper left, towards the viewer (unit vector).
  const float lx = -0.45f, ly = 0.60f, lz = -0.66f;

  for (int f = 0; f < 6; f++) {
    const uint8_t* v = face[f];
    float nx = (vx[v[0]] + vx[v[1]] + vx[v[2]] + vx[v[3]]) * 0.25f;
    float ny = (vy[v[0]] + vy[v[1]] + vy[v[2]] + vy[v[3]]) * 0.25f;
    float nz = (vz[v[0]] + vz[v[1]] + vz[v[2]] + vz[v[3]]) * 0.25f;
    if (nz >= -1.0f / d) continue;               // facing away

    //  Lambert shading in RealDriver's neon red (#ff3c5f), from a deep
    //  crimson on faces turned from the light up to a hot, slightly washed
    //  red on the lit face; edges in its neon cyan.
    float lit = nx * lx + ny * ly + nz * lz;
    if (lit < 0) lit = 0;
    float k = 0.30f + 0.70f * lit;
    uint8_t r = (uint8_t)(255 * k);
    uint8_t g = (uint8_t)(  8 + 90 * k * k);     // highlights wash a touch lighter
    uint8_t b = (uint8_t)( 20 + 110 * k * k);
    uint16_t col = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);

    inst->fillTriangle(px[v[0]], py[v[0]], px[v[1]], py[v[1]],
                       px[v[2]], py[v[2]], col);
    inst->fillTriangle(px[v[0]], py[v[0]], px[v[2]], py[v[2]],
                       px[v[3]], py[v[3]], col);
    //  Cyan outline so neighbouring faces of similar shade stay distinct.
    for (int e = 0; e < 4; e++) {
      int a = v[e], b2 = v[(e + 1) & 3];
      inst->drawLine(px[a], py[a], px[b2], py[b2], NEON_CYAN);
    }

    //  "UP" on the -z face — the one facing the viewer at rest, i.e. the
    //  cube's world-top with the board lying flat — as strokes lying IN that
    //  face, so the lettering tilts and foreshortens with the cube. Letters
    //  run along +x with their tops toward +y, so they read upright at rest.
    if (f == 4) {
      //  Unit-box strokes (u across, v up) for U and P.
      static const float kU[][4] = { {0,1, 0,0}, {0,0, 1,0}, {1,0, 1,1} };
      static const float kP[][4] = { {0,0, 0,1}, {0,1, 1,1}, {1,1, 1,0.5f}, {1,0.5f, 0,0.5f} };
      const float lw = 0.52f, lh = 0.78f, gap = 0.26f;       // in cube half-widths (face is 2 x 2)
      const float x0 = -(2 * lw + gap) / 2, zb = -lh / 2;
      auto stroke = [&](float xoff, const float s[4]) {
        int ax, ay, bx, by;
        xform(xoff + s[0] * lw, zb + s[1] * lh, -1.0f, &ax, &ay, nullptr, nullptr, nullptr);
        xform(xoff + s[2] * lw, zb + s[3] * lh, -1.0f, &bx, &by, nullptr, nullptr, nullptr);
        inst->drawLine(ax, ay, bx, by, BLACK);             // 2 px wide: draw it twice
        inst->drawLine(ax + 1, ay, bx + 1, by, BLACK);
        inst->drawLine(ax, ay + 1, bx, by + 1, BLACK);
      };
      for (const auto& s : kU) stroke(x0, s);
      for (const auto& s : kP) stroke(x0 + lw + gap, s);
    }
  }
}

//  Takes its geometry rather than reading the macros, so it can be drawn at
//  any size. Menu palette: cyan rim and cardinals, magenta north and index,
//  pink/magenta graduations.
void drawCompass(float headingDeg, int cx, int cy, int r) {
  inst->drawCircle(cx, cy, r,     NEON_CYAN);
  inst->drawCircle(cx, cy, r - 1, NEON_CYAN);
  inst->drawCircle(cx, cy, r - 3, CYBER_GRID);

  // The rose rotates opposite the heading, so the fixed index at the top
  // always reads the direction the board is pointing. Ticks every 10
  // degrees, longer every 30, longest (and doubled) on the cardinals.
  for (int b = 0; b < 360; b += 10) {
    float scr = b - headingDeg;
    bool card = (b % 90) == 0, mid = (b % 30) == 0;
    int  len  = card ? 14 : mid ? 9 : 5;
    uint16_t col = card ? NEON_CYAN : mid ? NEON_PINK : NEON_MAGENTA;
    int x0, y0, x1, y1;
    polar(cx, cy, r - 3 - len, scr, &x0, &y0);
    polar(cx, cy, r - 3,       scr, &x1, &y1);
    inst->drawLine(x0, y0, x1, y1, col);
    if (card) {
      polar(cx, cy, r - 3 - len, scr + 0.8f, &x0, &y0);
      polar(cx, cy, r - 3,       scr + 0.8f, &x1, &y1);
      inst->drawLine(x0, y0, x1, y1, col);
    }
  }

  // Bearing numbers on the 30s between the cardinals, then N/E/S/W.
  inst->setTextSize(1);
  inst->setTextColor(NEON_PINK);
  for (int b = 30; b < 360; b += 30) {
    if (b % 90 == 0) continue;
    char n[4]; snprintf(n, sizeof(n), "%d", b);
    int lx, ly;
    polar(cx, cy, r - 26, b - headingDeg, &lx, &ly);
    inst->setCursor(lx - (int)strlen(n) * 3, ly - 3);
    inst->print(n);
  }
  static const char* card[4] = { "N", "E", "S", "W" };
  const int cs = (r >= 60) ? 2 : 1;             // letter size scales with dial
  inst->setTextSize(cs);
  for (int i = 0; i < 4; i++) {
    int lx, ly;
    polar(cx, cy, r - 18 - 6 * cs, i * 90 - headingDeg, &lx, &ly);
    inst->setTextColor(i == 0 ? NEON_MAGENTA : NEON_CYAN);
    inst->setCursor(lx - 3 * cs, ly - 4 * cs);
    inst->print(card[i]);
  }

  // Lubber line and hub: where the board points, fixed to the screen.
  inst->drawFastVLine(cx, cy - r / 3, r / 3, NEON_MAGENTA);
  inst->fillCircle(cx, cy, 4, NEON_MAGENTA);
  inst->fillCircle(cx, cy, 1, CYBER_BG);

  // Fixed index mark at the top of the dial.
  inst->fillTriangle(cx - 7, cy - r - 8,
                     cx + 7, cy - r - 8,
                     cx,     cy - r - 1, NEON_MAGENTA);
}

//  A dead sensor used to draw a cube frozen at 0/0/0 and a compass stuck on
//  north, which looks exactly like real data that happens not to be moving.
//  Show the diagnosis instead — centred on yMid, nothing else drawn.
void drawImuFault(int yMid) {
  const char* v = imuVerdict[0] ? imuVerdict
                                : (imuRawBytes ? "IMU BAD" : "NO IMU");
  inst->setTextSize(2);
  inst->setTextColor(NEON_RED);
  inst->setCursor(TFT_W / 2 - (int)strlen(v) * 6, yMid - 8);
  inst->print(v);

  const char* h = imuHint[0] ? imuHint
                             : (imuProbed ? "" : "probing GPIO14...");
  if (*h) {
    inst->setTextSize(1);
    inst->setTextColor(DIM);
    inst->setCursor(TFT_W / 2 - (int)strlen(h) * 3, yMid + 14);
    inst->print(h);
  }
}

// ─────────────────────────────────────────────────────────
//  Thermal rendering — shared by the thermal view and anything else
//  that wants the false-colour block.
// ─────────────────────────────────────────────────────────
#if MLX_ENABLE
//  Why the sensor is not showing, in the space where the image would be.
//  Missing, the sensor is being re-probed every second (see mlxTask), so the
//  message says it is searching and the image appears as soon as it is found.
void thermalFault(int yMid) {
  const char* head = !mlxReady            ? "NO THERMAL CAMERA"
                   : (mlxReadIdx == 0xFF) ? "STARTING..."
                                          : "THERMAL CAMERA STALLED";
  const char* sub  = !mlxReady ? "SEARCHING - PLUG IT IN" : "";
  inst->setTextSize(2);
  inst->setTextColor(mlxReady ? NEON_YELLOW : NEON_RED);
  inst->setCursor((TFT_W - (int)strlen(head) * 12) / 2, yMid - 20);
  inst->print(head);
  if (*sub) {
    inst->setTextColor(NEON_CYAN);
    inst->setCursor((TFT_W - (int)strlen(sub) * 12) / 2, yMid + 2);
    inst->print(sub);
  }
  char pins[48];
  snprintf(pins, sizeof pins, "SDA%d SCL%d  addr 0x%02X  err %lu", MLX_SDA, MLX_SCL, MLX_ADDR,
           (unsigned long)mlxErrs);
  inst->setTextSize(1);
  inst->setTextColor(DIM);
  inst->setCursor((TFT_W - (int)strlen(pins) * 6) / 2, yMid + 26);
  inst->print(pins);
}

//  Draws the 160x120 false-colour block with its top edge at yTop, and hands
//  back the eased palette range so the caller can caption it. Shared by the
//  full-pane thermal view and the combined view, which is why the easing
//  state lives here — one set of statics, so switching views does not
//  restart the range from cold.
void thermalImage(int xLeft, int yTop, int scale, float* loOut, float* hiOut) {
  uint8_t      idx = mlxReadIdx;             // latch: the task may flip it
  const float* f   = mlxBuf[idx & 1];

  // Auto-range, but eased. Snapping the palette to each frame's own min/max
  // makes a static scene shimmer, because the extremes wander by a few
  // tenths of a degree frame to frame. Following them at a quarter of the
  // error per frame keeps the image steady and still tracks a hand entering
  // the scene within a second.
  float lo = mlxMin, hi = mlxMax;
  if (hi - lo < 2.0f) {                      // flat scene — don't amplify noise
    float mid = (lo + hi) * 0.5f;
    lo = mid - 1.0f;
    hi = mid + 1.0f;
  }
  static float sLo = 0, sHi = 0;
  static bool  sInit = false;
  if (!sInit) { sLo = lo; sHi = hi; sInit = true; }
  else        { sLo += (lo - sLo) * 0.25f; sHi += (hi - sHi) * 0.25f; }

  for (int y = 0; y < THERM_H; y++) {
    // Source row, hoisted: the flip is per-row, not per-pixel.
    const float* srow = f + (thermFlipV ? (THERM_H - 1 - y) : y) * THERM_W;
    for (int x = 0; x < THERM_W; x++) {
      uint16_t c = thermColor(srow[thermFlipH ? (THERM_W - 1 - x) : x], sLo, sHi);
      inst->fillRect(xLeft + x * scale, yTop + y * scale, scale, scale, c);
    }
  }

  // Centre crosshair, so there is something to aim the CTR reading with.
  int ccx = xLeft + (THERM_W * scale) / 2, ccy = yTop + (THERM_H * scale) / 2;
  inst->drawFastHLine(ccx - 5, ccy, 11, WHITE);
  inst->drawFastVLine(ccx, ccy - 5, 11, WHITE);

  *loOut = sLo;
  *hiOut = sHi;
}

#endif  // MLX_ENABLE

//  The OV5640 takes the best part of a second to initialise, which used to
//  sit squarely between power-on and the first video frame. Nothing needs it
//  until the camera view is actually chosen, so it is brought up the first
//  time that happens and never at boot.
static bool camInitTried = false;

//  For the web page, which is compiled above these flags: 0 = camera not
//  started yet, 1 = running, 2 = tried and failed.
int camWebState() { return !camInitTried ? 0 : camReady ? 1 : 2; }

//  Publish a camera frame to the web page, at most every WEB_CAM_MS and
//  only while a page is watching. Called from loop() with a frame in hand.
bool webCamDue() {
  static uint32_t last = 0;
  if (!webJpgMux || !webWantsCam() || millis() - last < WEB_CAM_MS) return false;
  last = millis();
  return true;
}
void webCamPublish(camera_fb_t* fb) {
  if (fb->format != PIXFORMAT_RGB565) return;
  uint8_t* j = nullptr; size_t n = 0;
  if (!frame2jpg(fb, WEB_JPEG_Q, &j, &n)) return;
  if (xSemaphoreTake(webJpgMux, 0) != pdTRUE) { free(j); return; }   // mid-send: skip
  free(webJpg);
  webJpg = j; webJpgLen = n; webJpgMs = millis();
  xSemaphoreGive(webJpgMux);
}

bool camEnsure() {
#if CAM_ENABLE
  if (camInitTried) return camReady;
  camInitTried = true;
  camReady = initCamera();
  return camReady;
#else
  camInitTried = true;
  return false;
#endif
}

// ─────────────────────────────────────────────────────────────
//  UI — full-screen views, and the menu that picks between them
//
//  Every drawn view renders into the one full-panel canvas and lands in a
//  single push. The camera is the exception: its frames go straight from
//  the sensor buffer to the panel, because copying 110 KB through a canvas
//  first would halve the frame rate for no benefit.
//
//  Input is deliberately indirect. The BOOT button synthesises UiAction
//  values, and only uiAction() knows what a press MEANS — so the 5-button
//  panel arrives later as five more callers of the same function, with no
//  change to any view.
// ─────────────────────────────────────────────────────────────
//  Largest whole-pixel zoom that still leaves a strip at the bottom for the
//  readouts. Whole pixels only — a fractional scale would need interpolation
//  and 32x24 has no detail to justify it.
//  Image hard left, readings in a column down the right. With no title plate
//  and no bottom strip, the height is the limit rather than the width:
//  320x172 gives 7x -> 224x168, leaving a column wide enough for six size-2
//  characters ("104.2F").
#define UI_THERM_COL_W  90                      // reserved for the readings
#define UI_THERM_SCALE  ((((TFT_W - UI_THERM_COL_W) / THERM_W) < ((TFT_H - 4) / THERM_H)) \
                           ? ((TFT_W - UI_THERM_COL_W) / THERM_W) : ((TFT_H - 4) / THERM_H))
#define UI_THERM_W      (THERM_W * UI_THERM_SCALE)
#define UI_THERM_H      (THERM_H * UI_THERM_SCALE)
#define UI_THERM_X      2
#define UI_THERM_Y      ((TFT_H - UI_THERM_H) / 2)
#define UI_THERM_TXT_X  (UI_THERM_X + UI_THERM_W + 6)
static_assert(UI_THERM_H <= TFT_H - 4, "thermal image taller than the panel");
static_assert(UI_THERM_TXT_X + 7 * 12 <= TFT_W - 2,
              "thermal reading column too narrow for its values");

//  Menu geometry — everything derived from the panel so the rows always
//  fill it. Nothing here is a free-standing number: the header plate sets
//  where the rows start, the rows share out whatever height is left, and
//  the text size is the largest that fits both a row's height and the
//  longest item name across the width.
#define MENU_HEAD_Y   3
#define MENU_HEAD_H   23                        // header plate height
#define MENU_HEAD_B   (MENU_HEAD_Y + MENU_HEAD_H)
#define MENU_ROW_H    18                        // size-2 glyph (16) + 2
#define MENU_PITCH    18
#define MENU_TOP0     (MENU_HEAD_B + 2)         // first row when the list fills
//  Connection footer (see drawMenuFooter): two size-2 lines on a cyan plate,
//  the way the old I2C OLED showed IP / network / signal. The rows fit
//  between it and the header, leaving 7 px for the "more below" arrow.
#define MENU_FOOT_H   40                        // 2 x 16 px lines + 2 gap + 3 + 3 pad
#define MENU_FOOT_Y   (TFT_H - MENU_HEAD_Y - MENU_FOOT_H)
#define MENU_VISIBLE  ((MENU_FOOT_Y - 7 - MENU_TOP0) / MENU_PITCH)  // rows that fit
#define MENU_NAME_X   16                        // left edge of the item names
#define MENU_NAME_CH  23                        // "ENHANCED THERMAL CAMERA", the longest name

//  Rows are a fixed size 2 now, and the list SCROLLS when there are more
//  items than fit — so adding a menu entry no longer shrinks the text.
static_assert(12 + 19 * 12 < TFT_W - 30, "menu title runs into the header notch");
static_assert(MENU_VISIBLE >= 4, "panel too short to show the menu at size 2");
static_assert(MENU_NAME_X + MENU_NAME_CH * 6 * 2 <= TFT_W - 27,
              "longest menu item name runs into the selected-row notch");

//  Text centred on the panel both ways, for one-line status screens.
void uiCentreText(const char* text, int size, uint16_t col) {
  inst->setTextSize(size);
  inst->setTextColor(col);
  inst->setCursor((TFT_W - (int)strlen(text) * 6 * size) / 2,
                  (TFT_H - 8 * size) / 2);
  inst->print(text);
}

// ── Save a JPEG of the current screen to the SD card ─────────
//  ENTER captures whatever the panel is showing:
//    * CAMERA    -> the camera's own frame (QVGA), straight to JPEG.
//    * every other view -> the UI canvas (320x172), which is where the
//      thermal, fusion, cube, compass and menus are all composited.
//  Files land as /IMGnnnn.jpg with a counter kept in NVS so numbering
//  survives reboots.
#define JPEG_QUALITY 80

//  Brief on-panel confirmation, drawn straight to the panel so it clears on
//  the next frame without disturbing the canvas.
//  The captured filename is shown centred and held on screen: saveJpeg()
//  draws it, and loop() freezes the panel until toastUntil so the redraw
//  cannot wipe it before it has been read.
#define TOAST_MS 1500
static uint32_t toastUntil = 0;

//  Two-colour toast: separate frame and text colours (the main-menu look is a
//  pink frame with blue text). toast() keeps the single-colour convenience.
static void toast2(const char* msg, uint16_t border, uint16_t text) {
  int w = (int)strlen(msg) * 12 + 16;
  int x = (TFT_W - w) / 2, y = TFT_H / 2 - 12;
  tft.fillRect(x, y, w, 24, BLACK);
  tft.drawRect(x, y, w, 24, border);
  printBg(msg, x + 8, y + 5, 2, text, BLACK);
  toastUntil = millis() + TOAST_MS;
}
static void toast(const char* msg, uint16_t col) { toast2(msg, col, col); }

bool saveJpeg() {
  if (!sdMounted) { toast("NO CARD", NEON_RED); return false; }

  uint8_t* jpg = nullptr;
  size_t   jlen = 0;

  if (uiView == UI_CAMERA && camReady) {
    camera_fb_t* fb = esp_camera_fb_get();
    if (fb) {
      frame2jpg(fb, JPEG_QUALITY, &jpg, &jlen);   // RGB565 frame -> JPEG
      esp_camera_fb_return(fb);
    }
  } else if (inst) {
    //  The canvas stores native little-endian RGB565; fmt2jpg wants the
    //  camera's big-endian order, so swap around the conversion. byteSwap()
    //  is synchronous and we are not mid-draw here, so the flip is invisible.
    inst->byteSwap();
    fmt2jpg((uint8_t*)inst->getBuffer(), (size_t)TFT_W * TFT_H * 2, TFT_W, TFT_H,
            PIXFORMAT_RGB565, JPEG_QUALITY, &jpg, &jlen);
    inst->byteSwap();
  }

  if (!jpg || !jlen) { toast("CAPTURE FAIL", NEON_RED); return false; }

  //  Next free index, from an NVS counter (cheap, monotonic, reboot-safe).
  prefs.begin("servoctl", false);
  uint32_t n = prefs.getUInt("imgno", 0);
  prefs.putUInt("imgno", n + 1);
  prefs.end();

  char path[24];
  snprintf(path, sizeof(path), "/IMG%04lu.jpg", (unsigned long)(n % 10000));
  File f = SD_MMC.open(path, FILE_WRITE);
  bool ok = false;
  if (f) { ok = (f.write(jpg, jlen) == jlen); f.close(); }
  free(jpg);

  if (ok) { toast2(path + 1, NEON_MAGENTA, NEON_CYAN);   // pink frame, blue text
            Serial.printf("saved %s (%u bytes)\n", path, (unsigned)jlen); }
  else    { toast("WRITE FAIL", NEON_RED); }
  return ok;
}

void uiBlit() {
  if (!inst) return;
  tft.beginFrame(0, 0, TFT_W, TFT_H);
  tft.pushPixels16(inst->getBuffer(), (uint32_t)TFT_W * TFT_H);
  tft.endFrame();
}

//  One dark row every Nth line. Costs almost nothing and does more for the
//  CRT look than any amount of colour choice.
static void uiScanlines() {
#if CYBER_SCANLINE
  for (int y = 0; y < TFT_H; y += CYBER_SCANLINE)
    inst->drawFastHLine(0, y, TFT_W, BLACK);
#endif
}

//  Chamfered border — cut corners rather than a plain rectangle, which is
//  what stops it reading as a default GFX box.
static void uiFrame(uint16_t col) {
  const int c = 9;
  inst->drawFastHLine(c, 0, TFT_W - 2 * c, col);
  inst->drawFastHLine(c, TFT_H - 1, TFT_W - 2 * c, col);
  inst->drawFastVLine(0, c, TFT_H - 2 * c, col);
  inst->drawFastVLine(TFT_W - 1, c, TFT_H - 2 * c, col);
  inst->drawLine(0, c, c, 0, col);
  inst->drawLine(TFT_W - 1 - c, 0, TFT_W - 1, c, col);
  inst->drawLine(0, TFT_H - 1 - c, c, TFT_H - 1, col);
  inst->drawLine(TFT_W - 1 - c, TFT_H - 1, TFT_W - 1, TFT_H - 1 - c, col);
}

// ── 3D plates ────────────────────────────────────────────────
//  Every header, footer, selection bar and selected button is drawn as a
//  raised plate: slightly rounded corners, a vertical shade from lit (top)
//  to shadowed (bottom), a bright bevel on the top and left edges, a dark
//  one on the bottom and right, and a drop shadow down-right onto the
//  background. Text on a plate is embossed: a light 1 px highlight under the
//  black glyphs, as if stamped into it.
#define PLATE_RADIUS     4        // headers / footers
#define PLATE_RADIUS_SEL 3        // selection bars and buttons
#define PLATE_SHADOW     3        // headers / footers
#define PLATE_SHADOW_SEL 2        // selections sit in tighter lists
//  Base colours as rgb888 (the plate shades from these).
#define PLATE_MAGENTA 0xFF, 0x3C, 0x5F        // RealDriver neon red (name historical)
#define PLATE_CYAN    0x00, 0xFF, 0xE7        // RealDriver neon blue/cyan

//  rgb888 -> the panel's rgb565, with each channel scaled by k/256 and clamped.
static uint16_t plateShade(uint8_t r, uint8_t g, uint8_t b, int k) {
  int R = r * k / 256, G = g * k / 256, B = b * k / 256;
  if (R > 255) R = 255; if (G > 255) G = 255; if (B > 255) B = 255;
  return ((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3);
}

//  How far row i of an h-tall plate is pulled in at each end by corners of
//  radius rad (0 for the straight middle rows).
static int plateInset(int i, int h, int rad) {
  int d = (i < rad) ? rad - 1 - i : (i >= h - rad) ? i - (h - rad) : -1;
  if (d < 0) return 0;
  float dy = d + 0.5f, s = (float)(rad * rad) - dy * dy;
  return (s <= 0) ? rad : (int)(rad - sqrtf(s) + 0.5f);
}

//  One raised plate at (x, y, w, h) in base colour r,g,b, with corner radius
//  rad and a drop shadow sh px down-right (outside w x h — leave room).
static void ui3DPlate(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b,
                      int rad, int sh) {
  if (rad * 2 > h) rad = h / 2;
  const uint16_t shadow = 0x0000;                        // black, under the blue-black bg
  const uint16_t lit    = plateShade(r | 0x60, g | 0x60, b | 0x60, 300);
  const uint16_t dark   = plateShade(r, g, b, 90);
  for (int i = 0; sh && i < h; i++) {                    // rounded shadow, first
    int in = plateInset(i, h, rad);
    inst->drawFastHLine(x + sh + in, y + sh + i, w - 2 * in, shadow);
  }
  for (int i = 0; i < h; i++) {                          // shaded body + side bevels
    int in = plateInset(i, h, rad);
    int k  = 330 - 180 * i / (h > 1 ? h - 1 : 1);        // lit top -> shadowed bottom
    uint16_t row = (i < 2) ? lit : (i == h - 1) ? dark : plateShade(r, g, b, k);
    inst->drawFastHLine(x + in, y + i, w - 2 * in, row);
    if (i >= 2 && i < h - 1) {
      inst->drawPixel(x + in, y + i, lit);               // left edge lit
      inst->drawPixel(x + w - 1 - in, y + i, dark);      // right edge dark
    }
  }
}

//  Size-2 text stamped into a plate: highlight 1 px down-right, then black.
static void ui3DText(int x, int y, const char* s, uint16_t hi) {
  inst->setTextSize(2);
  inst->setTextColor(hi);
  inst->setCursor(x + 1, y + 1); inst->print(s);
  inst->setTextColor(BLACK);
  inst->setCursor(x, y);         inst->print(s);
}
static uint16_t plateHiMagenta() { return plateShade(0xFF, 0xB0, 0xBE, 256); }   // on red plates
static uint16_t plateHiCyan()    { return plateShade(0xB0, 0xFF, 0xFF, 256); }

//  The magenta title plate every list view opens with.
static void ui3DHeader(const char* title) {
  ui3DPlate(6, MENU_HEAD_Y, TFT_W - 12 - PLATE_SHADOW, MENU_HEAD_H, PLATE_MAGENTA,
            PLATE_RADIUS, PLATE_SHADOW);
  ui3DText(12, MENU_HEAD_Y + (MENU_HEAD_H - 16) / 2, title, plateHiMagenta());
}

//  A selected list row: a cyan plate the full width of (x, w), h tall.
static void ui3DSelect(int x, int y, int w, int h) {
  ui3DPlate(x, y, w - PLATE_SHADOW_SEL, h, PLATE_CYAN, PLATE_RADIUS_SEL, PLATE_SHADOW_SEL);
}

//  An on-screen button: selected is a raised 3D plate (cyan, or magenta for
//  a primary / confirm action) with stamped black text; unselected is cyan
//  text on the dark background with a grid-line outline. Used by the image
//  viewer, the compass and the sequence player. No default argument on
//  purpose: the .ino prototype generator duplicates defaults and breaks the
//  build.
static void uiButton(int x, int y, int w, int h, const char* lab, bool sel,
                     uint16_t plate) {
  int tx = x + (w - (int)strlen(lab) * 12) / 2, ty = y + (h - 16) / 2;
  if (sel) {
    bool mag = (plate == NEON_MAGENTA);
    if (mag) ui3DPlate(x, y, w - PLATE_SHADOW_SEL, h, PLATE_MAGENTA, PLATE_RADIUS_SEL, PLATE_SHADOW_SEL);
    else     ui3DPlate(x, y, w - PLATE_SHADOW_SEL, h, PLATE_CYAN,    PLATE_RADIUS_SEL, PLATE_SHADOW_SEL);
    ui3DText(tx - 1, ty, lab, mag ? plateHiMagenta() : plateHiCyan());
  } else {
    inst->fillRect(x, y, w, h, CYBER_BG);
    inst->drawRect(x, y, w, h, CYBER_GRID);
    inst->setTextSize(2);
    inst->setTextColor(NEON_CYAN);
    inst->setCursor(tx, ty);
    inst->print(lab);
  }
}

//  Title plate for the non-menu views, so the current mode is always named.
static void uiTag(const char* text, uint16_t col) {
  int w = (int)strlen(text) * 6 + 14;
  inst->fillRect(6, 5, w, 13, col);
  inst->fillTriangle(6 + w - 1, 5, 6 + w - 1, 17, 6 + w - 9, 5, CYBER_BG);
  inst->setTextSize(1);
  inst->setTextColor(BLACK);
  inst->setCursor(11, 8);
  inst->print(text);
}

// -------------------------------------------------------------
//  Settings — screen orientation and IMU/compass, persisted to NVS
// -------------------------------------------------------------
enum SetPage : uint8_t { SET_ROOT, SET_SCREEN, SET_CAM, SET_THERM, SET_IMU, SET_WIFI };
static SetPage  setPage = SET_ROOT;
static uint8_t  setSel  = 0;
static const uint8_t kSetCount[] = { 6, 4, 4, 4, 4, 5 };   // items per page

//  Apply the two flip toggles over the panel's base MADCTL. On the ST7789
//  the 34px CGRAM margin is symmetric (34+172+34 = 240), so mirroring either
//  axis does NOT move it — the flips are safe without touching the offset.
void applyOrientation() {
  uint8_t m = PANEL_MADCTL ^ (scrFlipX ? 0x40 : 0) ^ (scrFlipY ? 0x80 : 0);
  tft.setMadctl(m);
}

//  Push the visible-camera flips into the OV5640 if it is up. If it is not,
//  initCamera() reads the same vars when it runs, so the setting still holds.
void applyCamOrientation() {
#if CAM_ENABLE
  sensor_t* sn = esp_camera_sensor_get();
  if (sn) { sn->set_vflip(sn, camFlipV); sn->set_hmirror(sn, camFlipH); }
#endif
}

void settingsLoad() {
  prefs.begin("servoctl", true);          // read-only
  scrFlipX      = prefs.getBool("flipx", false);
  scrFlipY      = prefs.getBool("flipy", false);
  compassOffset = prefs.getFloat("north", COMP_HDG_OFFSET);
  camFlipH   = prefs.getBool("cfh", CAM_HMIRROR);
  camFlipV   = prefs.getBool("cfv", CAM_VFLIP);
  thermFlipH = prefs.getBool("tfh", THERM_HMIRROR);
  thermFlipV = prefs.getBool("tfv", THERM_VFLIP);
  i2cHz      = prefs.getUInt("i2chz", MLX_I2C_HZ);   // "i2c hz <n>" (diagnostic)
  imuMountDeg = prefs.getUShort("imurot", 0);         // BNO085 mount turn
  if (imuMountDeg % 90 || imuMountDeg >= 360) imuMountDeg = 0;
  prefs.end();
}
static void settingsSaveCams() {
  prefs.begin("servoctl", false);
  prefs.putBool("cfh", camFlipH);  prefs.putBool("cfv", camFlipV);
  prefs.putBool("tfh", thermFlipH);prefs.putBool("tfv", thermFlipV);
  prefs.end();
}
static void settingsSaveScreen() {
  prefs.begin("servoctl", false);
  prefs.putBool("flipx", scrFlipX);
  prefs.putBool("flipy", scrFlipY);
  prefs.end();
}
static void settingsSaveNorth() {
  prefs.begin("servoctl", false);
  prefs.putFloat("north", compassOffset);
  prefs.end();
}

//  One row of the settings list: label left, optional state on the right.
static void setRow(int y, bool sel, const char* label, const char* state,
                   uint16_t stateCol) {
  int h = 22;
  if (sel) {
    ui3DSelect(12, y, TFT_W - 24, h);
    inst->fillTriangle(3, y + 4, 3, y + h - 4, 10, y + h / 2, NEON_MAGENTA);
    ui3DText(22, y + 3, label, plateHiCyan());
  } else {
    inst->drawFastVLine(12, y, h, CYBER_GRID);
    inst->drawFastHLine(12, y + h - 1, TFT_W - 24, CYBER_GRID);
    inst->setTextSize(2);
    inst->setTextColor(NEON_CYAN);
    inst->setCursor(22, y + 3);
    inst->print(label);
  }
  if (state) {
    inst->setTextSize(1);
    inst->setTextColor(sel ? BLACK : stateCol);
    inst->setCursor(TFT_W - 20 - (int)strlen(state) * 6, y + 7);
    inst->print(state);
  }
}

void uiViewSettings() {
  inst->fillScreen(CYBER_BG);

  //  Header plate names the current page.
  const char* title = (setPage == SET_SCREEN) ? "SCREEN"
                    : (setPage == SET_CAM)    ? "CAMERA"
                    : (setPage == SET_THERM)  ? "THERMAL CAMERA"
                    : (setPage == SET_IMU)    ? "IMU / COMPASS"
                    : (setPage == SET_WIFI)   ? "WIFI" : "SETTINGS";
  ui3DHeader(title);

  //  Rows are 22 px; the pitch tightens on pages with more rows so they all
  //  still fit above the bottom edge (6 rows -> 23 px on the 172 px panel).
  const int top = 30;
  int pitch = (TFT_H - 4 - top - 22) / (kSetCount[setPage] > 1 ? kSetCount[setPage] - 1 : 1);
  if (pitch > 27) pitch = 27;
  if (setPage == SET_ROOT) {
    setRow(top + 0 * pitch, setSel == 0, "SCREEN",   ">", CYBER_DIMTXT);
    setRow(top + 1 * pitch, setSel == 1, "CAMERA",   ">", CYBER_DIMTXT);
    setRow(top + 2 * pitch, setSel == 2, "THERMAL",  ">", CYBER_DIMTXT);
    setRow(top + 3 * pitch, setSel == 3, "IMU/COMP", ">", CYBER_DIMTXT);
    setRow(top + 4 * pitch, setSel == 4, "WIFI",     ">", CYBER_DIMTXT);
    setRow(top + 5 * pitch, setSel == 5, "< BACK",   nullptr, 0);
  } else if (setPage == SET_WIFI) {
#if WEB_ENABLE && SERVO_ENABLE
    //  Row 0 is status only: which mode the web controller is in and the
    //  address to browse to.
    char ip[20];
    strncpy(ip, (webApMode ? WiFi.softAPIP() : WiFi.localIP()).toString().c_str(), sizeof(ip));
    ip[sizeof(ip) - 1] = '\0';
    setRow(top + 0 * pitch, setSel == 0, webApMode ? "HOTSPOT" : "JOINED", ip,
           webRunning ? NEON_GREEN : CYBER_DIMTXT);
    setRow(top + 1 * pitch, setSel == 1, "JOIN NETWORK", ">", CYBER_DIMTXT);
    setRow(top + 2 * pitch, setSel == 2, "USE HOTSPOT", webApMode ? "ON" : nullptr, NEON_GREEN);
    setRow(top + 3 * pitch, setSel == 3, "FORGET",   nullptr, 0);
#else
    setRow(top + 0 * pitch, setSel == 0, "WEB OFF", "WEB_ENABLE 0", CYBER_DIMTXT);
#endif
    setRow(top + 4 * pitch, setSel == 4, "< BACK",   nullptr, 0);
  } else if (setPage == SET_CAM) {
    setRow(top + 0 * pitch, setSel == 0, "FLIP H",  camFlipH ? "ON" : "OFF",
           camFlipH ? NEON_GREEN : CYBER_DIMTXT);
    setRow(top + 1 * pitch, setSel == 1, "FLIP V",  camFlipV ? "ON" : "OFF",
           camFlipV ? NEON_GREEN : CYBER_DIMTXT);
    setRow(top + 2 * pitch, setSel == 2, "ROT 180", nullptr, 0);
    setRow(top + 3 * pitch, setSel == 3, "< BACK",  nullptr, 0);
  } else if (setPage == SET_THERM) {
    setRow(top + 0 * pitch, setSel == 0, "FLIP H",  thermFlipH ? "ON" : "OFF",
           thermFlipH ? NEON_GREEN : CYBER_DIMTXT);
    setRow(top + 1 * pitch, setSel == 1, "FLIP V",  thermFlipV ? "ON" : "OFF",
           thermFlipV ? NEON_GREEN : CYBER_DIMTXT);
    setRow(top + 2 * pitch, setSel == 2, "ROT 180", nullptr, 0);
    setRow(top + 3 * pitch, setSel == 3, "< BACK",  nullptr, 0);
  } else if (setPage == SET_SCREEN) {
    setRow(top + 0 * pitch, setSel == 0, "FLIP H",  scrFlipX ? "ON" : "OFF",
           scrFlipX ? NEON_GREEN : CYBER_DIMTXT);
    setRow(top + 1 * pitch, setSel == 1, "FLIP V",  scrFlipY ? "ON" : "OFF",
           scrFlipY ? NEON_GREEN : CYBER_DIMTXT);
    setRow(top + 2 * pitch, setSel == 2, "ROT 180", nullptr, 0);
    setRow(top + 3 * pitch, setSel == 3, "< BACK",  nullptr, 0);
  } else {  // SET_IMU
    char hdg[12];
    if (imuAlive()) snprintf(hdg, sizeof(hdg), "%03d", (int)lroundf(compassHeading()) % 360);
    else            strcpy(hdg, "--");
    setRow(top + 0 * pitch, setSel == 0, "SET N HERE", hdg,
           imuAlive() ? NEON_GREEN : NEON_RED);
    setRow(top + 1 * pitch, setSel == 1, "RESET N",  nullptr, 0);
    //  How the BNO085 is turned on this board (CCW from above). ENTER cycles
    //  0 -> 90 -> 180 -> 270; the v6 PCB wants 270.
    char rot[8];
    snprintf(rot, sizeof(rot), "%u", imuMountDeg);
    setRow(top + 2 * pitch, setSel == 2, "MOUNT",    rot,
           imuMountDeg ? NEON_CYAN : CYBER_DIMTXT);
    setRow(top + 3 * pitch, setSel == 3, "< BACK",   nullptr, 0);
  }

  uiFrame(CYBER_GRID);
  uiScanlines();
  uiBlit();
}

//  Act on the highlighted settings row.
void settingsActivate() {
  if (setPage == SET_ROOT) {
    if      (setSel == 0) { setPage = SET_SCREEN; setSel = 0; }
    else if (setSel == 1) { setPage = SET_CAM;    setSel = 0; }
    else if (setSel == 2) { setPage = SET_THERM;  setSel = 0; }
    else if (setSel == 3) { setPage = SET_IMU;    setSel = 0; }
    else if (setSel == 4) { setPage = SET_WIFI;   setSel = 1; }
    else                  { uiEnter(UI_MENU); return; }
  } else if (setPage == SET_WIFI) {
#if WEB_ENABLE && SERVO_ENABLE
    //  Same saved effect as the web page's buttons, but no restart: the web
    //  task switches back to the hotspot live (webGoAp), and the status row
    //  above shows HOTSPOT 192.168.4.1 once it has. USE HOTSPOT keeps the
    //  saved network for later; FORGET erases it.
    if (setSel == 1) { uiEnter(UI_NETPICK); return; }
    if (setSel == 2 || setSel == 3) {
      prefs.begin("wifi", false);
      if (setSel == 2) prefs.putString("netmode", "ap"); else prefs.clear();
      prefs.end();
      webGoAp = true;
      toast(setSel == 2 ? "HOTSPOT ON" : "NETWORK FORGOTTEN", NEON_CYAN);
    }
#endif
    if (setSel == 4) { setPage = SET_ROOT; setSel = 4; uiLastDraw = 0; return; }
  } else if (setPage == SET_CAM) {
    if      (setSel == 0) camFlipH ^= 1;
    else if (setSel == 1) camFlipV ^= 1;
    else if (setSel == 2) { camFlipH ^= 1; camFlipV ^= 1; }
    else                  { setPage = SET_ROOT; setSel = 1; uiLastDraw = 0; return; }
    applyCamOrientation();
    settingsSaveCams();
  } else if (setPage == SET_THERM) {
    if      (setSel == 0) thermFlipH ^= 1;
    else if (setSel == 1) thermFlipV ^= 1;
    else if (setSel == 2) { thermFlipH ^= 1; thermFlipV ^= 1; }
    else                  { setPage = SET_ROOT; setSel = 2; uiLastDraw = 0; return; }
    settingsSaveCams();          // thermal flips are read live by the renderer
  } else if (setPage == SET_SCREEN) {
    if      (setSel == 0) scrFlipX ^= 1;
    else if (setSel == 1) scrFlipY ^= 1;
    else if (setSel == 2) { scrFlipX ^= 1; scrFlipY ^= 1; }   // 180 = both
    else                  { setPage = SET_ROOT; setSel = 0; uiLastDraw = 0; return; }
    applyOrientation();
    settingsSaveScreen();
  } else {  // SET_IMU
    if (setSel == 0) {
      //  Make the current heading read north (0). Only meaningful with a live
      //  sensor — the BNO085 in RVC mode is receive-only, so this offsets the
      //  displayed heading rather than commanding the chip's own mag cal.
      if (imuAlive()) { compassOffset = -imuYaw; settingsSaveNorth(); }
    } else if (setSel == 1) { compassOffset = COMP_HDG_OFFSET; settingsSaveNorth(); }
    else if (setSel == 2)   { imuMountSet(imuMountDeg + 90); }   // wraps at 360
    else                    { setPage = SET_ROOT; setSel = 3; uiLastDraw = 0; return; }
  }
  uiLastDraw = 0;
}

#if BLE_ENABLE
// -------------------------------------------------------------
//  BLE surveillance / tracker detection (NimBLE, listen-only)
//
//  A passive scan. Every advertisement is matched against known tracker and
//  surveillance signatures — Apple Find My / AirTag, Tile, Samsung SmartTag,
//  Google Find My, Ray-Ban Meta glasses, OpenDroneID drones, Flipper Zero,
//  Raven gunshot sensors — by BLE service UUID and manufacturer company ID.
//  Nothing is transmitted or connected to. Signatures ported from
//  SquachWatch-CYD (GPLv3); the IDs are public Bluetooth SIG assignments.
//
//  NOTE: Bluetooth-Classic skimmers (HC-05 and friends) are NOT visible to a
//  BLE scan — that needs a Classic inquiry, a separate, heavier radio mode.
// -------------------------------------------------------------
struct BleUuidRow { uint16_t uuid; DetType type; };
struct BleMfgRow  { uint16_t id;   DetType type; };

static const BleUuidRow kBleUuid[] = {
  {0xFEED, DET_TILE}, {0xFEEC, DET_TILE}, {0xFD5F, DET_META}, {0xFFFA, DET_DRONE},
  {0xFD5A, DET_SAMSUNG}, {0xFEAA, DET_GOOGLE},
  {0x3081, DET_HACKER}, {0x3082, DET_HACKER}, {0x3083, DET_HACKER},   // Flipper
  {0x3100, DET_RAVEN}, {0x3200, DET_RAVEN}, {0x3300, DET_RAVEN},
  {0x3400, DET_RAVEN}, {0x3500, DET_RAVEN},
};
static const BleMfgRow kBleMfg[] = {
  {0x09C8, DET_FLOCK},                                     // Flock BLE radio
  {0x01AB, DET_META}, {0x058E, DET_META}, {0x0D53, DET_META}, {0x03C2, DET_META},
  {0x0E29, DET_HACKER},                                    // Flipper Devices
};
#define BLE_UUID_COUNT (sizeof(kBleUuid)/sizeof(kBleUuid[0]))
#define BLE_MFG_COUNT  (sizeof(kBleMfg)/sizeof(kBleMfg[0]))

static DetType lookupBleUuid(uint16_t u) {
  for (uint16_t i = 0; i < BLE_UUID_COUNT; i++) if (kBleUuid[i].uuid == u) return kBleUuid[i].type;
  return DET_NONE;
}
static DetType lookupBleMfg(uint16_t id) {
  for (uint16_t i = 0; i < BLE_MFG_COUNT; i++) if (kBleMfg[i].id == id) return kBleMfg[i].type;
  return DET_NONE;
}

#define BLE_MAX      16
#define BLE_STALE_MS 15000
struct BleEnt { uint8_t mac[6]; int8_t rssi; DetType det; char name[14]; uint32_t seen; };
static BleEnt   bleList[BLE_MAX];
static volatile uint8_t  bleCount = 0;
static volatile uint32_t bleAdverts = 0;     // total adverts heard, for "is it alive"
static portMUX_TYPE bleMux = portMUX_INITIALIZER_UNLOCKED;
static bool     bleInited = false, bleScanning = false;
static uint8_t  blePage = 0;

//  Record a flagged device. Runs on the NimBLE host task, so the array is
//  touched only inside a short critical section shared with the renderer.
static void bleRecord(const uint8_t* mac, int8_t rssi, DetType det, const char* nm) {
  portENTER_CRITICAL(&bleMux);
  int slot = -1;
  for (uint8_t i = 0; i < bleCount; i++)
    if (memcmp(bleList[i].mac, mac, 6) == 0) { slot = i; break; }
  if (slot < 0) {
    if (bleCount < BLE_MAX) slot = bleCount++;
    else {                              // replace the stalest
      uint32_t oldest = 0xFFFFFFFF;
      for (uint8_t i = 0; i < BLE_MAX; i++) if (bleList[i].seen < oldest) { oldest = bleList[i].seen; slot = i; }
    }
    memcpy(bleList[slot].mac, mac, 6);
  }
  bleList[slot].rssi = rssi;
  bleList[slot].det  = det;
  bleList[slot].seen = millis();
  if (nm && nm[0]) { strncpy(bleList[slot].name, nm, 13); bleList[slot].name[13] = '\0'; }
  else             { bleList[slot].name[0] = '\0'; }
  portEXIT_CRITICAL(&bleMux);
}

class BleCb : public NimBLEScanCallbacks {
  void onResult(const NimBLEAdvertisedDevice* d) override {
    bleAdverts++;
    DetType det = DET_NONE;

    for (uint8_t i = 0; i < d->getServiceUUIDCount() && det == DET_NONE; i++) {
      NimBLEUUID u = d->getServiceUUID(i);
      if (u.bitSize() == 16) {
        const uint8_t* v = u.getValue();
        det = lookupBleUuid((uint16_t)(v[0] | (v[1] << 8)));
      }
    }
    if (det == DET_NONE && d->haveManufacturerData()) {
      std::string md = d->getManufacturerData(0);
      if (md.size() >= 2) {
        uint16_t cid = (uint8_t)md[0] | ((uint8_t)md[1] << 8);
        if (cid == 0x004C) {            // Apple: distinguish Find My vs iBeacon
          if (md.size() >= 4 && (uint8_t)md[2] == 0x12 && (uint8_t)md[3] == 0x19) det = DET_AIRTAG;
          else if (md.size() >= 4 && (uint8_t)md[2] == 0x02 && (uint8_t)md[3] == 0x15) det = DET_IBEACON;
          //  bare Apple data is too common to flag on its own
        } else {
          det = lookupBleMfg(cid);
        }
      }
    }
    if (det == DET_NONE) return;

    std::string nm = d->getName();
    bleRecord(d->getAddress().getVal(), d->getRSSI(), det, nm.c_str());
  }
};
static BleCb bleCb;

//  Why Bluetooth could not start, for the view to show ("" = it's fine).
static char bleErr[40] = "";

// ── Bluetooth crash post-mortem ──
//  Some start-up failures cannot be caught: nimble_port_init() and the host
//  task creation assert (abort -> reboot) instead of returning an error, and
//  a brownout or watchdog reset gives no chance to report either. So each
//  step is written to RTC memory, which survives a reset, before it runs.
//  At the next boot bleDiagBoot() turns an unfinished record plus the reset
//  reason into bleLast, and the BLE view then shows it and waits for ENTER
//  instead of walking straight back into the same crash.
#define BLE_DIAG_MAGIC 0xB1E5EED5u
//  Reset history, kept across reboots in RTC memory (cleared only by a real
//  power-up), so a reset nobody saw on the console can still be explained
//  afterwards: "resets". setup() turns the brownout detector off (camera
//  inrush), so a supply dip shows up here as a glitch / watchdog / crash.
#include "esp32s3/rom/rtc.h"   // rtc_get_reset_reason()
#define RST_HIST_N 8
RTC_NOINIT_ATTR static uint32_t rstHistMagic, rstHistCount;
RTC_NOINIT_ATTR static uint16_t rstHist[RST_HIST_N];   // (ROM code << 8) | esp_reset_reason()
static void resetHistoryBoot() {
  if (rstHistMagic != 0x52535448) { rstHistMagic = 0x52535448; rstHistCount = 0; memset(rstHist, 0, sizeof rstHist); }
  rstHist[rstHistCount % RST_HIST_N] = (uint16_t)((((int)rtc_get_reset_reason(0)) & 0xFF) << 8 | (((int)esp_reset_reason()) & 0xFF));
  rstHistCount++;
}
static const char* romResetName(int r) {      // esp32s3/rom/rtc.h RESET_REASON
  switch (r) {
    case 1:  return "power-on";
    case 3:  return "software restart";
    case 5:  return "deep-sleep wake";
    case 7:  case 8:  return "timer-group watchdog (system)";
    case 9:  return "RTC watchdog (system)";
    case 11: case 17: return "timer-group watchdog (CPU)";
    case 12: return "software CPU reset";
    case 13: return "RTC watchdog (CPU)";
    case 15: return "BROWNOUT";
    case 16: return "RTC watchdog (whole chip)";
    case 18: return "super watchdog";
    case 19: return "GLITCH (RTC) - supply dip?";
    case 20: return "efuse error";
    case 21: return "USB serial (host port open / esptool)";
    case 22: return "USB JTAG";
    case 23: return "POWER GLITCH - supply dip";
    default: return "?";
  }
}
static const char* resetName(int r) {         // esp_reset_reason_t
  switch (r) {
    case ESP_RST_POWERON:  return "power-on";
    case ESP_RST_EXT:      return "reset pin";
    case ESP_RST_SW:       return "software";
    case ESP_RST_PANIC:    return "CRASH (panic)";
    case ESP_RST_INT_WDT:  return "interrupt watchdog";
    case ESP_RST_TASK_WDT: return "task watchdog";
    case ESP_RST_WDT:      return "other watchdog";
    case ESP_RST_BROWNOUT: return "brownout";
    default:               return "unknown";
  }
}
void resetConsole() {
  Serial.printf("up %lu s; last %d boots, newest last:\n", (unsigned long)(millis() / 1000),
                (int)(rstHistCount < RST_HIST_N ? rstHistCount : RST_HIST_N));
  const uint32_t n = rstHistCount < RST_HIST_N ? rstHistCount : RST_HIST_N;
  for (uint32_t i = rstHistCount - n; i < rstHistCount; i++) {
    const uint16_t h = rstHist[i % RST_HIST_N];
    Serial.printf("  boot %lu  rst:0x%02x %-38s idf: %s\n", (unsigned long)i + 1, h >> 8, romResetName(h >> 8), resetName(h & 0xFF));
  }
}

RTC_NOINIT_ATTR static uint32_t bleDiagMagic, bleDiagStage, bleDiagFree, bleDiagBlock;
enum { BLE_ST_NONE, BLE_ST_INIT, BLE_ST_SCAN, BLE_ST_RUNNING };
static char bleLast[48]  = "";            // "" = no crash on record
static char bleLast2[40] = "";

static void bleDiagMark(uint32_t stage) {
  bleDiagMagic = BLE_DIAG_MAGIC;
  bleDiagStage = stage;
  bleDiagFree  = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
  bleDiagBlock = heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL);
}

//  setup(): read what the last Bluetooth attempt left behind, then clear it.
void bleDiagBoot() {
  if (bleDiagMagic == BLE_DIAG_MAGIC && bleDiagStage != BLE_ST_NONE) {
    esp_reset_reason_t rr = esp_reset_reason();
    const char* why = (rr == ESP_RST_PANIC)    ? "CRASHED"
                    : (rr == ESP_RST_BROWNOUT) ? "BROWNOUT (POWER DIP)"
                    : (rr == ESP_RST_INT_WDT || rr == ESP_RST_TASK_WDT || rr == ESP_RST_WDT)
                                               ? "WATCHDOG RESET" : "RESET";
    const char* where = (bleDiagStage == BLE_ST_INIT) ? "STARTING UP"
                      : (bleDiagStage == BLE_ST_SCAN) ? "STARTING SCAN" : "WHILE SCANNING";
    snprintf(bleLast,  sizeof(bleLast),  "%s %s", why, where);
    snprintf(bleLast2, sizeof(bleLast2), "RAM %luK FREE %luK BLOCK  RST %d",
             (unsigned long)(bleDiagFree / 1024), (unsigned long)(bleDiagBlock / 1024), (int)rr);
    Serial.printf("BLE post-mortem: %s - %s\n", bleLast, bleLast2);
  }
  bleDiagMagic = 0; bleDiagStage = BLE_ST_NONE;
}

//  Bring the radio up once, lazily, then run a forever scan. Kept off until
//  the BLE view is opened so a board that never uses it never powers BT.
//
//  NimBLEDevice::init() RETURNS FALSE when the controller cannot start —
//  typically no internal RAM for it, now that the Wi-Fi stack (web servo
//  control) is up from boot. This used to be ignored: the scan was then
//  started on a stack that never came up, which crashed and restarted the
//  board. Now a failure is cleaned up, reported on screen with the internal
//  heap figures, and retried the next time the view is opened.
void bleStart() {
#if BLE_ENABLE
  if (bleLast[0]) return;                   // crashed last time: wait for ENTER (see view)
  if (!bleInited) {
    size_t freeInt = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
    size_t bigInt  = heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL);
    Serial.printf("BLE: starting - internal heap %u free, largest block %u\n",
                  (unsigned)freeInt, (unsigned)bigInt);
    //  ESP-IDF rule for Wi-Fi + Bluetooth together: Wi-Fi modem sleep MUST
    //  be on, because the two radios timeslice the one antenna. The
    //  coexistence library aborts otherwise ("Should enable WiFi modem sleep
    //  when both WiFi and Bluetooth are enabled") — the web server turns
    //  sleep off at boot for snappier control, so this was the Bluetooth
    //  reboot (RST 4, crashed starting up). Minimum modem sleep costs the
    //  hotspot nothing (the AP side does not sleep); a joined STA link gains
    //  a little latency. It stays on afterwards: turning it off again with
    //  the Bluetooth controller up would trip the same check.
    btActive = true;                        // web code: never turn sleep back off
    if (WiFi.getMode() != WIFI_MODE_NULL) WiFi.setSleep(true);   // WIFI_PS_MIN_MODEM
    bleDiagMark(BLE_ST_INIT);
    if (!NimBLEDevice::init("")) {
      NimBLEDevice::deinit(true);
      snprintf(bleErr, sizeof(bleErr), "RAM %uK FREE %uK BLOCK",
               (unsigned)(freeInt / 1024), (unsigned)(bigInt / 1024));
      Serial.printf("BLE: init FAILED (%s)\n", bleErr);
      bleDiagStage = BLE_ST_NONE;           // failed cleanly — nothing to report
      return;
    }
    bleErr[0] = '\0';
    NimBLEScan* sc = NimBLEDevice::getScan();
    sc->setScanCallbacks(&bleCb, false);
    sc->setActiveScan(true);
    sc->setInterval(100);
    sc->setWindow(80);
    bleInited = true;
  }
  bleCount = 0;
  blePage  = 0;
  bleDiagMark(BLE_ST_SCAN);
  NimBLEDevice::getScan()->start(0, false, true);   // 0 = until stopped
  bleScanning = true;
  bleDiagMark(BLE_ST_RUNNING);              // a crash from here on = while scanning
#endif
}
void bleStop() {
#if BLE_ENABLE
  if (bleInited && bleScanning) { NimBLEDevice::getScan()->stop(); bleScanning = false; }
  bleDiagStage = BLE_ST_NONE;               // left cleanly: later resets aren't Bluetooth's
#endif
}

//  Drop entries not heard in BLE_STALE_MS. Called from the view.
static void bleAgeOut() {
  uint32_t now = millis();
  portENTER_CRITICAL(&bleMux);
  for (uint8_t i = 0; i < bleCount; ) {
    if (now - bleList[i].seen > BLE_STALE_MS) {
      bleList[i] = bleList[bleCount - 1]; bleCount--;
    } else i++;
  }
  portEXIT_CRITICAL(&bleMux);
}

static uint8_t blePages() { return bleCount ? (bleCount + 3) / 4 : 1; }
void bleNextPage() { if (++blePage >= blePages()) blePage = 0; }
void blePrevPage() { blePage = (blePage == 0) ? blePages() - 1 : blePage - 1; }

void uiViewBle() {
  inst->fillScreen(CYBER_BG);
  uiFrame(CYBER_GRID);
  if (bleLast[0]) {                           // the last attempt took the board down
    inst->setTextSize(2);
    inst->setTextColor(NEON_RED);
    const char* m = "BLUETOOTH RESET BOARD";
    inst->setCursor((TFT_W - (int)strlen(m) * 12) / 2, 22);
    inst->print(m);
    inst->setTextSize(1);
    inst->setTextColor(NEON_PINK);
    inst->setCursor((TFT_W - (int)strlen(bleLast) * 6) / 2, 52);
    inst->print(bleLast);
    inst->setTextColor(CYBER_DIMTXT);
    inst->setCursor((TFT_W - (int)strlen(bleLast2) * 6) / 2, 68);
    inst->print(bleLast2);
    const char* h1 = "ENTER = try again   LEFT = back";
    inst->setTextColor(NEON_CYAN);
    inst->setCursor((TFT_W - (int)strlen(h1) * 6) / 2, 100);
    inst->print(h1);
    uiScanlines();
    uiBlit();
    return;
  }
  if (!bleInited) {                           // start-up failed: say why, don't crash
    inst->setTextSize(2);
    inst->setTextColor(NEON_RED);
    const char* m = "BLUETOOTH FAILED";
    inst->setCursor((TFT_W - (int)strlen(m) * 12) / 2, TFT_H / 2 - 20);
    inst->print(m);
    inst->setTextSize(1);
    inst->setTextColor(CYBER_DIMTXT);
    const char* s = bleErr[0] ? bleErr : "not started";
    inst->setCursor((TFT_W - (int)strlen(s) * 6) / 2, TFT_H / 2 + 2);
    inst->print(s);
    const char* h = "back out and re-enter to retry";
    inst->setCursor((TFT_W - (int)strlen(h) * 6) / 2, TFT_H / 2 + 16);
    inst->print(h);
    uiScanlines();
    uiBlit();
    return;
  }
  bleAgeOut();

  //  Snapshot the shared list under the lock, then render from the copy.
  BleEnt view[BLE_MAX]; uint8_t n;
  portENTER_CRITICAL(&bleMux);
  n = bleCount; memcpy(view, bleList, n * sizeof(BleEnt));
  portEXIT_CRITICAL(&bleMux);

  if (n == 0) {
    inst->setTextSize(2);
    inst->setTextColor(bleAdverts ? NEON_GREEN : CYBER_DIMTXT);
    const char* msg = bleAdverts ? "NO TRACKERS" : "SCANNING";
    inst->setCursor((TFT_W - (int)strlen(msg) * 12) / 2, TFT_H / 2 - 8);
    inst->print(msg);
    inst->setTextSize(1);
    inst->setTextColor(CYBER_DIMTXT);
    char sub[24]; snprintf(sub, sizeof(sub), "%lu adverts heard", (unsigned long)bleAdverts);
    inst->setCursor((TFT_W - (int)strlen(sub) * 6) / 2, TFT_H / 2 + 12);
    inst->print(sub);
  } else {
    inst->setTextSize(1);
    inst->setTextColor(NEON_RED);
    char thr[16]; snprintf(thr, sizeof(thr), "%u NEARBY", n);
    inst->setCursor(TFT_W - 10 - (int)strlen(thr) * 6, 2);
    inst->print(thr);

    int first = blePage * 4;
    for (int r = 0; r < 4 && first + r < n; r++) {
      const BleEnt& b = view[first + r];
      int y = 8 + r * 40;
      inst->setTextSize(2);
      inst->setTextColor(NEON_RED);
      inst->setCursor(12, y);
      inst->print(detName(b.det));

      inst->setTextSize(1);
      inst->setTextColor(CYBER_DIMTXT);
      inst->setCursor(12, y + 18);
      if (b.name[0]) inst->print(b.name);
      else inst->printf("%02X:%02X:%02X", b.mac[5], b.mac[4], b.mac[3]);

      char rs[8]; snprintf(rs, sizeof(rs), "%d", b.rssi);
      inst->setTextSize(3);
      inst->setTextColor(b.rssi >= -60 ? NEON_GREEN : b.rssi >= -75 ? NEON_YELLOW : NEON_RED);
      inst->setCursor(TFT_W - 12 - (int)strlen(rs) * 18, y + 2);
      inst->print(rs);
    }
  }

  uiScanlines();
  uiBlit();
}
#endif  // BLE_ENABLE

// -------------------------------------------------------------
//  MAX-M10M-20B GNSS over I2C (u-blox DDC) + a minimal NMEA parser
//
//  The receiver sits at 0x42 on the shared bus and streams NMEA. Reading it
//  is: register 0xFD/0xFE = bytes available, then read that many from the
//  0xFF data register. We parse only GGA (fix/pos/alt/sats), RMC (speed/
//  validity) and GSV (satellites in view + signal, for "gps sky") — enough
//  for a position screen without pulling in a library.
//  Every bus access is fenced by i2cMutex, same as the MLX and the buttons.
// -------------------------------------------------------------
#if GPS_ENABLE                               // switch is with the others near the top
#define GPS_ADDR      0x42
#define GPS_STALE_MS  5000

static double   gpsLat = 0, gpsLon = 0;
static float    gpsAlt = 0, gpsHDOP = 0, gpsSpeedKn = 0;
static uint8_t  gpsFix = 0, gpsSats = 0;      // fix: 0 none, 1 GPS, 2 DGPS
static char     gpsUTC[10] = "";              // hhmmss.ss
static char     gpsDate[7] = "";              // ddmmyy (RMC)
static uint32_t gpsUTCMs = 0;                 // millis() when gpsUTC last arrived
static uint32_t gpsLastMs = 0, gpsBytes = 0;

//  ddmm.mmmm -> signed decimal degrees.
static double gpsDeg(const char* f, char hemi) {
  double v = atof(f);
  int    d = (int)(v / 100);
  double deg = d + (v - d * 100) / 60.0;
  if (hemi == 'S' || hemi == 'W') deg = -deg;
  return deg;
}

//  Satellites in view, from GSV: one row per satellite (and signal band),
//  kept for 15 s after it was last reported. GSV comes every 5 s by default.
#define GPS_SKY_MAX 48
static GpsSat gpsSky[GPS_SKY_MAX];

static void gpsSkyNote(char sys, int id, int sig, int elev, int az, int cno) {
  int slot = -1, oldest = 0;
  for (int i = 0; i < GPS_SKY_MAX; i++) {
    const GpsSat& g = gpsSky[i];
    if (g.ms && g.sys == sys && g.id == id && g.sig == sig) { slot = i; break; }
    if (g.ms < gpsSky[oldest].ms) oldest = i;
  }
  if (slot < 0)                                     // new: a free row, else the stalest
    for (int i = 0; i < GPS_SKY_MAX && slot < 0; i++) if (!gpsSky[i].ms) slot = i;
  if (slot < 0) slot = oldest;
  gpsSky[slot] = { sys, (uint8_t)id, (uint8_t)sig, (uint8_t)cno, (int8_t)elev, (uint16_t)az, millis() | 1 };
}

//  Split a comma sentence into up to 24 field pointers (in place).
static void gpsParse(char* line) {
  char* fld[24]; int nf = 0;
  fld[nf++] = line;
  for (char* c = line; *c && nf < 24; c++) if (*c == ',') { *c = '\0'; fld[nf++] = c + 1; }
  if (char* star = strchr(fld[nf - 1], '*')) *star = '\0';   // drop the checksum

  const char* t = fld[0];
  if (nf >= 10 && strstr(t, "GGA")) {
    strncpy(gpsUTC, fld[1], sizeof(gpsUTC) - 1); gpsUTC[sizeof(gpsUTC) - 1] = '\0';
    if (gpsUTC[0]) gpsUTCMs = millis();
    gpsFix  = (uint8_t)atoi(fld[6]);
    gpsSats = (uint8_t)atoi(fld[7]);
    gpsHDOP = atof(fld[8]);
    gpsAlt  = atof(fld[9]);
    if (gpsFix && fld[2][0]) { gpsLat = gpsDeg(fld[2], fld[3][0]);
                               gpsLon = gpsDeg(fld[4], fld[5][0]); gpsLastMs = millis(); }
  } else if (nf >= 8 && strstr(t, "RMC")) {
    if (nf >= 10 && strlen(fld[9]) == 6) memcpy(gpsDate, fld[9], 7);
    if (fld[7][0]) gpsSpeedKn = atof(fld[7]);
    if (fld[2][0] == 'A' && fld[3][0]) { gpsLat = gpsDeg(fld[3], fld[4][0]);
                                         gpsLon = gpsDeg(fld[5], fld[6][0]); gpsLastMs = millis(); }
  } else if (nf >= 4 && strstr(t, "GSV")) {
    //  $xxGSV,msgs,msg,inView,{id,elev,az,cno} x1..4[,signalId]
    const int blocks = (nf - 4) / 4;
    const int sig = ((nf - 4) % 4 == 1) ? (int)strtol(fld[nf - 1], nullptr, 16) : 0;
    const char sys = t[2] == 'P' ? 'G' : t[2] == 'L' ? 'R' : t[2] == 'A' ? 'E'
                   : (t[2] == 'B' || t[2] == 'D') ? 'C' : t[2] == 'Q' ? 'J' : '?';
    for (int b = 0; b < blocks; b++) {
      char** f = &fld[4 + b * 4];
      if (!f[0][0]) continue;
      gpsSkyNote(sys, atoi(f[0]), sig, f[1][0] ? atoi(f[1]) : -1, atoi(f[2]), f[3][0] ? atoi(f[3]) : 0);
    }
  }
}

//  Pull whatever the receiver has and feed the line assembler. Bounded so a
//  flood cannot stall the UI; leftover bytes come on the next poll.
void gpsPoll() {
  if (!i2cMutex) return;
  static char line[100]; static uint8_t len = 0;
  //  A receiver that is not answering is only retried every 5 s, so it
  //  cannot keep adding I2C timeouts to every pass.
  static uint8_t  fails = 0;
  static uint32_t retryAt = 0;
  if (fails >= 3 && (int32_t)(millis() - retryAt) < 0) return;

  uint16_t avail = 0;
  if (xSemaphoreTake(i2cMutex, pdMS_TO_TICKS(10)) != pdTRUE) return;
  Wire.beginTransmission(GPS_ADDR);
  Wire.write(0xFD);
  if (Wire.endTransmission(false) == 0 && Wire.requestFrom((int)GPS_ADDR, 2) == 2) {
    avail = ((uint16_t)Wire.read() << 8) | Wire.read();
    fails = 0;
  } else {
    i2cNoteFail("GNSS 0x42", i2cErrGps);
    if (fails < 255) fails++;
    retryAt = millis() + 5000;
  }
  uint16_t want = avail > 96 ? 96 : avail;    // cap per poll
  uint8_t  buf[96]; int got = 0;
  if (want) {
    Wire.beginTransmission(GPS_ADDR);
    Wire.write(0xFF);
    Wire.endTransmission(false);
    got = Wire.requestFrom((int)GPS_ADDR, (int)want);
    for (int i = 0; i < got; i++) buf[i] = Wire.read();
  }
  xSemaphoreGive(i2cMutex);

  gpsBytes += got;
  for (int i = 0; i < got; i++) {
    char c = (char)buf[i];
    if (c == 0xFF) continue;                  // idle filler when nothing queued
    if (c == '\n' || c == '\r') {
      if (len) { line[len] = '\0'; if (line[0] == '$') gpsParse(line); len = 0; }
    } else if (len < sizeof(line) - 1) line[len++] = c;
  }
}

bool gpsAlive() { return gpsFix && (millis() - gpsLastMs) < GPS_STALE_MS; }

//  Console "gps": poll the receiver a few times from here (it is otherwise
//  only read while the GPS view is open) and report what came back.
void gpsReport() {
  uint32_t before = gpsBytes, errs = i2cErrGps;
  for (int i = 0; i < 20; i++) { gpsPoll(); delay(50); }   // ~1 s of stream
  Serial.printf("GNSS @0x%02X: %lu bytes this second, %lu total, %lu read errors\n",
                GPS_ADDR, (unsigned long)(gpsBytes - before), (unsigned long)gpsBytes,
                (unsigned long)(i2cErrGps - errs));
  Serial.printf("  fix %u  sats %u  hdop %.1f  utc %s  %s\n", gpsFix, gpsSats, gpsHDOP,
                gpsUTC[0] ? gpsUTC : "-",
                gpsBytes == before ? "(no data: not answering, or nothing queued)"
                : gpsFix ? "(position valid)" : "(data flowing, no fix - antenna?)");
}

//  Console "gps sky": listen ~6 s (GSV comes every 5 s), then list every
//  satellite heard with its signal strength. C/N0 is what decides a fix:
//  under ~25 dB-Hz it is seen but too weak to use; 35+ is healthy.
void gpsSkyReport() {
  Serial.println("listening for satellites (6 s)...");
  for (int i = 0; i < 120; i++) { gpsPoll(); delay(50); }
  const uint32_t now = millis();
  int idx[GPS_SKY_MAX], n = 0;
  for (int i = 0; i < GPS_SKY_MAX; i++) if (gpsSky[i].ms && now - gpsSky[i].ms < 15000) idx[n++] = i;
  for (int a = 1; a < n; a++)                                  // strongest first
    for (int b = a; b > 0 && gpsSky[idx[b]].cno > gpsSky[idx[b - 1]].cno; b--) { int x = idx[b]; idx[b] = idx[b - 1]; idx[b - 1] = x; }
  if (!n) { Serial.println("no satellites reported - antenna not connected, or no sky view"); return; }
  int strong = 0, usable = 0, weak = 0, silent = 0;
  Serial.println("  SAT   ELEV   AZ  C/N0  signal");
  for (int k = 0; k < n; k++) {
    const GpsSat& g = gpsSky[idx[k]];
    char bar[21]; int nb = g.cno / 2; if (nb > 20) nb = 20;
    memset(bar, '#', nb); bar[nb] = '\0';
    const char* q = !g.cno ? "not heard" : g.cno < 25 ? "weak" : g.cno < 35 ? "ok" : "strong";
    if (!g.cno) silent++; else if (g.cno < 25) weak++; else if (g.cno < 35) usable++; else strong++;
    char el[6]; if (g.elev < 0) strcpy(el, "--"); else snprintf(el, sizeof el, "%d", g.elev);
    Serial.printf("  %c%-3u  %4s  %3u  %3u   %-20s %s\n", g.sys, g.id, el, g.az, g.cno, bar, q);
  }
  Serial.printf("%d listed: %d strong (35+), %d ok (25-34), %d weak (<25), %d not heard\n",
                n, strong, usable, weak, silent);
  Serial.println("  G=GPS E=Galileo C=BeiDou R=GLONASS J=QZSS. A fix needs 4+ at 25+ dB-Hz;");
  Serial.println("  a first fix wants ~30 s of unbroken signal from each.");
  Serial.printf("receiver: fix %u, %u used, hdop %.1f, utc %s\n", gpsFix, gpsSats, gpsHDOP, gpsUTC[0] ? gpsUTC : "-");
}

//  The satellites currently heard, one per satellite (strongest signal band
//  kept), strongest first. Returns how many went into out[].
static int gpsSkyList(GpsSat* out, int max) {
  const uint32_t now = millis();
  int n = 0;
  for (int i = 0; i < GPS_SKY_MAX; i++) {
    const GpsSat& g = gpsSky[i];
    if (!g.ms || now - g.ms >= 15000) continue;
    int k = 0;
    while (k < n && !(out[k].sys == g.sys && out[k].id == g.id)) k++;
    if (k < n) { if (g.cno > out[k].cno) out[k] = g; continue; }
    if (n < max) out[n++] = g;
  }
  for (int a = 1; a < n; a++)
    for (int b = a; b > 0 && out[b].cno > out[b - 1].cno; b--) { GpsSat x = out[b]; out[b] = out[b - 1]; out[b - 1] = x; }
  return n;
}

static uint16_t gpsCnoColor(uint8_t cno) {
  return !cno ? CYBER_DIMTXT : cno < 25 ? NEON_RED : cno < 35 ? NEON_YELLOW : NEON_GREEN;
}

//  GPS page 3 (ENTER from the details): the sky. Left, a plot looking up -
//  centre is straight overhead, the ring is the horizon, north at the top -
//  with each satellite coloured by signal. Right, the strongest as bars.
static void uiViewGpsSky() {
  inst->fillScreen(CYBER_BG);
  uiFrame(CYBER_GRID);
  GpsSat sv[GPS_SKY_MAX];
  const int n = gpsSkyList(sv, GPS_SKY_MAX);
  int strong = 0, ok = 0, weak = 0;
  for (int i = 0; i < n; i++) { if (sv[i].cno >= 35) strong++; else if (sv[i].cno >= 25) ok++; else if (sv[i].cno) weak++; }

  inst->setTextSize(2); inst->setTextColor(NEON_MAGENTA);
  inst->setCursor(10, 6); inst->print("SKY");
  char b[40];
  inst->setTextSize(1);
  if (gpsAlive()) snprintf(b, sizeof b, "FIX  %u USED", gpsSats);
  else            snprintf(b, sizeof b, "NO FIX  %u USED", gpsSats);
  inst->setTextColor(gpsAlive() ? NEON_GREEN : NEON_YELLOW);
  inst->setCursor(296 - 6 * (int)strlen(b), 6); inst->print(b);
  snprintf(b, sizeof b, "%d STRONG %d OK %d WEAK", strong, ok, weak);
  inst->setTextColor(CYBER_DIMTXT);
  inst->setCursor(296 - 6 * (int)strlen(b), 17); inst->print(b);

  //  The sky plot.
  const int cx = 80, cy = 100, R = 58;
  inst->drawCircle(cx, cy, R, CYBER_GRID);
  inst->drawCircle(cx, cy, R * 2 / 3, CYBER_GRID);             // 30 deg up
  inst->drawCircle(cx, cy, R / 3, CYBER_GRID);                 // 60 deg up
  inst->drawFastHLine(cx - R, cy, 2 * R + 1, CYBER_GRID);
  inst->drawFastVLine(cx, cy - R, 2 * R + 1, CYBER_GRID);
  inst->setTextColor(CYBER_DIMTXT);
  inst->setCursor(cx - 2, cy - R - 9);  inst->print("N");
  inst->setCursor(cx + R + 4, cy - 3);  inst->print("E");
  inst->setCursor(cx - 2, cy + R + 3);  inst->print("S");
  inst->setCursor(cx - R - 9, cy - 3);  inst->print("W");
  for (int i = n - 1; i >= 0; i--) {                           // strongest drawn last, on top
    if (sv[i].elev < 0) continue;
    const float r = R * (90 - sv[i].elev) / 90.0f, a = sv[i].az * (float)M_PI / 180.0f;
    const int x = cx + (int)lroundf(r * sinf(a)), y = cy - (int)lroundf(r * cosf(a));
    const uint16_t col = gpsCnoColor(sv[i].cno);
    if (!sv[i].cno) { inst->drawCircle(x, y, 2, col); continue; }  // not heard: unlabelled ring
    inst->fillCircle(x, y, 3, col);
    snprintf(b, sizeof b, "%c%u", sv[i].sys, sv[i].id);
    inst->setTextColor(col); inst->setCursor(x + 5, y - 3); inst->print(b);
  }

  //  The strongest, as bars against the 25 / 35 dB-Hz marks.
  const int lx = 160, bx = 186, bw = 84, top = 34, rows = 11;
  if (!n) {
    inst->setTextColor(CYBER_DIMTXT);
    inst->setCursor(lx, top);      inst->print("no satellites heard");
    inst->setCursor(lx, top + 12); inst->print(gpsBytes ? "antenna? sky view?" : "no data from GNSS");
  }
  for (int i = 0; i < n && i < rows; i++) {
    const int y = top + i * 11;
    const uint16_t col = gpsCnoColor(sv[i].cno);
    snprintf(b, sizeof b, "%c%u", sv[i].sys, sv[i].id);
    inst->setTextColor(col); inst->setCursor(lx, y); inst->print(b);
    int w = sv[i].cno * bw / 50; if (w > bw) w = bw;
    inst->drawRect(bx, y, bw, 7, CYBER_GRID);
    if (w) inst->fillRect(bx, y, w, 7, col);
    inst->drawFastVLine(bx + 25 * bw / 50, y - 1, 9, CYBER_DIMTXT);
    inst->drawFastVLine(bx + 35 * bw / 50, y - 1, 9, CYBER_DIMTXT);
    snprintf(b, sizeof b, "%2u", sv[i].cno);
    inst->setCursor(bx + bw + 4, y); inst->print(b);
  }

  inst->setTextColor(CYBER_DIMTXT);
  inst->setCursor(160, TFT_H - 14); inst->print("ENTER: map  LEFT: back");
  uiScanlines();
  uiBlit();
}

void uiViewGps() {
  gpsPoll();
  const uint8_t page = gmapPage();
  if (page == 0) { gmapView(); return; }               // the map (ENTER: details, then sky)
  if (page == 2) { uiViewGpsSky(); return; }
  inst->fillScreen(CYBER_BG);
  uiFrame(CYBER_GRID);

  //  Header: GPS + fix state.
  inst->setTextSize(2);
  inst->setTextColor(NEON_MAGENTA);
  inst->setCursor(10, 6);
  inst->print("GPS");
  const char* fx = !gpsBytes ? "NO DATA" : gpsAlive() ? (gpsFix >= 2 ? "DGPS" : "FIX") : "NO FIX";
  inst->setTextColor(gpsAlive() ? NEON_GREEN : (gpsBytes ? NEON_YELLOW : NEON_RED));
  inst->setCursor(TFT_W - 10 - (int)strlen(fx) * 12, 6);
  inst->print(fx);

  if (!gpsAlive()) {
    char l1[40];
    snprintf(l1, sizeof l1, "sats %u   bytes %lu", gpsSats, (unsigned long)gpsBytes);
    const char* l2 = gpsBytes ? "acquiring satellites..." : "no data - check wiring/0x42";
    inst->setTextSize(1);
    inst->setTextColor(CYBER_DIMTXT);
    inst->setCursor((TFT_W - (int)strlen(l1) * 6) / 2, 72);
    inst->print(l1);
    inst->setCursor((TFT_W - (int)strlen(l2) * 6) / 2, 86);
    inst->print(l2);
  } else {
    inst->setTextSize(2);
    inst->setTextColor(NEON_CYAN);
    inst->setCursor(10, 34);
    inst->printf("%+.5f", gpsLat);
    inst->setCursor(10, 56);
    inst->printf("%+.5f", gpsLon);

    inst->setTextSize(1);
    inst->setTextColor(CYBER_DIMTXT);
    inst->setCursor(10,  84); inst->printf("ALT  %.1f m", gpsAlt);
    inst->setCursor(170, 84); inst->printf("SATS %u", gpsSats);
    inst->setCursor(10,  98); inst->printf("SPD  %.1f kn", gpsSpeedKn);
    inst->setCursor(170, 98); inst->printf("HDOP %.1f", gpsHDOP);
    inst->setCursor(10, 112); inst->printf("UTC  %.6s", gpsUTC[0] ? gpsUTC : "------");
  }
  inst->setTextSize(1);
  inst->setTextColor(CYBER_DIMTXT);
  inst->setCursor(10, TFT_H - 18); inst->print("ENTER: sky   LEFT: back");

  uiScanlines();
  uiBlit();
}
#endif  // GPS_ENABLE

void uiViewMenu() {
  inst->fillScreen(CYBER_BG);

  ui3DHeader("32 SERVO CONTROLLER");

  const int pitch = MENU_PITCH, hgt = MENU_ROW_H;
  const int vis   = (UI_ITEMS < MENU_VISIBLE) ? UI_ITEMS : MENU_VISIBLE;

  //  Scroll window: keep the selection on screen, clamped to the ends.
  int first = 0;
  if (UI_ITEMS > MENU_VISIBLE) {
    first = uiSel - MENU_VISIBLE / 2;
    if (first < 0) first = 0;
    if (first > UI_ITEMS - MENU_VISIBLE) first = UI_ITEMS - MENU_VISIBLE;
  }
  //  Centre the visible block between the header and the footer.
  const int top = MENU_HEAD_B + 3 + (MENU_FOOT_Y - MENU_HEAD_B - 3 - vis * pitch) / 2;

  for (int r = 0; r < vis; r++) {
    int  i   = first + r;
    int  y   = top + r * pitch;
    bool sel = (i == uiSel);

    if (sel) {
      ui3DSelect(12, y, TFT_W - 24, hgt);
      inst->fillTriangle(3, y + 3, 3, y + hgt - 3, 10, y + hgt / 2, NEON_MAGENTA);
      ui3DText(MENU_NAME_X, y + (hgt - 16) / 2, kUiName[i + 1], plateHiCyan());
    } else {
      inst->drawFastVLine(12, y, hgt, CYBER_GRID);
      inst->drawFastHLine(12, y + hgt - 1, TFT_W - 24, CYBER_GRID);
      inst->setTextSize(2);
      inst->setTextColor(NEON_CYAN);
      inst->setCursor(MENU_NAME_X, y + (hgt - 16) / 2);
      inst->print(kUiName[i + 1]);
    }
  }

  //  Little scroll arrows when there is more list above or below.
  if (UI_ITEMS > MENU_VISIBLE) {
    inst->setTextColor(CYBER_DIMTXT);
    if (first > 0)
      inst->fillTriangle(TFT_W/2 - 4, top - 2, TFT_W/2 + 4, top - 2, TFT_W/2, top - 7, CYBER_DIMTXT);
    if (first + vis < UI_ITEMS) {
      int yb = top + vis * pitch + 1;
      inst->fillTriangle(TFT_W/2 - 4, yb, TFT_W/2 + 4, yb, TFT_W/2, yb + 5, CYBER_DIMTXT);
    }
  }

  drawMenuFooter();
  uiFrame(CYBER_GRID);
  uiScanlines();
  uiBlit();
}

//  Connection footer on the main menu — what the old I2C OLED showed:
//    hotspot:  AP 32_SC        PW 12345678     joined:  MyNetwork      ▂▄▆█
//              192.168.4.1        2 CONN                192.168.1.57   -58dBm
//  A raised cyan plate (see ui3DPlate), square at both ends like the
//  header, with embossed black size-2 text lined up under the header's.
//  Redrawn with the menu, so the signal is live.
static void drawMenuFooter() {
  const int fy = MENU_FOOT_Y;
  //  The plate is MENU_FOOT_H - PLATE_SHADOW = 37 px tall. Size-2 glyphs
  //  are 14 px of ink (+1 px stamped highlight), so lines at +3 and +20 put
  //  ink on rows 3..34 — an even 3 px inside the top bevel and the bottom
  //  edge. (They were at +4/+22, which ran the 2nd line past the bottom.)
  const int y1 = fy + 3, y2 = fy + 20, xl = 12, xr = TFT_W - 17;
  const uint16_t hi = plateHiCyan();
  //  38 px tall (one more than the space left above the shadow): its shadow
  //  still ends at row TFT_H-3, clear of the frame, and the 2nd line gets a
  //  4 px bottom margin to match the look of the top.
  ui3DPlate(6, fy, TFT_W - 12 - PLATE_SHADOW, MENU_FOOT_H - PLATE_SHADOW + 1, PLATE_CYAN,
            PLATE_RADIUS, PLATE_SHADOW);
  //  Right-aligned embossed text ending at xr.
  auto left  = [&](int y, const char* s) { ui3DText(xl, y, s, hi); };
  auto right = [&](int y, const char* s) { ui3DText(xr - (int)strlen(s) * 12, y, s, hi); };

#if WEB_ENABLE && SERVO_ENABLE
  if (!webRunning) { left(y1, "WIFI STARTING..."); return; }
  char a[40], b[24];
  if (webApMode) {
    snprintf(a, sizeof(a), "AP: %s", AP_SSID);
    left(y1, a);
    snprintf(b, sizeof(b), "PW: %s", AP_PASSWORD);
    right(y1, b);
    snprintf(a, sizeof(a), "IP: %s", WiFi.softAPIP().toString().c_str());
    left(y2, a);
    return;
  }
  //  Joined (or trying to rejoin) a network.
  bool up = (WiFi.status() == WL_CONNECTED);
  const int barsW = 4 * 7;                     // meter at the right of line 1
  int maxCh = (xr - barsW - 8 - xl) / 12;
  String ss = WiFi.SSID();
  snprintf(a, sizeof(a), "%.*s", maxCh, ss.length() ? ss.c_str() : "NETWORK");
  if ((int)ss.length() > maxCh) a[maxCh - 1] = '~';
  left(y1, a);
  int8_t rssi = up ? (int8_t)WiFi.RSSI() : -127;
  int bars = !up ? 0 : (rssi >= -55) ? 4 : (rssi >= -67) ? 3 : (rssi >= -78) ? 2 : (rssi >= -88) ? 1 : 0;
  for (int i = 0; i < 4; i++) {
    int h = 4 + i * 3, x = xr - barsW + i * 7 + 1, yb = y1 + 15;
    if (i < bars) { inst->fillRect(x + 1, yb - h + 1, 5, h, hi); inst->fillRect(x, yb - h, 5, h, BLACK); }
    else          inst->drawRect(x, yb - h, 5, h, CYBER_GRID);
  }
  if (up) {
    snprintf(a, sizeof(a), "IP: %s", WiFi.localIP().toString().c_str());
    left(y2, a);
    //  A long address ("IP: 192.168.100.200") would reach the signal
    //  reading; drop its "dBm" then so the two never overlap.
    snprintf(b, sizeof(b), "%ddBm", rssi);
    if (xl + (int)strlen(a) * 12 + 12 > xr - (int)strlen(b) * 12)
      snprintf(b, sizeof(b), "%d", rssi);
    right(y2, b);
  } else {
    left(y2, "RECONNECTING...");
  }
#else
  left(y1, "WIFI OFF");
#endif
}

void uiViewCube() {
  inst->fillScreen(CYBER_BG);
  if (!imuAlive()) {
    drawImuFault(TFT_H / 2);
  } else {
    //  UP face locked to the real sky; heading held from the RESET aim.
    float M[3][3];
    cubeMatrix(M);
    drawCube(M, CUBE_CX, CUBE_CY, CUBE_SZ);

    //  RESET: the only button here, so always shown selected; ENTER presses
    //  it. Right after a press it turns magenta and reads DONE for 1.5 s.
    bool justSet = cubeResetMs && (millis() - cubeResetMs < 1500);
    const int bw = 86, bx = TFT_W - 12 - bw;
    uiButton(bx, TFT_H - 6 - 26, bw, 26, justSet ? "DONE" : "RESET", true,
             justSet ? NEON_MAGENTA : NEON_CYAN);
  }
  uiFrame(CYBER_GRID);
  uiScanlines();
  uiBlit();
}

void uiViewCompass() {
  inst->fillScreen(CYBER_BG);
  if (!imuAlive()) {
    drawImuFault(TFT_H / 2);
  } else {
    float hdg = compassHeading();
    drawCompass(hdg, COMP_CX, COMP_CY, COMP_R);

    //  Readout panel: magenta "HEADING" plate like the view headers, the
    //  bearing large, its 8-point cardinal under it, CALIBRATE at the foot.
    const int px = COMP_PANEL_X, pw = COMP_PANEL_W, pc = px + pw / 2;
    ui3DPlate(px, 6, pw - PLATE_SHADOW_SEL, 20, PLATE_MAGENTA, PLATE_RADIUS, PLATE_SHADOW_SEL);
    ui3DText(px + 6, 8, "HEADING", plateHiMagenta());

    int deg = (int)lroundf(hdg) % 360;
    char num[4]; snprintf(num, sizeof(num), "%03d", deg);
    inst->setTextSize(5);                        // 30 x 40 px glyphs
    inst->setTextColor(NEON_CYAN);
    int nx = pc - 45 - 5;                        // 3 glyphs, nudged left for the degree ring
    inst->setCursor(nx, 36);
    inst->print(num);
    inst->drawCircle(nx + 94, 40, 4, NEON_CYAN);     // degree sign
    inst->drawCircle(nx + 94, 40, 3, NEON_CYAN);

    static const char* c8[8] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW" };
    const char* cd = c8[((deg * 2 + 45) / 90) % 8];   // nearest 45 degrees
    inst->setTextSize(3);
    inst->setTextColor(deg < 23 || deg >= 338 ? NEON_MAGENTA : NEON_PINK);
    inst->setCursor(pc - (int)strlen(cd) * 9, 86);
    inst->print(cd);

    //  The only button here, so it is always shown selected; ENTER presses
    //  it. Right after a press it turns magenta and confirms for 1.5 s.
    bool justSet = compCalMs && (millis() - compCalMs < 1500);
    uiButton(px, TFT_H - 6 - COMP_BTN_H, pw, COMP_BTN_H,
             justSet ? "NORTH SET" : "CALIBRATE", true,
             justSet ? NEON_MAGENTA : NEON_CYAN);
  }
  uiFrame(CYBER_GRID);
  uiScanlines();
  uiBlit();
}

#if MLX_ENABLE
//  One reading in the right-hand column: small grey label centred over a
//  size-2 value, the value drawn in the colour that temperature has in the
//  image. lo/hi are the image's own palette range, so the two always agree.
static void uiThermReading(int y, const char* label, float c, float lo, float hi) {
  const int cx = (UI_THERM_TXT_X + TFT_W - 2) / 2;

  inst->setTextSize(1);
  inst->setTextColor(CYBER_DIMTXT);
  inst->setCursor(cx - (int)strlen(label) * 3, y);
  inst->print(label);

  char v[16];
  snprintf(v, sizeof(v), "%.1f%c", tconv(c), tunit());
  inst->setTextSize(2);
  inst->setTextColor(thermTextColor(c, lo, hi));
  inst->setCursor(cx - (int)strlen(v) * 6, y + 10);
  inst->print(v);
}
#endif

void uiViewThermal() {
  inst->fillScreen(CYBER_BG);
  //  Frame first, image on top of it: the image sits flush left, and drawing
  //  the frame afterwards would scribble its chamfered corners over the
  //  picture.
  uiFrame(CYBER_GRID);
#if MLX_ENABLE
  if (!mlxAlive()) {
    thermalFault(TFT_H / 2);
  } else {
    float lo, hi;
    thermalImage(UI_THERM_X, UI_THERM_Y, UI_THERM_SCALE, &lo, &hi);

    //  MAX and MIN are the raw frame extremes rather than the eased palette
    //  range, so they are the numbers you would actually quote — but they
    //  are coloured against that same eased range, so each one matches the
    //  colour it has on screen.
    const int pitch = (TFT_H - 8) / 4;
    uiThermReading(6,             "MAX",     mlxMax,    lo, hi);
    uiThermReading(6 + pitch,     "CENTRE",  mlxCentre, lo, hi);
    uiThermReading(6 + 2 * pitch, "MIN",     mlxMin,    lo, hi);
    uiThermReading(6 + 3 * pitch, "AMBIENT", mlxTa,     lo, hi);
  }
#else
  inst->setTextSize(1);
  inst->setTextColor(NEON_RED);
  inst->setCursor(12, TFT_H / 2);
  inst->print("MLX90640 not built");
#endif
  uiScanlines();
  uiBlit();
}

// ── SD card browser ──────────────────────────────────────────
//  The root directory is read ONCE on entering the view and cached. Walking
//  the filesystem at the 15 Hz redraw rate would hammer the card for a
//  listing that changes about never, and the read latency would show up as
//  a stutter every frame.
#define FILES_MAX      64
#define FILES_NAME_LEN 22
//  Rows are drawn at the same size as the menu items. The footer is a solid
//  cyan tool panel, the counterpart of the pink header plate, the same
//  height and text size as the header. Six rows fit between the two on 172 px.
//  The file count lives in the header so the footer only has to fit two items.
#define FILES_TXT_SIZE  2
#define FILES_ROWS      6
#define FILES_ROW_Y     30                  // clears the pink header plate
#define FILES_ROW_PITCH 19
#define FILES_FOOT_SIZE 2                   // same as the header text
#define FILES_FOOT_H    MENU_HEAD_H         // same as the header plate
#define FILES_FOOT_Y    (TFT_H - MENU_HEAD_Y - FILES_FOOT_H)   // panel top
#define FILES_FOOT_TXT  (FILES_FOOT_Y + (FILES_FOOT_H - 8 * FILES_FOOT_SIZE) / 2)
//  Longest size string is "1234.5M" — seven characters. What is left after
//  that and the margins is what the name gets.
#define FILES_SIZE_CH   7
#define FILES_NAME_SHOW 16

static_assert(FILES_ROW_Y + (FILES_ROWS - 1) * FILES_ROW_PITCH
                + 8 * FILES_TXT_SIZE + 1 < FILES_FOOT_Y,
              "file rows overrun the footer panel");
//  Widest footer: "11/11" on the left (64 files / 6 rows), "999G FREE" on
//  the right, with at least one glyph of gap between them.
static_assert(28 + (5 + 1 + 9) * 6 * FILES_FOOT_SIZE <= TFT_W - 14,
              "footer page count collides with the free-space figure");
//  Header: "FILE BROWSER" on the left, "64 FILES+" right-aligned before the notch.
static_assert(12 + 12 * 12 + 12 + 9 * 12 <= TFT_W - 34,
              "header file count collides with the title");
static_assert(12 + FILES_NAME_SHOW * 6 * FILES_TXT_SIZE
                <= TFT_W - 14 - FILES_SIZE_CH * 6 * FILES_TXT_SIZE,
              "file name column collides with the size column");

struct FileEnt {
  char     name[FILES_NAME_LEN + 1];
  uint32_t size;
  bool     dir;
};

static FileEnt  fileList[FILES_MAX];
static uint8_t  fileCount = 0;
static uint8_t  filePage  = 0;
static uint8_t  fileSel   = 0;   // highlighted row (absolute index)
static bool     fileTrunc = false;      // more entries than FILES_MAX
//  Folder being browsed ("/" = card root). Kept across visits, so coming back
//  from the image viewer (or the menu) lands in the same folder.
static char     fileDir[96] = "/";

//  Entries not worth showing: the Windows "System Volume Information"
//  folder, and dot-names (macOS ._ files, .Trashes, .Spotlight-V100 ...).
static bool filesHidden(const char* nm) {
  return nm[0] == '.' || !strcasecmp(nm, "System Volume Information");
}

//  fileDir + "/" + name, into out.
static void filesJoin(char* out, size_t n, const char* name) {
  snprintf(out, n, "%s%s%s", fileDir, strcmp(fileDir, "/") ? "/" : "", name);
}

void filesScan() {
  fileCount = 0;
  filePage  = 0;
  fileSel   = 0;
  fileTrunc = false;
  if (!sdMounted) return;

  File dir = SD_MMC.open(fileDir);
  if (!dir || !dir.isDirectory()) {            // folder vanished (card swapped): root
    if (dir) dir.close();
    strcpy(fileDir, "/");
    dir = SD_MMC.open(fileDir);
    if (!dir || !dir.isDirectory()) return;
  }

  //  Inside a folder, ".." comes first: ENTER on it goes back up.
  if (strcmp(fileDir, "/")) {
    strcpy(fileList[0].name, "..");
    fileList[0].size = 0;
    fileList[0].dir  = true;
    fileCount = 1;
  }

  File e;
  while ((e = dir.openNextFile())) {
    if (fileCount >= FILES_MAX) { fileTrunc = true; e.close(); break; }
    //  name() hands back a full path on this core version, so keep only the
    //  last component or every row would read "/something".
    const char* nm = e.name();
    const char* slash = strrchr(nm, '/');
    if (slash) nm = slash + 1;
    if (filesHidden(nm)) { e.close(); continue; }

    strncpy(fileList[fileCount].name, nm, FILES_NAME_LEN);
    fileList[fileCount].name[FILES_NAME_LEN] = '\0';
    fileList[fileCount].size = (uint32_t)e.size();
    fileList[fileCount].dir  = e.isDirectory();
    fileCount++;
    e.close();
  }
  dir.close();
}

//  Up one folder, re-list, and put the highlight on the folder just left.
void filesUp() {
  if (!strcmp(fileDir, "/")) return;
  char left[FILES_NAME_LEN + 1] = "";
  char* s = strrchr(fileDir, '/');
  strncpy(left, s + 1, FILES_NAME_LEN); left[FILES_NAME_LEN] = '\0';
  if (s == fileDir) fileDir[1] = '\0'; else *s = '\0';
  filesScan();
  for (uint8_t i = 0; i < fileCount; i++)
    if (!strcmp(fileList[i].name, left)) { fileSel = i; filePage = i / FILES_ROWS; break; }
}

//  Into the named sub-folder of the current one (if the path still fits).
void filesInto(const char* name) {
  char p[sizeof(fileDir)];
  filesJoin(p, sizeof(p), name);
  if (strlen(p) >= sizeof(fileDir) - 1) return;
  strcpy(fileDir, p);
  filesScan();
}

static uint8_t filePages() {
  if (fileCount == 0) return 1;
  return (fileCount + FILES_ROWS - 1) / FILES_ROWS;
}

//  Paging wraps back to the first page AND rescans, so the same button that
//  browses is also the refresh after swapping a card.
void filesPrevPage() {
  filePage = (filePage == 0) ? filePages() - 1 : filePage - 1;
}
void filesNextPage() {
  if (++filePage >= filePages()) filesScan();
}

static void fileSizeStr(char* out, size_t n, uint32_t bytes) {
  if (bytes < 1024UL)             snprintf(out, n, "%luB", (unsigned long)bytes);
  else if (bytes < 1048576UL)     snprintf(out, n, "%.1fK", bytes / 1024.0);
  else                            snprintf(out, n, "%.1fM", bytes / 1048576.0);
}

// -------------------------------------------------------------
//  WiFi surveillance-device detection
//
//  A passive layer over the AP scan: every access point's BSSID prefix
//  (OUI) and SSID are matched against known surveillance/tracker hardware,
//  and duplicate SSIDs from different vendors are flagged as evil twins.
//  Listen-only -- nothing is transmitted. A privacy/defensive tool: spotting
//  cameras, licence-plate readers, body cams and rogue APs around you.
//
//  Signature architecture and OUI/SSID data ported from SquachWatch-CYD
//  (github.com/skizzophrenic/SquachWatch-CYD, GPLv3); the prefixes are public
//  IEEE registry facts. The BLE half of that project (AirTags, Meta glasses,
//  drones, Tile, skimmers) needs a Bluetooth stack and is not included here,
//  nor is promiscuous-mode deauth/pwnagotchi detection (needs raw frame
//  capture, not an AP scan). Those are the natural next steps.
// -------------------------------------------------------------
static const char* detName(DetType t) {
  switch (t) {
    case DET_FLOCK:    return "FLOCK";       // Flock Safety camera/sensor
    case DET_AXON:     return "AXON";        // Axon body cam / TASER kit
    case DET_ALPR:     return "ALPR";        // licence-plate reader
    case DET_CAMERA:   return "CAMERA";      // surveillance camera
    case DET_RING:     return "RING";        // Ring doorbell/camera
    case DET_SKIMMER:  return "SKIMMER";     // Bluetooth card-skimmer module
    case DET_HACKER:   return "PENTEST";     // Flipper/Pineapple/deauther
    case DET_EVILTWIN: return "EVIL TWIN";   // spoofed AP
    case DET_AIRTAG:   return "AIRTAG";      // Apple Find My tracker
    case DET_META:     return "META";        // Ray-Ban/Meta glasses
    case DET_DRONE:    return "DRONE";       // OpenDroneID RemoteID
    case DET_TILE:     return "TILE";        // Tile tracker
    case DET_SAMSUNG:  return "SMARTTAG";    // Samsung SmartTag
    case DET_GOOGLE:   return "FINDMY";      // Google Find My Device
    case DET_RAVEN:    return "RAVEN";       // gunshot detector
    case DET_IBEACON:  return "IBEACON";     // proximity beacon
    default:           return "";
  }
}

//  BSSID prefixes (first 3 MAC bytes). Confidence: HIGH = block belongs to
//  the product's maker; LOW = shared silicon/ODM (Flock builds on ESP32, so
//  the prefix is real evidence, but evidence shared with every dev board).
static const OuiRow kOui[] = {
  {{0x00,0x25,0xDF}, DET_AXON, CONF_HIGH}, {{0xE4,0x05,0x40}, DET_AXON, CONF_LOW},
  {{0x28,0x24,0xFF}, DET_AXON, CONF_LOW},
  {{0x24,0x0A,0xC4}, DET_FLOCK, CONF_LOW}, {{0x30,0xAE,0xA4}, DET_FLOCK, CONF_LOW},
  {{0x24,0x6F,0x28}, DET_FLOCK, CONF_LOW}, {{0xCC,0x50,0xE3}, DET_FLOCK, CONF_LOW},
  {{0xDC,0x54,0x75}, DET_FLOCK, CONF_LOW}, {{0xE8,0x9F,0x6D}, DET_FLOCK, CONF_LOW},
  {{0x8C,0xAA,0xB5}, DET_FLOCK, CONF_LOW}, {{0x34,0x85,0x18}, DET_FLOCK, CONF_LOW},
  {{0xB4,0x1E,0x52}, DET_FLOCK, CONF_HIGH},{{0xD4,0xAD,0xFC}, DET_FLOCK, CONF_LOW},
  {{0xAC,0x67,0xB2}, DET_FLOCK, CONF_LOW}, {{0x84,0xF3,0xEB}, DET_FLOCK, CONF_LOW},
  {{0xB4,0xE6,0x2D}, DET_FLOCK, CONF_LOW}, {{0xCC,0xDB,0xA7}, DET_FLOCK, CONF_LOW},
  {{0x94,0xB9,0x7E}, DET_FLOCK, CONF_LOW}, {{0xA4,0xCF,0x12}, DET_FLOCK, CONF_LOW},
  {{0xC0,0x49,0xEF}, DET_FLOCK, CONF_LOW}, {{0x24,0xB2,0xB9}, DET_FLOCK, CONF_LOW},
  {{0x00,0xA0,0xD8}, DET_FLOCK, CONF_LOW},
  {{0x00,0x04,0x7D}, DET_ALPR, CONF_HIGH}, {{0x00,0x18,0x85}, DET_ALPR, CONF_HIGH},
  {{0x00,0x1F,0x92}, DET_ALPR, CONF_HIGH}, {{0x4C,0xCC,0x34}, DET_ALPR, CONF_HIGH},
  {{0xB8,0xE2,0x8C}, DET_ALPR, CONF_HIGH}, {{0x00,0xBF,0x15}, DET_ALPR, CONF_HIGH},
  {{0x0C,0xBF,0x15}, DET_ALPR, CONF_HIGH},
  {{0x20,0x13,0x00}, DET_SKIMMER, CONF_LOW}, {{0x98,0xD3,0x00}, DET_SKIMMER, CONF_LOW},
  {{0x00,0x1A,0x7D}, DET_SKIMMER, CONF_LOW},
  {{0x2C,0xAA,0x8E}, DET_CAMERA, CONF_HIGH},{{0xD0,0x3F,0x27}, DET_CAMERA, CONF_HIGH},
  {{0x7C,0x78,0xB2}, DET_CAMERA, CONF_HIGH},{{0xB8,0xD7,0xAF}, DET_CAMERA, CONF_LOW},
  {{0x34,0xD2,0x70}, DET_CAMERA, CONF_MED}, {{0xF0,0x27,0x2D}, DET_CAMERA, CONF_MED},
  {{0xC0,0x56,0xE3}, DET_CAMERA, CONF_HIGH},{{0x44,0x19,0xB6}, DET_CAMERA, CONF_HIGH},
  {{0x28,0x57,0xBE}, DET_CAMERA, CONF_HIGH},{{0xBC,0xDD,0xC2}, DET_CAMERA, CONF_LOW},
  {{0x4C,0x69,0x05}, DET_CAMERA, CONF_LOW}, {{0xA4,0xC1,0x38}, DET_CAMERA, CONF_LOW},
  {{0xE0,0xA7,0x00}, DET_CAMERA, CONF_HIGH},{{0x70,0x1A,0xD5}, DET_CAMERA, CONF_HIGH},
  {{0x00,0x40,0x8C}, DET_CAMERA, CONF_HIGH},{{0xB8,0xA4,0x4F}, DET_CAMERA, CONF_HIGH},
  {{0xFC,0x65,0xDE}, DET_RING, CONF_MED}, {{0x68,0x37,0xE9}, DET_RING, CONF_MED},
  {{0xAC,0x9F,0xC3}, DET_RING, CONF_HIGH},{{0x18,0x7F,0x88}, DET_RING, CONF_HIGH},
  {{0x34,0x3E,0xA4}, DET_RING, CONF_HIGH},{{0x54,0xE0,0x19}, DET_RING, CONF_HIGH},
  {{0x5C,0x47,0x5E}, DET_RING, CONF_HIGH},{{0x64,0x9A,0x63}, DET_RING, CONF_HIGH},
  {{0x90,0x48,0x6C}, DET_RING, CONF_HIGH},{{0x9C,0x76,0x13}, DET_RING, CONF_HIGH},
  {{0xCC,0x3B,0xFB}, DET_RING, CONF_HIGH},{{0xC4,0xDB,0xAD}, DET_RING, CONF_HIGH},
  {{0x24,0x2B,0xD6}, DET_RING, CONF_HIGH},{{0x00,0xB4,0x63}, DET_RING, CONF_HIGH},
  {{0x50,0xE4,0x67}, DET_RING, CONF_HIGH},
  {{0x0C,0xFA,0x22}, DET_HACKER, CONF_HIGH},{{0x02,0xC0,0xCA}, DET_HACKER, CONF_LOW},
  {{0x02,0x13,0x37}, DET_HACKER, CONF_LOW},
};
#define OUI_COUNT (sizeof(kOui) / sizeof(kOui[0]))

//  SSID prefixes -- the management/setup networks these devices put up.
static const SsidRow kSsid[] = {
  {"AB2-", DET_AXON}, {"AB3-", DET_AXON}, {"AB4-", DET_AXON}, {"AXON-", DET_AXON},
  {"flock-", DET_FLOCK}, {"FLOCK-", DET_FLOCK},
  {"Pineapple_", DET_HACKER}, {"pwned", DET_HACKER},
};
#define SSID_ROW_COUNT (sizeof(kSsid) / sizeof(kSsid[0]))

static DetType lookupOui(const uint8_t* mac, DetConf* conf) {
  for (uint16_t i = 0; i < OUI_COUNT; i++)
    if (mac[0]==kOui[i].b[0] && mac[1]==kOui[i].b[1] && mac[2]==kOui[i].b[2]) {
      if (conf) *conf = kOui[i].conf;
      return kOui[i].type;
    }
  return DET_NONE;
}
static DetType lookupSsid(const char* ssid) {
  for (uint16_t i = 0; i < SSID_ROW_COUNT; i++)
    if (strncasecmp(ssid, kSsid[i].prefix, strlen(kSsid[i].prefix)) == 0)
      return kSsid[i].type;
  return DET_NONE;
}

// ── WiFi scanner — listen-only AP scan ───────────────────────
//  A passive scan: WiFi.scanNetworks() only listens for the beacons access
//  points already broadcast. Nothing is transmitted, nothing is connected
//  to. The radio is put in station mode and left idle between scans.
//
//  The scan is ASYNC. A blocking scan would freeze the panel for 2-4 s and
//  starve the camera and the MLX task; instead it is kicked off on entering
//  the view and polled, so the "SCANNING" screen still animates.
#define WIFI_MAX      24
#define WIFI_SSID_LEN 20
//  Laid out like the other list views: the 3D header plate on top, a 3D
//  footer plate (count, page, threat tally) at the bottom, and five 23 px
//  network rows between them — signal bars on the left, the SSID at size 2
//  beside them, nothing else. The SSID has the rest of the row width.
#define WIFI_ROWS      5
#define WIFI_ROW_TOP   30                        // clears the header plate + shadow
#define WIFI_ROW_PITCH 23
#define WIFI_ROW_H     22
#define WIFI_FOOT_H    23                        // same plate as the file browser
#define WIFI_FOOT_Y    (TFT_H - MENU_HEAD_Y - WIFI_FOOT_H)
#define WIFI_NAME_X    40
#define WIFI_NAME_SHOW WIFI_SSID_LEN             // all 20 stored characters fit
static_assert(WIFI_NAME_X + WIFI_NAME_SHOW * 6 * 2 <= TFT_W - 12,
              "wifi SSID column runs off the row");
static_assert(WIFI_ROW_TOP + WIFI_ROWS * WIFI_ROW_PITCH <= WIFI_FOOT_Y,
              "wifi rows overrun the footer plate");

struct WifiEnt {
  char    ssid[WIFI_SSID_LEN + 1];
  uint8_t oui[3];                 // BSSID prefix, for OUI + evil-twin checks
  int8_t  rssi;
  uint8_t ch;
  bool    enc;
  DetType det;                    // DET_NONE, or the surveillance category
  DetConf conf;
};
static uint8_t wifiThreats = 0;   // detections in the last scan

static WifiEnt  wifiList[WIFI_MAX];
static uint8_t  wifiCount = 0;
static uint8_t  wifiPage  = 0;
static bool     wifiTrunc = false;
static bool     wifiScanning = false;
static bool     wifiInit  = false;      // radio brought up once, lazily

//  Kick off an async scan. The radio is started on first use rather than at
//  boot, so a board that never opens this view never powers the WiFi stack.
void wifiStartScan() {
  if (!wifiInit) {
#if WEB_ENABLE && SERVO_ENABLE
    //  The servo web server owns the radio (AP+STA, or joined to a network):
    //  both can scan as they are, and switching mode or disconnecting here
    //  would drop the controller's connection.
    if (!webRunning)
#endif
    {
      WiFi.mode(WIFI_STA);
      WiFi.disconnect(false, true);     // ensure not associating to anything
    }
    wifiInit = true;
  }
  WiFi.scanDelete();
  WiFi.scanNetworks(true, false);           // async, show hidden = false
  wifiScanning = true;
}

//  Copy a finished scan out of the driver into our own array, then free the
//  driver's copy. Called from the view once scanComplete() reports done.
static void wifiHarvest(int n) {
  wifiCount = 0;
  wifiPage  = 0;
  wifiTrunc = false;
  for (int i = 0; i < n; i++) {
    if (wifiCount >= WIFI_MAX) { wifiTrunc = true; break; }
    String ss = WiFi.SSID(i);
    WifiEnt& e = wifiList[wifiCount];
    if (ss.length() == 0) { strcpy(e.ssid, "(hidden)"); }
    else { strncpy(e.ssid, ss.c_str(), WIFI_SSID_LEN); e.ssid[WIFI_SSID_LEN] = '\0'; }
    e.rssi = (int8_t)WiFi.RSSI(i);
    e.ch   = (uint8_t)WiFi.channel(i);
    e.enc  = (WiFi.encryptionType(i) != WIFI_AUTH_OPEN);

    const uint8_t* bssid = WiFi.BSSID(i);
    if (bssid) memcpy(e.oui, bssid, 3); else memset(e.oui, 0, 3);

    //  BSSID prefix first (it carries a confidence), SSID prefix as fallback
    //  for devices whose radios use generic silicon.
    e.conf = CONF_LOW;
    e.det  = lookupOui(e.oui, &e.conf);
    if (e.det == DET_NONE) {
      DetType st = lookupSsid(e.ssid);
      if (st != DET_NONE) { e.det = st; e.conf = CONF_MED; }
    }
    wifiCount++;
  }

  //  Evil-twin pass: one SSID beaconing from two BSSIDs whose OUIs differ.
  //  Skips already-matched nets and blank/(hidden) names.
  for (uint8_t a = 0; a < wifiCount; a++) {
    if (wifiList[a].det != DET_NONE || wifiList[a].ssid[0] == '(') continue;
    for (uint8_t b = 0; b < wifiCount; b++) {
      if (b != a && strcmp(wifiList[a].ssid, wifiList[b].ssid) == 0 &&
          memcmp(wifiList[a].oui, wifiList[b].oui, 3) != 0) {
        wifiList[a].det = DET_EVILTWIN; wifiList[a].conf = CONF_MED; break;
      }
    }
  }

  //  Count threats and float them to the top so a full screen never buries
  //  the thing worth seeing. Stable insertion, preserving RSSI order within.
  wifiThreats = 0;
  for (uint8_t i = 0; i < wifiCount; i++) if (wifiList[i].det != DET_NONE) wifiThreats++;
  for (uint8_t i = 1; i < wifiCount; i++) {
    if (wifiList[i].det == DET_NONE) continue;
    uint8_t dst = 0;
    while (dst < i && wifiList[dst].det != DET_NONE) dst++;
    if (dst < i) {
      WifiEnt tmp = wifiList[i];
      for (uint8_t k = i; k > dst; k--) wifiList[k] = wifiList[k - 1];
      wifiList[dst] = tmp;
    }
  }

  WiFi.scanDelete();
  wifiScanning = false;
  if (wifiThreats)
    Serial.printf("WiFi detect: %u flagged of %u nets\n", wifiThreats, wifiCount);
}

static uint8_t wifiPages() {
  if (wifiCount == 0) return 1;
  return (wifiCount + WIFI_ROWS - 1) / WIFI_ROWS;
}

//  Paging past the last page starts a fresh scan — same gesture as the SD
//  browser's reload.
void wifiPrevPage() {
  wifiPage = (wifiPage == 0) ? wifiPages() - 1 : wifiPage - 1;
}
void wifiNextPage() {
  if (++wifiPage >= wifiPages()) wifiStartScan();
}

//  RSSI -> colour in the theme palette: strong cyan, fair pink, weak magenta.
static uint16_t wifiRssiColor(int8_t r) {
  if (r >= -60) return NEON_CYAN;
  if (r >= -75) return NEON_PINK;
  return NEON_MAGENTA;
}

//  Four-bar meter, baseline at y=base, growing upward. col 0 = by strength.
static void wifiBars(int x, int base, int8_t rssi, uint16_t col) {
  int bars = (rssi >= -55) ? 4 : (rssi >= -67) ? 3 : (rssi >= -78) ? 2 : (rssi >= -88) ? 1 : 0;
  if (!col) col = wifiRssiColor(rssi);
  for (int b = 0; b < 4; b++) {
    int h = 6 + b * 5;
    if (b < bars) inst->fillRect(x + b * 7, base - h, 4, h, col);
    else          inst->drawRect(x + b * 7, base - h, 4, h, CYBER_GRID);
  }
}

void uiViewWifi() {
  inst->fillScreen(CYBER_BG);

  //  Async: check whether the running scan has finished.
  if (wifiScanning) {
    int done = WiFi.scanComplete();
    if (done >= 0) wifiHarvest(done);
  }

  ui3DHeader("WIFI");

  //  Footer plate: count and page on the left, threat tally on the right.
  const int fy = WIFI_FOOT_Y, fh = WIFI_FOOT_H - PLATE_SHADOW, fty = fy + (fh - 16) / 2;
  ui3DPlate(6, fy, TFT_W - 12 - PLATE_SHADOW, fh, PLATE_CYAN, PLATE_RADIUS, PLATE_SHADOW);
  const uint16_t hiC = plateHiCyan(), hiM = plateHiMagenta();

  if (wifiScanning) {
    //  Animated ellipsis so it reads as busy, not hung.
    char dots[4] = "   ";
    for (int i = 0; i < (int)((millis() / 350) % 4); i++) dots[i] = '.';
    char msg[16]; snprintf(msg, sizeof(msg), "SCANNING%s", dots);
    inst->setTextSize(2);
    inst->setTextColor(NEON_CYAN);
    inst->setCursor((TFT_W - 11 * 12) / 2, (WIFI_ROW_TOP + WIFI_FOOT_Y) / 2 - 8);
    inst->print(msg);
    ui3DText(12, fty, "SCANNING", hiC);
    uiFrame(CYBER_GRID);
    uiScanlines();
    uiBlit();
    return;
  }

  char l[24], rt[16];
  snprintf(l, sizeof(l), "%u NET%s %u/%u", wifiCount, wifiCount == 1 ? "" : "S",
           (unsigned)wifiPage + 1, (unsigned)wifiPages());
  if (wifiThreats) snprintf(rt, sizeof(rt), "%u FLAGGED", wifiThreats);
  else             strcpy(rt, "ALL CLEAR");
  ui3DText(12, fty, l, hiC);
  ui3DText(TFT_W - 17 - (int)strlen(rt) * 12, fty, rt, hiC);

  if (wifiCount == 0) {
    inst->setTextSize(2);
    inst->setTextColor(CYBER_DIMTXT);
    inst->setCursor((TFT_W - 11 * 12) / 2, (WIFI_ROW_TOP + WIFI_FOOT_Y) / 2 - 8);
    inst->print("NO NETWORKS");
  } else {
    int first = wifiPage * WIFI_ROWS;
    for (int r = 0; r < WIFI_ROWS && first + r < wifiCount; r++) {
      const WifiEnt& w = wifiList[first + r];
      const int y = WIFI_ROW_TOP + r * WIFI_ROW_PITCH;
      const bool flagged = (w.det != DET_NONE);

      //  SSID, clipped to the size-2 name column, marked with '~' if cut.
      char nm[WIFI_NAME_SHOW + 1];
      strncpy(nm, w.ssid, WIFI_NAME_SHOW);
      nm[WIFI_NAME_SHOW] = '\0';
      if (strlen(w.ssid) > WIFI_NAME_SHOW) nm[WIFI_NAME_SHOW - 1] = '~';

      //  Bars fill rows y..y+20 (tallest is 21 px), clear of the row rule;
      //  the SSID's 14 px of ink is centred in the 22 px row.
      const int barBase = y + WIFI_ROW_H - 1, ty = y + (WIFI_ROW_H - 14) / 2;

      if (flagged) {
        //  Flagged networks stand out as a raised magenta bar, bars and
        //  name stamped into it in black.
        ui3DPlate(6, y, TFT_W - 12 - PLATE_SHADOW_SEL, WIFI_ROW_H, PLATE_MAGENTA,
                  PLATE_RADIUS_SEL, PLATE_SHADOW_SEL);
        wifiBars(10, barBase, w.rssi, BLACK);
        ui3DText(WIFI_NAME_X, ty, nm, hiM);
        continue;
      }

      //  Ordinary row, drawn like a menu row: grid rule left and below.
      inst->drawFastVLine(6, y, WIFI_ROW_H, CYBER_GRID);
      inst->drawFastHLine(6, y + WIFI_ROW_H - 1, TFT_W - 12, CYBER_GRID);
      wifiBars(10, barBase, w.rssi, 0);
      inst->setTextSize(2);
      inst->setTextColor(w.enc ? NEON_CYAN : NEON_PINK);
      inst->setCursor(WIFI_NAME_X, ty);
      inst->print(nm);
    }
  }

  uiFrame(CYBER_GRID);
  uiScanlines();
  uiBlit();
}

#if MLX_ENABLE
// ── IR/visible fusion frame ──────────────────────────────────
//  Two passes over the 320x172 display window:
//    1. decode the camera crop to an 8-bit luma buffer;
//    2. Sobel that buffer for edges, sample the thermal image bilinearly,
//       and write the composited RGB565 straight into the UI canvas.
//  The camera frame is 320x240 big-endian RGB565; the display shows its
//  centre 172 rows (srcY offset), matching the plain camera view.
static uint8_t* fusLuma = nullptr;      // TFT_W x TFT_H, lazily allocated in PSRAM

static inline uint16_t fusRGB(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void fuseFrame(const camera_fb_t* fb) {
  if (!inst) return;
  const int srcY = (CAM_H - TFT_H) / 2;          // 34: centre crop, as showFrame

  if (!fusLuma) {
    fusLuma = (uint8_t*)ps_malloc((size_t)TFT_W * TFT_H);
    if (!fusLuma) {                              // no PSRAM for it: fall back to raw
      showFrame(fb);
      return;
    }
  }

  // ── pass 1: camera crop -> luma ──
  const uint8_t* buf = fb->buf;
  for (int y = 0; y < TFT_H; y++) {
    const uint8_t* row = buf + ((size_t)(y + srcY) * CAM_W) * 2;
    uint8_t* lrow = fusLuma + (size_t)y * TFT_W;
    for (int x = 0; x < TFT_W; x++) {
      uint16_t px = (row[x * 2] << 8) | row[x * 2 + 1];    // big-endian in memory
      uint8_t r = (px >> 8) & 0xF8, g = (px >> 3) & 0xFC, b = (px << 3) & 0xF8;
      lrow[x] = (uint8_t)((r * 77 + g * 150 + b * 29) >> 8);
    }
  }

  // ── thermal range, lightly eased so a still scene does not shimmer ──
  uint8_t      idx = mlxReadIdx;
  const float* tf  = (idx < 2) ? mlxBuf[idx & 1] : nullptr;
  float lo = mlxMin, hi = mlxMax;
  if (hi - lo < 2.0f) { float m = (lo + hi) * 0.5f; lo = m - 1.0f; hi = m + 1.0f; }
  static float sLo = 0, sHi = 0; static bool sInit = false;
  if (!sInit) { sLo = lo; sHi = hi; sInit = true; }
  else        { sLo += (lo - sLo) * 0.25f; sHi += (hi - sHi) * 0.25f; }

  //  Map display-x to thermal-u once per frame, not per pixel.
  const float su = (fusW > 1) ? (float)(THERM_W - 1) / (fusW - 1) : 0;
  const float sv = (fusH > 1) ? (float)(THERM_H - 1) / (fusH - 1) : 0;

  uint16_t* out = inst->getBuffer();

  // ── pass 2: Sobel + thermal sample -> composite ──
  for (int y = 0; y < TFT_H; y++) {
    uint16_t* orow = out + (size_t)y * TFT_W;
    const uint8_t* lc = fusLuma + (size_t)y * TFT_W;
    const uint8_t* lu = lc - TFT_W;
    const uint8_t* ld = lc + TFT_W;
    bool yEdge = (y == 0 || y == TFT_H - 1);

    bool inRowBand = (tf && y >= fusY && y < fusY + fusH);
    float v = 0;
    if (inRowBand) {
      v = (y - fusY) * sv;
      if (thermFlipV) v = (THERM_H - 1) - v;
    }
    int   j0 = (int)v; if (j0 > THERM_H - 2) j0 = THERM_H - 2; if (j0 < 0) j0 = 0;
    float fv = v - j0;

    for (int x = 0; x < TFT_W; x++) {
      // edge magnitude (0 at the border, where the 3x3 would read outside)
      int edge = 0;
      if (!yEdge && x > 0 && x < TFT_W - 1) {
        int gx = (lu[x+1] + 2*lc[x+1] + ld[x+1]) - (lu[x-1] + 2*lc[x-1] + ld[x-1]);
        int gy = (ld[x-1] + 2*ld[x] + ld[x+1]) - (lu[x-1] + 2*lu[x] + lu[x+1]);
        if (gx < 0) gx = -gx;
        if (gy < 0) gy = -gy;
        edge = ((gx + gy) * FUS_EDGE_GAIN) >> 2;
        if (edge > FUS_EDGE_MAX) edge = FUS_EDGE_MAX;
      }

      bool inRect = inRowBand && x >= fusX && x < fusX + fusW;
      if (inRect) {
        float u = (x - fusX) * su;
        if (thermFlipH) u = (THERM_W - 1) - u;
        int   i0 = (int)u; if (i0 > THERM_W - 2) i0 = THERM_W - 2; if (i0 < 0) i0 = 0;
        float fu = u - i0;
        const float* r0 = tf + j0 * THERM_W + i0;
        const float* r1 = r0 + THERM_W;
        float t = r0[0]*(1-fu)*(1-fv) + r0[1]*fu*(1-fv)
                + r1[0]*(1-fu)*fv     + r1[1]*fu*fv;

        uint16_t base = thermColor(t, sLo, sHi);
        uint8_t br = (base >> 8) & 0xF8, bg = (base >> 3) & 0xFC, bb = (base << 3) & 0xF8;
        int k = 255 - edge;                       // emboss: darken toward the edge
        orow[x] = fusRGB((br * k) >> 8, (bg * k) >> 8, (bb * k) >> 8);
      } else {
        //  Context ring: dimmed grayscale so the narrower thermal cone reads
        //  as a window onto the wider visible scene.
        int gval = (lc[x] * FUS_CTX_DIM) >> 8;
        orow[x] = fusRGB(gval, gval, gval);
      }
    }
  }

#if FUS_OUTLINE
  //  Thin cyan box round the thermal-covered region — also the guide you
  //  line up during calibration.
  int x0 = fusX, x1 = fusX + fusW - 1, y0 = fusY, y1 = fusY + fusH - 1;
  if (x0 < 0) x0 = 0; if (y0 < 0) y0 = 0;
  if (x1 > TFT_W - 1) x1 = TFT_W - 1; if (y1 > TFT_H - 1) y1 = TFT_H - 1;
  for (int x = x0; x <= x1; x++) { out[y0*TFT_W+x] = NEON_CYAN; out[y1*TFT_W+x] = NEON_CYAN; }
  for (int y = y0; y <= y1; y++) { out[y*TFT_W+x0] = NEON_CYAN; out[y*TFT_W+x1] = NEON_CYAN; }
#endif

  uiBlit();
}
#endif  // MLX_ENABLE

#if VIDEO_ENABLE
// -------------------------------------------------------------
//  Image viewer — show a JPEG from the card, with delete overlay
//
//  Entered from the file browser (ENTER on a .jpg). The file is read into
//  PSRAM once, then re-decoded on each repaint (cheap enough at user pace)
//  so the overlay buttons can be drawn over a clean image every time.
//  Buttons: BACK and DELETE; DELETE asks to confirm before removing.
// -------------------------------------------------------------
//  The image viewer borrows the video player's decoder instead of owning a
//  second one: a JPEGDEC is 17.9 KB of INTERNAL RAM, which Bluetooth needs
//  to start now that Wi-Fi is up from boot. The two never overlap — while a
//  clip plays, loop() returns before any view is drawn, and each use is a
//  complete open/decode/close in one call.
static JPEGDEC&  imgDec = vidDec;
static uint8_t*  imgBuf = nullptr;
static size_t    imgLen = 0;
static char      imgPath[128] = "";      // full path: images can live in folders
static int       imgOffX = 0, imgOffY = 0;
static uint8_t   imgBtnSel = 0;      // 0 = BACK, 1 = DELETE
static bool      imgConfirm = false; // delete confirmation showing
static bool      imgDirty = true;    // repaint needed
static bool      imgOk = false;      // decoded cleanly

static int imgDraw(JPEGDRAW* pDraw) {
  uint16_t* fb = inst->getBuffer();
  for (int r = 0; r < pDraw->iHeight; r++) {
    int y = imgOffY + pDraw->y + r;
    if (y < 0 || y >= TFT_H) continue;
    int x = imgOffX + pDraw->x, w = pDraw->iWidth;
    if (x < 0) { w += x; x = 0; }
    if (x + w > TFT_W) w = TFT_W - x;
    if (w <= 0) continue;
    memcpy(&fb[y * TFT_W + x], &pDraw->pPixels[r * pDraw->iWidth], w * 2);
  }
  return 1;
}

//  Read the whole JPEG into PSRAM. Returns false if absent or too large.
bool imgLoad(const char* path) {
  free(imgBuf); imgBuf = nullptr; imgLen = 0; imgOk = false;
  if (!sdMounted) return false;
  File f = SD_MMC.open(path, FILE_READ);
  if (!f) return false;
  size_t n = f.size();
  if (n == 0 || n > 400000) { f.close(); return false; }   // 400 KB cap
  imgBuf = (uint8_t*)ps_malloc(n);
  if (!imgBuf) { f.close(); return false; }
  imgLen = f.read(imgBuf, n);
  f.close();
  strncpy(imgPath, path, sizeof(imgPath) - 1); imgPath[sizeof(imgPath) - 1] = '\0';
  imgConfirm = false; imgBtnSel = 0; imgDirty = true;
  return imgLen == n;
}

//  Decode into the canvas, letterboxed and scaled to fit, then the overlay.
void uiViewImage() {
  if (!imgDirty || !inst) return;
  imgDirty = false;
  inst->fillScreen(BLACK);

  imgOk = false;
  if (imgBuf && imgDec.openRAM(imgBuf, imgLen, imgDraw)) {
    int w = imgDec.getWidth(), h = imgDec.getHeight(), div = 1, opt = 0;
    while ((w / div > TFT_W || h / div > TFT_H) && div < 8) { div *= 2; }
    opt = (div == 2) ? JPEG_SCALE_HALF : (div == 4) ? JPEG_SCALE_QUARTER
        : (div >= 8) ? JPEG_SCALE_EIGHTH : 0;
    int sw = w / div, sh = h / div;
    imgOffX = (TFT_W - sw) / 2; if (imgOffX < 0) imgOffX = 0;
    imgOffY = (TFT_H - sh) / 2; if (imgOffY < 0) imgOffY = 0;
    imgDec.setPixelType(RGB565_LITTLE_ENDIAN);   // canvas is native LE
    imgDec.setUserPointer(nullptr);
    imgOk = (imgDec.decode(0, 0, opt) == 1);
    imgDec.close();
  }
  if (!imgOk) {
    inst->setTextSize(2); inst->setTextColor(NEON_RED);
    inst->setCursor(20, TFT_H / 2 - 8); inst->print("CANNOT DECODE");
  }

  // ── overlay ──
  if (imgConfirm) {
    //  Prompt plate styled like the magenta header: pink frame, black box.
    inst->fillRect(30, TFT_H / 2 - 30, TFT_W - 60, 60, CYBER_BG);
    inst->drawRect(30, TFT_H / 2 - 30, TFT_W - 60, 60, NEON_MAGENTA);
    inst->setTextSize(2); inst->setTextColor(NEON_MAGENTA);
    inst->setCursor(40, TFT_H / 2 - 24); inst->print("DELETE FILE?");
    //  NO (0) / YES (1)
    const char* lab[2] = { "NO", "YES" };
    for (int b = 0; b < 2; b++)
      uiButton(44 + b * 120, TFT_H / 2 + 2, 90, 22, lab[b], imgBtnSel == b, NEON_CYAN);
  } else {
    const char* lab[2] = { "BACK", "DELETE" };
    for (int b = 0; b < 2; b++) {
      int bw = 100, bh = 24, gap = 12;
      int bx = (TFT_W - (bw * 2 + gap)) / 2 + b * (bw + gap);
      uiButton(bx, TFT_H - bh - 4, bw, bh, lab[b], imgBtnSel == b, NEON_CYAN);
    }
  }
  uiBlit();
}

//  Gamepad action inside the image view. LEFT/RIGHT move between the two
//  overlay buttons; ENTER activates the highlighted one. UP/DOWN do nothing.
//  Exit is via the BACK button, not a dedicated key.
void imgAction(UiAction a) {
  if (a == ACT_BACK || a == ACT_RIGHT) { imgBtnSel ^= 1; imgDirty = true; return; }
  if (a == ACT_SELECT) {
    if (imgConfirm) {
      if (imgBtnSel == 1) {                 // YES: delete and leave
        SD_MMC.remove(imgPath);
        free(imgBuf); imgBuf = nullptr;
        filesScan();                        // refresh the listing
        uiEnter(UI_FILES);
      } else { imgConfirm = false; imgBtnSel = 0; imgDirty = true; }
    } else {
      if (imgBtnSel == 1) { imgConfirm = true; imgBtnSel = 0; imgDirty = true; }  // DELETE
      else { free(imgBuf); imgBuf = nullptr; uiEnter(UI_FILES); }                 // BACK
    }
  }
}
#endif  // VIDEO_ENABLE

void uiViewFiles() {
  inst->fillScreen(CYBER_BG);

  //  3D header plate, the file count stamped at its right end.
  //  Header: the folder being browsed, the item count stamped at the right.
  //  A path too long for the room left is shown by its end ("~/deep/folder").
  {
    const bool inSub = strcmp(fileDir, "/") != 0;
    unsigned n = fileCount - (inSub ? 1 : 0);             // don't count ".."
    char cnt[16] = "";
    if (sdMounted)
      snprintf(cnt, sizeof(cnt), "%u ITEM%s%s", n, n == 1 ? "" : "S", fileTrunc ? "+" : "");
    const int cw = (int)strlen(cnt) * 12;
    int room = (TFT_W - 17 - cw - (cw ? 12 : 0) - 12) / 12;
    char path[32];
    int len = (int)strlen(fileDir);
    if (len <= room) snprintf(path, sizeof(path), "%s", fileDir);
    else             snprintf(path, sizeof(path), "~%s", fileDir + len - (room - 1));
    ui3DHeader(path);
    if (cw) ui3DText(TFT_W - 17 - cw, MENU_HEAD_Y + (MENU_HEAD_H - 16) / 2, cnt, plateHiMagenta());
  }

  if (!sdMounted) {
    inst->setTextSize(2);
    inst->setTextColor(NEON_RED);
    inst->setCursor((TFT_W - 7 * 12) / 2, TFT_H / 2 - 8);
    inst->print("NO CARD");
    inst->setTextSize(1);
    inst->setTextColor(CYBER_DIMTXT);
    inst->setCursor((TFT_W - 30 * 6) / 2, TFT_H / 2 + 12);
    inst->print("mount it, then press to rescan");
  } else if (fileCount == 0) {
    inst->setTextSize(2);
    inst->setTextColor(CYBER_DIMTXT);
    inst->setCursor((TFT_W - 5 * 12) / 2, TFT_H / 2 - 8);
    inst->print("EMPTY");
  } else {
    int first = filePage * FILES_ROWS;
    for (int r = 0; r < FILES_ROWS && first + r < fileCount; r++) {
      const FileEnt& f = fileList[first + r];
      int y = FILES_ROW_Y + r * FILES_ROW_PITCH;

      //  Bigger glyphs mean fewer of them fit, so a long name is cut and
      //  marked rather than allowed to run into the size column.
      char nm[FILES_NAME_SHOW + 1];
      strncpy(nm, f.name, FILES_NAME_SHOW);
      nm[FILES_NAME_SHOW] = '\0';
      if (strlen(f.name) > FILES_NAME_SHOW) nm[FILES_NAME_SHOW - 1] = '~';

      char sz[12];
      if (f.dir) strcpy(sz, strcmp(f.name, "..") ? "<DIR>" : "<UP>");
      else       fileSizeStr(sz, sizeof(sz), f.size);
      const int szx = TFT_W - 14 - (int)strlen(sz) * 6 * FILES_TXT_SIZE;

      bool sel = (first + r == fileSel);
      if (sel) {
        //  Same raised cyan bar as the menus, name and size stamped into it.
        ui3DSelect(8, y - 2, TFT_W - 14, 8 * FILES_TXT_SIZE + 3);
        inst->fillTriangle(1, y, 1, y + 8 * FILES_TXT_SIZE, 6,
                           y + 4 * FILES_TXT_SIZE, NEON_MAGENTA);
        ui3DText(12, y, nm, plateHiCyan());
        ui3DText(szx, y, sz, plateHiCyan());
        continue;
      }
      inst->setTextSize(FILES_TXT_SIZE);
      inst->setTextColor(f.dir ? NEON_CYAN : NEON_PINK);
      inst->setCursor(12, y);
      inst->print(nm);
      inst->setTextColor(f.dir ? NEON_CYAN : CYBER_DIMTXT);
      inst->setCursor(szx, y);
      inst->print(sz);
    }
  }

  //  Footer: which page you are on, and what is left on the card, on a
  //  raised cyan plate like the main menu's footer (its shadow takes the
  //  plate's last 3 px of height).
  const int fy = FILES_FOOT_Y, fh = FILES_FOOT_H - PLATE_SHADOW, fty = fy + (fh - 16) / 2;
  ui3DPlate(6, fy, TFT_W - 12 - PLATE_SHADOW, fh, PLATE_CYAN, PLATE_RADIUS, PLATE_SHADOW);
  if (sdMounted) {
    char pg[12];
    snprintf(pg, sizeof(pg), "%u/%u", filePage + 1, filePages());
    ui3DText(12, fty, pg, plateHiCyan());

    uint64_t freeB = SD_MMC.totalBytes() - SD_MMC.usedBytes();
    char tail[20];
    //  Whole units keep this at 9 characters or fewer.
    if (freeB >= 1000ULL * 1073741824ULL)
      snprintf(tail, sizeof(tail), "%.1fT FREE", freeB / 1099511627776.0);
    else if (freeB >= 1073741824ULL)
      snprintf(tail, sizeof(tail), "%luG FREE", (unsigned long)(freeB / 1073741824ULL));
    else
      snprintf(tail, sizeof(tail), "%luM FREE", (unsigned long)(freeB / 1048576ULL));
    ui3DText(TFT_W - 17 - (int)strlen(tail) * 6 * FILES_FOOT_SIZE, fty, tail, plateHiCyan());
  } else {
    ui3DText(12, fty, "INSERT CARD", plateHiCyan());
  }

  uiFrame(CYBER_GRID);
  uiScanlines();
  uiBlit();
}

//  The 3D title plate, for the views below that draw their own screens.
static void uiHeader(const char* title) { ui3DHeader(title); }

//  Centred message box over whatever is drawn (join progress, errors).
static void uiMsgBox(const char* l1, uint16_t c1, const char* l2, uint16_t c2) {
  const int w = TFT_W - 40, h = 52, x = 20, y = TFT_H / 2 - 22;
  inst->fillRect(x, y, w, h, CYBER_BG);
  inst->drawRect(x, y, w, h, c1);
  inst->setTextSize(2);
  inst->setTextColor(c1);
  inst->setCursor(TFT_W / 2 - (int)strlen(l1) * 6, y + 8);
  inst->print(l1);
  if (l2 && *l2) {
    inst->setTextSize(1);
    inst->setTextColor(c2);
    inst->setCursor(TFT_W / 2 - (int)strlen(l2) * 3, y + 34);
    inst->print(l2);
  }
}

#if WEB_ENABLE && SERVO_ENABLE
// ─────────────────────────────────────────────────────────────
//  Settings > WIFI > JOIN NETWORK — pick a network, type its password with
//  the D-pad, and join the controller to it.
//
//  The password is TESTED before anything is saved: the board connects
//  alongside its running hotspot (AP+STA), and only once the network has
//  actually accepted it are the credentials stored (NVS "wifi", exactly as
//  the web page's WiFi setup stores them). No restart: the web server is
//  already reachable on the new address, and the web task drops the
//  hotspot and captive portal live (webGoSta). Next boot joins the same
//  network from the saved credentials. A wrong password just returns to
//  the keyboard with the text intact.
// ─────────────────────────────────────────────────────────────
#define NET_MAX   24
#define NET_ROWS  5
#define JOIN_TIMEOUT_MS 15000

struct NetEnt { char ssid[33]; int8_t rssi; bool enc; };
static NetEnt  netList[NET_MAX];
static uint8_t netCount = 0, netSel = 0;   // netSel 0 = RESCAN, 1.. = networks
static bool    netScanning = false;

static char    kbSsid[33] = "";
static char    kbText[64] = "";
static uint8_t kbLen = 0, kbMode = 0, kbRow = 1, kbCol = 0;   // mode 0 abc 1 ABC 2 #+=
enum JoinState : uint8_t { JOIN_EDIT, JOIN_TRYING, JOIN_FAILED, JOIN_OK };
static JoinState joinState = JOIN_EDIT;
static uint32_t  joinMs = 0;

static void netStartScan() {
  //  The web server already has the radio up (AP+STA or STA) and both can
  //  scan as they are; only bring it up ourselves if it has not started.
  if (!webRunning) WiFi.mode(WIFI_AP_STA);
  WiFi.scanDelete();
  WiFi.scanNetworks(true, false);           // async; the view polls it
  netScanning = true;
  netCount = 0; netSel = 0;
}

//  Full-length SSIDs (the WIFI scanner view clips at 20, too short to join
//  by), one row per SSID at its strongest, strongest first, hidden skipped.
static void netHarvest(int n) {
  netCount = 0;
  for (int i = 0; i < n; i++) {
    String s = WiFi.SSID(i);
    if (!s.length()) continue;
    int8_t r = (int8_t)WiFi.RSSI(i);
    int k = 0;
    while (k < netCount && strcmp(netList[k].ssid, s.c_str())) k++;
    if (k < netCount) { if (r > netList[k].rssi) netList[k].rssi = r; continue; }
    if (netCount >= NET_MAX) continue;
    strncpy(netList[netCount].ssid, s.c_str(), 32); netList[netCount].ssid[32] = '\0';
    netList[netCount].rssi = r;
    netList[netCount].enc  = (WiFi.encryptionType(i) != WIFI_AUTH_OPEN);
    netCount++;
  }
  for (int i = 1; i < netCount; i++)          // insertion sort, strongest first
    for (int j = i; j > 0 && netList[j].rssi > netList[j - 1].rssi; j--) {
      NetEnt t = netList[j]; netList[j] = netList[j - 1]; netList[j - 1] = t;
    }
  WiFi.scanDelete();
  netScanning = false;
  netSel = netCount ? 1 : 0;
}

void uiViewNetPick() {
  inst->fillScreen(CYBER_BG);
  uiHeader("JOIN NETWORK");
  if (netScanning) {
    int done = WiFi.scanComplete();
    if (done >= 0) netHarvest(done);
    else if (done == WIFI_SCAN_FAILED) { netScanning = false; netCount = 0; }
  }
  if (netScanning) {
    char dots[4] = "   ";
    for (int i = 0; i < (int)((millis() / 350) % 4); i++) dots[i] = '.';
    inst->setTextSize(2);
    inst->setTextColor(NEON_CYAN);
    inst->setCursor((TFT_W - 11 * 12) / 2, TFT_H / 2);
    inst->printf("SCANNING%s", dots);
  } else {
    //  Scroll window over RESCAN + the networks, keeping the selection shown.
    int total = netCount + 1, first = netSel - NET_ROWS / 2;
    if (first > total - NET_ROWS) first = total - NET_ROWS;
    if (first < 0) first = 0;
    for (int r = 0; r < NET_ROWS && first + r < total; r++) {
      int i = first + r, y = 30 + r * 27;
      if (i == 0) {
        setRow(y, netSel == 0, netCount ? "RESCAN" : "NONE FOUND - RESCAN", nullptr, 0);
        continue;
      }
      const NetEnt& e = netList[i - 1];
      char nm[17]; strncpy(nm, e.ssid, 16); nm[16] = '\0';
      if (strlen(e.ssid) > 16) nm[15] = '~';
      char st[16]; snprintf(st, sizeof(st), "%s %d", e.enc ? "LOCK" : "OPEN", e.rssi);
      setRow(y, netSel == i, nm, st, wifiRssiColor(e.rssi));
    }
  }
  uiFrame(CYBER_GRID);
  uiScanlines();
  uiBlit();
}

static void joinStart() {
  Serial.printf("WiFi: trying \"%s\"\n", kbSsid);
  WiFi.begin(kbSsid, kbText);               // AP stays up alongside (AP+STA)
  joinState = JOIN_TRYING;
  joinMs = millis();
}

//  Give up on a try: drop the attempt and, if the controller was already
//  joined to another network, go back to it.
static void joinAbandon() {
  WiFi.disconnect(false);
  if (!webApMode) {
    prefs.begin("wifi", true);
    String s = prefs.getString("ssid", ""), p = prefs.getString("pass", "");
    prefs.end();
    if (s.length()) WiFi.begin(s.c_str(), p.c_str());
  }
}

static void netAction(UiAction a) {
  if (netScanning && a != ACT_BACK) return;
  int total = netCount + 1;
  switch (a) {
    case ACT_NEXT: netSel = (netSel + 1) % total; break;
    case ACT_PREV: netSel = (netSel + total - 1) % total; break;
    case ACT_RIGHT:
    case ACT_SELECT:
      if (netSel == 0) { netStartScan(); break; }
      strncpy(kbSsid, netList[netSel - 1].ssid, 32); kbSsid[32] = '\0';
      kbText[0] = '\0'; kbLen = 0; kbMode = 0; kbRow = 1; kbCol = 0;
      joinState = JOIN_EDIT;
      uiEnter(UI_KEYB);
      if (!netList[netSel - 1].enc) joinStart();   // open network: no password
      break;
    case ACT_BACK:
      uiEnter(UI_SETTINGS); setPage = SET_WIFI; setSel = 1;
      break;
    default: break;
  }
}

// ── On-screen keyboard ──
//  Four character rows and a row of actions, driven by the D-pad: UP/DOWN
//  change row, LEFT/RIGHT move along it (LEFT is not "back" here — ESC is),
//  ENTER presses. Rows may be different lengths; the column is clamped.
static const char* const kKbRows[3][4] = {
  { "1234567890", "qwertyuiop", "asdfghjkl-", "zxcvbnm_.@" },
  { "1234567890", "QWERTYUIOP", "ASDFGHJKL-", "ZXCVBNM_.@" },
  { "!@#$%^&*()", "-_=+[]{}\\|", ";:'\",.<>/?", "`~" },
};
static const char* const kKbSpecial[6] = { "Aa", "#+=", "SPC", "DEL", "OK", "ESC" };
#define KB_ROWS 5
static int kbRowLen(int r) { return r < 4 ? (int)strlen(kKbRows[kbMode][r]) : 6; }

//  One key. The selected key is a small raised 3D plate (1 px shadow: the
//  keys sit only 2 px apart) with the label stamped in.
static void kbKey(int x, int y, int w, int h, const char* lab, bool sel, uint16_t plate) {
  int tx = x + (w - (int)strlen(lab) * 12) / 2, ty = y + (h - 16) / 2;
  if (sel) {
    bool mag = (plate == NEON_MAGENTA);
    if (mag) ui3DPlate(x, y, w - 1, h - 1, PLATE_MAGENTA, 2, 1);
    else     ui3DPlate(x, y, w - 1, h - 1, PLATE_CYAN,    2, 1);
    ui3DText(tx, ty, lab, mag ? plateHiMagenta() : plateHiCyan());
    return;
  }
  inst->drawRect(x, y, w, h, CYBER_GRID);
  inst->setTextSize(2);
  inst->setTextColor(NEON_CYAN);
  inst->setCursor(tx, ty);
  inst->print(lab);
}

void uiViewKeyb() {
  //  Poll a join in progress.
  if (joinState == JOIN_TRYING) {
    wl_status_t s = WiFi.status();
    if (s == WL_CONNECTED) {
      prefs.begin("wifi", false);
      prefs.putString("ssid", kbSsid);
      prefs.putString("pass", kbText);
      prefs.putString("netmode", "sta");
      prefs.end();
      Serial.printf("WiFi: joined \"%s\" as %s - saved\n",
                    kbSsid, WiFi.localIP().toString().c_str());
      webGoSta  = true;                     // web task drops the hotspot, no restart
      joinState = JOIN_OK; joinMs = millis();
    } else if (millis() - joinMs > JOIN_TIMEOUT_MS ||
               ((s == WL_CONNECT_FAILED || s == WL_NO_SSID_AVAIL) && millis() - joinMs > 3000)) {
      joinAbandon();
      joinState = JOIN_FAILED;
    }
  }
  //  Leave the confirmation up long enough to read the address, then back to
  //  Settings > WIFI, whose status row now shows JOINED and the same IP.
  if (joinState == JOIN_OK && millis() - joinMs > 4000) {
    joinState = JOIN_EDIT;
    uiEnter(UI_SETTINGS); setPage = SET_WIFI; setSel = 0;
    return;
  }

  inst->fillScreen(CYBER_BG);
  char title[24]; snprintf(title, sizeof(title), "%.18s", kbSsid);
  uiHeader(title);

  //  Text field: the tail of the password if it outgrows the box, caret blinking.
  inst->drawRect(8, 30, TFT_W - 16, 20, NEON_CYAN);
  const int showMax = (TFT_W - 32) / 12;
  const char* tail = kbText + (kbLen > showMax ? kbLen - showMax : 0);
  inst->setTextSize(2);
  inst->setTextColor(WHITE);
  inst->setCursor(14, 32);
  inst->print(tail);
  if ((millis() / 400) % 2 && joinState == JOIN_EDIT)
    inst->fillRect(14 + (int)strlen(tail) * 12, 33, 2, 14, NEON_MAGENTA);

  //  Keys: 10-wide character rows, then the six action keys.
  const int kx0 = (TFT_W - 300) / 2;
  for (int r = 0; r < 4; r++) {
    const char* row = kKbRows[kbMode][r];
    for (int c = 0; row[c]; c++) {
      char lab[2] = { row[c], '\0' };
      kbKey(kx0 + c * 30, 54 + r * 22, 28, 20, lab, kbRow == r && kbCol == c, NEON_CYAN);
    }
  }
  for (int c = 0; c < 6; c++)
    kbKey(kx0 + c * 50, 54 + 4 * 22, 48, 20, kKbSpecial[c], kbRow == 4 && kbCol == c,
          c == 4 ? NEON_MAGENTA : NEON_CYAN);

  if (joinState == JOIN_TRYING) {
    char dots[4] = "   ";
    for (int i = 0; i < (int)((millis() / 350) % 4); i++) dots[i] = '.';
    char l1[24]; snprintf(l1, sizeof(l1), "CONNECTING%s", dots);
    uiMsgBox(l1, NEON_CYAN, "LEFT TO CANCEL", CYBER_DIMTXT);
  } else if (joinState == JOIN_FAILED) {
    uiMsgBox("COULD NOT JOIN", NEON_RED, "CHECK THE PASSWORD - ANY KEY TO EDIT", CYBER_DIMTXT);
  } else if (joinState == JOIN_OK) {
    char l2[40]; snprintf(l2, sizeof(l2), "NOW AT http://%s/", WiFi.localIP().toString().c_str());
    uiMsgBox("CONNECTED", NEON_GREEN, l2, NEON_CYAN);
  }
  uiFrame(CYBER_GRID);
  uiScanlines();
  uiBlit();
}

static void kbAction(UiAction a) {
  if (joinState == JOIN_OK) return;
  if (joinState == JOIN_TRYING) {
    if (a == ACT_BACK) { joinAbandon(); joinState = JOIN_EDIT; }
    return;
  }
  if (joinState == JOIN_FAILED) { joinState = JOIN_EDIT; return; }
  switch (a) {
    case ACT_PREV: kbRow = (kbRow + KB_ROWS - 1) % KB_ROWS; break;
    case ACT_NEXT: kbRow = (kbRow + 1) % KB_ROWS; break;
    case ACT_BACK:  { int n = kbRowLen(kbRow); kbCol = (kbCol + n - 1) % n; return; }
    case ACT_RIGHT: { int n = kbRowLen(kbRow); kbCol = (kbCol + 1) % n; return; }
    case ACT_SELECT:
      if (kbRow < 4) {
        if (kbLen < sizeof(kbText) - 1) { kbText[kbLen++] = kKbRows[kbMode][kbRow][kbCol]; kbText[kbLen] = '\0'; }
      } else switch (kbCol) {
        case 0: kbMode = (kbMode == 0) ? 1 : 0; break;             // Aa
        case 1: kbMode = (kbMode == 2) ? 0 : 2; break;             // #+=
        case 2: if (kbLen < sizeof(kbText) - 1) { kbText[kbLen++] = ' '; kbText[kbLen] = '\0'; } break;
        case 3: if (kbLen) kbText[--kbLen] = '\0'; break;          // DEL
        case 4: joinStart(); break;                                // OK
        case 5: uiEnter(UI_NETPICK); return;                       // ESC
      }
      break;
    default: break;
  }
  int n = kbRowLen(kbRow);                  // row or layout changed: clamp
  if (kbCol >= n) kbCol = n - 1;
}
#endif  // WEB_ENABLE && SERVO_ENABLE

#if SERVO_ENABLE
// ─────────────────────────────────────────────────────────────
//  SEQUENCES — play realsequencer exports from the SD card on the servos.
//
//  Files: *.csv and *.seq in the card root and in /sequences. A .seq is the
//  sequencer's ZIP bundle (CSV + media); JSZip writes it uncompressed, so
//  sequence.csv is found through the ZIP's central directory and read in
//  place — no decompressor. Media in the bundle is ignored.
//
//  Playback matches the sequencer's own USB (HID) output exactly:
//    angle = getAngleAt(track, t, interp)   linear / ease (smoothstep) / step,
//            first keyframe's angle before it, last after it, 90 if none
//    value = round(clamp(angle, 0, 180) / 180 * 255) -> servoSet(ch - 1)
//  Only enabled tracks with an output channel 1-32 are driven; every other
//  channel is left where it is. LOOP modes: once / loop / ping-pong.
//  Playback runs from loop() while SEQUENCES is open (player or file list);
//  leaving SEQUENCES for any other view stops it (see uiEnter).
// ─────────────────────────────────────────────────────────────
#include <vector>
#include <algorithm>
#define SEQ_FILES_MAX 32
#define SEQ_UPDATE_MS 20

//  Which files are sequences. No extra marker is needed — realsequencer
//  already writes one, and its own importer tells formats apart the same way
//  (parseAndDisplayCSV): look at the first non-empty line.
//    SEQ_NEW     "#SETTINGS"  — the current sectioned export
//    SEQ_LEGACY  a header with a "time..." column and "*_angle" columns —
//                the old sampled export the sequencer still imports
//  Anything else (imulog.csv, spreadsheets, ...) is not listed, and is
//  refused if asked for by name. Checked while listing, so a wrong file is
//  never offered in the first place.
#define SEQ_NONE   0
#define SEQ_NEW    1
#define SEQ_LEGACY 2
//  Hard limits, so a huge or hostile file fails fast instead of freezing
//  the UI or running the heap dry. A 60 s legacy capture of 32 servos at
//  50 Hz is well under both.
#define SEQ_MAX_BYTES (4UL * 1024 * 1024)
#define SEQ_MAX_KEYS  30000
#define SEQ_MAX_COLS  64

struct SeqFile  { char path[64]; uint32_t size; };
struct SeqKey   { float t, a; };
struct SeqTrack { int ch = 0; bool en = true; uint16_t col = 0; std::vector<SeqKey> k; };

//  Curve colours for tracks the file gives none for (legacy exports): the
//  theme's neons first, then a few extras.
static const uint16_t kSeqPalette[8] = {          // the RealDriver colours first
  0x07FC /*cyan*/, 0xF9EB /*red*/, 0xFEA0 /*yellow*/, 0x07F1 /*green*/,
  0xFBD1 /*light red*/, 0xFCC7 /*orange*/, 0x7DDF /*light blue*/, 0xFFFF /*white*/ };

//  "#rrggbb" (the sequencer's track colour) -> rgb565, 0 if not that form.
static uint16_t seqParseColour(const char* s) {
  while (*s == ' ') s++;
  if (*s != '#' || strlen(s) < 7) return 0;
  char hex[7]; memcpy(hex, s + 1, 6); hex[6] = '\0';
  uint32_t v = strtoul(hex, nullptr, 16);
  uint16_t c = ((v >> 8) & 0xF800) | ((v >> 5) & 0x07E0) | ((v >> 3) & 0x001F);
  return c ? c : 0x2104;                     // pure black -> just-visible grey
}

static SeqFile  seqFiles[SEQ_FILES_MAX];
static uint8_t  seqFileCount = 0, seqFileSel = 0;
static std::vector<SeqTrack> seqTracks;
static char     seqName[40] = "";
static float    seqDur = 0, seqPos = 0;
static uint8_t  seqLoop = 0, seqInterp = 0;   // loop 0 once 1 loop 2 ping; interp 0 lin 1 ease 2 step
static bool     seqLoaded = false, seqPlaying = false, seqListMode = true;
static uint32_t seqStartMs = 0;
static uint8_t  seqBtn = 0;                   // player button: 0 play/stop 1 loop 2 list
static char     seqErr[40] = "";

static const char* seqBase(const char* p) { const char* s = strrchr(p, '/'); return s ? s + 1 : p; }

static uint16_t rd16(const uint8_t* p) { return p[0] | (p[1] << 8); }
static uint32_t rd32(const uint8_t* p) { return p[0] | (p[1] << 8) | (p[2] << 16) | ((uint32_t)p[3] << 24); }

//  Locate sequence.csv inside a .seq ZIP via the central directory (which
//  always carries the sizes). Returns false with seqErr set on failure.
//  The end record is looked for in the last 1 KB first (JSZip writes no
//  archive comment), and only then in the full 64 KB a comment could take.
static bool seqZipFind(File& f, uint32_t* off, uint32_t* len) {
  uint32_t sz = f.size();
  uint8_t sig[4] = { 0 };
  f.seek(0);
  if (sz < 22 || f.read(sig, 4) != 4 || rd32(sig) != 0x04034b50) {
    strcpy(seqErr, "NOT A .SEQ BUNDLE"); return false;
  }
  uint32_t cdOff = 0; uint16_t cdN = 0; bool found = false;
  for (uint32_t want : { 1024UL, 65557UL }) {
    uint32_t tailLen = sz < want ? sz : want;
    uint8_t* tail = (uint8_t*)malloc(tailLen);
    if (!tail) { strcpy(seqErr, "OUT OF MEMORY"); return false; }
    f.seek(sz - tailLen);
    f.read(tail, tailLen);
    for (int i = (int)tailLen - 22; i >= 0; i--)
      if (rd32(tail + i) == 0x06054b50) {
        cdN = rd16(tail + i + 10); cdOff = rd32(tail + i + 16); found = true; break;
      }
    free(tail);
    if (found || tailLen == sz) break;
  }
  if (!found || cdOff >= sz) { strcpy(seqErr, "DAMAGED .SEQ"); return false; }

  f.seek(cdOff);
  for (uint16_t n = 0; n < cdN; n++) {
    uint8_t h[46];
    if (f.read(h, 46) != 46 || rd32(h) != 0x02014b50) break;
    uint16_t method = rd16(h + 10), nl = rd16(h + 28), xl = rd16(h + 30), cl = rd16(h + 32);
    uint32_t csize = rd32(h + 20), lofs = rd32(h + 42);
    char name[96] = "";
    uint16_t take = nl < sizeof(name) - 1 ? nl : sizeof(name) - 1;
    f.read((uint8_t*)name, take); name[take] = '\0';
    f.seek(f.position() + (nl - take) + xl + cl);
    if (!strcasecmp(seqBase(name), "sequence.csv")) {
      if (method != 0) { strcpy(seqErr, "COMPRESSED .SEQ"); return false; }
      uint8_t lh[30];
      f.seek(lofs);
      if (f.read(lh, 30) != 30 || rd32(lh) != 0x04034b50) { strcpy(seqErr, "DAMAGED .SEQ"); return false; }
      *off = lofs + 30 + rd16(lh + 26) + rd16(lh + 28);
      *len = csize;
      if (*off + *len > sz) { strcpy(seqErr, "DAMAGED .SEQ"); return false; }
      return true;
    }
  }
  strcpy(seqErr, "NO SEQUENCE IN .SEQ");
  return false;
}

//  Buffered line reader over [off, off+len) of one file — 512-byte block
//  reads instead of a read per character. Lines longer than the caller's
//  buffer are cut (the rest skipped), so a binary or single-line file
//  cannot overrun anything. State is file-scope: one reader at a time.
static File*    rdF;
static uint8_t  rdBuf[512];
static uint16_t rdN = 0, rdI = 0;
static uint32_t rdLeft = 0;
static void rdBegin(File& f, uint32_t off, uint32_t len) {
  rdF = &f; f.seek(off); rdLeft = len; rdN = rdI = 0;
}
static bool rdLine(char* buf, size_t max) {
  size_t n = 0; bool any = false;
  for (;;) {
    if (rdI >= rdN) {
      if (!rdLeft) break;
      uint32_t want = rdLeft < sizeof(rdBuf) ? rdLeft : sizeof(rdBuf);
      int got = rdF->read(rdBuf, want);
      if (got <= 0) { rdLeft = 0; break; }
      rdN = (uint16_t)got; rdI = 0; rdLeft -= got;
    }
    char c = (char)rdBuf[rdI++];
    any = true;
    if (c == '\n') break;
    if (c != '\r' && n < max - 1) buf[n++] = c;
  }
  buf[n] = '\0';
  return any;
}

//  First non-empty line of a candidate -> SEQ_NEW / SEQ_LEGACY / SEQ_NONE.
static uint8_t seqKindOf(const char* line) {
  if (!strncmp(line, "\xEF\xBB\xBF", 3)) line += 3;           // UTF-8 BOM
  while (*line == ' ' || *line == '\t') line++;
  if (!strncmp(line, "#SETTINGS", 9)) return SEQ_NEW;
  //  Legacy header: a column starting "time" and at least one "*_angle".
  bool hasTime = false, hasAngle = false;
  const char* p = line;
  while (*p) {
    while (*p == ' ') p++;
    const char* s = p;
    while (*p && *p != ',') p++;
    const char* e = p;
    while (e > s && e[-1] == ' ') e--;
    if (e - s >= 4 && !strncasecmp(s, "time", 4)) hasTime = true;
    if (e - s > 6 && !strncasecmp(e - 6, "_angle", 6)) hasAngle = true;
    if (*p == ',') p++;
  }
  return (hasTime && hasAngle) ? SEQ_LEGACY : SEQ_NONE;
}

//  Open path and find its CSV text: the whole file, or sequence.csv inside
//  a .seq. Leaves f open on success.
static bool seqOpenCsv(const char* path, File& f, uint32_t* off, uint32_t* len) {
  f = SD_MMC.open(path);
  if (!f || f.isDirectory()) { strcpy(seqErr, "CANNOT OPEN"); if (f) f.close(); return false; }
  *off = 0; *len = f.size();
  const char* dot = strrchr(path, '.');
  if (dot && !strcasecmp(dot, ".seq") && !seqZipFind(f, off, len)) { f.close(); return false; }
  return true;
}

//  Cheap check used while listing: only the first line is read.
static uint8_t seqSniff(const char* path) {
  File f; uint32_t off, len;
  if (!seqOpenCsv(path, f, &off, &len)) return SEQ_NONE;
  rdBegin(f, off, len);
  char line[256]; uint8_t kind = SEQ_NONE;
  for (int i = 0; i < 4 && rdLine(line, sizeof(line)); i++)
    if (line[0]) { kind = seqKindOf(line); break; }
  f.close();
  return kind;
}

static void seqScanDir(const char* dir) {
  File d = SD_MMC.open(dir);
  if (!d || !d.isDirectory()) return;
  File e;
  while ((e = d.openNextFile()) && seqFileCount < SEQ_FILES_MAX) {
    char path[64];
    const char* nm = seqBase(e.name());
    const char* dot = strrchr(nm, '.');
    bool cand = !e.isDirectory() && dot && (!strcasecmp(dot, ".seq") || !strcasecmp(dot, ".csv"));
    uint32_t size = (uint32_t)e.size();
    snprintf(path, sizeof(path), "%s%s%s", dir, strcmp(dir, "/") ? "/" : "", nm);
    e.close();
    if (cand && seqSniff(path) != SEQ_NONE) {
      SeqFile& f = seqFiles[seqFileCount++];
      strcpy(f.path, path);
      f.size = size;
    }
  }
  d.close();
}
void seqScanFiles() {
  seqFileCount = 0;
  if (!sdMounted) return;
  seqScanDir("/");
  seqScanDir("/sequences");
  if (seqFileSel >= seqFileCount) seqFileSel = 0;
}

//  Let the rest of the system breathe during a long load: the idle task on
//  this core is watched by the task watchdog, which resets the board if a
//  loop never yields for ~5 s.
static void seqYield() {
  static uint32_t last = 0;
  if (millis() - last > 50) { vTaskDelay(1); last = millis(); }
}

//  Split a CSV row in place into up to max trimmed fields.
static int seqSplit(char* line, char** out, int max) {
  int n = 0; char* p = line;
  while (n < max) {
    while (*p == ' ') p++;
    out[n++] = p;
    char* c = strchr(p, ',');
    char* e = c ? c : p + strlen(p);
    while (e > p && e[-1] == ' ') e--;
    if (!c) { *e = '\0'; break; }
    *e = '\0'; p = c + 1;
  }
  return n;
}

//  Load and validate a sequence. Everything is parsed into locals and only
//  swapped in on success, so a bad file leaves the current sequence (even a
//  playing one) untouched.
bool seqLoad(const char* path) {
  seqErr[0] = '\0';
  File f; uint32_t off, len;
  if (!seqOpenCsv(path, f, &off, &len)) return false;
  if (len > SEQ_MAX_BYTES) { f.close(); strcpy(seqErr, "FILE TOO BIG"); return false; }
  rdBegin(f, off, len);

  static char line[1024];                   // legacy headers can be long; static: off the stack
  uint8_t kind = SEQ_NONE;
  while (rdLine(line, sizeof(line))) if (line[0]) { kind = seqKindOf(line); break; }
  if (kind == SEQ_NONE) { f.close(); strcpy(seqErr, "NOT A SEQUENCE"); return false; }

  std::vector<SeqTrack> tracks;
  char    name[40];
  float   dur = 0, maxT = 0;
  uint8_t loop = 0, interp = 0;
  uint32_t keys = 0;
  bool    tooMany = false;
  strncpy(name, seqBase(path), sizeof(name) - 1); name[sizeof(name) - 1] = '\0';
  char* d = strrchr(name, '.'); if (d) *d = '\0';

  if (kind == SEQ_NEW) {
    enum { S_NONE, S_SET, S_SERVO, S_KEY } sec = S_SET;   // line 1 was #SETTINGS
    while (!tooMany && rdLine(line, sizeof(line))) {
      seqYield();
      if (!line[0]) continue;
      if (line[0] == '#') {
        sec = !strncmp(line, "#SETTINGS", 9) ? S_SET : !strncmp(line, "#SERVOS", 7) ? S_SERVO
            : !strncmp(line, "#KEYFRAMES", 10) ? S_KEY : S_NONE;
        continue;
      }
      char* comma = strchr(line, ',');
      if (!comma) continue;
      if (sec == S_SET) {
        *comma = '\0'; const char* v = comma + 1;
        if      (!strcmp(line, "duration"))  dur = atof(v);
        else if (!strcmp(line, "loop_mode")) loop = !strcmp(v, "loop") ? 1 : !strcmp(v, "ping") ? 2 : 0;
        else if (!strcmp(line, "interp"))    interp = !strcmp(v, "ease") ? 1 : !strcmp(v, "step") ? 2 : 0;
        else if (!strcmp(line, "name") && *v) { strncpy(name, v, sizeof(name) - 1); name[sizeof(name) - 1] = '\0'; }
      } else if (sec == S_SERVO) {
        //  idx,name,ch,color,enabled — the name is written unquoted and may
        //  hold commas, so ch/enabled are taken from the right-hand end.
        if (line[0] < '0' || line[0] > '9') continue;          // column header
        int idx = atoi(line);
        char* c3 = strrchr(line, ','); if (!c3 || c3 == comma) continue;
        *c3 = '\0'; char* c2 = strrchr(line, ','); if (!c2 || c2 == comma) continue;
        *c2 = '\0'; char* c1 = strrchr(line, ','); if (!c1) continue;
        if (idx < 0 || idx >= SEQ_MAX_COLS) continue;
        if ((int)tracks.size() <= idx) tracks.resize(idx + 1);
        tracks[idx].ch  = atoi(c1 + 1);
        tracks[idx].en  = strcmp(c3 + 1, "false") != 0;
        tracks[idx].col = seqParseColour(c2 + 1);     // the colour field
      } else if (sec == S_KEY) {
        if (line[0] < '0' || line[0] > '9') continue;          // column header
        int idx = atoi(line); char* c2 = strchr(comma + 1, ',');
        if (!c2 || idx < 0 || idx >= SEQ_MAX_COLS) continue;
        if (++keys > SEQ_MAX_KEYS) { tooMany = true; break; }
        SeqKey k = { (float)atof(comma + 1), (float)atof(c2 + 1) };
        if ((int)tracks.size() <= idx) tracks.resize(idx + 1);
        tracks[idx].k.push_back(k);
        if (k.t > maxT) maxT = k.t;
      }
    }
    for (auto& t : tracks)
      std::sort(t.k.begin(), t.k.end(), [](const SeqKey& a, const SeqKey& b) { return a.t < b.t; });
  } else {
    //  Legacy sampled format, converted the way the sequencer converts it
    //  (loadLegacyFormatIntoSequencer): one track per *_angle column on
    //  output channel 1, 2, 3 ... in column order; a sample becomes a
    //  keyframe only when it moved >= 0.5 deg from the last one kept, plus
    //  the first and last samples; t rounded to ms, angle to 0.1 deg;
    //  duration = the last row's time.
    char* col[SEQ_MAX_COLS];
    int nc = seqSplit(line, col, SEQ_MAX_COLS), timeIdx = -1;
    int angCol[SEQ_MAX_COLS]; int na = 0;
    for (int i = 0; i < nc; i++) {
      size_t l = strlen(col[i]);
      if (timeIdx < 0 && !strncasecmp(col[i], "time", 4)) timeIdx = i;
      if (l > 6 && !strcasecmp(col[i] + l - 6, "_angle")) angCol[na++] = i;
    }
    tracks.resize(na);
    std::vector<SeqKey> lastSeen(na, SeqKey{ 0, 0 });
    std::vector<bool>   seen(na, false);
    for (int s = 0; s < na; s++) tracks[s].ch = s + 1;
    while (!tooMany && rdLine(line, sizeof(line))) {
      seqYield();
      if (!line[0]) continue;
      char* v[SEQ_MAX_COLS];
      int n = seqSplit(line, v, SEQ_MAX_COLS);
      if (timeIdx >= n || !*v[timeIdx]) continue;
      float t = roundf(atof(v[timeIdx]) * 1000.0f) / 1000.0f;
      for (int s = 0; s < na; s++) {
        if (angCol[s] >= n || !*v[angCol[s]]) continue;
        SeqKey k = { t, roundf(atof(v[angCol[s]]) * 10.0f) / 10.0f };
        std::vector<SeqKey>& K = tracks[s].k;
        if (!seen[s] || fabsf(k.a - K.back().a) >= 0.5f) {
          if (++keys > SEQ_MAX_KEYS) { tooMany = true; break; }
          K.push_back(k);
        }
        seen[s] = true; lastSeen[s] = k;
      }
      maxT = t;                                           // the last row's time
    }
    for (int s = 0; s < na; s++)                          // ... plus the last sample
      if (seen[s] && (tracks[s].k.back().t != lastSeen[s].t)) tracks[s].k.push_back(lastSeen[s]);
  }
  f.close();

  if (tooMany) { strcpy(seqErr, "TOO MANY KEYFRAMES"); return false; }
  int driven = 0;
  for (const auto& t : tracks) if (t.en && t.ch >= 1 && t.ch <= NUM_SERVOS) driven++;
  if (!driven) { strcpy(seqErr, "NO SERVO CHANNELS"); return false; }
  if (dur <= 0 || kind == SEQ_LEGACY) dur = maxT;
  if (dur <= 0) { strcpy(seqErr, "EMPTY SEQUENCE"); return false; }

  //  Valid — swap it in.
  seqPlaying = false;
  seqTracks.swap(tracks);
  strcpy(seqName, name);
  seqDur = dur; seqLoop = loop; seqInterp = interp;
  seqLoaded = true; seqPos = 0;
  {                                         // palette colour where the file gave none
    int n = 0;
    for (auto& t : seqTracks) if (!t.col) t.col = kSeqPalette[n++ % 8];
  }
  seqBuildGraph();
  Serial.printf("SEQ: %s (%s) - %d servos, %lu keys, %.2f s, %s, %s\n", seqName,
                kind == SEQ_LEGACY ? "legacy" : "sequencer", driven, (unsigned long)keys, seqDur,
                seqInterp == 1 ? "ease" : seqInterp == 2 ? "step" : "linear",
                seqLoop == 1 ? "loop" : seqLoop == 2 ? "ping" : "once");
  return true;
}

//  The sequencer's getAngleAt(), verbatim in behaviour. Takes a track INDEX:
//  the .ino prototype generator puts prototypes above the SeqTrack type, so
//  a SeqTrack parameter would not compile.
static float seqAngleAt(int ti, float t) {
  const std::vector<SeqKey>& k = seqTracks[ti].k;
  if (k.empty()) return 90;
  if (t <= k.front().t) return k.front().a;
  if (t >= k.back().t)  return k.back().a;
  for (size_t i = 0; i + 1 < k.size(); i++) {
    if (t >= k[i].t && t <= k[i + 1].t) {
      float span = k[i + 1].t - k[i].t;
      float p = span > 0 ? (t - k[i].t) / span : 1;
      if (seqInterp == 2) return k[i].a;
      if (seqInterp == 1) p = p * p * (3 - 2 * p);
      return k[i].a + (k[i + 1].a - k[i].a) * p;
    }
  }
  return 90;
}

// ── Player graph ──
//  A miniature of the sequencer's timeline: every driven track's angle
//  (0-180) over the whole duration, one sample per pixel column, in the
//  track's own colour. Sampled once at load (seqBuildGraph), so drawing it
//  each frame is only line segments.
#define SEQ_GX  12                              // graph box on the player screen
#define SEQ_GY  52
#define SEQ_GW  (TFT_W - 24)
#define SEQ_GH  82
#define SEQ_PW  (SEQ_GW - 4)                    // plot area inside the box
#define SEQ_PH  (SEQ_GH - 6)
static std::vector<uint8_t>  seqGraph;          // [driven track][column] -> y in plot
static std::vector<uint16_t> seqGraphCol;       // colour per driven track
static std::vector<int>      seqGraphIdx;       // seqTracks index per driven track

void seqBuildGraph() {
  seqGraphIdx.clear(); seqGraphCol.clear();
  for (int i = 0; i < (int)seqTracks.size(); i++) {
    const SeqTrack& t = seqTracks[i];
    if (t.en && t.ch >= 1 && t.ch <= NUM_SERVOS) { seqGraphIdx.push_back(i); seqGraphCol.push_back(t.col); }
  }
  seqGraph.assign(seqGraphIdx.size() * SEQ_PW, 0);
  for (size_t k = 0; k < seqGraphIdx.size(); k++) {
    for (int x = 0; x < SEQ_PW; x++) {
      float a = seqAngleAt(seqGraphIdx[k], seqDur * x / (SEQ_PW - 1));
      if (a < 0) a = 0; if (a > 180) a = 180;
      seqGraph[k * SEQ_PW + x] = (uint8_t)((SEQ_PH - 1) - lroundf(a / 180.0f * (SEQ_PH - 1)));
    }
    seqYield();
  }
}

//  Box, 0/90/180 guides, one-second (or coarser) ticks, the played part
//  tinted, every curve, then the playhead with a dot on each track's
//  current position.
static void seqDrawGraph() {
  const int px = SEQ_GX + 2, py = SEQ_GY + 3;
  inst->drawRect(SEQ_GX, SEQ_GY, SEQ_GW, SEQ_GH, CYBER_GRID);

  float frac = seqDur > 0 ? seqPos / seqDur : 0;
  if (frac > 1) frac = 1;
  const int hx = px + (int)lroundf(frac * (SEQ_PW - 1));
  if (hx > px) inst->fillRect(px, py, hx - px, SEQ_PH, 0x0905);      // played: faint teal

  for (int q = 0; q <= 2; q++) {                                      // 180 / 90 / 0 degrees
    int gy = py + q * (SEQ_PH - 1) / 2;
    for (int x = px; x < px + SEQ_PW; x += (q == 1 ? 3 : 6)) inst->drawPixel(x, gy, CYBER_GRID);
  }
  if (seqDur > 0) {                                                   // time ticks, <= ~15 of them
    float step = 1;
    while (seqDur / step > 15) step *= (step == 1 || step == 10) ? 5 : 2;   // 1,5,10,50,100...
    for (float s = step; s < seqDur; s += step) {
      int x = px + (int)lroundf(s / seqDur * (SEQ_PW - 1));
      inst->drawFastVLine(x, py + SEQ_PH - 4, 4, CYBER_GRID);
    }
  }

  for (size_t k = 0; k < seqGraphIdx.size(); k++) {
    const uint8_t* g = &seqGraph[k * SEQ_PW];
    for (int x = 1; x < SEQ_PW; x++)
      inst->drawLine(px + x - 1, py + g[x - 1], px + x, py + g[x], seqGraphCol[k]);
  }

  //  Playhead: magenta line, a marker above the box, current-value dots.
  inst->drawFastVLine(hx, SEQ_GY + 1, SEQ_GH - 2, NEON_MAGENTA);
  inst->fillTriangle(hx - 4, SEQ_GY - 5, hx + 4, SEQ_GY - 5, hx, SEQ_GY, NEON_MAGENTA);
  const int col = hx - px;
  for (size_t k = 0; k < seqGraphIdx.size() && col >= 0 && col < SEQ_PW; k++) {
    int y = py + seqGraph[k * SEQ_PW + col];
    inst->fillCircle(hx, y, 3, BLACK);
    inst->fillCircle(hx, y, 2, seqGraphCol[k]);
  }
}

void seqPlay()  { if (seqLoaded) { seqPlaying = true; seqStartMs = millis(); seqPos = 0; } }
void seqStop()  { seqPlaying = false; }

//  Console "seq": the sequence state lives down here, below the console, so
//  it asks through this function rather than reading the variables itself.
//    seq             status        seq ls          list files
//    seq play [n|file]  load + play (number from "seq ls", or a path)
//    seq stop
void seqConsole(char* arg) {
  if (!strcmp(arg, "ls")) {
    seqScanFiles();
    for (int i = 0; i < seqFileCount; i++)
      Serial.printf("%2d  %s  (%lu B)\n", i + 1, seqFiles[i].path, (unsigned long)seqFiles[i].size);
    if (!seqFileCount) Serial.println(sdMounted ? "no .seq/.csv in / or /sequences" : "no card");
    return;
  }
  if (!strcmp(arg, "stop")) { seqStop(); Serial.println("seq stopped"); return; }
  if (!strncmp(arg, "play", 4)) {
    const char* w = arg + 4; while (*w == ' ') w++;
    char path[64] = "";
    if (!*w && seqLoaded) { seqPlay(); Serial.println("seq replay"); return; }
    if (*w >= '1' && *w <= '9' && atoi(w) <= 99) {
      seqScanFiles();
      int n = atoi(w);
      if (n < 1 || n > seqFileCount) { Serial.println("no such number - see seq ls"); return; }
      strncpy(path, seqFiles[n - 1].path, sizeof(path) - 1);
    } else if (*w) {
      snprintf(path, sizeof(path), "%s%s", *w == '/' ? "" : "/", w);
    } else { Serial.println("seq play <n|file>"); return; }
    if (seqLoad(path)) { seqListMode = false; seqPlay(); }
    else Serial.printf("seq: %s - %s\n", path, seqErr);
    return;
  }
  if (*arg) { Serial.println("seq [ls | play <n|file> | stop]"); return; }
  if (!seqLoaded) { Serial.println("seq: nothing loaded"); return; }
  Serial.printf("seq: %s  %s  %.1f / %.1f s  %s\n", seqName,
                seqPlaying ? "PLAYING" : "stopped", seqPos, seqDur,
                seqLoop == 1 ? "loop" : seqLoop == 2 ? "ping" : "once");
}

//  loop(): advance the playhead and drive the servos.
void seqService() {
  static uint32_t last = 0;
  if (!seqPlaying || millis() - last < SEQ_UPDATE_MS) return;
  last = millis();
  float t = (millis() - seqStartMs) / 1000.0f, tt = 0;
  bool done = false;
  if (seqDur <= 0)       tt = 0, done = (seqLoop == 0);
  else if (seqLoop == 1) tt = fmodf(t, seqDur);
  else if (seqLoop == 2) { float p = fmodf(t, 2 * seqDur); tt = p <= seqDur ? p : 2 * seqDur - p; }
  else if (t >= seqDur)  tt = seqDur, done = true;
  else                   tt = t;
  seqPos = tt;
  for (int i = 0; i < (int)seqTracks.size(); i++) {
    const SeqTrack& tr = seqTracks[i];
    if (!tr.en || tr.ch < 1 || tr.ch > NUM_SERVOS) continue;
    float a = seqAngleAt(i, tt);
    if (a < 0) a = 0; if (a > 180) a = 180;
    servoSet(tr.ch - 1, (int)lroundf(a / 180.0f * 255.0f));
  }
  if (done) seqPlaying = false;
}

void uiViewSeq() {
  inst->fillScreen(CYBER_BG);
  if (seqListMode || !seqLoaded) {
    uiHeader(seqPlaying ? "SEQUENCES  >PLAY" : "SEQUENCES");
    if (!sdMounted || !seqFileCount) {
      inst->setTextSize(2);
      inst->setTextColor(sdMounted ? CYBER_DIMTXT : NEON_RED);
      const char* m = sdMounted ? "NO SEQUENCES" : "NO CARD";
      inst->setCursor(TFT_W / 2 - (int)strlen(m) * 6, TFT_H / 2 - 12);
      inst->print(m);
      inst->setTextSize(1);
      inst->setTextColor(CYBER_DIMTXT);
      const char* h = "put .seq / .csv in / or /sequences";
      inst->setCursor(TFT_W / 2 - (int)strlen(h) * 3, TFT_H / 2 + 10);
      inst->print(h);
    } else {
      int first = seqFileSel - NET_ROWS / 2;
      if (first > seqFileCount - NET_ROWS) first = seqFileCount - NET_ROWS;
      if (first < 0) first = 0;
      for (int r = 0; r < NET_ROWS && first + r < seqFileCount; r++) {
        int i = first + r;
        const char* nm = seqBase(seqFiles[i].path);
        //  Name only, extension dropped; the whole row width is free for it
        //  (size 2 from x=22 to the row's right edge = 22 characters).
        const int maxCh = (TFT_W - 24 - 22) / 12;
        char lab[40]; strncpy(lab, nm, sizeof(lab) - 1); lab[sizeof(lab) - 1] = '\0';
        char* d = strrchr(lab, '.'); if (d) *d = '\0';
        if ((int)strlen(lab) > maxCh) { lab[maxCh] = '\0'; lab[maxCh - 1] = '~'; }
        setRow(30 + r * 27, seqFileSel == i, lab, nullptr, 0);
      }
    }
  } else {
    //  Player: the header names the sequence and its length; under it the
    //  playhead time and state, then the curve graph and PLAY/STOP - LOOP -
    //  LIST buttons.
    char dur[16]; snprintf(dur, sizeof(dur), "%.1fs", seqDur);
    const int dw = (int)strlen(dur) * 12, hty = MENU_HEAD_Y + (MENU_HEAD_H - 16) / 2;
    int maxCh = (TFT_W - 17 - dw - 12 - 12) / 12;          // name stops a glyph short of it
    char nm[26]; snprintf(nm, sizeof(nm), "%.*s", maxCh < 24 ? maxCh : 24, seqName);
    if ((int)strlen(seqName) > maxCh && maxCh > 1) nm[maxCh - 1] = '~';
    ui3DHeader(nm);
    ui3DText(TFT_W - 17 - dw, hty, dur, plateHiMagenta());

    char tm[16]; snprintf(tm, sizeof(tm), "%.1fs", seqPos);
    const char* stt = seqPlaying ? "PLAYING"
                    : (seqPos >= seqDur && seqDur > 0) ? "DONE"
                    : (seqPos <= 0) ? "READY" : "STOPPED";
    inst->setTextSize(2);
    inst->setTextColor(seqPlaying ? WHITE : CYBER_DIMTXT);  // bright while it runs
    inst->setCursor(12, 32);
    inst->print(tm);
    inst->setTextColor(seqPlaying ? NEON_CYAN : NEON_PINK);
    inst->setCursor(TFT_W - 12 - (int)strlen(stt) * 12, 32);
    inst->print(stt);

    seqDrawGraph();

    const char* lab[3] = { seqPlaying ? "STOP" : "PLAY",
                           seqLoop == 1 ? "LOOP" : seqLoop == 2 ? "PING" : "ONCE", "LIST" };
    const int w = (TFT_W - 24 - 16) / 3;
    for (int b = 0; b < 3; b++)
      uiButton(12 + b * (w + 8), TFT_H - 6 - 26, w, 26, lab[b], seqBtn == b,
               b == 0 ? NEON_MAGENTA : NEON_CYAN);
  }
  uiFrame(CYBER_GRID);
  uiScanlines();
  uiBlit();
}

static void seqAction(UiAction a) {
  if (seqListMode || !seqLoaded) {
    switch (a) {
      case ACT_NEXT: if (seqFileCount) seqFileSel = (seqFileSel + 1) % seqFileCount; break;
      case ACT_PREV: if (seqFileCount) seqFileSel = (seqFileSel + seqFileCount - 1) % seqFileCount; break;
      case ACT_RIGHT:
      case ACT_SELECT:
        if (!seqFileCount) { seqScanFiles(); break; }
        toast("LOADING", NEON_CYAN);
        //  Load only: the player opens stopped at 0.0 with PLAY highlighted,
        //  so nothing moves until the user presses it.
        if (seqLoad(seqFiles[seqFileSel].path)) { seqListMode = false; seqBtn = 0; }
        else toast(seqErr, NEON_RED);
        break;
      case ACT_BACK: uiSel = UI_SEQ - 1; uiEnter(UI_MENU); break;   // uiEnter stops playback
      default: break;
    }
    return;
  }
  switch (a) {
    case ACT_NEXT: case ACT_RIGHT: seqBtn = (seqBtn + 1) % 3; break;
    case ACT_PREV:                 seqBtn = (seqBtn + 2) % 3; break;
    case ACT_SELECT:
      if (seqBtn == 0) { if (seqPlaying) seqStop(); else seqPlay(); }
      else if (seqBtn == 1) seqLoop = (seqLoop + 1) % 3;
      else { seqListMode = true; seqScanFiles(); }
      break;
    //  LEFT steps back one level at a time: from LOOP/LIST to the PLAY
    //  button first, and only from PLAY out to the file list (still inside
    //  SEQUENCES, so a playing sequence keeps playing).
    case ACT_BACK:
      if (seqBtn != 0) seqBtn = 0;
      else { seqListMode = true; seqScanFiles(); }
      break;
    default: break;
  }
}
#endif  // SERVO_ENABLE

// ─────────────────────────────────────────────────────────────
//  NEON RUNNER — a small side-scrolling platformer.
//
//  An original game in the classic run-and-jump style (not a copy of any
//  commercial game's characters, art or levels): a little neon robot runs
//  through a cyberpunk skyline, stomps patrol droids, bumps "?" blocks for
//  coins, and reaches the goal beacon at the end of each level.
//
//  Levels are generated from a seed out of hand-made segments (flat runs,
//  pits, stairs, floating platforms, block rows, droid patrols), so each
//  level differs and later ones are longer, with wider pits and more
//  droids. The generator only emits jumps the physics below can clear.
//
//  Controls (PCF8574 pad, read as HELD buttons): LEFT/RIGHT run, UP or ENTER
//  jump (hold for height), DOWN pause. Paused: LEFT/RIGHT pick, ENTER picks.
//  The high score is kept in NVS.
// ─────────────────────────────────────────────────────────────
#define GAME_FRAME_MS 30                  // ~33 fps target; physics uses real dt
#define GT        16                      // tile size, px
#define G_ROWS    10                      // map rows (row 0 is kept clear for the HUD)
#define G_COLS_MAX 260
#define G_TOP     (TFT_H - G_ROWS * GT)   // 12: map drawn below a strip of sky
#define G_EN_MAX  32

//  Tiles
enum : uint8_t { T_AIR = 0, T_GROUND, T_BRICK, T_QBLOCK, T_USED, T_COIN, T_GOAL };

static uint8_t  gMap[G_ROWS][G_COLS_MAX];
static int      gCols = 0;
struct GEnemy { float x, y, vx; bool alive; uint16_t squash; };
static GEnemy   gEn[G_EN_MAX];
static int      gEnN = 0;

enum GState : uint8_t { GS_TITLE, GS_PLAY, GS_DYING, GS_CLEAR, GS_OVER, GS_PAUSE };
static GState   gState = GS_TITLE;
static float    gPx, gPy, gVx, gVy;       // player, top-left, px and px/s
static bool     gGround = false, gFaceL = false, gJumpHeld = false;
static float    gCam = 0;
static int      gLevel = 1, gLives = 3, gCoins = 0;
static uint32_t gScore = 0, gHi = 0, gStateMs = 0, gLastMs = 0;
static float    gTime = 300;              // seconds left
static uint8_t  gPauseSel = 0;
static uint32_t gRng = 1;
static float    gBumpT = 0; static int gBumpC = -1, gBumpR = -1;   // block bounce anim

#define PW 12                              // player box
#define PH 15
static const float G_GRAV = 1000, G_JUMPV = -345, G_RUNMAX = 115, G_ACC = 650, G_DEC = 900;

static uint32_t gRand() { gRng ^= gRng << 13; gRng ^= gRng >> 17; gRng ^= gRng << 5; return gRng; }
static int      gRandN(int n) { return (int)(gRand() % (uint32_t)n); }

static bool gSolid(int c, int r) {
  if (c < 0 || c >= gCols) return true;            // level ends are walls
  if (r < 0) return false;
  if (r >= G_ROWS) return false;                   // below the map = pit
  uint8_t t = gMap[r][c];
  return t == T_GROUND || t == T_BRICK || t == T_QBLOCK || t == T_USED;
}

static void gAddEnemy(int c, int r) {
  if (gEnN >= G_EN_MAX) return;
  gEn[gEnN++] = { (float)(c * GT + 2), (float)(r * GT + 4), -30.0f, true, 0 };
}

//  Build level `lv` from segments. Ground is rows 8..9; the player starts on
//  a flat run and the goal beacon stands on a flat run at the end.
static void gBuildLevel(int lv) {
  memset(gMap, 0, sizeof(gMap));
  gEnN = 0;
  gRng = 0x9E3779B9u ^ (uint32_t)lv * 2654435761u;
  gCols = 120 + lv * 20; if (gCols > G_COLS_MAX) gCols = G_COLS_MAX;
  auto ground = [&](int c0, int c1) { for (int c = c0; c < c1 && c < gCols; c++) { gMap[8][c] = T_GROUND; gMap[9][c] = T_GROUND; } };

  ground(0, 14);                                   // safe start
  int c = 14;
  const int endStart = gCols - 14;
  while (c < endStart) {
    int kind = gRandN(7), len;
    switch (kind) {
      case 0:                                      // flat run with coins
        len = 6 + gRandN(6); ground(c, c + len);
        for (int i = 1; i < len - 1; i += 2) gMap[6][c + i] = T_COIN;
        break;
      case 1: {                                    // pit, wider later (max 4: clearable)
        int gap = 2 + gRandN(lv > 2 ? 3 : 2);
        len = gap + 4; ground(c + gap, c + len);
        break;
      }
      case 2:                                      // block row: bricks and ? blocks
        len = 8; ground(c, c + len);
        for (int i = 2; i < 6; i++) gMap[5][c + i] = (i % 2) ? T_QBLOCK : T_BRICK;
        if (gRandN(2)) gAddEnemy(c + 6, 7);
        break;
      case 3: {                                    // stairs up and down
        int h = 2 + gRandN(2);
        len = h * 2 + 4; ground(c, c + len);
        for (int s = 0; s < h; s++)
          for (int y = 0; y <= s; y++) { gMap[7 - y][c + 1 + s] = T_BRICK; gMap[7 - y][c + len - 2 - s] = T_BRICK; }
        break;
      }
      case 4:                                      // floating platforms over a pit
        len = 10; ground(c, c + 2); ground(c + 8, c + len);
        for (int i = 3; i < 7; i++) { gMap[6][c + i] = T_BRICK; }
        gMap[4][c + 4] = T_COIN; gMap[4][c + 5] = T_COIN;
        break;
      default:                                     // droid patrol
        len = 9 + gRandN(4); ground(c, c + len);
        gAddEnemy(c + len / 2, 7);
        if (lv > 1 && gRandN(2)) gAddEnemy(c + len - 2, 7);
        break;
    }
    c += len;
  }
  ground(endStart, gCols);
  gMap[7][gCols - 6] = T_GOAL;                     // beacon base; drawn tall
}

static void gRespawn() {
  gPx = 2 * GT; gPy = 6 * GT; gVx = gVy = 0; gGround = false; gCam = 0;
  gTime = 300;
}

static void gNewGame() {
  gLevel = 1; gLives = 3; gCoins = 0; gScore = 0;
  gBuildLevel(gLevel); gRespawn();
  gJumpHeld = true;                                // the ENTER that started it is not a jump
  gState = GS_PLAY; gStateMs = millis();
}

void gameEnter() {
  prefs.begin("servoctl", true); gHi = prefs.getUInt("gamehi", 0); prefs.end();
  gState = GS_TITLE; gStateMs = millis(); gLastMs = 0;
}

static void gSaveHi() {
  if (gScore <= gHi) return;
  gHi = gScore;
  prefs.begin("servoctl", false); prefs.putUInt("gamehi", gHi); prefs.end();
}

static void gKill() {
  if (gState != GS_PLAY) return;
  gState = GS_DYING; gStateMs = millis(); gVy = -300; gVx = 0;
}

//  Player vs tiles, one axis at a time.
static void gMoveX(float dx) {
  gPx += dx;
  int r0 = (int)floorf(gPy / GT), r1 = (int)floorf((gPy + PH - 1) / GT);
  if (dx > 0) {
    int c = (int)floorf((gPx + PW - 1) / GT);
    for (int r = r0; r <= r1; r++) if (gSolid(c, r)) { gPx = c * GT - PW; gVx = 0; break; }
  } else if (dx < 0) {
    int c = (int)floorf(gPx / GT);
    for (int r = r0; r <= r1; r++) if (gSolid(c, r)) { gPx = (c + 1) * GT; gVx = 0; break; }
  }
}
static void gMoveY(float dy) {
  gPy += dy;
  int c0 = (int)floorf(gPx / GT), c1 = (int)floorf((gPx + PW - 1) / GT);
  if (dy > 0) {
    int r = (int)floorf((gPy + PH - 1) / GT);
    for (int c = c0; c <= c1; c++) if (gSolid(c, r)) { gPy = r * GT - PH; gVy = 0; break; }
  } else if (dy < 0) {
    int r = (int)floorf(gPy / GT);
    //  Head bump: the column under the player's centre takes the hit.
    int cc = (int)floorf((gPx + PW / 2) / GT);
    for (int c = c0; c <= c1; c++) if (gSolid(c, r)) {
      gPy = (r + 1) * GT; gVy = 0;
      int hc = gSolid(cc, r) ? cc : c;
      if (r >= 0 && gMap[r][hc] == T_QBLOCK) {
        gMap[r][hc] = T_USED; gCoins++; gScore += 100;
        gBumpC = hc; gBumpR = r; gBumpT = 0.18f;
        if (gCoins >= 50) { gCoins -= 50; gLives++; }
      } else if (r >= 0 && gMap[r][hc] == T_BRICK) {
        gBumpC = hc; gBumpR = r; gBumpT = 0.12f;
      }
      break;
    }
  }
  //  Standing = not rising, with solid ground in the pixel row just under the
  //  feet. Deciding it from "did this step sink into the floor" flickered:
  //  a sub-pixel step often doesn't, so half the jump presses were refused.
  gGround = false;
  if (gVy >= 0) {
    int rf = (int)floorf((gPy + PH) / GT);
    for (int c = c0; c <= c1; c++) if (gSolid(c, rf)) { gGround = true; break; }
  }
}

static void gUpdate(float dt) {
  const uint8_t s = pcfStable;
  auto held = [&](int bit) { return !(s & (1 << bit)); };
  bool L = held(PCF_LEFT), R = held(PCF_RIGHT), J = held(PCF_UP) || held(PCF_ENTER);
  if (L || R || J) uiNoteActivity();              // don't dim the panel mid-game

  if (gBumpT > 0) gBumpT -= dt;

  if (gState == GS_DYING) {                         // hop up, fall off screen
    gVy += G_GRAV * dt; gPy += gVy * dt;
    if (millis() - gStateMs > 1600) {
      if (--gLives <= 0) { gSaveHi(); gState = GS_OVER; gStateMs = millis(); }
      else { gRespawn(); gState = GS_PLAY; }
    }
    return;
  }
  if (gState == GS_CLEAR) {
    if (millis() - gStateMs > 2200) {
      gLevel++; gBuildLevel(gLevel); gRespawn(); gState = GS_PLAY;
    }
    return;
  }
  if (gState != GS_PLAY) return;

  //  Run: accelerate toward the held direction, brake otherwise.
  float target = R ? G_RUNMAX : L ? -G_RUNMAX : 0;
  if (target > gVx)      gVx = fminf(target, gVx + (target != 0 ? G_ACC : G_DEC) * dt);
  else if (target < gVx) gVx = fmaxf(target, gVx - (target != 0 ? G_ACC : G_DEC) * dt);
  if (L) gFaceL = true; else if (R) gFaceL = false;

  //  Jump on press (not on hold), variable height: lighter gravity while
  //  rising with the button still held.
  if (J && !gJumpHeld && gGround) { gVy = G_JUMPV; gGround = false; }
  gJumpHeld = J;
  float grav = (gVy < 0 && J) ? G_GRAV * 0.55f : G_GRAV;
  gVy = fminf(gVy + grav * dt, 520);

  const float prevBottom = gPy + PH;               // for the stomp test below
  gMoveX(gVx * dt);
  gMoveY(gVy * dt);

  //  Coins and the goal beacon.
  int c0 = (int)(gPx / GT), c1 = (int)((gPx + PW - 1) / GT);
  int r0 = (int)(gPy / GT), r1 = (int)((gPy + PH - 1) / GT);
  for (int r = r0; r <= r1; r++) for (int c = c0; c <= c1; c++) {
    if (r < 0 || r >= G_ROWS || c < 0 || c >= gCols) continue;
    if (gMap[r][c] == T_COIN) { gMap[r][c] = T_AIR; gCoins++; gScore += 10;
                                if (gCoins >= 50) { gCoins -= 50; gLives++; } }
  }
  if (gPx + PW >= (gCols - 6) * GT) {
    gScore += (uint32_t)gTime * 10;                 // time bonus
    gSaveHi(); gState = GS_CLEAR; gStateMs = millis(); gVx = 0;
    return;
  }

  //  Droids: walk, turn at walls and ledges; stomp from above, else it's you.
  for (int i = 0; i < gEnN; i++) {
    GEnemy& e = gEn[i];
    if (!e.alive) { if (e.squash) e.squash--; continue; }
    if (fabsf(e.x - gPx) > 360) continue;           // asleep until near
    e.x += e.vx * dt;
    int ec = (int)((e.vx < 0 ? e.x : e.x + 11) / GT), er = (int)((e.y + 6) / GT);
    int below = (int)((e.y + 13) / GT);
    if (gSolid(ec, er) || !gSolid(ec, below)) { e.vx = -e.vx; e.x += e.vx * dt * 2; }
    bool hitX = gPx < e.x + 12 && gPx + PW > e.x;
    bool hitY = gPy < e.y + 12 && gPy + PH > e.y;
    if (hitX && hitY) {
      //  A stomp is "was above its top last step, and not rising now" —
      //  judged by where the feet WERE, so a fast fall that crosses the
      //  whole top in one step still counts instead of reading as a hit.
      if (gVy >= 0 && prevBottom <= e.y + 4) {      // landed on top
        e.alive = false; e.squash = 12; gVy = J ? G_JUMPV * 0.9f : -230;
        gScore += 200;
      } else gKill();
    }
  }

  gTime -= dt;
  if (gTime <= 0) { gTime = 0; gKill(); }
  if (gPy > G_ROWS * GT + 8) gKill();               // fell into a pit

  //  Camera: keep the robot at ~40% across, clamped to the level.
  float want = gPx - TFT_W * 0.4f;
  gCam += (want - gCam) * fminf(1.0f, dt * 8);
  if (gCam < 0) gCam = 0;
  float maxCam = gCols * GT - TFT_W; if (gCam > maxCam) gCam = maxCam;
}

// ── Drawing ──
static void gDrawRobot(int x, int y, bool faceL, bool dead) {
  //  A small neon droid: cyan shell, dark visor with a red eye, legs that
  //  alternate while running.
  const uint16_t shell = dead ? CYBER_DIMTXT : NEON_CYAN;
  inst->fillRoundRect(x, y + 1, PW, 10, 3, shell);
  inst->fillRect(x + 2, y + 4, PW - 4, 4, BLACK);                 // visor
  inst->fillRect(faceL ? x + 3 : x + PW - 6, y + 5, 3, 2, NEON_MAGENTA);   // eye
  inst->drawFastVLine(x + PW / 2, y - 2, 3, shell);               // antenna
  inst->drawPixel(x + PW / 2, y - 3, NEON_MAGENTA);
  bool step = gGround && fabsf(gVx) > 20 && ((millis() / 110) % 2);
  if (!gGround && !dead) {                                        // jump pose
    inst->fillRect(x + 1, y + 11, 3, 3, shell); inst->fillRect(x + PW - 4, y + 11, 3, 3, shell);
  } else {
    inst->fillRect(x + 2, y + 11, 3, step ? 4 : 3, shell);
    inst->fillRect(x + PW - 5, y + 11, 3, step ? 3 : 4, shell);
  }
}

static void gDrawEnemy(int i, int x) {            // index: see seqAngleAt on prototypes
  const GEnemy& e = gEn[i];
  int y = G_TOP + (int)e.y;
  if (!e.alive) { inst->fillRect(x, y + 9, 12, 3, NEON_MAGENTA); return; }
  inst->fillRoundRect(x, y, 12, 12, 4, NEON_MAGENTA);             // red patrol droid
  bool blink = (millis() / 400) % 6 == 0;
  inst->fillRect(x + 2, y + 4, 3, blink ? 1 : 3, WHITE);
  inst->fillRect(x + 7, y + 4, 3, blink ? 1 : 3, WHITE);
  int f = (millis() / 150) % 2;
  inst->drawFastHLine(x + 1 + f, y + 12, 3, NEON_PINK);
  inst->drawFastHLine(x + 8 - f, y + 12, 3, NEON_PINK);
}

static void gDrawTile(uint8_t t, int x, int y, int c, int r) {
  switch (t) {
    case T_GROUND: {
      inst->fillRect(x, y, GT, GT, 0x0105);                       // deep teal
      if (r == 0 || !gSolid(c, r - 1))                            // lit top edge
        { inst->drawFastHLine(x, y, GT, NEON_CYAN); inst->drawFastHLine(x, y + 1, GT, 0x03CF); }
      else inst->drawPixel(x + ((c * 7 + r * 3) % 13) + 1, y + 7, 0x0249);
      break;
    }
    case T_BRICK:
      inst->fillRect(x, y, GT, GT, 0x3004);                       // dark red brick
      inst->drawRect(x, y, GT, GT, NEON_MAGENTA);
      inst->drawFastHLine(x, y + 7, GT, 0x8008);
      inst->drawFastVLine(x + 7, y, 7, 0x8008); inst->drawFastVLine(x + 3, y + 8, 7, 0x8008);
      break;
    case T_QBLOCK: {
      bool glow = (millis() / 300) % 2;
      inst->fillRect(x, y, GT, GT, glow ? NEON_YELLOW : 0xDD40);
      inst->drawRect(x, y, GT, GT, 0x8400);
      inst->setTextSize(2); inst->setTextColor(0x4200);
      inst->setCursor(x + 2, y + 1); inst->print("?");
      break;
    }
    case T_USED:
      inst->fillRect(x, y, GT, GT, 0x3186);
      inst->drawRect(x, y, GT, GT, CYBER_DIMTXT);
      break;
    case T_COIN: {                                                // spinning coin
      int w = 2 + abs(((int)(millis() / 90) % 8) - 4);
      inst->fillRoundRect(x + 8 - w, y + 3, w * 2, 10, 2, NEON_YELLOW);
      break;
    }
    case T_GOAL: {                                                // goal beacon
      int top = G_TOP + 1 * GT;
      inst->drawFastVLine(x + 7, top, y + GT - top, NEON_CYAN);
      inst->drawFastVLine(x + 8, top, y + GT - top, NEON_CYAN);
      int wave = (millis() / 120) % 3;
      inst->fillTriangle(x + 9, top + 2, x + 9, top + 14, x + 22 - wave, top + 8, NEON_MAGENTA);
      inst->fillCircle(x + 8, top, 3, (millis() / 250) % 2 ? NEON_YELLOW : WHITE);
      break;
    }
    default: break;
  }
}

static void gDrawSkyline() {
  //  Two parallax layers of buildings with lit windows; deterministic, so
  //  they scroll without being stored.
  for (int layer = 0; layer < 2; layer++) {
    float k = layer ? 0.5f : 0.25f;
    uint16_t col = layer ? 0x0106 : 0x0083;
    int off = (int)(gCam * k);
    int w = layer ? 34 : 26;
    for (int b = off / w - 1; b <= (off + TFT_W) / w + 1; b++) {
      uint32_t h = (uint32_t)(b * 2654435761u + layer * 97);
      int bh = (layer ? 50 : 70) + (int)(h % (layer ? 45 : 40));
      int bx = b * w - off, by = G_TOP + G_ROWS * GT - 2 * GT - bh;
      inst->fillRect(bx, by, w - 4, bh + 2 * GT, col);
      for (int wy = by + 5; wy < by + bh; wy += 9)
        for (int wx = bx + 3; wx < bx + w - 7; wx += 6)
          if (((wx * 13 + wy * 7 + b) % 5) == 0)
            inst->fillRect(wx, wy, 2, 3, layer ? ((wx + wy) % 3 ? 0x0451 : 0x8124) : 0x0229);
    }
  }
}

static void gCentre(const char* s, int y, int size, uint16_t col) {
  inst->setTextSize(size); inst->setTextColor(col);
  inst->setCursor((TFT_W - (int)strlen(s) * 6 * size) / 2, y); inst->print(s);
}

void uiViewGame() {
  uint32_t now = millis();
  float dt = gLastMs ? (now - gLastMs) / 1000.0f : 0;
  gLastMs = now;
  if (dt > 0.05f) dt = 0.05f;                     // a stall must not tunnel through floors
  //  Two half-steps: the fastest fall (~520 px/s) then moves < 16 px per step.
  gUpdate(dt * 0.5f); gUpdate(dt * 0.5f);

  inst->fillScreen(CYBER_BG);
  if (gState == GS_TITLE) {
    gCam = (now / 25) % 2000;                       // skyline drifts behind the title
    gDrawSkyline();
    gCentre("NEON RUNNER", 34, 3, NEON_CYAN);
    gCentre("NEON RUNNER", 33, 3, NEON_CYAN);
    gCentre("run  jump  stomp  collect", 72, 1, CYBER_DIMTXT);
    char hi[24]; snprintf(hi, sizeof(hi), "HI %06lu", (unsigned long)gHi);
    gCentre(hi, 92, 2, NEON_YELLOW);
    if ((now / 500) % 2) gCentre("PRESS ENTER", 124, 2, NEON_MAGENTA);
    gCentre("L/R run  UP/ENTER jump  DOWN pause", 156, 1, CYBER_DIMTXT);
    uiFrame(CYBER_GRID); uiBlit();
    return;
  }

  gDrawSkyline();
  const int cam = (int)gCam;
  int cFirst = cam / GT, cLast = (cam + TFT_W) / GT + 1;
  for (int r = 0; r < G_ROWS; r++)
    for (int c = cFirst; c <= cLast && c < gCols; c++) {
      uint8_t t = gMap[r][c];
      if (t == T_AIR) continue;
      int yo = (c == gBumpC && r == gBumpR && gBumpT > 0) ? -4 : 0;   // bumped block pops
      gDrawTile(t, c * GT - cam, G_TOP + r * GT + yo, c, r);
    }
  for (int i = 0; i < gEnN; i++) {
    int x = (int)gEn[i].x - cam;
    if (x < -16 || x > TFT_W) continue;
    if (!gEn[i].alive && !gEn[i].squash) continue;
    gDrawEnemy(i, x);
  }
  if (gState != GS_OVER)
    gDrawRobot((int)gPx - cam, G_TOP + (int)gPy, gFaceL, gState == GS_DYING);

  //  HUD over the clear top row: score, coins, lives, time, level.
  char hud[48];
  snprintf(hud, sizeof(hud), "%06lu  C%02d  x%d  T%03d  L%d", (unsigned long)gScore, gCoins,
           gLives, (int)ceilf(gTime), gLevel);
  inst->setTextSize(2);
  inst->setTextColor(BLACK);   inst->setCursor(9, 4); inst->print(hud);
  inst->setTextColor(WHITE);   inst->setCursor(8, 3); inst->print(hud);

  if (gState == GS_CLEAR)  { gCentre("LEVEL CLEAR", 60, 3, NEON_YELLOW);
                             char b[24]; snprintf(b, sizeof(b), "TIME BONUS %d", (int)gTime * 10);
                             gCentre(b, 96, 2, NEON_CYAN); }
  if (gState == GS_OVER)   { gCentre("GAME OVER", 56, 3, NEON_MAGENTA);
                             char b[32]; snprintf(b, sizeof(b), "SCORE %06lu  HI %06lu",
                                                  (unsigned long)gScore, (unsigned long)gHi);
                             gCentre(b, 92, 1, WHITE);
                             if ((now / 500) % 2) gCentre("ENTER: PLAY AGAIN", 116, 2, NEON_CYAN); }
  if (gState == GS_PAUSE)  { inst->fillRect(60, 44, 200, 84, CYBER_BG);
                             inst->drawRect(60, 44, 200, 84, NEON_CYAN);
                             gCentre("PAUSED", 54, 2, NEON_CYAN);
                             uiButton(74, 88, 82, 26, "RESUME", gPauseSel == 0, NEON_CYAN);
                             uiButton(164, 88, 82, 26, "QUIT", gPauseSel == 1, NEON_MAGENTA); }
  uiFrame(CYBER_GRID);
  uiBlit();
}

//  Button EVENTS (movement reads the held state in gUpdate instead).
static void gameAction(UiAction a) {
  switch (gState) {
    case GS_TITLE:
      if (a == ACT_SELECT) gNewGame();
      else if (a == ACT_BACK) { uiSel = UI_GAME - 1; uiEnter(UI_MENU); }
      break;
    case GS_OVER:
      if (a == ACT_SELECT) gNewGame();
      else if (a == ACT_BACK) { gState = GS_TITLE; }
      break;
    case GS_PLAY:
      if (a == ACT_NEXT) { gState = GS_PAUSE; gPauseSel = 0; }       // DOWN pauses
      break;
    case GS_PAUSE:
      if (a == ACT_BACK || a == ACT_RIGHT) gPauseSel ^= 1;
      else if (a == ACT_NEXT) { gState = GS_PLAY; gLastMs = 0; }      // DOWN again resumes
      else if (a == ACT_SELECT) {
        if (gPauseSel == 0) { gState = GS_PLAY; gLastMs = 0; }
        else { gSaveHi(); gState = GS_TITLE; }
      }
      break;
    default: break;
  }
}

// ─────────────────────────────────────────────────────────
//  FISH TANK — pocket-tank by MediaCutlet
//  (github.com/mediacutlet/pocket-tank, MIT: src/pockettank/LICENSE.txt).
//
//  The simulation, renderer and progression are the upstream C sources,
//  untouched except for the tank size: 320x172, the panel itself, so every
//  fish and plant is drawn at its full upstream pixel size (upstream is
//  448x368). The fish think with the rule-based advisor only — no language
//  model.
//
//  The original is a touch screen; here a fingertip cursor stands in:
//    ambient   ENTER / DOWN = show the fingertip, RIGHT = feed,
//              UP = tank light on/off, LEFT = back to the menu
//    fingertip arrows move it; ENTER tap = tap the glass (at the surface it
//              feeds; two quick taps then a pause switch the light), ENTER
//              held = rest a finger (fish come to look), held while moving
//              = wipe algae / trim the plants. It hides after a few idle
//              seconds.
//  The IMU: moving the board counts as handling the tank; tilting it makes
//  pellets slide and fish drift downhill while bubbles lean uphill; a sharp
//  shake startles the fish (and costs a little trust). "tank axis" on the
//  console says which IMU axis runs along the panel.
//  The tank lives only while this view is open; time spent elsewhere is
//  lived through as a doze on the way back in (progression_slept).
// ─────────────────────────────────────────────────────────
#define TANK_FRAME_MS   40
#define PT_HAND_IDLE_MS 6000
#define PT_TAP_MS       300          // ENTER released sooner than this = a tap

static tank_t      ptTank;
static bool        ptReady = false, ptFailed = false;
static uint16_t*   ptFb = nullptr;
static uint32_t    ptLastMs = 0, ptLeftMs = 0, ptEnterMs = 0;
static bool        ptHand = false, ptLatch = false, ptPrevE = false, ptTouchDown = false;
static uint32_t    ptHandMs = 0, ptDownMs = 0;
static float       ptCx = TFT_W / 2, ptCy = TFT_H / 2, ptMoveT = 0;
static Preferences ptPrefs;          // own object: progression saves mid-frame
static bool        ptNtpAsked = false;
static uint32_t    ptFrames = 0, ptUsTick = 0, ptUsRender = 0, ptUsScale = 0, ptUsBlit = 0;
//  IMU: the low-passed gravity and the current sideways tilt (-1 left side
//  down .. +1 right side down), along the shared screen axis (imuScrX).
static float       ptG[3] = { 0, 0, 0 }, ptTilt = 0;
static bool        ptGValid = false;
static uint32_t    ptShakeMs = 0;

//  Platform hooks the upstream code calls (progression.h). The save's layout
//  depends on the tank size (the algae grid rides in it), so the key names
//  the size: a save from another size is ignored, never misread.
#define PT_SAVE_KEY "s" PT_STR(TANK_W) "x" PT_STR(TANK_H) "f" PT_STR(N_FISH_MAX)
#define PT_STR2(x) #x
#define PT_STR(x) PT_STR2(x)
extern "C" bool persist_port_load(void* buf, size_t max, size_t* got) {
  if (!ptPrefs.begin("ptank", true)) return false;
  size_t n = ptPrefs.getBytesLength(PT_SAVE_KEY);
  bool ok = n > 0 && ptPrefs.getBytes(PT_SAVE_KEY, buf, n < max ? n : max) > 0;
  ptPrefs.end();
  if (ok) *got = n < max ? n : max;
  return ok;
}
extern "C" bool persist_port_save(const void* buf, size_t len) {
  if (!ptPrefs.begin("ptank", false)) return false;
  bool ok = ptPrefs.putBytes(PT_SAVE_KEY, buf, len) == len;
  ptPrefs.end();
  return ok;
}
extern "C" bool persist_port_erase(void) {
  if (!ptPrefs.begin("ptank", false)) return false;
  ptPrefs.clear(); ptPrefs.end();
  return true;
}
//  Wall clock from NTP once the controller has joined a network; 0 (unknown)
//  otherwise, which the tank handles by just restoring the save.
extern "C" int64_t clock_port_now_unix(void) {
  time_t t = time(nullptr);
  return t > 1700000000 ? (int64_t)t : 0;
}
extern "C" const char* version_port_string(void) { return "32sc"; }

//  Upstream starts with a pair that breeds up to the cap over hours of
//  tending; this port stocks a thin tank straight away with PT_STOCK fish of
//  mixed ages, each in its own colours. Breeding still fills the rest.
#define PT_STOCK 8
static void ptStock() {
  if (ptTank.n_fish >= 4) return;           // a tank already under way is left alone
  static const float kAge[PT_STOCK] = {     // seconds of life: adult .. fry
    STAGE_ADULT_AGE + 3600, STAGE_ADULT_AGE + 600, STAGE_JUV_AGE + 1200, STAGE_ADULT_AGE,
    STAGE_JUV_AGE + 300, 600, STAGE_JUV_AGE + 4000, 60 };
  while (ptTank.n_fish < PT_STOCK) {
    int s = tank_add_fish(&ptTank, 0, 1);
    if (s < 0) break;
    const fish_t& f = ptTank.fish[s];
    //  Its own roster look rather than the founding pair's family colours.
    tank_make_fish(&ptTank, s, f.preset, f.sociable, f.bold, STAGE_FRY);
  }
  for (int i = 0; i < ptTank.n_fish && i < PT_STOCK; i++) progression_set_age(&ptTank, i, kAge[i]);
  progression_save(&ptTank);
  Serial.printf("TANK: stocked with %d fish\n", ptTank.n_fish);
}

static bool ptEnsure() {
  if (ptReady) return true;
  if (ptFailed) return false;
  const size_t fbBytes = (size_t)TANK_W * TANK_H * 2;
  ptFb           = (uint16_t*)heap_caps_aligned_alloc(64, fbBytes, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
  uint16_t* scn  = (uint16_t*)heap_caps_aligned_alloc(64, fbBytes, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
  uint8_t*  vig  = (uint8_t*)ps_malloc((size_t)TANK_W * TANK_H);
  void*     dec  = ps_malloc(render_decor_scratch_size());
  uint32_t* drt  = (uint32_t*)heap_caps_malloc(RENDER_DIRTY_WORDS * 4, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  if (!drt) drt  = (uint32_t*)ps_malloc(RENDER_DIRTY_WORDS * 4);
  if (!ptFb || !dec) {
    Serial.println("TANK: no PSRAM for the framebuffer");
    ptFailed = true; return false;
  }
  //  The caches are optional (the renderer redraws everything without them).
  if (scn) render_set_scene_cache(scn);
  if (vig) render_set_vignette_cache(vig);
  if (drt) render_set_dirty_mask(drt);
  render_set_decor_scratch(dec);

  ptPrefs.begin("ptank", false);
  ptPrefs.remove("save");                  // older layouts' saves
  ptPrefs.remove("s320x172");
  ptPrefs.end();

  tank_init(&ptTank, esp_random());
  float h = progression_boot(&ptTank);
  //  The naming / colour pages need a touch screen: keep the roster names.
  if (progression_setup_pending()) progression_setup_done(&ptTank);
  ptStock();
  Serial.printf("TANK: %d fish, %s (%dx%d)\n", ptTank.n_fish,
                h < 0 ? "fresh or no clock" : "caught up", TANK_W, TANK_H);
  ptReady = true;
  return true;
}

void tankEnter() {
  //  One NTP request once there is a network, so the tank knows how long
  //  it was left across power cycles.
  if (!ptNtpAsked && WiFi.status() == WL_CONNECTED) {
    configTime(0, 0, "pool.ntp.org", "time.nist.gov"); ptNtpAsked = true;
  }
  if (ptEnsure() && ptLeftMs) {
    float away = (millis() - ptLeftMs) / 1000.0f;
    if (away > 30) progression_slept(&ptTank, away);
  }
  ptLeftMs = 0; ptLastMs = 0; ptEnterMs = millis();
  ptHand = false; ptLatch = false; ptTouchDown = false;
}

void tankLeave() {
  if (!ptReady) return;
  progression_save(&ptTank);
  ptLeftMs = millis();
}

//  The tank is the panel's size, so a frame is a straight copy. The renderer
//  keeps its own buffer (it only repaints what changed), and the overlays
//  drawn on the canvas afterwards must not leak into it.
static void ptPresent() {
  static_assert(TANK_W == TFT_W && TANK_H == TFT_H, "the tank is drawn 1:1");
  memcpy(inst->getBuffer(), ptFb, (size_t)TANK_W * TANK_H * 2);
}

//  The board's motion, from the BNO085's accelerometer (gravity included).
static void ptImu(float dt) {
  if (!imuAlive()) { ptTilt *= 0.9f; return; }
  const float a[3] = { imuAx, imuAy, imuAz };
  if (!ptGValid) { for (int i = 0; i < 3; i++) ptG[i] = a[i]; ptGValid = true; }
  //  How far this sample is from the slow gravity estimate = motion.
  float jx = a[0] - ptG[0], jy = a[1] - ptG[1], jz = a[2] - ptG[2];
  float jerk = sqrtf(jx * jx + jy * jy + jz * jz);
  float k = dt * 3.0f; if (k > 1) k = 1;
  for (int i = 0; i < 3; i++) ptG[i] += (a[i] - ptG[i]) * k;
  float gm = sqrtf(ptG[0] * ptG[0] + ptG[1] * ptG[1] + ptG[2] * ptG[2]);

  uint32_t now = millis();
  if (jerk > 1.5f) { tank_handled(&ptTank); uiNoteActivity(); }
  if (jerk > 9.0f && now - ptShakeMs > 1500) {             // a shake: scatter
    ptShakeMs = now;
    ptTank.startled = true;
    ptTank.startle_x = TANK_W / 2; ptTank.startle_y = TANK_H / 2;
    ptTank.startle_cooldown = 6.0f;               // tank.c STARTLE_COOLDOWN
    for (int i = 0; i < ptTank.n_fish; i++) {
      fish_t* f = &ptTank.fish[i];
      f->stress = fminf(10, f->stress + 2.5f);
      f->trust  = fmaxf(0, f->trust - 0.2f);
    }
  }
  if (gm < 4.0f) return;                                   // free fall / garbage
  imuScrLoad();
  float side = imuPick(imuScrX, ptG[0], ptG[1], ptG[2]) / gm;
  //  A few degrees of wobble in a hand is not a tilt.
  float t = fabsf(side) < 0.08f ? 0 : side - (side > 0 ? 0.08f : -0.08f);
  ptTilt = constrain(t * 1.6f, -1.0f, 1.0f);
}

//  Tilt, applied after the simulation's own step: pellets slide, fish are
//  nudged by the "current", bubbles lean the other way as they rise.
static void ptApplyTilt(float dt) {
  if (ptTilt == 0) return;
  for (int i = 0; i < MAX_FOOD; i++) {
    food_t* fd = &ptTank.food[i];
    if (fd->alive) fd->x = constrain(fd->x + ptTilt * 70.0f * dt, 4.0f, TANK_W - 4.0f);
  }
  for (int i = 0; i < ptTank.n_fish; i++) {
    fish_t* f = &ptTank.fish[i];
    f->x = constrain(f->x + ptTilt * 14.0f * dt, 12.0f, TANK_W - 12.0f);
  }
  for (int i = 0; i < MAX_BUBBLE; i++) {
    bubble_t* b = &ptTank.bubble[i];
    b->x = constrain(b->x - ptTilt * 40.0f * dt, 2.0f, TANK_W - 2.0f);
  }
}

//  The fingertip: held buttons, read every frame (the menu's press events
//  can't express "held" or "moving while held").
static void ptInput(float dt) {
  const uint8_t s = pcfStable;
  auto held = [&](int bit) { return !(s & (1 << bit)); };
  bool L = held(PCF_LEFT), R = held(PCF_RIGHT), U = held(PCF_UP),
       D = held(PCF_DOWN), E = held(PCF_ENTER);
  uint32_t now = millis();
  if (!ptHand) { ptPrevE = E; ptMoveT = 0; return; }

  bool mv = L || R || U || D;
  if (mv || E) { ptHandMs = now; uiNoteActivity(); tank_handled(&ptTank); }
  if (mv) {
    ptMoveT += dt;
    float v = ptMoveT > 0.45f ? 170.0f : 80.0f;          // px/s, faster once held
    ptCx += ((int)R - (int)L) * v * dt;
    ptCy += ((int)D - (int)U) * v * dt;
    ptCx = constrain(ptCx, 0.0f, (float)(TFT_W - 1));
    ptCy = constrain(ptCy, 0.0f, (float)(TFT_H - 1));
  } else ptMoveT = 0;

  float tx = ptCx * TANK_W / TFT_W, ty = ptCy * TANK_H / TFT_H;
  if (ptLatch) {                          // the ENTER that summoned the fingertip
    if (!E) ptLatch = false;
  } else if (E) {
    if (!ptPrevE) { ptDownMs = now; ptTouchDown = false; }
    if (ptTouchDown || now - ptDownMs >= PT_TAP_MS) {     // a finger on the glass
      ptTouchDown = true;
      tank_touch_hold(&ptTank, tx, ty);
      tank_touch_drag(&ptTank, tx, ty);
    }
  } else if (ptPrevE) {                   // released
    if (!ptTouchDown) tank_touch_tap(&ptTank, tx, ty);
    ptTouchDown = false;
  }
  ptPrevE = E;
  if (!E && now - ptHandMs > PT_HAND_IDLE_MS) ptHand = false;
}

//  Nearest fish under the fingertip, or -1.
static int ptFishAt(float tx, float ty) {
  int best = -1; float bd = 32.0f;
  for (int i = 0; i < ptTank.n_fish; i++) {
    float d = tank_dist(tx, ty, ptTank.fish[i].x, ptTank.fish[i].y);
    if (d < bd) { bd = d; best = i; }
  }
  return best;
}

static void ptText(const char* s, int x, int y, uint16_t col) {
  inst->setTextSize(1);
  inst->setTextColor(BLACK);  inst->setCursor(x + 1, y + 1); inst->print(s);
  inst->setTextColor(col);    inst->setCursor(x, y);         inst->print(s);
}

void uiViewTank() {
  if (!ptEnsure()) {
    inst->fillScreen(CYBER_BG);
    uiCentreText("NO PSRAM", 2, NEON_MAGENTA);
    uiFrame(CYBER_GRID); uiBlit();
    return;
  }
  uint32_t now = millis();
  float dt = ptLastMs ? (now - ptLastMs) / 1000.0f : TANK_FRAME_MS / 1000.0f;
  if (dt > 0.25f) dt = 0.25f;
  ptLastMs = now;

  uint32_t t0 = micros();
  ptInput(dt);
  ptImu(dt);
  tank_tick(&ptTank, dt, advisor_rules);
  ptApplyTilt(dt);
  progression_tick(&ptTank, dt);
  if (progression_newborn() >= 0) progression_newborn_done(&ptTank);   // no naming page
  uint32_t t1 = micros();
  render_tank(&ptTank, ptFb, TANK_W);
  render_sd_toast(&ptTank, ptFb, TANK_W);
  uint32_t t2 = micros();
  ptPresent();
  uint32_t t3 = micros();

  if (ptHand) {
    int cx = (int)ptCx, cy = (int)ptCy;
    int f = ptFishAt(ptCx * TANK_W / TFT_W, ptCy * TANK_H / TFT_H);
    if (f >= 0) {                         // who is that?
      static const char* const kStage[4] = { "FRY", "JUVENILE", "ADULT", "ELDER" };
      const fish_t& fi = ptTank.fish[f];
      char line[48];
      snprintf(line, sizeof line, "%s  %s", fi.name, kStage[fi.stage & 3]);
      ptText(line, 6, TFT_H - 22, NEON_CYAN);
      int hw = (int)(constrain(fi.hunger, 0.0f, 10.0f) * 6);
      ptText("HUNGER", 6, TFT_H - 11, NEON_PINK);
      inst->drawRect(46, TFT_H - 11, 62, 7, CYBER_DIMTXT);
      if (hw) inst->fillRect(47, TFT_H - 10, hw, 5, fi.hunger > 6 ? NEON_RED : NEON_YELLOW);
    }
    uint16_t c = ptTouchDown || (ptPrevE && !ptLatch) ? NEON_MAGENTA : NEON_CYAN;
    inst->drawCircle(cx, cy, 6, BLACK);
    inst->drawCircle(cx, cy, 5, c);
    if (ptTouchDown) inst->fillCircle(cx, cy, 3, c);
    else             inst->drawPixel(cx, cy, c);
    if (cy < (int)(FEED_ZONE_Y * TFT_H / TANK_H) + 2) ptText("FEED", cx + 8, cy + 2, NEON_YELLOW);
  } else if (now - ptEnterMs < 4000) {
    ptText("ENTER HAND  RIGHT FEED  UP LIGHT  LEFT EXIT", 31, TFT_H - 12, NEON_CYAN);
  }
  uiBlit();
  ptFrames++; ptUsTick += t1 - t0; ptUsRender += t2 - t1; ptUsScale += t3 - t2;
  ptUsBlit += micros() - t3;
}

static void ptToggleLight() {
  ptTank.light_auto = false;
  ptTank.light_manual_off = !ptTank.night;
  progression_settings_changed();
}

//  Console "tank [light|feed]": population and what a frame costs (averages
//  since the last report); "light" and "feed" do what UP and RIGHT do.
void tankConsole(const char* arg) {
  if (!ptReady) { Serial.println("tank: not started (open FISH TANK)"); return; }
  if (!strcmp(arg, "light")) { ptToggleLight(); Serial.printf("tank: light %s\n", ptTank.light_manual_off ? "off" : "on"); return; }
  if (!strcmp(arg, "feed"))  { tank_feed(&ptTank, TANK_W / 2, 4); Serial.println("tank: fed"); return; }
  if (!strncmp(arg, "axis", 4)) { imuAxesConsole(arg + 4); return; }   // old spelling
  Serial.printf("tank: %d fish, night %d, algae %.0f%%, sand dollars %d, clock %.0f s\n",
                ptTank.n_fish, (int)ptTank.night, tank_algae_cover(&ptTank) * 100,
                (int)ptTank.sd_balance, ptTank.clock);
  for (int i = 0; i < ptTank.n_fish; i++)
    Serial.printf("  %-10s stage %d hunger %.1f energy %.1f at %.0f,%.0f\n", ptTank.fish[i].name,
                  (int)ptTank.fish[i].stage, ptTank.fish[i].hunger, ptTank.fish[i].energy,
                  ptTank.fish[i].x, ptTank.fish[i].y);
  if (ptFrames)
    Serial.printf("  frame: tick %.2f ms, render %.2f ms, copy %.2f ms, blit %.2f ms (%lu frames)\n",
                  ptUsTick / 1e3f / ptFrames, ptUsRender / 1e3f / ptFrames,
                  ptUsScale / 1e3f / ptFrames, ptUsBlit / 1e3f / ptFrames, (unsigned long)ptFrames);
  ptFrames = ptUsTick = ptUsRender = ptUsScale = ptUsBlit = 0;
}

// ─────────────────────────────────────────────────────────
//  SAND — falling-sand physics driven by the BNO085.
//
//  Every grain is a particle with its own position and velocity (1/256 of a
//  cell), living on a 160x86 occupancy grid of 2x2 px cells. Each step the
//  board's acceleration, in screen axes and gravity included, is added to
//  every grain's velocity, so tilting pours the sand and moving or shaking
//  the board throws it about. A grain that runs into another tries to slide
//  along the free axis, then slips diagonally off the one below — that is
//  what builds slopes instead of towers.
//    UP / DOWN  more / less sand      RIGHT  next scene (box, hourglass, pegs)
//    ENTER      next colours          LEFT   back to the menu
// ─────────────────────────────────────────────────────────
#define SAND_GW      160
#define SAND_GH      86
#define SAND_CELL    2
#define SAND_MAX     5000
#define SAND_MIN     500
#define SAND_STEP    500
#define SAND_WALL    255             // a wall cell on the edge (drawn)
#define SAND_WALLIN  254             // a wall cell inside a wall (drawn dark)
#define SAND_ITERS   3               // physics steps per frame
#define SAND_ACC     2.4f            // m/s^2 -> 1/256 cell per step^2
#define SAND_ELASTIC 72              // bounce kept, /256
#define SAND_NCOL    6

static int32_t*  sdX = nullptr;      // 1/256 cell
static int32_t*  sdY = nullptr;
static int16_t*  sdVX = nullptr;
static int16_t*  sdVY = nullptr;
static uint8_t*  sdC = nullptr;      // grain colour index 1..SAND_NCOL
static uint8_t*  sdGrid = nullptr;   // 0 empty, 1..SAND_NCOL grain, SAND_WALL/WALLIN
static int       sdN = 0, sdTarget = 2500;
static uint8_t   sdScene = 0, sdPal = 0;
static uint32_t  sdMsgMs = 0, sdEnterMs = 0, sdShakeMs = 0;
static float     sdGx = 0, sdGy = 9.8f, sdLp[3] = { 0, 0, 0 };
static bool      sdLpValid = false;
static uint32_t  sdRng = 0x9E3779B9u;

static const char* const kSandScene[3] = { "BOX", "HOURGLASS", "PEGS" };
static const char* const kSandPal[3]   = { "DESERT", "NEON", "RAINBOW" };
static const uint16_t kSandCols[3][SAND_NCOL] = {
  { 0xE5CD, 0xD52B, 0xF6B0, 0xC4A9, 0xEE0E, 0xB447 },                   // sandstone strata
  { NEON_CYAN, NEON_MAGENTA, NEON_CYAN, NEON_PINK, 0x2D7F, NEON_RED },  // RealDriver neon
  { NEON_RED, NEON_ORANGE, NEON_YELLOW, NEON_GREEN, NEON_CYAN, 0x901F },
};

static inline uint32_t sdRand() {    // xorshift: rand() is far too slow per grain
  sdRng ^= sdRng << 13; sdRng ^= sdRng >> 17; sdRng ^= sdRng << 5; return sdRng;
}

static void sandFree() {
  free(sdX); free(sdY); free(sdVX); free(sdVY); free(sdC); free(sdGrid);
  sdX = sdY = nullptr; sdVX = sdVY = nullptr; sdC = sdGrid = nullptr; sdN = 0;
}

//  Internal RAM first (the grid is hit at random every step), PSRAM after.
static void* sdAlloc(size_t n) {
  void* p = heap_caps_malloc(n, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  return p ? p : ps_malloc(n);
}

static bool sandAlloc() {
  if (sdGrid) return true;
  sdX = (int32_t*)sdAlloc(SAND_MAX * 4);  sdY = (int32_t*)sdAlloc(SAND_MAX * 4);
  sdVX = (int16_t*)sdAlloc(SAND_MAX * 2); sdVY = (int16_t*)sdAlloc(SAND_MAX * 2);
  sdC = (uint8_t*)sdAlloc(SAND_MAX);      sdGrid = (uint8_t*)sdAlloc(SAND_GW * SAND_GH);
  if (!sdX || !sdY || !sdVX || !sdVY || !sdC || !sdGrid) { sandFree(); return false; }
  return true;
}

//  Walls for the current scene, then the sand poured in from the top.
static void sandBuild() {
  memset(sdGrid, 0, SAND_GW * SAND_GH);
  const int cy = SAND_GH / 2;
  if (sdScene == 1) {                          // hourglass: two bulbs, a 4-cell neck
    for (int y = 0; y < SAND_GH; y++) {
      int half = 2 + abs(y - cy) * 3 / 2 + (abs(y - cy) > 30 ? (abs(y - cy) - 30) * 2 : 0);
      if (half > SAND_GW / 2) half = SAND_GW / 2;
      for (int x = 0; x < SAND_GW; x++)
        if (abs(x - SAND_GW / 2) >= half) sdGrid[y * SAND_GW + x] = SAND_WALL;
    }
  } else if (sdScene == 2) {                   // Galton-style pegs, staggered rows
    for (int r = 0; r < 5; r++) {
      int py = 24 + r * 11, off = (r & 1) ? 8 : 0;
      for (int px = 8 + off; px < SAND_GW - 4; px += 16)
        for (int dy = -1; dy <= 1; dy++)
          for (int dx = -1; dx <= 1; dx++)
            if (abs(dx) + abs(dy) < 2) sdGrid[(py + dy) * SAND_GW + px + dx] = SAND_WALL;
    }
  }
  //  Walls with walls all round are interior: drawn dark, so a scene reads
  //  as outlines rather than slabs. Both kinds block grains the same.
  for (int y = 0; y < SAND_GH; y++)
    for (int x = 0; x < SAND_GW; x++) {
      if (sdGrid[y * SAND_GW + x] != SAND_WALL) continue;
      auto w = [&](int xx, int yy) {
        return xx < 0 || yy < 0 || xx >= SAND_GW || yy >= SAND_GH || sdGrid[yy * SAND_GW + xx] >= SAND_WALLIN;
      };
      if (w(x - 1, y) && w(x + 1, y) && w(x, y - 1) && w(x, y + 1)) sdGrid[y * SAND_GW + x] = SAND_WALLIN;
    }
  //  Fill free cells row by row from the top, in coloured bands, leaving
  //  alternate gaps so it arrives as a pour rather than a solid slab.
  sdN = 0;
  int band = 0, rowsInBand = 0;
  for (int y = 0; y < SAND_GH && sdN < sdTarget; y++) {
    if (++rowsInBand > 4) { rowsInBand = 1; band = (band + 1) % SAND_NCOL; }
    for (int x = 0; x < SAND_GW && sdN < sdTarget; x++) {
      uint8_t* g = &sdGrid[y * SAND_GW + x];
      if (*g || (sdScene != 1 && y > cy)) continue;   // box / pegs: top half only
      *g = (uint8_t)(band + 1);
      sdX[sdN] = x * 256 + 128; sdY[sdN] = y * 256 + 128;
      sdVX[sdN] = (int16_t)((int)(sdRand() % 61) - 30); sdVY[sdN] = 0;
      sdC[sdN] = (uint8_t)(band + 1);
      sdN++;
    }
  }
  //  The hourglass's top bulb may hold fewer than asked for.
  sdMsgMs = millis();
}

//  Acceleration in screen axes (x right, y down), m/s^2. The raw sample,
//  gravity and motion together — the motion is what lets a shake throw it.
static void sandAccel() {
  if (!imuAlive()) { sdGx = 0; sdGy = 9.8f; return; }
  imuScreenAccel(&sdGx, &sdGy);
  //  A hard jolt (far from the slow gravity estimate): kick every grain.
  const float a[3] = { imuAx, imuAy, imuAz };
  if (!sdLpValid) { for (int i = 0; i < 3; i++) sdLp[i] = a[i]; sdLpValid = true; }
  float j = 0;
  for (int i = 0; i < 3; i++) { float d = a[i] - sdLp[i]; j += d * d; sdLp[i] += d * 0.15f; }
  if (j > 12.0f * 12.0f && millis() - sdShakeMs > 250) {
    sdShakeMs = millis();
    for (int i = 0; i < sdN; i++) {
      sdVX[i] += (int16_t)((int)(sdRand() % 257) - 128);
      sdVY[i] += (int16_t)((int)(sdRand() % 257) - 128);
    }
  }
  if (j > 1.5f * 1.5f) uiNoteActivity();       // being handled: don't dim
}

static inline bool sdFree(int cx, int cy) {
  return cx >= 0 && cy >= 0 && cx < SAND_GW && cy < SAND_GH && !sdGrid[cy * SAND_GW + cx];
}

static void sandStep() {
  const int ax = (int)lroundf(sdGx * SAND_ACC), ay = (int)lroundf(sdGy * SAND_ACC);
  //  The downhill cell step, for the diagonal slip: whichever axis gravity
  //  pulls hardest along.
  const bool gyDom = abs(ay) >= abs(ax);
  const int gs = gyDom ? (ay >= 0 ? 1 : -1) : (ax >= 0 ? 1 : -1);
  const bool still = abs(ax) + abs(ay) < 4;     // flat on the table: no pull
  const int32_t XM = SAND_GW * 256 - 1, YM = SAND_GH * 256 - 1;
  //  Alternate the sweep direction so neither side of a pile is favoured.
  static bool rev = false; rev = !rev;
  for (int k = 0; k < sdN; k++) {
    const int i = rev ? sdN - 1 - k : k;
    int32_t vx = sdVX[i] + ax + (int)(sdRand() & 3) - 1;
    int32_t vy = sdVY[i] + ay + (int)(sdRand() & 3) - 1;
    //  At most one cell per step: nothing can tunnel through a neighbour.
    int32_t v2 = vx * vx + vy * vy;
    if (v2 > 256 * 256) { float s = 256.0f / sqrtf((float)v2); vx = (int32_t)(vx * s); vy = (int32_t)(vy * s); }
    int32_t x = sdX[i], y = sdY[i], nx = x + vx, ny = y + vy;
    if (nx < 0)  { nx = 0;  vx = -vx * SAND_ELASTIC / 256; }
    if (nx > XM) { nx = XM; vx = -vx * SAND_ELASTIC / 256; }
    if (ny < 0)  { ny = 0;  vy = -vy * SAND_ELASTIC / 256; }
    if (ny > YM) { ny = YM; vy = -vy * SAND_ELASTIC / 256; }
    const int ocx = x >> 8, ocy = y >> 8, ncx = nx >> 8, ncy = ny >> 8;
    const uint8_t col = sdC[i];
    if (ncx != ocx || ncy != ocy) {
      int tx = ocx, ty = ocy;
      if (sdFree(ncx, ncy)) { tx = ncx; ty = ncy; x = nx; y = ny; }
      else {
        const bool fx = ncx != ocx && sdFree(ncx, ocy), fy = ncy != ocy && sdFree(ocx, ncy);
        if (fx && (!fy || abs(vx) >= abs(vy))) {          // slide along x
          tx = ncx; x = nx; vy = -vy * SAND_ELASTIC / 256;
        } else if (fy) {                                  // slide along y
          ty = ncy; y = ny; vx = -vx * SAND_ELASTIC / 256;
        } else {
          //  Boxed in along its path: slip diagonally downhill if it can.
          bool moved = false;
          if (!still) {
            const int side = (sdRand() & 1) ? 1 : -1;
            for (int t2 = 0; t2 < 2 && !moved; t2++) {
              const int s = t2 ? -side : side;
              const int dx = gyDom ? s : gs, dy = gyDom ? gs : s;
              if (sdFree(ocx + dx, ocy + dy)) {
                tx = ocx + dx; ty = ocy + dy;
                x = tx * 256 + 128; y = ty * 256 + 128;
                if (gyDom) vx = s * 48; else vy = s * 48;
                moved = true;
              }
            }
          }
          if (!moved) { vx = -vx * SAND_ELASTIC / 256; vy = -vy * SAND_ELASTIC / 256; }
        }
      }
      if (tx != ocx || ty != ocy) {
        sdGrid[ocy * SAND_GW + ocx] = 0;
        sdGrid[ty * SAND_GW + tx] = col;
      }
    } else { x = nx; y = ny; }
    sdX[i] = x; sdY[i] = y;
    sdVX[i] = (int16_t)constrain(vx, -2000, 2000);
    sdVY[i] = (int16_t)constrain(vy, -2000, 2000);
  }
}

void sandEnter() {
  sdEnterMs = millis(); sdLpValid = false;
  imuScrLoad();
  if (!sandAlloc()) { Serial.println("SAND: out of memory"); return; }
  sdRng ^= esp_random();
  sandBuild();
}

void sandLeave() { sandFree(); }                  // ~75 KB back for the other views

void uiViewSand() {
  if (!sdGrid) {
    inst->fillScreen(CYBER_BG);
    uiCentreText("NO MEMORY", 2, NEON_MAGENTA);
    uiFrame(CYBER_GRID); uiBlit();
    return;
  }
  sandAccel();
  for (int s = 0; s < SAND_ITERS; s++) sandStep();

  //  Paint straight into the canvas: every cell is a 2x2 block.
  uint16_t* fb = inst->getBuffer();
  const uint16_t* pal = kSandCols[sdPal];
  const uint16_t bg = CYBER_BG, wall = CYBER_GRID, wallIn = 0x0063;
  for (int cy = 0; cy < SAND_GH; cy++) {
    uint16_t* r0 = fb + cy * SAND_CELL * TFT_W;
    uint16_t* r1 = r0 + TFT_W;
    const uint8_t* g = sdGrid + cy * SAND_GW;
    for (int cx = 0; cx < SAND_GW; cx++) {
      uint8_t v = g[cx];
      uint16_t c = !v ? bg : v == SAND_WALL ? wall : v == SAND_WALLIN ? wallIn : pal[(v - 1) % SAND_NCOL];
      r0[cx * 2] = c; r0[cx * 2 + 1] = c; r1[cx * 2] = c; r1[cx * 2 + 1] = c;
    }
  }

  //  Gravity arrow, bottom right: which way the sand thinks is down.
  {
    const int ox = TFT_W - 14, oy = TFT_H - 14;
    float m = sqrtf(sdGx * sdGx + sdGy * sdGy);
    inst->drawCircle(ox, oy, 10, CYBER_DIMTXT);
    if (m > 0.5f) {
      float l = fminf(m / 9.8f, 1.3f) * 9.0f;
      int ex = ox + (int)(sdGx / m * l), ey = oy + (int)(sdGy / m * l);
      inst->drawLine(ox, oy, ex, ey, NEON_CYAN);
      inst->fillCircle(ex, ey, 2, NEON_CYAN);
    } else inst->drawPixel(ox, oy, NEON_CYAN);
  }
  uint32_t now = millis();
  if (!imuAlive()) ptText("NO IMU - GRAVITY IS DOWN", (TFT_W - 24 * 6) / 2, 6, NEON_RED);
  if (now - sdMsgMs < 2500) {
    char line[48];
    snprintf(line, sizeof line, "%s  %d GRAINS  %s", kSandScene[sdScene], sdN, kSandPal[sdPal]);
    ptText(line, (TFT_W - (int)strlen(line) * 6) / 2, TFT_H - 12, NEON_CYAN);
  } else if (now - sdEnterMs < 5000) {
    ptText("UP/DN SAND  RIGHT SCENE  ENTER COLOUR", (TFT_W - 36 * 6) / 2, TFT_H - 12, NEON_CYAN);
  }
  uiBlit();
}

static void sandAction(UiAction a) {
  switch (a) {
    case ACT_BACK:   uiSel = UI_SAND - 1; uiEnter(UI_MENU); return;
    case ACT_PREV:   if (sdTarget < SAND_MAX) { sdTarget += SAND_STEP; if (sdGrid) sandBuild(); } break;
    case ACT_NEXT:   if (sdTarget > SAND_MIN) { sdTarget -= SAND_STEP; if (sdGrid) sandBuild(); } break;
    case ACT_RIGHT:  sdScene = (sdScene + 1) % 3; if (sdGrid) sandBuild(); break;
    case ACT_SELECT: sdPal = (sdPal + 1) % 3; sdMsgMs = millis(); break;
    default: break;
  }
  sdMsgMs = millis();
}

// ─────────────────────────────────────────────────────────
//  DOOM — launcher.
//
//  Doom itself is a separate firmware (FIRMWARE/32_Servo_Controller_DOOM:
//  PrBoom via Espressif's esp32-doom, GPL) living in the flash's second app
//  slot (app1, 0x310000). This page picks a WAD from the SD card, leaves its
//  path in NVS ("doom"/"wad"), points the bootloader at app1 and reboots.
//  Quitting Doom points it back here. Nothing of Doom is linked into this
//  firmware, so it costs no RAM here and the two programs stay separate.
//
//  The game data is the user's own WAD, in /DOOM or the card's root: the
//  shareware DOOM1.WAD or the free FREEDOOM1.WAD / FREEDOOM2.WAD.
// ─────────────────────────────────────────────────────────
#define DOOM_MAXWADS 8

static String   doomWads[DOOM_MAXWADS];
static int      doomWadCount = 0, doomSel = 0;
static bool     doomScanned = false, doomAppOk = false;
static String   doomLast;                    // how the last Doom run ended ("OK" or its error)

//  Is there a bootable image in app1 (the Doom firmware)?
static bool doomAppPresent() {
  const esp_partition_t* app1 =
      esp_partition_find_first(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_OTA_1, NULL);
  esp_app_desc_t d;
  return app1 && esp_ota_get_partition_description(app1, &d) == ESP_OK;
}

//  WADs on the card: *.wad in /DOOM, then in the root.
static void doomScan() {
  doomWadCount = 0; doomSel = 0; doomScanned = true;
  doomAppOk = doomAppPresent();
  prefs.begin("doom", true); doomLast = prefs.getString("last", ""); prefs.end();
  if (!sdMounted) return;
  const char* dirs[2] = { "/DOOM", "/" };
  for (int d = 0; d < 2 && doomWadCount < DOOM_MAXWADS; d++) {
    File dir = SD_MMC.open(dirs[d]);
    if (!dir || !dir.isDirectory()) continue;
    for (File e = dir.openNextFile(); e && doomWadCount < DOOM_MAXWADS; e = dir.openNextFile()) {
      if (e.isDirectory()) continue;
      String n = e.name();
      int slash = n.lastIndexOf('/'); if (slash >= 0) n = n.substring(slash + 1);
      String l = n; l.toLowerCase();
      if (!l.endsWith(".wad") || l.startsWith(".")) continue;
      doomWads[doomWadCount++] = String(d == 0 ? "/DOOM/" : "/") + n;
    }
  }
}

static void doomLines(const char* const* lines, int n, int y0) {
  inst->setTextSize(1);
  for (int i = 0; i < n; i++) {
    inst->setTextColor(i == 0 ? NEON_MAGENTA : NEON_CYAN);
    inst->setCursor(14, y0 + i * 13); inst->print(lines[i]);
  }
}

void uiViewDoom() {
  if (!doomScanned) doomScan();
  inst->fillScreen(CYBER_BG);
  ui3DHeader("DOOM");
  if (!doomAppOk) {
    static const char* const l[] = {
      "The Doom firmware is not installed.",
      "",
      "It is a separate program in the second app slot:",
      "build FIRMWARE/32_Servo_Controller_DOOM and write",
      "its .bin to 0x310000 (see the top of that sketch).",
      "",
      "LEFT: back",
    };
    doomLines(l, 7, 44);
  } else if (!doomWadCount) {
    static const char* const l[] = {
      "No WAD file on the SD card.",
      "",
      "Copy one into /DOOM on the card:",
      "  DOOM1.WAD      (the shareware episode)",
      "  FREEDOOM1.WAD  (free - freedoom.github.io)",
      "",
      "LEFT: back",
    };
    doomLines(l, 7, 44);
  } else {
    for (int i = 0; i < doomWadCount && i < 3; i++) {
      int y = 40 + i * 22;
      if (i == doomSel) ui3DSelect(8, y - 3, TFT_W - 16, 20);
      inst->setTextSize(2);
      inst->setTextColor(i == doomSel ? BLACK : NEON_CYAN);
      inst->setCursor(16, y);
      String n = doomWads[i]; int s = n.lastIndexOf('/'); if (s >= 0) n = n.substring(s + 1);
      inst->print(n.substring(0, 22));
    }
    inst->setTextSize(1);
    static const char* const help[] = {
      "UP/DN walk  LEFT/RIGHT turn  ENTER fire  TILT strafe",
      "UP+DN weapon  DOWN+RIGHT menu  BOOT map",
      "ENTER: play (reboots into Doom; Quit comes back)",
    };
    for (int i = 0; i < 3; i++) {
      inst->setTextColor(i == 2 ? NEON_MAGENTA : CYBER_DIMTXT);
      inst->setCursor(8, TFT_H - 44 + i * 12); inst->print(help[i]);
    }
    if (doomLast.length() && doomLast != "OK") {   // the last run failed: say why
      inst->setTextColor(NEON_RED);
      inst->setCursor(8, 108); inst->print(("LAST RUN: " + doomLast).substring(0, 52));
    }
  }
  uiFrame(CYBER_GRID); uiBlit();
}

static void doomLaunch() {
  if (!doomAppOk || doomSel >= doomWadCount) return;
  const esp_partition_t* app1 =
      esp_partition_find_first(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_OTA_1, NULL);
  prefs.begin("doom", false); prefs.putString("wad", doomWads[doomSel]); prefs.end();
  Serial.printf("DOOM: booting app1 with %s\n", doomWads[doomSel].c_str());
  if (!app1 || esp_ota_set_boot_partition(app1) != ESP_OK) {
    uiCentreText("DOOM FIRMWARE BAD", 2, NEON_RED); uiBlit(); delay(2000);
    return;
  }
#if SERVO_ENABLE
  seqStop();
#endif
  blSet(0);                          // a clean cut to black, then Doom
  ESP.restart();
}

//  Console "doom [n]": the WADs and how the last run ended; with n, launch WAD n.
void doomConsole(const char* arg) {
  doomScan();
  Serial.printf("doom: firmware in app1 %s, last run: %s\n", doomAppOk ? "present" : "MISSING",
                doomLast.length() ? doomLast.c_str() : "-");
  for (int i = 0; i < doomWadCount; i++) Serial.printf("  %d  %s\n", i, doomWads[i].c_str());
  if (*arg >= '0' && *arg <= '9') { doomSel = atoi(arg); doomLaunch(); }
}

//  Chosen from the menu: straight into the game with the last-played WAD
//  (or the first one found). Only when something needs saying - the Doom
//  firmware missing, no WAD on the card, or the last run ended in an error -
//  does the DOOM page stay up to explain (ENTER there still starts it).
static bool doomQuickStart() {
  doomScan();
  if (!doomAppOk || !doomWadCount) return false;
  if (doomLast.length() && doomLast != "OK") return false;
  prefs.begin("doom", true); String last = prefs.getString("wad", ""); prefs.end();
  doomSel = 0;
  for (int i = 0; i < doomWadCount; i++) if (doomWads[i] == last) doomSel = i;
  doomLaunch();                      // reboots; comes back only if the switch failed
  return false;
}

static void doomAction(UiAction a) {
  switch (a) {
    case ACT_BACK:   uiSel = UI_DOOM - 1; uiEnter(UI_MENU); break;
    case ACT_NEXT:   if (doomWadCount) doomSel = (doomSel + 1) % doomWadCount; break;
    case ACT_PREV:   if (doomWadCount) doomSel = (doomSel + doomWadCount - 1) % doomWadCount; break;
    case ACT_SELECT: case ACT_RIGHT: doomLaunch(); break;
    default: break;
  }
}

// ─────────────────────────────────────────────────────────
//  PLANE RADAR — live aircraft around a home point, as a radar scope.
//
//  The idea comes from MatixYo's ESP32-Plane-Radar (MIT, a round GC9A01
//  build); this is a fresh implementation for this board's 320x172 panel.
//  Aircraft come from the adsb.fi open data API (personal, non-commercial
//  use; credited on screen as its terms ask):
//      https://opendata.adsb.fi/api/v3/lat/<lat>/lon/<lon>/dist/<NM>
//  One request every 5 s (the API allows 1/s) on a task of its own, only
//  while this view is open. Each aircraft arrives with its distance (NM)
//  and bearing from the query point, so placing it needs no map maths;
//  between fetches it is moved along its track at its ground speed.
//
//  Home: the GPS when it has a fix, else the saved point ("radar home <lat>
//  <lon>" on the console), else — only if asked with ENTER on the "no home"
//  screen — an approximate point from the connection's public IP (ip-api.com).
//  Needs internet: the board must have joined a network (SETTINGS > WIFI).
//
//    UP / DOWN   select an aircraft        RIGHT  range 5/10/25/50/100 km
//    ENTER       north-up / heading-up     LEFT   back
// ─────────────────────────────────────────────────────────
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#define RD_MAX        48
#define RD_FETCH_MS   5000
#define RD_CX         86            // scope centre and radius
#define RD_CY         86
#define RD_R          84
#define RD_PANEL_X    176

static const uint16_t kRdRanges[] = { 5, 10, 25, 50, 100 };   // km, ring radius
#define RD_NRANGES (sizeof(kRdRanges) / sizeof(kRdRanges[0]))

//  The aircraft table (parallel arrays: the .ino prototype generator and
//  struct parameters don't mix). rd* is what the view draws; rs* is the
//  fetch task's staging copy, swapped in under radLock.
static char     radCall[RD_MAX][9], radType[RD_MAX][5], radReg[RD_MAX][9];
static float    radDst[RD_MAX], radDir[RD_MAX];    // km, degrees from home
static float    radGs[RD_MAX], radTrk[RD_MAX];     // knots, degrees (-1 = unknown)
static int32_t  radAlt[RD_MAX];                   // feet, INT32_MIN = on the ground
static int      radN = 0;
static char     rsCall[RD_MAX][9], rsType[RD_MAX][5], rsReg[RD_MAX][9];
static float    rsDst[RD_MAX], rsDir[RD_MAX], rsGs[RD_MAX], rsTrk[RD_MAX];
static int32_t  rsAlt[RD_MAX];
static int      rsN = 0;
static SemaphoreHandle_t radLock = nullptr;

static double   radLat = 0, radLon = 0;
static bool     radHome = false;
static char     radHomeSrc[12] = "";              // "GPS", "SAVED", "IP ~", "ZIP 12345"
//  The saved home (ZIP / typed / IP / "radar home gps"), kept apart from the
//  centre actually in use, which follows a live GPS fix when USE GPS is on.
static double   radSavedLat = 0, radSavedLon = 0;
static bool     radSavedHas = false;
static char     radSavedSrc[12] = "";
static bool     radUseGps = true;                // NVS "radar"/"usegps"
static uint8_t  radRange = 1;                     // index into kRdRanges
static bool     radHdgUp = false;
static int      radSel = 0;
static volatile bool     radRun = false, radTaskAlive = false, radLocateReq = false, radForce = false;
static volatile uint32_t radFetchedMs = 0;        // when the table was last swapped in
static volatile int      radHttp = 0;             // last HTTP status (or <0 client error)
static char     radMsg[40] = "";
//  The ZIP code page: ENTER on "NO HOME", or hold ENTER on the radar.
static bool     radZipMode = false;
static uint8_t  radZip[5] = { 0, 0, 0, 0, 0 }, radZipPos = 0;
static volatile bool radZipReq = false, radZipOk = false;
static uint32_t radToastMs = 0, radEAt = 0;
static bool     radPrevE = true, radEUsed = true;       // ENTER: tap vs hold

//  The scope's centre: a live GPS fix when USE GPS is on and there is one,
//  otherwise the saved home. Called every frame, so the centre follows the
//  GPS as the board moves and falls back the moment the fix is lost.
static void radApplyHome() {
  double la = 0, lo = 0; bool has = false; const char* src = "";
  if (radUseGps && gpsAlive()) { la = gpsLat; lo = gpsLon; has = true; src = "GPS"; }
  else if (radSavedHas)        { la = radSavedLat; lo = radSavedLon; has = true; src = radSavedSrc; }
  if (radLock) xSemaphoreTake(radLock, portMAX_DELAY);       // the fetch task reads these
  radLat = la; radLon = lo; radHome = has;
  snprintf(radHomeSrc, sizeof radHomeSrc, "%s", src);
  if (radLock) xSemaphoreGive(radLock);
}

static void radLoadHome() {
  prefs.begin("radar", true);
  radSavedHas = prefs.isKey("lat");
  radSavedLat = prefs.getDouble("lat", 0);
  radSavedLon = prefs.getDouble("lon", 0);
  String src = prefs.getString("src", "SAVED");
  radRange = prefs.getUChar("range", 1) % RD_NRANGES;
  radUseGps = prefs.getBool("usegps", true);
  prefs.end();
  snprintf(radSavedSrc, sizeof radSavedSrc, "%s", src.c_str());
  radApplyHome();
}

static void radSaveHome(double la, double lo, const char* src) {
  prefs.begin("radar", false);
  prefs.putDouble("lat", la); prefs.putDouble("lon", lo); prefs.putString("src", src);
  prefs.end();
  radSavedLat = la; radSavedLon = lo; radSavedHas = true;
  snprintf(radSavedSrc, sizeof radSavedSrc, "%s", src);
  radApplyHome();                                 // a live GPS fix still wins, if in use
}

static void radSetUseGps(bool on) {
  radUseGps = on;
  prefs.begin("radar", false); prefs.putBool("usegps", on); prefs.end();
  radApplyHome();
}

//  One line on the GPS, for the SET HOME page.
static const char* radGpsStatus() {
  static char b[40];
  if (!radUseGps) snprintf(b, sizeof b, "GPS OFF - using %s", radSavedHas ? radSavedSrc : "saved home");
  else if (gpsAlive()) snprintf(b, sizeof b, "GPS FIX, %u SATS - radar centres on you", gpsSats);
  else if (gpsBytes) snprintf(b, sizeof b, "GPS: NO FIX YET - using %s", radSavedHas ? radSavedSrc : "nothing");
  else snprintf(b, sizeof b, "GPS: NOT ANSWERING - using %s", radSavedHas ? radSavedSrc : "nothing");
  return b;
}

//  Approximate home from the public IP — only on the user's ENTER.
static bool radLocateByIp() {
  HTTPClient http;
  http.setTimeout(8000);
  if (!http.begin("http://ip-api.com/json/?fields=status,lat,lon")) return false;
  int code = http.GET();
  bool ok = false;
  if (code == 200) {
    JsonDocument d;
    if (!deserializeJson(d, http.getString()) && d["status"] == "success") {
      radSaveHome(d["lat"].as<double>(), d["lon"].as<double>(), "IP ~");
      ok = true;
    }
  }
  http.end();
  return ok;
}

//  A US ZIP code to the lat/lon of its centre, via zippopotam.us (free, no
//  key). Runs on the radar task. Sets radMsg to the town, or why it failed.
static bool radLocateByZip(const char* zip) {
  HTTPClient http;
  http.setTimeout(8000);
  char url[64];
  snprintf(url, sizeof url, "http://api.zippopotam.us/us/%s", zip);
  if (!http.begin(url)) { snprintf(radMsg, sizeof radMsg, "LOOKUP FAILED"); return false; }
  int code = http.GET();
  bool ok = false;
  if (code == 200) {
    JsonDocument d;
    if (!deserializeJson(d, http.getString())) {
      JsonObject p = d["places"][0];
      const char* la = p["latitude"] | "";
      const char* lo = p["longitude"] | "";
      if (la[0] && lo[0]) {
        char src[12]; snprintf(src, sizeof src, "ZIP %s", zip);
        radSaveHome(atof(la), atof(lo), src);
        prefs.begin("radar", false); prefs.putString("zip", zip); prefs.end();
        snprintf(radMsg, sizeof radMsg, "%s, %s", (const char*)(p["place name"] | ""),
                 (const char*)(p["state abbreviation"] | ""));
        ok = true;
      }
    }
    if (!ok) snprintf(radMsg, sizeof radMsg, "LOOKUP FAILED");
  } else if (code == 404) snprintf(radMsg, sizeof radMsg, "ZIP %s NOT FOUND", zip);
  else snprintf(radMsg, sizeof radMsg, "LOOKUP FAILED (%d)", code);
  http.end();
  return ok;
}

//  One fetch into the staging table, then swap it in.
static void radFetch() {
  float km = kRdRanges[radRange] * 1.3f;                  // a little past the ring: rim dots
  int nm = (int)ceilf(km / 1.852f); if (nm < 1) nm = 1; if (nm > 250) nm = 250;
  char url[128];
  double la, lo;
  xSemaphoreTake(radLock, portMAX_DELAY); la = radLat; lo = radLon; xSemaphoreGive(radLock);
  snprintf(url, sizeof url, "https://opendata.adsb.fi/api/v3/lat/%.4f/lon/%.4f/dist/%d", la, lo, nm);

  WiFiClientSecure tls;
  tls.setInsecure();                                     // public data; no secrets sent
  HTTPClient http;
  http.setTimeout(8000);
  http.useHTTP10(true);                                  // plain stream for the parser
  if (!http.begin(tls, url)) { radHttp = -1; return; }
  int code = http.GET();
  radHttp = code;
  if (code != 200) { http.end(); return; }

  JsonDocument filter;
  JsonObject f = filter["ac"][0].to<JsonObject>();
  for (const char* k : { "flight", "r", "t", "alt_baro", "gs", "track", "dst", "dir" }) f[k] = true;
  JsonDocument doc;
  DeserializationError e = deserializeJson(doc, http.getStream(), DeserializationOption::Filter(filter));
  http.end();
  if (e) { radHttp = -2; return; }

  int n = 0;
  for (JsonObject a : doc["ac"].as<JsonArray>()) {
    if (n >= RD_MAX) break;
    if (a["dst"].isNull() || a["dir"].isNull()) continue;
    const char* fl = a["flight"] | "";
    const char* rg = a["r"] | "";
    snprintf(rsCall[n], sizeof rsCall[n], "%s", fl[0] ? fl : (rg[0] ? rg : "?"));
    for (int k = strlen(rsCall[n]) - 1; k >= 0 && rsCall[n][k] == ' '; k--) rsCall[n][k] = 0;
    snprintf(rsType[n], sizeof rsType[n], "%s", (const char*)(a["t"] | ""));
    snprintf(rsReg[n], sizeof rsReg[n], "%s", rg);
    rsDst[n] = a["dst"].as<float>() * 1.852f;
    rsDir[n] = a["dir"].as<float>();
    rsGs[n]  = a["gs"] | 0.0f;
    rsTrk[n] = a["track"].isNull() ? -1.0f : a["track"].as<float>();
    rsAlt[n] = a["alt_baro"].is<int>() ? a["alt_baro"].as<int>() : INT32_MIN;   // "ground"
    n++;
  }
  //  Nearest first: that is the list's order.
  for (int i = 1; i < n; i++)
    for (int j = i; j > 0 && rsDst[j] < rsDst[j - 1]; j--) {
      char t9[9]; char t5[5]; float tf; int32_t ti;
      memcpy(t9, rsCall[j], 9); memcpy(rsCall[j], rsCall[j - 1], 9); memcpy(rsCall[j - 1], t9, 9);
      memcpy(t5, rsType[j], 5); memcpy(rsType[j], rsType[j - 1], 5); memcpy(rsType[j - 1], t5, 5);
      memcpy(t9, rsReg[j], 9);  memcpy(rsReg[j], rsReg[j - 1], 9);  memcpy(rsReg[j - 1], t9, 9);
      tf = rsDst[j]; rsDst[j] = rsDst[j - 1]; rsDst[j - 1] = tf;
      tf = rsDir[j]; rsDir[j] = rsDir[j - 1]; rsDir[j - 1] = tf;
      tf = rsGs[j];  rsGs[j]  = rsGs[j - 1];  rsGs[j - 1]  = tf;
      tf = rsTrk[j]; rsTrk[j] = rsTrk[j - 1]; rsTrk[j - 1] = tf;
      ti = rsAlt[j]; rsAlt[j] = rsAlt[j - 1]; rsAlt[j - 1] = ti;
    }
  rsN = n;
  xSemaphoreTake(radLock, portMAX_DELAY);
  memcpy(radCall, rsCall, sizeof radCall); memcpy(radType, rsType, sizeof radType);
  memcpy(radReg, rsReg, sizeof radReg);
  memcpy(radDst, rsDst, sizeof radDst); memcpy(radDir, rsDir, sizeof radDir);
  memcpy(radGs, rsGs, sizeof radGs);    memcpy(radTrk, rsTrk, sizeof radTrk);
  memcpy(radAlt, rsAlt, sizeof radAlt);
  radN = rsN;
  radFetchedMs = millis();
  xSemaphoreGive(radLock);
}

static void radTask(void*) {
  radTaskAlive = true;
  uint32_t last = 0;
  while (radRun) {
    if (WiFi.status() == WL_CONNECTED) {
      if (radLocateReq) {
        snprintf(radMsg, sizeof radMsg, "%s", radLocateByIp() ? "" : "IP LOOKUP FAILED");
        radLocateReq = false; last = 0;
      }
      if (radZipReq) {
        char z[6];
        for (int i = 0; i < 5; i++) z[i] = (char)('0' + radZip[i]);
        z[5] = 0;
        if (radLocateByZip(z)) { radZipOk = true; last = 0; radForce = true; }
        radZipReq = false;
      }
      if (radHome && (!last || radForce || millis() - last >= RD_FETCH_MS)) {
        radForce = false; last = millis(); radFetch();
      }
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
  radTaskAlive = false;
  vTaskDelete(nullptr);
}

void radarEnter() {
  if (!radLock) radLock = xSemaphoreCreateMutex();
  radLoadHome();
  radSel = 0; radMsg[0] = 0;
  prefs.begin("radar", true); String z = prefs.getString("zip", ""); prefs.end();
  if (z.length() == 5) for (int i = 0; i < 5; i++) radZip[i] = (uint8_t)(z[i] - '0');
  radZipMode = false; radPrevE = true; radEUsed = true;
  radRun = true;
  if (!radTaskAlive)
    xTaskCreatePinnedToCore(radTask, "radar", 12288, nullptr, 1, nullptr, 0);
}

void radarLeave() { radRun = false; }             // the task finishes its request and ends

//  A colour scaled toward black (0..1).
static uint16_t radDim(uint16_t c, float k) {
  int r = (c >> 11) & 31, g = (c >> 5) & 63, b = c & 31;
  return (uint16_t)(((int)(r * k) << 11) | ((int)(g * k) << 5) | (int)(b * k));
}

static void radAltStr(char* out, size_t n, int32_t alt) {
  if (alt == INT32_MIN) snprintf(out, n, "GND");
  else if (alt >= 18000) snprintf(out, n, "FL%03d", (int)((alt + 50) / 100));
  else snprintf(out, n, "%dFT", (int)alt);
}

//  Text with a 1 px black shadow, so it reads over rings and the sweep.
static void radText(const char* s, int x, int y, uint8_t size, uint16_t col) {
  inst->setTextSize(size);
  inst->setTextColor(BLACK); inst->setCursor(x + 1, y + 1); inst->print(s);
  inst->setTextColor(col);   inst->setCursor(x, y);         inst->print(s);
}

static void radOpenZip() { radZipMode = true; radZipPos = 0; radMsg[0] = 0; }

//  Five big digits; the selected one boxed with arrows above and below.
static void radDrawZip() {
  inst->fillScreen(CYBER_BG);
  ui3DHeader("SET HOME: ZIP / GPS");
  const int dw = 34, gap = 10, gw = 62, x0 = (TFT_W - (5 * dw + 4 * gap + 16 + gw)) / 2, y0 = 46, dh = 42;
  for (int i = 0; i < 6; i++) {
    const bool sel = i == radZipPos;
    const int x = i < 5 ? x0 + i * (dw + gap) : x0 + 5 * dw + 4 * gap + 16;
    const int w = i < 5 ? dw : gw;
    if (sel) inst->fillRect(x, y0, w, dh, radDim(NEON_CYAN, 0.35f));
    inst->drawRect(x, y0, w, dh, sel ? NEON_CYAN : CYBER_GRID);
    if (i < 5) {
      char d[2] = { (char)('0' + radZip[i]), 0 };
      radText(d, x + (dw - 18) / 2, y0 + (dh - 24) / 2, 3, sel ? NEON_YELLOW : NEON_CYAN);
    } else {                                            /* the GPS switch */
      radText("GPS", x + (gw - 18) / 2, y0 + 5, 1, sel ? NEON_YELLOW : CYBER_DIMTXT);
      const char* v = radUseGps ? "ON" : "OFF";
      radText(v, x + (gw - (int)strlen(v) * 12) / 2, y0 + 19, 2,
              radUseGps ? (gpsAlive() ? NEON_GREEN : NEON_CYAN) : CYBER_DIMTXT);
    }
    if (sel) {
      int cx = x + w / 2;
      inst->fillTriangle(cx - 5, y0 - 3, cx + 5, y0 - 3, cx, y0 - 8, NEON_CYAN);
      inst->fillTriangle(cx - 5, y0 + dh + 2, cx + 5, y0 + dh + 2, cx, y0 + dh + 7, NEON_CYAN);
    }
  }
  //  Line 1: the lookup's result, else Wi-Fi trouble. Line 2: the GPS.
  const char* st = radMsg[0] ? radMsg
                 : WiFi.status() != WL_CONNECTED ? "NO WIFI - join in SETTINGS > WIFI" : "";
  radText(st, (TFT_W - (int)strlen(st) * 6) / 2, 100, 1,
          radZipReq ? NEON_CYAN : (radMsg[0] ? NEON_YELLOW : NEON_RED));
  const char* gs = radGpsStatus();
  radText(gs, (TFT_W - (int)strlen(gs) * 6) / 2, 112, 1, radUseGps && gpsAlive() ? NEON_GREEN : CYBER_DIMTXT);
  radText("UP/DOWN change   LEFT/RIGHT move", 64, 130, 1, CYBER_DIMTXT);
  radText(radZipPos == 5 ? "ENTER: GPS on/off   LEFT on 1st digit: back"
                         : "ENTER: look up ZIP   LEFT on 1st digit: back", radZipPos == 5 ? 34 : 31, 142, 1, CYBER_DIMTXT);
  radText("US ZIP codes, via zippopotam.us", 67, 158, 1, radDim(CYBER_DIMTXT, 0.8f));
  uiBlit();
}

void uiViewRadar() {
  //  GPS: polled here because nothing else does outside the GPS page (it
  //  backs off by itself if the receiver is not answering).
  if (radUseGps) {
    static uint32_t lastPoll = 0;
    if (millis() - lastPoll >= 200) { lastPoll = millis(); gpsPoll(); }
  }
  radApplyHome();

  //  ENTER: a tap switches north-up / heading-up (or, with no home yet,
  //  opens the ZIP page); a hold opens the ZIP page to change home.
  {
    const bool E = !(pcfStable & (1 << PCF_ENTER));
    const uint32_t now = millis();
    if (!radZipMode) {
      if (E && !radPrevE) { radEAt = now; radEUsed = false; }
      if (E && !radEUsed && now - radEAt >= 700) { radEUsed = true; radOpenZip(); }
      else if (!E && radPrevE && !radEUsed) {
        radEUsed = true;
        if (!radHome) radOpenZip(); else radHdgUp = !radHdgUp;
      }
    }
    radPrevE = E;
    if (radZipOk) { radZipOk = false; radZipMode = false; radEUsed = true; radToastMs = millis(); }
  }
  if (radZipMode) { radDrawZip(); return; }

  inst->fillScreen(CYBER_BG);
  const bool net = WiFi.status() == WL_CONNECTED;
  const float rangeKm = kRdRanges[radRange];
  const float rot = radHdgUp && imuAlive() ? compassHeading() : 0;   // heading-up turns the scope

  //  Rings, the centre cross, cardinal letters, the half-range label.
  for (int k = 1; k <= 4; k++) {
    inst->drawCircle(RD_CX, RD_CY, RD_R * k / 4, k == 4 ? NEON_CYAN : radDim(NEON_CYAN, 0.35f));
    if (k == 4) inst->drawCircle(RD_CX, RD_CY, RD_R - 1, radDim(NEON_CYAN, 0.6f));
  }
  static const char* const kCard[4] = { "N", "E", "S", "W" };
  for (int i = 0; i < 4; i++) {
    float a = (i * 90 - rot) * DEG_TO_RAD;
    int x = RD_CX + (int)((RD_R - 12) * sinf(a)) - 5, y = RD_CY - (int)((RD_R - 12) * cosf(a)) - 7;
    radText(kCard[i], x, y, 2, i == 0 ? NEON_MAGENTA : NEON_CYAN);
  }
  char buf[48];
  snprintf(buf, sizeof buf, "%d", (int)(rangeKm / 2));
  radText(buf, RD_CX + 4, RD_CY - RD_R / 2 + 3, 1, radDim(NEON_CYAN, 0.8f));
  //  Status labels: top right of the side panel, stacked and right-aligned
  //  over the list's distance column - off the scope, and ending at x 296 so
  //  the panel's rounded top-right corner doesn't clip them.
  {
    const int rx = 296;
    int ly = 3;
    if (radHdgUp) { radText("HDG", rx - 18, ly, 1, NEON_YELLOW); ly += 10; }
    if (radUseGps) {
      const char* g = gpsAlive() ? "GPS" : "GPS?";
      radText(g, rx - 6 * (int)strlen(g), ly, 1, gpsAlive() ? NEON_GREEN : CYBER_DIMTXT);
    }
  }

  //  The sweep: a line and a fading trail, one turn every 4 s.
  float sw = fmodf(millis() / 4000.0f * 360.0f, 360.0f);
  for (int t = 12; t >= 0; t--) {
    float a = (sw - t * 3) * DEG_TO_RAD;
    inst->drawLine(RD_CX, RD_CY, RD_CX + (int)(RD_R * sinf(a)), RD_CY - (int)(RD_R * cosf(a)),
                   radDim(NEON_CYAN, t == 0 ? 1.0f : 0.4f * (1.0f - t / 13.0f)));
  }

  //  Home: a small white dot with a slow pulse ring, over the sweep and
  //  under the aircraft (so a plane overhead still shows).
  {
    uint32_t ph = millis() % 1600;
    int pr = 5 + (int)(ph * 20 / 1600);
    inst->drawCircle(RD_CX, RD_CY, pr, radDim(WHITE, 0.8f * (1.0f - ph / 1600.0f)));
    inst->fillCircle(RD_CX, RD_CY, 3, WHITE);
    inst->drawCircle(RD_CX, RD_CY, 4, BLACK);
  }

  //  Aircraft: moved on from the fetch along track at ground speed.
  if (radLock) xSemaphoreTake(radLock, portMAX_DELAY);
  const int n = radN;
  if (radSel >= n) radSel = n ? n - 1 : 0;
  const float dtH = radFetchedMs ? (millis() - radFetchedMs) / 3600000.0f : 0;
  for (int i = n - 1; i >= 0; i--) {                     // nearest drawn last, on top
    float bx = radDst[i] * sinf(radDir[i] * DEG_TO_RAD), by = radDst[i] * cosf(radDir[i] * DEG_TO_RAD);
    if (radTrk[i] >= 0 && radGs[i] > 0) {
      float d = radGs[i] * 1.852f * dtH;
      bx += d * sinf(radTrk[i] * DEG_TO_RAD); by += d * cosf(radTrk[i] * DEG_TO_RAD);
    }
    float dist = sqrtf(bx * bx + by * by), brg = atan2f(bx, by) - rot * DEG_TO_RAD;
    float pr = dist / rangeKm * RD_R;
    bool sel = i == radSel, ground = radAlt[i] == INT32_MIN;
    uint16_t col = sel ? NEON_YELLOW : NEON_RED;
    if (pr > RD_R) {                                     // off the scope: a dot on the rim
      inst->fillCircle(RD_CX + (int)(RD_R * sinf(brg)), RD_CY - (int)(RD_R * cosf(brg)), sel ? 5 : 4, col);
      continue;
    }
    int x = RD_CX + (int)(pr * sinf(brg)), y = RD_CY - (int)(pr * cosf(brg));
    if (ground) { inst->fillCircle(x, y, 3, sel ? NEON_YELLOW : CYBER_DIMTXT); }
    else if (radTrk[i] >= 0) {
      float h = (radTrk[i] - rot) * DEG_TO_RAD, s = sinf(h), c = cosf(h);
      //  Speed vector: where it will be in 30 s at this range's scale,
      //  capped so fast jets at short range don't criss-cross the scope.
      float v = fminf(radGs[i] * 1.852f / 120.0f / rangeKm * RD_R, 26.0f);
      if (v > 3) {
        int ex = x + (int)(v * s), ey = y - (int)(v * c);
        inst->drawLine(x, y, ex, ey, NEON_PINK);
        inst->drawLine(x + 1, y, ex + 1, ey, NEON_PINK);
      }
      //  A bold arrowhead: tip 10 px ahead, 7 px wings.
      int tx = x + (int)(10 * s), ty = y - (int)(10 * c);
      int lx = x + (int)(-6 * s + 7 * c), ly = y - (int)(-6 * c - 7 * s);
      int rx = x + (int)(-6 * s - 7 * c), ry = y - (int)(-6 * c + 7 * s);
      inst->fillTriangle(tx, ty, lx, ly, rx, ry, col);
      inst->drawTriangle(tx, ty, lx, ly, rx, ry, BLACK);
    } else inst->fillCircle(x, y, 5, col);
    if (sel) { inst->drawCircle(x, y, 13, NEON_YELLOW); inst->drawCircle(x, y, 14, NEON_YELLOW); }
    if (sel || n <= 5) {                                 // label it (all of them, if few)
      uint8_t sz = sel ? 2 : 1;
      int w = (sel ? 12 : 6) * (int)strlen(radCall[i]);
      int lx = x > RD_CX ? x - 16 - w : x + 16;
      radText(radCall[i], constrain(lx, 1, RD_PANEL_X - 6 - w), constrain(y - (sel ? 8 : 4), 1, TFT_H - 17), sz,
              sel ? NEON_YELLOW : NEON_CYAN);
    }
  }

  //  The right panel, in double-size text: range, the nearest four, then the
  //  selected aircraft's altitude, speed and track.
  inst->drawFastVLine(RD_PANEL_X - 4, 4, TFT_H - 8, CYBER_GRID);
  snprintf(buf, sizeof buf, "%dKM", (int)rangeKm);
  radText(buf, RD_PANEL_X, 3, 2, NEON_MAGENTA);

  int y = 24;
  if (!net) {
    radText("NO WIFI", RD_PANEL_X, y, 2, NEON_RED);
    radText("Join a network in", RD_PANEL_X, y + 24, 1, NEON_CYAN);
    radText("SETTINGS > WIFI", RD_PANEL_X, y + 36, 1, NEON_CYAN);
  } else if (!radHome) {
    radText("NO HOME", RD_PANEL_X, y, 2, NEON_RED);
    radText("ENTER: set your", RD_PANEL_X, y + 24, 1, NEON_CYAN);
    radText("ZIP code", RD_PANEL_X, y + 36, 1, NEON_CYAN);
    radText("or console:", RD_PANEL_X, y + 54, 1, NEON_CYAN);
    radText("radar home LAT LON", RD_PANEL_X, y + 66, 1, NEON_CYAN);
    if (radUseGps) radText("or wait for a GPS fix", RD_PANEL_X, y + 82, 1, CYBER_DIMTXT);
    if (radMsg[0]) radText(radMsg, RD_PANEL_X, y + 98, 1, NEON_YELLOW);
  } else {
    const int rows = 4, first = radSel >= rows ? radSel - rows + 1 : 0;
    for (int i = first; i < n && i < first + rows; i++, y += 18) {
      snprintf(buf, sizeof buf, "%-7.7s%3d", radCall[i], (int)lroundf(radDst[i]));
      if (i == radSel) inst->fillRect(RD_PANEL_X - 2, y - 2, TFT_W - RD_PANEL_X, 18, radDim(NEON_CYAN, 0.4f));
      radText(buf, RD_PANEL_X, y, 2, i == radSel ? NEON_YELLOW : NEON_CYAN);
    }
    if (!n) radText(radFetchedMs ? "NONE" : "WAIT..", RD_PANEL_X, y, 2, CYBER_DIMTXT);
    if (n && radSel < n) {                               // the selected one, in full
      char alt[10]; radAltStr(alt, sizeof alt, radAlt[radSel]);
      radText(alt, RD_PANEL_X, 100, 2, NEON_MAGENTA);
      if (radTrk[radSel] >= 0) snprintf(buf, sizeof buf, "%dKT %03d", (int)radGs[radSel], (int)radTrk[radSel]);
      else                     snprintf(buf, sizeof buf, "%dKT", (int)radGs[radSel]);
      radText(buf, RD_PANEL_X, 118, 2, NEON_CYAN);
      snprintf(buf, sizeof buf, "%s %s", radType[radSel], radReg[radSel]);
      radText(buf, RD_PANEL_X, 137, 1, NEON_CYAN);
    }
  }
  if (radLock) xSemaphoreGive(radLock);

  //  Footer: freshness, home source, and the data credit adsb.fi asks for.
  if (net && radHome) {
    uint32_t age = radFetchedMs ? (millis() - radFetchedMs) / 1000 : 0;
    if (radHttp && radHttp != 200) snprintf(buf, sizeof buf, "ERR %d  %s", radHttp, radHomeSrc);
    else snprintf(buf, sizeof buf, "%d AC  %lus  %s", n, (unsigned long)age, radHomeSrc);
    radText(buf, RD_PANEL_X, TFT_H - 22, 1, CYBER_DIMTXT);
  }
  radText("Data: adsb.fi", RD_PANEL_X, TFT_H - 11, 1, CYBER_DIMTXT);
  if (radToastMs && millis() - radToastMs < 4000 && radMsg[0]) {
    char t[48]; snprintf(t, sizeof t, "HOME: %s", radMsg);
    inst->fillRect(0, TFT_H - 14, RD_PANEL_X - 6, 14, BLACK);
    radText(t, 16, TFT_H - 11, 1, NEON_YELLOW);           // clear of the rounded corner
  }
  uiBlit();
}

static void radarAction(UiAction a) {
  if (radZipMode) {
    switch (a) {
      case ACT_PREV:
      case ACT_NEXT:
        if (radZipPos == 5) { radSetUseGps(!radUseGps); break; }
        radZip[radZipPos] = (radZip[radZipPos] + (a == ACT_PREV ? 1 : 9)) % 10;
        if (!radZipReq) radMsg[0] = 0;
        break;
      case ACT_RIGHT: if (radZipPos < 5) radZipPos++; break;
      case ACT_BACK:
        if (radZipPos) radZipPos--;
        else { radZipMode = false; radEUsed = true; radMsg[0] = 0; }
        break;
      case ACT_SELECT:
        if (radZipPos == 5) { radSetUseGps(!radUseGps); break; }
        if (WiFi.status() != WL_CONNECTED) snprintf(radMsg, sizeof radMsg, "NO WIFI - join in SETTINGS > WIFI");
        else if (!radZipReq) { snprintf(radMsg, sizeof radMsg, "LOOKING UP..."); radZipReq = true; }
        break;
      default: break;
    }
    return;
  }
  switch (a) {
    case ACT_BACK:  uiSel = UI_RADAR - 1; uiEnter(UI_MENU); break;
    case ACT_NEXT:  if (radN) radSel = (radSel + 1) % radN; break;
    case ACT_PREV:  if (radN) radSel = (radSel + radN - 1) % radN; break;
    case ACT_RIGHT:
      radRange = (radRange + 1) % RD_NRANGES;
      prefs.begin("radar", false); prefs.putUChar("range", radRange); prefs.end();
      radForce = true;                                    // refetch at the new radius now
      break;
    case ACT_SELECT: break;            // tap / hold: handled per frame in uiViewRadar
    default: break;
  }
}

//  Console "radar [home <lat> <lon> | home gps | home clear]".
void radarConsole(const char* arg) {
  while (*arg == ' ') arg++;
  if (!strncmp(arg, "home", 4)) {
    const char* v = arg + 4; while (*v == ' ') v++;
    double la, lo;
    if (!strcmp(v, "gps")) {
      if (gpsAlive()) radSaveHome(gpsLat, gpsLon, "GPS"); else { Serial.println("radar: no GPS fix"); return; }
    } else if (!strcmp(v, "clear")) {
      prefs.begin("radar", false); prefs.remove("lat"); prefs.remove("lon"); prefs.end();
      radHome = false;
    } else if (sscanf(v, "%lf %lf", &la, &lo) == 2 && fabs(la) <= 90 && fabs(lo) <= 180) {
      radSaveHome(la, lo, "SAVED");
    } else { Serial.println("radar home <lat> <lon> | gps | clear   e.g. radar home 51.4700 -0.4543"); return; }
  }
  Serial.printf("radar: home %s %.4f, %.4f (%s) | range %d km | %d aircraft, fetched %lus ago, HTTP %d | wifi %s\n",
                radHome ? "set" : "NOT SET", radLat, radLon, radHomeSrc, kRdRanges[radRange], radN,
                radFetchedMs ? (unsigned long)((millis() - radFetchedMs) / 1000) : 0UL, radHttp,
                WiFi.status() == WL_CONNECTED ? "connected" : "not connected");
}

// ─────────────────────────────────────────────────────────
//  NEON BLOCKS — a falling-block puzzle: the seven four-square shapes,
//  full rows clear, it speeds up every ten rows. Original neon look.
//
//    LEFT / RIGHT  move (hold to slide)     UP     rotate
//    DOWN          drop faster              ENTER  tap: drop straight down
//                                                  hold: pause (resume / quit)
//  Movement reads the held pad state every frame (like NEON RUNNER); the
//  title, pause and game-over screens use the menu's press events.
// ─────────────────────────────────────────────────────────
#define BK_W          10
#define BK_H          20
#define BK_CELL       8
#define BK_FX         120           // playfield, top-left
#define BK_FY         6
#define BK_DAS_MS     170           // hold LEFT/RIGHT this long, then slide
#define BK_ARR_MS     45            // ... one column every this often
#define BK_SOFT_MS    35            // DOWN held: a row every this often
#define BK_LOCK_MS    450           // resting on something this long = placed
#define BK_LOCK_MOVES 15            // moves that may postpone the lock
#define BK_HOLD_MS    600           // ENTER held this long = pause
#define BK_CLEAR_MS   260           // full rows flash this long

enum BkState : uint8_t { BK_TITLE, BK_PLAY, BK_CLEAR, BK_PAUSE, BK_OVER };
static BkState  bkState = BK_TITLE;
static uint8_t  bkBoard[BK_H][BK_W];          // 0 empty, 1..7 a placed shape's colour
static int8_t   bkP = 0, bkR = 0, bkX = 0, bkY = 0;   // the falling piece
static uint8_t  bkNext[3], bkBag[7], bkBagN = 0;
static uint32_t bkScore = 0, bkLines = 0, bkHi = 0;
static uint16_t bkLevel = 1;
static uint32_t bkFallAt = 0, bkLandAt = 0, bkClearAt = 0, bkDasAt = 0, bkEnterAt = 0;
static uint8_t  bkLockMoves = 0, bkPauseSel = 0;
static int8_t   bkDasDir = 0;
static bool     bkPrevU = true, bkPrevE = true, bkEnterUsed = true, bkNewHi = false;
static bool     bkFull[BK_H];                  // rows being cleared

//  The shapes: I O T S Z J L, as cells in an n x n box.
static const uint8_t kBkN[7] = { 4, 2, 3, 3, 3, 3, 3 };
static const int8_t  kBkCells[7][4][2] = {
  { {0,1}, {1,1}, {2,1}, {3,1} },
  { {0,0}, {1,0}, {0,1}, {1,1} },
  { {1,0}, {0,1}, {1,1}, {2,1} },
  { {1,0}, {2,0}, {0,1}, {1,1} },
  { {0,0}, {1,0}, {1,1}, {2,1} },
  { {0,0}, {0,1}, {1,1}, {2,1} },
  { {2,0}, {0,1}, {1,1}, {2,1} },
};
static const uint16_t kBkCol[8] = { 0, NEON_CYAN, NEON_YELLOW, 0xB81F, NEON_GREEN,
                                    NEON_RED, 0x2D7F, NEON_ORANGE };

//  Cell k of shape p at rotation r (quarter turns clockwise).
static void bkCell(int p, int r, int k, int* cx, int* cy) {
  int x = kBkCells[p][k][0], y = kBkCells[p][k][1], n = kBkN[p];
  for (int i = 0; i < (r & 3); i++) { int t = x; x = n - 1 - y; y = t; }
  *cx = x; *cy = y;
}

static bool bkFits(int p, int r, int x, int y) {
  for (int k = 0; k < 4; k++) {
    int cx, cy; bkCell(p, r, k, &cx, &cy);
    int bx = x + cx, by = y + cy;
    if (bx < 0 || bx >= BK_W || by >= BK_H) return false;
    if (by >= 0 && bkBoard[by][bx]) return false;
  }
  return true;
}

//  Shuffled bags of all seven: no long droughts of any one shape.
static uint8_t bkDraw() {
  if (!bkBagN) {
    for (int i = 0; i < 7; i++) bkBag[i] = i;
    for (int i = 6; i > 0; i--) { int j = esp_random() % (i + 1); uint8_t t = bkBag[i]; bkBag[i] = bkBag[j]; bkBag[j] = t; }
    bkBagN = 7;
  }
  return bkBag[--bkBagN];
}

static uint32_t bkGravityMs() {
  int ms = 800 - (int)(bkLevel - 1) * 70;
  return ms < 70 ? 70 : ms;
}

static void bkSaveHi() {
  if (bkScore <= bkHi) return;
  bkHi = bkScore; bkNewHi = true;
  prefs.begin("servoctl", false); prefs.putUInt("blkhi", bkHi); prefs.end();
}

//  The next piece in at the top; if it has nowhere to go, the game is over.
static void bkSpawn() {
  bkP = bkNext[0]; bkNext[0] = bkNext[1]; bkNext[1] = bkNext[2]; bkNext[2] = bkDraw();
  bkR = 0; bkX = (BK_W - kBkN[bkP]) / 2; bkY = bkP == 0 ? -1 : 0;
  bkLandAt = 0; bkLockMoves = 0; bkFallAt = millis() + bkGravityMs();
  if (!bkFits(bkP, bkR, bkX, bkY)) { bkSaveHi(); bkState = BK_OVER; }
}

static void bkNewGame() {
  memset(bkBoard, 0, sizeof bkBoard);
  bkScore = 0; bkLines = 0; bkLevel = 1; bkBagN = 0; bkNewHi = false;
  for (int i = 0; i < 3; i++) bkNext[i] = bkDraw();
  bkState = BK_PLAY;
  bkPrevU = true; bkPrevE = true; bkEnterUsed = true; bkDasDir = 0;   // the ENTER that started it
  bkSpawn();
}

void blocksEnter() {
  prefs.begin("servoctl", true); bkHi = prefs.getUInt("blkhi", 0); prefs.end();
  bkState = BK_TITLE;
}

//  A successful move or turn while resting postpones the lock (a few times).
static void bkMoved() {
  if (bkLandAt && bkLockMoves < BK_LOCK_MOVES) { bkLandAt = millis(); bkLockMoves++; }
}

static bool bkShift(int dx) {
  if (!bkFits(bkP, bkR, bkX + dx, bkY)) return false;
  bkX += dx; bkMoved(); return true;
}

//  Turn, nudging sideways or up if the wall or the stack is in the way.
static void bkRotate() {
  static const int8_t kKick[6][2] = { {0,0}, {-1,0}, {1,0}, {0,-1}, {-2,0}, {2,0} };
  int r = (bkR + 1) & 3;
  for (int k = 0; k < 6; k++)
    if (bkFits(bkP, r, bkX + kKick[k][0], bkY + kKick[k][1])) {
      bkR = r; bkX += kKick[k][0]; bkY += kKick[k][1]; bkMoved(); return;
    }
}

//  Place the piece; mark full rows (they flash, then go).
static void bkLock() {
  for (int k = 0; k < 4; k++) {
    int cx, cy; bkCell(bkP, bkR, k, &cx, &cy);
    int by = bkY + cy;
    if (by < 0) { bkSaveHi(); bkState = BK_OVER; return; }   // stuck out of the top
    bkBoard[by][bkX + cx] = bkP + 1;
  }
  int n = 0;
  for (int y = 0; y < BK_H; y++) {
    bool full = true;
    for (int x = 0; x < BK_W && full; x++) full = bkBoard[y][x] != 0;
    bkFull[y] = full; n += full;
  }
  if (n) { bkState = BK_CLEAR; bkClearAt = millis(); }
  else bkSpawn();
}

static void bkFinishClear() {
  static const uint16_t kPts[5] = { 0, 100, 300, 500, 800 };
  int n = 0;
  for (int y = BK_H - 1; y >= 0; ) {
    if (!bkFull[y]) { y--; continue; }
    for (int yy = y; yy > 0; yy--) { memcpy(bkBoard[yy], bkBoard[yy - 1], BK_W); bkFull[yy] = bkFull[yy - 1]; }
    memset(bkBoard[0], 0, BK_W); bkFull[0] = false;
    n++;                                   // same y again: the row above moved down
  }
  bkScore += kPts[n > 4 ? 4 : n] * bkLevel;
  bkLines += n;
  bkLevel = 1 + bkLines / 10;
  bkState = BK_PLAY;
  bkSpawn();
}

static void bkHardDrop() {
  int d = 0;
  while (bkFits(bkP, bkR, bkX, bkY + 1)) { bkY++; d++; }
  bkScore += 2 * d;
  bkLock();
}

static void bkUpdate() {
  const uint8_t s = pcfStable;
  auto held = [&](int bit) { return !(s & (1 << bit)); };
  bool L = held(PCF_LEFT), R = held(PCF_RIGHT), U = held(PCF_UP), D = held(PCF_DOWN), E = held(PCF_ENTER);
  uint32_t now = millis();
  if (L || R || U || D || E) uiNoteActivity();

  if (bkState == BK_CLEAR) { if (now - bkClearAt >= BK_CLEAR_MS) bkFinishClear(); }
  if (bkState != BK_PLAY) { bkPrevU = U; bkPrevE = E; return; }

  //  ENTER: a tap drops, a hold pauses.
  if (E && !bkPrevE) { bkEnterAt = now; bkEnterUsed = false; }
  if (E && !bkEnterUsed && now - bkEnterAt >= BK_HOLD_MS) {
    bkEnterUsed = true; bkState = BK_PAUSE; bkPauseSel = 0; bkPrevE = E; return;
  }
  if (!E && bkPrevE && !bkEnterUsed) { bkEnterUsed = true; bkPrevE = E; bkHardDrop(); return; }
  bkPrevE = E;

  if (U && !bkPrevU) bkRotate();
  bkPrevU = U;

  int dir = L && !R ? -1 : R && !L ? 1 : 0;
  if (dir != bkDasDir) { bkDasDir = dir; if (dir) { bkShift(dir); bkDasAt = now + BK_DAS_MS; } }
  else if (dir && (int32_t)(now - bkDasAt) >= 0) { bkShift(dir); bkDasAt = now + BK_ARR_MS; }

  //  Falling: gravity, or faster with DOWN (a point a row).
  uint32_t step = D ? BK_SOFT_MS : bkGravityMs();
  if ((int32_t)(now - bkFallAt) >= 0 || (D && now + step < bkFallAt)) {
    if (bkFits(bkP, bkR, bkX, bkY + 1)) { bkY++; if (D) bkScore++; bkLandAt = 0; }
    bkFallAt = now + step;
  }
  //  Resting on something: place it after the lock delay.
  if (!bkFits(bkP, bkR, bkX, bkY + 1)) {
    if (!bkLandAt) bkLandAt = now;
    else if (now - bkLandAt >= BK_LOCK_MS) bkLock();
  } else bkLandAt = 0;
}

// ── Drawing ──
static uint16_t bkShade(uint16_t c, float k) {        // k < 1 darker, > 1 toward white
  int r = (c >> 11) & 31, g = (c >> 5) & 63, b = c & 31;
  if (k <= 1) { r = r * k; g = g * k; b = b * k; }
  else { float t = k - 1; r += (31 - r) * t; g += (63 - g) * t; b += (31 - b) * t; }
  return (uint16_t)((r << 11) | (g << 5) | b);
}

//  One raised block: light top-left edge, dark bottom-right, like the plates.
static void bkBlock(int px, int py, int sz, uint16_t c) {
  inst->fillRect(px, py, sz, sz, c);
  inst->drawFastHLine(px, py, sz, bkShade(c, 1.55f));
  inst->drawFastVLine(px, py, sz, bkShade(c, 1.55f));
  inst->drawFastHLine(px, py + sz - 1, sz, bkShade(c, 0.45f));
  inst->drawFastVLine(px + sz - 1, py, sz, bkShade(c, 0.45f));
}

static void bkText(const char* s, int x, int y, uint8_t size, uint16_t col) {
  inst->setTextSize(size);
  inst->setTextColor(BLACK); inst->setCursor(x + 1, y + 1); inst->print(s);
  inst->setTextColor(col);   inst->setCursor(x, y);         inst->print(s);
}
static void bkCentre(const char* s, int y, uint8_t size, uint16_t col) {
  bkText(s, (TFT_W - (int)strlen(s) * 6 * size) / 2, y, size, col);
}

static void bkDrawPiece(int p, int r, int ox, int oy, int sz, uint16_t c) {
  for (int k = 0; k < 4; k++) {
    int cx, cy; bkCell(p, r, k, &cx, &cy);
    bkBlock(ox + cx * sz, oy + cy * sz, sz, c);
  }
}

static void bkDrawField(uint32_t now) {
  const int W = BK_W * BK_CELL, H = BK_H * BK_CELL;
  inst->fillRect(BK_FX, BK_FY, W, H, BLACK);
  for (int y = 1; y < BK_H; y++)                     // faint grid dots
    for (int x = 1; x < BK_W; x++) inst->drawPixel(BK_FX + x * BK_CELL, BK_FY + y * BK_CELL, CYBER_GRID);
  inst->drawRect(BK_FX - 2, BK_FY - 2, W + 4, H + 4, NEON_CYAN);
  inst->drawRect(BK_FX - 3, BK_FY - 3, W + 6, H + 6, bkShade(NEON_CYAN, 0.4f));

  bool flash = bkState == BK_CLEAR && ((now - bkClearAt) / 65) % 2 == 0;
  for (int y = 0; y < BK_H; y++)
    for (int x = 0; x < BK_W; x++) {
      uint8_t v = bkBoard[y][x];
      if (!v) continue;
      uint16_t c = (bkState == BK_CLEAR && bkFull[y]) ? (flash ? WHITE : bkShade(kBkCol[v], 1.3f)) : kBkCol[v];
      if (bkState == BK_OVER) c = bkShade(c, 0.45f);
      bkBlock(BK_FX + x * BK_CELL, BK_FY + y * BK_CELL, BK_CELL, c);
    }
  if (bkState == BK_PLAY || bkState == BK_PAUSE) {
    //  Where it will land: an outline.
    int gy = bkY;
    while (bkFits(bkP, bkR, bkX, gy + 1)) gy++;
    uint16_t gc = bkShade(kBkCol[bkP + 1], 0.55f);
    for (int k = 0; k < 4; k++) {
      int cx, cy; bkCell(bkP, bkR, k, &cx, &cy);
      if (gy + cy >= 0) inst->drawRect(BK_FX + (bkX + cx) * BK_CELL, BK_FY + (gy + cy) * BK_CELL, BK_CELL, BK_CELL, gc);
    }
    for (int k = 0; k < 4; k++) {
      int cx, cy; bkCell(bkP, bkR, k, &cx, &cy);
      if (bkY + cy >= 0) bkBlock(BK_FX + (bkX + cx) * BK_CELL, BK_FY + (bkY + cy) * BK_CELL, BK_CELL, kBkCol[bkP + 1]);
    }
  }
}

static void bkDrawSide() {
  char b[24];
  const int lx = 14;
  struct { const char* lab; uint32_t v; } rows[4] = {
    { "SCORE", bkScore }, { "LINES", bkLines }, { "LEVEL", bkLevel }, { "BEST", bkHi } };
  for (int i = 0; i < 4; i++) {
    int y = 8 + i * 40;
    bkText(rows[i].lab, lx, y, 1, CYBER_DIMTXT);
    snprintf(b, sizeof b, "%lu", (unsigned long)rows[i].v);
    bkText(b, lx, y + 11, 2, i == 0 ? NEON_YELLOW : i == 3 ? NEON_MAGENTA : NEON_CYAN);
  }
  //  Next three, the first full size.
  const int rx = BK_FX + BK_W * BK_CELL + 16;
  bkText("NEXT", rx, 8, 1, CYBER_DIMTXT);
  inst->drawRect(rx - 3, 20, 46, 30, CYBER_GRID);
  { int p = bkNext[0], n = kBkN[p];
    bkDrawPiece(p, 0, rx + (40 - n * 10) / 2, 22 + (p == 0 ? -4 : 3), 10, kBkCol[p + 1]); }
  for (int i = 1; i < 3; i++) {
    int p = bkNext[i];
    bkDrawPiece(p, 0, rx + 6, 58 + (i - 1) * 26, 6, bkShade(kBkCol[p + 1], 0.7f));
  }
  bkText("UP turn", rx, 118, 1, CYBER_DIMTXT);
  bkText("ENTER drop", rx, 130, 1, CYBER_DIMTXT);
  bkText("hold: pause", rx, 142, 1, CYBER_DIMTXT);
}

static void bkDrawTitle(uint32_t now) {
  //  Blocks drifting down behind the title.
  for (int i = 0; i < 14; i++) {
    uint32_t seed = i * 2654435761u;
    int x = (seed >> 8) % (TFT_W - 12);
    int y = (int)(((now / (18 + (seed >> 20) % 20)) + (seed >> 4)) % (TFT_H + 40)) - 20;
    bkDrawPiece((seed >> 12) % 7, (seed >> 16) & 3, x, y, 6, bkShade(kBkCol[(seed >> 12) % 7 + 1], 0.35f));
  }
  bkCentre("NEON", 22, 4, NEON_CYAN);
  bkCentre("BLOCKS", 60, 4, NEON_MAGENTA);
  char b[32]; snprintf(b, sizeof b, "BEST %lu", (unsigned long)bkHi);
  bkCentre(b, 104, 2, NEON_YELLOW);
  if ((now / 500) % 2) bkCentre("ENTER: START", 128, 2, NEON_CYAN);
  bkCentre("LEFT/RIGHT move   UP turn   ENTER drop", 154, 1, CYBER_DIMTXT);
}

void uiViewBlocks() {
  uint32_t now = millis();
  bkUpdate();
  inst->fillScreen(CYBER_BG);
  if (bkState == BK_TITLE) { bkDrawTitle(now); uiBlit(); return; }
  bkDrawField(now);
  bkDrawSide();
  const int W = BK_W * BK_CELL;
  if (bkState == BK_PAUSE) {
    inst->fillRect(BK_FX - 30, 50, W + 60, 76, CYBER_BG);
    inst->drawRect(BK_FX - 30, 50, W + 60, 76, NEON_CYAN);
    bkCentre("PAUSED", 58, 2, NEON_CYAN);
    uiButton(BK_FX - 24, 84, 60, 26, "PLAY", bkPauseSel == 0, NEON_CYAN);
    uiButton(BK_FX + 44, 84, 60, 26, "QUIT", bkPauseSel == 1, NEON_MAGENTA);
  } else if (bkState == BK_OVER) {
    inst->fillRect(BK_FX - 30, 44, W + 60, 88, CYBER_BG);
    inst->drawRect(BK_FX - 30, 44, W + 60, 88, NEON_MAGENTA);
    bkCentre("GAME OVER", 52, 2, NEON_MAGENTA);
    char b[32]; snprintf(b, sizeof b, "%lu", (unsigned long)bkScore);
    bkCentre(b, 74, 2, NEON_YELLOW);
    if (bkNewHi) bkCentre("NEW BEST!", 96, 1, NEON_CYAN);
    bkCentre("ENTER: again", 110, 1, NEON_CYAN);
    bkCentre("LEFT: title", 120, 1, CYBER_DIMTXT);
  }
  uiBlit();
}

//  Press events: only the non-playing screens use them.
static void blocksAction(UiAction a) {
  switch (bkState) {
    case BK_TITLE:
      if (a == ACT_SELECT) bkNewGame();
      else if (a == ACT_BACK) { uiSel = UI_BLOCKS - 1; uiEnter(UI_MENU); }
      break;
    case BK_OVER:
      if (a == ACT_SELECT) bkNewGame();
      else if (a == ACT_BACK) bkState = BK_TITLE;
      break;
    case BK_PAUSE:
      if (a == ACT_BACK || a == ACT_RIGHT) bkPauseSel ^= 1;
      else if (a == ACT_SELECT) {
        if (bkPauseSel == 0) {                   // back to the game
          bkState = BK_PLAY; bkPrevE = true; bkEnterUsed = true; bkDasDir = 0;
          bkFallAt = millis() + bkGravityMs(); if (bkLandAt) bkLandAt = millis();
        } else { bkSaveHi(); bkState = BK_TITLE; }
      }
      break;
    default: break;
  }
}

// ─────────────────────────────────────────────────────────
//  SERVO TESTER — pick a channel, move it with the buttons.
//
//  Goes through servoSet(), so every move passes the channel's saved
//  endpoints (min / mid / max us) exactly as sequences and the web page do:
//  the tester can't push a servo past limits already set for it.
//    UP / DOWN     channel 1..32
//    LEFT / RIGHT  move: a tap is one step, a hold moves faster and faster
//    ENTER         tap: centre   hold: menu (sweep / set power-on / exit)
//  Movement and ENTER read the held pad state each frame; the channel keys
//  and the menu use the press events (UP/DOWN auto-repeat from pcfPoll).
// ─────────────────────────────────────────────────────────
#if SERVO_ENABLE
#define ST_HOLD_MS    600           // ENTER held this long = the menu
#define ST_SWEEP_S    2.5f          // one end to the other while sweeping
#define ST_BAR_X      14
#define ST_BAR_W      292
#define ST_BAR_Y      98

static uint8_t  stCh = 0;
static float    stPos = 127, stMoveT = 0, stSweepPh = 0;
static bool     stSweep = false, stMenu = false;
static bool     stPrevE = true, stEnterUsed = true;
static uint8_t  stMenuSel = 0;
static uint32_t stEnterAt = 0, stLastMs = 0, stMsgMs = 0;
static char     stMsg[32] = "";

static void stText(const char* s, int x, int y, uint8_t size, uint16_t col) {
  inst->setTextSize(size);
  inst->setTextColor(BLACK); inst->setCursor(x + 1, y + 1); inst->print(s);
  inst->setTextColor(col);   inst->setCursor(x, y);         inst->print(s);
}

void servoTestEnter() {
  stPos = servoVal[stCh];
  stSweep = false; stMenu = false; stMoveT = 0; stLastMs = 0;
  stPrevE = true; stEnterUsed = true;          // the ENTER that opened this view
}

static void stSetChannel(int ch) {
  stCh = (uint8_t)((ch + NUM_SERVOS) % NUM_SERVOS);
  stPos = servoVal[stCh];
  stSweep = false; stMoveT = 0;
}

static void stUpdate() {
  uint32_t now = millis();
  float dt = stLastMs ? (now - stLastMs) / 1000.0f : 0.03f;
  if (dt > 0.2f) dt = 0.2f;
  stLastMs = now;
  const uint8_t s = pcfStable;
  auto held = [&](int bit) { return !(s & (1 << bit)); };
  bool L = held(PCF_LEFT), R = held(PCF_RIGHT), E = held(PCF_ENTER);
  if (L || R || E) uiNoteActivity();

  if (stMenu) { stPrevE = E; stMoveT = 0; return; }

  //  ENTER: a tap centres, a hold opens the menu.
  if (E && !stPrevE) { stEnterAt = now; stEnterUsed = false; }
  if (E && !stEnterUsed && now - stEnterAt >= ST_HOLD_MS) {
    stEnterUsed = true; stMenu = true; stMenuSel = 0;
  } else if (!E && stPrevE && !stEnterUsed) {
    stEnterUsed = true; stSweep = false; stPos = 127;
  }
  stPrevE = E;

  //  LEFT / RIGHT: one step on the press, then (after 0.3 s) a glide that
  //  speeds up from 40 to 255 steps a second.
  int dir = (R ? 1 : 0) - (L ? 1 : 0);
  if (dir) {
    stSweep = false;
    if (stMoveT == 0) stPos += dir;
    else if (stMoveT > 0.3f) stPos += dir * fminf(40.0f + (stMoveT - 0.3f) * 180.0f, 255.0f) * dt;
    stMoveT += dt;
  } else stMoveT = 0;

  if (stSweep) {                               // end to end and back
    stSweepPh = fmodf(stSweepPh + dt / ST_SWEEP_S, 2.0f);
    stPos = (stSweepPh < 1 ? stSweepPh : 2 - stSweepPh) * 255.0f;
  }
  stPos = constrain(stPos, 0.0f, 255.0f);
  int v = (int)lroundf(stPos);
  if (v != servoVal[stCh]) servoSet(stCh, v);
}

void uiViewServoTest() {
  stUpdate();
  const int ch = stCh, v = servoVal[ch];
  const uint32_t us = applyEndpoints(v, ch);
  char b[40];

  inst->fillScreen(CYBER_BG);
  ui3DHeader("SERVO TESTER");

  //  Channel, big.
  stText("CH", 14, 36, 2, CYBER_DIMTXT);
  snprintf(b, sizeof b, "%02d", ch + 1);
  stText(b, 42, 32, 4, NEON_CYAN);

  //  Pulse width and value, big, on the right.
  snprintf(b, sizeof b, "%luus", (unsigned long)us);
  stText(b, TFT_W - 14 - (int)strlen(b) * 18, 32, 3, NEON_YELLOW);
  snprintf(b, sizeof b, "%d / 255", v);
  stText(b, TFT_W - 14 - (int)strlen(b) * 6, 62, 1, NEON_CYAN);
  if (stSweep && (millis() / 300) % 2) stText("SWEEP", TFT_W - 14 - 60, 74, 2, NEON_MAGENTA);

  //  The travel bar: min / mid / max endpoints marked, the position as a
  //  bright block, the filled part from the middle out.
  const int by = ST_BAR_Y, bh = 12;
  inst->drawRect(ST_BAR_X - 1, by - 1, ST_BAR_W + 2, bh + 2, CYBER_GRID);
  int mx = ST_BAR_X + ST_BAR_W * 127 / 255, px = ST_BAR_X + ST_BAR_W * v / 255;
  inst->fillRect(min(mx, px), by, abs(px - mx) + 1, bh, 0x0269);
  inst->drawFastVLine(mx, by - 3, bh + 6, CYBER_DIMTXT);
  inst->fillRect(px - 3, by - 3, 7, bh + 6, NEON_CYAN);
  inst->drawRect(px - 3, by - 3, 7, bh + 6, BLACK);
  snprintf(b, sizeof b, "%d", chCfg[ch].epMin); stText(b, ST_BAR_X, by + bh + 4, 1, CYBER_DIMTXT);
  snprintf(b, sizeof b, "%d", chCfg[ch].epMid); stText(b, mx - (int)strlen(b) * 3, by + bh + 4, 1, CYBER_DIMTXT);
  snprintf(b, sizeof b, "%d", chCfg[ch].epMax);
  stText(b, ST_BAR_X + ST_BAR_W - (int)strlen(b) * 6, by + bh + 4, 1, CYBER_DIMTXT);

  //  All 32 at a glance: a small bar each, this one highlighted.
  const int sy = 128, sh = 18;
  for (int i = 0; i < NUM_SERVOS; i++) {
    int x = 16 + i * 9, h = 1 + servoVal[i] * (sh - 1) / 255;
    uint16_t c = i == ch ? NEON_CYAN : (pcaOk[i / 16] ? CYBER_DIMTXT : 0x4000);
    inst->drawRect(x, sy, 8, sh, i == ch ? NEON_CYAN : CYBER_GRID);
    inst->fillRect(x + 1, sy + sh - h, 6, h - 1 > 0 ? h - 1 : 1, c);
  }

  if (millis() - stMsgMs < 2000 && stMsg[0]) stText(stMsg, 16, 152, 1, NEON_YELLOW);
  else stText("UP/DN ch  L/R move  ENTER centre  hold: menu", 16, 152, 1, CYBER_DIMTXT);

  //  The hold-ENTER menu.
  if (stMenu) {
    static const char* const kItem[3] = { "SWEEP", "SET POWER-ON", "EXIT" };
    const int w = 196, x0 = (TFT_W - w) / 2, y0 = 34;
    inst->fillRect(x0, y0, w, 104, CYBER_BG);
    inst->drawRect(x0, y0, w, 104, NEON_CYAN);
    for (int i = 0; i < 3; i++) {
      const char* lab = kItem[i];
      if (i == 0) { snprintf(b, sizeof b, "SWEEP: %s", stSweep ? "ON" : "OFF"); lab = b; }
      uiButton(x0 + 8, y0 + 8 + i * 32, w - 16, 26, lab, stMenuSel == i, i == 2 ? NEON_MAGENTA : NEON_CYAN);
    }
  }
  uiBlit();
}

static void servoTestAction(UiAction a) {
  if (!stMenu) {
    if (a == ACT_PREV)      stSetChannel(stCh - 1);
    else if (a == ACT_NEXT) stSetChannel(stCh + 1);
    return;                                    // LEFT/RIGHT/ENTER: read held, in stUpdate
  }
  switch (a) {
    case ACT_PREV: stMenuSel = (stMenuSel + 2) % 3; break;
    case ACT_NEXT: stMenuSel = (stMenuSel + 1) % 3; break;
    case ACT_BACK: stMenu = false; stEnterUsed = true; break;
    case ACT_SELECT:
      stMenu = false; stEnterUsed = true;      // its release must not centre
      if (stMenuSel == 0) { stSweep = !stSweep; stSweepPh = stPos / 255.0f; }
      else if (stMenuSel == 1) {
        chCfg[stCh].bootVal = servoVal[stCh];
        saveChannelConfig(stCh);
        snprintf(stMsg, sizeof stMsg, "CH %d POWER-ON = %d SAVED", stCh + 1, servoVal[stCh]);
        stMsgMs = millis();
      } else { stSweep = false; uiSel = UI_SERVO - 1; uiEnter(UI_MENU); }
      break;
    default: break;
  }
}
#endif  // SERVO_ENABLE

// ─────────────────────────────────────────────────────────
//  IMU TO SERVO — the board's yaw, pitch and roll drive servos.
//
//  Each axis has: a servo channel (1..32, or OFF), a range (degrees of tilt
//  either side of zero for full servo travel) and a direction. Zero is the
//  board's orientation when the page opens, or when ZERO HERE is pressed.
//  Servos are driven only while this page is open (they hold their last
//  position after), through servoSet() so each channel's saved endpoints
//  still apply. Settings are saved in NVS ("imusv").
//    UP / DOWN   pick a row             LEFT / RIGHT  pick a setting
//    ENTER       edit it: UP/DOWN change, ENTER done
//    LEFT on the first column: back to the menu
// ─────────────────────────────────────────────────────────
#if SERVO_ENABLE
#define IS_ROWS     3               // yaw, pitch, roll
#define IS_COLS     3               // servo, range, direction
#define IS_ROW_Y0   44
#define IS_ROW_H    28

static const char* const kIsAxis[IS_ROWS] = { "YAW", "PITCH", "ROLL" };
static uint8_t  isCh[IS_ROWS]    = { 0, 0, 0 };      // 0 = off, else channel 1..32
static uint8_t  isRange[IS_ROWS] = { 45, 45, 45 };   // degrees each side
static bool     isRev[IS_ROWS]   = { false, false, false };
static float    isRef[IS_ROWS]   = { 0, 0, 0 };      // zero orientation
static float    isVal[IS_ROWS]   = { 127, 127, 127 };// smoothed servo value
static float    isAng[IS_ROWS]   = { 0, 0, 0 };      // angle from zero, degrees
static uint8_t  isRow = 0, isCol = 0;                // row IS_ROWS = the ZERO button
static bool     isEdit = false;
static uint32_t isZeroMs = 0;

static void isText(const char* s, int x, int y, uint8_t size, uint16_t col) {
  inst->setTextSize(size);
  inst->setTextColor(BLACK); inst->setCursor(x + 1, y + 1); inst->print(s);
  inst->setTextColor(col);   inst->setCursor(x, y);         inst->print(s);
}

static float isRaw(int axis) {
  return axis == 0 ? imuYaw : axis == 1 ? imuPitch : imuRoll;
}

static void isZero() {
  for (int i = 0; i < IS_ROWS; i++) isRef[i] = isRaw(i);
  isZeroMs = millis();
}

static void isSave() {
  prefs.begin("imusv", false);
  for (int i = 0; i < IS_ROWS; i++) {
    char k[4];
    k[0] = 'c'; k[1] = '0' + i; k[2] = 0; prefs.putUChar(k, isCh[i]);
    k[0] = 'r'; prefs.putUChar(k, isRange[i]);
    k[0] = 'v'; prefs.putBool(k, isRev[i]);
  }
  prefs.end();
}

void imuServoEnter() {
  prefs.begin("imusv", true);
  for (int i = 0; i < IS_ROWS; i++) {
    char k[4];
    k[0] = 'c'; k[1] = '0' + i; k[2] = 0; isCh[i] = prefs.getUChar(k, 0) % (NUM_SERVOS + 1);
    k[0] = 'r'; isRange[i] = constrain(prefs.getUChar(k, 45), 10, 180);
    k[0] = 'v'; isRev[i] = prefs.getBool(k, false);
  }
  prefs.end();
  isRow = 0; isCol = 0; isEdit = false;
  for (int i = 0; i < IS_ROWS; i++) isVal[i] = isCh[i] ? servoVal[isCh[i] - 1] : 127;
  isZero();                                    // this orientation = centre
}

//  Every frame: angles from zero -> servo values (lightly smoothed) -> servos.
static void isUpdate() {
  if (!imuAlive()) return;
  for (int i = 0; i < IS_ROWS; i++) {
    float a = isRaw(i) - isRef[i];
    while (a > 180) a -= 360;                  // yaw (and roll) wrap
    while (a < -180) a += 360;
    isAng[i] = a;
    float t = constrain(a / isRange[i], -1.0f, 1.0f);
    if (isRev[i]) t = -t;
    float target = 127.5f + t * 127.5f;
    isVal[i] += (target - isVal[i]) * 0.35f;   // a little smoothing against sensor jitter
    if (!isCh[i]) continue;
    int v = constrain((int)lroundf(isVal[i]), 0, 255);
    if (v != servoVal[isCh[i] - 1]) servoSet(isCh[i] - 1, v);
  }
  //  No uiNoteActivity() here: idlePoll() already treats real movement of the
  //  board as activity, so it stays lit while being moved and dims when still.
}

void uiViewImuServo() {
  isUpdate();
  char b[24];
  inst->fillScreen(CYBER_BG);
  ui3DHeader("IMU TO SERVO");

  //  Column headings.
  static const int kColX[IS_COLS] = { 80, 140, 190 };
  static const int kColW[IS_COLS] = { 54, 44, 54 };
  isText("AXIS", 8, 32, 1, CYBER_DIMTXT);
  isText("SERVO", kColX[0] + 2, 32, 1, CYBER_DIMTXT);
  isText("RANGE", kColX[1] + 2, 32, 1, CYBER_DIMTXT);
  isText("DIR", kColX[2] + 2, 32, 1, CYBER_DIMTXT);
  isText("LIVE", 252, 32, 1, CYBER_DIMTXT);

  for (int r = 0; r < IS_ROWS; r++) {
    const int y = IS_ROW_Y0 + r * IS_ROW_H;
    const bool rowSel = r == isRow;
    isText(kIsAxis[r], 8, y + 5, 2, rowSel ? NEON_YELLOW : (isCh[r] ? NEON_CYAN : CYBER_DIMTXT));
    for (int c = 0; c < IS_COLS; c++) {
      if (c == 0) { if (isCh[r]) snprintf(b, sizeof b, "CH%02d", isCh[r]); else snprintf(b, sizeof b, "OFF"); }
      else if (c == 1) snprintf(b, sizeof b, "%d", isRange[r]);
      else snprintf(b, sizeof b, "%s", isRev[r] ? "REV" : "NORM");
      const bool sel = rowSel && c == isCol;
      const int x = kColX[c], w = kColW[c];
      if (sel) inst->fillRoundRect(x, y, w, 24, 4, isEdit ? NEON_YELLOW : NEON_CYAN);
      else inst->drawRoundRect(x, y, w, 24, 4, CYBER_GRID);
      int tx = x + (w - (int)strlen(b) * 12) / 2;
      if (sel) { inst->setTextSize(2); inst->setTextColor(BLACK); inst->setCursor(tx, y + 5); inst->print(b); }
      else isText(b, tx, y + 5, 2, isCh[r] || c == 0 ? NEON_CYAN : CYBER_DIMTXT);
    }
    //  Live: the angle from zero, and the servo position on a small bar.
    const int bx = 250, bw = 62, by = y + 15;
    snprintf(b, sizeof b, "%+.0f", imuAlive() ? isAng[r] : 0.0f);
    isText(b, bx, y + 2, 1, NEON_CYAN);
    inst->drawRect(bx, by, bw, 8, CYBER_GRID);
    inst->drawFastVLine(bx + bw / 2, by - 2, 12, CYBER_DIMTXT);
    int px = bx + 1 + (int)(isVal[r] * (bw - 3) / 255.0f);
    inst->fillRect(px - 1, by - 2, 3, 12, isCh[r] ? NEON_MAGENTA : CYBER_DIMTXT);
  }

  //  ZERO HERE, and the hints / status line.
  uiButton(8, 132, 132, 24, "ZERO HERE", isRow == IS_ROWS, NEON_MAGENTA);
  if (!imuAlive()) isText("IMU SILENT", 152, 140, 1, NEON_RED);
  else if (millis() - isZeroMs < 1500) isText("ZEROED", 152, 140, 1, NEON_YELLOW);
  isText(isEdit ? "UP/DN change   ENTER done"
                : "UP/DN row  L/R setting  ENTER edit  LEFT back",
         8, 161, 1, CYBER_DIMTXT);
  uiBlit();
}

static void imuServoAction(UiAction a) {
  if (isEdit) {                                // changing one setting
    int d = a == ACT_PREV ? 1 : a == ACT_NEXT ? -1 : 0;
    if (d) {
      uint8_t& ch = isCh[isRow];
      if (isCol == 0) ch = (uint8_t)((ch + d + NUM_SERVOS + 1) % (NUM_SERVOS + 1));
      else if (isCol == 1) isRange[isRow] = constrain(isRange[isRow] + d * 5, 10, 180);
      else isRev[isRow] = !isRev[isRow];
      if (isCol == 0 && ch) isVal[isRow] = servoVal[ch - 1];   // pick up where that servo is
    } else if (a == ACT_SELECT || a == ACT_BACK || a == ACT_RIGHT) {
      isEdit = false; isSave();
    }
    return;
  }
  switch (a) {
    case ACT_PREV: isRow = (isRow + IS_ROWS) % (IS_ROWS + 1); break;
    case ACT_NEXT: isRow = (isRow + 1) % (IS_ROWS + 1); break;
    case ACT_RIGHT: if (isRow < IS_ROWS && isCol < IS_COLS - 1) isCol++; break;
    case ACT_BACK:
      if (isRow < IS_ROWS && isCol > 0) isCol--;
      else { uiSel = UI_IMUSERVO - 1; uiEnter(UI_MENU); }
      break;
    case ACT_SELECT:
      if (isRow == IS_ROWS) isZero();
      else isEdit = true;
      break;
    default: break;
  }
}
#endif  // SERVO_ENABLE

// ─────────────────────────────────────────────────────────
//  GPS MAP — MapTiler raster tiles around the GPS position.
//
//  256 px PNG tiles from https://api.maptiler.com/maps/<style>/256/z/x/y.png
//  with the user's own MapTiler key, fetched on a task of their own while the
//  GPS page is open. (PNG, not JPEG: MapTiler's JPEG tiles are progressive,
//  which JPEGDEC only decodes as a 1/8-size thumbnail.) Every tile fetched is
//  kept on the SD card (/MAPS/<style>/<z>/<x>/<y>.png), so places already
//  seen also work with no internet. Up to 8 decoded tiles live in PSRAM.
//
//  The key: /MAPS/maptiler_key.txt on the card, or "map key <KEY>" on the
//  console (stored in NVS, which wins). Requests send the User-Agent
//  GM_USER_AGENT, so the key can be restricted to this board in MapTiler
//  Cloud (Allowed User-Agent header). The bottom strip shows the
//  button functions. (MapTiler's terms ask for the credit line
//  "(c) MapTiler (c) OpenStreetMap contributors" on the map; it was removed
//  from the screen at the owner's request.)
//
//  Centre: the live GPS fix; without one, the last fix this session, then
//  the plane radar's saved home.
//    UP / DOWN  zoom in / out      RIGHT  map style (streets, outdoor, satellite)
//    ENTER      map -> GPS details -> sky (satellites + signal)   LEFT  back
// ─────────────────────────────────────────────────────────
#if GPS_ENABLE
#include <new>                                  // placement new: the decoder lives in PSRAM
#define GM_USER_AGENT  "32ServoController/1.0"
#define GM_SLOTS       8                      // decoded tiles kept in PSRAM
#define GM_TILE_PX     256
#define GM_IMG_MAX     (256 * 1024)           // satellite PNGs run large
#define GM_ZMIN        3
#define GM_ZMAX        18
#define GM_TRACK       300                    // breadcrumb points

//  Each style has a list of map IDs to try: if MapTiler answers 400/404 for
//  one, the next is tried ("map style <id>" on the console overrides).
static const char* const kGmStyleName[3] = { "STREETS", "OUTDOOR", "SATELLITE" };
static const char* const kGmStyleIds[3][3] = {
  { "streets-v2", "streets-v4", "streets" },
  { "outdoor-v2", "outdoor-v4", "outdoor" },
  { "satellite",  "hybrid",     nullptr   },
};
static uint8_t  gmIdTry[3] = { 0, 0, 0 };     // which ID of each style is in use
static char     gmCustomId[24] = "";          // console override, for the current style

static char     gmKey[96] = "";
static uint8_t  gmStyle = 0, gmZoom = 15;
static uint8_t  gmPage = 0;                   // ENTER cycles: 0 map, 1 details, 2 sky
static uint32_t gmEnterMs = 0;
static volatile bool gmRun = false, gmTaskAlive = false;
static volatile int  gmHttp = 0;              // last HTTP status (0 = none yet)
static volatile uint32_t gmFetched = 0, gmFromCard = 0;
static double   gmLastLat = 0, gmLastLon = 0; // last good fix this session
static bool     gmHaveLast = false;

//  Tile cache. key = style << 48 | z << 40 | x << 20 | y.
static uint64_t gmSlotKey[GM_SLOTS];
static volatile uint8_t gmSlotState[GM_SLOTS];      // 0 empty, 1 loading, 2 ready, 3 failed
static uint32_t gmSlotUsed[GM_SLOTS];
static uint16_t* gmSlotPx[GM_SLOTS];
static uint8_t*  gmJpg = nullptr;                    // download / card buffer (one tile file)
static PNG*      gmPng = nullptr;                    // its own decoder, in PSRAM
static SemaphoreHandle_t gmLock = nullptr;

//  The tiles the screen wants now (written by the UI, read by the task).
static uint64_t gmWant[6];
static volatile uint8_t gmWantN = 0;

//  Breadcrumb track of GPS fixes.
static float    gmTrLat[GM_TRACK], gmTrLon[GM_TRACK];
static uint16_t gmTrN = 0, gmTrHead = 0;

static inline uint64_t gmKeyOf(int st, int z, uint32_t x, uint32_t y) {
  return ((uint64_t)st << 48) | ((uint64_t)z << 40) | ((uint64_t)x << 20) | y;
}

static const char* gmStyleId(int st) {
  if (st == gmStyle && gmCustomId[0]) return gmCustomId;
  const char* id = kGmStyleIds[st][gmIdTry[st]];
  return id ? id : kGmStyleIds[st][0];
}

//  Web Mercator: lat/lon -> global pixel at zoom z.
static void gmProject(double lat, double lon, int z, double* px, double* py) {
  double n = (double)(1UL << z) * GM_TILE_PX;
  double s = sin(lat * DEG_TO_RAD);
  if (s > 0.9999) s = 0.9999;
  if (s < -0.9999) s = -0.9999;
  *px = (lon + 180.0) / 360.0 * n;
  *py = (0.5 - log((1 + s) / (1 - s)) / (4 * PI)) * n;
}

static void gmLoadKey() {
  prefs.begin("gmap", true);
  String k = prefs.getString("key", "");
  gmStyle = prefs.getUChar("style", 0) % 3;
  gmZoom = constrain(prefs.getUChar("zoom", 15), GM_ZMIN, GM_ZMAX);
  prefs.end();
  if (!k.length() && sdMounted) {                    // else the card's key file
    File f = SD_MMC.open("/MAPS/maptiler_key.txt");
    if (f) { k = f.readString(); f.close(); }
  }
  k.trim();
  snprintf(gmKey, sizeof gmKey, "%s", k.c_str());
}

static void gmSavePrefs() {
  prefs.begin("gmap", false);
  prefs.putUChar("style", gmStyle); prefs.putUChar("zoom", gmZoom);
  prefs.end();
}

//  The centre: live fix, else last fix, else the radar's saved home.
static bool gmCentre(double* lat, double* lon, int* src) {
  if (gpsAlive()) { *lat = gpsLat; *lon = gpsLon; *src = 0; return true; }
  if (gmHaveLast) { *lat = gmLastLat; *lon = gmLastLon; *src = 1; return true; }
  if (radSavedHas) { *lat = radSavedLat; *lon = radSavedLon; *src = 2; return true; }
  return false;
}

// ── Tile fetching (task) ──
//  PNGdec hands over one row at a time; it converts to the canvas's native
//  RGB565 straight into the tile's slot.
static int gmPngDraw(PNGDRAW* d) {
  if (d->y >= 0 && d->y < GM_TILE_PX && d->iWidth == GM_TILE_PX)
    gmPng->getLineAsRGB565(d, (uint16_t*)d->pUser + d->y * GM_TILE_PX, PNG_RGB565_LITTLE_ENDIAN, 0xFFFFFFFF);
  return 1;
}

static bool gmDecode(int slot, size_t len) {
  if (gmPng->openRAM(gmJpg, (int)len, gmPngDraw) != PNG_SUCCESS) return false;
  bool ok = gmPng->getWidth() == GM_TILE_PX && gmPng->getHeight() == GM_TILE_PX &&
            gmPng->decode(gmSlotPx[slot], 0) == PNG_SUCCESS;
  gmPng->close();
  return ok;
}

static void gmPath(char* out, size_t n, int st, int z, uint32_t x, uint32_t y) {
  snprintf(out, n, "/MAPS/%s/%d/%lu/%lu.png", gmStyleId(st), z, (unsigned long)x, (unsigned long)y);
}

static void gmMkdirs(const char* path) {               // every folder of a file path
  char p[96]; snprintf(p, sizeof p, "%s", path);
  for (char* c = p + 1; *c; c++)
    if (*c == '/') { *c = 0; if (!SD_MMC.exists(p)) SD_MMC.mkdir(p); *c = '/'; }
}

//  Fill one tile: from the card if it is there, else from MapTiler (and
//  then onto the card). Returns the length in gmJpg, 0 on failure.
static size_t gmGetTile(int st, int z, uint32_t x, uint32_t y, WiFiClientSecure& tls, HTTPClient& http) {
  char path[96]; gmPath(path, sizeof path, st, z, x, y);
  if (sdMounted) {
    File f = SD_MMC.open(path);
    if (f) {
      size_t n = f.size();
      if (n > 0 && n <= GM_IMG_MAX && f.read(gmJpg, n) == n) { f.close(); gmFromCard++; return n; }
      f.close();
    }
  }
  if (!gmKey[0] || WiFi.status() != WL_CONNECTED) return 0;

  for (int attempt = 0; attempt < 3; attempt++) {      // style-ID fallbacks
    char url[200];
    snprintf(url, sizeof url, "https://api.maptiler.com/maps/%s/256/%d/%lu/%lu.png?key=%s",
             gmStyleId(st), z, (unsigned long)x, (unsigned long)y, gmKey);
    if (!http.begin(tls, url)) { gmHttp = -1; return 0; }
    int code = http.GET();
    gmHttp = code;
    if (code == 200) {
      int len = http.getSize();
      WiFiClient* s = http.getStreamPtr();
      size_t got = 0;
      uint32_t t0 = millis();
      while (s && (len < 0 || (int)got < len) && got < GM_IMG_MAX && millis() - t0 < 8000) {
        int a = s->available();
        if (a > 0) got += s->readBytes(gmJpg + got, min((size_t)a, (size_t)(GM_IMG_MAX - got)));
        else if (!s->connected()) break;
        else delay(2);
      }
      http.end();
      if (got == 0 || (len > 0 && (int)got != len)) return 0;
      gmFetched++;
      if (sdMounted) {                                   // keep it for next time
        gmPath(path, sizeof path, st, z, x, y);
        gmMkdirs(path);
        File f = SD_MMC.open(path, FILE_WRITE);
        if (f) { f.write(gmJpg, got); f.close(); }
      }
      return got;
    }
    http.end();
    //  400/404: this style ID isn't one MapTiler knows - try the next.
    if ((code == 400 || code == 404) && !gmCustomId[0] &&
        gmIdTry[st] < 2 && kGmStyleIds[st][gmIdTry[st] + 1]) { gmIdTry[st]++; continue; }
    return 0;
  }
  return 0;
}

static void gmTask(void*) {
  gmTaskAlive = true;
  WiFiClientSecure tls;
  tls.setInsecure();                                    // public map tiles; the key is in the URL
  HTTPClient http;
  http.setReuse(true);                                  // one TLS session for many tiles
  http.setTimeout(8000);
  http.setUserAgent(GM_USER_AGENT);
  while (gmRun) {
    //  The first wanted tile that is not in the cache yet.
    int slot = -1; uint64_t key = 0;
    xSemaphoreTake(gmLock, portMAX_DELAY);
    for (int w = 0; w < gmWantN && slot < 0; w++) {
      bool have = false;
      for (int s = 0; s < GM_SLOTS; s++)
        if (gmSlotState[s] && gmSlotKey[s] == gmWant[w]) { have = true; break; }
      if (have) continue;
      //  Evict the least recently drawn slot not on screen.
      int best = -1;
      for (int s = 0; s < GM_SLOTS; s++) {
        bool onScreen = false;
        for (int v = 0; v < gmWantN; v++) if (gmSlotState[s] && gmSlotKey[s] == gmWant[v]) onScreen = true;
        if (onScreen) continue;
        if (best < 0 || !gmSlotState[s] || gmSlotUsed[s] < gmSlotUsed[best]) best = s;
        if (!gmSlotState[s]) break;
      }
      if (best >= 0) { slot = best; key = gmWant[w]; gmSlotKey[slot] = key; gmSlotState[slot] = 1; }
    }
    xSemaphoreGive(gmLock);

    if (slot < 0) { vTaskDelay(pdMS_TO_TICKS(50)); continue; }
    int st = (int)(key >> 48) & 0xFF, z = (int)(key >> 40) & 0xFF;
    uint32_t x = (uint32_t)(key >> 20) & 0xFFFFF, y = (uint32_t)key & 0xFFFFF;
    size_t n = gmGetTile(st, z, x, y, tls, http);
    gmSlotState[slot] = (n && gmDecode(slot, n)) ? 2 : 3;
    if (gmSlotState[slot] == 3) vTaskDelay(pdMS_TO_TICKS(300));   // don't hammer on errors
  }
  http.end();
  gmTaskAlive = false;
  vTaskDelete(nullptr);
}

void gmapEnter() {
  gmLoadKey();
  gmPage = 0; gmEnterMs = millis();
  if (!gmLock) gmLock = xSemaphoreCreateMutex();
  if (!gmJpg) gmJpg = (uint8_t*)ps_malloc(GM_IMG_MAX);
  if (!gmPng) { void* m = ps_malloc(sizeof(PNG)); if (m) gmPng = new (m) PNG(); }
  for (int s = 0; s < GM_SLOTS; s++) {
    if (!gmSlotPx[s]) gmSlotPx[s] = (uint16_t*)ps_malloc(GM_TILE_PX * GM_TILE_PX * 2);
    if (gmSlotState[s] != 2) gmSlotState[s] = 0;      // a half-fetched tile starts over
  }
  if (!gmJpg || !gmPng || !gmSlotPx[GM_SLOTS - 1]) { Serial.println("MAP: no PSRAM"); return; }
  gmRun = true;
  if (!gmTaskAlive) xTaskCreatePinnedToCore(gmTask, "map", 16384, nullptr, 1, nullptr, 0);
}

void gmapLeave() { gmRun = false; gmWantN = 0; }

// ── Drawing ──
static void gmText(const char* s, int x, int y, uint16_t col) {
  inst->setTextSize(1);
  inst->setTextColor(BLACK); inst->setCursor(x + 1, y + 1); inst->print(s);
  inst->setTextColor(col);   inst->setCursor(x, y);         inst->print(s);
}

static void gmTrackAdd(double lat, double lon) {
  if (gmTrN) {
    int last = (gmTrHead + GM_TRACK - 1) % GM_TRACK;
    double dy = (lat - gmTrLat[last]) * 111320.0;
    double dx = (lon - gmTrLon[last]) * 111320.0 * cos(lat * DEG_TO_RAD);
    if (dx * dx + dy * dy < 5.0 * 5.0) return;          // moved under 5 m
  }
  gmTrLat[gmTrHead] = (float)lat; gmTrLon[gmTrHead] = (float)lon;
  gmTrHead = (gmTrHead + 1) % GM_TRACK;
  if (gmTrN < GM_TRACK) gmTrN++;
}

void gmapView() {
  inst->fillScreen(CYBER_BG);
  if (gpsAlive()) { gmLastLat = gpsLat; gmLastLon = gpsLon; gmHaveLast = true; gmTrackAdd(gpsLat, gpsLon); }

  double lat, lon; int src;
  if (!gmCentre(&lat, &lon, &src)) {
    uiCentreText("NO POSITION YET", 2, NEON_YELLOW);
    gmText("Waiting for a GPS fix (or set a radar home)", 34, 120, CYBER_DIMTXT);
    uiBlit(); return;
  }
  if (!gmKey[0]) {
    gmText("THE MAP NEEDS A MAPTILER KEY", 76, 40, NEON_YELLOW);
    gmText("Put it in /MAPS/maptiler_key.txt on the", 44, 66, NEON_CYAN);
    gmText("SD card, or type on the console:", 64, 80, NEON_CYAN);
    gmText("map key YOUR_KEY", 112, 98, NEON_CYAN);
    gmText("ENTER: GPS details   LEFT: back", 70, 140, CYBER_DIMTXT);
    uiBlit(); return;
  }

  //  Which tiles cover the screen, centred on the position.
  double cx, cy; gmProject(lat, lon, gmZoom, &cx, &cy);
  const double left = cx - TFT_W / 2, top = cy - TFT_H / 2;
  const uint32_t nTiles = 1UL << gmZoom;
  int tx0 = (int)floor(left / GM_TILE_PX), ty0 = (int)floor(top / GM_TILE_PX);
  int tx1 = (int)floor((left + TFT_W - 1) / GM_TILE_PX), ty1 = (int)floor((top + TFT_H - 1) / GM_TILE_PX);

  uint64_t want[6]; int nw = 0;
  for (int ty = ty0; ty <= ty1; ty++)
    for (int tx = tx0; tx <= tx1 && nw < 6; tx++)
      if (ty >= 0 && ty < (int)nTiles)
        want[nw++] = gmKeyOf(gmStyle, gmZoom, (uint32_t)((tx % (int)nTiles + nTiles) % nTiles), (uint32_t)ty);

  uint16_t* fb = inst->getBuffer();
  int loading = 0, failed = 0;
  xSemaphoreTake(gmLock, portMAX_DELAY);
  memcpy(gmWant, want, sizeof want); gmWantN = (uint8_t)nw;
  int k = 0;
  for (int ty = ty0; ty <= ty1; ty++)
    for (int tx = tx0; tx <= tx1; tx++) {
      if (ty < 0 || ty >= (int)nTiles) continue;
      uint64_t key = want[k++];
      int dx = (int)lround(tx * (double)GM_TILE_PX - left), dy = (int)lround(ty * (double)GM_TILE_PX - top);
      int slot = -1;
      for (int s = 0; s < GM_SLOTS; s++) if (gmSlotState[s] && gmSlotKey[s] == key) { slot = s; break; }
      if (slot < 0 || gmSlotState[slot] != 2) { if (slot >= 0 && gmSlotState[slot] == 3) failed++; else loading++; continue; }
      gmSlotUsed[slot] = millis();
      const uint16_t* src = gmSlotPx[slot];
      int x0 = max(0, dx), x1 = min(TFT_W, dx + GM_TILE_PX);
      int y0 = max(0, dy), y1 = min(TFT_H, dy + GM_TILE_PX);
      for (int y = y0; y < y1; y++)
        memcpy(&fb[y * TFT_W + x0], &src[(y - dy) * GM_TILE_PX + (x0 - dx)], (x1 - x0) * 2);
    }
  xSemaphoreGive(gmLock);

  //  The track, then the position marker.
  if (gmTrN > 1) {
    int px0 = 0, py0 = 0;
    for (int i = 0; i < gmTrN; i++) {
      int idx = (gmTrHead + GM_TRACK - gmTrN + i) % GM_TRACK;
      double tx, ty; gmProject(gmTrLat[idx], gmTrLon[idx], gmZoom, &tx, &ty);
      int px = (int)lround(tx - left), py = (int)lround(ty - top);
      if (i) { inst->drawLine(px0, py0, px, py, NEON_MAGENTA); inst->drawLine(px0, py0 + 1, px, py + 1, NEON_MAGENTA); }
      px0 = px; py0 = py;
    }
  }
  const int mx = TFT_W / 2, my = TFT_H / 2;
  if (src == 0) {
    uint32_t ph = millis() % 1500;
    inst->drawCircle(mx, my, 6 + (int)(ph * 12 / 1500), NEON_CYAN);
    inst->fillCircle(mx, my, 5, BLACK);
    inst->fillCircle(mx, my, 4, NEON_CYAN);
  } else {                                              // not a live fix
    inst->drawCircle(mx, my, 6, BLACK); inst->drawCircle(mx, my, 5, NEON_MAGENTA);
    inst->drawFastHLine(mx - 9, my, 19, NEON_MAGENTA); inst->drawFastVLine(mx, my - 9, 19, NEON_MAGENTA);
  }

  //  Corners: zoom + style; fix state; position; the button strip.
  char b[48];
  snprintf(b, sizeof b, "Z%d %s", gmZoom, kGmStyleName[gmStyle]);
  gmText(b, 14, 5, NEON_CYAN);
  if (src == 0) snprintf(b, sizeof b, "GPS %u SATS", gpsSats);
  else snprintf(b, sizeof b, "%s", src == 1 ? "LAST FIX" : "RADAR HOME");
  gmText(b, TFT_W - 14 - 6 * (int)strlen(b), 5, src == 0 ? NEON_GREEN : NEON_YELLOW);
  snprintf(b, sizeof b, "%.5f %.5f", lat, lon);
  gmText(b, 14, TFT_H - 22, NEON_CYAN);
  if (loading || failed) {
    if (failed && gmHttp == 401) snprintf(b, sizeof b, "KEY NOT VALID (401)");
    else if (failed && gmHttp == 403) snprintf(b, sizeof b, "KEY REFUSED (403) - check its User-Agent");
    else if (WiFi.status() != WL_CONNECTED) snprintf(b, sizeof b, "OFFLINE - card tiles only");
    else if (failed) snprintf(b, sizeof b, "TILE ERROR %d", gmHttp);
    else snprintf(b, sizeof b, "LOADING %d", loading);
    gmText(b, TFT_W - 14 - 6 * (int)strlen(b), 18, failed ? NEON_RED : NEON_YELLOW);
  }
  inst->fillRect(0, TFT_H - 11, TFT_W, 11, BLACK);      // button strip
  gmText("UP/DN zoom  RIGHT style  ENTER details", 46, TFT_H - 9, WHITE);
  uiBlit();
}

uint8_t gmapPage() { return gmPage; }

static void gpsAction(UiAction a) {
  switch (a) {
    case ACT_BACK:   uiSel = UI_GPS - 1; uiEnter(UI_MENU); return;
    case ACT_SELECT: gmPage = (gmPage + 1) % 3; gmEnterMs = gmPage ? 0 : millis(); return;
    case ACT_PREV:   if (!gmPage && gmZoom < GM_ZMAX) { gmZoom++; gmSavePrefs(); } return;
    case ACT_NEXT:   if (!gmPage && gmZoom > GM_ZMIN) { gmZoom--; gmSavePrefs(); } return;
    case ACT_RIGHT:  if (!gmPage) { gmStyle = (gmStyle + 1) % 3; gmCustomId[0] = 0; gmSavePrefs(); } return;
    default: return;
  }
}

//  Console "map [key <KEY> | style <id> | clear]".
void mapConsole(const char* arg) {
  while (*arg == ' ') arg++;
  if (!strncmp(arg, "key", 3)) {
    const char* k = arg + 3; while (*k == ' ') k++;
    if (*k) {
      prefs.begin("gmap", false); prefs.putString("key", k); prefs.end();
      snprintf(gmKey, sizeof gmKey, "%s", k);
      Serial.println("map: key saved");
    }
  } else if (!strncmp(arg, "style", 5)) {
    const char* id = arg + 5; while (*id == ' ') id++;
    snprintf(gmCustomId, sizeof gmCustomId, "%s", id);
    Serial.printf("map: style ID for %s is now %s\n", kGmStyleName[gmStyle], *id ? id : gmStyleId(gmStyle));
  } else if (!strcmp(arg, "clear")) {
    prefs.begin("gmap", false); prefs.remove("key"); prefs.end();
    gmKey[0] = 0; Serial.println("map: stored key removed (the card's key file still counts)");
  }
  size_t kl = strlen(gmKey);
  Serial.printf("map: key %s%s | style %s (%s) | zoom %d | %lu fetched, %lu from card | last HTTP %d\n",
                kl ? "set, ends ..." : "NOT SET", kl > 4 ? gmKey + kl - 4 : "",
                kGmStyleName[gmStyle], gmStyleId(gmStyle), gmZoom,
                (unsigned long)gmFetched, (unsigned long)gmFromCard, gmHttp);
}
#endif  // GPS_ENABLE

// ─────────────────────────────────────────────────────────
//  CLOCK — the time from the GPS.
//
//  The receiver sends UTC (GGA) and the date (RMC) once a second, even
//  before it has a position. That is turned into local time with a POSIX
//  time-zone rule, so daylight saving switches by itself. Between sentences
//  the seconds run on millis(). The board's own clock is set from it too
//  (once a minute), so anything else that asks for the time gets it.
//    UP / DOWN  time zone     ENTER  12 / 24 hour     LEFT  back
// ─────────────────────────────────────────────────────────
static const struct { const char* name; const char* tz; } kClockZones[] = {
  { "UTC",            "UTC0" },
  { "EASTERN",        "EST5EDT,M3.2.0,M11.1.0" },
  { "CENTRAL",        "CST6CDT,M3.2.0,M11.1.0" },
  { "MOUNTAIN",       "MST7MDT,M3.2.0,M11.1.0" },
  { "ARIZONA",        "MST7" },
  { "PACIFIC",        "PST8PDT,M3.2.0,M11.1.0" },
  { "ALASKA",         "AKST9AKDT,M3.2.0,M11.1.0" },
  { "HAWAII",         "HST10" },
  { "UK",             "GMT0BST,M3.5.0/1,M10.5.0" },
  { "CENTRAL EUROPE", "CET-1CEST,M3.5.0,M10.5.0/3" },
  { "INDIA",          "IST-5:30" },
  { "JAPAN",          "JST-9" },
  { "SYDNEY",         "AEST-10AEDT,M10.1.0,M4.1.0/3" },
};
#define CLOCK_NZONES ((int)(sizeof(kClockZones) / sizeof(kClockZones[0])))
static uint8_t  clockZone = 2;                 // CENTRAL; NVS "clock"/"tz"
static bool     clock24 = false;               // NVS "clock"/"h24"
static bool     clockLoaded = false;
static uint32_t clockSetSysMs = 0;

static void clockLoad() {
  if (clockLoaded) return;
  prefs.begin("clock", true);
  clockZone = prefs.getUChar("tz", 2) % CLOCK_NZONES;
  clock24   = prefs.getBool("h24", false);
  prefs.end();
  clockLoaded = true;
}
static void clockSave() {
  prefs.begin("clock", false);
  prefs.putUChar("tz", clockZone); prefs.putBool("h24", clock24);
  prefs.end();
}

//  Days since 1970-01-01 for a civil date (Howard Hinnant's algorithm).
static int32_t clockDays(int y, int m, int d) {
  y -= m <= 2;
  const int32_t era = (y >= 0 ? y : y - 399) / 400;
  const int32_t yoe = y - era * 400;
  const int32_t doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
  const int32_t doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
  return era * 146097 + doe - 719468;
}

static int clockTwo(const char* p) { return (p[0] - '0') * 10 + (p[1] - '0'); }

//  UTC now from the GPS, or 0 if it has not sent a believable time + date.
//  *ageMs: how long since the last sentence (the seconds run on meanwhile).
static time_t clockGpsNow(uint32_t* ageMs) {
  if (strlen(gpsUTC) < 6 || strlen(gpsDate) < 6) return 0;
  const int hh = clockTwo(gpsUTC), mi = clockTwo(gpsUTC + 2), ss = clockTwo(gpsUTC + 4);
  const int dd = clockTwo(gpsDate), mo = clockTwo(gpsDate + 2), yy = 2000 + clockTwo(gpsDate + 4);
  if (yy < 2024 || mo < 1 || mo > 12 || dd < 1 || dd > 31 || hh > 23 || mi > 59 || ss > 60) return 0;
  const uint32_t age = millis() - gpsUTCMs;
  if (ageMs) *ageMs = age;
  return (time_t)clockDays(yy, mo, dd) * 86400 + hh * 3600 + mi * 60 + ss + age / 1000;
}

static void clockCentre(const char* t, int y, int size, uint16_t col) {
  inst->setTextSize(size); inst->setTextColor(col);
  inst->setCursor((TFT_W - (int)strlen(t) * 6 * size) / 2, y);
  inst->print(t);
}

void uiViewClock() {
  clockLoad();
  static uint32_t lastPoll = 0;
  if (millis() - lastPoll >= 100) { lastPoll = millis(); gpsPoll(); }
  inst->fillScreen(CYBER_BG);
  uiFrame(CYBER_GRID);

  uint32_t age = 0;
  const time_t now = clockGpsNow(&age);
  if (now && (!clockSetSysMs || millis() - clockSetSysMs > 60000)) {   // the board's clock follows the GPS
    struct timeval tv = { now, 0 }; settimeofday(&tv, nullptr);
    clockSetSysMs = millis();
  }

  //  Header: CLOCK, and where the time comes from.
  inst->setTextSize(2); inst->setTextColor(NEON_MAGENTA);
  inst->setCursor(16, 8); inst->print("CLOCK");
  char b[48];
  uint16_t sc;
  if (!gpsBytes)         { snprintf(b, sizeof b, "NO GPS");                sc = NEON_RED; }
  else if (!now)         { snprintf(b, sizeof b, "GPS: WAITING FOR TIME"); sc = NEON_YELLOW; }
  else if (age > 10000)  { snprintf(b, sizeof b, "GPS LOST %lu MIN AGO", (unsigned long)(age / 60000)); sc = NEON_YELLOW; }
  else if (gpsAlive())   { snprintf(b, sizeof b, "GPS TIME  %u SATS", gpsSats); sc = NEON_GREEN; }
  else                   { snprintf(b, sizeof b, "GPS TIME  NO FIX");      sc = NEON_GREEN; }
  inst->setTextSize(1); inst->setTextColor(sc);
  inst->setCursor(304 - 6 * (int)strlen(b), 12); inst->print(b);

  if (!now) {
    clockCentre("--:--", 42, 6, CYBER_GRID);
    if (!gpsBytes) {
      clockCentre("NO GPS", 102, 2, NEON_RED);
      clockCentre("connect the GNSS module (I2C 0x42)", 124, 1, CYBER_DIMTXT);
    } else {
      clockCentre("WAITING FOR GPS TIME", 102, 2, NEON_YELLOW);
      clockCentre("needs one satellite - try near a window", 124, 1, CYBER_DIMTXT);
    }
  } else {
    setenv("TZ", kClockZones[clockZone].tz, 1); tzset();
    struct tm lt; localtime_r(&now, &lt);

    //  HH:MM big, :SS and AM/PM beside it, the whole row centred.
    int h = lt.tm_hour;
    if (!clock24) { h %= 12; if (!h) h = 12; }
    char hm[8], sec[4];
    snprintf(hm, sizeof hm, clock24 ? "%02d:%02d" : "%d:%02d", h, lt.tm_min);
    snprintf(sec, sizeof sec, ":%02d", lt.tm_sec);
    const int wHm = (int)strlen(hm) * 36, wSec = 3 * 18, gap = 6;
    const int x0 = (TFT_W - (wHm + gap + wSec)) / 2, y0 = 40;
    inst->setTextSize(6); inst->setTextColor(NEON_CYAN);
    inst->setCursor(x0, y0); inst->print(hm);
    inst->setTextSize(3); inst->setTextColor(NEON_MAGENTA);
    inst->setCursor(x0 + wHm + gap, y0 + 24); inst->print(sec);
    if (!clock24) {
      inst->setTextSize(2); inst->setTextColor(NEON_YELLOW);
      inst->setCursor(x0 + wHm + gap + 6, y0); inst->print(lt.tm_hour < 12 ? "AM" : "PM");
    }

    static const char* const kDay[] = { "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY" };
    static const char* const kMon[] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };
    snprintf(b, sizeof b, "%s %s %d %d", kDay[lt.tm_wday], kMon[lt.tm_mon], lt.tm_mday, 1900 + lt.tm_year);
    clockCentre(b, 100, 2, NEON_GREEN);

    //  Zone, its abbreviation and its offset from UTC right now.
    const int32_t off = (int32_t)(((time_t)clockDays(1900 + lt.tm_year, lt.tm_mon + 1, lt.tm_mday) * 86400
                         + lt.tm_hour * 3600 + lt.tm_min * 60 + lt.tm_sec) - now);
    char abbr[8]; strftime(abbr, sizeof abbr, "%Z", &lt);
    const int ao = abs(off);
    snprintf(b, sizeof b, "%s  %s  UTC%c%02d:%02d", kClockZones[clockZone].name, abbr,
             off < 0 ? '-' : '+', ao / 3600, (ao / 60) % 60);
    clockCentre(b, 124, 1, CYBER_DIMTXT);
  }
  clockCentre("UP/DN zone   ENTER 12/24h   LEFT back", TFT_H - 18, 1, CYBER_DIMTXT);
  uiScanlines();
  uiBlit();
}

static void clockAction(UiAction a) {
  clockLoad();
  switch (a) {
    case ACT_BACK:   uiSel = UI_CLOCK - 1; uiEnter(UI_MENU); return;
    case ACT_PREV:   clockZone = (clockZone + CLOCK_NZONES - 1) % CLOCK_NZONES; clockSave(); return;
    case ACT_NEXT:   clockZone = (clockZone + 1) % CLOCK_NZONES; clockSave(); return;
    case ACT_SELECT: clock24 = !clock24; clockSave(); return;
    case ACT_RIGHT:  saveJpeg(); return;
    default: return;
  }
}

// ─────────────────────────────────────────────────────────
//  AUDIO — MUSIC PLAYER and SOUND RECORDER
//
//  Two MAX98357A amps and a DMM-4026 I2S MEMS mic (v6 board) share one
//  I2S port in full duplex, on the four GPIOs nothing else uses (the
//  UART0 pins are free because the console is on USB CDC):
//    BCLK  GPIO 44  -> amp BCLK + mic SCK   (U0RXD)
//    LRC   GPIO 3   -> amp LRC  + mic WS
//    DIN   GPIO 45  -> amp DIN   (strapping pin: only ever an ESP output)
//    DOUT  GPIO 43  <- mic SD    (U0TXD; R3 100k to GND on the board)
//  The bench rig before v6 had BCLK / DOUT the other way round (43 / 44).
//  32-bit stereo slots at 44.1 kHz: BCLK 2.82 MHz, inside the mics' range.
//  Pin drive 2 by default: on the v6 PCB, 3 made the speakers crackle and
//  0-1 corrupt the mic data (the jumper-wire bench rig needed 3).
//  "audio drive N" on the console changes it until the next reboot.
//
//  One task owns the port. Every 5.8 ms it reads a block from the mic and
//  writes a block to the amp: music (MP3 / WAV, ESP8266Audio), a recording
//  being played back, or silence. Recording goes mic -> PSRAM ring -> a
//  writer task -> /REC/RECnnn.WAV (16-bit mono), so a slow card write never
//  drops audio. With nothing to do the port stops; the amp mutes itself
//  without clocks.
//
//  AUDIO_PINS 0 (near the top) leaves all four pins alone: the "port" is a
//  timer that paces the decoder in real time and hands back silence.
//
//  MUSIC PLAYER (/MUSIC, then the card root, then /REC; .mp3 and .wav):
//    ENTER play / pause   RIGHT next track   UP / DOWN volume   LEFT back
//    Music keeps playing on other screens ("music stop" on the console).
//  SOUND RECORDER:
//    ENTER record / stop   RIGHT play the last recording   UP / DOWN gain
// ─────────────────────────────────────────────────────────
#if AUDIO_ENABLE
#define AUD_BCLK       44
#define AUD_LRC        3
#define AUD_DIN        45
#define AUD_DOUT       43
#define AUD_RATE       44100
#define AUD_BLK        256                     // frames per block, 5.8 ms
#define AUD_MAX_TRACKS 96
#define AUD_NAME_LEN   128
#define AUD_FILE_BUF   (64 * 1024)             // card read-ahead (PSRAM)
#define AUD_MP3_SPACE  (48 * 1024)             // MP3 decoder state (PSRAM)
#define AUD_RING_BYTES (512 * 1024)            // recording slack, ~5.9 s (PSRAM)
#define AUD_RING_N     (AUD_RING_BYTES / 2)

enum : uint8_t { AUD_IDLE, AUD_TRACK, AUD_RECORD, AUD_REPLAY };

static volatile uint8_t  audMode = AUD_IDLE;
static volatile bool     audPaused = false;
static volatile int      audCur = -1;          // track playing / last played
static volatile uint32_t audFrames = 0;        // frames played of the current file
static volatile uint32_t audRateNow = AUD_RATE;
static volatile uint32_t audPos = 0, audSize = 0;
static char              audTitle[AUD_NAME_LEN] = "";
static char              audLastRec[32] = "";
static volatile uint32_t audLastRecMs = 0;
static volatile float    audLevelDb = -120, audPeakDb = -120;   // mic, dBFS before gain
static volatile bool     audMicOk = false;
static Preferences       audPrefs;            // own NVS handle (the shared one may be open elsewhere)
static volatile int      audSlot = -1;
static volatile uint32_t audDrops = 0;
static volatile int      audVol = 10;          // 0..20      NVS "audio"/"vol"
static volatile int      audMicGainDb = 24;    // 0..48 dB   NVS "audio"/"mic"
static int               audDrive = 2;
static char              audMsg[48] = "";
static volatile uint32_t audMsgMs = 0;
static char            (*audTracks)[AUD_NAME_LEN] = nullptr;
static volatile int      audNTracks = 0;
static volatile bool     audScanned = false;
static volatile bool     audWantMic = false;   // recorder open: keep the port running
static bool              audReady = false;
static TaskHandle_t      audTaskH = nullptr, audWriterH = nullptr;
static QueueHandle_t     audQ = nullptr;
struct AudCmd { char c; int arg; };

static int16_t*          audRing = nullptr;    // recording ring, monotonic indices
static volatile uint32_t audRingHead = 0, audRingTail = 0;
static File              audRecFile;
static volatile bool     audRecStopping = false;
static volatile uint32_t audRecBytes = 0, audRecFrames = 0;

static uint8_t*          audFileBuf = nullptr;
static uint8_t*          audMp3Space = nullptr;
static AudioGenerator*        audGen  = nullptr;
static AudioFileSourceFS*     audFile = nullptr;
static AudioFileSourceBuffer* audBuf  = nullptr;

static void audPortRate(uint32_t hz) {
#if AUDIO_PINS
  i2s_set_sample_rates(I2S_NUM_0, hz);
#endif
  audRateNow = hz;
}
static void audPortStart() {
#if AUDIO_PINS
  i2s_start(I2S_NUM_0);
#endif
}
static void audPortStop() {
#if AUDIO_PINS
  i2s_stop(I2S_NUM_0); i2s_zero_dma_buffer(I2S_NUM_0);
#endif
}
//  One block in: frames read. Without pins: silence, paced to the sample rate.
static int audPortRead(int32_t* rx) {
#if AUDIO_PINS
  size_t got = 0;
  i2s_read(I2S_NUM_0, rx, AUD_BLK * 8, &got, portMAX_DELAY);
  return got / 8;
#else
  static uint64_t due = 0;
  const uint64_t now = esp_timer_get_time();
  if (!due || now > due + 50000) due = now;              // first block, or after a stall
  due += (uint64_t)AUD_BLK * 1000000ULL / (audRateNow ? audRateNow : AUD_RATE);
  const int64_t wait = (int64_t)(due - now);
  if (wait >= 1000) vTaskDelay(pdMS_TO_TICKS(wait / 1000)); else taskYIELD();
  memset(rx, 0, AUD_BLK * 8);
  return AUD_BLK;
#endif
}
static void audPortWrite(const int32_t* tx, int frames) {
#if AUDIO_PINS
  size_t w; i2s_write(I2S_NUM_0, tx, frames * 8, &w, portMAX_DELAY);
#else
  (void)tx; (void)frames;
#endif
}

static void audSay(const char* m) { snprintf(audMsg, sizeof audMsg, "%s", m); audMsgMs = millis() | 1; }

//  The decoders hand over one sample at a time; this collects a block of
//  32-bit stereo frames and says "full" once it has one, so the decoder's
//  loop() returns and the task can write it.
class AudBlockOut : public AudioOutput {
 public:
  int32_t tx[AUD_BLK * 2];
  int     n = 0;
  bool begin() override { return true; }
  bool SetRate(int hz) override {
    hertz = hz;
    if (hz > 0 && (uint32_t)hz != audRateNow) audPortRate(hz);
    return true;
  }
  bool ConsumeSample(int16_t s[2]) override {
    if (n == AUD_BLK) return false;
    MakeSampleStereo16(s);
    tx[n * 2]     = (int32_t)Amplify(s[LEFTCHANNEL])  << 16;
    tx[n * 2 + 1] = (int32_t)Amplify(s[RIGHTCHANNEL]) << 16;
    n++;
    return true;
  }
  bool stop() override { return true; }
};
static AudBlockOut* audOut = nullptr;

static void audVolApply() {
  if (!audOut) return;
  const float g = audVol / 20.0f;
  audOut->SetGain(g * g);                      // squared: even steps by ear
}

static void audSetDrive(int d) {
  audDrive = constrain(d, 0, 3);
  if (!AUDIO_PINS) return;                             // pins not ours yet
  for (int p : { AUD_BCLK, AUD_LRC, AUD_DIN }) gpio_set_drive_capability((gpio_num_t)p, (gpio_drive_cap_t)audDrive);
}

static void audWavHeader(uint8_t* h, uint32_t dataBytes) {
  static const uint8_t t[44] = { 'R','I','F','F', 0,0,0,0, 'W','A','V','E', 'f','m','t',' ', 16,0,0,0, 1,0, 1,0,
                                 0,0,0,0, 0,0,0,0, 2,0, 16,0, 'd','a','t','a', 0,0,0,0 };
  memcpy(h, t, 44);
  auto put32 = [&](int o, uint32_t v) { h[o] = v; h[o + 1] = v >> 8; h[o + 2] = v >> 16; h[o + 3] = v >> 24; };
  put32(4, 36 + dataBytes); put32(24, AUD_RATE); put32(28, AUD_RATE * 2); put32(40, dataBytes);
}

static const char* audBase(const char* path) { const char* b = strrchr(path, '/'); return b ? b + 1 : path; }

// ── track list ───────────────────────────────────────────
static bool audIsAudio(const char* n) {
  const char* dot = strrchr(n, '.');
  return n[0] != '.' && dot && (!strcasecmp(dot, ".mp3") || !strcasecmp(dot, ".wav"));
}
static void audScanDir(const char* dir) {
  File d = SD_MMC.open(dir);
  if (!d || !d.isDirectory()) return;
  for (File f = d.openNextFile(); f && audNTracks < AUD_MAX_TRACKS; f = d.openNextFile()) {
    if (f.isDirectory()) continue;
    const char* b = audBase(f.name());
    if (!audIsAudio(b)) continue;
    snprintf(audTracks[audNTracks], AUD_NAME_LEN, "%s%s%s", dir, strcmp(dir, "/") ? "/" : "", b);
    audNTracks++;
  }
}
//  Rescan, keeping whatever is playing pointed at the same file.
static void audScan() {
  char keep[AUD_NAME_LEN] = "";
  if (audCur >= 0 && audCur < audNTracks) snprintf(keep, sizeof keep, "%s", audTracks[audCur]);
  audNTracks = 0;
  if (sdMounted && audTracks) { audScanDir("/MUSIC"); audScanDir("/"); audScanDir("/REC"); }
  audCur = -1;
  for (int i = 0; keep[0] && i < audNTracks; i++) if (!strcmp(audTracks[i], keep)) audCur = i;
  audScanned = true;
}

// ── playback ─────────────────────────────────────────────
static void audCloseFile() {
  if (audGen) { if (audGen->isRunning()) audGen->stop(); delete audGen; audGen = nullptr; }
  delete audBuf;  audBuf = nullptr;
  delete audFile; audFile = nullptr;
}

static bool audOpen(const char* path) {
  audCloseFile();
  if (!sdMounted || !audOut) return false;
  audFile = new AudioFileSourceFS(SD_MMC, path);
  if (!audFile->isOpen()) { audCloseFile(); return false; }
  audBuf = new AudioFileSourceBuffer(audFile, audFileBuf, AUD_FILE_BUF);
  const char* dot = strrchr(path, '.');
  if (dot && !strcasecmp(dot, ".wav")) audGen = new AudioGeneratorWAV();
  else                                 audGen = new AudioGeneratorMP3(audMp3Space, AUD_MP3_SPACE);
  audFrames = 0; audPaused = false;
  if (!audGen->begin(audBuf, audOut)) { audCloseFile(); return false; }
  audSize = audFile->getSize();
  snprintf(audTitle, sizeof audTitle, "%s", audBase(path));
  if (char* d = strrchr(audTitle, '.')) *d = '\0';
  return true;
}

//  Track i, or the next one that opens.
static void audPlayTrack(int i) {
  const int n = audNTracks;
  for (int t = 0; t < n; t++) {
    const int k = (((i + t) % n) + n) % n;
    if (audOpen(audTracks[k])) {
      audCur = k; audMode = AUD_TRACK;
      Serial.printf("AUDIO: playing %d/%d %s\n", k + 1, n, audTracks[k]);
      return;
    }
    Serial.printf("AUDIO: can't play %s\n", audTracks[k]);
  }
  audMode = AUD_IDLE;
  audSay(n ? "CAN'T PLAY THESE FILES" : "NO MUSIC ON THE CARD");
}

// ── recording ────────────────────────────────────────────
static void audRecStart() {
  if (!AUDIO_PINS) { audSay("NO MIC - AUDIO PINS ARE OFF"); return; }
  if (!sdMounted || !audRing) { audSay("NO CARD"); return; }
  audCloseFile();                                      // music stops
  if (audRateNow != AUD_RATE) audPortRate(AUD_RATE);
  SD_MMC.mkdir("/REC");
  char path[32] = "";
  for (int i = 1; i < 1000; i++) { snprintf(path, sizeof path, "/REC/REC%03d.WAV", i); if (!SD_MMC.exists(path)) break; }
  audRecFile = SD_MMC.open(path, FILE_WRITE);
  if (!audRecFile) { audSay("CAN'T CREATE FILE"); audMode = AUD_IDLE; return; }
  uint8_t h[44]; audWavHeader(h, 0); audRecFile.write(h, 44);
  snprintf(audLastRec, sizeof audLastRec, "%s", path);
  audRingHead = audRingTail = 0; audRecBytes = 0; audRecFrames = 0; audDrops = 0;
  audRecStopping = false;
  audMode = AUD_RECORD;
  Serial.printf("AUDIO: recording %s\n", path);
}

static void audRecStop() {
  if (audMode != AUD_RECORD) return;
  audMode = AUD_IDLE;
  audRecStopping = true;                               // the writer flushes, fixes the header, closes
  if (audWriterH) xTaskNotifyGive(audWriterH);
}

//  Drains the ring to the card in big writes; on stop, finishes the file.
static void audWriterTask(void*) {
  for (;;) {
    ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(50));
    if (!audRecFile) continue;
    for (;;) {
      const uint32_t head = audRingHead, tail = audRingTail, avail = head - tail;
      if (!avail || (avail < 2048 && !audRecStopping)) break;
      const uint32_t idx = tail % AUD_RING_N;
      uint32_t n = min(avail, (uint32_t)(AUD_RING_N - idx));
      n = min(n, (uint32_t)8192);
      audRecFile.write((const uint8_t*)&audRing[idx], n * 2);
      audRecBytes += n * 2;
      audRingTail = tail + n;
    }
    if (audRecStopping && audRingHead == audRingTail) {
      uint8_t h[44]; audWavHeader(h, audRecBytes);
      audRecFile.seek(0); audRecFile.write(h, 44); audRecFile.close();
      audLastRecMs = (uint32_t)((uint64_t)audRecBytes * 500 / AUD_RATE);
      char m[48]; snprintf(m, sizeof m, "SAVED %s", audBase(audLastRec)); audSay(m);
      Serial.printf("AUDIO: saved %s (%lu ms, %lu dropped)\n", audLastRec,
                    (unsigned long)audLastRecMs, (unsigned long)audDrops);
      audRecStopping = false;
      audScanned = false;                               // the player's list gains it
    }
  }
}

// ── the task that owns the port ──────────────────────────
static void audHandle(char c, int arg) {
  switch (c) {
    case 'S': audScan(); break;
    case 'p':                                          // play / pause
      if (audMode == AUD_TRACK) { audPaused = !audPaused; break; }
      if (audMode == AUD_RECORD) break;
      if (!audScanned) audScan();
      audPlayTrack(audCur >= 0 ? audCur : 0);
      break;
    case 'P': if (audMode != AUD_RECORD) { if (!audScanned) audScan(); audPlayTrack(arg); } break;
    case 'n': if (audMode != AUD_RECORD) { if (!audScanned) audScan(); audPlayTrack(audCur + 1); } break;
    case 's': if (audMode == AUD_TRACK || audMode == AUD_REPLAY) { audCloseFile(); audMode = AUD_IDLE; } break;
    case 'v': audVolApply(); break;
    case 'R': if (audMode == AUD_RECORD) audRecStop(); else if (!audRecStopping) audRecStart(); break;
    case 'L':                                          // play / stop the last recording
      if (audMode == AUD_REPLAY) { audCloseFile(); audMode = AUD_IDLE; break; }
      if (audMode == AUD_RECORD || audRecStopping || !audLastRec[0]) break;
      if (audOpen(audLastRec)) audMode = AUD_REPLAY; else audSay("CAN'T PLAY IT");
      break;
    case 'D': audSetDrive(arg); break;
    default: break;                                    // 'W': just wake up
  }
}

static void audTask(void*) {
  static int32_t rx[AUD_BLK * 2];
  float dcX[2] = { 0, 0 }, dcY[2] = { 0, 0 };
  double slotE[2] = { 0, 0 }; uint32_t slotN = 0;
  double sumSq = 0; float pk = 0; uint32_t nLvl = 0;
  bool running = false;
  uint32_t idleSince = millis();
  AudCmd cmd;
  for (;;) {
    if (!running) {                                    // asleep until someone wants audio
      if (xQueueReceive(audQ, &cmd, portMAX_DELAY) != pdTRUE) continue;
      audPortStart();
      running = true; idleSince = millis();
      audSlot = -1; slotE[0] = slotE[1] = 0; slotN = 0; dcX[0] = dcX[1] = dcY[0] = dcY[1] = 0;
      audHandle(cmd.c, cmd.arg);
    }
    while (xQueueReceive(audQ, &cmd, 0) == pdTRUE) audHandle(cmd.c, cmd.arg);

    const int frames = audPortRead(rx);

    //  Out: music or a recording, else silence.
    audOut->n = 0;
    if ((audMode == AUD_TRACK || audMode == AUD_REPLAY) && !audPaused && audGen && audGen->isRunning()) {
      for (int guard = 0; audOut->n < frames && guard < 16; guard++) {
        if (!audGen->loop()) {                         // end of the file
          const bool replay = audMode == AUD_REPLAY;
          audCloseFile();
          if (!replay && audNTracks) audPlayTrack(audCur + 1); else audMode = AUD_IDLE;
          break;
        }
      }
      audFrames += audOut->n;
      if (audFile) audPos = audFile->getPos();
    }
    for (int i = audOut->n; i < frames; i++) { audOut->tx[i * 2] = 0; audOut->tx[i * 2 + 1] = 0; }
    if (audMode == AUD_IDLE && audRateNow != AUD_RATE) audPortRate(AUD_RATE);

    //  In: find the mic's slot (the empty one reads constant), then level
    //  meter and recording.
    if (audSlot < 0) {
      for (int i = 0; i < frames; i++)
        for (int s = 0; s < 2; s++) {
          const float x = (float)(rx[i * 2 + s] >> 8) / 8388608.0f;
          const float y = x - dcX[s] + 0.995f * dcY[s]; dcX[s] = x; dcY[s] = y;
          slotE[s] += y * y;
        }
      if ((slotN += frames) >= AUD_RATE / 2) {
        audSlot = slotE[1] > slotE[0] ? 1 : 0;
        audMicOk = slotE[audSlot] > 1e-9;
        if (AUDIO_PINS) Serial.printf("AUDIO: mic %s (slot %d, %.2e vs %.2e)\n", audMicOk ? "found" : "NOT ANSWERING",
                      audSlot, slotE[audSlot], slotE[audSlot ^ 1]);
      }
    } else {
      const int s = audSlot;
      const float g = powf(10.0f, audMicGainDb / 20.0f);
      for (int i = 0; i < frames; i++) {
        const float x = (float)(rx[i * 2 + s] >> 8) / 8388608.0f;
        const float m = x - dcX[s] + 0.995f * dcY[s]; dcX[s] = x; dcY[s] = m;
        sumSq += m * m; pk = fmaxf(pk, fabsf(m)); nLvl++;
        if (audMode == AUD_RECORD) {
          const float v = constrain(m * g, -1.0f, 1.0f);
          if (audRingHead - audRingTail < AUD_RING_N) {
            audRing[audRingHead % AUD_RING_N] = (int16_t)(v * 32767.0f);
            audRingHead = audRingHead + 1;
          } else audDrops = audDrops + 1;
          audRecFrames = audRecFrames + 1;
        }
      }
      if (audMode == AUD_RECORD && audWriterH && audRingHead - audRingTail >= 2048) xTaskNotifyGive(audWriterH);
      if (nLvl >= AUD_RATE / 10) {
        audLevelDb = 20.0f * log10f(fmaxf(sqrtf(sumSq / nLvl), 1e-9f));
        audPeakDb  = 20.0f * log10f(fmaxf(pk, 1e-9f));
        sumSq = 0; pk = 0; nLvl = 0;
      }
    }

    audPortWrite(audOut->tx, frames);

    //  Nothing to do for a while: stop the clocks (the amp mutes) and sleep.
    if (audMode != AUD_IDLE || audWantMic || audRecStopping) idleSince = millis();
    else if (millis() - idleSince > 1500) {
      audPortStop();
      running = false;
    }
  }
}

//  First use: buffers in PSRAM, the port (stopped), the two tasks.
static bool audEnsure() {
  if (audReady) return true;
  audPrefs.begin("audio", true);
  audVol = audPrefs.getUChar("vol", 10); audMicGainDb = audPrefs.getUChar("mic", 24);
  audPrefs.end();
  audTracks   = (char(*)[AUD_NAME_LEN])ps_malloc(AUD_MAX_TRACKS * AUD_NAME_LEN);
  audFileBuf  = (uint8_t*)ps_malloc(AUD_FILE_BUF);
  audMp3Space = (uint8_t*)ps_malloc(AUD_MP3_SPACE);
  audRing     = AUDIO_PINS ? (int16_t*)ps_malloc(AUD_RING_BYTES) : nullptr;   // recording only
  if (!audTracks || !audFileBuf || !audMp3Space || (AUDIO_PINS && !audRing)) { Serial.println("AUDIO: no PSRAM"); return false; }
  audOut = new AudBlockOut();
  audVolApply();

#if AUDIO_PINS
  i2s_config_t cfg = {};
  cfg.mode                 = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX);
  cfg.sample_rate          = AUD_RATE;
  cfg.bits_per_sample      = I2S_BITS_PER_SAMPLE_32BIT;
  cfg.channel_format       = I2S_CHANNEL_FMT_RIGHT_LEFT;
  cfg.communication_format = I2S_COMM_FORMAT_STAND_I2S;
  cfg.dma_buf_count        = 8;
  cfg.dma_buf_len          = AUD_BLK;
  cfg.tx_desc_auto_clear   = true;
  i2s_pin_config_t pins = {};
  pins.mck_io_num = I2S_PIN_NO_CHANGE; pins.bck_io_num = AUD_BCLK; pins.ws_io_num = AUD_LRC;
  pins.data_out_num = AUD_DIN; pins.data_in_num = AUD_DOUT;
  if (i2s_driver_install(I2S_NUM_0, &cfg, 0, nullptr) != ESP_OK || i2s_set_pin(I2S_NUM_0, &pins) != ESP_OK) {
    Serial.println("AUDIO: I2S start FAILED"); return false;
  }
  i2s_stop(I2S_NUM_0);                                 // until something needs it
  audSetDrive(audDrive);
#endif

  audQ = xQueueCreate(16, sizeof(AudCmd));
  xTaskCreatePinnedToCore(audTask, "audio", 16384, nullptr, 3, &audTaskH, 1);
  xTaskCreatePinnedToCore(audWriterTask, "audwr", 4096, nullptr, 2, &audWriterH, 0);
  audReady = true;
  if (AUDIO_PINS) Serial.printf("AUDIO: ready (BCLK %d LRC %d DIN %d DOUT %d, drive %d)\n", AUD_BCLK, AUD_LRC, AUD_DIN, AUD_DOUT, audDrive);
  else            Serial.println("AUDIO: ready - pins OFF (AUDIO_PINS 0): silent playback, no mic");
  return true;
}

static void audSend(char c, int arg) {
  if (!audEnsure()) return;
  AudCmd m = { c, arg };
  xQueueSend(audQ, &m, pdMS_TO_TICKS(20));
}

static void audSavePrefs() {
  if (!audPrefs.begin("audio", false)) { Serial.println("AUDIO: settings not saved (NVS busy)"); return; }
  audPrefs.putUChar("vol", audVol); audPrefs.putUChar("mic", audMicGainDb);
  audPrefs.end();
}

//  Before a reboot (DOOM): finish a recording so the file is whole.
static void audShutdown() {
  if (!audReady) return;
  if (audMode == AUD_RECORD) audSend('R', 0);
  for (int i = 0; i < 150 && (audMode == AUD_RECORD || audRecStopping); i++) delay(10);
}

// ── drawing helpers ──────────────────────────────────────
static void audText(const char* s, int x, int y, int size, uint16_t col) {
  inst->setTextSize(size); inst->setTextColor(col); inst->setCursor(x, y); inst->print(s);
}
static void audCentre(const char* s, int y, int size, uint16_t col) {
  audText(s, (TFT_W - (int)strlen(s) * 6 * size) / 2, y, size, col);
}
static void audTime(char* b, size_t n, uint32_t sec) { snprintf(b, n, "%lu:%02lu", (unsigned long)(sec / 60), (unsigned long)(sec % 60)); }

// ── MUSIC PLAYER ─────────────────────────────────────────
void uiViewMusic() {
  inst->fillScreen(CYBER_BG);
  ui3DHeader("MUSIC PLAYER");
  char b[64];
  if (!audReady)       { audCentre("AUDIO NOT AVAILABLE", 80, 2, NEON_RED); uiBlit(); return; }
  if (!sdMounted)      { audCentre("NO CARD", 70, 2, NEON_RED); audCentre("insert the SD card", 94, 1, CYBER_DIMTXT); uiBlit(); return; }
  if (!audScanned)     { audCentre("READING CARD...", 80, 2, NEON_CYAN); uiBlit(); return; }
  if (!audNTracks)     {
    audCentre("NO MUSIC", 62, 2, NEON_YELLOW);
    audCentre("put .mp3 or .wav files in /MUSIC", 88, 1, CYBER_DIMTXT);
    audCentre("on the SD card", 100, 1, CYBER_DIMTXT);
    uiBlit(); return;
  }
  const bool playing = audMode == AUD_TRACK || audMode == AUD_REPLAY;
  const int cur = audCur;

  //  Status line: position in the list, play state.
  snprintf(b, sizeof b, "TRACK %d/%d", cur >= 0 ? cur + 1 : 0, (int)audNTracks);
  audText(b, 16, 33, 1, CYBER_DIMTXT);
  const char* st = audMode == AUD_RECORD ? "RECORDER BUSY" : !playing ? "STOPPED" : audPaused ? "PAUSED" : "PLAYING";
  audText(st, 304 - 6 * (int)strlen(st), 33, 1, !playing ? CYBER_DIMTXT : audPaused ? NEON_YELLOW : NEON_GREEN);

  //  Title, scrolled when it does not fit (24 characters at size 2).
  const char* t = playing ? audTitle : (cur >= 0 ? audBase(audTracks[cur]) : audBase(audTracks[0]));
  char title[AUD_NAME_LEN]; snprintf(title, sizeof title, "%s", t);
  if (char* d = strrchr(title, '.')) if (!playing) *d = '\0';
  const int len = strlen(title), fit = 24;
  char win[fit + 1];
  if (len <= fit) snprintf(win, sizeof win, "%s", title);
  else {
    const int span = len + 4, off = (millis() / 250) % span;
    for (int i = 0; i < fit; i++) { int k = (off + i) % span; win[i] = k < len ? title[k] : ' '; }
    win[fit] = '\0';
  }
  audText(win, 16, 45, 2, NEON_CYAN);

  //  Progress through the file, elapsed time.
  inst->drawRect(16, 66, 288, 7, CYBER_GRID);
  if (playing && audSize) inst->fillRect(17, 67, (int)(286.0f * min(1.0f, (float)audPos / audSize)), 5, NEON_MAGENTA);
  if (playing) { audTime(b, sizeof b, audFrames / max(1u, (unsigned)audRateNow)); audText(b, 16, 77, 1, CYBER_DIMTXT); }

  //  The list around the current track.
  const int rows = 4;
  int first = (cur >= 0 ? cur : 0) - 1;
  if (first > audNTracks - rows) first = audNTracks - rows;
  if (first < 0) first = 0;
  for (int r = 0; r < rows && first + r < audNTracks; r++) {
    const int k = first + r;
    char nm[48]; snprintf(nm, sizeof nm, "%s", audBase(audTracks[k]));
    if (char* d = strrchr(nm, '.')) *d = '\0';
    const bool me = k == cur;
    const int y = 91 + r * 11;
    if (me) inst->fillTriangle(16, y, 16, y + 6, 21, y + 3, playing ? NEON_GREEN : NEON_CYAN);
    audText(nm, 26, y, 1, me ? NEON_CYAN : CYBER_DIMTXT);
  }

  //  Volume.
  audText("VOL", 16, 140, 1, CYBER_DIMTXT);
  inst->drawRect(40, 139, 202, 9, CYBER_GRID);
  if (audVol) inst->fillRect(41, 140, audVol * 10, 7, NEON_GREEN);
  snprintf(b, sizeof b, "%d", (int)audVol); audText(b, 250, 140, 1, NEON_GREEN);

  if (audMsgMs && millis() - audMsgMs < 3000) audCentre(audMsg, 126, 1, NEON_YELLOW);
  else if (!AUDIO_PINS) audText("NO SPEAKER", 304 - 60, 77, 1, NEON_YELLOW);
  audCentre("ENTER play/pause  RIGHT next  UP/DN vol", TFT_H - 14, 1, CYBER_DIMTXT);
  uiBlit();
}

static void musicAction(UiAction a) {
  switch (a) {
    case ACT_BACK:   uiSel = UI_MUSIC - 1; uiEnter(UI_MENU); return;
    case ACT_SELECT: audSend('p', 0); return;
    case ACT_RIGHT:  audSend('n', 0); return;
    case ACT_PREV:   if (audVol < 20) { audVol = audVol + 1; audSavePrefs(); audSend('v', 0); } return;
    case ACT_NEXT:   if (audVol > 0)  { audVol = audVol - 1; audSavePrefs(); audSend('v', 0); } return;
    default: return;
  }
}

// ── SOUND RECORDER ───────────────────────────────────────
void uiViewRecorder() {
  inst->fillScreen(CYBER_BG);
  ui3DHeader("SOUND RECORDER");
  char b[64];
  if (!audReady)  { audCentre("AUDIO NOT AVAILABLE", 80, 2, NEON_RED); uiBlit(); return; }
  if (!sdMounted) { audCentre("NO CARD", 70, 2, NEON_RED); audCentre("recordings are saved to the SD card", 94, 1, CYBER_DIMTXT); uiBlit(); return; }

  //  Big state line.
  if (audMode == AUD_RECORD) {
    char tm[12]; audTime(tm, sizeof tm, audRecFrames / AUD_RATE);
    snprintf(b, sizeof b, "REC %s", tm);
    const int w = (int)strlen(b) * 18, x = (TFT_W - w) / 2 + 10;
    if ((millis() / 500) % 2) inst->fillCircle(x - 14, 46, 6, NEON_RED);
    audText(b, x, 36, 3, NEON_RED);
  } else if (audRecStopping) {
    audCentre("SAVING...", 36, 3, NEON_YELLOW);
  } else if (audMode == AUD_REPLAY) {
    char tm[12]; audTime(tm, sizeof tm, audFrames / max(1u, (unsigned)audRateNow));
    snprintf(b, sizeof b, "PLAY %s", tm); audCentre(b, 36, 3, NEON_GREEN);
  } else {
    audCentre(!AUDIO_PINS ? "NO MIC" : audSlot < 0 ? "LISTENING..." : "READY", 36, 3, !AUDIO_PINS ? CYBER_DIMTXT : NEON_CYAN);
  }

  //  Level meter: what goes into the file (mic level + gain), -60..0 dB.
  const float lv = audLevelDb + audMicGainDb, pkv = audPeakDb + audMicGainDb;
  auto xOf = [](float db) { return 41 + (int)(262.0f * constrain((db + 60.0f) / 60.0f, 0.0f, 1.0f)); };
  audText("MIC", 16, 73, 1, CYBER_DIMTXT);
  inst->drawRect(40, 70, 264, 14, CYBER_GRID);
  if (audSlot >= 0 && audMicOk) {
    const int xe = xOf(lv);
    const uint16_t col = lv > -3 ? NEON_RED : lv > -12 ? NEON_YELLOW : NEON_GREEN;
    if (xe > 41) inst->fillRect(41, 71, xe - 41, 12, col);
    inst->drawFastVLine(xOf(pkv), 71, 12, WHITE);
  }
  for (int db = -48; db < 0; db += 12) inst->drawFastVLine(xOf(db), 84, 3, CYBER_DIMTXT);
  snprintf(b, sizeof b, "LEVEL %d dB", audSlot >= 0 && audMicOk ? (int)lroundf(lv) : -99);
  audText(b, 16, 92, 1, CYBER_DIMTXT);
  snprintf(b, sizeof b, "GAIN +%d dB", (int)audMicGainDb);
  audText(b, 304 - 6 * (int)strlen(b), 92, 1, NEON_CYAN);

  //  Mic trouble, else the last recording.
  if (!AUDIO_PINS) {
    audCentre("MIC NOT CONNECTED", 108, 1, NEON_YELLOW);
    audCentre("audio pins are off in this firmware", 120, 1, CYBER_DIMTXT);
  } else if (audSlot >= 0 && !audMicOk) {
    audCentre("NO MIC SIGNAL", 108, 1, NEON_RED);
    snprintf(b, sizeof b, "check the mic's power and SD on GPIO %d", AUD_DOUT);
    audCentre(b, 120, 1, CYBER_DIMTXT);
  } else if (audLastRec[0]) {
    char tm[12]; audTime(tm, sizeof tm, audLastRecMs / 1000);
    snprintf(b, sizeof b, "LAST  %s  %s", audBase(audLastRec), tm);
    audCentre(b, 110, 1, CYBER_DIMTXT);
  }
  if (audMsgMs && millis() - audMsgMs < 3000) audCentre(audMsg, 126, 1, NEON_YELLOW);
  if (audDrops) { snprintf(b, sizeof b, "card too slow: %lu samples lost", (unsigned long)audDrops); audCentre(b, 138, 1, NEON_RED); }

  audCentre("ENTER rec/stop  RIGHT play  UP/DN gain", TFT_H - 14, 1, CYBER_DIMTXT);
  uiBlit();
}

static void recorderAction(UiAction a) {
  switch (a) {
    case ACT_BACK:   uiSel = UI_RECORDER - 1; uiEnter(UI_MENU); return;
    case ACT_SELECT: audSend('R', 0); return;
    case ACT_RIGHT:  audSend('L', 0); return;
    case ACT_PREV:   if (audMicGainDb < 48) { audMicGainDb = audMicGainDb + 3; audSavePrefs(); } return;
    case ACT_NEXT:   if (audMicGainDb > 0)  { audMicGainDb = audMicGainDb - 3; audSavePrefs(); } return;
    default: return;
  }
}

//  Called by uiEnter() on every view change.
static void audViewChange(UiView from, UiView to) {
  if (to == UI_RECORDER && from != UI_RECORDER) { audWantMic = true; audSend('W', 0); }
  if (from == UI_RECORDER && to != UI_RECORDER) {
    audWantMic = false;
    if (audReady && audMode == AUD_RECORD) audSend('R', 0);          // leaving stops and saves
  }
  if (to == UI_MUSIC && from != UI_MUSIC && audEnsure() && !audScanned) audSend('S', 0);
}

// ── console ──────────────────────────────────────────────
void audioConsole(const char* cmd, const char* arg) {
  while (*arg == ' ') arg++;
  if (!audEnsure()) return;
  if (!strcmp(cmd, "music")) {
    if (!strcmp(arg, "ls")) {
      if (!audScanned) { audSend('S', 0); delay(300); }
      Serial.printf("%d track(s):\n", (int)audNTracks);
      for (int i = 0; i < audNTracks; i++) Serial.printf("  %2d  %s%s\n", i + 1, audTracks[i], i == audCur ? "   <-" : "");
    }
    else if (!strncmp(arg, "play", 4)) { int n = atoi(arg + 4); if (n > 0) audSend('P', n - 1); else audSend('p', 0); }
    else if (!strcmp(arg, "pause")) audSend('p', 0);
    else if (!strcmp(arg, "next"))  audSend('n', 0);
    else if (!strcmp(arg, "stop"))  audSend('s', 0);
    else if (!strncmp(arg, "vol", 3)) { audVol = constrain(atoi(arg + 3), 0, 20); audSavePrefs(); audSend('v', 0); Serial.printf("volume %d/20\n", (int)audVol); }
    else Serial.printf("music: %s  %s  vol %d/20   (music ls | play [n] | pause | next | stop | vol 0-20)\n",
                       audMode == AUD_TRACK ? (audPaused ? "PAUSED" : "PLAYING") : "STOPPED",
                       audMode == AUD_TRACK ? audTitle : "", (int)audVol);
  } else if (!strcmp(cmd, "rec")) {
    if (!strcmp(arg, "start"))     { if (audMode != AUD_RECORD) audSend('R', 0); }
    else if (!strcmp(arg, "stop")) { if (audMode == AUD_RECORD) audSend('R', 0); }
    else if (!strcmp(arg, "play")) audSend('L', 0);
    else if (!strncmp(arg, "gain", 4)) { audMicGainDb = constrain(atoi(arg + 4), 0, 48); audSavePrefs(); Serial.printf("mic gain +%d dB\n", (int)audMicGainDb); }
    else Serial.printf("rec: %s  last %s  gain +%d dB   (rec start | stop | play | gain 0-48)\n",
                       audMode == AUD_RECORD ? "RECORDING" : "idle", audLastRec[0] ? audLastRec : "-", (int)audMicGainDb);
  } else {                                             // "audio [drive N]"
    if (!strncmp(arg, "drive", 5)) { audSend('D', atoi(arg + 5)); delay(30); }
    if (!AUDIO_PINS) Serial.println("audio: pins OFF (AUDIO_PINS 0) - GPIO 3/43/44/45 untouched; playback is silent, no mic");
    else Serial.printf("audio: BCLK %d LRC %d DIN %d DOUT %d, %lu Hz, drive %d, port %s\n", AUD_BCLK, AUD_LRC, AUD_DIN, AUD_DOUT,
                  (unsigned long)audRateNow, audDrive, audMode != AUD_IDLE || audWantMic ? "running" : "idle (stops when unused)");
    Serial.printf("  mic: %s, slot %d, level %.1f dBFS (peak %.1f)\n", audSlot < 0 ? "not checked yet" : audMicOk ? "OK" : "NO SIGNAL",
                  (int)audSlot, audLevelDb, audPeakDb);
  }
}
#endif  // AUDIO_ENABLE

// ─────────────────────────────────────────────────────────
//  GAS SENSORS — Sensirion SCD40: CO2 (photoacoustic), temperature and
//  relative humidity, on the shared I2C bus at 0x62.
//
//  From the SCD4x datasheet (v1.7, April 2025): 16-bit commands, every
//  data word followed by a CRC-8 (poly 0x31, init 0xFF), up to 400 kHz.
//  Periodic mode gives one reading every 5 s:
//    CO2 [ppm] = w0    T [C] = -45 + 175 * w1 / 65535    RH [%] = 100 * w2 / 65535
//  At boot the sensor may still be measuring from before an ESP reset, so
//  start-up is stop (500 ms) -> serial number (proves it is there) ->
//  start periodic. Polled from loop() as a small state machine - no
//  blocking waits beyond the 1 ms command time - and retried every 10 s
//  when absent, so plugging it in later works.
//
//  GAS SENSORS page: CO2 with an air-quality band, temperature, humidity,
//  and a chart of the last 10 min / 30 min / 2 h.
//    ENTER  chart: CO2 -> temperature -> humidity    UP / DOWN  chart span
//  Console: "gas" status, "gas frc <ppm>" forced recalibration (outdoors,
//  ~420), "gas asc on|off" automatic self-calibration.
// ─────────────────────────────────────────────────────────
#if GAS_ENABLE
#define SCD_ADDR   0x62
#define SCD_HIST   1440                        // 2 h of 5 s readings (PSRAM)

enum : uint8_t { SCD_BOOT, SCD_STOPPING, SCD_RUN, SCD_ABSENT };
static uint8_t   scdState = SCD_BOOT;
static uint32_t  scdT = 0;                     // state timer
static bool      scdHave = false, scdSaid = false;
static uint8_t   scdFails = 0;
static uint64_t  scdSerial = 0;
static uint16_t  scdCo2 = 0;
static float     scdTempC = 0, scdRh = 0;
static uint32_t  scdLastMs = 0, scdReads = 0, scdErrs = 0;
static uint16_t* scdHCo2 = nullptr;            // history rings
static int16_t*  scdHTemp = nullptr;           //   C x 100
static uint16_t* scdHRh = nullptr;             //   % x 100
static uint32_t  scdHN = 0;                    // samples written (monotonic)
static uint8_t   gasMetric = 0;                // chart: 0 CO2, 1 temperature, 2 humidity
static uint8_t   gasSpan = 1;                  // 0: 10 min, 1: 30 min, 2: 2 h
static const uint16_t kGasSpanS[3] = { 600, 1800, 7200 };

static uint8_t scdCrc(const uint8_t* d, int n) {
  uint8_t c = 0xFF;
  for (int i = 0; i < n; i++) {
    c ^= d[i];
    for (int b = 0; b < 8; b++) c = (c & 0x80) ? (uint8_t)((c << 1) ^ 0x31) : (uint8_t)(c << 1);
  }
  return c;
}

//  Bus access: the caller holds i2cMutex.
static bool scdSend(uint16_t cmd) {
  Wire.beginTransmission(SCD_ADDR);
  Wire.write((uint8_t)(cmd >> 8)); Wire.write((uint8_t)cmd);
  return Wire.endTransmission() == 0;
}
static bool scdSendWord(uint16_t cmd, uint16_t w) {
  const uint8_t d[2] = { (uint8_t)(w >> 8), (uint8_t)w };
  Wire.beginTransmission(SCD_ADDR);
  Wire.write((uint8_t)(cmd >> 8)); Wire.write((uint8_t)cmd);
  Wire.write(d, 2); Wire.write(scdCrc(d, 2));
  return Wire.endTransmission() == 0;
}
//  Command, wait its execution time, then read n words (CRC-checked).
static bool scdRead(uint16_t cmd, uint16_t* out, int n, uint32_t execMs) {
  if (!scdSend(cmd)) return false;
  delay(execMs);
  if (Wire.requestFrom((int)SCD_ADDR, n * 3) != n * 3) return false;
  bool ok = true;
  for (int i = 0; i < n; i++) {
    uint8_t b[3]; b[0] = Wire.read(); b[1] = Wire.read(); b[2] = Wire.read();
    if (scdCrc(b, 2) != b[2]) ok = false;
    out[i] = ((uint16_t)b[0] << 8) | b[1];
  }
  if (!ok) scdErrs++;
  return ok;
}
static bool scdLock() { return i2cMutex && xSemaphoreTake(i2cMutex, pdMS_TO_TICKS(20)) == pdTRUE; }
static void scdUnlock() { xSemaphoreGive(i2cMutex); }

static void scdHistAdd() {
  if (!scdHCo2) {
    scdHCo2  = (uint16_t*)ps_malloc(SCD_HIST * sizeof(uint16_t));
    scdHTemp = (int16_t*) ps_malloc(SCD_HIST * sizeof(int16_t));
    scdHRh   = (uint16_t*)ps_malloc(SCD_HIST * sizeof(uint16_t));
    if (!scdHCo2 || !scdHTemp || !scdHRh) { scdHCo2 = nullptr; return; }
  }
  const uint32_t i = scdHN % SCD_HIST;
  scdHCo2[i]  = scdCo2;
  scdHTemp[i] = (int16_t)lroundf(scdTempC * 100.0f);
  scdHRh[i]   = (uint16_t)lroundf(scdRh * 100.0f);
  scdHN++;
}

//  Called every loop() pass; does at most one short exchange.
void scdPoll() {
  if (!i2cMutex) return;
  const uint32_t now = millis();
  switch (scdState) {
    case SCD_BOOT: {                                   // stop whatever it was doing
      if (!scdLock()) return;
      scdSend(0x3f86);                                 // stop_periodic_measurement
      scdUnlock();
      scdState = SCD_STOPPING; scdT = now;
      return;
    }
    case SCD_STOPPING: {
      if (now - scdT < 520) return;                    // 500 ms execution time
      if (!scdLock()) return;
      uint16_t w[3];
      bool ok = scdRead(0x3682, w, 3, 1);              // get_serial_number
      if (ok) ok = scdSend(0x21b1);                    // start_periodic_measurement
      scdUnlock();
      scdT = now;
      if (ok) {
        scdSerial = ((uint64_t)w[0] << 32) | ((uint64_t)w[1] << 16) | w[2];
        scdState = SCD_RUN; scdHave = true; scdFails = 0;
        Serial.printf("SCD40 CO2 sensor @0x%02X, serial %04X%04X%04X - first reading in ~5 s\n",
                      SCD_ADDR, w[0], w[1], w[2]);
      } else {
        scdState = SCD_ABSENT; scdHave = false;
        if (!scdSaid) Serial.printf("SCD40 not found @0x%02X - will keep checking every 10 s\n", SCD_ADDR);
      }
      scdSaid = true;
      return;
    }
    case SCD_ABSENT:
      if (now - scdT >= 10000) scdState = SCD_BOOT;
      return;
    case SCD_RUN: {
      if (now - scdT < 1000) return;                   // ask once a second; data comes every 5 s
      scdT = now;
      if (!scdLock()) return;
      uint16_t st = 0, w[3];
      bool ok = scdRead(0xe4b8, &st, 1, 1);            // get_data_ready_status
      bool got = ok && (st & 0x07FF) && scdRead(0xec05, w, 3, 1);   // read_measurement
      scdUnlock();
      if (!ok) {
        if (++scdFails >= 5) {
          scdState = SCD_ABSENT; scdHave = false;
          Serial.println("SCD40 stopped answering - will keep checking every 10 s");
        }
        return;
      }
      scdFails = 0;
      if (got && w[0]) {                               // the very first frame can read 0 ppm
        scdCo2 = w[0];
        scdTempC = -45.0f + 175.0f * w[1] / 65535.0f;
        scdRh = 100.0f * w[2] / 65535.0f;
        scdLastMs = now; scdReads++;
        scdHistAdd();
      }
      return;
    }
  }
}

//  The everyday bands for indoor CO2.
static const char* gasBand(uint16_t ppm, uint16_t* col) {
  if (ppm < 800)  { *col = NEON_GREEN;  return "FRESH"; }
  if (ppm < 1000) { *col = NEON_CYAN;   return "GOOD"; }
  if (ppm < 1400) { *col = NEON_YELLOW; return "STUFFY"; }
  if (ppm < 2000) { *col = NEON_ORANGE; return "VENTILATE"; }
  *col = NEON_RED; return "POOR AIR";
}

static void gasText(const char* s, int x, int y, int size, uint16_t col) {
  inst->setTextSize(size); inst->setTextColor(col); inst->setCursor(x, y); inst->print(s);
}
static void gasCentre(const char* s, int y, int size, uint16_t col) {
  gasText(s, (TFT_W - (int)strlen(s) * 6 * size) / 2, y, size, col);
}

//  One history sample of the charted metric, in display units.
static float gasSample(uint32_t k) {
  const uint32_t i = k % SCD_HIST;
  if (gasMetric == 0) return scdHCo2[i];
  if (gasMetric == 1) return tconv(scdHTemp[i] / 100.0f);
  return scdHRh[i] / 100.0f;
}

void uiViewGas() {
  inst->fillScreen(CYBER_BG);
  ui3DHeader("GAS SENSORS");
  char b[48];

  if (!scdHave) {
    gasCentre("NO GAS SENSOR", 62, 2, NEON_RED);
    gasCentre("SCD40 not answering at I2C 0x62", 88, 1, CYBER_DIMTXT);
    gasCentre("checking again every 10 s", 100, 1, CYBER_DIMTXT);
    uiBlit(); return;
  }
  if (!scdReads) {
    gasCentre("SCD40 FOUND", 58, 2, NEON_CYAN);
    snprintf(b, sizeof b, "first reading in a few seconds%.*s", (int)((millis() / 400) % 4), "...");
    gasCentre(b, 84, 1, CYBER_DIMTXT);
    uiBlit(); return;
  }

  //  CO2, big, with its band.
  uint16_t bandCol;
  const char* band = gasBand(scdCo2, &bandCol);
  snprintf(b, sizeof b, "%u", scdCo2);
  gasText(b, 16, 33, 5, bandCol);
  gasText("ppm CO2", 16 + (int)strlen(b) * 30 + 6, 61, 1, CYBER_DIMTXT);
  const int cw = (int)strlen(band) * 6 + 12;
  inst->fillRoundRect(16, 79, cw, 13, 4, bandCol);
  gasText(band, 22, 82, 1, CYBER_BG);

  //  Temperature and humidity, right column.
  gasText("TEMPERATURE", 200, 33, 1, CYBER_DIMTXT);
  snprintf(b, sizeof b, "%.1f", tconv(scdTempC));
  gasText(b, 200, 44, 2, NEON_MAGENTA);
  const int dx = 200 + (int)strlen(b) * 12 + 3;
  inst->drawCircle(dx + 2, 46, 2, NEON_MAGENTA);
  char u[2] = { tunit(), 0 }; gasText(u, dx + 7, 44, 2, NEON_MAGENTA);
  gasText("HUMIDITY", 200, 66, 1, CYBER_DIMTXT);
  snprintf(b, sizeof b, "%.0f %%RH", scdRh);
  gasText(b, 200, 77, 2, NEON_CYAN);

  //  Chart of the chosen metric over the chosen span (newest at the right).
  const int cx = 16, cy = 104, cwid = 288, ch = 44;
  inst->drawRect(cx, cy, cwid, ch, CYBER_GRID);
  static const char* const kMetric[3] = { "CO2 ppm", "TEMP", "HUMIDITY %" };
  static const char* const kSpan[3] = { "10 MIN", "30 MIN", "2 H" };
  const uint32_t want = kGasSpanS[gasSpan] / 5;
  const uint32_t n = scdHCo2 ? min(want, min(scdHN, (uint32_t)SCD_HIST)) : 0;
  if (n >= 2) {
    float lo = 1e9f, hi = -1e9f;
    for (uint32_t k = scdHN - n; k < scdHN; k++) { const float v = gasSample(k); lo = fminf(lo, v); hi = fmaxf(hi, v); }
    const float minRange = gasMetric == 0 ? 100.0f : gasMetric == 1 ? 1.0f : 5.0f;   // don't magnify noise
    if (hi - lo < minRange) { const float mid = (hi + lo) / 2; lo = mid - minRange / 2; hi = mid + minRange / 2; }
    auto yOf = [&](float v) { return cy + ch - 3 - (int)lroundf((v - lo) / (hi - lo) * (ch - 6)); };
    if (gasMetric == 0 && lo < 1000 && hi > 1000)                        // the 1000 ppm line
      for (int x = cx + 2; x < cx + cwid - 2; x += 4) inst->drawPixel(x, yOf(1000), NEON_YELLOW);
    const uint16_t lineCol = gasMetric == 0 ? bandCol : gasMetric == 1 ? NEON_MAGENTA : NEON_CYAN;
    int px = 0, py = 0;
    for (uint32_t j = 0; j < n; j++) {
      const uint32_t k = scdHN - n + j;
      const int x = cx + cwid - 2 - (int)((uint64_t)(n - 1 - j) * (cwid - 4) / (want - 1));   // time-true x
      const int y = yOf(gasSample(k));
      if (j) inst->drawLine(px, py, x, y, lineCol);
      px = x; py = y;
    }
    snprintf(b, sizeof b, gasMetric == 0 ? "%.0f-%.0f" : "%.1f-%.1f", lo, hi);
    gasText(b, cx + cwid - 4 - (int)strlen(b) * 6, cy + 3, 1, CYBER_DIMTXT);
  } else {
    gasText("collecting...", cx + 6, cy + ch / 2 - 4, 1, CYBER_DIMTXT);
  }
  snprintf(b, sizeof b, "%s  %s", gasMetric == 1 ? (tempF ? "TEMP F" : "TEMP C") : kMetric[gasMetric], kSpan[gasSpan]);
  gasText(b, cx + 4, cy + 3, 1, CYBER_DIMTXT);

  snprintf(b, sizeof b, "ENTER chart  UP/DN span   %lus ago", (unsigned long)((millis() - scdLastMs) / 1000));
  gasCentre(b, TFT_H - 13, 1, CYBER_DIMTXT);
  uiBlit();
}

static void gasAction(UiAction a) {
  switch (a) {
    case ACT_BACK:   uiSel = UI_GAS - 1; uiEnter(UI_MENU); return;
    case ACT_SELECT: gasMetric = (gasMetric + 1) % 3; return;
    case ACT_PREV:   if (gasSpan < 2) gasSpan++; return;
    case ACT_NEXT:   if (gasSpan > 0) gasSpan--; return;
    case ACT_RIGHT:  saveJpeg(); return;
    default: return;
  }
}

//  Console "gas [frc <ppm> | asc on|off]".
void gasConsole(const char* arg) {
  while (*arg == ' ') arg++;
  if (!strncmp(arg, "frc", 3) || !strncmp(arg, "asc", 3)) {
    if (!scdHave) { Serial.println("gas: no SCD40"); return; }
    const bool frc = arg[0] == 'f';
    const int v = frc ? atoi(arg + 3) : (strstr(arg + 3, "on") ? 1 : 0);
    if (frc && (v < 300 || v > 2000)) { Serial.println("gas frc <ppm>   e.g. gas frc 420 (after 3+ min in fresh outdoor air)"); return; }
    if (!scdLock()) { Serial.println("gas: I2C busy"); return; }
    scdSend(0x3f86); delay(510);                       // both need the sensor idle
    uint16_t r = 0xFFFF; bool ok;
    if (frc) { ok = scdSendWord(0x362f, (uint16_t)v); delay(410);
               ok = ok && Wire.requestFrom((int)SCD_ADDR, 3) == 3;
               if (ok) { uint8_t b[3] = { (uint8_t)Wire.read(), (uint8_t)Wire.read(), (uint8_t)Wire.read() }; r = (b[0] << 8) | b[1]; ok = scdCrc(b, 2) == b[2]; } }
    else       { ok = scdSendWord(0x2416, (uint16_t)v); delay(2); }
    scdSend(0x21b1);                                   // measuring again
    scdUnlock();
    scdState = SCD_RUN; scdT = millis();
    if (frc) {
      if (ok && r != 0xFFFF) Serial.printf("gas: recalibrated to %d ppm (correction %d ppm)\n", v, (int)r - 0x8000);
      else Serial.println("gas: recalibration FAILED (it needs 3+ minutes of measuring first)");
    } else Serial.printf("gas: automatic self-calibration %s %s (not saved over power-off)\n", v ? "ON" : "OFF", ok ? "" : "- FAILED");
    return;
  }
  if (!scdHave) { Serial.printf("gas: SCD40 not found @0x%02X (retrying every 10 s)\n", SCD_ADDR); return; }
  Serial.printf("gas: SCD40 @0x%02X serial %04X%04X%04X, %lu readings, %lu CRC errors\n", SCD_ADDR,
                (unsigned)(scdSerial >> 32), (unsigned)((scdSerial >> 16) & 0xFFFF), (unsigned)(scdSerial & 0xFFFF),
                (unsigned long)scdReads, (unsigned long)scdErrs);
  if (scdReads) Serial.printf("  CO2 %u ppm   %.1f %c   %.1f %%RH   (%lu s ago)\n", scdCo2, tconv(scdTempC), tunit(), scdRh,
                              (unsigned long)((millis() - scdLastMs) / 1000));
  else Serial.println("  waiting for the first reading");
}
#endif  // GAS_ENABLE

// ─────────────────────────────────────────────────────────
//  AIR QUALITY — Sensirion SEN69C-SIN-T on the shared I2C bus at 0x6B:
//  particulate matter (PM1.0/2.5/4.0/10 mass and PM0.5..10 particle
//  counts), temperature, humidity, VOC index, NOx index, formaldehyde
//  (HCHO) and CO2.
//
//  From the SEN6x datasheet (D1, v1.0, October 2026), command codes checked
//  against Sensirion's own arduino-i2c-sen69c driver:
//   - 7-bit address 0x6B, 100 kHz MAXIMUM, no clock stretching: while it
//     works on a command it NACKs, so a command is sent and its reply read
//     only after the execution time (20 ms for most). The rest of this bus
//     runs at 400 kHz (the MLX90640 needs that), so every SEN69C transfer
//     drops the clock to 100 kHz under i2cMutex and then restores it.
//   - 16-bit commands; every data word carries a CRC-8 (0x31, init 0xFF).
//   - New readings every second. Unknown values read 0xFFFF (unsigned) or
//     0x7FFF (signed): CO2 for 24 s after a start, NOx for 11 s and HCHO for
//     60 s after power-on. In spec after: PM 30 s, HCHO 10 min, VOC index
//     under 1 h, NOx index under 6 h, CO2 12 h plus some fresh air.
//   - The CO2 part conditions itself for 24 s after each start: never start
//     again within 24 s of a start, and never stop and then recalibrate or
//     change auto-calibration inside that window (sticky CO2 error).
//   - Supply 3.15-3.6 V: about 75 mA (100 max) measuring, 210 mA peaks.
//
//  Polled from loop() as a state machine. Each pass does at most one short
//  transfer; the waits for the sensor happen between passes, not in them.
//  A sensor that is already measuring at boot (the ESP reset, the sensor
//  kept power) is left running. Retried every 10 s when absent, so
//  plugging it in later works.
//
//  AIR QUALITY page: ten tiles (PM1.0 PM2.5 PM4.0 PM10 CO2 / VOC NOx HCHO
//  TEMP RH), a chart of the selected one over 10 min / 30 min / 2 h, and the
//  overall verdict in the header. ENTER past the last tile opens DETAILS:
//  particle counts, raw signals, serial and firmware, the status register,
//  and actions (fan cleaning, SHT heater, CO2 auto-calibration, clear
//  status).
//    ENTER  next tile, then DETAILS   UP / DOWN  chart span   RIGHT  snapshot
//    DETAILS: UP / DOWN pick an action, ENTER run it, LEFT back to the charts
//  Console: "air" status, "air help" for the rest (recalibration, altitude,
//  pressure, temperature offset, VOC/NOx tuning, resets).
// ─────────────────────────────────────────────────────────
#if AIR_ENABLE
#define SEN_ADDR    0x6B
#define SEN_I2C_HZ  100000UL                    // datasheet maximum
#define SEN_HIST    1440                        // 2 h of 5 s means (PSRAM)
#define SEN_NM      10                          // tiles / charted metrics

//  Tile and history order.
enum : uint8_t { AIR_PM1, AIR_PM25, AIR_PM4, AIR_PM10, AIR_CO2,
                 AIR_VOC, AIR_NOX, AIR_HCHO, AIR_TEMP, AIR_RH };
enum : uint8_t { SEN_PROBE, SEN_CHECKRUN, SEN_IDLECFG, SEN_START, SEN_RUN,
                 SEN_OPSTOP, SEN_OPDO, SEN_ABSENT };
//  Requests. The first group needs the sensor idle: the measurement is
//  stopped, the command run, and measuring resumes. The rest run between
//  readings.
enum : uint8_t { SOP_NONE, SOP_CLEAN, SOP_HEAT, SOP_ASC, SOP_FRC, SOP_ALT,
                 SOP_RESET, SOP_CO2RESET, SOP_VOCGET, SOP_VOCSET, SOP_NOXGET,
                 SOP_NOXSET,
                 SOP_LIVE,                       // ---- below: no stop needed
                 SOP_HPA, SOP_TOFF, SOP_CLEAR };
enum : int8_t  { SX_WAIT, SX_OK, SX_CRC, SX_FAIL };

static uint8_t   senState = SEN_PROBE, senStep = 0;
static uint32_t  senTm = 0;                     // state / cycle timer
static bool      senHave = false, senSaid = false, senIsSen69c = false, senToldRun = false;
static uint8_t   senFails = 0;
static char      senType[33] = "", senName[33] = "", senSerial[33] = "";
static uint8_t   senFwMaj = 0, senFwMin = 0;
static uint32_t  senStartMs = 0;                // last start (0 = none yet)
static uint32_t  senRestUntil = 0;              // no restart before this
static uint32_t  senLastMs = 0, senReads = 0, senErrs = 0;
static uint32_t  senStatus = 0, senStatusSaid = 0;
static int8_t    senAsc = -1;                   // CO2 auto-calibration, -1 unknown
static int32_t   senAltM = -1, senHpa = -1;     // CO2 pressure compensation inputs
static float     senV[SEN_NM];                  // latest; NAN = sensor says unknown
static float     senNc[5];                      // PM0.5/1.0/2.5/4.0/10, particles/cm3
static float     senRawRh = NAN, senRawT = NAN, senHeatRh = NAN, senHeatT = NAN;
static int32_t   senRawVoc = -1, senRawNox = -1;
//  The one exchange in flight.
static bool      senPendOn = false;
static uint16_t  senPend = 0;
static uint32_t  senPendAt = 0;
static uint16_t  senW[16];                      // reply words
//  The one request in flight.
static uint8_t   senOp = SOP_NONE;
static int16_t   senOpArg[6];
static const char* senBusy = nullptr;           // what the page says while stopped
//  History rings (PSRAM): SEN_NM x SEN_HIST 5 s means, NAN = unknown.
static float*    senH = nullptr;
static uint32_t  senHN = 0, senAccT = 0;
static float     senAcc[SEN_NM];
static uint8_t   senAccN[SEN_NM];
//  Page state.
static uint8_t   airMetric = AIR_PM25, airSpan = 1, airSel = 0;
static bool      airDetails = false;
static char      airMsg[56] = "";
static uint32_t  airMsgUntil = 0;
static const uint16_t kAirSpanS[3] = { 600, 1800, 7200 };

//  Status register (datasheet 4.3). Errors stay set until cleared; the fan
//  speed warning (bit 21) clears itself.
static const uint8_t     kSenFlagBit[7]  = { 4, 6, 7, 10, 11, 12, 21 };
static const char* const kSenFlagName[7] = { "FAN", "RH&T", "GAS", "HCHO", "PM", "CO2", "FAN-SPEED" };

static uint8_t senCrc(const uint8_t* d, int n) {
  uint8_t c = 0xFF;
  for (int i = 0; i < n; i++) {
    c ^= d[i];
    for (int b = 0; b < 8; b++) c = (c & 0x80) ? (uint8_t)((c << 1) ^ 0x31) : (uint8_t)(c << 1);
  }
  return c;
}
static bool senLock() { return i2cMutex && xSemaphoreTake(i2cMutex, pdMS_TO_TICKS(20)) == pdTRUE; }
static void senUnlock() { xSemaphoreGive(i2cMutex); }
//  This sensor's speed limit, for the length of one transfer.
static void senSlow(bool on) { Wire.setClock(on && i2cHz > SEN_I2C_HZ ? SEN_I2C_HZ : i2cHz); }

//  Bus access: the caller holds i2cMutex.
static bool senTx(uint16_t cmd, const uint16_t* w, uint8_t n) {
  senSlow(true);
  Wire.beginTransmission(SEN_ADDR);
  Wire.write((uint8_t)(cmd >> 8)); Wire.write((uint8_t)cmd);
  for (uint8_t i = 0; i < n; i++) {
    const uint8_t d[2] = { (uint8_t)(w[i] >> 8), (uint8_t)w[i] };
    Wire.write(d, 2); Wire.write(senCrc(d, 2));
  }
  const bool ok = Wire.endTransmission() == 0;
  senSlow(false);
  return ok;
}
static int8_t senRx(uint8_t n) {
  senSlow(true);
  const int want = n * 3;
  const int got = Wire.requestFrom((int)SEN_ADDR, want);
  bool crcOk = true;
  if (got == want) {
    for (uint8_t i = 0; i < n; i++) {
      uint8_t b[3]; b[0] = Wire.read(); b[1] = Wire.read(); b[2] = Wire.read();
      if (senCrc(b, 2) != b[2]) crcOk = false;
      senW[i] = ((uint16_t)b[0] << 8) | b[1];
    }
  } else while (Wire.available()) Wire.read();
  senSlow(false);
  if (got != want) return SX_FAIL;
  if (!crcOk) { senErrs++; return SX_CRC; }
  return SX_OK;
}

//  One command spread over loop() passes: the first call sends it, later
//  calls return SX_WAIT until its execution time is up and then read the
//  nRx reply words into senW. A write-only command also waits its time out,
//  so the next command never lands while the sensor is still busy.
static int8_t senXfer(uint16_t cmd, const uint16_t* tx, uint8_t nTx, uint8_t nRx, uint16_t execMs) {
  if (senPendOn && senPend != cmd) {           // a different one is still in flight
    if (millis() - senPendAt >= 1500) senPendOn = false;   // longest execution time
    return SX_WAIT;
  }
  if (!senPendOn) {
    if (!senLock()) return SX_WAIT;
    const bool ok = senTx(cmd, tx, nTx);
    senUnlock();
    if (!ok) return SX_FAIL;
    senPendOn = true; senPend = cmd; senPendAt = millis();
    return SX_WAIT;
  }
  if (millis() - senPendAt < (uint32_t)execMs + 2) return SX_WAIT;
  if (!nRx) { senPendOn = false; return SX_OK; }
  if (!senLock()) return SX_WAIT;
  const int8_t r = senRx(nRx);
  senUnlock();
  senPendOn = false;
  return r;
}

static float senU(uint16_t w, float div) { return w == 0xFFFF ? NAN : w / div; }
static float senS(uint16_t w, float div) { return w == 0x7FFF ? NAN : (int16_t)w / div; }
//  A string<32> reply (16 words) as text.
static void senStr(char* out) {
  for (int i = 0; i < 16; i++) { out[2 * i] = (char)(senW[i] >> 8); out[2 * i + 1] = (char)senW[i]; }
  out[32] = 0;
  for (char* p = out; *p; p++) if (*p < 32 || *p > 126) { *p = 0; break; }
}

static void senValuesClear() {
  for (int i = 0; i < SEN_NM; i++) senV[i] = NAN;
  for (int i = 0; i < 5; i++) senNc[i] = NAN;
  senRawRh = senRawT = senHeatRh = senHeatT = NAN;
  senRawVoc = senRawNox = -1;
  senStatus = senStatusSaid = 0;
  senReads = 0; senAsc = -1; senAltM = senHpa = -1;
}

//  "FAN PM ..." for the set flags, or "OK".
static void senFlagText(uint32_t st, char* out, size_t n) {
  out[0] = 0;
  for (int i = 0; i < 7; i++)
    if (st & (1UL << kSenFlagBit[i])) {
      if (out[0]) strlcat(out, " ", n);
      strlcat(out, kSenFlagName[i], n);
    }
  if (!out[0]) strlcpy(out, "OK", n);
}

//  A short result, on the page footer for a few seconds and in the log.
static void senNote(const char* fmt, ...) {
  va_list ap; va_start(ap, fmt);
  vsnprintf(airMsg, sizeof airMsg, fmt, ap);
  va_end(ap);
  airMsgUntil = millis() + 6000;
  Serial.printf("air: %s\n", airMsg);
}

static void senHistAdd(uint32_t now) {
  for (int i = 0; i < SEN_NM; i++)
    if (!isnan(senV[i])) { senAcc[i] += senV[i]; senAccN[i]++; }
  if (!senAccT) senAccT = now;
  if (now - senAccT < 5000) return;
  senAccT = now;
  if (!senH) senH = (float*)ps_malloc(SEN_NM * SEN_HIST * sizeof(float));
  const uint32_t k = senHN % SEN_HIST;
  for (int i = 0; i < SEN_NM; i++) {
    if (senH) senH[i * SEN_HIST + k] = senAccN[i] ? senAcc[i] / senAccN[i] : NAN;
    senAcc[i] = 0; senAccN[i] = 0;
  }
  if (senH) senHN++;
}

static void senGone(const char* why) {
  if (senHave) Serial.printf("SEN69C %s - will keep checking every 10 s\n", why);
  else if (!senSaid) Serial.printf("SEN69C not found @0x%02X - will keep checking every 10 s\n", SEN_ADDR);
  senSaid = true; senHave = false;
  senState = SEN_ABSENT; senStep = 0; senTm = millis(); senPendOn = false;
  if (senOp != SOP_NONE) { senOp = SOP_NONE; senNote("request dropped - the sensor stopped answering"); }
  senBusy = nullptr;
}

//  Store one reply of the reading cycle (step 1..4).
static void senTake(uint8_t step, uint32_t now) {
  switch (step) {
    case 1:                                            // read_measured_values (SEN69C)
      for (int i = 0; i < 4; i++) senV[i] = senU(senW[i], 10.0f);
      senV[AIR_RH]   = senS(senW[4], 100.0f);
      senV[AIR_TEMP] = senS(senW[5], 200.0f);
      senV[AIR_VOC]  = senS(senW[6], 10.0f);
      senV[AIR_NOX]  = senS(senW[7], 10.0f);
      senV[AIR_HCHO] = senU(senW[8], 10.0f);
      senV[AIR_CO2]  = senS(senW[9], 1.0f);
      senLastMs = now; senReads++;
      senHistAdd(now);
      break;
    case 2:                                            // read_number_concentration_values
      for (int i = 0; i < 5; i++) senNc[i] = senU(senW[i], 10.0f);
      break;
    case 3:                                            // read_measured_raw_values
      senRawRh = senS(senW[0], 100.0f);
      senRawT  = senS(senW[1], 200.0f);
      senRawVoc = senW[2] == 0xFFFF ? -1 : senW[2];
      senRawNox = senW[3] == 0xFFFF ? -1 : senW[3];
      break;
    case 4: {                                          // read_device_status
      senStatus = ((uint32_t)senW[0] << 16) | senW[1];
      if (senStatus != senStatusSaid) {
        char f[64]; senFlagText(senStatus, f, sizeof f);
        Serial.printf("SEN69C status 0x%08lX: %s\n", (unsigned long)senStatus, f);
        senStatusSaid = senStatus;
      }
      break;
    }
  }
}

//  Run the queued request's command(s). Returns true when it is finished.
static bool senDoOp(uint32_t now) {
  uint16_t cmd = 0, tx[6] = { 0 };
  uint8_t nTx = 0, nRx = 0;
  uint16_t ms = 20;
  switch (senOp) {
    case SOP_CLEAN:    cmd = 0x5607; break;                          // start_fan_cleaning
    case SOP_HEAT:     if (senStep == 0) { cmd = 0x6765; ms = 1300; }   // activate_sht_heater
                       else { cmd = 0x6790; nRx = 2; }                // get_sht_heater_measurements
                       break;
    case SOP_ASC:      cmd = 0x6711; tx[0] = senOpArg[0] ? 1 : 0; nTx = 1; break;
    case SOP_FRC:      cmd = 0x6707; tx[0] = (uint16_t)senOpArg[0]; nTx = 1; nRx = 1; ms = 500; break;
    case SOP_ALT:      cmd = 0x6736; tx[0] = (uint16_t)senOpArg[0]; nTx = 1; break;
    case SOP_RESET:    cmd = 0xD304; ms = 1200; break;
    case SOP_CO2RESET: cmd = 0x6754; ms = 1400; break;
    case SOP_VOCGET:   cmd = 0x60D0; nRx = 6; break;
    case SOP_NOXGET:   cmd = 0x60E1; nRx = 6; break;
    case SOP_VOCSET:
    case SOP_NOXSET:   cmd = senOp == SOP_VOCSET ? 0x60D0 : 0x60E1;
                       for (int i = 0; i < 6; i++) tx[i] = (uint16_t)senOpArg[i];
                       nTx = 6; break;
    case SOP_HPA:      cmd = 0x6720; tx[0] = (uint16_t)senOpArg[0]; nTx = 1; break;
    case SOP_TOFF:     cmd = 0x60B2; tx[0] = (uint16_t)senOpArg[0];  // offset x200, slope 0,
                       nTx = 4; break;                               //  time constant 0, slot 0
    case SOP_CLEAR:    cmd = 0xD210; nRx = 2; break;                 // read_and_clear_device_status
    default: return true;
  }
  const int8_t r = senXfer(cmd, tx, nTx, nRx, ms);
  if (r == SX_WAIT) return false;
  const bool ok = r == SX_OK;
  switch (senOp) {
    case SOP_CLEAN:
      senRestUntil = now + 10500;                      // datasheet: wait 10 s before starting
      senNote(ok ? "fan cleaning: full speed for 10 s" : "fan cleaning FAILED");
      break;
    case SOP_HEAT:
      if (senStep == 0 && ok && (senFwMaj >= 9)) { senStep = 1; return false; }   // fw 9.0+ reports
      if (senStep == 1 && ok) { senHeatRh = senS(senW[0], 100.0f); senHeatT = senS(senW[1], 200.0f); }
      senRestUntil = now + 20500;                      // datasheet: wait 20 s before starting
      senNote(senStep == 0 && !ok ? "SHT heater FAILED" : "SHT heater: done, readings resume in 20 s");
      break;
    case SOP_ASC:
      senNote("CO2 auto-calibration %s%s (until the sensor is reset)", senOpArg[0] ? "ON" : "OFF", ok ? "" : " - FAILED");
      break;
    case SOP_FRC:
      if (ok && senW[0] != 0xFFFF)
        senNote("CO2 recalibrated to %d ppm (correction %d ppm, kept)", senOpArg[0], (int)senW[0] - 0x8000);
      else senNote("CO2 recalibration FAILED");
      break;
    case SOP_ALT:      senNote("altitude %d m%s (until the sensor is reset)", senOpArg[0], ok ? "" : " - FAILED"); break;
    case SOP_RESET:    senNote(ok ? "device reset" : "device reset FAILED"); break;
    case SOP_CO2RESET: senNote(ok ? "CO2 factory reset: FRC/ASC history erased" : "CO2 factory reset FAILED"); break;
    case SOP_VOCGET:
    case SOP_NOXGET:
      if (ok) Serial.printf("air: %s tuning: index offset %d, learning offset %d h, learning gain %d h, "
                            "gating %d min, std initial %d, gain %d\n", senOp == SOP_VOCGET ? "VOC" : "NOx",
                            (int16_t)senW[0], (int16_t)senW[1], (int16_t)senW[2], (int16_t)senW[3],
                            (int16_t)senW[4], (int16_t)senW[5]);
      else senNote("reading the tuning FAILED");
      break;
    case SOP_VOCSET:
    case SOP_NOXSET:
      senNote("%s tuning set%s (until the sensor is reset)", senOp == SOP_VOCSET ? "VOC" : "NOx", ok ? "" : " - FAILED");
      break;
    case SOP_HPA:      senNote("ambient pressure %d hPa%s (until the sensor is reset)", senOpArg[0], ok ? "" : " - FAILED"); break;
    case SOP_TOFF:     senNote("temperature offset %+.2f C%s (until the sensor is reset)", senOpArg[0] / 200.0f, ok ? "" : " - FAILED"); break;
    case SOP_CLEAR: {
      if (!ok) { senNote("clearing the status FAILED"); break; }
      char f[64]; senFlagText(((uint32_t)senW[0] << 16) | senW[1], f, sizeof f);
      senNote("status cleared (was %s)", f);
      senStatus = 0;
      break;
    }
  }
  return true;
}

//  Called every loop() pass; does at most one short exchange.
void senPoll() {
  if (!i2cMutex) return;
  const uint32_t now = millis();
  int8_t r;
  switch (senState) {
    case SEN_ABSENT:
      if (now - senTm >= 10000) { senState = SEN_PROBE; senStep = 0; }
      return;

    case SEN_PROBE: {                                  // product type, name, serial, firmware
      static const uint16_t kCmd[4] = { 0xD002, 0xD014, 0xD033, 0xD100 };
      r = senXfer(kCmd[senStep], nullptr, 0, senStep < 3 ? 16 : 1, 20);
      if (r == SX_WAIT) return;
      if (r == SX_FAIL) { senGone("stopped answering"); return; }
      if (r == SX_OK) {
        if      (senStep == 0) senStr(senType);
        else if (senStep == 1) senStr(senName);
        else if (senStep == 2) senStr(senSerial);
        else { senFwMaj = senW[0] >> 8; senFwMin = senW[0] & 0xFF; }
      }
      if (++senStep < 4) return;
      senIsSen69c = !strcmp(senType, "0x00085900") || strstr(senName, "SEN69C");
      senValuesClear();
      senHave = true; senSaid = true; senFails = 0; senToldRun = false;
      Serial.printf("SEN69C air-quality sensor @0x%02X: \"%s\" type %s, serial %s, firmware %u.%u%s\n",
                    SEN_ADDR, senName, senType, senSerial, senFwMaj, senFwMin,
                    senIsSen69c ? "" : "  (NOT identified as a SEN69C - readings may be wrong)");
      senState = SEN_CHECKRUN; senStep = 0; senTm = now;
      return;
    }

    case SEN_CHECKRUN:                                 // measuring already?
      //  Measuring, it has new data every second, so two looks 1.1 s apart
      //  settle it. Idle, it answers "not ready" (or NACKs: same meaning).
      if (senStep == 1 && now - senTm < 1100) return;
      r = senXfer(0x0202, nullptr, 0, 1, 20);          // get_data_ready
      if (r == SX_WAIT) return;
      if (r == SX_OK && (senW[0] & 0xFF)) {
        senStartMs = now | 1;                          // start time unknown: assume just now
        senState = SEN_RUN; senStep = 0; senTm = now - 1000;
        Serial.println("SEN69C was already measuring - left running");
        senToldRun = true;
        return;
      }
      if (senStep == 0) { senStep = 1; senTm = now; return; }
      senState = SEN_IDLECFG; senStep = 0;
      return;

    case SEN_IDLECFG: {                                // settings only readable while idle
      static const uint16_t kCmd[3] = { 0x6711, 0x6736, 0x6720 };   // ASC, altitude, pressure
      r = senXfer(kCmd[senStep], nullptr, 0, 1, 20);
      if (r == SX_WAIT) return;
      if (r == SX_OK) {
        if      (senStep == 0) senAsc = (senW[0] & 0xFF) ? 1 : 0;
        else if (senStep == 1) senAltM = senW[0];
        else                   senHpa = senW[0];
      }
      if (++senStep < 3) return;
      senState = SEN_START; senStep = 0;
      return;
    }

    case SEN_START:
      if ((int32_t)(senRestUntil - now) > 0) return;
      if (senStartMs && now - senStartMs < 24500) return;   // CO2 conditioning rule
      r = senXfer(0x0021, nullptr, 0, 0, 50);          // start_continuous_measurement
      if (r == SX_WAIT) return;
      if (r != SX_OK) {
        if (++senFails >= 5) senGone("would not start measuring");
        else { senState = SEN_CHECKRUN; senStep = 0; senTm = now; }
        return;
      }
      senStartMs = now | 1; senFails = 0; senBusy = nullptr;
      senState = SEN_RUN; senStep = 0; senTm = now;
      if (!senToldRun) Serial.println("SEN69C measuring - PM in ~1 s, CO2 after ~24 s, HCHO after ~60 s");
      senToldRun = true;
      return;

    case SEN_RUN: {
      if (senOp != SOP_NONE && senStep == 0 && !senPendOn) {
        senState = senOp < SOP_LIVE ? SEN_OPSTOP : SEN_OPDO;
        senStep = 0;
        return;
      }
      if (senStep == 0 && !senPendOn) {                // once a second
        if (now - senTm < 1000) return;
        senTm = now;
      }
      //  data ready -> values -> particle counts -> raw signals -> status
      static const uint16_t kCmd[5] = { 0x0202, 0x04B5, 0x0316, 0x0455, 0xD206 };
      static const uint8_t  kN[5]   = { 1, 10, 5, 4, 2 };
      r = senXfer(kCmd[senStep], nullptr, 0, kN[senStep], 20);
      if (r == SX_WAIT) return;
      if (r == SX_FAIL) {
        senStep = 0;
        if (++senFails >= 5) senGone("stopped answering");
        return;
      }
      senFails = 0;
      if (r == SX_OK && senStep) senTake(senStep, now);
      if (senStep == 0 && !(r == SX_OK && (senW[0] & 0xFF))) return;   // nothing new yet
      if (++senStep >= 5) senStep = 0;
      return;
    }

    case SEN_OPSTOP:                                   // stop, then wait the 1.4 s out
      r = senXfer(0x0104, nullptr, 0, 0, 1400);
      if (r == SX_WAIT) return;
      if (r != SX_OK) {
        senOp = SOP_NONE; senBusy = nullptr;
        senNote("could not stop the measurement");
        senState = SEN_RUN; senStep = 0;
        return;
      }
      senState = SEN_OPDO; senStep = 0;
      return;

    case SEN_OPDO: {
      if (!senDoOp(now)) return;
      const uint8_t op = senOp;
      senOp = SOP_NONE; senStep = 0;
      if (op > SOP_LIVE)        { senState = SEN_RUN; senTm = now; }     // never stopped
      else if (op == SOP_RESET) { senState = SEN_PROBE; senTm = now; senToldRun = false; }
      else                        senState = SEN_IDLECFG;   // re-read settings, then restart
      return;
    }
  }
}

//  Queue a request. False, with the reason in *why, when it cannot run now.
static bool senRequest(uint8_t op, const int16_t* args, uint8_t nArgs, const char** why) {
  if (!senHave)            { *why = "no SEN69C"; return false; }
  if (senOp != SOP_NONE || senState != SEN_RUN)
                           { *why = "busy - try again in a moment"; return false; }
  const uint32_t up = millis() - senStartMs;
  if ((op == SOP_ASC || op == SOP_FRC || op == SOP_CO2RESET) && up < 25000)
                           { *why = "CO2 part still conditioning - wait 25 s after a start"; return false; }
  if (op == SOP_FRC && up < 180000)
                           { *why = "recalibration needs 3+ minutes of measuring first"; return false; }
  for (uint8_t i = 0; i < nArgs && i < 6; i++) senOpArg[i] = args[i];
  senOp = op;
  static const char* const kBusy[] = { "", "FAN CLEANING", "SHT HEATER", "CO2 AUTO-CAL", "CO2 RECAL",
                                       "ALTITUDE", "DEVICE RESET", "CO2 FACTORY RESET", "VOC TUNING",
                                       "VOC TUNING", "NOx TUNING", "NOx TUNING" };
  senBusy = op < SOP_LIVE ? kBusy[op] : nullptr;
  return true;
}

// ── AIR QUALITY page ──
static void airText(const char* s, int x, int y, int size, uint16_t col) {
  inst->setTextSize(size); inst->setTextColor(col); inst->setCursor(x, y); inst->print(s);
}
static void airCentre(const char* s, int y, int size, uint16_t col) {
  airText(s, (TFT_W - (int)strlen(s) * 6 * size) / 2, y, size, col);
}

static const char* const kAirLabel[SEN_NM] = { "PM1.0", "PM2.5", "PM4.0", "PM10", "CO2 ppm",
                                               "VOC idx", "NOx idx", "HCHO ppb", "TEMP", "RH %" };
static const char* const kAirChart[SEN_NM] = { "PM1.0 ug/m3", "PM2.5 ug/m3", "PM4.0 ug/m3", "PM10 ug/m3",
                                               "CO2 ppm", "VOC INDEX", "NOx INDEX", "HCHO ppb",
                                               "TEMP", "HUMIDITY %" };
//  Smallest chart range (display units) so noise is not magnified, and the
//  dotted line where the colour turns orange (NAN = none).
static const float kAirMinRange[SEN_NM] = { 5, 5, 5, 5, 100, 20, 5, 10, 1, 5 };
static const float kAirRef[SEN_NM]      = { NAN, 35.4f, NAN, 154, 1000, NAN, NAN, 80, NAN, NAN };

//  Display bands, 0 best .. 4 worst; -1 = no band. PM2.5 and PM10 follow the
//  US EPA AQI breakpoints (PM2.5 as revised in 2024): good / moderate /
//  sensitive groups / unhealthy and up. CO2 uses the GAS SENSORS page's
//  bands. HCHO: the WHO 30-minute guideline is 0.1 mg/m3, about 80 ppb. VOC
//  and NOx are Sensirion's RELATIVE indices (VOC 100 = this room's usual
//  air, NOx 1 = clean), so their bands are only a rough guide.
static int8_t airLevel(uint8_t m, float v) {
  if (isnan(v)) return -1;
  switch (m) {
    case AIR_PM25: return v <= 9.0f ? 0 : v <= 35.4f ? 2 : v <= 55.4f ? 3 : 4;
    case AIR_PM10: return v <= 54   ? 0 : v <= 154   ? 2 : v <= 254   ? 3 : 4;
    case AIR_CO2:  return v < 800   ? 0 : v < 1000   ? 1 : v < 1400   ? 2 : v < 2000 ? 3 : 4;
    case AIR_VOC:  return v <= 150  ? 0 : v <= 250   ? 2 : v <= 400   ? 3 : 4;
    case AIR_NOX:  return v < 50    ? 0 : v < 100    ? 2 : v < 300    ? 3 : 4;
    case AIR_HCHO: return v <= 30   ? 0 : v <= 80    ? 2 : v <= 200   ? 3 : 4;
    default:       return -1;                          // PM1.0, PM4.0, temperature, humidity
  }
}
static const uint16_t    kAirLvlCol[5]  = { NEON_GREEN, NEON_CYAN, NEON_YELLOW, NEON_ORANGE, NEON_RED };
static const char* const kAirLvlName[5] = { "GOOD", "FAIR", "MODERATE", "POOR", "BAD" };

static uint16_t airCol(uint8_t m, float v) {
  const int8_t l = airLevel(m, v);
  if (l >= 0) return kAirLvlCol[l];
  if (isnan(v)) return CYBER_DIMTXT;
  return m == AIR_TEMP ? NEON_MAGENTA : NEON_CYAN;
}
//  A value as shown, in display units.
static void airFmt(char* b, size_t n, uint8_t m, float v) {
  if (isnan(v)) { strlcpy(b, "--", n); return; }
  switch (m) {
    case AIR_TEMP: snprintf(b, n, "%.1f", tconv(v)); return;
    case AIR_CO2: case AIR_VOC: case AIR_NOX: case AIR_RH: snprintf(b, n, "%.0f", v); return;
    default:       snprintf(b, n, v < 100 ? "%.1f" : "%.0f", v); return;   // PM, HCHO
  }
}

//  What the footer says while measuring is paused for a request.
static bool airBusyText(char* b, size_t n) {
  if (!senBusy) return false;
  const uint32_t now = millis();
  int32_t left = (int32_t)(senRestUntil - now);
  const int32_t co2 = senStartMs ? (int32_t)(senStartMs + 24500 - now) : 0;
  if (co2 > left) left = co2;
  if (senState == SEN_START && left > 0)
    snprintf(b, n, "%s - measuring again in %lds", senBusy, (long)((left + 999) / 1000));
  else snprintf(b, n, "%s...", senBusy);
  return true;
}

static void airDrawCharts() {
  char b[48];
  const int gap = 4, tw = (TFT_W - 12 - 4 * gap) / 5, th = 34, y0 = 30, y1 = y0 + th + 3;
  for (uint8_t m = 0; m < SEN_NM; m++) {
    const int x = 6 + (m % 5) * (tw + gap), y = m < 5 ? y0 : y1;
    const bool sel = m == airMetric;
    inst->drawRoundRect(x, y, tw, th, 4, sel ? NEON_CYAN : CYBER_GRID);
    if (sel) inst->drawRoundRect(x + 1, y + 1, tw - 2, th - 2, 3, NEON_CYAN);
    if (m == AIR_TEMP) snprintf(b, sizeof b, "TEMP %c", tunit());
    else strlcpy(b, kAirLabel[m], sizeof b);
    airText(b, x + 4, y + 4, 1, sel ? NEON_CYAN : CYBER_DIMTXT);
    airFmt(b, sizeof b, m, senV[m]);
    const bool big = (int)strlen(b) * 12 <= tw - 8;
    airText(b, x + 4, big ? y + 15 : y + 19, big ? 2 : 1, airCol(m, senV[m]));
  }

  //  Chart of the selected tile over the chosen span (newest at the right).
  const int cx = 6, cy = y1 + th + 4, cw = TFT_W - 12, ch = TFT_H - 17 - cy;
  inst->drawRect(cx, cy, cw, ch, CYBER_GRID);
  static const char* const kSpan[3] = { "10 MIN", "30 MIN", "2 H" };
  const uint32_t want = kAirSpanS[airSpan] / 5;
  const uint32_t n = senH ? min(want, min(senHN, (uint32_t)SEN_HIST)) : 0;
  const float* h = senH ? senH + airMetric * SEN_HIST : nullptr;
  auto val = [&](uint32_t k) {
    const float v = h[k % SEN_HIST];
    return airMetric == AIR_TEMP && !isnan(v) ? tconv(v) : v;
  };
  float lo = 1e9f, hi = -1e9f;
  uint32_t good = 0;
  for (uint32_t k = senHN - n; k < senHN; k++) {
    const float v = val(k);
    if (isnan(v)) continue;
    lo = fminf(lo, v); hi = fmaxf(hi, v); good++;
  }
  if (good >= 2) {
    const float minRange = kAirMinRange[airMetric];
    if (hi - lo < minRange) { const float mid = (hi + lo) / 2; lo = mid - minRange / 2; hi = mid + minRange / 2; }
    auto yOf = [&](float v) { return cy + ch - 3 - (int)lroundf((v - lo) / (hi - lo) * (ch - 6)); };
    const float ref = kAirRef[airMetric];
    if (!isnan(ref) && lo < ref && hi > ref)
      for (int x = cx + 2; x < cx + cw - 2; x += 4) inst->drawPixel(x, yOf(ref), NEON_YELLOW);
    uint16_t lineCol = airCol(airMetric, senV[airMetric]);
    if (lineCol == CYBER_DIMTXT) lineCol = NEON_CYAN;
    int px = 0, py = 0;
    bool pen = false;
    for (uint32_t j = 0; j < n; j++) {
      const float v = val(senHN - n + j);
      if (isnan(v)) { pen = false; continue; }                   // a gap stays a gap
      const int x = cx + cw - 2 - (int)((uint64_t)(n - 1 - j) * (cw - 4) / (want - 1));   // time-true x
      const int y = yOf(v);
      if (pen) inst->drawLine(px, py, x, y, lineCol); else inst->drawPixel(x, y, lineCol);
      px = x; py = y; pen = true;
    }
    snprintf(b, sizeof b, (airMetric == AIR_TEMP || hi - lo < 20) ? "%.1f-%.1f" : "%.0f-%.0f", lo, hi);
    airText(b, cx + cw - 4 - (int)strlen(b) * 6, cy + 3, 1, CYBER_DIMTXT);
  } else {
    airText("collecting...", cx + 6, cy + ch / 2 - 4, 1, CYBER_DIMTXT);
  }
  if (airMetric == AIR_TEMP) snprintf(b, sizeof b, "TEMP %c  %s", tunit(), kSpan[airSpan]);
  else snprintf(b, sizeof b, "%s  %s", kAirChart[airMetric], kSpan[airSpan]);
  airText(b, cx + 4, cy + 3, 1, CYBER_DIMTXT);
}

#define AIR_ACTIONS 5
static void airDrawDetails() {
  char b[64];
  const int lx = 6, rx = TFT_W / 2 + 4, valX = lx + 120;
  //  Left: particle counts and the raw signals.
  int y = 31;
  airText("PARTICLES / cm3", lx, y, 1, NEON_MAGENTA); y += 11;
  static const char* const kNc[5] = { "PM0.5", "PM1.0", "PM2.5", "PM4.0", "PM10" };
  for (int i = 0; i < 5; i++, y += 9) {
    airText(kNc[i], lx, y, 1, CYBER_DIMTXT);
    if (isnan(senNc[i])) strlcpy(b, "--", sizeof b); else snprintf(b, sizeof b, "%.1f", senNc[i]);
    airText(b, valX - (int)strlen(b) * 6, y, 1, NEON_CYAN);
  }
  y += 4;
  airText("RAW SIGNALS", lx, y, 1, NEON_MAGENTA); y += 11;
  airText("HUMIDITY", lx, y, 1, CYBER_DIMTXT);
  if (isnan(senRawRh)) strlcpy(b, "--", sizeof b); else snprintf(b, sizeof b, "%.2f %%", senRawRh);
  airText(b, valX - (int)strlen(b) * 6, y, 1, NEON_CYAN); y += 9;
  airText("TEMP", lx, y, 1, CYBER_DIMTXT);
  if (isnan(senRawT)) strlcpy(b, "--", sizeof b); else snprintf(b, sizeof b, "%.2f %c", tconv(senRawT), tunit());
  airText(b, valX - (int)strlen(b) * 6, y, 1, NEON_CYAN); y += 9;
  airText("VOC TICKS", lx, y, 1, CYBER_DIMTXT);
  if (senRawVoc < 0) strlcpy(b, "--", sizeof b); else snprintf(b, sizeof b, "%ld", (long)senRawVoc);
  airText(b, valX - (int)strlen(b) * 6, y, 1, NEON_CYAN); y += 9;
  airText("NOx TICKS", lx, y, 1, CYBER_DIMTXT);
  if (senRawNox < 0) strlcpy(b, "--", sizeof b); else snprintf(b, sizeof b, "%ld", (long)senRawNox);
  airText(b, valX - (int)strlen(b) * 6, y, 1, NEON_CYAN);

  //  Right: the device, its status, and the actions.
  y = 31;
  airText("DEVICE", rx, y, 1, NEON_MAGENTA);
  snprintf(b, sizeof b, "%s fw %u.%u", senName[0] ? senName : "?", senFwMaj, senFwMin);
  airText(b, rx + 42, y, 1, senIsSen69c ? NEON_CYAN : NEON_YELLOW); y += 11;
  snprintf(b, sizeof b, "S/N %s", senSerial[0] ? senSerial : "?");
  airText(b, rx, y, 1, CYBER_DIMTXT); y += 9;
  const uint32_t up = senStartMs ? (millis() - senStartMs) / 1000 : 0;
  snprintf(b, sizeof b, "UP %lu:%02lu:%02lu  ALT %s", (unsigned long)(up / 3600), (unsigned long)(up / 60 % 60),
           (unsigned long)(up % 60), senAltM < 0 ? "?" : "");
  if (senAltM >= 0) snprintf(b + strlen(b), sizeof b - strlen(b), "%ldm", (long)senAltM);
  airText(b, rx, y, 1, CYBER_DIMTXT); y += 9;
  char f[64]; senFlagText(senStatus, f, sizeof f);
  airText("STATUS", rx, y, 1, CYBER_DIMTXT);
  const int fx = rx + 42, fcols = (TFT_W - 6 - fx) / 6;
  if ((int)strlen(f) > fcols) {                        // wrap at a space
    int cut = fcols; while (cut > 0 && f[cut] != ' ') cut--;
    if (cut <= 0) cut = fcols;
    char a[64]; strlcpy(a, f, (size_t)cut + 1);
    airText(a, fx, y, 1, NEON_RED); y += 9;
    airText(f + cut + (f[cut] == ' '), fx, y, 1, NEON_RED);
  } else airText(f, fx, y, 1, senStatus ? NEON_RED : NEON_GREEN);
  y += 13;
  for (int i = 0; i < AIR_ACTIONS; i++, y += 11) {
    switch (i) {
      case 0: strlcpy(b, "BACK TO CHARTS", sizeof b); break;
      case 1: strlcpy(b, "FAN CLEANING", sizeof b); break;
      case 2: strlcpy(b, "SHT HEATER", sizeof b); break;
      case 3: snprintf(b, sizeof b, "CO2 AUTO-CAL %s", senAsc < 0 ? "?" : senAsc ? "ON" : "OFF"); break;
      default: strlcpy(b, "CLEAR STATUS", sizeof b); break;
    }
    const bool sel = i == airSel;
    if (sel) {
      inst->fillRect(rx - 2, y - 2, TFT_W - 6 - (rx - 2), 11, CYBER_GRID);
      airText(">", rx, y, 1, NEON_MAGENTA);
    }
    airText(b, rx + 9, y, 1, sel ? WHITE : NEON_CYAN);
  }
}

void uiViewAir() {
  inst->fillScreen(CYBER_BG);
  ui3DHeader(airDetails ? "AIR QUALITY INFO" : "AIR QUALITY");
  char b[64];

  if (!senHave) {
    airCentre("NO AIR SENSOR", 62, 2, NEON_RED);
    airCentre("SEN69C not answering at I2C 0x6B", 88, 1, CYBER_DIMTXT);
    airCentre("checking again every 10 s", 100, 1, CYBER_DIMTXT);
    uiBlit(); return;
  }

  //  Overall verdict: the worst banded reading, in the header.
  int8_t worst = -1;
  for (uint8_t m = 0; m < SEN_NM; m++) { const int8_t l = airLevel(m, senV[m]); if (l > worst) worst = l; }
  if (senReads && worst >= 0) {
    const char* w = kAirLvlName[worst];
    const int pw = (int)strlen(w) * 6 + 12, px = TFT_W - 15 - pw, py = MENU_HEAD_Y + (MENU_HEAD_H - 13) / 2;
    inst->fillRoundRect(px, py, pw, 13, 4, kAirLvlCol[worst]);
    airText(w, px + 6, py + 3, 1, CYBER_BG);
  }

  if (!senReads) {
    airCentre("SEN69C FOUND", 58, 2, NEON_CYAN);
    if (!airBusyText(b, sizeof b))
      snprintf(b, sizeof b, "first reading in a few seconds%.*s", (int)((millis() / 400) % 4), "...");
    airCentre(b, 84, 1, CYBER_DIMTXT);
    if (!senIsSen69c) {
      snprintf(b, sizeof b, "but it reports \"%s\" / %s", senName, senType);
      airCentre(b, 100, 1, NEON_YELLOW);
    }
    uiBlit(); return;
  }

  if (airDetails) airDrawDetails(); else airDrawCharts();

  //  Footer: a running request, then a fresh result, then faults (DETAILS
  //  has its own status line), then what is still warming up, then help.
  uint16_t col = CYBER_DIMTXT;
  static const char* const kShort[SEN_NM] = { "PM1.0", "PM2.5", "PM4.0", "PM10", "CO2",
                                              "VOC", "NOx", "HCHO", "TEMP", "RH" };
  char warm[48] = "";
  for (uint8_t m = 0; m < SEN_NM; m++)
    if (isnan(senV[m])) { strlcat(warm, " ", sizeof warm); strlcat(warm, kShort[m], sizeof warm); }
  if (airBusyText(b, sizeof b)) col = NEON_YELLOW;
  else if ((int32_t)(airMsgUntil - millis()) > 0) { strlcpy(b, airMsg, sizeof b); col = NEON_YELLOW; }
  else if (senStatus && !airDetails) {
    char f[48]; senFlagText(senStatus, f, sizeof f);
    snprintf(b, sizeof b, "SENSOR FAULT: %s", f);
    col = NEON_RED;
  } else if (warm[0] && !airDetails) {
    snprintf(b, sizeof b, "WARMING UP:%s", warm);
  } else if (airDetails) {
    static const char* const kHelp[AIR_ACTIONS] = {
      "ENTER back to charts   UP/DN pick   LEFT back",
      "ENTER: fan at full speed 10 s to blow out dust",
      "ENTER: heat the RH sensor 1 s (readings pause 22 s)",
      "ENTER: CO2 automatic self-calibration on/off",
      "ENTER: clear the sticky error flags" };
    strlcpy(b, kHelp[airSel], sizeof b);
  } else {
    snprintf(b, sizeof b, "ENTER next  UP/DN span   %lus ago", (unsigned long)((millis() - senLastMs) / 1000));
  }
  airCentre(b, TFT_H - 13, 1, col);
  uiBlit();
}

static void airRun(uint8_t sel) {
  const char* why = nullptr;
  int16_t a = 0;
  bool ok = true;
  switch (sel) {
    case 0: airDetails = false; return;
    case 1: ok = senRequest(SOP_CLEAN, nullptr, 0, &why); break;
    case 2: ok = senRequest(SOP_HEAT, nullptr, 0, &why); break;
    case 3: a = senAsc == 1 ? 0 : 1;                   // unknown -> ON, the recommended setting
            ok = senRequest(SOP_ASC, &a, 1, &why); break;
    default: ok = senRequest(SOP_CLEAR, nullptr, 0, &why); break;
  }
  if (!ok) senNote("%s", why);
}

static void airAction(UiAction a) {
  if (airDetails) {
    switch (a) {
      case ACT_BACK:   airDetails = false; return;
      case ACT_PREV:   airSel = (airSel + AIR_ACTIONS - 1) % AIR_ACTIONS; return;
      case ACT_NEXT:   airSel = (airSel + 1) % AIR_ACTIONS; return;
      case ACT_SELECT: airRun(airSel); return;
      case ACT_RIGHT:  saveJpeg(); return;
      default: return;
    }
  }
  switch (a) {
    case ACT_BACK:   uiSel = UI_AIR - 1; uiEnter(UI_MENU); return;
    case ACT_SELECT: if (++airMetric >= SEN_NM) { airMetric = 0; airDetails = true; airSel = 0; } return;
    case ACT_PREV:   if (airSpan < 2) airSpan++; return;
    case ACT_NEXT:   if (airSpan > 0) airSpan--; return;
    case ACT_RIGHT:  saveJpeg(); return;
    default: return;
  }
}

//  Console "air ...".
void airConsole(const char* arg) {
  while (*arg == ' ') arg++;
  char w[12] = "";
  int n = 0;
  while (arg[n] && arg[n] != ' ' && n < (int)sizeof w - 1) { w[n] = arg[n]; n++; }
  w[n] = 0;
  const char* rest = arg + n;
  while (*rest == ' ') rest++;

  if (!strcmp(w, "help")) {
    Serial.println(F("air                     SEN69C status and every reading"));
    Serial.println(F("air clean               fan cleaning (10 s at full speed)"));
    Serial.println(F("air heat                SHT heater, 1 s at 200 mW (fixes humidity creep; pauses ~22 s)"));
    Serial.println(F("air asc on|off          CO2 automatic self-calibration (needs fresh air weekly)"));
    Serial.println(F("air frc <ppm>           CO2 forced recalibration, e.g. 420 outdoors (after 3+ min)"));
    Serial.println(F("air alt <m>             altitude for CO2 pressure compensation (0-3000)"));
    Serial.println(F("air hpa <hPa>           ambient pressure instead (700-1200)"));
    Serial.println(F("air toff <C>            temperature offset for self-heating in a case (-50..50)"));
    Serial.println(F("air voc [6 values]      VOC index tuning: offset learnOff learnGain gating stdInit gain"));
    Serial.println(F("air nox [6 values]      NOx index tuning (learnGain must be 12, stdInit 50)"));
    Serial.println(F("air clear               read and clear the status flags"));
    Serial.println(F("air reset               device reset (settings back to default, VOC/NOx relearn)"));
    Serial.println(F("air co2reset            CO2 factory reset (erases recalibration history)"));
    return;
  }
  if (w[0]) {
    int16_t a[6] = { 0 };
    uint8_t op = SOP_NONE, na = 0;
    const int v = atoi(rest);
    if      (!strcmp(w, "clean"))    op = SOP_CLEAN;
    else if (!strcmp(w, "heat"))     op = SOP_HEAT;
    else if (!strcmp(w, "clear"))    op = SOP_CLEAR;
    else if (!strcmp(w, "reset"))    op = SOP_RESET;
    else if (!strcmp(w, "co2reset")) op = SOP_CO2RESET;
    else if (!strcmp(w, "asc")) {
      if (strncmp(rest, "on", 2) && strncmp(rest, "off", 3)) { Serial.println("air asc on|off"); return; }
      op = SOP_ASC; a[0] = !strncmp(rest, "on", 2); na = 1;
    } else if (!strcmp(w, "frc")) {
      if (v < 400 || v > 2000) { Serial.println("air frc <ppm>   e.g. air frc 420 (after 3+ min in fresh outdoor air)"); return; }
      op = SOP_FRC; a[0] = v; na = 1;
    } else if (!strcmp(w, "alt")) {
      if (!*rest || v < 0 || v > 3000) { Serial.println("air alt <m>   0-3000"); return; }
      op = SOP_ALT; a[0] = v; na = 1;
    } else if (!strcmp(w, "hpa")) {
      if (v < 700 || v > 1200) { Serial.println("air hpa <hPa>   700-1200"); return; }
      op = SOP_HPA; a[0] = v; na = 1;
    } else if (!strcmp(w, "toff")) {
      const float c = atof(rest);
      if (!*rest || c < -50 || c > 50) { Serial.println("air toff <C>   e.g. air toff -1.5"); return; }
      op = SOP_TOFF; a[0] = (int16_t)lroundf(c * 200.0f); na = 4;   // slope, time constant, slot 0
    } else if (!strcmp(w, "voc") || !strcmp(w, "nox")) {
      const bool voc = w[0] == 'v';
      int p[6];
      const int got = sscanf(rest, "%d %d %d %d %d %d", &p[0], &p[1], &p[2], &p[3], &p[4], &p[5]);
      if (got <= 0) op = voc ? SOP_VOCGET : SOP_NOXGET;
      else if (got != 6) { Serial.println("air voc|nox <offset> <learnOff h> <learnGain h> <gating min> <stdInit> <gain>"); return; }
      else {
        //  Ranges from the datasheet; out of range, the sensor ignores the lot.
        const bool okR = p[0] >= 1 && p[0] <= 250 && p[1] >= 1 && p[1] <= 1000 && p[3] >= 0 && p[3] <= 3000 &&
                         p[5] >= 1 && p[5] <= 1000 &&
                         (voc ? (p[2] >= 1 && p[2] <= 1000 && p[4] >= 10 && p[4] <= 5000) : (p[2] == 12 && p[4] == 50));
        if (!okR) { Serial.println(voc ? "air voc: offset 1-250, learn 1-1000 h, gating 0-3000 min, stdInit 10-5000, gain 1-1000 (defaults 100 12 12 180 50 230)"
                                       : "air nox: offset 1-250, learnOff 1-1000 h, learnGain 12, gating 0-3000 min, stdInit 50, gain 1-1000 (defaults 1 12 12 720 50 230)"); return; }
        for (int i = 0; i < 6; i++) a[i] = (int16_t)p[i];
        op = voc ? SOP_VOCSET : SOP_NOXSET; na = 6;
      }
    } else { Serial.println("air: unknown - try \"air help\""); return; }
    const char* why = nullptr;
    if (!senRequest(op, a, na, &why)) Serial.printf("air: %s\n", why);
    else if (op < SOP_LIVE) Serial.println("air: stopping the measurement for that - readings pause");
    return;
  }

  //  Plain "air": everything.
  if (!senHave) { Serial.printf("air: SEN69C not found @0x%02X (retrying every 10 s)\n", SEN_ADDR); return; }
  const uint32_t up = senStartMs ? (millis() - senStartMs) / 1000 : 0;
  Serial.printf("air: \"%s\" type %s @0x%02X, serial %s, firmware %u.%u%s\n", senName, senType, SEN_ADDR,
                senSerial, senFwMaj, senFwMin, senIsSen69c ? "" : "  (not identified as SEN69C)");
  Serial.printf("  measuring %lum%02lus, %lu readings, %lu CRC errors\n", (unsigned long)(up / 60),
                (unsigned long)(up % 60), (unsigned long)senReads, (unsigned long)senErrs);
  char b[16], f[64];
  if (senReads) {
    Serial.print("  mass ug/m3:");
    for (int i = 0; i < 4; i++) { airFmt(b, sizeof b, i, senV[i]); Serial.printf("  %s %s", kAirLabel[i], b); }
    Serial.print("\n  count /cm3: ");
    static const char* const kNc[5] = { "PM0.5", "PM1.0", "PM2.5", "PM4.0", "PM10" };
    for (int i = 0; i < 5; i++) Serial.printf(" %s %.1f", kNc[i], senNc[i]);
    Serial.println();
    airFmt(b, sizeof b, AIR_CO2, senV[AIR_CO2]);   Serial.printf("  CO2 %s ppm", b);
    airFmt(b, sizeof b, AIR_HCHO, senV[AIR_HCHO]); Serial.printf("   HCHO %s ppb", b);
    airFmt(b, sizeof b, AIR_VOC, senV[AIR_VOC]);   Serial.printf("   VOC index %s", b);
    airFmt(b, sizeof b, AIR_NOX, senV[AIR_NOX]);   Serial.printf("   NOx index %s\n", b);
    airFmt(b, sizeof b, AIR_TEMP, senV[AIR_TEMP]); Serial.printf("  %s %c", b, tunit());
    airFmt(b, sizeof b, AIR_RH, senV[AIR_RH]);     Serial.printf("   %s %%RH", b);
    Serial.printf("   raw: %.2f %c  %.2f %%RH  VOC %ld  NOx %ld ticks   (%lu s ago)\n",
                  tconv(senRawT), tunit(), senRawRh, (long)senRawVoc, (long)senRawNox,
                  (unsigned long)((millis() - senLastMs) / 1000));
  } else Serial.println("  waiting for the first reading");
  senFlagText(senStatus, f, sizeof f);
  Serial.printf("  status 0x%08lX: %s\n", (unsigned long)senStatus, f);
  Serial.printf("  CO2 auto-cal %s, altitude %s m, pressure %s hPa (read while idle)\n",
                senAsc < 0 ? "?" : senAsc ? "ON" : "OFF",
                senAltM < 0 ? "?" : String(senAltM).c_str(), senHpa < 0 ? "?" : String(senHpa).c_str());
  if (!isnan(senHeatT)) Serial.printf("  last SHT heater cycle: %.2f %c, %.2f %%RH\n", tconv(senHeatT), tunit(), senHeatRh);
}
#endif  // AIR_ENABLE

static void tankAction(UiAction a) {
  if (!ptReady) { if (a == ACT_BACK) { uiSel = UI_TANK - 1; uiEnter(UI_MENU); } return; }
  tank_handled(&ptTank);
  if (ptHand) { ptHandMs = millis(); return; }   // held-state input owns the pad
  switch (a) {
    case ACT_BACK:   uiSel = UI_TANK - 1; uiEnter(UI_MENU); break;
    case ACT_RIGHT:  tank_feed(&ptTank, TANK_W * (0.2f + 0.6f * (esp_random() % 1000) / 1000.0f), 4); break;
    case ACT_PREV:   ptToggleLight(); break;     // saved with the tank
    case ACT_SELECT: ptLatch = true;             // fall through: summon the fingertip
    case ACT_NEXT:   ptHand = true; ptHandMs = millis(); break;
    default: break;
  }
}

//  Repaint whichever view owns the panel. The camera is absent on purpose —
//  loop() streams that one straight from the sensor buffer.
void uiDraw() {
  if (!inst) return;
  switch (uiView) {
    case UI_MENU:    uiViewMenu();    break;
    case UI_THERMAL: uiViewThermal(); break;
    case UI_CUBE:    uiViewCube();    break;
    case UI_COMPASS: uiViewCompass(); break;
    case UI_FILES:   uiViewFiles();   break;
    case UI_WIFI:     uiViewWifi();     break;
#if BLE_ENABLE
    case UI_BLE:      uiViewBle();      break;
#endif
#if GPS_ENABLE
    case UI_GPS:      uiViewGps();      break;
#endif
#if VIDEO_ENABLE
    case UI_IMAGE:    uiViewImage();    break;
#endif
    case UI_SETTINGS: uiViewSettings(); break;
    case UI_GAME:     uiViewGame();     break;
    case UI_BLOCKS:   uiViewBlocks();   break;
#if SERVO_ENABLE
    case UI_SERVO:    uiViewServoTest(); break;
    case UI_IMUSERVO: uiViewImuServo(); break;
#endif
    case UI_TANK:     uiViewTank();     break;
    case UI_SAND:     uiViewSand();     break;
    case UI_CLOCK:    uiViewClock();    break;
#if GAS_ENABLE
    case UI_GAS:      uiViewGas();      break;
#endif
#if AIR_ENABLE
    case UI_AIR:      uiViewAir();      break;
#endif
#if AUDIO_ENABLE
    case UI_MUSIC:    uiViewMusic();    break;
    case UI_RECORDER: uiViewRecorder(); break;
#endif
    case UI_DOOM:     uiViewDoom();     break;
    case UI_RADAR:    uiViewRadar();    break;
#if SERVO_ENABLE
    case UI_SEQ:      uiViewSeq();      break;
#endif
#if WEB_ENABLE && SERVO_ENABLE
    case UI_NETPICK:  uiViewNetPick();  break;
    case UI_KEYB:     uiViewKeyb();     break;
#endif
    //  UI_FUSION renders from loop() with a live camera frame, so uiDraw()
    //  has nothing to do for it — leave the last fused frame on screen.
    //  Without a working IR sensor it shows the thermal view's fault instead.
    case UI_FUSION:
#if MLX_ENABLE
      if (!mlxAlive()) uiViewThermal();
#endif
      break;
    default: break;
  }
}

void uiEnter(UiView v) {
  if (v == UI_FILES) filesScan();   // read the card once, on the way in
  if (v == UI_WIFI)  wifiStartScan();
  if (v == UI_SETTINGS) { setPage = SET_ROOT; setSel = 0; }
  if (v == UI_GAME) gameEnter();
  if (v == UI_BLOCKS) blocksEnter();
#if SERVO_ENABLE
  if (v == UI_SERVO) servoTestEnter();
  if (v == UI_IMUSERVO) imuServoEnter();
#endif
  //  The fish tank only lives while it is on screen; leaving saves it.
  if (uiView == UI_TANK && v != UI_TANK) tankLeave();
  if (v == UI_TANK && uiView != UI_TANK) tankEnter();
  if (uiView == UI_SAND && v != UI_SAND) sandLeave();
  if (v == UI_SAND && uiView != UI_SAND) sandEnter();
  if (uiView == UI_RADAR && v != UI_RADAR) radarLeave();
  if (v == UI_RADAR && uiView != UI_RADAR) radarEnter();
#if GPS_ENABLE
  if (uiView == UI_GPS && v != UI_GPS) gmapLeave();
  if (v == UI_GPS && uiView != UI_GPS) gmapEnter();
#endif
#if AUDIO_ENABLE
  audViewChange(uiView, v);
  if (v == UI_DOOM) audShutdown();
#endif
  if (v == UI_DOOM) {
    doomScanned = false;                         // look at the card again
    if (uiView == UI_MENU) doomQuickStart();     // normally never returns
  }
#if SERVO_ENABLE
  //  Straight back to the player if a sequence is loaded, else the file list.
  if (v == UI_SEQ) { seqScanFiles(); seqListMode = !seqLoaded; }
  //  Leaving SEQUENCES (for the menu or any other view) stops playback, so
  //  servos never keep moving from a screen that no longer shows it. Moving
  //  between the player and the file list stays inside UI_SEQ and does not.
  if (uiView == UI_SEQ && v != UI_SEQ) seqStop();
#endif
#if WEB_ENABLE && SERVO_ENABLE
  if (v == UI_NETPICK) netStartScan();
#endif
#if VIDEO_ENABLE
  if (v == UI_IMAGE) imgDirty = true;
#endif
#if BLE_ENABLE
  //  BLE radio only runs while its view is open.
  if (v == UI_BLE) bleStart(); else if (bleScanning) bleStop();
#endif
  //  Only power the thermal scan (and its bus traffic) while it is on screen.
  mlxScanOn = (v == UI_THERMAL || v == UI_FUSION);
  uiView     = v;
  tft.fillScreen(BLACK);        // the camera leaves its own pixels behind
  uiLastDraw = 0;               // repaint on the very next pass
}

//  The only place that knows what a button MEANS. Five buttons later map
//  straight onto these five actions and nothing else changes.
void uiAction(UiAction a) {
  uiNoteActivity();
  //  Views with their own button meanings (lists with players, a keyboard
  //  where LEFT/RIGHT move the cursor) take every action themselves.
#if SERVO_ENABLE
  if (uiView == UI_SEQ)     { seqAction(a); uiLastDraw = 0; return; }
#endif
#if WEB_ENABLE && SERVO_ENABLE
  if (uiView == UI_NETPICK) { netAction(a); uiLastDraw = 0; return; }
  if (uiView == UI_KEYB)    { kbAction(a);  uiLastDraw = 0; return; }
#endif
  if (uiView == UI_GAME)    { gameAction(a); uiLastDraw = 0; return; }
  if (uiView == UI_BLOCKS)  { blocksAction(a); uiLastDraw = 0; return; }
#if SERVO_ENABLE
  if (uiView == UI_SERVO)   { servoTestAction(a); uiLastDraw = 0; return; }
  if (uiView == UI_IMUSERVO){ imuServoAction(a); uiLastDraw = 0; return; }
#endif
  if (uiView == UI_TANK)    { tankAction(a); return; }
  if (uiView == UI_SAND)    { sandAction(a); return; }
  if (uiView == UI_CLOCK)   { clockAction(a); uiLastDraw = 0; return; }
#if GAS_ENABLE
  if (uiView == UI_GAS)     { gasAction(a); uiLastDraw = 0; return; }
#endif
#if AIR_ENABLE
  if (uiView == UI_AIR)     { airAction(a); uiLastDraw = 0; return; }
#endif
#if AUDIO_ENABLE
  if (uiView == UI_MUSIC)    { musicAction(a);    uiLastDraw = 0; return; }
  if (uiView == UI_RECORDER) { recorderAction(a); uiLastDraw = 0; return; }
#endif
  if (uiView == UI_DOOM)    { doomAction(a); uiLastDraw = 0; return; }
  if (uiView == UI_RADAR)   { radarAction(a); uiLastDraw = 0; return; }
#if GPS_ENABLE
  if (uiView == UI_GPS)     { gpsAction(a); uiLastDraw = 0; return; }
#endif
  switch (a) {
    case ACT_NEXT:
      if (uiView == UI_MENU) { uiSel = (uiSel + 1) % UI_ITEMS; uiLastDraw = 0; }
      else if (uiView == UI_SETTINGS) {
        setSel = (setSel + 1) % kSetCount[setPage]; uiLastDraw = 0;
      }
      //  A list needs scrolling more than it needs to be skipped past, so
      //  here the short press pages. Long press still returns to the menu.
      else if (uiView == UI_FILES) {
        if (fileCount) { fileSel = (fileSel + 1) % fileCount;
                         filePage = fileSel / FILES_ROWS; } uiLastDraw = 0; }
#if VIDEO_ENABLE
      else if (uiView == UI_IMAGE) { imgAction(ACT_NEXT); uiLastDraw = 0; }
#endif
      else if (uiView == UI_WIFI)  { wifiNextPage();  uiLastDraw = 0; }
#if BLE_ENABLE
      else if (uiView == UI_BLE)   { bleNextPage();   uiLastDraw = 0; }
#endif
      //  Cycle within the menu's views only (it used to run on into the
      //  image viewer and other inner screens).
      else {
        const int v = uiView == UI_FUSION ? UI_THERMAL : uiView;
        uiEnter((UiView)(v + 1 > UI_ITEMS ? UI_CAMERA : v + 1));
      }
      break;
    case ACT_PREV:
      if (uiView == UI_MENU) { uiSel = (uiSel + UI_ITEMS - 1) % UI_ITEMS; uiLastDraw = 0; }
      else if (uiView == UI_SETTINGS) {
        uint8_t c = kSetCount[setPage]; setSel = (setSel + c - 1) % c; uiLastDraw = 0;
      }
      else if (uiView == UI_FILES) {
        if (fileCount) { fileSel = (fileSel + fileCount - 1) % fileCount;
                         filePage = fileSel / FILES_ROWS; } uiLastDraw = 0; }
#if VIDEO_ENABLE
      else if (uiView == UI_IMAGE) { imgAction(ACT_PREV); uiLastDraw = 0; }
#endif
      else if (uiView == UI_WIFI)  { wifiPrevPage(); uiLastDraw = 0; }
#if BLE_ENABLE
      else if (uiView == UI_BLE)   { blePrevPage(); uiLastDraw = 0; }
#endif
      else {
        const int v = uiView == UI_FUSION ? UI_THERMAL : uiView;
        uiEnter((UiView)(v <= UI_CAMERA ? UI_ITEMS : v - 1));
      }
      break;
    case ACT_RIGHT:
#if VIDEO_ENABLE
      //  In the image viewer, RIGHT moves between the overlay buttons rather
      //  than activating — ENTER is what activates. Everywhere else RIGHT is
      //  just a second ENTER, so fall through to ACT_SELECT.
      if (uiView == UI_IMAGE) { imgAction(ACT_RIGHT); uiLastDraw = 0; break; }
#endif
      //  The thermal views use ENTER to switch, so RIGHT is their screenshot.
      if (a == ACT_RIGHT && (uiView == UI_THERMAL || uiView == UI_FUSION)) { saveJpeg(); break; }
      // fall through
    case ACT_SELECT:
      if (uiView == UI_MENU) uiEnter((UiView)(uiSel + 1));
      else if (uiView == UI_SETTINGS) settingsActivate();
      //  Thermal camera: ENTER switches between the plain IR image and the
      //  enhanced view (IR blended over the camera picture).
      else if (uiView == UI_THERMAL) uiEnter(UI_FUSION);
      else if (uiView == UI_FUSION)  uiEnter(UI_THERMAL);
#if BLE_ENABLE
      //  Bluetooth after a crash (or a failed start): ENTER tries again.
      else if (uiView == UI_BLE && !bleScanning) { bleLast[0] = '\0'; bleStart(); uiLastDraw = 0; }
#endif
      //  Gyroscope: ENTER presses RESET — the cube turns to face you again.
      //  Heading only: UP stays on the real sky whatever the tilt.
      else if (uiView == UI_CUBE) {
        if (imuAlive()) {
          cubeAimHere();
          cubeResetMs = millis(); if (!cubeResetMs) cubeResetMs = 1;
        }
        uiLastDraw = 0;
      }
      //  Compass: ENTER presses CALIBRATE — wherever the board points now
      //  becomes north. Same tare and save as Settings' "SET NORTH HERE".
      else if (uiView == UI_COMPASS) {
        if (imuAlive()) {
          compassOffset = -imuYaw; settingsSaveNorth();
          compCalMs = millis(); if (!compCalMs) compCalMs = 1;
        }
        uiLastDraw = 0;
      }
      //  File browser: ENTER on a folder opens it (".." goes up); on a .jpg
      //  it opens the image viewer; other files do nothing.
      else if (uiView == UI_FILES) {
        if (fileSel < fileCount) {
          const FileEnt& fe = fileList[fileSel];
          if (fe.dir) {
            if (!strcmp(fe.name, "..")) filesUp(); else filesInto(fe.name);
          }
#if VIDEO_ENABLE
          else {
            const char* dot = strrchr(fe.name, '.');
            if (dot && (strcasecmp(dot, ".jpg") == 0 || strcasecmp(dot, ".jpeg") == 0)) {
              char path[128]; filesJoin(path, sizeof(path), fe.name);
              if (imgLoad(path)) uiEnter(UI_IMAGE);
            }
          }
#endif
        }
        uiLastDraw = 0;
      }
#if VIDEO_ENABLE
      else if (uiView == UI_IMAGE) imgAction(ACT_SELECT);
#endif
      else saveJpeg();                 // enter/right in any other view = screenshot
      break;
    case ACT_BACK:
      //  In settings, back steps out to the root page first, then to the menu.
      if (uiView == UI_SETTINGS && setPage != SET_ROOT) {
        setPage = SET_ROOT; setSel = 0; uiLastDraw = 0;
      }
#if VIDEO_ENABLE
      else if (uiView == UI_IMAGE) { imgAction(ACT_BACK); uiLastDraw = 0; }
#endif
      //  File browser: LEFT climbs one folder; only from the root does it
      //  leave for the menu.
      else if (uiView == UI_FILES && strcmp(fileDir, "/")) { filesUp(); uiLastDraw = 0; }
      else if (uiView != UI_MENU) {
        uiSel = (uint8_t)((uiView == UI_FUSION ? UI_THERMAL : uiView) - 1); uiEnter(UI_MENU);
      }
      break;
    default: break;
  }
}

// ── BOOT button ──────────────────────────────────────────────
//  Short press cycles, long press selects or goes back. Debounced by
//  requiring the level to hold still for BTN_DEBOUNCE_MS before it counts,
//  which is steadier than sampling on a fixed timer.
void btnBegin() { pinMode(BTN_BOOT_PIN, INPUT_PULLUP); }

#if PCF_ENABLE
// ── PCF8574 gamepad ──────────────────────────────────────────
//  Reads all five buttons in one byte, debounces the port, and turns each
//  press into a UiAction. The D-pad up/down auto-repeat when held (for
//  scrolling menus and paging lists); ENTER, LEFT and RIGHT fire once.
static bool pcfPresent = false;

//  P0..P4 -> action. LEFT backs out of a view; RIGHT and ENTER both select.
static const struct { uint8_t bit; UiAction act; bool repeat; } kPad[] = {
  { PCF_UP,    ACT_PREV,   true  },
  { PCF_DOWN,  ACT_NEXT,   true  },
  { PCF_LEFT,  ACT_BACK,   false },
  { PCF_RIGHT, ACT_RIGHT,  false },
  { PCF_ENTER, ACT_SELECT, false },
};
#define PCF_NBTN (sizeof(kPad) / sizeof(kPad[0]))

void pcfBegin() {
  if (i2cMutex && xSemaphoreTake(i2cMutex, pdMS_TO_TICKS(50)) == pdTRUE) {
    Wire.beginTransmission(PCF_ADDR);
    pcfPresent = (Wire.endTransmission() == 0);
    xSemaphoreGive(i2cMutex);
  }
  Serial.printf("PCF8574 gamepad @0x%02X %s\n", PCF_ADDR,
                pcfPresent ? "found" : "NOT FOUND (buttons via BOOT only)");
}

void pcfPoll() {
  if (!i2cMutex) return;

  static uint32_t nextMs = 0;
  uint32_t now = millis();
  if ((int32_t)(now - nextMs) < 0) return;
  nextMs = now + PCF_POLL_MS;

  //  A 1-byte read. If the bus is busy (MLX mid-frame) skip this tick rather
  //  than block loop(); the next tick will catch the gap.
  if (xSemaphoreTake(i2cMutex, pdMS_TO_TICKS(10)) != pdTRUE) { i2cBusyPcf++; return; }
  uint32_t t0 = micros();
  int n = Wire.requestFrom((int)PCF_ADDR, 1);
  uint8_t raw = (n == 1) ? Wire.read() : 0xFF;
  uint32_t dt = micros() - t0;
  xSemaphoreGive(i2cMutex);
  if (dt > i2cMaxUsPcf) i2cMaxUsPcf = dt;
  if (n != 1) { if (pcfPresent) i2cNoteFail("PCF8574 0x21", i2cErrPcf); return; }  // no ACK

  //  Debounce the whole port: adopt a new value only once it has held still.
  static uint8_t  lastRaw = 0xFF, stable = 0xFF;
  static uint32_t changeMs = 0;
  if (raw != lastRaw) { lastRaw = raw; changeMs = now; }
  if ((now - changeMs) >= PCF_DEBOUNCE_MS) stable = lastRaw;
  pcfStable = stable;                     // held state, for the game

  //  Edge + auto-repeat per button, off the debounced value.
  static bool     prev[PCF_NBTN] = { false };
  static uint32_t repeatAt[PCF_NBTN] = { 0 };
  for (uint8_t i = 0; i < PCF_NBTN; i++) {
    bool pressed = !(stable & (1 << kPad[i].bit));   // active low
    if (pressed && !prev[i]) {
      uiAction(kPad[i].act);
      repeatAt[i] = now + PCF_REPEAT_DELAY_MS;
    } else if (pressed && kPad[i].repeat && (int32_t)(now - repeatAt[i]) >= 0) {
      uiAction(kPad[i].act);
      repeatAt[i] = now + PCF_REPEAT_MS;
    }
    prev[i] = pressed;
  }
}
#endif  // PCF_ENABLE

void btnPoll() {
  static bool     lastRaw   = true;      // pulled up, so idle is HIGH
  static bool     stable    = true;
  static uint32_t edgeMs    = 0;
  static uint32_t downMs    = 0;
  static bool     longFired = false;

  bool     raw = digitalRead(BTN_BOOT_PIN);
  uint32_t now = millis();

  if (raw != lastRaw) { lastRaw = raw; edgeMs = now; return; }
  if (now - edgeMs < BTN_DEBOUNCE_MS) return;

  if (raw != stable) {
    stable = raw;
    if (!stable) {                       // pressed
      downMs    = now;
      longFired = false;
    } else if (!longFired) {             // released before the long threshold
      uiAction(ACT_NEXT);
    }
    return;
  }

  //  Fire the long press while the button is still down, so it is obvious
  //  it registered without having to let go first.
  if (!stable && !longFired && (now - downMs) >= BTN_LONG_MS) {
    longFired = true;
    uiAction(uiView == UI_MENU ? ACT_SELECT : ACT_BACK);
  }
}

#if BOOT_TEST_PATTERN
// Colour bars + border: proof that the panel is alive and correctly
// addressed, before anything camera-related can go wrong.
void bootTestPattern() {
  const uint16_t bars[4] = { NEON_RED, NEON_GREEN, 0x001F, WHITE };
  int bw = TFT_W / 4;
  for (int i = 0; i < 4; i++)
    tft.fillRect(i * bw, 0, (i == 3) ? (TFT_W - 3 * bw) : bw, TFT_H, bars[i]);

  // 2px white border proves the full extent is addressable — if the
  // CGRAM offset were wrong, an edge would be clipped or wrapped.
  tft.fillRect(0, 0, TFT_W, 2, WHITE);
  tft.fillRect(0, TFT_H - 2, TFT_W, 2, WHITE);
  tft.fillRect(0, 0, 2, TFT_H, WHITE);
  tft.fillRect(TFT_W - 2, 0, 2, TFT_H, WHITE);
}
#endif

void setup() {
  // The camera's inrush can drag this board's 3V3 below the 2.43 V
  // brownout threshold, which resets the chip before anything reaches
  // the screen. The sibling OV5640 sketch needs this too.
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  resetHistoryBoot();

  Serial.begin(115200);
  delay(50);                       // just enough for the first print

  // Reset reason distinguishes "hung" from "rebooting in a loop" — the
  // two failure modes that look identical on a blank panel.
  Serial.printf("\n=== SPILCD + SDCARD + OV5640 === reset reason %d\n",
                (int)esp_reset_reason());
#if BLE_ENABLE
  bleDiagBoot();                   // did the last Bluetooth attempt take the board down?
#endif

  // Core 0's idle task starves under camera + USB load, tripping the
  // Task WDT after ~5 s (reset reason 6). loopTask on Core 1 stays
  // monitored, so a genuine hang in our code is still caught.
  esp_task_wdt_delete(xTaskGetIdleTaskHandleForCPU(0));

  // Backlight first, held off: the panel powers up with random RAM, and with
  // BLK on a GPIO we can simply not show it rather than racing to clear it.
  uint32_t tBoot = millis();

  settingsLoad();                  // restore saved screen/compass settings
  blBegin();
  tft.begin();
  applyOrientation();              // honour saved flips
  tft.fillScreen(BLACK);
  blSet(BL_DEFAULT);               // safe to light it now

#if BNO_RST_PIN >= 0
  //  Hold the sensor in reset, then release: PS0/PS1 are sampled on the
  //  rising edge, so this is what makes a strap change take effect.
  pinMode(BNO_RST_PIN, OUTPUT);
  digitalWrite(BNO_RST_PIN, LOW);
  delay(10);
  digitalWrite(BNO_RST_PIN, HIGH);
  delay(100);                      // sensor boots and starts streaming
  Serial.printf("BNO085 reset via GPIO%d\n", BNO_RST_PIN);
#endif

  uint32_t tDisp = millis();       // panel is alive from here

  btnBegin();                      // BOOT button drives the menu

  Serial1.begin(BNO_BAUD, SERIAL_8N1, BNO_RX_PIN, -1);   // RVC is receive-only

  //  Bring the shared I2C bus up here (not in the MLX task) so the buttons
  //  work even if the sensor is absent, and create the mutex that serialises
  //  the two cores' access to it — both before anything can touch the bus.
  i2cMutex = xSemaphoreCreateMutex();
  i2cBusStart();
  i2cRecover(false);               // says so at boot if a line is held low
  Serial.printf("I2C bus at %lu kHz\n", (unsigned long)(i2cHz / 1000));
#if PCF_ENABLE
  pcfBegin();
#endif
#if SERVO_ENABLE
  servoBegin();                    // boot pulses out before the slow boot steps
#endif
#if WEB_ENABLE && SERVO_ENABLE
  webBegin();                      // Wi-Fi + servo web page, own task on core 0
#endif

#if MLX_ENABLE
  //  Spawns the sensor task and returns immediately — the EEPROM dump and
  //  every other slow part now happen on core 0, in parallel with the boot
  //  video rather than in front of it.
  mlxBegin();
#endif

  //  Views are full screen, so this is the whole panel: 110 KB at 320x172.
  //  Allocated before the camera and before any video framebuffer so it
  //  gets first call on internal DRAM — it is redrawn continuously, where
  //  the video buffer is written once per frame and streamed straight out,
  //  so PSRAM hurts this one more. The free-heap figure is printed either
  //  way, because a silent null canvas would just show a black screen with
  //  no explanation.
  Serial.printf("UI canvas %ux%u = %u B, free heap %u\n",
                (unsigned)TFT_W, (unsigned)TFT_H,
                (unsigned)(TFT_W * TFT_H * 2), (unsigned)ESP.getFreeHeap());
  inst = new GFXcanvas16(TFT_W, TFT_H);
  if (!inst || !inst->getBuffer()) {
    logLine(NEON_RED, "UI canvas alloc FAILED (%u B) - views stay black",
            (unsigned)(TFT_W * TFT_H * 2));
    inst = nullptr;
  }

#if BOOT_TEST_PATTERN
  bootTestPattern();
  Serial.println("boot pattern up - if the panel is blank, the fault is "
                 "the display (pins 47/21/48), not the camera");
  delay(BOOT_PATTERN_MS);
#endif

  // Camera before the card: nothing else may sit between power-on and
  // the first frame. Mounting is cheap, but the 64 KB verify is not.

#if BOOT_TEST_PATTERN
  // The camera pane is letterboxed, and the boot bars would otherwise survive
  // in the bands above and below the image. Leave a failure-red screen alone.
  if (camReady) tft.fillScreen(BLACK);
#endif

#if SD_SELFTEST_AT_BOOT
  sdSelfTest();
#else
  sdMount();                       // console commands need it mounted
  Serial.printf("SD %s - type 'test' for the full suite\n",
                sdMounted ? "mounted" : "NOT PRESENT");
#endif
  uint32_t tCard = millis();

  //  Coming back from Doom: no intro video, and the menu opens on DOOM.
  prefs.begin("doom", false);
  bool fromDoom = prefs.getBool("ret", false);
  if (fromDoom) prefs.remove("ret");
  prefs.end();
  if (fromDoom) uiSel = UI_DOOM - 1;

#if VIDEO_ENABLE && VIDEO_AT_BOOT
  //  After the card is mounted and after the camera, so a missing file or
  //  a failed mount reports itself on a serial log that is not yet
  //  scrolling frame-rate lines. If it cannot play, it simply does not —
  //  the panes come up as normal.
  if (sdMounted && !fromDoom) {
    vidLoop = false;                     // intro plays once
    vidPlay(VIDEO_DEFAULT_FILE);
  }
#endif

  //  Where the pre-roll actually goes. The panel's own reset and sleep-out
  //  timing dominates now — those delays are ST7789 datasheet minimums, so
  //  they are the floor unless the panel is left initialised across resets.
  Serial.printf("boot: panel %lums  card %lums  video open %lums  total %lums\n",
                (unsigned long)(tDisp - tBoot),
                (unsigned long)(tCard - tDisp),
                (unsigned long)(millis() - tCard),
                (unsigned long)(millis() - tBoot));

  imuLogging = (IMU_LOGGING != 0) && sdMounted;
  Serial.printf("IMU logging %s -> %s @ %d Hz\n",
                imuLogging ? "ON" : "OFF", IMU_LOG_FILE, IMU_LOG_HZ);

  sdConsoleHelp();

#if BL_DEMO_AT_BOOT
  // Runs concurrently with the live feed, so it adds nothing to the time
  // before the first frame appears.
  blDemoStart();
#endif
}

void loop() {
  sdConsolePoll();
  blDemoPoll();                    // brightness sweep, if running
  imuPoll();                       // drain the RVC stream every pass
  imuAutoProbe();                  // one-shot self-diagnosis if rx stays 0
  imuLogPoll();                    // rate-limited CSV append
  btnPoll();                       // debounced BOOT button -> UiAction
#if PCF_ENABLE
  pcfPoll();                       // 5-button gamepad on the PCF8574
#endif
#if SERVO_ENABLE
  seqService();                    // SD sequence playback, if running
  servoService();                  // push servo changes to the PCA9685s
#endif
  idlePoll();                      // dim the panel when left alone
#if GAS_ENABLE
  scdPoll();                       // SCD40: one short I2C exchange at most
#endif
#if AIR_ENABLE
  senPoll();                       // SEN69C: one short I2C exchange at most
#endif

  //  Hold the just-drawn snapshot toast (and the frame under it) on screen
  //  for its full duration — inputs keep polling, but no redraw runs, so the
  //  filename stays put instead of being overwritten by the next frame.
  if ((int32_t)(toastUntil - millis()) > 0) { delay(5); return; }

#if VIDEO_ENABLE
  //  Playback takes the whole panel, so the camera and instrument panes
  //  stand down — and the camera is not even grabbed, which gives the
  //  decoder the CPU it needs. The console still runs above, so "stop"
  //  works while a clip is playing.
  if (vidPlaying) {
    vidPoll();
    delay(1);
    return;
  }
#endif

  //  Every view except the camera repaints on a timer. The thermal view
  //  redraws at the full rate even though the sensor only produces 4
  //  frames/s: the readouts and the blinking caret still move, and
  //  re-blitting an unchanged canvas costs one push.
  //  Both the plain camera and the fusion view run at camera rate and need
  //  live frames; every other view repaints on the slow UI timer.
  //  The fusion view without a working IR sensor is drawn on the UI timer by
  //  uiViewThermal(), so it shows the same NO THERMAL CAMERA message.
#if MLX_ENABLE
  bool camView = (uiView == UI_CAMERA || (uiView == UI_FUSION && mlxAlive()));
#else
  bool camView = (uiView == UI_CAMERA);
#endif
  if (!camView) {
    //  A web page watching the camera still gets frames with the LCD on
    //  another view: grab one only when one is due, so the UI timer below
    //  is not held up waiting on the sensor every pass.
    if (webCamDue() && camEnsure()) {
      camera_fb_t* wfb = esp_camera_fb_get();
      if (wfb) { webCamPublish(wfb); esp_camera_fb_return(wfb); }
    }
    uint32_t nowMs = millis();
    //  The game runs at its own, faster frame rate; every other view at the
    //  UI rate.
    if (nowMs - uiLastDraw >= (uiView == UI_GAME || uiView == UI_SAND || uiView == UI_BLOCKS || uiView == UI_SERVO || uiView == UI_IMUSERVO ? GAME_FRAME_MS :
                               uiView == UI_TANK ? TANK_FRAME_MS : UI_REDRAW_MS)) {
      uiDraw();
      uiLastDraw = nowMs;
    }
    delay(2);
    return;
  }

  //  First entry to this view is what starts the camera. It blocks for about
  //  a second, so say what is happening rather than showing a frozen panel.
  if (!camInitTried && inst) {
    inst->fillScreen(CYBER_BG);
    uiCentreText("STARTING CAM", 2, NEON_CYAN);
    uiFrame(CYBER_GRID);
    uiScanlines();
    uiBlit();
  }

  //  Camera view with no camera: say so, rather than leaving a black panel
  //  that looks identical to a crash.
  if (!camEnsure()) {
    if (inst && millis() - uiLastDraw >= 500) {
      inst->fillScreen(CYBER_BG);
      uiCentreText("NO CAMERA", 2, NEON_RED);
      uiFrame(CYBER_GRID);
      uiScanlines();
      uiBlit();
      uiLastDraw = millis();
    }
    delay(5);
    return;
  }

  camera_fb_t* fb = esp_camera_fb_get();
  if (!fb) {
    camDrops++;
    delay(2);
    return;
  }

  // Guard the blit: a format or size mismatch would walk off the end of
  // the buffer. Only RGB565 at the size we asked for is safe to push.
  if (fb->format == PIXFORMAT_RGB565 && fb->width == CAM_W && fb->height == CAM_H) {
#if MLX_ENABLE
    if (uiView == UI_FUSION) fuseFrame(fb); else showFrame(fb);
#else
    showFrame(fb);
#endif
    camFrames++;
    if (webCamDue()) webCamPublish(fb);   // same frame to the web page
  } else {
    camDrops++;
  }
  esp_camera_fb_return(fb);

  // Frame rate to serial once a second — keeps the panel clean.
  static uint32_t lastReport = 0, lastFrames = 0;
  uint32_t now = millis();
  if (now - lastReport >= 1000) {
    Serial.printf("%lu fps (%lu drops)\n",
                  (unsigned long)(camFrames - lastFrames), (unsigned long)camDrops);
    lastFrames = camFrames;
    lastReport = now;
  }

  delay(1);                        // feed the idle task / Task WDT
}
