# File-checker
Finds a file in a specified directory, the function will be returned with these values below:
| Value | Meaning |
|-----------------|----------------------------|
| 0 (FALSE) | File not found or the function have no access or priviledge to find the file or folder (ex. When you want to find the file, but the function itself have limited functionality to open that file or folder.) |
| 1 (TRUE) | The function itself have found the file |

# Note:
This only works on Win32 applications, sometimes this will fail depends if the application itself have a limited functionality when it tries to access the file.
This works better if you set the file with SeFilePriviledge, or use this command:

```
takeown /f <filename> && icacls <filename> /grant "%username%:F"
```

### You can use this code, but you need a credit for this one.

For problems just leave a message on issues or contact my Discord: isolynxx
