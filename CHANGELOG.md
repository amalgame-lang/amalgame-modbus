# Changelog

## v0.1.0 — 2026-11-09

First version, written for Kairo Edge (SCADA).

- Modbus TCP client: function codes 01 02 03 04 05 06 16.
  - Connect timeout (non-blocking connect), response timeout.
  - Modbus exceptions reported with their text.
  - Late responses to a timed-out request are skipped by
    transaction id.
  - Reconnect on the next call after an I/O error.
- Decoding of the last read: uint16, int16, uint32, int32, float32,
  high or low word first. Writing int32 / float32 over FC16.
- Modbus TCP server as a PLC simulator: one per process, four
  65536-entry tables, function codes 01 to 06, 15 and 16, configurable
  size to produce "illegal data address".
- Portability: Linux, macOS / BSD, Windows (MinGW-w64). Winsock is
  resolved at runtime from ws2_32.dll, as in amalgame-pollen, so the
  manifest's `libs` stays the same on every OS.
- `tests/modbus_smoke.am` (35 checks) and `tests/run_am_tests.sh`,
  run by CI with amc 0.8.52 and 0.8.90. Verified on Windows 11 and on
  Linux with a gcc 15-like strictness (int-conversion errors).
