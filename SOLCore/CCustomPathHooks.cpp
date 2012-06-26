#include "CCustomPathHooks.h"

extern float f8xDivider;
extern float fPathShiftX;
extern float fPathShiftY;
extern float fPathShiftZ;

DWORD dwHookReturn41C6E1 = 0x41C6E7;
void _declspec (naked)Hook41C6E1(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn41C6E1
}

DWORD dwHookReturn41C6FF = 0x41C705;
void _declspec (naked)Hook41C6FF(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn41C6FF
}

DWORD dwHookReturn41CD42 = 0x41CD48;
void _declspec (naked)Hook41CD42(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn41CD42
}

DWORD dwHookReturn41CD60 = 0x41CD66;
void _declspec (naked)Hook41CD60(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn41CD60
}

DWORD dwHookReturn41CD76 = 0x41CD7C;
void _declspec (naked)Hook41CD76(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn41CD76
}

DWORD dwHookReturn41CDA7 = 0x41CDAD;
void _declspec (naked)Hook41CDA7(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn41CDA7
}

DWORD dwHookReturn41CDC8 = 0x41CDCE;
void _declspec (naked)Hook41CDC8(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn41CDC8
}

DWORD dwHookReturn41CDD6 = 0x41CDDC;
void _declspec (naked)Hook41CDD6(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn41CDD6
}

DWORD dwHookReturn41D0F5 = 0x41D0FB;
void _declspec (naked)Hook41D0F5(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn41D0F5
}

DWORD dwHookReturn41D105 = 0x41D10B;
void _declspec (naked)Hook41D105(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn41D105
}

DWORD dwHookReturn41D133 = 0x41D139;
void _declspec (naked)Hook41D133(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn41D133
}

DWORD dwHookReturn41D143 = 0x41D149;
void _declspec (naked)Hook41D143(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn41D143
}

DWORD dwHookReturn41D1F5 = 0x41D1FB;
void _declspec (naked)Hook41D1F5(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn41D1F5
}

DWORD dwHookReturn41D21D = 0x41D223;
void _declspec (naked)Hook41D21D(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn41D21D
}

DWORD dwHookReturn41D233 = 0x41D239;
void _declspec (naked)Hook41D233(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn41D233
}

DWORD dwHookReturn41D23F = 0x41D245;
void _declspec (naked)Hook41D23F(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn41D23F
}

DWORD dwHookReturn41F0EE = 0x41F0F4;
void _declspec (naked)Hook41F0EE(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn41F0EE
}

DWORD dwHookReturn41F11E = 0x41F124;
void _declspec (naked)Hook41F11E(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn41F11E
}

DWORD dwHookReturn41F156 = 0x41F15C;
void _declspec (naked)Hook41F156(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn41F156
}

DWORD dwHookReturn41F16E = 0x41F174;
void _declspec (naked)Hook41F16E(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn41F16E
}

DWORD dwHookReturn41F3AC = 0x41F3B2;
void _declspec (naked)Hook41F3AC(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn41F3AC
}

DWORD dwHookReturn41F3E7 = 0x41F3ED;
void _declspec (naked)Hook41F3E7(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn41F3E7
}

DWORD dwHookReturn41F558 = 0x41F55E;
void _declspec (naked)Hook41F558(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn41F558
}

DWORD dwHookReturn41F582 = 0x41F588;
void _declspec (naked)Hook41F582(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn41F582
}

DWORD dwHookReturn41F89C = 0x41F8A2;
void _declspec (naked)Hook41F89C(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn41F89C
}

DWORD dwHookReturn41F8D7 = 0x41F8DD;
void _declspec (naked)Hook41F8D7(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn41F8D7
}

DWORD dwHookReturn42100B = 0x421011;
void _declspec (naked)Hook42100B(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn42100B
}

DWORD dwHookReturn421033 = 0x421039;
void _declspec (naked)Hook421033(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn421033
}

DWORD dwHookReturn421049 = 0x42104F;
void _declspec (naked)Hook421049(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn421049
}

DWORD dwHookReturn42105B = 0x421061;
void _declspec (naked)Hook42105B(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn42105B
}

DWORD dwHookReturn4211C7 = 0x4211CD;
void _declspec (naked)Hook4211C7(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4211C7
}

DWORD dwHookReturn4211D9 = 0x4211DF;
void _declspec (naked)Hook4211D9(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4211D9
}

DWORD dwHookReturn421223 = 0x421229;
void _declspec (naked)Hook421223(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn421223
}

DWORD dwHookReturn421235 = 0x42123B;
void _declspec (naked)Hook421235(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn421235
}

DWORD dwHookReturn42144F = 0x421455;
void _declspec (naked)Hook42144F(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn42144F
}

DWORD dwHookReturn42147E = 0x421484;
void _declspec (naked)Hook42147E(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn42147E
}

DWORD dwHookReturn42149B = 0x4214A1;
void _declspec (naked)Hook42149B(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn42149B
}

DWORD dwHookReturn421668 = 0x42166E;
void _declspec (naked)Hook421668(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn421668
}

DWORD dwHookReturn421689 = 0x42168F;
void _declspec (naked)Hook421689(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn421689
}

DWORD dwHookReturn4216A9 = 0x4216AF;
void _declspec (naked)Hook4216A9(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4216A9
}

DWORD dwHookReturn4216B5 = 0x4216BB;
void _declspec (naked)Hook4216B5(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4216B5
}

DWORD dwHookReturn421996 = 0x42199C;
void _declspec (naked)Hook421996(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn421996
}

DWORD dwHookReturn4219BE = 0x4219C4;
void _declspec (naked)Hook4219BE(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4219BE
}

DWORD dwHookReturn4219D4 = 0x4219DA;
void _declspec (naked)Hook4219D4(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4219D4
}

DWORD dwHookReturn4219E6 = 0x4219EC;
void _declspec (naked)Hook4219E6(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4219E6
}

DWORD dwHookReturn421B82 = 0x421B88;
void _declspec (naked)Hook421B82(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn421B82
}

DWORD dwHookReturn421B94 = 0x421B9A;
void _declspec (naked)Hook421B94(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn421B94
}

DWORD dwHookReturn421BE5 = 0x421BEB;
void _declspec (naked)Hook421BE5(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn421BE5
}

DWORD dwHookReturn421BF7 = 0x421BFD;
void _declspec (naked)Hook421BF7(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn421BF7
}

DWORD dwHookReturn421DF9 = 0x421DFF;
void _declspec (naked)Hook421DF9(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn421DF9
}

DWORD dwHookReturn421E29 = 0x421E2F;
void _declspec (naked)Hook421E29(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn421E29
}

DWORD dwHookReturn421E43 = 0x421E49;
void _declspec (naked)Hook421E43(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn421E43
}

DWORD dwHookReturn421E65 = 0x421E6B;
void _declspec (naked)Hook421E65(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn421E65
}

DWORD dwHookReturn421E81 = 0x421E87;
void _declspec (naked)Hook421E81(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn421E81
}

DWORD dwHookReturn421E8D = 0x421E93;
void _declspec (naked)Hook421E8D(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn421E8D
}

DWORD dwHookReturn422632 = 0x422638;
void _declspec (naked)Hook422632(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn422632
}

DWORD dwHookReturn422660 = 0x422666;
void _declspec (naked)Hook422660(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn422660
}

DWORD dwHookReturn422676 = 0x42267C;
void _declspec (naked)Hook422676(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn422676
}

DWORD dwHookReturn42268C = 0x422692;
void _declspec (naked)Hook42268C(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn42268C
}

DWORD dwHookReturn4226A6 = 0x4226AC;
void _declspec (naked)Hook4226A6(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4226A6
}

DWORD dwHookReturn4226BA = 0x4226C0;
void _declspec (naked)Hook4226BA(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4226BA
}

DWORD dwHookReturn422820 = 0x422826;
void _declspec (naked)Hook422820(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn422820
}

DWORD dwHookReturn422832 = 0x422838;
void _declspec (naked)Hook422832(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn422832
}

DWORD dwHookReturn42287C = 0x422882;
void _declspec (naked)Hook42287C(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn42287C
}

DWORD dwHookReturn42288E = 0x422894;
void _declspec (naked)Hook42288E(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn42288E
}

DWORD dwHookReturn425F1B = 0x425F21;
void _declspec (naked)Hook425F1B(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn425F1B
}

DWORD dwHookReturn425F2B = 0x425F31;
void _declspec (naked)Hook425F2B(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn425F2B
}

DWORD dwHookReturn425F77 = 0x425F7D;
void _declspec (naked)Hook425F77(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn425F77
}

DWORD dwHookReturn425F91 = 0x425F97;
void _declspec (naked)Hook425F91(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn425F91
}

DWORD dwHookReturn427B46 = 0x427B4C;
void _declspec (naked)Hook427B46(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn427B46
}

DWORD dwHookReturn427B74 = 0x427B7A;
void _declspec (naked)Hook427B74(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn427B74
}

DWORD dwHookReturn427B90 = 0x427B96;
void _declspec (naked)Hook427B90(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn427B90
}

DWORD dwHookReturn427BAC = 0x427BB2;
void _declspec (naked)Hook427BAC(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn427BAC
}

DWORD dwHookReturn427BC8 = 0x427BCE;
void _declspec (naked)Hook427BC8(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn427BC8
}

DWORD dwHookReturn427BE8 = 0x427BEE;
void _declspec (naked)Hook427BE8(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn427BE8
}

DWORD dwHookReturn427DDB = 0x427DE1;
void _declspec (naked)Hook427DDB(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn427DDB
}

DWORD dwHookReturn427E06 = 0x427E0C;
void _declspec (naked)Hook427E06(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn427E06
}

DWORD dwHookReturn427E26 = 0x427E2C;
void _declspec (naked)Hook427E26(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn427E26
}

DWORD dwHookReturn427E35 = 0x427E3B;
void _declspec (naked)Hook427E35(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn427E35
}

DWORD dwHookReturn427E55 = 0x427E5B;
void _declspec (naked)Hook427E55(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn427E55
}

DWORD dwHookReturn427E6B = 0x427E71;
void _declspec (naked)Hook427E6B(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn427E6B
}

DWORD dwHookReturn428130 = 0x428136;
void _declspec (naked)Hook428130(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn428130
}

DWORD dwHookReturn42814B = 0x428151;
void _declspec (naked)Hook42814B(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn42814B
}

DWORD dwHookReturn4281BE = 0x4281C4;
void _declspec (naked)Hook4281BE(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4281BE
}

DWORD dwHookReturn4281D9 = 0x4281DF;
void _declspec (naked)Hook4281D9(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4281D9
}

DWORD dwHookReturn428491 = 0x428497;
void _declspec (naked)Hook428491(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn428491
}

DWORD dwHookReturn4284AC = 0x4284B2;
void _declspec (naked)Hook4284AC(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4284AC
}

DWORD dwHookReturn428508 = 0x42850E;
void _declspec (naked)Hook428508(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn428508
}

DWORD dwHookReturn42852C = 0x428532;
void _declspec (naked)Hook42852C(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn42852C
}

