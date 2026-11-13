# ZedBoard Temperature Logger

Bare-metal C++ firmware for the **Xilinx Zynq-7000** (ZedBoard). The ARM Cortex-A9 collects temperature samples in a fixed-size buffer, writes them to an **SD card** (FatFs) when the buffer is full, and sends them to a PC over **UART** when the PC asks for them.

Built with Vivado 2023.2 (hardware design) and Vitis Classic 2023.2 (software).

## How it works

```
 ┌──────────────┐  every cycle   ┌─────────────────┐  buffer full  ┌─────────────┐
 │ sample source├───────────────►│ TemperatureData ├──────────────►│ SD card     │
 └──────────────┘                │  (10 samples)   │               │ (FatFs)     │
                                 └───────┬─────────┘               └─────────────┘
                                         │ PC sends byte 123
                                         ▼
                                 ┌─────────────────┐
                                 │ UART (PS UART0, │──► PC
                                 │   1200 baud)    │
                                 └─────────────────┘
```

1. Each cycle a new sample is added to `TemperatureData`, a fixed buffer of `QUEUE_SIZE` (10) samples.
2. When the buffer is full, `SDCard` writes it to the card and clears the buffer.
3. Between samples, the firmware polls UART0. If the PC sends the request byte **`123`**, every buffered sample is sent as a packet and the buffer is cleared.

## UART packet format

Each sample is sent as one 9-byte packet:

| Bytes | Field |
|---|---|
| 0–3 | sync marker `FF FF FF FF` |
| 4 | temperature (`int8`) |
| 5–8 | timestamp (`uint32`, big-endian) |

The SD card file stores 7-byte records: `timestamp (4 bytes, big-endian) ' ' temperature '\n'`.

## Code

| File | Purpose |
|---|---|
| `no-rtos-proj/src/main.cc` | main loop: sample, store, serve UART requests |
| `no-rtos-proj/src/TemperatureData.*` | sample buffer |
| `no-rtos-proj/src/UartImp.*` | XUartPs wrapper: init, blocking receive, packet send |
| `no-rtos-proj/src/SDCard.*` | FatFs (xilffs) wrapper: mount, write, close |
| `design_1_wrapper/hw/` | exported hardware (`.xsa`, bitstream, `ps7_init`) |

## Status

The UART request/response protocol and SD card storage are implemented. The sample source is still a counter that stands in for a sensor, and timestamps are always `0`; reading a real sensor and adding a timer-based timestamp are the next steps. An earlier FreeRTOS version (task, queue, tick-based uptime) is still visible in commented-out code. I moved it to bare metal because of toolchain issues (below).

## Toolchain notes

Getting a stable Xilinx toolchain took a while, so here's what I found:

- **SDK 2015 and 2019:** `xilffs` SD card error (code 3) on both Debian and Windows 11, even with the official example code.
- **Vitis 2023.2 with FreeRTOS:** stdin/stdout could not be routed to `ps7_coresight_comp_0`.
- **Vitis 2023.2 bare-metal on Windows 11:** the `uartps` library did not work.
- **Vitis 2024.2:** hangs on the start page. There is no "Classic" edition of 2024.2.

**Recommended:** Vivado 2023.2 with Vitis Classic 2023.2. It is Eclipse-based and light on hardware, it was the most stable version for me, it supports stdin/stdout under FreeRTOS, and the ZedBoard doesn't need a licence for it.
