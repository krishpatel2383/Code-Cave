event_simpleName=ProcessRollup2 OR event_simpleName=ProcessBlocked CommandLine="net view" OR CommandLine="net user" OR CommandLine="tasklist /v" OR CommandLine="net localgroup administrators" OR CommandLine="net user administrator" OR CommandLine="regedit -e *" OR CommandLine="tasklist /svc" OR CommandLine="regsvr32 /s /u *" OR CommandLine="*CreateObject(\"WScript.Shell\").RegWrite*" OR CommandLine="bitsadmin /rawreturn /transfer getfile*" OR CommandLine="wmic qfe list full" OR CommandLine="schtasks.exe /create"  OR CommandLine="wmic share get" OR CommandLine="wmic nteventlog get" OR CommandLine="wevtutil cl *" OR CommandLine="sc query type= service" OR CommandLine="arp -a *"
| Table FileName CommandLine
| stats count by CommandLine