DWORD dwHookReturn4285C6 = 0x4285CC;
void _declspec (naked)Hook4285C6(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4285C6
}

DWORD dwHookReturn4285DE = 0x4285E4;
void _declspec (naked)Hook4285DE(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4285DE
}

DWORD dwHookReturn428605 = 0x42860B;
void _declspec (naked)Hook428605(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn428605
}

DWORD dwHookReturn42861D = 0x428623;
void _declspec (naked)Hook42861D(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn42861D
}

DWORD dwHookReturn428635 = 0x42863B;
void _declspec (naked)Hook428635(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn428635
}

DWORD dwHookReturn428642 = 0x428648;
void _declspec (naked)Hook428642(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn428642
}

DWORD dwHookReturn4286F7 = 0x4286FD;
void _declspec (naked)Hook4286F7(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4286F7
}

DWORD dwHookReturn428711 = 0x428717;
void _declspec (naked)Hook428711(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn428711
}

DWORD dwHookReturn444330 = 0x444336;
void _declspec (naked)Hook444330(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn444330
}

DWORD dwHookReturn444393 = 0x444399;
void _declspec (naked)Hook444393(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn444393
}

DWORD dwHookReturn444525 = 0x44452B;
void _declspec (naked)Hook444525(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn444525
}

DWORD dwHookReturn44453A = 0x444540;
void _declspec (naked)Hook44453A(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn44453A
}

DWORD dwHookReturn444558 = 0x44455E;
void _declspec (naked)Hook444558(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn444558
}

DWORD dwHookReturn444562 = 0x444568;
void _declspec (naked)Hook444562(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn444562
}

DWORD dwHookReturn4445EE = 0x4445F4;
void _declspec (naked)Hook4445EE(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4445EE
}

DWORD dwHookReturn444604 = 0x44460A;
void _declspec (naked)Hook444604(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn444604
}

DWORD dwHookReturn444616 = 0x44461C;
void _declspec (naked)Hook444616(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn444616
}

DWORD dwHookReturn444725 = 0x44472B;
void _declspec (naked)Hook444725(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn444725
}

DWORD dwHookReturn444746 = 0x44474C;
void _declspec (naked)Hook444746(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn444746
}

DWORD dwHookReturn444758 = 0x44475E;
void _declspec (naked)Hook444758(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn444758
}

DWORD dwHookReturn444867 = 0x44486D;
void _declspec (naked)Hook444867(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn444867
}

DWORD dwHookReturn44487D = 0x444883;
void _declspec (naked)Hook44487D(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn44487D
}

DWORD dwHookReturn44488F = 0x444895;
void _declspec (naked)Hook44488F(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn44488F
}

DWORD dwHookReturn455172 = 0x455178;
void _declspec (naked)Hook455172(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn455172
}

DWORD dwHookReturn45518E = 0x455194;
void _declspec (naked)Hook45518E(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn45518E
}

DWORD dwHookReturn45519F = 0x4551A5;
void _declspec (naked)Hook45519F(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn45519F
}

DWORD dwHookReturn465D51 = 0x465D57;
void _declspec (naked)Hook465D51(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn465D51
}

DWORD dwHookReturn465D7C = 0x465D82;
void _declspec (naked)Hook465D7C(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn465D7C
}

DWORD dwHookReturn465F21 = 0x465F27;
void _declspec (naked)Hook465F21(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn465F21
}

DWORD dwHookReturn465F4C = 0x465F52;
void _declspec (naked)Hook465F4C(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn465F4C
}

DWORD dwHookReturn466111 = 0x466117;
void _declspec (naked)Hook466111(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn466111
}

DWORD dwHookReturn46613C = 0x466142;
void _declspec (naked)Hook46613C(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn46613C
}

DWORD dwHookReturn466374 = 0x46637A;
void _declspec (naked)Hook466374(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn466374
}

DWORD dwHookReturn4663A0 = 0x4663A6;
void _declspec (naked)Hook4663A0(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4663A0
}

DWORD dwHookReturn4663BD = 0x4663C3;
void _declspec (naked)Hook4663BD(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4663BD
}

DWORD dwHookReturn466484 = 0x46648A;
void _declspec (naked)Hook466484(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn466484
}

DWORD dwHookReturn4664B5 = 0x4664BB;
void _declspec (naked)Hook4664B5(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4664B5
}

DWORD dwHookReturn4664D8 = 0x4664DE;
void _declspec (naked)Hook4664D8(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4664D8
}

DWORD dwHookReturn4664FF = 0x466505;
void _declspec (naked)Hook4664FF(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4664FF
}

DWORD dwHookReturn466515 = 0x46651B;
void _declspec (naked)Hook466515(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn466515
}

DWORD dwHookReturn466524 = 0x46652A;
void _declspec (naked)Hook466524(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn466524
}

DWORD dwHookReturn466792 = 0x466798;
void _declspec (naked)Hook466792(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn466792
}

DWORD dwHookReturn4667AC = 0x4667B2;
void _declspec (naked)Hook4667AC(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4667AC
}

DWORD dwHookReturn466894 = 0x46689A;
void _declspec (naked)Hook466894(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn466894
}

DWORD dwHookReturn4668D9 = 0x4668DF;
void _declspec (naked)Hook4668D9(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4668D9
}

DWORD dwHookReturn466914 = 0x46691A;
void _declspec (naked)Hook466914(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn466914
}

DWORD dwHookReturn46694D = 0x466953;
void _declspec (naked)Hook46694D(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn46694D
}

DWORD dwHookReturn46697F = 0x466985;
void _declspec (naked)Hook46697F(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn46697F
}

DWORD dwHookReturn4669A2 = 0x4669A8;
void _declspec (naked)Hook4669A2(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4669A2
}

DWORD dwHookReturn4AE9FB = 0x4AEA01;
void _declspec (naked)Hook4AE9FB(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4AE9FB
}

DWORD dwHookReturn4AEA13 = 0x4AEA19;
void _declspec (naked)Hook4AEA13(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4AEA13
}

DWORD dwHookReturn4AEA1E = 0x4AEA24;
void _declspec (naked)Hook4AEA1E(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4AEA1E
}

DWORD dwHookReturn4D4995 = 0x4D499B;
void _declspec (naked)Hook4D4995(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4D4995
}

DWORD dwHookReturn4D49A9 = 0x4D49AF;
void _declspec (naked)Hook4D49A9(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4D49A9
}

DWORD dwHookReturn4D49B5 = 0x4D49BB;
void _declspec (naked)Hook4D49B5(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4D49B5
}

DWORD dwHookReturn4D4B21 = 0x4D4B27;
void _declspec (naked)Hook4D4B21(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4D4B21
}

DWORD dwHookReturn4D4B35 = 0x4D4B3B;
void _declspec (naked)Hook4D4B35(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4D4B35
}

DWORD dwHookReturn4D4B41 = 0x4D4B47;
void _declspec (naked)Hook4D4B41(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4D4B41
}

DWORD dwHookReturn4F780A = 0x4F7810;
void _declspec (naked)Hook4F780A(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4F780A
}

DWORD dwHookReturn4F7832 = 0x4F7838;
void _declspec (naked)Hook4F7832(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4F7832
}

DWORD dwHookReturn4F9D5B = 0x4F9D61;
void _declspec (naked)Hook4F9D5B(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4F9D5B
}

DWORD dwHookReturn4F9D70 = 0x4F9D76;
void _declspec (naked)Hook4F9D70(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4F9D70
}

DWORD dwHookReturn4F9D7B = 0x4F9D81;
void _declspec (naked)Hook4F9D7B(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4F9D7B
}

DWORD dwHookReturn4FA20F = 0x4FA215;
void _declspec (naked)Hook4FA20F(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4FA20F
}

DWORD dwHookReturn4FA224 = 0x4FA22A;
void _declspec (naked)Hook4FA224(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4FA224
}

DWORD dwHookReturn4FA22F = 0x4FA235;
void _declspec (naked)Hook4FA22F(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4FA22F
}

DWORD dwHookReturn4FA956 = 0x4FA95C;
void _declspec (naked)Hook4FA956(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4FA956
}

DWORD dwHookReturn4FA970 = 0x4FA976;
void _declspec (naked)Hook4FA970(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4FA970
}

DWORD dwHookReturn4FA986 = 0x4FA98C;
void _declspec (naked)Hook4FA986(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4FA986
}

DWORD dwHookReturn4FABB2 = 0x4FABB8;
void _declspec (naked)Hook4FABB2(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4FABB2
}

DWORD dwHookReturn4FABCC = 0x4FABD2;
void _declspec (naked)Hook4FABCC(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4FABCC
}

DWORD dwHookReturn4FABE6 = 0x4FABEC;
void _declspec (naked)Hook4FABE6(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4FABE6
}

DWORD dwHookReturn5071A6 = 0x5071AC;
void _declspec (naked)Hook5071A6(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn5071A6
}

DWORD dwHookReturn5071C5 = 0x5071CB;
void _declspec (naked)Hook5071C5(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn5071C5
}

DWORD dwHookReturn5071E4 = 0x5071EA;
void _declspec (naked)Hook5071E4(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn5071E4
}

DWORD dwHookReturn50735A = 0x507360;
void _declspec (naked)Hook50735A(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn50735A
}

DWORD dwHookReturn507376 = 0x50737C;
void _declspec (naked)Hook507376(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn507376
}

DWORD dwHookReturn507392 = 0x507398;
void _declspec (naked)Hook507392(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn507392
}

DWORD dwHookReturn5073F2 = 0x5073F8;
void _declspec (naked)Hook5073F2(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn5073F2
}

DWORD dwHookReturn507411 = 0x507417;
void _declspec (naked)Hook507411(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn507411
}

DWORD dwHookReturn507430 = 0x507436;
void _declspec (naked)Hook507430(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn507430
}

DWORD dwHookReturn507476 = 0x50747C;
void _declspec (naked)Hook507476(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn507476
}

DWORD dwHookReturn507495 = 0x50749B;
void _declspec (naked)Hook507495(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn507495
}

DWORD dwHookReturn5074B4 = 0x5074BA;
void _declspec (naked)Hook5074B4(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn5074B4
}

DWORD dwHookReturn5074FA = 0x507500;
void _declspec (naked)Hook5074FA(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn5074FA
}

DWORD dwHookReturn507519 = 0x50751F;
void _declspec (naked)Hook507519(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn507519
}

DWORD dwHookReturn507538 = 0x50753E;
void _declspec (naked)Hook507538(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn507538
}

DWORD dwHookReturn5122E6 = 0x5122EC;
void _declspec (naked)Hook5122E6(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn5122E6
}

DWORD dwHookReturn5122F6 = 0x5122FC;
void _declspec (naked)Hook5122F6(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn5122F6
}

DWORD dwHookReturn512309 = 0x51230F;
void _declspec (naked)Hook512309(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn512309
}

DWORD dwHookReturn513F13 = 0x513F19;
void _declspec (naked)Hook513F13(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn513F13
}

DWORD dwHookReturn513F2B = 0x513F31;
void _declspec (naked)Hook513F2B(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn513F2B
}

