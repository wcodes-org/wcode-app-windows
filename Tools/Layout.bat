@Rem Admin Rights required
@Rem Admin Rights - test
@Echo Off

Net Session >Nul 2>&1

If %ErrorLevel% NEq 0			(
    Echo Run as Administrator
    Pause
    Exit				)

Rem [System32] to [Launch Dir]
CD /D "%~dp0"

@If [%1]==[] (
	@Set A=x86
	@GoTo X				
)
@If %1==x86 (
    @Set A=x86
    @GoTo X
)
@If %1==x64 (
    @Set A=x64
    @GoTo X
)
@Rem Else
	@Echo Params: x86 ^| x64
	@GoTo :Eof
	
:X

MD %A%\Debug\WCode\Lang
MD %A%\Release\WCode\Lang

MkLink %A%\Debug\WCode\Lang\Res44B.DLL.mui ..\..\Lang\EN_US\Res.DLL.mui
MkLink %A%\Release\WCode\Lang\Res44B.DLL.mui ..\..\Lang\EN_US\Res.DLL.mui

MkLink %A%\Debug\WCode\Lang\Res409.DLL.mui ..\..\Lang\HI_IN\Res.DLL.mui
MkLink %A%\Release\WCode\Lang\Res409.DLL.mui ..\..\Lang\HI_IN\Res.DLL.mui

MkLink %A%\Debug\WCode\Lang\Res439.DLL.mui ..\..\Lang\KN_IN\Res.DLL.mui
MkLink %A%\Release\WCode\Lang\Res439.DLL.mui ..\..\Lang\KN_IN\Res.DLL.mui

MkLink %A%\Debug\WCode\Lang\Res461.DLL.mui ..\..\Lang\NE_NP\Res.DLL.mui
MkLink %A%\Release\WCode\Lang\Res461.DLL.mui ..\..\Lang\NE_NP\Res.DLL.mui

MkLink %A%\Debug\WCode\Splash.bmp ..\..\..\Project\Resource\Splash.bmp
MkLink %A%\Release\WCode\Splash.bmp ..\..\..\Project\Resource\Splash.bmp


MD %A%\Debug\WCode\Dictionary
MD %A%\Release\WCode\Dictionary

MkLink %A%\Debug\WCode\Dictionary\WordList_EN.txt ..\..\..\..\Dictionary\WordList_EN.txt
MkLink %A%\Release\WCode\Dictionary\WordList_EN.txt ..\..\..\..\Dictionary\WordList_EN.txt

@If %A%==x86 (
	@If [%1]==[] (
		@Set A=x64
		@GoTo X
	)
)
