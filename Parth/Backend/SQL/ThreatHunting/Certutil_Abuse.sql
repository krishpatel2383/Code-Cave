event_simpleName=ProcessRollup2 OR event_simpleName=ProcessBlocked OR event_simpleName=SyntheticProcessRollup2 CommandLine="certutil* -encode*" OR CommandLine="certutil* -decode*"
| stats count by CommandLine 