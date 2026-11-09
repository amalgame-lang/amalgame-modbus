/* Amalgame_Modbus.h — runtime header for the amalgame-modbus package.
 * Forward declarations only : the implementation lives in the @c
 * block of facade.am, compiled into libamalgame-pkg-Modbus.a.
 *
 *   import Amalgame.Modbus
 *
 * Return codes of the read / write calls : >= 0 ok, -1 I/O error or
 * timeout, -2 Modbus exception, -3 malformed response, -4 bad
 * argument. Modbus.LastError(h) gives the text. */

#ifndef AMALGAME_MODBUS_H
#define AMALGAME_MODBUS_H

#include "_runtime.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Client */
int64_t     Amalgame_Modbus_Modbus_Connect(code_string host, int64_t port, int64_t timeoutMs);
void        Amalgame_Modbus_Modbus_Close(int64_t h);
code_bool   Amalgame_Modbus_Modbus_IsConnected(int64_t h);
code_string Amalgame_Modbus_Modbus_LastError(int64_t h);
int64_t     Amalgame_Modbus_Modbus_ReadCoils(int64_t h, int64_t unit, int64_t addr, int64_t count);
int64_t     Amalgame_Modbus_Modbus_ReadDiscreteInputs(int64_t h, int64_t unit, int64_t addr, int64_t count);
int64_t     Amalgame_Modbus_Modbus_ReadHolding(int64_t h, int64_t unit, int64_t addr, int64_t count);
int64_t     Amalgame_Modbus_Modbus_ReadInput(int64_t h, int64_t unit, int64_t addr, int64_t count);
int64_t     Amalgame_Modbus_Modbus_WriteCoil(int64_t h, int64_t unit, int64_t addr, code_bool on);
int64_t     Amalgame_Modbus_Modbus_WriteRegister(int64_t h, int64_t unit, int64_t addr, int64_t value);
int64_t     Amalgame_Modbus_Modbus_WriteRegisters(int64_t h, int64_t unit, int64_t addr, code_string values);
int64_t     Amalgame_Modbus_Modbus_WriteFloat32(int64_t h, int64_t unit, int64_t addr, double value, code_bool wordSwap);
int64_t     Amalgame_Modbus_Modbus_WriteInt32(int64_t h, int64_t unit, int64_t addr, int64_t value, code_bool wordSwap);

/* Values of the last read on a handle */
int64_t     Amalgame_Modbus_Modbus_Value(int64_t h, int64_t i);
int64_t     Amalgame_Modbus_Modbus_Int16(int64_t h, int64_t i);
int64_t     Amalgame_Modbus_Modbus_UInt32(int64_t h, int64_t i, code_bool wordSwap);
int64_t     Amalgame_Modbus_Modbus_Int32(int64_t h, int64_t i, code_bool wordSwap);
double      Amalgame_Modbus_Modbus_Float32(int64_t h, int64_t i, code_bool wordSwap);

/* Server (PLC simulator, one per process) */
code_bool   Amalgame_Modbus_Modbus_ServerStart(code_string host, int64_t port);
void        Amalgame_Modbus_Modbus_ServerSetSize(int64_t size);
void        Amalgame_Modbus_Modbus_ServerSetCoil(int64_t addr, code_bool on);
void        Amalgame_Modbus_Modbus_ServerSetDiscrete(int64_t addr, code_bool on);
void        Amalgame_Modbus_Modbus_ServerSetHolding(int64_t addr, int64_t value);
void        Amalgame_Modbus_Modbus_ServerSetInput(int64_t addr, int64_t value);
void        Amalgame_Modbus_Modbus_ServerSetFloat32(int64_t table, int64_t addr, double value, code_bool wordSwap);
void        Amalgame_Modbus_Modbus_ServerSetInt32(int64_t table, int64_t addr, int64_t value, code_bool wordSwap);
code_bool   Amalgame_Modbus_Modbus_ServerGetCoil(int64_t addr);
int64_t     Amalgame_Modbus_Modbus_ServerGetHolding(int64_t addr);
int64_t     Amalgame_Modbus_Modbus_ServerRequestCount(void);

#ifdef __cplusplus
}
#endif

#endif /* AMALGAME_MODBUS_H */
