//###########################################################
//#	CTxdStore.h:											#
//#															#
//###########################################################

#include "CTxdStore.h"


DWORD dwFunc_CTxdStore__PushCurrentTxd = 0x580AC0;
DWORD dwFunc_CTxdStore__FindTxdSlot    = 0x580D70;
DWORD dwFunc_CTxdStore__AddTxdSlot     = 0x580F00;
DWORD dwFunc_CTxdStore__LoadTxd        = 0x580CD0;
DWORD dwFunc_CTxdStore__AddRef         = 0x580A60;
DWORD dwFunc_CTxdStore__SetCurrentTxd  = 0x580AD0;
DWORD dwFunc_CTxdStore__PopCurrentTxd  = 0x580AA0;

__declspec(naked) VOID CTxdStore::AddRef(int _TxdIndex)
{
	__asm jmp dwFunc_CTxdStore__AddRef
}

__declspec(naked) DWORD CTxdStore::AddTxdSlot(const char *_SlotName)
{
	__asm jmp dwFunc_CTxdStore__AddTxdSlot
}

__declspec(naked) DWORD CTxdStore::FindTxdSlot(const char *_SlotName)
{
	__asm jmp dwFunc_CTxdStore__FindTxdSlot
}

__declspec(naked) VOID CTxdStore::LoadTxd(int _TxdIndex, const char *_TxdName)
{
	__asm jmp dwFunc_CTxdStore__LoadTxd
}

__declspec(naked) VOID CTxdStore::PopCurrentTxd()
{
	__asm jmp dwFunc_CTxdStore__PopCurrentTxd
}

__declspec(naked) VOID CTxdStore::PushCurrentTxd()
{
	__asm jmp dwFunc_CTxdStore__PushCurrentTxd
}

__declspec(naked) VOID CTxdStore::SetCurrentTxd(int _TxdIndex)
{
	__asm jmp dwFunc_CTxdStore__SetCurrentTxd
}