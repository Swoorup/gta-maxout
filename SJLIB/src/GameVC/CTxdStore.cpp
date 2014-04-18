#include "SJLIB/stdinc.h"

DWORD dwFunc_CTxdStore__PushCurrentTxd = 0x580AC0;
DWORD dwFunc_CTxdStore__FindTxdSlot    = 0x580D70;
DWORD dwFunc_CTxdStore__AddTxdSlot     = 0x580F00;
DWORD dwFunc_CTxdStore__LoadTxd        = 0x580CD0;
DWORD dwFunc_CTxdStore__AddRef         = 0x580A60;
DWORD dwFunc_CTxdStore__SetCurrentTxd  = 0x580AD0;
DWORD dwFunc_CTxdStore__PopCurrentTxd  = 0x580AA0;

_declspec(naked) VOID CTxdStore::AddRef(int _TxdIndex) {
	_asm jmp dwFunc_CTxdStore__AddRef
}

_declspec(naked) DWORD CTxdStore::AddTxdSlot(const char *_SlotName) {
	_asm jmp dwFunc_CTxdStore__AddTxdSlot
}

_declspec(naked) DWORD CTxdStore::FindTxdSlot(const char *_SlotName) {
	_asm jmp dwFunc_CTxdStore__FindTxdSlot
}

_declspec(naked) VOID CTxdStore::LoadTxd(int _TxdIndex, const char *_TxdName) {
	_asm jmp dwFunc_CTxdStore__LoadTxd
}

void CTxdStore::PopCurrentTxd() 
{
	RwTexDictionarySetCurrent(*(RwTexDictionary**)0xA0D078);
	*(RwTexDictionary**)0xA0D078 = NULL;
}

void CTxdStore::PushCurrentTxd() 
{
	*(RwTexDictionary**)0xA0D078 = RwTexDictionaryGetCurrent();
}

_declspec(naked) VOID CTxdStore::SetCurrentTxd(int _TxdIndex) {
	_asm jmp dwFunc_CTxdStore__SetCurrentTxd
}