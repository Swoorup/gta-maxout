//###########################################################
//#	CTxdStore.h:											#
//#															#
//###########################################################

#ifndef _CTXDSTORE_HPP_
#define _CTXDSTORE_HPP_

#include <windows.h>

class CTxdStore
{
public:
	static VOID	AddRef(int _TxdIndex);
	static DWORD AddTxdSlot(const char *_SlotName);
	static DWORD FindTxdSlot(const char *_SlotName);
	static VOID LoadTxd(int _TxdIndex, const char *_TxdName);
	static VOID PopCurrentTxd(void);
	static VOID PushCurrentTxd(void);
	static VOID SetCurrentTxd(int _TxdIndex);
};

#endif