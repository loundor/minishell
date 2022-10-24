# minishell

### My advancements:
✓ Show prompt waiting for command line ✅
<br />✓ Error message when quotes or double quotes are unclosed ✅
<br />✓ Basic parsing for quotes and double quotes ✅
<br />✓ Added 'echo' builtin command (with -n option) ✅
<br />✓ Added 'cd' builtin command (without options) ✅
<br />✓ Added 'pwd' builtin command (without options)
<br />✓ Added 'env' builtin command (without options or arguments) ✅
<br />✓ Added 'exit' builtin command (without options) ✅
<br />✓ Added possibility to create personal variables ✅
<br />✓ Added 'unset' builtin command (without options) ✅
<br />✓ Added 'export' builtin command (without options) ✅
<br />✓ Added a fonctionnal history, with file storage. ✅
<br />✓ Added execution of external binaries with full/relative path or with PATHfinder ✅
<br />✓ Added pipes ✅
<br />✓ Added redirections with >, >>, < and << ✅
<br />✓ Added Ctrl-C, and Ctrl-\ signal handling and Ctrl-D EOF termination ✅
<br /><br /> At this point, mandatory part is basically finished, except for tests and tweaks
### Bonus:
✓ Syntax is checked and complex commands with &&, || and parentheses are now supported ✅
<br />✓ Wildcard works with current directory (and others too 🤙) ✅
### Starting tests and tweaks:
- Fixed an issue on echo with multiple option -n not disappearing
- Fixed an issue on '$?' displaying undesired '?' after status
- Added processing of negative values as an argument for exit
- Fixed an issue concerning variables starting with a digit, those are not supposed to exist
