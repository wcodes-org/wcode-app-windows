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
    @Set PFD=%ProgramFiles(x86)%
	@GoTo X				
)
@If %1==x86 (
    @Set A=x86
    @Set PFD=%ProgramFiles(x86)%
    @GoTo X
)
@If %1==x64 (
    @Set A=x64
    @Set PFD=%ProgramFiles%
    @GoTo X
)
@Rem Else
	@Echo Params: x86 ^| x64
	@GoTo :Eof
	
:X

Del "%PFD%\WCode\WCode.exe"
Del "%PFD%\WCode\Splash.bmp"
Del /D "%PFD%\WCode\Lang"

RD "%PFD%\WCode"

@If %A%==x86 (
	@If [%1]==[] (
		@Set A=x64
		@GoTo X
	)
)
