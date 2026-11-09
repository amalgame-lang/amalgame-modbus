# amalgame-modbus

> Modbus TCP for [Amalgame](https://github.com/amalgame-lang/Amalgame): a client to read and write PLCs, and a server that plays a PLC for tests and demos.

Linux, macOS / BSD and Windows (MinGW-w64); tested on Linux and Windows 11, not yet on macOS. Plain C over BSD sockets / Winsock, no libmodbus.

## Status

**v0.1.0**: Modbus TCP client and PLC simulator.

| | |
|---|---|
| Function codes (client) | 01 read coils, 02 read discrete inputs, 03 read holding registers, 04 read input registers, 05 write coil, 06 write register, 16 write registers |
| Function codes (simulator) | the same, plus 15 write coils |
| Decoding | uint16, int16, uint32, int32, float32, high word first (ABCD) or low word first (CDAB) |
| Errors | connect timeout, response timeout, Modbus exceptions with their text, late responses skipped by transaction id |
| Connections | a handle reconnects by itself on the next call after an I/O error |

Not in v0.1: Modbus RTU (serial), RTU over TCP, FC 15 / 22 / 23 on the client side, host names (IPv4 addresses only).

## Client

```amalgame
import Amalgame.Modbus

let h: int = Modbus.Connect("192.168.1.10", 502, 1000)    // host, port, timeout in ms
let n: int = Modbus.ReadHolding(h, 1, 0, 10)              // unit id, first address, count
if (n < 0) {
    Console.WriteLine("read failed: " + Modbus.LastError(h))
} else {
    let speed: int   = Modbus.Value(h, 0)                 // register 0 as uint16
    let temp:  float = Modbus.Float32(h, 2, false)        // registers 2-3, high word first
}
Modbus.WriteRegister(h, 1, 100, 42)
Modbus.WriteFloat32(h, 1, 200, 21.5, false)
Modbus.Close(h)
```

Addresses are 0-based protocol addresses: holding register "40001" in a PLC manual is address 0.

Values of the last read stay in the handle and are read with `Value`, `Int16`, `UInt32`, `Int32` and `Float32`, the index being relative to the first address read. A handle is therefore not meant to be shared between threads: open one per thread.

| Return code | Meaning |
|---|---|
| `>= 0` | ok: count read, or 1 for a write |
| `-1` | I/O error or timeout; the connection is dropped and reopened on the next call |
| `-2` | Modbus exception from the device (`LastError`: "exception 2 (illegal data address)") |
| `-3` | malformed response |
| `-4` | bad argument (count, address, closed handle), nothing sent |

`Connect` returns -1 only for an address that is not IPv4 or when 64 handles are open. A device that does not answer yet still gets a handle: `IsConnected` tells, and every call tries to reconnect.

## Simulator

One per process. Four tables of 65536 entries: 1 coils, 2 discrete inputs, 3 holding registers, 4 input registers. It answers any unit id.

```amalgame
Modbus.ServerStart("127.0.0.1", 1502)          // "0.0.0.0" to listen on every interface
Modbus.ServerSetHolding(0, 1234)
Modbus.ServerSetFloat32(4, 10, 21.5, false)    // input registers 10-11
Modbus.ServerSetCoil(3, true)
let setpoint: int = Modbus.ServerGetHolding(100)   // what a client wrote
```

`127.0.0.1` keeps the simulator local: on Windows, listening on every interface opens a firewall prompt that needs an administrator.

`ServerSetSize(n)` makes addresses `>= n` answer "illegal data address", to test error handling.

## Tests

`tests/run_am_tests.sh [amc]` builds and runs every `tests/*.am` suite against the working tree, staged as a dev package, without a git tag. CI runs it with amc 0.8.52 and 0.8.90. On Windows, run it from Git Bash with `TMPDIR` on the same drive as the repository, e.g. `TMPDIR=/d/tmp/modbus-am`.

`modbus_smoke` (35 checks) covers every function code, the decodings, exceptions, argument checks, a refused connection and 1000 back-to-back reads.

## License

Apache-2.0. See [LICENSE](LICENSE).