DWORD dwHookReturn513F7C = 0x513F82;
void _declspec (naked)Hook513F7C(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn513F7C
}

DWORD dwHookReturn513F9A = 0x513FA0;
void _declspec (naked)Hook513F9A(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn513F9A
}

DWORD dwHookReturn514088 = 0x51408E;
void _declspec (naked)Hook514088(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn514088
}

DWORD dwHookReturn5140A6 = 0x5140AC;
void _declspec (naked)Hook5140A6(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn5140A6
}

DWORD dwHookReturn514196 = 0x51419C;
void _declspec (naked)Hook514196(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn514196
}

DWORD dwHookReturn5141AA = 0x5141B0;
void _declspec (naked)Hook5141AA(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn5141AA
}

DWORD dwHookReturn51F748 = 0x51F74E;
void _declspec (naked)Hook51F748(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn51F748
}

DWORD dwHookReturn51F767 = 0x51F76D;
void _declspec (naked)Hook51F767(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn51F767
}

DWORD dwHookReturn51F786 = 0x51F78C;
void _declspec (naked)Hook51F786(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn51F786
}

DWORD dwHookReturn520EA9 = 0x520EAF;
void _declspec (naked)Hook520EA9(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn520EA9
}

DWORD dwHookReturn520EC0 = 0x520EC6;
void _declspec (naked)Hook520EC0(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn520EC0
}

DWORD dwHookReturn520ECB = 0x520ED1;
void _declspec (naked)Hook520ECB(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn520ECB
}

DWORD dwHookReturn4351D8 = 0x4351DE;
void _declspec (naked)Hook4351D8(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4351D8
}

DWORD dwHookReturn4351F0 = 0x4351F6;
void _declspec (naked)Hook4351F0(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4351F0
}

DWORD dwHookReturn435208 = 0x43520E;
void _declspec (naked)Hook435208(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn435208
}

DWORD dwHookReturn4352B8 = 0x4352BE;
void _declspec (naked)Hook4352B8(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4352B8
}

DWORD dwHookReturn4352D0 = 0x4352D6;
void _declspec (naked)Hook4352D0(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4352D0
}

DWORD dwHookReturn4352DB = 0x4352E1;
void _declspec (naked)Hook4352DB(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4352DB
}

DWORD dwHookReturn435324 = 0x43532A;
void _declspec (naked)Hook435324(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn435324
}

DWORD dwHookReturn435342 = 0x435348;
void _declspec (naked)Hook435342(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn435342
}

DWORD dwHookReturn435367 = 0x43536D;
void _declspec (naked)Hook435367(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn435367
}

DWORD dwHookReturn43538B = 0x435391;
void _declspec (naked)Hook43538B(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43538B
}

DWORD dwHookReturn435437 = 0x43543D;
void _declspec (naked)Hook435437(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn435437
}

DWORD dwHookReturn435447 = 0x43544D;
void _declspec (naked)Hook435447(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn435447
}

DWORD dwHookReturn435458 = 0x43545E;
void _declspec (naked)Hook435458(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn435458
}

DWORD dwHookReturn435496 = 0x43549C;
void _declspec (naked)Hook435496(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn435496
}

DWORD dwHookReturn4354AE = 0x4354B4;
void _declspec (naked)Hook4354AE(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4354AE
}

DWORD dwHookReturn4354B9 = 0x4354BF;
void _declspec (naked)Hook4354B9(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4354B9
}

DWORD dwHookReturn4359BF = 0x4359C5;
void _declspec (naked)Hook4359BF(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4359BF
}

DWORD dwHookReturn4359D8 = 0x4359DE;
void _declspec (naked)Hook4359D8(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4359D8
}

DWORD dwHookReturn4359E4 = 0x4359EA;
void _declspec (naked)Hook4359E4(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4359E4
}

DWORD dwHookReturn435B0E = 0x435B14;
void _declspec (naked)Hook435B0E(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn435B0E
}

DWORD dwHookReturn435B27 = 0x435B2D;
void _declspec (naked)Hook435B27(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn435B27
}

DWORD dwHookReturn435B33 = 0x435B39;
void _declspec (naked)Hook435B33(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn435B33
}

DWORD dwHookReturn4368D0 = 0x4368D6;
void _declspec (naked)Hook4368D0(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4368D0
}

DWORD dwHookReturn4368E1 = 0x4368E7;
void _declspec (naked)Hook4368E1(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4368E1
}

DWORD dwHookReturn4368FD = 0x436903;
void _declspec (naked)Hook4368FD(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4368FD
}

DWORD dwHookReturn43690D = 0x436913;
void _declspec (naked)Hook43690D(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43690D
}

DWORD dwHookReturn43691D = 0x436923;
void _declspec (naked)Hook43691D(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43691D
}

DWORD dwHookReturn436926 = 0x43692C;
void _declspec (naked)Hook436926(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn436926
}

DWORD dwHookReturn436A8C = 0x436A92;
void _declspec (naked)Hook436A8C(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn436A8C
}

DWORD dwHookReturn436AA9 = 0x436AAF;
void _declspec (naked)Hook436AA9(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn436AA9
}

DWORD dwHookReturn436AB9 = 0x436ABF;
void _declspec (naked)Hook436AB9(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn436AB9
}

DWORD dwHookReturn436C0F = 0x436C15;
void _declspec (naked)Hook436C0F(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn436C0F
}

DWORD dwHookReturn436C2D = 0x436C33;
void _declspec (naked)Hook436C2D(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn436C2D
}

DWORD dwHookReturn436C42 = 0x436C48;
void _declspec (naked)Hook436C42(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn436C42
}

DWORD dwHookReturn436C57 = 0x436C5D;
void _declspec (naked)Hook436C57(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn436C57
}

DWORD dwHookReturn436C67 = 0x436C6D;
void _declspec (naked)Hook436C67(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn436C67
}

DWORD dwHookReturn436C75 = 0x436C7B;
void _declspec (naked)Hook436C75(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn436C75
}

DWORD dwHookReturn436D40 = 0x436D46;
void _declspec (naked)Hook436D40(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn436D40
}

DWORD dwHookReturn436D55 = 0x436D5B;
void _declspec (naked)Hook436D55(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn436D55
}

DWORD dwHookReturn436D73 = 0x436D79;
void _declspec (naked)Hook436D73(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn436D73
}

DWORD dwHookReturn436D86 = 0x436D8C;
void _declspec (naked)Hook436D86(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn436D86
}

DWORD dwHookReturn436D98 = 0x436D9E;
void _declspec (naked)Hook436D98(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn436D98
}

DWORD dwHookReturn436DA2 = 0x436DA8;
void _declspec (naked)Hook436DA2(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn436DA2
}

DWORD dwHookReturn436F12 = 0x436F18;
void _declspec (naked)Hook436F12(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn436F12
}

DWORD dwHookReturn436F2B = 0x436F31;
void _declspec (naked)Hook436F2B(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn436F2B
}

DWORD dwHookReturn436F3B = 0x436F41;
void _declspec (naked)Hook436F3B(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn436F3B
}

DWORD dwHookReturn437220 = 0x437226;
void _declspec (naked)Hook437220(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn437220
}

DWORD dwHookReturn437239 = 0x43723F;
void _declspec (naked)Hook437239(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn437239
}

DWORD dwHookReturn437247 = 0x43724D;
void _declspec (naked)Hook437247(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn437247
}

DWORD dwHookReturn43783E = 0x437844;
void _declspec (naked)Hook43783E(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43783E
}

DWORD dwHookReturn43784E = 0x437854;
void _declspec (naked)Hook43784E(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43784E
}

DWORD dwHookReturn43792A = 0x437930;
void _declspec (naked)Hook43792A(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43792A
}

DWORD dwHookReturn43794E = 0x437954;
void _declspec (naked)Hook43794E(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43794E
}

DWORD dwHookReturn437964 = 0x43796A;
void _declspec (naked)Hook437964(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn437964
}

DWORD dwHookReturn43797A = 0x437980;
void _declspec (naked)Hook43797A(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43797A
}

DWORD dwHookReturn437BDC = 0x437BE2;
void _declspec (naked)Hook437BDC(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn437BDC
}

DWORD dwHookReturn437BF0 = 0x437BF6;
void _declspec (naked)Hook437BF0(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn437BF0
}

DWORD dwHookReturn437CF0 = 0x437CF6;
void _declspec (naked)Hook437CF0(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn437CF0
}

DWORD dwHookReturn437D04 = 0x437D0A;
void _declspec (naked)Hook437D04(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn437D04
}

DWORD dwHookReturn437DF1 = 0x437DF7;
void _declspec (naked)Hook437DF1(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn437DF1
}

DWORD dwHookReturn437E01 = 0x437E07;
void _declspec (naked)Hook437E01(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn437E01
}

DWORD dwHookReturn437E21 = 0x437E27;
void _declspec (naked)Hook437E21(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn437E21
}

DWORD dwHookReturn437E31 = 0x437E37;
void _declspec (naked)Hook437E31(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn437E31
}

DWORD dwHookReturn437E51 = 0x437E57;
void _declspec (naked)Hook437E51(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn437E51
}

DWORD dwHookReturn437E61 = 0x437E67;
void _declspec (naked)Hook437E61(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn437E61
}

DWORD dwHookReturn43837F = 0x438385;
void _declspec (naked)Hook43837F(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43837F
}

DWORD dwHookReturn438393 = 0x438399;
void _declspec (naked)Hook438393(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn438393
}

DWORD dwHookReturn438451 = 0x438457;
void _declspec (naked)Hook438451(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn438451
}

DWORD dwHookReturn438465 = 0x43846B;
void _declspec (naked)Hook438465(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn438465
}

DWORD dwHookReturn438560 = 0x438566;
void _declspec (naked)Hook438560(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn438560
}

DWORD dwHookReturn438570 = 0x438576;
void _declspec (naked)Hook438570(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn438570
}

DWORD dwHookReturn438590 = 0x438596;
void _declspec (naked)Hook438590(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn438590
}

DWORD dwHookReturn4385AE = 0x4385B4;
void _declspec (naked)Hook4385AE(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4385AE
}

DWORD dwHookReturn4385C2 = 0x4385C8;
void _declspec (naked)Hook4385C2(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4385C2
}

DWORD dwHookReturn4385CE = 0x4385D4;
void _declspec (naked)Hook4385CE(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4385CE
}

DWORD dwHookReturn438701 = 0x438707;
void _declspec (naked)Hook438701(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn438701
}

DWORD dwHookReturn438719 = 0x43871F;
void _declspec (naked)Hook438719(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn438719
}

DWORD dwHookReturn438725 = 0x43872B;
void _declspec (naked)Hook438725(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn438725
}

DWORD dwHookReturn4388CC = 0x4388D2;
void _declspec (naked)Hook4388CC(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn4388CC
}

DWORD dwHookReturn4388E8 = 0x4388EE;
void _declspec (naked)Hook4388E8(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4388E8
}

DWORD dwHookReturn4388F4 = 0x4388FA;
void _declspec (naked)Hook4388F4(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn4388F4
}

