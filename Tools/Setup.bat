@Rem Admin Rights Test
@Echo Off

Net Session >Nul 2>&1

If %ErrorLevel% NEq 0			(
    Echo Run as Administrator
    Pause
    Exit				)

Rem [System32] to [Launch Dir]
CD /D "%~dp0"

:OPTIONS
Echo.
Echo .........
Echo   Setup
Echo .........
Echo.
Echo 1 - Layout : for Build Setup
Echo 2 - Deploy : for Built Setup
Echo 3 - Exit
Echo.
Set /P M=Select an Option: 

If %M%==1 Set Mode=Layout
If %M%==2 Set Mode=Deploy
If %M%==3 GoTo :EoF

Echo.
Echo .........
Echo  %Mode%:
Echo .........
Echo.
Echo 1 - x86
Echo 2 - x64
Echo 3 - x86 ^& x64
Echo 4 - Return
Echo.
Set /P O=Select an Option: 

If %O%==1 GoTo X
If %O%==2 GoTo X86
If %O%==3 GoTo X64
IF %O%==4 GoTo OPTIONS

:X
    @Echo On
    Call _%Mode%
    @Echo Off
GoTo OPTIONS

:X86
    @Echo On
    Call _%Mode% x86
    @Echo Off
GoTo OPTIONS

:X64
    @Echo On
    Call _%Mode% x64
    @Echo Off
GoTo OPTIONS
