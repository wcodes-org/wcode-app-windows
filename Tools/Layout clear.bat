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

Del %A%\Debug\WCode\Lang\Res44B.DLL.mui
Del %A%\Release\WCode\Lang\Res44B.DLL.mui

Del %A%\Debug\WCode\Lang\Res409.DLL.mui
Del %A%\Release\WCode\Lang\Res409.DLL.mui

Del %A%\Debug\WCode\Lang\Res439.DLL.mui
Del %A%\Release\WCode\Lang\Res439.DLL.mui

Del %A%\Debug\WCode\Lang\Res461.DLL.mui
Del %A%\Release\WCode\Lang\Res461.DLL.mui

RD /s /q %A%\Debug\WCode\Lang
RD /s /q %A%\Release\WCode\Lang

Del %A%\Debug\WCode\Splash.bmp
Del %A%\Release\WCode\Splash.bmp

Del %A%\Debug\WCode\Dictionary\WordList_EN.txt
Del %A%\Release\WCode\Dictionary\WordList_EN.txt

RD /s /q %A%\Debug\WCode\Dictionary

@If %A%==x86 (
	@If [%1]==[] (
		@Set A=x64
		@GoTo X
	)
)