DWORD dwHookReturn43894C = 0x438952;
void _declspec (naked)Hook43894C(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43894C
}

DWORD dwHookReturn43896D = 0x438973;
void _declspec (naked)Hook43896D(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43896D
}

DWORD dwHookReturn438994 = 0x43899A;
void _declspec (naked)Hook438994(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn438994
}

DWORD dwHookReturn4389BA = 0x4389C0;
void _declspec (naked)Hook4389BA(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn4389BA
}

DWORD dwHookReturn438DAC = 0x438DB2;
void _declspec (naked)Hook438DAC(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn438DAC
}

DWORD dwHookReturn438DCA = 0x438DD0;
void _declspec (naked)Hook438DCA(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn438DCA
}

DWORD dwHookReturn438DD6 = 0x438DDC;
void _declspec (naked)Hook438DD6(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn438DD6
}

DWORD dwHookReturn438E17 = 0x438E1D;
void _declspec (naked)Hook438E17(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn438E17
}

DWORD dwHookReturn438E35 = 0x438E3B;
void _declspec (naked)Hook438E35(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn438E35
}

DWORD dwHookReturn438E41 = 0x438E47;
void _declspec (naked)Hook438E41(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn438E41
}

DWORD dwHookReturn438FD4 = 0x438FDA;
void _declspec (naked)Hook438FD4(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn438FD4
}

DWORD dwHookReturn438FED = 0x438FF3;
void _declspec (naked)Hook438FED(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn438FED
}

DWORD dwHookReturn439005 = 0x43900B;
void _declspec (naked)Hook439005(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn439005
}

DWORD dwHookReturn439011 = 0x439017;
void _declspec (naked)Hook439011(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn439011
}

DWORD dwHookReturn43A162 = 0x43A168;
void _declspec (naked)Hook43A162(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43A162
}

DWORD dwHookReturn43A17A = 0x43A180;
void _declspec (naked)Hook43A17A(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43A17A
}

DWORD dwHookReturn43A1A4 = 0x43A1AA;
void _declspec (naked)Hook43A1A4(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43A1A4
}

DWORD dwHookReturn43A1B1 = 0x43A1B7;
void _declspec (naked)Hook43A1B1(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43A1B1
}

DWORD dwHookReturn43A61D = 0x43A623;
void _declspec (naked)Hook43A61D(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn43A61D
}

DWORD dwHookReturn43A647 = 0x43A64D;
void _declspec (naked)Hook43A647(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43A647
}

DWORD dwHookReturn43A661 = 0x43A667;
void _declspec (naked)Hook43A661(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43A661
}

DWORD dwHookReturn43A670 = 0x43A676;
void _declspec (naked)Hook43A670(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn43A670
}

DWORD dwHookReturn43A694 = 0x43A69A;
void _declspec (naked)Hook43A694(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43A694
}

DWORD dwHookReturn43A6B4 = 0x43A6BA;
void _declspec (naked)Hook43A6B4(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43A6B4
}

DWORD dwHookReturn43A759 = 0x43A75F;
void _declspec (naked)Hook43A759(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn43A759
}

DWORD dwHookReturn43A783 = 0x43A789;
void _declspec (naked)Hook43A783(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43A783
}

DWORD dwHookReturn43A79D = 0x43A7A3;
void _declspec (naked)Hook43A79D(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43A79D
}

DWORD dwHookReturn43A7AC = 0x43A7B2;
void _declspec (naked)Hook43A7AC(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn43A7AC
}

DWORD dwHookReturn43A7D0 = 0x43A7D6;
void _declspec (naked)Hook43A7D0(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43A7D0
}

DWORD dwHookReturn43A7F0 = 0x43A7F6;
void _declspec (naked)Hook43A7F0(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43A7F0
}

DWORD dwHookReturn43AE4C = 0x43AE52;
void _declspec (naked)Hook43AE4C(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn43AE4C
}

DWORD dwHookReturn43AE7B = 0x43AE81;
void _declspec (naked)Hook43AE7B(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43AE7B
}

DWORD dwHookReturn43AE9A = 0x43AEA0;
void _declspec (naked)Hook43AE9A(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43AE9A
}

DWORD dwHookReturn43AEB9 = 0x43AEBF;
void _declspec (naked)Hook43AEB9(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43AEB9
}

DWORD dwHookReturn43AED1 = 0x43AED7;
void _declspec (naked)Hook43AED1(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43AED1
}

DWORD dwHookReturn43AEEC = 0x43AEF2;
void _declspec (naked)Hook43AEEC(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn43AEEC
}

DWORD dwHookReturn43AF50 = 0x43AF56;
void _declspec (naked)Hook43AF50(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn43AF50
}

DWORD dwHookReturn43AF7F = 0x43AF85;
void _declspec (naked)Hook43AF7F(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43AF7F
}

DWORD dwHookReturn43AF9E = 0x43AFA4;
void _declspec (naked)Hook43AF9E(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43AF9E
}

DWORD dwHookReturn43AFBD = 0x43AFC3;
void _declspec (naked)Hook43AFBD(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43AFBD
}

DWORD dwHookReturn43AFD5 = 0x43AFDB;
void _declspec (naked)Hook43AFD5(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43AFD5
}

DWORD dwHookReturn43AFF0 = 0x43AFF6;
void _declspec (naked)Hook43AFF0(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn43AFF0
}

DWORD dwHookReturn43B08C = 0x43B092;
void _declspec (naked)Hook43B08C(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43B08C
}

DWORD dwHookReturn43B0B5 = 0x43B0BB;
void _declspec (naked)Hook43B0B5(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43B0B5
}

DWORD dwHookReturn43B0D3 = 0x43B0D9;
void _declspec (naked)Hook43B0D3(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn43B0D3
}

DWORD dwHookReturn43B0F3 = 0x43B0F9;
void _declspec (naked)Hook43B0F3(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn43B0F3
}

DWORD dwHookReturn442BFB = 0x442C01;
void _declspec (naked)Hook442BFB(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn442BFB
}

DWORD dwHookReturn442C17 = 0x442C1D;
void _declspec (naked)Hook442C17(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn442C17
}

DWORD dwHookReturn442C23 = 0x442C29;
void _declspec (naked)Hook442C23(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn442C23
}

DWORD dwHookReturn442EBF = 0x442EC5;
void _declspec (naked)Hook442EBF(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftZ
    _asm jmp dwHookReturn442EBF
}

DWORD dwHookReturn442EDB = 0x442EE1;
void _declspec (naked)Hook442EDB(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftY
    _asm jmp dwHookReturn442EDB
}

DWORD dwHookReturn442EE7 = 0x442EED;
void _declspec (naked)Hook442EE7(){
    _asm fmul f8xDivider
    _asm fadd fPathShiftX
    _asm jmp dwHookReturn442EE7
}

void InstallPathDivHooks() {
   //Hooks for Path Shift for X Coords
   CMemory::NoOperation(0x41CD42, 6);
   CMemory::InstallCallHook(0x41CD42, &Hook41CD42, ASM_JMP);
   CMemory::NoOperation(0x41CDA7, 6);
   CMemory::InstallCallHook(0x41CDA7, &Hook41CDA7, ASM_JMP);
   CMemory::NoOperation(0x41D0F5, 6);
   CMemory::InstallCallHook(0x41D0F5, &Hook41D0F5, ASM_JMP);
   CMemory::NoOperation(0x41D133, 6);
   CMemory::InstallCallHook(0x41D133, &Hook41D133, ASM_JMP);
   CMemory::NoOperation(0x41D1F5, 6);
   CMemory::InstallCallHook(0x41D1F5, &Hook41D1F5, ASM_JMP);
   CMemory::NoOperation(0x41D233, 6);
   CMemory::InstallCallHook(0x41D233, &Hook41D233, ASM_JMP);
   CMemory::NoOperation(0x41F0EE, 6);
   CMemory::InstallCallHook(0x41F0EE, &Hook41F0EE, ASM_JMP);
   CMemory::NoOperation(0x41F156, 6);
   CMemory::InstallCallHook(0x41F156, &Hook41F156, ASM_JMP);
   CMemory::NoOperation(0x41F3AC, 6);
   CMemory::InstallCallHook(0x41F3AC, &Hook41F3AC, ASM_JMP);
   CMemory::NoOperation(0x41F582, 6);
   CMemory::InstallCallHook(0x41F582, &Hook41F582, ASM_JMP);
   CMemory::NoOperation(0x41F8D7, 6);
   CMemory::InstallCallHook(0x41F8D7, &Hook41F8D7, ASM_JMP);
   CMemory::NoOperation(0x421049, 6);
   CMemory::InstallCallHook(0x421049, &Hook421049, ASM_JMP);
   CMemory::NoOperation(0x42105B, 6);
   CMemory::InstallCallHook(0x42105B, &Hook42105B, ASM_JMP);
   CMemory::NoOperation(0x4211D9, 6);
   CMemory::InstallCallHook(0x4211D9, &Hook4211D9, ASM_JMP);
   CMemory::NoOperation(0x421235, 6);
   CMemory::InstallCallHook(0x421235, &Hook421235, ASM_JMP);
   CMemory::NoOperation(0x42144F, 6);
   CMemory::InstallCallHook(0x42144F, &Hook42144F, ASM_JMP);
   CMemory::NoOperation(0x421668, 6);
   CMemory::InstallCallHook(0x421668, &Hook421668, ASM_JMP);
   CMemory::NoOperation(0x4216A9, 6);
   CMemory::InstallCallHook(0x4216A9, &Hook4216A9, ASM_JMP);
   CMemory::NoOperation(0x4219D4, 6);
   CMemory::InstallCallHook(0x4219D4, &Hook4219D4, ASM_JMP);
   CMemory::NoOperation(0x4219E6, 6);
   CMemory::InstallCallHook(0x4219E6, &Hook4219E6, ASM_JMP);
   CMemory::NoOperation(0x421B94, 6);
   CMemory::InstallCallHook(0x421B94, &Hook421B94, ASM_JMP);
   CMemory::NoOperation(0x421BF7, 6);
   CMemory::InstallCallHook(0x421BF7, &Hook421BF7, ASM_JMP);
   CMemory::NoOperation(0x421DF9, 6);
   CMemory::InstallCallHook(0x421DF9, &Hook421DF9, ASM_JMP);
   CMemory::NoOperation(0x421E43, 6);
   CMemory::InstallCallHook(0x421E43, &Hook421E43, ASM_JMP);
   CMemory::NoOperation(0x421E81, 6);
   CMemory::InstallCallHook(0x421E81, &Hook421E81, ASM_JMP);
   CMemory::NoOperation(0x4226A6, 6);
   CMemory::InstallCallHook(0x4226A6, &Hook4226A6, ASM_JMP);
   CMemory::NoOperation(0x4226BA, 6);
   CMemory::InstallCallHook(0x4226BA, &Hook4226BA, ASM_JMP);
   CMemory::NoOperation(0x422832, 6);
   CMemory::InstallCallHook(0x422832, &Hook422832, ASM_JMP);
   CMemory::NoOperation(0x42288E, 6);
   CMemory::InstallCallHook(0x42288E, &Hook42288E, ASM_JMP);
   CMemory::NoOperation(0x425F2B, 6);
   CMemory::InstallCallHook(0x425F2B, &Hook425F2B, ASM_JMP);
   CMemory::NoOperation(0x425F91, 6);
   CMemory::InstallCallHook(0x425F91, &Hook425F91, ASM_JMP);
   CMemory::NoOperation(0x427BC8, 6);
   CMemory::InstallCallHook(0x427BC8, &Hook427BC8, ASM_JMP);
   CMemory::NoOperation(0x427BE8, 6);
   CMemory::InstallCallHook(0x427BE8, &Hook427BE8, ASM_JMP);
   CMemory::NoOperation(0x427E26, 6);
   CMemory::InstallCallHook(0x427E26, &Hook427E26, ASM_JMP);
   CMemory::NoOperation(0x427E6B, 6);
   CMemory::InstallCallHook(0x427E6B, &Hook427E6B, ASM_JMP);
   CMemory::NoOperation(0x42814B, 6);
   CMemory::InstallCallHook(0x42814B, &Hook42814B, ASM_JMP);
   CMemory::NoOperation(0x4281D9, 6);
   CMemory::InstallCallHook(0x4281D9, &Hook4281D9, ASM_JMP);
   CMemory::NoOperation(0x4284AC, 6);
   CMemory::InstallCallHook(0x4284AC, &Hook4284AC, ASM_JMP);
   CMemory::NoOperation(0x42852C, 6);
   CMemory::InstallCallHook(0x42852C, &Hook42852C, ASM_JMP);
   CMemory::NoOperation(0x428635, 6);
   CMemory::InstallCallHook(0x428635, &Hook428635, ASM_JMP);
   CMemory::NoOperation(0x428642, 6);
   CMemory::InstallCallHook(0x428642, &Hook428642, ASM_JMP);
   CMemory::NoOperation(0x444330, 6);
   CMemory::InstallCallHook(0x444330, &Hook444330, ASM_JMP);
   CMemory::NoOperation(0x444558, 6);
   CMemory::InstallCallHook(0x444558, &Hook444558, ASM_JMP);
   CMemory::NoOperation(0x444562, 6);
   CMemory::InstallCallHook(0x444562, &Hook444562, ASM_JMP);
   CMemory::NoOperation(0x4445EE, 6);
   CMemory::InstallCallHook(0x4445EE, &Hook4445EE, ASM_JMP);
   CMemory::NoOperation(0x444725, 6);
   CMemory::InstallCallHook(0x444725, &Hook444725, ASM_JMP);
   CMemory::NoOperation(0x444867, 6);
   CMemory::InstallCallHook(0x444867, &Hook444867, ASM_JMP);
   CMemory::NoOperation(0x455172, 6);
   CMemory::InstallCallHook(0x455172, &Hook455172, ASM_JMP);
   CMemory::NoOperation(0x465D7C, 6);
   CMemory::InstallCallHook(0x465D7C, &Hook465D7C, ASM_JMP);
   CMemory::NoOperation(0x465F4C, 6);
   CMemory::InstallCallHook(0x465F4C, &Hook465F4C, ASM_JMP);
   CMemory::NoOperation(0x46613C, 6);
   CMemory::InstallCallHook(0x46613C, &Hook46613C, ASM_JMP);
   CMemory::NoOperation(0x466374, 6);
   CMemory::InstallCallHook(0x466374, &Hook466374, ASM_JMP);
   CMemory::NoOperation(0x466484, 6);
   CMemory::InstallCallHook(0x466484, &Hook466484, ASM_JMP);
   CMemory::NoOperation(0x4664FF, 6);
   CMemory::InstallCallHook(0x4664FF, &Hook4664FF, ASM_JMP);
   CMemory::NoOperation(0x466792, 6);
   CMemory::InstallCallHook(0x466792, &Hook466792, ASM_JMP);
   CMemory::NoOperation(0x46694D, 6);
   CMemory::InstallCallHook(0x46694D, &Hook46694D, ASM_JMP);
   CMemory::NoOperation(0x46697F, 6);
   CMemory::InstallCallHook(0x46697F, &Hook46697F, ASM_JMP);
   CMemory::NoOperation(0x4669A2, 6);
   CMemory::InstallCallHook(0x4669A2, &Hook4669A2, ASM_JMP);
   CMemory::NoOperation(0x4AE9FB, 6);
   CMemory::InstallCallHook(0x4AE9FB, &Hook4AE9FB, ASM_JMP);
   CMemory::NoOperation(0x4D4995, 6);
   CMemory::InstallCallHook(0x4D4995, &Hook4D4995, ASM_JMP);
   CMemory::NoOperation(0x4D4B21, 6);
   CMemory::InstallCallHook(0x4D4B21, &Hook4D4B21, ASM_JMP);
   CMemory::NoOperation(0x4F780A, 6);
   CMemory::InstallCallHook(0x4F780A, &Hook4F780A, ASM_JMP);
   CMemory::NoOperation(0x4F9D7B, 6);
   CMemory::InstallCallHook(0x4F9D7B, &Hook4F9D7B, ASM_JMP);
   CMemory::NoOperation(0x4FA22F, 6);
   CMemory::InstallCallHook(0x4FA22F, &Hook4FA22F, ASM_JMP);
   CMemory::NoOperation(0x4FA956, 6);
   CMemory::InstallCallHook(0x4FA956, &Hook4FA956, ASM_JMP);
   CMemory::NoOperation(0x4FABB2, 6);
   CMemory::InstallCallHook(0x4FABB2, &Hook4FABB2, ASM_JMP);
   CMemory::NoOperation(0x5071E4, 6);
   CMemory::InstallCallHook(0x5071E4, &Hook5071E4, ASM_JMP);
   CMemory::NoOperation(0x507392, 6);
   CMemory::InstallCallHook(0x507392, &Hook507392, ASM_JMP);
   CMemory::NoOperation(0x507430, 6);
   CMemory::InstallCallHook(0x507430, &Hook507430, ASM_JMP);
   CMemory::NoOperation(0x5074B4, 6);
   CMemory::InstallCallHook(0x5074B4, &Hook5074B4, ASM_JMP);
   CMemory::NoOperation(0x507538, 6);
   CMemory::InstallCallHook(0x507538, &Hook507538, ASM_JMP);
   CMemory::NoOperation(0x5122F6, 6);
   CMemory::InstallCallHook(0x5122F6, &Hook5122F6, ASM_JMP);
   CMemory::NoOperation(0x513F13, 6);
   CMemory::InstallCallHook(0x513F13, &Hook513F13, ASM_JMP);
   CMemory::NoOperation(0x513F9A, 6);
   CMemory::InstallCallHook(0x513F9A, &Hook513F9A, ASM_JMP);
   CMemory::NoOperation(0x5140A6, 6);
   CMemory::InstallCallHook(0x5140A6, &Hook5140A6, ASM_JMP);
   CMemory::NoOperation(0x5141AA, 6);
   CMemory::InstallCallHook(0x5141AA, &Hook5141AA, ASM_JMP);
   CMemory::NoOperation(0x51F786, 6);
   CMemory::InstallCallHook(0x51F786, &Hook51F786, ASM_JMP);
   CMemory::NoOperation(0x520ECB, 6);
   CMemory::InstallCallHook(0x520ECB, &Hook520ECB, ASM_JMP);
   CMemory::NoOperation(0x4351D8, 6);
   CMemory::InstallCallHook(0x4351D8, &Hook4351D8, ASM_JMP);
   CMemory::NoOperation(0x4352DB, 6);
   CMemory::InstallCallHook(0x4352DB, &Hook4352DB, ASM_JMP);
   CMemory::NoOperation(0x435342, 6);
   CMemory::InstallCallHook(0x435342, &Hook435342, ASM_JMP);
   CMemory::NoOperation(0x435367, 6);
   CMemory::InstallCallHook(0x435367, &Hook435367, ASM_JMP);
   CMemory::NoOperation(0x435458, 6);
   CMemory::InstallCallHook(0x435458, &Hook435458, ASM_JMP);
   CMemory::NoOperation(0x4354B9, 6);
   CMemory::InstallCallHook(0x4354B9, &Hook4354B9, ASM_JMP);
   CMemory::NoOperation(0x4359E4, 6);
   CMemory::InstallCallHook(0x4359E4, &Hook4359E4, ASM_JMP);
   CMemory::NoOperation(0x435B33, 6);
   CMemory::InstallCallHook(0x435B33, &Hook435B33, ASM_JMP);
   CMemory::NoOperation(0x43691D, 6);
   CMemory::InstallCallHook(0x43691D, &Hook43691D, ASM_JMP);
   CMemory::NoOperation(0x436926, 6);
   CMemory::InstallCallHook(0x436926, &Hook436926, ASM_JMP);
   CMemory::NoOperation(0x436AB9, 6);
   CMemory::InstallCallHook(0x436AB9, &Hook436AB9, ASM_JMP);
   CMemory::NoOperation(0x436C57, 6);
   CMemory::InstallCallHook(0x436C57, &Hook436C57, ASM_JMP);
   CMemory::NoOperation(0x436C67, 6);
   CMemory::InstallCallHook(0x436C67, &Hook436C67, ASM_JMP);
   CMemory::NoOperation(0x436D98, 6);
   CMemory::InstallCallHook(0x436D98, &Hook436D98, ASM_JMP);
   CMemory::NoOperation(0x436DA2, 6);
   CMemory::InstallCallHook(0x436DA2, &Hook436DA2, ASM_JMP);
   CMemory::NoOperation(0x436F3B, 6);
   CMemory::InstallCallHook(0x436F3B, &Hook436F3B, ASM_JMP);
   CMemory::NoOperation(0x437247, 6);
   CMemory::InstallCallHook(0x437247, &Hook437247, ASM_JMP);
   CMemory::NoOperation(0x43784E, 6);
   CMemory::InstallCallHook(0x43784E, &Hook43784E, ASM_JMP);
   CMemory::NoOperation(0x43792A, 6);
   CMemory::InstallCallHook(0x43792A, &Hook43792A, ASM_JMP);
   CMemory::NoOperation(0x437964, 6);
   CMemory::InstallCallHook(0x437964, &Hook437964, ASM_JMP);
   CMemory::NoOperation(0x437BF0, 6);
   CMemory::InstallCallHook(0x437BF0, &Hook437BF0, ASM_JMP);
   CMemory::NoOperation(0x437D04, 6);
   CMemory::InstallCallHook(0x437D04, &Hook437D04, ASM_JMP);
   CMemory::NoOperation(0x437E51, 6);
   CMemory::InstallCallHook(0x437E51, &Hook437E51, ASM_JMP);
   CMemory::NoOperation(0x437E61, 6);
   CMemory::InstallCallHook(0x437E61, &Hook437E61, ASM_JMP);
   CMemory::NoOperation(0x438393, 6);
   CMemory::InstallCallHook(0x438393, &Hook438393, ASM_JMP);
   CMemory::NoOperation(0x438465, 6);
   CMemory::InstallCallHook(0x438465, &Hook438465, ASM_JMP);
   CMemory::NoOperation(0x4385C2, 6);
   CMemory::InstallCallHook(0x4385C2, &Hook4385C2, ASM_JMP);
   CMemory::NoOperation(0x4385CE, 6);
   CMemory::InstallCallHook(0x4385CE, &Hook4385CE, ASM_JMP);
   CMemory::NoOperation(0x438725, 6);
   CMemory::InstallCallHook(0x438725, &Hook438725, ASM_JMP);
   CMemory::NoOperation(0x4388F4, 6);
   CMemory::InstallCallHook(0x4388F4, &Hook4388F4, ASM_JMP);
   CMemory::NoOperation(0x43896D, 6);
   CMemory::InstallCallHook(0x43896D, &Hook43896D, ASM_JMP);
   CMemory::NoOperation(0x438994, 6);
   CMemory::InstallCallHook(0x438994, &Hook438994, ASM_JMP);
   CMemory::NoOperation(0x438DD6, 6);
   CMemory::InstallCallHook(0x438DD6, &Hook438DD6, ASM_JMP);
   CMemory::NoOperation(0x438E41, 6);
   CMemory::InstallCallHook(0x438E41, &Hook438E41, ASM_JMP);
   CMemory::NoOperation(0x438FD4, 6);
   CMemory::InstallCallHook(0x438FD4, &Hook438FD4, ASM_JMP);
   CMemory::NoOperation(0x439005, 6);
   CMemory::InstallCallHook(0x439005, &Hook439005, ASM_JMP);
   CMemory::NoOperation(0x43A1A4, 6);
   CMemory::InstallCallHook(0x43A1A4, &Hook43A1A4, ASM_JMP);
   CMemory::NoOperation(0x43A1B1, 6);
   CMemory::InstallCallHook(0x43A1B1, &Hook43A1B1, ASM_JMP);
   CMemory::NoOperation(0x43A661, 6);
   CMemory::InstallCallHook(0x43A661, &Hook43A661, ASM_JMP);
   CMemory::NoOperation(0x43A6B4, 6);
   CMemory::InstallCallHook(0x43A6B4, &Hook43A6B4, ASM_JMP);
   CMemory::NoOperation(0x43A79D, 6);
   CMemory::InstallCallHook(0x43A79D, &Hook43A79D, ASM_JMP);
   CMemory::NoOperation(0x43A7F0, 6);
   CMemory::InstallCallHook(0x43A7F0, &Hook43A7F0, ASM_JMP);
   CMemory::NoOperation(0x43AE9A, 6);
   CMemory::InstallCallHook(0x43AE9A, &Hook43AE9A, ASM_JMP);
   CMemory::NoOperation(0x43AEB9, 6);
   CMemory::InstallCallHook(0x43AEB9, &Hook43AEB9, ASM_JMP);
   CMemory::NoOperation(0x43AF9E, 6);
   CMemory::InstallCallHook(0x43AF9E, &Hook43AF9E, ASM_JMP);
   CMemory::NoOperation(0x43AFBD, 6);
   CMemory::InstallCallHook(0x43AFBD, &Hook43AFBD, ASM_JMP);
   CMemory::NoOperation(0x43B0B5, 6);
   CMemory::InstallCallHook(0x43B0B5, &Hook43B0B5, ASM_JMP);
   CMemory::NoOperation(0x43B0F3, 6);
   CMemory::InstallCallHook(0x43B0F3, &Hook43B0F3, ASM_JMP);
   CMemory::NoOperation(0x442C23, 6);
   CMemory::InstallCallHook(0x442C23, &Hook442C23, ASM_JMP);
   CMemory::NoOperation(0x442EE7, 6);
   CMemory::InstallCallHook(0x442EE7, &Hook442EE7, ASM_JMP);


    //Hooks for Path Shift for Y Coords
   CMemory::NoOperation(0x41CD60, 6);
   CMemory::InstallCallHook(0x41CD60, &Hook41CD60, ASM_JMP);
   CMemory::NoOperation(0x41CDC8, 6);
   CMemory::InstallCallHook(0x41CDC8, &Hook41CDC8, ASM_JMP);
   CMemory::NoOperation(0x41D105, 6);
   CMemory::InstallCallHook(0x41D105, &Hook41D105, ASM_JMP);
   CMemory::NoOperation(0x41D143, 6);
   CMemory::InstallCallHook(0x41D143, &Hook41D143, ASM_JMP);
   CMemory::NoOperation(0x41D21D, 6);
   CMemory::InstallCallHook(0x41D21D, &Hook41D21D, ASM_JMP);
   CMemory::NoOperation(0x41D23F, 6);
   CMemory::InstallCallHook(0x41D23F, &Hook41D23F, ASM_JMP);
   CMemory::NoOperation(0x41F11E, 6);
   CMemory::InstallCallHook(0x41F11E, &Hook41F11E, ASM_JMP);
   CMemory::NoOperation(0x41F16E, 6);
   CMemory::InstallCallHook(0x41F16E, &Hook41F16E, ASM_JMP);
   CMemory::NoOperation(0x41F3E7, 6);
   CMemory::InstallCallHook(0x41F3E7, &Hook41F3E7, ASM_JMP);
   CMemory::NoOperation(0x41F558, 6);
   CMemory::InstallCallHook(0x41F558, &Hook41F558, ASM_JMP);
   CMemory::NoOperation(0x41F89C, 6);
   CMemory::InstallCallHook(0x41F89C, &Hook41F89C, ASM_JMP);
   CMemory::NoOperation(0x42100B, 6);
   CMemory::InstallCallHook(0x42100B, &Hook42100B, ASM_JMP);
   CMemory::NoOperation(0x421033, 6);
   CMemory::InstallCallHook(0x421033, &Hook421033, ASM_JMP);
   CMemory::NoOperation(0x4211C7, 6);
   CMemory::InstallCallHook(0x4211C7, &Hook4211C7, ASM_JMP);
   CMemory::NoOperation(0x421223, 6);
   CMemory::InstallCallHook(0x421223, &Hook421223, ASM_JMP);
   CMemory::NoOperation(0x42147E, 6);
   CMemory::InstallCallHook(0x42147E, &Hook42147E, ASM_JMP);
   CMemory::NoOperation(0x421689, 6);
   CMemory::InstallCallHook(0x421689, &Hook421689, ASM_JMP);
   CMemory::NoOperation(0x4216B5, 6);
   CMemory::InstallCallHook(0x4216B5, &Hook4216B5, ASM_JMP);
   CMemory::NoOperation(0x421996, 6);
   CMemory::InstallCallHook(0x421996, &Hook421996, ASM_JMP);
   CMemory::NoOperation(0x4219BE, 6);
   CMemory::InstallCallHook(0x4219BE, &Hook4219BE, ASM_JMP);
   CMemory::NoOperation(0x421B82, 6);
   CMemory::InstallCallHook(0x421B82, &Hook421B82, ASM_JMP);
   CMemory::NoOperation(0x421BE5, 6);
   CMemory::InstallCallHook(0x421BE5, &Hook421BE5, ASM_JMP);
   CMemory::NoOperation(0x421E29, 6);
   CMemory::InstallCallHook(0x421E29, &Hook421E29, ASM_JMP);
   CMemory::NoOperation(0x421E65, 6);
   CMemory::InstallCallHook(0x421E65, &Hook421E65, ASM_JMP);
   CMemory::NoOperation(0x421E8D, 6);
   CMemory::InstallCallHook(0x421E8D, &Hook421E8D, ASM_JMP);
   CMemory::NoOperation(0x422632, 6);
   CMemory::InstallCallHook(0x422632, &Hook422632, ASM_JMP);
   CMemory::NoOperation(0x422660, 6);
   CMemory::InstallCallHook(0x422660, &Hook422660, ASM_JMP);
   CMemory::NoOperation(0x422676, 6);
   CMemory::InstallCallHook(0x422676, &Hook422676, ASM_JMP);
   CMemory::NoOperation(0x42268C, 6);
   CMemory::InstallCallHook(0x42268C, &Hook42268C, ASM_JMP);
   CMemory::NoOperation(0x422820, 6);
   CMemory::InstallCallHook(0x422820, &Hook422820, ASM_JMP);
   CMemory::NoOperation(0x42287C, 6);
   CMemory::InstallCallHook(0x42287C, &Hook42287C, ASM_JMP);
   CMemory::NoOperation(0x425F1B, 6);
   CMemory::InstallCallHook(0x425F1B, &Hook425F1B, ASM_JMP);
   CMemory::NoOperation(0x425F77, 6);
   CMemory::InstallCallHook(0x425F77, &Hook425F77, ASM_JMP);
   CMemory::NoOperation(0x427B46, 6);
   CMemory::InstallCallHook(0x427B46, &Hook427B46, ASM_JMP);
   CMemory::NoOperation(0x427B74, 6);
   CMemory::InstallCallHook(0x427B74, &Hook427B74, ASM_JMP);
   CMemory::NoOperation(0x427B90, 6);
   CMemory::InstallCallHook(0x427B90, &Hook427B90, ASM_JMP);
   CMemory::NoOperation(0x427BAC, 6);
   CMemory::InstallCallHook(0x427BAC, &Hook427BAC, ASM_JMP);
   CMemory::NoOperation(0x427E06, 6);
   CMemory::InstallCallHook(0x427E06, &Hook427E06, ASM_JMP);
   CMemory::NoOperation(0x427E55, 6);
   CMemory::InstallCallHook(0x427E55, &Hook427E55, ASM_JMP);
   CMemory::NoOperation(0x428130, 6);
   CMemory::InstallCallHook(0x428130, &Hook428130, ASM_JMP);
   CMemory::NoOperation(0x4281BE, 6);
   CMemory::InstallCallHook(0x4281BE, &Hook4281BE, ASM_JMP);
   CMemory::NoOperation(0x428491, 6);
   CMemory::InstallCallHook(0x428491, &Hook428491, ASM_JMP);
   CMemory::NoOperation(0x428508, 6);
   CMemory::InstallCallHook(0x428508, &Hook428508, ASM_JMP);
   CMemory::NoOperation(0x428605, 6);
   CMemory::InstallCallHook(0x428605, &Hook428605, ASM_JMP);
   CMemory::NoOperation(0x42861D, 6);
   CMemory::InstallCallHook(0x42861D, &Hook42861D, ASM_JMP);
   CMemory::NoOperation(0x444393, 6);
   CMemory::InstallCallHook(0x444393, &Hook444393, ASM_JMP);
   CMemory::NoOperation(0x444525, 6);
   CMemory::InstallCallHook(0x444525, &Hook444525, ASM_JMP);
   CMemory::NoOperation(0x44453A, 6);
   CMemory::InstallCallHook(0x44453A, &Hook44453A, ASM_JMP);
   CMemory::NoOperation(0x444604, 6);
   CMemory::InstallCallHook(0x444604, &Hook444604, ASM_JMP);
   CMemory::NoOperation(0x444746, 6);
   CMemory::InstallCallHook(0x444746, &Hook444746, ASM_JMP);
   CMemory::NoOperation(0x44487D, 6);
   CMemory::InstallCallHook(0x44487D, &Hook44487D, ASM_JMP);
   CMemory::NoOperation(0x45518E, 6);
   CMemory::InstallCallHook(0x45518E, &Hook45518E, ASM_JMP);
   CMemory::NoOperation(0x465D51, 6);
   CMemory::InstallCallHook(0x465D51, &Hook465D51, ASM_JMP);
   CMemory::NoOperation(0x465F21, 6);
   CMemory::InstallCallHook(0x465F21, &Hook465F21, ASM_JMP);
   CMemory::NoOperation(0x466111, 6);
   CMemory::InstallCallHook(0x466111, &Hook466111, ASM_JMP);
   CMemory::NoOperation(0x4663A0, 6);
   CMemory::InstallCallHook(0x4663A0, &Hook4663A0, ASM_JMP);
   CMemory::NoOperation(0x4664B5, 6);
   CMemory::InstallCallHook(0x4664B5, &Hook4664B5, ASM_JMP);
   CMemory::NoOperation(0x466515, 6);
   CMemory::InstallCallHook(0x466515, &Hook466515, ASM_JMP);
   CMemory::NoOperation(0x4667AC, 6);
   CMemory::InstallCallHook(0x4667AC, &Hook4667AC, ASM_JMP);
   CMemory::NoOperation(0x466894, 6);
   CMemory::InstallCallHook(0x466894, &Hook466894, ASM_JMP);
   CMemory::NoOperation(0x4668D9, 6);
   CMemory::InstallCallHook(0x4668D9, &Hook4668D9, ASM_JMP);
   CMemory::NoOperation(0x466914, 6);
   CMemory::InstallCallHook(0x466914, &Hook466914, ASM_JMP);
   CMemory::NoOperation(0x4AEA13, 6);
   CMemory::InstallCallHook(0x4AEA13, &Hook4AEA13, ASM_JMP);
   CMemory::NoOperation(0x4D49A9, 6);
   CMemory::InstallCallHook(0x4D49A9, &Hook4D49A9, ASM_JMP);
   CMemory::NoOperation(0x4D4B35, 6);
   CMemory::InstallCallHook(0x4D4B35, &Hook4D4B35, ASM_JMP);
   CMemory::NoOperation(0x4F7832, 6);
   CMemory::InstallCallHook(0x4F7832, &Hook4F7832, ASM_JMP);
   CMemory::NoOperation(0x4F9D70, 6);
   CMemory::InstallCallHook(0x4F9D70, &Hook4F9D70, ASM_JMP);
   CMemory::NoOperation(0x4FA224, 6);
   CMemory::InstallCallHook(0x4FA224, &Hook4FA224, ASM_JMP);
   CMemory::NoOperation(0x4FA970, 6);
   CMemory::InstallCallHook(0x4FA970, &Hook4FA970, ASM_JMP);
   CMemory::NoOperation(0x4FABCC, 6);
   CMemory::InstallCallHook(0x4FABCC, &Hook4FABCC, ASM_JMP);
   CMemory::NoOperation(0x5071C5, 6);
   CMemory::InstallCallHook(0x5071C5, &Hook5071C5, ASM_JMP);
   CMemory::NoOperation(0x507376, 6);
   CMemory::InstallCallHook(0x507376, &Hook507376, ASM_JMP);
   CMemory::NoOperation(0x507411, 6);
   CMemory::InstallCallHook(0x507411, &Hook507411, ASM_JMP);
   CMemory::NoOperation(0x507495, 6);
   CMemory::InstallCallHook(0x507495, &Hook507495, ASM_JMP);
   CMemory::NoOperation(0x507519, 6);
   CMemory::InstallCallHook(0x507519, &Hook507519, ASM_JMP);
   CMemory::NoOperation(0x512309, 6);
   CMemory::InstallCallHook(0x512309, &Hook512309, ASM_JMP);
   CMemory::NoOperation(0x513F2B, 6);
   CMemory::InstallCallHook(0x513F2B, &Hook513F2B, ASM_JMP);
   CMemory::NoOperation(0x513F7C, 6);
   CMemory::InstallCallHook(0x513F7C, &Hook513F7C, ASM_JMP);
   CMemory::NoOperation(0x514088, 6);
   CMemory::InstallCallHook(0x514088, &Hook514088, ASM_JMP);
   CMemory::NoOperation(0x514196, 6);
   CMemory::InstallCallHook(0x514196, &Hook514196, ASM_JMP);
   CMemory::NoOperation(0x51F767, 6);
   CMemory::InstallCallHook(0x51F767, &Hook51F767, ASM_JMP);
   CMemory::NoOperation(0x520EC0, 6);
   CMemory::InstallCallHook(0x520EC0, &Hook520EC0, ASM_JMP);
   CMemory::NoOperation(0x4351F0, 6);
   CMemory::InstallCallHook(0x4351F0, &Hook4351F0, ASM_JMP);
   CMemory::NoOperation(0x4352D0, 6);
   CMemory::InstallCallHook(0x4352D0, &Hook4352D0, ASM_JMP);
   CMemory::NoOperation(0x435324, 6);
   CMemory::InstallCallHook(0x435324, &Hook435324, ASM_JMP);
   CMemory::NoOperation(0x43538B, 6);
   CMemory::InstallCallHook(0x43538B, &Hook43538B, ASM_JMP);
   CMemory::NoOperation(0x435447, 6);
   CMemory::InstallCallHook(0x435447, &Hook435447, ASM_JMP);
   CMemory::NoOperation(0x4354AE, 6);
   CMemory::InstallCallHook(0x4354AE, &Hook4354AE, ASM_JMP);
   CMemory::NoOperation(0x4359D8, 6);
   CMemory::InstallCallHook(0x4359D8, &Hook4359D8, ASM_JMP);
   CMemory::NoOperation(0x435B27, 6);
   CMemory::InstallCallHook(0x435B27, &Hook435B27, ASM_JMP);
   CMemory::NoOperation(0x4368FD, 6);
   CMemory::InstallCallHook(0x4368FD, &Hook4368FD, ASM_JMP);
   CMemory::NoOperation(0x43690D, 6);
   CMemory::InstallCallHook(0x43690D, &Hook43690D, ASM_JMP);
   CMemory::NoOperation(0x436AA9, 6);
   CMemory::InstallCallHook(0x436AA9, &Hook436AA9, ASM_JMP);
   CMemory::NoOperation(0x436C42, 6);
   CMemory::InstallCallHook(0x436C42, &Hook436C42, ASM_JMP);
   CMemory::NoOperation(0x436C75, 6);
   CMemory::InstallCallHook(0x436C75, &Hook436C75, ASM_JMP);
   CMemory::NoOperation(0x436D73, 6);
   CMemory::InstallCallHook(0x436D73, &Hook436D73, ASM_JMP);
   CMemory::NoOperation(0x436D86, 6);
   CMemory::InstallCallHook(0x436D86, &Hook436D86, ASM_JMP);
   CMemory::NoOperation(0x436F2B, 6);
   CMemory::InstallCallHook(0x436F2B, &Hook436F2B, ASM_JMP);
   CMemory::NoOperation(0x437239, 6);
   CMemory::InstallCallHook(0x437239, &Hook437239, ASM_JMP);
   CMemory::NoOperation(0x43783E, 6);
   CMemory::InstallCallHook(0x43783E, &Hook43783E, ASM_JMP);
   CMemory::NoOperation(0x43794E, 6);
   CMemory::InstallCallHook(0x43794E, &Hook43794E, ASM_JMP);
   CMemory::NoOperation(0x43797A, 6);
   CMemory::InstallCallHook(0x43797A, &Hook43797A, ASM_JMP);
   CMemory::NoOperation(0x437BDC, 6);
   CMemory::InstallCallHook(0x437BDC, &Hook437BDC, ASM_JMP);
   CMemory::NoOperation(0x437CF0, 6);
   CMemory::InstallCallHook(0x437CF0, &Hook437CF0, ASM_JMP);
   CMemory::NoOperation(0x437E21, 6);
   CMemory::InstallCallHook(0x437E21, &Hook437E21, ASM_JMP);
   CMemory::NoOperation(0x437E31, 6);
   CMemory::InstallCallHook(0x437E31, &Hook437E31, ASM_JMP);
   CMemory::NoOperation(0x43837F, 6);
   CMemory::InstallCallHook(0x43837F, &Hook43837F, ASM_JMP);
   CMemory::NoOperation(0x438451, 6);
   CMemory::InstallCallHook(0x438451, &Hook438451, ASM_JMP);
   CMemory::NoOperation(0x438590, 6);
   CMemory::InstallCallHook(0x438590, &Hook438590, ASM_JMP);
   CMemory::NoOperation(0x4385AE, 6);
   CMemory::InstallCallHook(0x4385AE, &Hook4385AE, ASM_JMP);
   CMemory::NoOperation(0x438719, 6);
   CMemory::InstallCallHook(0x438719, &Hook438719, ASM_JMP);
   CMemory::NoOperation(0x4388E8, 6);
   CMemory::InstallCallHook(0x4388E8, &Hook4388E8, ASM_JMP);
   CMemory::NoOperation(0x43894C, 6);
   CMemory::InstallCallHook(0x43894C, &Hook43894C, ASM_JMP);
   CMemory::NoOperation(0x4389BA, 6);
   CMemory::InstallCallHook(0x4389BA, &Hook4389BA, ASM_JMP);
   CMemory::NoOperation(0x438DCA, 6);
   CMemory::InstallCallHook(0x438DCA, &Hook438DCA, ASM_JMP);
   CMemory::NoOperation(0x438E35, 6);
   CMemory::InstallCallHook(0x438E35, &Hook438E35, ASM_JMP);
   CMemory::NoOperation(0x438FED, 6);
   CMemory::InstallCallHook(0x438FED, &Hook438FED, ASM_JMP);
   CMemory::NoOperation(0x439011, 6);
   CMemory::InstallCallHook(0x439011, &Hook439011, ASM_JMP);
   CMemory::NoOperation(0x43A162, 6);
   CMemory::InstallCallHook(0x43A162, &Hook43A162, ASM_JMP);
   CMemory::NoOperation(0x43A17A, 6);
   CMemory::InstallCallHook(0x43A17A, &Hook43A17A, ASM_JMP);
   CMemory::NoOperation(0x43A647, 6);
   CMemory::InstallCallHook(0x43A647, &Hook43A647, ASM_JMP);
   CMemory::NoOperation(0x43A694, 6);
   CMemory::InstallCallHook(0x43A694, &Hook43A694, ASM_JMP);
   CMemory::NoOperation(0x43A783, 6);
   CMemory::InstallCallHook(0x43A783, &Hook43A783, ASM_JMP);
   CMemory::NoOperation(0x43A7D0, 6);
   CMemory::InstallCallHook(0x43A7D0, &Hook43A7D0, ASM_JMP);
   CMemory::NoOperation(0x43AE7B, 6);
   CMemory::InstallCallHook(0x43AE7B, &Hook43AE7B, ASM_JMP);
   CMemory::NoOperation(0x43AED1, 6);
   CMemory::InstallCallHook(0x43AED1, &Hook43AED1, ASM_JMP);
   CMemory::NoOperation(0x43AF7F, 6);
   CMemory::InstallCallHook(0x43AF7F, &Hook43AF7F, ASM_JMP);
   CMemory::NoOperation(0x43AFD5, 6);
   CMemory::InstallCallHook(0x43AFD5, &Hook43AFD5, ASM_JMP);
   CMemory::NoOperation(0x43B08C, 6);
   CMemory::InstallCallHook(0x43B08C, &Hook43B08C, ASM_JMP);
   CMemory::NoOperation(0x43B0D3, 6);
   CMemory::InstallCallHook(0x43B0D3, &Hook43B0D3, ASM_JMP);
   CMemory::NoOperation(0x442C17, 6);
   CMemory::InstallCallHook(0x442C17, &Hook442C17, ASM_JMP);
   CMemory::NoOperation(0x442EDB, 6);
   CMemory::InstallCallHook(0x442EDB, &Hook442EDB, ASM_JMP);


    //Hooks for Path Shift for Z Coords
   CMemory::NoOperation(0x41C6E1, 6);
   CMemory::InstallCallHook(0x41C6E1, &Hook41C6E1, ASM_JMP);
   CMemory::NoOperation(0x41C6FF, 6);
   CMemory::InstallCallHook(0x41C6FF, &Hook41C6FF, ASM_JMP);
   CMemory::NoOperation(0x41CD76, 6);
   CMemory::InstallCallHook(0x41CD76, &Hook41CD76, ASM_JMP);
   CMemory::NoOperation(0x41CDD6, 6);
   CMemory::InstallCallHook(0x41CDD6, &Hook41CDD6, ASM_JMP);
   CMemory::NoOperation(0x42149B, 6);
   CMemory::InstallCallHook(0x42149B, &Hook42149B, ASM_JMP);
   CMemory::NoOperation(0x427DDB, 6);
   CMemory::InstallCallHook(0x427DDB, &Hook427DDB, ASM_JMP);
   CMemory::NoOperation(0x427E35, 6);
   CMemory::InstallCallHook(0x427E35, &Hook427E35, ASM_JMP);
   CMemory::NoOperation(0x4285C6, 6);
   CMemory::InstallCallHook(0x4285C6, &Hook4285C6, ASM_JMP);
   CMemory::NoOperation(0x4285DE, 6);
   CMemory::InstallCallHook(0x4285DE, &Hook4285DE, ASM_JMP);
   CMemory::NoOperation(0x4286F7, 6);
   CMemory::InstallCallHook(0x4286F7, &Hook4286F7, ASM_JMP);
   CMemory::NoOperation(0x428711, 6);
   CMemory::InstallCallHook(0x428711, &Hook428711, ASM_JMP);
   CMemory::NoOperation(0x444616, 6);
   CMemory::InstallCallHook(0x444616, &Hook444616, ASM_JMP);
   CMemory::NoOperation(0x444758, 6);
   CMemory::InstallCallHook(0x444758, &Hook444758, ASM_JMP);
   CMemory::NoOperation(0x44488F, 6);
   CMemory::InstallCallHook(0x44488F, &Hook44488F, ASM_JMP);
   CMemory::NoOperation(0x45519F, 6);
   CMemory::InstallCallHook(0x45519F, &Hook45519F, ASM_JMP);
   CMemory::NoOperation(0x4663BD, 6);
   CMemory::InstallCallHook(0x4663BD, &Hook4663BD, ASM_JMP);
   CMemory::NoOperation(0x4664D8, 6);
   CMemory::InstallCallHook(0x4664D8, &Hook4664D8, ASM_JMP);
   CMemory::NoOperation(0x466524, 6);
   CMemory::InstallCallHook(0x466524, &Hook466524, ASM_JMP);
   CMemory::NoOperation(0x4AEA1E, 6);
   CMemory::InstallCallHook(0x4AEA1E, &Hook4AEA1E, ASM_JMP);
   CMemory::NoOperation(0x4D49B5, 6);
   CMemory::InstallCallHook(0x4D49B5, &Hook4D49B5, ASM_JMP);
   CMemory::NoOperation(0x4D4B41, 6);
   CMemory::InstallCallHook(0x4D4B41, &Hook4D4B41, ASM_JMP);
   CMemory::NoOperation(0x4F9D5B, 6);
   CMemory::InstallCallHook(0x4F9D5B, &Hook4F9D5B, ASM_JMP);
   CMemory::NoOperation(0x4FA20F, 6);
   CMemory::InstallCallHook(0x4FA20F, &Hook4FA20F, ASM_JMP);
   CMemory::NoOperation(0x4FA986, 6);
   CMemory::InstallCallHook(0x4FA986, &Hook4FA986, ASM_JMP);
   CMemory::NoOperation(0x4FABE6, 6);
   CMemory::InstallCallHook(0x4FABE6, &Hook4FABE6, ASM_JMP);
   CMemory::NoOperation(0x5071A6, 6);
   CMemory::InstallCallHook(0x5071A6, &Hook5071A6, ASM_JMP);
   CMemory::NoOperation(0x50735A, 6);
   CMemory::InstallCallHook(0x50735A, &Hook50735A, ASM_JMP);
   CMemory::NoOperation(0x5073F2, 6);
   CMemory::InstallCallHook(0x5073F2, &Hook5073F2, ASM_JMP);
   CMemory::NoOperation(0x507476, 6);
   CMemory::InstallCallHook(0x507476, &Hook507476, ASM_JMP);
   CMemory::NoOperation(0x5074FA, 6);
   CMemory::InstallCallHook(0x5074FA, &Hook5074FA, ASM_JMP);
   CMemory::NoOperation(0x5122E6, 6);
   CMemory::InstallCallHook(0x5122E6, &Hook5122E6, ASM_JMP);
   CMemory::NoOperation(0x51F748, 6);
   CMemory::InstallCallHook(0x51F748, &Hook51F748, ASM_JMP);
   CMemory::NoOperation(0x520EA9, 6);
   CMemory::InstallCallHook(0x520EA9, &Hook520EA9, ASM_JMP);
   CMemory::NoOperation(0x435208, 6);
   CMemory::InstallCallHook(0x435208, &Hook435208, ASM_JMP);
   CMemory::NoOperation(0x4352B8, 6);
   CMemory::InstallCallHook(0x4352B8, &Hook4352B8, ASM_JMP);
   CMemory::NoOperation(0x435437, 6);
   CMemory::InstallCallHook(0x435437, &Hook435437, ASM_JMP);
   CMemory::NoOperation(0x435496, 6);
   CMemory::InstallCallHook(0x435496, &Hook435496, ASM_JMP);
   CMemory::NoOperation(0x4359BF, 6);
   CMemory::InstallCallHook(0x4359BF, &Hook4359BF, ASM_JMP);
   CMemory::NoOperation(0x435B0E, 6);
   CMemory::InstallCallHook(0x435B0E, &Hook435B0E, ASM_JMP);
   CMemory::NoOperation(0x4368D0, 6);
   CMemory::InstallCallHook(0x4368D0, &Hook4368D0, ASM_JMP);
   CMemory::NoOperation(0x4368E1, 6);
   CMemory::InstallCallHook(0x4368E1, &Hook4368E1, ASM_JMP);
   CMemory::NoOperation(0x436A8C, 6);
   CMemory::InstallCallHook(0x436A8C, &Hook436A8C, ASM_JMP);
   CMemory::NoOperation(0x436C0F, 6);
   CMemory::InstallCallHook(0x436C0F, &Hook436C0F, ASM_JMP);
   CMemory::NoOperation(0x436C2D, 6);
   CMemory::InstallCallHook(0x436C2D, &Hook436C2D, ASM_JMP);
   CMemory::NoOperation(0x436D40, 6);
   CMemory::InstallCallHook(0x436D40, &Hook436D40, ASM_JMP);
   CMemory::NoOperation(0x436D55, 6);
   CMemory::InstallCallHook(0x436D55, &Hook436D55, ASM_JMP);
   CMemory::NoOperation(0x436F12, 6);
   CMemory::InstallCallHook(0x436F12, &Hook436F12, ASM_JMP);
   CMemory::NoOperation(0x437220, 6);
   CMemory::InstallCallHook(0x437220, &Hook437220, ASM_JMP);
   CMemory::NoOperation(0x437DF1, 6);
   CMemory::InstallCallHook(0x437DF1, &Hook437DF1, ASM_JMP);
   CMemory::NoOperation(0x437E01, 6);
   CMemory::InstallCallHook(0x437E01, &Hook437E01, ASM_JMP);
   CMemory::NoOperation(0x438560, 6);
   CMemory::InstallCallHook(0x438560, &Hook438560, ASM_JMP);
   CMemory::NoOperation(0x438570, 6);
   CMemory::InstallCallHook(0x438570, &Hook438570, ASM_JMP);
   CMemory::NoOperation(0x438701, 6);
   CMemory::InstallCallHook(0x438701, &Hook438701, ASM_JMP);
   CMemory::NoOperation(0x4388CC, 6);
   CMemory::InstallCallHook(0x4388CC, &Hook4388CC, ASM_JMP);
   CMemory::NoOperation(0x438DAC, 6);
   CMemory::InstallCallHook(0x438DAC, &Hook438DAC, ASM_JMP);
   CMemory::NoOperation(0x438E17, 6);
   CMemory::InstallCallHook(0x438E17, &Hook438E17, ASM_JMP);
   CMemory::NoOperation(0x43A61D, 6);
   CMemory::InstallCallHook(0x43A61D, &Hook43A61D, ASM_JMP);
   CMemory::NoOperation(0x43A670, 6);
   CMemory::InstallCallHook(0x43A670, &Hook43A670, ASM_JMP);
   CMemory::NoOperation(0x43A759, 6);
   CMemory::InstallCallHook(0x43A759, &Hook43A759, ASM_JMP);
   CMemory::NoOperation(0x43A7AC, 6);
   CMemory::InstallCallHook(0x43A7AC, &Hook43A7AC, ASM_JMP);
   CMemory::NoOperation(0x43AE4C, 6);
   CMemory::InstallCallHook(0x43AE4C, &Hook43AE4C, ASM_JMP);
   CMemory::NoOperation(0x43AEEC, 6);
   CMemory::InstallCallHook(0x43AEEC, &Hook43AEEC, ASM_JMP);
   CMemory::NoOperation(0x43AF50, 6);
   CMemory::InstallCallHook(0x43AF50, &Hook43AF50, ASM_JMP);
   CMemory::NoOperation(0x43AFF0, 6);
   CMemory::InstallCallHook(0x43AFF0, &Hook43AFF0, ASM_JMP);
   CMemory::NoOperation(0x442BFB, 6);
   CMemory::InstallCallHook(0x442BFB, &Hook442BFB, ASM_JMP);
   CMemory::NoOperation(0x442EBF, 6);
   CMemory::InstallCallHook(0x442EBF, &Hook442EBF, ASM_JMP);

 }
